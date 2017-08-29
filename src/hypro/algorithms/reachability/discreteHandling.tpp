
namespace hypro {
namespace reachability {
	template<typename Number>
	bool Reach<Number>::intersectGuard( Transition<Number>* _trans, const State_t<Number>& _state,
							   State_t<Number>& result ) const {
		assert(!_state.timestamp.isUnbounded());
		result = _state;

		// check for continuous set guard intersection
		std::pair<bool, State_t<Number>> guardSatisfyingSet = _state.satisfies( _trans->getGuard() );

		// check if the intersection is empty
		if ( guardSatisfyingSet.first ) {
			#ifdef REACH_DEBUG
			std::cout << "Transition enabled!" << std::endl;
			#endif

			//for(unsigned rowIndex = 0; rowIndex < _trans->guard().mat.rows(); ++rowIndex) {
			//	Halfspace<Number> tmp( vector_t<Number>(_trans->guard().mat.row(rowIndex)), _trans->guard().vec(rowIndex));
			//	Plotter<Number>::getInstance().addObject( tmp );
			//}

			result.set = guardSatisfyingSet.second;
			return true;
		} else {
			#ifdef REACH_DEBUG
			std::cout << "Continuous guard invalidated." << std::endl;
			#endif
			return false;
		}
	}

	template<typename Number>
	void Reach<Number>::processDiscreteBehaviour( const std::vector<boost::tuple<Transition<Number>*, State_t<Number>>>& _newInitialSets ) {
		std::map<Transition<Number>*, std::vector<State_t<Number>>> toAggregate;

		for(const auto& tuple : _newInitialSets ) {
			if(boost::get<0>(tuple)->getAggregation() == Aggregation::none){
				// copy state - as there is no aggregation, the containing set and timestamp is already valid
				State_t<Number> s = boost::get<1>(tuple);
				assert(!s.getTimestamp().isUnbounded());
				s.location = boost::get<0>(tuple)->getTarget();
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
					toAggregate[boost::get<0>(tuple)] = std::vector<State_t<Number>>();
				}
				toAggregate[boost::get<0>(tuple)].push_back(boost::get<1>(tuple));
			}
		}

		// aggregation - TODO: add options for clustering.
		for(const auto& aggregationPair : toAggregate){
			assert(!aggregationPair.second.empty());
			carl::Interval<Number> aggregatedTimestamp = aggregationPair.second.begin()->getTimestamp();
			//std::cout << "Aggregated timestamp before aggregation " << aggregatedTimestamp << std::endl;
			State_t<Number> collectedSets = aggregationPair.second.begin();
			for(auto stateIt = ++aggregationPair.second.begin(); stateIt != aggregationPair.second.end(); ++stateIt){
				assert(!stateIt->getTimestamp().isUnbounded());
				aggregatedTimestamp = aggregatedTimestamp.convexHull(stateIt->getTimestamp());
				//std::cout << "New timestamp: " << aggregatedTimestamp << std::endl;
				collectedSets = collectedSets.aggregate(*stateIt);
			}

			#ifdef REACH_DEBUG
			std::cout << "Unified " << aggregationPair.second.size() << " sets for aggregation:" << std::endl << collectedSets << std::endl;
			//std::cout << "CollectedSets vertices: " << std::endl;
			//for(const auto& vertex : collectedSets.vertices()) {
			//	std::cout << convert<Number,double>(vertex) << std::endl;
			//}
			#endif

			State_t<Number> s;
			s.setLocation(aggregationPair.first->getTarget());

			// reduce new initial sets.
			//collectedSets.removeRedundancy();
			#ifdef USE_SMART_AGGREGATION
			aggregationReduction(collectedSets, aggregationPair.first, mSettings.timeBound, mSettings.timeStep);
			#endif
			s.setSet(collectedSets);

			//unsigned colSetIndex = Plotter<Number>::getInstance().addObject(collectedSets.vertices());
			//Plotter<Number>::getInstance().setObjectColor(colSetIndex, plotting::colors[plotting::red]);


			s.setTimestamp(aggregatedTimestamp);
			//std::cout << "Aggregate " << aggregationPair.second.size() << " sets." << std::endl;
			//std::cout << "Aggregated representation: " << collectedSets << std::endl;
			//std::cout << "Aggregated timestamp: " << aggregatedTimestamp << std::endl;

			// Perform resets.
			typename Transition<Number>::Reset reset = aggregationPair.first->getReset();
			#ifdef REACH_DEBUG
			std::cout << "Apply resets." << std::endl;
			std::cout << "Matrix: " << std::endl << aggregationPair.first->getReset().getMatrix() << std::endl << "Vector " << std::endl << aggregationPair.first->getReset().getVector() << std::endl;
			#endif
			State_t<Number> tmp = aggregationPair.first->getReset().applyReset(collectedSets);
			//std::cout << "Vertices after reset: " << std::endl;
			//for(const auto& vertex : tmp.vertices()) {
			//	std::cout << convert<Number,double>(vertex) << std::endl;
			//}
			std::pair<bool, State_t<Number>> invariantSatisfyingSet = tmp.satisfies(aggregationPair.first->getTarget()->getInvariant());
			if(invariantSatisfyingSet.first){
				//unsigned tmp = Plotter<Number>::getInstance().addObject(invariantSatisfyingSet.second.vertices());
				//Plotter<Number>::getInstance().setObjectColor(tmp, colors[orange]);
				s.setSet(invariantSatisfyingSet.second);
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

	template<typename Number>
	bool Reach<Number>::checkTransitions(const State_t<Number>& state, const carl::Interval<Number>& , std::vector<boost::tuple<Transition<Number>*, State_t<Number>>>& nextInitialSets) const {
		State_t<Number> guardSatisfyingState;
		bool transitionEnabled = false;
		for( auto transition : state.getLocation()->getTransitions() ){
			// handle time-triggered transitions
			if(intersectGuard(transition, state, guardSatisfyingState)){
				//std::cout << "hybrid transition enabled" << std::endl;
				//std::cout << *transition << std::endl;
				assert(guardSatisfyingState.getTimestamp() == state.getTimestamp());
				// when a guard is satisfied here, as we do not have dynamic behaviour, avoid calculation of flowpipe
				assert(!guardSatisfyingState.getTimestamp().isUnbounded());
				#ifdef USE_FORCE_REDUCTION
				applyReduction(guardSatisfyingState);
				#endif
				nextInitialSets.emplace_back(transition, guardSatisfyingState);
			}
		}
		return transitionEnabled;
	}

} // namespace reachability
} // namespace hypro
