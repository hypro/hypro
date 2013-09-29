/** 
 * @file   point.h
 * Created on Mar 12, 2011
 * Last modified Septemper 10, 2013
 * 
 * @author Sebastian Junges
 * 
 * NOTICE: All functions are located in this header file because this is a templated class.
 * For more information see http://stackoverflow.com/questions/8752837/undefined-reference-to-template-class-constructor
 * 
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
    	static const int POINT_RAND_MAX = 100;
    	
    	/**
	     * @brief gives the next point according to some (hardcoded) ordering.
	     * @param bounds The grid lies between the origin and this point.
	     *
	     */
    	void nextPointOnGrid(const Point<NumberType> & bounds) {
            for(unsigned i=getDimension(); i>0.; i--) {
                if (mCoordinates[i-1] < bounds[i-1]) {
                    mCoordinates[i-1]++;
                    return;
                }
                else {
                    mCoordinates[i-1] = 0;
                }
            }
        }
    	
    	NumberType getGaussianProbability(Point<NumberType> & mean) const{
        	return 0;
        }
    	
    	NumberType getDistanceDependentProbabiltity(Point<NumberType> & mean, unsigned intlength, float rate) const{
            NumberType dist;
            for (unsigned i = 0; i < getDimension(); i++) {
                dist += (mCoordinates[i] - mean[i]).pow(NumberType(2));
            }
            dist /= rate;
            if (dist < 1) return 1;
            return (((NumberType) intlength * (NumberType) getDimension()*(NumberType) getDimension() / dist));
        }
    	
    	/**
	     * @param parentheses Decides if the output is surrounded by parentheses. 
	     * @return The coordinates of the point.
	     */
	    std::string toString(const bool parentheses = true) const{
            unsigned dimension = mCoordinates.size();
            std::string result;

            if (parentheses) {
                result += "(";
            }

            for (unsigned i = 0; i < dimension - 1; i++) {
                result += mCoordinates[i].toString() + " ";
            }
            result += mCoordinates[dimension - 1].toString();

            if (parentheses) {
                result += ")";
            }
            return result;

        }
        
	    /**
         * @brief random move in one direction.
         */
        void moveRandom(){
            unsigned dim = getDimension();
            unsigned value = rand();
            unsigned dir = value%dim;
            bool neg = (rand() & 1);
            if (neg) mCoordinates[dir]--;
            else mCoordinates[dir]++;
        }
        
        /**
         * Set dimension coordinates, beginning at offset.
         * @param coordinates
         * @param dimension the dimension of the setted point.
         * @param offset first coordinate that is set.
         */
        void setCoordinates(NumberType coordinates[], unsigned dimension = 2, unsigned offset = 0){
            mCoordinates.reserve(dimension + offset);
            for (unsigned i = 0; i < dimension; i++) {
                mCoordinates[i + offset] = coordinates[i];
            }
        }
        
        /**
         * 
         * @return the sum of all coordinates
         */
        NumberType sum() const{
            NumberType sum = 0;
            for (unsigned i = 0; i < getDimension(); i++) {
                sum += mCoordinates[i];
            }
            return sum;
        }
        
        /**
         * 
         * @param coordinates
         * @param offset
         */
        void insertCoordinates(std::vector<NumberType> & coordinates, unsigned offset = 0) {
            typename std::vector<NumberType>::iterator it = mCoordinates.begin();
            mCoordinates.reserve(coordinates.size());
            while (offset > 0) {
                it++;
                offset--;
            }
            mCoordinates.insert(it, coordinates.begin(), coordinates.end());
        }
        
        /**
         * @brief: function to calculate points in the neighborhood, with one fixed dimension.
         * @return std::vector with all points in the neighborhood, with a fixed dimension, and except the point itself.
         */
        std::vector<Point<NumberType> > getAllNeighborsForAFixedDimension(int fixedDim) const {
            std::vector<Point<NumberType> > neighbors;
            unsigned dim = getDimension();

            // TODO comment
            int nrofNeighbors = (pow(2, (dim - 1)) - 1);
            neighbors.reserve(nrofNeighbors);

            std::vector<NumberType> coordinates;
            coordinates.resize(dim);

            for (int neighborNr = 1; neighborNr <= nrofNeighbors; neighborNr++) {
                //calculate the next neighbor we going to check
                for (int k = dim - 1; k >= 0; k--) {
                    if (k > fixedDim) {
                        coordinates[k] = mCoordinates[k] - ((neighborNr >> (dim - k - 1)) & 1);
                    } else if (k == fixedDim) {
                        coordinates[k] = mCoordinates[k];
                    } else { // k < fixed
                        coordinates[k] = mCoordinates[k] - ((neighborNr >> (dim - k - 1 - 1)) & 1);
                    }
                }
                Point<NumberType> neighbor = Point<NumberType>(coordinates);
                neighbors.push_back(neighbor);
            }
            return neighbors;
        }
        
        /**
         *
         * @param fixedDim
         * @return Vector filled with neighbours with coordinate[fixedDim] equal to the points coordinate.
         *  point is not an element of the returned vector.
         */
        std::vector<Point<NumberType> > getAllNeighbours(bool pointself=false) const{
            std::vector<Point<NumberType> > neighbors = getAllNeighborsForAFixedDimension(0);
            unsigned nrneighbors = neighbors.size();
            //TODO comment!
            for (unsigned i = 0; i < nrneighbors; i++) {
                Point<NumberType> neighborpredecessor = Point(neighbors[i]).getPredecessorInDimension(0);
                neighbors.push_back(neighborpredecessor);
            }

            Point<NumberType> pointPredecessor = getPredecessorInDimension(0);
            neighbors.push_back(pointPredecessor);
            
            if (pointself) {
                neighbors.push_back(*this);
            }

            return neighbors;
        }
   
        // --------------------------------------------------------------------------------------------
        
        /**
         * 
         * @param p1 One point
         * @param p2 Other point
         * @return A point with the coordinate-wise maximum of p1 and p2.
         */
        static Point<NumberType> coordinateMax(const Point<NumberType> & p1, const Point<NumberType> & p2) {
            Point<NumberType> p = Point<NumberType>(p1.getDimension());
            for (unsigned k = 0; k < p.getDimension(); k++) {
                (p1[k] > p2[k]) ? p[k] = p1[k] : p[k] = p2[k];
            }
            return p;
        }
        
        /**
         * Constructors & Destructor
         */

        /**
         * Constructs a point with the passed dimension.
         * @param dim
         */
        /*Point(unsigned dim = 2) {
            mCoordinates.reserve(dim);
            for(unsigned d = 0; d < dim; d++) {
            	mCoordinates.push_back(NumberType());
            }
        }*/
        
        /**
         * Constructs a point with the passed dimension and sets the coordinates to the initial value.
         * @param dim
         * @param initialValue
         */
        Point(const unsigned dim = 2, const NumberType & initialValue = NumberType()) {
        	mCoordinates.reserve(dim);
            for (unsigned d = 0; d < dim; d++) {
                mCoordinates.push_back(initialValue);
            }
        }

        /**
         * Constructs a point with the passed coordinates
         * @param coordinates
         */
        Point(const std::vector<NumberType> & coordinates) {
            mCoordinates.clear();
            mCoordinates.insert(mCoordinates.begin(), coordinates.begin(), coordinates.end());
        }

        /**
         * Copy constructor
         * @param p
         */
        Point(const Point<NumberType> & p) {
            mCoordinates.assign(p.mCoordinates.begin(), p.mCoordinates.end());
        }
        
        ~Point() {
        	mCoordinates.clear();
        }

        /**
         * Change the coordinates of the point. Moving the point one step in a given dimension.
         * @param d Dimension in which the coordinate is increased.
         */
        void IncrementInFixedDim(unsigned d) {
            ++(mCoordinates.at(d));
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
            --(mCoordinates.at(d));
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
         * @param dim the new dimension
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
         * Comparison operator for the map.
         * This is not true for greater distance to the origin.
         * It simply compares the entries for every dimension
         * As soon as they are different the method returns
         *
         * @param p1
         * @param p2
         * @return
         */
        friend bool operator>(const Point<NumberType> & p1, const Point<NumberType> & p2) {
            unsigned dim = p2.mCoordinates.size();
            for (unsigned i = 0; i < dim; i++) {
                if (p1.mCoordinates[Point::getStaticDimensionOrder(dim)[i]] != p2.mCoordinates[Point::getStaticDimensionOrder(dim)[i]]) {
                    return (p1.mCoordinates[Point::getStaticDimensionOrder(dim)[i]] > p2.mCoordinates[Point::getStaticDimensionOrder(dim)[i]]);
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
        	if(p1.getDimension() != p2.getDimension()) return false;
            for (unsigned i = 0; i < p1.mCoordinates.size(); i++) {
                if (p1.mCoordinates[i] != p2.mCoordinates[i]) return false;
            }
            //Points are equal.
            return true;
        }

        friend bool operator!=(const Point<NumberType> & p1, const Point<NumberType> & p2) {
        	if(p1.getDimension() != p2.getDimension()) return true;
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
        friend std::ostream & operator<< (std::ostream& ostr, const Point<NumberType> & p) {
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
