/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * @brief General context interface to set up a reachability worker.
 *
 */

#pragma once

namespace hypro {

    class IContext {
    public:
        // virtual ~IContext(){}

        virtual void execOnStart() {}

        virtual void execBeforeFirstSegment() {}

        virtual void firstSegment() = 0;

        virtual void execAfterFirstSegment() {}

        virtual void execBeforeCheckInvariant() {}

        virtual void checkInvariant() = 0;

        virtual void execAfterCheckInvariant() {}

        virtual void execBeforeIntersectBadStates() {}

        virtual void intersectBadStates() = 0;

        virtual void execAfterIntersectBadStates() {}

        virtual void execBeforeLoop() {}

        virtual bool doneCondition() = 0;

        virtual void execOnLoopItEnter() {}

        virtual void execBeforeCheckTransition() {}

        virtual void checkTransition() = 0;

        virtual void execAfterCheckTransition() {}

        virtual void execBeforeContinuousEvolution() {}

        virtual void applyContinuousEvolution() = 0;

        virtual void execAfterContinuousEvolution() {}

        virtual void execOnLoopItExit() {}

        virtual void execAfterLoop() {}

        virtual void execBeforeProcessDiscreteBehavior() {}

        virtual void processDiscreteBehavior() = 0;

        virtual void execAfterProcessDiscreteBehavior() {}

        virtual void execOnEnd() {}
    };
}  // namespace hypro
