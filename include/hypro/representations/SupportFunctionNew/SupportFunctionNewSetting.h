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

    BETTER_ENUM(sfnSetting_name, int,
                SupportFunctionNewDefault,
                SupportFunctionNewMorePrecision,
                SupportFunctionNewNoReduction,
                SupportFunctionNewLeGuernic)

// This is the default setting, which is the fastest setting, but not as precise
    struct SupportFunctionNewDefault {
        static constexpr int type_enum = sfnSetting_name::SupportFunctionNewDefault;
        // Whether multiple linear transformations in succession should be condensed into one linear transformation
        // Generally makes flowpipe construction faster without loss of precision
        static constexpr bool LIN_TRANS_REDUCTION = true;
        // If LIN_TRANS_REDUCTION is true, this determines how many linear transformations are condensed.
        // 2^LIN_TRANS_REDUCTION_GROUP_SIZE many linear transformations are condensed.
        static constexpr unsigned LIN_TRANS_REDUCTION_GROUP_SIZE = 2;
        // Whether after a jump, the new segment should be overapproximated by a box (if not active, it will be overapproximated by an octagon)
        // Overapproximating by a box greatly reduces runtime, but also loses precision, overapproximating by an hpoly is more precise, but slower.
        static constexpr bool APPROXIMATE_AS_BOX = true;
        // If activated, every SupportFunctionNew that is constructed through the generic-leaf-/matrix-vector-ctor (so only the leaves) is checked upon creation
        // whether it represents a box and converts it to one if this is the case.
        // Greatly reduces runtime if this is the case.
        static constexpr bool DETECT_BOX = true;
        // Whether the intersection between support functions and halfspaces should be computed after Le Guernic's method.
        // Reduces runtime for high dimensional problems wtih halfspace guards, else increases it.
        // Theoretically it introduces loss of precision, but practically there is no visible difference.
        static constexpr bool LE_GUERNIC_HSPACE_INTERSECTION = false;
    };

// The setting if more precision is needed, but runtime will be greater
    struct SupportFunctionNewMorePrecision {
        static constexpr int type_enum = sfnSetting_name::SupportFunctionNewMorePrecision;
        static constexpr bool LIN_TRANS_REDUCTION = true;
        static constexpr unsigned LIN_TRANS_REDUCTION_GROUP_SIZE = 2;
        static constexpr bool APPROXIMATE_AS_BOX = false;
        static constexpr bool DETECT_BOX = true;
        static constexpr bool LE_GUERNIC_HSPACE_INTERSECTION = false;
    };

// Inefficient setting for experimental purposes
    struct SupportFunctionNewNoReduction {
        static constexpr int type_enum = sfnSetting_name::SupportFunctionNewNoReduction;
        static constexpr bool LIN_TRANS_REDUCTION = false;
        static constexpr unsigned LIN_TRANS_REDUCTION_GROUP_SIZE = 1;
        static constexpr bool APPROXIMATE_AS_BOX = false;
        static constexpr bool DETECT_BOX = false;
        static constexpr bool LE_GUERNIC_HSPACE_INTERSECTION = false;
    };

// Setting which is better for high dimensional tasks
    struct SupportFunctionNewLeGuernic {
        static constexpr int type_enum = sfnSetting_name::SupportFunctionNewLeGuernic;
        static constexpr bool LIN_TRANS_REDUCTION = true;
        static constexpr unsigned LIN_TRANS_REDUCTION_GROUP_SIZE = 2;
        static constexpr bool APPROXIMATE_AS_BOX = true;
        static constexpr bool DETECT_BOX = true;
        static constexpr bool LE_GUERNIC_HSPACE_INTERSECTION = true;
    };
}  // namespace hypro
