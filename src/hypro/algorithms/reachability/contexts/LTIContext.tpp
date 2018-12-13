#include "LTIContext.h"

namespace hypro
{
	template<typename State>
	LTIContext<State>::LTIContext(const std::shared_ptr<Task<State>>& t,
	                    const Strategy<State>& strat,
	                    WorkQueue<std::shared_ptr<Task<State>>>* localQueue,
	                    WorkQueue<std::shared_ptr<Task<State>>>* localCEXQueue,
	                    std::vector<PlotData<State>>* localSegments,
	                    ReachabilitySettings &settings)
		: mTask(t)
		, mStrategy(strat)
		, mLocalQueue(localQueue)
		, mLocalCEXQueue(localCEXQueue)
		, mLocalSegments(localSegments)
		, mSettings(settings)
		, mTransitionTimings(HierarchicalIntervalVector<CONTAINMENT, tNumber>(std::vector<CONTAINMENT>({CONTAINMENT::BOT, CONTAINMENT::FULL, CONTAINMENT::NO, CONTAINMENT::YES})))
	{
    	mTransitionTimings.initialize(CONTAINMENT::BOT, SettingsProvider<State>::getInstance().getReachabilitySettings().timeBound*SettingsProvider<State>::getInstance().getReachabilitySettings().jumpDepth);
		mComputationState = State(mTask->treeNode->getStateAtLevel(mTask->btInfo.btLevel));
	}

	template<typename State>
	void LTIContext<State>::initalizeFirstSegmentHandlers(){
		TRACE("hypro.worker","Initializing " << mComputationState.getNumberSets() <<" first segment handlers");
		// initialize first segment handlers
		for(std::size_t i = 0; i < mComputationState.getNumberSets();i++){
			mFirstSegmentHandlers.push_back(HandlerFactory<State>::getInstance().buildFirstSegmentHandler(mComputationState.getSetType(i), &mComputationState, i,mStrategy.getParameters(mTask->btInfo.btLevel).timeStep));
			DEBUG("hypro.worker","Built " << mFirstSegmentHandlers.at(i)->handlerName() << "at pos " << i);
		}
	}
	template<typename State>
	void LTIContext<State>::initializeInvariantHandlers(){
		TRACE("hypro.worker","Initializing " << mComputationState.getNumberSets() <<" invariant handlers");
		// initialize invariant handlers
		for(std::size_t i = 0; i < mComputationState.getNumberSets();i++){
			matrix_t<Number> trafo = mFirstSegmentHandlers.at(i)->getTrafo();
			vector_t<Number> translation = mFirstSegmentHandlers.at(i)->getTranslation();
			bool noFlow = (trafo == matrix_t<Number>::Identity(trafo.rows(),trafo.rows()) && translation == vector_t<Number>::Zero(trafo.rows()));
			IInvariantHandler* ptr = HandlerFactory<State>::getInstance().buildInvariantHandler(mComputationState.getSetType(i), &mComputationState, i, noFlow);
			if(ptr){
				mInvariantHandlers.push_back(ptr);
				DEBUG("hypro.worker","Built " << ptr->handlerName() << "at pos " << i);
			}
		}
	}

	template<typename State>
	void LTIContext<State>::initializeBadStateHandlers(){
		TRACE("hypro.worker","Initializing " << mComputationState.getNumberSets() <<" bad state handlers");
		// initalize bad state handlers
		for(std::size_t i = 0; i < mComputationState.getNumberSets();i++){
			matrix_t<Number> trafo = mFirstSegmentHandlers.at(i)->getTrafo();
			vector_t<Number> translation = mFirstSegmentHandlers.at(i)->getTranslation();
			bool noFlow = (trafo == matrix_t<Number>::Identity(trafo.rows(),trafo.rows()) && translation == vector_t<Number>::Zero(trafo.rows()));
			IBadStateHandler* ptr = HandlerFactory<State>::getInstance().buildBadStateHandler(mComputationState.getSetType(i), &mComputationState, i, noFlow);
			if(ptr){
				mBadStateHandlers.push_back(ptr);
				DEBUG("hypro.worker","Built " << ptr->handlerName() << "at pos " << i);
			}
		}
	}

	template<typename State>
	void LTIContext<State>::initializeGuardHandlers(){
		for(Transition<Number>* transition :  mTask->treeNode->getStateAtLevel(mTask->btInfo.btLevel).getLocation()->getTransitions()){
            // handlers for this transition
			std::vector<IGuardHandler<State>*> guardHandlers;

			State* guardStatePtr = new State(mComputationState);
    		std::shared_ptr<State> shGuardPtr= std::shared_ptr<State>(guardStatePtr);
			for(std::size_t i = 0; i < mComputationState.getNumberSets();i++){
				matrix_t<Number> trafo = mFirstSegmentHandlers.at(i)->getTrafo();
				vector_t<Number> translation = mFirstSegmentHandlers.at(i)->getTranslation();
				bool noFlow = (trafo == matrix_t<Number>::Identity(trafo.rows(),trafo.rows()) && translation == vector_t<Number>::Zero(trafo.rows()));
				IGuardHandler<State>* ptr = HandlerFactory<State>::getInstance().buildGuardHandler(guardStatePtr->getSetType(i), shGuardPtr, i, transition, noFlow);
				if(ptr){
					guardHandlers.push_back(ptr);
					DEBUG("hypro.worker","Built " << ptr->handlerName() << "at pos " << i << " for transition " << transition->getSource()->hash() << " -> " << transition->getTarget()->hash());
				}
			}

			//order the handlers according to their sort index
			if(guardHandlers.size()>1){
				std::sort(guardHandlers.begin(),guardHandlers.end(), guardHandlerSorter());
			}

			mTransitionHandlerMap.insert(std::make_pair(transition, guardHandlers));
		}
	}

