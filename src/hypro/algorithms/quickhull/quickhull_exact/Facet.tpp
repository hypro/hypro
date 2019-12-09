//
// Created by leander.behr on 11/11/19.
//

#include "Facet.h"

namespace hypro {
    //modifiers
    template<typename Number>
    void ExactQuickhull<Number>::Facet::invert() {
        mNormal *= -1;
        mOffset *= -1;
    }

    template<typename Number>
    void ExactQuickhull<Number>::Facet::setOrientation(point_t const& containedPoint) {
        //Set orientation of normal
        if(visible(containedPoint)) {
            invert();
        }
    }

    //queries
    template<typename Number>
    Number ExactQuickhull<Number>::Facet::distance(point_t const& point) const {
        return point.dot(mNormal) - mOffset;
    }

    template<typename Number>
    bool ExactQuickhull<Number>::Facet::visible(point_t const& vertex) const {
        return distance(vertex) > Number(0);
    }

    template<typename Number>
    size_t ExactQuickhull<Number>::Facet::findNeighborIndex(facet_ind_t facet_i) {
        for(size_t neighbor_pos = 0; neighbor_pos < mNeighbors.size(); ++neighbor_pos) {
            if(mNeighbors[neighbor_pos] == facet_i) return neighbor_pos;
        }
        assert(false);
    }

}
