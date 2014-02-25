/** 
 * @file   point.h
 * Created on Mar 12, 2011
 * Last modified June 23, 2011
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
#include "boost/lexical_cast.hpp"
#include "settings.h"


namespace reachLin {
    
    /**
     * @class Point
     */
    class Point;
    typedef std::vector<Point> pVec;
    typedef std::vector<Point>::iterator pVecIt;

    /*
     *  Class to store points in a MAXIMAL_DIMENSION space.
     */
    class Point {
    public:
        std::string toString(bool parentheses = true) const;
        std::vector<Point> getAllNeighborsForAFixedDimension(int fixedDim) const;
        std::vector<Point> getAllNeighbours(bool pointself=false) const;
        double getGaussianProbability(Point mean) const;
        double getDistanceDependentProbabiltity(Point mean, unsigned intlength, float rate) const;        
        void setCoordinates(int coordinates[], unsigned dimension = MAXIMAL_DIMENSION, unsigned offset = 0);
        unsigned sum() const;
        void insertCoordinates(std::vector<int> coordinates, unsigned offset = 0);
        static Point coordinateMax(const Point& p1, const Point p2);
        void nextPointOnGrid(const Point& bounds);
        void moveRandom();



        Point(unsigned dim = MAXIMAL_DIMENSION, unsigned value = 0) {
            mCoordinates.reserve(dim);
            for (unsigned d = 0; d < dim; d++) {
                mCoordinates.push_back(value);
            }
        }

        /**
         * Constructs a point with the passed coordinates
         * @param coordinates
         * @return
         */
        Point(std::vector<int> coordinates) {
            mCoordinates.clear();
            mCoordinates.insert(mCoordinates.begin(), coordinates.begin(), coordinates.end());
        }

        /**
         * Copy constructor
         * @param p
         * @return
         */
        Point(const Point& p) {
            mCoordinates.assign(p.mCoordinates.begin(), p.mCoordinates.end());
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
        void IncrementInAllDim(unsigned val = 1) {
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
        Point getPredecessorInDimension(unsigned d) const {
            Point pred = Point(*this);
            pred.DecrementInFixedDim(d);
            return pred;
        }

        static Point Random(const Point& boundary) {
            Point p = Point(boundary.getDimension());
            for (unsigned d = 0; d < boundary.getDimension(); d++) {
                p[d] = unsigned(boundary[d]*(rand() / (RAND_MAX + 1.0)) + 0.5);
            }
            return p;
        }
        
        /**
         *
         * @return iterator to begin of mCoordinates
         */
        std::vector<int>::iterator getCoordinatesIteratorBegin() {
            return mCoordinates.begin();
        }

        /**
         *
         * @return iterator to end of mCoordinates
         */
        std::vector<int>::iterator getCoordinatesIteratorEnd() {
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
        bool isInBoundary(const Point& boundary) const {
            for (unsigned i = 0; i < getDimension(); i++) {
                if (mCoordinates[i] < 0 || mCoordinates[i] > boundary[i]) return false;
            }
            return true;
        }

        Point moveRandomInBoundary(const Point& boundary) const {
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
        int getCoordinate(unsigned dim) const {
            return mCoordinates[dim];
        }

        std::vector<int> getCoordinates() const {
            return mCoordinates;
        }

        /**
         * Method to move the point
         * @param p Point with coordinates describing the move.
         * @return true, if the result has a negative coordinate.
         */
        bool move(const Point& p) {
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
        void setCoordinate(unsigned dim, int value) {
            mCoordinates[dim] = value;
        }

        /**
         *
         * @param p2 the point to be compared with.
         * @param nrOfDimensions compares only the first nrOfDimensions coordinates
         * @return true, if the first nrOfDimensions coordinates are equal.
         */
        bool CompareReducedDimension(const Point& p2, unsigned nrOfDimensions) const {
            for (unsigned d = 0; d < nrOfDimensions; d++) {
                if (mCoordinates[d] != p2[d]) return false;
            }
            return true;
        }

        bool haveEqualCoordinate(const Point& p2) const {
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
        friend bool operator<(const Point& p1, const Point& p2) {
            unsigned dim = p2.mCoordinates.size();
            for (unsigned i = 0; i < dim; i++) {
                if (p1.mCoordinates[Settings::getStaticDimensionOrder(dim)[i]] != p2.mCoordinates[Settings::getStaticDimensionOrder(dim)[i]]) {
                    return (p1.mCoordinates[Settings::getStaticDimensionOrder(dim)[i]] < p2.mCoordinates[Settings::getStaticDimensionOrder(dim)[i]]);
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
        friend bool operator==(const Point& p1, const Point& p2) {
            for (unsigned i = 0; i < p1.mCoordinates.size(); i++) {
                if (p1.mCoordinates[i] != p2.mCoordinates[i]) return false;
            }
            //Points are equal.
            return true;
        }

        friend bool operator!=(const Point& p1, const Point& p2) {
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
        int& operator[] (unsigned i) {
            //TODO if (i > mCoordinates.size()) std::error();
            return mCoordinates[i];
        }

        /**
         *
         * @param i
         * @return
         */
        const int& operator[] (unsigned i) const {
            return mCoordinates[i];
        }

        /**
         *
         * @param ostr
         * @param p
         * @return
         */
        friend std::ostream & operator<<(std::ostream& ostr, const Point& p) {
            ostr << p.toString();
            return ostr;
        }

    protected:
        std::vector<int> mCoordinates;
    };


}
#endif /* POINT_H_ */
