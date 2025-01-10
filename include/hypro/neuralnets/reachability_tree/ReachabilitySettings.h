#pragma once

#include "../../util/type_handling/better_enums/enum_default_ctor.h"

namespace hypro {

BETTER_ENUM( BACKPROPAGATION_STRATEGY, int, DEFAULT,
			 SINGLESTEP, BINARYSEARCH, REMEMBERING_SEARCH, EXACT_SOURCES
);

BETTER_ENUM( COUNTEREXAMPLE_STRATEGY, int, DEFAULT,
			 Z3_BASIC, RANDOM, Z3_SMALL_REPRESENTATION 
);

BETTER_ENUM( REFINEMENT_TYPE, int, DEFAULT,
			 AVOIDANT, FULL  
);

}  // namespace hypro
