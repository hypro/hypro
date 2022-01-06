/**
 * @brief Benchmarking of the polytope representation.
 *
 * @file benchmarkPolytope.h
 * @author Stefan Schupp
 * @date 2018-09-28
 */
#pragma once

#include "../Clock.h"
#include "../Results.h"
#include "../Settings.h"
#include "../types.h"
#include <hypro/flags.h>
#include <hypro/representations/GeometricObjectBase.h>
#include <iostream>
#include <random>
#ifdef HYPRO_USE_PPL
#include "../box/pplStructs.h"
#include <ppl.hh>
#endif

namespace benchmark::polytope {

Results<std::size_t> intersectHalfspace( const Settings& settings );
Results<std::size_t> affineTransformation( const Settings& settings );
Results<std::size_t> unite( const Settings& settings );
Results<std::size_t> intersect( const Settings& settings );
Results<std::size_t> hPolyContainment( const Settings& settings );
Results<std::size_t> hPolyConstruction( const Settings& settings );
Results<std::size_t> run( const Settings& settings );

}  // namespace benchmark::polytope
