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
#include "../config.h"


namespace hypro {
    /*
     *  Class to store points in a MAXIMAL_DIMENSION space.
     */
    template<class Number>
    class Point 
    {
        public:
            typedef std::map<carl::Variable, carl::FLOAT_T<Number>> coordinateMap;
            typedef std::vector<carl::FLOAT_T<Number>> coordinateValues;

        protected:
            coordinateValues    mCoordinates;
            unsigned       mFactoryId;
		
        public:
        
            static const int POINT_RAND_MAX = 100;
            
            /**
             * Constructors & Destructor
             */

            /**
             * Constructs a point with the passed coordinates
             * @param coordinates
             */
            Point(const coordinateValues& _coordinates, unsigned _factory) : 
                mCoordinates(_coordinates),
                mFactoryId(_factory)
            {}

            /**
             * Copy constructor
             * @param p
             */
            Point(const Point<Number>& p) :
                mCoordinates(p.coordinates()),
                mFactoryId(p.factory())
            {}

            ~Point();
            
            /**
             * Getter & Setter
             */
            
            coordinateValues coordinates() const;
            coordinateValues& rCoordinates();
            unsigned factory() const;
            
            
            Point<Number> origin() const;
            
            /**
             * Returns the value of mCoordinates[dim].
             * @param  dim the dimension we want to get the value from.
             * @return 
             */
            carl::FLOAT_T<Number> coordinate(unsigned _index) const;
            carl::FLOAT_T<Number> coordinate(carl::Variable _var) const;
            
            /**
             * Set a specific coordinate
             * @param dim    the dimension that is changed
             * @param value  the new value
             */
            inline void setCoordinate(unsigned _index, carl::FLOAT_T<Number> value);
            inline void setCoordinate(carl::Variable var, carl::FLOAT_T<Number> value);

            
            /**
             * 
             * @param coordinates
             * @param offset
             */
            /*
            void insertCoordinates(vector_t& coordinates)
            {
                for(auto coordinate : coordinates)
                {
                    setCoordinate(coordinate.first, coordinate.second);
                }
            }
            */
            /**
             *
             * @return iterator to begin of mCoordinates
             */
            typename coordinateValues::const_iterator begin() const;

            /**
             *
             * @return iterator to end of mCoordinates
             */
            typename coordinateValues::const_iterator end() const;

            /**
             * 
             * @return The size of mCoordinates.
             */
            unsigned dimension() const;
            std::vector<carl::FLOAT_T<Number>> polarCoordinates( const Point<Number>& origin,  bool radians = true ) const;

            /**
             * Functions
             */
            
            /**
             * Method to move the point
             * @param p Point with coordinates describing the move.
             * @return true, if the result has a negative coordinate.
             */
            bool move(const Point<Number>& p);

            /**
	     * @brief gives the next point according to some (hardcoded) ordering.
	     * @param bounds The grid lies between the origin and this point.
	     *
	     */
            void nextPointOnGrid(const Point<Number>& bounds);
    	
            carl::FLOAT_T<Number> getGaussianProbability(Point<Number> & mean) const;
            carl::FLOAT_T<Number> getDistanceDependentProbabiltity(Point<Number> & mean, unsigned intlength, carl::FLOAT_T<Number> rate) const;
        
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
            carl::FLOAT_T<Number> sum() const;

            /**
             * @brief: function to calculate points in the neighborhood, with one fixed dimension.
             * @return std::vector with all points in the neighborhood, with a fixed dimension, and except the point itself.
             */
            std::vector<Point<Number> > getAllNeighborsForAFixedDimension(const carl::Variable& fixedDim) const;

            /**
             *
             * @param fixedDim
             * @return Vector filled with neighbours with coordinate[fixedDim] equal to the points coordinate.
             *  point is not an element of the returned vector.
             */
            std::vector<Point<Number> > getAllNeighbours(bool pointself=false) const;

