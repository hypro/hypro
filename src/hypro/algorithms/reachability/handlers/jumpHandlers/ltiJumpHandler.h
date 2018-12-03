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

namespace hypro {

	template<typename State>
	class ltiJumpHandler : public IJumpHandler {
		using Number = typename State::NumberType;

		std::vector<boost::tuple<Transition<Number>*, State>>* mSuccessorBuffer;
		representation_name mRepresentation;
		std::shared_ptr<Task<State>> mTask;
		Transition<Number>* mTransition;
		StrategyParameters mStrategy;
		WorkQueue<std::shared_ptr<Task<State>>>* mLocalQueue;
		WorkQueue<std::shared_ptr<Task<State>>>* mLocalCEXQueue;

	public:
		ltiJumpHandler() = delete;
		ltiJumpHandler(std::vector<boost::tuple<Transition<Number>*, State>>* successorBuffer,
										representation_name representation,
										std::shared_ptr<Task<State>> task,
										Transition<Number>* transition,
										StrategyParameters strategy,
										WorkQueue<std::shared_ptr<Task<State>>>* localQueue,
										WorkQueue<std::shared_ptr<Task<State>>>* localCEXQueue)
			: mSuccessorBuffer(successorBuffer)
			, mRepresentation(representation)
			, mTask(task)
			, mTransition(transition)
			, mStrategy(strategy)
			, mLocalQueue(localQueue)
			, mLocalCEXQueue(localCEXQueue)
		{}

		void handle();
		const char* handlerName() {return "ltiJumpHandler";}
		std::map<Transition<Number>*, std::vector<State>> aggregate(const std::vector<boost::tuple<Transition<Number>*, State>>& states, Transition<Number>* transition, const StrategyParameters& strategy);
		typename ReachTreeNode<State>::NodeList_t createNodesFromStates(Transition<Number>* transition, const std::vector<State>& states, representation_name repName, std::size_t targetLevel, carl::Interval<tNumber>& coveredTimeInterval, typename ReachTreeNode<State>::Node_t parent);

	};
} // hypro

#include "ltiJumpHandler.tpp"
