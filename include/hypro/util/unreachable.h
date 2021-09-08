#pragma once

#include <boost/predef.h>

namespace hypro {
[[noreturn]] inline void unreachable() {
#if BOOST_COMP_CLANG
	__builtin_unreachable();
#elif BOOST_COMP_GNUC
	__builtin_unreachable();
#elif BOOST_COMP_MSVC
	__assume( false );
#endif
	// On other compilers we will probably get a warning
}
}  // namespace hypro