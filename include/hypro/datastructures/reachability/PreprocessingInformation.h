#pragma once
#include "../../types.h"

namespace hypro {
/**
 * @brief Struct that collects all information obtained by the preprocessor
 */
struct PreprocessingInformation {
	DynamicType dynamic = DynamicType::affine;	///< detected type of dynamics
};
}  // namespace hypro
