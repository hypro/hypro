/*
 * Copyright (c) 2021.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "benchmarkSingularAnalyzer.h"

namespace benchmark::singularAnalysis {

Results<std::size_t> run( const Settings& settings ) {
	Timer totalRunningTime;
	Results<std::size_t> ress;

	std::cout << "Benchmarking singular time elapse." << std::endl;

	auto tmp = singularTimeElapse( settings );
	tmp.createCSV( "singularTimeElapse", "\t", "singularTimeElapse" );
	ress.insert( ress.end(), tmp.begin(), tmp.end() );

	std::cout << "Benchmarking singular with jumps." << std::endl;
	tmp = singularJumps( settings );
	tmp.createCSV( "singularJumps", "\t", "singularJumps" );
	ress.insert( ress.end(), tmp.begin(), tmp.end() );

	std::cout << "Singular analyzer benchmarking took " << totalRunningTime.elapsedMs() << " sec in total."
			  << std::endl;

	return ress;
}

}  // namespace benchmark::singularAnalysis
