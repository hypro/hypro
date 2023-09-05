/*
 * Copyright (c) 2021.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../Clock.h"
#include "../Results.h"
#include "../Settings.h"
#include "../types.h"
#include <future>
#include <hypro/flags.h>
#include <hypro/representations/GeometricObjectBase.h>
#include <iostream>
#include <queue>
#include <random>

namespace benchmark {
namespace sf {

Results<std::size_t> intersectHalfspace( const Settings& settings );
Results<std::size_t> affineTransformation( const Settings& settings );

void affineTrafoCreator( std::map<std::size_t, std::vector<hypro::matrix_t<::benchmark::Number>>>& matricesMap,
						 std::map<std::size_t, std::vector<hypro::vector_t<::benchmark::Number>>>& vectorsMap,
						 std::map<std::size_t, std::vector<hypro::vector_t<::benchmark::Number>>>& directionsMap,
						 const Settings& settings );

template <typename SFSettings>
Results<std::size_t> affineTrafoHelper(
	  const std::vector<hypro::matrix_t<::benchmark::Number>>& matrices,
	  const std::vector<hypro::vector_t<::benchmark::Number>>& vectors,
	  const std::vector<hypro::vector_t<::benchmark::Number>>& directions, std::size_t dimension, std::string name,
	  const Settings& settings,
	  const hypro::SupportFunctionT<::benchmark::Number, hypro::Converter<::benchmark::Number>, SFSettings>& sf ) {
	Results<std::size_t> ress;
	// for all configurations, i.e. all combinations of dimension, multiplications and evaluations run #instances many
	// experiments.
	for ( std::size_t m = 0; m < settings.multiplications; m += settings.stepSizeMultiplications ) {
		for ( std::size_t e = 0; e < settings.evaluations; e += settings.stepSizeEvaluations ) {
			Timer runTimerHyPro;
			for ( std::size_t i = 0; i < settings.iterations; ++i ) {
				auto tmp = sf;
				for ( std::size_t mCounter = 0; mCounter < m; ++mCounter ) {
					tmp = tmp.affineTransformation( matrices[i], vectors[i] );
				}
				for ( std::size_t eCounter = 0; eCounter < e; ++eCounter ) {
					tmp.evaluate( directions[i] );
				}
			}
			auto runningTime = runTimerHyPro.elapsed();
			std::vector<std::size_t> data;
			data.push_back( m );
			data.push_back( e );
			ress.emplace_back( { name, runningTime / settings.iterations, static_cast<int>( dimension ), data } );
			std::cout << "Dimension " << d << ", m " << m << ", e " << e << ":  Running took " << runningTime.count()
					  << " sec." << std::endl;
		}
	}
	return ress;
}

Results<std::size_t> affineTransformationEvaluation( const Settings& settings );
Results<std::size_t> unite( const Settings& settings );
Results<std::size_t> intersect( const Settings& settings );
Results<std::size_t> run( const Settings& settings );

}  // namespace sf
}  // namespace benchmark
