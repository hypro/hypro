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
#include <unordered_map>
#include <cmath>
#include <assert.h>
#include <carl/numbers/FLOAT_T.h>
#include <carl/core/Variable.h>

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
		//typedef std::vector<carl::FLOAT_T<NumberType> > vector_t;
		typedef std::unordered_map<carl::Variable, carl::FLOAT_T<NumberType> > vector_t;
	private:
		typedef carl::FLOAT_T<NumberType> number;
		
		protected:
			vector_t mCoordinates;
		
        public:
        
            
            static const int POINT_RAND_MAX = 100;
            
            /**
             * Constructors & Destructor
             */
		
			Point() : mCoordinates()
			{}
		
            /**
             * Constructs a point with the passed dimension and sets the coordinates to the initial value.
             * @param dim
             * @param initialValue
             */
			Point(const carl::Variable& var, const number& value = number())
            {
                mCoordinates[var] = value;
            }

            /**
             * Constructs a point with the passed coordinates
             * @param coordinates
             */
            Point(const vector_t& coordinates) 
            {
                mCoordinates.insert(coordinates.begin(), coordinates.end());
            }

            /**
             * Copy constructor
             * @param p
             */
            Point(const Point<NumberType>& p) 
            {
                mCoordinates.insert(p.mCoordinates.begin(), p.mCoordinates.end());
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
			number coordinate(const carl::Variable& var) const
            {
                assert(mCoordinates.count(var) > 0);
                return mCoordinates.at(var);
            }

            vector_t coordinates() const 
            {
                return mCoordinates;
            }
        
			vector_t& rCoordinates()
			{
				return mCoordinates;
			}
		
            /**
             * Set a specific coordinate
             * @param dim    the dimension that is changed
             * @param value  the new value
             */
			void setCoordinate(const carl::Variable& dim, number value)
            {
                mCoordinates[dim] = value;
            }
            
            /**
             * 
             * @param coordinates
             * @param offset
             */
            void insertCoordinates(vector_t& coordinates)
            {
                mCoordinates.insert(coordinates.begin(), coordinates.end());
            }
            
            /**
             *
             * @return iterator to begin of mCoordinates
             */
		typename vector_t::const_iterator getCoordinatesIteratorBegin() const
            {
                return mCoordinates.begin();
            }

            /**
             *
             * @return iterator to end of mCoordinates
             */
		typename vector_t::const_iterator getCoordinatesIteratorEnd() const
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
		
			void removeDimension(const carl::Variable& i)
			{
				mCoordinates.erase(i);
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
                for(auto pointIt = p.getCoordinatesIteratorBegin(); pointIt != p.getCoordinatesIteratorEnd(); ++pointIt)
				{
					if(mCoordinates.count((*pointIt).first) > 0)
					{
						mCoordinates[(*pointIt).first] += (*pointIt).second;
					}
					else
					{
						mCoordinates[(*pointIt).first] = (*pointIt).second;
					}
					if (mCoordinates.at((*pointIt).first) < 0) negative = true;
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
                for(auto pointIt : mCoordinates)
                {
                    if ((*pointIt).second < bounds.coordinate((*pointIt).first))
                    {
                        ++mCoordinates[(*pointIt).first];
                        return;
                    }
                    else 
                    {
                        mCoordinates[(*pointIt).first] = 0; //TODO: sure to set it to zero instead of setting it to bounds[i-1] ?
                    }
                }
            }
    	
            number getGaussianProbability(Point<NumberType> & mean) const{
                return 0;
            }

            number getDistanceDependentProbabiltity(Point<NumberType> & mean, unsigned intlength, number rate) const
            {
                number dist;
                for (auto pointIt : mCoordinates)
				{
                    dist += ( (*pointIt).second - mean.coordinate((*pointIt).first) ).pow(number(2));
                }
                dist /= rate; //TODO: use proper rounding?
                if (dist < 1) return 1;
                return (((number) intlength * (number) dimension()*(number) dimension() / dist));
            }
        
            /**
            * @brief random move in one direction.
            */
			/*
            void moveRandom()
            {
                unsigned dim = dimension();
                unsigned value = rand();
                unsigned dir = value%dim;
                bool neg = (rand() & 1);
                if (neg) mCoordinates[dir]--;
                else mCoordinates[dir]++;
            }
			*/
            /**
             * 
             * @return the sum of all coordinates
             */
            number sum() const
            {
                number sum = 0;
                for (auto pointIt : mCoordinates)
                {
                    sum += (pointIt).second;
                }
                return sum;
            }

            /**
             * @brief: function to calculate points in the neighborhood, with one fixed dimension.
             * @return std::vector with all points in the neighborhood, with a fixed dimension, and except the point itself.
             */
			std::vector<Point<NumberType> > getAllNeighborsForAFixedDimension(const carl::Variable& fixedDim) const
            {
                std::vector<Point<NumberType> > neighbors;
                unsigned dim = dimension();

                // TODO comment
                int nrofNeighbors = (pow(2, (dim - 1)) - 1);

                vector_t coordinates;

                for (int neighborNr = 1; neighborNr <= nrofNeighbors; neighborNr++) {
                    //calculate the next neighbor we going to check
                    for (auto pointIt : mCoordinates)
                    {
                        if ((*pointIt).first > fixedDim)
                        {
                            coordinates[(*pointIt).first] = (*pointIt).second - ((neighborNr >> (dim - (*pointIt).first - 1)) & 1);
                        } else if ( (*pointIt).first == fixedDim)
                        {
                            coordinates[(*pointIt).first] = (*pointIt).second;
                        } else 
                        { // k < fixed
                            coordinates[(*pointIt).first] = (*pointIt).second - ((neighborNr >> (dim - (*pointIt).first - 1 - 1)) & 1);
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
            static Point<NumberType> coordinateMax(const Point<NumberType>& p1, const Point<NumberType>& p2)
            {
                Point<NumberType> p = Point<NumberType>(p1.dimension());
                for (auto pointIt : p1.mCoordinates) {
                    ( (*pointIt).second > p2[(*pointIt).first]) ? p[(*pointIt).first] = (*pointIt).second : p[(*pointIt).first] = p2[(*pointIt).first];
                }
                return p;
            }

            /**
             * Change the coordinates of the point. Moving the point one step in a given dimension.
             * @param d Dimension in which the coordinate is increased.
             */
			void IncrementInFixedDim(const carl::Variable& d)
            {
                ++(mCoordinates.at(d));
            }

            /**
             * 
             * @param val The value to be added to each coordinate
             */
            void IncrementInAllDim(const number& val = 1)
            {
                for (auto pointIt : mCoordinates)
                {
                    mCoordinates[(pointIt).first] += val;
                }
            }

            /**
             * Change the point's coordinates. Moving the point one step in a given dimension.
             * @param d Dimension in which the coordinate is decreased.
             */
			void DecrementInFixedDim(const carl::Variable& d)
            {
                --(mCoordinates.at(d));
            }

            /**
             *
             * @param d
             * @return The point with coordinates [x(1), .., x(d-1), x(d)-1, x(d+1), ..., x(n) ]
             */
			Point& getPredecessorInDimension(const carl::Variable& d) const
            {
                Point<NumberType> pred = Point(*this);
                pred.DecrementInFixedDim(d);
                return pred;
            }

			/*
            static Point Random(const Point& boundary)
            {
                Point p = Point(boundary.dimension());
                for (unsigned d = 0; d < boundary.dimension(); d++) 
                {
                    p[d].from_double(boundary[d] * (rand() / (RAND_MAX + 1.0)) + 0.5);
                }
                return p;
            }
			*/
			 
            /**
             * @brief Check if in range.
             * @param boundary Point with coordinates that may not be exceeded in positive direction.
             * @return true, if every coordinate is within boundary[i] and 0. 
             */
            bool isInBoundary(const Point<NumberType>& boundary) const 
            {
                for (auto pointIt : mCoordinates)
                {
					if(!boundary.hasDimension(pointIt.first))
					{
						continue;
					}
                    if (pointIt.second > boundary.at(pointIt.first)) return false;
                }
                return true;
            }

			/*
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
			 */

            /**
             * Operators & Comparison functions
             */
		
			bool hasDimension(const carl::Variable& i) const
			{
				return (mCoordinates.find(i) != mCoordinates.end());
			}

            bool haveEqualCoordinate(const Point<NumberType>& p2) const 
            {
                if( dimension() == p2.dimension() )
                {
                    for (auto pointIt : mCoordinates)
                    {
						if ( p2.hasDimension(pointIt.first))
						{
							if ( pointIt.second == p2.mCoordinates.at(pointIt.first) ) return true;
						}
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
                for (auto pointIt : p1.mCoordinates)
                {
					assert(p2.hasDimension(pointIt.first));
                    if ( pointIt.second != p2.mCoordinates.at(pointIt.first) )
                    {
                        return ( pointIt.second < p2.mCoordinates.at(pointIt.first) );
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
                return p2 < p1;
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
                for (auto pointIt : p1.mCoordinates)
                {
                    if ( !p2.hasDimension(pointIt.first) || pointIt.second != p2.mCoordinates.at(pointIt.first)) return false;
                }
                return true;
            }

            friend bool operator!=(const Point<NumberType> & p1, const Point<NumberType> & p2)
            {
                return !(p1 == p2);
            }

            /**
             *
             * @param i
             * @return
             */
			number& operator[] (const carl::Variable& i)
            {
                return mCoordinates[i];
            }

			number at(const carl::Variable& i) const
			{
				return mCoordinates.at(i);
			}
		
		
            /**
             *
             * @param i
             * @return
             */
		/*
			const number& operator[] (const carl::Variable& i) const
            {
				std::cout << "Const" << std::endl;
                return mCoordinates[i];
            }
*/
            /**
             *
             * @param ostr
             * @param p
             * @return
             */
            friend std::ostream & operator<< (std::ostream& ostr, const Point<NumberType>& p)
            {
                ostr << "(";
				
				for (auto pointIt : p.mCoordinates) {
                    ostr << pointIt.second.toString() << "[" << pointIt.first << "] ";
                }
				
				ostr << ")";
                return ostr;
            }
    };
}