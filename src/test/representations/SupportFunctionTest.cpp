/**
 * Tests for SupportFunctions.
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since		2015-02-24
 * @version		2015-02-25
 */

#include "../../lib/representations/SupportFunction/SupportFunctionContent.h"
#include "gtest/gtest.h"
#include "../defines.h"


using namespace hypro;
using namespace carl;

template<typename Number>
class SupportFunctionTest : public ::testing::Test {
protected:
    virtual void SetUp() {
		constraints = matrix_t<Number>::Zero(3,2);
		constraints(0,0) = Number(2);
		constraints(0,1) = Number(4);
		constraints(1,0) = Number(1);
		constraints(1,1) = Number(-2);
		constraints(2,0) = Number(-4);
		constraints(2,1) = Number(1);

		constants = vector_t<Number>(3);
		constants(0) = Number(20);
		constants(1) = Number(5);
		constants(2) = Number(17);

		vec1 = vector_t<Number>(2);
		vec2 = vector_t<Number>(2);
		vec3 = vector_t<Number>(2);

		vec1(0) = Number(2);
		vec1(1) = Number(4);

		vec2(0) = Number(1);
		vec2(1) = Number(-2);

		vec3(0) = Number(-4);
		vec3(1) = Number(1);
    }

    virtual void TearDown(){
    }

	matrix_t<Number> constraints;
	vector_t<Number> constants;

	vector_t<Number> vec1;
	vector_t<Number> vec2;
	vector_t<Number> vec3;
};

/**
 * Tests only a single constructor which holds a concrete representation. Other constructors are tested by operations.
 */
TYPED_TEST(SupportFunctionTest, constructor) {
	std::shared_ptr<SupportFunctionContent<TypeParam>> psf1 = SupportFunctionContent<TypeParam>::create(SF_TYPE::POLY, this->constraints, this->constants);
	EXPECT_DEATH(SupportFunctionContent<TypeParam>::create(SF_TYPE::SUM, this->constraints, this->constants), "c*");

	SUCCEED();
}

TYPED_TEST(SupportFunctionTest, simpleEvaluation) {
	std::shared_ptr<SupportFunctionContent<TypeParam>> psf1 = SupportFunctionContent<TypeParam>::create(SF_TYPE::POLY, this->constraints, this->constants);
	matrix_t<TypeParam> vec1 = matrix_t<TypeParam>(2,1);
	matrix_t<TypeParam> vec2 = matrix_t<TypeParam>(2,1);
	matrix_t<TypeParam> vec3 = matrix_t<TypeParam>(2,1);

	EXPECT_EQ(TypeParam(20), psf1->evaluate(this->vec1).supportValue);
	EXPECT_EQ(TypeParam(5), psf1->evaluate(this->vec2).supportValue);
	EXPECT_EQ(TypeParam(17), psf1->evaluate(this->vec3).supportValue);
}

TYPED_TEST(SupportFunctionTest, linearTransformation) {
	std::shared_ptr<SupportFunctionContent<TypeParam>> psf1 = SupportFunctionContent<TypeParam>::create(SF_TYPE::POLY, this->constraints, this->constants);
	matrix_t<TypeParam> rotation = matrix_t<TypeParam>(2,2);
	TypeParam angle = 45;
	rotation(0,0) = carl::cos(angle);
	rotation(0,1) = -carl::sin(angle);
	rotation(1,0) = carl::sin(angle);
	rotation(1,1) = carl::cos(angle);

	vector_t<TypeParam> v1Rot = rotation*(this->vec1);
	vector_t<TypeParam> v2Rot = rotation*(this->vec2);
	vector_t<TypeParam> v3Rot = rotation*(this->vec3);

	std::shared_ptr<SupportFunctionContent<TypeParam>> res = psf1->linearTransformation(rotation, vector_t<TypeParam>::Zero(rotation.rows()));

	EXPECT_EQ(TypeParam(20), res->evaluate(v1Rot).supportValue);
	EXPECT_EQ(TypeParam(5), res->evaluate(v2Rot).supportValue);
	EXPECT_EQ(TypeParam(17), res->evaluate(v3Rot).supportValue);
}

