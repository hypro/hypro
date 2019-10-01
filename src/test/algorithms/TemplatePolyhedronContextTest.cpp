/**
 * TemplatePolyhedronContextTest.cpp
 *
 * Test suite for TemplatePolyhedronContext.tpp and all the handlers it entails:
 * TPolyFirstSegmentHandler, TPolyContinuousEvolutionHandler
 *
 * @author Phillip Tse
 * @date 30.9.2019
 */

#include "gtest/gtest.h"
#include "../defines.h"
#include "../../hypro/algorithms/reachability/contexts/TemplatePolyhedronContext.h"
#include "../../hypro/algorithms/reachability/handlers/firstSegmentHandlers/TPolyFirstSegmentHandler.h"

template<typename Number>
class TemplatePolyhedronContextTest : public ::testing::Test {

  protected:

	virtual void SetUp(){}

	virtual void TearDown(){}

};

TYPED_TEST(TemplatePolyhedronContextTest, TemplatePolyhedronContext){

}

TYPED_TEST(TemplatePolyhedronContextTest, TPolyFirstSegmentHandler){
	
}