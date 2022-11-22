#include <hypro/flags.h>
#ifdef HYPRO_USE_Z3
#include "hypro/util/linearOptimization/z3/z3Context.h"
namespace hypro {
z3::expr z3Context::real_val( mpq_class val ) {
	std::string valStr = val.get_str();
	assert( z3::context::real_val( valStr.c_str() ).is_real() );
	return z3::context::real_val( valStr.c_str() );	 // hack for now
													 // problem: z3 wraps mpq using a "rational" class. we can't directly use mpq_class but need the value of mpq_class. There is no
													 // public member function doing this
}
}  // namespace hypro
#endif
