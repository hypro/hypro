/* 
 * @file    Grid.h
 * @author  Benedikt Seidl
 *
 * @since   2014-04-14
 * @version 2014-04-14
 */

#pragma once

#include "../../datastructures/Point.h"
#include "../../datastructures/Vertex.h"
#include <carl/core/Variable.h>
#include <vector>
#include <map>
#include <bitset>

namespace hypro
{
	/**
	 * Represents a grid which maps points to its color.
	 */
	template<typename Number>
	class Grid
	{
		public:
			typedef std::map<Point<int>, bool> gridMap;
			typedef std::map<unsigned, std::vector<Number> > gridPoints;
		
		private:
			gridMap mGridMap;
			gridPoints mInducedGridPoints;
			
		public:
			
			/**
			 * Constructor
			 */
			Grid() {}

			/**
			 * Constructor
			 *
			 * @param vertices
			 */
			Grid(const vSet<Number>& vertices){
				induceGrid(vertices);
			}

			Grid(const std::vector<Vertex<Number>>& _vertices){
				induceGrid(vSet<Number>(_vertices.begin(), _vertices.end()));
			}
			
			/**
			 * Copy constructor
			 */
			Grid(const Grid<Number>& copy) :
				mGridMap(copy.mGridMap),
				mInducedGridPoints(copy.mInducedGridPoints)
			{}

			Grid<Number>& operator= ( const Grid<Number>& ) = default;
			Grid<Number>& operator= ( Grid<Number>&& ) = default;
		
			/**
			 * Clears the grid, induces it and sets up the vertices.
			 *
			 * @param vertices
			 */
			void induceGrid(const vSet<Number>& vertices);
			
			/**
			 * Returns the size ie. the number of points saved in this grid.
			 * 
			 * @return 
			 */
			int size() const {
				return mGridMap.size();
			}

			unsigned dimension() const {
				return mInducedGridPoints.size();
			}

			std::vector<Vertex<Number>> vertices() const {
				std::vector<Vertex<Number>> res;
				for(const auto& point : mGridMap) {
					res.emplace_back(calculateOriginal(point.first), point.second);
				}
				return res;
			}
			
			/**
			 * Returns if this grid is empty.
			 * @return 
			 */
			bool empty() const {
				return mGridMap.empty();
			}
			
			/**
			 * Inserts the value for the point.
			 * 
			 * @param point
			 * @param color
			 */
			void insert(const Point<Number>& point, bool color) {
				mGridMap.insert(std::make_pair(calculateInduced(point), color));
			}
			
			/**
			 * Inserts the value for the induced point.
			 *
			 * @param inducedPoint
			 * @param color
			 */
			void insertInduced(const Point<int>& inducedPoint, bool color) {
				mGridMap.insert(std::make_pair(inducedPoint, color));
			}
			
			/**
			 * Returns the color of the given point.
			 *
			 * @param point
			 * @return the color of the point
			 */
			bool colorAt(const Point<Number>& point) const {
				return mGridMap.at(calculateInduced(point));
			}
			
			/**
			 * Returns the color of the given induced point.
			 * 
			 * @param point
			 * @return the color of the induced point
			 */
			bool colorAtInduced(const Point<int>& inducedPoint) const {
				return mGridMap.at(inducedPoint);
			}

			Point<Number> iNeighborInduced(const Point<Number>& _inducedPoint, unsigned _dimension) const {
				assert(_dimension < mInducedGridPoints.size());
				Point<Number> result = _inducedPoint;
				unsigned pos = 0;
				Number last = _inducedPoint.at(_dimension);
				while(mInducedGridPoints.at(_dimension).at(pos) < _inducedPoint.at(_dimension) ){
					last = mInducedGridPoints.at(_dimension).at(pos);
					++pos;
				} 
				result[_dimension] = last;
				std::cout << result << std::endl;
				return result;
			}

			Point<Number> iPredecessor(const Point<Number>& _point, unsigned _dimension) const {
				return iNeighborInduced(_point,_dimension);
			}

