#pragma once

#include <vector>
#include <boost/dynamic_bitset.hpp>
#include "datastructures/Halfspace.h"
#include "carl/numbers/numbers.h"

namespace hypro {

    template<typename Number>
    inline constexpr bool is_exact = std::is_same_v<Number, mpq_class>;

    /**
     * Represents an exact quickhull computation on a set of input vertices.
     * @tparam Number The Number type to be used.
     */
    template<typename Number>
    class Quickhull {
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
        pointVector_t& inputPoints;
        dimension_t dimension{};

        //Members
        FacetSpace fSpace;
        point_t baryCenter;

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

        std::tuple<Number, point_ind_t> findFurthestPoint(Facet& facet);

        void findConeNeighbors(facet_ind_t facet_i);

        void partitionAllVertices();

        void initialPartition();

        facet_ind_t getFacetToProcess();

        void buildCone(facet_ind_t currentFacet_i, point_ind_t visiblePoint_i, bitset_t& visited);

        void processPoints();

        void constructLowerDimensional();
    };
}

#include "Facet.h"
#include "FacetSpace.h"

#include "Quickhull.tpp"