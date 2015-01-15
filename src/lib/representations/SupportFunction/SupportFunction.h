/* This header implements the support functions defined by Girard et al.
 * @file   SupportFunction.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since	2015-01-15
 * @version	2015-01-15
 */

#pragma once

#include "../../config.h"
#include "../../datastructures/Point.h"

namespace hypro {

// Eigen less operator for vectors
template<typename Number>
struct vecLess {
	bool operator() (const vector_t<Number>& lhs, const vector_t<Number>& rhs) const
	{
	assert(lhs.rows() == rhs.rows());
	unsigned pos = 0;
	while(pos < lhs.rows() && lhs(pos) == rhs(pos) )
		++pos;
	
	return (pos != lhs.rows() && lhs(pos) < rhs(pos) );
	}
	typedef vector_t<Number> first_argument_type;
	typedef vector_t<Number> second_argument_type;
	typedef bool result_type;
};



	
	
template<typename Number>
class SupportFunction {
	typedef vector_t<Number> direction;
	typedef std::map<direction, Number, vecLess<Number>> directionValueMapping;
	typedef std::set<direction, vecLess<Number>> directionSet;
	private:
		directionValueMapping mDirections;

	public:
		SupportFunction();
		SupportFunction( const SupportFunction<Number>& _orig );
		SupportFunction( SupportFunction<Number>&& ) = default;
		
		SupportFunction<Number>& operator= ( const SupportFunction<Number>& ) = default;
		SupportFunction<Number>& operator= ( SupportFunction<Number>&& ) = default;
		
		virtual ~SupportFunction(){}
		
		directionValueMapping content() const;
		directionValueMapping& rContent();
		
		directionSet directions() const;
		std::pair<const Number&,bool> distance(const direction& _direction) const;
		
		void addDirection(const direction& _direction, const Number& _distance);
		void addDirection(const Point<Number>& _direction, const Number& _distance);
};
} // namespace
#include "SupportFunction.tpp"