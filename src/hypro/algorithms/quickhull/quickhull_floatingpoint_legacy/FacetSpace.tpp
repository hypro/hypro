//
// Created by leander.behr on 11/11/19.
//

#include "FacetSpace.h"
#include "../ScopedRoundingMode.h"

namespace hypro {

    //facet construction
    template<typename Number>
    void FloatQuickhull<Number>::FacetSpace::insertNew() {
        facets.emplace_back();

        facets.back().mVertices = std::vector<point_ind_t>(dimension);
        facets.back().mNeighbors = std::vector<facet_ind_t>(dimension);
        facets.back().mOutsideSet = std::vector<point_ind_t>();
        facets.back().mNormal = point_t(dimension);
    }

    template<typename Number>
    void FloatQuickhull<Number>::FacetSpace::insertTrivialFacet(const Number scalar) {
        facets.emplace_back();
        facets.back().mOuterOffset = scalar;
        facets.back().mNormal = point_t(1);
        facets.back().mNormal[0] = 1;
    }

    template<typename Number>
    void FloatQuickhull<Number>::FacetSpace::insertReduced(Facet const& other, dimension_t newDimension, dimension_t reducedDimension) {
        Facet& facet = facets.emplace_back();
        facet.mOuterOffset = other.mOuterOffset;
        facet.mNormal = qhvector_t(newDimension);

        for(size_t i = 0, j = 0; i < newDimension; ++i, ++j) {
            if (i == reducedDimension) {
                facet.mNormal[i] = 0;
                j -= 1;
                continue;
            }
            facet.mNormal[i] = other.mNormal[j];
        }
    }

    template<typename Number>
    size_t FloatQuickhull<Number>::FacetSpace::copyVertices(Facet& facet, Facet const& other, point_ind_t visiblePoint, size_t replaceAt) {
        //Doing some work here to keep the vertices sorted
        bool inserted = false;
        size_t insertedPosition = dimension - 1;
        size_t thisInd = 0, otherInd = 0;

        while(true) {
            otherInd += (otherInd == replaceAt);

            if(!(thisInd < dimension && otherInd < dimension)) break;

            bool insertHere = !inserted && other.mVertices[otherInd] >= visiblePoint;

            facet.mVertices[thisInd] = insertHere ? visiblePoint : other.mVertices[otherInd];

            inserted |= insertHere;

            if(insertHere) insertedPosition = thisInd;
            else otherInd += 1;

            thisInd += 1;
        }

        if(!inserted) facet.mVertices[dimension - 1] = visiblePoint;

        return insertedPosition;
    }

    template<typename Number>
    size_t FloatQuickhull<Number>::FacetSpace::insertConePart(facet_ind_t other_i, point_ind_t visiblePoint, size_t replaceAt, hypro::vector_t<mpq_class> const& containedPoint) {
        insertNew();
        size_t insertedAt = copyVertices(facets.back(), facets[other_i], visiblePoint, replaceAt);
        computeNormal(facets.back());
        validateFacet(facets.back(), containedPoint);
        return insertedAt;
    }

    //facet modification
    template<typename Number>
    void FloatQuickhull<Number>::FacetSpace::computeNormal(Facet& facet) {
        ///TODO Allocate space for matrix once and reuse it
        ///TODO Could also use __restrict__ to get memcpy here (probably).
        matrix_t<Number> matrix(dimension, dimension + 1);
        for(size_t i = 0; i < dimension; ++i) {
            for(size_t j = 0; j < dimension; ++j) {
                matrix.row(i)[j] = (points[facet.mVertices[i]])[j];
            }
            matrix.row(i)[dimension] = 1;
        }

        TRACE("quickhull", "matrix" <<  std::endl << matrix);

        point_t result =  matrix.fullPivLu().kernel().col(0);
        
        TRACE("quickhull", "result" << std::endl << result);
        
        for(size_t i = 0; i < dimension; ++i) {
            facet.mNormal[i] = result[i];
        }
        facet.mOuterOffset = -result[dimension];
        facet.mInnerOffset = -result[dimension];
    }

    template<typename Number>
    void FloatQuickhull<Number>::FacetSpace::validateFacet(Facet& facet, hypro::vector_t<mpq_class> const& containedPoint) {
        facet.setOrientation(containedPoint);
        validateVertexContainment(facet);
    }

    template<typename Number>
    void FloatQuickhull<Number>::FacetSpace::validateVertexContainment(Facet& facet) {
        {
            ScopedRoundingMode round{FE_UPWARD};

            for(point_ind_t point_i : facet.mVertices) {
                Number distance = points[point_i].dot(facet.mNormal);

                if(distance > facet.mOuterOffset) {
                    facet.mOuterOffset = distance;
                }
                assert(distance - facet.mOuterOffset <= 0);
            }
        }
        {
            ScopedRoundingMode round{FE_DOWNWARD};
            for(point_ind_t point_i : facet.mVertices) {
                Number distance = points[point_i].dot(facet.mNormal);

                if(distance < facet.mInnerOffset) {
                    facet.mInnerOffset = distance;
                }
                assert(distance - facet.mInnerOffset >= 0);
            }
        }

        TRACE("quickhull", "New Facet is:");
        TRACE("quickhull", printFacet(facet));
#ifndef NDEBUG
        containsVertices(facet);        
#endif
    }