	template<typename State>
	void LTIContext<State>::applyBacktracking(){
		// ensure backtracking is possible - when we already reached the last level, do nothing.
		if(mTask->btInfo.btLevel + 1 >= mStrategy.size()) {
			// TODO: Make the whole program stop instead of not creating new tasks.
			INFO("benchmark", "Model could NOT be verified as SAFE.");
			DEBUG("hypro.worker","Final bt-level already reached - abort.");
			std::cout << "Model cannot be verified as being safe." << std::endl;
			TRACE("hypro.worker","Unlock node " << mTask->treeNode);
			mTask->treeNode->getMutex().unlock();
			return;
		}

		// Step 1: Find appropriate entry node for refinement
		// Either this is the root node or a node on the path to the current node with a higher bt-level.
		unsigned targetLevel = mTask->btInfo.btLevel + 1;
		Path<Number,tNumber> btPath = mTask->treeNode->getPath();;

		DEBUG("hypro.worker.refinement","Target btLevel: " << targetLevel);
		ReachTreeNode<State>* btNode = mTask->treeNode;
		DEBUG("hypro.worker.refinement","Find backtrack entry node.");
		DEBUG("hypro.worker.refinement", std::this_thread::get_id() << ": Local CEX-Queue size: " << mLocalCEXQueue->size() << "localCEXQueue is now:\n" << (*mLocalCEXQueue));
		TRACE("hypro.worker","Unlock node " << mTask->treeNode);
		btNode->getMutex().unlock();

		// backtrack to the root node. Note that the first processed node is the child of an empty node which collects
		// all initial states. This very root node does have 0 refinements.
		while(btNode->getParent()->getRefinements().size() > 0){
			TRACE("hypro.worker.refinement","Current node on the way to root: " << btNode << ", parent: " << btNode->getParent());
			TRACE("hypro.worker.refinement", "Parent has " << btNode->getParent()->getRefinements().size() << " refinements.");
			btNode = btNode->getParent();
		}
		// reached the root.
		DEBUG("hypro.worker.refinement", std::this_thread::get_id() << ": Reached root.");
		TRACE("hypro.worker.refinement","Target level: " << targetLevel);
		TRACE("hypro.worker.refinement","Num refinements so far: " << btNode->getRefinements().size());
		TRACE("hypro.worker.refinement","Prev. refinement type: " << btNode->getRefinements().at(targetLevel-1).initialSet.getSetType(0));
		TRACE("hypro.worker.refinement","Target representation: " << mStrategy.getParameters(targetLevel).representation_type);


		assert(btNode->getRefinements().size() >= targetLevel);

		if(btNode->getRefinements().size() == targetLevel) {
			// add a new refinement
			RefinementSetting<State> newSetting(btNode->getStateAtLevel(mTask->btInfo.btLevel).getLocation());
			// use initial set of previous run for new level and convert it to new representation.
			newSetting.initialSet = btNode->getStateAtLevel(targetLevel-1);
			for(std::size_t i = 0; i < btNode->getRefinements().at(targetLevel-1).initialSet.getNumberSets(); i++){
				mStrategy.advanceToLevel(newSetting.initialSet, targetLevel);
			}

			newSetting.initialSet.setTimestamp(carl::Interval<tNumber>(0));
			newSetting.isDummy = false;
			newSetting.fullyComputed = false;
			// lock node for modification.
			std::lock_guard<std::mutex> lock(btNode->getMutex());
			btNode->setNewRefinement(targetLevel, newSetting);
			// Todo: re-check -> global timing.
			btNode->setTimestamp(targetLevel, carl::Interval<tNumber>(0));
		}

			// now create a task and add it to the queue.
		std::shared_ptr<Task<State>> taskPtr = std::shared_ptr<Task<State>>(new Task<State>(btNode));
		// set the pos to a time-transition in the node which is the entry point -> During analysis the btPos has to be even, while discrete
		// transitions are the un-even positions in the bt-path.
		taskPtr->btInfo.currentBTPosition = (btNode->getDepth()-1)*2;
		taskPtr->btInfo.btLevel = targetLevel;
		taskPtr->btInfo.btPath = btPath;
		DEBUG("hypro.worker.refinement","Current refinements size of node " << taskPtr->treeNode <<  " : " << taskPtr->treeNode->getRefinements().size());
		assert(!taskPtr->treeNode->getRefinements().at(targetLevel).isDummy);
		DEBUG("hypro.worker.refinement","BT-Path: " << taskPtr->btInfo.btPath);
		// add task
		DEBUG("hypro.worker.refinement", std::this_thread::get_id() << ": Create new CEX-Task (local) with tree node " << taskPtr->treeNode);
		mLocalCEXQueue->nonLockingEnqueue(std::move(taskPtr));
		//DEBUG("hypro.worker", std::this_thread::get_id() << ": Local CEX-Queue size: " << localCEXQueue.size());
		DEBUG("hypro.worker.refinement", std::this_thread::get_id() << ": Local CEX-Queue size: " << mLocalCEXQueue->size() << "localCEXQueue is now:\n" << mLocalCEXQueue);
	}

