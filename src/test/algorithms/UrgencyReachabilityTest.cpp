#include "../defines.h"
#include "automata/automataCreation.h"
#include "hypro/datastructures/HybridAutomaton/Condition.h"
#include "hypro/datastructures/HybridAutomaton/Location.h"
#include "hypro/datastructures/HybridAutomaton/Transition.h"
#include "hypro/types.h"
#include "hypro/util/VariablePool.h"
#include "gtest/gtest.h"
#include <carl/interval/Interval.h>
#include <hypro/algorithms/reachability/Reach.h>
#include <hypro/algorithms/reachability/workers/UrgencyWorker.h>
#include <hypro/datastructures/HybridAutomaton/HybridAutomaton.h>
#include <hypro/datastructures/reachability/ReachTreev2Util.h>
#include <hypro/datastructures/reachability/Settings.h>
#include <hypro/representations/GeometricObjectBase.h>
#include <hypro/util/plotting/Plotter.h>
#include <hypro/algorithms/reachability/analyzer/UrgencyCEGARAnalyzer.h>

using Number = mpq_class;
using VPoly = hypro::VPolytope<Number>;
using HPoly = hypro::HPolytope<Number>;
using Box = hypro::Box<Number>;
using Matrix = hypro::matrix_t<Number>;
using Vector = hypro::vector_t<Number>;
using Point = hypro::Point<Number>;

template <typename Number>
hypro::HybridAutomaton<Number> ha1() {
    // One-dimensional HA with one location
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
    Matrix invariantConstraints = Matrix::Zero( 1, 1 );
    invariantConstraints( 0, 0 ) = 1;
    Vector invariantConstants = Vector::Ones( 1 );
    loc.setInvariant( { invariantConstraints, invariantConstants } );

    // Set initial state x = 0, aff = 1
    Matrix initialConstraints = Matrix::Zero( 2, 1 );
    Vector initialConstants = Vector::Zero( 2 );
    initialConstraints << 1, -1;
    initialConstants << 0, 0;

    // Create HA
    auto& locPtr = res.addLocation( std::make_unique<hypro::Location<Number>>( loc ) );
    res.addInitialState( locPtr.get(), hypro::Condition<Number>( initialConstraints, initialConstants ) );

    return res;
}

template <typename Number>
hypro::HybridAutomaton<Number> ha2() {
    // One-dimensional HA with two location
    using Matrix = hypro::matrix_t<Number>;
    using Vector = hypro::vector_t<Number>;

    hypro::HybridAutomaton<Number> res;

    // Create locations
    hypro::Location<Number> loc0;
    hypro::Location<Number> loc1;
    auto uniqueLoc0{ std::make_unique<hypro::Location<Number>>( loc0 ) };
    auto uniqueLoc1{ std::make_unique<hypro::Location<Number>>( loc1 ) };
    uniqueLoc0->setName( "l0" );
    uniqueLoc1->setName( "l1" );

    // Set flow x' = 1 in loc0
    Matrix flow0 = Matrix::Zero( 2, 2 );
    flow0( 0, 1 ) = 1;
    uniqueLoc0->setFlow( flow0 );

    // Set flow x' = 0 in loc1
    Matrix flow1 = Matrix::Zero( 2, 2 );
    uniqueLoc1->setFlow( flow1 );

    // Set invariant x <= 3 in loc0
    Matrix invariantConstraints = Matrix::Zero( 1, 1 );
    invariantConstraints( 0, 0 ) = 1;
    Vector invariantConstants = 3 * Vector::Ones( 1 );
    uniqueLoc0->setInvariant( { invariantConstraints, invariantConstants } );

    // Construct transitions
    // l0 -> l1 with guard x >= 1
    Matrix transConstraint = Matrix::Zero( 1, 1 );
    Vector transConstants = -1 * Vector::Ones( 1 );
    transConstraint( 0, 0 ) = -1;
    hypro::Condition<Number> guard( transConstraint, transConstants );
    hypro::Reset<Number> reset{ Matrix::Ones( 1, 1 ), Vector::Zero( 1 ) };

    std::unique_ptr<hypro::Transition<Number>> trans =
          std::make_unique<hypro::Transition<Number>>( uniqueLoc0.get(), uniqueLoc1.get(), guard, reset );

    trans->setUrgent();
    // Set initial state x = 0, aff = 1 in loc0
    Matrix initialConstraints = Matrix::Zero( 2, 1 );
    Vector initialConstants = Vector::Zero( 2 );
    initialConstraints << 1, -1;
    initialConstants << 0, 0;

    // Create HA
    uniqueLoc0->addTransition( std::move( trans ) );

    res.addLocation( std::move( uniqueLoc0 ) );
    res.addLocation( std::move( uniqueLoc1 ) );

    hypro::Location<Number>* loc0ptr = res.getLocation( "l0" );
    res.addInitialState( loc0ptr, hypro::Condition<Number>( initialConstraints, initialConstants ) );

    return res;
}

