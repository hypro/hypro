#include "rectangularResetHandler.h"

namespace hypro {
    template<typename State>
	void rectangularResetHandler<State>::handle() {
        TRACE("hypro.worker","Applying Reset trafo for subspace " << mIndex);
        assert(mState->getSetType(mIndex) == representation_name::carl_polytope);
        auto res = mState->partialIntervalAssignment(mIntervalResets,mIndex);
        // temporary
        mState->partiallyReduceRepresentation(mIndex);
        mState->setSetDirect(res.getSet(mIndex),mIndex);
        mState->setSetType(res.getSetType(mIndex),mIndex);
    }
} // hypro
