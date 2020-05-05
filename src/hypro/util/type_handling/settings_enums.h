#pragma once

namespace hypro {

// box settings
enum class boxSetting_name {
	BoxLinearOptimizationOn,
	BoxLinearOptimizationOff,
	BoxIntervalArithmeticOff,
	BoxAllOff
};

std::map<std::string, boxSetting_name> stringToBoxSetting{
	  {"BoxLinearOptimizationOn",
	   boxSetting_name::BoxLinearOptimizationOn},
	  {"BoxLinearOptimizationOff",
	   boxSetting_name::BoxLinearOptimizationOff},
	  {"BoxIntervalArithmeticOff",
	   boxSetting_name::BoxIntervalArithmeticOff},
	  {"BoxAllOff", boxSetting_name::BoxAllOff}};

int stringToSetting( representation_name Rep, const std::string& name ) {
	switch ( Rep ) {
		case representation_name::box:
			return stringToBoxSetting[name];
	}
}

}  // namespace hypro