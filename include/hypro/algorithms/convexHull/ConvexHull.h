#pragma once

#include "../../config.h"
#include "../../datastructures/Halfspace.h"
#include "../../datastructures/Point.h"
#include "vertexEnumeration.h"

namespace hypro {

/**
 * @brief      Class for Fukuda's reverse search.
 * @tparam     Number  The used number type.
 */
template <typename Number>
class ConvexHull {
  private:
	std::vector<Point<Number>> mPoints;			   ///< Vertices
	std::vector<vector_t<Number>> mCone;		   ///< Cone in case object is unbounded
	std::vector<vector_t<Number>> mLinealtySpace;  ///<
	std::vector<Halfspace<Number>> mConeHsv;	   ///< Half spaces representing a cone
	std::vector<Halfspace<Number>> mDualHsv;	   ///< Dual representation
	std::vector<Halfspace<Number>> mHsv;		   ///<
	vector_t<Number> mOffset;					   ///< translation applied to all vertices such that 0 is inside the polyhedron [based on original barycenter]

  public:
	/// default constructor
	ConvexHull() = default;
	/// copy constructor
	ConvexHull( const ConvexHull<Number>& _orig ) = default;
	/// constructor from a point set
	ConvexHull( const std::vector<Point<Number>> points );
	/// constructor from a point set and a cone
	ConvexHull( const std::vector<Point<Number>> points, const std::vector<vector_t<Number>> cone );
	/// constructor from a point set, a cone, and a lineality space
	ConvexHull( const std::vector<Point<Number>> points, const std::vector<vector_t<Number>> cone,
				const std::vector<vector_t<Number>> linealty );
	/// getter for the points
	std::vector<Point<Number>> getPoints() const;
	/// getter for the cone
	std::vector<vector_t<Number>> getCone() const;
	/// getter for the lineality space
	std::vector<vector_t<Number>> getLinealtySpace() const;
	/// getter for the half spaces defining the cone
	std::vector<Halfspace<Number>> getConeHsv() const;
	/// getter for the dual representation
	std::vector<Halfspace<Number>> getDualHsv() const;
	/// getter
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

	/// projection
	void projectOnLinealty();  // not used
};

}  // namespace hypro

#include "ConvexHull.tpp"
