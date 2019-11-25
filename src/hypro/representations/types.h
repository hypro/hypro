#pragma once

namespace hypro {

/**
 * @brief      Enum encapsulating all provided state set representations to be able to determine a type.
 */
enum representation_name { box = 0,
						   carl_polytope,
						   constraint_set,
						   polytope_h,
						   polytope_v,
						   ppl_polytope,
						   support_function,
						   taylor_model,
						   zonotope,
						   difference_bounds,
						   SFN,
						   polytope_t, 
						   orthoplex,
						   UNDEF,
						   genStar };

}  // namespace hypro
