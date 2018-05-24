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

#include "Timer.h"
 #include "Generators.h"
 #include <vector>

namespace hypro {
	template<typename Representation, typename Number, int operation>
	class BenchmarkGenerator {
	private:
		BenchmarkSetup<Number> mSetup;
		std::vector<typename Generator<Representation, Number, operation>::type> mBenchmarks;
	public:
		BenchmarkGenerator(BenchmarkSetup<Number> _setup) : 
			mSetup(_setup)
		{}

		double generateBenchmark() {
			Generator<Representation, Number, operation> g(mSetup);
			Timer t;
			for(unsigned i = 0; i < mSetup.size; ++i) {
				mBenchmarks.emplace_back(g());
			}
			return t.elapsed();
		}

		typename Generator<Representation, Number, operation>::type at(unsigned _pos) {
			return mBenchmarks.at(_pos);
		}

		unsigned size() const {
			return mBenchmarks.size();
		}
	};
}

