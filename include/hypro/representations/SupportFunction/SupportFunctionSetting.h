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

    BETTER_ENUM(supportFunctionSetting_name, int,
                SupportFunctionSetting,
                NoBoxReduction,
                NoBoxDetection,
                NoTrafoReduction,
                NoReduction,
                PolytopeSupportFunctionSetting)

    struct SupportFunctionSetting {
        static constexpr int type_enum = supportFunctionSetting_name::SupportFunctionSetting;
        static constexpr bool SUPPORTFUNCTION_VERBOSE = false;
        static constexpr bool USE_LIN_TRANS_REDUCTION = true;
        static constexpr bool REDUCE_TO_BOX = true;
        static constexpr bool DETECT_BOX = true;
        static constexpr bool AVOID_INTERSECTIONS = true;
        static constexpr bool BOXSUPPORTFUNCTION_VERBOSE = false;
        static constexpr bool BOXOPERATOR_VERBOSE = false;
        static constexpr bool CALCEPSILON_VERBOSE = false;
        static constexpr bool CALCVALUES_VERBOSE = false;
        static constexpr bool TEST_ = false;
        static constexpr bool PPOLYTOPESUPPORTFUNCTION_VERBOSE = false;
        static constexpr bool PPOLYTOPESUPPORTFUNCTION_VERIFY = true;
        // static constexpr bool HYPRO_USE_VECTOR_CACHING = false;
    };

    struct NoBoxReduction : SupportFunctionSetting {
        static constexpr int type_enum = supportFunctionSetting_name::NoBoxReduction;
        static constexpr bool REDUCE_TO_BOX = false;
    };

    struct NoBoxDetection : SupportFunctionSetting {
        static constexpr int type_enum = supportFunctionSetting_name::NoBoxDetection;
        static constexpr bool REDUCE_TO_BOX = false;
        static constexpr bool DETECT_BOX = false;
    };

    struct NoTrafoReduction : SupportFunctionSetting {
        static constexpr int type_enum = supportFunctionSetting_name::NoTrafoReduction;
        static constexpr bool USE_LIN_TRANS_REDUCTION = false;
    };

    struct NoReduction : SupportFunctionSetting {
        static constexpr int type_enum = supportFunctionSetting_name::NoReduction;
        static constexpr bool SUPPORTFUNCTION_VERBOSE = false;
        static constexpr bool USE_LIN_TRANS_REDUCTION = false;
        static constexpr bool REDUCE_TO_BOX = false;
        static constexpr bool DETECT_BOX = false;
        static constexpr bool BOXSUPPORTFUNCTION_VERBOSE = false;
        static constexpr bool BOXOPERATOR_VERBOSE = false;
        static constexpr bool CALCEPSILON_VERBOSE = false;
        static constexpr bool CALCVALUES_VERBOSE = false;
        static constexpr bool TEST_ = false;
        static constexpr bool PPOLYTOPESUPPORTFUNCTION_VERBOSE = false;
        static constexpr bool PPOLYTOPESUPPORTFUNCTION_VERIFY = true;
    };

// PolytopeSupportFunctions
    struct PolytopeSupportFunctionSetting : SupportFunctionSetting {
        static constexpr int type_enum = supportFunctionSetting_name::PolytopeSupportFunctionSetting;
        static constexpr bool PPOLYTOPESUPPORTFUNCTION_VERBOSE = false;
        static constexpr bool PPOLYTOPESUPPORTFUNCTION_VERIFY = true;
    };

}  // namespace hypro
