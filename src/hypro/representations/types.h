#pragma once
#include <boost/variant.hpp>

namespace hypro {

/**
 * @brief      Enum encapsulating all provided state set representations to be able to determine a type.
 */
enum representation_name { constraint_set, box, zonotope, polytope_h, polytope_v, ppl_polytope, support_function, taylor_model };

} // namespace hypro
