/**
 * The class which represents a box.
 *
 * @file Box.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since   2014-01-16
 * @version 2014-05-27
 */

#pragma once

#include <map>
#include <cassert>
#include <carl/interval/Interval.h>
#include "../GeometricObject.h"

namespace hypro {

template<typename Number>
class Box : hypro::GeometricObject<Number>
{
private:
    
public:
	typedef std::map<const carl::Variable, carl::Interval<Number> > intervalMap;
    typedef carl::Interval<Number> floatInterval;
	/***************************************************************************
	 * Members
	 **************************************************************************/
protected:
	intervalMap mBoundaries;
	
public:
	/***************************************************************************
	 * Constructors
	 **************************************************************************/
	
	/*
	 * Creates a box without any specifications
	 */
	Box() : mBoundaries()
	{}
        /*
         * Creates a copy of a box?
         * @param orig The box that's gonna be copied
         */
        Box(const Box& orig) : mBoundaries(orig.boundaries())
        {}
        
        /*
         * Creates a box by
         * @param var
         * @param val
         */
        Box(const carl::Variable& var, const floatInterval& val)
        {
            mBoundaries.insert(std::make_pair(var, val));
        }
        
        /*
         * Creates a box by
         * @param intervals
         */
        Box(const intervalMap& intervals)
        {
            mBoundaries.insert(intervals.begin(), intervals.end());
        }
        
        ~Box()
        {}
	
	/***************************************************************************
	 * Getters & setters
	 **************************************************************************/
	
    /*
     * @return
     */
	intervalMap& rBoundaries()
	{
        return mBoundaries;
	}
	
	/*
	 * @return
	 */
	intervalMap boundaries() const
	{
        return mBoundaries;
	}
	
	/**
	 * Inserts a new boundary for a variable.
	 * @param val Pair of Variable and Interval.
	 * @return True, if a new insertion has happened, else only update of an existing interval.
	 */
	bool insert(const std::pair<const carl::Variable, floatInterval >& val)
	{
		if(mBoundaries.find(val.first) == mBoundaries.end())
		{
			mBoundaries[val.first] = val.second;
			return true;
		}
		mBoundaries.at(val.first) = val.second;
		return false;
	}
	
	
    /*
     *@param var
     *@param val
     *@return
     */
	bool insert(const carl::Variable& var, const floatInterval& val)
	{
		if(mBoundaries.find(var) == mBoundaries.end())
		{
			mBoundaries[var] = val;
			return true;
		}
		mBoundaries.at(var) = val;
		return false;
	}
        

	/*
	 * Setter method for box boundaries
	 * @param boundaries Defines the new boundaries for the box
	 */
	void insert(const intervalMap& boundaries)
	{
            mBoundaries.insert(boundaries.begin(), boundaries.end());
	}
	
    /*
     * Checks if the box has the same dimension as the variable.
     * @param var
     * @return
     */
	bool hasDimension(const carl::Variable& var) const
	{
		return mBoundaries.find(var) != mBoundaries.end();
	}
            
	/**
	 * Checks if the box has the same dimensions as this box.
	 * The number of dimensions has to be equal as well as the actual
	 * variables used for those dimensions.
	 * 
	 * @param p
	 * @return True, if all dimension variables are equal
	 */
	bool haveSameDimensions(const Box<Number>& b) const
	{
		if (dimension() != b.dimension())
		{
			return false;
		}
		for (auto pointIt : mBoundaries)
		{
			if ( !b.hasDimension(pointIt.first))
			{
				return false;
			}
		}
		return true;
	}
	
	floatInterval* pInterval(const carl::Variable& var);
	floatInterval interval(const carl::Variable& var) const;
	
	/*
	 * @return
	 */
	bool isEmpty() const
	{
		if(mBoundaries.size() == 0)
			return true;
		for(auto interval : mBoundaries)
		{
			if(interval.second.isEmpty())
			{
				return true;
			}
		}
		return false;
	}

	/*
	 * @return
	 */
	Point<Number> max() const
	{
		typename Point<Number>::coordinateMap coordinates;
		for(auto interval : mBoundaries)
		{
			coordinates.insert(std::make_pair(interval.first, interval.second.upper()));
		}
		return Point<Number>(coordinates);
	}
        
	/*
	 * @return
	 */
	Point<Number> min() const
	{
		typename Point<Number>::coordinateMap coordinates;
		for(auto interval : mBoundaries)
		{
			coordinates.insert(std::make_pair(interval.first, interval.second.lower()));
		}
		return Point<Number>(coordinates);
	}

	/**
	 * Checks if two boxes are equal
	 * @param b1 Contains the first box
	 * @param b2 Contains the second box
	 * @return true, if they are equal.
	 */
	friend bool operator==(const Box<Number> & b1, const Box<Number> & b2)
	{
		if(b1.dimension() != b2.dimension()) return false;
		for (auto intervalIt : b1.mBoundaries)
		{
			if (!b2.hasDimension(intervalIt.first) || intervalIt.second != b2.mBoundaries.at(intervalIt.first)) return false;
		}
		return true;
	}

	/**
	 * @param b1
	 * @param b2
	 * @return true. if they are not equal
	 */
	friend bool operator!=(const Box<Number> & b1, const Box<Number> & b2)
	{
		return !(b1 == b2);
	}

	/*
	 *@param rhs
	 *@return
	 */
	Box<Number>& operator= (const Box<Number>& rhs) 
	{ 
		if (*this != rhs)
		{
			this->mBoundaries.clear();
			intervalMap tmp = rhs.boundaries();
			this->mBoundaries.insert(tmp.begin(), tmp.end());
		} 
		return *this;
	}

	/**
	 *
	 * @param ostr
	 * @param b
	 * @return
	 */
	friend std::ostream & operator<< (std::ostream& ostr, const Box<Number>& b)
	{
		ostr << "{";		
		for (auto intervalIt : b.mBoundaries) {
			if (intervalIt != *(b.mBoundaries.begin())) {
				ostr << ";";
			}
			ostr << " " << intervalIt.first << " " << intervalIt.second;
		}		
		ostr << " }";
		return ostr;
	}
        
        
	/***************************************************************************
	 * General interface
	 **************************************************************************/
	
	unsigned int dimension() const
	{
            return mBoundaries.size();
	}
	
	bool linearTransformation(Box& result /*, ... */) const;
	bool minkowskiSum(Box& result, const Box& rhs) const;
	bool intersect(Box& result, const Box& rhs) const;
	bool hull(Box& result) const;
	bool contains(const Point<Number>& point) const;
	bool unite(Box& result, const Box& rhs) const;
	
	void clear();
};

}
#include "Box.tpp"
