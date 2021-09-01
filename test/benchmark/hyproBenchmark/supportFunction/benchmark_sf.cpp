#include "benchmark_sf.h"

namespace benchmark {
namespace sf {

Results<std::size_t> run( const Settings& settings ) {
	Timer totalRunningTime;
	Results<std::size_t> ress;
	Results<std::size_t> tmp;

	// half-space intersection
	// std::cout << "Benchmarking half space intersection." << std::endl;
	// tmp = intersectHalfspace(settings);
	// tmp.createCSV("sfIntersectHalfspace", "\t", "intersectHalfspace");
	// ress.insert(ress.end(), tmp.begin(), tmp.end());

	// affine transformation
	// std::cout << "Benchmarking affine transformation." << std::endl;
	// tmp = affineTransformation(settings);
	// tmp.createCSV("sfAffineTransformation", "\t");
	// ress.insert(ress.end(), tmp.begin(), tmp.end());

	std::cout << "Benchmarking affine transformation with evaluation." << std::endl;
	auto results = affineTransformationEvaluation( settings );
	results.createCSV( "sfAffineTransformationEvaluation", "\t" );
	// ress.insert(ress.end(), tmp.begin(), tmp.end());

	// union
	// std::cout << "Benchmarking union." << std::endl;
	// tmp = unite(settings);
	// tmp.createCSV("sfUnion", "\t");
	// ress.insert(ress.end(), tmp.begin(), tmp.end());

	// intersection
	// std::cout << "Benchmarking intersection." << std::endl;
	// tmp = intersect(settings);
	// tmp.createCSV("sfIntersection", "\t","intersect");
	// ress.insert(ress.end(), tmp.begin(), tmp.end());

	std::cout << "SF benchmarking took " << totalRunningTime.elapsedMs() << " sec in total." << std::endl;

	return ress;
}

}  // namespace sf
}  // namespace benchmark
