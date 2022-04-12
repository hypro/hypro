/**
 * Testfile for hybrid automata.
 * Author: ckugler
 */

#include "test/defines.h"

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

		loc1 = hybrid.createLocation();
		loc2 = hybrid.createLocation();

		trans = loc1->createTransition( loc2 );

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
		locationMat( 0, 0 ) = 1;
		locationMat( 0, 1 ) = 1;
		locationMat( 1, 0 ) = 1;
		locationMat( 1, 1 ) = 1;
		loc2->setLinearFlow( locationMat );

		copyOfLoc1 = hybrid.createLocation( loc1 );
		copyOfLoc2 = hybrid.createLocation( loc2 );

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

		copyOfTrans = copyOfLoc1->createTransition( copyOfLoc2 );
		copyOfTrans->setGuard( guard );
		copyOfTrans->setReset( reset );

		/*
		 * Hybrid Automaton Setup
		 */

		// Polytope for InitialValuation
		coordinates( 0 ) = 2;
		coordinates( 1 ) = 3;
		std::vector<vector_t<Number>> vecSet;
		vecSet.push_back( coordinates );
		poly = valuation_t<Number>( vecSet );
		auto hpoly = Converter<Number>::toHPolytope( poly );
		hybrid.addInitialState( loc1, Condition<Number>( hpoly.matrix(), hpoly.vector() ) );

		// Local bad states: x0 >= 10 in location location2
		matrix_t<Number> constraints = matrix_t<Number>( 1, 2 );
		vector_t<Number> constants = vector_t<Number>( 1 );
		constraints << -1, 0;
		constants << -10;
		hybrid.addLocalBadStates( loc2, { constraints, constants } );
	}

	virtual void TearDown() {
		// delete loc1;
		// delete loc2;
		// delete trans;
	}

	// Hybrid Automaton Objects: Locations, Transitions, Automaton itself

	Location<Number>* loc1;
	Location<Number>* loc2;
	Location<Number>* copyOfLoc1;
	Location<Number>* copyOfLoc2;
	Transition<Number>* trans;
	Transition<Number>* copyOfTrans;
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
			return false;
		}
		for ( auto& ptrToALoc : locSet ) {
			if ( *ptrToALoc == *( loc ) ) {
				return true;
			}
		}
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
	matrix_t<TypeParam> locationMat( 2, 2 );
	locationMat( 0, 0 ) = 2;
	locationMat( 0, 1 ) = 0;
	locationMat( 1, 0 ) = 0;
	locationMat( 1, 1 ) = 1;
	EXPECT_EQ( this->loc1->getLinearFlow().getFlowMatrix(), locationMat );

	matrix_t<TypeParam> locationMat2( 2, 2 );
	locationMat2( 0, 0 ) = 1;
	locationMat2( 0, 1 ) = 1;
	locationMat2( 1, 0 ) = 1;
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

/// Flow-types test
TYPED_TEST( HybridAutomataTest, FlowTest ) {
	using Interval = carl::Interval<TypeParam>;

	typename rectangularFlow<TypeParam>::flowMap fmap;
	fmap[VariablePool::getInstance().carlVarByIndex( 0 )] = Interval( 0, 1 );
	rectangularFlow<TypeParam> rectFlow{ fmap };
	EXPECT_EQ( rectFlow.type(), DynamicType::rectangular );
	EXPECT_EQ( rectFlow.size(), std::size_t( 1 ) );
	EXPECT_EQ( rectFlow.dimension(), std::size_t( 1 ) );
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
	EXPECT_EQ( this->trans->getSource(), this->loc1 );

	// transition: End Location
	EXPECT_EQ( this->trans->getTarget(), this->loc2 );

	// transition: Assignment
	EXPECT_EQ( this->trans->getReset().getVector(), this->reset.getVector() );
	EXPECT_EQ( this->trans->getReset().getMatrix(), this->reset.getMatrix() );

	// transition: Guard
	EXPECT_EQ( this->trans->getGuard().getVector(), this->guard.getVector() );
	EXPECT_EQ( this->trans->getGuard().getMatrix(), this->guard.getMatrix() );

	// creation of transitions from source and target
	std::unique_ptr<Transition<TypeParam>> t( new Transition<TypeParam>( this->loc1, this->loc2 ) );
	EXPECT_EQ( t->getSource(), this->loc1 );
	EXPECT_EQ( t->getTarget(), this->loc2 );
	EXPECT_EQ( t->getAggregation(), Aggregation::none );
	EXPECT_FALSE( t->isTimeTriggered() );
	t->setAggregation( Aggregation::aggregation );
	EXPECT_EQ( t->getAggregation(), Aggregation::aggregation );

	t->setTriggerTime( TypeParam( 1 ) );
	EXPECT_TRUE( t->isTimeTriggered() );
	EXPECT_EQ( t->getTriggerTime(), TypeParam( 1 ) );

	Reset<TypeParam> empty{};
	EXPECT_TRUE( empty.isIdentity() );
	EXPECT_TRUE( empty.isAffineIdentity() );
	EXPECT_TRUE( empty.isIntervalIdentity() );

	matrix_t<TypeParam> id = matrix_t<TypeParam>::Identity( 3, 3 );
	vector_t<TypeParam> zero = vector_t<TypeParam>::Zero( 3 );
	Reset<TypeParam> identity{ id, zero };
	EXPECT_TRUE( identity.isIdentity() );
	EXPECT_TRUE( identity.isAffineIdentity() );
	EXPECT_TRUE( identity.isIntervalIdentity() );
	EXPECT_TRUE( identity.isIdentity( 0 ) );
	EXPECT_TRUE( identity.isIdentity( 1 ) );
	EXPECT_TRUE( identity.isIdentity( 2 ) );

	matrix_t<TypeParam> mat = matrix_t<TypeParam>::Identity( 3, 3 );
	vector_t<TypeParam> vec = vector_t<TypeParam>::Zero( 3 );
	vec( 0 ) = 1;
	mat( 0, 2 ) = 1;
	mat( 2, 1 ) = 1;
	Reset<TypeParam> r{ mat, vec };
	EXPECT_FALSE( r.isIdentity() );
	EXPECT_FALSE( r.isAffineIdentity() );
	EXPECT_TRUE( r.isIntervalIdentity() );
	EXPECT_FALSE( r.isIdentity( 0 ) );
	EXPECT_TRUE( r.isIdentity( 1 ) );
	EXPECT_FALSE( r.isIdentity( 2 ) );
}

