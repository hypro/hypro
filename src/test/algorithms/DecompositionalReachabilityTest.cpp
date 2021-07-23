#include "gtest/gtest.h"
#include <hypro/datastructures/HybridAutomaton/decomposition/DecompositionMethods.h>
#include <hypro/algorithms/reachability/analyzer/DecompositionalAnalyzer.h>
#include "decompositionalReachabilityAutomata.h"


using namespace hypro;

TEST( DecompositionalUtil, ComposeSubspaces ) {
    using Number = mpq_class;
    using HPol = HPolytope<Number>;

    using Matrix = matrix_t<Number>;
    using Vector = vector_t<Number>;

    Matrix mat1 = Matrix::Zero( 6, 3 );
    Vector vec1 = Vector::Zero( 6 );
    // x_0 = [0,1]
    mat1( 0, 1 ) = -1;
    mat1( 1, 1 ) = 1;
    vec1( 1 ) = 1;
    // c = [0,1]
    mat1( 2, 2 ) = -1;
    mat1( 3, 2 ) = 1;
    vec1( 3 ) = 1;
    // x = x_0 + c
    mat1( 4, 0 ) = 1;
    mat1( 4, 1 ) = -1;
    mat1( 4, 2 ) = -1;
    mat1( 5, 0 ) = -1;
    mat1( 5, 1 ) = 1;
    mat1( 5, 2 ) = 1;

    HPol subspace1( mat1, vec1 );
    HPol subspace2( mat1, vec1 );
    // dependency: x_0 = y_0
    Matrix depMat = Matrix::Zero( 2, 2 );
    Vector depVec = Vector::Zero( 2 );
    depMat << 1, -1, -1, 1;
    auto composed = detail::composeSubspaces( std::vector<HPol>{ subspace1, subspace2 }, Condition( depMat, depVec ), Decomposition{ { { 0 }, { 1 } }, { DynamicType::timed, DynamicType::timed } }, 1 );

    Matrix expectedMat = Matrix::Zero( 4, 2 );
    Vector expectedVec = Vector::Zero( 4 );
    expectedMat << 1, 0,
        -1, 0,
        1, -1,
        -1, 1;
    expectedVec << 2, 0, 0, 0;
    HPol expected = HPol( expectedMat, expectedVec );
    EXPECT_TRUE( expected.contains( composed ) );
    EXPECT_TRUE( composed.contains( expected ) );
}

TEST( DecompositionalUtil, ComposeSubspacesDiscrete ) {
    using Number = mpq_class;
    using HPol = HPolytope<Number>;

    using Matrix = matrix_t<Number>;
    using Vector = vector_t<Number>;

    Matrix mat1 = Matrix::Zero( 6, 3 );
    Vector vec1 = Vector::Zero( 6 );
    // x_0 = [0,1]
    mat1( 0, 1 ) = -1;
    mat1( 1, 1 ) = 1;
    vec1( 1 ) = 1;
    // c = [0,1]
    mat1( 2, 2 ) = -1;
    mat1( 3, 2 ) = 1;
    vec1( 3 ) = 1;
    // x = x_0 + c
    mat1( 4, 0 ) = 1;
    mat1( 4, 1 ) = -1;
    mat1( 4, 2 ) = -1;
    mat1( 5, 0 ) = -1;
    mat1( 5, 1 ) = 1;
    mat1( 5, 2 ) = 1;

    Matrix mat2 = Matrix::Zero( 2, 1 );
    mat2 << 1, -1;
    Vector vec2 = Vector::Zero( 2 );
    vec2 << 1, 0;

    HPol subspace1( mat1, vec1 );
    HPol subspace2( mat1, vec1 );
    HPol subspace3( mat2, vec2 );
    // dependency: x_0 = y_0
    Matrix depMat = Matrix::Zero( 2, 3 );
    Vector depVec = Vector::Zero( 2 );
    depMat << 1, -1, 0, -1, 1, 0;
    auto composed = detail::composeSubspaces( std::vector<HPol>{ subspace1, subspace2, subspace3 }, Condition( depMat, depVec ), Decomposition{ { { 0 }, { 1 }, { 2 } }, { DynamicType::timed, DynamicType::timed, DynamicType::discrete } }, 1 );

    Matrix expectedMat = Matrix::Zero( 6, 3 );
    Vector expectedVec = Vector::Zero( 6 );
    expectedMat << 1, 0, 0,
        -1, 0, 0,
        1, -1, 0,
        -1, 1, 0,
        0, 0, 1,
        0, 0, -1;
    expectedVec << 2, 0, 0, 0, 1, 0;
    HPol expected = HPol( expectedMat, expectedVec );
    EXPECT_TRUE( expected.contains( composed ) );
    EXPECT_TRUE( composed.contains( expected ) );
}



TEST( DecompositionalAnalysisMixedDynamics, NoJumpsNoBadStates ) {
    using Number = double;
    using Representation = HPolytope<Number>;

    std::size_t jumpDepth = 4;
    tNumber timeHorizon = 5;
    tNumber timeStep = 0.1;
    std::size_t clocks = 2;

    auto ha = mixedDynamicsNoJumpsHa<Number>();
    auto [decomposedHa, decomposition] = decomposeAutomaton( ha );
    for ( std::size_t subspace = 0; subspace < decomposition.subspaceTypes.size(); ++subspace ) {
        addInitialVarToAutomaton( decomposedHa, subspace, decomposition.subspaces[ subspace ].size() );
        addClocksToAutomaton( decomposedHa, subspace, clocks );
    }
    DecompositionalAnalyzer<Representation> analyzer( decomposedHa, decomposition, clocks, FixedAnalysisParameters{jumpDepth, timeHorizon, timeStep}, AnalysisParameters{ timeStep } );
    auto result = analyzer.run();
    EXPECT_EQ( REACHABILITY_RESULT::SAFE, result.result() );
}

TEST( DecompositionalAnalysisMixedDynamics, NoJumpsSafe ) {
    using Number = double;
    using Matrix = matrix_t<Number>;
    using Vector = vector_t<Number>;
    using Representation = HPolytope<Number>;

    std::size_t jumpDepth = 4;
    tNumber timeHorizon = 5;
    tNumber timeStep = 0.5;
    std::size_t clocks = 2;

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
        addInitialVarToAutomaton( decomposedHa, subspace, decomposition.subspaces[ subspace ].size() );
        addClocksToAutomaton( decomposedHa, subspace, clocks );
    }
    DecompositionalAnalyzer<Representation> analyzer( decomposedHa, decomposition, clocks, FixedAnalysisParameters{jumpDepth, timeHorizon, timeStep}, AnalysisParameters{ timeStep } );
    auto result = analyzer.run();
    EXPECT_EQ( REACHABILITY_RESULT::SAFE, result.result() );
}

