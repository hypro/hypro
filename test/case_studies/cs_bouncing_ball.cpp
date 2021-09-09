/*
 * Copyright (c) 2021.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
/*
 * Created by Stefan Schupp <stefan.schupp@tuwien.ac.at> on 02.08.21.
 */

#include <benchmark/benchmark.h>
#include <filesystem>
#include <hypro/algorithms/reachability/Reach.h>
#include <hypro/parser/antlr4-flowstar/ParserWrapper.h>
#include <string>

namespace hypro::benchmark {

static void Bouncing_Ball_Parsing( ::benchmark::State& state ) {
	// Perform setup here
	using Number = double;
	auto base_path = std::filesystem::current_path().parent_path().parent_path().append( "examples/input/" );
	std::string filename{ "bouncing_ball.model" };

	for ( auto _ : state ) {
		// This code gets timed
		auto [automaton, reachSettings] = hypro::parseFlowstarFile<Number>( base_path.string() + filename );
	}
}
// Register the function as a benchmark
BENCHMARK( Bouncing_Ball_Parsing );

template <class Representation>
static void Bouncing_Ball_Reachability( ::benchmark::State& state ) {
	// Perform setup here
	using Number = double;
	auto base_path = std::filesystem::current_path().parent_path().parent_path().append( "examples/input/" );
	std::string filename{ "bouncing_ball.model" };
	auto [automaton, reachSettings] = hypro::parseFlowstarFile<Number>( base_path.string() + filename );
	auto roots = hypro::makeRoots<Representation>( automaton );
	auto settings = hypro::convert( reachSettings );
	auto reacher = hypro::reachability::Reach<Representation>( automaton, settings.fixedParameters(),
															   settings.strategy().front(), roots );

	for ( auto _ : state ) {
		// This code gets timed
		reacher.computeForwardReachability();
	}
}
// Register the function as a benchmark
BENCHMARK_TEMPLATE( Bouncing_Ball_Reachability, hypro::Box<double> );

}  // namespace hypro::benchmark