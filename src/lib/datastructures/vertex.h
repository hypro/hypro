/** 
 * @file   vertex.h
 * Created on Mar 24, 2011
 * Last modified June 23, 2011
 * 
 * @author Sebastian Junges
 */

#ifndef VERTEX_H_
#define VERTEX_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <fstream>
//#include "boost/lexical_cast.hpp"
//#include "config.h"
#include "point.h"

namespace hypro {

/**
 *
 */
/*
    class Vertex;
    typedef std::vector<Vertex> vVec;
    typedef std::vector<Vertex>::iterator vVecIt; 
    typedef std::list<Vertex> vList;
    typedef std::list<Vertex>::iterator vListIt;
    typedef std::set<Vertex> vSet;
    typedef std::set<Vertex>::iterator vSetIt;*/ 
    
	/**
	 * @class Vertex
	 */
	template<class NumberType>
	class Vertex : public Point<NumberType> {
	public:
		/**
		 *
		 * @param dimension
		 * @param color
		 * @return
		 */
		Vertex(unsigned dimension = Point<NumberType>::DEFAULT_DIMENSION, bool color = false) : Point<NumberType>(dimension) {
			mColor = color;
		}
	
		/**
		 *
		 * @param coordinates
		 * @param color
		 * @return
		 */
		Vertex(std::vector<NumberType> coordinates, bool color) : Point<NumberType>(coordinates) {
			mColor = color;
		}
	
		/**
		 *
		 * @param p
		 * @param color
		 * @return
		 */
		Vertex(const Point<NumberType> & p, bool color) : Point<NumberType>(p) {
			mColor = color;
		}
	
		/**
		 *
		 * @return the color of the vertex.
		 */
		bool getColor() const{
			return mColor;
		}
	
		/**
		 *
		 * @param c the new value for this vertex' color.
		 */
		void setColor(bool c) {
			mColor = c;
		}
	
		/**
		 * Inverts the color.
		 */
		void invertColor() {
			mColor = !mColor;
		}
	
        /*
         * TODO
         * std::string toString(bool parentheses = true) const {
            if (parentheses) return Point<NumberType>::toString(true) + " " + 
                    "[" + boost::lexical_cast<std::string>(mColor) +"]";
            else return Point::toString(false) + " " + 
                    boost::lexical_cast<std::string>(mColor);
        }*/


        friend std::ostream& operator<<(std::ostream& ostr, const Vertex& v) {
            ostr << v.toString();
            return ostr;
        }
        
        friend std::istream& operator>>(std::istream& istr, Vertex& v) {
            for (unsigned d = 0; d < v.getDimension(); d++) {
                    istr >> v.mCoordinates[d];
                }
                istr >> v.mColor; 
                return istr;
        }
	
	private:
		bool mColor;
	};

}
#endif

