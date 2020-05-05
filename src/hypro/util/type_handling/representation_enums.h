#pragma once

#include <map>
#include <string>

namespace hypro {
/**
 * @brief      Enum encapsulating all provided state set representations to be able to determine a type.
 */
enum class representation_name { box,
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
								 UNDEF,
								 genStar };

inline std::map<std::string, representation_name> const stringToRepresentation{
	  {"box", representation_name::box},
	  {"carl_polytope", representation_name::carl_polytope},
	  {"support_function", representation_name::support_function}};

}  // namespace hypro
