#pragma once
#include <boost/variant.hpp>

namespace hypro {

/**
 * @brief      Enum encapsulating all provided state set representations to be able to determine a type.
 */
enum representation_name { box, constraint_set, polytope_h, polytope_v, ppl_polytope, support_function, taylor_model, zonotope };

} // namespace hypro
