/* 
 * @file    NeighborhoodContainer.h
 * @author  Sebastian Junges
 * @author  Benedikt Seidl
 *
 * @since   2014-03-17
 * @version 2014-05-18
 */

#pragma once

#include "../../datastructures/Point.h"
#include "../../datastructures/Vertex.h"
#include <map>
#include <utility>

namespace hypro
{
    /**
     * A neighborhood container which maps points
     * to their set of neighbor points.
     */
    template<typename Number>
    class NeighborhoodContainer {
        
    public:
        typedef std::vector<Point<Number> > neighborhood;
        
    private:
        std::map<Point<Number>, neighborhood> mNeighborhoods;
        
    public:
        NeighborhoodContainer() {}
        
        NeighborhoodContainer(const NeighborhoodContainer<Number>& copy)
        {
            mNeighborhoods.insert(copy.mNeighborhoods.begin(), copy.mNeighborhoods.end());
        }
        
        void clear()
        {
            mNeighborhoods.clear();
        }
        
        bool empty() const
        {
            return mNeighborhoods.empty();
        }
        
        /**
         * Returns the points in the neighborhood.
         *
         * @param p the point
         * @param pointself point is optionally an element of the returned vector
         * @return Vector filled with neighbors in all dimensions
         */
        neighborhood getNeighborhood(const Point<Number>& p, bool pointself = false);
        
        /**
         * Returns the points in the neighborhood, with one fixed dimension.
         *
         * @param p the point
         * @param dimension the fixed dimension
         * @param pointself point is optionally an element of the returned vector
         * @return 
         */
        neighborhood getNeighborhoodForDimension(const Point<Number>& p, const carl::Variable& dimension, bool pointself = false);

        /**
         * Moves all neighbors.
         *
         * @param p the point by which the neighbors should be moved
         */
        //void moveNeighbors(const Point<Number>& p);
        
    private:

        bool hasNeighborhood(const Point<Number>& p) const
        {
            return mNeighborhoods.find(p) != mNeighborhoods.end();
        }

        void calculateNeighborhood(const Point<Number>& p);
        
    };
    
}//namespace

#include "NeighborhoodContainer.tpp"

