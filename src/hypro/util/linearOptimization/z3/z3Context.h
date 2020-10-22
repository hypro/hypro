#pragma once
#include "../../../flags.h"
#ifdef HYPRO_USE_Z3
#include <carl/numbers/numbers.h>
#include <gmpxx.h>
#include <z3++.h>

namespace hypro {
/**
 * @brief Class storing the context when using z3 as a linear optimization backend
 *
 */
class z3Context : public z3::context {
  public:
	z3Context() {}
	~z3Context() {}

	/*
	 * z3::real_val extension for mpq_class values
	 */
	z3::expr real_val( mpq_class val );
};
}  // namespace hypro

#endif	// HYPRO_USE_Z3
