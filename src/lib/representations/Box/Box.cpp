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

unsigned int get_dimension() const;

template<typename Number>
void Box<Number>::linear_transformation(Box<Number>& result /*, ... */) const
{
	
}

template<typename Number>
void Box<Number>::minkowski_sum(Box<Number>& result, const Box<Number>& rhs) const
{
	
}

template<typename Number>
bool Box<Number>::intersect(Box<Number>& result, const Box<Number>& rhs) const
{
	
}

template<typename Number>
void Box<Number>::hull(Box<Number>& result, const Box<Number>& rhs) const
{
	
}

template<typename Number>
bool Box<Number>::contains(const Point <Number> point) const
{
	
}

template<typename Number>
void Box<Number>::unite(Box<Number>& result, const Box<Number>& rhs) const
{
	
}
