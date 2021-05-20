#include "../src/tool/reachability/analysis.cpp"

#include <algorithm>
#include <hypro/datastructures/HybridAutomaton/HybridAutomaton.h>
#include <hypro/datastructures/HybridAutomaton/State.h>
#include <hypro/datastructures/HybridAutomaton/output/Flowstar.h>
#include <hypro/parser/antlr4-flowstar/ParserWrapper.h>
#include <hypro/util/logging/Filewriter.h>
#include <iostream>
#include <string>

using namespace hypro;
using namespace std::literals;

static const int firingThreshold = 1;
static const double alpha = 1.1;
static const double globalTimeHorizon = 300;

/**
 * @brief      Creates a component using a synchronization variable for the
 * synchronizating robots benchmark (shdI).
 * @param[in]  i       Component identifier.
 * @tparam     Number  Numeric type.
 * @return     A hybrid automaton for one component (one robot).
 */
template <typename Number>
HybridAutomaton<Number> createComponent1( size_t i, size_t n ) {
	using HA = HybridAutomaton<Number>;
	using M = matrix_t<Number>;
	using V = vector_t<Number>;
	using Lpt = Location<Number>*;
	using Tpt = Transition<Number>*;

	// result automaton
	HA res;

	// set up variables
	typename HybridAutomaton<Number>::variableVector vars;
	vars.push_back( "x_"s + std::to_string( i ) );
	vars.push_back( "x_t" );  // t is the global clock for plotting
	vars.push_back( "z" );	  // z is the shared variable
	Eigen::Index xi = 0;
	Eigen::Index gt = 1;
	Eigen::Index z = 2;
	res.setVariables( vars );
	unsigned dim = vars.size();

	// wait

	Lpt wait = res.createLocation();
	wait->setName( "wait_"s + std::to_string( i ) );
	M waitFlow = M::Zero( dim + 1, dim + 1 );
	waitFlow( xi, dim ) = 1;
	waitFlow( gt, dim ) = 1;  // time always advances at rate 1
	wait->setFlow( waitFlow );

	// initial valuations: xi = i-1/n, z = 0, gt = 0
	Condition<Number> initialValuations = hypro::conditionFromIntervals<Number>(
		  { carl::Interval<Number>{ Number( i ) / Number( n ) },
			carl::Interval<Number>{ 0 },
			carl::Interval<Number>{ 0 } } );
	res.addInitialState( wait, initialValuations );

	M waitInvariant = M::Zero( 2, dim );
	waitInvariant( 0, xi ) = 1;
	waitInvariant( 1, gt ) = 1;
	V waitInvConsts = V::Zero( 2 );
	waitInvConsts << Number( firingThreshold ), Number( globalTimeHorizon );
	wait->setInvariant( Condition<Number>{ waitInvariant, waitInvConsts } );

	// adapt
	Lpt adapt = res.createLocation();
	adapt->setName( "adapt_"s + std::to_string( i ) );
	M adaptFlow = M::Zero( dim + 1, dim + 1 );
	adaptFlow( gt, dim ) = 1;  // time always advances at rate 1
	adapt->setFlow( adaptFlow );

	// flash
	Lpt flash = res.createLocation();
	flash->setName( "flash_"s + std::to_string( i ) );

	M flashFlow = M::Zero( dim + 1, dim + 1 );
	flashFlow( gt, dim ) = 1;  // time always advances at rate 1
	flash->setFlow( flashFlow );

	M flashInvariant = M::Zero( 2, dim );
	flashInvariant( 0, xi ) = 1;
	flashInvariant( 1, xi ) = -1;
	V flashInvConsts = V::Zero( 2 );
	flash->setInvariant( Condition<Number>{ flashInvariant, flashInvConsts } );

	// transitions
	// to flash
	Tpt toFlash = wait->createTransition( flash );
	M guardConstraints = M::Zero( 2, dim );
	guardConstraints( 0, xi ) = 1;
	guardConstraints( 1, xi ) = -1;
	V guardConstants = V::Zero( 2 );
	guardConstants << Number( firingThreshold ), Number( -firingThreshold );
	toFlash->setGuard( Condition<Number>{ guardConstraints, guardConstants } );

	M resetMat = M::Identity( dim, dim );
	V resetVec = V::Zero( dim );
	resetMat( 0, 0 ) = 0;
	resetMat( 2, 2 ) = 0;
	resetVec( 2 ) = 1;
	toFlash->setReset( Reset<Number>( resetMat, resetVec ) );
	toFlash->setAggregation( Aggregation::aggregation );
	// toFlash->setUrgent();

	// to execFlash
	Tpt flashLoop = flash->createTransition( flash );
	guardConstraints = M::Zero( 2, dim );
	guardConstraints( 0, z ) = 1;
	guardConstraints( 1, z ) = -1;
	guardConstants = V::Zero( 2 );
	guardConstants << 1, -1;
	flashLoop->setGuard( Condition<Number>{ guardConstraints, guardConstants } );

	resetMat = M::Identity( dim, dim );
	resetMat( 2, 2 ) = 0;
	resetVec = V::Zero( dim );
	flashLoop->setReset( Reset<Number>( resetMat, resetVec ) );
	flashLoop->setUrgent();
	flashLoop->addLabel( Label{ "sync_1" } );
	flashLoop->setAggregation( Aggregation::aggregation );

	// back to wait
	Tpt reWait = flash->createTransition( wait );
	guardConstraints = M::Zero( 2, dim );
	guardConstraints( 0, z ) = 1;
	guardConstraints( 1, z ) = -1;
	guardConstants = V::Zero( 2 );
	reWait->setGuard( Condition<Number>{ guardConstraints, guardConstants } );
	resetMat = M::Identity( dim, dim );
	resetVec = V::Zero( dim );
	reWait->setReset( Reset<Number>( resetMat, resetVec ) );
	reWait->addLabel( Label{ "sync_2" } );
	reWait->setUrgent();
	reWait->setAggregation( Aggregation::aggregation );

	// to adapt
	Tpt toAdapt = wait->createTransition( adapt );
	guardConstraints = M::Zero( 3, dim );
	guardConstraints( 0, z ) = 1;
	guardConstraints( 1, z ) = -1;
	guardConstraints( 2, xi ) = 1;
	guardConstants = V::Zero( 3 );
	guardConstants << 1, -1, Number( firingThreshold );
	toAdapt->setGuard( Condition<Number>{ guardConstraints, guardConstants } );
	resetMat = M::Identity( dim, dim );
	resetMat( xi, xi ) = Number( alpha );
	resetMat( z, z ) = 0;  // not 100% sure whether z := 0 should be set here.
	resetVec = V::Zero( dim );
	toAdapt->setReset( Reset<Number>( resetMat, resetVec ) );
	toAdapt->addLabel( Label{ "sync_1" } );
	toAdapt->setAggregation( Aggregation::aggregation );
	// toAdapt->setUrgent();

	// from adapt, regular
	Tpt fromAdaptRegular = adapt->createTransition( wait );
	guardConstraints = M::Zero( 1, dim );
	guardConstraints( 0, xi ) = 1;
	guardConstants = V::Zero( 1 );
	guardConstants << Number( firingThreshold );
	fromAdaptRegular->setGuard(
		  Condition<Number>{ guardConstraints, guardConstants } );
	resetMat = M::Identity( dim, dim );
	resetVec = V::Zero( dim );
	fromAdaptRegular->setReset( Reset<Number>( resetMat, resetVec ) );
	fromAdaptRegular->addLabel( Label{ "sync_2" } );
	fromAdaptRegular->setAggregation( Aggregation::aggregation );
	fromAdaptRegular->setUrgent();

	// from adapt, scale
	Tpt fromAdaptScale = adapt->createTransition( wait );
	guardConstraints = M::Zero( 1, dim );
	guardConstraints( 0, xi ) = -1;
	guardConstants = V::Zero( 1 );
	guardConstants << Number( -firingThreshold );
	fromAdaptScale->setGuard( Condition<Number>{ guardConstraints, guardConstants } );
	resetMat = M::Identity( dim, dim );
	resetVec = V::Zero( dim );
	resetMat( xi, xi ) = 0;
	fromAdaptScale->setReset( Reset<Number>( resetMat, resetVec ) );
	fromAdaptScale->addLabel( Label{ "sync_2" } );
	fromAdaptScale->setAggregation( Aggregation::aggregation );
	fromAdaptScale->setUrgent();

	return res;
}

