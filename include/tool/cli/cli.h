#pragma once
#include <boost/program_options.hpp>

namespace hydra {
boost::program_options::variables_map handleCMDArguments( int argc,
														  const char** argv );
}  // namespace hydra
