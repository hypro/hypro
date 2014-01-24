/**
 * The class which represents a box.
 *
 * @file Box.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since	2014-01-16
 * @version 2014-01-16
 */

#pragma once

//‚#include <Eigen/dense>
#include <map>
#include <cassert>
#include "../../datastructures/Point.h"
#include "../GeometricObject.h"
#include <carl/core/Variable.h>
#include <carl/interval/Interval.h>

namespace hypro {

template<typename Number>
class Box : hypro::GeometricObject<Box<Number>, Number>
{
	/***************************************************************************
	 * Members
	 **************************************************************************/
protected:
	std::map<carl::Variable, carl::Interval<Number>> mBoundaries;
	
public:
	/***************************************************************************
	 * Constructors
	 **************************************************************************/
	
	Box();
	
	/***************************************************************************
	 * Getters & setters
	 **************************************************************************/
	
	std::map<carl::Variable, carl::Interval<Number>>& rBoundaries()
	{
		return mBoundaries;
	}
	
	std::map<carl::Variable, carl::Interval<Number>> boundaries()
	{
		return mBoundaries;
	}
	
	/**
	 * Inserts a new boundary for a variable.
	 * @param val Pair of Variable and Interval.
	 * @return True, if a new insertion has happened, else only update of an existing interval.
	 */
	bool insert(const std::pair<carl::Variable, carl::Interval<Number>> val)
	{
		if(mBoundaries.find(val.first) == mBoundaries.end())
		{
			mBoundaries[val.first] = val.second;
			return true;
		}
		mBoundaries.at(val.first) = val.second;
		return false;
	}
	
	bool hasVariable(const carl::Variable& var)
	{
		return mBoundaries.find(var) != mBoundaries.end();
	}
	
	carl::Interval<Number>& rInterval(const carl::Variable& var);
	carl::Interval<Number> interval(const carl::Variable& var) const;
	
	/***************************************************************************
	 * General interface
	 **************************************************************************/
	
	unsigned int get_dimension() const
	{
		return mBoundaries.size();
	}
	
	bool linear_transformation(Box& result /*, ... */) const;
	bool minkowski_sum(Box& result, const Box& rhs) const;
	bool intersect(Box& result, const Box& rhs) const;
	bool hull(Box& result) const;
	bool contains(const Point<Number>& point) const;
	bool unite(Box& result, const Box& rhs) const;
	
	void clear();
};

}
