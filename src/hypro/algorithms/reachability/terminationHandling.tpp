

namespace hypro {
namespace reachability {

	template<typename Number>
	bool Reach<Number>::intersectBadStates( const State_t<Number>& _state ) const {
		assert(!_state.getTimestamp().isUnbounded());
		// check local bad states TODO: Note, we currently allow only one bad state per location -> allow multiple bad states!
		auto badStateIterator = mAutomaton.getLocalBadStates().find(_state.getLocation());
		if(badStateIterator != mAutomaton.getLocalBadStates().end()){
			if(_state.satisfies(badStateIterator->second).first == true){
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
		if(!mAutomaton.getGlobalBadStates().empty()){
			for(const auto& set : mAutomaton.getGlobalBadStates() ) {
				// bad state intersection
				if(_state.satisfies(set).first){
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