	template<typename State>
	void LTIContext<State>::execOnStart(){
		INFO("hypro.worker",  std::this_thread::get_id() << ": Compute flow in location " << mTask->treeNode->getStateAtLevel(mTask->btInfo.btLevel).getLocation()->getName() << "(" << mTask->treeNode->getStateAtLevel(mTask->btInfo.btLevel).getLocation()->hash() << ") on strategy level " << mTask->btInfo.btLevel);
		DEBUG("hypro.worker",  std::this_thread::get_id() << ": Process Node address:" << mTask->treeNode);
		DEBUG("hypro.worker",  std::this_thread::get_id() << ": WorkQueue size:" << mLocalQueue->size());
		DEBUG("hypro.worker",  std::this_thread::get_id() << ": Node path:" << mTask->treeNode->getPath());
	    assert(!mTask->treeNode->getTimestamp(mTask->btInfo.btLevel).isEmpty());
	    bool isRefinementTask = (mTask->btInfo.btPath.size() > 0);
	    DEBUG("hypro.worker",  std::this_thread::get_id() << ": Is a backtracking node: " << isRefinementTask);
	    if(isRefinementTask){
	    	DEBUG("hypro.worker",  std::this_thread::get_id() << ": BT-Path: " << mTask->btInfo.btPath);
	    	DEBUG("hypro.worker",  std::this_thread::get_id() << ": BT-Pos:  " << mTask->btInfo.currentBTPosition);
	    }
	    // This assertion always holds since the even positions in a path represent its time transitions and if there is no bt-path, the
	    // bt-pos is set to 0.
	    assert(mTask->btInfo.currentBTPosition % 2 == 0);
	    DEBUG("hypro.worker",  std::this_thread::get_id() << ": Depth: " << mTask->treeNode->getDepth() );
	    DEBUG("hypro.worker",  std::this_thread::get_id() << ": Desired refinement level: " << mTask->btInfo.btLevel);
	    DEBUG("hypro.worker",  std::this_thread::get_id() << ": Number sets (current strategy level): " << mTask->treeNode->getStateAtLevel(mTask->btInfo.btLevel).getNumberSets());
	    DEBUG("hypro.worker",  std::this_thread::get_id() << ": Location: " << mTask->treeNode->getStateAtLevel(mTask->btInfo.btLevel).getLocation()->getName() << "(" << mTask->treeNode->getStateAtLevel(mTask->btInfo.btLevel).getLocation()->hash() << ")");
	    DEBUG("hypro.worker",  std::this_thread::get_id() << ": Time step size (current strategy level): " << carl::toDouble(mStrategy.getParameters(mTask->btInfo.btLevel).timeStep) );
	    DEBUG("hypro.worker",  std::this_thread::get_id() << ": Representation (current strategy level): " << mStrategy.getParameters(mTask->btInfo.btLevel).representation_type );
	    DEBUG("hypro.worker",  std::this_thread::get_id() << ": Refinements:");
	    for(auto& ref : mTask->treeNode->rGetRefinements()){
	    	DEBUG("hypro.worker",  std::this_thread::get_id() << ": " << ref);
	    	// if the timing container is not initialized, initialize it to the maximal possible time bound.
	    	if(!ref.mTimings.isInitialized()) {
	    		ref.mTimings.initialize(SettingsProvider<State>::getInstance().getReachabilitySettings().timeBound*SettingsProvider<State>::getInstance().getReachabilitySettings().jumpDepth);
	    	}
	    }

	    if(isRefinementTask) {
	    	// TODO: Temporary - the pathfinder is buggy. SEE ReachabilityWorker.tpp, also needed?
	    	tNumber tBound = SettingsProvider<State>::getInstance().getReachabilitySettings().timeBound*SettingsProvider<State>::getInstance().getReachabilitySettings().jumpDepth;
	    	mLocalTimings.initialize(tBound);
	    	for(const auto child : mTask->treeNode->getChildren()) {
	    		unsigned latestLevel = child->getLatestFullyComputedLevel();
	    		assert(child->getPath().back().isDiscreteStep());
	    		mLocalTimings.insertTransition(child->getPath().back().transition, carl::Interval<tNumber>(0,tBound), CONTAINMENT::NO);
	    		mLocalTimings.insertTransition(child->getPath().back().transition, child->getPath().back().timeInterval, CONTAINMENT::YES);
	    		TRACE("hypro.worker.timings", "Current transition timings for transition " << child->getPath().back().transition->getSource()->hash() << " -> " << child->getPath().back().transition->getTarget()->hash() << ": " << mLocalTimings.getTransitionTimings(child->getPath().back().transition));
	    	}

	    }

	    initalizeFirstSegmentHandlers();
	}

