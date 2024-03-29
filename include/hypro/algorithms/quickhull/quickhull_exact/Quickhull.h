/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../../datastructures/Halfspace.h"
#include "../../../util/typetraits.h"

#include <boost/dynamic_bitset.hpp>
#include <hypro/util/adaptions_carl/adaptions_includes.h>
#include <vector>

namespace hypro {

/**
 * @brief Typedef for an implementation of the quickhull algorithm using exact arithmetic
 *
 * @tparam Number
 * @tparam Euclidian
 */
    template<typename Number, bool Euclidian>
    using ExactQuickhull = QuickhullAlgorithm<Number, Euclidian, EnableIfExact<Number>>;

/**
 * Represents an exact quickhull computation on a set of input vertices.
 * @tparam Number The Number type to be used.
 */
    template<typename Number, bool Euclidian>
    class QuickhullAlgorithm<Number, Euclidian, EnableIfExact<Number>> {
    public:
        // Nested classes
        struct Facet;

        class FacetSpace;

        // Type definitions
        using point_t = vector_t<Number>;
        using pointVector_t = std::vector<point_t>;
        using facetVector_t = std::vector<Facet>;
        using bitset_t = boost::dynamic_bitset<>;

        using qhvector_t = vector_t<Number>;
        using dimension_t = size_t;
        using point_ind_t = size_t;
        using facet_ind_t = size_t;

    private:
        // Inputs
        pointVector_t &points;      ///< Input set of points
        dimension_t dimension{};  ///< State space dimension

        // Members
        FacetSpace fSpace;    ///< TODO

    public:
        /// constructor
        QuickhullAlgorithm(pointVector_t &inputVertices, dimension_t dim);

        /**
         * @brief Main function which triggers the algorithm
         *
         */
        void compute();

        /**
         * @brief Get the Facets object
         *
         * @return facetVector_t&
         */
        facetVector_t &getFacets();

    private:
        void removeDuplicateInputs();

        void makeTrivialHull();

        void buildInitialPolytope();

        /**
         * @short constructs a facet from the first [1, ..., dim] points.
         * @return True iff a lower dimensional convex hull was constructed.
         **/
        bool constructInitialFacet();

        std::tuple<bool, point_ind_t> findFurthestPoint(Facet &facet);

        void findConeNeighbors(facet_ind_t facet_i);

        void partitionAllVertices();

        void initialPartition();

        facet_ind_t getFacetToProcess();

        void buildCone(facet_ind_t currentFacet_i, point_ind_t visiblePoint_i, bitset_t &visited);

        void buildCone_recursive(facet_ind_t currentFacet_i, point_ind_t visiblePoint_i, bitset_t &visited);

        void processPoints();

        void constructLowerDimensional();

        dimension_t pointSize();
    };
}  // namespace hypro

#include "Facet.h"
#include "FacetSpace.h"
#include "Quickhull.tpp"
