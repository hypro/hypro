#pragma once

#include <vector>
#include <algorithm>
#include <boost/dynamic_bitset.hpp>
#include "datastructures/Halfspace.h"
#include "carl/numbers/numbers.h"
#include "../number_traits.h"

namespace hypro {
    /**
     * Represents an exact quickhull computation on a set of input vertices.
     * @tparam Number The Number type to be used.
     */
    template<typename Number, bool Euclidian>
    class Quickhull<Number, Euclidian, EnableIfFloatingpoint<Number>> {
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
        //Inputs
        pointVector_t& points;
        std::vector<point_ind_t> currentVertices;
        dimension_t dimension{};

        //Members
        FacetSpace fSpace;

    public:
        Quickhull(pointVector_t& inputVertices, size_t dim);
        void compute();

        facetVector_t& getFacets();

    private:
        void removeDuplicateInputs();

        void makeTrivialHull();

        void buildInitialPolytope();

        /**
         * @short constructs a facet from the first [1, ..., dim] points.
         * @return True iff a lower dimensional convex hull was constructed.
         **/
        bool constructInitialFacet();

        std::tuple<bool, point_ind_t> findFurthestPoint(Facet& facet);

        void findConeNeighbors(facet_ind_t facet_i);

        void partitionAllVertices(point_ind_t newVertex_i);

        void initialPartition();

        facet_ind_t getFacetToProcess();

        void buildCone(facet_ind_t currentFacet_i, point_ind_t visiblePoint_i, bitset_t& visited);

        void processPoints();

        void constructLowerDimensional();

        dimension_t pointSize();
    };
}

#include "Facet.h"
#include "FacetSpace.h"

#include "Quickhull.tpp"