TYPED_TEST(SupportFunctionTest, scale) {
	std::shared_ptr<SupportFunctionContent<TypeParam>> psf1 = SupportFunctionContent<TypeParam>::create(SF_TYPE::POLY, this->constraints, this->constants);
	TypeParam factor = 2;

	std::shared_ptr<SupportFunctionContent<TypeParam>> res =  psf1->scale(factor);

	EXPECT_EQ(TypeParam(factor) * TypeParam(20), res->evaluate(this->vec1).supportValue);
	EXPECT_EQ(TypeParam(factor) * TypeParam(5), res->evaluate(this->vec2).supportValue);
	EXPECT_EQ(TypeParam(factor) * TypeParam(17), res->evaluate(this->vec3).supportValue);
}

TYPED_TEST(SupportFunctionTest, minkowskiSum) {
	matrix_t<TypeParam> constraints1 = matrix_t<TypeParam>(3,2);
	matrix_t<TypeParam> constraints2 = matrix_t<TypeParam>(3,2);
	vector_t<TypeParam> constants1 = vector_t<TypeParam>(3);
	vector_t<TypeParam> constants2 = vector_t<TypeParam>(3);

	// Triangle (-1,0) - (1,0) - (0,2)
	constraints1(0,0) = TypeParam(2);
	constraints1(0,1) = TypeParam(1);
	constraints1(1,0) = TypeParam(-2);
	constraints1(1,1) = TypeParam(1);
	constraints1(2,0) = TypeParam(0);
	constraints1(2,1) = TypeParam(-1);

	constants1(0) = TypeParam(2);
	constants1(1) = TypeParam(2);
	constants1(2) = TypeParam(0);

	// Triangle (0,2) - (-1,4) - (1,4)
	constraints2(0,0) = TypeParam(-2);
	constraints2(0,1) = TypeParam(-1);
	constraints2(1,0) = TypeParam(2);
	constraints2(1,1) = TypeParam(-1);
	constraints2(2,0) = TypeParam(0);
	constraints2(2,1) = TypeParam(1);

	constants2(0) = TypeParam(-2);
	constants2(1) = TypeParam(-2);
	constants2(2) = TypeParam(4);

	std::shared_ptr<SupportFunctionContent<TypeParam>> tri1 = SupportFunctionContent<TypeParam>::create(SF_TYPE::POLY, constraints1, constants1);
	std::shared_ptr<SupportFunctionContent<TypeParam>> tri2 = SupportFunctionContent<TypeParam>::create(SF_TYPE::POLY, constraints2, constants2);

	// Result directions
	vector_t<TypeParam> vec1 = vector_t<TypeParam>(2);
	vec1(0) = TypeParam(2);
	vec1(1) = TypeParam(1);

	vector_t<TypeParam> vec2 = vector_t<TypeParam>(2);
	vec2(0) = TypeParam(-2);
	vec2(1) = TypeParam(1);

	vector_t<TypeParam> vec3 = vector_t<TypeParam>(2);
	vec3(0) = TypeParam(0);
	vec3(1) = TypeParam(-1);

	vector_t<TypeParam> vec4 = vector_t<TypeParam>(2);
	vec4(0) = TypeParam(2);
	vec4(1) = TypeParam(-1);

	vector_t<TypeParam> vec5 = vector_t<TypeParam>(2);
	vec5(0) = TypeParam(-2);
	vec5(1) = TypeParam(-1);

	vector_t<TypeParam> vec6 = vector_t<TypeParam>(2);
	vec6(0) = TypeParam(0);
	vec6(1) = TypeParam(1);

	std::shared_ptr<SupportFunctionContent<TypeParam>> res = tri1->minkowskiSum(tri2);

	EXPECT_EQ(TypeParam(8), res->evaluate(vec1).supportValue);
	EXPECT_EQ(TypeParam(8), res->evaluate(vec2).supportValue);
	EXPECT_EQ(TypeParam(-2), res->evaluate(vec3).supportValue);
	EXPECT_EQ(TypeParam(0), res->evaluate(vec4).supportValue);
	EXPECT_EQ(TypeParam(0), res->evaluate(vec5).supportValue);
	EXPECT_EQ(TypeParam(6), res->evaluate(vec6).supportValue);
}

