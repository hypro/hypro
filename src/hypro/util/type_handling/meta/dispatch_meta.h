#pragma once
#include "../../unreachable.h"
#include "../representation_enums.h"
#include "../settings_enums.h"
#include "RepresentationCombinations.h"
#include "TypeList.h"

#include <assert.h>

namespace hypro {

//Maps an enum (or really any value) to each type. By default a static ::type_enum member is used so that a class can declare it itself. This may also be specialized elsewhere (simiar to std::hash) to provide the mapping.
template <class T>
static constexpr auto TypeEnum = T::type_enum;

//Takes a representation, unpacks its template arguments and allows matching against the TypeEnum values of those.
template <class Representation>
struct TypeMapping;

template <template <class...> class R, class N, class C, class Setting>
struct TypeMapping<R<N, C, Setting>> {
	static bool matches( representation_name representation, int setting ) {
		return TypeEnum<R<N, C, Setting>> == representation && TypeEnum<Setting> == setting;
	}
};

/// Recursive dispatch to find correct representation
template <class Representation, class... Representations>
struct Dispatcher_i {
	template <class Callable, class... Args>
	static auto dispatch( representation_name representation, int setting, Callable c, Args&&... args ) {
		if ( TypeMapping<Representation>::matches( representation, setting ) ) {
			return c.template operator()<Representation>( std::forward<Args>( args )... );
		} else {
			return Dispatcher_i<Representations...>::dispatch( representation, setting, c, std::forward<Args>( args )... );
		}
	}
};

/// Base case dispatch to find correct representation
template <class Representation>
struct Dispatcher_i<Representation> {
	template <class Callable, class... Args>
	static auto dispatch( representation_name representation, int setting, Callable c, Args&&... args ) {
		if ( TypeMapping<Representation>::matches( representation, setting ) ) {
			return c.template operator()<Representation>( std::forward<Args>( args )... );
		}
		assert( false && "No representation was matched." );
		unreachable();
	}
};

template <class Number, class Converter, class RepresentationCombinationsList>
using Dispatcher = apply<Dispatcher_i, flattenRepresentations<Number, Converter, RepresentationCombinationsList>>;
}  // namespace hypro