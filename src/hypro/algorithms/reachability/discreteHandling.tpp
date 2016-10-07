

namespace hypro {
namespace reachability {
	template<typename Number, typename Representation>
	bool Reach<Number,Representation>::intersectGuard( Transition<Number>* _trans, const State<Number>& _state,
							   State<Number>& result ) const {
		assert(!_state.timestamp.isUnbounded());
		result = _state;
		//std::cout << "check transition " << _trans->source()->id() << " -> " << _trans->target()->id() << std::endl;
		VariablePool& vpool = VariablePool::getInstance();

		// check discrete guard intersection.
		unsigned dOffset = _trans->guard().discreteOffset;
		for(const auto& guardPair : _trans->guard().discreteGuard){
			carl::Interval<Number> guardInterval = carl::Interval<Number>::unboundedInterval();
			carl::Interval<Number> substitution(0);
			//std::cout << "Guard row: " << guardPair.second << std::endl;
			// insert all current discrete assignments except the constrained one.
			for(unsigned colIndex = 0; colIndex < guardPair.second.cols()-1; ++colIndex){
				if(colIndex != VariablePool::getInstance().id(guardPair.first)-dOffset) {
					substitution += guardPair.second(0, colIndex) * _state.discreteAssignment.at(vpool.carlVarByIndex(colIndex+dOffset));
				}
			}
			carl::Interval<Number> constPart(guardPair.second(0,guardPair.second.cols()-1));
			substitution += constPart;
			//std::cout << "substitution interval " << substitution << std::endl;
			if(guardPair.second(0,vpool.id(guardPair.first)-dOffset) > 0){
				assert(guardPair.second(0,vpool.id(guardPair.first)-dOffset) == 1);
				guardInterval.setUpperBound(-substitution.lower(),carl::BoundType::WEAK);
				//std::cout << "After setting upper bound new: " << guardInterval << std::endl;
			} else {
				assert(guardPair.second(0,vpool.id(guardPair.first)-dOffset) == -1);
				guardInterval.setLowerBound(substitution.upper(), carl::BoundType::WEAK);
				//std::cout << "After setting lower bound new: " << guardInterval << std::endl;
			}

			//std::cout << "Guard Interval: " << guardInterval << std::endl;
			//std::cout << "Current assignment: " << _state.discreteAssignment.at(guardPair.first) << std::endl;
			//std::cout << "Intersected: " << _state.discreteAssignment.at(guardPair.first).intersect(guardInterval) << std::endl;

			if(_state.discreteAssignment.find(guardPair.first) != _state.discreteAssignment.end()) {
				result.discreteAssignment[guardPair.first] = _state.discreteAssignment.at(guardPair.first).intersect(guardInterval);
			} else {
				// set discrete assignment to match invariant.
				result.discreteAssignment[guardPair.first] = guardInterval;
			}
			if(result.discreteAssignment[guardPair.first].isEmpty()){
				#ifdef REACH_DEBUG
				std::cout << "Valuation violates discrete guard." << std::endl;
				#endif
				return false;
			}
		}

		/*
		// handle discrete reset assignment
		typename Transition<Number>::Reset reset = _trans->reset();
		assert(unsigned(reset.discreteMat.rows()) == result.discreteAssignment.size());
		std::map<carl::Variable, carl::Interval<Number>> guardSatisfyingDiscreteAssingment = result.discreteAssignment;
		for(unsigned rowIndex = 0; rowIndex < reset.discreteMat.rows(); ++rowIndex) {
			carl::Interval<Number> newAssignment(0);
			for(unsigned colIndex = 0; colIndex < reset.discreteMat.cols(); ++colIndex) {
				newAssignment += reset.discreteMat(rowIndex,colIndex) * guardSatisfyingDiscreteAssingment.at(vpool.carlVarByIndex(colIndex+reset.discreteOffset));
			}
			newAssignment += carl::Interval<Number>(reset.discreteVec(rowIndex));
			//std::cout << "Discrete Assignment: " << vpool.carlVarByIndex(rowIndex+reset.discreteOffset) << " set to " << newAssignment << std::endl;
			result.discreteAssignment[vpool.carlVarByIndex(rowIndex+reset.discreteOffset)] = newAssignment;
		}

		// At this point the discrete guard is satisfied and the result state contains all discrete assignments satisfying this guard -> verify against target location invariant.
		for(const auto& invariantPair : _trans->target()->invariant().discreteInvariant ) {
			carl::Interval<Number> invariant = carl::Interval<Number>::unboundedInterval();
			carl::Interval<Number> substitution(0);
			unsigned dOffset = _trans->target()->invariant().discreteOffset;
			//std::cout << "Guard row: " << guardPair.second << std::endl;
			// insert all current discrete assignments except the constrained one.
			for(unsigned colIndex = 0; colIndex < invariantPair.second.cols()-1; ++colIndex){
				if(colIndex != vpool.id(invariantPair.first)-dOffset) {
					substitution += invariantPair.second(0, colIndex) * result.discreteAssignment.at(vpool.carlVarByIndex(colIndex+dOffset));
				}
			}
			carl::Interval<Number> constPart(invariantPair.second(0,invariantPair.second.cols()-1));
			substitution += constPart;
			//std::cout << "substitution interval " << substitution << std::endl;
			if(invariantPair.second(0,vpool.id(invariantPair.first)-dOffset) > 0){
				assert(invariantPair.second(0,vpool.id(invariantPair.first)-dOffset) == 1);
				invariant.setUpperBound(-substitution.lower(),carl::BoundType::WEAK);
				//std::cout << "After setting upper bound new: " << invariant << std::endl;
			} else {
				assert(invariantPair.second(0,vpool.id(invariantPair.first)-dOffset) == -1);
				invariant.setLowerBound(substitution.upper(), carl::BoundType::WEAK);
				//std::cout << "After setting lower bound new: " << invariant << std::endl;
			}

			if(!invariant.intersectsWith(result.discreteAssignment.at(invariantPair.first))) {
#ifdef REACH_DEBUG
				std::cout << "Valuation invalidates discrete target location invariant." << std::endl;
#endif
				return false;
			}
		}
		*/

		// check for continuous set guard intersection
		std::pair<bool, Representation> guardSatisfyingSet = boost::get<Representation>(_state.set).satisfiesHalfspaces( _trans->guard().mat, _trans->guard().vec );
		// check if the intersection is empty
		if ( guardSatisfyingSet.first ) {
			#ifdef REACH_DEBUG
			std::cout << "Transition enabled!" << std::endl;
			#endif
			result.set = guardSatisfyingSet.second;
			//std::cout << "Guard satisfying set: " <<  guardSatisfyingSet.second << std::endl;
			return true;
			/*
			// apply reset function to guard-satisfying set.
			//std::cout << "Apply reset: " << _trans->reset().mat << " " << _trans->reset().vec << std::endl;
			Representation tmp = guardSatisfyingSet.second.linearTransformation( _trans->reset().mat, _trans->reset().vec );
			std::pair<bool, Representation> invariantSatisfyingSet = tmp.satisfiesHalfspaces(_trans->target()->invariant().mat, _trans->target()->invariant().vec);
			if(invariantSatisfyingSet.first){
				result.set = invariantSatisfyingSet.second;
				return true;
			}
			#ifdef REACH_DEBUG
			std::cout << "Valuation invalidates continuous target location invariant." << std::endl;
			#endif
			return false;
			*/
		} else {
			#ifdef REACH_DEBUG
			std::cout << "Continuous guard invalidated." << std::endl;
			#endif
			return false;
		}
	}

