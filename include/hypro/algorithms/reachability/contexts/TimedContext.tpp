#include "TimedContext.h"

namespace hypro {

template <typename State>
bool TimedContext<State>::doneCondition() {
	// <FULLTIME-SPECIFIC>
	return mElapsed;
	// </FULLTIME-SPECIFIC>
}

template <typename State>
void TimedContext<State>::applyContinuousEvolution() {
	// <FULLTIME-SPECIFIC>
	State stateBefore( this->mComputationState );
	// </FULLTIME-SPECIFIC>

	for ( std::size_t i = 0; i < this->mContinuousEvolutionHandlers.size(); i++ ) {
		this->mContinuousEvolutionHandlers.at( i )->handle();
	}

	// <FULLTIME-SPECIFIC>

	carl::Interval<tNumber> interval = handshakeTimestamps( stateBefore, this->mComputationState );
	assert( !interval.isEmpty() );

	TRACE( "hydra.worker", "Elapsed time interval " << interval );
	this->mComputationState.setTimestamp( interval );
	mElapsed = true;

	// </FULLTIME-SPECIFIC>
}

template <typename State>
void TimedContext<State>::execOnLoopItExit() {
	// <FULLTIME-SPECIFIC>
	/*
	 * We only go through the loop once. Consequently we have to adjust the timing differently.
	 * Also we have to call guard intersection because it is on loop start on the unelapsed first segment.
	 *
	 */
	this->mCurrentLocalTime = this->mComputationState.getTimestamp().upper();
	this->mCurrentTimeInterval = this->mComputationState.getTimestamp();
	carl::Interval<tNumber> entryTimeStamp = this->mTask->treeNode->getStateAtLevel( this->mTask->btInfo.btLevel ).getTimestamp();
	this->mCurrentGlobalTimeInterval = entryTimeStamp + this->mComputationState.getTimestamp();

	// intersect with transition guards
	// execBeforeCheckTransition(); // TODO: Was uncommented
	checkTransition();
	LTIContext<State>::execAfterCheckTransition();
	// </FULLTIME-SPECIFIC>
}

template <typename State>
void TimedContext<State>::checkInvariant() {
	// <FULLTIME-SPECIFIC>
	mPreOpState = this->mComputationState;
	// </FULLTIME-SPECIFIC>

	if ( this->mInvariantHandlers.size() > 0 ) {
		// compute strictes containment on the fly
		hypro::CONTAINMENT strictestContainment = hypro::CONTAINMENT::FULL;
		// applay handlers to state
		for ( std::size_t i = 0; i < this->mInvariantHandlers.size(); i++ ) {
			this->mInvariantHandlers.at( i )->handle();

			if ( this->mInvariantHandlers.at( i )->getContainment() != hypro::CONTAINMENT::NO ) {
				TRACE( "hydra.worker.continuous", "State set " << i << "(type " << this->mComputationState.getSetType( i ) << ") failed the condition - return empty." );
				strictestContainment = this->mInvariantHandlers.at( i )->getContainment();
				break;
			} else if ( this->mInvariantHandlers.at( i )->getContainment() == hypro::CONTAINMENT::PARTIAL ) {
				strictestContainment = hypro::CONTAINMENT::PARTIAL;
			}
		}

		// <FULLTIME-SPECIFIC>
		// only perform handshake if invariant satisfied in all subspaces
		if ( strictestContainment != hypro::CONTAINMENT::NO ) {
			carl::Interval<tNumber> interval = handshakeTimestamps( mPreOpState, this->mComputationState );
			if ( interval.isEmpty() ) {
				DEBUG( "hydra.worker.continuous", "Invariant invalidated due to failed timestamp handshake." );
				strictestContainment = hypro::CONTAINMENT::NO;
			} else {
				this->mComputationState.setTimestamp( interval );
			}
		}
		// </FULLTIME-SPECIFIC>

		DEBUG( "hydra.worker.continuous", "Valuation fulfills Invariant?: " );
		DEBUG( "hydra.worker.continuous", " " << strictestContainment << std::endl );

		if ( strictestContainment == hypro::CONTAINMENT::NO ) {
			throw FinishWithDiscreteProcessingException( "Segment does not fulfill invariant! Terminating worker by processing discrete States." );
		}
	}

	DEBUG( "hydra.worker", "State after intersection with invariant: " << this->mComputationState );

	// For plotting.
#ifdef HYDRA_ENABLE_PLOT
	TRACE( "hydra.worker.plot", "Add " << this->mComputationState.getSets().size() << "segments for plotting of type " << this->mComputationState.getSetType() << " and refinement level " << this->mTask->btInfo.btLevel );
	this->mLocalSegments.addState( this->mComputationState );
#endif
}

template <typename State>
void TimedContext<State>::checkTransition() {
	// Collect potential new initial states from discrete behaviour.
	if ( !( this->mSettings.jumpDepth < 0 || int( this->mTask->treeNode->getDepth() ) <= this->mSettings.jumpDepth ) ) {
		return;
	}

	bool urgentTransitionEnabled = false;

	for ( auto it = this->mTransitionHandlerMap.begin(); it != this->mTransitionHandlerMap.end(); ++it ) {
#ifdef SINGLE_THREAD_FIXED_POINT_TEST
		// if the considered transition is disabled (for one iteration), skip the test by starting the next loop iteration.
		auto disabledTransitionIt = std::find( this->mDisabledTransitions.begin(), this->mDisabledTransitions.end(), it->first );
		if ( disabledTransitionIt != this->mDisabledTransitions.end() ) {
			this->mDisabledTransitions.erase( disabledTransitionIt );
			continue;
		}
#endif

		if ( !it->first->isUrgent() && LTIContext<State>::omitTransition( it->first ) ) {
			// store that transition was not enabled for this time interval
			this->mTask->treeNode->rGetRefinements().at( this->mTask->btInfo.btLevel ).mTimings.insertTransition( it->first, this->mCurrentGlobalTimeInterval, hypro::CONTAINMENT::NO );
			continue;
		}

		TRACE( "hydra.worker", "Initializing " << it->second.size() << " guard handlers for transition " << it->first->getSource()->hash() << " -> " << it->first->getTarget()->hash() );

		State* guardStatePtr = new State( this->mComputationState );
		std::shared_ptr<State> shGuardPtr = std::shared_ptr<State>( guardStatePtr );

		for ( std::size_t i = 0; i < it->second.size(); i++ ) {
			it->second.at( i )->setState( shGuardPtr );
		}

		// apply handlers
		bool guardSatisfied = true;

		if ( it->second.size() > 0 ) {
			// START_BENCHMARK_OPERATION(FULL_CUT);
			for ( auto guardIt = it->second.begin(); guardIt != it->second.end(); ++guardIt ) {
				// START_BENCHMARK_OPERATION(SUBSPACE_CUT);
				( *guardIt )->reinitialize();
				( *guardIt )->handle();
				guardSatisfied &= ( *guardIt )->satisfiesGuard();
				// EVALUATE_BENCHMARK_RESULT(SUBSPACE_CUT);

				if ( !guardSatisfied ) {
					break;
				}
			}
		}

		// handle time-triggered transitions
		if ( it->first->isUrgent() ) {
			TRACE( "hydra.worker.discrete", "Checking urgent transition " << it->first->getSource()->hash() << " -> " << it->first->getTarget()->hash() );
			if ( guardSatisfied ) {
				this->mDiscreteSuccessorBuffer.push_back( std::tuple<hypro::Transition<Number>*, State>( it->first, *guardStatePtr ) );
				urgentTransitionEnabled = true;
			}
		}  // handle normal transitions, but only if they cannot be omitted (they can if the timing intervals do not intersect)
		else if ( guardSatisfied ) {
			// <FULLTIME-SPECIFIC>

			carl::Interval<tNumber> timeStamp = handshakeTimestamps( this->mComputationState, *( guardStatePtr ) );
			if ( timeStamp.isEmpty() ) {
				this->mTask->treeNode->rGetRefinements().at( this->mTask->btInfo.btLevel ).mTimings.insertTransition( it->first, this->mCurrentGlobalTimeInterval, hypro::CONTAINMENT::NO );
			} else {
				guardStatePtr->setTimestamp( timeStamp );
				TRACE( "hydra.worker.discrete", "hybrid transition enabled with timestamp " << guardStatePtr->getTimestamp() );
				TRACE( "hydra.worker.discrete", "Enqueued state: " << *( guardStatePtr ) );
				this->mDiscreteSuccessorBuffer.push_back( std::tuple<hypro::Transition<Number>*, State>( it->first, *( guardStatePtr ) ) );
				if ( SettingsProvider<State>::getInstance().useLocalTiming() ) {
					carl::Interval<tNumber> entryTimeStamp = this->mTask->treeNode->getStateAtLevel( this->mTask->btInfo.btLevel ).getTimestamp();
					carl::Interval<tNumber> guardSatTimeStamp = entryTimeStamp + guardStatePtr->getTimestamp();
					this->mTask->treeNode->rGetRefinements().at( this->mTask->btInfo.btLevel ).mTimings.insertTransition( it->first, guardSatTimeStamp, hypro::CONTAINMENT::YES );

				} else {
					this->mTask->treeNode->rGetRefinements().at( this->mTask->btInfo.btLevel ).mTimings.insertTransition( it->first, guardStatePtr->getTimestamp(), hypro::CONTAINMENT::YES );
				}
			}
			// </FULLTIME-SPECIFIC>
		} else {
			// store that transition was not enabled for this time interval
			this->mTask->treeNode->rGetRefinements().at( this->mTask->btInfo.btLevel ).mTimings.insertTransition( it->first, this->mCurrentGlobalTimeInterval, hypro::CONTAINMENT::NO );
		}
	}

	if ( urgentTransitionEnabled ) {
		// quit loop after firing time triggered transition -> time triggered transitions are handled as urgent.
		TRACE( "hydra.worker.discrete", "Urgent transition enabled, quit flowpipe computation immediately." << std::endl );
		throw FinishWithDiscreteProcessingException( "Urgent transition enabled, quit flowpipe computation immediately." );
	}
}

template <typename State>
carl::Interval<tNumber> TimedContext<State>::computeShortestElapsedTimeIntervalForSubspace( State& in, size_t index ) {
	carl::Interval<tNumber> minInterval = createEmptyInterval<tNumber>();
	tNumber minDiameter = -1.0;
	// this should always be a dbm. If not, we deliberately throw the bad get exception
	hypro::DifferenceBounds<Number> dbm = std::get<hypro::DifferenceBounds<Number>>( in.getSet( index ) );
	if ( dbm.dimension() > 0 ) {
		size_t numclocks = dbm.dimension();
		for ( size_t i = 0; i < numclocks; i++ ) {
			// for each clock project the DBM to its axis
			std::vector<size_t> v;
			v.push_back( i );
			hypro::DifferenceBounds<Number> projectedDBM = dbm.projectOn( v );
			// compute vertices ie endpoints of interval
			std::vector<hypro::Point<Number>> vert = projectedDBM.vertices();
			// if less than 2, this is a point interval and therefore minimal (diameter 0)
			if ( vert.size() == 0 ) {
				// can happen due to rounding issues on eg: [-2.22507e-308, 0] -> return point
				return carl::Interval<tNumber>( tNumber( 0.0 ) );
			} else if ( vert.size() < 2 ) {
				hypro::Point<Number> origin = hypro::Point<Number>( vector_t<Number>::Zero( 1 ) );
				Number timePoint = origin.distance( vert[0] );
				if ( abs( timePoint ) > 0 && abs( timePoint ) < 0.000000000001 ) {
					timePoint = Number( 0 );
				}
				return carl::Interval<tNumber>( carl::convert<Number, tNumber>( timePoint ) );
			}
			// as we projected to axis and the entries were not the same, that size should be 2
			assert( vert.size() == 2 );

			// compute diameter of interval
			hypro::Point<Number> origin = hypro::Point<Number>( vector_t<Number>::Zero( 1 ) );
			Number timePoint1 = origin.distance( vert[0] );
			if ( abs( timePoint1 ) > 0 && abs( timePoint1 ) < 0.000000000001 ) {
				timePoint1 = Number( 0 );
			}
			Number timePoint2 = origin.distance( vert[1] );
			if ( abs( timePoint2 ) > 0 && abs( timePoint2 ) < 0.000000000001 ) {
				timePoint2 = Number( 0 );
			}
			Number diameter = vert[0].distance( vert[1] );
			if ( abs( diameter ) > 0 && abs( diameter ) < 0.000000000001 ) {
				diameter = Number( 0 );
			}

			// if interval is minimal
			if ( diameter < minDiameter || minDiameter < 0.0 ) {  // on first iteration this might be -1.0 so update
				minDiameter = carl::convert<Number, tNumber>( diameter );
				minInterval = timePoint1 < timePoint2 ? carl::Interval<tNumber>( carl::convert<Number, tNumber>( timePoint1 ), carl::convert<Number, tNumber>( timePoint2 ) ) : carl::Interval<tNumber>( carl::convert<Number, tNumber>( timePoint2 ), carl::convert<Number, tNumber>( timePoint1 ) );
			}
		}
	}
	return minInterval;
}

template <typename State>
carl::Interval<tNumber> TimedContext<State>::handshakeTimestamps( State& preOp, State& postOp ) {
	assert( preOp.getNumberSets() == postOp.getNumberSets() );
	auto map = SettingsProvider<State>::getInstance().getLocationSubspaceTypeMap();
	std::vector<hypro::SUBSPACETYPE> types = *( map.find( preOp.getLocation() )->second );

	// for each timed subspace compute its minimal elapsed time interval before the operation happened
	std::map<size_t, carl::Interval<tNumber>> preOpTimeIntervals;
	for ( size_t index = 0; index < preOp.getNumberSets(); index++ ) {
		if ( types.at( index ) != hypro::SUBSPACETYPE::TIMED ) {
			// only compute for timed subspaces
			continue;
		}
		preOpTimeIntervals.insert( std::make_pair( index, computeShortestElapsedTimeIntervalForSubspace( preOp, index ) ) );
	}

	// for each timed subspace compute its minimal elapsed time interval before the operation happened
	std::map<size_t, carl::Interval<tNumber>> postOpTimeIntervals;
	for ( size_t index = 0; index < postOp.getNumberSets(); index++ ) {
		if ( types.at( index ) != hypro::SUBSPACETYPE::TIMED ) {
			// only compute for timed subspaces
			continue;
		}
		// build normalized vectors by substracting the lower bounds of the preOpTimeIntervals
		// e.g. lets assume we are between [7,19] before. We perform the guard cut and obtain [16,17]
		// as the time interval that satisfies the cut. [16,18] - [7,7] will give [9,11] i.e. the time in
		// which the cut happened after entering with the preop timestamp. Intersecting these timestamps
		// will either yield an empty interval (guards were satisfied at non intersecting timestamps)
		// or all timestamp will agree upon a time interval, eg. [9,10] in the above case.
		carl::Interval<tNumber> timestampPost = computeShortestElapsedTimeIntervalForSubspace( postOp, index );
		carl::Interval<tNumber> timestampPre = preOpTimeIntervals.find( index )->second;

		carl::Interval<tNumber> normalized = carl::Interval<tNumber>( timestampPost.lower() - timestampPre.lower(), timestampPost.upper() - timestampPre.lower() );
		postOpTimeIntervals.insert( std::make_pair( index, normalized ) );
	}

	carl::Interval<tNumber> agreedTimeStamp = createEmptyInterval<tNumber>();
	bool first = true;
	for ( auto it = postOpTimeIntervals.begin(); it != postOpTimeIntervals.end(); ++it ) {
		if ( first ) {
			// just copy over first timestamp
			agreedTimeStamp = it->second;
			first = false;
		} else {
			// intersect timestamps
			agreedTimeStamp = carl::set_intersection( agreedTimeStamp, it->second );
		}
	}

	if ( agreedTimeStamp.isEmpty() ) {
		// there was no agreement on the jump timestamp
		return createEmptyInterval<tNumber>();
	}
	for ( size_t index = 0; index < postOp.getNumberSets(); index++ ) {
		if ( types.at( index ) != hypro::SUBSPACETYPE::TIMED ) {
			// only compute for timed subspaces
			continue;
		}

		hypro::DifferenceBounds<Number> preOpDBM = std::get<hypro::DifferenceBounds<Number>>( preOp.getSet( index ) );
		hypro::DifferenceBounds<Number> postOpDBM = std::get<hypro::DifferenceBounds<Number>>( postOp.getSet( index ) );
		for ( int i = 1; i < postOpDBM.getDBM().rows(); i++ ) {
			Number lowerBound = preOpDBM.getDBM()( 0, i ).first;

			// eg clock[5,10] , agreed jumptimestep [2,4] <=> [5+2,5+4] = [7,9]
			Number newLowerBound = lowerBound - carl::convert<tNumber, Number>( agreedTimeStamp.lower() );
			Number newUpperBound = abs( lowerBound ) + carl::convert<tNumber, Number>( agreedTimeStamp.upper() );
			// cut with x-0 <= c
			postOpDBM = postOpDBM.intersectConstraint( i, 0, typename hypro::DifferenceBounds<Number>::DBMEntry( newUpperBound, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ ) );
			// cut with 0-x <= c
			postOpDBM = postOpDBM.intersectConstraint( 0, i, typename hypro::DifferenceBounds<Number>::DBMEntry( newLowerBound, hypro::DifferenceBounds<Number>::BOUND_TYPE::SMALLER_EQ ) );
		}
		postOp.setSet( postOpDBM, index );
	}

	return agreedTimeStamp;
}

}  // namespace hypro
