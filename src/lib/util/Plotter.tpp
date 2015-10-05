#include "Plotter.h"

namespace hypro {

template <typename Number>
Plotter<Number>::~Plotter() {
	mOutfile.close();
}

template <typename Number>
void Plotter<Number>::setFilename( const std::string &_filename ) {
	mFilename = _filename;
}

template <typename Number>
void Plotter<Number>::updateSettings( gnuplotSettings _settings ) {
	mSettings = _settings;
}

template <typename Number>
void Plotter<Number>::plot2d() const {
	mOutfile.open( mFilename + ".plt" );

	if ( !mObjects.empty() ) {
		// set object
		vector_t<Number> min = mObjects.begin()->second[0].rawCoordinates();
		vector_t<Number> max = mObjects.begin()->second[0].rawCoordinates();

		unsigned objectCount = 1;
		unsigned currId = 0;
		unsigned tmpId = 0;
		unsigned maxObj = mObjects.rbegin()->first;
		for ( auto objectIt = mObjects.begin(); objectIt != mObjects.end(); ++objectIt ) {
			if ( currId != objectIt->first ) {
				currId = objectIt->first;
				tmpId++;
				std::cout << "\rPlotting object " << tmpId << "/" << maxObj << std::flush;
			}

			mOutfile << "\n";
			mOutfile << "set object " << objectCount << " polygon from \\\n";

			for ( unsigned pointIndex = 0; pointIndex < objectIt->second.size(); ++pointIndex ) {
				assert( objectIt->second[pointIndex].dimension() <= 2 );  // TODO: Project to 2d
				if ( objectIt->second[pointIndex].dimension() == 0 ) {
					continue;
				}
				mOutfile << "  " << double( objectIt->second[pointIndex].at( 0 ) );

				// update min and max
				min( 0 ) =
					  min( 0 ) < objectIt->second[pointIndex].at( 0 ) ? min( 0 ) : objectIt->second[pointIndex].at( 0 );
				max( 0 ) =
					  max( 0 ) > objectIt->second[pointIndex].at( 0 ) ? max( 0 ) : objectIt->second[pointIndex].at( 0 );

				for ( unsigned d = 1; d < objectIt->second[pointIndex].dimension(); ++d ) {
					mOutfile << ", " << double( objectIt->second[pointIndex].at( d ) );
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
			// std::cout << double(objectIt->0].at(0)) << std::endl;
			mOutfile << "  " << double( objectIt->second[0].at( 0 ) );
			for ( unsigned d = 1; d < objectIt->second[0].dimension(); ++d ) {
				mOutfile << ", " << double( objectIt->second[0].at( d ) );
			}

			// color lookup
			std::string color = mSettings.color;
			if ( mObjectColors.find( objectIt->first ) != mObjectColors.end() ) {
				color = mObjectColors.at( objectIt->first );
			}

			if ( mSettings.fill )
				mOutfile << " front fs transparent solid 0.75 fc rgb '" << color << "'\n";
			else
				mOutfile << " front fs empty border lc rgb '" << color << "'\n";

			++objectCount;
		}

		std::map<unsigned, carl::Interval<double>> ranges;
		for ( unsigned d = 0; d < min.rows(); ++d ) {
			double rangeExt = double( ( max( d ) - min( d ) ) * 0.1 );
			ranges[d] = carl::Interval<double>(min( d ) - rangeExt, max( d ) + rangeExt );
		}

		// create plane functions
		int index = 0;
		if(!mPlanes.empty()){
			mOutfile << "\n";
			for( const auto& planePair : mPlanes ) {
				for( const auto& plane : planePair.second ) {
					assert(plane.dimension() == 2);
					mOutfile << "f_" << index << "(x) = " << -plane.normal()(0)/plane.normal()(1) << "*x+" << plane.offset()/plane.normal()(1) << "\n";
					++index;
				}
			}
			mOutfile << "\n";
		}
		

		if(mSettings.axes) {
			mOutfile << "set xzeroaxis \n";
			mOutfile << "set xtics axis \n";
			mOutfile << "set xrange ["<< ranges[0].lower() << ":" << ranges[0].upper() << "] \n";
			mOutfile << "set yzeroaxis \n";
			mOutfile << "set ytics axis \n";
			mOutfile << "set yrange ["<< ranges[1].lower() << ":" << ranges[1].upper() << "] \n";
		}

		mOutfile << "set size ratio 1\n";
		mOutfile << "set term post eps\n";
		mOutfile << "set output \"" << mFilename << ".eps\"";
		mOutfile << "\n";
		if(!mPlanes.empty()){
			mOutfile << "set multiplot \n";
			//plot all planes
			while(index > 0) {
				--index;
				mOutfile << "plot f_" << index << "(x) \n";
			}
		}
		
		mOutfile << "plot ";
		for ( unsigned d = 0; d < min.rows(); ++d ) {
			mOutfile << "[" << ranges[d].lower() << ":" << ranges[d].upper() << "] ";
		}
		mOutfile << "NaN notitle";
		if(!mPlanes.empty())
			mOutfile << "\n unset multiplot";
	}
	mOutfile.close();
	std::cout << std::endl << "Plotted to " << mFilename << ".plt" << std::endl;
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
	mPlanes.insert( std::make_pair( mId, _planes ) );
	return mId++;
}

template <typename Number>
void Plotter<Number>::setObjectColor( unsigned _id, const std::string _color ) {
	if ( _color != "" && mObjects.find( _id ) != mObjects.end() ) {
		mObjectColors[_id] = _color;
	} else if ( _color != "" && mPlanes.find( _id ) != mPlanes.end() ) {
		mObjectColors[_id] = _color;
	}
}

template <typename Number>
void Plotter<Number>::init( const std::string &_filename ) {
	mOutfile.open( _filename );
}

template <typename Number>
std::vector<Point<Number>> Plotter<Number>::grahamScan( const std::vector<Point<Number>> &_points ) {
	assert( _points.size() >= 3 );
	std::vector<Point<Number>> res;
	if ( !_points.empty() ) {
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
						if ( carl::AlmostEqual2sComplement( angle, newAngle, TOLLERANCE_ULPS ) ) {
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
}
