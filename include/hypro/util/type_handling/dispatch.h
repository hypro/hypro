#pragma once
#include "meta/default_dispatch.h"
#include "representation_enums.h"

namespace hypro {
template <typename Number, typename Converter, typename Callable, typename... Args>
auto dispatch( representation_name representation, int setting, Callable func, Args&&... args ) {
	return DefaultDispatcher<Number, Converter>::dispatch( representation, setting, func, std::forward<Args>( args )... );
}
}  // namespace hypro