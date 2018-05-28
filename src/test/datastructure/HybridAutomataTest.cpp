/**
 * Testfile for hybrid automata.
 * Author: ckugler
 */

#include "gtest/gtest.h"
#include "../defines.h"
#include "datastructures/HybridAutomaton/LocationManager.h"
#include "datastructures/HybridAutomaton/HybridAutomaton.h"
#include "representations/GeometricObject.h"


using namespace hypro;
using namespace carl;

template <typename Number>
using valuation_t = VPolytope<Number>;

template<typename Number>
class HybridAutomataTest : public ::testing::Test
{
/**
 * Test Setup:
 * one hybrid automaton which consists of two locations that are connected by one transition
 */
protected:
    virtual void SetUp()
    {
      	/*
		 * Location Setup
		 */

		//loc1 = locMan.create();
    	//loc2 = locMan.create();

    	std::cout << "a\n";
    	//loc1.reset(locMan.create());
    	//loc2.reset(locMan.create());
    	loc1 = std::make_unique<Location<Number>>();
    	loc2 = std::make_unique<Location<Number>>();

    	std::cout << "b\n";
    	trans = std::make_unique<Transition<Number>>();
    	copyOfTrans = std::make_unique<Transition<Number>>();

    	std::cout << "c\n";
		invariantVec(0) = 10;
		invariantVec(1) = 20;

		invariantMat(0,0) = 2;
		invariantMat(0,1) = 0;
		invariantMat(1,0) = 0;
		invariantMat(1,1) = 3;

		std::cout << "d\n";
		loc1->setInvariant(Condition<Number>(invariantMat,invariantVec));
		loc1->setName("Location1");

		inv.setMatrix(invariantMat);
		inv.setVector(invariantVec);

		std::cout << "e\n";
		loc2->setInvariant(inv);
		loc2->setName("Location2");

		locationMat(0,0) = 2;
		locationMat(0,1) = 0;
		locationMat(1,0) = 0;
		locationMat(1,1) = 1;

		loc1->setFlow(locationMat);
		loc2->setFlow(locationMat);

		std::cout << "f\n";
		//copyOfLoc1 = std::make_unique<Location<Number>>(loc1.get());
		//Location<Number>* tmp1 = new Location<Number>(loc1.get());
		//copyOfLoc1.reset(tmp1);
		copyOfLoc1 = std::unique_ptr<Location<Number>>(new Location<Number>(*loc1));
		std::cout << "g\n";
		//copyOfLoc2 = std::make_unique<Location<Number>>(loc2.get());
		copyOfLoc2 = std::unique_ptr<Location<Number>>(new Location<Number>(*loc2));
		//Location<Number>* tmp2 = new Location<Number>(loc2.get());
		//copyOfLoc2.reset(tmp2);
		

		//Location<Number>* tmp1 = locMan.create(loc1.get());
		//copyOfLoc1.reset(tmp1);
		
		//Location<Number>* tmp2 = locMan.create(loc2.get());
		//copyOfLoc2.reset(tmp2);

		//Location<Number>* tmp1 = locMan.location(loc1->getId());
		//copyOfLoc1 = std::make_unique<Location<Number>>(locMan.create(loc1.get()));
		//Location<Number>* tmp2 = locMan.location(loc2->getId());
		//tmp2->setName("gna");
		//copyOfLoc2 = std::make_unique<Location<Number>>(locMan.create(loc2.get()));
		std::cout << "h\n";
		//copyOfLoc1.reset(tmp1);
		std::cout << "i\n";
    	//copyOfLoc2.reset(tmp2);
    	if(copyOfLoc1 == nullptr){
    		std::cout << "copyOfLoc1 is nullptr\n";
    	} else {
    		std::cout << "Name of loc is: " << copyOfLoc1->getName() << std::endl;
    	}
    	if(copyOfLoc2 == nullptr){
    		std::cout << "copyOfLoc2 is nullptr\n";
    	} else {
    		std::cout << "Name of loc is: " << copyOfLoc2->getName() << std::endl;
    	}
    	if(loc1 == nullptr){
    		std::cout << "loc1 is nullptr\n";
    	} else {
    		std::cout << "Name of loc is: " << loc1->getName() << std::endl;
    	}
    	if(loc2 == nullptr){
    		std::cout << "loc2 is nullptr\n";
    	} else {
    		std::cout << "Name of loc is: " << loc2->getName() << std::endl;
    	}

		/*
		 * Transition Setup
		 */
		guard.setMatrix(inv.getMatrix());
		guard.setVector(inv.getVector());

		reset.setMatrix(inv.getMatrix());
		reset.setVector(inv.getVector());

		trans->setGuard(guard);
		trans->setSource(loc1);
		trans->setTarget(loc2);
		trans->setReset(reset);

		copyOfTrans->setGuard(guard);
		copyOfTrans->setSource(loc1);
		copyOfTrans->setTarget(loc2);
		copyOfTrans->setReset(reset);

		/*
		 * Hybrid Automaton Setup
		 */

		std::cout << "j\n";
		initLocSet.insert(loc1.get());
		locSet.insert(std::move(copyOfLoc1));
		locSet.insert(std::move(copyOfLoc2));
		std::cout << "k\n";
		if(copyOfLoc1 == nullptr){
    		std::cout << "copyOfLoc1 is nullptr\n";
    	} else {
    		std::cout << "Name of loc is: " << copyOfLoc1->getName() << std::endl;
    	}
    	if(copyOfLoc2 == nullptr){
    		std::cout << "copyOfLoc2 is nullptr\n";
    	} else {
    		std::cout << "Name of loc is: " << copyOfLoc2->getName() << std::endl;
    	}
    	if(loc1 == nullptr){
    		std::cout << "loc1 is nullptr\n";
    	} else {
    		std::cout << "Name of loc is: " << loc1->getName() << std::endl;
    	}
    	if(loc2 == nullptr){
    		std::cout << "loc2 is nullptr\n";
    	} else {
    		std::cout << "Name of loc is: " << loc2->getName() << std::endl;
    	}

		//locations[0] = loc1;
		//locations[1] = loc2;

		//locSet = std::set<Location<Number>*>(locations, locations+2);
		//init[0] = loc1;
		//initLocSet = std::set<Location<Number>*>(init, init+1);

		//Polytope for InitialValuation & Guard Assignment
		coordinates(0) = 2;
		coordinates(1) = 3;
		std::cout << "k1\n";		
    	std::vector< vector_t<Number> > vecSet;
    	vecSet.push_back(coordinates);
    	std::cout << "k2\n";
		poly = valuation_t<Number>(vecSet);
		auto hpoly = Converter<Number>::toHPolytope(poly);

		std::cout << "l\n";
		hybrid.setLocations(locSet);
		for(auto loc : initLocSet) {
			State_t<Number> initState(loc);
			initState.setSet(ConstraintSet<Number>(hpoly.matrix(), hpoly.vector()));
			hybrid.addInitialState(initState);
		}
		std::cout << "m\n";
		transSet.insert(std::move(copyOfTrans));
		ptrSet.insert(transSet.begin()->get());
		std::cout << "n\n";
		hybrid.setTransitions(transSet);
		loc1->setTransitions(ptrSet);
		std::cout << "o\n";

    }

