#pragma once
#include "../typedefs.h"

#include <hypro/algorithms/reachability/analyzer/LTIAnalyzer.h>
#include <hypro/datastructures/HybridAutomaton/State.h>
#include <hypro/datastructures/reachability/PreprocessingInformation.h>
#include <hypro/util/type_handling/dispatch.h>

namespace hydra::reachability {

using namespace hypro;

using FullState = hypro::apply<hypro::State, concat<TypeList<Number, CarlPolytope<Number>>, RepresentationsList<Number, Converter<Number>>>>;

using PolytopalState = hypro::apply<hypro::State, PolytopeTypesList<Number, Converter<Number>>>;

struct AnalysisResult {
	std::vector<hypro::PlotData<FullState>> plotData{};
};

AnalysisResult analyze( HybridAutomaton<Number> const& automaton, const Settings& setting, hypro::PreprocessingInformation information );

}  // namespace hydra::reachability