	template<typename Number, typename Representation>
	void Reach<Number,Representation>::processDiscreteBehaviour( const std::vector<boost::tuple<Transition<Number>*, State<Number>>>& _newInitialSets ) {
		std::map<Transition<Number>*, std::vector<State<Number>>> toAggregate;
		VariablePool& vpool = VariablePool::getInstance();

		for(const auto& tuple : _newInitialSets ) {
			if(boost::get<0>(tuple)->aggregation() == Aggregation::none){
				// copy state - as there is no aggregation, the containing set and timestamp is already valid
				State<Number> s = boost::get<1>(tuple);
				assert(!s.timestamp.isUnbounded());
				s.location = boost::get<0>(tuple)->target();
				bool duplicate = false;
				for(const auto stateTuple : mWorkingQueue) {
					if(boost::get<1>(stateTuple) == s){
						duplicate = true;
						break;
					}
				}
				if(!duplicate){
					mWorkingQueue.emplace_back(mCurrentLevel+1, s);
				}
			} else { // aggregate all
				// TODO: Note that all sets are collected for one transition, i.e. currently, if we intersect the guard for one transition twice with
				// some sets in between not satisfying the guard, we still collect all guard satisfying sets for that transition.
				if(toAggregate.find(boost::get<0>(tuple)) == toAggregate.end()){
					toAggregate[boost::get<0>(tuple)] = std::vector<State<Number>>();
				}
				toAggregate[boost::get<0>(tuple)].push_back(boost::get<1>(tuple));
			}
		}

		// aggregation - TODO: add options for clustering.
		for(const auto& aggregationPair : toAggregate){
			assert(!aggregationPair.second.empty());
			carl::Interval<Number> aggregatedTimestamp = aggregationPair.second.begin()->timestamp;
			//std::cout << "Aggregated timestamp before aggregation " << aggregatedTimestamp << std::endl;
			Representation collectedSets = boost::get<Representation>(aggregationPair.second.begin()->set);
			for(auto stateIt = ++aggregationPair.second.begin(); stateIt != aggregationPair.second.end(); ++stateIt){
				assert(!stateIt->timestamp.isUnbounded());
				aggregatedTimestamp = aggregatedTimestamp.convexHull(stateIt->timestamp);
				//std::cout << "New timestamp: " << aggregatedTimestamp << std::endl;
				collectedSets = collectedSets.unite(boost::get<Representation>(stateIt->set));
			}

			#ifdef REACH_DEBUG
			std::cout << "Unified " << aggregationPair.second.size() << " sets for aggregation." << std::endl;
			#endif

			State<Number> s;
			s.location = aggregationPair.first->target();

			// reduce new initial sets.
			//collectedSets.removeRedundancy();

			s.set = collectedSets;
			s.timestamp = aggregatedTimestamp;
			//std::cout << "Aggregate " << aggregationPair.second.size() << " sets." << std::endl;
			//std::cout << "Aggregated representation: " << collectedSets << std::endl;
			//std::cout << "Aggregated timestamp: " << aggregatedTimestamp << std::endl;

			// Perform resets - discrete and continuous.

			// ASSUMPTION: All discrete assignments are the same for this transition.
			typename Transition<Number>::Reset reset = aggregationPair.first->reset();
			//std::cout << "Discrete assignment size: " << aggregationPair.second.begin()->discreteAssignment.size() << " and reset matrix " << reset.discreteMat << std::endl;
			assert(unsigned(reset.discreteMat.rows()) == aggregationPair.second.begin()->discreteAssignment.size());
			for(unsigned rowIndex = 0; rowIndex < reset.discreteMat.rows(); ++rowIndex) {
				carl::Interval<Number> newAssignment(0);
				for(unsigned colIndex = 0; colIndex < reset.discreteMat.cols(); ++colIndex) {
					// ATTENTION: Here the assumption takes place that every state for that transition has the same discrete assignment.
					newAssignment += reset.discreteMat(rowIndex,colIndex) * aggregationPair.second.begin()->discreteAssignment.at(vpool.carlVarByIndex(colIndex+reset.discreteOffset));
				}
				newAssignment += carl::Interval<Number>(reset.discreteVec(rowIndex));
				//std::cout << "Discrete Assignment: " << vpool.carlVarByIndex(rowIndex+reset.discreteOffset) << " set to " << newAssignment << std::endl;
				s.discreteAssignment[vpool.carlVarByIndex(rowIndex+reset.discreteOffset)] = newAssignment;
			}
			//std::cout << "Discrete assignment size: " << s.discreteAssignment.size() << " and reset matrix " << reset.discreteMat << std::endl;
			assert(unsigned(reset.discreteMat.rows()) == s.discreteAssignment.size());

			// check discrete invariant of target location

			// At this point the discrete guard is satisfied and the result state contains all discrete assignments satisfying this guard -> verify against target location invariant.
			bool discreteInvariantInvalidated = false;
			for(const auto& invariantPair : aggregationPair.first->target()->invariant().discreteInvariant ) {
				carl::Interval<Number> invariant = carl::Interval<Number>::unboundedInterval();
				carl::Interval<Number> substitution(0);
				unsigned dOffset = aggregationPair.first->target()->invariant().discreteOffset;
				//std::cout << "Guard row: " << guardPair.second << std::endl;
				// insert all current discrete assignments except the constrained one.
				for(unsigned colIndex = 0; colIndex < invariantPair.second.cols()-1; ++colIndex){
					if(colIndex != vpool.id(invariantPair.first)-dOffset) {
						substitution += invariantPair.second(0, colIndex) * s.discreteAssignment.at(vpool.carlVarByIndex(colIndex+dOffset));
					}
				}
				carl::Interval<Number> constPart(invariantPair.second(0,invariantPair.second.cols()-1));
				substitution += constPart;
				//std::cout << "substitution interval " << substitution << std::endl;
				if(invariantPair.second(0,vpool.id(invariantPair.first)-dOffset) > 0){
					assert(invariantPair.second(0,vpool.id(invariantPair.first)-dOffset) == 1);
					invariant.setUpperBound(-substitution.lower(),carl::BoundType::WEAK);
					//std::cout << "After setting upper bound new: " << invariant << std::endl;
				} else {
					assert(invariantPair.second(0,vpool.id(invariantPair.first)-dOffset) == -1);
					invariant.setLowerBound(substitution.upper(), carl::BoundType::WEAK);
					//std::cout << "After setting lower bound new: " << invariant << std::endl;
				}

				if(!invariant.intersectsWith(s.discreteAssignment.at(invariantPair.first))) {
					#ifdef REACH_DEBUG
					std::cout << "Valuation invalidates discrete target location invariant." << std::endl;
					#endif
					discreteInvariantInvalidated = true;
					break;
				}
			}

			if(!discreteInvariantInvalidated) {
				#ifdef REACH_DEBUG
				std::cout << "Apply resets." << std::endl;
				#endif
				Representation tmp = collectedSets.linearTransformation(  aggregationPair.first->reset().mat,  aggregationPair.first->reset().vec );
				std::pair<bool, Representation> invariantSatisfyingSet = tmp.satisfiesHalfspaces(aggregationPair.first->target()->invariant().mat, aggregationPair.first->target()->invariant().vec);
				if(invariantSatisfyingSet.first){
					//unsigned tmp = Plotter<Number>::getInstance().addObject(invariantSatisfyingSet.second.vertices());
					//Plotter<Number>::getInstance().setObjectColor(tmp, colors[orange]);
					s.set = invariantSatisfyingSet.second;
					//std::cout << "Transformed, collected set (intersected with invariant): " << invariantSatisfyingSet.second << std::endl;
				} else {
					continue;
				}

				// find duplicate entries in work queue.
				bool duplicate = false;
				for(const auto stateTuple : mWorkingQueue) {
					if(boost::get<1>(stateTuple) == s){
						duplicate = true;
						break;
					}
				}
				if(!duplicate){
					#ifdef REACH_DEBUG
					std::cout << "Enqueue " << s << " for level " << mCurrentLevel+1 << std::endl;
					#endif
					mWorkingQueue.emplace_back(mCurrentLevel+1, s);
				}
			}
		}
	}