			std::vector<Point> iSliceInduced(unsigned i, unsigned pos) const {
				std::vector<Point> result;
				// get all points with common i-Component
				for(unsigned i = 0; i < std::pow(2,d-1); ++i) {
					std::bitset<MAX_DIMENSION_LIMIT> map(i);
					unsigned pos = 0;
					Point<Number> neighbor(directPredecessor);
					while(pos < d) {
						if(map.test(pos))
							neighbor[pos] = _inducedPoint.at(pos);
						++pos;
					}
					result.emplace_back(std::move(neighbor));
				}
			}

			std::vector<Point<Number>> iNeighborhood(const Point<Number>& _inducedPoint, unsigned _dimension) const {
				std::vector<Point<Number>> result;
				result.emplace_back(iNeighborInduced(_inducedPoint,_dimension));
				result.emplace_back(_inducedPoint);
				return result;
			}

			std::vector<Point<Number>> neighborhoodInduced(const Point<Number>& _inducedPoint) const {
				std::vector<Point<Number>> result;
				unsigned d = this->dimension();

				// calculate direct predecessor point in all dimensions
				Point<Number> directPredecessor = std::move(Point<Number>::zero(d));
				for(unsigned dim = 0; dim < d; ++dim) {
					unsigned p = 0;
					while(mInducedGridPoints.at(dim).at(p) < _inducedPoint.at(dim)) ++p;
					
					if (p > 0)
						directPredecessor[dim] = mInducedGridPoints.at(dim).at(p-1);
				}

				// get all 2^d i-neighbors by combination of the point and its direct predecessor
				for(unsigned i = 0; i < std::pow(2,d); ++i) {
					std::bitset<MAX_DIMENSION_LIMIT> map(i);
					unsigned pos = 0;
					Point<Number> neighbor(directPredecessor);
					while(pos < d) {
						if(map.test(pos))
							neighbor[pos] = _inducedPoint.at(pos);
						++pos;
					}
					result.emplace_back(std::move(neighbor));
				}

				return result;
			}

			/**
			 * 
			 * @param point
			 * @return 
			 */
			typename gridMap::const_iterator find(const Point<Number>& point) const {
				return mGridMap.find(calculateInduced(point));
			}
			
			/**
			 * 
			 * @param inducedPoint
			 * @return 
			 */
			typename gridMap::const_iterator findInduced(const Point<int>& inducedPoint) const {
				return mGridMap.find(inducedPoint);
			}
			
			/**
			 *
			 * @return 
			 */
			typename gridMap::const_iterator end() const {
				return mGridMap.end();
			}
			
			/**
			 * Calculates the coordinates of this point on the induced grid.
			 * 
			 * @param point
			 * @return induced point
			 */
			Point<int> calculateInduced(const Point<Number>& point) const;
			
			/**
			 * Calculates the original coordinates of this induced point.
			 * @param inducedPoint
			 * @return original point
			 */
			Point<Number> calculateOriginal(const Point<int>& inducedPoint) const;
			
			/**
			 * Translates the points to induced points.
			 * 
			 * @param vertices
			 * @return induced vertices
			 */
			vSet<int> translateToInduced(const vSet<Number>& vertices) const;
			
			/**
			 * Translates the induced points to original points.
			 * 
			 * @param inducedVertices
			 * @return original vertices
			 */
			vSet<Number> translateToOriginal(const vSet<int>& inducedVertices) const;
			
			/**
			 * Clears the grid.
			 */
			void clear() {
				mGridMap.clear();
			}

			friend bool operator==(const Grid<Number>& op1, const Grid<Number>& op2) {
				return op1.mInducedGridPoints == op2.mInducedGridPoints;
			}

			friend bool operator!=(const Grid<Number>& op1, const Grid<Number>& op2) {
				return op1.mInducedGridPoints != op2.mInducedGridPoints;
			}

			friend std::ostream& operator<<(std::ostream& out, const Grid<Number>& grid) {
				out << "[";
				for(unsigned d = 0; d < grid.mInducedGridPoints.size(); ++d){
					out << std::endl <<  d << ": ";
					for(unsigned p = 0; p < grid.mInducedGridPoints.at(d).size(); ++p)
						out << grid.mInducedGridPoints.at(d).at(p) << " ";
				}
				out << std::endl << "]" << std::endl;
				return out;
			}
	};
}

#include "Grid.tpp"
