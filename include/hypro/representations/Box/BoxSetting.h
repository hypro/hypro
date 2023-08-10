/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../util/type_handling/better_enums/enum_default_ctor.h"
#include "../../util/type_handling/meta/RepresentationCombinations.h"

namespace hypro {

    BETTER_ENUM(boxSetting_name, int,
                BoxLinearOptimizationOn,
                BoxLinearOptimizationOff,
                BoxIntervalArithmeticOff,
                BoxAllOff)

// For box and box_double
// This is the default setting
    struct BoxLinearOptimizationOn {
        static constexpr int type_enum = boxSetting_name::BoxLinearOptimizationOn;
        // used in case we do have a thread-safe optimizer.
        static constexpr bool HYPRO_BOX_AVOID_LINEAR_OPTIMIZATION = false;
        // enables methods from interval arithmetic
        static constexpr bool USE_INTERVAL_ARITHMETIC = true;
        // detects upon construction of a box from constraints whether those already represent a box.
        static constexpr bool DETECT_BOX = true;
    };

    struct BoxLinearOptimizationOff {
        static constexpr int type_enum = boxSetting_name::BoxLinearOptimizationOff;
        // used in case we do not have a thread-safe optimizer. Slow for high dimensions.
        static constexpr bool HYPRO_BOX_AVOID_LINEAR_OPTIMIZATION = true;
        // enables methods from interval arithmetic
        static constexpr bool USE_INTERVAL_ARITHMETIC = true;
        // detects upon construction of a box from constraints whether those already represent a box.
        static constexpr bool DETECT_BOX = true;
    };

    struct BoxIntervalArithmeticOff {
        static constexpr int type_enum = boxSetting_name::BoxIntervalArithmeticOff;
        // used in case we do not have a thread-safe optimizer. Slow for high dimensions.
        static constexpr bool HYPRO_BOX_AVOID_LINEAR_OPTIMIZATION = true;
        // enables methods from interval arithmetic
        static constexpr bool USE_INTERVAL_ARITHMETIC = false;
        // detects upon construction of a box from constraints whether those already represent a box.
        static constexpr bool DETECT_BOX = true;
    };

    struct BoxAllOff {
        static constexpr int type_enum = boxSetting_name::BoxAllOff;
        // used in case we do not have a thread-safe optimizer. Slow for high dimensions.
        static constexpr bool HYPRO_BOX_AVOID_LINEAR_OPTIMIZATION = false;
        // enables methods from interval arithmetic
        static constexpr bool USE_INTERVAL_ARITHMETIC = false;
        // detects upon construction of a box from constraints whether those already represent a box.
        static constexpr bool DETECT_BOX = false;
    };
}  // namespace hypro
