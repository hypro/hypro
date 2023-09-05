/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Created by Stefan Schupp <stefan.schupp@tuwien.ac.at> on 10.11.21.
 */

#include <benchmark/benchmark.h>
#include <hypro/algorithms/reachability/Reach.h>
#include <hypro/datastructures/HybridAutomaton/PathUtil.h>
#include <hypro/datastructures/Hyperoctree.h>
#include <hypro/datastructures/reachability/ReachTreev2Util.h>
#include <hypro/parser/antlr4-flowstar/ParserWrapper.h>
#include <hypro/paths.h>
#include <hypro/util/logging/Logger.h>
#include <hypro/util/plotting/Plotter.h>
#include <random>
#include <string>

namespace hypro::benchmark {

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
        hypro::Box<double> bbox = computeBoundingBox(roots).projectOn({0, 1});
	// widen dimensions until they are integer to increase stability
        std::vector<carl::Interval<double>> newIntervals;
        for (auto &interval: bbox.intervals()) {
            newIntervals.push_back(carl::Interval<double>(std::floor(interval.lower()), std::ceil(interval.upper())));
	}
        bbox = hypro::Box<double>(newIntervals);

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
	st.counters["contained"] = ::benchmark::Counter( count );
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
		++total;
	}
	st.counters["contained"] = ::benchmark::Counter( count );
}

}  // namespace hypro::benchmark
