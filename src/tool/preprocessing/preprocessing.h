#pragma once
#include "../typedefs.h"

#include <boost/program_options.hpp>
#include <hypro/algorithms/reachability/analyzer/DecompositionalUtil.h>
#include <hypro/datastructures/HybridAutomaton/HybridAutomaton.h>
#include <hypro/datastructures/HybridAutomaton/decomposition/DecompositionMethods.h>
#include <hypro/datastructures/reachability/PreprocessingInformation.h>
#include <hypro/datastructures/reachability/Settings.h>

namespace hydra {
namespace preprocessing {
/// calls the preprocessor on the passed hybrid automaton
hypro::PreprocessingInformation preprocess( const hypro::HybridAutomaton<hydra::Number>& automaton,
											bool decompose,
											std::size_t singularSubspaceSize,
											std::size_t clockCount );
}  // namespace preprocessing
}  // namespace hydra
