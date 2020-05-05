#pragma once
#include "../../hypro/util/type_handling/dispatch.h"
#include "../../hypro/algorithms/reachability/analyzer/LTIAnalyzer.h"
#include "../../hypro/datastructures/reachability/Settings.h"
#include "../typedefs.h"
#include "../../hypro/representations/conversion/Converter.h"
#include "../../hypro/datastructures/HybridAutomaton/State.h"

namespace hydra
{
namespace reachability
{
void analyze(hypro::DynamicStrategy strategy);

} // namespace reachability
} // namespace hydra
