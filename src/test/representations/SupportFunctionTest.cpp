/**
 * Tests for SupportFunctions.
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * 
 * @since		2015-02-24
 * @version		2015-021-24
 */

#include "../../lib/representations/SupportFunction/SupportFunction.h"
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

/**
 * Tests only a single constructor which holds a concrete representation. Other constructors are tested by operations.
 */
TYPED_TEST(SupportFunctionTest, constructor) {
	std::cout << this->constraints << std::endl;
	std::cout << this->constants << std::endl;
	SupportFunction<TypeParam> psf1 = SupportFunction<TypeParam>(SF_TYPE::POLY, this->constraints, this->constants);
	EXPECT_DEATH(SupportFunction<TypeParam>(SF_TYPE::SUM, this->constraints, this->constants), "Assertion `false' failed.");
	
	SUCCEED();
}

TYPED_TEST(SupportFunctionTest, simpleEvaluation) {
	SupportFunction<TypeParam> psf1 = SupportFunction<TypeParam>(SF_TYPE::POLY, this->constraints, this->constants);
	matrix_t<TypeParam> vec1 = matrix_t<TypeParam>(2,1);
	matrix_t<TypeParam> vec2 = matrix_t<TypeParam>(2,1);
	matrix_t<TypeParam> vec3 = matrix_t<TypeParam>(2,1);
	
	vec1(0,0) = TypeParam(2);
	vec1(1,0) = TypeParam(4);

	vec2(0,0) = TypeParam(1);
	vec2(1,0) = TypeParam(-2);
	
	vec3(0,0) = TypeParam(-4);
	vec3(1,0) = TypeParam(1);
	
	EXPECT_EQ(TypeParam(20),psf1.evaluate(vec1).supportValue);
	EXPECT_EQ(TypeParam(5),psf1.evaluate(vec2).supportValue);
	EXPECT_EQ(TypeParam(17),psf1.evaluate(vec3).supportValue);
}

TYPED_TEST(SupportFunctionTest, linearTransformation) {
	SupportFunction<TypeParam> psf1 = SupportFunction<TypeParam>(SF_TYPE::POLY, this->constraints, this->constants);
	matrix_t<TypeParam> rotation = matrix_t<TypeParam>(2,2);
	TypeParam angle = 45;
	rotation(0,0) = cos(angle);
	rotation(0,1) = -sin(angle);
	rotation(1,0) = sin(angle);
	rotation(1,1) = cos(angle);
	
	matrix_t<TypeParam> vec1 = matrix_t<TypeParam>(2,1);
	matrix_t<TypeParam> vec2 = matrix_t<TypeParam>(2,1);
	matrix_t<TypeParam> vec3 = matrix_t<TypeParam>(2,1);
	
	vec1(0,0) = TypeParam(2);
	vec1(1,0) = TypeParam(4);
	vector_t<TypeParam> v1Rot = rotation*vec1;
	vec2(0,0) = TypeParam(1);
	vec2(1,0) = TypeParam(-2);
	vector_t<TypeParam> v2Rot = rotation*vec2;
	vec3(0,0) = TypeParam(-4);
	vec3(1,0) = TypeParam(1);
	vector_t<TypeParam> v3Rot = rotation*vec3;
	
	SupportFunction<TypeParam> res = psf1.linearTransformation(rotation);
	
	if(typeid(TypeParam) == typeid(double)) {
		EXPECT_EQ(true, carl::AlmostEqual2sComplement(TypeParam(20),res.evaluate(v1Rot).supportValue,4));
		EXPECT_EQ(true, carl::AlmostEqual2sComplement(TypeParam(5),res.evaluate(v2Rot).supportValue,4));
		EXPECT_EQ(true, carl::AlmostEqual2sComplement(TypeParam(17),res.evaluate(v3Rot).supportValue,4));
	} else {
		EXPECT_EQ(TypeParam(20),res.evaluate(v1Rot).supportValue);
		EXPECT_EQ(TypeParam(5),res.evaluate(v2Rot).supportValue);
		EXPECT_EQ(TypeParam(17),res.evaluate(v3Rot).supportValue);
	}
}

TYPED_TEST(SupportFunctionTest, contains) {

}