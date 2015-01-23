/**
 * Tests for SupportFunctions.
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * 
 * @since		2015-01-20
 * @version		2015-01-22
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
        
    }
	
    virtual void TearDown(){
    }
	
};

TYPED_TEST(SupportFunctionTest, constructor) {
	SupportFunction<TypeParam> defConstr = SupportFunction<TypeParam>();
	SupportFunction<TypeParam> cpConstr = SupportFunction<TypeParam>(defConstr);
	SupportFunction<TypeParam> cpAssign = defConstr;
	
	SupportFunction<TypeParam> moveSource = SupportFunction<TypeParam>();
	SupportFunction<TypeParam> moveTarget(moveSource);
	
	moveSource = SupportFunction<TypeParam>();
	moveTarget = std::move(moveSource);
}

TYPED_TEST(SupportFunctionTest, access) {
	SupportFunction<TypeParam> base = SupportFunction<TypeParam>();
	base.addDirection(createVector<TypeParam>({2,3,1}), TypeParam(4));
	base.addDirection(createVector<TypeParam>(hypro::Point<TypeParam>{1,2,3}), TypeParam(5));
	
	EXPECT_EQ(base.dimension(), unsigned(3));
	
	std::cout << base << std::endl;
}

TYPED_TEST(SupportFunctionTest, linearTransformation) {
	vector_t<TypeParam> oldDir = createVector<TypeParam>({2,3,1});
	SupportFunction<TypeParam> base = SupportFunction<TypeParam>();
	base.addDirection(oldDir, TypeParam(4));
	
	// identity trafo
	matrix_t<TypeParam> trafoMatrix1;
	trafoMatrix1.setZero(3,3);
	trafoMatrix1(0,0) = TypeParam(1);
	trafoMatrix1(1,1) = TypeParam(1);
	trafoMatrix1(2,2) = TypeParam(1);
	
	SupportFunction<TypeParam> result = SupportFunction<TypeParam>();
	base.linearTransformation(result,trafoMatrix1);
	vector_t<TypeParam> newDir = *(result.directions().begin());
	EXPECT_EQ(oldDir, newDir);
	
	// rotation, 90 degrees, x-axis
	matrix_t<TypeParam> trafoMatrix2;
	trafoMatrix2.setZero(3,3);
	
	trafoMatrix2(0,0) = TypeParam(1);
	trafoMatrix2(1,1) = cos(TypeParam(90));
	trafoMatrix2(1,2) = -sin(TypeParam(90));
	trafoMatrix2(2,1) = sin(TypeParam(90));
	trafoMatrix2(2,2) = cos(TypeParam(90));
	
	base.linearTransformation(result,trafoMatrix2);
	newDir = *(result.directions().begin());
	
	EXPECT_EQ(trafoMatrix2.transpose()*createVector<TypeParam>({2,3,1}), newDir);
}

TYPED_TEST(SupportFunctionTest, MinkowskiSum) {
	vector_t<TypeParam> dir1 = createVector<TypeParam>({2,3});
	vector_t<TypeParam> dir2 = createVector<TypeParam>({-4,8});
	vector_t<TypeParam> dir3 = createVector<TypeParam>({1,-6});
	vector_t<TypeParam> dir4 = createVector<TypeParam>({-6,-2});
	
	vector_t<TypeParam> dir5 = createVector<TypeParam>({4,7});
	vector_t<TypeParam> dir6 = createVector<TypeParam>({-1,-3});
	vector_t<TypeParam> dir7 = createVector<TypeParam>({-1,5});
	
	SupportFunction<TypeParam> lhs = SupportFunction<TypeParam>();
	SupportFunction<TypeParam> rhs = SupportFunction<TypeParam>();
	SupportFunction<TypeParam> result = SupportFunction<TypeParam>();
	SupportFunction<TypeParam> result2 = SupportFunction<TypeParam>();
	
	lhs.addDirection(dir1, 1);
	lhs.addDirection(dir2, 2);
	lhs.addDirection(dir3, 3);
	lhs.addDirection(dir4, 4);
	
	rhs.addDirection(dir5, 5);
	rhs.addDirection(dir6, 6);
	rhs.addDirection(dir7, 7);
	
	result.addDirection(dir1, 1);
	result.addDirection(dir2, 2);
	result.addDirection(dir3, 3);
	result.addDirection(dir4, 4);
	result.addDirection(dir5, 5);
	result.addDirection(dir6, 6);
	result.addDirection(dir7, 7);
	
	lhs.minkowskiSum(result2, rhs);
	EXPECT_EQ(result, result2);
}

TYPED_TEST(SupportFunctionTest, contains) {
	vector_t<TypeParam> dir1 = createVector<TypeParam>({2,4});
	vector_t<TypeParam> dir2 = createVector<TypeParam>({-4,1});
	vector_t<TypeParam> dir3 = createVector<TypeParam>({1,-6});
	
	SupportFunction<TypeParam> set;
	
	set.addDirection(dir1, 20);
	set.addDirection(dir2, 17);
	set.addDirection(dir3, 37);
	
	EXPECT_TRUE(set.contains(hypro::Point<TypeParam>({2,4})));
	EXPECT_TRUE(set.contains(hypro::Point<TypeParam>({-4,1})));
	EXPECT_TRUE(set.contains(hypro::Point<TypeParam>({1,-6})));
	EXPECT_TRUE(set.contains(hypro::Point<TypeParam>({0,0})));
	EXPECT_TRUE(set.contains(hypro::Point<TypeParam>({0,4})));
	EXPECT_TRUE(set.contains(hypro::Point<TypeParam>({0,-2})));
	
	EXPECT_FALSE(set.contains(hypro::Point<TypeParam>({2,4.1})));
}