#include "Plotter.h"

namespace hypro {

template <typename Number>
Plotter<Number>::~Plotter() {}

template <typename Number>
void Plotter<Number>::setFilename( const std::string &_filename ) {
	mFilename = _filename;
}

template <typename Number>
void Plotter<Number>::updateSettings( const gnuplotSettings& _settings ) {
	mSettings = _settings;
}

template<typename Number>
const gnuplotSettings& Plotter<Number>::settings() const {
	return mSettings;
}

template<typename Number>
gnuplotSettings& Plotter<Number>::rSettings() {
	return mSettings;
}

template <typename Number>
void Plotter<Number>::plot2d() const {
	prepareObjects(mSettings.dimensions.first,mSettings.dimensions.second);
	//std::cout << "Prepared objects." << std::endl;

	mOutfile.open( mFilename + ".plt" );

	if(!mVectors.empty()){
		mOutfile << "# plotting vectors normalized to length 1\n";
		unsigned arrowIndex = 0;
		for(auto& vector : mVectors) {
			vector_t<Number> normalized = vector.second/norm(vector.second);
			mOutfile << "set arrow " << arrowIndex++ << " from 0,0 to " << normalized(0) << "," << normalized(1) << "\n";
		}
		mOutfile << "\n";
	}


	if ( (!mObjects.empty() && !mObjects.begin()->second.empty()) || !mPoints.empty() ) {
		// std::cout << "mObjects.empty(): " << mObjects.empty() << std::endl;
		// std::cout << "mPoints.empty(): " << mPoints.empty() << std::endl;
		// std::cout << "mObjects.begin()->second.empty(): " << mObjects.begin()->second.empty() << std::endl;
		// std::cout << "mObjects.size: " << mObjects.size() << " and mPoints.size() " << mPoints.size() << std::endl;
		// set object
		vector_t<Number> min = vector_t<Number>(2);
		vector_t<Number> max = vector_t<Number>(2);
		min(0) = mLimits.first(mSettings.dimensions.first);
		min(1) = mLimits.first(mSettings.dimensions.second);
		max(0) = mLimits.second(mSettings.dimensions.first);
		max(1) = mLimits.second(mSettings.dimensions.second);
		// extend ranges
		std::map<unsigned, carl::Interval<double>> ranges;
		for ( unsigned d = 0; d < min.rows(); ++d ) {
			double rangeExt = carl::toDouble( ( carl::toDouble(max( d )) - carl::toDouble(min( d )) ) * 0.1 );
			if(rangeExt != 0){
				ranges[d] = carl::Interval<double>(carl::toDouble(min( d )) - rangeExt, carl::toDouble(max( d )) + rangeExt );
			} else{
				rangeExt = carl::toDouble(carl::toDouble(min( d ))* 0.1);
				ranges[d] = carl::Interval<double>(carl::toDouble(min( d )) - rangeExt, carl::toDouble(max( d )) + rangeExt );
			}
		}


		mOutfile << "# settings\n";
		if(mSettings.keepAspectRatio) {
			mOutfile << "set size square\n";
		}
		mOutfile << "set term pdf\n";
		mOutfile << "set output \"" << mFilename << ".pdf\n";
		if(mSettings.grid) {
			mOutfile << "set xtics autofreq\n";
			mOutfile << "set ytics autofreq\n";
			mOutfile << "set grid back\n";
		}
		if(mSettings.axes) {
			mOutfile << "# axis settings\n";
			mOutfile << "set xzeroaxis \n";
			mOutfile << "set zeroaxis \n";
            mOutfile << "set xtics axis \n";
            mOutfile << "set xrange ["<< ranges[0].lower() << ":" << ranges[0].upper() << "] \n";
			mOutfile << "set yzeroaxis \n";
            mOutfile << "set ytics axis \n";
            mOutfile << "set yrange ["<< ranges[1].lower() << ":" << ranges[1].upper() << "] \n";
		}
		unsigned objectCount = 1;
		unsigned currId = 0;
		unsigned tmpId = 0;
		mOutfile << "\n# plotting sets\n";

		//std::cout << "Start plotting sets." << std::endl;

		for ( auto objectIt = mObjects.begin(); objectIt != mObjects.end(); ++objectIt ) {
			if ( currId != objectIt->first ) {
				currId = objectIt->first;
				tmpId++;
				INFO("Plotting object " << tmpId << "/" << (mObjects.size() + mPoints.size() + mPlanes.size()));
			}
			if(objectIt->second.size() > 0){
				mOutfile << "set object " << std::dec << objectCount << " polygon from \\\n";
				for ( unsigned pointIndex = 0; pointIndex < objectIt->second.size(); ++pointIndex ) {
					assert( objectIt->second[pointIndex].dimension() == 2 );
					if ( objectIt->second[pointIndex].dimension() == 0 ) {
						continue;
					}
					mOutfile << "  " << carl::toDouble( objectIt->second[pointIndex].at( 0 ) );
					for ( unsigned d = 1; d < objectIt->second[pointIndex].dimension(); ++d ) {
						mOutfile << ", " << carl::toDouble( objectIt->second[pointIndex].at( d ) );
					}
					mOutfile << " to \\\n";
				}
				// assert(objectIt->objectIt->size()-1].dimension() <= 2); // TODO:
				// Project to 2d	TODO: REINSERT ASSERTION
				// std::cout << carl::toDouble(objectIt->0].at(0)) << std::endl;
				mOutfile << "  " << carl::toDouble( objectIt->second[0].at( 0 ) );
				for ( unsigned d = 1; d < objectIt->second[0].dimension(); ++d ) {
					mOutfile << ", " << carl::toDouble( objectIt->second[0].at( d ) );
				}

				// color lookup
				auto color = mSettings.color;
				//std::cout << "Lookup color for object " << objectIt->first << std::endl;
				if ( mObjectColors.find( objectIt->first ) != mObjectColors.end() ) {
					color = mObjectColors.at( objectIt->first );
					//std::cout << "Found" << std::endl;
				}

				if ( mSettings.fill )
					mOutfile << " front fs transparent solid 0.75 fc rgb '#" << std::hex << color << "' lw " << mSettings.linewidth << "\n";
				else
					mOutfile << " front fs empty border lc rgb '#" << std::hex << color << "' lw " << mSettings.linewidth << "\n";

				if(mSettings.cummulative){
					mOutfile << "\nplot ";
					for ( unsigned d = 0; d < min.rows(); ++d ) {
						mOutfile << "[" << ranges[d].lower() << ":" << ranges[d].upper() << "] ";
					}
					mOutfile << "NaN notitle \n";
				}
			}
			++objectCount;
		}

		//std::cout << "Done plotting sets." << std::endl;

		if(mPlanes.empty() && mPoints.empty()){
			mOutfile << "plot ";
			for ( unsigned d = 0; d < min.rows(); ++d ) {
				mOutfile << "[" << ranges[d].lower() << ":" << ranges[d].upper() << "] ";
			}
			mOutfile << "NaN notitle \n";
		}


		// create plane functions
		int index = 1;
		if(!mPlanes.empty()){
			mOutfile << "\n";
			mOutfile << "# plotting Halfspaces\n";
			for( const auto& planePair : mPlanes ) {
				for( const auto& plane : planePair.second ) {
					std::cout << "Plot plane " << plane << std::endl;
					assert(plane.dimension() == 2);
					vector_t<Number> normal = plane.normal();
					if(normal(1) == Number(0.0)){
						mOutfile << "set arrow from " << carl::toDouble(Number(plane.offset()/normal(0))) <<",graph(0,0) to " << carl::toDouble(Number(plane.offset()/normal(0))) << ",graph(1,1) nohead\n";
					} else {
						mOutfile << "f_" << index << "(x) = " << carl::toDouble(Number(-normal(0)/normal(1))) << "*x";
						double off = carl::toDouble(Number(plane.offset()/normal(1)));
						if(off > 0)
							mOutfile << "+";

						mOutfile << off << "\n";
						++index;
					}
				}
			}

		}

		if(!mPoints.empty()){
			mOutfile << "# plotting points\n";
			mOutfile << "set multiplot\n";
			mOutfile << "unset key\n";
			mOutfile << "set pointsize " << mSettings.pointSize << "\n";
			mOutfile << "set style line 1 lc rgb '#" << std::hex << mSettings.color << "'\n";
			mOutfile << "plot ";
			mOutfile << "'-' w p ls 1";
			for(unsigned pos = 1; pos < mPoints.size(); ++pos){
				mOutfile << ", '-' w p ls 1";
			}
			mOutfile << "\n";
		}
		for(auto pointIt = mPoints.begin(); pointIt != mPoints.end(); ++pointIt ){
			mOutfile << carl::toDouble(pointIt->second.at(0)) << " " << carl::toDouble(pointIt->second.at(1)) << "\n";
			mOutfile << "e\n";
		}
		mOutfile << "\n";

		if(!mPlanes.empty()){
			if(mPoints.empty()){
				mOutfile << "set multiplot \n";
				mOutfile << "unset key\n";
			}
			//plot all planes
			auto color = mSettings.color;
			mOutfile << "set style line 1 linecolor rgb '#" << std::hex << color << "' \n";
			while(index > 1){
				--index;
				mOutfile << "plot f_" << index << "(x) with lines linestyle 1\n";
			}
		}

		if(!mPlanes.empty() || !mPoints.empty())
			mOutfile << "\n unset multiplot\n";
	}
	mOutfile.close();
	std::cout << std::endl << "Plotted to " << mFilename << ".plt" << std::endl;
	mOutfile.close();
}

template<typename Number>
void Plotter<Number>::plotTex() const {
	prepareObjects(mSettings.dimensions.first,mSettings.dimensions.second);

	mOutfile.open( mFilename + ".tex" );

	if ( !mObjects.empty() || !mPoints.empty() ) {
		// set object
		vector_t<Number> min = mObjects.begin()->second[0].rawCoordinates();
		vector_t<Number> max = mObjects.begin()->second[0].rawCoordinates();

		mOutfile << "\\begin{tikzpicture}[]\n";

		unsigned objectCount = 1;
		unsigned currId = 0;
		unsigned tmpId = 0;
		unsigned maxObj = mObjects.size() + mPoints.size() + mPlanes.size();
		for ( auto objectIt = mObjects.begin(); objectIt != mObjects.end(); ++objectIt ) {
			if ( currId != objectIt->first ) {
				currId = objectIt->first;
				tmpId++;
				std::cout << "\rPlotting object " << tmpId << "/" << maxObj << std::flush;
			}

			if(mSettings.fill)
				mOutfile << "\t\\draw[blue, thick, fill=blue, fill opacity=.5]";
			else
				mOutfile << "\t\\draw[blue, thick]";

			for ( unsigned pointIndex = 0; pointIndex < objectIt->second.size()-1; ++pointIndex ) {
				assert( objectIt->second[pointIndex].dimension() <= 2 );  // TODO: Project to 2d
				if ( objectIt->second[pointIndex].dimension() == 0 ) {
					continue;
				}
				mOutfile << " (" << carl::toDouble( objectIt->second[pointIndex].at( 0 ) );

				// update min and max
				min( 0 ) =
					  min( 0 ) < objectIt->second[pointIndex].at( 0 ) ? min( 0 ) : objectIt->second[pointIndex].at( 0 );
				max( 0 ) =
					  max( 0 ) > objectIt->second[pointIndex].at( 0 ) ? max( 0 ) : objectIt->second[pointIndex].at( 0 );

				for ( unsigned d = 1; d < objectIt->second[pointIndex].dimension(); ++d ) {
					mOutfile << ", " << carl::toDouble( objectIt->second[pointIndex].at( d ) );
					// update min and max
					min( d ) = min( d ) < objectIt->second[pointIndex].at( d ) ? min( d )
																			   : objectIt->second[pointIndex].at( d );
					max( d ) = max( d ) > objectIt->second[pointIndex].at( d ) ? max( d )
																			   : objectIt->second[pointIndex].at( d );
				}
				mOutfile << ") -- ";
			}
			// last point
			assert( objectIt->second[objectIt->second.size()-1].dimension() <= 2 );  // TODO: Project to 2d
			if ( objectIt->second[objectIt->second.size()-1].dimension() == 0 ) {
				continue;
			}
			mOutfile << " (" << carl::toDouble( objectIt->second[objectIt->second.size()-1].at( 0 ) );

			// update min and max
			min( 0 ) =
				  min( 0 ) < objectIt->second[objectIt->second.size()-1].at( 0 ) ? min( 0 ) : objectIt->second[objectIt->second.size()-1].at( 0 );
			max( 0 ) =
				  max( 0 ) > objectIt->second[objectIt->second.size()-1].at( 0 ) ? max( 0 ) : objectIt->second[objectIt->second.size()-1].at( 0 );

			for ( unsigned d = 1; d < objectIt->second[objectIt->second.size()-1].dimension(); ++d ) {
				mOutfile << ", " << carl::toDouble( objectIt->second[objectIt->second.size()-1].at( d ) );
				// update min and max
				min( d ) = min( d ) < objectIt->second[objectIt->second.size()-1].at( d ) ? min( d )
																		   : objectIt->second[objectIt->second.size()-1].at( d );
				max( d ) = max( d ) > objectIt->second[objectIt->second.size()-1].at( d ) ? max( d )
																		   : objectIt->second[objectIt->second.size()-1].at( d );
			}
			mOutfile << ") -- cycle;\n";

			//// color lookup
			//auto color = mSettings.color;
			//if ( mObjectColors.find( objectIt->first ) != mObjectColors.end() ) {
			//	color = mObjectColors.at( objectIt->first );
			//}
//
//			//if ( mSettings.fill )
//			//	mOutfile << " front fs transparent solid 0.75 fc rgb '#" << std::hex << color << "'\n";
//			//else
			//	mOutfile << " front fs empty border lc rgb '#" << std::hex << color << "'\n";

			++objectCount;
		}

		mOutfile << "\n";

		// collect ranges
		for(auto pointIt = mPoints.begin(); pointIt != mPoints.end(); ++pointIt ){
			// update min and max
			min(0) = min(0) > pointIt->second.at(0) ? pointIt->second.at(0) : min(0);
			min(1) = min(1) > pointIt->second.at(1) ? pointIt->second.at(1) : min(1);
			max(0) = max(0) < pointIt->second.at(0) ? pointIt->second.at(0) : max(0);
			max(1) = max(1) < pointIt->second.at(1) ? pointIt->second.at(1) : max(1);
		}
		std::map<unsigned, carl::Interval<double>> ranges;
		for ( unsigned d = 0; d < min.rows(); ++d ) {
			double rangeExt = carl::toDouble( ( carl::toDouble(max( d )) - carl::toDouble(min( d )) ) * 0.1 );
			ranges[d] = carl::Interval<double>(carl::toDouble(min( d )) - rangeExt, carl::toDouble(max( d )) + rangeExt );
		}
		assert(ranges.size() == 2);

		// create plane functions
		if(!mPlanes.empty()){
			mOutfile << "\n";
			for( const auto& planePair : mPlanes ) {
				for( const auto& plane : planePair.second ) {
					assert(plane.dimension() == 2);
					mOutfile << "\t\\draw[domain="<< ranges[0].lower() << ":" << ranges[0].upper() <<", smooth, variable=\\x] plot ({\\x},";
					mOutfile << "{" << carl::toDouble(Number(-plane.normal()(0)/plane.normal()(1))) << "*x";
					double off = carl::toDouble(Number(plane.offset()/plane.normal()(1)));
					if(off > 0)
						mOutfile << "+" << off << "}";
					else
						mOutfile << "}";

					mOutfile << ");\n";
				}
			}

		}

		if(mSettings.axes) {
			mOutfile << "\t\\draw[help lines]";
			mOutfile << " (" << ranges[0].lower() << "," << ranges[1].lower() << ") grid (" << ranges[0].upper() << "," << ranges[1].upper() << ");\n";
		}

		for(auto pointIt = mPoints.begin(); pointIt != mPoints.end(); ++pointIt ){
			mOutfile << "\t\\fill[fill=blue] (" << carl::toDouble(pointIt->second.at(0)) << "," << carl::toDouble(pointIt->second.at(1)) << ") circle [radius=2pt];\n";
		}

		mOutfile << "\\end{tikzpicture}\n";
	}
	std::cout << std::endl << "Plotted to " << mFilename << ".tex" << std::endl;
	mOutfile.close();
}

template<typename Number>
void Plotter<Number>::plotGen() const {
	prepareObjects(mSettings.dimensions.first,mSettings.dimensions.second);

	mOutfile.open( mFilename + ".gen" );

	if(!mVectors.empty()){
		// TODO: implement gen file plotting for vectors.
	}

	if ( !mObjects.empty() || !mObjects.begin()->second.empty() || !mPoints.empty() ) {
		for ( auto objectIt = mObjects.begin(); objectIt != mObjects.end(); ++objectIt ) {
			if(objectIt->second.size() > 0){
				for ( unsigned pointIndex = 0; pointIndex < objectIt->second.size(); ++pointIndex ) {
					assert( objectIt->second[pointIndex].dimension() == 2 );
					if ( objectIt->second[pointIndex].dimension() == 0 ) {
						continue;
					}
					mOutfile << carl::toDouble( objectIt->second[pointIndex].at( 0 ) );
					for ( unsigned d = 1; d < objectIt->second[pointIndex].dimension(); ++d ) {
						mOutfile << " " << carl::toDouble( objectIt->second[pointIndex].at( d ) );
					}
					mOutfile << "\n";
				}
				mOutfile << carl::toDouble( objectIt->second[0].at( 0 ) );
				for ( unsigned d = 1; d < objectIt->second[0].dimension(); ++d ) {
					mOutfile << " " << carl::toDouble( objectIt->second[0].at( d ) );
				}
				mOutfile << "\n";
			}
			mOutfile << "\n\n\n";
		}

		// create plane functions
		if(!mPlanes.empty()){
			// TODO: implement.
		}

		if(!mPoints.empty()){
			// TODO: implement.
		}
	}
	mOutfile.close();
	std::cout << std::endl << "Plotted to " << mFilename << ".gen" << std::endl;
}

template <typename Number>
unsigned Plotter<Number>::addObject( const std::vector<Point<Number>> &_points ) {
	// reduce dimensions
	if(!_points.empty()){
		// initialize limits
		if(mOriginalObjects.empty() && mOriginalPoints.empty()){
			mLimits.first = _points.begin()->rawCoordinates();
			mLimits.second = _points.begin()->rawCoordinates();
		}
		// update limits
		for(const auto& point : _points) {
			for(unsigned d = 0; d < mLimits.first.rows(); ++d){
				mLimits.first(d) = mLimits.first(d) > point.rawCoordinates()(d) ? point.rawCoordinates()(d) : mLimits.first(d);
				mLimits.second(d) = mLimits.second(d) < point.rawCoordinates()(d) ? point.rawCoordinates()(d) : mLimits.second(d);
			}
		}

		mOriginalObjects.insert( std::make_pair( mId, _points ) );
		mId++;
		return (mId-1);
	}
	return 0;
}

template <typename Number>
unsigned Plotter<Number>::addObject( const std::vector<std::vector<Point<Number>>> &_points ) {
	for ( const auto &part : _points ) {
		addObject(part);
		--mId;
	}
	mId++;
	return mId-1;
}

template<typename Number>
unsigned Plotter<Number>::addObject( const std::vector<Halfspace<Number>>& _planes ) {
	mOriginalPlanes.insert( std::make_pair( mId++, _planes ) );
	return mId;
}

template<typename Number>
unsigned Plotter<Number>::addObject( const Halfspace<Number>& _plane ) {
	std::vector<Halfspace<Number>> tmp;
	tmp.push_back(_plane);
	mOriginalPlanes.insert( std::make_pair( mId++, tmp ) );
	return mId;
}

template<typename Number>
unsigned Plotter<Number>::addPoint( const Point<Number>& _point ) {
	// initialize limits
	if(mOriginalObjects.empty() && mOriginalPoints.empty()){
		mLimits.first = _point.rawCoordinates();
		mLimits.second = _point.rawCoordinates();
	}
	// update limits
	for(unsigned d = 0; d < mLimits.first.rows(); ++d){
		mLimits.first(d) = mLimits.first(d) > _point.rawCoordinates()(d) ? _point.rawCoordinates()(d) : mLimits.first(d);
		mLimits.second(d) = mLimits.second(d) < _point.rawCoordinates()(d) ? _point.rawCoordinates()(d) : mLimits.second(d);
	}

	mOriginalPoints.insert( std::make_pair( mId, _point ) );
	return mId++;
}

template<typename Number>
unsigned Plotter<Number>::addPoints( const std::vector<Point<Number>>& _points ) {
	for(const auto& p : _points){
		addPoint(p);
		--mId;
	}
	mId++;
	return mId-1;
}

template<typename Number>
void Plotter<Number>::addVector( const vector_t<Number>& _vector ) {
	mOriginalVectors.insert( std::make_pair(mId++, _vector) );
}

template <typename Number>
void Plotter<Number>::setObjectColor( unsigned _id, const std::size_t _color ) {
	if ( _color != 0 && mOriginalObjects.find( _id ) != mOriginalObjects.end() ) {
		mObjectColors[_id] = _color;
	} else if ( _color != 0 && mOriginalPlanes.find( _id ) != mOriginalPlanes.end() ) {
		mObjectColors[_id] = _color;
	}
}

template <typename Number>
void Plotter<Number>::init( const std::string &_filename ) {
	mOutfile.open( _filename );
}

template <typename Number>
std::vector<Point<Number>> Plotter<Number>::grahamScan( const std::vector<Point<Number>> &_points ) {
	std::vector<Point<Number>> res;
	if(_points.size() < 3){
		return _points;
	}

	// initialize -> find minimum Point
	Point<Number> min = _points[0];
	std::map<Number, Point<Number>> sortedPoints;
	for ( const auto &point : _points ) {
		assert( point.dimension() == 2 );
		if ( point < min ) {
			min = point;
		}
	}

	// std::cout << "Minimum: " << min.rawCoordinates().transpose() <<
	// std::endl;

	// sort Points according to polar angle -> we have to insert manually
	// (because of double imprecision)
	for ( const auto &point : _points ) {
		if ( point != min ) {
			// std::cout << "Try to insert " << point << std::endl;
			Number angle = point.polarCoordinates( min ).at( 1 );
			// std::cout << "Computed polar angle: " << angle << std::endl;
			if ( sortedPoints.empty() ) {
				// std::cout << "points empty, simply insert." << std::endl;
				sortedPoints.insert( std::make_pair( angle, point ) );
			} else {
				// std::cout << "Compare." << std::endl;
				for ( auto pos = sortedPoints.begin(); pos != sortedPoints.end(); ) {
					// if equal, take the one with bigger radial component
					// std::cout << "Consider " << pos->second << ", angle: ";
					Number newAngle = pos->second.polarCoordinates( min ).at( 1 );
					// std::cout << newAngle << std::endl;
					if ( angle == newAngle ) {
						// if equal, compare radial coordinate (distance)
						// std::cout << "AlmostEqual2sComplement" << std::endl;
						if ( pos->second.polarCoordinates( min )[0] < point.polarCoordinates( min )[0] ) {
							// std::cout << "sortedPoints erase " << pos->second <<
							// std::endl;
							pos = sortedPoints.erase( pos );
							sortedPoints.insert( std::make_pair( angle, point ) );
						}
						break;
					}
					// we assume to be sorted, so check all angles, which are smaller or
					// equal for equality -
					// afterwards simply insert
					else if ( angle > newAngle ) {  // not equal and smaller -> continue
													// search (at end, simply insert)
						++pos;
						if ( pos == sortedPoints.end() ) {
							sortedPoints.insert( std::make_pair( angle, point ) );
							break;
						}
					} else {  // larger and not equal until this point -> simply insert
						sortedPoints.insert( std::make_pair( angle, point ) );
						break;
					}
				}
				// std::cout << "End Compare." << std::endl;
			}
		}
	}

	// for(const auto& pair : sortedPoints)
	//	std::cout << "sorted: " << pair.first << ", " <<
	// pair.second.rawCoordinates().transpose() << std::endl;

	// prepare stack -> initialize with 2 points
	if(sortedPoints.empty()) {
		res.emplace_back(min);
		return res;
	}
	assert( sortedPoints.size() >= 1 );
	std::stack<Point<Number>> stack;
	stack.push( min );
	stack.push( sortedPoints.begin()->second );
	sortedPoints.erase( sortedPoints.begin() );
	unsigned i = 0;
	unsigned n = sortedPoints.size();

	// main loop -> check the two topmost elements of the stack and one third,
	// new point
	while ( i < n ) {
		Point<Number> p1 = stack.top();
		stack.pop();
		Point<Number> p2 = stack.top();
		stack.pop();
		// std::cout << __func__ << ": " << p2.rawCoordinates().transpose() << "
		// -- " <<
		// p1.rawCoordinates().transpose() << " -- " <<
		// sortedPoints.begin()->second.rawCoordinates().transpose() <<
		// std::endl;
		if ( isLeftTurn( p2, p1, sortedPoints.begin()->second ) ) {
			// reinsert and add new point
			stack.push( p2 );
			stack.push( p1 );
			stack.push( sortedPoints.begin()->second );
			sortedPoints.erase( sortedPoints.begin() );
			++i;
		} else {
			// only reinsert second -> equal to removing the topmost object of the
			// stack
			// std::cout << "Drop " << p1.rawCoordinates().transpose() << std::endl;
			stack.push( p2 );
			if ( stack.size() < 2 ) {
				// in this case simply insert, as the stack has to contain at least 2
				// points
				stack.push( sortedPoints.begin()->second );
				sortedPoints.erase( sortedPoints.begin() );
				++i;
			}
		}
	}

	// write result
	while ( !stack.empty() ) {
		res.push_back( stack.top() );
		stack.pop();
	}

	return res;
}

template <typename Number>
bool Plotter<Number>::isLeftTurn( const Point<Number> &a, const Point<Number> &b, const Point<Number> &c ) {
	assert( a.dimension() == 2 );
	assert( b.dimension() == 2 );
	assert( c.dimension() == 2 );

	Number val = ( ( b.rawCoordinates()( 0 ) - a.rawCoordinates()( 0 ) ) *
				   ( c.rawCoordinates()( 1 ) - a.rawCoordinates()( 1 ) ) ) -
				 ( ( c.rawCoordinates()( 0 ) - a.rawCoordinates()( 0 ) ) *
				   ( b.rawCoordinates()( 1 ) - a.rawCoordinates()( 1 ) ) );
	// Number val = c.polarCoordinates(a,false)[1] -
	// b.polarCoordinates(a,false)[1];

	return ( val > 0 );
}

template<typename Number>
void Plotter<Number>::prepareObjects(unsigned firstDim, unsigned secondDim) const {
	if(mLastDimensions.first < 0 || (unsigned(mLastDimensions.first) != firstDim && unsigned(mLastDimensions.second) != secondDim)){
		std::vector<unsigned> targetDimensions;
		targetDimensions.push_back(firstDim);
		targetDimensions.push_back(secondDim);

		// reduce and sort objects
		if(!mOriginalObjects.empty()){
			//std::cout << "Prepare " << mOriginalObjects.size() << " objects. Reduce to dimensions " << targetDimensions << std::endl;
			for(const auto& objPair : mOriginalObjects){
				vector<Point<Number>> tmp;
				for(const auto& point : objPair.second)
					tmp.push_back(point.reduceToDimensions(targetDimensions));

				// sort
				// std::cout << "sort (" << tmp.size() << " points)" << std::endl;
				tmp = grahamScan(tmp);
				mObjects.insert(std::make_pair(objPair.first, tmp));
			}
		}

		// reduce planes
		if(!mOriginalPlanes.empty()){
			for(const auto& planePair : mOriginalPlanes)
				mPlanes.insert(planePair);
		}

		// reduce points
		if(!mOriginalPoints.empty()){
			for(const auto& pointPair : mOriginalPoints)
				mPoints.insert(std::make_pair(pointPair.first, pointPair.second.reduceToDimensions(targetDimensions)));
		}

		// reduce vectors
		if(!mOriginalVectors.empty()){
			for(const auto& vectorPair : mOriginalVectors){
				vector_t<Number> tmp = vector_t<Number>(2);
				tmp(0) = vectorPair.second(mSettings.dimensions.first);
				tmp(0) = vectorPair.second(mSettings.dimensions.second);
				mVectors.insert(std::make_pair(vectorPair.first, tmp));
			}
		}

		// update mLastDimensions
		mLastDimensions.first = firstDim;
		mLastDimensions.second = secondDim;
	}
}

} // namespace hypro
