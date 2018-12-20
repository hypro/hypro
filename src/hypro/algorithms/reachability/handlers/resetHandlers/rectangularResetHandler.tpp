#include "rectangularResetHandler.h"

namespace hypro {
    template<typename State>
	void rectangularResetHandler<State>::handle() {
        TRACE("hydra.worker","Applying Reset trafo for subspace " << mIndex);
        assert(mState->getSetType(mIndex) == representation_name::carl_polytope);
        mState->partialIntervalAssignment(mIntervalResets,mIndex);
    }
} // hypro
