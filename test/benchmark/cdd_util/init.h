/**
 * File that holds functions required for the usage of cdd.
 */

#ifdef COMPARE_CDD
#include "../../../src/config.h"

namespace hypro {
static void init() {
#ifdef __cplusplus
	extern "C" {
#endif
	dd_set_global_constants();

#ifdef __cplusplus
	}
#endif
}
}  // namespace hypro

#endif