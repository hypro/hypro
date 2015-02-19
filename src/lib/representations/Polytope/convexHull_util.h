/*
 * Contains utilities to create the convex hull.
 * @file   convexHull_util.h
 * @author tayfun
 *
 * @since       2014-12-10
 * @version     2015-01-21
 */

#pragma once

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
static std::vector<Facet<Number>> initConvexHull(std::vector<Point<Number>> points) {
	// TODO: check if points is empty or contains less than d+1 elements!
    int d = points[0].dimension();
    std::vector<Point<Number>> initialPoints;
    Facet<Number> f = Facet<Number>();
    std::cout << __func__ << " : " << __LINE__ << std::endl;
    for(int i = 0; i < d+1; ++i) {
        initialPoints.push_back(points[i]);
		// TODO: Introduce a consistency check here to ensure that this is not degenerate.
    }
    std::cout << __func__ << " : " << __LINE__ << std::endl;
    std::vector<Facet<Number>> facets;
    for(int i = 0; i < d+1; i++) {
        facets.push_back(f);
    }
    std::cout << __func__ << " : " << __LINE__ << std::endl;
    for(int i = 0; i < d+1; ++i) {
    	std::cout << __func__ << " : " << __LINE__ << std::endl;
        std::vector<Point<Number>> points_for_facet;
        for(int j = 0; j < d+1; ++j) {
            if(i!=j) {
                points_for_facet.push_back(initialPoints[j]);
                facets[i].addNeighbor(facets[j]);
            }
        }
        std::cout << __func__ << " : " << __LINE__ << std::endl;
        facets[i].setPoints(points_for_facet);
    }
    std::cout << __func__ << " : " << __LINE__ << std::endl;
    return facets;
}

/*
 * @return The list of points that are not contained by the facets.
 */
template<typename Number>
static std::vector<Point<Number>> points_not_in_facets(std::vector<Point<Number>> points, std::vector<Facet<Number>> facets) {
    std::vector<Point<Number>> pointsInFacets;
    for(Facet<Number> facet : facets) {
        std::set<Point<Number>> pointsInFacet = facet.rVertices();
        for(Point<Number> p : pointsInFacet) {
            pointsInFacets.push_back(p);
        }
    }

    for (unsigned i = 0; i<points.size(); i++) {
        for (unsigned j = 0; j<pointsInFacets.size(); j++) {
            if(points[i] == pointsInFacets[j]) {
                points.erase(points.begin() + i);
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
static std::vector<Facet<Number>> getFacetsNeighbors(std::vector<Facet<Number>> facets) {
    if(facets.empty()) {
        return std::vector<Facet<Number>>();
    }
    else {
        std::vector<Facet<Number>> result;
        std::vector<Facet<Number>> temp;
        std::vector<Facet<Number>> temp2;
        std::vector<Facet<Number>> neighbors;
        for(unsigned i = 0; i<facets.size(); i++) {
            neighbors = facets[i].neighbors();
            for(unsigned j = 0; j<neighbors.size(); j++) {
                temp.push_back(neighbors[j]);
            }
        }
        bool found = false;
        for(unsigned i = 0; i<temp.size(); i++) {
            for(unsigned j = 0; j<temp2.size(); j++) {
                if(temp[i] == temp2[j]) {
                    found = true;
                }
            }
            if(!found) {
                temp2.push_back(temp[i]);
            }
            found = false;
        }

        found = false;
        for(unsigned i = 0; i<temp2.size(); i++) {
            for(unsigned j = 0; j<facets.size(); j++) {
                if(temp2[i] == facets[j]) {
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
static std::vector<Ridge<Number>> getRidges(std::vector<Facet<Number>> facets) {
    if(facets.empty()) {
        return std::vector<Ridge<Number>>();
    }
    else {
        std::vector<Ridge<Number>> result;
        std::vector<Facet<Number>> neighbors = getFacetsNeighbors(facets);
        for(unsigned i = 0; i<facets.size(); i++) {
            for(unsigned j = 0; j<neighbors.size(); j++) {
                if(facets[i].isNeighbor(neighbors[j])) {
                    result.push_back(Ridge<Number>(facets[i].vertices(), neighbors[j].vertices()));
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
static std::vector<Point<Number>> points_outside_of_visible_facets(std::vector<Facet<Number>> visible_facets) {
    std::vector<Point<Number>> temp;
    std::vector<Point<Number>> result;
    std::vector<Point<Number>> outsideset;
    for(unsigned i = 0; i < visible_facets.size(); i++) {
        outsideset = visible_facets[i].getOutsideSet();
        for(unsigned j = 0; i<outsideset.size(); j++) {
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

/*
 * Checks for each facet if it has at least one point above. If it has it is not outside and will be returned.
 * @return The list of facets that have at least one point above.
 */
template<typename Number>
static std::vector<Facet<Number>> not_outside_facet(std::vector<Facet<Number>> facets) {
    std::vector<Facet<Number>> result;
    for(unsigned i = 0; i < facets.size(); i++) {
        if(!facets[i].getOutsideSet().empty()) {
            result.push_back(facets[i]);
        }
    }
    return result;
}



}

}
