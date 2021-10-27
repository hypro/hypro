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
#include <hypro/datastructures/Hyperoctree.h>
#include <hypro/datastructures/reachability/ReachTreev2Util.h>
#include <hypro/parser/antlr4-flowstar/ParserWrapper.h>
#include <hypro/paths.h>
#include <hypro/util/plotting/Plotter.h>
#include <random>
#include <string>

namespace hypro::benchmark {

void plotRecursive( const hypro::Hyperoctree<double>& octree, hypro::Plotter<double>& plt ) {
	if ( octree.isCovered() ) {
		plt.addObject( octree.getContainer().projectOn( { 0, 1 } ).vertices(),
					   hypro::plotting::colors[hypro::plotting::green] );
	} else {
		if ( !octree.getChildren().empty() ) {
			for ( const auto& child : octree.getChildren() ) {
				plotRecursive( *child, plt );
			}
		} else {
			plt.addObject( octree.getContainer().projectOn( { 0, 1 } ).vertices(),
						   hypro::plotting::colors[hypro::plotting::red] );
		}
	}
}

class HyperOctreeFixture : public ::benchmark::Fixture {
	using Number = double;

  public:
	void SetUp( const ::benchmark::State& state ) {
		std::string filename{ "21_simplex_watertanks_deterministic_monitor_small_init.model" };

		auto [automaton, reachSettings] = hypro::parseFlowstarFile<Number>( getCSModelsPath() + filename );

		auto settings = hypro::convert( reachSettings );
		settings.rStrategy().front().detectJumpFixedPoints = true;
		settings.rStrategy().front().detectFixedPointsByCoverage = false;
		settings.rStrategy().front().detectContinuousFixedPointsLocally = false;
		settings.rFixedParameters().localTimeHorizon = 100;
		settings.rFixedParameters().jumpDepth = 15;
		settings.rStrategy().begin()->aggregation = AGG_SETTING::AGG;
		std::vector<hypro::Path<Number>> last_paths{};

		roots = hypro::makeRoots<hypro::Box<Number>>( automaton );
		auto reacher = hypro::reachability::Reach<hypro::Box<Number>>( automaton, settings.fixedParameters(),
																	   settings.strategy().front(), roots );
		auto result = reacher.computeForwardReachability();
	}

	void TearDown( const ::benchmark::State& state ) {}

	std::vector<hypro::ReachTreeNode<hypro::Box<Number>>> roots;
	std::mt19937 generator;
	std::uniform_real_distribution<double> dist = std::uniform_real_distribution<double>( 0, 1 );
};

BENCHMARK_F( HyperOctreeFixture, HyperOctree )( ::benchmark::State& st ) {
	// create hyperoctree
	auto bbox = computeBoundingBox( roots ).projectOn( { 0, 1 } );
	// widen dimensions until they are integer to increase stability
	for ( auto& interval : bbox.rIntervals() ) {
		interval = carl::Interval<double>( std::floor( interval.lower() ), std::ceil( interval.upper() ) );
	}

	hypro::Hyperoctree<double> octree{ 2, 8, bbox };
	// add to hyperoctree
	for ( const auto& r : roots ) {
		auto segments = getSegments( r );
		for ( const auto& s : segments ) {
			octree.add( s.projectOn( { 0, 1 } ) );
		}
	}

	std::size_t count = 0;
	for ( auto _ : st ) {
		// create point
		hypro::vector_t<double> coordinates = hypro::vector_t<double>( 2 );
		for ( std::size_t d = 0; d < 2; ++d ) {
			coordinates( d ) = dist( generator );
		}
		hypro::Point<double> point{ coordinates };
		auto res = octree.contains( point );
		if ( res ) {
			++count;
		}
	}
	st.counters["contained"] = count;
}

BENCHMARK_F( HyperOctreeFixture, ClassicLookup )( ::benchmark::State& st ) {
	std::vector<hypro::Box<double>> segments;
	for ( const auto& r : roots ) {
		auto tmp = getSegments( r );
		for ( auto& segment : tmp ) {
			segments.push_back( segment.projectOn( { 0, 1 } ) );
		}
	}

	std::size_t count = 0;
	for ( auto _ : st ) {
		// create point
		hypro::vector_t<double> coordinates = hypro::vector_t<double>( 2 );
		for ( std::size_t d = 0; d < 2; ++d ) {
			coordinates( d ) = dist( generator );
		}
		hypro::Point<double> point{ coordinates };
		auto res = std::any_of( std::begin( segments ), std::end( segments ),
								[&point]( const auto& seg ) { return seg.contains( point ); } );
		if ( res ) {
			++count;
		}
	}
	st.counters["contained"] = count;
}

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

	// create hyperoctree
	auto bbox = computeBoundingBox( roots ).projectOn( { 0, 1 } );
	// widen dimensions until they are integer to increase stability
	for ( auto& interval : bbox.rIntervals() ) {
		interval = carl::Interval<double>( std::floor( interval.lower() ), std::ceil( interval.upper() ) );
	}

	hypro::Hyperoctree<Number> octree{ 2, 6, bbox };
	// add to hyperoctree
	for ( const auto& r : roots ) {
		auto segments = getSegments( r );
		for ( const auto& s : segments ) {
			octree.add( s.projectOn( { 0, 1 } ) );
		}
	}

	// test some random points
	std::mt19937 generator;
	std::uniform_real_distribution<double> dist = std::uniform_real_distribution<double>( 0, 1 );
	for ( std::size_t i = 0; i < 100; ++i ) {
		hypro::vector_t<double> coordinates = hypro::vector_t<double>( 2 );
		for ( std::size_t d = 0; d < 2; ++d ) {
			coordinates( d ) = dist( generator );
		}
		hypro::Point<double> point{ coordinates };
		if ( octree.contains( point ) ) {
			plt.addPoint( point, hypro::plotting::colors[hypro::plotting::green] );
		} else {
			plt.addPoint( point, hypro::plotting::colors[hypro::plotting::red] );
		}
	}

	for ( const auto& node : hypro::preorder( roots ) ) {
		for ( const auto& segment : node.getFlowpipe() ) {
			if ( node.hasFixedPoint() == TRIBOOL::TRUE ) {
				plt.addObject( segment.projectOn( { 0, 1 } ).vertices(),
							   hypro::plotting::colors[hypro::plotting::blue] );
			} else if ( node.hasFixedPoint() == TRIBOOL::FALSE ) {
				plt.addObject( segment.projectOn( { 0, 1 } ).vertices(),
							   hypro::plotting::colors[hypro::plotting::orange] );
			} else {
				plt.addObject( segment.projectOn( { 0, 1 } ).vertices() );
			}
		}
	}

	// plot octree
	plotRecursive( octree, plt );

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
	  ->DenseRange( 15, 15, 1 )
	  ->Unit( ::benchmark::kSecond );

}  // namespace hypro::benchmark
