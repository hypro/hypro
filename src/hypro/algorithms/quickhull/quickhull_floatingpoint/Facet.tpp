//
// Created by leander.behr on 11/11/19.
//

#include "Facet.h"

namespace hypro {
    //modifiers
    template<typename Number>
    void FloatQuickhull<Number>::Facet::invert() {
        mNormal *= -1;
        mOuterOffset *= -1;
    }

    template<typename Number>
    void FloatQuickhull<Number>::Facet::setOrientation(vector_t<mpq_class> const& containedPoint) {
        //Set orientation of normal
        if(containedPoint.dot(mNormal.template cast<mpq_class>()) - mOuterOffset > 0) {
            invert();
        }
    }

    //queries
    template<typename Number>
    Number FloatQuickhull<Number>::Facet::distance(point_t const& point) const {
        return distanceOuter(point);
    }

    template<typename Number>
    bool FloatQuickhull<Number>::Facet::visible(point_t const& point) const {
        return visibleOuter(point);
    }

    template<typename Number>
    Number FloatQuickhull<Number>::Facet::distanceOuter(point_t const& point) const {
        ScopedRoundingMode round{FE_UPWARD};
        return point.dot(mNormal) - mOuterOffset;
    }

    template<typename Number>
    bool FloatQuickhull<Number>::Facet::visibleOuter(point_t const& point) const {
        return distanceOuter(point) > Number(0);
    }

    template<typename Number>
    Number FloatQuickhull<Number>::Facet::distanceInner(point_t const& point) const {
        ScopedRoundingMode round{FE_UPWARD};
        return point.dot(mNormal) - mInnerOffset;
    }

    template<typename Number>
    bool FloatQuickhull<Number>::Facet::visibleInner(point_t const& point) const {
        return distanceInner(point) > Number(0);
    }

    template<typename Number>
    size_t FloatQuickhull<Number>::Facet::findNeighborIndex(facet_ind_t facet_i) {
        for(size_t neighbor_pos = 0; neighbor_pos < mNeighbors.size(); ++neighbor_pos) {
            if(mNeighbors[neighbor_pos] == facet_i) return neighbor_pos;
        }
        assert(false);
    }

}
