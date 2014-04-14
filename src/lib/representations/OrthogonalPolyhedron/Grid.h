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
     * Represents a grid which maps points to a boolean whether
     * the point is in the orthogonal polyhedron.
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
             * Recursive function to check if a point is within the polyhedron.
             * For the membership
             *
             * @param point
             * @return true, if the point lies within the polyhedron.
             */
            bool contains(const Point<Number>& point) const;
            
            /**
             * @brief Used within membershipRecursiveVertex.
             *
             * @param point
             * @return the colour of the point
             */
            bool checkAPoint(const Point<Number>& point) const;
            
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