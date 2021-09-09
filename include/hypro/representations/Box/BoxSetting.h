#pragma once
#include "../../util/type_handling/better_enums/enum_default_ctor.h"
#include "../../util/type_handling/meta/RepresentationCombinations.h"

namespace hypro {

BETTER_ENUM( boxSetting_name, int,
			 BoxLinearOptimizationOn,
			 BoxLinearOptimizationOff,
			 BoxIntervalArithmeticOff,
			 BoxAllOff )

// For box and box_double
// This is the default setting
struct BoxLinearOptimizationOn {
	static constexpr int type_enum = boxSetting_name::BoxLinearOptimizationOn;
	// used in case we do have a thread-safe optimizer.
	static constexpr bool HYPRO_BOX_AVOID_LINEAR_OPTIMIZATION = false;
	// enables methods from interval arithmetic
	static constexpr bool USE_INTERVAL_ARITHMETIC = true;
	// detects upon construction of a box from constraints whether those already represent a box.
	static constexpr bool DETECT_BOX = true;
};

struct BoxLinearOptimizationOff {
	static constexpr int type_enum = boxSetting_name::BoxLinearOptimizationOff;
	// used in case we do not have a thread-safe optimizer. Slow for high dimensions.
	static constexpr bool HYPRO_BOX_AVOID_LINEAR_OPTIMIZATION = true;
	// enables methods from interval arithmetic
	static constexpr bool USE_INTERVAL_ARITHMETIC = true;
	// detects upon construction of a box from constraints whether those already represent a box.
	static constexpr bool DETECT_BOX = true;
};

struct BoxIntervalArithmeticOff {
	static constexpr int type_enum = boxSetting_name::BoxIntervalArithmeticOff;
	// used in case we do not have a thread-safe optimizer. Slow for high dimensions.
	static constexpr bool HYPRO_BOX_AVOID_LINEAR_OPTIMIZATION = true;
	// enables methods from interval arithmetic
	static constexpr bool USE_INTERVAL_ARITHMETIC = false;
	// detects upon construction of a box from constraints whether those already represent a box.
	static constexpr bool DETECT_BOX = true;
};

struct BoxAllOff {
	static constexpr int type_enum = boxSetting_name::BoxAllOff;
	// used in case we do not have a thread-safe optimizer. Slow for high dimensions.
	static constexpr bool HYPRO_BOX_AVOID_LINEAR_OPTIMIZATION = false;
	// enables methods from interval arithmetic
	static constexpr bool USE_INTERVAL_ARITHMETIC = false;
	// detects upon construction of a box from constraints whether those already represent a box.
	static constexpr bool DETECT_BOX = false;
};
}  // namespace hypro
