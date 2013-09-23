/** 
 * @file   point.h
 * Created on Mar 12, 2011
 * Last modified Septemper 10, 2013
 * 
 * @author Sebastian Junges
 */
#ifndef POINT_H_
#define POINT_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <cmath>
#include <cstdlib>
//#include "boost/lexical_cast.hpp"


namespace hypro {
    
    /**
     * @class Point
     */
	/*
    class Point;
    typedef std::vector<Point> pVec;
    typedef std::vector<Point>::iterator pVecIt;
    */

    /*
     *  Class to store points in a MAXIMAL_DIMENSION space.
     */
    template<class NumberType>
    class Point {
    public:
    	static const unsigned DEFAULT_DIMENSION = 2;
    	static const int POINT_RAND_MAX = 100;
    	
        std::string toString(bool parentheses = true) const;
        std::vector<Point> getAllNeighborsForAFixedDimension(int fixedDim) const;
        std::vector<Point> getAllNeighbours(bool pointself=false) const;
        NumberType getGaussianProbability(Point<NumberType> & mean) const;
        NumberType getDistanceDependentProbabiltity(Point<NumberType> & mean, unsigned intlength, float rate) const;        
        void setCoordinates(NumberType coordinates[], unsigned dimension = DEFAULT_DIMENSION, unsigned offset = 0);
        NumberType sum() const;
        void insertCoordinates(std::vector<NumberType> coordinates, unsigned offset = 0);
        static Point<NumberType> coordinateMax(const Point<NumberType> & p1, const Point<NumberType> & p2);
        void nextPointOnGrid(const Point<NumberType> & bounds);
        void moveRandom();



        Point(unsigned dim = Point<NumberType>::DEFAULT_DIMENSION) {
            mCoordinates.reserve(dim);
        }
        
        Point(unsigned dim, NumberType & initialValue)
        {
        	mCoordinates.reserve(dim);
            for (unsigned d = 0; d < dim; d++) {
                mCoordinates.push_back(initialValue);
            }
        }

        /**
         * Constructs a point with the passed coordinates
         * @param coordinates
         * @return
         */
        Point(std::vector<NumberType> & coordinates) {
            mCoordinates.clear();
            mCoordinates.insert(mCoordinates.begin(), coordinates.begin(), coordinates.end());
        }

        /**
         * Copy constructor
         * @param p
         * @return
         */
        Point(const Point<NumberType> & p) {
            mCoordinates.assign(p.mCoordinates.begin(), p.mCoordinates.end());
        }
        
        ~Point()
        {
        	mCoordinates.clear();
        }

        /**
         * Change the coordinates of the point. Moving the point one step in a given dimension.
         * @param d Dimension in which the coordinate is increased.
         */
        void IncrementInFixedDim(unsigned d) {
            mCoordinates[d]++;
        }

        /**
         * 
         * @param val The value to be added to each coordinate
         */
        void IncrementInAllDim(NumberType val = 1) {
            for (unsigned i = 0; i < getDimension(); i++) {
                mCoordinates[i] += val;
            }
        }

        /**
         * Change the point's coordinates. Moving the point one step in a given dimension.
         * @param d Dimension in which the coordinate is decreased.
         */
        void DecrementInFixedDim(unsigned d) {
            mCoordinates[d]--;
        }

        /**
         *
         * @param d
         * @return The point with coordinates [x(1), .., x(d-1), x(d)-1, x(d+1), ..., x(n) ]
         */
        Point & getPredecessorInDimension(unsigned d) const {
            Point<NumberType> pred = Point(*this);
            pred.DecrementInFixedDim(d);
            return pred;
        }

        // TODO !!! rand() doesn't work here
        static Point & Random(const Point& boundary) {
            Point p = Point(boundary.getDimension());
            for (unsigned d = 0; d < boundary.getDimension(); d++) {
                p[d].from_double(boundary[d] * (rand() / (RAND_MAX + 1.0)) + 0.5);
            }
            return p;
        }
        
        /**
         *
         * @return iterator to begin of mCoordinates
         */
        typename std::vector<NumberType>::iterator getCoordinatesIteratorBegin() {
            return mCoordinates.begin();
        }

        /**
         *
         * @return iterator to end of mCoordinates
         */
        typename std::vector<NumberType>::iterator getCoordinatesIteratorEnd() {
            return mCoordinates.end();
        }

        /**
         * 
         * @return The size of mCoordinates.
         */
        unsigned getDimension() const {
            return mCoordinates.size();
        }

        /**
         *  Resizing the coordinates vector.
         */
        void setDimension(unsigned dim) {
            mCoordinates.resize(dim);
        }


