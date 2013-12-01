/** 
 * @file   point.h
 * Created on Mar 12, 2011
 * Last modified Septemper 10, 2013
 * 
 * @author Stefan Schupp
 * @author Sebastian Junges
 * 
 * @since 2011-03-12
 * @version 2013-11-25
 */
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <assert.h>


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
    template<class numbertype>
    class Point 
    {
    	typedef std::vector<FLOAT_T<numbertype> > vector_t;
    	    	
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
            Point(const unsigned dim = 2, const FLOAT_T<numbertype>& initialValue = FLOAT_T<numbertype>()) 
            {
                mCoordinates.assign(dim, initialValue);
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
            Point(const Point<numbertype>& p) 
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
            FLOAT_T<numbertype> coordinate(unsigned dim) const 
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
            void setCoordinate(unsigned dim, FLOAT_T<numbertype> value) 
            {
                mCoordinates[dim] = value;
            }
            
            /**
             * Set dimension coordinates, beginning at offset.
             * @param coordinates
             * @param dimension the dimension of the setted point.
             * @param offset first coordinate that is set.
             */
            void setCoordinates(FLOAT_T<numbertype> coordinates[], unsigned dimension = 2, unsigned offset = 0)
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
            bool move(const Point<numbertype>& p) 
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
            void nextPointOnGrid(const Point<numbertype>& bounds) 
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
    	
            FLOAT_T<numbertype> getGaussianProbability(Point<numbertype> & mean) const{
                return 0;
            }

            FLOAT_T<numbertype> getDistanceDependentProbabiltity(Point<numbertype> & mean, unsigned intlength, FLOAT_T<numbertype> rate) const
            {
                FLOAT_T<numbertype> dist;
                for (unsigned i = 0; i < dimension(); i++) {
                    dist += (mCoordinates[i] - mean[i]).pow(FLOAT_T<numbertype>(2));
                }
                dist /= rate; //TODO: use proper rounding?
                if (dist < 1) return 1;
                return (((FLOAT_T<numbertype>) intlength * (FLOAT_T<numbertype>) dimension()*(FLOAT_T<numbertype>) dimension() / dist));
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
            FLOAT_T<numbertype> sum() const
            {
                FLOAT_T<numbertype> sum = 0;
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
            std::vector<Point<numbertype> > getAllNeighborsForAFixedDimension(int fixedDim) const
            {
                std::vector<Point<numbertype> > neighbors;
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
                    Point<numbertype> neighbor = Point<numbertype>(coordinates);
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
            std::vector<Point<numbertype> > getAllNeighbours(bool pointself=false) const
            {
                std::vector<Point<numbertype> > neighbors = getAllNeighborsForAFixedDimension(0);
                unsigned nrneighbors = neighbors.size();
                //TODO comment!
                for (unsigned i = 0; i < nrneighbors; i++) 
                {
                    Point<numbertype> neighborpredecessor = Point(neighbors[i]).getPredecessorInDimension(0);
                    neighbors.push_back(neighborpredecessor);
                }

                Point<numbertype> pointPredecessor = getPredecessorInDimension(0);
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
            static Point<numbertype> coordinateMax(const Point<numbertype> & p1, const Point<numbertype> & p2) 
            {
                Point<numbertype> p = Point<numbertype>(p1.dimension());
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
            void IncrementInAllDim(FLOAT_T<numbertype> val = 1) 
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
                Point<numbertype> pred = Point(*this);
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
            bool isInBoundary(const Point<numbertype>& boundary) const 
            {
                for (unsigned i = 0; i < dimension(); i++) 
                {
                    if (mCoordinates[i] < 0 || mCoordinates[i] > boundary[i]) return false;
                }
                return true;
            }

            static Point moveRandomInBoundary(const Point<numbertype>& boundary)
            {
                Point q = Point(dimension());
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
            bool compareReducedDimension(const Point<numbertype>& p2, unsigned nrOfDimensions) const 
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

            bool haveEqualCoordinate(const Point<numbertype>& p2) const 
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
            friend bool operator<(const Point<numbertype>& p1, const Point<numbertype>& p2)
            {
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
            friend bool operator>(const Point<numbertype> & p1, const Point<numbertype> & p2)
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
            friend bool operator==(const Point<numbertype> & p1, const Point<numbertype> & p2)
            {
                if(p1.dimension() != p2.dimension()) return false;
                for (unsigned i = 0; i < p1.mCoordinates.size(); i++) 
                {
                    if (p1.mCoordinates.at(i) != p2.mCoordinates.at(i)) return false;
                }
                return true;
            }

            friend bool operator!=(const Point<numbertype> & p1, const Point<numbertype> & p2)
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
            FLOAT_T<numbertype>& operator[] (unsigned i)
            {
                assert(i <= dimension());
                return mCoordinates.at(i);
            }

            /**
             *
             * @param i
             * @return
             */
            const FLOAT_T<numbertype>& operator[] (unsigned i) const 
            {
                return mCoordinates.at(i);
            }

            /**
             *
             * @param ostr
             * @param p
             * @return
             */
            friend std::ostream & operator<< (std::ostream& ostr, const Point<numbertype>& p)
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