	template<typename State>
	void LTIContext<State>::execBeforeFirstSegment(){
	    // Check for urgent locations - if enabled we can skip the flow computation. Note that we need to check for multiple urgent transitions.
	    if (mSettings.jumpDepth < 0 || int(mTask->treeNode->getDepth()) <= mSettings.jumpDepth) {
	        bool locallyUrgent = false;

	    	for (auto transition : mTask->treeNode->getStateAtLevel(mTask->btInfo.btLevel).getLocation()->getTransitions()) {
	            // Handle only urgent transitions.
	            if (transition->isUrgent()) {
	            	State guardSatisfyingState(mComputationState);
	            	std::shared_ptr<State> ptr = std::make_shared<State>(guardSatisfyingState);
		        	std::vector<IGuardHandler<State>*> guardHandlers;
		        	TRACE("hypro.worker","Initializing " << mComputationState.getNumberSets() <<" guard handlers for transition " << transition->getSource()->hash() << " -> " << transition->getTarget()->hash());
		        	// create a set of fresh guard handlers for this transition
					for(std::size_t i = 0; i < mComputationState.getNumberSets();i++){
						IGuardHandler<State>* gptr = HandlerFactory<State>::getInstance().buildGuardHandler(guardSatisfyingState.getSetType(i), ptr, i, transition,false);
						if(gptr){
							guardHandlers.push_back(gptr);
							DEBUG("hypro.worker","Built " << gptr->handlerName() << "at pos " << i << " for transition " << transition->getSource()->hash() << " -> " << transition->getTarget()->hash());
						}
					}

					// apply handlers
					bool guardSatisfied = true;
					for(std::size_t i = 0; i < guardHandlers.size();i++){
						guardHandlers.at(i)->handle();
						guardSatisfied &= guardHandlers.at(i)->satisfiesGuard();
						if(!guardSatisfied){
							break;
						}
					}

	                TRACE("hypro.worker.discrete", "Checking urgent transition " << transition->getSource()->hash() << " -> " << transition->getTarget()->hash());
	                // Check if the transition is enabled.
	                if (guardSatisfied) {
	                    // Only jump, if maximal jump depth is not already reached.
	                    if (int(mTask->treeNode->getDepth()) != mSettings.jumpDepth) {
	                        mDiscreteSuccessorBuffer.push_back(boost::tuple<Transition<Number>*, State>(transition, guardSatisfyingState));
	                    }
	                    locallyUrgent = true;
	                }
	            }
	        }
	        // If at least one urgent transition is enabled, skip flow computation.
	        if (locallyUrgent) {
	            TRACE("hypro.worker.discrete", "The location is urgent, skip flowpipe computation.");
				TRACE("hypro.worker","Unlock node " << mTask->treeNode);
	            mTask->treeNode->getMutex().unlock();
	            throw FinishWithDiscreteProcessingException("Urgent transition enabled. Leaving location!");
	        }
	    }


	    #ifdef SINGLE_THREAD_FIXED_POINT_TEST
	    // Check if the initial set satisfies the guard and if so, detect a potential Zeno-cycle.
	    for (auto transition : mTask->treeNode->getStateAtLevel(mTask->btInfo.btLevel).getLocation()->getTransitions()) {

	    	State guardSatisfyingState(mComputationState);
	    	std::shared_ptr<State> ptr = std::make_shared<State>(guardSatisfyingState);
        	std::vector<IGuardHandler<State>*> guardHandlers;
        	// create a set of fresh guard handlers for this transition
			for(std::size_t i = 0; i < mComputationState.getNumberSets();i++){
				IGuardHandler<State>* gptr = HandlerFactory<State>::getInstance().buildGuardHandler(guardSatisfyingState.getSetType(i), ptr, i, transition,false);
				if(gptr){
					guardHandlers.push_back(gptr);
					DEBUG("hypro.worker","Built " << gptr->handlerName() << "at pos " << i << " for transition " << transition->getSource()->getId() << " -> " << transition->getTarget()->getId());
				}
			}

			// apply handlers
			bool guardSatisfied = true;
			for(std::size_t i = 0; i < guardHandlers.size();i++){
				guardHandlers.at(i)->handle();
				guardSatisfied &= guardHandlers.at(i)->satisfiesGuard();
				if(!guardSatisfied){
					break;
				}
			}

	    	if (guardSatisfied) {
	            if (int(mTask->treeNode->getDepth()) != mSettings.jumpDepth+1) {
	                // create artificial path and check for Zeno. The path extension simulates the case that we directly take the respective transition.
	                Path<Number,tNumber> extendedPath = mTask->treeNode->getPath();
	                extendedPath.addTimeStep(carl::Interval<tNumber>(0));
	                extendedPath.addTransition(transition, carl::Interval<tNumber>(0));
	                if(extendedPath.hasChatteringZeno()) {
	                	COUNT("Avoided Zeno path");
	                	mPotentialZenoTransitions.insert(std::make_pair(transition, guardSatisfyingState));
	                }
	            }
	        }
	    }
		#endif
	}

