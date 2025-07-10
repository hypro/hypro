#pragma once

#include "../../../util/type_handling/better_enums/enum_default_ctor.h"

namespace hypro {

// assuming that we have the same type of neurons in a single layer
// e.g a layer can be Affine layer or ReLU layer (in future we  extend with differen activation functions and layer types)
BETTER_ENUM( NN_LAYER_TYPE, int, DEFAULT,
			 AFFINE, RELU, HARD_TANH, LEAKY_RELU, HARD_SIGMOID, STEP_FUNCTION, GENERAL_PIECEWISE_LINEAR
			 // here we could have other types of layers (e.g. other piecewise linear activation functions, or convolutional layers etc.)
);

}  // namespace hypro
