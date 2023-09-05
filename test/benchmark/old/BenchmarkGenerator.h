/*
 * Copyright (c) 2021.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * File that holds the class of the benchmark generator, which creates a set of benchmarks according to the
 * BenchmarkInformation passed.
 * @file BenchmarkGenerator.h
 *
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since 	2015-03-19
 * @version 	2015-03-19
 */

#pragma once

#include "Generators.h"
#include "Timer.h"
#include <vector>

namespace hypro {
template <typename Representation, typename Number, int operation>
class BenchmarkGenerator {
  private:
	BenchmarkSetup<Number> mSetup;
	std::vector<typename Generator<Representation, Number, operation>::type> mBenchmarks;

  public:
	BenchmarkGenerator( BenchmarkSetup<Number> _setup ) : mSetup( _setup ) {}

	double generateBenchmark() {
		Generator<Representation, Number, operation> g( mSetup );
		Timer t;
		for ( unsigned i = 0; i < mSetup.size; ++i ) {
			mBenchmarks.emplace_back( g() );
		}
		return t.elapsed();
	}

	void setBenchmark( const std::vector<typename Generator<Representation, Number, operation>::type>& bms ) {
		mBenchmarks = bms;
	}

	typename Generator<Representation, Number, operation>::type at( unsigned _pos ) { return mBenchmarks.at( _pos ); }

	template <typename Other>
	std::vector<typename Generator<Other, Number, operation>::type> convert() const {
		std::vector<typename Generator<Other, Number, operation>::type> res;
		for ( const auto& bm : mBenchmarks ) {
			res.emplace_back( std::make_tuple( Other( std::get<0>( bm ) ), std::get<1>( bm ) ) );
		}
		return res;
	}

	unsigned size() const { return mBenchmarks.size(); }
};
}  // namespace hypro
