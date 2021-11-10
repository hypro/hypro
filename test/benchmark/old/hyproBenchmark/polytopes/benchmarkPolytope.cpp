/*
 * Copyright (c) 2021.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "benchmarkPolytope.h"

namespace benchmark::polytope {

Results<std::size_t> run( const Settings& settings ) {
	Timer totalRunningTime;
	Results<std::size_t> ress;

	// half-space intersection
	// std::cout << "Benchmarking half space intersection." << std::endl;
	// auto tmp = intersectHalfspace(settings);
	// tmp.createCSV("polytopeIntersectHalfspace", "\t", "intersectHalfspace");
	// tmp.createCSV("polytopeIntersectHalfspacePPL", "\t", "intersectHalfspacePPL");
	// ress.insert(ress.end(), tmp.begin(), tmp.end());

	// affine transformation
	// std::cout << "Benchmarking affine transformation." << std::endl;
	// auto tmp = affineTransformation( settings );
	// tmp.createCSV( "polytopeAffineTransformation", "\t" );
	// ress.insert( ress.end(), tmp.begin(), tmp.end() );

	// union
	// std::cout << "Benchmarking union." << std::endl;
	// tmp = unite(settings);
	// tmp.createCSV("polytopeUnion", "\t");
	// ress.insert(ress.end(), tmp.begin(), tmp.end());

	// intersection
	// std::cout << "Benchmarking intersection." << std::endl;
	// tmp = intersect( settings );
	// tmp.createCSV( "polytopeIntersection", "\t", "intersect" );
	// tmp.createCSV( "polytopeIntersectionPPL", "\t", "intersectPPL" );
	// ress.insert( ress.end(), tmp.begin(), tmp.end() );

	// hpoly containment
	std::cout << "Benchmarking containment with and without cache." << std::endl;
	auto tmp = hPolyContainment( settings );
	tmp.createCSV( "polytopeContainment", "\t", "hPolyContainmentRegular" );
	tmp.createCSV( "polytopeContainmentCache", "\t", "hPolyContainmentCache" );
	ress.insert( ress.end(), tmp.begin(), tmp.end() );

	std::cout << "Benchmarking HPolytope construction from list of vertices." << std::endl;
	tmp = hPolyConstruction( settings );
	ress.insert( ress.end(), tmp.begin(), tmp.end() );

	std::cout << "Polytope benchmarking took " << totalRunningTime.elapsedMs() << " sec in total." << std::endl;

	return ress;
}

}  // namespace benchmark::polytope