/**
 * Hybrid Automaton Test
 */
TYPED_TEST( HybridAutomataTest, HybridAutomatonTest ) {
	// construct a new hybrid automaton.
	TRACE( "hypro.datastructures", "START TEST" );
	HybridAutomaton<TypeParam> h1;

	Location<TypeParam>* anotherCopyOfLoc1 = h1.createLocation( this->loc1 );
	Location<TypeParam>* anotherCopyOfLoc2 = h1.createLocation( this->loc2 );
	// clear transitions which were also copied
	anotherCopyOfLoc1->rGetTransitions().clear();

	// Re-insert correct transition (take guards and resets, update source and target)
	Transition<TypeParam>* aTrans = anotherCopyOfLoc1->createTransition( this->trans );
	aTrans->setTarget( anotherCopyOfLoc2 );
	EXPECT_FALSE( aTrans == nullptr );

	EXPECT_EQ( std::size_t( 2 ), h1.getLocations().size() );
	EXPECT_EQ( this->loc1->getName(), h1.getLocations().front()->getName() );
	EXPECT_EQ( this->loc1->getLinearFlow(), h1.getLocations().front()->getLinearFlow() );
	EXPECT_EQ( this->loc1->getInvariant(), h1.getLocations().front()->getInvariant() );

	EXPECT_TRUE( *( h1.getLocation( "Location1" ) ) == *( anotherCopyOfLoc1 ) );
	EXPECT_TRUE( *( h1.getLocation( anotherCopyOfLoc1->hash() ) ) == *( anotherCopyOfLoc1 ) );
	// Comparison for location 2 works, as it does not have any transitions which would be copied and thus invalidate
	// equality.
	EXPECT_TRUE( *( h1.getLocation( "Location2" ) ) == *( anotherCopyOfLoc2 ) );
	EXPECT_TRUE( *( h1.getLocation( anotherCopyOfLoc2->hash() ) ) == *( anotherCopyOfLoc2 ) );

	matrix_t<TypeParam> matr = matrix_t<TypeParam>::Identity( 2, 2 );
	vector_t<TypeParam> vec = vector_t<TypeParam>( 2 );
	vec << 1, 2;

	h1.addInitialState( anotherCopyOfLoc1, Condition<TypeParam>( matr, vec ) );

	// Copy constructor test
	EXPECT_TRUE( aTrans->getTarget() == anotherCopyOfLoc2 );
	EXPECT_EQ( h1, h1 );
	HybridAutomaton<TypeParam> h0{ h1 };
	EXPECT_EQ( h0, h1 );

	// Copy assignment operator
	HybridAutomaton<TypeParam> h2 = h1;
	EXPECT_EQ( h1, h2 );
	EXPECT_EQ( h1.getLocations().front()->getName(), h2.getLocations().front()->getName() );

	// Move assignment operator
	HybridAutomaton<TypeParam> h3 = std::move( h1 );
	EXPECT_EQ( h2, h3 );

	HybridAutomaton<TypeParam> h4( std::move( h2 ) );
	EXPECT_EQ( h3, h4 );

	HybridAutomaton<TypeParam> h5 = this->dummyCopy( h3 );
	EXPECT_EQ( h4, h5 );

	HybridAutomaton<TypeParam> h6 = this->dummyMove( std::move( h3 ) );
	EXPECT_EQ( h4, h6 );
}

TYPED_TEST( HybridAutomataTest, State ) {
	// Constructors
	State_t<TypeParam> s1( this->loc1 );

	matrix_t<TypeParam> matr = matrix_t<TypeParam>::Identity( 2, 2 );
	vector_t<TypeParam> vec = vector_t<TypeParam>( 2 );
	vec << 1, 2;
	State_t<TypeParam> s2( this->loc1 );
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

TYPED_TEST( HybridAutomataTest, FlowUtility ) {
	using Matrix = matrix_t<TypeParam>;

	Matrix flow1 = Matrix::Zero( 3, 3 );
	linearFlow<TypeParam> f1{ flow1 };

	EXPECT_FALSE( f1.hasFlow( 0 ) );
	EXPECT_FALSE( f1.hasFlow( 1 ) );
	EXPECT_FALSE( f1.hasFlow( 2 ) );

	auto flow2 = flow1;
	flow2( 1, 1 ) = 2;
	linearFlow<TypeParam> f2{ flow2 };
	EXPECT_FALSE( f2.hasFlow( 0 ) );
	EXPECT_TRUE( f2.hasFlow( 1 ) );
	EXPECT_FALSE( f2.hasFlow( 2 ) );
}
