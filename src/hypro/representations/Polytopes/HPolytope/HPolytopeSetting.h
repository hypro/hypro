#pragma once

namespace hypro {

	//For usage as main representation of each segment
	struct HPolytopeSetting {
		static constexpr bool REDUCE_NUMBERS = true;
		static constexpr bool AVOID_CONVERSION = true;
		static constexpr bool OPTIMIZER_CACHING = false;
	};

	//For usage as leaf in SupportFunctionNew
	struct HPolytopeOptimizerCaching {
		static constexpr bool REDUCE_NUMBERS = true;
		static constexpr bool AVOID_CONVERSION = true;
		static constexpr bool OPTIMIZER_CACHING = true;		
	};
}

