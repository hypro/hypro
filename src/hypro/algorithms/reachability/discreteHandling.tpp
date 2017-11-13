
namespace hypro {
namespace reachability {
	template<typename Number>
	bool Reach<Number>::intersectGuard( Transition<Number>* _trans, const State_t<Number>& _state,
							   State_t<Number>& result ) const {

		assert(!_state.getTimestamp().isUnbounded());
		result = _state;

		//std::cout << "------ start intersecting guard!" << std::endl;

		// check for continuous set guard intersection
		std::pair<bool, State_t<Number>> guardSatisfyingSet = _state.satisfies( _trans->getGuard() );

		//std::cout << "------ guard satisfied? " << guardSatisfyingSet.first << std::endl;

		// check if the intersection is empty
		if ( guardSatisfyingSet.first ) {
			#ifdef REACH_DEBUG
			INFO("hypro.reacher", "Transition enabled!");
			#endif

			//for(unsigned rowIndex = 0; rowIndex < _trans->guard().mat.rows(); ++rowIndex) {
			//	Halfspace<Number> tmp( vector_t<Number>(_trans->guard().mat.row(rowIndex)), _trans->guard().vec(rowIndex));
			//	Plotter<Number>::getInstance().addObject( tmp );
			//}

			result.setSets(guardSatisfyingSet.second.getSets());
			//std::cout << "------ end intersecting guard!" << std::endl;
			return true;
		} else {
			#ifdef REACH_DEBUG
			INFO("hypro.reacher", "Continuous guard invalidated.");
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
				s.setLocation(boost::get<0>(tuple)->getTarget());
				bool duplicate = false;
				for(const auto stateTuple : mWorkingQueue) {
					if(boost::get<1>(stateTuple) == s){
						duplicate = true;
						break;
					}
				}
				if(!duplicate){
					mWorkingQueue.emplace_back(mCurrentLevel+1, s);
					//std::cout << "-- No duplicate state tupel found! mWorkingQueue size is now: " << mWorkingQueue.size() << std::endl;
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

			INFO("hypro.reacher", "-- Entered aggregation loop");

			assert(!aggregationPair.second.empty());
			carl::Interval<Number> aggregatedTimestamp = aggregationPair.second.begin()->getTimestamp();
			//std::cout << "Aggregated timestamp before aggregation " << aggregatedTimestamp << std::endl;
			State_t<Number> collectedSets = *aggregationPair.second.begin();
			for(auto stateIt = ++aggregationPair.second.begin(); stateIt != aggregationPair.second.end(); ++stateIt){
				assert(!stateIt->getTimestamp().isUnbounded());
				aggregatedTimestamp = aggregatedTimestamp.convexHull(stateIt->getTimestamp());
				//std::cout << "New timestamp: " << aggregatedTimestamp << std::endl;
				collectedSets = collectedSets.unite(*stateIt);
			}

			#ifdef REACH_DEBUG
			INFO("hypro.reacher", "Unified " << aggregationPair.second.size() << " sets for aggregation.");
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
			collectedSets.removeRedundancy();
			//aggregationReduction(collectedSets, aggregationPair.first, mSettings.timeBound, mSettings.timeStep);
			#endif

			//TODO: Maybe use smth else or use setSetsSave in all functions
			//s.setSetsSave(collectedSets.getSets());

			//unsigned colSetIndex = Plotter<Number>::getInstance().addObject(collectedSets.vertices());
			//Plotter<Number>::getInstance().setObjectColor(colSetIndex, plotting::colors[plotting::red]);


			s.setTimestamp(aggregatedTimestamp);
			//std::cout << "Aggregate " << aggregationPair.second.size() << " sets." << std::endl;
			//std::cout << "Aggregated representation: " << collectedSets << std::endl;
			//std::cout << "Aggregated timestamp: " << aggregatedTimestamp << std::endl;

			// Perform resets.
			State_t<Number> tmp = aggregationPair.first->getReset().applyReset(collectedSets);
			//std::cout << "Vertices after reset: " << std::endl;
			//for(const auto& vertex : tmp.vertices()) {
			//	std::cout << convert<Number,double>(vertex) << std::endl;
			//}

			std::pair<bool, State_t<Number>> invariantSatisfyingSet = tmp.satisfies(aggregationPair.first->getTarget()->getInvariant());
			if(invariantSatisfyingSet.first){
				//unsigned tmp = Plotter<Number>::getInstance().addObject(invariantSatisfyingSet.second.vertices());
				//Plotter<Number>::getInstance().setObjectColor(tmp, colors[orange]);
				//s.setSets(invariantSatisfyingSet.second.getSets());
				s.setSetsSave(invariantSatisfyingSet.second.getSets());
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
				INFO("hypro.reacher", "Enqueue " << s << " for level " << mCurrentLevel+1);
				#endif
				mWorkingQueue.emplace_back(mCurrentLevel+1, s);
			}
		}

		INFO("hypro.reacher", "After aggregation loop");
	}

	template<typename Number>
	bool Reach<Number>::checkTransitions(const State_t<Number>& state, const carl::Interval<Number>& , std::vector<boost::tuple<Transition<Number>*, State_t<Number>>>& nextInitialSets) const {

		State_t<Number> guardSatisfyingState;
		bool transitionEnabled = false;
		//std::cout << "------ how many transitions do we have? " << state.getLocation()->getTransitions().size() << std::endl;
		for( auto transition : state.getLocation()->getTransitions() ){
			DEBUG("hypro.reacher","Check transition " << transition->getSource()->getName() << " -> " << transition->getTarget()->getName() << " (@ "<< transition << ")." );
			// handle time-triggered transitions
			if(intersectGuard(transition, state, guardSatisfyingState)){
				INFO("hypro.reacher", "hybrid transition enabled");
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