/**
 * Construct shd II
 * @tparam Number
 * @param i
 * @param labels
 * @return
 */
template <typename Number>
HybridAutomaton<Number> createComponent2( unsigned i, size_t n,
										  const std::vector<Label>& labels ) {
	using HA = HybridAutomaton<Number>;
	using M = matrix_t<Number>;
	using V = vector_t<Number>;
	using Lpt = Location<Number>*;
	using Tpt = Transition<Number>*;

	// result automaton
	HA res;

	res.setVariables( { "x_"s + std::to_string( i ), "x_t" } );
	size_t dimension = 2;

	// wait
	Lpt wait = res.createLocation();
	wait->setName( "wait_"s + std::to_string( i ) );
	M waitFlow = M::Zero( dimension + 1, dimension + 1 );  // both variables advance
	waitFlow( 0, dimension ) = 1;
	waitFlow( 1, dimension ) = 1;
	wait->setFlow( waitFlow );

	M waitInvariant = M::Zero( 2, dimension );
	waitInvariant( 0, 0 ) = 1;
	waitInvariant( 1, 1 ) = 1;
	V waitInvConsts = V::Zero( 2 );
	waitInvConsts << Number( firingThreshold ), Number( globalTimeHorizon );
	wait->setInvariant( Condition<Number>{ waitInvariant, waitInvConsts } );

	// initial state
	hypro::Condition<Number> initialValuations = hypro::conditionFromIntervals<Number>(
		  { carl::Interval<Number>{ Number( i ) / Number( n ) },
			carl::Interval<Number>{ 0 } } );
	res.addInitialState( wait, initialValuations );

	// adapt
	Lpt adapt = res.createLocation();
	adapt->setName( "adapt_" + std::to_string( i ) );

	M adaptFlow = M::Zero( dimension + 1, dimension + 1 );
	adaptFlow( 1, dimension ) = 1;	// time always advances at rate 1
	adapt->setFlow( adaptFlow );

	// transitions
	// flash self loop
	Tpt flash = wait->createTransition( wait );
	M guardConstraints = M::Zero( 2, dimension );
	guardConstraints( 0, 0 ) = 1;
	guardConstraints( 1, 0 ) = -1;
	V guardConstants = V::Zero( 2 );
	guardConstants << Number( firingThreshold ), Number( -firingThreshold );
	flash->setGuard( Condition<Number>{ guardConstraints, guardConstants } );

	M resetMat = M::Identity( dimension, dimension );
	V resetVec = V::Zero( dimension );
	resetMat( 0, 0 ) = 0;
	flash->addLabel( labels.at( i ) );
	flash->setReset( Reset<Number>( resetMat, resetVec ) );
	flash->setAggregation( Aggregation::aggregation );

	// to adapt
	for ( unsigned j = 0; j < labels.size(); ++j ) {
		if ( j != i ) {
			Tpt toAdapt = wait->createTransition( adapt );
			resetMat = M::Identity( dimension, dimension );
			resetMat( 0, 0 ) = Number( alpha );
			resetVec = V::Zero( dimension );
			toAdapt->setReset( Reset<Number>( resetMat, resetVec ) );

			toAdapt->addLabel( labels.at( j ) );

			toAdapt->setAggregation( Aggregation::aggregation );
		}
	}

	// from adapt, regular
	Tpt fromAdaptRegular = adapt->createTransition( wait );
	guardConstraints = M::Zero( 1, dimension );
	guardConstraints( 0, 0 ) = 1;
	guardConstants = V::Zero( 1 );
	guardConstants << Number( firingThreshold );
	fromAdaptRegular->setGuard(
		  Condition<Number>{ guardConstraints, guardConstants } );
	resetMat = M::Identity( dimension, dimension );
	resetVec = V::Zero( dimension );
	fromAdaptRegular->setReset( Reset<Number>( resetMat, resetVec ) );
	fromAdaptRegular->setAggregation( Aggregation::aggregation );
	fromAdaptRegular->setUrgent();

	// from adapt, scale
	Tpt fromAdaptScale = adapt->createTransition( wait );
	guardConstraints = M::Zero( 1, dimension );
	guardConstraints( 0, 0 ) = -1;
	guardConstants = V::Zero( 1 );
	guardConstants << Number( -firingThreshold );
	fromAdaptScale->setGuard( Condition<Number>{ guardConstraints, guardConstants } );
	fromAdaptScale->setAggregation( Aggregation::aggregation );
	fromAdaptScale->setUrgent();

	resetMat = M::Identity( dimension, dimension );
	resetMat( 0, 0 ) = 0;
	resetVec = V::Zero( dimension );
	fromAdaptScale->setReset( Reset<Number>( resetMat, resetVec ) );

	return res;
}

