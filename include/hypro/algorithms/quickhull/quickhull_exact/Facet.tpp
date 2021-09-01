//
// Created by leander.behr on 11/11/19.
//

#include "Facet.h"

namespace hypro {
// modifiers
template <typename Number, bool Euclidian>
void ExactQuickhull<Number, Euclidian>::Facet::invert() {
	mNormal *= -1;
	mOffset *= -1;
}

template <typename Number, bool Euclidian>
void ExactQuickhull<Number, Euclidian>::Facet::setOrientation( point_t const& containedPoint, Facet const& adjacentFacet ) {
	// Set orientation of normal
	Number distance = this->distance( containedPoint );

	if ( distance > 0 ) {
		invert();
	} else if ( distance == 0 ) {
		mNormal = adjacentFacet.mNormal;
		mOffset = adjacentFacet.mOffset;
	}
}

// queries
template <typename Number, bool Euclidian>
Number ExactQuickhull<Number, Euclidian>::Facet::distance( point_t const& point ) const {
	if constexpr ( Euclidian ) {
		return point.dot( mNormal ) - mOffset;
	} else {
		Number dotProd = point.head( point.rows() - 1 ).dot( mNormal ) - point[point.rows() - 1] * mOffset;
		return dotProd;
	}
}

template <typename Number, bool Euclidian>
bool ExactQuickhull<Number, Euclidian>::Facet::visible( point_t const& vertex ) const {
	return distance( vertex ) > Number( 0 );
}

template <typename Number, bool Euclidian>
size_t ExactQuickhull<Number, Euclidian>::Facet::findNeighborIndex( facet_ind_t facet_i ) {
	for ( size_t neighbor_pos = 0; neighbor_pos < mNeighbors.size(); ++neighbor_pos ) {
		if ( mNeighbors[neighbor_pos] == facet_i ) return neighbor_pos;
	}
	assert( false );
	// This function is marked as noreturn and thus signals the compiler that the end of the function is not supposed to be reached.
	unreachable();
}
}  // namespace hypro