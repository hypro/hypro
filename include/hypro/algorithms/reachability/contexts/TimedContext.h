/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../../datastructures/HybridAutomaton/decomposition/DecisionEntity.h"
#include "../../../datastructures/reachability/Settings.h"
#include "../../../datastructures/reachability/SettingsProvider.h"
#include "../../../datastructures/reachability/Strategy.h"
#include "../../../datastructures/reachability/Task.h"
#include "../../../datastructures/reachability/timing/EventTimingContainer.h"
#include "../../../datastructures/reachability/workQueue/WorkQueue.h"
#include "../../../util/logging/Logger.h"
#include "../../../util/plotting/PlotData.h"
#include "../handlers/HandlerFactory.h"
#include "../handlers/IHandler.h"
#include "../workers/IWorker.h"
#include "Exceptions.h"
#include "LTIContext.h"

namespace hypro {
    template<typename State>
    class TimedContext : public LTIContext<State> {
        using Number = typename State::NumberType;

    private:
        bool mElapsed;
        State mPreOpState;    // used for comparison with postOpState to determine timings
    public:
        TimedContext() = default;

        ~TimedContext() {}

        TimedContext(const std::shared_ptr<Task<State>> &t,
                     const Strategy<State> &strat,
                     WorkQueue<std::shared_ptr<Task<State>>> *localQueue,
                     WorkQueue<std::shared_ptr<Task<State>>> *localCEXQueue,
                     Flowpipe<State> &localSegments,
                     ReachabilitySettings &settings)
                : LTIContext<State>(t, strat, localQueue, localCEXQueue, localSegments, settings) {
            mElapsed = false;
        }

        virtual void execOnLoopItExit() override;

        virtual bool doneCondition() override;

        virtual void applyContinuousEvolution() override;

        virtual void checkInvariant() override;

        virtual void checkTransition() override;

        /**
         * @brief  Compute the minimum elapsed time interval in a subspace.
         *
         * @param in the current state
         * @param index subspace index
         * @return time interval in that state
         */
        carl::Interval <tNumber> computeShortestElapsedTimeIntervalForSubspace(State &in, size_t index);

        /**
         * @brief  Performs a handshake over all timed subspaces. This is especially important checking for
         *         guard/invariant/badstate intersection. This check ensures that the satisfaction conditions occur
         *         on an intersecting timestamp over all subspaces.
         *
         *         If the timestamps intersect, the subspaces are cut to this intersecting timeframe.
         *         If the timestamps do not intersect, that means that the spaces may all validate their condition,
         *         but they don't validate it during the same time frame. We return an empty timestamp here.
         *
         *         Do not forget to set the returned timestamp on the corresponding state.
         *
         * @param state before operation
         * @param state after operation
         * @return timestamp after operation
         */
        carl::Interval <tNumber> handshakeTimestamps(State &preOp, State &postOp);
    };
}  // namespace hypro

#include "TimedContext.tpp"
