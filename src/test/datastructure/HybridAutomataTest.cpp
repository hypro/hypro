/**
 * Testfile for hybrid automata.
 * Author: ckugler
 */

#include "../defines.h"
#include "gtest/gtest.h"
#include <hypro/datastructures/HybridAutomaton/HybridAutomaton.h>
#include <hypro/datastructures/HybridAutomaton/State.h>
#include <hypro/representations/GeometricObjectBase.h>

using namespace hypro;

template <typename Number>
using valuation_t = VPolytope<Number>;

template <typename Number>
class HybridAutomataTest : public ::testing::Test {
	/**
	 * Test Setup:
	 * one hybrid automaton which consists of two locations that are connected by one transition
	 */
  protected:
	virtual void SetUp() {
		/*
		 * Location Setup
		 */

		loc1 = std::make_unique<Location<Number>>();
		loc2 = std::make_unique<Location<Number>>();

		trans = std::make_unique<Transition<Number>>();
		copyOfTrans = std::make_unique<Transition<Number>>();

		invariantVec( 0 ) = 10;
		invariantVec( 1 ) = 20;

		invariantMat( 0, 0 ) = 2;
		invariantMat( 0, 1 ) = 0;
		invariantMat( 1, 0 ) = 0;
		invariantMat( 1, 1 ) = 3;

		loc1->setInvariant( Condition<Number>( invariantMat, invariantVec ) );
		loc1->setName( "Location1" );

		inv.setMatrix( invariantMat );
		inv.setVector( invariantVec );

		loc2->setInvariant( inv );
		loc2->setName( "Location2" );

		locationMat( 0, 0 ) = 2;
		locationMat( 0, 1 ) = 0;
		locationMat( 1, 0 ) = 0;
		locationMat( 1, 1 ) = 1;

		loc1->setLinearFlow( locationMat );
		loc2->setLinearFlow( locationMat );

		copyOfLoc1 = std::make_unique<Location<Number>>( *loc1 );
		copyOfLoc2 = std::make_unique<Location<Number>>( *loc2 );

		/*
		 * Transition Setup
		 */
		guard.setMatrix( inv.getMatrix() );
		guard.setVector( inv.getVector() );

		reset.setMatrix( inv.getMatrix() );
		reset.setVector( inv.getVector() );

		trans->setGuard( guard );
		trans->setSource( loc1 );
		trans->setTarget( loc2 );
		trans->setReset( reset );

		copyOfTrans->setGuard( guard );
		copyOfTrans->setSource( copyOfLoc1.get() );
		copyOfTrans->setTarget( copyOfLoc2.get() );
		copyOfTrans->setReset( reset );

		copyOfLoc1->addTransition( std::move( copyOfTrans ) );

		/*
		 * Hybrid Automaton Setup
		 */

		initLocSet.push_back( loc1.get() );
		locSet.emplace_back( std::move( copyOfLoc1 ) );
		locSet.emplace_back( std::move( copyOfLoc2 ) );

		// Polytope for InitialValuation & Guard Assignment
		coordinates( 0 ) = 2;
		coordinates( 1 ) = 3;
		std::vector<vector_t<Number>> vecSet;
		vecSet.push_back( coordinates );
		poly = valuation_t<Number>( vecSet );
		auto hpoly = Converter<Number>::toHPolytope( poly );

		for ( auto loc : initLocSet ) {
			hybrid.addInitialState( loc, Condition<Number>( hpoly.matrix(), hpoly.vector() ) );
		}

		hybrid.setLocations( std::move( locSet ) );
	}

	virtual void TearDown() {
		// delete loc1;
		// delete loc2;
		// delete trans;
	}

	// Hybrid Automaton Objects: Locations, Transitions, Automaton itself

	std::unique_ptr<Location<Number>> loc1;
	std::unique_ptr<Location<Number>> loc2;
	std::unique_ptr<Location<Number>> copyOfLoc1;
	std::unique_ptr<Location<Number>> copyOfLoc2;
	std::unique_ptr<Transition<Number>> trans;
	std::unique_ptr<Transition<Number>> copyOfTrans;
	HybridAutomaton<Number> hybrid;

	// Other Objects: Vectors, Matrices, Guards...
	vector_t<Number> invariantVec = vector_t<Number>( 2, 1 );
	matrix_t<Number> invariantMat = matrix_t<Number>( 2, 2 );
	Condition<Number> inv;
	matrix_t<Number> locationMat = matrix_t<Number>( 2, 2 );