    template<typename Number>
    bool FloatQuickhull<Number>::FacetSpace::tryAddToOutsideSet(Facet& facet, point_ind_t point_i) {
        Number distance = facet.distance(points[point_i]);

        if(distance > Number(0)) {
            facet.mOutsideSet.push_back(point_i);

            if(distance > facet.furthestPointDistance) {
                facet.furthestPointDistance = distance;
                facet.furthestPoint = point_i;
            }
            return true;
        }
        return false;
    }

    template<typename Number>
    void FloatQuickhull<Number>::FacetSpace::establishNeighborhood(facet_ind_t facet_i, facet_ind_t other_i) {
        Facet& facet = facets[facet_i];
        Facet& other = facets[other_i];

        size_t thisNeighborPosition = dimension - 1;
        size_t otherNeighborPosition = dimension - 1;

        size_t thisInd = 0;
        size_t otherInd = 0;

        bool hammingNonZero = false;

        while(true) {
            if(facet.mVertices[thisInd] < other.mVertices[otherInd]) {
                if(hammingNonZero) return;
                hammingNonZero = true;
                thisNeighborPosition = thisInd;
                thisInd += 1;
            } else if(facet.mVertices[thisInd] > other.mVertices[otherInd]) {
                otherNeighborPosition = otherInd;
                otherInd += 1;
            } else {
                thisInd += 1;
                otherInd += 1;
            }

            if(thisInd == dimension) break;

            if(otherInd == dimension) {
                if(thisInd + 1 - hammingNonZero < otherInd) return;
                else break;
            }
        }

        facet.mNeighbors[thisNeighborPosition] = other_i;
        other.mNeighbors[otherNeighborPosition] = facet_i;
    }

    //facet queries
    template<typename Number>
    bool FloatQuickhull<Number>::FacetSpace::isParallel(Facet const& facet, Facet const& other) {
        if(dimension == 1) return false;

        std::unique_ptr<std::pair<Number, Number>[]> minMax(new std::pair<Number, Number>[dimension]);

        {
            ScopedRoundingMode roundingMode{FE_DOWNWARD};
            for(size_t i = 0; i < dimension; ++i) {
                minMax[i].first = facet.mNormal[i]/other.mNormal[i];
            }
        }

        {
            ScopedRoundingMode roundingMode{FE_UPWARD};
            for(size_t i = 0; i < dimension; ++i) {
                minMax[i].second = facet.mNormal[i]/other.mNormal[i];
            }
        }

        for(size_t i = 0; i < dimension; ++i) {
            for(size_t j = i + 1; j < dimension; ++j) {
                if(minMax[i].first > minMax[j].second || minMax[i].second < minMax[j].first){
                    return false;
                }
            }
        }

        return true;
    }

    //vector operations
    template<typename Number>
    template<typename UnaryPredicate>
    typename FloatQuickhull<Number>::facet_ind_t FloatQuickhull<Number>::FacetSpace::findFacet(UnaryPredicate predicate) {
        return std::distance(facets.begin(), std::find_if(facets.begin(), facets.end(), predicate));
    }

    template<typename Number>
    void FloatQuickhull<Number>::FacetSpace::compressVector() {
        size_t newSize = facets.size() - deletedPositions.size();

        assert(newSize > 0);

        size_t freePosInd = deletedPositions.size() - 1;

        while(facets.size() > newSize) {
            size_t freePos = deletedPositions[freePosInd];

            if(freePos == facets.size() - 1) continue;
            facets[freePos] = std::move(facets.back());
            facets.pop_back();

            freePosInd -= 1;
        }

        deletedPositions.clear();
    }

    template<typename Number>
    void FloatQuickhull<Number>::FacetSpace::endModificationPhase() {
        firstInserted = facets.size();
        firstDeleted = deletedPositions.size();
    }

    template<typename Number>
    void FloatQuickhull<Number>::FacetSpace::deleteFacet(facet_ind_t facet_i) {
        deletedPositions.push_back(facet_i);
    }

#ifndef NDEBUG
        template<typename Number>
        std::string FloatQuickhull<Number>::FacetSpace::printAll() {
            std::stringstream out;
            for(auto& facet : facets) {
                out << printFacet(facet);
            }
            return out.str();
        }

        template<typename Number>
        std::string FloatQuickhull<Number>::FacetSpace::printFacet(Facet const& facet) {
            std::stringstream out;

            char var = 'y';

            out << "(" << facet.mNormal[0] << ")x";
            for(size_t i = 1; i < dimension; ++i) {
                out << " + (" << facet.mNormal[i] << ")" << var;
                var += 1;
            }

            out << " = " << facet.mOuterOffset << std::endl;

            return out.str();
        }

        template<typename Number>
        void FloatQuickhull<Number>::FacetSpace::containsVertices(Facet& facet) {
            bitset_t visited(facets.size());
            containsVertices(facet, facet, visited);
        }

        template<typename Number>
        void FloatQuickhull<Number>::FacetSpace::containsVertices(Facet& facet, Facet& currentFacet, bitset_t& visited) {
            for(point_ind_t point_i : currentFacet.mVertices) {
                if(facet.visible(points[point_i])) {
                    TRACE("quickhull", "NON CONTAINMENT" << std::endl << points[point_i] << std::endl << "Facet:" << std::endl << printFacet(facet));
                    TRACE("quickhull", "point_i " << point_i);
                    //assert(false);
                }
            }

            for(facet_ind_t neighbor_i : facet.mNeighbors) {
                if(!visited[neighbor_i]) {
                    visited.set(neighbor_i);
                    containsVertices(facet, facets[neighbor_i], visited);
                }
            }
        }
#endif
}