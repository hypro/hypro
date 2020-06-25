#pragma once
// #include "../../hypro/datastructures/reachability/SettingsProvider.h"
#include "../../hypro/types.h"
#include "../../hypro/util/logging/Logger.h"
#include "../typedefs.h"
//#include "DynamicStrategyBuilder.h"
#include "../Strategies.h"
#include <boost/program_options.hpp>

namespace hydra {
boost::program_options::variables_map handleCMDArguments(int argc,
                                                         const char **argv);
} // namespace hydra
