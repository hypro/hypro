#pragma once
#include "../../hypro/datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../../hypro/datastructures/reachability/Settings.h"
#include "../typedefs.h"


namespace hydra {
namespace reachability {
void analyze( hypro::HybridAutomaton<Number> &automaton, hypro::Settings setting );

}  // namespace reachability
}  // namespace hydra
