/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../../util/adaptions_eigen/adaptions_eigen.h"
#include "../../../util/logging/Logger.h"
#include "../Quickhull.h"

namespace hypro {

    template<typename Number, bool Euclidian>
    class ExactQuickhull<Number, Euclidian>::FacetSpace {
        pointVector_t &points;
        dimension_t dimension;
        matrix_t<Number> normalComputationMatrix; //< matrix pre-allocated to reduce running time

    public:
        size_t firstInserted;
        size_t firstDeleted = 0;
        std::vector<facet_ind_t> deletedPositions{};

        facetVector_t facets{};

        explicit FacetSpace(pointVector_t &points, dimension_t dimension)
                : points(points), dimension(dimension),
                  normalComputationMatrix(matrix_t<Number>(dimension, dimension + 1)) {};

        // facet construction
        Facet &insertNew();

        /**
         * Inserts a one dimensional facet that represents an interval bound at the given scalar.
         * @param scalar The interval bound.
         */
        void insertTrivialFacet(Number const scalar);

        /**
         * Inserts a new facet in the given dimension, from a lower dimensional facet, by setting 'reducedDimension' to 0.
         * @param other The facet to construct the new one from.
         * @param newDimension The dimension of the new facet.
         * @param reducedDimension The dimension to set to 0 in the new facet.
         */
        void insertReduced(Facet const &other, dimension_t newDimension, dimension_t reducedDimension);

        /**
         * Inserts a new facet that is defined by an existing one, except that the visiblePoint replaces the point at the specified index.
         * @param other The existing facet to construct a new one from.
         * @param visiblePoint The point to insert.
         * @param insertAt The index to insert the visiblePoint at.
         * @param containedPoint A point to use for orientation.
         * @return The index where the visiblePoint was inserted.
         */
        size_t insertConePart(facet_ind_t other_i, point_ind_t visiblePoint, size_t replaceAt);

        // facet modification
        void computeNormal(Facet &facet);

        void validateFacet(Facet &facet, point_t const &containedPoint, Facet const &adjacentFacet);

        void validateVertexContainment(Facet &facet);

        bool tryAddToOutsideSet(Facet &facet, point_ind_t point_i);

        void establishNeighborhood(facet_ind_t facet_i, facet_ind_t other_i);

        // facet queries

        // vector operations
        template<typename UnaryPredicate>
        facet_ind_t findFacet(UnaryPredicate predicate);

        void removeCoplanarFacets();

        void compressVector();

        void endModificationPhase();

        void markForDeletion(facet_ind_t facet_i);

        // Debug functions

        std::string printAll();

        std::string printFacet(Facet const &facet);

        void containsVertices(Facet &facet);

        void containsVertices(Facet &facet, Facet &currentFacet, bitset_t &visited);

        void containsAllPoints(Facet &facet, bool inverted = false);

    private:
        size_t copyVertices(Facet &facet, Facet const &other, point_ind_t visiblePoint, size_t replaceAt);
    };

#ifdef HYPRO_EXTERNALIZE_CLASSES

    extern template
    class ExactQuickhull<mpq_class, true>::FacetSpace;

    extern template
    class ExactQuickhull<mpq_class, false>::FacetSpace;

#endif
}  // namespace hypro

#include "FacetSpace.tpp"
