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
#include <hypro/flags.h>
#include <future>
#include <iosfwd>
#include <random>
#include <hypro/representations/GeometricObjectBase.h>
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
