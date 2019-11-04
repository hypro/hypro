
namespace hypro {
namespace reachability {
	template<typename Number, typename ReacherSettings, typename State>
	bool Reach<Number,ReacherSettings,State>::intersectGuard( Transition<Number>* _trans, const State& _state,
							   State& result ) const {

		assert(!_state.getTimestamp().isUnbounded());
		result = _state;

		// check for continuous set guard intersection
		std::pair<CONTAINMENT, State> guardSatisfyingSet = _state.satisfies( _trans->getGuard() );

		INFO("hypro.reacher","------ guard satisfied? " << guardSatisfyingSet.first);

		// check if the intersection is empty
		if ( guardSatisfyingSet.first != CONTAINMENT::NO ) {
			#ifdef REACH_DEBUG
			INFO("hypro.reacher", "Transition enabled at timestamp " << _state.getTimestamp() << "!");
			#endif

			result.setSets(guardSatisfyingSet.second.getSets());
			return true;
		} else {
			#ifdef REACH_DEBUG
			INFO("hypro.reacher", "Continuous guard invalidated.");
			#endif
			return false;
		}
	}

	template<typename Number,typename ReacherSettings, typename State>
	void Reach<Number,ReacherSettings,State>::processDiscreteBehaviour( const std::vector<boost::tuple<Transition<Number>*, State>>& _newInitialSets ) {
		std::map<Transition<Number>*, std::vector<State>> toAggregate;

		for(const auto& tuple : _newInitialSets ) {
			if(boost::get<0>(tuple)->getAggregation() == Aggregation::none){
				TRACE("hypro.reacher","No aggregation.");
				// copy state - as there is no aggregation, the containing set and timestamp is already valid
				State s = boost::get<1>(tuple);
				assert(!s.getTimestamp().isUnbounded());
				s.setLocation(boost::get<0>(tuple)->getTarget());

				s = applyReset(s,boost::get<0>(tuple)->getReset());
				std::pair<CONTAINMENT,State> invariantPair = s.satisfies(boost::get<0>(tuple)->getTarget()->getInvariant());
				if(invariantPair.first != CONTAINMENT::NO){
					TRACE("hypro.reacher","Enqueue " << invariantPair.second << " for level " << mCurrentLevel+1 << ", current queue size (before) is " << mWorkingQueue.size());
					mWorkingQueue.enqueue(std::make_unique<TaskType>(std::make_pair(mCurrentLevel+1, invariantPair.second)));
				}
			} else { // aggregate all
				// TODO: Note that all sets are collected for one transition, i.e. currently, if we intersect the guard for one transition twice with
				// some sets in between not satisfying the guard, we still collect all guard satisfying sets for that transition.
				if(toAggregate.find(boost::get<0>(tuple)) == toAggregate.end()){
					toAggregate[boost::get<0>(tuple)] = std::vector<State>();
				}
				toAggregate[boost::get<0>(tuple)].push_back(boost::get<1>(tuple));

			}
		}

		// aggregation - TODO: add options for clustering.
		for(const auto& aggregationPair : toAggregate){

			INFO("hypro.reacher", "-- Entered aggregation loop");

			assert(!aggregationPair.second.empty());
			carl::Interval<tNumber> aggregatedTimestamp = aggregationPair.second.begin()->getTimestamp();
			State collectedSets = *aggregationPair.second.begin();
			for(auto stateIt = ++aggregationPair.second.begin(); stateIt != aggregationPair.second.end(); ++stateIt){
				assert(!stateIt->getTimestamp().isUnbounded());
				aggregatedTimestamp = aggregatedTimestamp.convexHull(stateIt->getTimestamp());
				collectedSets = collectedSets.unite(*stateIt);
			}

			#ifdef REACH_DEBUG
			INFO("hypro.reacher", "Unified " << aggregationPair.second.size() << " sets for aggregation.");
			#endif

			State s;
			s.setLocation(aggregationPair.first->getTarget());

			// reduce new initial sets.
			//collectedSets.removeRedundancy();
			#ifdef USE_SMART_AGGREGATION
			collectedSets.removeRedundancy();
			if(collectedSets.getSetType(0) == representation_name::support_function) {
				// Forced reduction to a box template.
				applyReduction<Number>(boost::get<hypro::SupportFunction<Number>>(collectedSets.rGetSet(0)));
			}
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
			INFO("hypro.reacher","Apply reset.");
			State tmp = applyReset(collectedSets, aggregationPair.first->getReset());
			INFO("hypro.reacher","Vertices size after reset: " << tmp.vertices().size());
			#ifdef HYPRO_LOGGING
			for(const auto& vertex : tmp.vertices()) {
				//std::cout << convert<Number,double>(vertex) << std::endl;
				INFO("hypro.reacher", vertex << ", ");
			}
			#endif

			std::pair<CONTAINMENT, State> invariantSatisfyingSet = tmp.satisfies(aggregationPair.first->getTarget()->getInvariant());
			INFO("hypro.reacher","does resetted satisfy invariant? " << invariantSatisfyingSet.first << " size of vertices: " << invariantSatisfyingSet.second.vertices().size() << " and resulting vertices: ");
			#ifdef HYPRO_LOGGING
			for(const auto& vertex : invariantSatisfyingSet.second.vertices()) {
				//std::cout << convert<Number,double>(vertex) << std::endl;
				INFO("hypro.reacher", vertex << ", ");
			}
			#endif

			if(invariantSatisfyingSet.first != CONTAINMENT::NO){
				//unsigned tmp = Plotter<Number>::getInstance().addObject(invariantSatisfyingSet.second.vertices());
				//Plotter<Number>::getInstance().setObjectColor(tmp, colors[orange]);
				//s.setSets(invariantSatisfyingSet.second.getSets());
				s.setSetsSave(invariantSatisfyingSet.second.getSets());
				//std::cout << "Transformed, collected set (intersected with invariant): " << invariantSatisfyingSet.second << std::endl;
			} else {
				continue;
			}

			//TRACE("hypro.reacher", "Enqueue " <<  s<< " for level " << mCurrentLevel+1 << ", current queue size (before) is " << mWorkingQueue.size());
			TRACE("hypro.reacher", "Enqueue state for level " << mCurrentLevel+1 << ", current queue size (before) is " << mWorkingQueue.size());
			mWorkingQueue.enqueue(std::make_unique<TaskType>(std::make_pair(mCurrentLevel+1, s)));
		}

		INFO("hypro.reacher", "--- After aggregation loop");
	}

	template<typename Number,typename ReacherSettings, typename State>
	bool Reach<Number,ReacherSettings,State>::checkTransitions(const State& state, const carl::Interval<tNumber>& , std::vector<boost::tuple<Transition<Number>*, State>>& nextInitialSets) const {

		State guardSatisfyingState;
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
				transitionEnabled = true;
			}
		}

		return transitionEnabled;
	}

} // namespace reachability
} // namespace hypro
