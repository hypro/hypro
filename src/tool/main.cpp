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

  // run reachability analysis
  hydra::reachability::analyze();

  return 0;
}