TEST( DecompositionalAnalysisMixedDynamics, NoJumpsUnsafe ) {
    using Number = double;
    using Matrix = matrix_t<Number>;
    using Vector = vector_t<Number>;
    using Representation = HPolytope<Number>;

    std::size_t jumpDepth = 4;
    tNumber timeHorizon = 5;
    tNumber timeStep = 0.1;
    std::size_t clocks = 2;

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
        addInitialVarToAutomaton( decomposedHa, subspace, decomposition.subspaces[ subspace ].size() );
        addClocksToAutomaton( decomposedHa, subspace, clocks );
    }
    DecompositionalAnalyzer<Representation> analyzer( decomposedHa, decomposition, clocks, FixedAnalysisParameters{jumpDepth, timeHorizon, timeStep}, AnalysisParameters{ timeStep } );
    auto result = analyzer.run();
    EXPECT_EQ( REACHABILITY_RESULT::UNKNOWN, result.result() );
}

TEST( DecompositionalAnalysisMixedDynamics, JumpsSafe ) {
    using Number = double;
    using Matrix = matrix_t<Number>;
    using Vector = vector_t<Number>;
    using Representation = HPolytope<Number>;

    std::size_t jumpDepth = 3;
    tNumber timeHorizon = 5;
    tNumber timeStep = 0.2;
    std::size_t clocks = 1;

    auto ha = mixedDynamicsWithJumpsHa<Number>();
    // bad state: x >= 3 and z in [1,2] in l1 (safe)
    Matrix badStateMat = Matrix::Zero( 3, 3 );
    badStateMat( 0, 0 ) = -1;
    badStateMat( 1, 2 ) = 1;
    badStateMat( 2, 2 ) = -1;
    Vector badStateVec = Vector::Zero( 3 );
    badStateVec << -3, 2, -1;
    ha.addLocalBadState( ha.getLocation( "l1" ), Condition<Number>( badStateMat, badStateVec ) );
    auto [decomposedHa, decomposition] = decomposeAutomaton( ha );
    ASSERT_EQ( (std::size_t) 2, decomposition.subspaces.size() );
    EXPECT_EQ( DynamicType::linear, decomposition.subspaceTypes[ 0 ] );
    EXPECT_EQ( DynamicType::timed, decomposition.subspaceTypes[ 1 ] );
    for ( std::size_t subspace = 0; subspace < decomposition.subspaceTypes.size(); ++subspace ) {
        addInitialVarToAutomaton( decomposedHa, subspace, decomposition.subspaces[ subspace ].size() );
        addClocksToAutomaton( decomposedHa, subspace, clocks );
    }
    DecompositionalAnalyzer<Representation> analyzer( decomposedHa, decomposition, clocks, FixedAnalysisParameters{jumpDepth, timeHorizon, timeStep}, AnalysisParameters{ timeStep } );
    auto result = analyzer.run();
    EXPECT_EQ( REACHABILITY_RESULT::SAFE, result.result() );
}

TEST( DecompositionalAnalysisMixedDynamics, JumpsUnsafe ) {
    using Number = double;
    using Matrix = matrix_t<Number>;
    using Vector = vector_t<Number>;
    using Representation = HPolytope<Number>;

    std::size_t jumpDepth = 3;
    tNumber timeHorizon = 5;
    tNumber timeStep = 0.2;
    std::size_t clocks = 1;

    auto ha = mixedDynamicsWithJumpsHa<Number>();
    // bad state: x >= 3 in l1 (unsafe)
    Matrix badStateMat = Matrix::Zero( 1, 3 );
    badStateMat( 0, 0 ) = -1;
    Vector badStateVec = Vector::Zero( 1 );
    badStateVec << -3;
    ha.addLocalBadState( ha.getLocation( "l1" ), Condition<Number>( badStateMat, badStateVec ) );

    auto [decomposedHa, decomposition] = decomposeAutomaton( ha );
    ASSERT_EQ( (std::size_t) 2, decomposition.subspaces.size() );
    EXPECT_EQ( DynamicType::linear, decomposition.subspaceTypes[ 0 ] );
    EXPECT_EQ( DynamicType::timed, decomposition.subspaceTypes[ 1 ] );
    for ( std::size_t subspace = 0; subspace < decomposition.subspaceTypes.size(); ++subspace ) {
        addInitialVarToAutomaton( decomposedHa, subspace, decomposition.subspaces[ subspace ].size() );
        addClocksToAutomaton( decomposedHa, subspace, clocks );
    }
    DecompositionalAnalyzer<Representation> analyzer( decomposedHa, decomposition, clocks, FixedAnalysisParameters{jumpDepth, timeHorizon, timeStep}, AnalysisParameters{ timeStep } );
    auto result = analyzer.run();
    EXPECT_EQ( REACHABILITY_RESULT::UNKNOWN, result.result() );
}





