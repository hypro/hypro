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
template <typename State>
class RectangularContext : public IContext {
	using Number = typename State::NumberType;
	using TaskType = std::shared_ptr<Task<State>>;

  protected:
	std::shared_ptr<Task<State>> mTask;
	Strategy<State> mStrategy;
	WorkQueue<TaskType>* mLocalQueue;
	WorkQueue<TaskType>* mLocalCEXQueue;
	Flowpipe<State>& mLocalSegments;
	ReachabilitySettings mSettings;

	EventTimingContainer<Number> mLocalTimings;
	HierarchicalIntervalVector<CONTAINMENT, tNumber> mTransitionTimings;

	std::vector<std::tuple<Transition<Number>*, State>> mDiscreteSuccessorBuffer;

	std::map<Transition<Number>*, State> mPotentialZenoTransitions;
	std::vector<Transition<Number>*> mDisabledTransitions;

	tNumber mCurrentLocalTime;
	carl::Interval<tNumber> mCurrentGlobalTimeInterval;
	carl::Interval<tNumber> mCurrentTimeInterval;

	// a copy of the state to perform the computation in, the state in the task is untouched
	State mCurrentSegment;

	// the handlers to process each operation in the specific subset
	// this is a 1:1 relation, for each subset at index I, there is a corresponding handler at index I
	std::vector<IFirstSegmentHandler<State>*> mFirstSegmentHandlers;
	std::vector<IInvariantHandler*> mInvariantHandlers;
	std::vector<IBadStateHandler*> mBadStateHandlers;
	std::vector<ITimeEvolutionHandler*> mContinuousEvolutionHandlers;

	std::map<Transition<Number>*, std::vector<IGuardHandler<State>*>> mTransitionHandlerMap;

  public:
	RectangularContext() = delete;
	~RectangularContext() {}
	RectangularContext( const TaskType& t,
						const Strategy<State>& strat,
						WorkQueue<TaskType>* localQueue,
						WorkQueue<TaskType>* localCEXQueue,
						Flowpipe<State>& localSegments,
						ReachabilitySettings& settings );

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

	bool omitTransition( Transition<Number>* transition );
	bool omitInvariant();
	bool omitBadStateCheck();
};
}  // namespace hypro

#include "RectangularContext.tpp"
