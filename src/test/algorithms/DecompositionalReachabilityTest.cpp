#include "gtest/gtest.h"
#include <hypro/datastructures/HybridAutomaton/decomposition/DecompositionMethods.h>
#include <hypro/algorithms/reachability/analyzer/DecompositionalAnalyzer.h>
#include "decompositionalReachabilityAutomata.h"


using namespace hypro;

TEST( DecompositionalAnalysisMixedDynamics, NoJumpsNoBadStates ) {
    using Number = mpq_class;
    using Representation = VPolytope<Number>;

    std::size_t jumpDepth = 100;
    tNumber timeHorizon = 50;
    tNumber timeStep = 0.1;

    auto ha = mixedDynamicsNoJumpsHa<Number>();
    auto [decomposedHa, decomposition] = decomposeAutomaton( ha );
    for ( std::size_t subspace = 0; subspace < decomposition.subspaceTypes.size(); ++subspace ) {
        if ( decomposition.subspaceTypes[ subspace ] != DynamicType::linear && decomposition.subspaceTypes[ subspace ] != DynamicType::affine ) {
            addClockToAutomaton( decomposedHa, subspace, 2);
        }
    }
    std::vector<std::vector<ReachTreeNode<Representation>>> roots = makeDecompositionalRoots<Representation, Number>( decomposedHa, decomposition );
    DecompositionalAnalyzer<Representation> analyzer( decomposedHa, decomposition, FixedAnalysisParameters{jumpDepth, timeHorizon, timeStep}, AnalysisParameters{ timeStep }, roots );
    analyzer.run();
}

TEST( DecompositionalAnalysisMixedDynamics, NoJumpsSafe ) {
    using Number = mpq_class;
    using Matrix = matrix_t<Number>;
    using Vector = vector_t<Number>;
    using Representation = VPolytope<Number>;

    std::size_t jumpDepth = 100;
    tNumber timeHorizon = 50;
    tNumber timeStep = 0.1;

    auto ha = mixedDynamicsNoJumpsHa<Number>();
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
            addClockToAutomaton( decomposedHa, subspace, 2);
        }
    }
    std::vector<std::vector<ReachTreeNode<Representation>>> roots = makeDecompositionalRoots<Representation, Number>( decomposedHa, decomposition );
    DecompositionalAnalyzer<Representation> analyzer( decomposedHa, decomposition, FixedAnalysisParameters{jumpDepth, timeHorizon, timeStep}, AnalysisParameters{ timeStep }, roots );
    auto result = analyzer.run();
    EXPECT_EQ( REACHABILITY_RESULT::SAFE, result.result() );
}

TEST( DecompositionalAnalysisMixedDynamics, NoJumpsUnsafe ) {
    using Number = mpq_class;
    using Matrix = matrix_t<Number>;
    using Vector = vector_t<Number>;
    using Representation = VPolytope<Number>;

    std::size_t jumpDepth = 100;
    tNumber timeHorizon = 50;
    tNumber timeStep = 0.1;

    auto ha = mixedDynamicsNoJumpsHa<Number>();
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
            addClockToAutomaton( decomposedHa, subspace, 2);
        }
    }
    std::vector<std::vector<ReachTreeNode<Representation>>> roots = makeDecompositionalRoots<Representation, Number>( decomposedHa, decomposition );
    DecompositionalAnalyzer<Representation> analyzer( decomposedHa, decomposition, FixedAnalysisParameters{jumpDepth, timeHorizon, timeStep}, AnalysisParameters{ timeStep }, roots );
    auto result = analyzer.run();
    EXPECT_EQ( REACHABILITY_RESULT::UNKNOWN, result.result() );
}

