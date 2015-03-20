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

	template<typename Representation, int operation>
	class Benchmark {
	private:
		typedef typename Representation::type Number;

		BenchmarkGenerator<Representation,operation> mGenerator;
		std::vector<Result> mResults;
		Executor<Representation, operation> mExecutor;
		BenchmarkSetup<Number> mSetup;
	public:
		Benchmark(BenchmarkSetup<Number> _setup) : 
			mGenerator(_setup),
			mResults(),
			mExecutor(),
			mSetup(_setup)
		{
			mResults.reserve(mGenerator.size());
			std::cout << "Generate " << _setup.size << " benchmarks for operation " << Generator<Representation,operation>(_setup).name << " ... ";
			double duration = mGenerator.generateBenchmark();
			std::cout << "done (" << duration << " ms)" << std::endl;
			std::cout << "Run benchmarks ... ";
			duration = runBenchmarks();
			std::cout << "done (" << duration << " ms)" << std::endl;
		}

	private:
		double runBenchmarks() {
			Timer clock;
			// execute all benchmarks
			for(unsigned i = 0; i < mSetup.size; ++i) {
				mResults.push_back(mExecutor.run(mGenerator.at(i)));
			}
			return clock.elapsed();
		}
	};

} // namespace

 