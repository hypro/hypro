#pragma once

#include "../../../util/adaptions_eigen/adaptions_eigen.h"
#include "../../../util/logging/Logger.h"
#include "../Quickhull.h"

namespace hypro {

template <typename Number, bool Euclidian>
class ExactQuickhull<Number, Euclidian>::FacetSpace {
	pointVector_t& points;
	dimension_t dimension;

  public:
	size_t firstInserted;
	size_t firstDeleted = 0;
	std::vector<facet_ind_t> deletedPositions{};

	facetVector_t facets{};

	explicit FacetSpace( pointVector_t& points, dimension_t dimension )
		: points( points )
		, dimension( dimension ){};

	// facet construction
	Facet& insertNew();

	/**
	 * Inserts a one dimensional facet that represents an interval bound at the given scalar.
	 * @param scalar The interval bound.
	 */
	void insertTrivialFacet( Number const scalar );

	/**
	 * Inserts a new facet in the given dimension, from a lower dimensional facet, by setting 'reducedDimension' to 0.
	 * @param other The facet to construct the new one from.
	 * @param newDimension The dimension of the new facet.
	 * @param reducedDimension The dimension to set to 0 in the new facet.
	 */
	void insertReduced( Facet const& other, dimension_t newDimension, dimension_t reducedDimension );

	/**
	 * Inserts a new facet that is defined by an existing one, except that the visiblePoint replaces the point at the specified index.
	 * @param other The existing facet to construct a new one from.
	 * @param visiblePoint The point to insert.
	 * @param insertAt The index to insert the visiblePoint at.
	 * @param containedPoint A point to use for orientation.
	 * @return The index where the visiblePoint was inserted.
	 */
	size_t insertConePart( facet_ind_t other_i, point_ind_t visiblePoint, size_t replaceAt );

	// facet modification
	void computeNormal( Facet& facet );
	void validateFacet( Facet& facet, point_t const& containedPoint, Facet const& adjacentFacet );
	void validateVertexContainment( Facet& facet );

	bool tryAddToOutsideSet( Facet& facet, point_ind_t point_i );
	void establishNeighborhood( facet_ind_t facet_i, facet_ind_t other_i );

	// facet queries

	// vector operations
	template <typename UnaryPredicate>
	facet_ind_t findFacet( UnaryPredicate predicate );

	void removeCoplanarFacets();
	void compressVector();
	void endModificationPhase();
	void deleteFacet( facet_ind_t facet_i );

	// Debug functions

#ifndef NDEBUG
	std::string printAll();
	std::string printFacet( Facet const& facet );
	void containsVertices( Facet& facet );
	void containsVertices( Facet& facet, Facet& currentFacet, bitset_t& visited );
	void containsAllPoints( Facet& facet, bool inverted = false );
#endif
  private:
	size_t copyVertices( Facet& facet, Facet const& other, point_ind_t visiblePoint, size_t replaceAt );
};
}  // namespace hypro

#include "FacetSpace.tpp"