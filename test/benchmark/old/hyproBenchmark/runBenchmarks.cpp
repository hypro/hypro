/*
 * Copyright (c) 2021.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * @brief Main file which starts all benchmark runs.
 *
 * @file runBenchmarks.cpp
 * @author your name
 * @date 2018-09-28
 */

#include "Clock.h"
#include "Settings.h"
#include "box/benchmarkBox.h"
#include "polytopes/benchmarkPolytope.h"
#include "algorithms/singularAnalysis/benchmarkSingularAnalyzer.h"
#include "algorithms/decompositionalAnalysis/benchmarkDecompositionalAnalyzer.h"
#include "supportFunction/benchmark_sf.h"
#include "types.h"
#include <hypro/flags.h>
#include <future>
#include <iostream>
#include <hypro/representations/GeometricObjectBase.h>

int main( int argc, char const *argv[] ) {
	benchmark::Timer general;
	benchmark::Settings s;

	// std::cout << "Benchmark boxes." << std::endl;
	// benchmark::box::run( s );

	std::cout << "Benchmark polytopes." << std::endl;
	s.maxDimension = 6;
	s.iterations = 10;
	//s.iterations = 10000000;
	benchmark::polytope::run( s );

	std::cout << "Benchmark singular analyzer." << std::endl;
	s.maxDimension = 5;
	s.iterations = 4;
	benchmark::singularAnalysis::run( s );

	std::cout << "Benchmark decompositional analyzer." << std::endl;
	benchmark::decompositionalAnalysis::run( s );

	// std::cout << "Benchmark support functions." << std::endl;
	// benchmark::sf::run( s );
	// std::async(std::launch::async,benchmark::sf::run,s);

	std::cout << "Benchmarking took " << general.elapsedMs() << " sec." << std::endl;
	return 0;
}
