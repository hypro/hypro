#include "../hypro/datastructures/reachability/SettingsProvider.h"
#include "../hypro/parser/antlr4-flowstar/ParserWrapper.h"
#include "../hypro/types.h"
#include "../hypro/util/logging/Logger.h"
#include "cli/cli.h"
#include "preprocessing/preprocessing.h"
#include "reachability/analysis.h"
#include "../hypro/datastructures/reachability/Settings.h"
#include "typedefs.h"

int main(int argc, char const *argv[])
{
    // parse command line arguments
    auto options = hydra::handleCMDArguments(argc, argv);

    // parse model file
    COUT("Passed model file: " << options["model"].as<std::string>());
    auto [automaton, reachSettings] = hypro::parseFlowstarFile<hydra::Number>(
        options["model"].as<std::string>());

    // perform preprocessing
    hydra::preprocessing::preprocess(automaton,
                                     reachSettings);

    mpq_class timeStep = options.count("delta")
                             ? options["delta"].as<mpq_class>()
                             : reachSettings.timeStep;

    hypro::representation_name representation =
        hypro::stringToRepresentation.at(options["representation"].as<std::string>());

    // create strategy
    hypro::Setting setting{{{timeStep, hypro::AGG_SETTING::MODEL, -1, representation,
                             stringToSetting(representation,
                                             options["setting"].as<std::string>())}},
                           reachSettings.jumpDepth,
                           reachSettings.timeBound};

    // run reachability analysis
    hydra::reachability::analyze(automaton, setting);

    return 0;
}