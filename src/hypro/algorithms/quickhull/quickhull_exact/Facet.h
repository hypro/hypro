#pragma once

#include "util/unreachable.h"

namespace hypro {
/**
 * @brief Struct representing a facet in Euclidean space.
 * @tparam Number
 * @tparam Euclidian
 */
template <typename Number, bool Euclidian>
struct ExactQuickhull<Number, Euclidian>::Facet {
	Facet() = default;

	//modifiers
	/// Inverts the facet
	void invert();
	/// Sets normal vector orientation and normal vector?
	void setOrientation( point_t const& containedPoint, Facet const& adjacentFacet );

	//queries
	/// Returns signed distance from point to hyperplane
	Number distance( point_t const& point ) const;
	/// True if the passed point is above the facet (outside)
	bool visible( point_t const& vertex ) const;
	/// Returns index in the neighbor set of the passed facet
	size_t findNeighborIndex( facet_ind_t facet_i );

	//members
	std::vector<point_ind_t> mVertices;			 ///< Vertex cache
	std::vector<facet_ind_t> mNeighbors;		 ///< Neighbor cache
	std::vector<point_ind_t> mOutsideSet;		 ///< Outside vertices cache
	point_t mNormal;							 ///< Normal vector
	point_ind_t furthestPoint;					 ///< ???
	Number furthestPointDistance = Number( 0 );	 ///< ???
	Number mOffset = Number( 1000 );			 ///< Offset
};

}  // namespace hypro

#include "Facet.tpp"