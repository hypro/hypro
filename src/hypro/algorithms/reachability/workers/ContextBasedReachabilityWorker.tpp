#include "ContextBasedReachabilityWorker.h"


namespace hypro
{

template<typename State>
void ContextBasedReachabilityWorker<State>::processTask(const std::shared_ptr<Task<State>>& t,
                                                const Strategy<State>& strat,
                                                WorkQueue<std::shared_ptr<Task<State>>>& localQueue,
                                                WorkQueue<std::shared_ptr<Task<State>>>& localCEXQueue,
                                                std::vector<PlotData<Number>>* localSegments){

    //INFO("hydra.worker",  std::this_thread::get_id() << ": Current btLevel: " << t->btInfo.btLevel << " and refinements size: " << t->treeNode->getRefinements().size());
    if(isValidTask(t,localCEXQueue)){
        computeForwardReachability(t,strat,localQueue,localCEXQueue,localSegments);
    }
}



template<typename State>
void ContextBasedReachabilityWorker<State>::computeForwardReachability(const std::shared_ptr<Task<State>>& task,
                                                                const Strategy<State>& strat,
                                                                WorkQueue<std::shared_ptr<Task<State>>>& localQueue,
                                                                WorkQueue<std::shared_ptr<Task<State>>>& localCEXQueue,
                                                                std::vector<PlotData<Number>>* localSegments){

    IContext* context = ContextFactory<State>::getInstance().createContext(task, strat, &localQueue, &localCEXQueue, localSegments, this->mSettings);

    try{
        context->execOnStart();

        //START_BENCHMARK_OPERATION(FIRST_SEGMENT);
        // compute first segment
        context->execBeforeFirstSegment();
        context->firstSegment();
        context->execAfterFirstSegment();
        //EVALUATE_BENCHMARK_RESULT(FIRST_SEGMENT);


        //START_BENCHMARK_OPERATION(CHECK_INVARIANT);
        // intersect with invariant
        context->execBeforeCheckInvariant();
        context->checkInvariant();
        context->execAfterCheckInvariant();
        //EVALUATE_BENCHMARK_RESULT(CHECK_INVARIANT);

        //START_BENCHMARK_OPERATION(INTERSECT_BAD_STATES);
        // intersect with bad states
        context->execBeforeIntersectBadStates();
        context->intersectBadStates();
        context->execAfterIntersectBadStates();
        //EVALUATE_BENCHMARK_RESULT(INTERSECT_BAD_STATES);

        context->execBeforeLoop();

        // while not done
        while(!context->doneCondition()){
            //START_BENCHMARK_OPERATION(COMPUTE_TIMESTEP);

            context->execOnLoopItEnter();


            //START_BENCHMARK_OPERATION(CHECK_TRANSITION);
            // intersect with transition guards
            context->execBeforeCheckTransition();
            context->checkTransition();
            context->execAfterCheckTransition();
            //EVALUATE_BENCHMARK_RESULT(CHECK_TRANSITION);

            //START_BENCHMARK_OPERATION(CONTINUOUS_EVOLUTION);
            // apply continuous time step
            context->execBeforeContinuousEvolution();
            context->applyContinuousEvolution();
            context->execAfterContinuousEvolution();
            //EVALUATE_BENCHMARK_RESULT(CONTINUOUS_EVOLUTION);

            //START_BENCHMARK_OPERATION(CHECK_INVARIANT);
            // intersect with invariant
            context->execBeforeCheckInvariant();
            context->checkInvariant();
            context->execAfterCheckInvariant();
            //EVALUATE_BENCHMARK_RESULT(CHECK_INVARIANT);


            //START_BENCHMARK_OPERATION(INTERSECT_BAD_STATES);
            // intersect with bad states
            context->execBeforeIntersectBadStates();
            context->intersectBadStates();
            context->execAfterIntersectBadStates();
            //EVALUATE_BENCHMARK_RESULT(INTERSECT_BAD_STATES);

            context->execOnLoopItExit();
            //EVALUATE_BENCHMARK_RESULT(COMPUTE_TIMESTEP);

        }

        context->execAfterLoop();

        //START_BENCHMARK_OPERATION(DISCRETE_SUCCESSORS);
        // create discrete successor states
        context->execBeforeProcessDiscreteBehavior();
        context->processDiscreteBehavior();
        context->execBeforeProcessDiscreteBehavior();
        //EVALUATE_BENCHMARK_RESULT(DISCRETE_SUCCESSORS);

        context->execOnEnd();
    }
    catch(HardTerminateException e1){
        DEBUG("hydra.worker", "" << e1.what());
        return;
    }catch(FinishWithDiscreteProcessingException e2){
        DEBUG("hydra.worker", "" << e2.what());
        //START_BENCHMARK_OPERATION(DISCRETE_SUCCESSORS);
        // finish creating discrete successor states
        context->execBeforeProcessDiscreteBehavior();
        context->processDiscreteBehavior();
        context->execBeforeProcessDiscreteBehavior();
        //EVALUATE_BENCHMARK_RESULT(DISCRETE_SUCCESSORS);
    }
}

template<typename State>
bool ContextBasedReachabilityWorker<State>::isValidTask(const std::shared_ptr<Task<State>>& t, WorkQueue<std::shared_ptr<Task<State>>>& localCEXQueue){
    if(t->treeNode->getRefinements().at(t->btInfo.btLevel).fullyComputed) {
        // This node has already been computed for the required level. This can only happen during concurrent BT-runs.
        DEBUG("hydra.worker",  std::this_thread::get_id() << ": Got node which is already on the desired level.");
        assert(t->btInfo.btLevel > 0);
        // Follow bt-path by creating new tasks
        // 1: Find correct transition.
        // 2: Fine correct potential child. Note: At least the children (their order and links) are updated already, so we can
        //    safely read those. Nonetheless they might be locked for computation.
        std::pair<hypro::Transition<Number>*, carl::Interval<tNumber>> transitionTimingPair = t->btInfo.btPath.getTransitionToJumpDepth(t->treeNode->getDepth());
        // Transition is only nullptr, if the jump depth is zero (which cannot be here) or the queried jump depth is larger than
        // the path's length (which cannot be either, as there would have been a bt-run, which already computed the whole path).
        if(transitionTimingPair.first == nullptr) {
            // the whole path has been computed already.
            TRACE("hydra.worker","Do not continue refinement as the path has been computed already to full extend.");
            t->treeNode->getMutex().unlock();
            return false;
        }
        // iterate over all children to match the timings
        DEBUG("hydra.worker",  std::this_thread::get_id() << ": Search for next nodes on btPath: " << t->btInfo.btPath);
        DEBUG("hydra.worker",  std::this_thread::get_id() << ": Consider child nodes for transition " << *transitionTimingPair.first);
        for(auto child : t->treeNode->getChildrenForTransition(transitionTimingPair.first)) {
            DEBUG("hydra.worker",  std::this_thread::get_id() << ": Consider child " << child);
            if(child->getLatestBTLevel() >= t->btInfo.btLevel && carl::set_have_intersection(child->getTimestamp(t->btInfo.btLevel), transitionTimingPair.second) ) {
                DEBUG("hydra.worker",  std::this_thread::get_id() << ": Timestamp matches, create follow-up task.");
                std::shared_ptr<Task<State>> newTask(new Task<State>(child));
                newTask->btInfo = t->btInfo;
                newTask->btInfo.currentBTPosition += 2;
                DEBUG("hydra.worker","Enqueue follow up child with tree node " << child << " to local CEX queue.");
                if(!SettingsProvider<State>::getInstance().useGlobalQueuesOnly()){
                    localCEXQueue.nonLockingEnqueue(std::move(newTask));
                } else {
                    localCEXQueue.enqueue(std::move(newTask));
                }

            }
        }
        DEBUG("hydra.worker", std::this_thread::get_id() << ": Local CEX-Queue size: " << localCEXQueue.nonLockingSize() << "localCEXQueue is now:\n" << localCEXQueue);
        t->treeNode->getMutex().unlock();
        return false;
    }

    // If a node is set to empty, skip this node. This can happen, if the number of child-nodes has changed upon refinement - in this case
    // we do not erase subtrees but rather set the particular level to empty.
    if(t->treeNode->getRefinements().at(t->btInfo.btLevel).isEmpty) {
        t->treeNode->getMutex().unlock();
        return false;
    }

    return true;
}
} // hypro