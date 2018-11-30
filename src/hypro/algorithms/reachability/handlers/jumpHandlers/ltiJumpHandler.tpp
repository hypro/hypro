#include "ltiJumpHandler.h"

namespace hypro {

    template<typename State>
    void ltiJumpHandler<State>::handle(){
		std::size_t targetLevel = mTask->btInfo.btLevel;
		bool isRefinementTask = mTask->btInfo.btPath.size() > 0;

		// State stage
		//
		// This stage deals with aggregation and set handling. Only valid states (i.e. non-empty) will be forwarded to the node stage.

		// holds a mapping of transitions to processed (i.e. aggregated or reduced) states
		//START_BENCHMARK_OPERATION(FULL_AGGREGATION);
		std::map<Transition<Number>*, std::vector<State>> processedStates = aggregate(*(mSuccessorBuffer),mTransition,mStrategy);
		//EVALUATE_BENCHMARK_RESULT(FULL_AGGREGATION);

		// At this point the state level processing is complete. Set up nodes. Note that each states timestamp corresponds to the enabled
		// transition time, i.e. use this time to update the path. After that, reset it to zero.

		// Node Stage
		//
		// This stage creates tree nodes and adds them to the tree. The relevant nodes which require further processing will be added as
		// tasks to the corresponding queue.
		for(const auto& transitionStatePair : processedStates) {

			carl::Interval<tNumber> coveredTimeInterval = transitionStatePair.second.begin()->getTimestamp();

			// the collected time interval is required for the timing updates and spans the time interval the transition was enabled
			// irregardless of aggregation settings.
			carl::Interval<tNumber> collectedTimeInterval = transitionStatePair.second.begin()->getTimestamp();
			for(const auto& s : transitionStatePair.second) {
				collectedTimeInterval = collectedTimeInterval.convexHull(s.getTimestamp());
			}

			// children holds the nodes which need to be added
			typename ReachTreeNode<State>::NodeList_t children = createNodesFromStates(transitionStatePair.first, transitionStatePair.second, mRepresentation, targetLevel, coveredTimeInterval, mTask->treeNode);

			// Update tree
			// Note: At this point we have a fresh node with only the refinement set for the dedicated level. In case of a backtrack
			// run, we need to match the node to existing children. In case of a fresh run (no childen), I think we can simply create
			// a new task (depending on the settings, i.e. reset to level 0, we have to modify the node).

			// regular, tree-extending (depth) case, i.e. no backtracking
			// Note: There might be children, but for a different transition, so catch this by the second condition.
			// Note: There can also be children for this transition, but with a whole different timestamp (wavy trajectories).


			if ( !isRefinementTask && isTreeExtension<State>(mTask->treeNode, transitionStatePair.first) ){
				TRACE("hydra.worker.discrete","Regular tree extension.");
				for(const auto& child : children) {
					// if the following is set, copy the refinement to level 0
					#ifdef RESET_REFINEMENTS_ON_CONTINUE_AFTER_BT_RUN
					if(targetLevel > 0) {
						for(auto i = 0; i < targetLevel; ++i){
							if(child->getRefinements()[i].isDummy){
								TRACE("hydra.worker.discrete","Add refinement for level " << i);
								child->convertRefinement(targetLevel, i, SettingsProvider<State>::getInstance().getStrategy().at(i));
							}
						}
					}
					#endif
					mTask->treeNode->addChild(child);

					// timing-tree updates
					INFO("hydra.worker.discrete","Enqueue Tree node " << child << " in local queue.");
					std::shared_ptr<Task<State>> newTask = std::shared_ptr<Task<State>>(new Task<State>(child));
					// if we do not reset to level 0, set refinementLevel of task
					#ifndef RESET_REFINEMENTS_ON_CONTINUE_AFTER_BT_RUN
					newTask->btInfo.btLevel = targetLevel;
					#endif

					if(!isRefinementTask || mTask->btInfo.currentBTPosition == mTask->btInfo.btPath.size()){
						#ifdef SINGLE_THREAD_FIXED_POINT_TEST
						if(!child->getPath().hasChatteringZeno()){
							if(!SettingsProvider<State>::getInstance().useGlobalQueuesOnly()){
								mLocalQueue.nonLockingEnqueue(newTask);
							} else {
								mLocalQueue.enqueue(newTask);
							}
						}
						#else
						if(!SettingsProvider<State>::getInstance().useGlobalQueuesOnly()){
							mLocalQueue.nonLockingEnqueue(std::move(newTask));
						} else {
							mLocalQueue.enqueue(std::move(newTask));
						}
						#endif
					}
				}
				//INFO("hydra.worker.discrete","No backtracking. localQueue is now:\n" << *(mLocalQueue) << "localCEXQueue is now:\n" << *(mLocalCEXQueue));
			} else { // there are already children, which need to be mapped. This is irregardless, whether the current task was a
						// refinement task or not. Upon queuing we decide, whether the new task will be a refinement task or not.
						// Edit: It is not irregardless of backtracking. If there are already children, but it is not a bt-task, these children might
						// be due to some "wavy" trajectory, i.e. the transition can be enabled multiple times with breaks in between.
						// This goes towards chattering behavior.


				TRACE("hydra.worker.discrete","Current->treeNode is: " << mTask->treeNode);

				typename ReachTreeNode<State>::NodeList_t oldChildren = mTask->treeNode->getChildrenForTransition(transitionStatePair.first);

				// collect the time-spans where the transition to existing child nodes was enabled to map new child nodes (update).
				std::vector<carl::Interval<tNumber>> oldTimespans;
				collectTimespansForRefinementLevel<State>(oldTimespans, oldChildren, targetLevel);

				DEBUG("hydra.worker.refinement","For transition " << *transitionStatePair.first << " there are " << oldChildren.size() << " existing relevant children and we attempt to add " << children.size() << " new ones.");
				//DEBUG("hydra.worker.refinement","The pre-defined timespans are " << oldTimespans);

				// now we need to map the children via their timestamp.
				// Note: All this relies on the child-nodes to be sorted ascending in their transition timestamps.
				if(!oldChildren.empty()){
					assert(!oldTimespans.empty());
					preProcess<State>(children, oldTimespans);
					// node updater matches new nodes (children) to existing nodes and creates new Tasks.
					nodeUpdater<State> nu(mTask, mLocalQueue, mLocalCEXQueue, targetLevel);
					nu(children, oldChildren, transitionStatePair.first);
					//matchAndUpdate(children, oldChildren, _current, localCEXQueue);
				} // old children empty

				// at this point either oldChildren or children should be empty (or both).
				assert( oldChildren.empty() || children.empty() );

				// in case there are old children left to map (i.e. we had too many old children and already mapped all new ones)
				// set the remaining old children for the target level to dummy.
				if(!oldChildren.empty()){
					for(auto oldChildIt = oldChildren.begin(); oldChildIt != oldChildren.end(); ++oldChildIt) {
						RefinementSetting<State> dummyRefinement;
						dummyRefinement.isDummy = true;
						TRACE("hydra.worker.refinement","Old child " << *oldChildIt << " not required. Set level " << mTask->btInfo.btLevel << " to dummy.");
						(*oldChildIt)->setNewRefinement(mTask->btInfo.btLevel,dummyRefinement);
					}
				}

				// in case there are more new children than old children have been, add new ones as fresh nodes.
				insertAndCreateTask(children, mTask, mLocalQueue, mLocalCEXQueue, targetLevel);

			} // case when there are already children in the tree which need to be updated and mapped.
		} // loop over processed states
		// When all sets are processed clear _newInitialSets
		if(mTransition == nullptr) {
			mSuccessorBuffer->clear();
		} else {
			// in case only one transition was processed, only delete its nodes.
			// Todo: Attention, can it happen, that the transition is already in that set due to previous reasons?
			for(auto tupleIt = mSuccessorBuffer->begin(); tupleIt != mSuccessorBuffer->end(); ) {
				if( boost::get<0>(*tupleIt) == mTransition ) {
					tupleIt = mSuccessorBuffer->erase(tupleIt);
				} else {
					++tupleIt;
				}
			}
		}
	}

