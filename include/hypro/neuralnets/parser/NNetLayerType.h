#pragma once

namespace hypro {

enum class NN_LAYER_TYPE {
	AFFINE,
    RELU
    // here we could have other types of layers (e.g. other piecewise linear activation functions, or convolutional layers etc.)
};

} // namespace hypro

