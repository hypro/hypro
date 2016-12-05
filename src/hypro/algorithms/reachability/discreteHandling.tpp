#include "util/Plotter.h"

namespace hypro {
namespace reachability {
	template<typename Number, typename Representation>
	bool Reach<Number,Representation>::intersectGuard( Transition<Number>* _trans, const State<Number>& _state,
							   State<Number>& result ) const {
		assert(!_state.timestamp.isUnbounded());
		result = _state;

		// check for continuous set guard intersection
		std::pair<bool, Representation> guardSatisfyingSet = boost::get<Representation>(_state.set).satisfiesHalfspaces( _trans->guard().mat, _trans->guard().vec );

		// check if the intersection is empty
		if ( guardSatisfyingSet.first ) {
			#ifdef REACH_DEBUG
			std::cout << "Transition enabled!" << std::endl;
			#endif
			result.set = guardSatisfyingSet.second;
			return true;
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
			std::cout << "Unified " << aggregationPair.second.size() << " sets for aggregation:" << std::endl << collectedSets << std::endl;
			//std::cout << "CollectedSets vertices: " << std::endl;
			//for(const auto& vertex : collectedSets.vertices()) {
			//	std::cout << convert<Number,double>(vertex) << std::endl;
			//}
			#endif

			State<Number> s;
			s.location = aggregationPair.first->target();

			// reduce new initial sets.
			//collectedSets.removeRedundancy();
			#ifdef USE_SMART_AGGREGATION
			aggregationReduction(collectedSets, aggregationPair.first, mSettings.timeBound, mSettings.timeStep);
			#endif
			s.set = collectedSets;

			s.timestamp = aggregatedTimestamp;
			//std::cout << "Aggregate " << aggregationPair.second.size() << " sets." << std::endl;
			//std::cout << "Aggregated representation: " << collectedSets << std::endl;
			//std::cout << "Aggregated timestamp: " << aggregatedTimestamp << std::endl;

			// Perform resets.
			typename Transition<Number>::Reset reset = aggregationPair.first->reset();
			#ifdef REACH_DEBUG
			std::cout << "Apply resets." << std::endl;
			std::cout << "Matrix: " << std::endl << aggregationPair.first->reset().mat << std::endl << "Vector " << std::endl << aggregationPair.first->reset().vec << std::endl;
			#endif
			Representation tmp = collectedSets.affineTransformation(aggregationPair.first->reset().mat,  aggregationPair.first->reset().vec);
			//std::cout << "Vertices after reset: " << std::endl;
			//for(const auto& vertex : tmp.vertices()) {
			//	std::cout << convert<Number,double>(vertex) << std::endl;
			//}
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

	template<typename Number, typename Representation>
	bool Reach<Number,Representation>::checkTransitions(const State<Number>& state, const carl::Interval<Number>& , std::vector<boost::tuple<Transition<Number>*, State<Number>>>& nextInitialSets) const {
		State<Number> guardSatisfyingState;
		bool transitionEnabled = false;
		for( auto transition : state.location->transitions() ){
			// handle time-triggered transitions
			if(intersectGuard(transition, state, guardSatisfyingState)){
				//std::cout << "hybrid transition enabled" << std::endl;
				//std::cout << *transition << std::endl;
				assert(guardSatisfyingState.timestamp == state.timestamp);
				// when a guard is satisfied here, as we do not have dynamic behaviour, avoid calculation of flowpipe
				assert(!guardSatisfyingState.timestamp.isUnbounded());
				#ifdef USE_FORCE_REDUCTION
				appylReduction(boost::get<Representation>(guardSatisfyingState.set));
				#endif
				nextInitialSets.emplace_back(transition, guardSatisfyingState);
			}
		}
		return transitionEnabled;
	}

} // namespace reachability
} // namespace hypro
