#pragma once
#include "util.h"
#include "timingUtil.h"
#include "../IHandler.h"
#include "../HandlerFactory.h"
#include "../../../../datastructures/HybridAutomaton/State.h"
#include "../../../../datastructures/reachability/workQueue/WorkQueue.h"
#include "../../../../datastructures/reachability/NodeManager.h"
#include "../../../../datastructures/reachability/ReachTreeNode.h"
#include "../../../../datastructures/reachability/Task.h"
#include "../../../../flags.h"

namespace hypro {

	template<typename State>
	class ltiJumpHandler : public IJumpHandler {
		using Number = typename State::NumberType;

		std::vector<boost::tuple<Transition<Number>*, State>>* mSuccessorBuffer;
		std::shared_ptr<Task<State>> mTask;
		Transition<Number>* mTransition;
		StrategyParameters mStrategy;
		WorkQueue<std::shared_ptr<Task<State>>>* mLocalQueue;
		WorkQueue<std::shared_ptr<Task<State>>>* mLocalCEXQueue;
		EventTimingContainer<Number> mObtainedTimings;

	public:
		ltiJumpHandler() = delete;
		ltiJumpHandler(std::vector<boost::tuple<Transition<Number>*, State>>* successorBuffer,
										std::shared_ptr<Task<State>> task,
										Transition<Number>* transition,
										StrategyParameters strategy,
										WorkQueue<std::shared_ptr<Task<State>>>* localQueue,
										WorkQueue<std::shared_ptr<Task<State>>>* localCEXQueue,
										const EventTimingContainer<typename State::NumberType>& timings)
			: mSuccessorBuffer(successorBuffer)
			, mTask(task)
			, mTransition(transition)
			, mStrategy(strategy)
			, mLocalQueue(localQueue)
			, mLocalCEXQueue(localCEXQueue)
			, mObtainedTimings(timings)
		{}

		void handle();
		const char* handlerName() {return "ltiJumpHandler";}
		std::map<Transition<Number>*, std::vector<State>> applyJump(const std::vector<boost::tuple<Transition<Number>*, State>>& states, Transition<Number>* transition, const StrategyParameters& strategy);
		void aggregate(std::map<Transition<Number>*, std::vector<State>>& processedStates, const std::map<Transition<Number>*, std::vector<State>>& toAggregate, const StrategyParameters& strategy) const;
		typename ReachTreeNode<State>::NodeList_t createNodesFromStates(Transition<Number>* transition, const std::vector<State>& states, std::size_t targetLevel, carl::Interval<tNumber>& coveredTimeInterval, typename ReachTreeNode<State>::Node_t parent);

	};
} // hypro

#include "ltiJumpHandler.tpp"
