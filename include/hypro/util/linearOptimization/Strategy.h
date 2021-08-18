#pragma once

namespace hypro {

enum OptimizerStrategy {
#ifdef HYPRO_USE_SMTRAT
	SMTRAT,
#endif
#ifdef HYPRO_USE_SOPLEX
	SOPLEX,
#endif
#ifdef HYPRO_USE_Z3
	SMTRAT,
#endif
	GLPK
};

}  // namespace hypro