/**
 * @brief Create a HA for the model shdII.
 * @tparam Number
 * @param i
 * @return HybridAutomaton<Number>
 */
template <typename Number>
HybridAutomaton<Number> createComponent3( size_t i, size_t n ) {
	using HA = HybridAutomaton<Number>;
	using M = matrix_t<Number>;
	using V = vector_t<Number>;
	using Lpt = Location<Number>*;
	using Tpt = Transition<Number>*;

	// result automaton
	HA res;

	// set up variables
	typename HybridAutomaton<Number>::variableVector vars;
	vars.push_back( "x_"s + std::to_string( i ) );
	vars.push_back( "x_t" );  // t is the global clock for plotting
	vars.push_back( "z" );	  // z is the shared variable
	res.setVariables( vars );
	unsigned dim = vars.size();

	// wait
	Lpt wait = res.createLocation();
	wait->setName( "wait_"s + std::to_string( i ) );
	M waitFlow = M::Zero( dim + 1, dim + 1 );
	waitFlow( 0, dim ) = 1;
	waitFlow( 1, dim ) = 1;	 // time always advances at rate 1
	wait->setFlow( waitFlow );

	hypro::Condition<Number> initialValuations = hypro::conditionFromIntervals<Number>(
		  { carl::Interval<Number>{ Number( i ) / Number( n ) },
			carl::Interval<Number>{ 0 },
			carl::Interval<Number>{ 0 } } );
	res.addInitialState( wait, initialValuations );

	M waitInvariant = M::Zero( 2, dim );
	waitInvariant << 1, 0, 0, 0, 1, 0;
	V waitInvConsts = V::Zero( 2 );
	waitInvConsts << Number( firingThreshold ), Number( globalTimeHorizon );
	wait->setInvariant( Condition<Number>{ waitInvariant, waitInvConsts } );

	// adapt
	// Lpt adapt = manager.create();
	// st.str(std::string());
	// st << "adapt_" << i;
	// adapt->setName(st.str());
	//
	//	//M adaptFlow = M::Zero(dim+1,dim+1);
	//	//adaptFlow(1,dim) = 1; // time always advances at rate 1
	//	//adapt->setFlow(adaptFlow);
	//
	// res.addLocation(adapt);

	// flash
	Lpt flash = res.createLocation();
	flash->setName( "adapt_"s + std::to_string( i ) );
	M flashFlow = M::Zero( dim + 1, dim + 1 );
	flashFlow( 1, dim ) = 1;  // time always advances at rate 1
	flash->setFlow( flashFlow );

	// M flashInvariant = M::Zero(2,dim);
	// flashInvariant(0,0) = 1;
	// flashInvariant(1,0) = -1;
	// V flashInvConsts = V::Zero(2);
	// flash->setInvariant(Condition<Number>{flashInvariant, flashInvConsts});

	// transitions
	// to flash, x = firingThreshold
	Tpt toFlash = wait->createTransition( flash );
	M guardConstraints = M::Zero( 2, dim );
	guardConstraints( 0, 0 ) = 1;
	guardConstraints( 1, 0 ) = -1;
	V guardConstants = V::Zero( 2 );
	guardConstants << Number( firingThreshold ), Number( -firingThreshold );
	toFlash->setGuard( Condition<Number>{ guardConstraints, guardConstants } );

	M resetMat = M::Identity( dim, dim );
	V resetVec = V::Zero( dim );
	resetMat( 0, 0 ) = 0;
	resetMat( 2, 2 ) = 0;
	resetVec( 2 ) = 1;
	toFlash->setReset( Reset<Number>( resetMat, resetVec ) );
	toFlash->setAggregation( Aggregation::aggregation );
	// toFlash->setUrgent();

	// to execFlash, z = 1
	Tpt flashLoop = flash->createTransition( flash );
	guardConstraints = M::Zero( 2, dim );
	guardConstraints( 0, 2 ) = 1;
	guardConstraints( 1, 2 ) = -1;
	guardConstants = V::Zero( 2 );
	guardConstants << 1, -1;
	flashLoop->setGuard( Condition<Number>{ guardConstraints, guardConstants } );

	resetMat = M::Identity( dim, dim );
	resetMat( 2, 2 ) = 0;
	resetVec = V::Zero( dim );
	flashLoop->setReset( Reset<Number>( resetMat, resetVec ) );
	flashLoop->setUrgent();
	flashLoop->addLabel( Label{ "sync_1" } );
	flashLoop->setAggregation( Aggregation::aggregation );

	// back to wait
	/*
  Tpt reWait = new Transition<Number>(flash,wait);
  guardConstraints = M::Zero(2,dim);
  guardConstraints(0,2) = 1;
  guardConstraints(1,2) = -1;
  guardConstants = V::Zero(2);
  reWait->setGuard(Condition<Number>{guardConstraints,guardConstants});
  resetMat = M::Identity(dim,dim);
  resetVec = V::Zero(dim);
  reWait->addLabel({"return"});
  reWait->setReset(Reset<Number>(resetMat,resetVec));
  reWait->setUrgent();
  reWait->setAggregation(Aggregation::aggregation);

  flash->addTransition(reWait);
  res.addTransition(reWait);
  */

	// to adapt
	Tpt toAdapt = wait->createTransition( flash );
	guardConstraints = M::Zero( 3, dim );
	guardConstraints( 0, 2 ) = 1;
	guardConstraints( 1, 2 ) = -1;
	guardConstraints( 2, 0 ) = 1;
	guardConstants = V::Zero( 3 );
	guardConstants << 1, -1, Number( firingThreshold );
	toAdapt->setGuard( Condition<Number>{ guardConstraints, guardConstants } );
	resetMat = M::Identity( dim, dim );
	resetMat( 0, 0 ) = Number( alpha );
	resetMat( 2, 2 ) = 0;
	resetVec = V::Zero( dim );
	toAdapt->setReset( Reset<Number>( resetMat, resetVec ) );
	toAdapt->addLabel( { Label( "sync_1" ) } );
	toAdapt->setAggregation( Aggregation::aggregation );

	// from adapt, regular, x < f, z = 0
	Tpt fromAdaptRegular = flash->createTransition( wait );
	guardConstraints = M::Zero( 3, dim );
	guardConstraints( 0, 0 ) = 1;
	guardConstraints( 1, 2 ) = 1;
	guardConstraints( 2, 2 ) = -1;
	guardConstants = V::Zero( 3 );
	guardConstants << Number( firingThreshold ), 0, 0;
	fromAdaptRegular->setGuard(
		  Condition<Number>{ guardConstraints, guardConstants } );
	resetMat = M::Identity( dim, dim );
	resetVec = V::Zero( dim );
	fromAdaptRegular->setReset( Reset<Number>( resetMat, resetVec ) );
	fromAdaptRegular->addLabel( Label{ "sync_2" } );
	fromAdaptRegular->setAggregation( Aggregation::aggregation );
	fromAdaptRegular->setUrgent();

	// from adapt, scale, x > f, z = 0
	Tpt fromAdaptScale = flash->createTransition( wait );
	guardConstraints = M::Zero( 3, dim );
	guardConstraints( 0, 0 ) = -1;
	guardConstraints( 1, 2 ) = 1;
	guardConstraints( 2, 2 ) = -1;
	guardConstants = V::Zero( 3 );
	guardConstants << Number( -firingThreshold ), 0, 0;
	fromAdaptScale->setGuard( Condition<Number>{ guardConstraints, guardConstants } );
	fromAdaptScale->addLabel( Label{ "sync_2" } );
	fromAdaptScale->setAggregation( Aggregation::aggregation );
	fromAdaptScale->setUrgent();

	resetMat = M::Identity( dim, dim );
	resetMat( 0, 0 ) = 0;
	resetVec = V::Zero( dim );
	fromAdaptScale->setReset( Reset<Number>( resetMat, resetVec ) );

	return res;
}

