/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../IHandler.h"
#include "ltiGuardHandler.h"

namespace hypro {
    template<typename State>
    class timedGuardHandler : public ltiGuardHandler<State> {
        using Number = typename State::NumberType;

    public:
        timedGuardHandler() = delete;

        timedGuardHandler(std::shared_ptr<State> state, size_t index, Transition <Number> *transition)
                : ltiGuardHandler<State>(state, index, transition) {
            // 0.1 because standard before timed of same dimension
            if (SettingsProvider<State>::getInstance().decomposeAutomaton()) {
                this->mSortIndex =
                        0.1 + SettingsProvider<State>::getInstance().getSubspaceDecomposition().at(this->mIndex).size();
            } else {
                this->mSortIndex = 0;
            }
        }

        void handle();

        const char *handlerName() { return "timedGuardHandler"; }

        // 1+ because standard before timed of same dimension
        double getSortIndex() { return this->mSortIndex; }

        void setSortIndex(double sortIndex) { this->mSortIndex = sortIndex; }
    };
}  // namespace hypro

#include "timedGuardHandler.tpp"
