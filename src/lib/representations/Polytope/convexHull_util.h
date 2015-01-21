/*
 * Contains utilities to create the convex hull.
 * @file   convexHull_util.h
 * @author tayfun
 *
 * @since       2014-12-10
 * @version     2014-12-10
 */

#include "../Hyperplane/Hyperplane.h"
#include "../../datastructures/Facet.h"
#include "../../datastructures/Ridge.h"
#include "../../datastructures/Point.h"

namespace hypro
{
namespace polytope
{

/*
 * Creates initial Convex Hull in dimension d with d+1 Points out of all the points given. Neighbor relationship of the facets are saved in neighbors.
 * @return The list of facets, i.e. Hyperplanes with dimension d-1 who form the Convex Hull.
 */
template<typename Number>
std::vector<Facet> initConvexHull(std::vector<Point<Number>> points) {
	Dimension d = points.front.dimension();
	std::vector<Point<Number>> initialPoints;
	for(int i = 0; i < d+1; i++) {
		initialPoints.push_back(points[i]);
	}
	std::vector<Facet> facets;
	for(int i = 0; i < d+1; i++) {
		facets.push_back(new Facet());
	}
	for(int i = 0; i < d+1; i++) {
		std::vector<Point<Number>> points_for_facet;
		for(int j = 0; j < d+1; i++) {
			if(i!=j) {
				points_for_facet.push_back(initialPoints[j]);
				facets[i].addNeighbor(facets[j]);
			}
		}
		facets[i].setPoints(initialPoints);
	}
	return facets;
}

/*
 * @return The list of points that are not contained by the facets.
 */
template<typename Number>
std::vector<Point<Number>> points_not_in_facets(std::vector<Point<Number>> points, std::vector<Facet> facets) {
	std::vector<Points<Number>> pointsInFacets;
	for(Facet facet : facets) {
		std::vector<Points<Number>> pointsInFacet = facet.getPoints();//right call? Look Facet.h !!!
		for(Point<Number> p : pointsInFacet) {
			pointsInFacets.push_back(p);
		}
	}

	for (Point<Number> point : points) {
		for (Point<Number> p : pointsInFacets) {
			if(p == point) {
				//delete aus points !!!
			}
		}
	}
	return points;
}

/*
 * Determines the neighbors of the Hyperplanes. Neighbors are taken from neighbors.
 * @return The list of neighbors from the Hyperplanes.
 */
template<typename Number>
std::vector<Facet> getFacetsNeighbors(std::vector<Facet> facets) {
	return null;
}

/*
 * Determines the ridges between the facets and their neighbors.
 * @return The list of ridges, i.e. Hyperplanes with dimension d-2 who are the intersection of two facets.
 */
template<typename Number>
std::vector<Ridge> getRidges(std::vector<Facet> facets) {
	return null;
}


/*
 * Determines the list of points which were outside of the visible_facets. The points are taken from hashlist.
 * @return The list of points which were outside of the visible_facets
 */
template<typename Number>
std::vector<Point<Number>> points_outside_of_visible_facets(std::vector<Facet> visible_facets) {
	return null;
}

/*
 * Checks for each facet if it has at least one point above. If it has it is not outside and will be returned.
 * @return The list of facets that have at least one point above.
 */
template<typename Number>
std::vector<Facet> not_outside_facet(std::vector<Facet> facets) {
	return null;
}

/*
 * checks if the new facets are outside or not. If not, then these facets will be inserted in notOutsideFacets
 */
template<typename Number>
void updateNotOutsideFacets(std::vector<Facet> newFacets) {
}


}

}
