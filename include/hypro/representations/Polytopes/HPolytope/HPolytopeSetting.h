/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../../util/type_handling/better_enums/enum_default_ctor.h"
#include "../../../util/type_handling/meta/RepresentationCombinations.h"

namespace hypro {

    BETTER_ENUM(hPolytopeSetting_name, int,
                HPolytopeSetting, HPolytopeOptimizerCaching, HPolytopeBoundingBoxCaching)

// For usage as main representation of each segment
    struct HPolytopeSetting {
        static constexpr int type_enum = hPolytopeSetting_name::HPolytopeSetting;
        static constexpr bool REDUCE_NUMBERS = false;
        static constexpr bool AVOID_CONVERSION = true;
        static constexpr bool OPTIMIZER_CACHING = false;
        static constexpr bool NAIVE_ALGORITHMS = false;
        static constexpr bool CACHE_BOUNDING_BOX = false;
        static constexpr bool SAFE_LP_CALLS = true;
    };

// For usage as leaf in SupportFunctionNew
    struct HPolytopeOptimizerCaching {
        static constexpr int type_enum = hPolytopeSetting_name::HPolytopeOptimizerCaching;
        static constexpr bool REDUCE_NUMBERS = true;
        static constexpr bool AVOID_CONVERSION = true;
        static constexpr bool OPTIMIZER_CACHING = true;
        static constexpr bool NAIVE_ALGORITHMS = false;
        static constexpr bool CACHE_BOUNDING_BOX = false;
        static constexpr bool SAFE_LP_CALLS = true;
    };

// increased caching for faster containment check (improves e.g., Monte Carlo Sampling)
    struct HPolytopeBoundingBoxCaching {
        static constexpr int type_enum = hPolytopeSetting_name::HPolytopeOptimizerCaching;
        static constexpr bool REDUCE_NUMBERS = true;
        static constexpr bool AVOID_CONVERSION = true;
        static constexpr bool OPTIMIZER_CACHING = true;
        static constexpr bool NAIVE_ALGORITHMS = false;
        static constexpr bool CACHE_BOUNDING_BOX = true;
        static constexpr bool SAFE_LP_CALLS = true;
    };

}  // namespace hypro
