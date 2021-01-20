#include <hypro/datastructures/HybridAutomaton/HybridAutomaton.h>
using namespace hypro;

/*
Singular
    time elapse
        x invariant on two variables - one violated earlier: singularNoJumpsWithInvHa1
        x invariant on only one variable: singularNoJumpsWithInvHa2
        x no invariants: singularNoJumpsNoInvHa
    guards
        guard in one subspace
        guard in both subspaces
        no guard
        "urgent"
    resets
        one reset
        both reset
        none reset
    jumps
        self loop
        3 jumps with non-box shaped successor sets (simple dynamics, no resets)
    safety
    edge cases
        empty jump successors due to invariant in new location
*/

template <typename Number>
HybridAutomaton<Number> singularNoJumpsNoInvHa() {
    using Matrix = matrix_t<Number>;
    using Vector = vector_t<Number>;

    HybridAutomaton<Number> ha;

    // Create locations
    Location<Number> loc0{};

    // Set flow x' = 1, y' = 1
    Matrix flow0 = Matrix::Zero( 3, 3 );
    flow0( 0, 2 ) = 1;
    flow0( 1, 2 ) = 1;
    loc0.setFlow( flow0 );

    // Set initial state x = [0,1], y = [0,1]
    Matrix initialConstraints = Matrix::Zero( 4, 2 );
    Vector initialConstants = Vector::Zero( 4 );
    initialConstraints << 1, 0,
                        -1, 0,
                        0, 1,
                        0, -1;
    initialConstants << 1, 0, 1, 0;

    auto& locPtr = ha.addLocation( std::make_unique<Location<Number>>( loc0 ) );
    ha.addInitialState( locPtr.get(), Condition<Number>( initialConstraints, initialConstants ) );
    return ha;
}


template <typename Number>
HybridAutomaton<Number> singularNoJumpsWithInvHa1() {
    // Two-dimensional HA with two locations. Invariant on both variables,
    // where one is enabled longer
    using Matrix = matrix_t<Number>;
    using Vector = vector_t<Number>;

    HybridAutomaton<Number> ha;

    // Create locations
    Location<Number> loc0{};

    // Set flow x' = 1, y' = 1
    Matrix flow0 = Matrix::Zero( 3, 3 );
    flow0( 0, 2 ) = 1;
    flow0( 1, 2 ) = 1;
    loc0.setFlow( flow0 );

    // Set invariant x <= 5 y <= 10
    Matrix invariantConstraints = Matrix::Zero( 2, 2 );
    invariantConstraints( 0, 0 ) = 1;
    invariantConstraints( 1, 1 ) = 1;
    Vector invariantConstants = Vector::Zero( 2 );
    invariantConstants << 5, 10;
    loc0.setInvariant( { invariantConstraints, invariantConstants } );

    // Set initial state x = [0,1], y = [0,1]
    Matrix initialConstraints = Matrix::Zero( 4, 2 );
    Vector initialConstants = Vector::Zero( 4 );
    initialConstraints << 1, 0,
                        -1, 0,
                        0, 1,
                        0, -1;
    initialConstants << 1, 0, 1, 0;

    auto& locPtr = ha.addLocation( std::make_unique<Location<Number>>( loc0 ) );
    ha.addInitialState( locPtr.get(), Condition<Number>( initialConstraints, initialConstants ) );
    return ha;
}

template <typename Number>
HybridAutomaton<Number> singularNoJumpsWithInvHa2() {
    // Two-dimensional HA with two locations. Invariant on only one variable
    using Matrix = matrix_t<Number>;
    using Vector = vector_t<Number>;

    HybridAutomaton<Number> ha;

    // Create locations
    Location<Number> loc0{};

    // Set flow x' = 1, y' = 1
    Matrix flow0 = Matrix::Zero( 3, 3 );
    flow0( 0, 2 ) = 1;
    flow0( 1, 2 ) = 1;
    loc0.setFlow( flow0 );

    // Set invariant x <= 5
    Matrix invariantConstraints = Matrix::Zero( 1, 2 );
    invariantConstraints( 0, 0 ) = 1;
    Vector invariantConstants = Vector::Zero( 1 );
    invariantConstants << 5;
    loc0.setInvariant( { invariantConstraints, invariantConstants } );

    // Set initial state x = [0,1], y = [0,1]
    Matrix initialConstraints = Matrix::Zero( 4, 2 );
    Vector initialConstants = Vector::Zero( 4 );
    initialConstraints << 1, 0,
                        -1, 0,
                        0, 1,
                        0, -1;
    initialConstants << 1, 0, 1, 0;

    auto& locPtr = ha.addLocation( std::make_unique<Location<Number>>( loc0 ) );
    ha.addInitialState( locPtr.get(), Condition<Number>( initialConstraints, initialConstants ) );
    return ha;
}

