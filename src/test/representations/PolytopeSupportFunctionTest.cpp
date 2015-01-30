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
	matrix_t<TypeParam> constraints = matrix_t<TypeParam>::Zero(2,2);
	artificialDirections<TypeParam>* ad = new artificialDirections<TypeParam>();
	PolytopeSupportFunction<TypeParam> defConstr = PolytopeSupportFunction<TypeParam>(constraints, constraints, operator_e::GEQ, 2, ad);
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