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

    // number typedef
    using Number = double;

    // read file from input
    if(argc != 2) {
        std::cout << "Need to pass input file as argument." << std::endl;
        exit(1);
    }

    std::string filename = argv[1];
    std::cout << "Read input file " << filename << std::endl;

    std::pair<hypro::HybridAutomaton<Number>, hypro::ReachabilitySettings> parsedInput = hypro::parseFlowstarFile<Number>(filename);
    hypro::ReachabilitySettings convertedSettings(parsedInput.second);

    std::vector<size_t> decomposition;
    for(size_t i = 0; i < parsedInput.first.dimension();i++ ){
        decomposition.push_back(i);
    }
    hypro::Decomposition decompositions;
    decompositions.push_back(decomposition);
    hypro::SettingsProvider<Number>::getInstance().setSubspaceDecomposition(decompositions);

    hypro::SettingsProvider<Number>::getInstance().computeLocationSubspaceTypeMapping(parsedInput.first);
    hypro::SettingsProvider<Number>::getInstance().computeLocationTypeMapping(parsedInput.first);        


    hypro::SettingsProvider<Number>::getInstance().setHybridAutomaton(parsedInput.first);
    hypro::SettingsProvider<Number>::getInstance().setReachabilitySettings(convertedSettings);
    hypro::EventTimingProvider<Number>::getInstance().initialize(parsedInput.first);

    hypro::WorkQueueManager<std::shared_ptr<hypro::Task<Number>>> queueManager;

    auto globalCEXQueue = queueManager.addQueue();
    auto globalQueue = queueManager.addQueue();

    hypro::HybridAutomaton<Number>::locationStateMap initialStates = hypro::SettingsProvider<Number>::getInstance().getHybridAutomaton().getInitialStates();
    std::vector<hypro::State_t<Number>> initialStateData;
    for (auto stateMapIt = initialStates.begin(); stateMapIt != initialStates.end(); ++stateMapIt) {
    	assert(!stateMapIt->second.getTimestamp().isEmpty());

    	hypro::State_t<Number> copyState;
    	copyState.setLocation(stateMapIt->second.getLocation());
    	copyState.setTimestamp(carl::Interval<hypro::tNumber>(stateMapIt->second.getTimestamp().lower(),stateMapIt->second.getTimestamp().upper()));

        hypro::representation_name repName = hypro::SettingsProvider<Number>::getInstance().getStartingRepresentation();
        for(size_t i = 0; i < stateMapIt->second.getNumberSets(); i++){
            // if the decider is in use - convert subspaces according to mapping
            if(hypro::SettingsProvider<Number>::getInstance().useDecider()){
                if(hypro::SettingsProvider<Number>::getInstance().getLocationSubspaceTypeMap().size() > 0){
                    std::map<const hypro::Location<Number>*,std::shared_ptr<std::vector<hypro::SUBSPACETYPE>>>::iterator it;
                    it = hypro::SettingsProvider<Number>::getInstance().getLocationSubspaceTypeMap().find(stateMapIt->second.getLocation());
                    if(it != hypro::SettingsProvider<Number>::getInstance().getLocationSubspaceTypeMap().end()){
                        if(it->second->at(i) == hypro::SUBSPACETYPE::TIMED){
                            //timed subspace
                            repName = hypro::representation_name::difference_bounds;      
                        }
                        else{
                            // standard subspace
                            repName = hypro::SettingsProvider<Number>::getInstance().getStartingRepresentation();
                        }
                    }
                    else{
                        // no entry in location subspace type map for this location -> compute type
                        repName = hypro::DecisionEntity<Number>::getInstance().getRepresentationForSubspace(*(stateMapIt->second.getLocation()), i); 
                        if(repName == hypro::representation_name::UNDEF) {
                            repName = hypro::SettingsProvider<Number>::getInstance().getStartingRepresentation();
                        }
                    }
                }
                else{ 
                    // no location subspace type map -> compute type    
                    repName = hypro::DecisionEntity<Number>::getInstance().getRepresentationForSubspace(*(stateMapIt->second.getLocation()), i);
                    if(repName == hypro::representation_name::UNDEF) {
                        repName = hypro::SettingsProvider<Number>::getInstance().getStartingRepresentation();
                    }
                }
            }
            else{
                repName = hypro::SettingsProvider<Number>::getInstance().getStartingRepresentation();
            }

            hypro::State_t<Number>::repVariant _temp = boost::apply_visitor(hypro::genericConversionVisitor<hypro::State_t<Number>::repVariant,Number>(repName), stateMapIt->second.getSet(i));
            copyState.setSetDirect(_temp,i);
            copyState.setSetType(repName,i);
        }
        initialStateData.emplace_back(copyState);
    }
    // setup tree and fill queue
    hypro::ReachTree<Number> tree = hypro::ReachTree<Number>(new hypro::ReachTreeNode<Number>());
    std::vector<hypro::ReachTreeNode<Number>*> initialNodes;
    for(const auto& state : initialStateData) {
        hypro::ReachTreeNode<Number>* n = new hypro::ReachTreeNode<Number>(state,0,tree.getRoot());
        n->setTimestamp(0, carl::Interval<hypro::tNumber>(0));
        initialNodes.push_back(n);
        tree.getRoot()->addChild(n);
    }
    
    for (const auto& initialNode : initialNodes) {
        globalQueue->enqueue(std::shared_ptr<hypro::Task<Number>>(new hypro::Task<Number>(initialNode)));
    }

    hypro::ContextBasedReachabilityWorker<Number> worker = hypro::ContextBasedReachabilityWorker<Number>(convertedSettings);
	return 0;
}