TEST( DecompositionalAnalysisSingular, TimeElapseNoInvariant ) {
    using Number = mpq_class;
    using Representation = HPolytope<Number>;
    //using Point = Point<Number>;

    std::size_t jumpDepth = 4;
    tNumber timeHorizon = 50;
    tNumber timeStep = 0.1;
    std::size_t clocks = 1;

    auto ha = singularNoJumpsNoInvHa<Number>();
    auto [decomposedHa, decomposition] = decomposeAutomaton( ha );
    for ( std::size_t subspace = 0; subspace < decomposition.subspaceTypes.size(); ++subspace ) {
        if ( decomposition.subspaceTypes[ subspace ] != DynamicType::linear && decomposition.subspaceTypes[ subspace ] != DynamicType::affine ) {
            addInitialVarToAutomaton( decomposedHa, subspace, decomposition.subspaces[ subspace ].size() );
            addClocksToAutomaton( decomposedHa, subspace, clocks );
        }
    }
    DecompositionalAnalyzer<Representation> analyzer( decomposedHa, decomposition, clocks, FixedAnalysisParameters{jumpDepth, timeHorizon, timeStep}, AnalysisParameters{ timeStep } );
    auto result = analyzer.run();

    EXPECT_EQ( REACHABILITY_RESULT::SAFE, result.result() );
//
//    // one initial set
//    EXPECT_EQ( 1, roots.size() );
//    // two subspaces
//    EXPECT_EQ( 2, roots[0].size() );
//    // no jumps
//    EXPECT_EQ( 0, roots[0][0].getChildren().size() );
//    EXPECT_EQ( 0, roots[0][1].getChildren().size() );    
//    // get time elapse segments
//    auto flowpipeSubspace0 = roots[0][0].getFlowpipe();
//    auto flowpipeSubspace1 = roots[0][1].getFlowpipe();
//    // singular flowpipes have exactly two segments, where the first is the initial set
//    EXPECT_EQ( 2, flowpipeSubspace0.size() );
//    EXPECT_EQ( 2, flowpipeSubspace1.size() );
//    auto segmentSubspace0 = flowpipeSubspace0[ 1 ];
//    auto segmentSubspace1 = flowpipeSubspace1[ 1 ];
//    // transform to vpolytope
//    State<Number, Representation> segment;
//    segment.setSet<Representation>( segmentSubspace0, 0 );
//    segment.setSet<Representation>( segmentSubspace1, 1 );
//    VPolytope<Number> reachableSet = VPolytope<Number>( composeSubspaces( segment, 0, 1, decomposition, jumpDepth ) );
//
//    VPolytope<Number> expectedReachableSet = VPolytope<Number>( std::vector<Point>{ 
//        Point{ 0, 0 }, Point{ 0, 1 }, Point{ 1, 0 }, Point{ 1, 1 },
//        Point{ 1 + timeHorizon, timeHorizon }, Point{ 1 + timeHorizon, 1 + timeHorizon }, Point{ timeHorizon, 1 + timeHorizon } } );
//    EXPECT_TRUE( expectedReachableSet.contains( reachableSet ) );
//    EXPECT_TRUE( reachableSet.contains( expectedReachableSet ) );
}

TEST( DecompositionalAnalysisSingular, TimeElapseNoInvariantSafetyCheck1 ) {
    using Number = mpq_class;
    using Matrix = matrix_t<Number>;
    using Vector = vector_t<Number>;
    using Representation = HPolytope<Number>;

    std::size_t jumpDepth = 4;
    tNumber timeHorizon = 50;
    tNumber timeStep = 0.1;
    std::size_t clocks = 1;

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
            addInitialVarToAutomaton( decomposedHa, subspace, decomposition.subspaces[ subspace ].size() );
            addClocksToAutomaton( decomposedHa, subspace, clocks );
        }
    }
    DecompositionalAnalyzer<Representation> analyzer( decomposedHa, decomposition, clocks, FixedAnalysisParameters{jumpDepth, timeHorizon, timeStep}, AnalysisParameters{ timeStep } );
    auto result = analyzer.run();
    EXPECT_EQ( REACHABILITY_RESULT::SAFE, result.result() );
}

TEST( DecompositionalAnalysisSingular, TimeElapseNoInvariantSafetyCheck2 ) {
    using Number = mpq_class;
    using Matrix = matrix_t<Number>;
    using Vector = vector_t<Number>;
    using Representation = HPolytope<Number>;

    std::size_t jumpDepth = 4;
    tNumber timeHorizon = 50;
    tNumber timeStep = 0.1;
    std::size_t clocks = 1;

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
            addInitialVarToAutomaton( decomposedHa, subspace, decomposition.subspaces[ subspace ].size() );
            addClocksToAutomaton( decomposedHa, subspace, clocks );
        }
    }
    DecompositionalAnalyzer<Representation> analyzer( decomposedHa, decomposition, clocks, FixedAnalysisParameters{jumpDepth, timeHorizon, timeStep}, AnalysisParameters{ timeStep } );
    auto result = analyzer.run();
    EXPECT_EQ( REACHABILITY_RESULT::UNKNOWN, result.result() );
}

TEST( DecompositionalAnalysisSingular, TimeElapseWithInv1 ) {
    using Number = mpq_class;
    using Matrix = matrix_t<Number>;
    using Vector = vector_t<Number>;
    using Representation = HPolytope<Number>;
    //using Point = Point<Number>;

    std::size_t jumpDepth = 4;
    tNumber timeHorizon = 50;
    tNumber timeStep = 0.1;
    std::size_t clocks = 1;

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
            addInitialVarToAutomaton( decomposedHa, subspace, decomposition.subspaces[ subspace ].size() );
            addClocksToAutomaton( decomposedHa, subspace, clocks );
        }
    }
    DecompositionalAnalyzer<Representation> analyzer( decomposedHa, decomposition, clocks, FixedAnalysisParameters{jumpDepth, timeHorizon, timeStep}, AnalysisParameters{ timeStep } );
    auto result = analyzer.run();

    EXPECT_EQ( REACHABILITY_RESULT::SAFE, result.result() );

//    // one initial set
//    EXPECT_EQ( 1, roots.size() );
//    // two subspaces
//    EXPECT_EQ( 2, roots[0].size() );
//    // no jumps
//    EXPECT_EQ( 0, roots[0][0].getChildren().size() );
//    EXPECT_EQ( 0, roots[0][1].getChildren().size() );    
//    // get time elapse segments
//    auto flowpipeSubspace0 = roots[0][0].getFlowpipe();
//    auto flowpipeSubspace1 = roots[0][1].getFlowpipe();
//    // singular flowpipes have exactly two segments, where the first is the initial set
//    EXPECT_EQ( 2, flowpipeSubspace0.size() );
//    EXPECT_EQ( 2, flowpipeSubspace1.size() );
//    auto segmentSubspace0 = flowpipeSubspace0[ 1 ];
//    auto segmentSubspace1 = flowpipeSubspace1[ 1 ];
//    // transform to vpolytope
//    State<Number, Representation> segment;
//    segment.setSet<Representation>( segmentSubspace0, 0 );
//    segment.setSet<Representation>( segmentSubspace1, 1 );
//    VPolytope<Number> reachableSet = VPolytope<Number>( composeSubspaces( segment, 0, 1, decomposition, jumpDepth ) );
//
//    VPolytope<Number> expectedReachableSet = VPolytope<Number>( std::vector<Point>{ 
//        Point{ 0, 0 }, Point{ 0, 1 }, Point{ 1, 0 }, Point{ 1, 1 },
//        Point{ 5, 4 }, Point{ 5, 5 }, Point{ 5, 6 }, Point{ 4, 5 } } );
//    EXPECT_TRUE( expectedReachableSet.contains( reachableSet ) );
//    EXPECT_TRUE( reachableSet.contains( expectedReachableSet ) );
}