    virtual void TearDown()
    { 	
    	//delete loc1;
    	//delete loc2;
    	//delete trans;
    }

    //Hybrid Automaton Objects: Locations, Transitions, Automaton itself

    //LocationManager<Number>& locMan = LocationManager<Number>::getInstance();

    std::unique_ptr<Location<Number>> loc1;
    std::unique_ptr<Location<Number>> loc2;
    std::unique_ptr<Location<Number>> copyOfLoc1;
    std::unique_ptr<Location<Number>> copyOfLoc2;
    std::unique_ptr<Transition<Number>> trans;
    std::unique_ptr<Transition<Number>> copyOfTrans;
    HybridAutomaton<Number> hybrid;

    //Other Objects: Vectors, Matrices, Guards...
    vector_t<Number> invariantVec = vector_t<Number>(2,1);
    matrix_t<Number> invariantMat = matrix_t<Number>(2,2);
	Condition<Number> inv;
	matrix_t<Number> locationMat = matrix_t<Number>(2,2);

    Condition<Number> guard;

    Reset<Number> reset;

    //Location<Number>* locations[2];
    //std::set<Location<Number>*> locSet;
    std::set<std::unique_ptr<Location<Number>>> locSet;

    //Location<Number>* init[1];
    std::set<Location<Number>*> initLocSet;

    std::set<std::unique_ptr<Transition<Number>>> transSet;
    std::set<Transition<Number>*> ptrSet;

	vector_t<Number> coordinates = vector_t<Number>(2,1);
    valuation_t<Number> poly;

  public:

