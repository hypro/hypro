#pragma once

#include <limits>
#include "../ScopedRoundingMode.h"

namespace hypro {
    template<typename Number, bool Euclidian>
    struct FloatQuickhull<Number, Euclidian>::Facet {
        Facet() = default;

        //modifiers
        void invert();
        void normalizeOffset();

        //queries
        template<int RoundingMode = FE_UPWARD>
        Number distance(point_t const& point, Number offset) const;
        template<int RoundingMode = FE_UPWARD>
        Number innerDistance(point_t const& point) const;
        template<int RoundingMode = FE_UPWARD>
        Number outerDistance(point_t const& point) const;
        
        bool outerVisible(point_t const& vertex) const;
        bool innerVisible(point_t const& vertex) const;
        size_t findNeighborIndex(facet_ind_t facet_i);

        //compatibility overloads
        template<int RoundingMode = FE_UPWARD>
        Number distance(point_t const& point) const;
        bool visible(point_t const& vertex) const;
        Number offset() const;

        //members
        std::vector<point_ind_t> mVertices{};
        std::vector<facet_ind_t> mNeighbors;
        std::vector<point_ind_t> mOutsideSet;
        point_t mNormal;
        point_ind_t furthestPoint;
        Number furthestPointDistance = Number(0);
        Number mInnerOffset = std::numeric_limits<Number>::infinity();
        Number mOuterOffset = -std::numeric_limits<Number>::infinity();
    };
}

#include "Facet.tpp"