/*
 * Contains utilities to create the convex hull.
 * @file   convexHull_util.h
 * @author tayfun
 *
 * @since       2014-12-10
 * @version     2015-01-21
 */

#pragma once

#include "../../datastructures/Hyperplane.h"
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
static std::vector<Facet<Number>> initConvexHull(const std::vector<Point<Number>>& points){
	// TODO: check if points is empty or contains less than d+1 elements!
	int d = points[0].dimension();
	std::vector<Point<Number>> initialPoints;
	Facet<Number> f = Facet<Number>();
	for(int i = 0; i < d+1; ++i) {
		initialPoints.push_back(points[i]);
		// TODO: Introduce a consistency check here to ensure that this is not degenerate.
	}
	std::vector<Facet<Number>> facets;
	for(int i = 0; i < d+1; i++) {
		facets.push_back(f);
	}
	for(int i = 0; i < d+1; ++i) {
		std::vector<Point<Number>> points_for_facet;
		for(int j = 0; j < d+1; ++j) {
			if(i!=j) {
				points_for_facet.push_back(initialPoints[j]);
			}
		}
		facets[i].setPoints(points_for_facet, initialPoints[i]);
	}

	for(int i = 0; i < d+1; ++i) {
		for(int j = 0; j < d+1; ++j) {
			if(i!=j) {
				facets[i].addNeighbor(facets[j]);
			}
		}
	}
	return facets;
}

/*
 * @return The list of points that are not contained by the facets.
 */
template<typename Number>
static std::vector<Point<Number>> points_not_in_facets(std::vector<Point<Number>> points, const std::vector<Facet<Number>>& facets){
	std::vector<Point<Number>> pointsInFacets;
	for(Facet<Number> facet : facets) {
		std::vector<Point<Number>> pointsInFacet = facet.vertices();
		for(Point<Number> p : pointsInFacet) {
			pointsInFacets.push_back(p);
		}
	}
	// Stefan: pointsInFacets holds all generating points of the given facets.

	std::vector<int> removeables;
	for (unsigned i = 0; i<points.size(); i++) {
		for (unsigned j = 0; j<pointsInFacets.size(); j++) {
			if(points[i] == pointsInFacets[j]) {
				removeables.push_back(i);
			}
		}
	}
	// Stefan: removables holds the indices of the points in points, which are contained in one of the facets.

	std::vector<int> remove;
	for(unsigned i = 0; i<removeables.size(); i++){
		bool found = false;
		for(unsigned j = 0; j<remove.size(); j++){
			if(remove[j] == removeables[i]){
				found = true;
			}
		}
		if(!found){
			remove.push_back(removeables[i]);
		}
	}
	// Clear removables of duplicates (-> remove)

	for(unsigned i = 0; i<remove.size(); i++){
		points.erase(points.begin() + remove[i]-i);
	}
	return points;
}

/*
 * Determines the neighbors of the Hyperplanes. Neighbors are taken from neighbors.
 * @return The list of neighbors from the Hyperplanes.
 */
template<typename Number>
static std::vector<Facet<Number>> getFacetsNeighbors(const std::vector<Facet<Number>>& facets){
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
		// Stefan: After this, temp contains all collected neighbors of all input facets.

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
		// Stefan: Here temp2 is a copy of temp, where the duplicates are removed.

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
		// Stefan: result contains all facets, that are neighbors of the input facets (without duplicates and without the facets themselves).
		return result;
	}
}
/*
 * Determines the ridges between the facets and their neighbors.
 * @return The list of ridges, i.e. Hyperplanes with dimension d-2 who are the intersection of two facets.
 */
