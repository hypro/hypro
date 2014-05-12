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
            typedef std::map<carl::Variable, std::vector<Number> > gridPoints;
        
        private:
            gridMap mGrid;
            gridPoints mInducedGridPoints;
            bool mInduced;
            Box<Number> mBoundingBox;
            
            /**
             * Reserves the induced grid for all dimensions.
             */
            void reserveInducedGrid();
            
        public:
            
            /**
             * Constructors
             */
            
            Grid() {}
            
            Grid(const gridMap& grid) : mGrid(grid)
            {
                reserveInducedGrid();
            }
            
            Grid(const gridMap& grid, const Box<Number> boundingBox) : mGrid(grid), mBoundingBox(boundingBox)
            {
                reserveInducedGrid();
            }
            
            /**
             * Returns the dimension of this grid.
             * @return dimension
             */
            int dimension()
            {
                assert( mGrid.size() > 0 );
                return (*mGrid.begin()).first.dimension();
            }
            
            std::vector<carl::Variable> variables()
            {
                assert( mGrid.size() > 0 );
                return (*mGrid.begin()).first.variables();
            }
            
            /**
             * Returns whether the grid is induced.
             * @return induced
             */
            bool induced()
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
             * Calculates the coordinates of the induced grid
             */
            void induceGrid(const vSet<Number>& vertices);
            
            /**
             * Translate a point into its coordinates on the induced grid.
             * @param point
             * @return induced point
             */
            Point<Number> calculateInduced(const Point<Number>& point) const;
            
            /**
             * Inserts the value for the point.
             * 
             * @param point
             * @param val
             */
            void insert(const Point<Number>& point, bool colour)
            {
                assert( point.dimension() == dimension() );
                mGrid.insert(std::pair<Point<Number>, bool>(point, colour));
            }
            
            /**
             * Recursive function to check if a point is within the polyhedron.
             * For the membership
             *
             * @param point
             * @return true, if the point lies within the polyhedron.
             */
            bool contains(const Point<Number>& point);
            
            /**
             * Returns the colour of the given point.
             *
             * @param point
             * @return the colour of the point
             */
            bool colourAt(const Point<Number>& point);
            
            /**
             * Clears the grid.
             */
            void clear()
            {
                mGrid.clear();
            }
    };
}

#include "Grid.tpp"