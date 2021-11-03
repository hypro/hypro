/*
 * Copyright (c) 2021.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Created by stefan on 04.08.21.
 */

#include <benchmark/benchmark.h>
#include <hypro/parser/antlr4-flowstar/ParserWrapper.h>
#include <hypro/paths.h>
#include <hypro/util/plotting/Plotter.h>
#include <string>
#include <tool/cli/cli.h>
#include <tool/cli/settingsProcessing.h>
#include <tool/preprocessing/preprocessing.h>
#include <tool/reachability/analysis.h>

namespace hypro::benchmark {

template <typename Representation>
static void run_hydra_leaking_tank( ::benchmark::State& state ) {
	// -m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s
	// BoxLinearOptimizationOn -a AGG -c 0 --clockCount 0 --decompose --singularSubspaceSize 1 --skipplot
	// store arguments
	std::size_t clocks = state.range( 0 );
	std::size_t subspaces = 1;	// state.range( 1 );
	// Perform setup here
	using Number = double;

	// assemble settings
	// create artificial options-mapping
	std::string filename{
		  getCSModelsPath() +
		  "subspaceBenchmarks/leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model" };
	std::string arguments =
		  "-m " + filename + " -r " + Representation::type()._to_string() + " -s BoxLinearOptimizationOn";
	// +" -a AGG -c"
	//" 0 "
	//"--clockCount " +
	// std::to_string( clocks ) + " --decompose --singularSubspaceSize " +
	// std::to_string( subspaces ) + " --skipplot";
	std::cout << "Passed options: " << arguments << std::endl;
	const char* args = arguments.c_str();
	boost::program_options::variables_map options = hydra::handleCMDArguments( 7, &args );

	auto [automaton, reachSettings] = hypro::parseFlowstarFile<typename Representation::NumberType>( filename );
	// perform preprocessing
	auto preprocessingInformation = hydra::preprocessing::preprocess( automaton, options["decompose"].as<bool>(),
																	  options["singularSubspaceSize"].as<std::size_t>(),
																	  options["clockCount"].as<std::size_t>() );
	auto settings = hydra::processSettings( reachSettings, options );
	// benchmark
	for ( auto _ : state ) {
		// run reachability analysis
		auto result = ::hydra::reachability::analyze( automaton, settings, preprocessingInformation );
	}
}
// Register the function as a benchmark
BENCHMARK_TEMPLATE( run_hydra_leaking_tank, hypro::BoxT<double, hypro::Converter<double>, BoxLinearOptimizationOn> )
	  ->DenseRange( 0, 4, 1 )
	  ->DenseRange( 1, 3, 1 )
	  ->Unit( ::benchmark::kSecond );

}  // namespace hypro::benchmark
