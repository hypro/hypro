#include "discreteGuardHandler.h"

namespace hypro {
    template <class Representation,typename Number>
	void discreteGuardHandler<Representation,Number>::reinitialize(){
		// only reinitialize on the first time we come here
		if(mComputed){
			return;
		}
		ltiGuardHandler<Representation,Number>::reinitialize();
	}

	template <class Representation,typename Number>
	void discreteGuardHandler<Representation,Number>::handle() {
		if(mComputed){
			TRACE("hydra.worker.discrete","No flow invariant handler already computed");	
			return;
		}
		TRACE("hydra.worker.discrete","Applying handler " << this->handlerName());	
		ltiGuardHandler<Representation,Number>::handle();
		mComputed=true;
	}
} // hypro