    template<typename State>
	void LTIContext<State>::firstSegment(){
		DEBUG("hypro.worker","State  before first segment: " << mComputationState);

		// applay handlers to state
		for(std::size_t i = 0; i < mComputationState.getNumberSets();i++){
			mFirstSegmentHandlers.at(i)->handle();
		}


    	DEBUG("hypro.worker","State  after first segment: " << mComputationState);
	    initializeInvariantHandlers();
	    initializeBadStateHandlers();
    }

    template<typename State>
	void LTIContext<State>::checkInvariant(){

    	if(mInvariantHandlers.size() > 0){
    		bool deleteRequested = false;
	    	// compute strictes containment on the fly
	    	CONTAINMENT strictestContainment = CONTAINMENT::FULL;
	    	// applay handlers to state
	    	for(std::size_t i = 0; i < mInvariantHandlers.size();i++){
				mInvariantHandlers.at(i)->handle();

				if(mInvariantHandlers.at(i)->getContainment() == CONTAINMENT::NO) {
					TRACE("hypro.worker.continuous","State set " << i << "(type " << mComputationState.getSetType(i) << ") failed the condition - return empty.");
					strictestContainment = mInvariantHandlers.at(i)->getContainment();
					break;
				} else if(mInvariantHandlers.at(i)->getContainment() == CONTAINMENT::PARTIAL) {
					strictestContainment = CONTAINMENT::PARTIAL;
				}

				if(mInvariantHandlers.at(i)->getMarkedForDelete()){
					deleteRequested = true;
				}
			}

		    DEBUG("hypro.worker.continuous", "Valuation fulfills Invariant?: ");
		    DEBUG("hypro.worker.continuous", " " << strictestContainment << std::endl);

		    if (strictestContainment == CONTAINMENT::NO) {
		    	throw FinishWithDiscreteProcessingException("Segment does not fulfill invariant! Terminating worker by processing discrete States.");
		    }

			if(deleteRequested){
				for(auto handler = mInvariantHandlers.begin(); handler != mInvariantHandlers.end(); ){

					if((*handler)->getMarkedForDelete()){
						delete *handler;
						handler = mInvariantHandlers.erase(handler);
					}
					else{
						++handler;
					}
				}
			}
		}

    	DEBUG("hypro.worker","State after intersection with invariant: " << mComputationState);

		// For plotting.
		//#ifdef HYDRA_ENABLE_PLOT
		TRACE("hypro.worker.plot","Add "<<  mComputationState.getSets().size() << "segments for plotting of type " << mComputationState.getSetType() << " and refinement level " << mTask->btInfo.btLevel);
        mLocalSegments->push_back(PlotData<State>(mComputationState, mTask->btInfo.btLevel));
		//#endif
    }

    template<typename State>
	void LTIContext<State>::intersectBadStates(){
    	if(mBadStateHandlers.size()>0){
    		bool deleteRequested = false;

	    	// apply handlers to state
	    	bool intersects = false;
			for(std::size_t i = 0; i < mBadStateHandlers.size();i++){
				mBadStateHandlers.at(i)->handle();
				intersects = mBadStateHandlers.at(i)->intersectsBadState();
				if(intersects){
					break;
				}
				if(mBadStateHandlers.at(i)->getMarkedForDelete()){
					deleteRequested = true;
				}
			}

	    	if (intersects) {
	          	DEBUG("hypro.worker", "Bad states hit");
				mTask->treeNode->rGetRefinements().at(mTask->btInfo.btLevel).hitBadStates = true;
				mTask->treeNode->rGetRefinements().at(mTask->btInfo.btLevel).fullyComputed = true;

		    	// Invoke backtracking. Unlocks the node, so no manual unlocking required
	            applyBacktracking();
	           	throw HardTerminateException("Bad states hit! Terminating this worker!");
	        }

	        if(deleteRequested){
				for(auto handler = mBadStateHandlers.begin(); handler != mBadStateHandlers.end(); ){

					if((*handler)->getMarkedForDelete()){
						delete *handler;
						handler = mBadStateHandlers.erase(handler);
					}
					else{
						++handler;
					}
				}
			}
    	}
    }

