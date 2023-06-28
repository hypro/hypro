/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../../types.h"
#include "affine.h"
#include "linear.h"
#include "rectangular.h"
#include "typetraits.h"
#include "visitors.h"

namespace hypro {

    template<typename T>
    DynamicType getFlowType(const T &f) {
        return std::visit(flowTypeVisitor(), f);
    }

    template<typename T>
    std::size_t getFlowDimension(const T &f) {
        return std::visit(flowDimensionVisitor(), f);
    }

    template<typename T>
    bool isTimed(const T &f) {
#ifdef HYPRO_LOGGING
        bool timed = std::visit(flowIsTimedVisitor(), f);
        DEBUG("hypro.flow", ": " << timed);
        return timed;
#else
        return std::visit( flowIsTimedVisitor(), f );
#endif
    }

    template<typename T>
    bool isSingular(const T &f) {
#ifdef HYPRO_LOGGING
        bool singular = std::visit(flowIsSingularVisitor(), f);
        DEBUG("hypro.flow", ": " << singular);
        return singular;
#else
        return std::visit( flowIsSingularVisitor(), f );
#endif
    }

    template<typename T>
    bool isDiscrete(const T &f) {
#ifdef HYPRO_LOGGING
        bool discrete = std::visit(flowIsDiscreteVisitor(), f);
        DEBUG("hypro.flow", ": " << discrete);
        return discrete;
#else
        return std::visit( flowIsDiscreteVisitor(), f );
#endif
    }

}  // namespace hypro
