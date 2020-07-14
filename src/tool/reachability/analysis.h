#pragma once
#include "../typedefs.h"

#include <hypro/algorithms/reachability/analyzer/LTIAnalyzer.h>
#include <hypro/algorithms/reachability/analyzer/RectangularAnalyzer.h>
#include <hypro/datastructures/HybridAutomaton/State.h>
#include <hypro/datastructures/reachability/PreprocessingInformation.h>
#include <hypro/datastructures/reachability/Settings.h>
#include <hypro/representations/conversion/Converter.h>
#include <hypro/util/plotting/Plotter.h>
#include <hypro/util/type_handling/dispatch.h>

namespace hydra {
namespace reachability {

using namespace hypro;

using FullState = hypro::apply<hypro::State, concat<TypeList<Number>, RepresentationsList<Number, Converter<Number>>>>;

struct AnalysisResult {
	std::vector<hypro::PlotData<FullState>> plotData{};
};

AnalysisResult analyze( HybridAutomaton<Number> &automaton, hypro::Settings setting );

}  // namespace reachability
}  // namespace hydra
