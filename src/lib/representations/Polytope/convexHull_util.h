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

template<typename Number>
static int dimensionCheck(const std::vector<Point<Number>>& points) {
	matrix_t<Number> matrix = matrix_t<Number>(points.at(0).rawCoordinates().size(), points.size());
	for(unsigned i = 0; i < points.at(0).rawCoordinates().size(); i++){
		for(unsigned j = 0; j < points.size(); j++){
			matrix(i,j) = points.at(j).rawCoordinates()(i);
		}
	}
	return matrix.fullPivLu().rank();
}

template<typename Number>
static bool maxRank(const std::vector<Point<Number>>& points, const Point<Number> point) {
	matrix_t<Number> matrix = matrix_t<Number>(point.rawCoordinates().size(), points.size() + 1);
	for(unsigned i = 0; i < point.rawCoordinates().size(); i++){
		for(unsigned j = 0; j < points.size(); j++){
			matrix(i,j) = points.at(j).rawCoordinates()(i);
		}
	}
	for(unsigned j = 0; j < point.rawCoordinates().size(); j++){
		matrix(j,points.size()) = point.rawCoordinates()(j);
	}

	return matrix.fullPivLu().rank() == (unsigned)(points.size() + 1);
}


/*
 * Creates initial Convex Hull in dimension d with d+1 Points out of all the points given. Neighbor relationship of the facets are saved in neighbors.
 * @return The list of facets, i.e. Hyperplanes with dimension d-1 who form the Convex Hull.
 */
template<typename Number>
static std::vector<Facet<Number>> initConvexHull(const std::vector<Point<Number>>& points){
	// TODO: check if points is empty or contains less than d+1 elements!
	int dimCheck = dimensionCheck(points);
	int d = points[0].dimension();
	if(dimCheck == d){
	std::vector<Point<Number>> initialPoints;
	Facet<Number> f = Facet<Number>();
	for(int i = 0; i < d; ++i) {
		for(unsigned j = 0; j < points.size(); j++) {
			if(maxRank(initialPoints, points[j])){
				initialPoints.push_back(points[j]);
				break;
			}
		}
	}
	for(unsigned i = 0; i< points.size(); i++) {
		bool found = false;
		for(unsigned j = 0; j < initialPoints.size(); j++) {
			if(points[i] == initialPoints[j]){
				found = true;
			}
		}
		if(!found){
			initialPoints.push_back(points[i]);
		}
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
				facets[j].addNeighbor(facets[i]);
			}
		}
	}
	return facets;
	}
	else {
		std::cout << __func__ << __LINE__ << "Inconsistent point set " << std::endl;
		return std::vector<Facet<Number>>();
	}
}

/*
 * @return The list of points that are not contained by the facets.
 */