	Condition<Number> guard;

	Reset<Number> reset;

	std::vector<std::unique_ptr<Location<Number>>> locSet;

	std::vector<Location<Number>*> initLocSet;

	std::vector<std::unique_ptr<Transition<Number>>> transSet;

	vector_t<Number> coordinates = vector_t<Number>( 2, 1 );
	valuation_t<Number> poly;

  public:
	bool find( const Location<Number>* loc, const std::vector<Location<Number>*>& locSet ) const {
		if ( loc == nullptr || locSet.empty() ) {
			// std::cout << "loc was nullptr or locSet was empty\n";
			return false;
		}
		// std::cout << "locSet size: " << locSet.size() << std::endl;
		// std::cout << "loc has hash: " << loc->hash() << std::endl;
		for ( auto& ptrToALoc : locSet ) {
			// std::cout << "ptrToALoc loc hash is: " << ptrToALoc->hash() << std::endl;
			if ( *ptrToALoc == *( loc ) ) {
				// std::cout << "found a match!\n";
				return true;
			}
		}
		// std::cout << "found no match.\n";
		return false;
	}

	bool find( const Transition<Number>* trans, const std::vector<Transition<Number>*>& transSet ) const {
		if ( trans == nullptr || transSet.empty() ) return false;
		for ( auto& ptrToTrans : transSet ) {
			if ( *ptrToTrans == *( trans ) ) {
				return true;
			}
		}
		return false;
	}

	// To test copying
	HybridAutomaton<Number> dummyCopy( HybridAutomaton<Number> orig ) { return orig; }

	// To test moving
	HybridAutomaton<Number> dummyMove( HybridAutomaton<Number>&& orig ) { return orig; }
};

/**
 * Location Test
 */
TYPED_TEST( HybridAutomataTest, LocationTest ) {
	// invariant: vector
	EXPECT_EQ( this->loc1->getInvariant().getVector(), this->invariantVec );
	EXPECT_EQ( this->loc2->getInvariant().getVector(), this->invariantVec );

	vector_t<TypeParam> invariantVec2( 2, 1 );
	invariantVec2( 0 ) = 10;
	invariantVec2( 1 ) = 10;
	EXPECT_NE( this->loc1->getInvariant().getVector(), invariantVec2 );

	// invariant: matrix
	EXPECT_EQ( this->loc1->getInvariant().getMatrix(), this->invariantMat );
	EXPECT_EQ( this->loc2->getInvariant().getMatrix(), this->invariantMat );

	matrix_t<TypeParam> invariantMat2( 2, 2 );
	invariantMat2( 0, 0 ) = 1;
	invariantMat2( 0, 1 ) = 0;
	invariantMat2( 1, 0 ) = 0;
	invariantMat2( 1, 1 ) = 3;
	EXPECT_NE( this->loc1->getInvariant().getMatrix(), invariantMat2 );

	// location: matrix
	EXPECT_EQ( this->loc1->getLinearFlow().getFlowMatrix(), this->locationMat );

	matrix_t<TypeParam> locationMat2( 2, 2 );
	locationMat2( 0, 0 ) = 1;
	locationMat2( 0, 1 ) = 0;
	locationMat2( 1, 0 ) = 0;
	locationMat2( 1, 1 ) = 1;
	EXPECT_NE( this->loc1->getLinearFlow().getFlowMatrix(), locationMat2 );

	// location: set of outgoing transitions
	// EXPECT_EQ(this->loc1->getTransitions(), this->ptrSet);

	EXPECT_TRUE( *this->loc1 < *this->loc2 || *this->loc2 < *this->loc1 );
	// EXPECT_FALSE(*this->loc2 < *this->loc1);

	EXPECT_TRUE( locPtrComp<TypeParam>()( this->loc1, this->loc2 ) ||
				 locPtrComp<TypeParam>()( this->loc2, this->loc1 ) );

	auto loc = *( this->hybrid.getLocation( "Location1" ) );
	EXPECT_EQ( std::size_t( 1 ), loc.getTransitions().size() );
	loc = *( this->hybrid.getLocation( "Location1" ) );
	EXPECT_EQ( std::size_t( 1 ), loc.getTransitions().size() );
}

