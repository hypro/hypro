

namespace hypro {
namespace reachability {

template <typename Number, typename ReacherSettings, typename State>
bool Reach<Number, ReacherSettings, State>::intersectBadStates( const State& _state ) const {
	assert( !isUnbounded( _state.getTimestamp() ) );
	// check local bad states TODO: Note, we currently allow only one bad state per location -> allow multiple bad states!
	auto badStateIterator = mAutomaton.getLocalBadStates().find( _state.getLocation() );
	if ( badStateIterator != mAutomaton.getLocalBadStates().end() ) {
		if ( _state.satisfies( badStateIterator->second ).first != CONTAINMENT::NO ) {
#ifdef REACH_DEBUG
			std::cout << "Intersection with all local bad states" << std::endl;
#endif
			mIntersectedBadStates = true;
			return true;
		}
#ifdef REACH_DEBUG
		// std::cout << "No intersection with local bad states" << std::endl;
		DEBUG( "hypro.Reach", "No intersection with local bad states.\n" );
#endif
	}

	// check global bad states
	if ( !mAutomaton.getGlobalBadStates().empty() ) {
		for ( const auto& set : mAutomaton.getGlobalBadStates() ) {
			// bad state intersection
			if ( _state.satisfies( set ).first != CONTAINMENT::NO ) {
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

}  // namespace reachability
}  // namespace hypro
