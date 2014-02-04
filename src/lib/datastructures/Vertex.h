/** 
 * A vertex is a point with a color assigned. The color determines is needed by
 * some representations e.g. to determine if the vertex is part of the state set.
 * @file Vertex.h
 * 
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @author Sebastian Junges
 * 
 * @since	2011-03-24
 * @version 2014-01-17
 */

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <list>

#include "Point.h"

namespace hypro {
	template<typename NumberType>
    class Vertex;
	template<typename NumberType>
    using vVec = typename std::vector<Vertex<NumberType>>;
    template<typename NumberType>
	using vVecIt = typename std::vector<Vertex<NumberType>>::iterator;
    template<typename NumberType>
	using vList = typename std::list<Vertex<NumberType>>;
    template<typename NumberType>
	using vListIt = typename std::list<Vertex<NumberType>>::iterator;
    template<typename NumberType>
	using vSet = typename std::set<Vertex<NumberType>>;
    template<typename NumberType>
	using vSetIt = typename std::set<Vertex<NumberType>>::iterator;
    
    template<class NumberType>
    class Vertex : public Point<NumberType> 
    {
        private:
            bool mColor;

        public:
            /**
             *
             * @param dimension
             * @param color
             * @return
             */
			Vertex(bool color = false) : Point<NumberType>()
            {
                mColor = color;
            }

            /**
             *
             * @param coordinates
             * @param color
             * @return
             */
			Vertex(const typename Point<NumberType>::vector_t& coordinates, bool color = false) : Point<NumberType>(coordinates)
            {
                mColor = color;
            }

            /**
             *
             * @param p
             * @param color
             * @return
             */
            Vertex(const Point<NumberType>& p, bool color = false) : Point<NumberType>(p)
            {
                mColor = color;
            }

            /**
             *
             * @return the color of the vertex.
             */
            bool color() const
            {
                return mColor;
            }

            /**
             *
             * @param c the new value for this vertex' color.
             */
            void setColor(bool c = true) 
            {
                mColor = c;
            }

            /**
             * Inverts the color.
             */
            void invertColor() 
            {
                mColor = !mColor;
            }

            friend std::ostream& operator<<(std::ostream& ostr, const Vertex& v) 
            {
                ostr << v.toString();
                return ostr;
            }

            friend std::istream& operator>>(std::istream& istr, Vertex& v) 
            {
                for (unsigned d = 0; d < v.dimension(); d++) {
                    istr >> v.mCoordinates.at(d);
                }
                istr >> v.mColor; 
                return istr;
            }

            std::string toString(bool parentheses = true) const 
            {
                if (parentheses) 
                    return Point<NumberType>::toString(true) + " " + "[" + mColor +"]";
                else 
                    return Point<NumberType>::toString(false) + " " + mColor;
            }
    };
}