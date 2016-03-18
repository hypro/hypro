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


	if ( !mObjects.empty() || !mObjects.begin()->second.empty() || !mPoints.empty() ) {
		// set object
		vector_t<Number> min;
		vector_t<Number> max;
		if(!mObjects.begin()->second.empty()){
			min = mObjects.begin()->second[0].rawCoordinates();
			max = mObjects.begin()->second[0].rawCoordinates();
		} else {
			min = mPoints.begin()->second.rawCoordinates();
			max = mPoints.begin()->second.rawCoordinates();
		}

		mOutfile << "# settings\n";
		mOutfile << "set size ratio 1\n";
		mOutfile << "set term post eps\n";
		mOutfile << "set output \"" << mFilename << ".eps\n";
		unsigned objectCount = 1;
		unsigned currId = 0;
		unsigned tmpId = 0;
		unsigned maxObj = mObjects.size() + mPoints.size() + mPlanes.size();
		mOutfile << "\n# plotting sets\n";
		for ( auto objectIt = mObjects.begin(); objectIt != mObjects.end(); ++objectIt ) {
			if ( currId != objectIt->first ) {
				currId = objectIt->first;
				tmpId++;
				std::cout << "\rPlotting object " << tmpId << "/" << maxObj << std::flush;
			}
			if(objectIt->second.size() > 0){
				mOutfile << "set object " << std::dec << objectCount << " polygon from \\\n";
				for ( unsigned pointIndex = 0; pointIndex < objectIt->second.size(); ++pointIndex ) {
					assert( objectIt->second[pointIndex].dimension() <= 2 );  // TODO: Project to 2d
					if ( objectIt->second[pointIndex].dimension() == 0 ) {
						continue;
					}
					mOutfile << "  " << carl::toDouble( objectIt->second[pointIndex].at( 0 ) );

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
				if ( mObjectColors.find( objectIt->first ) != mObjectColors.end() ) {
					color = mObjectColors.at( objectIt->first );
				}

				if ( mSettings.fill )
					mOutfile << " front fs transparent solid 0.75 fc rgb '#" << std::hex << color << "' lw 0.2 \n";
				else
					mOutfile << " front fs empty border lc rgb '#" << std::hex << color << "' lw 0.2 \n";
			}
			++objectCount;
		}

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
			if(rangeExt != 0)
				ranges[d] = carl::Interval<double>(carl::toDouble(min( d )) - rangeExt, carl::toDouble(max( d )) + rangeExt );
			else
				rangeExt = carl::toDouble(carl::toDouble(min( d ))* 0.1);
				ranges[d] = carl::Interval<double>(carl::toDouble(min( d )) - rangeExt, carl::toDouble(max( d )) + rangeExt );
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
			mOutfile << "# plotting hyperplanes\n";
			for( const auto& planePair : mPlanes ) {
				for( const auto& plane : planePair.second ) {
					assert(plane.dimension() == 2);
					if(plane.normal()(1) == 0){
						mOutfile << "set arrow from " << carl::toDouble(plane.offset()/plane.normal()(0)) <<",graph(0,0) to " << carl::toDouble(plane.offset()/plane.normal()(0)) << ",graph(1,1) nohead\n";
					} else {
						mOutfile << "f_" << index << "(x) = " << carl::toDouble(-plane.normal()(0)/plane.normal()(1)) << "*x";
						double off = carl::toDouble(plane.offset()/plane.normal()(1));
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
					mOutfile << "{" << carl::toDouble(-plane.normal()(0)/plane.normal()(1)) << "*x";
					double off = carl::toDouble(plane.offset()/plane.normal()(1));
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

template <typename Number>
unsigned Plotter<Number>::addObject( const std::vector<Point<Number>> &_points, bool sorted ) {
	if ( !sorted ) {
		std::vector<Point<Number>> sortedPoints = grahamScan( _points );
		mObjects.insert( std::make_pair( mId, sortedPoints ) );
	} else {
		mObjects.insert( std::make_pair( mId, _points ) );
	}
	return mId++;
}

template <typename Number>
unsigned Plotter<Number>::addObject( const std::vector<std::vector<Point<Number>>> &_points, bool sorted ) {
	for ( const auto &part : _points ) {
		if ( !sorted ) {
			std::vector<Point<Number>> sortedPoints = grahamScan( part );
			mObjects.insert( std::make_pair( mId, sortedPoints ) );
		} else {
			mObjects.insert( std::make_pair( mId, part ) );
		}
	}
	return mId++;
}

template<typename Number>
unsigned Plotter<Number>::addObject( const std::vector<Hyperplane<Number>>& _planes ) {
	mPlanes.insert( std::make_pair( mId++, _planes ) );
	return mId;
}

template<typename Number>
unsigned Plotter<Number>::addObject( const Hyperplane<Number>& _plane ) {
	std::vector<Hyperplane<Number>> tmp;
	tmp.push_back(_plane);
	mPlanes.insert( std::make_pair( mId++, tmp ) );
	return mId;
}

template<typename Number>
void Plotter<Number>::addPoint( const Point<Number>& _point ) {
	mPoints.insert( std::make_pair( mId++, _point ) );
}

template<typename Number>
void Plotter<Number>::addPoints( const std::vector<Point<Number>>& _points ) {
	for(const auto& p : _points){
		mPoints.insert( std::make_pair( mId++, p ) );
	}
}

template<typename Number>
void Plotter<Number>::addVector( const vector_t<Number>& _vector ) {
	mVectors.insert( std::make_pair(mId++, _vector) );
}

template <typename Number>
void Plotter<Number>::setObjectColor( unsigned _id, const std::size_t _color ) {
	if ( _color != 0 && mObjects.find( _id ) != mObjects.end() ) {
		mObjectColors[_id] = _color;
	} else if ( _color != 0 && mPlanes.find( _id ) != mPlanes.end() ) {
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

	return std::move(res);
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
}