template <typename Number>
HybridAutomaton<Number> createComponent4( unsigned i,
										  const std::vector<Label>& labels ) {
	using HA = HybridAutomaton<Number>;
	using M = matrix_t<Number>;
	using V = vector_t<Number>;
	using Lpt = Location<Number>*;
	using Tpt = Transition<Number>*;
	std::stringstream st;

	// result automaton
	HA res;

	// set up variables
	typename HybridAutomaton<Number>::variableVector vars;
	st << "x_" << i;
	vars.push_back( st.str() );
	vars.push_back( "x_t" );  // t is the global clock for plotting
	res.setVariables( vars );
	st.str( std::string() );
	unsigned dim = vars.size();

	// wait

	st << "wait_" << i;
	Lpt wait = res.createLocation();
	wait->setName( st.str() );
	M waitFlow = M::Zero( dim + 1, dim + 1 );  // both variables advance
	waitFlow( 0, dim ) = 1;
	waitFlow( 1, dim ) = 1;
	wait->setFlow( waitFlow );

	M waitInvariant = M::Zero( 2, dim );
	waitInvariant( 0, 0 ) = 1;
	waitInvariant( 1, 1 ) = 1;
	V waitInvConsts = V::Zero( 2 );
	waitInvConsts << Number( firingThreshold ), Number( globalTimeHorizon );
	wait->setInvariant( Condition<Number>{ waitInvariant, waitInvConsts } );

	// initial state
	M initConstraints = M::Zero( 4, 2 );
	initConstraints << 1, 0, -1, 0, 0, 1, 0, -1;
	V initConstants = V::Zero( 4 );
	initConstants << 0, 0, 0, 0;

	res.addInitialState( wait, Condition<Number>( initConstraints, initConstants ) );

	// adapt
	Lpt adapt = res.createLocation();
	st.str( std::string() );
	st << "adapt_" << i;
	adapt->setName( st.str() );

	M adaptFlow = M::Zero( dim + 1, dim + 1 );
	adaptFlow( 1, dim ) = 1;  // time always advances at rate 1
	adapt->setFlow( adaptFlow );

	// transitions
	// flash self loop
	Tpt flash = wait->createTransition( adapt );
	M guardConstraints = M::Zero( 2, dim );
	guardConstraints( 0, 0 ) = 1;
	guardConstraints( 1, 0 ) = -1;
	V guardConstants = V::Zero( 2 );
	guardConstants << Number( firingThreshold ), Number( -firingThreshold );
	flash->setGuard( Condition<Number>{ guardConstraints, guardConstants } );

	M resetMat = M::Identity( dim, dim );
	V resetVec = V::Zero( dim );
	resetMat( 0, 0 ) = 0;
	flash->addLabel( labels.at( i ) );
	flash->setReset( Reset<Number>( resetMat, resetVec ) );
	flash->setAggregation( Aggregation::aggregation );
	// flash->setUrgent();

	// to adapt
	for ( unsigned j = 0; j < labels.size(); ++j ) {
		if ( j != i ) {
			Tpt toAdapt = wait->createTransition( adapt );
			resetMat = M::Identity( dim, dim );
			resetMat( 0, 0 ) = Number( alpha );
			resetVec = V::Zero( dim );
			toAdapt->setReset( Reset<Number>( resetMat, resetVec ) );

			toAdapt->addLabel( labels.at( j ) );

			toAdapt->setAggregation( Aggregation::aggregation );
			// toAdapt->setUrgent();
		}
	}

	// from adapt, regular
	Tpt fromAdaptRegular = adapt->createTransition( wait );
	guardConstraints = M::Zero( 1, dim );
	guardConstraints( 0, 0 ) = 1;
	guardConstants = V::Zero( 1 );
	guardConstants << Number( firingThreshold );
	fromAdaptRegular->setGuard(
		  Condition<Number>{ guardConstraints, guardConstants } );
	resetMat = M::Identity( dim, dim );
	resetVec = V::Zero( dim );
	fromAdaptRegular->setReset( Reset<Number>( resetMat, resetVec ) );
	fromAdaptRegular->setAggregation( Aggregation::aggregation );
	fromAdaptRegular->setUrgent();
	fromAdaptRegular->addLabel( Label( "return" ) );

	// from adapt, scale
	Tpt fromAdaptScale = adapt->createTransition( wait );
	guardConstraints = M::Zero( 1, dim );
	guardConstraints( 0, 0 ) = -1;
	guardConstants = V::Zero( 1 );
	guardConstants << Number( -firingThreshold );
	fromAdaptScale->setGuard( Condition<Number>{ guardConstraints, guardConstants } );
	fromAdaptScale->setAggregation( Aggregation::aggregation );
	fromAdaptScale->setUrgent();
	fromAdaptScale->addLabel( Label( "return" ) );

	resetMat = M::Identity( dim, dim );
	resetMat( 0, 0 ) = 0;
	resetVec = V::Zero( dim );
	fromAdaptScale->setReset( Reset<Number>( resetMat, resetVec ) );

	return res;
}