	template<typename Number, typename Representation>
	bool Reach<Number,Representation>::checkTransitions(const State<Number>& state, const carl::Interval<Number>& currentTime, std::vector<boost::tuple<Transition<Number>*, State<Number>>>& nextInitialSets) const {
		bool timeTriggeredTransitionEnabled = false;
		State<Number> guardSatisfyingState;
		for( auto transition : state.location->transitions() ){
			// handle time-triggered transitions
			if(transition->isTimeTriggered()){
				#ifdef REACH_DEBUG
				std::cout << "Checking timed transition " << transition->source()->id() << " -> " << transition->target()->id() << " for time interval " << currentTime << std::endl;
				#endif
				// check if time trigger is enabled
				if( currentTime.contains(transition->triggerTime()) ){
					//std::cout << "Time trigger enabled" << std::endl;
					if(intersectGuard(transition, state, guardSatisfyingState)){
						// when taking a timed transition, reset timestamp
						//std::cout << "Time triggered transition enabled!" << std::endl;
						guardSatisfyingState.timestamp = carl::Interval<Number>(0);
						nextInitialSets.emplace_back(transition, guardSatisfyingState);
						timeTriggeredTransitionEnabled = true;
					}
				}
			} // handle normal transitions
			else if(intersectGuard(transition, state, guardSatisfyingState)){
				//std::cout << "hybrid transition enabled" << std::endl;
				//std::cout << *transition << std::endl;
				assert(guardSatisfyingState.timestamp == state.timestamp);
				// when a guard is satisfied here, as we do not have dynamic behaviour, avoid calculation of flowpipe
				assert(!guardSatisfyingState.timestamp.isUnbounded());
				nextInitialSets.emplace_back(transition, guardSatisfyingState);
			}
		}
		return timeTriggeredTransitionEnabled;
	}

} // namespace reachability
} // namespace hypro
