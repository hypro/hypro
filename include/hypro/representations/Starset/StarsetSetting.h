#pragma once

#include "../../util/type_handling/better_enums/enum_default_ctor.h"
#include "../../util/type_handling/meta/RepresentationCombinations.h"
namespace hypro {
	BETTER_ENUM( StarsetSetting_name, int, StarsetDefault)
	//This is the default setting
	struct StarsetDefault {
			static constexpr int type_enum = StarsetSetting_name::StarsetDefault;

		// put settings here
	};
}
