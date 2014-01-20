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

#include <Eigen/dense>
#include "../../datastructures/Point.h"

template<typename Number>
class Box : GeometricObject<Box, Number>
{
	/***************************************************************************
	 * Members
	 **************************************************************************/
protected:
	MatrixXd mBoundaries;
	
public:
	/***************************************************************************
	 * Constructors
	 **************************************************************************/
	
	Box();
	
	Box(unsigned dimension) : mBoundaries(dimension)
	{}
	
	/***************************************************************************
	 * General interface
	 **************************************************************************/
	
	unsigned int get_dimension() const;
	
	void linear_transformation(Box& result /*, ... */) const;
	void minkowski_sum(Box& result, const Box& rhs) const;
	bool intersect(Box& result, const Box& rhs) const;
	void hull(Box& result, const Box& rhs) const;
	bool contains(const Point<Number>& point) const;
	void unite(Box& result, const Box& rhs) const;
};


