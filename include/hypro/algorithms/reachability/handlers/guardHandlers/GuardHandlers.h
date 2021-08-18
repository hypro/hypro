#pragma once

#include "discreteGuardHandler.h"
#include "ltiGuardHandler.h"
#include "rectangularGuardHandler.h"
#include "timedGuardHandler.h"

namespace hypro {

struct guardHandlerSorter {
	template <typename State>
	inline bool operator()( IGuardHandler<State>* lhs, IGuardHandler<State>* rhs ) {
		return lhs->getSortIndex() < rhs->getSortIndex();
	}
};

}  // namespace hypro
