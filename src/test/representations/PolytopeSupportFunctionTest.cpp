/**
 * Tests for SupportFunctions.
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * 
 * @since		2015-01-20
 * @version		2015-01-22
 */

#include "../../lib/representations/SupportFunction/PolytopeSupportfunction.h"
#include "gtest/gtest.h"
#include "../defines.h"


using namespace hypro;
using namespace carl;

template<typename Number>
class PolytopeSupportFunctionTest : public ::testing::Test {
protected:
    virtual void SetUp() {
    }
	
    virtual void TearDown(){
    }
	
};

TYPED_TEST(PolytopeSupportFunctionTest, constructor) {
	matrix_t<TypeParam> constraints = matrix_t<TypeParam>::Zero(3,2);
	constraints(0,0) = TypeParam(2);
	constraints(0,1) = TypeParam(4);
	constraints(1,0) = TypeParam(1);
	constraints(1,1) = TypeParam(-2);
	constraints(2,0) = TypeParam(-4);
	constraints(2,1) = TypeParam(1);
	matrix_t<TypeParam> constants = matrix_t<TypeParam>(3,1);
	constants(0,0) = TypeParam(20);
	constants(1,0) = TypeParam(5);
	constants(2,0) = TypeParam(17);
	
	artificialDirections<TypeParam>* ad = new artificialDirections<TypeParam>();
	ad->dir1 = getZeroVector<TypeParam>(constraints.cols());
	ad->dir2 = getZeroVector<TypeParam>(constraints.cols());

	ad->dir1(constraints.cols()-1,0) = 1;
	ad->dir2(constraints.cols()-1,0) = -1;
	PolytopeSupportFunction<TypeParam> defConstr = PolytopeSupportFunction<TypeParam>(constraints, constants, operator_e::LEQ, 2, ad);
	delete ad;
}

TYPED_TEST(PolytopeSupportFunctionTest, access) {

}

TYPED_TEST(PolytopeSupportFunctionTest, linearTransformation) {

}

TYPED_TEST(PolytopeSupportFunctionTest, MinkowskiSum) {

}

TYPED_TEST(PolytopeSupportFunctionTest, contains) {

}