/*
TYPED_TEST(HybridAutomataTest, LocationParallelcompositionTest)
{
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

	l1->setLinearFlow(l1Flow);
	l2->setLinearFlow(l2Flow);

	std::unique_ptr<Location<TypeParam>> res1 = parallelCompose(l1.get(),l2.get(),l1Vars,l2Vars,haVars);
	matrix_t<TypeParam> expectedResult1 = matrix_t<TypeParam>::Zero(haVars.size()+1, haVars.size()+1);
	expectedResult1 << 1,0,2,0,
						0,1,2,0,
						3,3,4,0,
						0,0,0,0;
	EXPECT_EQ(res1->getLinearFlow(),expectedResult1);


	l1Vars = {"a","b"};
	l2Vars = {"c","d"};
	haVars = {"a","b","c","d"};
	std::unique_ptr<Location<TypeParam>> res2 = parallelCompose(l1.get(),l2.get(),l1Vars,l2Vars,haVars);

	matrix_t<TypeParam> expectedResult2 = matrix_t<TypeParam>::Zero(haVars.size()+1, haVars.size()+1);
	expectedResult2 << 1,2,0,0,0,
						3,4,0,0,0,
						0,0,1,2,0,
						0,0,3,4,0,
						0,0,0,0,0;
	EXPECT_EQ(res2->getLinearFlow(),expectedResult2);
}
*/

/**
 * Transition Test
 */
TYPED_TEST( HybridAutomataTest, TransitionTest ) {
	// transition: Start Location
	EXPECT_EQ( this->trans->getSource(), this->loc1.get() );

	// transition: End Location
	EXPECT_EQ( this->trans->getTarget(), this->loc2.get() );

	// transition: Assignment
	EXPECT_EQ( this->trans->getReset().getVector(), this->reset.getVector() );
	EXPECT_EQ( this->trans->getReset().getMatrix(), this->reset.getMatrix() );

	// transition: Guard
	EXPECT_EQ( this->trans->getGuard().getVector(), this->guard.getVector() );
	EXPECT_EQ( this->trans->getGuard().getMatrix(), this->guard.getMatrix() );

	// creation of transitions from source and target
	std::unique_ptr<Transition<TypeParam>> t( new Transition<TypeParam>( this->loc1.get(), this->loc2.get() ) );
	EXPECT_EQ( t->getSource(), this->loc1.get() );
	EXPECT_EQ( t->getTarget(), this->loc2.get() );
	EXPECT_EQ( t->getAggregation(), Aggregation::none );
	EXPECT_FALSE( t->isTimeTriggered() );
	t->setAggregation( Aggregation::aggregation );
	EXPECT_EQ( t->getAggregation(), Aggregation::aggregation );

	t->setTriggerTime( TypeParam( 1 ) );
	EXPECT_TRUE( t->isTimeTriggered() );
	EXPECT_EQ( t->getTriggerTime(), TypeParam( 1 ) );
}

/**
 * Hybrid Automaton Test
 */
