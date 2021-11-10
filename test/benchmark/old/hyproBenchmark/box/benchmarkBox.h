/*
 * Copyright (c) 2021.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * @brief Benchmarking of the box representation.
 *
 * @file benchmarkBox.h
 * @author Stefan Schupp
 * @date 2018-09-28
 */
#pragma once

#include "../Clock.h"
#include "../Results.h"
#include "../Settings.h"
#include "../types.h"
#include <future>
#include <hypro/flags.h>
#include <hypro/representations/GeometricObjectBase.h>
#include <iosfwd>
#include <random>
#ifdef HYPRO_USE_PPL
#include "pplStructs.h"
#include <ppl.hh>
#endif

namespace benchmark {
namespace box {
Results<std::size_t> intersectHalfspace( const Settings& settings );
Results<std::size_t> affineTransformation( const Settings& settings );
Results<std::size_t> unite( const Settings& settings );
Results<std::size_t> intersect( const Settings& settings );
Results<std::size_t> computeSupport( const Settings& settings );
Results<std::size_t> run( const Settings& settings );
}  // namespace box
}  // namespace benchmark