TEST( DecompositionalAnalysisSingular, TimeElapseWithInv2 ) {
    using Number = mpq_class;
    using Representation = HPolytope<Number>;
    //using Point = Point<Number>;

    std::size_t jumpDepth = 4;
    tNumber timeHorizon = 50;
    tNumber timeStep = 0.1;
    std::size_t clocks = 1;

    auto ha = singularNoJumpsWithInvHa2<Number>();
    auto [decomposedHa, decomposition] = decomposeAutomaton( ha );
    for ( std::size_t subspace = 0; subspace < decomposition.subspaceTypes.size(); ++subspace ) {
        if ( decomposition.subspaceTypes[ subspace ] != DynamicType::linear && decomposition.subspaceTypes[ subspace ] != DynamicType::affine ) {
            addInitialVarToAutomaton( decomposedHa, subspace, decomposition.subspaces[ subspace ].size() );
            addClocksToAutomaton( decomposedHa, subspace, clocks );
        }
    }
    DecompositionalAnalyzer<Representation> analyzer( decomposedHa, decomposition, clocks, FixedAnalysisParameters{jumpDepth, timeHorizon, timeStep}, AnalysisParameters{ timeStep } );
    auto result = analyzer.run();

    EXPECT_EQ( REACHABILITY_RESULT::SAFE, result.result() );

//    // one initial set
//    EXPECT_EQ( 1, roots.size() );
//    // two subspaces
//    EXPECT_EQ( 2, roots[0].size() );
//    // no jumps
//    EXPECT_EQ( 0, roots[0][0].getChildren().size() );
//    EXPECT_EQ( 0, roots[0][1].getChildren().size() );    
//    // get time elapse segments
//    auto flowpipeSubspace0 = roots[0][0].getFlowpipe();
//    auto flowpipeSubspace1 = roots[0][1].getFlowpipe();
//    // singular flowpipes have exactly two segments, where the first is the initial set
//    EXPECT_EQ( 2, flowpipeSubspace0.size() );
//    EXPECT_EQ( 2, flowpipeSubspace1.size() );
//    auto segmentSubspace0 = flowpipeSubspace0[ 1 ];
//    auto segmentSubspace1 = flowpipeSubspace1[ 1 ];
//    // transform to vpolytope
//    State<Number, Representation> segment;
//    segment.setSet<Representation>( segmentSubspace0, 0 );
//    segment.setSet<Representation>( segmentSubspace1, 1 );
//    VPolytope<Number> reachableSet = VPolytope<Number>( composeSubspaces( segment, 0, 1, decomposition, jumpDepth ) );
//
//    VPolytope<Number> expectedReachableSet = VPolytope<Number>( std::vector<Point>{ 
//        Point{ 0, 0 }, Point{ 0, 1 }, Point{ 1, 0 }, Point{ 1, 1 },
//        Point{ 5, 4 }, Point{ 5, 5 }, Point{ 5, 6 }, Point{ 4, 5 } } );
//    EXPECT_TRUE( expectedReachableSet.contains( reachableSet ) );
//    EXPECT_TRUE( reachableSet.contains( expectedReachableSet ) );
}

TEST( DecompositionalAnalysisSingular, JumpSuccessors1 ) {
    using Number = mpq_class;
    using Representation = HPolytope<Number>;
    //using Point = Point<Number>;

    std::size_t jumpDepth = 4;
    tNumber timeHorizon = 50;
    tNumber timeStep = 0.1;
    std::size_t clocks = 1;

    auto ha = singularJumpSuccessorsHa1<Number>();
    auto [decomposedHa, decomposition] = decomposeAutomaton( ha );
    for ( std::size_t subspace = 0; subspace < decomposition.subspaceTypes.size(); ++subspace ) {
        if ( decomposition.subspaceTypes[ subspace ] != DynamicType::linear && decomposition.subspaceTypes[ subspace ] != DynamicType::affine ) {
            addInitialVarToAutomaton( decomposedHa, subspace, decomposition.subspaces[ subspace ].size() );
            addClocksToAutomaton( decomposedHa, subspace, clocks );
        }
    }
    DecompositionalAnalyzer<Representation> analyzer( decomposedHa, decomposition, clocks, FixedAnalysisParameters{jumpDepth, timeHorizon, timeStep}, AnalysisParameters{ timeStep } );
    auto result = analyzer.run();

    EXPECT_EQ( REACHABILITY_RESULT::SAFE, result.result() );

    // one initial set
//    EXPECT_EQ( 1, roots.size() );
//    // two subspaces
//    EXPECT_EQ( 2, roots[0].size() );
//    // one jump
//    EXPECT_EQ( 1, roots[0][0].getChildren().size() );
//    EXPECT_EQ( 1, roots[0][1].getChildren().size() );    
//    // get successor segments
//    auto flowpipeSubspace0 = roots[0][0].getChildren()[0]->getFlowpipe();
//    auto flowpipeSubspace1 = roots[0][1].getChildren()[0]->getFlowpipe();
//    // singular flowpipes have exactly two segments, where the first is the initial set
//    EXPECT_EQ( 2, flowpipeSubspace0.size() );
//    EXPECT_EQ( 2, flowpipeSubspace1.size() );
//    auto segmentSubspace0 = flowpipeSubspace0[ 1 ];
//    auto segmentSubspace1 = flowpipeSubspace1[ 1 ];
//    // transform to vpolytope
//    State<Number, Representation> segment;
//    segment.setSet<Representation>( segmentSubspace0, 0 );
//    segment.setSet<Representation>( segmentSubspace1, 1 );
//    VPolytope<Number> reachableSet = VPolytope<Number>( composeSubspaces( segment, 0, 1, decomposition, jumpDepth ) );
//
//    VPolytope<Number> expectedReachableSet = VPolytope<Number>( std::vector<Point>{ 
//        Point{ 5, 4 }, Point{ 5, 6 }, Point{ 5, 5 },
//        Point{ timeHorizon, timeHorizon }, Point{ timeHorizon + 1, timeHorizon }, Point{ timeHorizon + 1, timeHorizon + 1 }, Point{ timeHorizon , timeHorizon + 1 } } );
//    EXPECT_TRUE( expectedReachableSet.contains( reachableSet ) );
//    EXPECT_TRUE( reachableSet.contains( expectedReachableSet ) );
}

