#pragma once
#include "../typedefs.h"

#include <hypro/algorithms/reachability/analyzer/LTIAnalyzer.h>
#include <hypro/datastructures/HybridAutomaton/State.h>
#include <hypro/datastructures/reachability/PreprocessingInformation.h>
#include <hypro/datastructures/reachability/Settings.h>
#include <hypro/representations/conversion/Converter.h>
#include <hypro/util/plotting/Plotter.h>
#include <hypro/util/type_handling/dispatch.h>

namespace hydra {
namespace reachability {
void analyze( hypro::HybridAutomaton<Number> &automaton, hypro::Settings setting, hypro::PreprocessingInformation );

}  // namespace reachability
}  // namespace hydra