  	bool find(const std::unique_ptr<Location<Number>>& loc, const std::set<std::unique_ptr<Location<Number>>>& locSet) const {
  		if(loc == nullptr || locSet.empty()){
  			std::cout << "loc was nullptr or locSet was empty\n";
  			return false;
  		}
  		std::cout << "locSet size: " << locSet.size() << std::endl;
  		std::cout << "loc has hash: " << loc->hash() << std::endl;
		for(auto& ptrToALoc : locSet){
			std::cout << "ptrToALoc loc hash is: " << ptrToALoc->hash() << std::endl;
			if(*ptrToALoc == *(loc)){
				std::cout << "found a match!\n";
				return true;
			}
		}
		std::cout << "found no match.\n";
		return false;
  	}
  	
  	bool find(const std::unique_ptr<Transition<Number>>& trans, const std::set<std::unique_ptr<Transition<Number>>>& transSet) const {
  		if(trans == nullptr || transSet.empty())
  			return false;
		for(auto& ptrToTrans : transSet){
			if(*ptrToTrans == *(trans)){
				return true;
			}
		}
		return false;
  	}


};

/**
 * Location Test
 */
TYPED_TEST(HybridAutomataTest, LocationTest)
{
	std::cout << "1\n";

    //invariant: vector
    EXPECT_EQ(this->loc1->getInvariant().getVector(), this->invariantVec);
    std::cout << "2\n";
    EXPECT_EQ(this->loc2->getInvariant().getVector(), this->invariantVec);
    std::cout << "3\n";

	vector_t<TypeParam> invariantVec2(2,1);
	invariantVec2(0) = 10;
	invariantVec2(1) = 10;
	EXPECT_NE(this->loc1->getInvariant().getVector(), invariantVec2);
	std::cout << "4\n";

	//invariant: matrix
	EXPECT_EQ(this->loc1->getInvariant().getMatrix(), this->invariantMat);
	EXPECT_EQ(this->loc2->getInvariant().getMatrix(), this->invariantMat);
	std::cout << "5\n";

	matrix_t<TypeParam> invariantMat2(2,2);
	invariantMat2(0,0) = 1;
	invariantMat2(0,1) = 0;
	invariantMat2(1,0) = 0;
	invariantMat2(1,1) = 3;
	EXPECT_NE(this->loc1->getInvariant().getMatrix(), invariantMat2);
	std::cout << "6\n";

	//location: matrix
	EXPECT_EQ(this->loc1->getFlow(), this->locationMat);
	std::cout << "7\n";

	matrix_t<TypeParam> locationMat2(2,2);
	locationMat2(0,0) = 1;
	locationMat2(0,1) = 0;
	locationMat2(1,0) = 0;
	locationMat2(1,1) = 1;
	EXPECT_NE(this->loc1->getFlow(), locationMat2);
	std::cout << "8\n";

	//location: set of outgoing transitions
	EXPECT_EQ(this->loc1->getTransitions(), this->ptrSet);
	std::cout << "9\n";

	EXPECT_TRUE(*this->loc1 < *this->loc2);
	EXPECT_FALSE(*this->loc2 < *this->loc1);
	std::cout << "10\n";

	EXPECT_TRUE(locPtrComp<TypeParam>()(this->loc1, this->loc2));
	std::cout << "11\n";
}

TYPED_TEST(HybridAutomataTest, LocationParallelcompositionTest)
{
	//Location<TypeParam>* l1 = this->locMan.create();
	//Location<TypeParam>* l2 = this->locMan.create();

	//std::unique_ptr<Location<TypeParam>> l1 (this->locMan.create());
	//std::unique_ptr<Location<TypeParam>> l2 (this->locMan.create());

	std::unique_ptr<Location<TypeParam>> l1 = std::make_unique<Location<TypeParam>>();
	std::unique_ptr<Location<TypeParam>> l2 = std::make_unique<Location<TypeParam>>();

	typename HybridAutomaton<TypeParam>::variableVector l1Vars{"a","b"};
	typename HybridAutomaton<TypeParam>::variableVector l2Vars{"x","b"};
	typename HybridAutomaton<TypeParam>::variableVector haVars{"a","x","b"};

	matrix_t<TypeParam> l1Flow = matrix_t<TypeParam>::Zero(3,3);
	l1Flow << 1,2,0,
				3,4,0,
				0,0,0;
	matrix_t<TypeParam> l2Flow = matrix_t<TypeParam>::Zero(3,3);
	l2Flow << 1,2,0,
				3,4,0,
				0,0,0;

	l1->setFlow(l1Flow);
	l2->setFlow(l2Flow);

	//Location<TypeParam>* res1 = parallelCompose(l1,l2,l1Vars,l2Vars,haVars);
	std::unique_ptr<Location<TypeParam>> res1 = parallelCompose(l1,l2,l1Vars,l2Vars,haVars);
	matrix_t<TypeParam> expectedResult1 = matrix_t<TypeParam>::Zero(haVars.size()+1, haVars.size()+1);
	expectedResult1 << 1,0,2,0,
						0,1,2,0,
						3,3,4,0,
						0,0,0,0;
	EXPECT_EQ(res1->getFlow(),expectedResult1);


	l1Vars = {"a","b"};
	l2Vars = {"c","d"};
	haVars = {"a","b","c","d"};
	std::unique_ptr<Location<TypeParam>> res2 = parallelCompose(l1,l2,l1Vars,l2Vars,haVars);
	//Location<TypeParam>* res2 = parallelCompose(l1,l2,l1Vars,l2Vars,haVars);

	matrix_t<TypeParam> expectedResult2 = matrix_t<TypeParam>::Zero(haVars.size()+1, haVars.size()+1);
	expectedResult2 << 1,2,0,0,0,
						3,4,0,0,0,
						0,0,1,2,0,
						0,0,3,4,0,
						0,0,0,0,0;
	EXPECT_EQ(res2->getFlow(),expectedResult2);
}

