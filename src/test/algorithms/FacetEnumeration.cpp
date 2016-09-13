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

	TEST_F(FacetEnumerationTest, DegenerateEnumeration2) {
		// Actual (failing) problem from benchmark runs, which specifies an object described by 2 points in a 3D space.
		std::vector<Point<mpq_class>> points;
		points.push_back(Point<mpq_class>({mpq_class("1170371095970163531301353990512407462289424333177/11692013098647223345629478661730264157247460343808"), 0, 0}));
		points.push_back(Point<mpq_class>({mpq_class("2340742191940321312133937153702758040756082833417/11692013098647223345629478661730264157247460343808"), 0, 0}));

		ConvexHull<mpq_class> ch(points);
		ch.convexHullVertices();

		EXPECT_EQ(ch.getHsv().size(), 6);
		HPolytope<mpq_class> resContainer(ch.getHsv());
		for(const auto point : points) {
			EXPECT_TRUE(resContainer.contains(point));
		}
	}

	TEST_F(FacetEnumerationTest, DegenerateEnumeration3) {
		// Actual (failing) problem from benchmark runs.
		std::vector<Point<mpq_class>> points;
		points.push_back(Point<mpq_class>( { mpq_class("510") , mpq_class("20") , mpq_class("20") } ));
		points.push_back(Point<mpq_class>( { mpq_class("499997556421277873/980373000000000") , mpq_class("500001253523251079/24987506500000000") , mpq_class("500001253523251079/24987506500000000") } ));
		points.push_back(Point<mpq_class>( { mpq_class("499997556421277873/980373000000000") , mpq_class("500001253523251079/24987506500000000") , mpq_class("250000626774106751/12493753000000000") } ));
		points.push_back(Point<mpq_class>( { mpq_class("499997556421277873/980373000000000") , mpq_class("250000626774106751/12493753000000000") , mpq_class("500001253523251079/24987506500000000") } ));
		points.push_back(Point<mpq_class>( { mpq_class("499997556421277873/980373000000000") , mpq_class("250000626774106751/12493753000000000") , mpq_class("250000626774106751/12493753000000000") } ));
		points.push_back(Point<mpq_class>( { mpq_class("520") , mpq_class("20") , mpq_class("20") } ));
		points.push_back(Point<mpq_class>( { mpq_class("249998801730340251/480750500000000") , mpq_class("500001253523251079/24987506500000000") , mpq_class("500001253523251079/24987506500000000") } ));
		points.push_back(Point<mpq_class>( { mpq_class("249998801730340251/480750500000000") , mpq_class("500001253523251079/24987506500000000") , mpq_class("250000626774106751/12493753000000000") } ));
		points.push_back(Point<mpq_class>( { mpq_class("249998801730340251/480750500000000") , mpq_class("250000626774106751/12493753000000000") , mpq_class("500001253523251079/24987506500000000") } ));
		points.push_back(Point<mpq_class>( { mpq_class("249998801730340251/480750500000000") , mpq_class("250000626774106751/12493753000000000") , mpq_class("250000626774106751/12493753000000000") } ));

		ConvexHull<mpq_class> ch(points);
		ch.convexHullVertices();

		HPolytope<mpq_class> resContainer(ch.getHsv());
		for(const auto point : points) {
			EXPECT_TRUE(resContainer.contains(point));
		}
	}
