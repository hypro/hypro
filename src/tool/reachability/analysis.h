#pragma once
#include "../../hypro/algorithms/reachability/analyzer/LTIAnalyzer.h"
#include "../../hypro/datastructures/HybridAutomaton/State.h"
#include "../../hypro/datastructures/reachability/Settings.h"
#include "../../hypro/representations/conversion/Converter.h"
#include "../../hypro/util/plotting/PlotData.h"
#include "../../hypro/util/plotting/Plotter.h"
#include "../../hypro/util/type_handling/dispatch.h"
#include "../hypro/datastructures/HybridAutomaton/State.h"
#include "../typedefs.h"

namespace hydra {
namespace reachability {

using namespace hypro;

using FullState = hypro::apply<hypro::State, concat<TypeList<Number>, RepresentationsList<Number, Converter<Number>>>>;

struct AnalysisResult {
	std::vector<hypro::PlotData<FullState>> plotData{};
};

AnalysisResult analyze( hypro::HybridAutomaton<Number> &automaton, hypro::Settings setting );

}  // namespace reachability
}  // namespace hydra
