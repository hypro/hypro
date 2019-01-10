#pragma once

namespace hypro {

	//For box and box_double
	//This is the default setting
	struct BoxLinearOptimizationOn {
		// used in case we do have a thread-safe optimizer.
		static constexpr bool HYPRO_BOX_AVOID_LINEAR_OPTIMIZATION = false;
		// enables methods from interval arithmetic
		static constexpr bool USE_INTERVAL_ARITHMETIC = true;
	};

	struct BoxLinearOptimizationOff {
		// used in case we do not have a thread-safe optimizer. Slow for high dimensions.
		static constexpr bool HYPRO_BOX_AVOID_LINEAR_OPTIMIZATION = true;
		// enables methods from interval arithmetic
		static constexpr bool USE_INTERVAL_ARITHMETIC = true;
	};

	struct BoxIntervalArithmeticOff {
		// used in case we do not have a thread-safe optimizer. Slow for high dimensions.
		static constexpr bool HYPRO_BOX_AVOID_LINEAR_OPTIMIZATION = true;
		// enables methods from interval arithmetic
		static constexpr bool USE_INTERVAL_ARITHMETIC = false;
	};

	struct BoxAllOff {
		// used in case we do not have a thread-safe optimizer. Slow for high dimensions.
		static constexpr bool HYPRO_BOX_AVOID_LINEAR_OPTIMIZATION = false;
		// enables methods from interval arithmetic
		static constexpr bool USE_INTERVAL_ARITHMETIC = false;
	};
}
