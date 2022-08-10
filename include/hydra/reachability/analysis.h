/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once
#include "typedefs.h"

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

AnalysisResult analyze( HybridAutomaton<Number>& automaton, Settings& setting, hypro::PreprocessingInformation information, bool urgency_cegar = false );

}  // namespace hydra::reachability