template <typename Number>
HybridAutomaton<Number> singularGuardHa1() {
    // guard in one subspace, no reset
    using Matrix = matrix_t<Number>;
    using Vector = vector_t<Number>;

    HybridAutomaton<Number> ha;

    // Create locations
    Location<Number> loc0{};
    Location<Number> loc1{};
    auto uniqueLoc0{ std::make_unique<Location<Number>>( loc0 ) };
    auto uniqueLoc1{ std::make_unique<Location<Number>>( loc1 ) };
    uniqueLoc0->setName( "l0" );
    uniqueLoc1->setName( "l1" );

    // Set flow x' = 1, y' = 1 in loc0
    Matrix flow0 = Matrix::Zero( 3, 3 );
    flow0( 0, 2 ) = 1;
    flow0( 1, 2 ) = 1;
    uniqueLoc0->setFlow( flow0 );

    // Set flow x' = 0, y' = 0 in loc1
    Matrix flow1 = Matrix::Zero( 3, 3 );
    uniqueLoc1->setFlow( flow1 );

    // Construct transitions
    // l0 -> l1 with guard x >= 5 and no reset
    Matrix transConstraint = Matrix::Zero( 1, 2 );
    Vector transConstants = -5 * Vector::Ones( 1 );
    transConstraint( 0, 0 ) = -1;
    Condition<Number> guard = Condition<Number>( transConstraint, transConstants );
    Reset<Number> reset = Reset<Number>( { carl::Interval<Number>(), carl::Interval<Number>() } );

    std::unique_ptr<Transition<Number>> trans0 =
          std::make_unique<Transition<Number>>( uniqueLoc0.get(), uniqueLoc1.get(), guard, reset );

    // Set initial state x = [0,1], y = [0,1]
    Matrix initialConstraints = Matrix::Zero( 4, 2 );
    Vector initialConstants = Vector::Zero( 4 );
    initialConstraints << 1, 0, 
                        -1, 0, 
                        0, 1, 
                        0, -1;
    initialConstants << 1, 0, 1, 0;

    // Create HA
    uniqueLoc0->addTransition( std::move( trans0 ) );

    ha.addInitialState( uniqueLoc0.get(), Condition<Number>( initialConstraints, initialConstants ) );

    ha.addLocation( std::move( uniqueLoc0 ) );
    ha.addLocation( std::move( uniqueLoc1 ) );

    return ha;
}

template <typename Number>
HybridAutomaton<Number> singularWithJumpsHa() {
    // Two-dimensional HA with two locations
    using Matrix = matrix_t<Number>;
    using Vector = vector_t<Number>;

    HybridAutomaton<Number> ha;

    // Create locations
    Location<Number> loc0{};
    Location<Number> loc1{};
    auto uniqueLoc0{ std::make_unique<Location<Number>>( loc0 ) };
    auto uniqueLoc1{ std::make_unique<Location<Number>>( loc1 ) };
    uniqueLoc0->setName( "l0" );
    uniqueLoc1->setName( "l1" );

    // Set flow x' = 1, y' = -1 in loc0
    Matrix flow0 = Matrix::Zero( 3, 3 );
    flow0( 0, 2 ) = 1;
    flow0( 1, 2 ) = -1;
    uniqueLoc0->setFlow( flow0 );

    // Set flow x' = 0, y' = 1 in loc1
    Matrix flow1 = Matrix::Zero( 3, 3 );
    flow1( 1, 2 ) = 1;
    uniqueLoc1->setFlow( flow1 );

    // Set invariant x <= 3 in loc0 and loc1
    Matrix invariantConstraints = Matrix::Zero( 1, 2 );
    invariantConstraints( 0, 0 ) = 1;
    Vector invariantConstants = 3 * Vector::Ones( 1 );
    uniqueLoc0->setInvariant( { invariantConstraints, invariantConstants } );
    uniqueLoc1->setInvariant( { invariantConstraints, invariantConstants } );

    // Construct transitions
    // l0 -> l0 with guard x >= 1 and reset x := 0
    Matrix transConstraint = Matrix::Zero( 1, 2 );
    Vector transConstants = -1 * Vector::Ones( 1 );
    transConstraint( 0, 0 ) = -1;
    Condition<Number> guard( transConstraint, transConstants );
    Reset<Number> reset{ { { 0, 0 }, { } } };

    std::unique_ptr<Transition<Number>> trans0 =
          std::make_unique<Transition<Number>>( uniqueLoc0.get(), uniqueLoc0.get(), guard, reset );

    // l0 -> l1 with guard y <= -2 and no reset
    transConstraint = Matrix::Zero( 1, 2 );
    transConstants = -2 * Vector::Ones( 1 );
    transConstraint( 0, 1 ) = 1;
    guard = Condition<Number>( transConstraint, transConstants );
    reset = Reset<Number>( { carl::Interval<Number>(), carl::Interval<Number>() } );

    std::unique_ptr<Transition<Number>> trans1 =
          std::make_unique<Transition<Number>>( uniqueLoc0.get(), uniqueLoc1.get(), guard, reset );

    // Set initial state x = 0, y = 0
    Matrix initialConstraints = Matrix::Zero( 4, 2 );
    Vector initialConstants = Vector::Zero( 4 );
    initialConstraints << 1, 0, -1, 0, 0, 1, 0, -1;
    initialConstants << 0, 0, 0, 0;

    // Create HA
    uniqueLoc0->addTransition( std::move( trans0 ) );
    //uniqueLoc0->addTransition( std::move( trans1 ) );

    ha.addInitialState( uniqueLoc0.get(), Condition<Number>( initialConstraints, initialConstants ) );

    ha.addLocation( std::move( uniqueLoc0 ) );
    ha.addLocation( std::move( uniqueLoc1 ) );

    return ha;
}

