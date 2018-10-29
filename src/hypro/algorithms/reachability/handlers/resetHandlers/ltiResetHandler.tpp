#include "ltiResetHandler.h"

namespace hypro {
    template <class Representation,typename Number>
	void ltiResetHandler<Representation,Number>::handle() {         
        TRACE("hydra.worker","Applying Reset trafo: \n" << mTrafo << "\n Reset translation: \n"<< mTranslation << "to" << mIndex);
        State_t<Number> res = mState->partiallyApplyTransformation(hypro::ConstraintSet<Number>(mTrafo, mTranslation), mIndex);
        mState->setSetDirect(res.getSet(mIndex),mIndex);
        mState->setSetType(res.getSetType(mIndex),mIndex); 
    }
} // hypro