template<typename Number>
static void points_not_in_facets(const std::vector<Point<Number>>& points, const std::vector<Facet<Number>>& facets, std::vector<Point<Number>>& unassignedPoints, std::vector<Point<Number>>& assignedPoints){
	unassignedPoints = points;
	std::vector<Point<Number>> pointsInFacets;
	for(Facet<Number> facet : facets) {
		std::vector<Point<Number>> pointsInFacet = facet.vertices();
		for(Point<Number> p : pointsInFacet) {
			pointsInFacets.push_back(p);
		}
	}
	// Stefan: pointsInFacets holds all generating points of the given facets.

	std::vector<int> removeables;
	for (unsigned i = 0; i<unassignedPoints.size(); i++) {
		for (unsigned j = 0; j<pointsInFacets.size(); j++) {
			if(unassignedPoints[i] == pointsInFacets[j]) {
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
		assignedPoints.push_back(unassignedPoints.at(remove[i]));
		unassignedPoints.erase(unassignedPoints.begin() + remove[i]-i);
	}

	std::cout << __func__ << " : " << __LINE__ << unassignedPoints << "  " << assignedPoints << std::endl;
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
static std::vector<Ridge<Number>> getRidges(Facet<Number>& facet) {
	std::vector<Ridge<Number>> result;
	if(!facet.empty()) {
		std::vector<Facet<Number>> neighbors = facet.rNeighbors();
		//std::cout << __func__ << " Current Neighbors of Ridges: " << neighbors << std::endl;
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
static void not_outside_facet(std::vector<Facet<Number>>& facets, std::queue<Facet<Number>>& result ) {
	std::stack<unsigned> toDelete;
	for(unsigned i = 0; i < facets.size(); i++) {
		if(!facets[i].getOutsideSet().empty()) {
			result.push(facets[i]);
			toDelete.push(i);
		}
	}
	while(!toDelete.empty()) {
		facets.erase(facets.begin() + toDelete.top()); //index fehler?
		toDelete.pop();
	}
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
		int checkValue = facet1.vertices().at(0).dimension() - 1; //number of points they have to share to be neighbors
		//std::cout << "checkValue: " << checkValue << std::endl;
		int currentValue = 0; //number of points that are confirmed to be shared
		for(unsigned i = 0; i < facet1.vertices().size(); i++) {
			for(unsigned j = 0; j < facet2.vertices().size(); j++){
				if(facet1.vertices().at(i) == facet2.vertices().at(j)){
					currentValue++;
				}
			}
		}
		//std::cout << "currentValue: " << currentValue << std::endl;
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
				newFacets[i].addNeighbor(newFacets[j]);
				newFacets[j].addNeighbor(newFacets[i]);// if neighbor check true add to the neighborset of the facet
			}
		}
		//std::cout << __func__ << " NewFacet: " << newFacets[i] << std::endl;
		//std::cout << __func__ << " Neighbors of NewFacet: " << newFacets[i].neighbors() << std::endl;
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


template<typename Number>
static bool includeFacet(const Facet<Number> facet1, const Facet<Number> facet2) {
	if(facet1 == facet2){
		return true;
	}
	else {
		int checkValue = facet1.vertices().size();
		if(checkValue > (int) facet2.vertices().size()){
			checkValue = facet2.vertices().size();
		}
		int currentValue = 0;
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

template<typename Number>
static std::vector<Facet<Number>> maximizeFacets (std::vector<Facet<Number>>& facets) {
	std::vector<Facet<Number>> result;
	//unsigned dimension = facets.front().vertices().front().dimension();
	std::cout << __func__ << " : " << __LINE__ << std::endl;
		while(!facets.empty()){
			Facet<Number> newFacet = facets.front();
			facets.erase(facets.begin());
			//std::cout << __func__ << " : " << __LINE__ << std::endl;
			for(unsigned l = 0; l<facets.size(); l++){
				Facet<Number> neighbor = facets.at(l);
				//std::cout << __func__ << " : " << __LINE__ << " Neighbors : " << newFacet.neighbors() << std::endl;
				if(neighborCheck(newFacet, neighbor)){
					std::cout << __func__ << " : " << __LINE__ << " neighbor : " << neighbor << std::endl;
					Point<Number> point1, point2;
					for(unsigned i = 0; i<neighbor.vertices().size(); i++) {
						bool found = false;
						for(unsigned j = 0; j<newFacet.vertices().size(); j++) {
							if(neighbor.vertices().at(i) == newFacet.vertices().at(j)){
								found = true;
							}
						}
						if(!found) {
							point1 = neighbor.vertices().at(i);
						}

					}

					for(unsigned i = 0; i<newFacet.vertices().size(); i++) {
						bool found = false;
						for(unsigned j = 0; j<neighbor.vertices().size(); j++) {
							if(neighbor.vertices().at(j) == newFacet.vertices().at(i)){
								found = true;
							}
						}
						if(!found) {
							point2 = newFacet.vertices().at(i);
						}
					}
					//std::cout << __func__ << " : " << __LINE__ << " normalsize : " << point1.dimension() << std::endl;
					std::cout << __func__ << " : " << __LINE__ << " Dist 1 : " << newFacet.getDist(point1) << std::endl;
					std::cout << __func__ << " : " << __LINE__ << " Dist 2 : " << neighbor.getDist(point2) << std::endl;
					if ((newFacet.getDist(point1) == 0) && (neighbor.getDist(point2) == 0)){
						std::cout << __func__ << " : " << __LINE__ << " Same level neighbor : " << neighbor << std::endl;
						newFacet.addPoint(point1);
						for(unsigned i = 0; i<neighbor.rNeighbors().size(); i++) {
							if(!newFacet.isNeighbor(neighbor.rNeighbors().at(i))){
								newFacet.addNeighbor(neighbor.rNeighbors().at(i));
							}
						}
						//for(unsigned k = 0; k<neighbor.neighbors().size(); k++){
						//	newFacet.addNeighbor(neighbor.neighbors().at(k));
						//}
						facets.erase(facets.begin()+l);
						l--;
					}
				}
				else if(includeFacet(newFacet, neighbor)){
					facets.erase(facets.begin()+l);
				}
			}
			result.push_back(newFacet);
		}
		std::cout << __func__ << " : " << __LINE__ << std::endl;

		for(unsigned i = 0; i<result.size();){
			bool del = false;
			for(unsigned j = 0; j<result.size();){
				if(includeFacet(result[i], result[j]) && result[i]!=result[j]) {
					result.erase(result.begin()+j);
					del = true;
				}else{
					j++;
				}
			}
			if(!del){
				i++;
			}
		}


	/*	for(unsigned a = 0; a<facets.size(); a++ ){
			Facet<Number> newFacet = facets.at(a);
			//std::cout << __func__ << " : " << __LINE__ << std::endl;
			for(unsigned l = 0; l<facets.size(); l++){
				Facet<Number> neighbor = facets.at(l);
				if(neighborCheck(newFacet, neighbor)){
					std::cout << __func__ << " : " << __LINE__ << " neighbor : " << neighbor << std::endl;
					Point<Number> point1, point2;
					for(unsigned i = 0; i<neighbor.vertices().size(); i++) {
						bool found = false;
						for(unsigned j = 0; j<newFacet.vertices().size(); j++) {
							if(neighbor.vertices().at(i) == newFacet.vertices().at(j)){
								found = true;
							}
						}
						if(!found) {
							point1 = neighbor.vertices().at(i);
						}

					}

					for(unsigned i = 0; i<newFacet.vertices().size(); i++) {
						bool found = false;
						for(unsigned j = 0; j<neighbor.vertices().size(); j++) {
							if(neighbor.vertices().at(j) == newFacet.vertices().at(i)){
								found = true;
							}
						}
						if(!found) {
							point2 = newFacet.vertices().at(i);
						}
					}

					std::cout << __func__ << " : " << __LINE__ << " Dist 1 : " << newFacet.getDist(point1) << std::endl;
					std::cout << __func__ << " : " << __LINE__ << " Dist 2 : " << neighbor.getDist(point2) << std::endl;
					if ((newFacet.getDist(point1) == 0) || (neighbor.getDist(point2) == 0)){
						std::cout << __func__ << " : " << __LINE__ << " Same level neighbor : " << neighbor << std::endl;
						newFacet.addPoint(point1);
						//for(unsigned k = 0; k<neighbor.neighbors().size(); k++){
						//	newFacet.addNeighbor(neighbor.neighbors().at(k));
						//}
						//facets.erase(facets.begin()+l);
						//l--;
					}
				}
			}
			result.push_back(newFacet);
		}
		std::cout << __func__ << " : " << __LINE__ << std::endl;
	 	 */
		std::cout << __func__ << " : " << __LINE__ << std::endl;
	return result;
}

template<typename Number>
static Facet<Number> newNeighbor(Facet<Number> oldNeighbor, std::vector<Facet<Number>> newFacets){
	for(unsigned i = 0; i<newFacets.size(); i++) {
		if(neighborCheck(oldNeighbor, newFacets[i])){
			return newFacets[i];
		}
	}
	return oldNeighbor;
}

template<typename Number>
static void setNeighborhoodOfPoints(std::vector<Facet<Number>>& facets) {
	for(unsigned i = 0; i<facets.size(); i++) {
		for(unsigned j = 0; j<facets[i].vertices().size(); j++){
			for(unsigned k = 0; k<facets[i].vertices().size(); k++){
				if(facets[i].vertices().at(j) == facets[i].vertices().at(k)){
					facets[i].vertices().at(j).addNeighbor(&(facets[i].vertices().at(k)));
				}
			}
		}
	}
}

}

}
