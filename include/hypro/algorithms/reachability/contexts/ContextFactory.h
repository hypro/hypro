/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../../datastructures/reachability/Settings.h"
#include "../../../datastructures/reachability/Strategy.h"
#include "../../../datastructures/reachability/Task.h"
#include "../../../datastructures/reachability/workQueue/WorkQueue.h"
#include "../../../util/logging/Logger.h"
#include "../../../util/plotting/PlotData.h"
#include "../workers/IWorker.h"
#include "IContext.h"
#include "LTIContext.h"
#include "TemplatePolyhedronContext.h"
#include "TimedContext.h"

namespace hypro {
    template<typename State>
    class ContextFactory : public carl::Singleton<ContextFactory<State>> {
        using Number = typename State::NumberType;
        friend carl::Singleton<ContextFactory<State>>;

    public:
        IContext *createContext(const std::shared_ptr<Task<State>> &t,
                                const Strategy<State> &strat,
                                WorkQueue<std::shared_ptr<Task<State>>> *localQueue,
                                WorkQueue<std::shared_ptr<Task<State>>> *localCEXQueue,
                                Flowpipe<State> &localSegments,
                                hypro::ReachabilitySettings &settings);

        // Todo: Add destructor and vector which keeps the pointers to the contexts.
    };

}  // namespace hypro

#include "ContextFactory.tpp"
