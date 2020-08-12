#pragma once
#include "../Strategies.h"

#include <boost/program_options.hpp>
#include <hypro/datastructures/reachability/Settings.h>
#include <hypro/types.h>
#include <hypro/util/type_handling/plottype_enums.h>

namespace hydra {

hypro::Settings processSettings( const hypro::ReachabilitySettings& parsedSettings, const boost::program_options::variables_map& cliOptions );

}  // namespace hydra