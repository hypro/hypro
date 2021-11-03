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

static void run_hydra_leaking_tank_box( ::benchmark::State& state ) {
	// Perform setup here
	using Number = mpq_class;
	using Representation = hypro::BoxT<Number, hypro::Converter<Number>, BoxLinearOptimizationOn>;
	namespace po = boost::program_options;
	// -m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s
	// BoxLinearOptimizationOn -a AGG -c 0 --clockCount 0 --decompose --singularSubspaceSize 1 --skipplot
	// store arguments
	std::size_t clocks = state.range( 0 );
	std::size_t subspaces = state.range( 1 );

	// assemble settings

	std::string filename{
		  getCSModelsPath() +
		  "subspaceBenchmarks/leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model" };
	const char* arguments[] = {
		  "-m ",
		  filename.c_str(),
		  "-r",
		  Representation::type()._to_string(),
		  "-s",
		  hypro::boxSetting_name::_from_integral( Representation::Settings::type_enum )._to_string(),
		  "-a",
		  "AGG",
		  "-c",
		  "0",
		  "--clockCount",
		  std::to_string( clocks ).c_str(),
		  "--decompose",
		  "--singularSubspaceSize",
		  std::to_string( subspaces ).c_str(),
		  "--skipplot",
		  "--silent" };
	po::variables_map options = hydra::handleCMDArguments( 17, arguments );

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
	state.counters.insert( { { "clocks", clocks }, { "merge-bound", subspaces } } );
}

static void run_hydra_two_tanks_box( ::benchmark::State& state ) {
	// Perform setup here
	using Number = mpq_class;
	using Representation = hypro::BoxT<Number, hypro::Converter<Number>, BoxLinearOptimizationOn>;
	namespace po = boost::program_options;
	// -m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s
	// BoxLinearOptimizationOn -a AGG -c 0 --clockCount 0 --decompose --singularSubspaceSize 1 --skipplot
	// store arguments
	std::size_t clocks = state.range( 0 );
	std::size_t subspaces = state.range( 1 );

	// assemble settings

	std::string filename{
		  getCSModelsPath() +
		  "subspaceBenchmarks/two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model" };
	const char* arguments[] = {
		  "-m ",
		  filename.c_str(),
		  "-r",
		  Representation::type()._to_string(),
		  "-s",
		  hypro::boxSetting_name::_from_integral( Representation::Settings::type_enum )._to_string(),
		  "-a",
		  "AGG",
		  "-c",
		  "0",
		  "--clockCount",
		  std::to_string( clocks ).c_str(),
		  "--decompose",
		  "--singularSubspaceSize",
		  std::to_string( subspaces ).c_str(),
		  "--skipplot",
		  "--silent" };
	po::variables_map options = hydra::handleCMDArguments( 17, arguments );

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
	state.counters.insert( { { "clocks", clocks }, { "merge-bound", subspaces } } );
}

static void run_hydra_thermostat_box( ::benchmark::State& state ) {
	// Perform setup here
	using Number = mpq_class;
	using Representation = hypro::BoxT<Number, hypro::Converter<Number>, BoxLinearOptimizationOn>;
	namespace po = boost::program_options;
	// -m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s
	// BoxLinearOptimizationOn -a AGG -c 0 --clockCount 0 --decompose --singularSubspaceSize 1 --skipplot
	// store arguments
	std::size_t clocks = state.range( 0 );
	std::size_t subspaces = state.range( 1 );

	// assemble settings

	std::string filename{
		  getCSModelsPath() +
		  "subspaceBenchmarks/thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model" };
	const char* arguments[] = {
		  "-m ",
		  filename.c_str(),
		  "-r",
		  Representation::type()._to_string(),
		  "-s",
		  hypro::boxSetting_name::_from_integral( Representation::Settings::type_enum )._to_string(),
		  "-a",
		  "AGG",
		  "-c",
		  "0",
		  "--clockCount",
		  std::to_string( clocks ).c_str(),
		  "--decompose",
		  "--singularSubspaceSize",
		  std::to_string( subspaces ).c_str(),
		  "--skipplot",
		  "--silent" };
	po::variables_map options = hydra::handleCMDArguments( 17, arguments );

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
	state.counters.insert( { { "clocks", clocks }, { "merge-bound", subspaces } } );
}

// Register the function as a benchmark
BENCHMARK( run_hydra_leaking_tank_box )
	  ->ArgsProduct( { ::benchmark::CreateDenseRange( 1, 4, 1 ), ::benchmark::CreateDenseRange( 1, 3, 1 ) } )
	  ->Unit( ::benchmark::kSecond );
BENCHMARK( run_hydra_two_tanks_box )
	  ->ArgsProduct( { ::benchmark::CreateDenseRange( 1, 4, 1 ), ::benchmark::CreateDenseRange( 1, 3, 1 ) } )
	  ->Unit( ::benchmark::kSecond );
BENCHMARK( run_hydra_thermostat_box )
	  ->ArgsProduct( { ::benchmark::CreateDenseRange( 1, 4, 1 ), ::benchmark::CreateDenseRange( 1, 3, 1 ) } )
	  ->Unit( ::benchmark::kSecond );

}  // namespace hypro::benchmark