    template<typename State>
	void LTIContext<State>::execBeforeLoop(){
		// by now we have a valid first segment. Time to adjust the timings
    	if(SettingsProvider<State>::getInstance().useLocalTiming()) {
    		mComputationState.setTimestamp(carl::Interval<tNumber>(Number(0), mStrategy.getParameters(mTask->btInfo.btLevel).timeStep));
    	} else {
    		TRACE("hypro.worker","State timestamp: " << mTask->treeNode->getStateAtLevel(mTask->btInfo.btLevel).getTimestamp());
    		mComputationState.setTimestamp(mTask->treeNode->getStateAtLevel(mTask->btInfo.btLevel).getTimestamp() + carl::Interval<tNumber>(Number(0),mStrategy.getParameters(mTask->btInfo.btLevel).timeStep));
    	}

    	TRACE("hypro.worker","Set timestamp to " << mComputationState.getTimestamp());
		// The first segment already covers one time step.
	    mCurrentLocalTime = mStrategy.getParameters(mTask->btInfo.btLevel).timeStep;
	    mCurrentGlobalTimeInterval = mComputationState.getTimestamp();
	    mCurrentTimeInterval = carl::Interval<tNumber>(mCurrentLocalTime-mStrategy.getParameters(mTask->btInfo.btLevel).timeStep, mCurrentLocalTime);

	    DEBUG("hypro.worker", "Current global time interval: " << mCurrentGlobalTimeInterval);

	    // the valid first segment also computed the trafo mat and translation vec, we can create timestep handlers now
	    // initialize invariant handlers
	    TRACE("hypro.worker","Initializing " << mComputationState.getNumberSets() <<" continuous evolution handlers");
		for(std::size_t i = 0; i < mComputationState.getNumberSets();i++){
			ITimeEvolutionHandler* ptr = HandlerFactory<State>::getInstance().buildContinuousEvolutionHandler(mComputationState.getSetType(i), &mComputationState, i, mStrategy.getParameters(mTask->btInfo.btLevel).timeStep, mSettings.timeBound, mFirstSegmentHandlers.at(i)->getTrafo(), mFirstSegmentHandlers.at(i)->getTranslation());
			if(ptr){
				mContinuousEvolutionHandlers.push_back(ptr);
				DEBUG("hypro.worker","Built " << ptr->handlerName());
			}
		}
		mEndLoop = (mContinuousEvolutionHandlers.size() == 0);

		initializeGuardHandlers();

		#ifdef SINGLE_THREAD_FIXED_POINT_TEST
        // finish the test for chattering Zeno by intersecting the full initial set with the guard and compare the already stored guard satisfying
        // sets with the intersection of the full set with the guard. If this is the same, we have chattering Zeno.
        for(auto transitionStatePair : mPotentialZenoTransitions) {
        	State potentialZenoState(mComputationState);
        	std::shared_ptr<State> ptr = std::make_shared<State>(potentialZenoState);
        	std::vector<IGuardHandler<State>*> guardHandlers;
        	// create a set of fresh guard handlers for this transition
			for(std::size_t i = 0; i < mComputationState.getNumberSets();i++){
				IGuardHandler<State>* gptr = HandlerFactory<State>::getInstance().buildGuardHandler(potentialZenoState.getSetType(i), ptr, i, transitionStatePair.first,false);
				if(gptr){
					guardHandlers.push_back(gptr);
				}
			}

			// apply handlers
			bool guardSatisfied = true;
			for(std::size_t i = 0; i < guardHandlers.size();i++){
				guardHandlers.at(i)->handle();
				guardSatisfied &= guardHandlers.at(i)->satisfiesGuard();
				if(!guardSatisfied){
					break;
				}
			}

        	if(guardSatisfied) {
        		// explicitly set the timestamp equal, as this cannot be equal. In case the rest is equal, we have chattering Zeno.
        		carl::Interval<tNumber> tmpTimespan = potentialZenoState.getTimestamp();
        		potentialZenoState.setTimestamp(transitionStatePair.second.getTimestamp());
        		bool TODO_RECHECK_THIS = false;
        		//if(potentialZenoState == transitionStatePair.second) {
        		//	std::cout << __func__ << ": Potential Zeno state is truly a Zeno state. Disable for one timestep." << std::endl;
        		mDisabledTransitions.push_back(transitionStatePair.first);
        		//}
        		potentialZenoState.setTimestamp(tmpTimespan);
        	}
        }
		#endif
    }

    template<typename State>
	bool LTIContext<State>::doneCondition(){
    	DEBUG("hypro.worker", "Checking done condition: CurrentLocalTime (" << carl::toDouble(mCurrentLocalTime) << ") > timeBound (" << mSettings.timeBound << ")");
    	return !mEndLoop && (mCurrentLocalTime > mSettings.timeBound);
    }