            /**
             * 
             * @param p1 One point
             * @param p2 Other point
             * @return A point with the coordinate-wise maximum of p1 and p2.
             */
            static Point<Number> coordinateMax(const Point<Number>& p1, const Point<Number>& p2)
            {
                Point<Number> p = Point<Number>(p1.dimension());
                for (auto pointIt : p1.mCoordinates) {
                    ( (*pointIt).second > p2[(*pointIt).first]) ? p[(*pointIt).first] = (*pointIt).second : p[(*pointIt).first] = p2[(*pointIt).first];
                }
                return p;
            }

            /**
             * Change the coordinates of the point. Moving the point one step in a given dimension.
             * @param d Dimension in which the coordinate is increased.
             */
            void incrementInFixedDim(const carl::Variable& d);

            /**
             * 
             * @param val The value to be added to each coordinate
             */
            void incrementInAllDim(const carl::FLOAT_T<Number>& val = 1);

            /**
             * Change the point's coordinates. Moving the point one step in a given dimension.
             * @param d Dimension in which the coordinate is decreased.
             */
            void decrementInFixedDim(const carl::Variable& d);

            /**
             *
             * @param d
             * @return The point with coordinates [x(1), .., x(d-1), x(d)-1, x(d+1), ..., x(n) ]
             */
            Point<Number>& getPredecessorInDimension(const carl::Variable& d) const;

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
            bool isInBoundary(const Point<Number>& boundary) const;

			/*
            static Point moveRandomInBoundary(const Point<Number>& boundary)
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
		
            bool hasDimension(const carl::Variable& i) const;
            bool haveEqualCoordinate(const Point<Number>& p2) const;
            
            /**
             * Checks if the point has the same dimensions as this point.
             * The number of dimensions has to be equal as well as the actual
             * variables used for those dimensions.
             * 
             * @param p
             * @return True, if all dimension variables are equal
             */
            bool haveSameDimensions(const Point<Number>& p) const;

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
            friend bool operator<(const Point<Number>& p1, const Point<Number>& p2)
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
            friend bool operator>(const Point<Number> & p1, const Point<Number> & p2)
            {
                return p2 < p1;
            }

            /**
             *
             * @param p1
             * @param p2
             * @return true, if they are equal.
             */
            friend bool operator==(const Point<Number> & p1, const Point<Number> & p2)
            {
                if(p1.dimension() != p2.dimension()) return false;
                for (auto pointIt : p1.mCoordinates)
                {
                    if ( !p2.hasDimension(pointIt.first) || pointIt.second != p2.mCoordinates.at(pointIt.first)) return false;
                }
                return true;
            }
            
            friend bool operator!=(const Point<Number> & p1, const Point<Number> & p2)
            {
                return !(p1 == p2);
            }
            
            /**
             *
             * @param i
             * @return
             */
            
            carl::FLOAT_T<Number>& operator[] (const carl::Variable& i);
            
            carl::FLOAT_T<Number> at(const carl::Variable& i) const;
		
            /**
             *
             * @param ostr
             * @param p
             * @return
             */
            friend std::ostream & operator<< (std::ostream& ostr, const Point<Number>& p)
            {
                ostr << "(";		
                for (auto pointIt : p.mCoordinates) {
                    ostr << pointIt.second.toString() << "[" << pointIt.first << "] ";
                }		
                ostr << ")";
                return ostr;
            }
    };
    
    template<typename Number>
    const Point<Number> operator+( const Point<Number>& lhs, const Point<Number>& rhs )
    {
        assert(lhs.dimension() == rhs.dimension());
        Point<Number> result;
        for( auto lCoordinate : lhs)
        {
            assert(rhs.hasDimension(lCoordinate.first));
            result.setCoordinate(lCoordinate.first, lCoordinate.second+rhs.coordinate(lCoordinate.first));
        }
        return result;
    }
    
    template<typename Number>
    const Point<Number> operator-( const Point<Number>& lhs, const Point<Number>& rhs )
    {
        assert(lhs.dimension() == rhs.dimension());
        Point<Number> result;
        for( auto lCoordinate : lhs)
        {
            assert(rhs.hasDimension(lCoordinate.first));
            result.setCoordinate(lCoordinate.first, lCoordinate.second-rhs.coordinate(lCoordinate.first));
        }
        return result;
    }
}

#include "Point.tpp"