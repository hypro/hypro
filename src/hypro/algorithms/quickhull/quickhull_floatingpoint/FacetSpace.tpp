//
// Created by leander.behr on 11/11/19.
//

#include "FacetSpace.h"

namespace hypro {

    //facet construction
    template<typename Number, bool Euclidian>
    typename FloatQuickhull<Number, Euclidian>::Facet& FloatQuickhull<Number, Euclidian>::FacetSpace::insertNew() {
        facets.emplace_back();

        facets.back().mVertices = std::vector<point_ind_t>(dimension);
        facets.back().mNeighbors = std::vector<facet_ind_t>(dimension);
        facets.back().mOutsideSet = std::vector<point_ind_t>();
        facets.back().mNormal = point_t(dimension);

        return facets.back();
    }

    template<typename Number, bool Euclidian>
    void FloatQuickhull<Number, Euclidian>::FacetSpace::insertTrivialFacet(const Number scalar) {
        facets.emplace_back();
        facets.back().mOuterOffset = scalar;
        facets.back().mInnerOffset = scalar;
        facets.back().mNormal = point_t{1};
        facets.back().mNormal[0] = 1;
    }

    template<typename Number, bool Euclidian>
    void FloatQuickhull<Number, Euclidian>::FacetSpace::insertReduced(Facet const& other, dimension_t newDimension, dimension_t reducedDimension) {
        Facet& facet = facets.emplace_back();
        facet.mOuterOffset = other.mOuterOffset;
        facet.mInnerOffset = other.mInnerOffset;
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

    template<typename Number, bool Euclidian>
    size_t FloatQuickhull<Number, Euclidian>::FacetSpace::copyVertices(Facet& facet, Facet const& other, point_ind_t visiblePoint, size_t replaceAt) {
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

    template<typename Number, bool Euclidian>
    size_t FloatQuickhull<Number, Euclidian>::FacetSpace::insertConePart(facet_ind_t other_i, point_ind_t visiblePoint, size_t replaceAt) {
        insertNew();
        size_t insertedAt = copyVertices(facets.back(), facets[other_i], visiblePoint, replaceAt);
        computeNormal(facets.back());
        if(!validateFacet(facets.back())) {
            TRACE("quickhull", "facet " << facets.size()-1 << " copyof " << other_i);
            facets.back().mNormal = facets[other_i].mNormal;
            fixOffset(facets.back());
        }

        return insertedAt;
    }

    //facet modification
    template<typename Number, bool Euclidian>
    void FloatQuickhull<Number, Euclidian>::FacetSpace::computeNormal(Facet& facet) {
        ///TODO Allocate space for matrix once and reuse it
        ///TODO Could also use __restrict__ to get memcpy here (probably).
        matrix_t<Number> matrix(dimension, dimension + 1);
        
        if constexpr(Euclidian) {
            for(size_t i = 0; i < dimension; ++i) {
                matrix.row(i).head(dimension) = points[facet.mVertices[i]].transpose();
                matrix.row(i)[dimension] = 1;
            }
        } else {
            for(size_t i = 0; i < dimension; ++i) {
                matrix.row(i) = points[facet.mVertices[i]].transpose();
            }
        }

        matrix_t<double> m = convert<Number, double>(matrix);
        TRACE("quickhull", "matrix" <<  std::endl << m);
        
        Eigen::FullPivLU<matrix_t<Number>> lu(matrix);

        // assert(static_cast<size_t>(lu.rank()) == dimension);
        TRACE("quickhull", "matrix rank " << lu.rank());

        point_t result =  matrix.fullPivLu().kernel().col(0);
        
        vector_t<double> r = convert<Number, double>(result);
        TRACE("quickhull", "result" << std::endl << r);
        
        for(size_t i = 0; i < dimension; ++i) {
            facet.mNormal[i] = result[i];
        }
    }

    template<typename Number, bool Euclidian>
    bool FloatQuickhull<Number, Euclidian>::FacetSpace::validateFacet(Facet& facet) {
        fixOffset(facet);

        if(facets.size() == 26) {
            TRACE("quickhull", printAllDistances());
        }

        bool flipped = false;
        for(point_ind_t vertex_i : currentVertices) {
            if(std::find(facet.mVertices.begin(), facet.mVertices.end(), vertex_i) != facet.mVertices.end()) continue;

            if(facet.innerVisible(points[vertex_i])) {
                if(flipped) {
                    return false;
                }
                facet.invert();
                TRACE("quickhull", "inverted");
                TRACE("quickhull", printAllDistances());
                if(facet.innerVisible(points[vertex_i])) return false;
            }
            flipped = true;
        }

#ifndef NDEBUG
        containsVertices(facet);
#endif
        return true;
    }

    template<typename Number, bool Euclidian>
    void FloatQuickhull<Number, Euclidian>::FacetSpace::fixOffset(Facet& facet) {
        {
            ScopedRoundingMode rounding{FE_UPWARD};
            facet.mOuterOffset = 
                std::accumulate(facet.mVertices.begin(), facet.mVertices.end(), -std::numeric_limits<Number>::infinity(), [this,&facet](Number& prev, point_ind_t& point_i) {
                        
                        Number proj = points[point_i].dot(facet.mNormal);
                        TRACE("quickhull", "prev " << prev << " new " <<  proj);
                        
                        return std::max(prev, proj);
                });
        }

        {
            ScopedRoundingMode rounding{FE_DOWNWARD};
            facet.mInnerOffset =             
                std::accumulate(facet.mVertices.begin(), facet.mVertices.end(), std::numeric_limits<Number>::infinity(), [this,&facet](Number& prev, point_ind_t& point_i) {
                        return std::min(prev, points[point_i].dot(facet.mNormal));
                });
        }
    }


    template<typename Number, bool Euclidian>
    bool FloatQuickhull<Number, Euclidian>::FacetSpace::tryAddToOutsideSet(Facet& facet, point_ind_t point_i) {
        Number distance = facet.innerDistance(points[point_i]);

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

    template<typename Number, bool Euclidian>
    void FloatQuickhull<Number, Euclidian>::FacetSpace::establishNeighborhood(facet_ind_t facet_i, facet_ind_t other_i) {
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
    //none yet

    //vector operations
    template<typename Number, bool Euclidian>
    template<typename UnaryPredicate>
    typename FloatQuickhull<Number, Euclidian>::facet_ind_t FloatQuickhull<Number, Euclidian>::FacetSpace::findFacet(UnaryPredicate predicate) {
        return std::distance(facets.begin(), std::find_if(facets.begin(), facets.end(), predicate));
    }

    template<typename Number, bool Euclidian>
    void FloatQuickhull<Number, Euclidian>::FacetSpace::removeCoplanarFacets() {
        for(facet_ind_t facet_i = 0; facet_i < facets.size(); ++facet_i) {
            facets.erase(std::remove_if(facets.begin() + facet_i + 1, facets.end(), [this, facet_i](Facet& facet) {
                return facet.mNormal == facets[facet_i].mNormal && facet.offset() == facets[facet_i].offset();
            }), facets.end());
        }
    }

    template<typename Number, bool Euclidian>
    void FloatQuickhull<Number, Euclidian>::FacetSpace::compressVector() {
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

    template<typename Number, bool Euclidian>
    void FloatQuickhull<Number, Euclidian>::FacetSpace::endModificationPhase() {
        firstInserted = facets.size();
        firstDeleted = deletedPositions.size();
    }

    template<typename Number, bool Euclidian>
    void FloatQuickhull<Number, Euclidian>::FacetSpace::deleteFacet(facet_ind_t facet_i) {
        deletedPositions.push_back(facet_i);
    }

#ifndef NDEBUG

        template<typename Number, bool Euclidian>
        std::string FloatQuickhull<Number, Euclidian>::FacetSpace::printAllDistances() {
            std::stringstream out;
            for(int i = 0; i < points.size(); ++i) {
                out << " point " << i << " distanceInner " << facets.back().innerDistance(points[i]) << " distanceOuter " << facets.back().outerDistance(points[i]) << std::endl;
            }
            return out.str();
        }


        template<typename Number, bool Euclidian>
        std::string FloatQuickhull<Number, Euclidian>::FacetSpace::printAll() {
            std::stringstream out;
            for(auto& facet : facets) {
                out << printFacet(facet);
            }
            return out.str();
        }

        template<typename Number, bool Euclidian>
        std::string FloatQuickhull<Number, Euclidian>::FacetSpace::printFacet(Facet const& facet) {
            std::stringstream out;

            char var = 'y';

            out << "(" << carl::convert<mpq_class, double>(facet.mNormal[0]) << ")x";
            for(size_t i = 1; i < dimension; ++i) {
                out << " + (" << carl::convert<mpq_class, double>(facet.mNormal[i]) << ")" << var;
                var += 1;
            }

            out << " = " << carl::convert<mpq_class, double>(facet.offset()) << std::endl;

            return out.str();
        }

        template<typename Number, bool Euclidian>
        void FloatQuickhull<Number, Euclidian>::FacetSpace::containsVertices(Facet& facet) {
            bitset_t visited(facets.size());
            containsVertices(facet, facet, visited);
        }

        template<typename Number, bool Euclidian>
        void FloatQuickhull<Number, Euclidian>::FacetSpace::containsVertices(Facet& facet, Facet& currentFacet, bitset_t& visited) {
            for(point_ind_t point_i : currentFacet.mVertices) {
                if(facet.visible(points[point_i])) {
                    TRACE("quickhull", "NON CONTAINMENT" << std::endl << points[point_i] << std::endl << "Facet:" << std::endl << printFacet(facet));
                    TRACE("quickhull", "point_i " << point_i);
                    assert(false);
                }
            }

            for(facet_ind_t neighbor_i : facet.mNeighbors) {
                if(!visited[neighbor_i]) {
                    visited.set(neighbor_i);
                    containsVertices(facet, facets[neighbor_i], visited);
                }
            }
        }

        template<typename Number, bool Euclidian>
        void FloatQuickhull<Number, Euclidian>::FacetSpace::containsAllPoints(Facet& facet, bool inverted) {
            bitset_t checked(points.size());

            for(Facet& facet : facets) {
                for(point_ind_t point_i : facet.mOutsideSet) {
                    checked.set(point_i);
                }
            }

            for(point_ind_t point_i = 0; point_i < points.size(); ++point_i) {
                if(!checked[point_i] && facet.innerVisible(points[point_i]) &&
                    std::find(facet.mVertices.begin(), facet.mVertices.end(), point_i) == facet.mVertices.end()) {
                    TRACE("quickhull", "NON CONTAINMENT" << std::endl << points[point_i] << std::endl << "Facet:" << std::endl << printFacet(facet));
                    TRACE("quickhull", "point_i " << point_i);

                    for(int i = 0; i < facets.size(); ++i) {
                        bool deleted = std::find(deletedPositions.begin(), deletedPositions.end(), i) != deletedPositions.end();
                        TRACE("quickhull", "facet_i " << i << " contains " << !facets[i].innerVisible(points[point_i]) << " deleted " << deleted);
                    }
                    assert(false);
                }
            }

        }
#endif

}