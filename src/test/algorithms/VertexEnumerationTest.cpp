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