//
// Created by leander.behr on 11/11/19.
//

#ifndef HYPRO_FACET_H
#define HYPRO_FACET_H

#include "Quickhull.h"

namespace hypro {
    template<typename Number>
    struct Quickhull<Number>::Facet {
        //modifiers
        void invert();
        void setOrientation(vector_t<mpq_class> const& containedPoint);

        //queries
        //aliases to the outer versions, as the outer facet is the 'real' facet for most purposes.
        Number distance(point_t const& point) const;
        bool visible(point_t const& point) const;
      
        Number distanceOuter(point_t const& point) const;
        Number distanceInner(point_t const& point) const;
        bool visibleOuter(point_t const& point) const;
        bool visibleInner(point_t const& point) const;
        size_t findNeighborIndex(facet_ind_t facet_i);

        std::vector<point_ind_t> mVertices;
        std::vector<facet_ind_t> mNeighbors;
        std::vector<point_ind_t> mOutsideSet;
        point_t mNormal;
        point_ind_t furthestPoint;
        Number furthestPointDistance = Number(0);
        Number mOuterOffset;
        Number mInnerOffset;
    };
}


#include "Facet.tpp"

#endif //HYPRO_FACET_H
