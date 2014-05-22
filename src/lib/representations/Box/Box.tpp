/**
 * Implementation of the box.
 *
 * @file Box.tpp
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since   2014-01-16
 * @version 2014-02-11
 */

#include "Box.h"

namespace hypro {
	
template<typename Number>
carl::Interval<carl::FLOAT_T<Number>>& Box<Number>::rInterval(const carl::Variable& var)
{
    auto intervalIt = mBoundaries.find(var);
    if( intervalIt == mBoundaries.end() )
    {
        assert(false);
        return carl::Interval<Number>();
    }
    else
    {
        return (*intervalIt).second;
    }
}

template<typename Number>
carl::Interval<carl::FLOAT_T<Number>> Box<Number>::interval(const carl::Variable& var) const
{
    auto intervalIt = mBoundaries.find(var);
    if( intervalIt == mBoundaries.end() )
    {
        assert(false);
        return carl::Interval<Number>();
    }
    else
    {
        return (*intervalIt).second;
    }
}

template<typename Number>
bool Box<Number>::linearTransformation(Box<Number>& result /*, ... */) const
{
    return false; // @todo
}

template<typename Number>
bool Box<Number>::minkowskiSum(Box<Number>& result, const Box<Number>& rhs) const
{
    result.clear();
    for (auto intervalIt = mBoundaries.begin(); intervalIt != mBoundaries.end(); ++intervalIt)
    {
        if (!rhs.hasDimension((*intervalIt).first))
        {
            result.clear();
            return false;
        }
        result.insert( std::make_pair((*intervalIt).first, (*intervalIt).second.add(rhs.interval((*intervalIt).first)) ));
    }
    return true;
}

template<typename Number>
bool Box<Number>::intersect(Box<Number>& result, const Box<Number>& rhs) const
{
    result.clear();
    for (auto intervalIt = mBoundaries.begin(); intervalIt != mBoundaries.end(); ++intervalIt)
    {
        if (!rhs.hasDimension((*intervalIt).first))
        {
            result.clear();
            return false;
        }
        std::cout << rhs.interval((*intervalIt).first) << std::endl;
        carl::Interval<carl::FLOAT_T<Number>> res = (*intervalIt).second.intersect(rhs.interval((*intervalIt).first));
        if( res.isEmpty() )
        {
            result.clear();
            return false;
        }
        result.insert( std::make_pair((*intervalIt).first, res ) );
    }
    return true;
}

template<typename Number>
bool Box<Number>::hull(Box<Number>& result) const
{
    result = *this;
    return true;
}

template<typename Number>
bool Box<Number>::contains(const Point<Number>& point) const
{
    if( this->dimension() > point.dimension() )
        return false;
    
    for(auto interval : mBoundaries)
    {
        if( !interval.second.contains(point.at(interval.first).value()))
            return false;
    }
    return true;
}

template<typename Number>
bool Box<Number>::unite(Box<Number>& result, const Box<Number>& rhs) const
{
    for(auto intervalIt = mBoundaries.begin(); intervalIt != mBoundaries.end(); ++intervalIt)
    {
        if(!rhs.hasDimension((*intervalIt).first))
        {
            result.clear();
            return false;
        }
        Number lowerMin = (*intervalIt).second.lower() < rhs.interval((*intervalIt).first).lower() ? (*intervalIt).second.lower() : rhs.interval((*intervalIt).first).lower();
        Number upperMax = (*intervalIt).second.upper() > rhs.interval((*intervalIt).first).upper() ? (*intervalIt).second.upper() : rhs.interval((*intervalIt).first).upper();
        carl::BoundType lowerType = carl::getWeakestBoundType((*intervalIt).second.lowerBoundType(), rhs.interval((*intervalIt).first).lowerBoundType());
        carl::BoundType upperType = carl::getWeakestBoundType((*intervalIt).second.upperBoundType(), rhs.interval((*intervalIt).first).upperBoundType());
        result.insert( std::make_pair(lowerMin, carl::Interval<Number>( lowerMin, lowerType, upperMax, upperType )) );
    }
    return true;
}

template<typename Number>
void Box<Number>::clear()
{
    mBoundaries.erase(mBoundaries.begin(), mBoundaries.end());
}
	
}
