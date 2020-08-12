#include "discreteInvariantHandler.h"

namespace hypro {
template <typename State>
void discreteInvariantHandler<State>::handle() {
	// ltiInvariantHandler<State>::handle();
	// only compute once
	this->mMarkedForDelete = true;
}
}  // namespace hypro