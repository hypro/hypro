/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "gtest/gtest.h"
#include <hypro/datastructures/HybridAutomaton/HybridAutomaton.h>
#include <hypro/datastructures/HybridAutomaton/decomposition/DecompositionMethods.h>
#include <hypro/util/VariablePool.h>

using namespace hypro;

template <typename Number>
HybridAutomaton<Number> singleVariableHa() {
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

template <typename Number>
HybridAutomaton<Number> independentHa() {
	using Matrix = hypro::matrix_t<Number>;
	using Vector = hypro::vector_t<Number>;

	hypro::HybridAutomaton<Number> ha;

	// Create location
	hypro::Location<Number> loc;

	// Set flow x' = 1, y' = 2
	Matrix flow = Matrix::Zero( 3, 3 );
	flow( 0, 2 ) = 1;
	flow( 1, 2 ) = 2;
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

template <typename Number>
HybridAutomaton<Number> dependentFlowHa() {
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

template <typename Number>
HybridAutomaton<Number> dependentInvariantHa() {
	using Matrix = hypro::matrix_t<Number>;
	using Vector = hypro::vector_t<Number>;

	hypro::HybridAutomaton<Number> ha;

	// Create location
	hypro::Location<Number> loc;

	// Set flow x' = 0, y' = 0
	Matrix flow = Matrix::Zero( 3, 3 );
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

template <typename Number>
HybridAutomaton<Number> transitiveDependentHa() {
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

template <typename Number>
HybridAutomaton<Number> rectangularIndependentHa() {
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

template <typename Number>
HybridAutomaton<Number> mixedDynamicsHa() {
	using Matrix = hypro::matrix_t<Number>;
	using Vector = hypro::vector_t<Number>;

	hypro::HybridAutomaton<Number> ha;

	// Create location
	hypro::Location<Number> loc;

	// Set flow x' = 1, y' = 1, z' = 1, u' = 0
	Matrix flow = Matrix::Zero( 5, 5 );
	flow( 0, 4 ) = 1;
	flow( 1, 4 ) = 1;
	flow( 2, 4 ) = 1;
	loc.setFlow( flow );

	// Set invariant y + z <= 0
	Matrix invariantConstraints = Matrix::Zero( 1, 4 );
	invariantConstraints( 0, 1 ) = 1;
	invariantConstraints( 0, 2 ) = 1;
	Vector invariantConstants = Vector::Zero( 1 );
	loc.setInvariant( { invariantConstraints, invariantConstants } );

	// Set initial state x = 0, y = 0, z = 0, u = 0
	Matrix initialConstraints = Matrix::Zero( 8, 4 );
	Vector initialConstants = Vector::Zero( 8 );
	initialConstraints << 1, 0, 0, 0,
		  -1, 0, 0, 0,
		  0, 1, 0, 0,
		  0, -1, 0, 0,
		  0, 0, 1, 0,
		  0, 0, -1, 0,
		  0, 0, 0, 1,
		  0, 0, 0, -1;
	initialConstants << 0, 0, 0, 0, 0, 0, 0, 0;

	// Create HA
	auto& locPtr = ha.addLocation( std::make_unique<hypro::Location<Number>>( loc ) );
	ha.addInitialState( locPtr.get(), hypro::Condition<Number>( initialConstraints, initialConstants ) );

	return ha;
}

template <typename Number>
HybridAutomaton<Number> multipleLocationsHa() {
	using Matrix = hypro::matrix_t<Number>;
	using Vector = hypro::vector_t<Number>;

	hypro::HybridAutomaton<Number> ha;

	// Create locations
	hypro::Location<Number> loc0{};
	hypro::Location<Number> loc1{};
	auto uniqueLoc0{ std::make_unique<hypro::Location<Number>>( loc0 ) };
	auto uniqueLoc1{ std::make_unique<hypro::Location<Number>>( loc1 ) };

	// Set flow x' = 1, y' = 0, z' = 0, u' = 1 in loc0
	Matrix flow0 = Matrix::Zero( 5, 5 );
	flow0( 0, 4 ) = 1;
	flow0( 3, 4 ) = 1;
	uniqueLoc0->setFlow( flow0 );

	// Set flow x' = 1, y' = 2x+1, z' = 2, u' = 0 in loc1
	Matrix flow1 = Matrix::Zero( 5, 5 );
	flow1( 0, 4 ) = 1;
	flow1( 1, 0 ) = 2;
	flow1( 1, 4 ) = 1;
	flow1( 2, 4 ) = 2;
	uniqueLoc1->setFlow( flow1 );

	// Set invariant y + z <= 0 in loc0
	Matrix invariantConstraints = Matrix::Zero( 1, 4 );
	invariantConstraints( 0, 1 ) = 1;
	invariantConstraints( 0, 2 ) = 1;
	Vector invariantConstants = Vector::Zero( 1 );
	uniqueLoc0->setInvariant( { invariantConstraints, invariantConstants } );

	// Set initial state x = 0, y = 0, z = 0, u = 0 in loc0
	Matrix initialConstraints = Matrix::Zero( 8, 4 );
	Vector initialConstants = Vector::Zero( 8 );
	initialConstraints << 1, 0, 0, 0,
		  -1, 0, 0, 0,
		  0, 1, 0, 0,
		  0, -1, 0, 0,
		  0, 0, 1, 0,
		  0, 0, -1, 0,
		  0, 0, 0, 1,
		  0, 0, 0, -1;
	initialConstants << 0, 0, 0, 0, 0, 0, 0, 0;

	// Create HA
	auto locPtr = uniqueLoc0.get();
	ha.addLocation( std::move( uniqueLoc0 ) );
	ha.addLocation( std::move( uniqueLoc1 ) );
	ha.addInitialState( locPtr, hypro::Condition<Number>( initialConstraints, initialConstants ) );
	return ha;
}

template <typename Number>
HybridAutomaton<Number> resetHa() {
	using Matrix = hypro::matrix_t<Number>;
	using Vector = hypro::vector_t<Number>;

	hypro::HybridAutomaton<Number> ha;

	// Create locations
	hypro::Location<Number> loc0{};
	hypro::Location<Number> loc1{};
	auto uniqueLoc0{ std::make_unique<hypro::Location<Number>>( loc0 ) };
	auto uniqueLoc1{ std::make_unique<hypro::Location<Number>>( loc1 ) };

	// Set flow x' = 0, y' = 0, z' = 0 in loc0 and loc1
	Matrix flow = Matrix::Zero( 4, 4 );
	uniqueLoc0->setFlow( flow );
	uniqueLoc1->setFlow( flow );

	// Construct transitions
	// l0 -> l1 with guard x <= 0, y + z <= 0 and reset x := [0,2], z := 0
	Matrix transConstraint = Matrix::Zero( 2, 3 );
	Vector transConstants = Vector::Zero( 2 );
	transConstraint( 0, 0 ) = 1;
	transConstraint( 1, 1 ) = 1;
	transConstraint( 1, 2 ) = 1;
	hypro::Condition<Number> guard( transConstraint, transConstants );
	hypro::Reset<Number> reset{
		  { carl::Interval<Number>{ 0, 2 }, carl::Interval<Number>{}, carl::Interval<Number>{ 0, 0 } } };

	auto trans0 =
		  std::make_unique<hypro::Transition<Location<Number>>>( uniqueLoc0.get(), uniqueLoc1.get(), guard, reset );
	uniqueLoc0->addTransition( std::move( trans0 ) );

	// Set initial state x = 0, y = 0, z = 0 in loc0
	Matrix initialConstraints = Matrix::Zero( 6, 3 );
	Vector initialConstants = Vector::Zero( 6 );
	initialConstraints << 1, 0, 0,
		  -1, 0, 0,
		  0, 1, 0,
		  0, -1, 0,
		  0, 0, 1,
		  0, 0, -1,
		  initialConstants << 0, 0, 0, 0, 0, 0;

	// Create HA
	auto locPtr = uniqueLoc0.get();
	ha.addLocation( std::move( uniqueLoc0 ) );
	ha.addLocation( std::move( uniqueLoc1 ) );
	ha.addInitialState( locPtr, hypro::Condition<Number>( initialConstraints, initialConstants ) );
	return ha;
}

template <typename Number>
HybridAutomaton<Number> affineResetHa() {
	using Matrix = hypro::matrix_t<Number>;
	using Vector = hypro::vector_t<Number>;

	hypro::HybridAutomaton<Number> ha;

	// Create locations
	hypro::Location<Number> loc0{};
	hypro::Location<Number> loc1{};
	auto uniqueLoc0{ std::make_unique<hypro::Location<Number>>( loc0 ) };
	auto uniqueLoc1{ std::make_unique<hypro::Location<Number>>( loc1 ) };

	// Set flow x' = 0, y' = 0, z' = 0 in loc0 and loc1
	Matrix flow = Matrix::Zero( 4, 4 );
	uniqueLoc0->setFlow( flow );
	uniqueLoc1->setFlow( flow );

	// Construct transitions
	// l0 -> l1 with guard x <= 0 and reset x := y, z := 1
	Matrix transConstraint = Matrix::Zero( 1, 3 );
	Vector transConstants = Vector::Zero( 1 );
	transConstraint( 0, 0 ) = 1;
	hypro::Condition<Number> guard( transConstraint, transConstants );
	Matrix resetMat = Matrix::Zero( 3, 3 );
	Vector resetVec = Vector::Zero( 3 );
	resetMat( 0, 1 ) = 1;
	resetMat( 1, 1 ) = 1;
	resetVec( 2 ) = 1;
	hypro::Reset<Number> reset( resetMat, resetVec );

	auto trans0 =
		  std::make_unique<hypro::Transition<Location<Number>>>( uniqueLoc0.get(), uniqueLoc1.get(), guard, reset );
	uniqueLoc0->addTransition( std::move( trans0 ) );

	// Set initial state x = 0, y = 0, z = 0 in loc0
	Matrix initialConstraints = Matrix::Zero( 6, 3 );
	Vector initialConstants = Vector::Zero( 6 );
	initialConstraints << 1, 0, 0,
		  -1, 0, 0,
		  0, 1, 0,
		  0, -1, 0,
		  0, 0, 1,
		  0, 0, -1,
		  initialConstants << 0, 0, 0, 0, 0, 0;

	// Create HA
	auto locPtr = uniqueLoc0.get();
	ha.addLocation( std::move( uniqueLoc0 ) );
	ha.addLocation( std::move( uniqueLoc1 ) );
	ha.addInitialState( locPtr, hypro::Condition<Number>( initialConstraints, initialConstants ) );
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

TEST( DecompositionMethodsTest, getSubspacePartition ) {
	using Number = double;

	auto ha1 = singleVariableHa<Number>();
	auto partition1 = getSubspacePartition( ha1 );
	EXPECT_EQ( std::vector<std::vector<std::size_t>>{ { 0 } }, partition1 );

	auto ha2 = independentHa<Number>();
	auto partition2 = getSubspacePartition( ha2 );
	auto expectedSubspaces2 = std::vector<std::vector<std::size_t>>{ { 0 }, { 1 } };
	EXPECT_EQ( expectedSubspaces2, partition2 );

	auto ha3 = dependentFlowHa<Number>();
	auto partition3 = getSubspacePartition( ha3 );
	auto expectedSubspaces3 = std::vector<std::vector<std::size_t>>{ { 0, 1 } };
	EXPECT_EQ( expectedSubspaces3, partition3 );

	auto ha4 = dependentInvariantHa<Number>();
	auto partition4 = getSubspacePartition( ha4 );
	auto expectedSubspaces4 = std::vector<std::vector<std::size_t>>{ { 0, 1 } };
	EXPECT_EQ( expectedSubspaces4, partition4 );

	auto ha5 = transitiveDependentHa<Number>();
	auto partition5 = getSubspacePartition( ha5 );
	auto expectedSubspaces5 = std::vector<std::vector<std::size_t>>{ { 0, 1, 2 } };
	EXPECT_EQ( expectedSubspaces5, partition5 );

	auto ha6 = rectangularIndependentHa<Number>();
	auto partition6 = getSubspacePartition( ha6 );
	auto expectedSubspaces6 = std::vector<std::vector<std::size_t>>{ { 0 }, { 1 } };
	EXPECT_EQ( expectedSubspaces6, partition6 );

	auto ha7 = mixedDynamicsHa<Number>();
	auto partition7 = getSubspacePartition( ha7 );
	auto expectedSubspaces7 = std::vector<std::vector<std::size_t>>{ { 0 }, { 1, 2 }, { 3 } };
	EXPECT_EQ( expectedSubspaces7, partition7 );

	auto ha8 = multipleLocationsHa<Number>();
	auto partition8 = getSubspacePartition( ha8 );
	auto expectedSubspaces8 = std::vector<std::vector<std::size_t>>{ { 0, 1, 2 }, { 3 } };
	EXPECT_EQ( expectedSubspaces8, partition8 );

	auto ha9 = resetHa<Number>();
	auto partition9 = getSubspacePartition( ha9 );
	auto expectedSubspaces9 = std::vector<std::vector<std::size_t>>{ { 0 }, { 1, 2 } };
	EXPECT_EQ( expectedSubspaces9, partition9 );

	auto ha10 = affineResetHa<Number>();
	auto partition10 = getSubspacePartition( ha10 );
	auto expectedSubspaces10 = std::vector<std::vector<std::size_t>>{ { 0, 1 }, { 2 } };
	EXPECT_EQ( expectedSubspaces10, partition10 );
}

TEST( DecompositionMethodsTest, decomposeAutomaton1 ) {
	using Number = double;

	auto ha = singleVariableHa<Number>();
	HybridAutomaton<Number> decomposedHa;
	Decomposition decomposition;
	std::tie( decomposedHa, decomposition ) = decomposeAutomaton( ha );

	Decomposition expectedDecomposition{ { { 0 } }, { DynamicType::timed } };

	EXPECT_EQ( ha, decomposedHa );
	EXPECT_EQ( expectedDecomposition.subspaces, decomposition.subspaces );
	EXPECT_EQ( expectedDecomposition.subspaceTypes, decomposition.subspaceTypes );
}

TEST( DecompositionMethodsTest, decomposeAutomaton2 ) {
	using Number = double;
	using Matrix = matrix_t<Number>;
	using Vector = vector_t<Number>;

	auto ha = independentHa<Number>();
	HybridAutomaton<Number> decomposedHa;
	Decomposition decomposition;
	std::tie( decomposedHa, decomposition ) = decomposeAutomaton( ha );

	Decomposition expectedDecomposition{ { { 0 }, { 1 } }, { DynamicType::timed, DynamicType::singular } };
	Condition<Number> expectedInvariant( { ConstraintSetT<Number>{ Matrix::Ones( 1, 1 ), Vector::Ones( 1 ) }, ConstraintSetT<Number>{} } );
	Matrix initialConstraints = Matrix::Zero( 2, 1 );
	initialConstraints << 1, -1;
	Condition<Number> expectedInitial( { ConstraintSetT<Number>{ initialConstraints, Vector::Zero( 2 ) }, ConstraintSetT<Number>{ initialConstraints, Vector::Zero( 2 ) } } );
	Matrix expectedFlow1 = Matrix::Zero( 2, 2 );
	Matrix expectedFlow2 = Matrix::Zero( 2, 2 );
	expectedFlow1( 0, 1 ) = 1;
	expectedFlow2( 0, 1 ) = 2;
	auto loc = decomposedHa.getLocations()[0];

	EXPECT_EQ( 2, loc->getNumberSubspaces() );
	EXPECT_EQ( expectedDecomposition.subspaces, decomposition.subspaces );
	EXPECT_EQ( expectedDecomposition.subspaceTypes, decomposition.subspaceTypes );
	EXPECT_EQ( expectedInvariant, loc->getInvariant() );
	EXPECT_EQ( expectedFlow1, loc->getLinearFlow( 0 ).getFlowMatrix() );
	EXPECT_EQ( expectedFlow2, loc->getLinearFlow( 1 ).getFlowMatrix() );
	EXPECT_EQ( expectedInitial, decomposedHa.getInitialStates().at( loc ) );
}

TEST( DecompositionMethodsTest, decomposeAutomaton3 ) {
	using Number = double;

	auto ha = dependentFlowHa<Number>();
	HybridAutomaton<Number> decomposedHa;
	Decomposition decomposition;
	std::tie( decomposedHa, decomposition ) = decomposeAutomaton( ha );

	Decomposition expectedDecomposition{ { { 0, 1 } }, { DynamicType::linear } };
	auto loc = decomposedHa.getLocations()[0];

	EXPECT_EQ( 1, loc->getNumberSubspaces() );
	EXPECT_EQ( ha, decomposedHa );
	EXPECT_EQ( expectedDecomposition.subspaces, decomposition.subspaces );
	EXPECT_EQ( expectedDecomposition.subspaceTypes, decomposition.subspaceTypes );
}

TEST( DecompositionMethodsTest, decomposeAutomaton4 ) {
	using Number = double;

	auto ha = dependentInvariantHa<Number>();
	HybridAutomaton<Number> decomposedHa;
	Decomposition decomposition;
	std::tie( decomposedHa, decomposition ) = decomposeAutomaton( ha );

	Decomposition expectedDecomposition{ { { 0, 1 } }, { DynamicType::discrete } };
	EXPECT_EQ( ha, decomposedHa );
	EXPECT_EQ( expectedDecomposition.subspaces, decomposition.subspaces );
	EXPECT_EQ( expectedDecomposition.subspaceTypes, decomposition.subspaceTypes );
}

TEST( DecompositionMethodsTest, decomposeAutomaton5 ) {
	using Number = double;
	using Matrix = matrix_t<Number>;
	using Vector = vector_t<Number>;

	auto ha = mixedDynamicsHa<Number>();
	HybridAutomaton<Number> decomposedHa;
	Decomposition decomposition;
	std::tie( decomposedHa, decomposition ) = decomposeAutomaton( ha );

	Decomposition expectedDecomposition{ { { 0 }, { 1, 2 }, { 3 } }, { DynamicType::timed, DynamicType::linear, DynamicType::discrete } };
	Condition<Number> expectedInvariant( { ConstraintSetT<Number>{}, ConstraintSetT<Number>{ Matrix::Ones( 1, 2 ), Vector::Zero( 1 ) }, ConstraintSetT<Number>{} } );
	Matrix expectedFlow1 = Matrix::Zero( 2, 2 );
	Matrix expectedFlow2 = Matrix::Zero( 3, 3 );
	Matrix expectedFlow3 = Matrix::Zero( 2, 2 );
	expectedFlow1( 0, 1 ) = 1;
	expectedFlow2( 0, 2 ) = 1;
	expectedFlow2( 1, 2 ) = 1;

	auto loc = decomposedHa.getLocations()[0];

	EXPECT_EQ( 3, loc->getNumberSubspaces() );
	EXPECT_EQ( expectedDecomposition.subspaces, decomposition.subspaces );
	EXPECT_EQ( expectedDecomposition.subspaceTypes, decomposition.subspaceTypes );
	EXPECT_EQ( expectedInvariant, loc->getInvariant() );
	EXPECT_EQ( expectedFlow1, loc->getLinearFlow( 0 ).getFlowMatrix() );
	EXPECT_EQ( expectedFlow2, loc->getLinearFlow( 1 ).getFlowMatrix() );
	EXPECT_EQ( expectedFlow3, loc->getLinearFlow( 2 ).getFlowMatrix() );
}

TEST( DecompositionMethodsTest, decomposeAutomaton6 ) {
	using Number = double;
	using Matrix = matrix_t<Number>;
	using Vector = vector_t<Number>;

	auto ha = multipleLocationsHa<Number>();
	HybridAutomaton<Number> decomposedHa;
	Decomposition decomposition;
	std::tie( decomposedHa, decomposition ) = decomposeAutomaton( ha );

	Decomposition expectedDecomposition{ { { 0, 1, 2 }, { 3 } }, { DynamicType::linear, DynamicType::singular } };

	Matrix invariantConstraints = Matrix::Zero( 1, 3 );
	invariantConstraints << 0, 1, 1;
	Condition<Number> expectedInvariant0( { ConstraintSetT<Number>{ invariantConstraints, Vector::Zero( 1 ) }, ConstraintSetT<Number>{} } );
	Condition<Number> expectedInvariant1( { ConstraintSetT<Number>{}, ConstraintSetT<Number>{} } );
	Matrix expectedFlow00 = Matrix::Zero( 4, 4 );
	Matrix expectedFlow01 = Matrix::Zero( 2, 2 );
	Matrix expectedFlow10 = Matrix::Zero( 4, 4 );
	Matrix expectedFlow11 = Matrix::Zero( 2, 2 );
	expectedFlow00( 0, 3 ) = 1;
	expectedFlow01( 0, 1 ) = 1;
	expectedFlow10( 0, 3 ) = 1;
	expectedFlow10( 1, 0 ) = 2;
	expectedFlow10( 1, 3 ) = 1;
	expectedFlow10( 2, 3 ) = 2;
	auto loc0 = decomposedHa.getLocations()[0];
	auto loc1 = decomposedHa.getLocations()[1];

	EXPECT_EQ( expectedDecomposition.subspaces, decomposition.subspaces );
	EXPECT_EQ( expectedDecomposition.subspaceTypes, decomposition.subspaceTypes );
	EXPECT_EQ( expectedInvariant0, loc0->getInvariant() );
	EXPECT_EQ( expectedInvariant1, loc1->getInvariant() );
	EXPECT_EQ( expectedFlow00, loc0->getLinearFlow( 0 ).getFlowMatrix() );
	EXPECT_EQ( expectedFlow01, loc0->getLinearFlow( 1 ).getFlowMatrix() );
	EXPECT_EQ( expectedFlow10, loc1->getLinearFlow( 0 ).getFlowMatrix() );
	EXPECT_EQ( expectedFlow11, loc1->getLinearFlow( 1 ).getFlowMatrix() );
}

TEST( DecompositionMethodsTest, decomposeAutomaton7 ) {
	using Number = double;
	using Matrix = matrix_t<Number>;
	using Vector = vector_t<Number>;

	auto ha = resetHa<Number>();
	HybridAutomaton<Number> decomposedHa;
	Decomposition decomposition;
	std::tie( decomposedHa, decomposition ) = decomposeAutomaton( ha );

	Decomposition expectedDecomposition{ { { 0 }, { 1, 2 } }, { DynamicType::discrete, DynamicType::discrete } };
	auto loc0 = decomposedHa.getLocations()[0];
	auto loc1 = decomposedHa.getLocations()[1];

	// Construct expected transition
	// l0 -> l1 with guard x <= 0, y + z <= 0 and reset x := [0,2], z := 0
	Matrix transConstraint0 = Matrix::Ones( 1, 1 );
	Vector transConstants0 = Vector::Zero( 1 );
	Matrix transConstraint1 = Matrix::Ones( 1, 2 );
	Vector transConstants1 = Vector::Zero( 1 );

	Condition<Number> expectedGuard( { ConstraintSetT<Number>{ transConstraint0, transConstants0 },
									   ConstraintSetT<Number>{ transConstraint1, transConstants1 } } );
	Reset<Number> expectedReset;
	expectedReset.setMatrix( Matrix::Identity( 1, 1 ), 0 );
	expectedReset.setVector( Vector::Zero( 1 ), 0 );
	expectedReset.setMatrix( Matrix::Identity( 2, 2 ), 1 );
	expectedReset.setVector( Vector::Zero( 2 ), 1 );
	expectedReset.setIntervals( { carl::Interval<Number>{ 0, 2 } }, 0 );
	expectedReset.setIntervals( { carl::Interval<Number>{}, carl::Interval<Number>{ 0, 0 } }, 1 );

	Transition<Location<Number>> expectedTrans( loc0, loc1, expectedGuard, expectedReset );

	EXPECT_EQ( expectedDecomposition.subspaces, decomposition.subspaces );
	EXPECT_EQ( expectedDecomposition.subspaceTypes, decomposition.subspaceTypes );
	auto trans = *decomposedHa.getLocations()[0]->getTransitions()[0].get();
	EXPECT_EQ( expectedTrans, trans );
}

TEST( DecompositionMethodsTest, decomposeAutomaton8 ) {
	using Number = double;
	using Matrix = matrix_t<Number>;
	using Vector = vector_t<Number>;

	auto ha = affineResetHa<Number>();
	HybridAutomaton<Number> decomposedHa;
	Decomposition decomposition;
	std::tie( decomposedHa, decomposition ) = decomposeAutomaton( ha );

	Decomposition expectedDecomposition{ { { 0, 1 }, { 2 } }, { DynamicType::discrete, DynamicType::discrete } };
	auto loc0 = decomposedHa.getLocations()[0];
	auto loc1 = decomposedHa.getLocations()[1];

	// Construct expected transition
	// l0 -> l1 with guard x <= 0 and reset x := y, z := 1
	Matrix transConstraint = Matrix::Zero( 1, 2 );
	Vector transConstants = Vector::Zero( 1 );
	transConstraint( 0, 0 ) = 1;

	Condition<Number> expectedGuard( { ConstraintSetT<Number>{ transConstraint, transConstants }, ConstraintSetT<Number>{} } );
	Reset<Number> expectedReset;
	Matrix resetMat0 = Matrix::Zero( 2, 2 );
	resetMat0( 0, 1 ) = 1;
	resetMat0( 1, 1 ) = 1;
	expectedReset.setMatrix( resetMat0, 0 );
	expectedReset.setVector( Vector::Zero( 2 ), 0 );
	expectedReset.setMatrix( Matrix::Zero( 1, 1 ), 1 );
	expectedReset.setVector( Vector::Ones( 1 ), 1 );
	expectedReset.setIntervals( { {}, {} }, 0 );
	expectedReset.setIntervals( { {} }, 1 );
	Transition<Location<Number>> expectedTrans( loc0, loc1, expectedGuard, expectedReset );

	EXPECT_EQ( expectedDecomposition.subspaces, decomposition.subspaces );
	EXPECT_EQ( expectedDecomposition.subspaceTypes, decomposition.subspaceTypes );
	auto trans = *decomposedHa.getLocations()[0]->getTransitions()[0].get();
	EXPECT_EQ( expectedTrans, trans );
}
