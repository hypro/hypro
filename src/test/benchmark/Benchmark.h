/**
 * File that holds the implementation of a benchmark, which consists of a set of benchmarks, an executor and some
 * additional information.
 * @file Benchmark.h
 *
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since 	2015-03-19
 * @version 	2015-03-19
 */

#pragma once

#include "BenchmarkGenerator.h"
#include "BenchmarkSetup.h"
#include "Executors.h"
#include "Generators.h"
#include "ObjectGenerator.h"
#include "Result.h"
#include "Timer.h"
#ifdef COMPARE_POLYMAKE
#include "polymake_util/converter.h"
#endif

#include <iostream>
#include <vector>

namespace hypro {

template <typename Representation, typename Number, int operation>
class Benchmark {
  private:
	BenchmarkGenerator<Representation, Number, operation> mGenerator;
	std::vector<Result> mResults;
	Executor<Representation, Number, operation> mExecutor;
	BenchmarkSetup<Number> mSetup;
#ifdef COMPARE_POLYMAKE
	polymake::Main mPolyMain;
#endif
  public:
	Benchmark() = default;

	Benchmark( BenchmarkSetup<Number> _setup ) : mGenerator( _setup ), mResults(), mExecutor(), mSetup( _setup ) {
#ifdef COMPARE_POLYMAKE
		mPolyMain();
#endif
		mResults.reserve( mGenerator.size() );
		std::cout << "Generate " << _setup.size << " benchmarks for operation "
				  << Generator<Representation, Number, operation>( _setup ).name << " ... ";
		double duration = mGenerator.generateBenchmark();
		std::cout << "done (" << duration << " ms)" << std::endl;
		std::cout << "Run benchmarks ... ";
		duration = runBenchmarks();
		std::cout << "done (" << duration << " ms)" << std::endl;
	}

	Benchmark( BenchmarkSetup<Number> _setup, const BenchmarkGenerator<Representation, Number, operation>& generator )
		: mGenerator( generator ), mResults(), mExecutor(), mSetup( _setup ) {
		mResults.reserve( mGenerator.size() );
		std::cout << "Run benchmarks ... ";
		double duration = runBenchmarks();
		std::cout << "done (" << duration << " ms)" << std::endl;
	}

	const BenchmarkGenerator<Representation, Number, operation>& getGenerator() const { return mGenerator; }
	void setSetup( const BenchmarkSetup<Number>& inSetup ) { mSetup = inSetup; }

	// template<typename Other>
	// BenchmarkGenerator<Other,Number,operation> convertRepresentation() const;

  private:
	double runBenchmarks() {
		Timer clock;
		// execute all benchmarks
		for ( unsigned i = 0; i < mSetup.size; ++i ) {
			mResults.push_back( mExecutor.run( mGenerator.at( i ) ) );
		}
		return clock.elapsed();
	}
};

}  // namespace hypro
