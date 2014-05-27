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
#include "../../datastructures/VertexContainer.h"
#include "../Box/Box.h"
#include <carl/core/Variable.h>
#include <carl/numbers/FLOAT_T.h>
#include <map>
#include <vector>

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
            typedef std::map<carl::Variable, std::vector<carl::FLOAT_T<Number> > > gridPoints;
        
        private:
            gridMap mGridMap;
            gridPoints mInducedGridPoints;
            bool mInduced = false;
            
            /**
             * Reserves the induced grid for all dimensions.
             */
            void reserveInducedGrid();
            
        public:
            
            /**
             * Constructor
             */
            Grid() {}

            /**
             * Constructor
             * 
             * @param grid
             */
            Grid(const gridMap& grid) : mGridMap(grid)
            {
                reserveInducedGrid();
            }
            
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
                assert( mGridMap.size() > 0 );
                return (*mGridMap.begin()).first.dimension();
            }
            
            /**
             * Returns the variables used in this grid. Only points with exactly
             * this variables are allowed to be inserted into the grid.
             * 
             * @return 
             */
            std::vector<carl::Variable> variables() const
            {
                assert( mGridMap.size() > 0 );
                return (*mGridMap.begin()).first.variables();
            }
            
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
            void insertVerticesInMap(const VertexContainer<Number>& vertexContainer);
            
            /**
             * Inserts the value for the point.
             * 
             * @param point
             * @param val
             */
            void insert(const Point<Number>& point, bool colour)
            {
                assert( point.hasDimensions(variables()) );
                mGridMap[calculateInduced(point)] = colour;
            }
            
            /**
             * Returns the colour of the given point.
             *
             * @param point
             * @return the colour of the point
             */
            bool colourAt(const Point<Number>& point)
            {
                return mGridMap[calculateInduced(point)];
            }
            
            /**
             * Calculates the coordinates of the induced grid.
             * 
             * @param vertices
             */
            void induceGrid(const vSet<Number>& vertices);
            
            /**
             * Translate a point into its coordinates on the induced grid.
             * 
             * @param point
             * @return induced point
             */
            Point<Number> calculateInduced(const Point<Number>& point) const;
            
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