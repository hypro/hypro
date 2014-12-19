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
     * Represents a grid which maps points to its colour.
     */
    template<typename Number>
    class Grid
    {
        public:
            typedef std::map<Point<Number>, bool> gridMap;
            typedef std::map<const carl::Variable, std::vector<Number> > gridPoints;
        
        private:
            mutable gridMap mGridMap; // mutable to allow performance optimization
            gridPoints mInducedGridPoints;
            bool mInduced = false;
            std::vector<carl::Variable> mVariables;
            
        public:
            
            /**
             * Constructor
             */
            Grid() {}
            
            /**
             * Copy constructor
             */
            Grid(const Grid<Number>& copy) :
            	mGridMap(copy.mGridMap),
            	mInducedGridPoints(copy.mInducedGridPoints),
            	mInduced(copy.mInduced),
            	mVariables(copy.mVariables)
            {}
            
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
             * Returns the dimension of this grid.
             * @return dimension
             */
            int dimension() const
            {
                return mVariables.size();
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
             * Returns the variables used in this grid. Only points with exactly
             * this variables are allowed to be inserted into the grid.
             * 
             * @return 
             */
            std::vector<carl::Variable> variables() const
            {
                return mVariables;
            }

            /**
             * Reserves the induced grid for all dimensions.
             * 
             * @param variables
             */
            void reserveInducedGrid(const std::vector<carl::Variable>& variables);
            
            /**
             * Returns whether the grid is induced.
             * @return induced
             */
            bool induced() const
            {
                return mInduced;
            }
            
            /**
             * Method to copy from a VertexContainer to a grid.
             * 
             * @param vertexContainer
             */
            void insertVerticesInMap(const vSet<Number>& vertices);
            
            /**
             * Inserts the value for the point.
             * 
             * @param point
             * @param colour
             */
            void insert(const Point<Number>& point, bool colour) const
            {
                assert( point.hasDimensions(mVariables) );
                mGridMap.insert(std::make_pair(calculateInduced(point), colour));
            }
            
            /**
             * Inserts the value for the induced point.
             *
             * @param inducedPoint
             * @param colour
             */
            void insertInduced(const Point<Number>& inducedPoint, bool colour) const
            {
                assert( inducedPoint.hasDimensions(mVariables) );
                mGridMap.insert(std::make_pair(inducedPoint, colour));
            }
            
            /**
             * Returns the colour of the given point.
             *
             * @param point
             * @return the colour of the point
             */
            bool colourAt(const Point<Number>& point) const
            {
                return mGridMap[calculateInduced(point)];
            }
            
            /**
             * Returns the colour of the given induced pointi
             * 
             * @param point
             * @return the colour of the induced point
             */
            bool colourAtInduced(const Point<Number>& inducedPoint) const
            {
                return mGridMap[inducedPoint];
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
            typename gridMap::const_iterator findInduced(const Point<Number>& inducedPoint) const
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
             * Calculates the coordinates of the induced grid.
             * 
             * @param vertices
             */
            void induceGrid(const vSet<Number>& vertices);
            
            /**
             * Gets the next point on the gird.
             * 
             * @param point
             * @return next point on grid
             */
            Point<Number> nextPointOnGrid(const Point<Number>& point) const;
            
            /**
             * Calculates the coordinates of this point on the induced grid.
             * 
             * @param point
             * @return induced point
             */
            Point<Number> calculateInduced(const Point<Number>& point) const;
            
            /**
             * Calculates the original coordinates of this induced point.
             * @param inducedPoint
             * @return original point
             */
            Point<Number> calculateOriginal(const Point<Number>& inducedPoint) const;
            
            /**
             * Translates the points to induced points.
             * 
             * @param vertices
             * @return induced vertices
             */
            vSet<Number> translateToInduced(const vSet<Number>& vertices) const;
            
            /**
             * Translates the induced points to original points.
             * 
             * @param inducedVertices
             * @return original vertices
             */
            vSet<Number> translateToOriginal(const vSet<Number>& inducedVertices) const;
            
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
