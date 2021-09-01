#pragma once
#include "../../util/type_handling/better_enums/enum_default_ctor.h"
#include "../../util/type_handling/meta/RepresentationCombinations.h"

namespace hypro {

BETTER_ENUM( supportFunctionSetting_name, int,
			 SupportFunctionSetting,
			 NoBoxReduction,
			 NoBoxDetection,
			 NoTrafoReduction,
			 NoReduction,
			 PolytopeSupportFunctionSetting )

struct SupportFunctionSetting {
	static constexpr int type_enum = supportFunctionSetting_name::SupportFunctionSetting;
	static constexpr bool SUPPORTFUNCTION_VERBOSE = false;
	static constexpr bool USE_LIN_TRANS_REDUCTION = true;
	static constexpr bool REDUCE_TO_BOX = true;
	static constexpr bool DETECT_BOX = true;
	static constexpr bool AVOID_INTERSECTIONS = true;
	static constexpr bool BOXSUPPORTFUNCTION_VERBOSE = false;
	static constexpr bool BOXOPERATOR_VERBOSE = false;
	static constexpr bool CALCEPSILON_VERBOSE = false;
	static constexpr bool CALCVALUES_VERBOSE = false;
	static constexpr bool TEST_ = false;
	static constexpr bool PPOLYTOPESUPPORTFUNCTION_VERBOSE = false;
	static constexpr bool PPOLYTOPESUPPORTFUNCTION_VERIFY = true;
	// static constexpr bool HYPRO_USE_VECTOR_CACHING = false;
};

struct NoBoxReduction : SupportFunctionSetting {
	static constexpr int type_enum = supportFunctionSetting_name::NoBoxReduction;
	static constexpr bool REDUCE_TO_BOX = false;
};

struct NoBoxDetection : SupportFunctionSetting {
	static constexpr int type_enum = supportFunctionSetting_name::NoBoxDetection;
	static constexpr bool REDUCE_TO_BOX = false;
	static constexpr bool DETECT_BOX = false;
};

struct NoTrafoReduction : SupportFunctionSetting {
	static constexpr int type_enum = supportFunctionSetting_name::NoTrafoReduction;
	static constexpr bool USE_LIN_TRANS_REDUCTION = false;
};

struct NoReduction : SupportFunctionSetting {
	static constexpr int type_enum = supportFunctionSetting_name::NoReduction;
	static constexpr bool SUPPORTFUNCTION_VERBOSE = false;
	static constexpr bool USE_LIN_TRANS_REDUCTION = false;
	static constexpr bool REDUCE_TO_BOX = false;
	static constexpr bool DETECT_BOX = false;
	static constexpr bool BOXSUPPORTFUNCTION_VERBOSE = false;
	static constexpr bool BOXOPERATOR_VERBOSE = false;
	static constexpr bool CALCEPSILON_VERBOSE = false;
	static constexpr bool CALCVALUES_VERBOSE = false;
	static constexpr bool TEST_ = false;
	static constexpr bool PPOLYTOPESUPPORTFUNCTION_VERBOSE = false;
	static constexpr bool PPOLYTOPESUPPORTFUNCTION_VERIFY = true;
};

// PolytopeSupportFunctions
struct PolytopeSupportFunctionSetting : SupportFunctionSetting {
	static constexpr int type_enum = supportFunctionSetting_name::PolytopeSupportFunctionSetting;
	static constexpr bool PPOLYTOPESUPPORTFUNCTION_VERBOSE = false;
	static constexpr bool PPOLYTOPESUPPORTFUNCTION_VERIFY = true;
};

}  // namespace hypro
