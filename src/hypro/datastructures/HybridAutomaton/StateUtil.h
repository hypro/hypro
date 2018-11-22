#include "Reset.h"

namespace hypro {

    template<typename Number, typename Representation, typename ...Rargs>
	State<Number,Representation,Rargs...> applyReset(const State<Number,Representation,Rargs...>& inState, const Reset<Number>& reset) {
        TRACE("hydra.datastructures","inState #sets: " << inState.getNumberSets() << " and #resets: " << reset.size());
		assert(reset.empty() || inState.getNumberSets() == reset.size());
		if(reset.empty()) {
			return inState;
		}
		return inState.applyTransformation(reset.getResetTransformations());
    }

} // hypro
