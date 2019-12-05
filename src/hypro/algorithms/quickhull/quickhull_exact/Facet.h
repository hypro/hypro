//
// Created by leander.behr on 11/11/19.
//

#ifndef HYPRO_FACET_H
#define HYPRO_FACET_H

#include "Quickhull.h"

namespace hypro {
    template<typename Number>
    struct Quickhull<Number>::Facet {
        Facet() = default;

        //modifiers
        void invert();
        void setOrientation(point_t const& containedPoint);

        //queries
        Number distance(point_t const& point) const;
        bool visible(point_t const& vertex) const;
        size_t findNeighborIndex(facet_ind_t facet_i);

        //members
        std::vector<point_ind_t> mVertices;
        std::vector<facet_ind_t> mNeighbors;
        std::vector<point_ind_t> mOutsideSet;
        point_t mNormal;
        point_ind_t furthestPoint;
        Number furthestPointDistance = Number(0);
        Number mOffset = Number(1000);
    };
}


#include "Facet.tpp"

#endif //HYPRO_FACET_H
