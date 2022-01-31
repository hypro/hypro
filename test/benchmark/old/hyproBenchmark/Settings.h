/*
 * Copyright (c) 2021.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

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
