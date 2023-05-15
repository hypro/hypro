/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * @file GeometricObjectBase.h
 * \defgroup geoState State set representations
 * Most state set representations conform to a unified interface, which is defined in GeometricObjectBase.h.
 * Furthermore some of the representations have additional functionality, which is documented separately.
 */

#pragma once

#define INCL_FROM_GOHEADER true

#include "../config.h"
#include "types.h"

#include <hypro/flags.h>

#ifdef HYPRO_STATISTICS
#include "../util/statistics/statistics.h"
#endif
#ifdef HYPRO_USE_OPENMP
#include <omp.h>
#endif

namespace hypro {

    template<typename Number>
    class Point;

    template<typename Number>
    class Halfspace;

    template<typename Number>
    class Location;

/**
 * @brief      Purely virtual class defining a common interface for geometric objects.
 * \ingroup geoState @{
 */

    class GeometricObjectBase {
    protected:
        mutable SETSTATE mEmptyState = SETSTATE::UNKNOWN;

        GeometricObjectBase() = default;

        GeometricObjectBase(const GeometricObjectBase &in) = default;

        GeometricObjectBase(GeometricObjectBase &&in) = default;

        GeometricObjectBase &operator=(const GeometricObjectBase &in) = default;

        GeometricObjectBase &operator=(GeometricObjectBase &&in) = default;

        GeometricObjectBase(SETSTATE state)
                : mEmptyState(state) {}

        /**
         * @brief      Determines, whether the set is empty.
         * @return     True, if the set is empty, false otherwise.
         */
        SETSTATE getEmptyState() const { return mEmptyState; }

        /**
         * @brief Set the Empty State member - only to be used if you know what you are doing.
         * @param state The state the member is set to.
         */
        void setEmptyState(SETSTATE state) { mEmptyState = state; }

        template<class Archive>
        [[maybe_unused]] void serialize(Archive &ar) {
            ar(mEmptyState);
        }
    };

/** @} */

}  // namespace hypro

#include "conversion/Converter.h"
