#pragma once

#include "discreteGuardHandler.h"
#include "ltiGuardHandler.h"
#include "timedGuardHandler.h"

namespace hypro {

    struct guardHandlerSorter{

        template<typename Number>
		inline bool operator()(IGuardHandler<Number>* lhs, IGuardHandler<Number>* rhs){
			return lhs->getSortIndex() < rhs->getSortIndex();
		}
	};

} // hypro