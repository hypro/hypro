/**
 * Testfile reproducing the example given at the end of the Avis and Fukuda paper.
 */

#include "gtest/gtest.h"
#include "../defines.h"
#include "../../src/lib/util/vertexEnumeration.h"

#include "../../src/lib/config.h"
#include "../../src/lib/representations/Polytope/Polytope.h"
#include "../../src/lib/datastructures/Point.h"
#include "../../src/lib/datastructures/Facet.h"
#include "../../src/lib/datastructures/Ridge.h"
#include "../../src/lib/util/convexHull.h"

template<typename Number>
class VertexEnumerationTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		hypro::matrix_t<Number> a = hypro::matrix_t<Number>(5,2);
		a << 1,3,5,1,3,2,-1,-3,-2,1;

		hypro::vector_t<Number> b = hypro::vector_t<Number>(5);
		b << 4,5,2,1,2;

		initial = hypro::Dictionary<Number>(a,b);
	}

	virtual void TearDown()
	{}

	hypro::Dictionary<Number> initial;
};

TYPED_TEST(VertexEnumerationTest, DictionaryAccess)
{
	std::map<std::size_t, std::size_t> expectedBasis;
	expectedBasis[1] = 0;
	expectedBasis[2] = 1;
	expectedBasis[3] = 2;

	EXPECT_EQ(expectedBasis, this->initial.basis());

	std::map<std::size_t, std::size_t> expectedCoBasis;
	expectedCoBasis[4] = 1;
	expectedCoBasis[5] = 2;

	EXPECT_EQ(expectedCoBasis, this->initial.cobasis());
}

TYPED_TEST(VertexEnumerationTest, DictionaryModification)
{

}

TYPED_TEST(VertexEnumerationTest, DictionaryPivot)
{

}

/*
 * Test simplex algorithm - constaints->vertices
 */
TYPED_TEST(VertexEnumerationTest, ComputeVertices) {
	// unity box in 3D
	hypro::matrix_t<TypeParam> boxConstraints = hypro::matrix_t<TypeParam>(6,3);
	boxConstraints << 1,0,0,
					 -1,0,0,
					  0,1,0,
					  0,-1,0,
					  0,0,1,
					  0,0,-1;

	hypro::vector_t<TypeParam> boxConstants = hypro::vector_t<TypeParam>(6);
	boxConstants << 1,1,1,1,1,1;

	hypro::Dictionary<TypeParam> boxDictionary(boxConstraints, boxConstants);
	std::vector<hypro::Point<TypeParam>> boxVertices = boxDictionary.search();

	EXPECT_TRUE( std::find(boxVertices.begin(), boxVertices.end(), hypro::Point<TypeParam>({1,1,1})) != boxVertices.end() );
	EXPECT_TRUE( std::find(boxVertices.begin(), boxVertices.end(), hypro::Point<TypeParam>({1,1,-1})) != boxVertices.end() );
	EXPECT_TRUE( std::find(boxVertices.begin(), boxVertices.end(), hypro::Point<TypeParam>({1,-1,1})) != boxVertices.end() );
	EXPECT_TRUE( std::find(boxVertices.begin(), boxVertices.end(), hypro::Point<TypeParam>({1,-1,-1})) != boxVertices.end() );
	EXPECT_TRUE( std::find(boxVertices.begin(), boxVertices.end(), hypro::Point<TypeParam>({-1,1,1})) != boxVertices.end() );
	EXPECT_TRUE( std::find(boxVertices.begin(), boxVertices.end(), hypro::Point<TypeParam>({-1,1,-1})) != boxVertices.end() );
	EXPECT_TRUE( std::find(boxVertices.begin(), boxVertices.end(), hypro::Point<TypeParam>({-1,-1,1})) != boxVertices.end() );
	EXPECT_TRUE( std::find(boxVertices.begin(), boxVertices.end(), hypro::Point<TypeParam>({-1,-1,-1})) != boxVertices.end() );

	// pyramid with quadratic bottom -> test towards degenerated vertices.
	hypro::matrix_t<TypeParam> pyramidConstraints = hypro::matrix_t<TypeParam>(5,3);
	pyramidConstraints << 1,1,0,
					 -1,1,0,
					  0,1,1,
					  0,1,-1,
					  0,-1,0;

	hypro::vector_t<TypeParam> pyramidConstants = hypro::vector_t<TypeParam>(5);
	pyramidConstants << 1,1,1,1,0;

	hypro::Dictionary<TypeParam> pyramidDictionary(pyramidConstraints, pyramidConstants);
	std::vector<hypro::Point<TypeParam>> pyramidVertices = pyramidDictionary.search();

	std::cout << "Pyramid vertices: " << std::endl;
	for(const auto& vertex : pyramidVertices)
		std::cout << vertex << std::endl;

	EXPECT_TRUE( std::find(pyramidVertices.begin(), pyramidVertices.end(), hypro::Point<TypeParam>({1,0,1})) != pyramidVertices.end() );
	EXPECT_TRUE( std::find(pyramidVertices.begin(), pyramidVertices.end(), hypro::Point<TypeParam>({1,0,-1})) != pyramidVertices.end() );
	EXPECT_TRUE( std::find(pyramidVertices.begin(), pyramidVertices.end(), hypro::Point<TypeParam>({-1,0,1})) != pyramidVertices.end() );
	EXPECT_TRUE( std::find(pyramidVertices.begin(), pyramidVertices.end(), hypro::Point<TypeParam>({-1,0,-1})) != pyramidVertices.end() );
	EXPECT_TRUE( std::find(pyramidVertices.begin(), pyramidVertices.end(), hypro::Point<TypeParam>({0,1,0})) != pyramidVertices.end() );
}

