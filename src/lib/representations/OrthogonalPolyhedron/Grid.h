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
#include <map>
#include <vector>

namespace hypro
{
    /**
     * Represents a grid which maps points to a its colour.
     */
    template<typename Number>
    class Grid
    {
        public:
            typedef std::map<Point<Number>, bool> gridMap;
        
        private:
            gridMap mGrid;
            
        public:
            Grid() : mGrid() {}
            Grid(const gridMap& grid) : mGrid(grid) {}
            
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
                mGrid.insert(std::pair<Point<Number>, bool>(point, colour));
            }
            
            /**
             * Recursive function to check if a point is within the polyhedron.
             * For the membership
             *
             * @param point
             * @return true, if the point lies within the polyhedron.
             */
            bool contains(const Point<Number>& point) const;
            
            /**
             * Returns the colour of the given point.
             *
             * @param point
             * @return the colour of the point
             */
            bool colourAt(const Point<Number>& point) const;
            
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