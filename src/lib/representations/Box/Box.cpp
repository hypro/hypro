/**
 * Implementation of the box.
 *
 * @file Box.cpp
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since	2014-01-16
 * @version 2014-01-16
 */

#include "Box.h"

template<typename Number>
carl::Interval<Number>& Box<Number::rInterval(const carl::Variable& var)
{
	auto intervalIt = mBoundaries.find(var);
	if( intervalIt == mBoundaries.end() )
	{
		assert(false);
		return carl::Interval<Number>();
	}
	else
	{
		return (intervalIt).second;
	}
}

template<typename Number>
carl::Interval<Number> Box<Number>::interval(const carl::Variable& var) const
{
	auto intervalIt = mBoundaries.find(var);
	if( intervalIt == mBoundaries.end() )
	{
		assert(false);
		return carl::Interval<Number>();
	}
	else
	{
		return (intervalIt).second;
	}
}

template<typename Number>
void Box<Number>::linear_transformation(Box<Number>& result /*, ... */) const
{
	
}

template<typename Number>
bool Box<Number>::minkowski_sum(Box<Number>& result, const Box<Number>& rhs) const
{
	result.clear();
	for (auto intervalIt = mBoundaries.begin(); intervalIt != mBoundaries.end(); ++intervalIt)
	{
		if (!rhs.hasVariable((*intervalIt).first))
		{
			result.clear();
			return false;
		}
		result.insert( std::make_pair((*intervalIt).first), (*intervalIt).second.add(rhs.interval((*intervalIt).first)) );
	}
	return true;
}

template<typename Number>
bool Box<Number>::intersect(Box<Number>& result, const Box<Number>& rhs) const
{
	result.clear();
	for (auto intervalIt = mBoundaries.begin(); intervalIt != mBoundaries.end(); ++intervalIt)
	{
		if (!rhs.hasVariable((*intervalIt).first))
		{
			result.clear();
			return false;
		}
		result.insert( std::make_pair((*intervalIt).first), (*intervalIt).second.intersect(rhs.interval((*intervalIt).first)) );
	}
	return true;
}

template<typename Number>
bool Box<Number>::hull(Box<Number>& result) const
{
	
}

template<typename Number>
bool Box<Number>::contains(const Point <Number> point) const
{
	
}

template<typename Number>
bool Box<Number>::unite(Box<Number>& result, const Box<Number>& rhs) const
{
	
}

template<typename Number>
void Box<Number>::clear()
{
	mBoundaries.erase(mBoundaries.begin(), mBoundaries.end());
}
