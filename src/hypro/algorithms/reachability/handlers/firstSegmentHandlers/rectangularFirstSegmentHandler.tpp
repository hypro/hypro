#include "rectangularFirstSegmentHandler.h"

namespace hypro
{
    template<typename State>
    void rectangularFirstSegmentHandler<State>::handle() {
        // do nothing, just extract flow
        assert(getFlowType(mState->getLocation()->getFlow(mIndex)) == DynamicType::rectangular);
        mFlow = mState->getLocation()->getFlow(mIndex);
    }
} // hypro
