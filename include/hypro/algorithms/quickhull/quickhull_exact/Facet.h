/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../../util/unreachable.h"

namespace hypro {
/**
 * @brief Struct representing a facet in Euclidean space.
 * @tparam Number
 * @tparam Euclidian
 */
    template<typename Number, bool Euclidian>
    struct ExactQuickhull<Number, Euclidian>::Facet {
        Facet() = default;

        //modifiers
        /// Inverts the facet
        void invert();

        /// Sets normal vector orientation and normal vector?
        void setOrientation(point_t const &containedPoint, Facet const &adjacentFacet);

        //queries
        /// Returns signed distance from point to hyperplane
        Number distance(point_t const &point) const;

        /// True if the passed point is above the facet (outside)
        bool visible(point_t const &vertex) const;

        /// Returns index in the neighbor set of the passed facet
        size_t findNeighborIndex(facet_ind_t facet_i);

        // members
        std::vector<point_ind_t> mVertices;             ///< Vertex cache
        std::vector<facet_ind_t> mNeighbors;         ///< Neighbor cache
        std::vector<point_ind_t> mOutsideSet;         ///< Outside vertices cache
        point_t mNormal;                             ///< Normal vector
        point_ind_t furthestPoint;                     ///< ???
        Number furthestPointDistance = Number(0);     ///< ???
        Number mOffset = Number(1000);             ///< Offset
    };

    template<typename Number, bool Euclidian>
    inline std::ostream &operator<<(std::ostream &out, const typename ExactQuickhull<Number, Euclidian>::Facet &in) {
        out << in.mNormal << " <= " << in.mOffset;
        return out;
    }

}  // namespace hypro

#include "Facet.tpp"
