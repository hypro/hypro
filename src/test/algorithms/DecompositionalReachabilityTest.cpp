#include "gtest/gtest.h"
#include <hypro/datastructures/HybridAutomaton/HybridAutomaton.h>
#include <hypro/datastructures/HybridAutomaton/decomposition/DecompositionMethods.h>
#include <hypro/algorithms/reachability/analyzer/DecompositionalAnalyzer.h>


using namespace hypro;

template<typename Number>
HybridAutomaton<Number> makeHa() {
    using Matrix = matrix_t<Number>;
    using Vector = vector_t<Number>;

    HybridAutomaton<Number> ha;

    // Create location
    Location<Number> loc;

    // Set flow x' = y, y' = -x, z' = 2
    Matrix flow = Matrix::Zero( 4, 4 );
    flow( 0, 1 ) = 1;
    flow( 1, 0 ) = -1;
    flow( 2, 3 ) = 2;
    loc.setFlow( flow );

    // Set invariant z <= 30
    Matrix invariantConstraints = Matrix::Zero( 1, 3 );
    invariantConstraints( 0, 2 ) = 1;
    Vector invariantConstants = 30 * Vector::Ones( 1 );
    loc.setInvariant( { invariantConstraints, invariantConstants } );

    // Set initial state x = 1, y = 1, z = [0, 10]
    Matrix initialConstraints = Matrix::Zero( 6, 3 );
    Vector initialConstants = Vector::Zero( 6 );
    initialConstraints << 1, 0, 0,
                        -1, 0, 0,
                        0, 1, 0,
                        0, -1, 0,
                        0, 0, 1,
                        0, 0, -1;
    initialConstants << 1, -1, 1, -1, 10, 0;

    // Create HA
    auto& locPtr = ha.addLocation( std::make_unique<Location<Number>>( loc ) );
    ha.addInitialState( locPtr.get(), Condition<Number>( initialConstraints, initialConstants ) );
    return ha;
}



TEST( DecompositionalAnalysis, NoBadStatesNoJumps ) {
    using Number = double;
    using Matrix = matrix_t<Number>;
    using Vector = vector_t<Number>;
    using Representation = VPolytope<Number>;

    auto ha = makeHa<Number>();
    auto [decomposedHa, decomposition] = decomposeAutomaton( ha );
    for ( std::size_t subspace = 0; subspace < decomposition.subspaceTypes.size(); ++subspace ) {
        if ( decomposition.subspaceTypes[ subspace ] != DynamicType::linear && decomposition.subspaceTypes[ subspace ] != DynamicType::affine ) {
            addClockToAutomaton( decomposedHa, subspace );
        }
    }
    std::vector<std::vector<ReachTreeNode<Representation>>> roots = makeDecompositionalRoots<Representation, Number>( decomposedHa, decomposition );
    DecompositionalAnalyzer<Representation> analyzer( decomposedHa, decomposition, FixedAnalysisParameters{1, 50, 0.1}, AnalysisParameters{ 0.1 }, roots );
    analyzer.run();
}

TEST( DecompositionalAnalysis, SafeNoJumps ) {
    using Number = double;
    using Matrix = matrix_t<Number>;
    using Vector = vector_t<Number>;
    using Representation = VPolytope<Number>;

    auto ha = makeHa<Number>();
    // bad state: x <= 0 && z <= 4 (safe)
    Matrix badStateMat = Matrix::Zero( 2, 3 );
    badStateMat( 0, 0 ) = 1;
    badStateMat( 1, 2 ) = 1;
    Vector badStateVec = Vector::Zero( 2 );
    badStateVec( 1 ) = 4;
    ha.setGlobalBadStates( { Condition<Number>( badStateMat, badStateVec ) } );
    auto [decomposedHa, decomposition] = decomposeAutomaton( ha );
    for ( std::size_t subspace = 0; subspace < decomposition.subspaceTypes.size(); ++subspace ) {
        if ( decomposition.subspaceTypes[ subspace ] != DynamicType::linear && decomposition.subspaceTypes[ subspace ] != DynamicType::affine ) {
            addClockToAutomaton( decomposedHa, subspace );
        }
    }
    std::vector<std::vector<ReachTreeNode<Representation>>> roots = makeDecompositionalRoots<Representation, Number>( decomposedHa, decomposition );
    DecompositionalAnalyzer<Representation> analyzer( decomposedHa, decomposition, FixedAnalysisParameters{1, 50, 0.1}, AnalysisParameters{ 0.1 }, roots );
    auto result = analyzer.run();
    EXPECT_EQ( hypro::REACHABILITY_RESULT::SAFE, result.result() );
}

TEST( DecompositionalAnalysis, UnsafeNoJumps ) {
    using Number = double;
    using Matrix = matrix_t<Number>;
    using Vector = vector_t<Number>;
    using Representation = VPolytope<Number>;

    auto ha = makeHa<Number>();
    // bad state: x <= 0 && z <= 20 (safe)
    Matrix badStateMat = Matrix::Zero( 2, 3 );
    badStateMat( 0, 0 ) = 1;
    badStateMat( 1, 2 ) = 1;
    Vector badStateVec = Vector::Zero( 2 );
    badStateVec( 1 ) = 20;
    ha.setGlobalBadStates( { Condition<Number>( badStateMat, badStateVec ) } );
    auto [decomposedHa, decomposition] = decomposeAutomaton( ha );
    for ( std::size_t subspace = 0; subspace < decomposition.subspaceTypes.size(); ++subspace ) {
        if ( decomposition.subspaceTypes[ subspace ] != DynamicType::linear && decomposition.subspaceTypes[ subspace ] != DynamicType::affine ) {
            addClockToAutomaton( decomposedHa, subspace );
        }
    }
    std::vector<std::vector<ReachTreeNode<Representation>>> roots = makeDecompositionalRoots<Representation, Number>( decomposedHa, decomposition );
    DecompositionalAnalyzer<Representation> analyzer( decomposedHa, decomposition, FixedAnalysisParameters{1, 50, 0.1}, AnalysisParameters{ 0.1 }, roots );
    auto result = analyzer.run();
    EXPECT_EQ( hypro::REACHABILITY_RESULT::UNKNOWN, result.result() );

}