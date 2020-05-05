#pragma once
#include "representation_enums.h"
#include "settings_enums.h"

namespace hypro {

/**
 * @brief
 * @detail  Example usage: see example_dispatch.cpp
 *
 * @tparam Number
 * @tparam Converter
 * @tparam Callable
 * @tparam Args
 * @param representation
 * @param setting
 * @param func
 * @param args
 * @return auto
 */
template <typename Number, typename Converter, typename Callable, typename... Args>
auto dispatch( representation_name representation, int setting, Callable func, Args... args ) {
	switch ( representation ) {
		case representation_name::box:
			switch ( static_cast<boxSetting_name>( setting ) ) {
				case boxSetting_name::BoxLinearOptimizationOn:
					return func<BoxT<Number, Converter, BoxLinearOptimizationOn>>( args );
					break;
			}
		case representation_name::support_function:
			break;
	}
	assert( false );
}
}  // namespace hypro