TEST( DecompositionalAnalysisSingular, JumpSuccessors2 ) {
    using Number = mpq_class;
    using Representation = HPolytope<Number>;
    //using Point = Point<Number>;

    std::size_t jumpDepth = 4;
    tNumber timeHorizon = 50;
    tNumber timeStep = 0.1;
    std::size_t clocks = 1;

    auto ha = singularJumpSuccessorsHa2<Number>();
    auto [decomposedHa, decomposition] = decomposeAutomaton( ha );
    for ( std::size_t subspace = 0; subspace < decomposition.subspaceTypes.size(); ++subspace ) {
        if ( decomposition.subspaceTypes[ subspace ] != DynamicType::linear && decomposition.subspaceTypes[ subspace ] != DynamicType::affine ) {
            addInitialVarToAutomaton( decomposedHa, subspace,  );
            addClocksToAutomaton( decomposedHa, subspace, clocks );
        }
    }
    DecompositionalAnalyzer<Representation> analyzer( decomposedHa, decomposition, clocks, FixedAnalysisParameters{jumpDepth, timeHorizon, timeStep}, AnalysisParameters{ timeStep } );
    auto result = analyzer.run();

    EXPECT_EQ( REACHABILITY_RESULT::SAFE, result.result() );

    // one initial set
//    EXPECT_EQ( 1, roots.size() );
//    // two subspaces
//    EXPECT_EQ( 2, roots[0].size() );
//    // one jump
//    EXPECT_EQ( 1, roots[0][0].getChildren().size() );
//    EXPECT_EQ( 1, roots[0][1].getChildren().size() );    
//    // get successor segments
//    auto flowpipeSubspace0 = roots[0][0].getChildren()[0]->getFlowpipe();
//    auto flowpipeSubspace1 = roots[0][1].getChildren()[0]->getFlowpipe();
//    // singular flowpipes have exactly two segments, where the first is the initial set
//    EXPECT_EQ( 2, flowpipeSubspace0.size() );
//    EXPECT_EQ( 2, flowpipeSubspace1.size() );
//    auto segmentSubspace0 = flowpipeSubspace0[ 1 ];
//    auto segmentSubspace1 = flowpipeSubspace1[ 1 ];
//    // transform to vpolytope
//    State<Number, Representation> segment;
//    segment.setSet<Representation>( segmentSubspace0, 0 );
//    segment.setSet<Representation>( segmentSubspace1, 1 );
//    VPolytope<Number> reachableSet = VPolytope<Number>( composeSubspaces( segment, 0, 1, decomposition, jumpDepth ) );
//
//    VPolytope<Number> expectedReachableSet = VPolytope<Number>( std::vector<Point>{ 
//        Point{ 5, 4 }, Point{ 5, 6 }, Point{ 5, 5 },
//        Point{ 9, 10 }, Point{ 11, 10 }, Point{ 10, 9 } } );
//    EXPECT_TRUE( expectedReachableSet.contains( reachableSet ) );
//    EXPECT_TRUE( reachableSet.contains( expectedReachableSet ) );
}

TEST( DecompositionalAnalysisSingular, JumpSuccessors3 ) {
    using Number = mpq_class;
    using Representation = HPolytope<Number>;
    //using Point = Point<Number>;

    std::size_t jumpDepth = 4;
    tNumber timeHorizon = 50;
    tNumber timeStep = 0.1;
    std::size_t clocks = 1;

    auto ha = singularJumpSuccessorsHa3<Number>();
    auto [decomposedHa, decomposition] = decomposeAutomaton( ha );
    for ( std::size_t subspace = 0; subspace < decomposition.subspaceTypes.size(); ++subspace ) {
        if ( decomposition.subspaceTypes[ subspace ] != DynamicType::linear && decomposition.subspaceTypes[ subspace ] != DynamicType::affine ) {
            addInitialVarToAutomaton( decomposedHa, subspace, decomposition.subspaces[ subspace ].size() );
            addClocksToAutomaton( decomposedHa, subspace, clocks );
        }
    }
    DecompositionalAnalyzer<Representation> analyzer( decomposedHa, decomposition, clocks, FixedAnalysisParameters{jumpDepth, timeHorizon, timeStep}, AnalysisParameters{ timeStep } );
    auto result = analyzer.run();

    EXPECT_EQ( REACHABILITY_RESULT::SAFE, result.result() );

//    // one initial set
//    EXPECT_EQ( 1, roots.size() );
//    // two subspaces
//    EXPECT_EQ( 2, roots[0].size() );
//    // one jump
//    EXPECT_EQ( 1, roots[0][0].getChildren().size() );
//    EXPECT_EQ( 1, roots[0][1].getChildren().size() );    
//    // get successor segments
//    auto flowpipeSubspace0 = roots[0][0].getChildren()[0]->getFlowpipe();
//    auto flowpipeSubspace1 = roots[0][1].getChildren()[0]->getFlowpipe();
//    // singular flowpipes have exactly two segments, where the first is the initial set
//    EXPECT_EQ( 2, flowpipeSubspace0.size() );
//    EXPECT_EQ( 2, flowpipeSubspace1.size() );
//    auto segmentSubspace0 = flowpipeSubspace0[ 1 ];
//    auto segmentSubspace1 = flowpipeSubspace1[ 1 ];
//    // transform to vpolytope
//    State<Number, Representation> segment;
//    segment.setSet<Representation>( segmentSubspace0, 0 );
//    segment.setSet<Representation>( segmentSubspace1, 1 );
//    VPolytope<Number> reachableSet = VPolytope<Number>( composeSubspaces( segment, 0, 1, decomposition, jumpDepth ) );
//
//    VPolytope<Number> expectedReachableSet = VPolytope<Number>( std::vector<Point>{ 
//        Point{ 0, 0 }, Point{ 0, 1 }, Point{ 1, 0 },
//        Point{ timeHorizon + 1, timeHorizon + 1 }, Point{ timeHorizon, timeHorizon + 1 }, Point{ timeHorizon + 1, timeHorizon } } );
//    EXPECT_TRUE( expectedReachableSet.contains( reachableSet ) );
//    EXPECT_TRUE( reachableSet.contains( expectedReachableSet ) );
}

