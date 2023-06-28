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
#include "../../../datastructures/reachability/Task.h"
#include "../../../datastructures/reachability/workQueue/WorkQueue.h"
#include "../../../util/logging/Logger.h"
#include "../../../util/plotting/PlotData.h"
#include "../contexts/ContextFactory.h"
#include "../contexts/Exceptions.h"
#include "../contexts/IContext.h"
#include "IWorker.h"

#include <vector>

namespace hypro {

    template<typename State>
    class ContextBasedReachabilityWorker : public IWorker<std::shared_ptr<Task<State>>, State> {
        using Number = typename State::NumberType;
        using TaskType = std::shared_ptr<Task<State>>;

    public:
        ContextBasedReachabilityWorker(const ReachabilitySettings &settings)
                : IWorker<std::shared_ptr<Task<State>>, State>(settings) {
        }

        ~ContextBasedReachabilityWorker() {
        }

        void processTask(const TaskType &t,
                         const Strategy<State> &strat,
                         WorkQueue<TaskType> *localQueue,
                         WorkQueue<TaskType> *localCEXQueue,
                         Flowpipe<State> &localSegments);

        void computeForwardReachability(const TaskType &task,
                                        const Strategy<State> &strat,
                                        WorkQueue<TaskType> *localQueue,
                                        WorkQueue<TaskType> *localCEXQueue,
                                        Flowpipe<State> &localSegments);

        bool isValidTask(const TaskType &task, WorkQueue<TaskType> *localCEXQueue);

    private:
        int mWorkerId;
    };

}  // namespace hypro

#include "ContextBasedReachabilityWorker.tpp"