template<typename Number>
HybridAutomaton<Number> mixedDynamicsNoJumpsHa() {
    using Matrix = matrix_t<Number>;
    using Vector = vector_t<Number>;

    HybridAutomaton<Number> ha;
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

template <typename Number>
HybridAutomaton<Number> mixedDynamicsWithJumpsHa() {
    // Three-dimensional HA with two locations. First subspace is lti, second is singular
    using Matrix = matrix_t<Number>;
    using Vector = vector_t<Number>;

    HybridAutomaton<Number> res;

    // Create locations
    Location<Number> loc0{};
    Location<Number> loc1{};
    auto uniqueLoc0{ std::make_unique<Location<Number>>( loc0 ) };
    auto uniqueLoc1{ std::make_unique<Location<Number>>( loc1 ) };
    uniqueLoc0->setName( "l0" );
    uniqueLoc1->setName( "l1" );

    // Set flow x' = y, y' = -x, z' = 2 in loc0
    Matrix flow0 = Matrix::Zero( 4, 4 );
    flow0( 0, 1 ) = 1;
    flow0( 1, 0 ) = -1;
    flow0( 2, 3 ) = 2;
    uniqueLoc0->setFlow( flow0 );

    // Set flow x' = 1, y' = x + 2, z' = -1 in loc1
    Matrix flow1 = Matrix::Zero( 4, 4 );
    flow1( 0, 1 ) = 1;
    flow1( 1, 1 ) = 1;
    flow1( 1, 3 ) = 2;
    flow1( 2, 3 ) = -1;
    uniqueLoc1->setFlow( flow1 );

    // Set invariant x <= 3 in loc0 and loc1
    Matrix invariantConstraints = Matrix::Zero( 1, 3 );
    invariantConstraints( 0, 0 ) = 1;
    Vector invariantConstants = 3 * Vector::Ones( 1 );
    uniqueLoc0->setInvariant( { invariantConstraints, invariantConstants } );
    uniqueLoc1->setInvariant( { invariantConstraints, invariantConstants } );

    // Construct transitions
    // l0 -> l0 with guard x >= 1 and reset x := 0, y := 0
    Matrix transConstraint = Matrix::Zero( 1, 3 );
    Vector transConstants = -1 * Vector::Ones( 1 );
    transConstraint( 0, 0 ) = -1;
    Condition<Number> guard( transConstraint, transConstants );
    Matrix resetMat = Matrix::Zero( 3, 3 );
    Vector resetVec = Vector::Zero( 3 );
    resetMat( 2, 2 ) = 1;
    Reset<Number> reset( resetMat, resetVec );


    std::unique_ptr<Transition<Number>> trans0 =
          std::make_unique<Transition<Number>>( uniqueLoc0.get(), uniqueLoc0.get(), guard, reset );

    // l0 -> l1 with guard y <= -2 and no reset
    transConstraint = Matrix::Zero( 1, 3 );
    transConstants = -2 * Vector::Ones( 1 );
    transConstraint( 0, 1 ) = 1;
    guard = Condition<Number>( transConstraint, transConstants );
    reset = Reset<Number>( { carl::Interval<Number>(), carl::Interval<Number>(), carl::Interval<Number>() } );

    std::unique_ptr<Transition<Number>> trans1 =
          std::make_unique<Transition<Number>>( uniqueLoc0.get(), uniqueLoc1.get(), guard, reset );

    // Set initial state x = 0, y = 0, z = 1
    Matrix initialConstraints = Matrix::Zero( 6, 3 );
    Vector initialConstants = Vector::Zero( 6 );
    initialConstraints << 1, 0, 0,
                          -1, 0, 0,
                          0, 1, 0,
                          0, -1, 0,
                          0, 0, 1,
                          0, 0, -1;
    initialConstants << 0, 0, 0, 0, 1, -1;

    // Create HA
    uniqueLoc0->addTransition( std::move( trans0 ) );
    uniqueLoc0->addTransition( std::move( trans1 ) );

    res.addInitialState( uniqueLoc0.get(), Condition<Number>( initialConstraints, initialConstants ) );

    res.addLocation( std::move( uniqueLoc0 ) );
    res.addLocation( std::move( uniqueLoc1 ) );

    return res;
}