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
#include <flags.h>
#include <representations/GeometricObject.h>
#include <iostream>
#include <random>
#ifdef HYPRO_USE_PPL
#include "pplStructs.h"
#include <ppl.hh>
#endif

namespace benchmark {
namespace box
{
    Results<int> intersectHalfspace(const Settings& settings);
    Results<int> affineTransformation(const Settings& settings);
    Results<int> unite(const Settings& settings);
    Results<int> intersect(const Settings& settings);
    Results<int> run(const Settings& settings);

} // box
} // namespace benchmark