        /**
         * @brief Check if in range.
         * @param boundary Point with coordinates that may not be exceeded in positive direction.
         * @return true, if every coordinate is within boundary[i] and 0. 
         */
        bool isInBoundary(const Point<NumberType> & boundary) const {
            for (unsigned i = 0; i < getDimension(); i++) {
                if (mCoordinates[i] < 0 || mCoordinates[i] > boundary[i]) return false;
            }
            return true;
        }

        Point moveRandomInBoundary(const Point<NumberType> & boundary) const {
            Point q = Point(getDimension());
            Point orig = Point(getDimension());
            do {
                q = Point(*this);
                q.moveRandom();
            } while (!q.isInBoundary(boundary));
            return q;
        }

        /**
         *
         * @param  dim the dimension we want to get the value from.
         * @return the value of mCoordinates[dim]
         */
        NumberType getCoordinate(unsigned dim) const {
            return mCoordinates[dim];
        }

        std::vector<NumberType> getCoordinates() const {
            return mCoordinates;
        }

        /**
         * Method to move the point
         * @param p Point with coordinates describing the move.
         * @return true, if the result has a negative coordinate.
         */
        bool move(const Point<NumberType> & p) {
            bool negative = false;
            for (unsigned i = 0; i < p.getDimension(); i++) {
                mCoordinates[i] += p[i];
                if (mCoordinates[i] < 0) negative = true;
            }
            return negative;
        }

        /**
         * Set a specific coordinate
         * @param dim    the dimension that is changed
         * @param value  the new value
         */
        void setCoordinate(unsigned dim, NumberType value) {
            mCoordinates[dim] = value;
        }

        /**
         *
         * @param p2 the point to be compared with.
         * @param nrOfDimensions compares only the first nrOfDimensions coordinates
         * @return true, if the first nrOfDimensions coordinates are equal.
         */
        bool CompareReducedDimension(const Point<NumberType> & p2, unsigned nrOfDimensions) const {
            for (unsigned d = 0; d < nrOfDimensions; d++) {
                if (mCoordinates[d] != p2[d]) return false;
            }
            return true;
        }

        bool haveEqualCoordinate(const Point<NumberType> & p2) const {
            for (unsigned d = 0; d < getDimension(); d++) {
                if (mCoordinates[d] == p2[d]) return true;
            }
            return false;
        }

        /**
         * Comparison operator for the map.
         * This is not true for lesser distance to the origin.
         * It simply compares the entries for every dimension
         * As soon as they are different the method returns
         *
         * @param p1
         * @param p2
         * @return
         */
        friend bool operator<(const Point<NumberType> & p1, const Point<NumberType> & p2) {
            unsigned dim = p2.mCoordinates.size();
            for (unsigned i = 0; i < dim; i++) {
                if (p1.mCoordinates[Point::getStaticDimensionOrder(dim)[i]] != p2.mCoordinates[Point::getStaticDimensionOrder(dim)[i]]) {
                    return (p1.mCoordinates[Point::getStaticDimensionOrder(dim)[i]] < p2.mCoordinates[Point::getStaticDimensionOrder(dim)[i]]);
                }
            }
            //Points are equal.
            return false;
        }

        /**
         *
         * @param p1
         * @param p2
         * @return true, if they are equal.
         */
        friend bool operator==(const Point<NumberType> & p1, const Point<NumberType> & p2) {
            for (unsigned i = 0; i < p1.mCoordinates.size(); i++) {
                if (p1.mCoordinates[i] != p2.mCoordinates[i]) return false;
            }
            //Points are equal.
            return true;
        }

        friend bool operator!=(const Point<NumberType> & p1, const Point<NumberType> & p2) {
            for (unsigned i = 0; i < p1.mCoordinates.size(); i++) {
                if (p1[i] != p2[i]) return true;
            }
            return false;
        }

        /**
         *
         * @param i
         * @return
         */
        NumberType & operator[] (unsigned i) {
            //TODO if (i > mCoordinates.size()) std::error();
            return mCoordinates.at(i);
        }

        /**
         *
         * @param i
         * @return
         */
        const NumberType & operator[] (unsigned i) const {
            return mCoordinates.at(i);
        }

        /**
         *
         * @param ostr
         * @param p
         * @return
         */
        friend std::ostream & operator<<(std::ostream& ostr, const Point<NumberType> & p) {
            ostr << p.toString();
            return ostr;
        }
        
        static std::vector<unsigned> getStaticDimensionOrder(unsigned dimension) {
            std::vector<unsigned> dimOrder;
            dimOrder.reserve(dimension);
            for (unsigned d=0; d<dimension; d++) {
                dimOrder.push_back(d);
            }
            return dimOrder;
        }

    protected:
        std::vector<NumberType> mCoordinates;
    };


}
#endif /* POINT_H_ */
