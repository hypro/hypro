//
// Created by leander.behr on 11/11/19.
//

#include "Facet.h"

namespace hypro {
    //modifiers
    template<typename Number, bool Euclidian>
    void ExactQuickhull<Number, Euclidian>::Facet::invert() {
        mNormal *= -1;
        mOffset *= -1;
    }

    template<typename Number, bool Euclidian>
    void ExactQuickhull<Number, Euclidian>::Facet::setOrientation(point_t const& containedPoint) {
        //Set orientation of normal
        if(visible(containedPoint)) {
            invert();
        }
    }

    //queries
    template<typename Number, bool Euclidian>
    Number ExactQuickhull<Number, Euclidian>::Facet::distance(point_t const& point) const {
        
        if constexpr(Euclidian) { 
            return point.dot(mNormal) - mOffset;
        } else {
            if(point[point.rows() - 1] == 0) {
                return point.head(point.rows() - 1).dot(mNormal) - mOffset;
            } else {
                return point.head(point.rows() - 1).dot(mNormal) / point[point.rows() - 1] - mOffset;
            }
        }
    }

    template<typename Number, bool Euclidian>
    bool ExactQuickhull<Number, Euclidian>::Facet::visible(point_t const& vertex) const {
        return distance(vertex) > Number(0);
    }

    template<typename Number, bool Euclidian>
    size_t ExactQuickhull<Number, Euclidian>::Facet::findNeighborIndex(facet_ind_t facet_i) {
        for(size_t neighbor_pos = 0; neighbor_pos < mNeighbors.size(); ++neighbor_pos) {
            if(mNeighbors[neighbor_pos] == facet_i) return neighbor_pos;
        }
        assert(false);
    }

}
