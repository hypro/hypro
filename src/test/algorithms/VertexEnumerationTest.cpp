/**
 * Testfile reproducing the example given at the end of the Avis and Fukuda paper.
 */

#include "gtest/gtest.h"
#include "../defines.h"
#include "../../src/lib/util/vertexEnumeration.h"

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
	hypro::matrix_t<TypeParam> expected = hypro::matrix_t<TypeParam>(4,3);
	expected << 5,-1,0,10,-1,-2,5,-1,-1,0,-1,-1;

	EXPECT_EQ(expected, this->initial.dictionary());

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