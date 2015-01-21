/*
 * Contains utilities to create the convex hull.
 * @file   convexHull_util.h
 * @author tayfun
 *
 * @since       2014-12-10
 * @version     2015-01-21
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
        std::vector<Points<Number>> pointsInFacet = facet.vertices();
        for(Point<Number> p : pointsInFacet) {
            pointsInFacets.push_back(p);
        }
    }

    for (int i = 0; i<points.size(); i++) {
        for (int j = 0; j<pointsInFacets.size(); j++) {
            if(points[i] == pointsInFacets[j]) {
                points.erase(i);
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
    if(facets.isEmpty()) {
        return null;
    }
    else {
        std::vector<Facet> result;
        std::vector<Facet> temp;
        std::vector<Facet> temp2;
        std::set<Facet> neighbors;
        for(int i = 0; i<facets.size(); i++) {
            neighbors = facet.neighbors();
            for(int j = 0; j<neighbors.size(); j++) {
                temp.push_back(neighbors[j]);
            }
        }
        bool found = false;
        for(int i = 0; i<temp.size(); i++) {
            for(int j = 0; j<temp2.size(); j++) {
                if(temp[i].isEqual(temp2[j])) {
                    found = true;
                }
            }
            if(!found) {
                temp2.push_back(temp[i]);
            }
            found = false;
        }

        found = false;
        for(int i = 0; i<temp2.size(); i++) {
            for(int j = 0; j<facets.size(); j++) {
                if(temp2[i].isEqual(facets[j])) {
                    found = true;
                }
            }
            if(!found) {
                result.push_back(temp2[i]);
            }
            found = false;
        }
        return result;
    }
}

/*
 * Determines the ridges between the facets and their neighbors.
 * @return The list of ridges, i.e. Hyperplanes with dimension d-2 who are the intersection of two facets.
 */
template<typename Number>
std::vector<Ridge> getRidges(std::vector<Facet> facets) {
    if(facets.isEmpty()) {
        return null;
    }
    else {
        std::vector<Ridge> result;
        std::vector<Facet> neighbors = getFacetsNeighbors(facets);
        for(int i = 0; i<facets.size(); i++) {
            for(int j = 0; j<neighbors.size(); j++) {
                if(facets[i].isNeighbor(neighbors[j])) {
                    result.push_back(new Ridge(facets[i], neighbors[j]));
                }
            }
        }
        return result;
    }
}


/*
 * Determines the list of points which were outside of the visible_facets. The points are taken from hashlist.
 * @return The list of points which were outside of the visible_facets
 */
template<typename Number>
std::vector<Point<Number>> points_outside_of_visible_facets(std::vector<Facet> visible_facets) {
    std::vector<Point<Number>> temp;
    std::vector<Point<Number>> result;
    std::vector<Point<Number>> outsideset;
    for(int i = 0; i < visible_facets.size(); i++) {
        outsideset = visible_facets[i].outsideset();
        for(int j = 0; i<outsideset.size(); j++) {
            temp.push_back(outsideset[j]);
        }
    }
    bool found = false;
    for(int i = 0; i < temp.size(); i++) {
        for(int j = 0; i<result.size(); j++) {
            if(temp[i].isEqual(result[j])) {
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

/*
 * Checks for each facet if it has at least one point above. If it has it is not outside and will be returned.
 * @return The list of facets that have at least one point above.
 */
template<typename Number>
std::vector<Facet> not_outside_facet(std::vector<Facet> facets) {
    std::vector<Facet> result;
    for(int i = 0; i < facets.size(); i++) {
        if(!facets[i].outsideset().isEmpty()) {
            result.push_back(facets[i]);
        }
    }
    return result;
}



}

}
