#pragma once
#ifdef USE_Z3

#include <z3++.h>

namespace z3 {
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

#endif // USE_Z3
