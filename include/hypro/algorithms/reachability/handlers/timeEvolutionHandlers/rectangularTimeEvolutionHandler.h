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
    rectangularApplyBoundedTimeEvolution(const PolyhedralRepresentation<Number, Converter, Setting> &initialSet,
                                         const rectangularFlow<Number> &flow, tNumber timeBound);

    template<typename Number>
    CarlPolytope<Number>
    rectangularApplyReverseTimeEvolution(const CarlPolytope<Number> &badSet, const Location<Number> *loc);

    template<typename Number>
    CarlPolytope<Number> rectangularUnderapproximateReverseTimeEvolution(const CarlPolytope<Number> &badSet,
                                                                         const rectangularFlow<Number> &flow);

    template<template<typename, typename, typename> class PolyhedralRepresentation, typename Number, typename Converter, typename Setting, enable_if<!std::is_same_v<CarlPolytope<Number>, PolyhedralRepresentation<Number, Converter, Setting>>> = 0>
    PolyhedralRepresentation<Number, Converter, Setting>
    rectangularApplyReverseTimeEvolution(const PolyhedralRepresentation<Number, Converter, Setting> &badSet,
                                         const Location<Number> *loc) {
        auto convertedSet = Converter::toCarlPolytope(badSet);
        auto convertedResult = rectangularApplyReverseTimeEvolution(convertedSet, loc);
        // std::cout << __func__ << ": Set before conversion: " << convertedResult << std::endl;
        PolyhedralRepresentation<Number, Converter, Setting> res;
        convert(convertedResult, res);
        // std::cout << __func__ << ": Set after conversion: " << res << std::endl;
        return res;
    }

    template<template<typename, typename, typename> class PolyhedralRepresentation, typename Number, typename Converter, typename Setting, enable_if<!std::is_same_v<CarlPolytope<Number>, PolyhedralRepresentation<Number, Converter, Setting>>> = 0>
    PolyhedralRepresentation<Number, Converter, Setting>
    rectangularUnderapproximateReverseTimeEvolution(const PolyhedralRepresentation<Number, Converter, Setting> &badSet,
                                                    const rectangularFlow<Number> &flow) {
        auto convertedSet = Converter::toCarlPolytope(badSet);
        auto convertedResult = rectangularUnderapproximateReverseTimeEvolution(convertedSet, flow);
        PolyhedralRepresentation<Number, Converter, Setting> res;
        convert(convertedResult, res);
        return res;
    }


	template<typename Number, typename Representation>
	CarlPolytope<Number> rectangularUnderapproximateReverseTimeEvolution( const Representation& badSet, const Location<Number>* loc ) ;

    template<typename Number>
    CarlPolytope<Number>
    rectangularApplyTimeEvolution(const CarlPolytope<Number> &initialSet, const rectangularFlow<Number> &flow);

}  // namespace hypro

#include "rectangularTimeEvolutionHandler.tpp"
