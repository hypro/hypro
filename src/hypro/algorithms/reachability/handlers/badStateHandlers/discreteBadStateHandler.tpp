#include "discreteBadStateHandler.h"

namespace hypro {
template <typename State>
void discreteBadStateHandler<State>::handle() {
	ltiBadStateHandler<State>::handle();
	this->mMarkedForDelete = true;
}
}  // namespace hypro