template<typename Number>
static std::vector<Ridge<Number>> getRidges(const std::vector<Facet<Number>>& facets) {
	if(facets.empty()) {
		return std::vector<Ridge<Number>>();
	}
	else {
		std::vector<Ridge<Number>> result;
		std::vector<Facet<Number>> neighbors = getFacetsNeighbors(facets);
		for(unsigned i = 0; i<facets.size(); ++i) {
			for(unsigned j = 0; j<neighbors.size(); ++j) {
				if(facets[i].isNeighbor(neighbors[j])) {
					Ridge<Number> newRidge(facets[i], neighbors[j]);
					result.push_back(newRidge);
				}
			}
		}
		return result;
	}
}


template<typename Number>
static std::vector<Ridge<Number>> getRidges(const Facet<Number>& facet) {
	std::vector<Ridge<Number>> result;
	if(!facet.empty()) {
		std::vector<Facet<Number>> neighbors = facet.neighbors();
		for(unsigned j = 0; j<neighbors.size(); ++j) {
			Ridge<Number> newRidge(facet, neighbors[j]);
			result.push_back(newRidge);
		}
	}
	return result;
}


/*
 * Determines the list of points which were outside of the visible_facets. The points are taken from hashlist.
 * @return The list of points which were outside of the visible_facets
 */
template<typename Number>
static std::vector<Point<Number>> points_outside_of_visible_facets(const std::vector<Facet<Number>>& visible_facets) {
	std::vector<Point<Number>> temp;
	std::vector<Point<Number>> result;
	std::vector<Point<Number>> outsideset;
	for(unsigned i = 0; i < visible_facets.size(); i++) {
		outsideset = visible_facets[i].getOutsideSet();
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

/*
 * Checks for each facet if it has at least one point above. If it has it is not outside and will be returned. Note that the input facets is modified to 
 * contain only facets with an empty outside set.
 * @return The list of facets that have at least one point above.
 */
template<typename Number>
static std::queue<Facet<Number>> not_outside_facet(std::vector<Facet<Number>>& facets) {
	std::queue<Facet<Number>> result;
	std::stack<unsigned> toDelete;
	for(unsigned i = 0; i < facets.size(); i++) {
		if(!facets[i].getOutsideSet().empty()) {
			result.push(facets[i]);
			toDelete.push(i);
		}
	}
	while(!toDelete.empty()) {
		facets.erase(facets.begin() + toDelete.top());
		toDelete.pop();
	}
	return result;
}


/*
 * Checks if two facets are neighbors by determining the number of points they share
 */
template<typename Number>
static bool neighborCheck(const Facet<Number> facet1, const Facet<Number> facet2) {
	if(facet1 == facet2){
		return false;
	}
	else {
		int checkValue = facet1.vertices().size() - 1; //number of points they have to share to be neighbors
		int currentValue = 0; //number of points that are confirmed to be shared
		for(unsigned i = 0; i < facet1.vertices().size(); i++) {
			for(unsigned j = 0; j < facet2.vertices().size(); j++){
				if(facet1.vertices().at(i) == facet2.vertices().at(j)){
					currentValue++;
				}
			}
		}
		return checkValue == currentValue;
	}
}

/*
 * Finds the neighbors of the new created Facets among themselves
 */
template<typename Number>
static void determineNeighbors(std::vector<Facet<Number>>& newFacets){
	for(unsigned i = 0; i < newFacets.size(); i++) {
		for(unsigned j = 0; j < newFacets.size(); j++){
			if(neighborCheck(newFacets[i],newFacets[j])){
				newFacets[i].addNeighbor(newFacets[j]); // if neighbor check true add to the neighborset of the facet
			}
		}
	}
}


/*
 * Finds the inside Point to a ridge and an associated facet, which is the point in the facet which isn't in the ridge
 */
template<typename Number>
static Point<Number> findInsidePoint(const Ridge<Number>& ridge, const Facet<Number>& _facet){
	for(Point<Number> point1 : _facet.vertices()){
		bool found = true;
		for(Point<Number> point2: ridge.vertices()){
			if(point1 == point2) {
				found = false;
				break;
			}
		}
		if(found)
			return point1;
	}
	assert(false);
	return Point<Number>();
}

}

}
