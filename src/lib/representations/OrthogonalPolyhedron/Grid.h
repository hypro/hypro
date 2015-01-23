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
            typedef std::map<const carl::Variable, std::vector<Number> > gridPoints;
        
        private:
            gridMap mGridMap; // mutable to allow performance optimization
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
            Grid(const vSet<Number>& vertices)
            {
                induceGrid(vertices);
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
            int size() const
            {
                return mGridMap.size();
            }
            
            /**
             * Returns if this grid is empty.
             * @return 
             */
            bool empty() const
            {
                return mGridMap.empty();
            }
            
            /**
             * Inserts the value for the point.
             * 
             * @param point
             * @param color
             */
            void insert(const Point<Number>& point, bool color)
            {
                mGridMap.insert(std::make_pair(calculateInduced(point), color));
            }
            
            /**
             * Inserts the value for the induced point.
             *
             * @param inducedPoint
             * @param color
             */
            void insertInduced(const Point<int>& inducedPoint, bool color)
            {
                mGridMap.insert(std::make_pair(inducedPoint, color));
            }
            
            /**
             * Returns the color of the given point.
             *
             * @param point
             * @return the color of the point
             */
            bool colorAt(const Point<Number>& point) const
            {
                return mGridMap.at(calculateInduced(point));
            }
            
            /**
             * Returns the color of the given induced pointi
             * 
             * @param point
             * @return the color of the induced point
             */
            bool colorAtInduced(const Point<int>& inducedPoint) const
            {
                return mGridMap.at(inducedPoint);
            }
            
            /**
             * 
             * @param point
             * @return 
             */
            typename gridMap::const_iterator find(const Point<Number>& point) const
            {
                return mGridMap.find(calculateInduced(point));
            }
            
            /**
             * 
             * @param inducedPoint
             * @return 
             */
            typename gridMap::const_iterator findInduced(const Point<int>& inducedPoint) const
            {
                return mGridMap.find(inducedPoint);
            }
            
            /**
             *
             * @return 
             */
            typename gridMap::const_iterator end() const
            {
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
            void clear()
            {
                mGridMap.clear();
            }

    };
}

#include "Grid.tpp"
