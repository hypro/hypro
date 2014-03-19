/* 
 * A file which contains the data for a facet needed by the algorithm for convex hulls.
 * File:   Facet.h
 * Author: stefan
 *
 * Created on March 19, 2014, 4:08 PM
 */

#pragma once

#include "../config.h"

namespace hypro
{
    template<class Number>
    class Facet
    {
        public:
        /**
         * Typedefs
         */
            typedef std::set<Point<Number>> vertices;
            typedef std::set<Point<Number>> neighbors;
        
        /**
         * Members
         */
        private:
            vertices            mVertices;
            neighbors           mNeighbors;
            Polynomial          mHyperplane;
            
        /**
         * Constructors & Destructor
         */
        public:
            Facet() : 
                    mVertices(),
                    mNeighbors(),
                    mHyperplane()
            {}
                
            Facet( const Facet<Number>& f) :
                    mVertices(f.vertices()),
                    mNeighbors(f.neighbors()),
                    mHyperplane(f.hyperplane())
            {}
                
            ~Facet()
            {}
        
            /**
             * Getters and Setters
             */
            
            vertices& rVertices()
            {
                return mVertices;
            }
            
            vertices vertices() const
            {
                return mVertices;
            }
            
            neighbors& rNeighbors()
            {
                return mNeighbors;
            }
            
            neighbors neighbors() const
            {
                return mNeighbors;
            }
            
            Polynomial hyperplane() const
            {
                return mHyperplane;
            }
    };
}