/*
 * Copyright (c) 2021.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "benchmarkBox.h"

namespace benchmark::box {

Results<std::size_t> run( const Settings& settings ) {
	Timer totalRunningTime;
	Results<std::size_t> ress;
	std::vector<std::future<Results<std::size_t>>> workingTasks;

	workingTasks.emplace_back( std::async( std::launch::deferred, intersectHalfspace, settings ) );
	workingTasks.emplace_back( std::async( std::launch::deferred, affineTransformation, settings ) );
	workingTasks.emplace_back( std::async( std::launch::deferred, unite, settings ) );
	workingTasks.emplace_back( std::async( std::launch::deferred, intersect, settings ) );
	workingTasks.emplace_back( std::async( std::launch::deferred, computeSupport, settings ) );

	// half-space intersection
	auto tmp = workingTasks[0].get();
	tmp.createCSV( "boxIntersectHalfspace", "\t", "intersectHalfspace" );
	tmp.createCSV( "boxIntersectHalfspaceNaive", "\t", "intersectHalfspaceNaive" );
	tmp.createCSV( "boxIntersectHalfspacePPL", "\t", "intersectHalfspacePPL" );
	std::cout << "Benchmarked hsp intersection." << std::endl;

	// affine transformation
	tmp = workingTasks[1].get();
	tmp.createCSV( "boxAffineTransformation", "\t", "affineTransformation" );
	tmp.createCSV( "boxAffineTransformationNaive", "\t", "affineTransformationNaive" );
	std::cout << "Benchmarked affine transformation." << std::endl;

	// union
	tmp = workingTasks[2].get();
	tmp.createCSV( "boxUnion", "\t" );
	std::cout << "Benchmarked union." << std::endl;

	// satisfies half-spaces
	// satisfiesHalfspaces(settings);
	// std::cout << "Box benchmarking took " << totalRunningTime.elapsedMs() << " sec in total." << std::endl;

	// intersection
	tmp = workingTasks[3].get();
	tmp.createCSV( "boxIntersection", "\t", "intersect" );
	tmp.createCSV( "boxIntersectionPPL", "\t", "intersectPPL" );
	std::cout << "Benchmarked intersection." << std::endl;

	// support
	tmp = workingTasks[4].get();
	tmp.createCSV( "boxComputeSupport", "\t", "computeSupport" );
	tmp.createCSV( "boxComputeSupportNaive", "\t", "computeSupportNaive" );
	std::cout << "Benchmarked compute support." << std::endl;

	return ress;
}

}  // namespace benchmark::box
