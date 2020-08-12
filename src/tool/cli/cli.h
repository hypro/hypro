#pragma once
#include "../Strategies.h"
#include "../typedefs.h"

#include <boost/program_options.hpp>
#include <hypro/types.h>
#include <hypro/util/logging/Logger.h>

namespace hydra {
boost::program_options::variables_map handleCMDArguments( int argc,
														  const char **argv );
}  // namespace hydra
