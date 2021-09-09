#pragma once
#include "TypeList.h"

namespace hypro {
/// Holds a representation and a list of viable settings for it
/// General case
template <template <class...> class Representation, class... Settings>
struct RepresentationCombinations {
	// Holds the list of Representations with the settings
	// Apply first setting and concat into the rest
	template <class Number, class Converter>
	using combinations = TypeList<Representation<Number, Converter, Settings>...>;
};

/// Takes a Number and Converter type and a TypeList of RepresentationCombinations and flattens them into a TypeList of instantiations of Representations
template <class Number, class Converter, class CombinationsList>
struct flattenRepresentations_i;

/// Flattens representations list
template <class Number, class Converter, class... RepCombinationsList>
struct flattenRepresentations_i<Number, Converter, TypeList<RepCombinationsList...>> {
	// Use fold expression to concat the combinations lists of the RepresentationCombinations
	using type = concat<typename RepCombinationsList::template combinations<Number, Converter>...>;
};

/// Quick access
template <class Number, class Converter, class CombinationsList>
using flattenRepresentations = typename flattenRepresentations_i<Number, Converter, CombinationsList>::type;
}  // namespace hypro