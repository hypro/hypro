#include "gtest/gtest.h"
#include "../defines.h"
#include "../../src/lib/algorithms/convexHull/ConvexHull.h"
#include "../../src/lib/representations/GeometricObject.h"

#include "../../src/lib/config.h"

using namespace hypro;

class FacetEnumerationTest : public ::testing::Test
{
protected:

	virtual void SetUp()
	{}

	virtual void TearDown()
	{}

public:
	FacetEnumerationTest(){}
	~FacetEnumerationTest(){}
	};

	TEST_F(FacetEnumerationTest, Constructor) {
		std::vector<Point<mpq_class>> points;
		points.push_back(Point<mpq_class>({1,0}));

		ConvexHull<mpq_class> def;
		ConvexHull<mpq_class> degenerate(points);
		EXPECT_EQ(degenerate.getPoints().size(), 1);

		points.push_back(Point<mpq_class>({0,0}));
		points.push_back(Point<mpq_class>({0,1}));
		points.push_back(Point<mpq_class>({1,1}));

		ConvexHull<mpq_class> box(points);
		ConvexHull<mpq_class> boxCopy(box);

		EXPECT_EQ(degenerate.getPoints().size(), 1);
		EXPECT_EQ(box.getPoints().size(), 4);
		EXPECT_EQ(boxCopy.getPoints().size(), 4);

		SUCCEED();
	}

	TEST_F(FacetEnumerationTest, Access) {
	}

	TEST_F(FacetEnumerationTest, SimpleEnumeration) {
		std::vector<Point<mpq_class>> points;
		points.push_back(Point<mpq_class>({1,0}));
		points.push_back(Point<mpq_class>({0,0}));
		points.push_back(Point<mpq_class>({0,1}));
		points.push_back(Point<mpq_class>({1,1}));
		ConvexHull<mpq_class> box(points);
		box.convexHullVertices();
		EXPECT_EQ(box.getHsv().size(), 4);
		HPolytope<mpq_class> resContainer(box.getHsv());
		for(const auto point : points) {
			EXPECT_TRUE(resContainer.contains(point));
		}
	}

	TEST_F(FacetEnumerationTest, SimpleRedundantEnumeration) {
		std::vector<Point<mpq_class>> points;
		points.push_back(Point<mpq_class>({1,0}));
		points.push_back(Point<mpq_class>({0,0}));
		points.push_back(Point<mpq_class>({0,1}));
		points.push_back(Point<mpq_class>({1,1}));
		points.push_back(Point<mpq_class>({1,0}));
		points.push_back(Point<mpq_class>({carl::rationalize<mpq_class>(0.5),1}));
		points.push_back(Point<mpq_class>({carl::rationalize<mpq_class>(0.5),carl::rationalize<mpq_class>(0.5)}));
		points.push_back(Point<mpq_class>({1,1}));
		points.push_back(Point<mpq_class>({1,1}));
		ConvexHull<mpq_class> box(points);
		box.convexHullVertices();
		EXPECT_EQ(box.getHsv().size(), 4);
		HPolytope<mpq_class> resContainer(box.getHsv());
		for(const auto point : points) {
			EXPECT_TRUE(resContainer.contains(point));
		}
	}

	TEST_F(FacetEnumerationTest, DegenerateEnumeration) {
		// Test a pyramid with quadratic foundation in 3D space
		std::vector<Point<mpq_class>> points;
		points.push_back(Point<mpq_class>({1,0,1}));
		points.push_back(Point<mpq_class>({1,0,-1}));
		points.push_back(Point<mpq_class>({-1,0,1}));
		points.push_back(Point<mpq_class>({-1,0,-1}));
		points.push_back(Point<mpq_class>({0,1,0}));
		ConvexHull<mpq_class> box(points);
		box.convexHullVertices();
		EXPECT_EQ(box.getHsv().size(), 5);
		HPolytope<mpq_class> resContainer(box.getHsv());
		for(const auto point : points) {
			EXPECT_TRUE(resContainer.contains(point));
		}
	}
