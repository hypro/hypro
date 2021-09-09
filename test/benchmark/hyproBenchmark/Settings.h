/**
 * @brief General benchmark settings.
 *
 * @file Settings.h
 * @author Stefan Schupp
 * @date 2018-09-28
 */
#pragma once

namespace benchmark {
struct Settings {
	std::size_t maxDimension = 100;	 // maximal dimension for benchmark objects
	std::size_t iterations = 10;	 // number of iterations per benchmark
	static constexpr std::size_t multiplications = 100;
	static constexpr std::size_t evaluations = 100;
	static constexpr std::size_t stepSize = 5;
	static constexpr std::size_t stepSizeEvaluations = 10;
	static constexpr std::size_t stepSizeMultiplications = 2;
	static constexpr std::size_t timeoutSec =
		  60;  // if an operation takes longer than this, stop computing it from now on.
};
}  // namespace benchmark
