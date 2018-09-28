/**
 * @brief Benchmarking of the box representation.
 * 
 * @file benchmarkBox.h
 * @author Stefan Schupp
 * @date 2018-09-28
 */
#pragma once

#include "Clock.h"
#include "Results.h"
#include "Settings.h"
#include <iostream>

namespace benchmark {
namespace box
{
    Results run(const Settings& settings);
} // box
} // namespace benchmark