#pragma once

#include "../../util/type_handling/better_enums/enum_default_ctor.h"
#include "../../util/type_handling/meta/RepresentationCombinations.h"

namespace hypro {

BETTER_ENUM( StarsetSetting_name, int,
			 StarsetDefault, StarsetEqvPolytopeCaching )

// This is the default setting
struct StarsetDefault {
	static constexpr int type_enum = StarsetSetting_name::StarsetDefault;
	static constexpr bool CACHE_EQV_POLYTOPE = false;
	// put settings here
};

// Enabled caching of equivalent H-Polytope of the Starset
// useful when conversion to H-Polytope repeadatly needed (check containment multiple times)
struct StarsetEqvPolytopeCaching {
	static constexpr int type_enum = StarsetSetting_name::StarsetEqvPolytopeCaching;
	static constexpr bool CACHE_EQV_POLYTOPE = true;
};

}  // namespace hypro
