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
#include "../IHandler.h"
#include "ltiTimeEvolutionHandler.h"

namespace hypro {
/**
 * used when a timedFirstSegmentHandler was used. It does a tick on first segment and is used if the automaton
 * is not full timed
 */
    template<typename State>
    class timedElapseAfterTickTimeEvolutionHandler : public ltiTimeEvolutionHandler<State> {
        using Number = typename State::NumberType;

    protected:
        bool mComputed;
        tNumber mTimeBound;

    public:
        timedElapseAfterTickTimeEvolutionHandler() = delete;

        timedElapseAfterTickTimeEvolutionHandler(State *state, size_t index, tNumber timeStep, tNumber timeBound,
                                                 hypro::matrix_t<Number> trafo, hypro::vector_t<Number> translation)
                : ltiTimeEvolutionHandler<State>(state, index, timeStep, trafo, translation) {
            mComputed = false;
            mTimeBound = timeBound;
        }

        void handle();

        const char *handlerName() { return "timedElapseContinuousEvolutionHandler"; }

        bool getMarkedForDelete() { return false; };

        void setMarkedForDelete(bool) { /*no op*/ };
    };
}  // namespace hypro

#include "timedElapseAfterTickTimeEvolutionHandler.tpp"