TEST( DecompositionalAnalysisMixedDynamics, JumpsNoBadStates ) {
    using Number = mpq_class;
    using Representation = VPolytope<Number>;

    std::size_t jumpDepth = 3;
    tNumber timeHorizon = 10;
    tNumber timeStep = 0.1;

    auto ha = mixedDynamicsWithJumpsHa<Number>();
    auto [decomposedHa, decomposition] = decomposeAutomaton( ha );
    ASSERT_EQ( (std::size_t) 2, decomposition.subspaces.size() );
    EXPECT_EQ( DynamicType::linear, decomposition.subspaceTypes[ 0 ] );
    EXPECT_EQ( DynamicType::singular, decomposition.subspaceTypes[ 1 ] );
    for ( std::size_t subspace = 0; subspace < decomposition.subspaceTypes.size(); ++subspace ) {
        if ( decomposition.subspaceTypes[ subspace ] != DynamicType::linear && decomposition.subspaceTypes[ subspace ] != DynamicType::affine ) {
            addClockToAutomaton( decomposedHa, subspace, 2 );
        }
    }
    std::vector<std::vector<ReachTreeNode<Representation>>> roots = makeDecompositionalRoots<Representation, Number>( decomposedHa, decomposition );
    DecompositionalAnalyzer<Representation> analyzer( decomposedHa, decomposition, FixedAnalysisParameters{jumpDepth, timeHorizon, timeStep}, AnalysisParameters{ timeStep }, roots );

    analyzer.run();
}

TEST( DecompositionalAnalysisSingular, TimeElapseNoInvariant ) {
    using Number = mpq_class;
    using Representation = VPolytope<Number>;
    using Point = Point<Number>;

    std::size_t jumpDepth = 100;
    tNumber timeHorizon = 50;
    tNumber timeStep = 0.1;

    auto ha = singularNoJumpsNoInvHa<Number>();
    auto [decomposedHa, decomposition] = decomposeAutomaton( ha );
    for ( std::size_t subspace = 0; subspace < decomposition.subspaceTypes.size(); ++subspace ) {
        if ( decomposition.subspaceTypes[ subspace ] != DynamicType::linear && decomposition.subspaceTypes[ subspace ] != DynamicType::affine ) {
            addClockToAutomaton( decomposedHa, subspace, 2 );
        }
    }
    std::vector<std::vector<ReachTreeNode<Representation>>> roots = makeDecompositionalRoots<Representation, Number>( decomposedHa, decomposition );
    DecompositionalAnalyzer<Representation> analyzer( decomposedHa, decomposition, FixedAnalysisParameters{jumpDepth, timeHorizon, timeStep}, AnalysisParameters{ timeStep }, roots );
    auto result = analyzer.run();

    EXPECT_EQ( REACHABILITY_RESULT::SAFE, result.result() );

    // one initial set
    EXPECT_EQ( 1, roots.size() );
    // two subspaces
    EXPECT_EQ( 2, roots[0].size() );
    // no jumps
    EXPECT_EQ( 0, roots[0][0].getChildren().size() );
    EXPECT_EQ( 0, roots[0][1].getChildren().size() );    
    // get time elapse segments
    auto flowpipeSubspace0 = roots[0][0].getFlowpipe();
    auto flowpipeSubspace1 = roots[0][1].getFlowpipe();
    // singular flowpipes have exactly two segments, where the first is the initial set
    EXPECT_EQ( 2, flowpipeSubspace0.size() );
    EXPECT_EQ( 2, flowpipeSubspace1.size() );
    auto segmentSubspace0 = flowpipeSubspace0[ 1 ];
    auto segmentSubspace1 = flowpipeSubspace1[ 1 ];
    // transform to vpolytope
    State<Number, Representation> segment;
    segment.setSet<Representation>( segmentSubspace0, 0 );
    segment.setSet<Representation>( segmentSubspace1, 1 );
    VPolytope<Number> reachableSet = VPolytope<Number>( composeSubspaces( segment, 0, 1, decomposition ) );

    VPolytope<Number> expectedReachableSet = VPolytope<Number>( std::vector<Point>{ 
        Point{ 0, 0 }, Point{ 0, 1 }, Point{ 1, 0 }, Point{ 1, 1 },
        Point{ 1 + timeHorizon, timeHorizon }, Point{ 1 + timeHorizon, 1 + timeHorizon }, Point{ timeHorizon, 1 + timeHorizon } } );
    EXPECT_TRUE( expectedReachableSet.contains( reachableSet ) );
    EXPECT_TRUE( reachableSet.contains( expectedReachableSet ) );
}