/**
 * Transition Test
 */
TYPED_TEST(HybridAutomataTest, TransitionTest)
{
	//transition: Start Location
	EXPECT_EQ(this->trans->getSource(), this->loc1.get());

	//transition: End Location
	EXPECT_EQ(this->trans->getTarget(), this->loc2.get());

	//transition: Assignment
	EXPECT_EQ(this->trans->getReset().getVector(), this->reset.getVector());
	EXPECT_EQ(this->trans->getReset().getMatrix(), this->reset.getMatrix());

	//transition: Guard
	EXPECT_EQ(this->trans->getGuard().getVector(), this->guard.getVector());
	EXPECT_EQ(this->trans->getGuard().getMatrix(), this->guard.getMatrix());

	// creation of transitions from source and target
	std::unique_ptr<Transition<TypeParam>> t(new Transition<TypeParam>(this->loc1.get(), this->loc2.get()));
	EXPECT_EQ(t->getSource(), this->loc1.get());
	EXPECT_EQ(t->getTarget(), this->loc2.get());
	EXPECT_EQ(t->getAggregation(), Aggregation::none);
	EXPECT_FALSE(t->isTimeTriggered());
	t->setAggregation(Aggregation::boxAgg);
	EXPECT_EQ(t->getAggregation(), Aggregation::boxAgg);

	t->setTriggerTime(TypeParam(1));
	EXPECT_TRUE(t->isTimeTriggered());
	EXPECT_EQ(t->getTriggerTime(), TypeParam(1));
}

/**
 * Hybrid Automaton Test
 */
