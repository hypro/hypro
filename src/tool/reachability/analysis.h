#pragma once
#include "../../hypro/algorithms/reachability/analyzer/CEGARAnalyzer.h"
#include "../../hypro/algorithms/reachability/analyzer/LTIAnalyzer.h"
#include "../../hypro/datastructures/HybridAutomaton/State.h"
#include "../../hypro/datastructures/reachability/Settings.h"
#include "../../hypro/representations/conversion/Converter.h"
#include "../../hypro/util/plotting/Plotter.h"
#include "../../hypro/util/type_handling/dispatch.h"
#include "../typedefs.h"

namespace hydra {
namespace reachability {
void analyze( hypro::HybridAutomaton<Number> &automaton, hypro::Settings setting );

}  // namespace reachability
}  // namespace hydra
