/**
 * TemplatePolyhedronContextTest.cpp
 *
 * Test suite for TemplatePolyhedronContext.tpp and all the handlers it entails:
 * TPolyFirstSegmentHandler, TPolyContinuousEvolutionHandler
 *
 * @author Phillip Tse
 * @date 30.9.2019
 */
 
#include "../defines.h"
#include "../../hypro/representations/GeometricObject.h"
#include "../../hypro/datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../../hypro/algorithms/reachability/contexts/TemplatePolyhedronContext.h"
//#include "../../hypro/algorithms/reachability/handlers/firstSegmentHandlers/TPolyFirstSegmentHandler.h"
#include "gtest/gtest.h"

using namespace hypro;

template<typename Number>
class TemplatePolyhedronContextTest : public ::testing::Test {

  protected:

	virtual void SetUp(){

		//Initialize Location
		flow = matrix_t<Number>::Zero(3,3);
		flow << 3,2,1,		//affine flow, should grow into infinity
				0,-2,-1,	//linear flow, should grow into -infinity
				0,0,0;
		invMat = -matrix_t<Number>::Zero(2,2);
		invVec = 10*vector_t<Number>::Ones(2);
		inv = Condition<Number>(invMat, invVec);
		loc = Location<Number>(flow);
		loc.setInvariant(inv);
		loc.setName("blub");

		//Initialize tpoly
		mat = matrix_t<Number>::Zero(3,2);
		mat << -1,2,
				1,2,
				0,-1;
		vec = vector_t<Number>::Zero(3);
		vec << 0,2,0;
		tpoly = TemplatePolyhedronT<Number,hypro::Converter<Number>,TemplatePolyhedronDefault>(mat,vec);

/*
		//Needed to initialize task
		//state = State_t<Number>(tpoly);
		//state.setLocation(&loc);
		state = State_t<Number>(&loc);
		state.setSet(tpoly,0);
		rnode = ReachTreeNode<State_t<Number>>(state,0);
		task = std::make_shared<Task<State_t<Number>>>(&rnode);
*/
		//Initialize tpcontext
		strat = Strategy<State_t<Number>>();
		localQueue = nullptr;
		localCEXQueue = nullptr;
		localSegments = Flowpipe<State_t<Number>>();
		settings = ReachabilitySettings();
		//tpcontext = TemplatePolyhedronContext<State_t<Number>>(task,strat,localQueue,localCEXQueue,settings);
	}

	virtual void TearDown(){}

	//Location members - Needed to create State
	matrix_t<Number> flow;
	matrix_t<Number> invMat;
	vector_t<Number> invVec;
	Condition<Number> inv;
	Location<Number> loc;
	
	//Template Polyhedron members - Needed to create State
	matrix_t<Number> mat;
	vector_t<Number> vec;
	TemplatePolyhedronT<Number,hypro::Converter<Number>,TemplatePolyhedronDefault> tpoly;

	//Needed to create Task
	//State_t<Number> state;
	//ReachTreeNode<State_t<Number>> rnode;
	//std::shared_ptr<Task<State_t<Number>>> task;

	//Needed to create tpcontext
	Strategy<State_t<Number>> strat;
	WorkQueue<std::shared_ptr<Task<State_t<Number>>>>* localQueue;
	WorkQueue<std::shared_ptr<Task<State_t<Number>>>>* localCEXQueue;
	Flowpipe<State_t<Number>> localSegments;
	ReachabilitySettings settings;

	//The thing we want to test
	//TemplatePolyhedronContext<State_t<Number>> tpcontext;
};

TYPED_TEST(TemplatePolyhedronContextTest, GradientOfLinearFunction){

	//Initialize tpcontext
	//NOTE: This must be copied into every test since ReachTreeNodes cannot be copy assigned and therefore cannot be a member of the test
	State_t<TypeParam> state(&(this->loc));
	state.setSet(this->tpoly,0);
	ReachTreeNode<State_t<TypeParam>> rnode(state,(unsigned)0);
	auto task = std::make_shared<Task<State_t<TypeParam>>>(&rnode);
	TemplatePolyhedronContext<State_t<TypeParam>> tpcontext(task,this->strat,this->localQueue,this->localCEXQueue,this->localSegments,this->settings);

	//Zero function - Given the vector (0,0,0), so the function f = 0*x + 0*y + 0, the gradient is (df/dx, df/dy, 0) and thus (0,0,0)
	//NOTE: the last 0 is just an extension needed for the other computations within TemplatePolyhedronContext
	vector_t<TypeParam> zeroFunction = vector_t<TypeParam>::Zero(3);
	EXPECT_EQ(tpcontext.gradientOfLinearFct(zeroFunction), zeroFunction);
	
	//Constant fct
	vector_t<TypeParam> testFunction = zeroFunction;
	testFunction(2) = TypeParam(1000);
	EXPECT_EQ(tpcontext.gradientOfLinearFct(testFunction), zeroFunction);

	//multivariate linear fct
	testFunction << 100,200,300;
	auto res = tpcontext.gradientOfLinearFct(testFunction);
	EXPECT_EQ(res(0), testFunction(0));
	EXPECT_EQ(res(1), testFunction(1));
	EXPECT_EQ(res(2), 0);
}

TYPED_TEST(TemplatePolyhedronContextTest, LieDerivative){

	//Initialize tpcontext
	//NOTE: This must be copied into every test since ReachTreeNodes cannot be copy assigned and therefore cannot be a member of the test
	State_t<TypeParam> state(&(this->loc));
	state.setSet(this->tpoly,0);
	ReachTreeNode<State_t<TypeParam>> rnode(state,(unsigned)0);
	auto task = std::make_shared<Task<State_t<TypeParam>>>(&rnode);
	TemplatePolyhedronContext<State_t<TypeParam>> tpcontext(task,this->strat,this->localQueue,this->localCEXQueue,this->localSegments,this->settings);

	//Zero function
	vector_t<TypeParam> zeroFunction = vector_t<TypeParam>::Zero(2);
	EXPECT_EQ(tpcontext.lieDerivative(zeroFunction).first, zeroFunction);
	EXPECT_EQ(tpcontext.lieDerivative(zeroFunction).second, 0);

	//Constant function - Not possible right now since we extend the given function within the lieDerivative() function

	//Multivariate linear fct
	vector_t<TypeParam> testFunction = zeroFunction;
	testFunction << 1,2;
	auto res = tpcontext.lieDerivative(testFunction);
	EXPECT_EQ(res.first(0), 3);
	EXPECT_EQ(res.first(1), -2);
	EXPECT_EQ(res.second, -1);
}

TYPED_TEST(TemplatePolyhedronContextTest, PositiveInvariant){
	


}

TYPED_TEST(TemplatePolyhedronContextTest, CreateTemplateContent){
	SUCCEED();
}

TYPED_TEST(TemplatePolyhedronContextTest, LocationInvariantStrengthening){
	SUCCEED();
}

TYPED_TEST(TemplatePolyhedronContextTest, ExecBeforeFirstSegment){
	SUCCEED();
}

TYPED_TEST(TemplatePolyhedronContextTest, FirstSegment){
	SUCCEED();
}

TYPED_TEST(TemplatePolyhedronContextTest, ApplyContinuousEvolution){
	SUCCEED();
}

TYPED_TEST(TemplatePolyhedronContextTest, Reachability){
	SUCCEED();
}

//TYPED_TEST(TemplatePolyhedronContextTest, TPolyFirstSegmentHandler){
//	
//}


//Unit Tests: Instantiation, Every handler, 

//Integration Tests: One Reachability Analysis, 