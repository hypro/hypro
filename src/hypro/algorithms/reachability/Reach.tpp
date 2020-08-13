#include "Reach.h"

namespace hypro {
namespace reachability {

using clock = std::chrono::high_resolution_clock;
using timeunit = std::chrono::microseconds;

template <typename Number, typename ReacherSettings, typename State>
Reach<Number, ReacherSettings, State>::Reach( const HybridAutomaton<Number>& _automaton, const ReachabilitySettings& _settings )
	: mAutomaton( _automaton )
	, mSettings( _settings )
	, mCurrentLevel( 0 )
	, mReachabilityTree( std::make_unique<ReachTree<State>>( new ReachTreeNode<State>() ) )
	, mIntersectedBadStates( false ) {
	assert( mSettings.timeBound >= 0 );
}

template <typename Number, typename ReacherSettings, typename State>
void Reach<Number, ReacherSettings, State>::setInitialStates( std::vector<State>&& initialStates ) {
	for ( auto& s : initialStates ) {
		s.setTimestamp( carl::Interval<tNumber>( 0 ) );
		ReachTreeNode<State>* treeNode = new ReachTreeNode<State>( s );
		treeNode->setParent( mReachabilityTree->getRoot() );
		mReachabilityTree->getRoot()->addChild( treeNode );
		mWorkingQueue.enqueue( std::make_unique<TaskType>( std::make_pair( mCurrentLevel, treeNode ) ) );
	}
	mInitialStatesSet = true;
}

template <typename Number, typename ReacherSettings, typename State>
void Reach<Number, ReacherSettings, State>::addInitialState( State&& initialState ) {
	initialState.setTimestamp( carl::Interval<tNumber>( 0 ) );
	ReachTreeNode<State>* treeNode = new ReachTreeNode<State>( initialState );
	treeNode->setParent( mReachabilityTree->getRoot() );
	mReachabilityTree->getRoot()->addChild( treeNode );
	mWorkingQueue.enqueue( std::make_unique<TaskType>( std::make_pair( mCurrentLevel, treeNode ) ) );
}

template <typename Number, typename ReacherSettings, typename State>
const std::map<typename Reach<Number, ReacherSettings, State>::NodePtr, typename Reach<Number, ReacherSettings, State>::flowpipe_t>& Reach<Number, ReacherSettings, State>::computeForwardReachability() {
	if ( !mInitialStatesSet ) {
		WARN( "hypro.reachability", "Attention, initial states have not been set yet." );
	}

	if ( ReacherSettings::printStatus ) {
		std::cout << std::endl
				  << "Queue size: " << mWorkingQueue.size() << std::flush;
	}

	TRACE( "hypro.reacher", "working queue size: " << mWorkingQueue.size() );

	if ( ReacherSettings::printStatus ) {
		std::cout << std::endl;
	}
	while ( !mWorkingQueue.isEmpty() ) {
		TaskTypePtr nextInitialSet = mWorkingQueue.dequeueFront();
		TRACE( "hypro.reacher", "working queue after pop: " << mWorkingQueue.size() );
		if ( ReacherSettings::printStatus ) {
			std::cout << "\rQueue size: " << mWorkingQueue.size() << std::flush;
		}

		mCurrentLevel = nextInitialSet->first;
		INFO( "hypro.reacher", "Depth " << mCurrentLevel << ", Location: " << nextInitialSet->second->getState().getLocation()->getName() );
		assert( int( mCurrentLevel ) <= mSettings.jumpDepth );
		TRACE( "hypro.reacher", "Obtained set of type " << nextInitialSet->second->getState().getSetType() << ", requested type is " << mType );
		flowpipe_t newFlowpipe = computeForwardTimeClosure( nextInitialSet->second );

		if ( !newFlowpipe.empty() ) {
			mReachableStates[nextInitialSet->second] = newFlowpipe;
		}
	}

	return mReachableStates;
}

template <typename Number, typename ReacherSettings, typename State>
typename Reach<Number, ReacherSettings, State>::flowpipe_t Reach<Number, ReacherSettings, State>::computeForwardTimeClosure( ReachTreeNode<State>* currentTreeNode ) {
	assert( !currentTreeNode->getState().getTimestamp().isUnbounded() );
#ifdef REACH_DEBUG
	INFO( "hypro.reacher", "Location: " << currentTreeNode->getState().getLocation()->hash() );
	INFO( "hypro.reacher", "Location printed : " << *( currentTreeNode->getState().getLocation() ) );
	INFO( "hypro.reacher", "Time step size: " << mSettings.timeStep );
#endif
	// new empty Flowpipe
	typename Reach<Number, ReacherSettings, State>::flowpipe_t flowpipe;
	std::vector<std::tuple<Transition<Number>*, State>> nextInitialSets;

	std::tuple<hypro::CONTAINMENT, State, matrix_t<Number>, vector_t<Number>, Box<Number>> initialSetup = computeFirstSegment<Number, State>( currentTreeNode->getState(), mSettings.timeStep );
#ifdef REACH_DEBUG
	INFO( "hypro.reacher", "Valuation fulfills Invariant?: " << std::get<0>( initialSetup ) );
#endif
	if ( std::get<0>( initialSetup ) != CONTAINMENT::NO ) {	 // see convenienceOperators for details
		assert( !std::get<1>( initialSetup ).getTimestamp().isUnbounded() );
		bool noFlow = false;

		// if the location does not have dynamic behaviour, check guards and exit loop.
		if ( std::get<2>( initialSetup ) == matrix_t<Number>::Identity( std::get<2>( initialSetup ).rows(), std::get<2>( initialSetup ).cols() ) &&
			 std::get<3>( initialSetup ) == vector_t<Number>::Zero( std::get<3>( initialSetup ).rows() ) ) {
			noFlow = true;
			// Collect potential new initial states from discrete behaviour.
			if ( int( mCurrentLevel ) <= mSettings.jumpDepth || mSettings.jumpDepth < 0 ) {
				INFO( "hypro.reacher", "-- Checking Transitions from initial!" );
				checkTransitions( currentTreeNode->getState(), carl::Interval<tNumber>( tNumber( 0 ), mSettings.timeBound ), nextInitialSets );
			}
		}

		// insert first Segment into the empty flowpipe
		State currentSegment;
		if ( noFlow ) {
			currentSegment = currentTreeNode->getState();
		} else {
			currentSegment = std::get<1>( initialSetup );
		}
		flowpipe.push_back( currentSegment );

		// Check for bad states intersection. The first segment is validated against the invariant, already.
		if ( intersectBadStates( currentSegment ) ) {
			// clear queue to stop whole algorithm
			while ( !mWorkingQueue.isEmpty() ) {
				mWorkingQueue.dequeueFront();
			}
			return flowpipe;
		}

		// Set after linear transformation
		State nextSegment;
#ifdef USE_SYSTEM_SEPARATION
		State autonomPart = currentSegment;
#ifdef USE_ELLIPSOIDS
		// Easy to addapt to any State use ellipsoid for the idea of my masterthesis here
		Ellipsoid<Number> nonautonomPart( mBloatingFactor, currentSegment.dimension() );
		Ellipsoid<Number> totalBloating = nonautonomPart;
#else
		Ellipsoid<Number> nonautonomPartAsEllispsoid( mBloatingFactor, currentSegment.dimension() );
		State nonautonomPart = State( nonautonomPartAsEllispsoid );
		State totalBloating = nonautonomPart;
#endif
#endif
#ifdef REACH_DEBUG
		if ( !noFlow ) {
			INFO( "hypro.reacher", "--- Loop entered ---" );
		}
#endif
		// the first segment covers one time step already
		tNumber currentLocalTime = mSettings.timeStep;
		bool forward = mSettings.timeStep > 0;
		INFO( "hypro.reacher", "Compute forwards time closure: " << forward );
		// intersection of bad states and violation of invariant is handled inside the loop
		while ( !noFlow && ( ( forward && currentLocalTime <= mSettings.timeBound ) || ( !forward && currentLocalTime >= -mSettings.timeBound ) ) ) {
			INFO( "hypro.reacher", "Time: " << std::setprecision( 4 ) << std::setw( 8 ) << std::fixed << carl::toDouble( currentLocalTime ) );
			// Verify transitions on the current set.
			if ( int( mCurrentLevel ) < mSettings.jumpDepth || mSettings.jumpDepth < 0 ) {
				//State currentState = _state;
				State currentState = currentSegment;
				INFO( "hypro.reacher", "--- Checking Transitions!" );
				checkTransitions( currentState, currentState.getTimestamp(), nextInitialSets );
			}

			// perform linear transformation on the last segment of the flowpipe
#ifdef USE_SYSTEM_SEPARATION
			autonomPart = autonomPart.partiallyApplyTimeStep( ConstraintSet<Number>( std::get<2>( initialSetup ), std::get<3>( initialSetup ) ), mSettings.timeStep, 0 );
#ifdef USE_ELLIPSOIDS
			if ( mBloatingFactor != 0 ) {
				Representation temp = Representation( totalBloating );
				nextSegment = autonomPart.minkowskiSum( temp );
			} else {
				nextSegment = autonomPart;
			}
#else
			if ( mBloatingFactor != 0 ) {
				nextSegment = autonomPart.minkowskiSum( totalBloating );
			} else {
				nextSegment = autonomPart;
			}
#endif
			// nonautonomPart = nonautonomPart.linearTransformation( std::get<2>(initialSetup), vector_t<Number>::Zero(autonomPart.dimension()));
			nonautonomPart = nonautonomPart.linearTransformation( std::get<2>( initialSetup ) );
			totalBloating = totalBloating.minkowskiSum( nonautonomPart );
#else
			nextSegment = currentSegment.partiallyApplyTimeStep( ConstraintSet<Number>( std::get<2>( initialSetup ), std::get<3>( initialSetup ) ), mSettings.timeStep, 0 );
#endif
			// extend flowpipe (only if still within Invariant of location)
			std::pair<hypro::CONTAINMENT, State> newSegment = nextSegment.satisfies( currentTreeNode->getState().getLocation()->getInvariant() );

#ifdef REACH_DEBUG
			INFO( "hypro.reacher", "still within Invariant?: " << newSegment.first );
#endif
			if ( newSegment.first != CONTAINMENT::NO ) {
				flowpipe.push_back( newSegment.second );
				if ( intersectBadStates( newSegment.second ) ) {
					// clear queue to stop whole algorithm
					while ( !mWorkingQueue.isEmpty() ) {
						mWorkingQueue.dequeueFront();
					}
					return flowpipe;
				}
				// update currentSegment
				currentSegment = newSegment.second;
			} else {
				// the flowpipe does not longer satisfy the invariant -> quit loop
				break;
			}
			currentLocalTime += mSettings.timeStep;
		}
#ifdef REACH_DEBUG
		if ( !noFlow ) {
			INFO( "hypro.reacher", "--- Loop left ---" );
		}
		INFO( "hypro.reacher", "flowpipe: " << flowpipe.size() << " Segments computed." );
		INFO( "hypro.reacher", "Process " << nextInitialSets.size() << " new initial sets." );
		INFO( "hypro.reacher", "current level: " << mCurrentLevel );

#endif
		// The loop terminated correctly (i.e. no bad states were hit), process discrete behavior.
		assert( nextInitialSets.empty() || ( int( mCurrentLevel ) < mSettings.jumpDepth || mSettings.jumpDepth < 0 ) );
		if ( int( mCurrentLevel ) < mSettings.jumpDepth || mSettings.jumpDepth < 0 ) {
			processDiscreteBehaviour( nextInitialSets, currentTreeNode );
		}
		return flowpipe;
	} else {
		// return an empty flowpipe
		return flowpipe;
	}
}

}  // namespace reachability
}  // namespace hypro