template <typename Number>
hypro::HybridAutomaton<Number> ha3() {
    // One-dimensional HA with two locations
    using Matrix = hypro::matrix_t<Number>;
    using Vector = hypro::vector_t<Number>;

    hypro::HybridAutomaton<Number> res;

    // Create locations
    hypro::Location<Number> loc0;
    hypro::Location<Number> loc1;
    auto uniqueLoc0{ std::make_unique<hypro::Location<Number>>( loc0 ) };
    auto uniqueLoc1{ std::make_unique<hypro::Location<Number>>( loc1 ) };
    uniqueLoc0->setName( "l0" );
    uniqueLoc1->setName( "l1" );

    // Set flow x' = 1 in loc0
    Matrix flow0 = Matrix::Zero( 2, 2 );
    flow0( 0, 1 ) = 1;
    uniqueLoc0->setFlow( flow0 );

    // Set flow x' = 0 in loc1
    Matrix flow1 = Matrix::Zero( 2, 2 );
    uniqueLoc1->setFlow( flow1 );

    // Set invariant x <= 3 in loc0
    Matrix invariantConstraints = Matrix::Zero( 1, 1 );
    invariantConstraints( 0, 0 ) = 1;
    Vector invariantConstants = 3 * Vector::Ones( 1 );
    uniqueLoc0->setInvariant( { invariantConstraints, invariantConstants } );

    // Construct transitions
    // l0 -> l1 urgent with guard x >= 10
    Matrix transConstraint1 = Matrix::Zero( 1, 1 );
    Vector transConstants1 = -10 * Vector::Ones( 1 );
    transConstraint1( 0, 0 ) = -1;
    hypro::Condition<Number> guard1( transConstraint1, transConstants1 );
    hypro::Reset<Number> reset1{ Matrix::Ones( 1, 1 ), Vector::Zero( 1 ) };

    std::unique_ptr<hypro::Transition<Number>> trans1 =
          std::make_unique<hypro::Transition<Number>>( uniqueLoc0.get(), uniqueLoc1.get(), guard1, reset1 );
    trans1->setUrgent();

    // l0 -> l1 urgent with guard x >= 1
    Matrix transConstraint2 = Matrix::Zero( 1, 1 );
    Vector transConstants2 = -1 * Vector::Ones( 1 );
    transConstraint2( 0, 0 ) = -1;
    hypro::Condition<Number> guard2( transConstraint2, transConstants2 );
    hypro::Reset<Number> reset2{ Matrix::Ones( 1, 1 ), Vector::Zero( 1 ) };

    std::unique_ptr<hypro::Transition<Number>> trans2 =
          std::make_unique<hypro::Transition<Number>>( uniqueLoc0.get(), uniqueLoc1.get(), guard2, reset2 );
    trans2->setUrgent();

    // Set initial state x = 0, aff = 1 in loc0
    Matrix initialConstraints = Matrix::Zero( 2, 1 );
    Vector initialConstants = Vector::Zero( 2 );
    initialConstraints << 1, -1;
    initialConstants << 0, 0;

    // Create HA
    uniqueLoc0->addTransition( std::move( trans1 ) );
    uniqueLoc0->addTransition( std::move( trans2 ) );

    res.addLocation( std::move( uniqueLoc0 ) );
    res.addLocation( std::move( uniqueLoc1 ) );

    hypro::Location<Number>* loc0ptr = res.getLocation( "l0" );
    res.addInitialState( loc0ptr, hypro::Condition<Number>( initialConstraints, initialConstants ) );

    return res;
}

TEST( UrgencyCutoff, Box ) {
    Vector p1( 2 ), p2( 2 ), p3( 2 ), p4( 2 );
    p1 << 0, 0;
    p2 << 0, 1;
    p3 << 1, 0;
    p4 << 1, 1;
    VPoly cube( std::vector<Point>{ Point( p1 ), Point( p2 ), Point( p3 ), Point( p4 ) } );
    Matrix mat1 = Matrix::Zero( 1, 2 );
    mat1 << -1, -1;
    Vector vec1 = -1.5 * Vector::Ones( 1 );
    hypro::Condition<Number> cond1( mat1, vec1 );
    hypro::ltiUrgencyHandler<VPoly> urgencyHandler;
    auto res1 = urgencyHandler.cutoff( cube, cond1 );

    Vector p5( 2 ), p6( 2 );
    p5 << 0.5, 1;
    p6 << 1, 0.5;
    VPoly expectedRes1( std::vector<Point>{ Point( p1 ), Point( p2 ), Point( p3 ), Point( p5 ), Point( p6 ) } );
    EXPECT_TRUE( expectedRes1.contains( res1 ) );
    EXPECT_TRUE( res1.contains( expectedRes1 ) );

    Matrix mat2 = Matrix::Zero( 1, 2 );
    mat2 << 1, 1;
    Vector vec2 = 1.5 * Vector::Ones( 1 );
    hypro::Condition<Number> cond2( mat2, vec2 );
    auto res2 = urgencyHandler.cutoff( cube, cond2 );

    VPoly expectedRes2( std::vector<Point>{ Point( p4 ), Point( p5 ), Point( p6 ) } );
    EXPECT_TRUE( expectedRes2.contains( res2 ) );
    EXPECT_TRUE( res2.contains( expectedRes2 ) );
}