TEST( DecompositionalAnalysisSingular, TimeElapseNoInvariantSafetyCheck1 ) {
    using Number = mpq_class;
    using Matrix = matrix_t<Number>;
    using Vector = vector_t<Number>;
    using Representation = VPolytope<Number>;
    using Point = Point<Number>;

    std::size_t jumpDepth = 100;
    tNumber timeHorizon = 50;
    tNumber timeStep = 0.1;

    auto ha = singularNoJumpsNoInvHa<Number>();
    // x >= 3, y <= 1 is safe
    Matrix badStateMat = Matrix::Zero( 2, 2 );
    badStateMat( 0, 0 ) = -1;
    badStateMat( 1, 1 ) = 1;
    Vector badStateVec = Vector::Zero( 2 );
    badStateVec << -3, 1;
    ha.setGlobalBadStates( { Condition<Number>( badStateMat, badStateVec ) } );
    auto [decomposedHa, decomposition] = decomposeAutomaton( ha );

    for ( std::size_t subspace = 0; subspace < decomposition.subspaceTypes.size(); ++subspace ) {
        if ( decomposition.subspaceTypes[ subspace ] != DynamicType::linear && decomposition.subspaceTypes[ subspace ] != DynamicType::affine ) {
            addClockToAutomaton( decomposedHa, subspace, 2 );
        }
    }
    std::vector<std::vector<ReachTreeNode<Representation>>> roots = makeDecompositionalRoots<Representation, Number>( decomposedHa, decomposition );
    DecompositionalAnalyzer<Representation> analyzer( decomposedHa, decomposition, FixedAnalysisParameters{jumpDepth, timeHorizon, timeStep}, AnalysisParameters{ timeStep }, roots );
    auto result = analyzer.run();
    EXPECT_EQ( REACHABILITY_RESULT::SAFE, result.result() );
}

TEST( DecompositionalAnalysisSingular, TimeElapseNoInvariantSafetyCheck2 ) {
    using Number = mpq_class;
    using Matrix = matrix_t<Number>;
    using Vector = vector_t<Number>;
    using Representation = VPolytope<Number>;
    using Point = Point<Number>;

    std::size_t jumpDepth = 100;
    tNumber timeHorizon = 50;
    tNumber timeStep = 0.1;

    auto ha = singularNoJumpsNoInvHa<Number>();
    // x >= 3, y <= 2 is usafe
    Matrix badStateMat = Matrix::Zero( 2, 2 );
    badStateMat( 0, 0 ) = -1;
    badStateMat( 1, 1 ) = 1;
    Vector badStateVec = Vector::Zero( 2 );
    badStateVec << -3, 2;
    ha.setGlobalBadStates( { Condition<Number>( badStateMat, badStateVec ) } );
    auto [decomposedHa, decomposition] = decomposeAutomaton( ha );

    for ( std::size_t subspace = 0; subspace < decomposition.subspaceTypes.size(); ++subspace ) {
        if ( decomposition.subspaceTypes[ subspace ] != DynamicType::linear && decomposition.subspaceTypes[ subspace ] != DynamicType::affine ) {
            addClockToAutomaton( decomposedHa, subspace, 2 );
        }
    }
    std::vector<std::vector<ReachTreeNode<Representation>>> roots = makeDecompositionalRoots<Representation, Number>( decomposedHa, decomposition );
    DecompositionalAnalyzer<Representation> analyzer( decomposedHa, decomposition, FixedAnalysisParameters{jumpDepth, timeHorizon, timeStep}, AnalysisParameters{ timeStep }, roots );
    auto result = analyzer.run();
    EXPECT_EQ( REACHABILITY_RESULT::UNKNOWN, result.result() );
}

