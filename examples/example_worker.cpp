/**
 * @brief Example file which shows how to instanciate a concrete worker out of context handlers.
 */

#include <datastructures/reachability/SettingsProvider.h>
#include <datastructures/reachability/ReachTree.h>
#include <datastructures/reachability/Task.h>
#include <datastructures/reachability/workQueue/WorkQueueManager.h>
#include <datastructures/reachability/timing/EventTimingProvider.h>
#include <algorithms/reachability/workers/ContextBasedReachabilityWorker.h>
#include <parser/antlr4-flowstar/ParserWrapper.h>
#include <iostream>

int main(int argc, char** argv) {

    // typedefs
    using Number = double;
    using State = hypro::State_t<Number>;

    // settings provider instance as reference for readability
    hypro::SettingsProvider<State>& settingsProvider = hypro::SettingsProvider<State>::getInstance();

    // read file from input
    if(argc != 2) {
        std::cout << "Need to pass input file as argument." << std::endl;
        exit(1);
    }

    std::string filename = argv[1];
    std::cout << "Read input file " << filename << std::endl;

    std::pair<hypro::HybridAutomaton<Number>, hypro::ReachabilitySettings> parsedInput = hypro::parseFlowstarFile<Number>(filename);
    settingsProvider.addStrategyElement<hypro::Box<Number>>(mpq_class(1)/mpq_class(100), hypro::AGG_SETTING::AGG, -1);

    std::vector<size_t> decomposition;
    for(size_t i = 0; i < parsedInput.first.dimension();i++ ){
        decomposition.push_back(i);
    }
    hypro::Decomposition decompositions;
    decompositions.push_back(decomposition);
    settingsProvider.setSubspaceDecomposition(decompositions);

    settingsProvider.computeLocationSubspaceTypeMapping(parsedInput.first);
    settingsProvider.computeLocationTypeMapping(parsedInput.first);


    settingsProvider.setHybridAutomaton(parsedInput.first);
    settingsProvider.setReachabilitySettings(parsedInput.second);
    hypro::EventTimingProvider<Number>::getInstance().initialize(parsedInput.first, settingsProvider.getReachabilitySettings().timeBound*settingsProvider.getReachabilitySettings().jumpDepth);

    hypro::WorkQueueManager<std::shared_ptr<hypro::Task<State>>> queueManager;

    auto& globalCEXQueue = queueManager.addQueue();
    auto& globalQueue = queueManager.addQueue();

    hypro::HybridAutomaton<Number>::locationStateMap initialStates = settingsProvider.getHybridAutomaton().getInitialStates();
    std::vector<hypro::State_t<Number>> initialStateData;
    for (auto stateMapIt = initialStates.begin(); stateMapIt != initialStates.end(); ++stateMapIt) {

    	hypro::State_t<Number> copyState;
    	copyState.setLocation(stateMapIt->first);
    	copyState.setTimestamp(carl::Interval<hypro::tNumber>(0));

        // if the decider is in use - convert subspaces according to mapping
        State::repVariant _temp;
        if(settingsProvider.useDecider()){
            if(settingsProvider.getLocationSubspaceTypeMap().size() > 0){
                std::map<const hypro::Location<Number>*,std::shared_ptr<std::vector<hypro::SUBSPACETYPE>>>::iterator it;
                it = settingsProvider.getLocationSubspaceTypeMap().find(stateMapIt->first);
                if(it != settingsProvider.getLocationSubspaceTypeMap().end()){
                    if(it->second->at(0) == hypro::SUBSPACETYPE::TIMED){
                        //timed subspace
                        _temp = hypro::DifferenceBounds<Number>(stateMapIt->second.matrix(), stateMapIt->second.vector());
                    }
                    else{
                        // standard subspace
                        _temp = hypro::Box<Number>(stateMapIt->second.matrix(), stateMapIt->second.vector());
                    }
                }
                else{
                    // no entry in location subspace type map for this location -> compute type

                    // TODO

                    /*
                    repName = hypro::DecisionEntity<Number>::getInstance().getRepresentationForSubspace(*(stateMapIt->first), 0);
                    if(repName == hypro::representation_name::UNDEF) {
                        _temp = hypro::Box<Number>(stateMapIt->second.matrix(), stateMapIt->second.vector());
                    }
                    */
                }
            }
            else{
                // no location subspace type map -> compute type

                // TODO

                /*
                repName = hypro::DecisionEntity<Number>::getInstance().getRepresentationForSubspace(*(stateMapIt->first), 0);
                if(repName == hypro::representation_name::UNDEF) {
                    _temp = hypro::Box<Number>(stateMapIt->second.matrix(), stateMapIt->second.vector());
                }
                */
            }
        }
        else{
            _temp = hypro::Box<Number>(stateMapIt->second.matrix(), stateMapIt->second.vector());
        }

        copyState.setSet(_temp,0);

        initialStateData.emplace_back(copyState);
    }
    // setup tree and fill queue
    hypro::ReachTree<State> tree = hypro::ReachTree<State>(new hypro::ReachTreeNode<State>());
    std::vector<hypro::ReachTreeNode<State>*> initialNodes;
    for(const auto& state : initialStateData) {
        hypro::ReachTreeNode<State>* n = new hypro::ReachTreeNode<State>(state,0,tree.getRoot());
        n->setTimestamp(0, carl::Interval<hypro::tNumber>(0));
        initialNodes.push_back(n);
        tree.getRoot()->addChild(n);
    }

    for (const auto& initialNode : initialNodes) {
        globalQueue.enqueue(std::shared_ptr<hypro::Task<State>>(new hypro::Task<State>(initialNode)));
    }

    hypro::ContextBasedReachabilityWorker<State> worker = hypro::ContextBasedReachabilityWorker<State>(parsedInput.second);
    std::vector<hypro::PlotData<State>> segments;

    while(queueManager.hasWorkable(true)) { // locking access to queues.
        auto task = queueManager.getNextWorkable(true,true); // get next task locked and dequeue from front.
        assert(task!=nullptr);
        worker.processTask(task,settingsProvider.getStrategy(), globalQueue, globalCEXQueue, &segments);
    }

	return 0;
}
