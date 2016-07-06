#include "z3Context.h"

namespace z3
{
	z3::expr real_val (mpq_class val) {
		return this->real_val(carl::toString(carl::convert<Number,hypro::Rational>(_objective(colIndex))).c_str()); // hack for now
		// problem: z3 wraps mpq using a "rational" class. we can't directly use mpq_class but need the value of mpq_class. There is no
		// public member function doing this
	}
}