TEST( DecompositionalAnalysisSingular, JumpSuccessors4 ) {
    using Number = mpq_class;
    using Representation = HPolytope<Number>;
    //using Point = Point<Number>;

    std::size_t jumpDepth = 4;
    tNumber timeHorizon = 50;
    tNumber timeStep = 0.1;
    std::size_t clocks = 1;

    auto ha = singularJumpSuccessorsHa4<Number>();
    auto [decomposedHa, decomposition] = decomposeAutomaton( ha );
    for ( std::size_t subspace = 0; subspace < decomposition.subspaceTypes.size(); ++subspace ) {
        if ( decomposition.subspaceTypes[ subspace ] != DynamicType::linear && decomposition.subspaceTypes[ subspace ] != DynamicType::affine ) {
            addInitialVarToAutomaton( decomposedHa, subspace, decomposition.subspaces[ subspace ].size() );
            addClocksToAutomaton( decomposedHa, subspace, clocks );
        }
    }
    DecompositionalAnalyzer<Representation> analyzer( decomposedHa, decomposition, clocks, FixedAnalysisParameters{jumpDepth, timeHorizon, timeStep}, AnalysisParameters{ timeStep } );
    auto result = analyzer.run();

    EXPECT_EQ( REACHABILITY_RESULT::SAFE, result.result() );

    // one initial set
//    EXPECT_EQ( 1, roots.size() );
//    // two subspaces
//    EXPECT_EQ( 2, roots[0].size() );
//    // one jump
//    EXPECT_EQ( 1, roots[0][0].getChildren().size() );
//    EXPECT_EQ( 1, roots[0][1].getChildren().size() );    
//    // get successor segments
//    auto flowpipeSubspace0 = roots[0][0].getChildren()[0]->getFlowpipe();
//    auto flowpipeSubspace1 = roots[0][1].getChildren()[0]->getFlowpipe();
//    // singular flowpipes have exactly two segments, where the first is the initial set
//    EXPECT_EQ( 2, flowpipeSubspace0.size() );
//    EXPECT_EQ( 2, flowpipeSubspace1.size() );
//    auto segmentSubspace0 = flowpipeSubspace0[ 1 ];
//    auto segmentSubspace1 = flowpipeSubspace1[ 1 ];
//    // transform to vpolytope
//    State<Number, Representation> segment;
//    segment.setSet<Representation>( segmentSubspace0, 0 );
//    segment.setSet<Representation>( segmentSubspace1, 1 );
//    VPolytope<Number> reachableSet = VPolytope<Number>( composeSubspaces( segment, 0, 1, decomposition, jumpDepth ) );
//
//    VPolytope<Number> expectedReachableSet = VPolytope<Number>( std::vector<Point>{ 
//        Point{ 5, 5 } } );
//    EXPECT_TRUE( expectedReachableSet.contains( reachableSet ) );
//    EXPECT_TRUE( reachableSet.contains( expectedReachableSet ) );
}

TEST( DecompositionalAnalysisSingular, Resets1 ) {
    using Number = mpq_class;
    using Representation = HPolytope<Number>;
    //using Point = Point<Number>;

    std::size_t jumpDepth = 4;
    tNumber timeHorizon = 50;
    tNumber timeStep = 0.1;
    std::size_t clocks = 1;

    auto ha = singularResetsHa1<Number>();
    auto [decomposedHa, decomposition] = decomposeAutomaton( ha );
    for ( std::size_t subspace = 0; subspace < decomposition.subspaceTypes.size(); ++subspace ) {
        if ( decomposition.subspaceTypes[ subspace ] != DynamicType::linear && decomposition.subspaceTypes[ subspace ] != DynamicType::affine ) {
            addInitialVarToAutomaton( decomposedHa, subspace, decomposition.subspaces[ subspace ].size() );
            addClocksToAutomaton( decomposedHa, subspace, clocks );
        }
    }
    DecompositionalAnalyzer<Representation> analyzer( decomposedHa, decomposition, clocks, FixedAnalysisParameters{jumpDepth, timeHorizon, timeStep}, AnalysisParameters{ timeStep } );
    auto result = analyzer.run();

    EXPECT_EQ( REACHABILITY_RESULT::SAFE, result.result() );

    // one initial set
//    EXPECT_EQ( 1, roots.size() );
//    // two subspaces
//    EXPECT_EQ( 2, roots[0].size() );
//    // one jump
//    EXPECT_EQ( 1, roots[0][0].getChildren().size() );
//    EXPECT_EQ( 1, roots[0][1].getChildren().size() );    
//    // get successor segments
//    auto flowpipeSubspace0 = roots[0][0].getChildren()[0]->getFlowpipe();
//    auto flowpipeSubspace1 = roots[0][1].getChildren()[0]->getFlowpipe();
//    // singular flowpipes have exactly two segments, where the first is the initial set (jump successors)
//    EXPECT_EQ( 2, flowpipeSubspace0.size() );
//    EXPECT_EQ( 2, flowpipeSubspace1.size() );
//    auto successorsSubspace0 = flowpipeSubspace0[ 0 ];
//    auto successorsSubspace1 = flowpipeSubspace1[ 0 ];
//    auto segmentSubspace0 = flowpipeSubspace0[ 1 ];
//    auto segmentSubspace1 = flowpipeSubspace1[ 1 ];
//    // transform to vpolytopes
//    State<Number, Representation> successors;
//    successors.setSet<Representation>( successorsSubspace0, 0 );
//    successors.setSet<Representation>( successorsSubspace1, 1 );
//    VPolytope<Number> successorSet = VPolytope<Number>( composeSubspaces( successors, 0, 1, decomposition, jumpDepth ) );
//
//    State<Number, Representation> segment;
//    segment.setSet<Representation>( segmentSubspace0, 0 );
//    segment.setSet<Representation>( segmentSubspace1, 1 );
//    VPolytope<Number> reachableSet = VPolytope<Number>( composeSubspaces( segment, 0, 1, decomposition, jumpDepth ) );
//
//    VPolytope<Number> expectedSuccessorSet = VPolytope<Number>( std::vector<Point>{
//        Point{ -1, 4 }, Point{ -1, 10 }, Point{ 0, 4 }, Point{ 0, 10 }
//    } );
//    EXPECT_TRUE( expectedSuccessorSet.contains( successorSet ) );
//    EXPECT_TRUE( successorSet.contains( expectedSuccessorSet ) );
//
//    VPolytope<Number> expectedReachableSet = VPolytope<Number>( std::vector<Point>{ 
//        Point{ -1, 4 }, Point{ -1, 10 }, Point{ 0, 4 }, Point{ 0, 10 },
//        Point{ -5, -1 }, Point{ -5, 6 } } );
//    EXPECT_TRUE( expectedReachableSet.contains( reachableSet ) );
//    EXPECT_TRUE( reachableSet.contains( expectedReachableSet ) );
}

