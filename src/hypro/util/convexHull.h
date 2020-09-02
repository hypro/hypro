/*
 * Contains utilities to create the convex hull.
 * @file   convexHull.h
 * @author tayfun
 *
 * @since       2014-12-10
 * @version     2015-11-09
 */

#pragma once

#include "../datastructures/Facet.h"
#include "../datastructures/Halfspace.h"
#include "../datastructures/Point.h"
#include "../datastructures/Ridge.h"

#include <queue>

namespace hypro {

template <typename Number>
static bool maxRank( const std::vector<Point<Number>>& points, const Point<Number>& point ) {
	// std::cout << __func__ << std::endl;
	matrix_t<Number> matrix = matrix_t<Number>( point.rawCoordinates().size(), points.size() );

	for ( unsigned i = 0; i < matrix.cols(); i++ ) {
		if ( i < matrix.cols() - 1 ) {
			matrix.col( i ) = points.at( i + 1 ).rawCoordinates() - points.at( 0 ).rawCoordinates();
		} else {
			matrix.col( i ) = point.rawCoordinates() - points.at( 0 ).rawCoordinates();
		}
	}

	return matrix.fullPivLu().rank() == (unsigned)( matrix.cols() );  // TODO This is expensive, can we get rid of that?
}

/*
 * Creates initial Convex Hull in dimension d with d+1 Points out of all the points given. Neighbor relationship of the
 * facets are saved in neighbors.
 * @return The list of facets, i.e. Halfspaces with dimension d-1 who form the Convex Hull.
 */
template <typename Number>
static void initConvexHull( const std::vector<Point<Number>>& points, std::vector<std::shared_ptr<Facet<Number>>>& facets ) {
	unsigned dimCheck = effectiveDimension( points );
	unsigned dimension = points.at( 0 ).dimension();

	if ( dimCheck == dimension ) {
		std::vector<Point<Number>> initialPoints;
		unsigned minIndex = 0, maxIndex = 0;  // determine min and max of first value

		for ( unsigned j = 0; j < points.size(); j++ ) {
			if ( points.at( minIndex ).rawCoordinates()( 0 ) > points.at( j ).rawCoordinates()( 0 ) ) {
				minIndex = j;
			}
			if ( points.at( maxIndex ).rawCoordinates()( 0 ) < points.at( j ).rawCoordinates()( 0 ) ) {
				maxIndex = j;
			}
		}

		initialPoints.push_back( points.at( minIndex ) );
		initialPoints.push_back( points.at( maxIndex ) );

		// search rest for rank d accordingly for each dimension
		for ( unsigned d = 1; d < dimension; d++ ) {
			for ( unsigned i = 0; i < points.size(); i++ ) {
				if ( std::find( initialPoints.begin(), initialPoints.end(), points.at( i ) ) == initialPoints.end() ) {
					if ( maxRank( initialPoints, points.at( i ) ) ) {
						initialPoints.push_back( points.at( i ) );
						break;
					}
				}
			}
		}

		// search for unused point as last member for initConvexhull
		unsigned index = 0;
		while ( initialPoints.size() < dimension + 1 && index < points.size() ) {
			if ( std::find( initialPoints.begin(), initialPoints.end(), points.at( index ) ) == initialPoints.end() ) {
				initialPoints.push_back( points.at( index ) );
			}
			index++;
		}

		// inti facets
		for ( unsigned i = 0; i < dimension + 1; i++ ) {
			facets.emplace_back( std::make_shared<Facet<Number>>( Facet<Number>() ) );
		}
		for ( unsigned i = 0; i < dimension + 1; ++i ) {
			std::vector<Point<Number>> points_for_facet;
			for ( unsigned j = 0; j < dimension + 1; ++j ) {
				if ( i != j ) {
					points_for_facet.push_back( initialPoints.at( j ) );
				}
			}
			facets.at( i )->setPoints( std::move( points_for_facet ), initialPoints.at( i ) );
		}

		// Add neighbors
		for ( unsigned i = 0; i < facets.size(); ++i ) {
			for ( unsigned j = 0; j < facets.size(); ++j ) {
				if ( i != j ) {
					facets.at( i )->addNeighbor( facets.at( j ) );
				}
			}
		}

	} else {
		std::cout << __func__ << " : " << __LINE__ << "Error: Inconsistent point set " << std::endl;
		assert( false );
		facets = std::vector<std::shared_ptr<Facet<Number>>>();
	}
}

/*
 * @return The list of points that are not contained by the facets.
 */
template <typename Number>
static void pointsNotContainedInFacets( const std::vector<Point<Number>>& points, const std::vector<std::shared_ptr<Facet<Number>>>& facets, std::vector<Point<Number>>& unassignedPoints, std::vector<Point<Number>>& assignedPoints ) {
	// std::cout << __func__ << std::endl;
	unassignedPoints.clear();
	std::vector<Point<Number>> pointsInFacets;

	for ( std::shared_ptr<Facet<Number>> facet : facets ) {
		for ( Point<Number> p : facet->vertices() ) {
			pointsInFacets.push_back( p );
		}
	}
	// Stefan: pointsInFacets holds all generating points of the given facets.

	for ( Point<Number> point : points ) {
		if ( std::find( pointsInFacets.begin(), pointsInFacets.end(), point ) != pointsInFacets.end() ) {
			assignedPoints.push_back( point );
		} else {
			unassignedPoints.push_back( point );
		}
	}
	// Stefan: removables holds the indices of the points in points, which are contained in one of the facets.
}

/*
 * Determines the neighbors of the Halfspaces. Neighbors are taken from neighbors.
 * @return The list of neighbors from the Halfspaces.
 */
template <typename Number>
static std::vector<std::shared_ptr<Facet<Number>>> getFacetsNeighbors( const std::vector<std::shared_ptr<Facet<Number>>>& facets ) {
	// std::cout << __func__ << std::endl;
	std::vector<std::shared_ptr<Facet<Number>>> result;

	if ( !facets.empty() ) {
		for ( auto facet : facets ) {  // get 'all' neighbors
			for ( auto neighbor : facet->neighbors() ) {
				if ( std::find( result.begin(), result.end(), neighbor ) == result.end() && std::find( facets.begin(), facets.end(), neighbor ) == facets.end() ) {
					result.push_back( neighbor );  // insert if it's a new neighbor and it isn't one of the given facets
				}
			}
		}
	}

	return result;
}
/*
 * Determines the ridges between the facets and their neighbors.polytope::
 * @return The list of ridges, i.e. Halfspaces with dimension d-2 who are the intersection of two facets.
 */
template <typename Number>
static std::vector<Ridge<Number>> getRidges( const std::vector<std::shared_ptr<Facet<Number>>>& facets ) {
	// std::cout << __func__ << std::endl;
	std::vector<Ridge<Number>> result;

	if ( !facets.empty() ) {
		std::vector<std::shared_ptr<Facet<Number>>> neighbors = getFacetsNeighbors( facets );
		for ( auto facet : facets ) {
			for ( auto neighbor : neighbors ) {
				if ( facet->isNeighbor( neighbor ) ) {
					Ridge<Number> newRidge( facet, neighbor );
					result.push_back( newRidge );
				}
			}
		}
	}

	return result;
}

template <typename Number>
static std::vector<Ridge<Number>> getRidges( std::shared_ptr<Facet<Number>> facet ) {
	// std::cout << __func__ << std::endl;
	std::vector<Ridge<Number>> result;

	if ( !facet->empty() ) {
		//std::cout << "_____________insde getRidges - Amount of neighbors is " << facet->neighbors().size() << std::endl;
		for ( auto neighbor : facet->neighbors() ) {
			//std::cout << "_____________insde getRidges - call of neighbor of " << facet->getNormal() << std::endl;

			Ridge<Number> newRidge( facet, neighbor );
			result.push_back( newRidge );
		}
	}

	return result;
}

template <typename Number>
static bool checkInsideRidge( const Ridge<Number>& ridge, const Point<Number>& point ) {
	// std::cout << __func__ << std::endl;
	for ( unsigned i = 0; i < ridge.vertices(); i++ ) {
		if ( point == ridge.vertices().at( i ) ) {
			return true;
		}
	}
	return false;
}

template <typename Number>
static std::vector<std::shared_ptr<Facet<Number>>> shareRidge( const std::vector<std::shared_ptr<Facet<Number>>>& facets, const Ridge<Number>& ridge ) {
	// std::cout << __func__ << std::endl;
	std::vector<std::shared_ptr<Facet<Number>>> result;
	std::vector<Point<Number>> ridgepoints = ridge.vertices();

	for ( const auto& facet : facets ) {
		std::vector<Point<Number>> points = facet->vertices();
		unsigned checkvalue = 0;
		for ( auto point : points ) {
			for ( auto ridgepoint : ridgepoints ) {
				if ( point == ridgepoint ) {
					checkvalue++;
				}
			}
		}
		if ( checkvalue == ridgepoints.size() ) {
			result.push_back( facet );
		}
	}

	return result;
}

/*
 * Checks for each facet if it has at least one point above. If it has it is not outside and will be returned. Note that
 * the input facets is modified to
 * contain only facets with an empty outside set.
 * @return The list of facets that have at least one point above.
 */
template <typename Number>
static void removeBorderFacets( std::vector<std::shared_ptr<Facet<Number>>>& facets, std::queue<std::shared_ptr<Facet<Number>>>& result ) {
	// std::cout << __func__ << std::endl;
	for ( std::size_t i = facets.size(); i > 0; i-- ) {
		if ( !facets.at( i - 1 )->getOutsideSet().empty() ) {
			result.push( facets.at( i - 1 ) );
			facets.erase( facets.begin() + i - 1 );
		}
	}
}

/*
 * Checks if two facets are neighbors by determining the number of points they share
 */
template <typename Number>
static bool neighborCheck( std::shared_ptr<Facet<Number>> facet1, std::shared_ptr<Facet<Number>> facet2 ) {
	// std::cout << __func__ << std::endl;
	int checkValue = facet1->vertices().at( 0 ).dimension() - 1;  // number of points they have to share to be neighbors
	int currentValue = 0;										  // number of points that are confirmed to be shared

	for ( auto vertex1 : facet1->vertices() ) {
		for ( auto vertex2 : facet2->vertices() ) {
			if ( vertex1 == vertex2 ) {
				currentValue++;
			}
		}
	}
	if ( checkValue == currentValue ) return true;

	return false;
}

/*
 * Finds the neighbors of the new created Facets among themselves
 */
template <typename Number>
static void determineNeighbors( std::vector<std::shared_ptr<Facet<Number>>>& facets ) {
	// std::cout << __func__ << std::endl;
	for ( auto facet : facets ) {
		for ( auto facet2 : facets ) {
			if ( neighborCheck( facet, facet2 ) ) {	 // check all pairs of new facets if they are neighbors
				facet->addNeighbor( facet2 );
				facet2->addNeighbor( facet );
			}
		}
	}
}

/*
 * Finds the inside Point to a ridge and an associated facet, which is the point in the facet which isn't in the ridge
 */
template <typename Number>
static Point<Number> findInsidePoint( const Ridge<Number>& ridge, const std::shared_ptr<Facet<Number>>& _facet ) {
	// std::cout << __func__ << std::endl;
	for ( Point<Number> point1 : _facet->vertices() ) {
		bool found = true;
		for ( Point<Number> point2 : ridge.vertices() ) {
			if ( point1 == point2 ) {
				found = false;
				break;
			}
		}
		if ( found ) return point1;
	}
	assert( false );
	return Point<Number>();
}

template <typename Number>
static bool includeFacet( std::shared_ptr<Facet<Number>> facet1, std::shared_ptr<Facet<Number>> facet2 ) {
	// std::cout << __func__ << std::endl;
	bool result;

	if ( *facet1 == *facet2 ) {
		return true;
	} else {
		std::size_t checkValue = ( facet2->vertices().size() < facet1->vertices().size() ) ? facet2->vertices().size() : facet1->vertices().size();

		std::size_t currentValue = 0;
		for ( auto vertex1 : facet1->vertices() ) {
			for ( auto vertex2 : facet2->vertices() ) {
				if ( vertex1 == vertex2 ) {
					currentValue++;
				}
			}
		}
		result = ( checkValue == currentValue );
	}

	return result;
}

template <typename Number>
static std::map<Point<Number>, std::set<Point<Number>>> setNeighborhoodOfPointsBeforehand( std::vector<std::shared_ptr<Facet<Number>>>& facets ) {
	std::map<Point<Number>, std::set<Point<Number>>> res;

	for ( const auto& facet : facets ) {
		for ( const auto& j : facet->vertices() ) {
			for ( const auto& k : facet->vertices() ) {
				if ( j != k ) {
					res[j].insert( k );
				}
			}
		}
	}

	return res;
}

template <typename Number>
static std::vector<std::shared_ptr<Facet<Number>>> maximizeFacets( std::vector<std::shared_ptr<Facet<Number>>>& facets ) {
	// std::cout << __func__ << std::endl;
	std::vector<std::shared_ptr<Facet<Number>>> result;

	while ( !facets.empty() ) {
		std::shared_ptr<Facet<Number>> newFacet = facets.front();
		facets.erase( facets.begin() );

		for ( unsigned n = 0; n < facets.size(); n++ ) {
			std::shared_ptr<Facet<Number>> neighbor = facets.at( n );

			if ( neighborCheck( newFacet, neighbor ) ) {
				// find vertices of newFacet and neighbor which are not in the other facet
				Point<Number> point1;
				std::vector<Point<Number>> vertices_newFacet = newFacet->vertices();

				for ( auto vertex : neighbor->vertices() ) {
					if ( std::find( vertices_newFacet.begin(), vertices_newFacet.end(), vertex ) == vertices_newFacet.end() ) {
						point1 = vertex;
						break;
					}
				}

				// is neighbor a relevant facet?
				//if (carl::AlmostEqual2sComplement(newFacet->getDist(point1)+(Number) 1, (Number) 1)) { // TODO compare with 0 and not with +1
				if ( newFacet->getDist( point1 ) == 0 ) {
					newFacet->addPoint( point1 );  // update newFacet - point1 and neighbors of neighbor
					for ( auto neighborOfneighbor : neighbor->rNeighbors() ) {
						if ( !newFacet->isNeighbor( neighborOfneighbor ) ) newFacet->addNeighbor( neighborOfneighbor );
					}

					facets.erase( facets.begin() + n );	 // remove non-relevant neighbor
					n--;
				}
			} else if ( includeFacet( newFacet, neighbor ) ) {
				facets.erase( facets.begin() + n );
				n--;
			}
		}

		result.push_back( newFacet );
	}

	std::vector<unsigned> toErase;
	// check result - TODO correct?
	for ( unsigned i = 0; i < result.size() - 1; ++i ) {
		for ( unsigned j = i + 1; j < result.size(); ++j ) {
			if ( result.at( i ) != result.at( j ) && includeFacet( result.at( i ), result.at( j ) ) ) {
				//std::cout << "convexHull.h " << __func__ << " : " << __LINE__ << " remove non-relevant facet" << std::endl;
				if ( std::find( toErase.begin(), toErase.end(), j ) == toErase.end() ) {
					toErase.push_back( j );
				}
			}
		}
	}
	std::reverse( toErase.begin(), toErase.end() );

	for ( unsigned erase : toErase ) {
		//std::cout << "Erase: " << erase << std::endl;
		result.erase( result.begin() + erase );
	}

	return result;
}

template <typename Number>
static std::shared_ptr<Facet<Number>> newNeighbor( std::shared_ptr<Facet<Number>> oldNeighbor, const std::vector<std::shared_ptr<Facet<Number>>>& newFacets ) {
	// std::cout << __func__ << std::endl;
	for ( unsigned i = 0; i < newFacets.size(); i++ ) {
		if ( neighborCheck( oldNeighbor, newFacets.at( i ) ) ) {
			return newFacets.at( i );
		}
	}

	return oldNeighbor;
}

template <typename Number>
static void setNeighborhoodOfPoints( std::vector<std::shared_ptr<Facet<Number>>>& facets ) {
	// std::cout << __func__ << std::endl;

	if ( facets.at( 0 )->vertices().at( 0 ).dimension() == 2 ) {  // 2D
		for ( auto facet : facets ) {
			facet->rVertices().at( 0 ).addNeighbor( facet->rVertices().at( 1 ) );
			facet->rVertices().at( 1 ).addNeighbor( facet->rVertices().at( 0 ) );
		}
	}

	else if ( facets.at( 0 )->vertices().at( 0 ).dimension() > 2 ) {  // 3D, 4D , ...
		for ( auto facet1 : facets ) {
			for ( auto facet2 : facets ) {
				if ( neighborCheck( facet1, facet2 ) ) {
					std::vector<unsigned> facet1Vector, facet2Vector;

					for ( unsigned k = 0; k < facet1->vertices().size(); k++ ) {
						for ( unsigned l = 0; l < facet2->vertices().size(); l++ ) {
							if ( facet1->vertices().at( k ) == facet2->vertices().at( l ) ) {
								facet1Vector.push_back( k );
								facet2Vector.push_back( l );
							}
						}
					}

					for ( unsigned facet1Value : facet1Vector ) {
						for ( unsigned facet1Value2 : facet1Vector ) {
							if ( facet1Value != facet1Value2 ) {
								facet1->rVertices().at( facet1Value ).addNeighbor( ( facet1->vertices().at( facet1Value2 ) ) );
								facet1->rVertices().at( facet1Value2 ).addNeighbor( ( facet1->vertices().at( facet1Value ) ) );
							}
						}
					}

					for ( unsigned facet2Value : facet2Vector ) {
						for ( unsigned facet2Value2 : facet2Vector ) {
							if ( facet2Value != facet2Value2 ) {
								facet2->rVertices().at( facet2Value ).addNeighbor( ( facet2->vertices().at( facet2Value2 ) ) );
								facet2->rVertices().at( facet2Value2 ).addNeighbor( ( facet2->vertices().at( facet2Value ) ) );
							}
						}
					}
				}
			}
		}
	}
}

/*
* ------------------------------------------------------------------------------
* MAIN FUNCTION
* ------------------------------------------------------------------------------
*/

template <typename Number>
static std::pair<std::vector<std::shared_ptr<Facet<Number>>>, std::map<Point<Number>, std::set<Point<Number>>>>
convexHull( const std::vector<Point<Number>>& pts ) {
	// initialization: remove duplicate points
	auto points = pts;
	std::sort( points.begin(), points.end() );
	std::unique( points.begin(), points.end() );

	if ( points.size() >= points.at( 0 ).dimension() + 1 ) {
		std::vector<std::shared_ptr<Facet<Number>>> facets;
		std::vector<Point<Number>> unassignedPoints, assignedPoints;

		// init facets and points
		initConvexHull( points, facets );
		pointsNotContainedInFacets( points, facets, unassignedPoints, assignedPoints );	 // Determine points which belong to a facet

		for ( auto facet : facets ) {
			for ( auto point : unassignedPoints ) {
				if ( facet->isAbove( point ) ) {  // isAbove
					facet->addPointToOutsideSet( point );
				}
			}
		}

		std::queue<std::shared_ptr<Facet<Number>>> workingSet;
		removeBorderFacets( facets, workingSet );  // extract the facets to be examined

		/*
		 * ------------------------------------------------------------------------------
		 * MAIN BODY
		 * ------------------------------------------------------------------------------
		 */

		while ( !workingSet.empty() ) {
			std::shared_ptr<Facet<Number>> currentFacet = workingSet.front();  // next facet
			Point<Number> currentPoint = currentFacet->furthest_Point();	   // next point

			std::vector<std::shared_ptr<Facet<Number>>> currentVisibleFacets;
			currentVisibleFacets.push_back( currentFacet );
			std::queue<std::shared_ptr<Facet<Number>>> newVisibleFacets;
			bool changed = true;

			// determin horizon into currentVisibleFacets
			while ( changed ) {
				changed = false;
				for ( const auto& facet : currentVisibleFacets ) {
					assert( !facet->neighbors().empty() );
					for ( const auto& neighbor : facet->neighbors() ) {
						if ( neighbor->isAbove( currentPoint ) ) {
							newVisibleFacets.push( neighbor );	// update new visible facets
							assert( !neighbor->neighbors().empty() );
						}
					}
				}
				while ( !newVisibleFacets.empty() ) {
					if ( std::find( currentVisibleFacets.begin(), currentVisibleFacets.end(), *newVisibleFacets.front() ) == currentVisibleFacets.end() ) {
						currentVisibleFacets.push_back( newVisibleFacets.front() );	 // insert the new visible facets into the current visible facets - if they are no duplicates
						changed = true;
					}
					newVisibleFacets.pop();	 // remove the new visible facet
				}
			}

			/* Stefan: Note that here, we have a set of visible facets - we need to get the ridges, which are between a
			 * visible facet and the next invisible
			 * facet (Horizon ridges). This means, that we have to take into account all ridges, which are built of one
			 * facet out of the visible facet set and one facet out of
			 * the neighbors set.
			 */
			std::vector<std::shared_ptr<Facet<Number>>> newFacets;

			// Create new facets
			for ( auto facet : currentVisibleFacets ) {
				for ( auto ridge : getRidges( facet ) ) {
					for ( auto neighbor : ridge.neighbors() ) {
						if ( std::find( currentVisibleFacets.begin(), currentVisibleFacets.end(), *neighbor ) == currentVisibleFacets.end() ) {	 // we have a neighbor of this ridge, which is not visible -> horizon
							//std::cout << "Found a candidate for a newFacet" << std::endl;
							// ridge, create new facet
							Point<Number> insidePoint = findInsidePoint( ridge, facet );

							std::shared_ptr<Facet<Number>> newFacet = std::make_shared<Facet<Number>>( ridge.vertices(), currentPoint, insidePoint );

							newFacet->addNeighbor( neighbor );
							neighbor->addNeighbor( newFacet );

							newFacets.emplace_back( std::move( newFacet ) );
						}
					}
				}
			}

			// at this point we created all new facets from any horizon ridge to the current considered point
			// (currentPoint). We need to set up the neighborhood
			// relations in between the new facets.
			// std::cout << __func__ << " New Facets before neighborhood: " << newFacets << std::endl;

			determineNeighbors( newFacets );

			// std::vector<Point<Number>> outsidePoints =
			// polytope::currentPoints_outside_of_currentVisibleFacets(currentVisibleFacets);

			// update unassignedPoints -> assignedPoints
			if ( std::find( unassignedPoints.begin(), unassignedPoints.end(), currentPoint ) != unassignedPoints.end() ) {
				assignedPoints.push_back( currentPoint );  // assign currentPoint if not yet

				for ( unsigned i = 0; i < unassignedPoints.size(); i++ ) {
					if ( unassignedPoints.at( i ) == currentPoint ) {
						unassignedPoints.erase( unassignedPoints.begin() + i );	 // erase currentPoint in unassignedPoints
						break;
					}
				}
			}

			// update outside sets of the new facets.
			for ( auto facet : newFacets ) {
				for ( auto point : unassignedPoints ) {
					if ( facet->isAbove( point ) ) {
						facet->addPointToOutsideSet( point );
					}
				}
			}

			std::queue<std::shared_ptr<Facet<Number>>> notOutsideNewFacets;
			std::vector<std::shared_ptr<Facet<Number>>> newNeighOpt = newFacets;
			removeBorderFacets( newFacets, notOutsideNewFacets );
			std::move( newFacets.begin(), newFacets.end(), std::back_inserter( facets ) );

			// update working set with relevant new facets
			while ( !notOutsideNewFacets.empty() ) {
				workingSet.push( notOutsideNewFacets.front() );
				notOutsideNewFacets.pop();
			}

			// remove non-relevant facets from workingSet
			std::queue<std::shared_ptr<Facet<Number>>> temp;
			while ( !workingSet.empty() ) {
				if ( std::find( currentVisibleFacets.begin(), currentVisibleFacets.end(), *workingSet.front() ) == currentVisibleFacets.end() ) {  // update neighbors of relevant facets
					for ( auto facet : currentVisibleFacets ) {
						if ( workingSet.front()->removeNeighbor( facet ) ) {
							workingSet.front()->addNeighbor( newNeighbor( workingSet.front(), newNeighOpt ) );
						}
					}
					temp.push( workingSet.front() );
				}

				workingSet.pop();
			}
			workingSet = temp;

			//// Choose next facet with non-empty outside set.
			//while(workingSet.front().getOutsideSet().empty()) {
			//	std::cout << "Current workingSet.front() is empty" << std::endl;
			//	facets.push_back(workingSet.front());
			//	workingSet.pop();
			//}
		}
		std::map<Point<Number>, std::set<Point<Number>>> neighborhood = setNeighborhoodOfPointsBeforehand( facets );

		facets = maximizeFacets( facets );

		// setNeighborhoodOfPoints(facets);

		return std::make_pair( facets, neighborhood );
	} else {
		std::cout << "Error: not enough points to determine convex hull in dimension " << points.at( 0 ).dimension()
				  << std::endl;
		return std::make_pair( std::vector<std::shared_ptr<Facet<Number>>>(),
							   std::map<Point<Number>, std::set<Point<Number>>>() );
	}
}
}  // namespace hypro