    template<typename State>
	void LTIContext<State>::checkTransition(){
    	DEBUG("hypro.worker","State before guard intersection: " << mComputationState);
    	// Collect potential new initial states from discrete behaviour.
        if (!(mSettings.jumpDepth < 0 || int(mTask->treeNode->getDepth()) <= mSettings.jumpDepth)) {
        	return;
        }

        std::vector<typename std::map<Transition<Number>*, std::vector<IGuardHandler<State>*> >::iterator> alwaysDisabledTransitions;
        std::vector<typename std::map<Transition<Number>*, std::vector<IGuardHandler<State>*> >::iterator> sortIndexChanged;
        bool urgentTransitionEnabled = false;

    	for(auto it = mTransitionHandlerMap.begin(); it != mTransitionHandlerMap.end(); ++it){

    		#ifdef SINGLE_THREAD_FIXED_POINT_TEST
        	// if the considered transition is disabled (for one iteration), skip the test by starting the next loop iteration.
        	auto disabledTransitionIt = std::find(mDisabledTransitions.begin(), mDisabledTransitions.end(), it->first);
        	if(disabledTransitionIt != mDisabledTransitions.end()) {
        		mDisabledTransitions.erase(disabledTransitionIt);
        		continue;
        	}
			#endif

        	if(!it->first->isUrgent() && omitTransition(it->first)){
        		// store that transition was not enabled for this time interval
            	mTask->treeNode->rGetRefinements().at(mTask->btInfo.btLevel).mTimings.insertTransition(it->first, mCurrentGlobalTimeInterval, CONTAINMENT::NO);
        		continue;
        	}

    		TRACE("hypro.worker","Initializing " << it->second.size() <<" guard handlers for transition " << it->first->getSource()->hash() << " -> " << it->first->getTarget()->hash());

    		State* guardStatePtr = new State(mComputationState);
    		std::shared_ptr<State> shGuardPtr= std::shared_ptr<State>(guardStatePtr);

			for(std::size_t i = 0; i < it->second.size();i++){
				it->second.at(i)->setState(shGuardPtr);
			}

			// apply handlers
			bool guardSatisfied = true;

			if(it->second.size()>0){
				bool deleteRequested = false;
	            //START_BENCHMARK_OPERATION(FULL_CUT);
	            int i = 0;
				for(auto guardIt = it->second.begin(); guardIt != it->second.end();++guardIt){

	           		//START_BENCHMARK_OPERATION(SUBSPACE_CUT);
					(*guardIt)->reinitialize();
					(*guardIt)->handle();
					guardSatisfied &= (*guardIt)->satisfiesGuard();
					//EVALUATE_BENCHMARK_RESULT(SUBSPACE_CUT);

					if(!guardSatisfied &&(strcmp((*guardIt)->handlerName(),"noFlowGuardHandler")==0) ){
						//this transition will never be enabled, remove it from the map
						TRACE("hypro.worker.discrete","noFlowGuardHandler unsatisfied for transition " << it->first->getSource()->hash() << " -> " << it->first->getTarget()->hash() << ". Transition will be removed from further checks.");
						//std::cout << "Guard not satisfied and no Flow handler. Removing Transition." << std::endl;
						alwaysDisabledTransitions.push_back(it);
						deleteRequested = false;
						break;
					}
					// if this guardHandler is not satisfied, it is likely not satisfied next time, so adjust its sortindex to move it to the front
					else if(!guardSatisfied){
						if(i!=0){ //lassen wir einen handler an position 0 mal nicht in den sonnenuntergang reiten
							(*guardIt)->setSortIndex(it->second.at(0)->getSortIndex()-1);
							sortIndexChanged.push_back(it);
						}
						break;
					}
					else if(guardSatisfied && (strcmp((*guardIt)->handlerName(),"noFlowGuardHandler")==0) ){
						// do not recheck again
						(*guardIt)->setMarkedForDelete(true);
						deleteRequested = true;
					}
					i++;
				}
				//EVALUATE_BENCHMARK_RESULT(FULL_CUT);
				if(deleteRequested){
					for(auto handler = it->second.begin(); handler != it->second.end(); ){

						if((*handler)->getMarkedForDelete()){
							delete *handler;
							handler = it->second.erase(handler);
						}
						else{
							++handler;
						}
					}
				}
			}
        	// handle time-triggered transitions
            if (it->first->isUrgent()) {
                TRACE("hypro.worker.discrete", "Checking urgent transition " << it->first->getSource()->hash() << " -> " << it->first->getTarget()->hash());
                if (guardSatisfied) {
                    mDiscreteSuccessorBuffer.push_back(boost::tuple<Transition<Number>*, State>(it->first, *guardStatePtr));
                    urgentTransitionEnabled = true;
                }
            }  // handle normal transitions, but only if they cannot be omitted (they can if the timing intervals do not intersect)
            else if (guardSatisfied) {
                TRACE("hypro.worker.discrete","hybrid transition enabled with timestamp " << guardStatePtr->getTimestamp());

    			DEBUG("hypro.worker","Guard satisfying state: " << *guardStatePtr);
                mDiscreteSuccessorBuffer.push_back(boost::tuple<Transition<Number>*, State>(it->first, *(guardStatePtr)));
                mTask->treeNode->rGetRefinements().at(mTask->btInfo.btLevel).mTimings.insertTransition(it->first, mCurrentGlobalTimeInterval, CONTAINMENT::YES);
            } else {
            	// store that transition was not enabled for this time interval
            	mTask->treeNode->rGetRefinements().at(mTask->btInfo.btLevel).mTimings.insertTransition(it->first, mCurrentGlobalTimeInterval, CONTAINMENT::NO);
            }
    	}
    	for(auto disabledTransition : alwaysDisabledTransitions){
    		mTransitionHandlerMap.erase(disabledTransition);
    	}
    	for(auto sortIterator : sortIndexChanged){
        	//order the handlers according to their sort index
			std::sort(sortIterator->second.begin(),sortIterator->second.end(), guardHandlerSorter());
    	}
        if (urgentTransitionEnabled) {
            // quit loop after firing time triggered transition -> time triggered transitions are handled as urgent.
            TRACE("hypro.worker.discrete", "Urgent transition enabled, quit flowpipe computation immediately." << std::endl);
            throw FinishWithDiscreteProcessingException("Urgent transition enabled, quit flowpipe computation immediately.");
        }
    }

    template<typename State>
	void LTIContext<State>::applyContinuousEvolution(){
    	for(std::size_t i = 0; i < mContinuousEvolutionHandlers.size();i++){
			mContinuousEvolutionHandlers.at(i)->handle();
		}
		mComputationState.setTimestamp(mComputationState.getTimestamp()+mStrategy.getParameters(mTask->btInfo.btLevel).timeStep);
		DEBUG("hypro.worker","State after timestep: " << mComputationState);
    }