	template<typename State>
	std::map<Transition<typename State::NumberType>*, std::vector<State>> ltiJumpHandler<State>::aggregate(const std::vector<boost::tuple<Transition<Number>*, State>>& states, Transition<Number>* transition, const StrategyParameters& strategy){
		// holds a mapping of transitions to states which need to be processed (i.e. aggregated)
		std::map<Transition<Number>*, std::vector<State>> toAggregate;
		// holds a mapping of transitions to processed (i.e. aggregated or reduced) states
		std::map<Transition<Number>*, std::vector<State>> processedStates;
		for (const auto& tuple : states) {
			// only handle sets related to the passed transition, in case any is passed.
			if(transition == nullptr || boost::get<0>(tuple) == transition) {

				// check aggregation settings
				if ( (strategy.aggregation == AGG_SETTING::NO_AGG && strategy.clustering == -1)||
					(strategy.aggregation == AGG_SETTING::MODEL && boost::get<0>(tuple)->getAggregation() == Aggregation::none)) {
					// copy state - as there is no aggregation, the containing set and timestamp is already valid
					assert(!boost::get<1>(tuple).getTimestamp().isEmpty());
					State newState(boost::get<1>(tuple));
					// apply reset function
					int i = 0;
					for(auto trafo : boost::get<0>(tuple)->getReset().getResetTransformations()){
						TRACE("hydra.worker.discrete","Reset transformation " << i << ": " << trafo );
						i++;
					}

					for(size_t i = 0; i < newState.getNumberSets(); i++){
						matrix_t<Number> trafo = boost::get<0>(tuple)->getReset().getResetTransformations().at(i).matrix();
						vector_t<Number> translation = boost::get<0>(tuple)->getReset().getResetTransformations().at(i).vector();

						IResetHandler* ptr = HandlerFactory<State>::getInstance().buildResetHandler(newState.getSetType(i), &newState, i, trafo,translation);
						if(ptr){
							ptr->handle();
							DEBUG("hydra.worker","Applied " << ptr->handlerName() << "at pos " << i);
						}
					}

					// check invariant in new location
					newState.setLocation(boost::get<0>(tuple)->getTarget());
					bool strictestContainment = true;
					for(std::size_t i = 0; i < newState.getNumberSets();i++){

						IInvariantHandler* ptr = HandlerFactory<State>::getInstance().buildInvariantHandler(newState.getSetType(i), &newState, i, false);
						if(ptr){
							ptr->handle();
							DEBUG("hydra.worker","Applied " << ptr->handlerName() << "at pos " << i);
							if(ptr->getContainment() == CONTAINMENT::NO) {
								TRACE("hydra.worker.continuous","State set " << i << "(type " << newState.getSetType(i) << ") failed the condition - return empty.");
								strictestContainment = false;
								break;
							}
						}
					}

					if(strictestContainment == false) {
						newState.setLocation(boost::get<0>(tuple)->getSource());
						TRACE("hydra.worker.discrete","Transition disabled as the new initial set does not satisfy the invariant of the target location.")
						continue;
					}

					// reduce if possible (Currently only for support functions)
					// TODO why does the reduction visitor not work for multi sets?
					for(size_t i = 0; i < newState.getNumberSets(); i++){
						if(newState.getSetType(i) == representation_name::support_function){
							auto tmpHPoly = boost::apply_visitor(genericConvertAndGetVisitor<HPolytope<typename State::NumberType>>(), newState.getSet(i));
							//auto tmpHPoly = Converter<Number>::toHPolytope(boost::get<SupportFunction<Number>>(newState.getSet(i)));
							SupportFunction<Number> newSet(tmpHPoly.matrix(), tmpHPoly.vector());
							// convert to actual support function inside the state, which might have different settings == different type.
							newState.setSet(boost::apply_visitor(genericInternalConversionVisitor<typename State::repVariant, SupportFunction<Number>>(newSet), newState.getSet(i)),i);
						}
					}


					DEBUG("hydra.worker.discrete","State after reduction: " << newState);

					// Note: Here we misuse the state's timestamp to carry the transition timing to the next stage -> just don't reset
					// the timestamp in case no aggregation happens.

					if (processedStates.find(boost::get<0>(tuple)) == processedStates.end()) {
						processedStates[boost::get<0>(tuple)] = std::vector<State>();
					}
					processedStates[boost::get<0>(tuple)].emplace_back(newState);

				} else {  // store for aggregation
					// TODO: Note that all sets are collected for one transition, i.e. currently, if we intersect the guard for one transition twice with
					// some sets in between not satisfying the guard, we still collect all guard satisfying sets for that transition.
					// Note: Whenever such a "chunk" is complete we call this method. However we need to treat this on node stage.
					if (toAggregate.find(boost::get<0>(tuple)) == toAggregate.end()) {
						toAggregate[boost::get<0>(tuple)] = std::vector<State>();
					}
					toAggregate[boost::get<0>(tuple)].emplace_back(boost::get<1>(tuple));
				}
			}
		}

		// Aggregation
		DEBUG("hydra.worker.discrete", "Number of transitions to aggregate: " << toAggregate.size() << std::endl);
		for (const auto& transitionStatePair : toAggregate) {
			assert(!transitionStatePair.second.empty());
			TRACE("hydra.worker.discrete",transitionStatePair.second.size() << " sets to aggregate for transition " << transitionStatePair.first->getSource()->getName() << " -> " << transitionStatePair.first->getTarget()->getName());
			std::vector<State> aggregatedStates;
			// Aggregate sets by using sequential unite operations (TODO: Implement and make use of multi-unite).
			State aggregatedState(*transitionStatePair.second.begin());
			// counts the number of processed sets - just for debugging.
			unsigned setCnt = 1;
			// counts the number of sets in the current cluster.
			std::size_t clusterCnt = 1;
			// determines whether there are still sets to be clustered together.
			bool leftovers = true;

			std::vector<SUBSPACETYPE> types = *(SettingsProvider<State>::getInstance().getLocationSubspaceTypeMap().find(aggregatedState.getLocation())->second);
			// perform union directly on the current set vector to avoid an extreme amount of consistency checks
			std::vector<typename State::repVariant> currentSets = aggregatedState.getSets();
			//START_BENCHMARK_OPERATION(AGGREGATE);
			for (auto stateIt = ++transitionStatePair.second.begin(); stateIt != transitionStatePair.second.end(); ++stateIt) {
				assert(!(*stateIt).getTimestamp().isEmpty());
				TRACE("hydra.worker.discrete","Agg. aggState and set " << setCnt);
				// actual aggregation.
				for(std::size_t i = 0; i < aggregatedState.getNumberSets(); i++){
					if(types.at(i) == SUBSPACETYPE::DISCRETE){
						// in discrete subspaces, the set does not change
						continue;
					}
					else{
						//START_BENCHMARK_OPERATION(UNION);
						currentSets[i] = boost::apply_visitor(genericUniteVisitor<typename State::repVariant>(),currentSets[i], stateIt->getSet(i));
						//EVALUATE_BENCHMARK_RESULT(UNION);
					}
				}

				leftovers = true;
				++setCnt;
				++clusterCnt;
				#ifdef CLUSTERING_NUMBER_LIMITS_SUCESSORS
				if(strategy.clustering > 0 && clusterCnt == std::ceil(double(transitionStatePair.second.size())/double(strategy.clustering))) {
					TRACE("hydra.worker.discrete","Clustering.");
					aggregatedStates.emplace_back(aggregatedState);
					leftovers = false;
					if(stateIt+1 != transitionStatePair.second.end()) {
						aggregatedState = *(++stateIt);
						clusterCnt = 1;
					} else {
						break;
					}
				}
				#else
				if(strategy.clustering > 0 && clusterCnt == std::size_t(strategy.clustering)) {
					TRACE("hydra.worker.discrete","Clustering.");
					aggregatedStates.emplace_back(aggregatedState);
					leftovers = false;
					if(stateIt+1 != transitionStatePair.second.end()) {
						aggregatedState = *(++stateIt);
						clusterCnt = 1;
					} else {
						break;
					}
				}
				#endif
			}
			aggregatedState.setSets(currentSets);
			//EVALUATE_BENCHMARK_RESULT(AGGREGATE);

			if(strategy.clustering < 1 || leftovers) {
				TRACE("hydra.worker.discrete","No clustering.");
				aggregatedStates.emplace_back(aggregatedState);
			}

			// handle resets and invariant checks for the new location for each cluster independently.
			for(auto& state : aggregatedStates) {
				DEBUG("hydra.worker.discrete", "Aggregated timestamp after aggregation " << state.getTimestamp());
				carl::Interval<tNumber> aggregatedTimestamp = state.getTimestamp();


				#ifdef HYDRA_USE_LOGGING
				int i = 0;
				for(auto trafo : transitionStatePair.first->getReset().getResetTransformations()){
					TRACE("hydra.worker.discrete","Reset transformation " << i << ": " << trafo );
					i++;
				}
				// DBG
				for(size_t i = 0; i < state.getNumberSets(); i++){
					Box<Number> tmp = boost::get<Box<Number>>(boost::apply_visitor(genericConversionVisitor<RepresentationVariant, Number>(representation_name::box),state.getSet(i)));
					DEBUG("hydra.worker.discrete","Subspace set before reset: " << tmp);
				}
				#endif

				DEBUG("hydra.worker.discrete","Set before reset: " << state);
				//START_BENCHMARK_OPERATION(RESET);
				// apply resets to aggregated state
				for(size_t i = 0; i < state.getNumberSets(); i++){
					matrix_t<Number> trafo = transitionStatePair.first->getReset().getResetTransformations().at(i).matrix();
					vector_t<Number> translation = transitionStatePair.first->getReset().getResetTransformations().at(i).vector();

					IResetHandler* ptr = HandlerFactory<State>::getInstance().buildResetHandler(state.getSetType(i), &state, i, trafo,translation);
					if(ptr){
						ptr->handle();
						DEBUG("hydra.worker.discrete","Applied " << ptr->handlerName() << "at pos " << i);
					}
				}
				//EVALUATE_BENCHMARK_RESULT(RESET);
				DEBUG("hydra.worker.discrete","Set after reset: " << state);


				#ifdef HYDRA_USE_LOGGING
				// DBG
				for(size_t i = 0; i < state.getNumberSets(); i++){
					Box<Number> tmp = boost::get<Box<Number>>(boost::apply_visitor(genericConversionVisitor<RepresentationVariant, Number>(representation_name::box),state.getSet(i)));
					DEBUG("hydra.worker.discrete","Subspace set after reset: " << tmp);
				}
				#endif


				// check if invariant is satisfied in the target location.
				state.setLocation(transitionStatePair.first->getTarget());

				//START_BENCHMARK_OPERATION(TARGET_INVARIANT);
				bool strictestContainment = true;
				for(std::size_t i = 0; i < state.getNumberSets();i++){
					IInvariantHandler* ptr = HandlerFactory<State>::getInstance().buildInvariantHandler(state.getSetType(i), &state, i, false);
					if(ptr){
						ptr->handle();
						DEBUG("hydra.worker.discrete","Applied " << ptr->handlerName() << "at pos " << i);
						if(ptr->getContainment() == CONTAINMENT::NO) {
							TRACE("hydra.worker.discrete","State set " << i << "(type " << state.getSetType(i) << ") failed the condition - return empty.");
							strictestContainment = false;
							break;
						}
					}
				}

				//std::pair<bool,State> validStatePair = state.satisfies(transitionStatePair.first->getTarget()->getInvariant());

				if(strictestContainment == false) {
					state.setLocation(transitionStatePair.first->getSource());
					TRACE("hydra.worker.discrete","Transition disabled as the new initial set does not satisfy the invariant of the target location.")
					continue;
				}
				//EVALUATE_BENCHMARK_RESULT(TARGET_INVARIANT);

					// apply reduction if possible (currently only support function -> see visitor implementation in Visitor.h)
				// TODO why does the reduction visitor not work for multi sets?
				for(size_t i = 0; i < state.getNumberSets(); i++){
					if(state.getSetType(i) == representation_name::support_function){
						auto tmpHPoly = boost::apply_visitor(genericConvertAndGetVisitor<HPolytope<typename State::NumberType>>(), state.getSet(i));
						SupportFunction<Number> newSet(tmpHPoly.matrix(), tmpHPoly.vector());
						// convert to actual support function inside the state, which might have different settings == different type.
						state.setSet(boost::apply_visitor(genericInternalConversionVisitor<typename State::repVariant, SupportFunction<Number>>(newSet), state.getSet(i)),i);
					}
				}

				#ifdef HYDRA_USE_LOGGING
				// DBG
				for(size_t i = 0; i < state.getNumberSets(); i++){
					Box<Number> tmp = boost::get<Box<Number>>(boost::apply_visitor(genericConversionVisitor<RepresentationVariant, Number>(representation_name::box),state.getSet(i)));
					TRACE("hydra.worker.discrete","Subspace set after reduction: " << tmp);
				}
				#endif
				// Note: Here we misuse the state's timestamp to carry the transition timing to the next stage
				// Note 2: If we use global timing, this is correct.
				state.setTimestamp(aggregatedTimestamp);

				if (processedStates.find(transitionStatePair.first) == processedStates.end()) {
					processedStates[transitionStatePair.first] = std::vector<State>();
				}
				processedStates[transitionStatePair.first].emplace_back(state);
			}
		}

		return processedStates;
	}

