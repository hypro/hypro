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
	template<typename Number>
    class Vertex;
	template<typename Number>
    using vVec = typename std::vector<Vertex<Number>>;
    template<typename Number>
	using vVecIt = typename std::vector<Vertex<Number>>::iterator;
    template<typename Number>
	using vList = typename std::list<Vertex<Number>>;
    template<typename Number>
	using vListIt = typename std::list<Vertex<Number>>::iterator;
    template<typename Number>
	using vSet = typename std::set<Vertex<Number>>;
    template<typename Number>
	using vSetIt = typename std::set<Vertex<Number>>::iterator;
    
    template<class Number>
    class Vertex : public Point<Number> 
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
            Vertex(bool color = false) : Point<Number>()
            {
                mColor = color;
            }

            /**
             *
             * @param coordinates
             * @param color
             * @return
             */
            Vertex(const typename Point<Number>::coordinateMap& coordinates, bool color = false) : Point<Number>(coordinates)
            {
                mColor = color;
            }

            /**
             *
             * @param p
             * @param color
             * @return
             */
            Vertex(const Point<Number>& p, bool color = false) : Point<Number>(p)
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

            /**
             *
             * @param v1
             * @param v2
             * @return true, if they are equal.
             */
            friend bool operator==(const Vertex<Number> & _v1, const Vertex<Number> & _v2)
            {
                if(_v1.dimension() != _v2.dimension()) return false;
                if(_v1.color() != _v2.color()) return false;
                for (auto vertexIt : _v1.mCoordinates)
                {
                    if ( !_v2.hasDimension(vertexIt.first) || vertexIt.second != _v2.mCoordinates.at(vertexIt.first)) return false;
                }
                return true;
            }

            /**
             *
             * @param v1
             * @param v2
             * @return true, if they are not equal.
             */
            friend bool operator!=(const Vertex<Number> & _v1, const Vertex<Number> & _v2)
            {
                return !(_v1 == _v2);
            }

            friend std::ostream& operator<<(std::ostream& ostr, const Vertex& v) 
            {
                ostr << "( ";		
                for (auto pointIt : v.mCoordinates) {
                    ostr << pointIt.second.toString() << "[" << pointIt.first << "] ";
                }		
                ostr << ") [" << v.mColor << "]";
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
    };
}