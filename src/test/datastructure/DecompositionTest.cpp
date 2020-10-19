#include "../../hypro/datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../../hypro/datastructures/HybridAutomaton/decomposition/DecompositionMethods.h"
#include "../../hypro/util/VariablePool.h"
#include "gtest/gtest.h"

using namespace hypro;

template<typename Number>
HybridAutomaton<Number> singleVariableHA() {
    using Matrix = hypro::matrix_t<Number>;
    using Vector = hypro::vector_t<Number>;

    hypro::HybridAutomaton<Number> ha;

    // Create location
    hypro::Location<Number> loc;

    // Set flow x' = 1
    Matrix flow = Matrix::Zero( 2, 2 );
    flow( 0, 1 ) = 1;
    loc.setFlow( flow );

    // Set invariant x <= 1
    Matrix invariantConstraints = Matrix::Zero( 1, 1 );
    invariantConstraints( 0, 0 ) = 1;
    Vector invariantConstants = Vector::Ones( 1 );
    loc.setInvariant( { invariantConstraints, invariantConstants } );

    // Set initial state x = 0
    Matrix initialConstraints = Matrix::Zero( 2, 1 );
    Vector initialConstants = Vector::Zero( 2 );
    initialConstraints << 1, -1;
    initialConstants << 0, 0;

    // Create HA
    auto& locPtr = ha.addLocation( std::make_unique<hypro::Location<Number>>( loc ) );
    ha.addInitialState( locPtr.get(), hypro::Condition<Number>( initialConstraints, initialConstants ) );

    return ha;
}

template<typename Number>
HybridAutomaton<Number> independentHA() {
    using Matrix = hypro::matrix_t<Number>;
    using Vector = hypro::vector_t<Number>;

    hypro::HybridAutomaton<Number> ha;

    // Create location
    hypro::Location<Number> loc;

    // Set flow x' = 1, y' = 1
    Matrix flow = Matrix::Zero( 3, 3 );
    flow( 0, 2 ) = 1;
    flow( 1, 2 ) = 1;
    loc.setFlow( flow );

    // Set invariant x <= 1
    Matrix invariantConstraints = Matrix::Zero( 1, 2 );
    invariantConstraints( 0, 0 ) = 1;
    Vector invariantConstants = Vector::Ones( 1 );
    loc.setInvariant( { invariantConstraints, invariantConstants } );

    // Set initial state x = 0, y = 0
    Matrix initialConstraints = Matrix::Zero( 4, 2 );
    Vector initialConstants = Vector::Zero( 4 );
    initialConstraints << 1, 0,
                        -1, 0,
                        0, 1,
                        0, -1;
    initialConstants << 0, 0, 0, 0;

    // Create HA
    auto& locPtr = ha.addLocation( std::make_unique<hypro::Location<Number>>( loc ) );
    ha.addInitialState( locPtr.get(), hypro::Condition<Number>( initialConstraints, initialConstants ) );

    return ha;
}

template<typename Number>
HybridAutomaton<Number> dependentFlowHA() {
    using Matrix = hypro::matrix_t<Number>;
    using Vector = hypro::vector_t<Number>;

    hypro::HybridAutomaton<Number> ha;

    // Create location
    hypro::Location<Number> loc;

    // Set flow x' = 1, y' = x + 1
    Matrix flow = Matrix::Zero( 3, 3 );
    flow( 0, 2 ) = 1;
    flow( 1, 0 ) = 1;
    flow( 1, 2 ) = 1;
    loc.setFlow( flow );

    // Set invariant x <= 1
    Matrix invariantConstraints = Matrix::Zero( 1, 2 );
    invariantConstraints( 0, 0 ) = 1;
    Vector invariantConstants = Vector::Ones( 1 );
    loc.setInvariant( { invariantConstraints, invariantConstants } );

    // Set initial state x = 0, y = 0
    Matrix initialConstraints = Matrix::Zero( 4, 2 );
    Vector initialConstants = Vector::Zero( 4 );
    initialConstraints << 1, 0,
                        -1, 0,
                        0, 1,
                        0, -1;
    initialConstants << 0, 0, 0, 0;

    // Create HA
    auto& locPtr = ha.addLocation( std::make_unique<hypro::Location<Number>>( loc ) );
    ha.addInitialState( locPtr.get(), hypro::Condition<Number>( initialConstraints, initialConstants ) );

    return ha;
}

template<typename Number>
HybridAutomaton<Number> dependentInvariantHA() {
    using Matrix = hypro::matrix_t<Number>;
    using Vector = hypro::vector_t<Number>;

    hypro::HybridAutomaton<Number> ha;

    // Create location
    hypro::Location<Number> loc;

    // Set flow x' = 1, y' = 1
    Matrix flow = Matrix::Zero( 3, 3 );
    flow( 0, 2 ) = 1;
    flow( 1, 2 ) = 1;
    loc.setFlow( flow );

    // Set invariant x + y <= 1
    Matrix invariantConstraints = Matrix::Zero( 1, 2 );
    invariantConstraints( 0, 0 ) = 1;
    invariantConstraints( 0, 1 ) = 1;
    Vector invariantConstants = Vector::Ones( 1 );
    loc.setInvariant( { invariantConstraints, invariantConstants } );

    // Set initial state x = 0, y = 0
    Matrix initialConstraints = Matrix::Zero( 4, 2 );
    Vector initialConstants = Vector::Zero( 4 );
    initialConstraints << 1, 0,
                        -1, 0,
                        0, 1,
                        0, -1;
    initialConstants << 0, 0, 0, 0;

    // Create HA
    auto& locPtr = ha.addLocation( std::make_unique<hypro::Location<Number>>( loc ) );
    ha.addInitialState( locPtr.get(), hypro::Condition<Number>( initialConstraints, initialConstants ) );

    return ha;
}

