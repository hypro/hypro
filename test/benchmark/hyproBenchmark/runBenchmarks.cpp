/**
 * @brief Main file which starts all benchmark runs.
 *
 * @file runBenchmarks.cpp
 * @author your name
 * @date 2018-09-28
 */

#include "Clock.h"
#include "Settings.h"
#include "algorithms/singularAnalysis/benchmarkSingularAnalyzer.h"
#include "box/benchmarkBox.h"
#include "polytopes/benchmarkPolytope.h"
#include "supportFunction/benchmark_sf.h"
#include "types.h"
#include <future>
#include <hypro/flags.h>
#include <hypro/representations/GeometricObjectBase.h>
#include <iostream>

int main( int argc, char const *argv[] ) {
	benchmark::Timer general;
	benchmark::Settings s;

	// std::cout << "Benchmark boxes." << std::endl;
	// benchmark::box::run( s );

	std::cout << "Benchmark polytopes." << std::endl;
	s.maxDimension = 6;
	s.iterations = 10;
	// s.iterations = 10000000;
	benchmark::polytope::run( s );

	std::cout << "Benchmark singular analyzer." << std::endl;
	s.maxDimension = 5;
	s.iterations = 4;
	benchmark::singularAnalysis::run( s );

	// std::cout << "Benchmark support functions." << std::endl;
	// benchmark::sf::run( s );
	// std::async(std::launch::async,benchmark::sf::run,s);

	std::cout << "Benchmarking took " << general.elapsedMs() << " sec." << std::endl;
	return 0;
}
