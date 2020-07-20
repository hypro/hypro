#include "../../hypro/datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../../hypro/datastructures/HybridAutomaton/decomposition/DecompositionMethods.h"
#include "../../hypro/util/VariablePool.h"
#include "gtest/gtest.h"

using namespace hypro;

TEST( DecompositionMethodsTest, GetDynamicTypeLocation ) {
	using N = double;
	using Matrix = matrix_t<N>;
	using Vector = vector_t<N>;
	Location<N> loc{ "l" };
	EXPECT_EQ( DynamicType::discrete, getDynamicType( loc ) );

	Matrix flow = Matrix::Identity( 2, 2 );
	loc.setFlow( flow );
	EXPECT_EQ( DynamicType::linear, getDynamicType( loc ) );

	flow = Matrix::Zero( 2, 2 );
	loc.setFlow( flow );
	EXPECT_EQ( DynamicType::discrete, getDynamicType( loc ) );

	flow = Matrix::Zero( 3, 3 );
	flow( 0, 2 ) = 1;
	flow( 1, 2 ) = 1;
	loc.setFlow( flow );
	EXPECT_EQ( DynamicType::timed, getDynamicType( loc ) );

	auto& vpool = VariablePool::getInstance();
	rectangularFlow<N> rFlow;
	rFlow.setFlowIntervalForDimension( carl::Interval<N>( 0, 1 ), vpool.carlVarByIndex( 0 ) );
	loc.setFlow( rFlow );
	EXPECT_EQ( DynamicType::rectangular, getDynamicType( loc ) );

	loc.setFlow( flow, 1 );
	EXPECT_EQ( DynamicType::mixed, getDynamicType( loc ) );

	// case: set timed flow but linear-combination in invariant
	Location<N> loc2{ "l2" };
	flow = Matrix::Zero( 3, 3 );
	flow( 0, 2 ) = 1;
	flow( 1, 2 ) = 1;
	loc2.setFlow( flow );
	EXPECT_EQ( DynamicType::timed, getDynamicType( loc2 ) );
	Condition<N> invariant{ Matrix::Ones( 1, 3 ), Vector::Zero( 1 ) };
	loc2.setInvariant( invariant );
	EXPECT_EQ( DynamicType::linear, getDynamicType( loc2 ) );

	// case: invariant condition also axis-aligned
	Matrix constraints = Matrix::Zero( 1, 3 );
	constraints( 0, 1 ) = 2;
	invariant = Condition<N>{ constraints, Vector::Zero( 1 ) };
	loc2.setInvariant( invariant );
	EXPECT_EQ( DynamicType::timed, getDynamicType( loc2 ) );

	// TODO: transitions - reset
}