TYPED_TEST(HybridAutomataTest, HybridAutomatonTest)
{
	// construct a new hybrid automaton.
	HybridAutomaton<TypeParam> h1;

	//std::unique_ptr<Location<Number>> anotherCopyOfLoc1(new Location<TypeParam>(*(this->loc1)));
	//std::unique_ptr<Location<Number>> anotherCopyOfLoc2(new Location<TypeParam>(*(this->loc2)));

	//h1.addLocation(this->loc1);
	//h1.addLocation(this->loc2);

	//Location<TypeParam>* ptrToLoc1 = this->locMan.create(this->loc1.get());
	//Location<TypeParam>* ptrToLoc2 = this->locMan.create(this->loc2.get());

	Location<TypeParam>* ptrToLoc1 = this->loc1.get();
	Location<TypeParam>* ptrToLoc2 = this->loc2.get();

	std::unique_ptr<Location<TypeParam>> anotherCopyOfLoc1(new Location<TypeParam>(*ptrToLoc1));
	std::unique_ptr<Location<TypeParam>> anotherCopyOfLoc2(new Location<TypeParam>(*ptrToLoc2));
	
	std::cout << "loc1 name: " << this->loc1->getName() << " hash: " << this->loc1->hash() << std::endl;
	std::cout << "loc2 name: " << this->loc2->getName() << " hash: " << this->loc2->hash() << std::endl;
	std::cout << "anotherCopyOfLoc1 name: " << anotherCopyOfLoc1->getName() << " hash: " << anotherCopyOfLoc1->hash() << std::endl;
	std::cout << "anotherCopyOfLoc2 name: " << anotherCopyOfLoc2->getName() << " hash: " << anotherCopyOfLoc2->hash() << std::endl;

	h1.addLocation(std::move(anotherCopyOfLoc1));
	h1.addLocation(std::move(anotherCopyOfLoc2));

	EXPECT_TRUE(this->find(this->loc1, h1.getLocations()));
	EXPECT_TRUE(this->find(this->loc2, h1.getLocations()));

	//EXPECT_TRUE(std::find(h1.getLocations().begin(), h1.getLocations().end(), this->loc1) != h1.getLocations().end());
	//EXPECT_TRUE(std::find(h1.getLocations().begin(), h1.getLocations().end(), this->loc2) != h1.getLocations().end());

	//std::cout << "h1 getLocation via name Location1 with id hash " << h1.getLocation("Location1")->hash() << "\n";
	//std::cout << "this loc1.get() with hash " << this->loc1->hash() << "\n";

	EXPECT_TRUE(h1.getLocation("Location1") != nullptr);
	EXPECT_TRUE(this->loc1.get() != nullptr);
	EXPECT_TRUE(*(h1.getLocation("Location1")) == *(this->loc1.get()));
	EXPECT_TRUE(*(h1.getLocation(this->loc1->hash())) == *(this->loc1.get()));

	//std::cout << "h1 getLocation via name Location2 with id hash " << h1.getLocation("Location2")->hash() << "\n";
	//std::cout << "this loc1.get() with hash " << this->loc2->hash() << "\n";

	EXPECT_TRUE(*(h1.getLocation("Location2")) == *(this->loc2.get()));
	EXPECT_TRUE(*(h1.getLocation(this->loc2->hash())) == *(this->loc2.get()));

	//Check if trans can be found in h1's transition set after inserting
	std::unique_ptr<Transition<TypeParam>> aTrans(new Transition<TypeParam>(*(this->trans)));
	EXPECT_FALSE(aTrans == nullptr);
	h1.addTransition(std::move(aTrans));
	EXPECT_TRUE(aTrans == nullptr);
	EXPECT_TRUE(this->find(this->trans, h1.getTransitions()));
	
	//bool found = false;
	//for(auto& ptrToTrans : h1.getTransitions()){
	//	if(*ptrToTrans == *(this->trans)){
	//		found = true;
	//	}
	//}
	//if(!found){
	//	std::cout << "Transition could not found after inserting it.\n";
	//	FAIL();
	//}

	matrix_t<TypeParam> matr = matrix_t<TypeParam>::Identity(2,2);
	vector_t<TypeParam> vec = vector_t<TypeParam>(2);
	vec << 1,2;

	State_t<TypeParam> s(this->loc1.get());
	s.setSet(ConstraintSet<TypeParam>(matr, vec));

	h1.addInitialState(s);

	// copy assignment operator
	HybridAutomaton<TypeParam> h2 = h1;
	EXPECT_EQ(h1, h2);

	// somehow check move assignment
	HybridAutomaton<TypeParam> h3 = std::move(h1);
	EXPECT_TRUE(h1.getTransitions().size() == 0);
	EXPECT_EQ(h2, h3);
}

/*
TYPED_TEST(HybridAutomataTest, LocationManagerTest)
{
	matrix_t<TypeParam> flow = matrix_t<TypeParam>::Identity(2,2);
	Location<TypeParam>* loc = this->locMan.create(flow);
	EXPECT_EQ(loc->getFlow(), flow);

	unsigned id = this->locMan.id(loc);
	EXPECT_EQ(this->locMan.location(id), loc);
}
*/

TYPED_TEST(HybridAutomataTest, State) {
	// Constructors
	State_t<TypeParam> s1(this->loc1.get());

	matrix_t<TypeParam> matr = matrix_t<TypeParam>::Identity(2,2);
	vector_t<TypeParam> vec = vector_t<TypeParam>(2);
	vec << 1,2;
	State_t<TypeParam> s2(this->loc1.get());
	s2.setSet(ConstraintSet<TypeParam>(matr, vec));

	EXPECT_EQ(s1.getLocation()->getId(), this->loc1->getId());
	EXPECT_EQ(s2.getLocation()->getId(), this->loc1->getId());
	EXPECT_EQ(boost::get<ConstraintSet<TypeParam>>(s2.getSet()).matrix(), matr);
	EXPECT_EQ(boost::get<ConstraintSet<TypeParam>>(s2.getSet()).vector(), vec);
	EXPECT_EQ(boost::get<ConstraintSet<TypeParam>>(s2.getSet(0)).matrix(), matr);
	EXPECT_EQ(boost::get<ConstraintSet<TypeParam>>(s2.getSet(0)).vector(), vec);
}
