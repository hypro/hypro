#pragma once

#include "../../util/type_handling/better_enums/enum_default_ctor.h"

namespace hypro {
namespace reachability {

BETTER_ENUM( REACHABILITY_OPERATION, int,
			 DEFAULT,
			 INPUT,
			 AFFINE,
			 RELU_POS,
			 RELU_NEG,
			 RELU_APPROX,
			 LEAKY_RELU_POS,
			 LEAKY_RELU_NEG,
			 LEAKY_RELU_APPROX,
			 HARD_TANH_MAX,
			 HARD_TANH_MID,
			 HARD_TANH_MIN,
			 HARD_TANH_APPROX,
			 HARD_SIGMOID_MAX,
			 HARD_SIGMOID_MID,
			 HARD_SIGMOID_MIN,
			 HARD_SIGMOID_APPROX,
			 STEP_FUNCTION_MAX,
			 STEP_FUNCTION_MIN,
			 STEP_FUNCTION_APPROX);
}
}  // namespace hypro
