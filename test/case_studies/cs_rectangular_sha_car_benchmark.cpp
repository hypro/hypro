/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Created by stefan on 06.05.22
 */

#include <hypro/algorithms/reachability/Reach.h>
#include <hypro/algorithms/reachability/analyzer/RectangularAnalyzer.h>
#include <hypro/datastructures/HybridAutomaton/HybridAutomaton.h>
#include <hypro/parser/antlr4-flowstar/ParserWrapper.h>
#include <hypro/paths.h>
#include <hypro/util/logging/Logger.h>
#include <hypro/util/plotting/Plotter.h>
#include <hypro/util/statistics/statistics.h>
#include <string>

int main() {
	using Representation = hypro::HPolytope<mpq_class>;
	std::size_t days = 1;
	std::string filename = hypro::getCSModelsPath() + "rectangular_sha_car_benchmark/car_days_" + std::to_string( days ) + "_charging_ABC.model";

	// setup
	hypro::FixedAnalysisParameters fixedParams{ 7 * days, 21 * days, 1 };
	hypro::AnalysisParameters analysisParams{ 1 };
	hypro::PlottingSettings pltSettings{};	// default construction disables plotting
	auto settings = hypro::Settings{ pltSettings, fixedParams, { analysisParams } };

	auto [automaton, parsedSettings] = hypro::parseFlowstarFile<mpq_class>( filename );
	auto roots = hypro::makeRoots<Representation, mpq_class>( automaton );

	auto analyzer = hypro::RectangularAnalyzer<Representation>( automaton, settings, roots );
	START_BENCHMARK_OPERATION( "Reachability Analysis" );
	auto result = analyzer.run();
	STOP_BENCHMARK_OPERATION( "Reachability Analysis" );

	// plotting
	/*
	START_BENCHMARK_OPERATION( "Plotting" );
	auto& plt = hypro::Plotter<mpq_class>::getInstance();
	for ( const auto& root : roots ) {
		for ( const auto& node : hypro::preorder( root ) ) {
			for ( const auto& segment : node.getFlowpipe() ) {
				plt.addObject( segment.vertices() );
			}
		}
	}
	plt.plot2d( hypro::PLOTTYPE::png, true );
	STOP_BENCHMARK_OPERATION( "Plotting" );
	*/
	PRINT_STATS();
	return 0;
}
