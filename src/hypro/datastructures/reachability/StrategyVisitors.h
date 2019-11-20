#pragma once
#include "../../types.h"

#include <variant>
namespace hypro {

template <typename State>
struct setCreationVisitor {
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