template <class Number>
HybridAutomaton<Number> generateShd2( long componentCount ) {
	cout << "Create parallel composition for synchronization benchmark with "
		 << componentCount << " components using a reduced version with a shared variable."
		 << endl;

	HybridAutomaton<Number> composed_sync_sharedVar_2states = createComponent3<Number>( 1, componentCount );
	for ( int i = 2; i <= componentCount; ++i ) {
		HybridAutomaton<Number> tmp = createComponent3<Number>( i, componentCount );
		composed_sync_sharedVar_2states = composed_sync_sharedVar_2states ||
										  tmp;
		//assert( composed_sync_sharedVar_2states.isComposedOf( tmp ) );
	}

	composed_sync_sharedVar_2states.reduce();
	return composed_sync_sharedVar_2states;
}

template <class Number>
HybridAutomaton<Number> generateShd1( long componentCount ) {
	cout << "Create parallel composition for synchronization benchmark with "
		 << componentCount << " components using a shared variable." << endl;

	HybridAutomaton<Number> composed_sync_sharedVar = createComponent1<Number>( 1, componentCount );
	for ( int i = 2; i <= componentCount; ++i ) {
		HybridAutomaton<Number> tmp = createComponent1<Number>( i, componentCount );
		composed_sync_sharedVar = composed_sync_sharedVar || tmp;
		//assert( composed_sync_sharedVar.isComposedOf( tmp ) );
	}

	composed_sync_sharedVar.reduce();
	return composed_sync_sharedVar;
}

