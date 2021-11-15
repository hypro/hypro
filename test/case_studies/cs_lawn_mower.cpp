/*
 * Created by stefan on 04.08.21.
 */

#include <benchmark/benchmark.h>
#include <filesystem>
#include <hypro/algorithms/reachability/Reach.h>
#include <hypro/parser/antlr4-flowstar/ParserWrapper.h>
#include <hypro/util/plotting/Plotter.h>
#include <hypro/paths.h>
#include <string>

namespace hypro::benchmark {

template <class Representation>
static void Lawn_Mower_Reachability( ::benchmark::State& state ) {
	// store arguments
	std::size_t maxJumps = state.range( 0 );
	// clear statistics
	RESET_STATS();
	// Perform setup here
	using Number = double;
	auto base_path = getCSModelsPath();
	std::string filename{ "lawn_mower.model" };

	auto [automaton, reachSettings] = hypro::parseFlowstarFile<Number>( base_path + filename );

	auto settings = hypro::convert( reachSettings );
	//settings.rFixedParameters().detectFixedPoints = true;
	settings.rStrategy().begin()->detectJumpFixedPoints = true;
	// settings.rFixedParameters().localTimeHorizon = 1;
	settings.rFixedParameters().jumpDepth = maxJumps;
	settings.rStrategy().begin()->aggregation = AGG_SETTING::AGG;
	std::vector<hypro::Path<Number>> last_paths{};

	for ( auto _ : state ) {
		// This code gets timed
		last_paths = std::vector<hypro::Path<Number>>{};
		auto roots = hypro::makeRoots<Representation>( automaton );
		auto reacher = hypro::reachability::ReachUrgency<Representation>( automaton, settings.fixedParameters(),
																   settings.strategy().front(), roots );
		reacher.computeForwardReachability();

		// plotting
		auto& plt = hypro::Plotter<Number>::getInstance();
		plt.clear();
		plt.rSettings().overwriteFiles = true;
		plt.setFilename( "lawn_mower" );

		auto finished_leaves = std::size_t( 0 );
		auto unfinished_leaves = std::size_t( 0 );
		auto leaves = std::size_t( 0 );
		auto nodes = std::size_t( 0 );

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
// BENCHMARK_TEMPLATE( Lawn_Mower_Reachability, hypro::SupportFunction<double> )->DenseRange(1, 3, 1);
BENCHMARK_TEMPLATE( Lawn_Mower_Reachability, hypro::Box<double> )
	  ->DenseRange( 1, 40, 1 )
	  ->Unit( ::benchmark::kSecond );

}  // namespace hypro::benchmark