/*
 * @file    NeighborhoodContainer.h
 * @author  Benedikt Seidl
 */

#pragma once

#include "../../datastructures/Vertex.h"

#include <map>

namespace hypro {

/**
 * @brief      A neighborhood container which maps points
 * to their set of neighbor points.
 */
class NeighborhoodContainer {
  public:
	using neighborhood = std::vector<Point<int> >;

  private:
	std::map<Point<int>, neighborhood> mNeighborhoods;

  public:
	NeighborhoodContainer() {}

	NeighborhoodContainer( const NeighborhoodContainer& copy ) {
		mNeighborhoods.insert( copy.mNeighborhoods.begin(), copy.mNeighborhoods.end() );
	}

	NeighborhoodContainer& operator=( const NeighborhoodContainer& orig ) = default;
	NeighborhoodContainer& operator=( NeighborhoodContainer&& orig ) = default;

	~NeighborhoodContainer() {}

	void clear() { mNeighborhoods.clear(); }

	bool empty() const { return mNeighborhoods.empty(); }

	/**
	 * Returns the points in the neighborhood.
	 *
	 * @param p the point
	 * @param pointself point is optionally an element of the returned vector
	 * @return Vector filled with neighbors in all dimensions
	 */
	neighborhood getNeighborhood( const Point<int>& p, bool pointself = false );

	/**
	 * Returns the points in the neighborhood, with one fixed dimension.
	 *
	 * @param p the point
	 * @param dimension the fixed dimension
	 * @param pointself point is optionally an element of the returned vector
	 * @return
	 */
	neighborhood getNeighborhoodForDimension( const Point<int>& p, const carl::Variable& dimension,
											  bool pointself = false );

	/**
	 * Moves all neighbors.
	 *
	 * @param p the point by which the neighbors should be moved
	 */
	// void moveNeighbors(const Point<int>& p);

  private:
	bool hasNeighborhood( const Point<int>& p ) const { return mNeighborhoods.find( p ) != mNeighborhoods.end(); }

	void calculateNeighborhood( const Point<int>& p );
};

}  // namespace hypro