TEST( DecompositionalAnalysisSingular, TimeElapseWithInv1 ) {
    using Number = mpq_class;
    using Matrix = matrix_t<Number>;
    using Vector = vector_t<Number>;
    using Representation = VPolytope<Number>;
    using Point = Point<Number>;

    std::size_t jumpDepth = 100;
    tNumber timeHorizon = 50;
    tNumber timeStep = 0.1;

    auto ha = singularNoJumpsWithInvHa1<Number>();
    // y >= 7 is safe, but reachable in the subspace computation
    Matrix badStateMat = Matrix::Zero( 1, 2 );
    badStateMat( 0, 1 ) = -1;
    Vector badStateVec = Vector::Zero( 1 );
    badStateVec << -7;
    ha.setGlobalBadStates( { Condition<Number>( badStateMat, badStateVec ) } );
    auto [decomposedHa, decomposition] = decomposeAutomaton( ha );
    for ( std::size_t subspace = 0; subspace < decomposition.subspaceTypes.size(); ++subspace ) {
        if ( decomposition.subspaceTypes[ subspace ] != DynamicType::linear && decomposition.subspaceTypes[ subspace ] != DynamicType::affine ) {
            addClockToAutomaton( decomposedHa, subspace, 2 );
        }
    }
    std::vector<std::vector<ReachTreeNode<Representation>>> roots = makeDecompositionalRoots<Representation, Number>( decomposedHa, decomposition );
    DecompositionalAnalyzer<Representation> analyzer( decomposedHa, decomposition, FixedAnalysisParameters{jumpDepth, timeHorizon, timeStep}, AnalysisParameters{ timeStep }, roots );
    auto result = analyzer.run();

    EXPECT_EQ( REACHABILITY_RESULT::SAFE, result.result() );

    // one initial set
    EXPECT_EQ( 1, roots.size() );
    // two subspaces
    EXPECT_EQ( 2, roots[0].size() );
    // no jumps
    EXPECT_EQ( 0, roots[0][0].getChildren().size() );
    EXPECT_EQ( 0, roots[0][1].getChildren().size() );    
    // get time elapse segments
    auto flowpipeSubspace0 = roots[0][0].getFlowpipe();
    auto flowpipeSubspace1 = roots[0][1].getFlowpipe();
    // singular flowpipes have exactly two segments, where the first is the initial set
    EXPECT_EQ( 2, flowpipeSubspace0.size() );
    EXPECT_EQ( 2, flowpipeSubspace1.size() );
    auto segmentSubspace0 = flowpipeSubspace0[ 1 ];
    auto segmentSubspace1 = flowpipeSubspace1[ 1 ];
    // transform to vpolytope
    State<Number, Representation> segment;
    segment.setSet<Representation>( segmentSubspace0, 0 );
    segment.setSet<Representation>( segmentSubspace1, 1 );
    VPolytope<Number> reachableSet = VPolytope<Number>( composeSubspaces( segment, 0, 1, decomposition ) );

    VPolytope<Number> expectedReachableSet = VPolytope<Number>( std::vector<Point>{ 
        Point{ 0, 0 }, Point{ 0, 1 }, Point{ 1, 0 }, Point{ 1, 1 },
        Point{ 5, 4 }, Point{ 5, 5 }, Point{ 5, 6 }, Point{ 4, 5 } } );
    EXPECT_TRUE( expectedReachableSet.contains( reachableSet ) );
    EXPECT_TRUE( reachableSet.contains( expectedReachableSet ) );
}

