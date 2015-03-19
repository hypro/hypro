
#include "../src/lib/representations/Polytopes/VPolytope/VPolytope.h"
#include "../src/test/benchmark/Benchmark.h"

int main(int argc, char** argv) {
	hypro::BenchmarkSetup<double> setup;
	setup.size = 3;
	setup.vertices = 3;
	setup.dimension = 2;
	setup.minValue = 0;
	setup.maxValue = 10;

	hypro::Benchmark<hypro::ContainsGenerator<hypro::VPolytope<double>,double>, hypro::ContainsExecutor<hypro::VPolytope<double>,double>, double> b(setup);
}