	template<typename State>
	typename ReachTreeNode<State>::NodeList_t ltiJumpHandler<State>::createNodesFromStates(
		Transition<Number>* transition, const std::vector<State>& states,
		representation_name repName, std::size_t targetLevel,
		carl::Interval<tNumber>& coveredTimeInterval, typename ReachTreeNode<State>::Node_t parent){

		typename ReachTreeNode<State>::NodeList_t children;
		for(const auto& state : states) {

			//fix point test does not seem to work in full timed context
			if(!SettingsProvider<State>::getInstance().isFullTimed() && SettingsProvider<State>::getInstance().getLocationTypeMap().find(transition->getSource())->second != LOCATIONTYPE::TIMEDLOC){
				bool reachedFixedPoint = false;
				if(SettingsProvider<State>::getInstance().useFixedPointTest()) {
					for(const auto n : NodeManager<State>::getInstance().getTree().getRoot()->getChildren()) {
						reachedFixedPoint = n->hasFixedPoint(state,parent);
						if(reachedFixedPoint){
							std::cout << "Detected fixed point." << std::endl;
							break;
						}
					}
				}

				if(reachedFixedPoint) {
					continue;
				}
			}

			typename ReachTreeNode<State>::Node_t newNode = new ReachTreeNode<State>(state, targetLevel, parent);

			// collect covered time interval
			coveredTimeInterval = coveredTimeInterval.convexHull(state.getTimestamp());

			// set up node properties
			newNode->addTimeStepToPath(state.getTimestamp());
			newNode->addTransitionToPath(transition, state.getTimestamp());
			newNode->setDepth(parent->getDepth() + 1);
			newNode->setTimestamp(targetLevel, state.getTimestamp());

			// Todo: In general: switch to in-place modifications for the child-nodes later as well.
			RefinementSetting<State> tmpRefinement = newNode->getRefinements().at(targetLevel);
			if(SettingsProvider<State>::getInstance().useLocalTiming()) {
				tmpRefinement.initialSet.setTimestamp(carl::Interval<tNumber>(0));
			}

			tmpRefinement.isDummy = false;
			newNode->setNewRefinement(targetLevel,tmpRefinement);
			assert(!newNode->getTimestamp(targetLevel).isEmpty());

			DEBUG("hydra.worker.discrete","New node path: " << newNode->getPath());
			DEBUG("hydra.worker.discrete", "new jump depth: " << newNode->getDepth());
			DEBUG("hydra.worker.discrete", "new refinements size: " << newNode->getRefinements().size());
			children.emplace_back(newNode);
		}
		return children;
	}

} // hypro
