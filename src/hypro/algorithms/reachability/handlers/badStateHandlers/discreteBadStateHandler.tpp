#include "discreteBadStateHandler.h"

namespace hypro
{
    template <class Representation,typename Number>
	void discreteBadStateHandler<Representation,Number>::handle() {
		ltiBadStateHandler<Representation,Number>::handle();
		this->mMarkedForDelete = true;
	}
} // hypro
