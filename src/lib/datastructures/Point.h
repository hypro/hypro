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
    class Point {
        public:
            typedef std::set<Point<Number> > pointSet;
            typedef std::map<carl::Variable, Number > coordinateMap;
			
        private:
            vector_t<Number> mCoordinates;

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
            Point(const Number& _value)
            {
				mCoordinates = vector_t<Number>(1);
                mCoordinates(0) = _value;
            }
            
            Point(std::initializer_list<Number> _coordinates)
            {
                unsigned count = 0;
				mCoordinates = vector_t<Number>(_coordinates.size());
                for(auto& coordinate : _coordinates)
                {
                    mCoordinates(count) = coordinate;
                    ++count;
                }
            }
			
			template<typename F, carl::DisableIf< std::is_same<F, Number> > = carl::dummy>
			Point(std::initializer_list<F> _coordinates)
            {
                unsigned count = 0;
				mCoordinates = vector_t<Number>(_coordinates.size());
                for(auto& coordinate : _coordinates)
                {
                    mCoordinates(count) = Number(coordinate);
                    ++count;
                }
            }

            //@author Chris K. (for Minkowski Sum Test)
            Point(std::vector<Number> _coordinates)
            {
                unsigned count = 0;
				mCoordinates = vector_t<Number>(_coordinates.size());
                for(unsigned j = 0; j < _coordinates.size(); ++j)
                {
                    mCoordinates(count) = _coordinates.at(count);
                    ++count;
                }
            }

            /**
             * Constructs a point with the passed coordinates
             * @param coordinates
             */
            Point(const coordinateMap& _coordinates) 
            {
				mCoordinates = vector_t<Number>(_coordinates.size());
                for(auto& coordinatepair : _coordinates) {
                    mCoordinates(hypro::VariablePool::getInstance().dimension(coordinatepair.first)) = coordinatepair.second;
                }
            }
            
            Point(const vector_t<Number>& _vector) :
			mCoordinates(_vector)
            {}

            /**
             * Copy constructor
             * @param p
             */
            Point(const Point<Number>& _p) 
            {
                mCoordinates = _p.rawCoordinates();
                for(auto& neighbor : _p.mNeighbors)
                {
                	mNeighbors.push_back(neighbor);
                }

                for(auto& composite : _p.mComposedOf)
                {
                	mComposedOf.push_back(composite);
                }
            }
             
            template<typename F, carl::DisableIf< std::is_same<F, Number> > = carl::dummy>
            Point(const Point<F>& _p)
            {
				mCoordinates = vector_t<Number>(_p.coordinates().size());
				unsigned count = 0;
                for(auto& coordinate : _p.coordinates())
                {
                    mCoordinates(count) = Number(coordinate.second);
					++count;
                }
            }

            virtual ~Point() 
            {}
            
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

          /*  std::vector<Point<Number> >& rNeighbors() {
            	//return mNeighbors;
            	//TODO fix (does this have bad side effects?)
            	std::vector<Point<Number>> res;
            	for (unsigned i =0; i<mNeighbors.size(); ++i) {
            		res.push_back( *(mNeighbors.at(i)) );
            	}
            	return res;
            }*/

            void setNeighbors(const std::vector<Point<Number>* >& _neighbors) {
            	mNeighbors = _neighbors;
            }

            void addNeighbor(Point<Number>* _neighbor) {
            	mNeighbors.push_back(_neighbor);
            }

            void removeNeighbor(Point<Number>* _neighbor) {
            	for(unsigned i = 0; i < mNeighbors.size(); i++){
            		if(*(mNeighbors.at(i)) == *(_neighbor)) {
            			mNeighbors.erase(mNeighbors.begin() + i);
            			break;
            		}
            	}
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

			static Point<Number> zero(unsigned _dim = 0) {
				return Point<Number>(vector_t<Number>::Zero(_dim));
			}
			
            Point<Number> origin() const
            {
                vector_t<Number> coordinates = vector_t<Number>::Zero(this->dimension());
				Point<Number> result = Point<Number>(coordinates);
                return result;
            }
            
            /**
             * Returns the value of mCoordinates[dim].
             * @param  dim the dimension we want to get the value from.
             * @return 
             */
            Number coordinate(const carl::Variable& _var) const
            {
                return mCoordinates(hypro::VariablePool::getInstance().dimension(_var));
            }
			
			Number coordinate(unsigned _dimension) const
			{
				assert(mCoordinates.size() > _dimension);
				return mCoordinates(_dimension);
			}

            coordinateMap coordinates() const 
            {
				coordinateMap res;
				for(unsigned i = 0 ; i < mCoordinates.rows(); ++i) {
					res.insert(std::make_pair(hypro::VariablePool::getInstance().carlVarByIndex(i), mCoordinates(i)));
				}
                return res;
            }
        
            vector_t<Number> rawCoordinates() const
            {
                return mCoordinates;
            }
		
            /**
             * Set a specific coordinate
             * @param dim    the dimension that is changed
             * @param value  the new value
             */
            void setCoordinate(const carl::Variable& _dim, const Number& _value)
            {
				unsigned dim = hypro::VariablePool::getInstance().dimension(_dim);
				assert(dim >= 0);
				if(dim >= mCoordinates.rows()) {
					vector_t<Number> old = mCoordinates;
					mCoordinates.resize(dim+1);
					mCoordinates.topLeftCorner(old.rows(),1) = old;
				}
                mCoordinates(dim) = _value;
            }
            
            /**
             * 
             * @param coordinates
             * @param offset
             */
//            void insertCoordinates(const coordinateMap& _coordinates)
//            {
//                mCoordinates.insert(_coordinates.begin(), _coordinates.end());
//            }
            
            /**
             * Sets the coordinates from the given vector
             */
            void coordinatesFromVector(const vector_t<Number>& vector)
            {
            	mCoordinates = vector;
            }

            /**
             * 
             * @return The size of mCoordinates.
             */
            unsigned dimension() const 
            {
                return mCoordinates.rows();
            }
		
//            void removeDimension(const carl::Variable& _i)
//            {
//                mCoordinates.erase(_i);
//            }
            
            std::vector<carl::Variable> variables() const
            {
                std::vector<carl::Variable> variables;
                for(unsigned i = 0; i != mCoordinates.rows(); ++i)
                {
                    variables.push_back(hypro::VariablePool::getInstance().carlVarByIndex(i));
                }
                return variables;
            }
            
            Point<Number> extAdd(const Point<Number>& _rhs) const
            {
            	assert(mCoordinates.rows() == _rhs.rawCoordinates().rows());

                Point<Number> result = Point<Number>(mCoordinates + _rhs.rawCoordinates());
                return result;
            }

            Number distance(const Point<Number>& _rhs) const {
            		return ( (mCoordinates - _rhs.rawCoordinates()).norm() );
            }
            
            std::vector<Number> polarCoordinates( const Point<Number>& _origin,  bool _radians = true ) const
            {
                Point<Number> base = *this - _origin;
                //std::cout << "Point: " << base << std::endl;
                
                std::vector<Number> result;
                
                // 1st component of the result is the radial part, the following components are the angles.
                Number radialCoordinate = Number(0);
                for(unsigned i = 0; i < base.dimension(); ++i)
                {
                    Number square;
                    square = pow(base.mCoordinates(i), 2);
                    radialCoordinate += square;
                }
                radialCoordinate = sqrt(radialCoordinate);
                result.insert(result.begin(), radialCoordinate);
                std::cout << __func__ << ":" << __LINE__ << std::endl;
				
                //std::cout << "Radial coordinate: " << radialCoordinate << std::endl;
                
                // compute polar angles
                Number angle;
                for(unsigned dimension = 0; dimension < base.dimension()-1; ++dimension)
                {
					std::cout << __func__ << ":" << __LINE__ << std::endl;
                    //std::cout << "Processing: " << (*dimension).first << "->" << (*dimension).second << std::endl;
                    angle = 0;
                    for(auto dimension2 = dimension; dimension2 < base.dimension(); ++dimension2)
                    {
						std::cout << __func__ << ":" << __LINE__ << std::endl;
                        Number square;
						square = pow(base.rawCoordinates()(dimension2), 2); // TODO: Check if this does the right thing and why angle += (*dimension) ... does not work
                        angle += square;
                    }
                    //std::cout << "Summed squares: " << angle << std::endl;
                    angle = sqrt(angle);
                    angle = base.mCoordinates(dimension) / angle;
                    //std::cout << "After division: " << angle << std::endl;
                    angle = acos(angle);
                    //std::cout << "After acos: " << angle << std::endl;
                    if(!_radians)
                    {
                        angle /= 2*PI_DN ;
                        angle *= 360;
                    }
                    result.insert(result.end(), angle);
                    //std::cout << "Angle: " << angle << std::endl;
                }
				std::cout << __func__ << ":" << __LINE__ << std::endl;
                if((base.mCoordinates(base.dimension()-1)) < Number(0))
                {
                    //std::cout << "Correct last angle: ";
                    Number tmp = result.back();
                    result.pop_back();
                    if(!_radians)
                    {
                        tmp = Number(360) - tmp;
                    }
                    else
                    {
                        tmp = -tmp;
                    }
                    //std::cout << tmp << std::endl;
                    result.push_back(tmp);
                }
                std::cout << __func__ << ":" << __LINE__ << std::endl;
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
				vector_t<Number> origin = vector_t<Number>::Zero(this->dimension());
                return Point<Number>(origin);
            }
            
            /**
             * Method to move the point
             * @param p Point with coordinates describing the move.
             * @return true, if the result has a negative coordinate.
             */
            bool move(const Point<Number>& _p) 
            {
                mCoordinates = mCoordinates + _p.rawCoordinates();
				bool negative = false;
				for(unsigned i = 0 ; i < mCoordinates.rows(); ++i) {
					if(mCoordinates(i) < 0) {
						negative = true;
						break;
					}
				}
                return negative;
            }

            /**
             * Makes a linear transformation, ie A * p + b
             */
            void linearTransformation(const matrix_t<Number>& A, const vector_t<Number>& b = vector_t<Number>())
            {
            	mCoordinates = A*mCoordinates + b;
            }

            /**
             * @return the sum of all coordinates (solved via dot product)
             */
            Number sum() const {
                Number sum = mCoordinates.dot(vector_t<Number>::One(mCoordinates.rows()));
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
                assert(_p1.dimension() == _p2.dimension());
                vector_t<Number> coordinates = vector_t<Number>(_p1.dimension());
				vector_t<Number> p1Coord = _p1.rawCoordinates();
				vector_t<Number> p2Coord = _p2.rawCoordinates();
                for (unsigned i = 0; i < _p1.dimension(); ++i) {
                    coordinates(i) = p1Coord(i) >= p2Coord(i) ? p1Coord(i) : p2Coord(i);
                }
                return Point<Number>(coordinates);
            }
            
            static Number inftyNorm(const Point<Number> _p)
            {
                Number res = 0;
				vector_t<Number> coord = _p.rawCoordinates();
                for (unsigned i = 0; i < _p.dimension(); ++i) {
                    Number absolute = abs(coord(i));
                    res = res > absolute ? res : absolute;
                }
                return res;
            }

            /**
             * Change the coordinates of the point. Moving the point one step in a given dimension.
             * @param d Dimension in which the coordinate is increased.
             */
            void incrementInFixedDim(const carl::Variable& _d) {
				mCoordinates(hypro::VariablePool::getInstance().dimension(_d)) += 1;
			}
			
			void incrementInFixedDim(unsigned _d) {
				mCoordinates(_d) += 1;
			}

            /**
             * 
             * @param val The value to be added to each coordinate
             */
            void incrementInAllDim(const Number& _val = 1)
            {
				vector_t<Number> one = vector_t<Number>::Ones(mCoordinates.rows());
				one *= _val;
                mCoordinates += one;
            }

            /**
             * Change the point's coordinates. Moving the point one step in a given dimension.
             * @param d Dimension in which the coordinate is decreased.
             */
            void decrementInFixedDim(const carl::Variable& _d)
            {
                mCoordinates(hypro::VariablePool::getInstance().dimension(_d)) -= 1;
            }
			
			void decrementInFixedDim(unsigned _d)
            {
                mCoordinates(_d) -= 1;
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
			
			Point getPredecessorInDimension(unsigned _d) const
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
                return (mCoordinates < _boundary.rawCoordinates());
            }

            /**
             * Operators & Comparison functions
             */
		
            bool hasDimension(const carl::Variable& _i) const
            {
                return (mCoordinates.rows() > hypro::VariablePool::getInstance().dimension(_i));
            }
            
            bool hasDimensions(const std::vector<carl::Variable>& _variables) const
            {
//                if (dimension() != _variables.size()) return false;
                for (auto it : _variables) {
                    if (!hasDimension(it)) return false;
                }
                return true;
            }

            bool haveEqualCoordinate(const Point<Number>& _p2) const 
            {
                if( dimension() == _p2.dimension() )
                {
                    for (unsigned i = 0 ; i < mCoordinates.rows(); ++i)
                    {
						if ( mCoordinates(i) == _p2.rawCoordinates()(i) ) return true;
                    }
                }
                return false;
            }
            
            /**
             * Checks if the point has the same dimensions as this point.
             * The Number of dimensions has to be equal as well as the actual
             * variables used for those dimensions.
             * 
             * @param p
             * @return True, if all dimension variables are equal
             */
            bool haveSameDimensions(const Point<Number>& _p) const
            {
                return (dimension() == _p.dimension());
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
                return (_p1.rawCoordinates() < _p2.rawCoordinates());
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
                return (_p1.rawCoordinates() == _p2.rawCoordinates());
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
                for(unsigned i = 0 ; i < mCoordinates.rows(); ++i)
                {
                    mCoordinates(i) += _rhs.at(i); 
                }
                return *this;
            }
            
            Point<Number>& operator-=(const Point<Number>& _rhs)
            {
                assert(this->dimension() == _rhs.dimension());
                for(unsigned i = 0 ; i < mCoordinates.rows(); ++i)
                {
                    mCoordinates(i) -= _rhs.at(i);
                }
                return *this;
            }
            
            Point<Number>& operator/=(unsigned _quotient)
            {
                for(unsigned i = 0 ; i < mCoordinates.rows(); ++i)
                {
                    mCoordinates(i) = mCoordinates(i)/_quotient;
                }
                return *this;
            }
            
            Point<Number>& operator*=(const Number _factor)
            {
                for(unsigned i = 0 ; i < mCoordinates.rows(); ++i)
                {
                    mCoordinates(i) = mCoordinates(i)*_factor;
                }
                return *this;
            }

            /**
             *
             * @param i
             * @return
             */
            Number& operator[] (const carl::Variable& _i)
            {
				unsigned dim = hypro::VariablePool::getInstance().dimension(_i);
				if(dim >= mCoordinates.rows()) {
					vector_t<Number> old = mCoordinates;
					mCoordinates.resize(dim+1);
					mCoordinates.topLeftCorner(old.rows(),1) = old;
				}
                return mCoordinates(dim);
            }
			
			Number& operator[] (unsigned _i)
            {
				if(_i >= mCoordinates.rows()) {
					vector_t<Number> old = mCoordinates;
					mCoordinates.resize(_i+1);
					mCoordinates.topLeftCorner(old.rows(),1) = old;
				}
                return mCoordinates(_i);
            }

            Number at(const carl::Variable& _i) const
            {
				assert(hypro::VariablePool::getInstance().dimension(_i) < mCoordinates.rows());
                return mCoordinates(hypro::VariablePool::getInstance().dimension(_i));
            }
			
			Number at(unsigned _index) const {
				assert(_index < mCoordinates.rows());
				return mCoordinates(_index);
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
                for (unsigned i = 0 ; i < _p.dimension()-1; ++i) {
                    _ostr << _p.at(i) << ", ";
                } 
                _ostr << _p.at(_p.dimension()-1);
                _ostr << ")";
                return _ostr;
            }

            explicit operator vector_t<Number>() const
            {
            	return mCoordinates;
            }
    };
    
    template<typename Number>
    const Point<Number> operator+( const Point<Number>& _lhs, const Point<Number>& _rhs )
    {
        assert(_lhs.dimension() == _rhs.dimension());
		vector_t<Number> resCoord = vector_t<Number>(_lhs.dimension());
		vector_t<Number> p1Coord = _lhs.rawCoordinates();
		vector_t<Number> p2Coord = _rhs.rawCoordinates();;
        resCoord = p1Coord + p2Coord;
        return Point<Number>(resCoord);
    }
    
    template<typename Number>
    const Point<Number> operator-( const Point<Number>& _lhs, const Point<Number>& _rhs )
    {
        assert(_lhs.dimension() == _rhs.dimension());
        vector_t<Number> resCoord = vector_t<Number>(_lhs.dimension());
		vector_t<Number> p1Coord = _lhs.rawCoordinates();
		vector_t<Number> p2Coord = _rhs.rawCoordinates();;
        resCoord = p1Coord - p2Coord;
        return Point<Number>(resCoord);
    }
    
    template<typename Number>
    const Point<Number> operator/( const Point<Number>& _lhs, unsigned _quotient )
    {
        vector_t<Number> resCoord = vector_t<Number>(_lhs.dimension());
		vector_t<Number> p1Coord = _lhs.rawCoordinates();
        resCoord = p1Coord / _quotient;
        return Point<Number>(resCoord);
    }
    
    template<typename Number>
    Number operator*( const Point<Number>& _lhs, const Point<Number>& _rhs )
    {
		vector_t<Number> p1Coord = _lhs.rawCoordinates();
		vector_t<Number> p2Coord = _rhs.rawCoordinates();;
        return p1Coord.dot(p2Coord);
    }
    
    template<typename Number>
    const Point<Number> operator*( const Point<Number>& _lhs, const Number& _factor)
    {
        vector_t<Number> resCoord = vector_t<Number>(_lhs.dimension());
		vector_t<Number> p1Coord = _lhs.rawCoordinates();
        resCoord = p1Coord * _factor;
        return Point<Number>(resCoord);
    }

}
