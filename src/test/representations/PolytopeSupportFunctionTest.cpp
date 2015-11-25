/**
 * Tests for SupportFunctions.
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since		2015-01-20
 * @version		2015-01-22
 */

#include "../../lib/representations/SupportFunction/PolytopeSupportFunction.h"
#include "gtest/gtest.h"
#include "../defines.h"


using namespace hypro;
using namespace carl;

template<typename Number>
class PolytopeSupportFunctionTest : public ::testing::Test {
protected:
    virtual void SetUp() {
		constraints = matrix_t<Number>::Zero(3,2);

		constraints(0,0) = Number(2);
		constraints(0,1) = Number(4);
		constraints(1,0) = Number(1);
		constraints(1,1) = Number(-2);
		constraints(2,0) = Number(-4);
		constraints(2,1) = Number(1);

		constants = matrix_t<Number>(3,1);
		constants(0,0) = Number(20);
		constants(1,0) = Number(5);
		constants(2,0) = Number(17);
    }

    virtual void TearDown(){
    }

	matrix_t<Number> constraints;
	matrix_t<Number> constants;
};

TYPED_TEST(PolytopeSupportFunctionTest, constructor) {
	PolytopeSupportFunction<TypeParam> psf1 = PolytopeSupportFunction<TypeParam>(this->constraints, this->constants);
	SUCCEED();
}

TYPED_TEST(PolytopeSupportFunctionTest, evaluation) {
	PolytopeSupportFunction<TypeParam> psf1 = PolytopeSupportFunction<TypeParam>(this->constraints, this->constants);
	vector_t<TypeParam> vec1 = vector_t<TypeParam>(2,1);
	vector_t<TypeParam> vec2 = vector_t<TypeParam>(2,1);
	vector_t<TypeParam> vec3 = vector_t<TypeParam>(2,1);
	vector_t<TypeParam> vec4 = vector_t<TypeParam>(2,1);

	vec1(0,0) = TypeParam(2);
	vec1(1,0) = TypeParam(4);

	vec2(0,0) = TypeParam(1);
	vec2(1,0) = TypeParam(-2);

	vec3(0,0) = TypeParam(-4);
	vec3(1,0) = TypeParam(1);

	vec4(0,0) = TypeParam(2);
	vec4(1,0) = TypeParam(5);

	EXPECT_EQ(TypeParam(20),psf1.evaluate(vec1).supportValue);
	EXPECT_EQ(TypeParam(5),psf1.evaluate(vec2).supportValue);
	EXPECT_EQ(TypeParam(17),psf1.evaluate(vec3).supportValue);
}

TYPED_TEST(PolytopeSupportFunctionTest, multiEvaluation) {
	PolytopeSupportFunction<TypeParam> psf1 = PolytopeSupportFunction<TypeParam>(this->constraints, this->constants);
	matrix_t<TypeParam> directions = matrix_t<TypeParam>(3,2);
	directions(0,0) = TypeParam(2);
	directions(0,1) = TypeParam(4);
	directions(1,0) = TypeParam(1);
	directions(1,1) = TypeParam(-2);
	directions(2,0) = TypeParam(-4);
	directions(2,1) = TypeParam(1);

	vector_t<TypeParam> res = psf1.multiEvaluate(directions);
	EXPECT_EQ(TypeParam(20), res(0));
	EXPECT_EQ(TypeParam(5), res(1));
	EXPECT_EQ(TypeParam(17), res(2));
}

TYPED_TEST(PolytopeSupportFunctionTest, contains) {
	PolytopeSupportFunction<TypeParam> psf1 = PolytopeSupportFunction<TypeParam>(this->constraints, this->constants);

	EXPECT_TRUE(psf1.contains(Point<TypeParam>({0,0})));
	EXPECT_TRUE(psf1.contains(Point<TypeParam>({-2,-2})));
	EXPECT_TRUE(psf1.contains(Point<TypeParam>({3,3})));

	TypeParam xCoord = TypeParam(-12)/TypeParam(4.5)-TypeParam(0.0001);
	TypeParam yCoord = TypeParam(4)*xCoord + TypeParam(17)-TypeParam(0.0001);

	EXPECT_TRUE(psf1.contains(Point<TypeParam>({xCoord,yCoord})));
	EXPECT_FALSE(psf1.contains(Point<TypeParam>({xCoord+TypeParam(0.001),yCoord+TypeParam(0.001)})));
}