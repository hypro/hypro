#pragma once

#include "../Clock.h"
#include "../Results.h"
#include "../Settings.h"
#include "../types.h"
#include <flags.h>
#include <representations/GeometricObject.h>
#include <iostream>
#include <random>

namespace benchmark {
namespace sf {

    Results<std::size_t> intersectHalfspace(const Settings& settings);
    Results<std::size_t> affineTransformation(const Settings& settings);
    Results<std::size_t> unite(const Settings& settings);
    Results<std::size_t> intersect(const Settings& settings);
    Results<std::size_t> run(const Settings& settings);

} // sf
} // benchmark
