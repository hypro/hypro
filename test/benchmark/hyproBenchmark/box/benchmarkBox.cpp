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
