#pragma once

#include "Reset.h"

namespace hypro {

template <typename Number, typename Representation, typename... Rargs>
State<Number, Representation, Rargs...> applyReset( const State<Number, Representation, Rargs...>& inState, const Reset<Number>& reset ) {
	TRACE( "hypro.datastructures", "inState #sets: " << inState.getNumberSets() << " and #resets: " << reset.size() );
	assert( reset.empty() || inState.getNumberSets() == reset.size() );
	if ( reset.empty() ) {
		DEBUG( "hypro.datastructures", "Reset is empty." );
		return inState;
	}
	auto res = inState;
	for ( std::size_t pos = 0; pos < reset.size(); ++pos ) {
		if ( !reset.getAffineReset( pos ).isIdentity() ) {
			res = res.applyTransformation( reset.getAffineReset( pos ).mTransformation, pos );
		}
		if ( !reset.getIntervalReset( pos ).isIdentity() ) {
			res = res.partialIntervalAssignment( reset.getIntervalReset( pos ).mIntervals, pos );
		}
	}

	return res;
}

template <class Number, class R, class... Rs>
std::string printSet( State<Number, R, Rs...> const& state, size_t index = 0 ) {
	std::stringstream s_stream{};
	state.visit(index, [&](auto&& set) {
		s_stream << set;
	});
	return s_stream.str();
}

}  // namespace hypro
