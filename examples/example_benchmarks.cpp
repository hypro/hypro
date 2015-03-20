
#include "../src/lib/representations/Polytopes/VPolytope/VPolytope.h"
#include "../src/test/benchmark/Benchmark.h"

int main(int argc, char** argv) {
	hypro::BenchmarkSetup<double> setup;
	setup.size = 1000;
	setup.vertices = 3;
	setup.dimension = 8;
	setup.minValue = 0;
	setup.maxValue = 10;

	hypro::Benchmark<hypro::VPolytope<double>, hypro::operation::LINEARTRAFO> linearTrafo(setup);
	hypro::Benchmark<hypro::VPolytope<double>, hypro::operation::MINKOWSKISUM> minkowskiSum(setup);
	hypro::Benchmark<hypro::VPolytope<double>, hypro::operation::INTERSECTION> intersection(setup);
	hypro::Benchmark<hypro::VPolytope<double>, hypro::operation::CONTAINS> contains(setup);
	hypro::Benchmark<hypro::VPolytope<double>, hypro::operation::UNION> unite(setup);
}