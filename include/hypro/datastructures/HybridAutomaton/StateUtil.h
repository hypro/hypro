/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "Reset.h"

namespace hypro {

    template<typename Number, typename Representation, typename... Rargs>
    State<Number, Representation, Rargs...>
    applyReset(const State<Number, Representation, Rargs...> &inState, const Reset<Number> &reset) {
        TRACE("hypro.datastructures", "inState #sets: " << inState.getNumberSets() << " and #resets: " << reset.size());
        assert(reset.empty() || inState.getNumberSets() == reset.size());
        if (reset.empty()) {
            DEBUG("hypro.datastructures", "Reset is empty.");
            return inState;
        }
        auto res = inState;
        for (std::size_t pos = 0; pos < reset.size(); ++pos) {
            if (!reset.getAffineReset(pos).isIdentity()) {
                res = res.applyTransformation(reset.getAffineReset(pos).mTransformation, pos);
            }
            if (!reset.getIntervalReset(pos).isIdentity()) {
                res = res.partialIntervalAssignment(reset.getIntervalReset(pos).mIntervals, pos);
            }
        }

        return res;
    }

    template<class Number, class R, class... Rs>
    std::string printSet(State<Number, R, Rs...> const &state, size_t index = 0) {
        std::stringstream s_stream{};
        state.visit(index, [&](auto &&set) {
            s_stream << set;
        });
        return s_stream.str();
    }

}  // namespace hypro
