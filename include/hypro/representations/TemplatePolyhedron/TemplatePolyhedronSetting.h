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

    BETTER_ENUM(tpolySetting_name, int,
                TemplatePolyhedronDefault, OctagonShape)

// Defines what which constraints are added to the template matrix.
// Generally, if more contraints are added, then runtime will be slower.
// If location invariants or guards are often just halfspaces, it makes sense to add them since this would make computations easier.
    enum TEMPLATE_CONTENT {
        ONLY_INIT = 0,         // Only initial constraints will be added
        INIT_INV,             // Initial constraints + location invariants
        INIT_INV_GUARD,         // Initial constraints + location invariants + guards
        INIT_INV_GUARD_BAD,     // Initial constraints + location invariants + guards + bad states
        OCTAGON                 // Octagonal set
    };

// This is the default setting
    struct TemplatePolyhedronDefault {
        static constexpr int type_enum = tpolySetting_name::TemplatePolyhedronDefault;

        // Determines which constraints should be added to the template matrix.
        static constexpr TEMPLATE_CONTENT TEMPLATE_SHAPE = TEMPLATE_CONTENT::INIT_INV_GUARD_BAD;

        // Whether the specialized reachability algorithm from Sankaranarayanan 2008 should be used .
        static constexpr bool USE_ALTERNATIVE_REACH_ALGO = false;

        /* Setting that are only relevant if USE_ALTERNATIVE_REACH_ALGO = true */

        // If the alternative reachability algorithm is used, this determines the order to which a Taylor series approximation is computed.
        static constexpr unsigned DERIVATIVE_ORDER = 6;
        static_assert(DERIVATIVE_ORDER >= 1, "Template Polyhedron DERIVATIVE_ORDER must be greater equal 1.");

        // If the alternative reachability algorithm is used, say whether location invariant strengthening should also be used
        static constexpr bool USE_LOCATION_INVARIANT_STRENGTHENING = true;

        // Activate numerical corrections during location invariant strengthening.
        static constexpr bool USE_NUMERICAL_CORRECTIONS = false;

        // Value that is used to bound unbounded invariants initially (are shrinked through location invariant strengthening)
        static constexpr double BOUNDING_VALUE = 10000;

        // NOTE: DON'T USE MONOTONICITY CHECKS ITS NOT SOUND (to don't use them DIRECTLY_COMPUTE_ROOTS should be true)
        // If the alternative reachability algorithm is used, a monotonicity check is conducted before the expensive root enumeration, if this option is false.
        static constexpr bool DIRECTLY_COMPUTE_ROOTS = true;

        // NOTE: DON'T USE MONOTONICITY CHECKS ITS NOT SOUND (to don't use them DIRECTLY_COMPUTE_ROOTS should be true)
        // If the alternative reachability algorithm is used and roots are not directly computed, then the granularity defines the precision of the monotonicity check
        static constexpr unsigned int MONOTONICITY_GRANULARITY = 4;
        static_assert(MONOTONICITY_GRANULARITY >= 1,
                      "Template Polyhedron MONOTONICITY_GRANULARITY must be greater equal 1.");
    };

    struct OctagonShape : TemplatePolyhedronDefault {
        static constexpr int type_enum = tpolySetting_name::OctagonShape;
        static constexpr TEMPLATE_CONTENT TEMPLATE_SHAPE = TEMPLATE_CONTENT::OCTAGON;
        static constexpr bool USE_ALTERNATIVE_REACH_ALGO = false;
    };

}  // namespace hypro
