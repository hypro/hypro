#pragma once

#include "../../config.h"
#include "../../datastructures/Halfspace.h"
#include "../../datastructures/Point.h"
#include "vertexEnumeration.h"

namespace hypro {

/**
 * @brief      Class for convex hull computation.
 * @tparam     Number  The used number type.
 */
template <typename Number>
class ConvexHull {
  private:
	std::vector<Point<Number>> mPoints;
	std::vector<vector_t<Number>> mCone;
	std::vector<vector_t<Number>> mLinealtySpace;
	std::vector<Halfspace<Number>> mConeHsv;
	std::vector<Halfspace<Number>> mDualHsv;
	std::vector<Halfspace<Number>> mHsv;
	vector_t<Number> mOffset;  // translation applied to all vertices such that 0 is inside the polyhedron [based on original barycenter]

  public:
	ConvexHull() = default;
	ConvexHull( const ConvexHull<Number>& _orig ) = default;
	ConvexHull( const std::vector<Point<Number>> points );
	ConvexHull( const std::vector<Point<Number>> points, const std::vector<vector_t<Number>> cone );
	ConvexHull( const std::vector<Point<Number>> points, const std::vector<vector_t<Number>> cone,
				const std::vector<vector_t<Number>> linealty );

	std::vector<Point<Number>> getPoints() const;
	std::vector<vector_t<Number>> getCone() const;
	std::vector<vector_t<Number>> getLinealtySpace() const;
	std::vector<Halfspace<Number>> getConeHsv() const;
	std::vector<Halfspace<Number>> getDualHsv() const;
	std::vector<Halfspace<Number>> getHsv() const;

	/**
		 * @brief substracts to every point the barycenter of all the group
		 */
	void findOffset();

	/**
		 * @brief fils mDualHsv with the dual of the points in mPoints
		 */
	void toDual();

	/**
		 * @brief puts the dual of the points in "points" in mHsv
		 */
	void toPrimal( const std::vector<Point<Number>> points );

	/**
		 * @brief finds the convex hull of the vertices in mPoints by Fukuda
		 */
	void convexHullVertices();

	/**
		 * @brief finds the conic hull of the vectors in mCones.
		 */
	void conicHull();

	/**
		 * @brief Finds the convex hull of a polyhedron.
		 */
	void polyhedriclHull();

	/**
		 * @brief modify the hyperplanes in mHsv to take ino account the offset
		 * -> translate back/revert moving to the barycenter.
		 */
	void translateHsv();

	void projectOnLinealty();  //not used
};

}  // namespace hypro

#include "ConvexHull.tpp"
