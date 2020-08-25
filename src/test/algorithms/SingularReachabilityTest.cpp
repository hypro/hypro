#include "../defines.h"
#include "gtest/gtest.h"
#include <algorithms/reachability/workers/SingularWorker.h>
#include <datastructures/HybridAutomaton/HybridAutomaton.h>
#include <datastructures/reachability/Settings.h>
#include <representations/GeometricObjectBase.h>
#include <algorithms/reachability/analyzer/SingularAnalyzer.h>

template <typename Number>
hypro::HybridAutomaton<Number> createBouncingBall() {
    using Matrix = hypro::matrix_t<Number>;
    using Vector = hypro::vector_t<Number>;

    hypro::HybridAutomaton<Number> res;

    hypro::Location<Number> loc;
    loc.setName( "l0" );

    Matrix invariantConstraints = Matrix::Zero( 1, 3 );
    invariantConstraints( 1, 1 ) = Number( -1 );
    Vector invariantConstants = Vector::Zero( 1 );
    loc.setInvariant( { invariantConstraints, invariantConstants } );

    res.addLocation( std::make_unique<hypro::Location<Number>>( loc ) );

    return hypro::HybridAutomaton<Number>{};
}

template <typename Number>
hypro::HybridAutomaton<Number> createSingularHA() {
    using Matrix = hypro::matrix_t<Number>;
    using Vector = hypro::vector_t<Number>;

    hypro::HybridAutomaton<Number> res;

    // Create location
    hypro::Location<Number> loc;

    // Set flow x' = 1
    Matrix flow = Matrix::Zero( 2, 2 );
    flow( 0, 1 ) = 1;
    loc.setFlow( flow );

    // Set invariant x <= 1
    Matrix invariantConstraints = Matrix::Zero( 1, 2 );
    invariantConstraints( 0, 0 ) = 1;
    Vector invariantConstants = Vector::Ones( 1 );
    loc.setInvariant( { invariantConstraints, invariantConstants } );

    // Set initial state x = 0, aff = 1
    Matrix initialConstraints = Matrix::Zero( 4, 2 );
    Vector initialConstants = Vector::Zero( 4 );
    initialConstraints << 1, 0,
                        -1, 0,
                        0, 1,
                        0, -1;
    initialConstants << 0, 0, 1, -1;

    // Create HA
    res.addLocation( std::make_unique<hypro::Location<Number>>( loc ) );
    res.addInitialState( &loc, hypro::Condition<Number>( initialConstraints, initialConstants ) );

    return res;
}

TEST( SingularRechabilityTest, WorkerConstruction ) {
    using Number = mpq_class;
    using VPoly = hypro::VPolytope<Number>;

    auto automaton = createSingularHA<Number>();

    auto worker =
          hypro::SingularWorker<VPoly>( automaton, hypro::Settings{ {}, { 1, hypro::tNumber( 10 ) }, {} } );    
}

TEST( SingularRechabilityTest, SingularAnalyzer ) {
    using Number = mpq_class;
    using VPoly = hypro::VPolytope<Number>;
    using Matrix = hypro::matrix_t<Number>;
    using Vector = hypro::vector_t<Number>;

    // Create automaton and analyzer
    auto automaton = createSingularHA<Number>();

    // Add bad states and analyze
    // 1. x >= 0.5 (unsafe)
    Matrix badStateMat = Matrix::Zero( 1, 2 );
    badStateMat << -1, 0;
    Vector badStateVec = -0.5*Vector::Ones( 1 );

    automaton.setGlobalBadStates( { hypro::Condition<Number>( badStateMat, badStateVec ) } );
    auto analyzer = hypro::SingularAnalyzer<VPoly>( automaton, hypro::Settings{ {}, { 0, hypro::tNumber( 4 ), hypro::tNumber( 0.01 ) }, {} } );
    hypro::REACHABILITY_RESULT result = analyzer.run();
    EXPECT_EQ( hypro::REACHABILITY_RESULT::UNKNOWN, result );
    
    // 2. x >= 2 (safe)
    badStateVec = -2*Vector::Ones( 1 );
    automaton.setGlobalBadStates( { hypro::Condition<Number>( badStateMat, badStateVec ) } );
    analyzer = hypro::SingularAnalyzer<VPoly>( automaton, hypro::Settings{ {}, { 0, hypro::tNumber( 4 ), hypro::tNumber( 0.01 ) }, {} } );
    result = analyzer.run();
    EXPECT_EQ( hypro::REACHABILITY_RESULT::SAFE, result );

}