/*
 * Test convexHull algorithm - vertices->constaints
 */
TYPED_TEST(VertexEnumerationTest, ComputeConstraints) {
	// unityBox in 2D
	// init
	hypro::vector_t<TypeParam> v01_box2 = hypro::vector_t<TypeParam>(2);
	v01_box2(0) = 1; v01_box2(1) = 1;

	hypro::vector_t<TypeParam> v02_box2 = hypro::vector_t<TypeParam>(2);
	v02_box2(0) = 1; v02_box2(1) = -1;

	hypro::vector_t<TypeParam> v03_box2 = hypro::vector_t<TypeParam>(2);
	v03_box2(0) = -1; v03_box2(1) = 1;

	hypro::vector_t<TypeParam> v04_box2 = hypro::vector_t<TypeParam>(2);
	v04_box2(0) = -1; v04_box2(1) = -1;


	std::vector<hypro::Point<TypeParam>> points_box2;
	points_box2.push_back(hypro::Point<TypeParam>(v01_box2));
	points_box2.push_back(hypro::Point<TypeParam>(v02_box2));
	points_box2.push_back(hypro::Point<TypeParam>(v03_box2));
	points_box2.push_back(hypro::Point<TypeParam>(v04_box2));


	// compute constraints
	auto facets_box2 = convexHull(points_box2);

	// init test constraints
	bool f1_box2=false, f2_box2=false, f3_box2=false, f4_box2=false, fail_box2=false;

	hypro::vector_t<TypeParam> test_v01_box2 = hypro::vector_t<TypeParam>(2);
	test_v01_box2(0) = 1; test_v01_box2(1) = 0;

	hypro::vector_t<TypeParam> test_v02_box2 = hypro::vector_t<TypeParam>(2);
	test_v02_box2(0) = -1; test_v02_box2(1) = 0;

	hypro::vector_t<TypeParam> test_v03_box2 = hypro::vector_t<TypeParam>(2);
	test_v03_box2(0) = 0; test_v03_box2(1) = 1;

	hypro::vector_t<TypeParam> test_v04_box2 = hypro::vector_t<TypeParam>(2);
	test_v04_box2(0) = 0; test_v04_box2(1) = -1;

	// test
	for(unsigned i = 0; i<facets_box2.first.size(); i++){
		hypro::vector_t<TypeParam> normal = facets_box2.first.at(i)->getNormal();
		TypeParam offset = facets_box2.first.at(i)->getScalar();

		//std::cout << "Result Nr." << i << std::endl << "normal: "<< normal <<"\noffset: "<<offset << std::endl;
		if(     normal == test_v01_box2 && offset==1) 	f1_box2=true;
		else if(normal == test_v02_box2 && offset==1) 	f2_box2=true;
		else if(normal == test_v03_box2 && offset==1) 	f3_box2=true;
		else if(normal == test_v04_box2 && offset==1) 	f4_box2=true;
		else fail_box2=true;
	}

	EXPECT_FALSE( fail_box2 );
	EXPECT_TRUE( f1_box2 );
	EXPECT_TRUE( f2_box2 );
	EXPECT_TRUE( f3_box2 );
	EXPECT_TRUE( f4_box2 );


	// unity box in 3D
	// init
	hypro::vector_t<TypeParam> v01_box = hypro::vector_t<TypeParam>(3);
	v01_box(0) = 1; v01_box(1) = 1; v01_box(2) = 1;

	hypro::vector_t<TypeParam> v02_box = hypro::vector_t<TypeParam>(3);
	v02_box(0) = 1; v02_box(1) = 1; v02_box(2) = -1;

	hypro::vector_t<TypeParam> v03_box = hypro::vector_t<TypeParam>(3);
	v03_box(0) = 1; v03_box(1) = -1; v03_box(2) = 1;

	hypro::vector_t<TypeParam> v04_box = hypro::vector_t<TypeParam>(3);
	v04_box(0) = 1; v04_box(1) = -1; v04_box(2) = -1;

	hypro::vector_t<TypeParam> v05_box = hypro::vector_t<TypeParam>(3);
	v05_box(0) = -1; v05_box(1) = 1; v05_box(2) = 1;

	hypro::vector_t<TypeParam> v06_box = hypro::vector_t<TypeParam>(3);
	v06_box(0) = -1; v06_box(1) = 1; v06_box(2) = -1;

	hypro::vector_t<TypeParam> v07_box = hypro::vector_t<TypeParam>(3);
	v07_box(0) = -1; v07_box(1) = -1; v07_box(2) = 1;

	hypro::vector_t<TypeParam> v08_box = hypro::vector_t<TypeParam>(3);
	v08_box(0) = -1; v08_box(1) = -1; v08_box(2) = -1;

	std::vector<hypro::Point<TypeParam>> points_box;
	points_box.push_back(hypro::Point<TypeParam>(v01_box));
	points_box.push_back(hypro::Point<TypeParam>(v02_box));
	points_box.push_back(hypro::Point<TypeParam>(v03_box));
	points_box.push_back(hypro::Point<TypeParam>(v04_box));
	points_box.push_back(hypro::Point<TypeParam>(v05_box));
	points_box.push_back(hypro::Point<TypeParam>(v06_box));
	points_box.push_back(hypro::Point<TypeParam>(v07_box));
	points_box.push_back(hypro::Point<TypeParam>(v08_box));

	// compute constraints
	auto facets_box = convexHull(points_box);

	// init test constraints
	bool f1_box=false, f2_box=false, f3_box=false, f4_box=false, f5_box=false, f6_box=false, fail_box=false;
	hypro::vector_t<TypeParam> test_v01_box = hypro::vector_t<TypeParam>(3);
	test_v01_box(0) = 1; test_v01_box(1) = 0; test_v01_box(2) = 0;

	hypro::vector_t<TypeParam> test_v02_box = hypro::vector_t<TypeParam>(3);
	test_v02_box(0) = -1; test_v02_box(1) = 0; test_v02_box(2) = 0;

	hypro::vector_t<TypeParam> test_v03_box = hypro::vector_t<TypeParam>(3);
	test_v03_box(0) = 0; test_v03_box(1) = 1; test_v03_box(2) = 0;

	hypro::vector_t<TypeParam> test_v04_box = hypro::vector_t<TypeParam>(3);
	test_v04_box(0) = 0; test_v04_box(1) = -1; test_v04_box(2) = 0;

	hypro::vector_t<TypeParam> test_v05_box = hypro::vector_t<TypeParam>(3);
	test_v05_box(0) = 0; test_v05_box(1) = 0; test_v05_box(2) = 1;

	hypro::vector_t<TypeParam> test_v06_box = hypro::vector_t<TypeParam>(3);
	test_v06_box(0) = 0; test_v06_box(1) = 0; test_v06_box(2) = -1;

	// test
	for(unsigned i = 0; i<facets_box.first.size(); i++){
		hypro::vector_t<TypeParam> normal = facets_box.first.at(i)->getNormal();
		TypeParam offset = facets_box.first.at(i)->getScalar();

		if(    normal == test_v01_box && offset==1)  f1_box=true;
		else if(normal == test_v02_box && offset==1) f2_box=true;
		else if(normal == test_v03_box && offset==1) f3_box=true;
		else if(normal == test_v04_box && offset==1) f4_box=true;
		else if(normal == test_v05_box && offset==1) f5_box=true;
		else if(normal == test_v06_box && offset==1) f6_box=true;
		else fail_box=true;
	}

	EXPECT_FALSE( fail_box );
	EXPECT_TRUE( f1_box );
	EXPECT_TRUE( f2_box );
	EXPECT_TRUE( f3_box );
	EXPECT_TRUE( f4_box );
	EXPECT_TRUE( f5_box );
	EXPECT_TRUE( f6_box );

	// unity box in 4D
	// init
	hypro::vector_t<TypeParam> v01_box4 = hypro::vector_t<TypeParam>(4);
	v01_box4(0) = 1; v01_box4(1) = 1; v01_box4(2) = 1; v01_box4(3) = 1;

	hypro::vector_t<TypeParam> v02_box4 = hypro::vector_t<TypeParam>(4);
	v02_box4(0) = 1; v02_box4(1) = 1; v02_box4(2) = 1; v02_box4(3) = -1;

	hypro::vector_t<TypeParam> v03_box4 = hypro::vector_t<TypeParam>(4);
	v03_box4(0) = 1; v03_box4(1) = 1; v03_box4(2) = -1; v03_box4(3) = 1;

	hypro::vector_t<TypeParam> v04_box4 = hypro::vector_t<TypeParam>(4);
	v04_box4(0) = 1; v04_box4(1) = 1; v04_box4(2) = -1; v04_box4(3) = -1;

	hypro::vector_t<TypeParam> v05_box4 = hypro::vector_t<TypeParam>(4);
	v05_box4(0) = 1; v05_box4(1) = -1; v05_box4(2) = 1; v05_box4(3) = 1;

	hypro::vector_t<TypeParam> v06_box4 = hypro::vector_t<TypeParam>(4);
	v06_box4(0) = 1; v06_box4(1) = -1; v06_box4(2) = 1; v06_box4(3) = -1;

	hypro::vector_t<TypeParam> v07_box4 = hypro::vector_t<TypeParam>(4);
	v07_box4(0) = 1; v07_box4(1) = -1; v07_box4(2) = -1; v07_box4(3) = 1;

	hypro::vector_t<TypeParam> v08_box4 = hypro::vector_t<TypeParam>(4);
	v08_box4(0) = 1; v08_box4(1) = -1; v08_box4(2) = -1; v08_box4(3) = -1;

	hypro::vector_t<TypeParam> v09_box4 = hypro::vector_t<TypeParam>(4);
	v09_box4(0) = -1; v09_box4(1) = 1; v09_box4(2) = 1; v09_box4(3) = 1;

	hypro::vector_t<TypeParam> v10_box4 = hypro::vector_t<TypeParam>(4);
	v10_box4(0) = -1; v10_box4(1) = 1; v10_box4(2) = 1; v10_box4(3) = -1;

	hypro::vector_t<TypeParam> v11_box4 = hypro::vector_t<TypeParam>(4);
	v11_box4(0) = -1; v11_box4(1) = 1; v11_box4(2) = -1; v11_box4(3) = 1;

	hypro::vector_t<TypeParam> v12_box4 = hypro::vector_t<TypeParam>(4);
	v12_box4(0) = -1; v12_box4(1) = 1; v12_box4(2) = -1; v12_box4(3) = -1;

	hypro::vector_t<TypeParam> v13_box4 = hypro::vector_t<TypeParam>(4);
	v13_box4(0) = -1; v13_box4(1) = -1; v13_box4(2) = 1; v13_box4(3) = 1;

	hypro::vector_t<TypeParam> v14_box4 = hypro::vector_t<TypeParam>(4);
	v14_box4(0) = -1; v14_box4(1) = -1; v14_box4(2) = 1; v14_box4(3) = -1;

	hypro::vector_t<TypeParam> v15_box4 = hypro::vector_t<TypeParam>(4);
	v15_box4(0) = -1; v15_box4(1) = -1; v15_box4(2) = -1; v15_box4(3) = 1;

	hypro::vector_t<TypeParam> v16_box4 = hypro::vector_t<TypeParam>(4);
	v16_box4(0) = -1; v16_box4(1) = -1; v16_box4(2) = -1; v16_box4(3) = -1;

	std::vector<hypro::Point<TypeParam>> points_box4;
	points_box4.push_back(hypro::Point<TypeParam>(v01_box4));
	points_box4.push_back(hypro::Point<TypeParam>(v02_box4));
	points_box4.push_back(hypro::Point<TypeParam>(v03_box4));
	points_box4.push_back(hypro::Point<TypeParam>(v04_box4));
	points_box4.push_back(hypro::Point<TypeParam>(v05_box4));
	points_box4.push_back(hypro::Point<TypeParam>(v06_box4));
	points_box4.push_back(hypro::Point<TypeParam>(v07_box4));
	points_box4.push_back(hypro::Point<TypeParam>(v08_box4));
	points_box4.push_back(hypro::Point<TypeParam>(v09_box4));
	points_box4.push_back(hypro::Point<TypeParam>(v10_box4));
	points_box4.push_back(hypro::Point<TypeParam>(v11_box4));
	points_box4.push_back(hypro::Point<TypeParam>(v12_box4));
	points_box4.push_back(hypro::Point<TypeParam>(v13_box4));
	points_box4.push_back(hypro::Point<TypeParam>(v14_box4));
	points_box4.push_back(hypro::Point<TypeParam>(v15_box4));
	points_box4.push_back(hypro::Point<TypeParam>(v16_box4));


	// compute constraints
	auto facets_box4 = convexHull(points_box4);

	// init test constraints
	bool f1_box4=false, f2_box4=false, f3_box4=false, f4_box4=false, f5_box4=false, f6_box4=false, f7_box4=false, f8_box4=false, fail_box4=false;
	hypro::vector_t<TypeParam> test_v01_box4 = hypro::vector_t<TypeParam>(4);
	test_v01_box4(0) = 1; test_v01_box4(1) = 0; test_v01_box4(2) = 0; test_v01_box4(3) = 0;

	hypro::vector_t<TypeParam> test_v02_box4 = hypro::vector_t<TypeParam>(4);
	test_v02_box4(0) = -1; test_v02_box4(1) = 0; test_v02_box4(2) = 0; test_v02_box4(3) = 0;

	hypro::vector_t<TypeParam> test_v03_box4 = hypro::vector_t<TypeParam>(4);
	test_v03_box4(0) = 0; test_v03_box4(1) = 1; test_v03_box4(2) = 0; test_v03_box4(3) = 0;

	hypro::vector_t<TypeParam> test_v04_box4 = hypro::vector_t<TypeParam>(4);
	test_v04_box4(0) = 0; test_v04_box4(1) = -1; test_v04_box4(2) = 0; test_v04_box4(3) = 0;

	hypro::vector_t<TypeParam> test_v05_box4 = hypro::vector_t<TypeParam>(4);
	test_v05_box4(0) = 0; test_v05_box4(1) = 0; test_v05_box4(2) = 1; test_v05_box4(3) = 0;

	hypro::vector_t<TypeParam> test_v06_box4 = hypro::vector_t<TypeParam>(4);
	test_v06_box4(0) = 0; test_v06_box4(1) = 0; test_v06_box4(2) = -1; test_v06_box4(3) = 0;

	hypro::vector_t<TypeParam> test_v07_box4 = hypro::vector_t<TypeParam>(4);
	test_v07_box4(0) = 0; test_v07_box4(1) = 0; test_v07_box4(2) = 0; test_v07_box4(3) = 1;

	hypro::vector_t<TypeParam> test_v08_box4 = hypro::vector_t<TypeParam>(4);
	test_v08_box4(0) = 0; test_v08_box4(1) = 0; test_v08_box4(2) = 0; test_v08_box4(3) = -1;

	// test
	for(unsigned i = 0; i<facets_box4.first.size(); i++){
		hypro::vector_t<TypeParam> normal = facets_box4.first.at(i)->getNormal();
		TypeParam offset = facets_box4.first.at(i)->getScalar();

		//std::cout << "Result Nr." << i << std::endl << "normal: "<< normal <<"\noffset: "<<offset << std::endl;
		if(    normal == test_v01_box4 && offset==1)  f1_box4=true;
		else if(normal == test_v02_box4 && offset==1) f2_box4=true;
		else if(normal == test_v03_box4 && offset==1) f3_box4=true;
		else if(normal == test_v04_box4 && offset==1) f4_box4=true;
		else if(normal == test_v05_box4 && offset==1) f5_box4=true;
		else if(normal == test_v06_box4 && offset==1) f6_box4=true;
		else if(normal == test_v07_box4 && offset==1) f7_box4=true;
		else if(normal == test_v08_box4 && offset==1) f8_box4=true;
		else fail_box4=true;
	}

	EXPECT_FALSE( fail_box4 );
	EXPECT_TRUE( f1_box4 );
	EXPECT_TRUE( f2_box4 );
	EXPECT_TRUE( f3_box4 );
	EXPECT_TRUE( f4_box4 );
	EXPECT_TRUE( f5_box4 );
	EXPECT_TRUE( f6_box4 );
	EXPECT_TRUE( f7_box4 );
	EXPECT_TRUE( f8_box4 );

	// pyramid with quadratic bottom -> test towards degenerated vertices.
	// init
	hypro::vector_t<TypeParam> v01_pyramid = hypro::vector_t<TypeParam>(3);
	v01_pyramid(0) = 1; v01_pyramid(1) = 0; v01_pyramid(2) = 1;

	hypro::vector_t<TypeParam> v02_pyramid = hypro::vector_t<TypeParam>(3);
	v02_pyramid(0) = 1; v02_pyramid(1) = 0; v02_pyramid(2) = -1;

	hypro::vector_t<TypeParam> v03_pyramid = hypro::vector_t<TypeParam>(3);
	v03_pyramid(0) = -1; v03_pyramid(1) = 0; v03_pyramid(2) = 1;

	hypro::vector_t<TypeParam> v04_pyramid = hypro::vector_t<TypeParam>(3);
	v04_pyramid(0) = -1; v04_pyramid(1) = 0; v04_pyramid(2) = -1;

	hypro::vector_t<TypeParam> v05_pyramid = hypro::vector_t<TypeParam>(3);
	v05_pyramid(0) = 0; v05_pyramid(1) = 1; v05_pyramid(2) = 0;

	std::vector<hypro::Point<TypeParam>> points_pyramid;
	points_pyramid.push_back(hypro::Point<TypeParam>(v01_pyramid));
	points_pyramid.push_back(hypro::Point<TypeParam>(v02_pyramid));
	points_pyramid.push_back(hypro::Point<TypeParam>(v03_pyramid));
	points_pyramid.push_back(hypro::Point<TypeParam>(v04_pyramid));
	points_pyramid.push_back(hypro::Point<TypeParam>(v05_pyramid));

	// compute constraints
	auto facets_pyramid = convexHull(points_pyramid);

	// init test constraints
	bool f1_pyramid=false, f2_pyramid=false, f3_pyramid=false, f4_pyramid=false, f5_pyramid=false, fail_pyramid=false;

	hypro::vector_t<TypeParam> test_v01_pyramid = hypro::vector_t<TypeParam>(3);
	test_v01_pyramid(0) = 1; test_v01_pyramid(1) = 1; test_v01_pyramid(2) = 0;

	hypro::vector_t<TypeParam> test_v02_pyramid = hypro::vector_t<TypeParam>(3);
	test_v02_pyramid(0) = -1; test_v02_pyramid(1) = 1; test_v02_pyramid(2) = 0;

	hypro::vector_t<TypeParam> test_v03_pyramid = hypro::vector_t<TypeParam>(3);
	test_v03_pyramid(0) = 0; test_v03_pyramid(1) = 1; test_v03_pyramid(2) = 1;

	hypro::vector_t<TypeParam> test_v04_pyramid = hypro::vector_t<TypeParam>(3);
	test_v04_pyramid(0) = 0; test_v04_pyramid(1) = 1; test_v04_pyramid(2) = -1;

	hypro::vector_t<TypeParam> test_v05_pyramid = hypro::vector_t<TypeParam>(3);
	test_v05_pyramid(0) = 0; test_v05_pyramid(1) = -1; test_v05_pyramid(2) = 0;

	// test
	for(unsigned i = 0; i<facets_pyramid.first.size(); i++){
		hypro::vector_t<TypeParam> normal = facets_pyramid.first.at(i)->getNormal();
		TypeParam offset = facets_pyramid.first.at(i)->getScalar();

		//std::cout << "Result Nr." << i << std::endl << "normal: "<< normal <<"\noffset: "<<offset << std::endl;
		if(     normal == test_v01_pyramid && offset==1) 	f1_pyramid=true;
		else if(normal == test_v02_pyramid && offset==1) 	f2_pyramid=true;
		else if(normal == test_v03_pyramid && offset==1) 	f3_pyramid=true;
		else if(normal == test_v04_pyramid && offset==1) 	f4_pyramid=true;
		else if(normal == test_v05_pyramid && offset==0) 	f5_pyramid=true;
		else fail_pyramid=true;
	}

	EXPECT_FALSE( fail_pyramid );
	EXPECT_TRUE( f1_pyramid );
	EXPECT_TRUE( f2_pyramid );
	EXPECT_TRUE( f3_pyramid );
	EXPECT_TRUE( f4_pyramid );
	EXPECT_TRUE( f5_pyramid );
}
