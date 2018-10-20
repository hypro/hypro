#include "discreteInvariantHandler.h"

namespace hypro {
    template <class Representation,typename Number>
	void discreteInvariantHandler<Representation,Number>::handle() {
		ltiInvariantHandler<Representation,Number>::handle();
		// only compute once
		this->mMarkedForDelete = true;
	}	
} // hypro