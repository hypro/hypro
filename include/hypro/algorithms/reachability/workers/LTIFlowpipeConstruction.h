/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once
#pragma once

#include "../../../datastructures/HybridAutomaton/Transition.h"
#include "../../../datastructures/HybridAutomaton/flow/linear.h"
#include "../../../representations/GeometricObjectBase.h"
#include "../../../types.h"
#include "../../../util/typetraits.h"
#include "../FlowpipeConstructionConvenience.h"
#include "../types.h"
#include "../util.h"

namespace hypro {

    template<class Number>
    struct ErrorBoxes {
        Box<Number> X0Box{};
        Box<Number> ExternalInputBox{};
        Box<Number> DifferenceBox{};
    };

    template<class Number>
    matrix_t<Number> computeTimeTransformation(linearFlow<Number> const &flow, tNumber timeStep);

    template<class Representation, class Number>
    Representation constructFirstSegment(Representation const &initialSet,
                                         linearFlow<Number> const &flow,
                                         matrix_t<Number> const &rawTransformation,
                                         tNumber timeStep);

    template<class Representation, class Number>
    ErrorBoxes<Number>
    constructErrorBoxes(Number const &delta, matrix_t<Number> const &flowMatrix, Representation const &initialSet,
                        matrix_t<Number> const &trafoMatrix, Box<Number> const &externalInput);

    template<class Representation>
    std::vector<Representation> aggregate(int segmentsPerBlock, std::vector<Representation> &valuationSets);

}  // namespace hypro

#include "LTIFlowpipeConstruction.tpp"
