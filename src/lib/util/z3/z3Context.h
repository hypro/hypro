#pragma once
#include "../../flags.h"
#ifdef HYPRO_USE_Z3
#include <gmpxx.h>
#include <z3++.h>
#include <carl/numbers/numbers.h>

namespace hypro {
	class z3Context : public z3::context
	{
	public:
		z3Context() {}
		~z3Context() {}

		/*
		 * z3::real_val extension for mpq_class values
		 */
		z3::expr real_val (mpq_class val);
	};
}

#endif // HYPRO_USE_Z3
