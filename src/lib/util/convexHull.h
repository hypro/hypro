/*
 * Contains utilities to create the convex hull.
 * @file   convexHull.h
 * @author tayfun
 *
 * @since       2014-12-10
 * @version     2015-05-06
 */

#pragma once

#include "../datastructures/Hyperplane.h"
#include "../datastructures/Facet.h"
#include "../datastructures/Ridge.h"
#include "../datastructures/Point.h"

namespace hypro {

template <typename Number>
static unsigned dimensionCheck( const std::vector<Point<Number>>& points ) {
	matrix_t<Number> matrix = matrix_t<Number>(points.at(0).rawCoordinates().size(), points.size());

	for (unsigned i=0; i < matrix.rows(); i++) {
		for (unsigned j=0; j < matrix.cols(); j++) {
			matrix(i, j) = points.at(j).rawCoordinates()(i);
		}
	}

	return matrix.fullPivLu().rank();
}

template <typename Number>
static bool maxRank( const std::vector<Point<Number>>& points, const Point<Number>& point ) {
	matrix_t<Number> matrix = matrix_t<Number>(point.rawCoordinates().size(), points.size()+1);

	for (unsigned i=0; i < matrix.rows(); i++) {
		for (unsigned j=0; j < matrix.cols(); j++) {
			if(j==matrix.cols()-1) {
				matrix(i, j) = point.rawCoordinates()(i);
			}
			else {
				matrix(i, j) = points.at(j).rawCoordinates()(i);
			}
		}
	}

	return matrix.fullPivLu().rank() == (unsigned)(matrix.cols());
}

/*
 * Creates initial Convex Hull in dimension d with d+1 Points out of all the points given. Neighbor relationship of the
 * facets are saved in neighbors.
 * @return The list of facets, i.e. Hyperplanes with dimension d-1 who form the Convex Hull.
 */
template <typename Number>
static void initConvexHull( const std::vector<Point<Number>>& points, std::vector<std::shared_ptr<Facet<Number>>>& facets ) {
	unsigned dimCheck = dimensionCheck(points);
	unsigned dimension = points.at(0).dimension();
	if (dimCheck == dimension) {
		std::vector<Point<Number>> initialPoints;
		unsigned minIndex = 0, maxIndex = 0; // determine min and max of first value

		for (unsigned j=0; j < points.size(); j++) {
			if (points.at(minIndex).rawCoordinates()(0) > points.at(j).rawCoordinates()(0)) minIndex = j;
			if (points.at(maxIndex).rawCoordinates()(0) < points.at(j).rawCoordinates()(0)) maxIndex = j;
		}
		initialPoints.push_back(points.at(minIndex));
		initialPoints.push_back(points.at(maxIndex));

		// search rest for rank d accordingly for each dimension
		for (unsigned d=1; d<dimension; d++) {
			for (unsigned i=0; i < points.size(); i++) {
				if(std::find(initialPoints.begin(), initialPoints.end(), points.at(i))==initialPoints.end()) {
					if (maxRank(initialPoints, points.at(i))) {
						initialPoints.push_back(points.at(i));
						break;
					}
				}
			}
		}

		// search for unused point as last member for initConvexhull
		unsigned index=0;
		while (initialPoints.size()<dimension+1) {
			if (std::find(initialPoints.begin(), initialPoints.end(), points.at(index))==initialPoints.end()) {
				initialPoints.push_back( points[index] );
			}
			index++;
		}

		// inti facets
		for (unsigned i=0; i < dimension+1; i++) {
			facets.push_back(std::shared_ptr<Facet<Number>>(new Facet<Number>()));
		}
		for (unsigned i=0; i < dimension+1; ++i) {
			std::vector<Point<Number>> points_for_facet;
			for (unsigned j=0; j < dimension+1; ++j) {
				if (i != j) {
					points_for_facet.push_back(initialPoints[j]);
				}
			}
			facets[i]->setPoints(points_for_facet, initialPoints[i]);
		}

		// Add neighbors
		for (unsigned i=0; i < dimension+1; ++i) {
			for (unsigned j=0; j < dimension+1; ++j) {
				if (i != j) {
					facets[i]->addNeighbor(facets[j]);
				}
			}
		}

	} else {
		std::cout << __func__ << __LINE__ << "Error: Inconsistent point set " << std::endl;
		facets = std::vector<std::shared_ptr<Facet<Number>>>();
	}
}

/*
 * @return The list of points that are not contained by the facets.
 */
template <typename Number>
static void pointsNotContainedInFacets( const std::vector<Point<Number>>& points, const std::vector<std::shared_ptr<Facet<Number>>>& facets, std::vector<Point<Number>>& unassignedPoints, std::vector<Point<Number>>& assignedPoints ) {
	unassignedPoints = points;
	std::vector<Point<Number>> pointsInFacets;
	for (std::shared_ptr<Facet<Number>> facet : facets) {
		for (Point<Number> p : facet->vertices()) {
			pointsInFacets.push_back( p );
		}
	}
	// Stefan: pointsInFacets holds all generating points of the given facets.

	std::vector<unsigned> removeables;
	for (unsigned i=0; i < unassignedPoints.size(); i++) {
		for (unsigned j=0; j < pointsInFacets.size(); j++) {
			if (unassignedPoints[i] == pointsInFacets[j] && std::find(removeables.begin(), removeables.end(), i)!=removeables.end()) {
				removeables.push_back(i);
			}
		}
	}
	// Stefan: removables holds the indices of the points in points, which are contained in one of the facets.
	// std::cout<<__func__ << " : " <<__LINE__ <<std::endl;

	for ( unsigned i = 0; i < removeables.size(); i++ ) {
		assignedPoints.push_back( unassignedPoints.at( removeables[i] - i ) );
		unassignedPoints.erase( unassignedPoints.begin() + ( removeables[i] - i ) );
	}
	// std::cout << __func__ << " : " << __LINE__ << unassignedPoints << "  " << assignedPoints << std::endl;
}

/*
 * Determines the neighbors of the Hyperplanes. Neighbors are taken from neighbors.
 * @return The list of neighbors from the Hyperplanes.
 */
template <typename Number>
static std::vector<std::shared_ptr<Facet<Number>>> getFacetsNeighbors(const std::vector<std::shared_ptr<Facet<Number>>>& facets) {
	std::vector<std::shared_ptr<Facet<Number>>> result;

	if (!facets.empty()) {
		for (auto facet: facets) { // get 'all' neighbors
			for (auto neighbor: facet->neighbors()) {
				if(std::find(result.begin(), result.end(), neighbor)==result.end() && std::find(facets.begin(), facets.end(), neighbor)==facets.end()){
					result.push_back(neighbor); // insert if it's a new neighbor and it isn't one of the given facets
				}
			}
		}
	}

	return result;
}
/*
 * Determines the ridges between the facets and their neighbors.polytope::
 * @return The list of ridges, i.e. Hyperplanes with dimension d-2 who are the intersection of two facets.
 */
template <typename Number>
static std::vector<Ridge<Number>> getRidges( const std::vector<std::shared_ptr<Facet<Number>>>& facets ) {
	std::vector<Ridge<Number>> result;

	if (!facets.empty()) {
		std::vector<std::shared_ptr<Facet<Number>>> neighbors = getFacetsNeighbors( facets );
		for (auto facet: facets) {
			for (auto neighbor: neighbors) {
				if (facet->isNeighbor(neighbor)) {
					Ridge<Number> newRidge(facet, neighbor);
					result.push_back(newRidge);				}
			}
		}
	}

	return result;
}

template <typename Number>
static std::vector<Ridge<Number>> getRidges( std::shared_ptr<Facet<Number>> facet ) {
	std::vector<Ridge<Number>> result;

	if (!facet->empty()) {
		for (auto neighbor: facet->neighbors()) {
			Ridge<Number> newRidge(facet, neighbor);
			result.push_back(newRidge);
		}
	}

	return result;
}

template <typename Number>
static bool checkInsideRidge( const Ridge<Number>& ridge, const Point<Number>& point ) {
	for ( unsigned i = 0; i < ridge.vertices(); i++ ) {
		if ( point == ridge.vertices().at( i ) ) {
			return true;
		}
	}
	return false;
}

template <typename Number>
static std::vector<std::shared_ptr<Facet<Number>>> shareRidge(
	  const std::vector<std::shared_ptr<Facet<Number>>>& facets, const Ridge<Number>& ridge ) {
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
 * Determines the list of points which were outside of the visible_facets. The points are taken from hashlist.
 * @return The list of points which were outside of the visible_facets
 */
/*
template<typename Number>
static std::vector<Point<Number>> points_outside_of_visible_facets(const std::vector<std::shared_ptr<Facet<Number>>>&
visible_facets) {
   std::vector<Point<Number>> temp;
   std::vector<Point<Number>> result;
   std::vector<Point<Number>> outsideset;
   for(unsigned i = 0; i < visible_facets.size(); i++) {
	   outsideset = visible_facets[i]->getOutsideSet();
	   for(unsigned j = 0; j<outsideset.size(); j++) {
		   temp.push_back(outsideset[j]);
	   }
   }
   bool found = false;
   for(unsigned i = 0; i < temp.size(); i++) {
	   for(unsigned j = 0; i<result.size(); j++) {
		   if(temp[i] == result[j]) {
			   found = true;
		   }
	   }
	   if(!found) {
		   result.push_back(temp[i]);
	   }
	   found = false;
   }
   return result;
}
*/
/*
 * Checks for each facet if it has at least one point above. If it has it is not outside and will be returned. Note that
 * the input facets is modified to
 * contain only facets with an empty outside set.
 * @return The list of facets that have at least one point above.
 */
template <typename Number>
static void removeBorderFacets(std::vector<std::shared_ptr<Facet<Number>>>& facets, std::queue<std::shared_ptr<Facet<Number>>>& result) {
	for (unsigned i=facets.size(); i > 0; i--) {
		if (!facets.at(i-1)->getOutsideSet().empty()) {
			result.push(facets[i-1]);
			facets.erase( facets.begin() + i-1 );
		}
	}
}

/*
 * Checks if two facets are neighbors by determining the number of points they share
 */
template <typename Number>
static bool neighborCheck( std::shared_ptr<Facet<Number>> facet1, std::shared_ptr<Facet<Number>> facet2 ) {
	int checkValue = facet1->vertices().at( 0 ).dimension() - 1;  // number of points they have to share to be neighbors
	int currentValue = 0;  // number of points that are confirmed to be shared

	for (auto vertex1: facet1->vertices()) {
		for (auto vertex2: facet2->vertices()) {
			if ( vertex1 == vertex2) {
				currentValue++;
			}
		}
	}
	if(checkValue == currentValue) return true;

	return false;
}

/*
 * Finds the neighbors of the new created Facets among themselves
 */
template <typename Number>
static void determineNeighbors( std::vector<std::shared_ptr<Facet<Number>>>& newFacets ) {
	for (unsigned i = 0; i < newFacets.size(); i++) {
		for (unsigned j = i+1; j < newFacets.size(); j++) {
			if (neighborCheck(newFacets[i], newFacets[j])) { // check all pairs of new facets if they are neighbors
				newFacets[i]->addNeighbor(newFacets[j]);
				newFacets[j]->addNeighbor(newFacets[i]);
			}
		}
	}
}

/*
 * Finds the inside Point to a ridge and an associated facet, which is the point in the facet which isn't in the ridge
 */
template <typename Number>
static Point<Number> findInsidePoint( const Ridge<Number>& ridge, const std::shared_ptr<Facet<Number>>& _facet ) {
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
	if ( *facet1 == *facet2 ) {
		return true;
	} else {
		int checkValue = facet1->vertices().size();
		if ( checkValue > (int)facet2->vertices().size() ) {
			checkValue = facet2->vertices().size();
		}
		int currentValue = 0;
		for ( unsigned i = 0; i < facet1->vertices().size(); i++ ) {
			for ( unsigned j = 0; j < facet2->vertices().size(); j++ ) {
				if ( facet1->vertices().at( i ) == facet2->vertices().at( j ) ) {
					currentValue++;
				}
			}
		}
		return checkValue == currentValue;
	}
}

template <typename Number>
static std::map<Point<Number>, std::set<Point<Number>>> setNeighborhoodOfPointsBeforehand(
	  std::vector<std::shared_ptr<Facet<Number>>>& facets ) {
	std::map<Point<Number>, std::set<Point<Number>>> res;
	for ( auto& facet : facets ) {
		for ( unsigned j = 0; j < facet->rVertices().size(); j++ ) {
			for ( unsigned k = 0; k < facet->vertices().size(); k++ ) {
				if ( j != k ) {
					res[facet->rVertices().at( j )].insert( facet->vertices().at( k ) );
					// facet->rVertices().at(j).addNeighbor(facet->vertices().at(k));
				}
			}
		}
	}
	return res;
}

template <typename Number>
static std::vector<std::shared_ptr<Facet<Number>>> maximizeFacets(
	  std::vector<std::shared_ptr<Facet<Number>>>& facets ) {
	std::vector<std::shared_ptr<Facet<Number>>> result;
	// unsigned dimension = facets.front().vertices().front().dimension();
	// std::cout << __func__ << " : " << __LINE__ << std::endl;
	while ( !facets.empty() ) {
		std::shared_ptr<Facet<Number>> newFacet = facets.front();
		facets.erase( facets.begin() );
		// std::cout << __func__ << " : " << __LINE__ << std::endl;
		for ( unsigned l = 0; l < facets.size(); l++ ) {
			std::shared_ptr<Facet<Number>> neighbor = facets.at( l );
			// std::cout << __func__ << " : " << __LINE__ << " Neighbors : " << newFacet.neighbors() << std::endl;
			if ( neighborCheck( newFacet, neighbor ) ) {
				// std::cout << __func__ << " : " << __LINE__ << " neighbor : " << neighbor << std::endl;
				Point<Number> point1, point2;
				for ( unsigned i = 0; i < neighbor->vertices().size(); i++ ) {
					bool found = false;
					for ( unsigned j = 0; j < newFacet->vertices().size(); j++ ) {
						if ( neighbor->vertices().at( i ) == newFacet->vertices().at( j ) ) {
							found = true;
						}
					}
					if ( !found ) {
						point1 = neighbor->vertices().at( i );
					}
				}

				for ( unsigned i = 0; i < newFacet->vertices().size(); i++ ) {
					bool found = false;
					for ( unsigned j = 0; j < neighbor->vertices().size(); j++ ) {
						if ( neighbor->vertices().at( j ) == newFacet->vertices().at( i ) ) {
							found = true;
						}
					}
					if ( !found ) {
						point2 = newFacet->vertices().at( i );
					}
				}
				// std::cout << __func__ << " : " << __LINE__ << " normalsize : " << point1.dimension() << std::endl;
				// std::cout << __func__ << " : " << __LINE__ << " Dist 1 : " << newFacet.getDist(point1) << std::endl;
				// std::cout << __func__ << " : " << __LINE__ << " Dist 2 : " << neighbor.getDist(point2) << std::endl;
				if ( ( newFacet->getDist( point1 ) == 0 ) && ( neighbor->getDist( point2 ) == 0 ) ) {
					// std::cout << __func__ << " : " << __LINE__ << " Same level neighbor : " << neighbor << std::endl;
					newFacet->addPoint( point1 );
					for ( unsigned i = 0; i < neighbor->rNeighbors().size(); i++ ) {
						if ( !newFacet->isNeighbor( neighbor->rNeighbors().at( i ) ) ) {
							newFacet->addNeighbor( neighbor->rNeighbors().at( i ) );
						}
					}
					// for(unsigned k = 0; k<neighbor.neighbors().size(); k++){
					//	newFacet.addNeighbor(neighbor.neighbors().at(k));
					//}
					facets.erase( facets.begin() + l );
					l--;
				}
			} else if ( includeFacet( newFacet, neighbor ) ) {
				facets.erase( facets.begin() + l );
			}
		}
		result.push_back( newFacet );
	}
	// std::cout << __func__ << " : " << __LINE__ << std::endl;

	for ( unsigned i = 0; i < result.size(); ) {
		bool del = false;
		for ( unsigned j = 0; j < result.size(); ) {
			if ( includeFacet( result[i], result[j] ) && result[i] != result[j] ) {
				result.erase( result.begin() + j );
				del = true;
			} else {
				j++;
			}
		}
		if ( !del ) {
			i++;
		}
	}
	return result;
}

template <typename Number>
static std::shared_ptr<Facet<Number>> newNeighbor( std::shared_ptr<Facet<Number>> oldNeighbor,
												   const std::vector<std::shared_ptr<Facet<Number>>>& newFacets ) {
	for ( unsigned i = 0; i < newFacets.size(); i++ ) {
		if ( neighborCheck( oldNeighbor, newFacets[i] ) ) {
			return newFacets[i];
		}
	}
	return oldNeighbor;
}

template <typename Number>
static void setNeighborhoodOfPoints( std::vector<std::shared_ptr<Facet<Number>>>& facets ) {
	if ( facets[0]->vertices().at( 0 ).dimension() <= 1 ) {
	} else if ( facets[0]->vertices().at( 0 ).dimension() == 2 ) {
		for ( unsigned i = 0; i < facets.size(); i++ ) {
			facets[i]->rVertices().at( 0 ).addNeighbor( facets[i]->rVertices().at( 1 ) );
			facets[i]->rVertices().at( 1 ).addNeighbor( facets[i]->rVertices().at( 0 ) );
		}
	} else {
		for ( unsigned i = 0; i < facets.size(); i++ ) {
			for ( unsigned j = 0; j < facets.size(); j++ ) {
				if ( neighborCheck( facets[i], facets[j] ) ) {
					std::vector<unsigned> facet1;
					std::vector<unsigned> facet2;

					for ( unsigned k = 0; k < facets[i]->vertices().size(); k++ ) {
						for ( unsigned l = 0; l < facets[j]->vertices().size(); l++ ) {
							if ( facets[i]->vertices().at( k ) == facets[j]->vertices().at( l ) ) {
								facet1.push_back( k );
								facet2.push_back( l );
							}
						}
					}

					for ( unsigned k = 0; k < facet1.size(); k++ ) {
						for ( unsigned l = 0; l < facet1.size(); l++ ) {
							if ( k != l ) {
								facets[i]->rVertices().at( facet1[k] ).addNeighbor(
									  ( facets[i]->vertices().at( facet1[l] ) ) );
								facets[i]->rVertices().at( facet1[l] ).addNeighbor(
									  ( facets[i]->vertices().at( facet1[k] ) ) );
							}
						}
					}

					for ( unsigned k = 0; k < facet2.size(); k++ ) {
						for ( unsigned l = 0; l < facet2.size(); l++ ) {
							if ( k != l ) {
								facets[j]->rVertices().at( facet2[k] ).addNeighbor(
									  ( facets[j]->vertices().at( facet2[l] ) ) );
								facets[j]->rVertices().at( facet2[l] ).addNeighbor(
									  ( facets[j]->vertices().at( facet2[k] ) ) );
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
	// initialization
	std::set<Point<Number>> pt;
	for ( auto& p : pts ) {
		pt.insert( p );
	}
	std::vector<Point<Number>> points;
	for ( auto& p : pt ) {
		points.push_back( p );
	}

	if (points.size() >= points.at(0).dimension()+1 ) {
		std::vector<std::shared_ptr<Facet<Number>>> facets;
		std::vector<Point<Number>> unassignedPoints, assignedPoints;

		// init facets and points
		initConvexHull(points, facets);
		pointsNotContainedInFacets(points, facets, unassignedPoints, assignedPoints); // Determine points which belong to a facet
		for (auto facet: facets) {
			for (auto point: unassignedPoints) {
				if (facet->isAbove(point)) { // isAbove
					facet->addPointToOutsideSet(point);
				}
			}
		}

		std::queue<std::shared_ptr<Facet<Number>>> workingSet;
		removeBorderFacets(facets, workingSet); // extract the facets to be examined

		/*
		* ------------------------------------------------------------------------------
		* MAIN BODY
		* ------------------------------------------------------------------------------
		*/

		while (!workingSet.empty()) {
			std::shared_ptr<Facet<Number>> currentFacet = workingSet.front(); // next facet
			Point<Number> currentPoint = currentFacet->furthest_Point(); // next point

			std::vector<std::shared_ptr<Facet<Number>>> currentVisibleFacets;
			currentVisibleFacets.push_back(currentFacet);
			std::queue<std::shared_ptr<Facet<Number>>> newVisibleFacets;
			bool changed = true;

			// determin horizon into currentVisibleFacets
			while(changed){
				changed = false;
				for (const auto& facet : currentVisibleFacets) {
					assert(!facet->neighbors().empty());
					for (const auto& neighbor : facet->neighbors()) {
						if (neighbor->isAbove(currentPoint)) {
							newVisibleFacets.push(neighbor); // update new visible facets
							assert(!neighbor->neighbors().empty());
						}
					}
				}
				while (!newVisibleFacets.empty()) {
					if(std::find(currentVisibleFacets.begin(), currentVisibleFacets.end(), *newVisibleFacets.front())== currentVisibleFacets.end()){
						currentVisibleFacets.push_back(newVisibleFacets.front()); // insert the new visible facets into the current visible facets - if they are no duplicates
						changed = true;
					}
					newVisibleFacets.pop(); // remove the new visible facet
				}
			}

			// std::cout << "From current point visible facets: ";
			// for(const auto item : currentVisibleFacets)
			//	std::cout << *item << ", ";
			// std::cout << std::endl;

			/* Stefan: Note that here, we have a set of visible facets - we need to get the ridges, which are between a
			 * visible facet and the next invisible
			 * facet (Horizon ridges). This means, that we have to take into account all ridges, which are built of one
			 * facet out of the visible facet set and one facet out of
			 * the neighbors set.
			 */
			std::vector<std::shared_ptr<Facet<Number>>> newFacets;

			// Create new facets
			for(auto facet: currentVisibleFacets){
				for (auto ridge: getRidges( facet ) ) {
					for (auto neighbor: ridge.neighbors() ) {
						if (std::find(currentVisibleFacets.begin(), currentVisibleFacets.end(), *neighbor) == currentVisibleFacets.end()) {  // we have a neighbor of this ridge, which is not visible -> horizon
							// ridge, create new facet
							Point<Number> insidePoint = findInsidePoint(ridge, facet);
							std::shared_ptr<Facet<Number>> newFacet = std::shared_ptr<Facet<Number>>(new Facet<Number>(ridge.vertices(), currentPoint, insidePoint));
							newFacet->addNeighbor(neighbor);
							neighbor->addNeighbor(newFacet);
							newFacets.push_back(newFacet);
						}
					}
				}
			}
			// at this point we created all new facets from any horizon ridge to the current considered point
			// (currentPoint). We need to set up the neighborhood
			// relations in between the new facets.
			// std::cout << __func__ << " New Facets before neighborhood: " << newFacets << std::endl;

			determineNeighbors(newFacets);

			// std::cout << __func__ << " New Facets: " << newFacets << std::endl;
			// std::cout << __func__ << " New Facets: ";
			// for(const auto item : newFacets)
			//	std::cout << *item << ", ";
			// std::cout << std::endl;

			// std::vector<Point<Number>> outsidePoints =
			// polytope::currentPoints_outside_of_currentVisibleFacets(currentVisibleFacets);

			// update unassignedPoints -> assignedPoints
			if (std::find(unassignedPoints.begin(), unassignedPoints.end(), currentPoint)!=unassignedPoints.end()) {
				assignedPoints.push_back(currentPoint); // assign currentPoint if not yet

				for (unsigned i = 0; i < unassignedPoints.size(); i++) {
					if (unassignedPoints.at(i) == currentPoint) {
						unassignedPoints.erase(unassignedPoints.begin()+i); // erase currentPoint in unassignedPoints
						break;
					}
				}
			}

			// std::cout << __func__ << " Unassigned Points: " << unassignedPoints << std::endl;

			// update outside sets of the new facets.
			for (auto facet: newFacets) {
				for (auto point: unassignedPoints) {
					if (facet->isAbove(point)) {
						facet->addPointToOutsideSet(point);
					}
				}
			}

			std::queue<std::shared_ptr<Facet<Number>>> notOutsideNewFacets;
			std::vector<std::shared_ptr<Facet<Number>>> newNeighOpt = newFacets;
			removeBorderFacets(newFacets, notOutsideNewFacets);
			for ( const auto& facet : newFacets ) {
				facets.push_back( facet ); // update facets with new "final" border facets
			}

			// update working set with relevant new facets
			while ( !notOutsideNewFacets.empty() ) {
				workingSet.push( notOutsideNewFacets.front() );
				notOutsideNewFacets.pop();
			}

			// remove non-relevant facets from workingSet
			std::queue<std::shared_ptr<Facet<Number>>> temp;
			while ( !workingSet.empty() ) {
				if(std::find(currentVisibleFacets.begin(), currentVisibleFacets.end(), *workingSet.front())==currentVisibleFacets.end()){
					for(auto facet: currentVisibleFacets){
						if(workingSet.front()->removeNeighbor(facet)){
							workingSet.front()->addNeighbor(newNeighbor(workingSet.front(), newNeighOpt));
						}
					}
					temp.push( workingSet.front());
				}


				//bool isVisible = false;
				//for ( unsigned i = 0; i < currentVisibleFacets.size(); i++ ) {
				//	bool done = workingSet.front()->removeNeighbor( currentVisibleFacets[i] );
				//	if ( done ) {
				//		std::shared_ptr<Facet<Number>> newNeigh = newNeighbor( workingSet.front(), newNeighOpt );
				//		// std::cout << __func__ << "Old Neighbor: " << currentVisibleFacets[i] << std::endl;
				//		// std::cout << "Current Facet: " << workingSet.front() << std::endl;
				//		// std::cout << "NewNeighbor: " << newNeigh << std::endl;
				//		workingSet.front()->addNeighbor( newNeigh );
				//	}

				//	/*for(unsigned j = 0; j<facets.size(); j++){
				//		bool done2 = facets.at(j).removeNeighbor(currentVisibleFacets[i]);
				//		if(done2){
				//			Facet<Number> newNeigh = polytope::newNeighbor(workingSet.front(), newNeighOpt);
				//			//std::cout << __func__ << "Old Neighbor: " << currentVisibleFacets[i] << std::endl;
				//			//std::cout << "Current Facet: " << workingSet.front() << std::endl;
				//			//std::cout << "NewNeighbor: " << newNeigh << std::endl;
				//			facets.at(j).addNeighbor(newNeigh);
				//		}
				//	}*/

				//	if ( *workingSet.front() == *currentVisibleFacets.at( i ) ) isVisible = true;
				//}
				//if ( !isVisible ) temp.push( workingSet.front() );

				workingSet.pop();
			}
			workingSet = temp;

			/*
			// Choose next facet with non-empty outside set.
			while(workingSet.front().getOutsideSet().empty()) {
				facets.push_back(workingSet.front());
				workingSet.pop();
			}
			*/
			// std::cout << __func__ << " facets: " << facets << std::endl;
		}
		std::map<Point<Number>, std::set<Point<Number>>> neighborhood = setNeighborhoodOfPointsBeforehand( facets );

		facets = maximizeFacets( facets );

		// setNeighborhoodOfPoints(facets);

		return std::make_pair( facets, neighborhood );
	}
	else
	{
		std::cout << "Error: not enough points to determine convex hull in dimension " << points.at(0).dimension()
				  << std::endl;
		return std::make_pair( std::vector<std::shared_ptr<Facet<Number>>>(),
							   std::map<Point<Number>, std::set<Point<Number>>>() );
	}
}
}
