#pragma once

#include <map>
#include <string>

namespace hypro {

// box settings
enum class boxSetting_name {
	BoxLinearOptimizationOn,
	BoxLinearOptimizationOff,
	BoxIntervalArithmeticOff,
	BoxAllOff
};

inline std::map<std::string, boxSetting_name> const stringToBoxSetting{
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
			return static_cast<int>( stringToBoxSetting.at( name ) );
	}
}

}  // namespace hypro