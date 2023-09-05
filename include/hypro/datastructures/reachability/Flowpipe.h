/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../datastructures/HybridAutomaton/Condition.h"
#include "../../util/Range.h"

/*
	Requirements:
 */

namespace hypro {

/**
 * @brief Container for a flowpipe, i.e. an ordered sequence of state sets (flowpipe segments).
 *
 * @tparam State Used state type.
 */
    template<typename Representation>
    class Flowpipe {
    private:
        std::vector<Representation> mStates;

    public:
        Flowpipe( /* args */ ) {};

        ~Flowpipe() {};

        void setStates(const std::vector<Representation> &states) { mStates = states; }

        void setStates(std::vector<Representation> &&states) { mStates = std::move(states); }

        void addState(const Representation &state) { mStates.emplace_back(state); }

        void addState(Representation &&state) { mStates.emplace_back(state); }

        template<typename Number>
        Range<std::vector<Representation>> selectSatisfyingStates(const Condition<Number> &cond) {
            return selectFirstConsecutiveRange(mStates, [&](const Representation &in) -> bool {
                auto tmp = in.satisfiesHalfspaces(cond.getMatrix(), cond.getVector()).first;
                return tmp != CONTAINMENT::NO && tmp != CONTAINMENT::BOT;
            });
        }

        void clear() { mStates.clear(); }

        typename std::vector<Representation>::iterator begin() { return mStates.begin(); }

        typename std::vector<Representation>::iterator end() { return mStates.end(); }

        typename std::vector<Representation>::const_iterator begin() const { return mStates.begin(); }

        typename std::vector<Representation>::const_iterator end() const { return mStates.end(); }

        const Representation &front() const { return *mStates.begin(); }

        const Representation &back() const { return std::next(mStates.end(), -1); }

        std::size_t size() const { return mStates.size(); }
    };

}  // namespace hypro
