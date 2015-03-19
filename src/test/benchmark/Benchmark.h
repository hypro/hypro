/**
 * File that holds the implementation of a benchmark, which consists of a set of benchmarks, an executor and some additional information.
 * @file Benchmark.h
 * 
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * 
 * @since 	2015-03-19
 * @version 	2015-03-19
 */

 #pragma once

 #include "Timer.h"
 #include "BenchmarkSetup.h"
 #include "BenchmarkGenerator.h"
 #include "ObjectGenerator.h"
 #include "Generators.h"
 #include "Executors.h"
 #include "Result.h"
 #include <vector>
 #include <iostream>

namespace hypro {

	template<typename Generator, typename Executor, typename Number>
	class Benchmark {
	private:
		BenchmarkGenerator<Generator, Number> mGenerator;
		std::vector<Result> mResults;
		Executor mExecutor;
		BenchmarkSetup<Number> mSetup;
	public:
		Benchmark(BenchmarkSetup<Number> _setup) : 
			mGenerator(_setup),
			mResults(),
			mExecutor(),
			mSetup(_setup)
		{
			mResults.reserve(mGenerator.size());
			mGenerator.generateBenchmark();
			double duration = runBenchmarks();
			std::cout << "It took " << duration << std::endl;
		}

	private:
		double runBenchmarks() {
			Timer<unsigned> clock;
			// execute all benchmarks
			for(unsigned i = 0; i < mSetup.size; ++i) {
				mResults.push_back(mExecutor.run(mGenerator.at(i)));
			}
			return clock.elapsed();
		}
	};

} // namespace

 