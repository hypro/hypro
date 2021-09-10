/*
 * Created by stefan on 04.08.21.
 */

#include <benchmark/benchmark.h>
#include <filesystem>
#include <hypro/algorithms/reachability/Reach.h>
#include <hypro/datastructures/HybridAutomaton/PathUtil.h>
#include <hypro/parser/antlr4-flowstar/ParserWrapper.h>
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
	auto base_path = std::filesystem::current_path().parent_path().parent_path().append( "examples/input/" );
	std::string filename{ "21_simplex_watertanks.model" };

	auto [automaton, reachSettings] = hypro::parseFlowstarFile<Number>( base_path.string() + filename );

	auto settings = hypro::convert( reachSettings );
	settings.rStrategy().front().detectJumpFixedPoints = true;
	settings.rStrategy().front().detectContinuousFixedPointsLocally = true;
	// settings.rFixedParameters().localTimeHorizon = 1;
	settings.rFixedParameters().jumpDepth = maxJumps;
	settings.rStrategy().begin()->aggregation = AGG_SETTING::AGG;
	std::vector<hypro::Path<Number>> last_paths{};

	for ( auto _ : state ) {
		// This code gets timed
		last_paths = std::vector<hypro::Path<Number>>{};
		auto roots = hypro::makeRoots<Representation>( automaton );
		auto reacher = hypro::reachability::Reach<Representation>( automaton, settings.fixedParameters(),
																   settings.strategy().front(), roots );
		reacher.computeForwardReachability();

		// plotting
		auto& plt = hypro::Plotter<Number>::getInstance();
		plt.clear();
		plt.rSettings().overwriteFiles = true;
		plt.setFilename( "simplex_watertanks" );

		auto finished_leaves = std::size_t( 0 );
		auto unfinished_leaves = std::size_t( 0 );
		auto leaves = std::size_t( 0 );
		auto nodes = std::size_t( 0 );
		auto cyclic_path_count = std::size_t( 0 );

		for ( const auto& node : hypro::preorder( roots ) ) {
			COUNT( "nodes/flowpipes" );
			++nodes;
			if ( node.getChildren().empty() ) {
				if ( node.hasFixedPoint() == TRIBOOL::TRUE ) {
					COUNT( "Finished leaves" );
					++finished_leaves;
				} else {
					COUNT( "Unfinished leaves" );
					++unfinished_leaves;
					last_paths.push_back( node.getPath() );
					if ( has_discrete_cycle( node.getPath() ) ) {
						++cyclic_path_count;
					} else {
						std::cout << "Path " << node.getPath() << " is truly unfinished." << std::endl;
					}
				}
				++leaves;
				COUNT( "leaves" );
			}
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
		state.counters["fin.leaves"] = double( double( finished_leaves ) / double( leaves ) );
		state.counters["nfin.leaves"] = double( double( unfinished_leaves ) / double( leaves ) );
		state.counters["#fin.leaves"] = double( finished_leaves );
		state.counters["#nfin.leaves"] = double( unfinished_leaves );
		state.counters["leaves"] = leaves;
		state.counters["jumps"] = maxJumps;
		state.counters["nodes"] = nodes;
		state.counters["cycles"] = cyclic_path_count;

		plt.plot2d( hypro::PLOTTYPE::png );
	}

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
	  ->DenseRange( 1, 5, 1 )
	  ->Unit( ::benchmark::kSecond );

}  // namespace hypro::benchmark