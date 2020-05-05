#include "../hypro/datastructures/reachability/SettingsProvider.h"
#include "../hypro/parser/antlr4-flowstar/ParserWrapper.h"
#include "../hypro/types.h"
#include "../hypro/util/logging/Logger.h"
#include "cli/cli.h"
#include "preprocessing/preprocessing.h"
#include "reachability/analysis.h"
#include "typedefs.h"

int main(int argc, char const *argv[]) {
  // parse command line arguments
  auto options = hydra::handleCMDArguments(argc, argv);

  // parse model file
  COUT("Passed model file: " << options["model"].as<std::string>());
  auto automatonSettingsPair = hypro::parseFlowstarFile<hydra::Number>(
      options["model"].as<std::string>());

  // perform preprocessing
  hydra::preprocessing::preprocess(automatonSettingsPair.first,
                                   automatonSettingsPair.second);

  mpq_class timeStep = options.count("delta")
                           ? options["delta"].as<mpq_class>()
                           : automatonSettingsPair.second.timeStep;

  representation_name representation =
      stringToRepresentation(options["representation"].as<std::string>());

  // create strategy
  DynamicStrategy strategy{
      {timeStep, AGG_SETTING::MODEL, -1, representation,
       stringToSetting(representation,
                       options["rep_setting"].as<std::string>())}};

  // run reachability analysis
  hydra::reachability::analyze(strategy);

  return 0;
}