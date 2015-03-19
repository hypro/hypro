/**
 * File that holds the class of the benchmark generator, which creates a set of benchmarks according to the BenchmarkInformation passed.
 * @file BenchmarkGenerator.h
 * 
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * 
 * @since 	2015-03-19
 * @version 	2015-03-19
 */

#pragma once

 #include <vector>

namespace hypro {
	template<typename Generator, typename Number>
	class BenchmarkGenerator {
	private:
		BenchmarkSetup<Number> mSetup;
		std::vector<typename Generator::type> mBenchmarks;
	public:
		BenchmarkGenerator(BenchmarkSetup<Number> _setup) : 
			mSetup(_setup)
		{}

		void generateBenchmark() {
			Generator g(mSetup);
			for(unsigned i = 0; i < mSetup.size; ++i) {
				mBenchmarks.emplace_back(g());
			}
		}

		typename Generator::type at(unsigned _pos) {
			return mBenchmarks.at(_pos);
		}

		unsigned size() const {
			return mBenchmarks.size();
		}
	};
}

