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
#include <hypro/algorithms/reachability/Reach.h>
#include <hypro/datastructures/HybridAutomaton/PathUtil.h>
#include <hypro/parser/antlr4-flowstar/ParserWrapper.h>
#include <hypro/paths.h>
#include <hypro/util/plotting/Plotter.h>
#include <string>

namespace hypro::benchmark {

template <class Representation>
static void Simplex_Watertanks_Reachability( ::benchmark::State& state ) {
	// store arguments
	std::size_t maxJumps = state.range( 0 );
	// clear statistics
	RESET_STATS();
	// Perform setup here
	using Number = double;
	std::string filename{ "21_simplex_watertanks_deterministic_monitor_small_init.model" };

	auto [automaton, reachSettings] = hypro::parseFlowstarFile<Number>( getCSModelsPath() + filename );

	auto settings = hypro::convert( reachSettings );
	settings.rStrategy().front().detectJumpFixedPoints = true;
	settings.rStrategy().front().detectFixedPointsByCoverage = false;
	settings.rStrategy().front().detectContinuousFixedPointsLocally = false;
	settings.rFixedParameters().localTimeHorizon = 100;
	settings.rFixedParameters().jumpDepth = maxJumps;
	settings.rStrategy().begin()->aggregation = AGG_SETTING::AGG;
	std::vector<hypro::Path<Number>> last_paths{};

	std::vector<ReachTreeNode<Representation>> roots;

	for ( auto _ : state ) {
		// This code gets timed
		last_paths = std::vector<hypro::Path<Number>>{};
		roots = hypro::makeRoots<Representation>( automaton );
		auto reacher = hypro::reachability::Reach<Representation>( automaton, settings.fixedParameters(),
																   settings.strategy().front(), roots );
		auto result = reacher.computeForwardReachability();
		INFO( "hypro.casestudies", "System is safe: " << result );

		// statistics
		auto finished_leaves = std::size_t( 0 );
		auto unfinished_leaves = std::size_t( 0 );
		auto leaves = std::size_t( 0 );
		auto nodes = std::size_t( 0 );
		auto cyclic_path_count = std::size_t( 0 );
		auto segments = std::size_t( 0 );

		for ( const ReachTreeNode<Representation>& node : hypro::preorder( roots ) ) {
			++nodes;
			segments += node.getFlowpipe().size();
			if ( node.getChildren().empty() ) {
				if ( node.hasFixedPoint() == TRIBOOL::TRUE ) {
					++finished_leaves;
				} else {
					++unfinished_leaves;
					last_paths.push_back( node.getPath() );
					if ( has_discrete_cycle( node.getPath() ) ) {
						INFO( "hypro.casestudies", "Path " << node.getPath() << " is cyclic." );
						++cyclic_path_count;
					}
#ifdef HYPRO_LOGGING
					else {
						INFO( "hypro.casestudies", "Path " << node.getPath() << " is truly unfinished." );
					}
#endif
				}
				++leaves;
				COUNT( "leaves" );
			}
		}
		// state.counters["fin.leaves"] = double( double( finished_leaves ) / double( leaves ) );
		// state.counters["nfin.leaves"] = double( double( unfinished_leaves ) / double( leaves ) );
		state.counters["#fin.leaves"] = finished_leaves;
		state.counters["#nfin.leaves"] = unfinished_leaves;
		state.counters["leaves"] = leaves;
		state.counters["jumps"] = maxJumps;
		state.counters["nodes"] = nodes;
		state.counters["cycles"] = cyclic_path_count;
		state.counters["segments"] = segments;
#ifdef HYPRO_STATISTICS
		state.counters["fp-cov"] = hypro::Statistician::getInstance().getCounter( "FP-by-coverage" ).val;
#endif
	}

	// only plot the last run
	// plotting
	auto& plt = hypro::Plotter<Number>::getInstance();
	plt.clear();
	plt.rSettings().overwriteFiles = true;
	plt.rSettings().cummulative = false;
	plt.setFilename( "simplex_watertanks" );

	for ( const auto& node : hypro::preorder( roots ) ) {
		for ( const auto& segment : node.getFlowpipe() ) {
			if ( node.hasFixedPoint() == TRIBOOL::TRUE ) {
				plt.addObject( segment.projectOn( { 0, 1 } ).vertices(),
							   hypro::plotting::colors[hypro::plotting::green] );
			} else if ( node.hasFixedPoint() == TRIBOOL::FALSE ) {
				plt.addObject( segment.projectOn( { 0, 1 } ).vertices(),
							   hypro::plotting::colors[hypro::plotting::orange] );
			} else {
				plt.addObject( segment.projectOn( { 0, 1 } ).vertices() );
			}
		}
	}

	plt.plot2d( hypro::PLOTTYPE::png );
	plt.plot2d( hypro::PLOTTYPE::pdf );
	plt.plot2d( hypro::PLOTTYPE::gen );
	plt.plot2d( hypro::PLOTTYPE::tex );

	// output unfinished paths
	std::string channel =
		  "benchmark.paths." +
		  std::to_string( carl::convert<tNumber, double>( settings.strategy().begin()->timeStep ) ) + "_delta." +
		  std::to_string( carl::convert<hypro::tNumber, double>( settings.fixedParameters().localTimeHorizon ) ) +
		  "_TH." + std::to_string( state.range( 0 ) ) + "_jumps";
	TRACE( channel, "#################################################" );
	for ( const auto& path : last_paths ) {
		TRACE( channel, path );
	}

	PRINT_STATS()
}
// Register the function as a benchmark
// BENCHMARK_TEMPLATE( Simplex_Watertanks_Reachability, hypro::SupportFunction<double> )->DenseRange(1, 3, 1);
BENCHMARK_TEMPLATE( Simplex_Watertanks_Reachability, hypro::Box<double> )
	  ->DenseRange( 1, 15, 1 )
	  ->Unit( ::benchmark::kSecond );

}  // namespace hypro::benchmark
