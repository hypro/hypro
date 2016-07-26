#pragma once

#include "../../config.h"
#include "../../datastructures/Point.h"
#include "../../datastructures/Halfspace.h"
#include "vertexEnumeration.h"

namespace hypro {

template<typename Number>
class ConvexHull {
	private:
		std::vector<Point<Number>> mPoints;
		std::vector<vector_t<Number>> mCone;
		std::vector<vector_t<Number>> mLinealtySpace;
		std::vector<Halfspace<Number>> mConeHsv;
		std::vector<Halfspace<Number>> mDualHsv;
		std::vector<Halfspace<Number>> mHsv;
		vector_t<Number> mOffset;//translqtion applied to all ertices such that 0 is inside the polyhedron
		
	public:
		ConvexHull() = default;
		ConvexHull(const ConvexHull<Number>& _orig) = default;
		ConvexHull(const std::vector<Point<Number>> points);
		ConvexHull(const std::vector<Point<Number>> points, const std::vector<vector_t<Number>> cone);	
		ConvexHull(const std::vector<Point<Number>> points, const std::vector<vector_t<Number>> cone, 
								const std::vector<vector_t<Number>> linealty);		
		
		std::vector<Point<Number>> getPoints() const;
		std::vector<vector_t<Number>> getCone() const;
		std::vector<vector_t<Number>> getLinealtySpace() const;
		std::vector<Halfspace<Number>> getConeHsv() const;
		std::vector<Halfspace<Number>> getDualHsv() const;
		std::vector<Halfspace<Number>> getHsv() const;

		void findOffset();
		/**
		 * @brief substracts to every point the barycenter of all the group
		 */

		void toDual();
		/**
		 * @brief fils mDualHsv with the dual of the points in mPoints
		 */
		void toPrimal(const std::vector<Point<Number>> points);
		/**
		 * @brief puts the dual of the points in "points" in mHsv 
		 */
		void convexHullVertices();
		/**
		 * @brief finds the convex hull of the vertices in mPoints by Fukuda
		 */
		void conicHull();
		/**
		 * @brief finds the conic hull of the vectors in mCones.
		 */
		void polyhedriclHull();
		/**
		 * @brief Finds the convex hull of a polyhedron.
		 */
		
		void translateHsv();
		/**
		 * @brief modify the hyperplanes in mHsv to take ino account the offset
		 */
		void projectOnLinealty();//not used

};

}

#include "ConvexHull.tpp"
