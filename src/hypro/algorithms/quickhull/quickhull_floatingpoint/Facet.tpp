//
// Created by leander.behr on 11/11/19.
//

#include "Facet.h"

namespace hypro {
    //modifiers
    template<typename Number, bool Euclidian>
    void FloatQuickhull<Number, Euclidian>::Facet::invert() {
        mNormal *= -1;
        mOuterOffset *= -1;
        mInnerOffset *= -1;
        std::swap(mInnerOffset, mOuterOffset);
    }

    template<typename Number, bool Euclidian>
    void FloatQuickhull<Number, Euclidian>::Facet::normalizeOffset() {

        for(int i = 0; i < mNormal.cols(); ++i) {
            int roundingMode = mNormal[i] < 0 ? FE_DOWNWARD : FE_UPWARD;
            ScopedRoundingMode rounding{roundingMode};
            mNormal[i] /= mInnerOffset;
        }

    }

    //queries
    template<typename Number, bool Euclidian>
    template<int RoundingMode>
    Number FloatQuickhull<Number, Euclidian>::Facet::outerDistance(point_t const& point) const {
        return distance<RoundingMode>(point, mOuterOffset);
    }

    template<typename Number, bool Euclidian>
    template<int RoundingMode>
    Number FloatQuickhull<Number, Euclidian>::Facet::innerDistance(point_t const& point) const {
        return distance<RoundingMode>(point, mInnerOffset);
    }
    
    template<typename Number, bool Euclidian>
    template<int RoundingMode>
    Number FloatQuickhull<Number, Euclidian>::Facet::distance(point_t const& point, Number offset) const {
        ScopedRoundingMode rounding{RoundingMode};

        if constexpr(Euclidian) { 
            return point.dot(mNormal) - offset;
        } else {
            Number dotProd = point.head(point.rows() - 1).dot(mNormal) + point[point.rows() - 1] * -offset;
            return dotProd;
        }
    }

    template<typename Number, bool Euclidian>
    bool FloatQuickhull<Number, Euclidian>::Facet::outerVisible(point_t const& vertex) const {
        return outerDistance(vertex) > Number(0);
    }

    template<typename Number, bool Euclidian>
    bool FloatQuickhull<Number, Euclidian>::Facet::innerVisible(point_t const& vertex) const {
        return innerDistance(vertex) > Number(0);
    }

    template<typename Number, bool Euclidian>
    size_t FloatQuickhull<Number, Euclidian>::Facet::findNeighborIndex(facet_ind_t facet_i) {
        for(size_t neighbor_pos = 0; neighbor_pos < mNeighbors.size(); ++neighbor_pos) {
            if(mNeighbors[neighbor_pos] == facet_i) return neighbor_pos;
        }
        assert(false);
    }

    //compatibility overloads
    template<typename Number, bool Euclidian>
    template<int RoundingMode>
    Number FloatQuickhull<Number, Euclidian>::Facet::distance(point_t const& point) const {
        return outerDistance<RoundingMode>(point);
    }

    template<typename Number, bool Euclidian>
    bool FloatQuickhull<Number, Euclidian>::Facet::visible(point_t const& vertex) const {
        return outerVisible(vertex);
    }

    template<typename Number, bool Euclidian>
    Number FloatQuickhull<Number, Euclidian>::Facet::offset() const {
        return mOuterOffset;
    }

}