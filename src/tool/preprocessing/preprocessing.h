#pragma once
#include "../../hypro/datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../../hypro/datastructures/reachability/Settings.h"
#include "../typedefs.h"
#include <boost/program_options.hpp>

namespace hydra {
namespace preprocessing {
void preprocess(const hypro::HybridAutomaton<hydra::Number> &,
                const hypro::ReachabilitySettings &);
} // namespace preprocessing
} // namespace hydra
