#pragma once
#include "../../../util/type_handling/better_enums/enum_default_ctor.h"
#include "../../../util/type_handling/meta/RepresentationCombinations.h"

namespace hypro {

BETTER_ENUM( carlPolytopeSetting_name, int, CarlPolytopeSetting )

struct CarlPolytopeSetting {
	static constexpr int type_enum = carlPolytopeSetting_name::CarlPolytopeSetting;
};

}  // namespace hypro