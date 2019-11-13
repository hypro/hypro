#pragma once
#include "../../types.h"

#include <boost/variant.hpp>
#include <boost/variant/static_visitor.hpp>

namespace hypro {

template <typename State>
struct setCreationVisitor : public boost::static_visitor<typename State::repVariant> {
	matrix_t<typename State::NumberType> mMatrix;
	vector_t<typename State::NumberType> mVector;

	setCreationVisitor() = delete;
	setCreationVisitor( const matrix_t<typename State::NumberType>& constraints, const vector_t<typename State::NumberType>& constants )
		: mMatrix( constraints )
		, mVector( constants ) {}

	template <typename SElement>
	typename State::repVariant operator()( const SElement& se ) {
		return SElement::representationType( mMatrix, mVector );
	}
};

}  // namespace hypro