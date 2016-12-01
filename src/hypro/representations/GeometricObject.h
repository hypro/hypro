/**
 * @file GeometricObject.h
 */

#pragma once

#define INCL_FROM_GOHEADER true

#include "types.h"
#include "flags.h"
#include "../config.h"
#include "util/adaptions_eigen/adaptions_eigen.h"
#include "util/logging/Logger.h"

namespace hypro {

/**
 * @brief      Forward declaration of class Point.
 * @tparam     Number  The used number type.
 */
template<typename Number>
class Point;

/**
 * @brief      Forward declaration of class Halfspace.
 * @tparam     Number  The used number type.
 */
template<typename Number>
class Halfspace;

/**
 * @brief      Purely virtual class defining a common interface for geometric objects.
 * @tparam     Number  The used number type.
 */
template<typename Number, typename DerivedShape>
class GeometricObject {

public:
	virtual ~GeometricObject(){}

	virtual std::size_t dimension() const = 0;

	virtual std::pair<bool, DerivedShape> satisfiesHalfspace( const Halfspace<Number>& rhs ) const = 0;
	virtual std::pair<bool, DerivedShape> satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const = 0;
	virtual DerivedShape project(const std::vector<unsigned>& dimensions) const = 0;
	// virtual GeometricObject<Number> linearTransformation( const matrix_t<Number>& A ) const = 0;
	// virtual GeometricObject<Number> affineTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const = 0;
	virtual DerivedShape minkowskiSum( const DerivedShape& rhs ) const = 0;
	// virtual DerivedShape intersect( const DerivedShape& rhs ) const = 0;
	virtual DerivedShape intersectHalfspace( const Halfspace<Number>& rhs ) const = 0;
	virtual DerivedShape intersectHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const = 0;
	virtual bool contains( const Point<Number>& point ) const = 0;
	//virtual bool contains( const vector_t<Number>& vec ) const = 0;
	//virtual bool contains( const DerivedShape& rhs ) const = 0;
	virtual DerivedShape unite( const DerivedShape& rhs ) const = 0;
	//virtual DerivedShape unite( const std::vector<DerivedShape>& rhs ) const = 0;

};

} // namespace hypro

#include "conversion/Converter.h"