TEST( DecompositionalAnalysisSingular, Resets2 ) {
    using Number = mpq_class;
    using Representation = HPolytope<Number>;
    //using Point = Point<Number>;

    std::size_t jumpDepth = 4;
    tNumber timeHorizon = 50;
    tNumber timeStep = 0.1;
    std::size_t clocks = 1;

    auto ha = singularResetsHa2<Number>();
    auto [decomposedHa, decomposition] = decomposeAutomaton( ha );
    for ( std::size_t subspace = 0; subspace < decomposition.subspaceTypes.size(); ++subspace ) {
        if ( decomposition.subspaceTypes[ subspace ] != DynamicType::linear && decomposition.subspaceTypes[ subspace ] != DynamicType::affine ) {
            addInitialVarToAutomaton( decomposedHa, subspace, decomposition.subspaces[ subspace ].size() );
            addClocksToAutomaton( decomposedHa, subspace, clocks );
        }
    }
    DecompositionalAnalyzer<Representation> analyzer( decomposedHa, decomposition, clocks, FixedAnalysisParameters{jumpDepth, timeHorizon, timeStep}, AnalysisParameters{ timeStep } );
    auto result = analyzer.run();

    EXPECT_EQ( REACHABILITY_RESULT::SAFE, result.result() );

    // one initial set
//    EXPECT_EQ( 1, roots.size() );
//    // two subspaces
//    EXPECT_EQ( 2, roots[0].size() );
//    // one jump
//    EXPECT_EQ( 1, roots[0][0].getChildren().size() );
//    EXPECT_EQ( 1, roots[0][1].getChildren().size() );    
//    // get successor segments
//    auto flowpipeSubspace0 = roots[0][0].getChildren()[0]->getFlowpipe();
//    auto flowpipeSubspace1 = roots[0][1].getChildren()[0]->getFlowpipe();
//    // singular flowpipes have exactly two segments, where the first is the initial set (jump successors)
//    EXPECT_EQ( 2, flowpipeSubspace0.size() );
//    EXPECT_EQ( 2, flowpipeSubspace1.size() );
//    auto successorsSubspace0 = flowpipeSubspace0[ 0 ];
//    auto successorsSubspace1 = flowpipeSubspace1[ 0 ];
//    auto segmentSubspace0 = flowpipeSubspace0[ 1 ];
//    auto segmentSubspace1 = flowpipeSubspace1[ 1 ];
//    // transform to vpolytopes
//    State<Number, Representation> successors;
//    successors.setSet<Representation>( successorsSubspace0, 0 );
//    successors.setSet<Representation>( successorsSubspace1, 1 );
//    VPolytope<Number> successorSet = VPolytope<Number>( composeSubspaces( successors, 0, 1, decomposition, jumpDepth ) );
//
//    State<Number, Representation> segment;
//    segment.setSet<Representation>( segmentSubspace0, 0 );
//    segment.setSet<Representation>( segmentSubspace1, 1 );
//    VPolytope<Number> reachableSet = VPolytope<Number>( composeSubspaces( segment, 0, 1, decomposition, jumpDepth ) );
//
//    VPolytope<Number> expectedSuccessorSet = VPolytope<Number>( std::vector<Point>{
//        Point{ 0, 0 },
//    } );
//    EXPECT_TRUE( expectedSuccessorSet.contains( successorSet ) );
//    EXPECT_TRUE( successorSet.contains( expectedSuccessorSet ) );
//
//    VPolytope<Number> expectedReachableSet = VPolytope<Number>( std::vector<Point>{ 
//        Point{ 0, 0 }, Point{ -1 * timeHorizon, -1 * timeHorizon } } );
//    EXPECT_TRUE( expectedReachableSet.contains( reachableSet ) );
//    EXPECT_TRUE( reachableSet.contains( expectedReachableSet ) );
}


TEST( DecompositionalAnalysisSingular, SingularJumps ) {
    using Number = mpq_class;
    using Matrix = matrix_t<Number>;
    using Vector = vector_t<Number>;
    using Representation = HPolytope<Number>;

    std::size_t jumpDepth = 4;
    tNumber timeHorizon = 50;
    tNumber timeStep = 0.1;
    std::size_t clocks = 1;

    auto ha = singularWithJumpsHa<Number>();
    // bad state: y <= -12 in l0 (unsafe with jumpDepth >= 3)
    Matrix badStateMat = Matrix::Zero( 1, 2 );
    Vector badStateVec = -12 * Vector::Ones( 1 );
    badStateMat( 0, 1 ) = 1;
    ha.addLocalBadState( ha.getLocation( "l0" ), Condition<Number>( badStateMat, badStateVec ) );
    auto [decomposedHa, decomposition] = decomposeAutomaton( ha );
    for ( std::size_t subspace = 0; subspace < decomposition.subspaceTypes.size(); ++subspace ) {
        if ( decomposition.subspaceTypes[ subspace ] != DynamicType::linear && decomposition.subspaceTypes[ subspace ] != DynamicType::affine ) {
            addInitialVarToAutomaton( decomposedHa, subspace, decomposition.subspaces[ subspace ].size() );
            addClocksToAutomaton( decomposedHa, subspace, clocks );
        }
    }
    DecompositionalAnalyzer<Representation> analyzer( decomposedHa, decomposition, clocks, FixedAnalysisParameters{jumpDepth, timeHorizon, timeStep}, AnalysisParameters{ timeStep } );
    auto result = analyzer.run();
    EXPECT_EQ( REACHABILITY_RESULT::UNKNOWN, result.result() );
}