TEST( UrgencyReachabilityTest, WorkerConstruction ) {
    auto automaton = ha1<Number>();
    hypro::AnalysisParameters analysisParameters;
    analysisParameters.timeStep = hypro::tNumber( 1 ) / hypro::tNumber( 100 );
    analysisParameters.aggregation = hypro::AGG_SETTING::AGG;
    analysisParameters.representation_type = hypro::representation_name::polytope_h;
    hypro::TimeTransformationCache<Number> transformationCache;
    auto worker = hypro::UrgencyWorker<HPoly>( automaton, analysisParameters, hypro::tNumber( 10 ), transformationCache );
    auto roots = hypro::makeRoots<HPoly>( automaton );
    worker.computeTimeSuccessors( roots[ 0 ] );
    SUCCEED();
}

TEST( UrgencyReachabilityTest, AnalyzerConstruction ) {
    auto automaton = ha1<Number>();
    hypro::AnalysisParameters analysisParameters;
    analysisParameters.timeStep = hypro::tNumber( 1 ) / hypro::tNumber( 100 );
    analysisParameters.aggregation = hypro::AGG_SETTING::AGG;
    analysisParameters.representation_type = hypro::representation_name::polytope_h;
    hypro::FixedAnalysisParameters fixedParams{ 5, hypro::tNumber( 10 ), hypro::tNumber( 0.01 ) };
    hypro::UrgencyCEGARAnalyzer<HPoly> analyzer( automaton, fixedParams, analysisParameters );
    analyzer.run();
    SUCCEED();  
}

TEST( UrgencyReachabilityTest, Refine ) {
    auto automaton = ha2<Number>();
    Matrix badStateMat = -1 * Matrix::Ones( 1, 1 );
    Vector badStateVec = -2 * Vector::Ones( 1 );

    auto l1 = automaton.getLocation( "l1" );

    std::map<const hypro::Location<Number>*, hypro::Condition<Number>> localBadStates;
    hypro::Condition<Number> badState( badStateMat, badStateVec );
    localBadStates[l1] = badState;
    automaton.setLocalBadStates( localBadStates );

    hypro::AnalysisParameters analysisParameters;
    analysisParameters.timeStep = hypro::tNumber( 1 ) / hypro::tNumber( 100 );
    analysisParameters.aggregation = hypro::AGG_SETTING::AGG;
    analysisParameters.representation_type = hypro::representation_name::polytope_h;
    hypro::FixedAnalysisParameters fixedParams{ 5, hypro::tNumber( 10 ), hypro::tNumber( 0.1 ) };
    hypro::UrgencyCEGARAnalyzer<HPoly> analyzer( automaton, fixedParams, analysisParameters );
    auto result = analyzer.run();
    EXPECT_EQ( hypro::REACHABILITY_RESULT::UNKNOWN, result.result() );
    SUCCEED();
}

TEST( UrgencyReachabilityTest, Refine2 ) {
    auto automaton = ha3<Number>();
    Matrix badStateMat = -1 * Matrix::Ones( 1, 1 );
    Vector badStateVec = -2 * Vector::Ones( 1 );

    auto l1 = automaton.getLocation( "l1" );

    std::map<const hypro::Location<Number>*, hypro::Condition<Number>> localBadStates;
    hypro::Condition<Number> badState( badStateMat, badStateVec );
    localBadStates[l1] = badState;
    automaton.setLocalBadStates( localBadStates );

    hypro::AnalysisParameters analysisParameters;
    analysisParameters.timeStep = hypro::tNumber( 1 ) / hypro::tNumber( 100 );
    analysisParameters.aggregation = hypro::AGG_SETTING::AGG;
    analysisParameters.representation_type = hypro::representation_name::polytope_h;
    hypro::FixedAnalysisParameters fixedParams{ 5, hypro::tNumber( 10 ), hypro::tNumber( 0.1 ) };
    hypro::UrgencyCEGARAnalyzer<Box> analyzer( automaton, fixedParams, analysisParameters );
    auto result = analyzer.run();
    EXPECT_EQ( hypro::REACHABILITY_RESULT::UNKNOWN, result.result() );
    SUCCEED();
}