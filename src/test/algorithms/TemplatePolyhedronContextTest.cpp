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
#include "../../hypro/datastructures/HybridAutomaton.h"
#include "../../hypro/algorithms/reachability/contexts/TemplatePolyhedronContext.h"
#include "../../hypro/algorithms/reachability/handlers/firstSegmentHandlers/TPolyFirstSegmentHandler.h"

template<typename Number>
class TemplatePolyhedronContextTest : public ::testing::Test {

  protected:

	virtual void SetUp(){

		//Create 3D flow matrix for loc1
		flow = matrix_t<Number>(4,4);
		flow << 4,3,2,1,		//affine flow, should grow into infinity
				0,-2,-1,0,		//linear flow, should grow into -infinity
				0,0,0,-1,		//constant flow, should grow into -infinity
				0,0,0,0;

		//Create locations
		loc_no_inv = Location<Number>(flow);
		loc_partial_inv = Location<Number>(flow);
		loc_full_inv = Location<Number>(flow);

		//Create partial invariants and set them for loc_partial_inv
		partialInvMat = matrix<Number>(1,3);
		partialInvMat << 1,0,0;
		partialInvVec = vector_t<Number>(1);
		partialInvVec << 20;
		loc_partial_inv.setInvariant(Condition<Number>(partialInvMat,partialInvVec));

		//Create full invariants
		fullInvMat = matrix<Number>::Identity(3,3);
		fullInvVec = vector_t<Number>(3);
		fullInvVec << 40,-30,20;
		loc_full_inv.setInvariant(Condition<Number>(fullInvMat,fullInvVec));

		//Create Transitions
		auto no2partial = std::make_unique<Transition<Number>>(&loc_no_inv, &loc_partial_inv);	//No guard and reset
		auto 
		
	}

	virtual void TearDown(){}

	//Matrices and Vectors for invariants
	matrix<Number> partialInvMat;
	vector_t<Number> partialInvVec;
	matrix<Number> fullInvMat;
	vector_t<Number> fullInvVec;
	
	//Flow
	matrix_t<Number> flow;

	//Locations
	Location<Number> loc_no_inv;		//A location with no invariants
	Location<Number> loc_partial_inv;	//A location with invariants for some variables but not all
	Location<Number> loc_full_inv;		//A location with invariants for all variables

	//Transitions

	TemplatePolyhedronContext<State> tpcontext; //TODO

};

TYPED_TEST(TemplatePolyhedronContextTest, ExecBeforeFirstSegment){

}

TYPED_TEST(TemplatePolyhedronContextTest, TPolyFirstSegmentHandler){
	
}