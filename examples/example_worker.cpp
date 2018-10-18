/**
 * @brief Example file which shows how to instanciate a concrete worker out of context handlers.
 */

#include <datastructures/reachability/SettingsProvider.h>
#include <datastructures/reachability/timing/EventTimingProvider.h>
#include <algorithms/reachability/workers/ContextBasedReachabilityWorker.h>
#include <parser/antlr4-flowstar/ParserWrapper.h>
#include <iostream>

int main(int argc, char** argv) {

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
    hypro::SettingsProvider<double>::getInstance().setSubspaceDecomposition(decompositions);

    hypro::SettingsProvider<double>::getInstance().computeLocationSubspaceTypeMapping(parsedInput.first);
    hypro::SettingsProvider<double>::getInstance().computeLocationTypeMapping(parsedInput.first);        


    hypro::SettingsProvider<double>::getInstance().setHybridAutomaton(parsedInput.first);
    hypro::SettingsProvider<double>::getInstance().setReachabilitySettings(convertedSettings);
    hypro::EventTimingProvider<double>::getInstance().initialize(parsedInput.first);

    hypro::WorkQueue<double> wq;



    hypro::ContextBasedReachabilityWorker<double> worker = hypro::ContextBasedReachabilityWorker<double>(convertedSettings);
	return 0;
}