TEST( DecompositionalAnalysisSingular, SingularJumps2 ) {
    using Number = mpq_class;
    using Representation = HPolytope<Number>;
    //using Point = Point<Number>;

    std::size_t jumpDepth = 1;
    tNumber timeHorizon = 50;
    tNumber timeStep = 0.1;
    std::size_t clocks = 1;

    auto ha = singularSingleJumpHa<Number>();
    auto [decomposedHa, decomposition] = decomposeAutomaton( ha );
    for ( std::size_t subspace = 0; subspace < decomposition.subspaceTypes.size(); ++subspace ) {
        if ( decomposition.subspaceTypes[ subspace ] != DynamicType::linear && decomposition.subspaceTypes[ subspace ] != DynamicType::affine ) {
            addInitialVarToAutomaton( decomposedHa, subspace, decomposition.subspaces[ subspace ].size() );
            addClocksToAutomaton( decomposedHa, subspace, clocks );
        }
    }
    DecompositionalAnalyzer<Representation> analyzer( decomposedHa, decomposition, clocks, FixedAnalysisParameters{jumpDepth, timeHorizon, timeStep}, AnalysisParameters{ timeStep } );
    auto result = analyzer.run();
    EXPECT_EQ( REACHABILITY_RESULT::SAFE, result.result() );

//    // one initial set
//    EXPECT_EQ( 1, roots.size() );
//    // two subspaces
//    EXPECT_EQ( 2, roots[0].size() );
//    // one jump
//    EXPECT_EQ( 1, roots[0][0].getChildren().size() );
//    EXPECT_EQ( 1, roots[0][1].getChildren().size() );    
//    // get successor segments
//    auto flowpipeSubspace0 = roots[0][0].getChildren()[0]->getFlowpipe();
//    auto flowpipeSubspace1 = roots[0][1].getChildren()[0]->getFlowpipe();
//    // singular flowpipes have exactly two segments, where the first is the initial set (jump successors)
//    EXPECT_EQ( 2, flowpipeSubspace0.size() );
//    EXPECT_EQ( 2, flowpipeSubspace1.size() );
//    auto successorsSubspace0 = flowpipeSubspace0[ 0 ];
//    auto successorsSubspace1 = flowpipeSubspace1[ 0 ];
//    auto segmentSubspace0 = flowpipeSubspace0[ 1 ];
//    auto segmentSubspace1 = flowpipeSubspace1[ 1 ];
//    // transform to vpolytopes
//    State<Number, Representation> successors;
//    successors.setSet<Representation>( successorsSubspace0, 0 );
//    successors.setSet<Representation>( successorsSubspace1, 1 );
//    VPolytope<Number> successorSet = VPolytope<Number>( composeSubspaces( successors, 0, 1, decomposition, jumpDepth + 1 ) );
//
//    State<Number, Representation> segment;
//    segment.setSet<Representation>( segmentSubspace0, 0 );
//    segment.setSet<Representation>( segmentSubspace1, 1 );
//    VPolytope<Number> reachableSet = VPolytope<Number>( composeSubspaces( segment, 0, 1, decomposition, jumpDepth + 1 ) );
//
//    VPolytope<Number> expectedSuccessorSet = VPolytope<Number>( std::vector<Point>{
//        Point{ 0, 0 }, Point{ timeHorizon, timeHorizon }
//    } );
//    EXPECT_TRUE( expectedSuccessorSet.contains( successorSet ) );
//    EXPECT_TRUE( successorSet.contains( expectedSuccessorSet ) );
//
//    VPolytope<Number> expectedReachableSet = VPolytope<Number>( std::vector<Point>{ 
//        Point{ 0, 0 }, Point{ timeHorizon, timeHorizon } } );
//    EXPECT_TRUE( expectedReachableSet.contains( reachableSet ) );
//    EXPECT_TRUE( reachableSet.contains( expectedReachableSet ) );
}

TEST( DecompositionalAnalysisSingular, SingularJumps3 ) {
    using Number = mpq_class;
    using Representation = HPolytope<Number>;
    //using Point = Point<Number>;

    std::size_t jumpDepth = 1;
    tNumber timeHorizon = 50;
    tNumber timeStep = 0.1;
    std::size_t clocks = 2;

    auto ha = singularSingleJumpHa<Number>();
    auto [decomposedHa, decomposition] = decomposeAutomaton( ha );
    for ( std::size_t subspace = 0; subspace < decomposition.subspaceTypes.size(); ++subspace ) {
        if ( decomposition.subspaceTypes[ subspace ] != DynamicType::linear && decomposition.subspaceTypes[ subspace ] != DynamicType::affine ) {
            addInitialVarToAutomaton( decomposedHa, subspace, decomposition.subspaces[ subspace ].size() );
            addClocksToAutomaton( decomposedHa, subspace, clocks );
        }
    }
    DecompositionalAnalyzer<Representation> analyzer( decomposedHa, decomposition, clocks, FixedAnalysisParameters{jumpDepth, timeHorizon, timeStep}, AnalysisParameters{ timeStep } );
    auto result = analyzer.run();
    EXPECT_EQ( REACHABILITY_RESULT::SAFE, result.result() );
}

TEST( DecompositionalAnalysisSingular, SingularJumps4 ) {
    using Number = mpq_class;
    using Representation = HPolytope<Number>;
    //using Point = Point<Number>;
    using Matrix = matrix_t<Number>;
    using Vector = vector_t<Number>;

    std::size_t jumpDepth = 4;
    tNumber timeHorizon = 2;
    tNumber timeStep = 0.1;
    std::size_t clocks = 3;

    auto ha = singularSingleJumpHa2<Number>();
    // bad state: y <= -1 x <= 0 in l1
    Matrix badStateMat = Matrix::Zero( 2, 2 );
    Vector badStateVec = Vector::Zero( 2 );
    badStateMat( 0, 1 ) = 1;
    badStateMat( 1, 0 ) = 1;
    badStateVec << -1, 0;
    ha.addLocalBadState( ha.getLocation( "l1" ), Condition<Number>( badStateMat, badStateVec ) );
    auto [decomposedHa, decomposition] = decomposeAutomaton( ha );
    for ( std::size_t subspace = 0; subspace < decomposition.subspaceTypes.size(); ++subspace ) {
        if ( decomposition.subspaceTypes[ subspace ] != DynamicType::linear && decomposition.subspaceTypes[ subspace ] != DynamicType::affine ) {
            addInitialVarToAutomaton( decomposedHa, subspace, decomposition.subspaces[ subspace ].size() );
            addClocksToAutomaton( decomposedHa, subspace, clocks );
        }
    }
    DecompositionalAnalyzer<Representation> analyzer( decomposedHa, decomposition, clocks, FixedAnalysisParameters{jumpDepth, timeHorizon, timeStep}, AnalysisParameters{ timeStep } );
    auto result = analyzer.run();

    EXPECT_EQ( REACHABILITY_RESULT::SAFE, result.result() );
}