TYPED_TEST( HybridAutomataTest, HybridAutomatonTest ) {
	// construct a new hybrid automaton.
	HybridAutomaton<TypeParam> h1;

	std::unique_ptr<Location<TypeParam>> anotherCopyOfLoc1 = std::make_unique<Location<TypeParam>>( *this->loc1.get() );
	std::unique_ptr<Location<TypeParam>> anotherCopyOfLoc2 = std::make_unique<Location<TypeParam>>( *this->loc2.get() );

	// Check if trans can be found in h1's transition set after inserting
	std::unique_ptr<Transition<TypeParam>> aTrans = std::make_unique<Transition<TypeParam>>( *( this->trans ) );
	EXPECT_FALSE( aTrans == nullptr );

	aTrans->setSource( anotherCopyOfLoc1.get() );
	aTrans->setTarget( anotherCopyOfLoc2.get() );
	anotherCopyOfLoc1->addTransition( std::move( aTrans ) );

	h1.addLocation( std::move( anotherCopyOfLoc1 ) );
	h1.addLocation( std::move( anotherCopyOfLoc2 ) );

	EXPECT_EQ( std::size_t( 2 ), h1.getLocations().size() );
	EXPECT_EQ( this->loc1->getName(), h1.getLocations().front()->getName() );
	EXPECT_EQ( this->loc1->getLinearFlow(), h1.getLocations().front()->getLinearFlow() );
	EXPECT_EQ( this->loc1->getInvariant(), h1.getLocations().front()->getInvariant() );

	// EXPECT_TRUE( *( h1.getLocation( "Location1" ) ) == *( this->loc1.get() ) );
	// EXPECT_TRUE( *( h1.getLocation( this->loc1->hash() ) ) == *( this->loc1.get() ) );
	// Comparison for location 2 works, as it does not have any transitions which would be copied and thus invalidate
	// equality.
	EXPECT_TRUE( *( h1.getLocation( "Location2" ) ) == *( this->loc2.get() ) );
	EXPECT_TRUE( *( h1.getLocation( this->loc2->hash() ) ) == *( this->loc2.get() ) );

	// h1.addTransition(std::move(aTrans));
	EXPECT_TRUE( aTrans == nullptr );
	// EXPECT_TRUE(this->find(this->trans.get(), h1.getTransitions()));

	matrix_t<TypeParam> matr = matrix_t<TypeParam>::Identity( 2, 2 );
	vector_t<TypeParam> vec = vector_t<TypeParam>( 2 );
	vec << 1, 2;

	h1.addInitialState( this->loc1.get(), Condition<TypeParam>( matr, vec ) );

	// Copy constructor;
	/*
	std::cout << "Expect copy constructor\n";
	HybridAutomaton<TypeParam> h0(h1);
	EXPECT_EQ(h0, h1);
	*/
	// copy assignment operator
	std::cout << "====== Expect copy assignment\n";
	HybridAutomaton<TypeParam> h2 = h1;
	EXPECT_NE( h1, h2 );
	EXPECT_EQ( h1.getLocations().front()->getName(), h2.getLocations().front()->getName() );
	// std::cout << "=== h1 at after:" << h1 << std::endl;
	// std::cout << "=== h2 at after:" << h2 << std::endl;

	// somehow check move assignment
	std::cout << "====== Expect move assignment\n";
	HybridAutomaton<TypeParam> h3 = std::move( h1 );
	// EXPECT_TRUE(h1.getTransitions().size() == 0);
	EXPECT_EQ( h2, h3 );

	std::cout << "====== Expect move constructor\n";
	HybridAutomaton<TypeParam> h4( std::move( h2 ) );
	EXPECT_EQ( h3, h4 );

	std::cout << "====== Expect copy assignment\n";
	HybridAutomaton<TypeParam> h5 = this->dummyCopy( h3 );
	EXPECT_EQ( h4, h5 );

	std::cout << "====== Expect move assignment\n";
	HybridAutomaton<TypeParam> h6 = this->dummyMove( std::move( h3 ) );
	EXPECT_EQ( h4, h6 );
}

TYPED_TEST( HybridAutomataTest, State ) {
	// Constructors
	State_t<TypeParam> s1( this->loc1.get() );

	matrix_t<TypeParam> matr = matrix_t<TypeParam>::Identity( 2, 2 );
	vector_t<TypeParam> vec = vector_t<TypeParam>( 2 );
	vec << 1, 2;
	State_t<TypeParam> s2( this->loc1.get() );
	s2.setSet( ConstraintSet<TypeParam>( matr, vec ) );

	EXPECT_EQ( s1.getLocation()->hash(), this->loc1->hash() );
	EXPECT_EQ( s2.getLocation()->hash(), this->loc1->hash() );
	EXPECT_EQ( std::get<ConstraintSet<TypeParam>>( s2.getSet() ).matrix(), matr );
	EXPECT_EQ( std::get<ConstraintSet<TypeParam>>( s2.getSet() ).vector(), vec );
	EXPECT_EQ( std::get<ConstraintSet<TypeParam>>( s2.getSet( 0 ) ).matrix(), matr );
	EXPECT_EQ( std::get<ConstraintSet<TypeParam>>( s2.getSet( 0 ) ).vector(), vec );
}

TYPED_TEST( HybridAutomataTest, HashTest ) {
	// Condition
	Condition<TypeParam> c1;
	EXPECT_TRUE( c1.hash() == 0 );
	matrix_t<TypeParam> m = matrix_t<TypeParam>::Identity( 3, 3 );
	vector_t<TypeParam> v = vector_t<TypeParam>( 3 );
	v << 1, 2, 3;
	c1.setMatrix( m );
	c1.setVector( v );
	EXPECT_TRUE( c1.hash() != 0 );
	Condition<TypeParam> c2 = c1;
	EXPECT_TRUE( c1.hash() == c2.hash() );

	// Reset
	Reset<TypeParam> r1;
	EXPECT_TRUE( r1.hash() == 0 );
	r1.setMatrix( m );
	r1.setVector( v );
	EXPECT_TRUE( r1.hash() != 0 );
	Reset<TypeParam> r2 = r1;
	EXPECT_TRUE( r1.hash() == r2.hash() );
}
