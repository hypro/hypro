#pragma once

#include "IContext.h"
#include "../handlers/IHandler.h"
#include "../handlers/HandlerFactory.h"
#include "../handlers/guardHandlers/GuardHandlers.h"
#include "../workers/IWorker.h"
#include "../../../datastructures/reachability/workQueue/WorkQueue.h"
#include "../../../datastructures/reachability/Settings.h"
#include "../../../datastructures/reachability/SettingsProvider.h"
#include "../../../datastructures/reachability/Task.h"
#include "../../../datastructures/reachability/timing/EventTimingContainer.h"
#include "../../../datastructures/HybridAutomaton/decomposition/DecisionEntity.h"
#include "../../../util/logging/Logger.h"
#include "../../../util/PlotData.h"

namespace hypro
{
	template<typename Number>
	class LTIContext : public IContext{
	protected:
		std::shared_ptr<Task<Number>> mTask;
		std::vector<StrategyNode> mStrategy;
		WorkQueue<std::shared_ptr<Task<Number>>>* mLocalQueue;
		WorkQueue<std::shared_ptr<Task<Number>>>* mLocalCEXQueue;
	    std::vector<PlotData<Number>>* mLocalSegments;
	    ReachabilitySettings mSettings;

	    EventTimingContainer<Number> mLocalTimings;
    	HierarchicalIntervalVector<CONTAINMENT, tNumber> mTransitionTimings;


   		std::vector<boost::tuple<Transition<Number>*, State_t<Number>>> mDiscreteSuccessorBuffer;

	    std::map<Transition<Number>*, State_t<Number>> mPotentialZenoTransitions;
	    std::vector<Transition<Number>*> mDisabledTransitions;

   		tNumber mCurrentLocalTime;
   		carl::Interval<tNumber> mCurrentGlobalTimeInterval;
	    carl::Interval<tNumber> mCurrentTimeInterval;

        // a copy of the state to perform the computation in, the state in the task is untouched
        State_t<Number> mComputationState; 

        // the handlers to process each operation in the specific subset
        // this is a 1:1 relation, for each subset at index I, there is a corresponding handler at index I
        std::vector<IFirstSegmentHandler<Number>*> mFirstSegmentHandlers;
        std::vector<IInvariantHandler*> mInvariantHandlers;      
        std::vector<IBadStateHandler*> mBadStateHandlers;   
        std::vector<ITimeEvolutionHandler*> mContinuousEvolutionHandlers;

        std::map<Transition<Number>*, std::vector<IGuardHandler<Number>*>> mTransitionHandlerMap;

        bool mEndLoop = false;


	public:
		LTIContext() = default;
		~LTIContext(){}
		LTIContext(const std::shared_ptr<Task<Number>>& t,
	                    const std::vector<StrategyNode>& strat,
	                    WorkQueue<std::shared_ptr<Task<Number>>>* localQueue,
	                    WorkQueue<std::shared_ptr<Task<Number>>>* localCEXQueue,
	                    std::vector<PlotData<Number>>* localSegments,
	                    ReachabilitySettings &settings);

		virtual void execOnStart() override ;

		virtual void execBeforeFirstSegment() override;

	    virtual void firstSegment() override ;

	    virtual void checkInvariant() override ;

	    virtual void intersectBadStates() override ;

	    virtual void execBeforeLoop() override;
	    
	    virtual bool doneCondition() override ;

	    virtual void checkTransition() override ;

	    virtual void applyContinuousEvolution() override ;

	    virtual void execOnLoopItExit() override;

	    virtual void processDiscreteBehavior() override ;

	    virtual void execOnEnd() override;

	    void initalizeFirstSegmentHandlers();
	    void initializeInvariantHandlers();
	    void initializeBadStateHandlers();
	    void initializeGuardHandlers();

	    void applyBacktracking();

	    bool omitTransition(Transition<Number>* transition);
	};
} // hypro

#include "LTIContext.tpp"