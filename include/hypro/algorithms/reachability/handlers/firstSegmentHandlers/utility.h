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
#include "../../../../representations/GeometricObjectBase.h"

namespace hypro {
    template<typename State>
    State bloatBox(const State &in, const hypro::Box<typename State::NumberType> &bloatBox, size_t index) {
        DEBUG("hypro.worker", "For index " << index);
        State bloatState{in};  // Todo: this is clumsy, as we just require SOME state set in the state.

        bloatState.setSet(std::visit(
                genericInternalConversionVisitor<typename State::repVariant, hypro::Box<typename State::NumberType>>(
                        bloatBox), bloatState.rGetSet(index)), index);
        DEBUG("hypro.worker", "Used box for bloating: " << bloatState);
        return in.partiallyMinkowskiSum(bloatState, index);
    }
}  // namespace hypro
