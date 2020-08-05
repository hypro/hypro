#pragma once
#include "../../../util/type_handling/better_enums/enum.h"
#include "../../../util/type_handling/meta/RepresentationCombinations.h"

namespace hypro {

BETTER_ENUM( hPolytopeSetting_name, int,
			 HPolytopeSetting, HPolytopeOptimizerCaching )

//For usage as main representation of each segment
struct HPolytopeSetting {
	static constexpr int type_enum = hPolytopeSetting_name::HPolytopeSetting;
	static constexpr bool REDUCE_NUMBERS = true;
	static constexpr bool AVOID_CONVERSION = true;
	static constexpr bool OPTIMIZER_CACHING = false;
	static constexpr bool NAIVE_ALGORITHMS = false;
};

//For usage as leaf in SupportFunctionNew
struct HPolytopeOptimizerCaching {
	static constexpr int type_enum = hPolytopeSetting_name::HPolytopeOptimizerCaching;
	static constexpr bool REDUCE_NUMBERS = true;
	static constexpr bool AVOID_CONVERSION = true;
	static constexpr bool OPTIMIZER_CACHING = true;
	static constexpr bool NAIVE_ALGORITHMS = false;
};
}  // namespace hypro
