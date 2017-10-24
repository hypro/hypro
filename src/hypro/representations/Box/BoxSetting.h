#pragma once

namespace hypro {

	//For box and box_double
	struct BoxSetting {
		// used in case we do not have a thread-safe optimizer. Slow for high dimensions.
		static constexpr bool HYPRO_BOX_AVOID_LINEAR_OPTIMIZATION = false;
	};
	
}