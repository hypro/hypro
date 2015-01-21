/**
 * Tests for SupportFunctions.
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 */

#include "gtest/gtest.h"
#include "../defines.h"
#include "../../lib/representations/SupportFunction/SupportFunction.h"


using namespace hypro;
using namespace carl;

template<typename Number>
class SupportFunctionTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        
    }
	
    virtual void TearDown()
    {
    }
	
};

TYPED_TEST(SupportFunctionTest, Constructor)
{
	SupportFunction<TypeParam> defConstr = SupportFunction<TypeParam>();
	SupportFunction<TypeParam> cpConstr = SupportFunction<TypeParam>(defConstr);
	SupportFunction<TypeParam> cpAssign = defConstr;
	
	SupportFunction<TypeParam> moveSource = SupportFunction<TypeParam>();
	SupportFunction<TypeParam> moveTarget(moveSource);
	
	moveSource = SupportFunction<TypeParam>();
	moveTarget = std::move(moveSource);
}

TYPED_TEST(SupportFunctionTest, Access)
{
	SupportFunction<TypeParam> base = SupportFunction<TypeParam>();
	base.addDirection(createVector<TypeParam>({2,3,1}), TypeParam(4));
	base.addDirection(createVector<TypeParam>(hypro::Point<TypeParam>{1,2,3}), TypeParam(5));
	
	std::cout << base << std::endl;
}