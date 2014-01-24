/** 
 * The point class is the basis for all implementation. It consists of a vector
 * of coordinates which forms a point in a n-dimensional space.
 * @file   Point.h
 * 
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @author Sebastian Junges
 * @author Benedikt Seidl
 * 
 * @since	2011-03-12
 * @version 2014-01-17
 */
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <assert.h>
#include "carl/numbers/FLOAT_T.h"
#include "../config.h"

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
    class Point 
    {
		public:
		typedef std::vector<carl::FLOAT_T<NumberType> > vector_t;
		
		protected:
			vector_t mCoordinates;
		
        public:
        
            
            static const int POINT_RAND_MAX = 100;
            
            /**
             * Constructors & Destructor
             */
		
            /**
             * Constructs a point with the passed dimension and sets the coordinates to the initial value.
             * @param dim
             * @param initialValue
             */
            Point(const carl::FLOAT_T<NumberType>& initialValue = carl::FLOAT_T<NumberType>(), const unsigned dim = 1)
            {
                mCoordinates.assign(dim, initialValue);
            }
		
			Point(const NumberType& val)
			{
				mCoordinates.assign(1, carl::FLOAT_T<NumberType>(val));
			}

            /**
             * Constructs a point with the passed coordinates
             * @param coordinates
             */
            Point(const vector_t& coordinates) 
            {
                mCoordinates.assign(coordinates.begin(), coordinates.end());
            }

            /**
             * Copy constructor
             * @param p
             */
            Point(const Point<NumberType>& p) 
            {
                mCoordinates.assign(p.mCoordinates.begin(), p.mCoordinates.end());
            }

            ~Point() 
            {
                mCoordinates.clear();
            }
            
            /**
             * Getter & Setter
             */
            
            /**
             * Returns the value of mCoordinates[dim].
             * @param  dim the dimension we want to get the value from.
             * @return 
             */
            carl::FLOAT_T<NumberType> coordinate(unsigned dim) const 
            {
                assert(dim <= mCoordinates.size());
                return mCoordinates.at(dim);
            }

            vector_t coordinates() const 
            {
                return mCoordinates;
            }
            
            /**
             * Set a specific coordinate
             * @param dim    the dimension that is changed
             * @param value  the new value
             */
            void setCoordinate(unsigned dim, carl::FLOAT_T<NumberType> value) 
            {
                mCoordinates[dim] = value;
            }
            
            /**
             * Set dimension coordinates, beginning at offset.
             * @param coordinates
             * @param dimension the dimension of the setted point.
             * @param offset first coordinate that is set.
             */
            void setCoordinates(carl::FLOAT_T<NumberType> coordinates[], unsigned dimension = 2, unsigned offset = 0)
            {
                mCoordinates.reserve(dimension + offset);
                for (unsigned i = 0; i < dimension; i++)
                {
                    mCoordinates[i + offset] = coordinates[i];
                }
            }
            
            /**
             * 
             * @param coordinates
             * @param offset
             */
            void insertCoordinates(vector_t& coordinates, unsigned offset = 0)
            {
                typename vector_t::iterator it = mCoordinates.begin();
                mCoordinates.reserve(coordinates.size());
                while (offset > 0)
                {
                    it++;
                    offset--;
                }
                mCoordinates.insert(it, coordinates.begin(), coordinates.end());
            }
            
            /**
             *
             * @return iterator to begin of mCoordinates
             */
            typename vector_t::iterator getCoordinatesIteratorBegin() const
            {
                return mCoordinates.begin();
            }

            /**
             *
             * @return iterator to end of mCoordinates
             */
            typename vector_t::iterator getCoordinatesIteratorEnd() const
            {
                return mCoordinates.end();
            }

            /**
             * 
             * @return The size of mCoordinates.
             */
            unsigned dimension() const 
            {
                return mCoordinates.size();
            }

            /**
             *  Resizing the coordinates vector.
             * @param dim the new dimension
             */
            void setDimension(unsigned dim) 
            {
                mCoordinates.resize(dim);
            }

            /**
             * Functions
             */
            
            /**
             * Method to move the point
             * @param p Point with coordinates describing the move.
             * @return true, if the result has a negative coordinate.
             */
            bool move(const Point<NumberType>& p) 
            {
                bool negative = false;
                for (unsigned i = 0; i < p.dimension(); i++) 
                {
                    mCoordinates[i] += p[i];
                    if (mCoordinates[i] < 0) negative = true;
                }
                return negative;
            }

            /**
	     * @brief gives the next point according to some (hardcoded) ordering.
	     * @param bounds The grid lies between the origin and this point.
	     *
	     */
            void nextPointOnGrid(const Point<NumberType>& bounds) 
            {
                for(unsigned i=dimension(); i>0.; i--) 
                {
                    if (mCoordinates[i-1] < bounds[i-1]) 
                    {
                        mCoordinates[i-1]++;
                        return;
                    }
                    else 
                    {
                        mCoordinates[i-1] = 0; //TODO: sure to set it to zero instead of setting it to bounds[i-1] ?
                    }
                }
            }
    	
            carl::FLOAT_T<NumberType> getGaussianProbability(Point<NumberType> & mean) const{
                return 0;
            }

            carl::FLOAT_T<NumberType> getDistanceDependentProbabiltity(Point<NumberType> & mean, unsigned intlength, carl::FLOAT_T<NumberType> rate) const
            {
                carl::FLOAT_T<NumberType> dist;
                for (unsigned i = 0; i < dimension(); i++) {
                    dist += (mCoordinates[i] - mean[i]).pow(carl::FLOAT_T<NumberType>(2));
                }
                dist /= rate; //TODO: use proper rounding?
                if (dist < 1) return 1;
                return (((carl::FLOAT_T<NumberType>) intlength * (carl::FLOAT_T<NumberType>) dimension()*(carl::FLOAT_T<NumberType>) dimension() / dist));
            }
        
            /**
            * @brief random move in one direction.
            */
            void moveRandom()
            {
                unsigned dim = dimension();
                unsigned value = rand();
                unsigned dir = value%dim;
                bool neg = (rand() & 1);
                if (neg) mCoordinates[dir]--;
                else mCoordinates[dir]++;
            }

            /**
             * 
             * @return the sum of all coordinates
             */
            carl::FLOAT_T<NumberType> sum() const
            {
                carl::FLOAT_T<NumberType> sum = 0;
                for (unsigned i = 0; i < dimension(); i++)
                {
                    sum += mCoordinates.at(i);
                }
                return sum;
            }

            /**
             * @brief: function to calculate points in the neighborhood, with one fixed dimension.
             * @return std::vector with all points in the neighborhood, with a fixed dimension, and except the point itself.
             */
            std::vector<Point<NumberType> > getAllNeighborsForAFixedDimension(int fixedDim) const
            {
                std::vector<Point<NumberType> > neighbors;
                unsigned dim = dimension();

                // TODO comment
                int nrofNeighbors = (pow(2, (dim - 1)) - 1);
                neighbors.reserve(nrofNeighbors);

                vector_t coordinates;
                coordinates.resize(dim);

                for (int neighborNr = 1; neighborNr <= nrofNeighbors; neighborNr++) {
                    //calculate the next neighbor we going to check
                    for (int k = dim - 1; k >= 0; k--) 
                    {
                        if (k > fixedDim) 
                        {
                            coordinates[k] = mCoordinates.at(k) - ((neighborNr >> (dim - k - 1)) & 1);
                        } else if (k == fixedDim) 
                        {
                            coordinates[k] = mCoordinates.at(k);
                        } else 
                        { // k < fixed
                            coordinates[k] = mCoordinates.at(k) - ((neighborNr >> (dim - k - 1 - 1)) & 1);
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
            std::vector<Point<NumberType> > getAllNeighbours(bool pointself=false) const
            {
                std::vector<Point<NumberType> > neighbors = getAllNeighborsForAFixedDimension(0);
                unsigned nrneighbors = neighbors.size();
                //TODO comment!
                for (unsigned i = 0; i < nrneighbors; i++) 
                {
                    Point<NumberType> neighborpredecessor = Point(neighbors[i]).getPredecessorInDimension(0);
                    neighbors.push_back(neighborpredecessor);
                }

                Point<NumberType> pointPredecessor = getPredecessorInDimension(0);
                neighbors.push_back(pointPredecessor);

                if (pointself) 
                {
                    neighbors.push_back(*this);
                }

                return neighbors;
            }

            /**
             * 
             * @param p1 One point
             * @param p2 Other point
             * @return A point with the coordinate-wise maximum of p1 and p2.
             */
            static Point<NumberType> coordinateMax(const Point<NumberType> & p1, const Point<NumberType> & p2) 
            {
                Point<NumberType> p = Point<NumberType>(p1.dimension());
                for (unsigned k = 0; k < p.dimension(); k++) {
                    (p1[k] > p2[k]) ? p[k] = p1[k] : p[k] = p2[k];
                }
                return p;
            }

            /**
             * Change the coordinates of the point. Moving the point one step in a given dimension.
             * @param d Dimension in which the coordinate is increased.
             */
            void IncrementInFixedDim(unsigned d) 
            {
                ++(mCoordinates.at(d));
            }

            /**
             * 
             * @param val The value to be added to each coordinate
             */
            void IncrementInAllDim(carl::FLOAT_T<NumberType> val = 1) 
            {
                for (unsigned i = 0; i < dimension(); i++) 
                {
                    mCoordinates[i] += val;
                }
            }

            /**
             * Change the point's coordinates. Moving the point one step in a given dimension.
             * @param d Dimension in which the coordinate is decreased.
             */
            void DecrementInFixedDim(unsigned d) 
            {
                --(mCoordinates.at(d));
            }

            /**
             *
             * @param d
             * @return The point with coordinates [x(1), .., x(d-1), x(d)-1, x(d+1), ..., x(n) ]
             */
            Point& getPredecessorInDimension(unsigned d) const 
            {
                Point<NumberType> pred = Point(*this);
                pred.DecrementInFixedDim(d);
                return pred;
            }

            static Point Random(const Point& boundary)
            {
                Point p = Point(boundary.dimension());
                for (unsigned d = 0; d < boundary.dimension(); d++) 
                {
                    p[d].from_double(boundary[d] * (rand() / (RAND_MAX + 1.0)) + 0.5);
                }
                return p;
            }

            /**
             * @brief Check if in range.
             * @param boundary Point with coordinates that may not be exceeded in positive direction.
             * @return true, if every coordinate is within boundary[i] and 0. 
             */
            bool isInBoundary(const Point<NumberType>& boundary) const 
            {
                for (unsigned i = 0; i < dimension(); i++) 
                {
                    if (mCoordinates[i] < 0 || mCoordinates[i] > boundary[i]) return false;
                }
                return true;
            }

            static Point moveRandomInBoundary(const Point<NumberType>& boundary)
            {
                Point q = Point(boundary.dimension());
                do 
                {
//                    q = Point(*this);
                    q.moveRandom();
                }while (!q.isInBoundary(boundary));
                return q;
            }

            /**
             * Operators & Comparison functions
             */
            
            /**
             *
             * @param p2 the point to be compared with.
             * @param nrOfDimensions compares only the first nrOfDimensions coordinates
             * @return true, if the first nrOfDimensions coordinates are equal.
             */
            bool compareReducedDimension(const Point<NumberType>& p2, unsigned nrOfDimensions) const 
            {
                for (unsigned d = 0; d < nrOfDimensions; d++) {
                    if (mCoordinates[d] != p2[d]) return false;
                }
                return true;
            }
            
            static std::vector<unsigned> getStaticDimensionOrder(unsigned dimension) 
            {
                std::vector<unsigned> dimOrder;
                dimOrder.reserve(dimension);
                for (unsigned d=0; d<dimension; d++) {
                    dimOrder.push_back(d);
                }
                return dimOrder;
            }

            bool haveEqualCoordinate(const Point<NumberType>& p2) const 
            {
                if( dimension() == p2.dimension() )
                {
                    for (unsigned d = 0; d < dimension(); d++) 
                    {
                        if ( mCoordinates.at(d) == p2.mCoordinates.at(d) ) return true;
                    }
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
            friend bool operator<(const Point<NumberType>& p1, const Point<NumberType>& p2)
            {
				std::cout << "Dimension1: " << p1.dimension() << ", Dimension2: " << p2.dimension() << std::endl;
                assert(p1.dimension() == p2.dimension());
                unsigned dim = p2.dimension();
                for (unsigned i = 0; i < dim; i++) 
                {
                    if ( p1.mCoordinates.at(Point::getStaticDimensionOrder(dim)[i]) != p2.mCoordinates.at(Point::getStaticDimensionOrder(dim)[i]) ) 
                    {
                        return ( p1.mCoordinates.at(Point::getStaticDimensionOrder(dim)[i]) < p2.mCoordinates.at(Point::getStaticDimensionOrder(dim)[i]) );
                    }
                }
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
            friend bool operator>(const Point<NumberType> & p1, const Point<NumberType> & p2)
            {
                assert(p1.dimension() == p2.dimension());
                unsigned dim = p2.mCoordinates.size();
                for (unsigned i = 0; i < dim; i++) 
                {
                    if ( p1.mCoordinates.at(Point::getStaticDimensionOrder(dim)[i]) != p2.mCoordinates.at(Point::getStaticDimensionOrder(dim)[i]) ) 
                    {
                        return ( p1.mCoordinates.at(Point::getStaticDimensionOrder(dim)[i]) > p2.mCoordinates.at(Point::getStaticDimensionOrder(dim)[i]) );
                    }
                }
                return false;
            }

            /**
             *
             * @param p1
             * @param p2
             * @return true, if they are equal.
             */
            friend bool operator==(const Point<NumberType> & p1, const Point<NumberType> & p2)
            {
                if(p1.dimension() != p2.dimension()) return false;
                for (unsigned i = 0; i < p1.mCoordinates.size(); i++) 
                {
                    if (p1.mCoordinates.at(i) != p2.mCoordinates.at(i)) return false;
                }
                return true;
            }

            friend bool operator!=(const Point<NumberType> & p1, const Point<NumberType> & p2)
            {
                if(p1.dimension() != p2.dimension()) return true;
                for (unsigned i = 0; i < p1.mCoordinates.size(); i++) 
                {
                    if (p1[i] != p2[i]) return true;
                }
                return false;
            }

            /**
             *
             * @param i
             * @return
             */
            carl::FLOAT_T<NumberType>& operator[] (unsigned i)
            {
                assert(i <= dimension());
                return mCoordinates.at(i);
            }

            /**
             *
             * @param i
             * @return
             */
            const carl::FLOAT_T<NumberType>& operator[] (unsigned i) const 
            {
                return mCoordinates.at(i);
            }

            /**
             *
             * @param ostr
             * @param p
             * @return
             */
            friend std::ostream & operator<< (std::ostream& ostr, const Point<NumberType>& p)
            {
                ostr << p.toString();
                return ostr;
            }
            
            /**
            * @param parentheses Decides if the output is surrounded by parentheses. 
            * @return The coordinates of the point.
            */
            std::string toString(const bool parentheses = true) const
            {
                unsigned dimension = mCoordinates.size();
                std::string result;

                if (parentheses) {
                    result += "(";
                }

                for (unsigned i = 0; i < dimension - 1; i++) {
                    result += mCoordinates.at(i).toString() + " ";
                }
                result += mCoordinates.at(dimension - 1).toString();

                if (parentheses) {
                    result += ")";
                }
                return result;
            }
    };
}