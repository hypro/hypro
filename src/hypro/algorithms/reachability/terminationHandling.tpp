

namespace hypro {
namespace reachability {

	template<typename Number, typename Representation>
	bool Reach<Number,Representation>::intersectBadStates( const State<Number>& _state, const Representation& _segment ) const {
		assert(!_state.timestamp.isUnbounded());
		// check local bad states TODO: Note, we currently allow only one bad state per location -> allow multiple bad states!
		auto badStateIterator = mAutomaton.localBadStates().find(_state.location);
		if(badStateIterator != mAutomaton.localBadStates().end()){
			if(_segment.satisfiesHalfspaces(badStateIterator->second.set.first, badStateIterator->second.set.second).first == true){
				#ifdef REACH_DEBUG
				std::cout << "Intersection with all local bad states" << std::endl;
				#endif
				mIntersectedBadStates = true;
				return true;
			}
			#ifdef REACH_DEBUG
			std::cout << "No intersection with local bad states" << std::endl;
			#endif
		}

		// check global bad states
		if(!mAutomaton.globalBadStates().empty()){
			for(const auto& set : mAutomaton.globalBadStates() ) {
				// bad state intersection
				if(_segment.satisfiesHalfspaces(set.first, set.second).first){
					#ifdef REACH_DEBUG
					std::cout << "Intersection with global bad states" << std::endl;
					#endif
					mIntersectedBadStates = true;
					return true;
				}
			}
		}
		return false;
	}

} // namespace reachability
} // namespace hypro
