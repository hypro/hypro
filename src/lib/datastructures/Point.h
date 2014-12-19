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
            typedef std::set<Point<Number> > pointSet;
            typedef std::map<carl::Variable, carl::FLOAT_T<Number> > coordinateMap;
            typedef std::map<carl::Variable, Number> rawCoordinateMap;

        private:
            coordinateMap mCoordinates;

            //Adjacency List of this Point (if applicable)
            std::vector<Point<Number>* > mNeighbors;
            //Minkowsi Decompositon of this point (if applicable)
            std::vector<Point<Number> > mComposedOf;

		
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
            Point(const carl::Variable& _var, const carl::FLOAT_T<Number>& _value = carl::FLOAT_T<Number>())
            {
                mCoordinates[_var] = _value;
            }
		
            /**
             * Constructs a point with the passed dimension and sets the coordinates to the initial value.
             * @param dim
             * @param initialValue
             */
            Point(const carl::Variable& _var, const Number& _value = Number())
            {
                mCoordinates[_var] = carl::FLOAT_T<Number>(_value);
            }
            
            Point(std::initializer_list<Number> _coordinates)
            {
                unsigned count = 0;
                for(auto& coordinate : _coordinates)
                {
                    mCoordinates.insert( std::make_pair(hypro::VariablePool::getInstance().carlVarByIndex(count), carl::FLOAT_T<Number>(coordinate)) );
                    ++count;
                }

            }

            //@author Chris K. (for Minkowski Sum Test)
            Point(std::vector<Number> _coordinates)
            {
                unsigned count = 0;
                for(unsigned j = 0; j < _coordinates.size(); ++j)
                {
                    mCoordinates.insert( std::make_pair(hypro::VariablePool::getInstance().carlVarByIndex(count), carl::FLOAT_T<Number>(_coordinates.at(j))) );
                    ++count;
                }
            }

            /**
             * Constructs a point with the passed coordinates
             * @param coordinates
             */
            Point(const coordinateMap& _coordinates) 
            {
                mCoordinates.insert(_coordinates.begin(), _coordinates.end());
            }

            /**
             * Constructs a point with the passed coordinates
             * @param coordinates
             */
            Point(const rawCoordinateMap& _coordinates) 
            {
                for (auto it : _coordinates) {
                    mCoordinates.insert(std::make_pair(it.first, carl::FLOAT_T<Number>(it.second)));
                }
            }
            
            Point(const vector& _vector)
            {
                for (unsigned rowIndex = 0; rowIndex < _vector.rows(); ++rowIndex)
                {
                    mCoordinates.insert( std::make_pair( hypro::VariablePool::getInstance().carlVarByIndex(rowIndex), _vector(rowIndex,0) ) );
                }
            }

            /**
             * Copy constructor
             * @param p
             */
            Point(const Point<Number>& _p) 
            {
                mCoordinates.insert(_p.mCoordinates.begin(), _p.mCoordinates.end());
                for(auto& neighbor : _p.mNeighbors)
                {
                	mNeighbors.push_back(neighbor);
                }

                for(auto& composite : _p.mComposedOf)
                {
                	mComposedOf.push_back(composite);
                }
            }
            
            /*
            template<typename F = FloatType, DisableIf< std::is_same<F, double> > = dummy>
            FLOAT_T<FloatType>(const FloatType& val, const CARL_RND=CARL_RND::N)
            {
                mValue = val;
            }
            */
             
            template<typename F, carl::DisableIf< std::is_same<F, Number> > = carl::dummy>
            Point(const Point<F>& _p)
            {
                for(auto& coordinate : _p.coordinates())
                {
                    carl::FLOAT_T<Number> tmp = coordinate.second;
                    mCoordinates.insert(std::make_pair(coordinate.first, tmp));
                }
            }

            ~Point() 
            {
                mCoordinates.clear();
            }
            
            /**
             * Getter & Setter
             */
            
            std::vector<Point<Number> > neighbors() const {
            	//return mNeighbors;
            	//TODO fix (does this have bad side effects?)
            	std::vector<Point<Number>> res;
            	for (unsigned i =0; i<mNeighbors.size(); ++i) {
            		res.push_back( *(mNeighbors.at(i)) );
            	}
            	return res;
            }

            void setNeighbors(const std::vector<Point<Number>* >& _neighbors) {
            	mNeighbors = _neighbors;
            }

            void addNeighbor(Point<Number>* _neighbor) {
            	mNeighbors.push_back(_neighbor);
            }

            std::vector<Point<Number> > composedOf() const {
            	return mComposedOf;
            }

            void setComposition(const std::vector<Point<Number> >& _elements) {
            	mComposedOf = _elements;
            }

            void addToComposition(const Point<Number>& _element) {
            	mComposedOf.push_back(_element);
            }

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
            carl::FLOAT_T<Number> coordinate(const carl::Variable& _var) const
            {
                assert(mCoordinates.count(_var) > 0);
                return mCoordinates.at(_var);
            }
            
            const Number& rawCoordinate(const carl::Variable& _var) const
            {
                return this->coordinate(_var).value();
            }

            coordinateMap coordinates() const 
            {
                return mCoordinates;
            }
        
            coordinateMap& rCoordinates()
            {
                return mCoordinates;
            }
		
            /**
             * Set a specific coordinate
             * @param dim    the dimension that is changed
             * @param value  the new value
             */
            void setCoordinate(const carl::Variable& _dim, carl::FLOAT_T<Number> _value)
            {
                mCoordinates[_dim] = _value;
            }
            
            void setCoordinate(const carl::Variable& _dim, Number _value)
            {
                mCoordinates[_dim] = carl::FLOAT_T<Number>(_value);
            }
            
            /**
             * 
             * @param coordinates
             * @param offset
             */
            void insertCoordinates(const coordinateMap& _coordinates)
            {
                mCoordinates.insert(_coordinates.begin(), _coordinates.end());
            }
            
            void insertCoordinates(const rawCoordinateMap& _coordinates)
            {
                for(auto& valuePair : _coordinates)
                {
                    mCoordinates.insert(std::make_pair(valuePair.first, carl::FLOAT_T<Number>(valuePair.second)));
                }
            }
            
            /**
             * Sets the coordinates from the given vector
             */
            void coordinatesFromVector(const vector& vector)
            {
            	assert( (unsigned) vector.size() == mCoordinates.size() );
            	unsigned index = 0;
            	for (auto& pointIt : mCoordinates) {
            		mCoordinates[pointIt.first] = vector(index);
            		++index;
            	}
            }

            /**
             *
             * @return iterator to begin of mCoordinates
             */
            typename coordinateMap::const_iterator begin() const
            {
                return mCoordinates.begin();
            }

            /**passing
             *
             * @return iterator to end of mCoordinates
             */
            typename coordinateMap::const_iterator end() const
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
		
            void removeDimension(const carl::Variable& _i)
            {
                mCoordinates.erase(_i);
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
            
            Point<Number> extAdd(const Point<Number>& _rhs) const
            {
                Point<Number> result = *this;
                for(auto& coeffB : _rhs.coordinates())
                {
                    if(result.hasDimension(coeffB.first)) 
                    {
                        result.setCoordinate(coeffB.first, result.coordinate(coeffB.first) + coeffB.second);
                    }
                    else
                    {
                        result.setCoordinate(coeffB.first, coeffB.second);
                    }
                }
                return result;
            }
            
            std::vector<carl::FLOAT_T<Number> > polarCoordinates( const Point<Number>& _origin,  bool _radians = true ) const
            {
                Point<Number> base = *this - _origin;
                std::cout << "Point: " << base << std::endl;
                
                
                std::vector<carl::FLOAT_T<Number> > result;
                
                // 1st component of the result is the radial part, the following components are the angles.
                carl::FLOAT_T<Number> radialCoordinate;
                for(auto dimension : base.mCoordinates)
                {
                    carl::FLOAT_T<Number> square;
                    dimension.second.pow(square, 2);
                    radialCoordinate += square;
                }
                radialCoordinate.sqrt_assign();
                result.insert(result.begin(), radialCoordinate);
                
                std::cout << "Radial coordinate: " << radialCoordinate << std::endl;
                
                // compute polar angles
                carl::FLOAT_T<Number> angle;
                for(auto dimension = base.mCoordinates.begin(); dimension != --base.mCoordinates.end(); ++dimension)
                {
                    std::cout << "Processing: " << (*dimension).first << "->" << (*dimension).second << std::endl;
                    angle = 0;
                    for(auto dimension2 = dimension; dimension2 != base.mCoordinates.end(); ++dimension2)
                    {
                        carl::FLOAT_T<Number> square;
                        angle += (*dimension2).second.pow(square, 2);
                    }
                    std::cout << "Summed squares: " << angle << std::endl;
                    angle.sqrt_assign();
                    angle = (*dimension).second / angle;
                    std::cout << "After division: " << angle << std::endl;
                    angle.acos_assign();
                    std::cout << "After acos: " << angle << std::endl;
                    if(!_radians)
                    {
                        angle /= 2*PI_DN ;
                        angle *= 360;
                    }
                    result.insert(result.end(), angle);
                    std::cout << "Angle: " << angle << std::endl;
                }
                if((*base.mCoordinates.rbegin()).second < carl::FLOAT_T<Number>(0))
                {
                    std::cout << "Correct last angle: ";
                    carl::FLOAT_T<Number> tmp = result.back();
                    result.pop_back();
                    if(!_radians)
                    {
                        tmp = Number(360) - tmp;
                    }
                    else
                    {
                        tmp = -tmp;
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
            Point<Number> newEmpty() const
            {
                coordinateMap coordinates;
                for (auto pointIt : mCoordinates)
                {
                    coordinates.insert(std::make_pair(pointIt.first, carl::FLOAT_T<Number>(0)));
                }
                return Point<Number>(coordinates);
            }
            
            /**
             * Method to move the point
             * @param p Point with coordinates describing the move.
             * @return true, if the result has a negative coordinate.
             */
            bool move(const Point<Number>& _p) 
            {
                bool negative = false;
                for(auto pointIt = _p.begin(); pointIt != _p.end(); ++pointIt)
                {
                    if(mCoordinates.count((*pointIt).first) > 0)
                    {
                        mCoordinates[(*pointIt).first] += (*pointIt).second;
                    }
                    else
                    {
                        mCoordinates[(*pointIt).first] = (*pointIt).second;
                    }
                    if (mCoordinates.at((*pointIt).first) < carl::FLOAT_T<Number>(0)) negative = true;
                }
                return negative;
            }

            /**
             * Makes a linear transformation, ie A * p + b
             */
            void linearTransformation(const matrix& A, const vector& b = vector())
            {
            	coordinatesFromVector(A * vector(*this) + b);
            }

            /**
             * 
             * @return the sum of all coordinates
             */
            carl::FLOAT_T<Number> sum() const
            {
                carl::FLOAT_T<Number> sum = 0;
                for (auto pointIt : mCoordinates)
                {
                    sum += (pointIt).second;
                }
                return sum;
            }

            /**
             * 
             * @param p1 One point
             * @param p2 Other point
             * @return A point with the coordinate-wise maximum of p1 and p2.
             */
            static Point<Number> coordinateMax(const Point<Number>& _p1, const Point<Number>& _p2)
            {
                assert(_p1.hasDimensions(_p2.variables()));
                coordinateMap coordinates;
                for (auto pointIt : _p1.mCoordinates) {
                    if (pointIt.second > _p2.at(pointIt.first)) {
                        coordinates[pointIt.first] = pointIt.second;
                    } else {
                        coordinates[pointIt.first] = _p2.at(pointIt.first);
                    }
                }
                return Point<Number>(coordinates);
            }
            
            static const Number& inftyNorm(const Point<Number> _p)
            {
                carl::FLOAT_T<Number> res = 0;
                for(auto coordinateIt = _p.mCoordinates.begin(); coordinateIt != _p.mCoordinates.end(); ++coordinateIt)
                {
                    carl::FLOAT_T<Number> abs;
                    coordinateIt->second.abs(abs);
                    res = res > abs ? res : abs;
                }
                return res.value();
            }

            /**
             * Change the coordinates of the point. Moving the point one step in a given dimension.
             * @param d Dimension in which the coordinate is increased.
             */
            void incrementInFixedDim(const carl::Variable& _d)
            {
                ++(mCoordinates.at(_d));
            }

            /**
             * 
             * @param val The value to be added to each coordinate
             */
            void incrementInAllDim(const carl::FLOAT_T<Number>& _val = 1)
            {
                for (auto pointIt : mCoordinates)
                {
                    mCoordinates[(pointIt).first] += _val;
                }
            }

            /**
             * Change the point's coordinates. Moving the point one step in a given dimension.
             * @param d Dimension in which the coordinate is decreased.
             */
            void decrementInFixedDim(const carl::Variable& _d)
            {
                --(mCoordinates.at(_d));
            }

            /**
             *
             * @param d
             * @return The point with coordinates [x(1), .., x(d-1), x(d)-1, x(d+1), ..., x(n) ]
             */
            Point getPredecessorInDimension(const carl::Variable& _d) const
            {
                Point<Number> pred = Point<Number>(*this);
                pred.decrementInFixedDim(_d);
                return pred;
            }
			 
            /**
             * @brief Check if in range.
             * @param boundary Point with coordinates that may not be exceeded in positive direction.
             * @return true, if every coordinate is within boundary[i] and 0. 
             */
            bool isInBoundary(const Point<Number>& _boundary) const 
            {
                for (auto pointIt : mCoordinates)
                {
                    if(!_boundary.hasDimension(pointIt.first))
                    {
                        continue;
                    }
                    if (pointIt.second > _boundary.at(pointIt.first)) return false;
                }
                return true;
            }

            /**
             * Operators & Comparison functions
             */
		
            bool hasDimension(const carl::Variable& _i) const
            {
                return (mCoordinates.find(_i) != mCoordinates.end());
            }
            
            bool hasDimensions(const std::vector<carl::Variable>& _variables) const
            {
                if (dimension() != _variables.size()) return false;
                for (auto it : _variables) {
                    if (!hasDimension(it)) return false;
                }
                return true;
            }

            bool haveEqualCoordinate(const Point<Number>& _p2) const 
            {
                if( dimension() == _p2.dimension() )
                {
                    for (auto pointIt : mCoordinates)
                    {
                        if ( _p2.hasDimension(pointIt.first))
                        {
                            if ( pointIt.second == _p2.mCoordinates.at(pointIt.first) ) return true;
                        }
                    }
                }
                return false;
            }
            
            /**
             * Checks if the point has the same dimensions as this point.
             * The carl::FLOAT_T<Number> of dimensions has to be equal as well as the actual
             * variables used for those dimensions.
             * 
             * @param p
             * @return True, if all dimension variables are equal
             */
            bool haveSameDimensions(const Point<Number>& _p) const
            {
                if (dimension() != _p.dimension())
                {
                    return false;
                }
                for (auto pointIt : mCoordinates)
                {
                    if ( !_p.hasDimension(pointIt.first))
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
            friend bool operator<(const Point<Number>& _p1, const Point<Number>& _p2)
            {
                for (auto pointIt : _p1.mCoordinates)
                {
                    assert(_p2.hasDimension(pointIt.first));
                    if ( pointIt.second != _p2.mCoordinates.at(pointIt.first) )
                    {
                        return ( pointIt.second < _p2.mCoordinates.at(pointIt.first) );
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
            friend bool operator>(const Point<Number> & _p1, const Point<Number> & _p2)
            {
                return _p2 < _p1;
            }

            /**
             *
             * @param p1
             * @param p2
             * @return true, if they are equal.
             */
            friend bool operator==(const Point<Number> & _p1, const Point<Number> & _p2)
            {
                if(_p1.dimension() != _p2.dimension()) return false;
                for (auto pointIt : _p1.mCoordinates)
                {
                    if ( !_p2.hasDimension(pointIt.first) || pointIt.second != _p2.mCoordinates.at(pointIt.first)) return false;
                }
                return true;
            }

            /**
             *
             * @param p1
             * @param p2
             * @return true, if they are not equal.
             */
            friend bool operator!=(const Point<Number> & _p1, const Point<Number> & _p2)
            {
                return !(_p1 == _p2);
            }
            
            Point<Number>& operator+=(const Point<Number>& _rhs)
            {
                assert(this->dimension() == _rhs.dimension());
                for( auto lCoordinate : mCoordinates)
                {
                    assert(_rhs.hasDimension(lCoordinate.first));
                    mCoordinates[lCoordinate.first] = lCoordinate.second+_rhs.coordinate(lCoordinate.first);
                }
                return *this;
            }
            
            Point<Number>& operator-=(const Point<Number>& _rhs)
            {
                assert(this->dimension() == _rhs.dimension());
                for( auto lCoordinate : mCoordinates)
                {
                    assert(_rhs.hasDimension(lCoordinate.first));
                    mCoordinates[lCoordinate.first] = lCoordinate.second-_rhs.coordinate(lCoordinate.first);
                }
                return *this;
            }
            
            Point<Number>& operator/=(unsigned _quotient)
            {
                for( auto lCoordinate : mCoordinates)
                {
                    mCoordinates[lCoordinate.first] = lCoordinate.second/_quotient;
                }
                return *this;
            }
            
            Point<Number>& operator*=(const carl::FLOAT_T<Number> _factor)
            {
                for( auto lCoordinate : mCoordinates)
                {
                    mCoordinates[lCoordinate.first] = lCoordinate.second*_factor;
                }
                return *this;
            }

            /**
             *
             * @param i
             * @return
             */
            carl::FLOAT_T<Number>& operator[] (const carl::Variable& _i)
            {
                return mCoordinates[_i];
            }

            carl::FLOAT_T<Number> at(const carl::Variable& _i) const
            {
                return mCoordinates.at(_i);
            }
		
            /**
             *
             * @param ostr
             * @param p
             * @return
             */
            friend std::ostream & operator<< (std::ostream& _ostr, const Point<Number>& _p)
            {
                _ostr << "( ";		
                for (auto pointIt : _p.mCoordinates) {
                    _ostr << pointIt.second.toString() << "[" << pointIt.first << "] ";
                } 
                _ostr << ")";
                return _ostr;
            }

            explicit operator vector() const
            {
            	vector result = vector(mCoordinates.size());
            	unsigned index = 0;
            	for (auto& pointIt : mCoordinates) {
            		result(index) = pointIt.second;
            		++index;
            	}
            	return result;
            }
    };
    
    template<typename Number>
    const Point<Number> operator+( const Point<Number>& _lhs, const Point<Number>& _rhs )
    {
        assert(_lhs.dimension() == _rhs.dimension());
        Point<Number> result;
        for( auto lCoordinate : _lhs)
        {
            assert(_rhs.hasDimension(lCoordinate.first));
            result.setCoordinate(lCoordinate.first, lCoordinate.second+_rhs.coordinate(lCoordinate.first));
        }
        return result;
    }
    
    template<typename Number>
    const Point<Number> operator-( const Point<Number>& _lhs, const Point<Number>& _rhs )
    {
        assert(_lhs.dimension() == _rhs.dimension());
        Point<Number> result;
        for( auto lCoordinate : _lhs)
        {
            assert(_rhs.hasDimension(lCoordinate.first));
            result.setCoordinate(lCoordinate.first, lCoordinate.second-_rhs.coordinate(lCoordinate.first));
        }
        return result;
    }
    
    template<typename Number>
    const Point<Number> operator/( const Point<Number>& _lhs, unsigned _quotient )
    {
        Point<Number> result;
        for(auto& lCoordinate : _lhs)
        {
            result.setCoordinate(lCoordinate.first,(lCoordinate.second/_quotient));
        }
        return result;
    }
    
    template<typename Number>
    carl::FLOAT_T<Number> operator*( const Point<Number>& _lhs, const Point<Number>& _rhs )
    {
        assert(_lhs.dimension() == _rhs.dimension());
        carl::FLOAT_T<Number> result = 0;
        for(auto lCoordinate : _lhs)
        {
            assert(_rhs.hasDimension(lCoordinate.first));
            result += lCoordinate.second*_rhs.coordinate(lCoordinate.first);
        }
        return result;
    }
    
    template<typename Number>
    const Point<Number> operator*( const Point<Number>& _lhs, const carl::FLOAT_T<Number>& _factor)
    {
        Point<Number> result = _lhs;
        for(auto& coordinate : result)
        {
            coordinate *= _factor;
        }
        return result;
    }

}
