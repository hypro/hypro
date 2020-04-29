#include "../hypro/datastructures/reachability/SettingsProvider.h"
#include "../hypro/types.h"
#include "../hypro/util/logging/Logger.h"
#include "cli/cli.h"
#include "typedefs.h"

int main(int argc, char const *argv[]) {
  // parse command line arguments
  auto options = hydra::handleCMDArguments(argc, argv);
  return 0;
}