#pragma once
#include "../../representations/Box/BoxSetting.h"
#include "../../representations/GeometricObjectBase.h"
#include "representation_enums.h"
#include "settings_enums.h"

#include <assert.h>

namespace hypro {

/**
 * @brief
 * @detail  Example usage: see example_dispatch.cpp
 */
template <typename Number, typename Converter, typename Callable, typename... Args>
auto dispatch( representation_name representation, int setting, Callable func, Args... args ) {
	switch ( representation ) {
		case representation_name::box:
			switch ( static_cast<boxSetting_name>( setting ) ) {
				case boxSetting_name::BoxLinearOptimizationOn:
					return func.template operator()<BoxT<Number, Converter, BoxLinearOptimizationOn>>( args... );
				case boxSetting_name::BoxAllOff:
					return func.template operator()<BoxT<Number, Converter, BoxLinearOptimizationOn>>( args... );
			}
	}
	assert( false );
}
}  // namespace hypro