template<typename Number>
HybridAutomaton<Number> transitiveDependentHA() {
    using Matrix = hypro::matrix_t<Number>;
    using Vector = hypro::vector_t<Number>;

    hypro::HybridAutomaton<Number> ha;

    // Create location
    hypro::Location<Number> loc;

    // Set flow x' = 1, y' = x, z' = 1
    Matrix flow = Matrix::Zero( 4, 4 );
    flow( 0, 3 ) = 1;
    flow( 1, 0 ) = 1;
    flow( 2, 3 ) = 1;
    loc.setFlow( flow );

    // Set invariant y + z <= 0
    Matrix invariantConstraints = Matrix::Zero( 1, 3 );
    invariantConstraints( 0, 1 ) = 1;
    invariantConstraints( 0, 2 ) = 1;
    Vector invariantConstants = Vector::Zero( 1 );
    loc.setInvariant( { invariantConstraints, invariantConstants } );

    // Set initial state x = 0, y = 0, z = 0
    Matrix initialConstraints = Matrix::Zero( 6, 3 );
    Vector initialConstants = Vector::Zero( 6 );
    initialConstraints << 1, 0, 0,
                        -1, 0, 0,
                        0, 1, 0,
                        0, -1, 0,
                        0, 0, 1,
                        0, 0, -1;
    initialConstants << 0, 0, 0, 0, 0, 0;

    // Create HA
    auto& locPtr = ha.addLocation( std::make_unique<hypro::Location<Number>>( loc ) );
    ha.addInitialState( locPtr.get(), hypro::Condition<Number>( initialConstraints, initialConstants ) );

    return ha;
}

template<typename Number>
HybridAutomaton<Number> rectangularIndependentHA() {
    using Matrix = hypro::matrix_t<Number>;
    using Vector = hypro::vector_t<Number>;

    hypro::HybridAutomaton<Number> ha;

    // Create location
    hypro::Location<Number> loc;

    // variables
    carl::Variable x = hypro::VariablePool::getInstance().carlVarByIndex( 0 );
    carl::Variable y = hypro::VariablePool::getInstance().carlVarByIndex( 1 );
    // rectangular dynamics x' = [0,2], y' = [1,2]
    std::map<carl::Variable, carl::Interval<Number>> dynamics;
    dynamics.emplace( std::make_pair( x, carl::Interval<Number>( 0, 2 ) ) );
    dynamics.emplace( std::make_pair( y, carl::Interval<Number>( 1, 2 ) ) );

    // Set flow
    hypro::rectangularFlow<Number> flow( dynamics );
    loc.setFlow( flow );
    
    // Set invariant x <= 1
    Matrix invariantConstraints = Matrix::Zero( 1, 2 );
    invariantConstraints( 0, 0 ) = 1;
    Vector invariantConstants = Vector::Ones( 1 );
    loc.setInvariant( { invariantConstraints, invariantConstants } );

    // Set initial state x = 0, y = 0
    Matrix initialConstraints = Matrix::Zero( 4, 2 );
    Vector initialConstants = Vector::Zero( 4 );
    initialConstraints << 1, 0,
                        -1, 0,
                        0, 1,
                        0, -1;
    initialConstants << 0, 0, 0, 0;

    // Create HA
    auto& locPtr = ha.addLocation( std::make_unique<hypro::Location<Number>>( loc ) );
    ha.addInitialState( locPtr.get(), hypro::Condition<Number>( initialConstraints, initialConstants ) );

    return ha;
}

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

TEST( DecompositionMethodsTest, GetSubspaceDecomposition ) {
	using Number = double;

    auto ha1 = singleVariableHA<Number>();
	auto decomposition1 = getSubspaceDecomposition( ha1 );
	EXPECT_EQ( std::vector<std::vector<std::size_t>>{ { 0 } }, decomposition1.subspaces );

	auto ha2 = independentHA<Number>();
	auto decomposition2 = getSubspaceDecomposition( ha2 );
	auto expectedSubspaces2 = std::vector<std::vector<std::size_t>>{ { 0 }, { 1 } };
	EXPECT_EQ( expectedSubspaces2, decomposition2.subspaces );

	auto ha3 = dependentFlowHA<Number>();
	auto decomposition3 = getSubspaceDecomposition( ha3 );
	auto expectedSubspaces3 = std::vector<std::vector<std::size_t>>{ { 0, 1 } };
	EXPECT_EQ( expectedSubspaces3, decomposition3.subspaces );

	auto ha4 = dependentInvariantHA<Number>();
	auto decomposition4 = getSubspaceDecomposition( ha4 );
	auto expectedSubspaces4 = std::vector<std::vector<std::size_t>>{ { 0, 1 } };
	EXPECT_EQ( expectedSubspaces4, decomposition4.subspaces );

	auto ha5 = transitiveDependentHA<Number>();
	auto decomposition5 = getSubspaceDecomposition( ha5 );
	auto expectedSubspaces5 = std::vector<std::vector<std::size_t>>{ { 0, 1, 2 } };
	EXPECT_EQ( expectedSubspaces5, decomposition5.subspaces );

	auto ha6 = rectangularIndependentHA<Number>();
	auto decomposition6 = getSubspaceDecomposition( ha6 );
	auto expectedSubspaces6 = std::vector<std::vector<std::size_t>>{ { 0 }, { 1 } };
	EXPECT_EQ( expectedSubspaces6, decomposition6.subspaces );


}