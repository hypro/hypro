/* 
 * File:   util.h
 * Author: stefan
 *
 * Created on August 11, 2014, 4:15 PM
 */

#pragma once

#include <cassert>
#include "../../datastructures/Point.h"

namespace hypro
{
namespace polytope
{

    template<typename Number>
    class Cone 
    {
        typedef std::vector<Point<Number> > vectors;
        private:
            vectors mVectors;
            
        public:
            Cone() :
            mVectors()
            {}
            
            ~Cone()
            {
                mVectors.clear();
            }
            
            Cone(const Cone& orig)
            {
                mVectors.clear();
                mVectors = orig.get();
            }
            
            Cone(unsigned dimension) :
            mVectors(dimension)
            {
                assert(mVectors.max_size() == dimension);
            }
            
            /*
             * Getters & setters
             */
            
            const vectors& get()
            {
                return mVectors;
            }
            
            const Point<Number>& get(unsigned index)
            {
                return mVectors.at(index);
            }
            
            const Point<Number>& get(typename vectors::const_iterator pos)
            {
                return *pos;
            }
            
            typename vectors::const_iterator begin()
            {
                return mVectors.begin();
            }
            
            typename vectors::const_iterator end()
            {
                return mVectors.end();
            }
            
            void add(const Point<Number>& vector)
            {
                assert(mVectors.size() < mVectors.max_size());
                mVectors.push_back(vector);
            }
            
            bool contains(const Point<Number>& vector)
            {
                return false;
            }
            
    };
    
    template<typename Number>
    struct Fan 
    {

    };
    
}
}

