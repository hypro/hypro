/** 
 * The point class is the basis for all implementation. It consists of a vector
 * of coordinates which forms a point in a n-dimensional space.
 * @file   Point.h
 * 
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @author Sebastian Junges
 * @author Benedikt Seidl
 * 
 * @since	2011-01-17
 * @version     2014-04-03
 */
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
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
    template<class Number>
    class Point 
    {
        public:
            //typedef std::vector<carl::FLOAT_T<Number> > vector_t;
            typedef std::set<Point<Number> > pointSet;
            typedef std::map<carl::Variable, carl::FLOAT_T<Number> > vector_t;
	private:
            typedef carl::FLOAT_T<Number> number;
            typedef std::map<carl::Variable, Number> orig_number_map;

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
            Point(const Point<Number>& p) 
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
            
            Point<Number> origin() const
            {
                Point<Number> result;
                for(auto dimension : mCoordinates)
                {
                    result.setCoordinate(dimension.first, 0);
                }
                return result;
            }
            
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
            
            void setCoordinate(const carl::Variable& dim, Number value)
            {
                mCoordinates[dim] = carl::FLOAT_T(value);
            }
            
            /**
             * 
             * @param coordinates
             * @param offset
             */
            void insertCoordinates(const vector_t& coordinates)
            {
                mCoordinates.insert(coordinates.begin(), coordinates.end());
            }
            
            void insertCoordinates(const orig_number_map& coordinates)
            {
                for(auto& valuePair : coordinates)
                {
                    mCoordinates.insert(std::make_pair(valuePair.first, carl::FLOAT_T<Number>(valuePair.second)));
                }
            }
            
            /**
             *
             * @return iterator to begin of mCoordinates
             */
            typename vector_t::const_iterator begin() const
            {
                return mCoordinates.begin();
            }

            /**
             *
             * @return iterator to end of mCoordinates
             */
            typename vector_t::const_iterator end() const
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
            
            std::vector<carl::Variable> variables() const
            {
                std::vector<carl::Variable> variables;
                for(auto dimension : mCoordinates)
                {
                    variables.push_back(dimension.first);
                }
                return variables;
            }
            
            std::vector<number> polarCoordinates( const Point<Number>& origin,  bool radians = true ) const
            {
                Point<Number> base = *this - origin;
                std::cout << "Point: " << base << std::endl;
                
                
                std::vector<number> result;
                
                // 1st component of the result is the radial part, the following components are the angles.
                number radialCoordinate;
                for(auto dimension : base.mCoordinates)
                {
                    number square;
                    dimension.second.pow(square, 2);
                    radialCoordinate += square;
                }
                radialCoordinate.sqrt_assign();
                result.insert(result.begin(), radialCoordinate);
                
                std::cout << "Radial coordinate: " << radialCoordinate << std::endl;
                
                // compute polar angles
                number angle;
                for(auto dimension = base.mCoordinates.begin(); dimension != --base.mCoordinates.end(); ++dimension)
                {
                    std::cout << "Processing: " << (*dimension).first << "->" << (*dimension).second << std::endl;
                    angle = 0;
                    for(auto dimension2 = dimension; dimension2 != base.mCoordinates.end(); ++dimension2)
                    {
                        number square;
                        angle += (*dimension2).second.pow(square, 2);
                    }
                    std::cout << "Summed squares: " << angle << std::endl;
                    angle.sqrt_assign();
                    angle = (*dimension).second / angle;
                    std::cout << "After division: " << angle << std::endl;
                    angle.acos_assign();
                    std::cout << "After acos: " << angle << std::endl;
                    if(!radians)
                    {
                        angle /= 2*PI_DN ;
                        angle *= 360;
                    }
                    result.insert(result.end(), angle);
                    std::cout << "Angle: " << angle << std::endl;
                }
                if((*base.mCoordinates.rbegin()).second < 0)
                {
                    std::cout << "Correct last angle: ";
                    number tmp = result.back();
                    result.pop_back();
                    if(!radians)
                    {
                        tmp = 360 - tmp;
                    }
                    else
                    {
                        tmp = -1* tmp;
                    }
                    std::cout << tmp << std::endl;
                    result.push_back(tmp);
                }
                
                assert(result.size() == this->dimension());
                return result;
            }
            

            /**
             * Functions
             */
            
            /**
             * Creates a new empty point (origin) with the same dimensions
             * as this point.
             * 
             * @return new empty point
             */
            Point<Number> newEmpty()
            {
                vector_t coordinates;
                for (auto pointIt : mCoordinates)
                {
                    coordinates.insert(std::make_pair(pointIt.first, Number(0)));
                }
                return Point<Number>(coordinates);
            }
            
            /**
             * Method to move the point
             * @param p Point with coordinates describing the move.
             * @return true, if the result has a negative coordinate.
             */
            bool move(const Point<Number>& p) 
            {
                bool negative = false;
                for(auto pointIt = p.begin(); pointIt != p.end(); ++pointIt)
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
            void nextPointOnGrid(const Point<Number>& bounds) 
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
    	
            number getGaussianProbability(Point<Number> & mean) const{
                return 0;
            }

            number getDistanceDependentProbabiltity(Point<Number> & mean, unsigned intlength, number rate) const
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
            std::vector<Point<Number> > getAllNeighborsForAFixedDimension(const carl::Variable& fixedDim) const
            {
                std::vector<Point<Number> > neighbors;
                unsigned dim = dimension();

                // TODO comment
                int nrofNeighbors = (pow(2, (dim - 1)) - 1);

                vector_t coordinates;
                
                // iterate through all neighbors
                for (int neighborNr = 1; neighborNr <= nrofNeighbors; neighborNr++) {
                    // then iterate through all dimensions
                    int i = 0;
                    for (auto& pointIt : mCoordinates) {
                        // look if the bit of the current coordinate is set
                        // thus the first point will have 1 less in every second dimension,
                        // the second point will have 1 less in every fourth dimension etc.
                        if (pointIt.first == fixedDim) {
                            coordinates[pointIt.first] = pointIt.second;
                        }    
                        else if ((neighborNr >> i++) & 1) {
                            coordinates[pointIt.first] = pointIt.second - 1;
                        }
                        else {
                            coordinates[pointIt.first] = pointIt.second;
                        }
                    }
                    Point<Number> neighbor = Point<Number>(coordinates);
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
            std::vector<Point<Number> > getAllNeighbours(bool pointself=false) const
            {
                std::vector<Point<Number> > neighbors = getAllNeighborsForAFixedDimension(0);
                unsigned nrneighbors = neighbors.size();
                //TODO comment!
                for (unsigned i = 0; i < nrneighbors; i++) 
                {
                    Point<Number> neighborpredecessor = Point(neighbors[i]).getPredecessorInDimension(0);
                    neighbors.push_back(neighborpredecessor);
                }

                Point<Number> pointPredecessor = getPredecessorInDimension(0);
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
            void incrementInFixedDim(const carl::Variable& d)
            {
                ++(mCoordinates.at(d));
            }

            /**
             * 
             * @param val The value to be added to each coordinate
             */
            void incrementInAllDim(const number& val = 1)
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
            void decrementInFixedDim(const carl::Variable& d)
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
                Point<Number> pred = Point<Number>(*this);
                pred.decrementInFixedDim(d);
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
            bool isInBoundary(const Point<Number>& boundary) const 
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
		
            bool hasDimension(const carl::Variable& i) const
            {
                return (mCoordinates.find(i) != mCoordinates.end());
            }
            
            bool hasDimensions(const std::vector<carl::Variable>& variables) const
            {
                if (dimension() != variables.size()) return false;
                for (auto it : variables) {
                    if (!hasDimension(it)) return false;
                }
                return true;
            }

            bool haveEqualCoordinate(const Point<Number>& p2) const 
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
             * Checks if the point has the same dimensions as this point.
             * The number of dimensions has to be equal as well as the actual
             * variables used for those dimensions.
             * 
             * @param p
             * @return True, if all dimension variables are equal
             */
            bool haveSameDimensions(const Point<Number>& p) const
            {
                if (dimension() != p.dimension())
                {
                    return false;
                }
                for (auto pointIt : mCoordinates)
                {
                    if ( !p.hasDimension(pointIt.first))
                    {
                        return false;
                    }
                }
                return true;
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