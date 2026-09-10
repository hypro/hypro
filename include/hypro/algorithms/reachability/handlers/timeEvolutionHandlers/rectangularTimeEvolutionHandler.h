/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../../../datastructures/HybridAutomaton/State.h"
#include "../../../../datastructures/HybridAutomaton/flow/rectangular.h"
#include "../../../../datastructures/HybridAutomaton/flow/rectangularOperations.h"
#include "../../../../representations/GeometricObjectBase.h"
#include "../../../../representations/conversion/conversionHelper.h"
#include "../../../../util/typetraits.h"


#include <sstream>
#include <string>

namespace hypro {

    template<typename Number, class... Reps>
    State<Number, Reps...>
    rectangularApplyTimeEvolution(const State<Number, Reps...> &initialSet, const rectangularFlow<Number> &flow);

    template<typename Number, class... Reps>
    State<Number, Reps...>
    rectangularApplyReverseTimeEvolution(const State<Number, Reps...> &badSet, const Location<Number> *loc);

    template<template<typename, typename, typename> class PolyhedralRepresentation, typename Number, typename Converter, typename Setting>
    PolyhedralRepresentation<Number, Converter, Setting>
    rectangularApplyTimeEvolution(const PolyhedralRepresentation<Number, Converter, Setting> &initialSet,
                                  const rectangularFlow<Number> &flow);

	template<template<typename, typename, typename> class PolyhedralRepresentation, typename Number, typename Converter, typename Setting>
	PolyhedralRepresentation<Number, Converter, Setting>
	rectangularApplyTimeEvolution(const PolyhedralRepresentation<Number, Converter, Setting> &initialSet,
								   const rectangularFlow<Number> &flow, const Condition<Number> &invariant);

    template<template<typename, typename, typename> class PolyhedralRepresentation, typename Number, typename Converter, typename Setting>
    PolyhedralRepresentation<Number, Converter, Setting>
    rectangularApplyBoundedTimeEvolution(const PolyhedralRepresentation<Number, Converter, Setting> &initialSet,
                                         const rectangularFlow<Number> &flow, tNumber timeBound);

    template<typename Number>
    CarlPolytope<Number>
    rectangularApplyReverseTimeEvolution(const CarlPolytope<Number> &badSet, const Location<Number> *loc);

	// stochJumpAndMappedDim/firstEnabledIndex are vectors, not single optional pairs, because more
	// than one stochastic-resettable clock can be simultaneously timed in the same location (e.g. two
	// clocks racing each other toward whichever fires first) -- each such clock independently needs
	// its own pre-image pin (stochJumpAndMappedDim) and/or closing-value capture (firstEnabledIndex)
	// applied within the same reverse time evolution call, since they share one location's flow/
	// invariant and must be eliminated together. An empty vector is exactly the old std::nullopt case.
	// initialConditions now carries genuine (possibly multi-variable, correlated) constraint rows rather
	// than one axis-aligned interval per variable -- e.g. a caller can inject "x <= 2*y + 3" to correlate
	// two variables' entry-side values, not just bound each independently. See the injection site inside
	// this function's .tpp for exactly how/when these rows are added (after every non-frozen variable has
	// already been substituted to its entry-side identity, so every row's meaning is well-defined
	// regardless of how many variables it spans).
	// firstEnabledIndexLowerBoundOnly is shaped identically to firstEnabledIndex (clock -> instance index
	// pairs) but adds a one-sided "instance >= clock's closing value" constraint instead of an equality --
	// for an epoch that was timed but never reached its own firing transition (a strictCycleLimitVariable
	// whose racing counterpart fired instead, or whose location exited some other way), the closing value
	// only proves the clock hadn't yet reached its (unknown) firing threshold, not what its eventual real
	// value will be. See the injection site inside this function's .tpp for the exact constraint added.
	template<typename Number>
	CarlPolytope<Number>
	rectangularApplyReverseTimeEvolution(const CarlPolytope<Number> &badSet, const rectangularFlow<Number> &flow, const Condition<Number> &invariant, std::vector<std::pair<size_t,size_t>> stochJumpAndMappedDim = {}, std::vector<std::pair<size_t,size_t>> firstEnabledIndex = {}, std::optional<std::vector<ConstraintT<hypro::tNumber>>> initialConditions = std::nullopt, std::vector<std::pair<size_t,size_t>> firstEnabledIndexLowerBoundOnly = {});

    template<typename Number>
    CarlPolytope<Number> rectangularUnderapproximateReverseTimeEvolution(const CarlPolytope<Number> &badSet, const rectangularFlow<Number> &flow);

	template<template<typename, typename, typename> class PolyhedralRepresentation, typename Number, typename Converter, typename Setting, enable_if<!std::is_same_v<CarlPolytope<Number>, PolyhedralRepresentation<Number, Converter, Setting>>> = 0>
	PolyhedralRepresentation<Number, Converter, Setting>
	rectangularApplyReverseTimeEvolution(const PolyhedralRepresentation<Number, Converter, Setting> &badSet, const rectangularFlow<Number> &flow, const Condition<Number> &invariant, std::vector<std::pair<size_t,size_t>> stochJumpAndMappedDim = {}, std::vector<std::pair<size_t,size_t>> firstEnabledIndex = {}, std::optional<std::vector<ConstraintT<hypro::tNumber>>> initialConditions = std::nullopt, std::vector<std::pair<size_t,size_t>> firstEnabledIndexLowerBoundOnly = {});

    template<template<typename, typename, typename> class PolyhedralRepresentation, typename Number, typename Converter, typename Setting, enable_if<!std::is_same_v<CarlPolytope<Number>, PolyhedralRepresentation<Number, Converter, Setting>>> = 0>
    PolyhedralRepresentation<Number, Converter, Setting>
    rectangularApplyReverseTimeEvolution(const PolyhedralRepresentation<Number, Converter, Setting> &badSet,
                                         const Location<Number> *loc);

    template<template<typename, typename, typename> class PolyhedralRepresentation, typename Number, typename Converter, typename Setting, enable_if<!std::is_same_v<CarlPolytope<Number>, PolyhedralRepresentation<Number, Converter, Setting>>> = 0>
    PolyhedralRepresentation<Number, Converter, Setting>
    rectangularUnderapproximateReverseTimeEvolution(const PolyhedralRepresentation<Number, Converter, Setting> &badSet,
													 const Location<Number> *loc);

    template<typename Number>
    CarlPolytope<Number>
    rectangularApplyTimeEvolution(const CarlPolytope<Number> &initialSet, const rectangularFlow<Number> &flow);

}  // namespace hypro

#include "rectangularTimeEvolutionHandler.tpp"
