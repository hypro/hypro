#pragma once

namespace hypro {

BETTER_ENUM( vPolytopeSetting_name, int,
			 VPolytopeSetting )

struct VPolytopeSetting {
	static constexpr int type_enum = vPolytopeSetting_name::VPolytopeSetting;
	static constexpr bool checkVerticesBeforeConversion = true;
	static constexpr bool useLpForPointContainment = true;
};

}  // namespace hypro