TEST( DecompositionalAnalysisSingular, TimeElapseWithInv2 ) {
    using Number = mpq_class;
    using Representation = VPolytope<Number>;
    using Point = Point<Number>;

    std::size_t jumpDepth = 100;
    tNumber timeHorizon = 50;
    tNumber timeStep = 0.1;

    auto ha = singularNoJumpsWithInvHa2<Number>();
    auto [decomposedHa, decomposition] = decomposeAutomaton( ha );
    for ( std::size_t subspace = 0; subspace < decomposition.subspaceTypes.size(); ++subspace ) {
        if ( decomposition.subspaceTypes[ subspace ] != DynamicType::linear && decomposition.subspaceTypes[ subspace ] != DynamicType::affine ) {
            addClockToAutomaton( decomposedHa, subspace, 2 );
        }
    }
    std::vector<std::vector<ReachTreeNode<Representation>>> roots = makeDecompositionalRoots<Representation, Number>( decomposedHa, decomposition );
    DecompositionalAnalyzer<Representation> analyzer( decomposedHa, decomposition, FixedAnalysisParameters{jumpDepth, timeHorizon, timeStep}, AnalysisParameters{ timeStep }, roots );
    auto result = analyzer.run();

    EXPECT_EQ( REACHABILITY_RESULT::SAFE, result.result() );

    // one initial set
    EXPECT_EQ( 1, roots.size() );
    // two subspaces
    EXPECT_EQ( 2, roots[0].size() );
    // no jumps
    EXPECT_EQ( 0, roots[0][0].getChildren().size() );
    EXPECT_EQ( 0, roots[0][1].getChildren().size() );    
    // get time elapse segments
    auto flowpipeSubspace0 = roots[0][0].getFlowpipe();
    auto flowpipeSubspace1 = roots[0][1].getFlowpipe();
    // singular flowpipes have exactly two segments, where the first is the initial set
    EXPECT_EQ( 2, flowpipeSubspace0.size() );
    EXPECT_EQ( 2, flowpipeSubspace1.size() );
    auto segmentSubspace0 = flowpipeSubspace0[ 1 ];
    auto segmentSubspace1 = flowpipeSubspace1[ 1 ];
    // transform to vpolytope
    State<Number, Representation> segment;
    segment.setSet<Representation>( segmentSubspace0, 0 );
    segment.setSet<Representation>( segmentSubspace1, 1 );
    VPolytope<Number> reachableSet = VPolytope<Number>( composeSubspaces( segment, 0, 1, decomposition ) );

    VPolytope<Number> expectedReachableSet = VPolytope<Number>( std::vector<Point>{ 
        Point{ 0, 0 }, Point{ 0, 1 }, Point{ 1, 0 }, Point{ 1, 1 },
        Point{ 5, 4 }, Point{ 5, 5 }, Point{ 5, 6 }, Point{ 4, 5 } } );
    EXPECT_TRUE( expectedReachableSet.contains( reachableSet ) );
    EXPECT_TRUE( reachableSet.contains( expectedReachableSet ) );
}