TYPED_TEST(SupportFunctionTest, intersect) {
	std::shared_ptr<SupportFunctionContent<TypeParam>> psf1 = SupportFunctionContent<TypeParam>::create(SF_TYPE::POLY, this->constraints, this->constants);
}

TYPED_TEST(SupportFunctionTest, unite) {
	matrix_t<TypeParam> constraints1 = matrix_t<TypeParam>(3,2);
	matrix_t<TypeParam> constraints2 = matrix_t<TypeParam>(3,2);
	vector_t<TypeParam> constants1 = vector_t<TypeParam>(3);
	vector_t<TypeParam> constants2 = vector_t<TypeParam>(3);

	// Triangle (-1,0) - (1,0) - (0,2)
	constraints1(0,0) = TypeParam(2);
	constraints1(0,1) = TypeParam(1);
	constraints1(1,0) = TypeParam(-2);
	constraints1(1,1) = TypeParam(1);
	constraints1(2,0) = TypeParam(0);
	constraints1(2,1) = TypeParam(-1);

	constants1(0) = TypeParam(2);
	constants1(1) = TypeParam(2);
	constants1(2) = TypeParam(0);

	// Triangle (0,2) - (-1,4) - (1,4)
	constraints2(0,0) = TypeParam(-2);
	constraints2(0,1) = TypeParam(-1);
	constraints2(1,0) = TypeParam(2);
	constraints2(1,1) = TypeParam(-1);
	constraints2(2,0) = TypeParam(0);
	constraints2(2,1) = TypeParam(1);

	constants2(0) = TypeParam(-2);
	constants2(1) = TypeParam(-2);
	constants2(2) = TypeParam(4);

	std::shared_ptr<SupportFunctionContent<TypeParam>> tri1 = SupportFunctionContent<TypeParam>::create(SF_TYPE::POLY, constraints1, constants1);
	std::shared_ptr<SupportFunctionContent<TypeParam>> tri2 = SupportFunctionContent<TypeParam>::create(SF_TYPE::POLY, constraints2, constants2);

	std::shared_ptr<SupportFunctionContent<TypeParam>> res = tri1->unite(tri2);

	// Result directions
	vector_t<TypeParam> vec1 = vector_t<TypeParam>(2);
	vec1(0) = TypeParam(1);
	vec1(1) = TypeParam(0);

	vector_t<TypeParam> vec2 = vector_t<TypeParam>(2);
	vec2(0) = TypeParam(0);
	vec2(1) = TypeParam(1);

	vector_t<TypeParam> vec3 = vector_t<TypeParam>(2);
	vec3(0) = TypeParam(-1);
	vec3(1) = TypeParam(0);

	vector_t<TypeParam> vec4 = vector_t<TypeParam>(2);
	vec4(0) = TypeParam(0);
	vec4(1) = TypeParam(-1);

	EXPECT_EQ(TypeParam(1), res->evaluate(vec1).supportValue);
	EXPECT_EQ(TypeParam(4), res->evaluate(vec2).supportValue);
	EXPECT_EQ(TypeParam(1), res->evaluate(vec3).supportValue);
	EXPECT_EQ(TypeParam(0), res->evaluate(vec4).supportValue);
}

TYPED_TEST(SupportFunctionTest, contains) {
	std::shared_ptr<SupportFunctionContent<TypeParam>> psf1 = SupportFunctionContent<TypeParam>::create(SF_TYPE::POLY, this->constraints, this->constants);
	EXPECT_TRUE(psf1->contains(Point<TypeParam>({0,0})));
	EXPECT_TRUE(psf1->contains(Point<TypeParam>({-2,-2})));
	EXPECT_TRUE(psf1->contains(Point<TypeParam>({3,3})));

	TypeParam xCoord = TypeParam(-12)/carl::rationalize<TypeParam>(4.5)-carl::rationalize<TypeParam>(0.0001);
	TypeParam yCoord = TypeParam(4)*xCoord + TypeParam(17)-carl::rationalize<TypeParam>(0.0001);

	EXPECT_TRUE(psf1->contains(Point<TypeParam>({xCoord,yCoord})));
	EXPECT_FALSE(psf1->contains(Point<TypeParam>({xCoord+carl::rationalize<TypeParam>(0.001),yCoord+carl::rationalize<TypeParam>(0.001)})));
}
