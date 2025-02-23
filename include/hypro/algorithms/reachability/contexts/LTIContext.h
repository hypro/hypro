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
#include "../../../datastructures/reachability/timing/EventTimingProvider.h"
#include "../../../datastructures/reachability/workQueue/WorkQueue.h"
#include "../../../util/conversion.h"
#include "../../../util/logging/Logger.h"
#include "../../../util/plotting/PlotData.h"
#include "../handlers/HandlerFactory.h"
#include "../handlers/IHandler.h"
#include "../handlers/guardHandlers/GuardHandlers.h"
#include "../workers/IWorker.h"
#include "Exceptions.h"
#include "IContext.h"

#include <tuple>

namespace hypro {
    template<typename State>
    class LTIContext : public IContext {
        using Number = typename State::NumberType;
        using TaskType = std::shared_ptr<Task<State>>;

    protected:
        std::shared_ptr<Task<State>> mTask;
        Strategy<State> mStrategy;
        WorkQueue<TaskType> *mLocalQueue;
        WorkQueue<TaskType> *mLocalCEXQueue;
        Flowpipe<State> &mLocalSegments;
        ReachabilitySettings mSettings;

        EventTimingContainer<Number> mLocalTimings;
        HierarchicalIntervalVector<CONTAINMENT, tNumber> mTransitionTimings;

        std::vector<std::tuple<Transition<Number> *, State>> mDiscreteSuccessorBuffer;

        std::map<Transition<Number> *, State> mPotentialZenoTransitions;
        std::vector<Transition<Number> *> mDisabledTransitions;

        tNumber mCurrentLocalTime;
        carl::Interval <tNumber> mCurrentGlobalTimeInterval;
        carl::Interval <tNumber> mCurrentTimeInterval;

        // a copy of the state to perform the computation in, the state in the task is untouched
        State mComputationState;

        // the handlers to process each operation in the specific subset
        // this is a 1:1 relation, for each subset at index I, there is a corresponding handler at index I
        std::vector<IFirstSegmentHandler<State> *> mFirstSegmentHandlers;
        std::vector<IInvariantHandler *> mInvariantHandlers;
        std::vector<IBadStateHandler *> mBadStateHandlers;
        std::vector<ITimeEvolutionHandler *> mContinuousEvolutionHandlers;

        std::map<Transition<Number> *, std::vector<IGuardHandler<State> *>> mTransitionHandlerMap;

    public:
        LTIContext() = delete;

        ~LTIContext() {}

        LTIContext(const TaskType &t,
                   const Strategy<State> &strat,
                   WorkQueue<TaskType> *localQueue,
                   WorkQueue<TaskType> *localCEXQueue,
                   Flowpipe<State> &localSegments,
                   ReachabilitySettings &settings);

        virtual void execOnStart() override;

        virtual void execBeforeFirstSegment() override;

        virtual void firstSegment() override;

        virtual void execAfterFirstSegment() override;

        virtual void checkInvariant() override;

        virtual void intersectBadStates() override;

        virtual void execBeforeLoop() override;

        virtual bool doneCondition() override;

        virtual void checkTransition() override;

        virtual void applyContinuousEvolution() override;

        virtual void execOnLoopItExit() override;

        virtual void processDiscreteBehavior() override;

        virtual void execOnEnd() override;

        void initalizeFirstSegmentHandlers();

        void initializeInvariantHandlers();

        void initializeBadStateHandlers();

        void initializeGuardHandlers();

        void applyBacktracking();

        bool omitTransition(Transition<Number> *transition);

        bool omitInvariant();

        bool omitBadStateCheck();
    };
}  // namespace hypro

#include "LTIContext.tpp"
