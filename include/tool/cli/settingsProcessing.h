#pragma once
#include <boost/program_options.hpp>
#include <hypro/datastructures/reachability/Settings.h>

namespace hydra {

hypro::Settings processSettings( const hypro::ReachabilitySettings& parsedSettings, const boost::program_options::variables_map& cliOptions );

}  // namespace hydra