    template<typename State>
	void LTIContext<State>::execOnLoopItExit(){
    	mCurrentLocalTime += mStrategy.getParameters(mTask->btInfo.btLevel).timeStep;
        mCurrentTimeInterval += mStrategy.getParameters(mTask->btInfo.btLevel).timeStep;
        mCurrentGlobalTimeInterval += mStrategy.getParameters(mTask->btInfo.btLevel).timeStep;
    }

    template<typename State>
	void LTIContext<State>::processDiscreteBehavior(){
    	DEBUG("hypro.worker",  std::this_thread::get_id() << ": --- Loop left ---" << std::endl);
        DEBUG("hypro.worker.discrete",  std::this_thread::get_id() << ": Process " << mDiscreteSuccessorBuffer.size() << " new initial sets which are leftover." << std::endl);
        TRACE("hypro.worker","Initializing discrete successor handler");
		IJumpHandler* handler = HandlerFactory<State>::getInstance().buildDiscreteSuccessorHandler(&mDiscreteSuccessorBuffer, mTask->treeNode->getRefinements().at(mTask->btInfo.btLevel).initialSet.getSetType(), mTask, nullptr, mStrategy.getParameters(mTask->btInfo.btLevel), mLocalQueue, mLocalCEXQueue);
		TRACE("hypro.worker","Built discrete successor handler of type: " << handler->handlerName());
		handler->handle();
    }

    template<typename State>bool
	LTIContext<State>::omitTransition(Transition<Number>* transition){
    	TRACE("hypro.worker.discrete","Check if transition " << transition << " can be omitted.");
		// the timings for a transition are either empty because this node is not fully computed or because this transition cannot
		// be enabled although the node has been visited before - the first case requires to check the transition while the later
		// allows to omit it.

		// temporary for dbg-output
		carl::Interval<double> tmp = carl::Interval<double>(carl::toDouble(mCurrentGlobalTimeInterval.lower()), carl::toDouble(mCurrentGlobalTimeInterval.upper()));

		if(mTask->btInfo.currentBTPosition < mTask->btInfo.btPath.size() && mTask->btInfo.btPath.at(mTask->btInfo.currentBTPosition + 1).transition != transition) {
			TRACE("hypro.worker.discrete","Cannot Omit transition " << transition->getSource()->getName() << " -> " << transition->getTarget()->getName() << " for time interval " << tmp);
			return false;
		}

		// If there is no recorded event and the node has never been fully computed, we cannot omit the transition. However,
		// if the node has been fully computed but there is no event there never will be a non-spurious event ever and we can savely
		// omit the transition.
		if(!mLocalTimings.hasTransitionEvent(transition) && !mTask->treeNode->isFullyComputedOnSomeLevel()){
			TRACE("hypro.worker.discrete","Cannot Omit transition " << transition->getSource()->getName() << " -> " << transition->getTarget()->getName() << " for time interval " << tmp);
			return false;
		} else if(!mLocalTimings.hasTransitionEvent(transition) && mTask->treeNode->isFullyComputedOnSomeLevel()) {
			TRACE("hypro.worker.discrete","Omit transition " << transition->getSource()->getName() << " -> " << transition->getTarget()->getName() << " for time interval " << tmp);
			return true;
		}

		//if(mTransitionTimings.intersectsEntry(currentTime, CONTAINMENT::NO)) {
		if(mLocalTimings.getTransitionTimings(transition).intersectsEntry(mCurrentGlobalTimeInterval, CONTAINMENT::YES)) {
			TRACE("hypro.worker.discrete","Cannot Omit transition " << transition->getSource()->getName() << " -> " << transition->getTarget()->getName() << " for time interval " << tmp);
			return false;
		}
		TRACE("hypro.worker.discrete","Omit transition " << transition->getSource()->getName() << " -> " << transition->getTarget()->getName() << " for time interval " << tmp);
		return true;
    }

    template<typename State>
	void LTIContext<State>::execOnEnd() {

        // Set the node to be fully computed to avoid re-computation from other tasks (only relevant in case we encounter tasks
    	// concurring for a bt-run [their independent bt-paths share a common prefix which both try to compute/refine]).
    	RefinementSetting<State> updatedRefinementSetting = mTask->treeNode->getRefinements().at(mTask->btInfo.btLevel);
		assert(updatedRefinementSetting.fullyComputed == false);
		updatedRefinementSetting.fullyComputed = true;
		mTask->treeNode->setNewRefinement(mTask->btInfo.btLevel, updatedRefinementSetting);
		TRACE("hypro.worker.refinement",std::this_thread::get_id() << ": Refinements of node " << mTask->treeNode << " after leaving loop:");

		for(const auto& ref : mTask->treeNode->getRefinements()) {
			TRACE("hypro.worker.refinement", std::this_thread::get_id() << ": Node: " << mTask->treeNode << ": " << ref);
		}

		TRACE("hypro.worker.refinement","Done printing refinements.");
		TRACE("hypro.worker","Unlock node " << mTask->treeNode);
		mTask->treeNode->getMutex().unlock();
    }

} // hypro
