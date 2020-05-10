#pragma once

#include "better_enums/enum.h"

#include <string>

namespace hypro {

// box settings
BETTER_ENUM( boxSetting_name, int,
			 BoxLinearOptimizationOn,
			 BoxLinearOptimizationOff,
			 BoxIntervalArithmeticOff,
			 BoxAllOff )

BETTER_ENUM( supportFunctionSetting_name, int,
			 SupportFunctionSetting,
			 NoBoxReduction,
			 NoBoxDetection,
			 NoTrafoReduction,
			 NoReduction,
			 PolytopeSupportFunctionSetting )

int stringToSetting( const std::string& name );

}  // namespace hypro