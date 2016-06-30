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
		std::vector<Halfspace<Number>> mConeHsv;
		std::vector<Halfspace<Number>> mDualHsv;
		std::vector<Halfspace<Number>> mHsv;
		vector_t<Number> mOffset;
		
	public:
		ConvexHull() = default;
		ConvexHull(const ConvexHull<Number>& _orig) = default;
		ConvexHull(const std::vector<Point<Number>> points);
		ConvexHull(const std::vector<Point<Number>> points, const std::vector<vector_t<Number>> cone);		
		
		std::vector<Point<Number>> getPoints() const;
		std::vector<vector_t<Number>> getCone() const;
		std::vector<Halfspace<Number>> getConeHsv() const;
		std::vector<Halfspace<Number>> getDualHsv() const;
		std::vector<Halfspace<Number>> getHsv() const;

		bool findOffset();

		void toDual();
		void toPrimal(const std::vector<Point<Number>> points);
		void convexHullVertices();
		void conicHull();
		void polyhedriclHull();
		
		void translateHsv();

};

}

#include "ConvexHull.tpp"
