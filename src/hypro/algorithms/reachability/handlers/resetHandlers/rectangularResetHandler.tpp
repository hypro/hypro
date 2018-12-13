#include "rectangularResetHandler.h"

namespace hypro {
    template<typename State>
	void rectangularResetHandler<State>::handle() {
        TRACE("hydra.worker","Applying Reset trafo: \n" << mTrafo << "\n Reset translation: \n"<< mTranslation << "to" << mIndex);
        // linear transformations are not supported
    }
} // hypro
