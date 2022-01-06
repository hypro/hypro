#include "rectangularFirstSegmentHandler.h"

namespace hypro {
template <typename State>
void rectangularFirstSegmentHandler<State>::handle() {
	// do nothing, just extract flow
	mFlow = mState.getLocation()->getRectangularFlow( mIndex );
}
}  // namespace hypro