TEST( DecompositionalAnalysisSingular, JumpsGuard1 ) {
    using Number = mpq_class;
    using Representation = VPolytope<Number>;
    using Point = Point<Number>;

    std::size_t jumpDepth = 100;
    tNumber timeHorizon = 50;
    tNumber timeStep = 0.1;

    auto ha = singularGuardHa1<Number>();
    auto [decomposedHa, decomposition] = decomposeAutomaton( ha );
    for ( std::size_t subspace = 0; subspace < decomposition.subspaceTypes.size(); ++subspace ) {
        if ( decomposition.subspaceTypes[ subspace ] != DynamicType::linear && decomposition.subspaceTypes[ subspace ] != DynamicType::affine ) {
            addClockToAutomaton( decomposedHa, subspace, 2 );
        }
    }
    std::vector<std::vector<ReachTreeNode<Representation>>> roots = makeDecompositionalRoots<Representation, Number>( decomposedHa, decomposition );
    DecompositionalAnalyzer<Representation> analyzer( decomposedHa, decomposition, FixedAnalysisParameters{jumpDepth, timeHorizon, timeStep}, AnalysisParameters{ timeStep }, roots );
    auto result = analyzer.run();

    EXPECT_EQ( REACHABILITY_RESULT::SAFE, result.result() );

    // one initial set
    EXPECT_EQ( 1, roots.size() );
    // two subspaces
    EXPECT_EQ( 2, roots[0].size() );
    // one jump
    EXPECT_EQ( 1, roots[0][0].getChildren().size() );
    EXPECT_EQ( 1, roots[0][1].getChildren().size() );    
    // get successor segments
    auto flowpipeSubspace0 = roots[0][0].getChildren()[0]->getFlowpipe();
    auto flowpipeSubspace1 = roots[0][1].getChildren()[0]->getFlowpipe();
    // singular flowpipes have exactly two segments, where the first is the initial set
    EXPECT_EQ( 2, flowpipeSubspace0.size() );
    EXPECT_EQ( 2, flowpipeSubspace1.size() );
    auto segmentSubspace0 = flowpipeSubspace0[ 1 ];
    auto segmentSubspace1 = flowpipeSubspace1[ 1 ];
    // transform to vpolytope
    State<Number, Representation> segment;
    segment.setSet<Representation>( segmentSubspace0, 0 );
    segment.setSet<Representation>( segmentSubspace1, 1 );
    VPolytope<Number> reachableSet = VPolytope<Number>( composeSubspaces( segment, 0, 1, decomposition ) );

    VPolytope<Number> expectedReachableSet = VPolytope<Number>( std::vector<Point>{ 
        Point{ 5, 4 }, Point{ 5, 6 }, Point{ 5, 5 },
        Point{ timeHorizon, timeHorizon }, Point{ timeHorizon + 1, timeHorizon }, Point{ timeHorizon + 1, timeHorizon + 1 }, Point{ timeHorizon , timeHorizon + 1 } } );
    EXPECT_TRUE( expectedReachableSet.contains( reachableSet ) );
    EXPECT_TRUE( reachableSet.contains( expectedReachableSet ) );
}

TEST( DecompositionalAnalysisSingular, SingularJumps ) {
    using Number = mpq_class;
    using Matrix = matrix_t<Number>;
    using Vector = vector_t<Number>;
    using Representation = VPolytope<Number>;

    std::size_t jumpDepth = 100;
    tNumber timeHorizon = 50;
    tNumber timeStep = 0.1;

    auto ha = singularWithJumpsHa<Number>();

    // bad state: y <= -12 in l0 (unsafe with jumpDepth >= 3)
    Matrix badStateMat = Matrix::Zero( 1, 2 );
    Vector badStateVec = -12 * Vector::Ones( 1 );
    badStateMat( 0, 1 ) = 1;
    ha.addLocalBadState( ha.getLocation( "l0" ), Condition<Number>( badStateMat, badStateVec ) );
    auto [decomposedHa, decomposition] = decomposeAutomaton( ha );
    for ( std::size_t subspace = 0; subspace < decomposition.subspaceTypes.size(); ++subspace ) {
        if ( decomposition.subspaceTypes[ subspace ] != DynamicType::linear && decomposition.subspaceTypes[ subspace ] != DynamicType::affine ) {
            addClockToAutomaton( decomposedHa, subspace, 2 );
        }
    }
    std::vector<std::vector<ReachTreeNode<Representation>>> roots = makeDecompositionalRoots<Representation, Number>( decomposedHa, decomposition );
    DecompositionalAnalyzer<Representation> analyzer( decomposedHa, decomposition, FixedAnalysisParameters{4, 50, 0.1}, AnalysisParameters{ 0.1 }, roots );
    auto result = analyzer.run();
    EXPECT_EQ( REACHABILITY_RESULT::UNKNOWN, result.result() );
}

