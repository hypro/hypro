/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../datastructures/HybridAutomaton/State.h"
#include "../../representations/types.h"

namespace hypro {

/**
 * @brief Class that contains a raw segment for plotting. Note that a segment can be composed of several sub-segments, in case subspace decomposition is used.
 *
 * @tparam Number
 */
    template<typename State>
    struct PlotData {
        State sets;                      // contains sets - one segment per subspace
        std::size_t threadId;          // thread-id for color coding
        std::size_t refinementLevel;  // refinement level for color coding

        PlotData(const State &s, std::size_t l)
                : sets(s), threadId(), refinementLevel(l) {}

        PlotData(const State &s, std::size_t l, std::size_t t)
                : sets(s), threadId(t), refinementLevel(l) {}
    };

}  // namespace hypro