template <class Number>
HybridAutomaton<Number> generateLsync1( long componentCount ) {
	cout << "Create parallel composition for synchronization benchmark with "
		 << componentCount << " components using label synchronization."
		 << endl;

	vector<Label> labels;
	for ( int i = 0; i < componentCount; ++i ) {
		labels.emplace_back( "flash"s + to_string( i ) );
	}

	HybridAutomaton<Number> composed_sync_label =
		  createComponent2<Number>( 0, componentCount, labels );
	for ( int i = 1; i < componentCount; ++i ) {
		HybridAutomaton<Number> tmp = createComponent2<Number>( i, componentCount, labels );
		composed_sync_label = composed_sync_label || tmp;
		//assert( composed_sync_label.isComposedOf( tmp ) );
	}
	composed_sync_label.reduce();
	return composed_sync_label;
}

template <class Number>
void lsync1_to_lsync2( long componentCount, HybridAutomaton<Number>& composed_sync_label ) {
	std::string stats = composed_sync_label.getStatistics();
	std::cout << "Automaton stats:\n" << stats << "\n";

	std::cout << "Create parallel composition for synchronization benchmark with "
		 << componentCount
		 << " components using  optimized label synchronization.\n";

	auto transitions = composed_sync_label.getTransitions();
	vector<Transition<Number>*> toDelete;
	for ( auto transition : transitions ) {
		if ( transition->getSource()->getName().find( "adapt" ) != std::string::npos &&
			 transition->getTarget()->getName().find( "adapt" ) != std::string::npos ) {
			cout << "Remove edge " << transition->getSource()->getName() << " -> "
				 << transition->getTarget()->getName() << endl;
			toDelete.emplace_back( transition );
		}
	}
	for_each( begin( toDelete ), end( toDelete ), [&composed_sync_label]( const auto transitionPtr ) { composed_sync_label.removeTransition( transitionPtr ); } );

	composed_sync_label.reduce();
}
int main( int argc, char** argv ) {
	using Number = double;

	if ( argc != 3 ) {
		std::cout << "Wrong number of arguments: " << argc << "\n";
		return 1;
	}
	long int componentCount = std::strtol( argv[1], nullptr, 10 );

	std::string file_name{};
	HybridAutomaton<Number> const composition = [&] {
		if ( std::strcmp( argv[2], "lsync1" ) == 0 ) {
			file_name = "lsync1";
			return generateLsync1<Number>( componentCount );
		} else if ( std::strcmp( argv[2], "lsync2" ) == 0 ) {
			file_name = "lsync2";
			HybridAutomaton<Number> result = generateLsync1<Number>( componentCount );
			lsync1_to_lsync2( componentCount, result );
			return result;
		} else if ( std::strcmp( argv[2], "shd1" ) == 0 ) {
			file_name = "shd1";
			return generateShd1<Number>( componentCount );
		} else if ( std::strcmp( argv[2], "shd2" ) == 0 ) {
			file_name = "shd2";
			return generateShd2<Number>( componentCount );
		} else {
			std::cout << "invalid model name\n";
			throw std::invalid_argument( "invalid model name" );
		}
	}();

	PreprocessingInformation preprocessingInformation{};
	PlottingSettings plottingSettings{
		  { { 0, 1 } },
		  { file_name },
		  PLOTTYPE::pdf };
	FixedAnalysisParameters fixedParameters{ 20, 10 };
	AnalysisParameters analysisParameters{
		  0.001,
		  AGG_SETTING::AGG,
		  -1,
		  representation_name::box,
		  boxSetting_name::BoxAllOff,
	};

	START_BENCHMARK_OPERATION( "Verification" );
	auto result = hydra::reachability::analyze( composition,
												Settings( plottingSettings, fixedParameters, { analysisParameters } ),
												preprocessingInformation );
	EVALUATE_BENCHMARK_RESULT( "Verification" );

	std::cout << "Automaton stats:\n" << composition.getStatistics() << "\n";

	// settings to be used for flowstar format output
	// settings.plotDimensions.push_back(std::vector<std::size_t>());
	// settings.plotDimensions[0].push_back(0);
	// settings.plotDimensions[0].push_back(componentCount+1);

	// LockedFileWriter flowstar_sharedVar( "sync_sharedVar.model" );
	// flowstar_sharedVar.clearFile();
	// flowstar_sharedVar << toFlowstarFormat( composed_sync_sharedVar, settings );
	// // create dot output.
	// LockedFileWriter sharedVar_single( "sync_sharedVarSingle.dot" );
	// sharedVar_single.clearFile();
	// sharedVar_single << createComponent1<Number>( 1, componentCount ).getDotRepresentation();
	// LockedFileWriter sharedVar_res( "sync_sharedVarComposed.dot" );
	// sharedVar_res.clearFile();
	// sharedVar_res << composed_sync_sharedVar.getDotRepresentation();

	//	LockedFileWriter flowstar_label( "sync_labelSync.model" );
	//	flowstar_label.clearFile();
	//	flowstar_label << toFlowstarFormat( composed_sync_label, settings );
	// create dot output.
	//	LockedFileWriter label_single( "sync_labelSingle.dot" );
	//	label_single.clearFile();
	//	label_single << createComponent2<Number>(0, componentCount, std::vector<Label>( { Label( "flash0" ) } ) )
	//						  .getDotRepresentation();
	//	LockedFileWriter label_res( "sync_labelComposed.dot" );
	//	label_res.clearFile();
	//	label_res << composed_sync_label.getDotRepresentation();

	//	LockedFileWriter flowstar_label2( "sync_labelSyncRed.model" );
	//	flowstar_label2.clearFile();
	//	flowstar_label2 << toFlowstarFormat( composed_sync_label, settings );
	//	// create dot output.
	//	LockedFileWriter label_res2( "sync_labelComposed2.dot" );
	//	label_res2.clearFile();
	//	label_res2 << composed_sync_label.getDotRepresentation();

	/*
	std::cout << "Create parallel composition for synchronization benchmark with "
			  << componentCount << " components using 2nd optimized label synchronization."
			  << std::endl;

	std::vector<Label> labels;
	for ( int i = 0; i < componentCount; ++i ) {
		labels.emplace_back( "flash"s + std::to_string( i ) );
	}

	HybridAutomaton<Number> composed_sync_label_opt =
		  createComponent4<Number>( 0, labels );
	for ( int i = 1; i < componentCount; ++i ) {
		HybridAutomaton<Number> tmp = createComponent4<Number>( i, labels );
		composed_sync_label_opt = composed_sync_label_opt || tmp;
		//assert( composed_sync_label.isComposedOf( tmp ) );
	}

	// settings.fileName = "sync_labels";
	// LockedFileWriter flowstar_label( "sync_labelSync.model" );
	// flowstar_label.clearFile();
	// flowstar_label << toFlowstarFormat( composed_sync_label, settings );
	// // create dot output.
	// LockedFileWriter label_single( "sync_labelSingle.dot" );
	// label_single.clearFile();
	// label_single << createComponent2<Number>( 0, std::vector<Label>( { Label( "flash0" ) } ) ).getDotRepresentation();
	// LockedFileWriter label_res( "sync_labelComposed.dot" );
	// label_res.clearFile();
	// label_res << composed_sync_label.getDotRepresentation();

	std::cout << "Automaton stats: " << std::endl
			  << composed_sync_label_opt.getStatistics() << std::endl;
	std::cout << "Automaton: " << composed_sync_label_opt << std::endl;
	*/
	// settings.fileName = "sync_sharedVar2";
	// LockedFileWriter flowstar_sharedVarRed( "sync_sharedVar_2_states.model" );
	// flowstar_sharedVarRed.clearFile();
	// flowstar_sharedVarRed << toFlowstarFormat( composed_sync_sharedVar_2states, settings );
	// // create dot output.
	// LockedFileWriter sharedVarReduced_single( "sync_sharedVarReducedSingle.dot" );
	// sharedVarReduced_single.clearFile();
	// sharedVarReduced_single << createComponent3<Number>( 1 ).getDotRepresentation();
	// LockedFileWriter sharedVarReduced_res( "sync_sharedVarReducedComposed.dot" );
	// sharedVarReduced_res.clearFile();
	// sharedVarReduced_res << composed_sync_sharedVar_2states.getDotRepresentation();


	// for testing
	// auto haTuple = parseFlowstarFile<double>(std::string("composed.model"));

	return 0;
}
