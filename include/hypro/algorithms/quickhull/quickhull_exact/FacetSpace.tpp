/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

//
// Created by leander.behr on 11/11/19.
//

#include "FacetSpace.h"

namespace hypro {

// facet construction
    template<typename Number, bool Euclidian>
    typename ExactQuickhull<Number, Euclidian>::Facet &ExactQuickhull<Number, Euclidian>::FacetSpace::insertNew() {
        facets.emplace_back();

        facets.back().mVertices = std::vector<point_ind_t>(dimension);
        facets.back().mNeighbors = std::vector<facet_ind_t>(dimension);
        facets.back().mOutsideSet = std::vector<point_ind_t>();
        facets.back().mNormal = point_t(dimension);

        return facets.back();
    }

    template<typename Number, bool Euclidian>
    void ExactQuickhull<Number, Euclidian>::FacetSpace::insertTrivialFacet(const Number scalar) {
        facets.emplace_back();
        facets.back().mOffset = scalar;
        facets.back().mNormal = point_t{1};
        facets.back().mNormal[0] = 1;
    }

    template<typename Number, bool Euclidian>
    void ExactQuickhull<Number, Euclidian>::FacetSpace::insertReduced(Facet const &other, dimension_t newDimension,
                                                                      dimension_t reducedDimension) {
        Facet &facet = facets.emplace_back();
        facet.mOffset = other.mOffset;
        facet.mNormal = qhvector_t(newDimension);

        for (size_t i = 0, j = 0; i < newDimension; ++i, ++j) {
            if (i == reducedDimension) {
                facet.mNormal[i] = 0;
                j -= 1;
                continue;
            }
            facet.mNormal[i] = other.mNormal[j];
        }
    }

    template<typename Number, bool Euclidian>
    size_t ExactQuickhull<Number, Euclidian>::FacetSpace::copyVertices(Facet &facet, Facet const &other,
                                                                       point_ind_t visiblePoint, size_t replaceAt) {
        // Doing some work here to keep the vertices sorted
        bool inserted = false;
        size_t insertedPosition = dimension - 1;
        size_t thisInd = 0, otherInd = 0;

        while (true) {
            otherInd += (otherInd == replaceAt);

            if (!(thisInd < dimension && otherInd < dimension)) break;

            bool insertHere = !inserted && other.mVertices[otherInd] >= visiblePoint;

            facet.mVertices[thisInd] = insertHere ? visiblePoint : other.mVertices[otherInd];

            inserted |= insertHere;

            if (insertHere)
                insertedPosition = thisInd;
            else
                otherInd += 1;

            thisInd += 1;
        }

        if (!inserted) facet.mVertices[dimension - 1] = visiblePoint;

        return insertedPosition;
    }

    template<typename Number, bool Euclidian>
    size_t ExactQuickhull<Number, Euclidian>::FacetSpace::insertConePart(facet_ind_t other_i, point_ind_t visiblePoint,
                                                                         size_t replaceAt) {
        insertNew();
        size_t insertedAt = copyVertices(facets.back(), facets[other_i], visiblePoint, replaceAt);
        computeNormal(facets.back());
        validateFacet(facets.back(), points[facets[other_i].mVertices[replaceAt]], facets[other_i]);
        return insertedAt;
    }

// facet modification
    template<typename Number, bool Euclidian>
    void ExactQuickhull<Number, Euclidian>::FacetSpace::computeNormal(Facet &facet) {
        /// TODO Allocate space for matrix once and reuse it
        /// TODO Could also use __restrict__ to get memcpy here (probably).
#ifdef QUICKHULL_USE_LOW_DIMENSIONAL_IMPROVEMENT
        assert(((Euclidian && (std::size_t) points[facet.mVertices[0]].size() == dimension) ||
                (!Euclidian && (std::size_t) points[facet.mVertices[0]].size() == dimension + 1)));
        if (Euclidian && dimension == 3) {
            const point_t &v0 = points[facet.mVertices[0]];
            const point_t &v1 = points[facet.mVertices[1]];
            const point_t &v2 = points[facet.mVertices[2]];
            point_t p1 = v1 - v0;
            point_t p2 = v2 - v0;
            point_t normal = point_t(3);
            normal[0] = p1[1] * p2[2] - p1[2] * p2[1];
            normal[1] = p1[2] * p2[0] - p1[0] * p2[2];
            normal[2] = p1[0] * p2[1] - p1[1] * p2[0];
            Number offset = normal[0] * v0[0] + normal[1] * v0[1] + normal[2] * v0[2];
            facet.mNormal = normal;
            facet.mOffset = offset;
            return;
        } else if (Euclidian && dimension == 2) {
            point_t v0 = points[facet.mVertices[0]];
            point_t v1 = points[facet.mVertices[1]];
            point_t normal = point_t(2);
            normal[0] = v1[1] - v0[1];
            normal[1] = -1 * (v1[0] - v0[0]);
            Number offset = v0[0] * v1[1] - v0[1] * v1[0];
            facet.mNormal = normal;
            facet.mOffset = offset;
            return;
        }
#endif

        matrix_t<Number> matrix(dimension, dimension + 1);

        if constexpr (Euclidian) {
            for (size_t i = 0; i < dimension; ++i) {
                matrix.row(i).head(dimension) = points[facet.mVertices[i]].transpose();
                matrix.row(i)[dimension] = 1;
            }
        } else {
            for (size_t i = 0; i < dimension; ++i) {
                matrix.row(i) = points[facet.mVertices[i]].transpose();
            }
        }

        Eigen::FullPivLU<matrix_t<Number>> lu(matrix);
        assert(static_cast<size_t>( lu.rank()) == dimension);


        point_t result = lu.kernel().col(0);
        assert(matrix * result == point_t::Zero(dimension));

#ifndef NDEBUG
        // point_t tmp = facet.mNormal;
        // if ( tmp.rows() < dimension ) {
        //	tmp.resize( dimension );
        // }
        // tmp.block( 0, 0, dimension, 1 ) = result;
#endif

        for (size_t i = 0; i < dimension; ++i) {
            facet.mNormal[i] = result[i];
        }
        facet.mOffset = -result[dimension];
        // assert( tmp == facet.mNormal );
    }

    template<typename Number, bool Euclidian>
    void ExactQuickhull<Number, Euclidian>::FacetSpace::validateFacet(Facet &facet, point_t const &contained,
                                                                      Facet const &adjacentFacet) {
        facet.setOrientation(contained, adjacentFacet);
#ifndef NDEBUG
        containsVertices(facet);
#endif
    }

    template<typename Number, bool Euclidian>
    bool ExactQuickhull<Number, Euclidian>::FacetSpace::tryAddToOutsideSet(Facet &facet, point_ind_t point_i) {
        Number distance = facet.distance(points[point_i]);

        if (distance > Number(0)) {
            facet.mOutsideSet.push_back(point_i);

            if (distance > facet.furthestPointDistance) {
                facet.furthestPointDistance = distance;
                facet.furthestPoint = point_i;
            }
            return true;
        }
        return false;
    }

    template<typename Number, bool Euclidian>
    void
    ExactQuickhull<Number, Euclidian>::FacetSpace::establishNeighborhood(facet_ind_t facet_i, facet_ind_t other_i) {
        Facet &facet = facets[facet_i];
        Facet &other = facets[other_i];

        size_t thisNeighborPosition = dimension - 1;
        size_t otherNeighborPosition = dimension - 1;

        size_t thisInd = 0;
        size_t otherInd = 0;

        bool hammingNonZero = false;

        while (true) {
            if (facet.mVertices[thisInd] < other.mVertices[otherInd]) {
                if (hammingNonZero) return;
                hammingNonZero = true;
                thisNeighborPosition = thisInd;
                thisInd += 1;
            } else if (facet.mVertices[thisInd] > other.mVertices[otherInd]) {
                otherNeighborPosition = otherInd;
                otherInd += 1;
            } else {
                thisInd += 1;
                otherInd += 1;
            }

            if (thisInd == dimension) break;

            if (otherInd == dimension) {
                if (thisInd + 1 - hammingNonZero < otherInd)
                    return;
                else
                    break;
            }
        }

        facet.mNeighbors[thisNeighborPosition] = other_i;
        other.mNeighbors[otherNeighborPosition] = facet_i;
    }

// facet queries
// none yet

// vector operations
    template<typename Number, bool Euclidian>
    template<typename UnaryPredicate>
    typename ExactQuickhull<Number, Euclidian>::facet_ind_t
    ExactQuickhull<Number, Euclidian>::FacetSpace::findFacet(UnaryPredicate predicate) {
        return std::distance(facets.begin(), std::find_if(facets.begin(), facets.end(), predicate));
    }

    template<typename Number, bool Euclidian>
    void ExactQuickhull<Number, Euclidian>::FacetSpace::removeCoplanarFacets() {
        for (facet_ind_t facet_i = 0; facet_i < facets.size(); ++facet_i) {
            facets.erase(std::remove_if(facets.begin() + facet_i + 1, facets.end(), [this, facet_i](Facet &facet) {
                             return facet.mNormal == facets[facet_i].mNormal && facet.mOffset == facets[facet_i].mOffset;
                         }),
                         facets.end());
        }
    }

    template<typename Number, bool Euclidian>
    void ExactQuickhull<Number, Euclidian>::FacetSpace::compressVector() {
        assert(facets.size() - deletedPositions.size() > 0 || !Euclidian);

        facetVector_t newVec;

        for (size_t i = 0; i < facets.size(); ++i) {
            if (std::find(deletedPositions.begin(), deletedPositions.end(), i) != deletedPositions.end()) continue;
            newVec.emplace_back(std::move(facets[i]));
        }

        facets = std::move(newVec);

        deletedPositions.clear();
    }

    template<typename Number, bool Euclidian>
    void ExactQuickhull<Number, Euclidian>::FacetSpace::endModificationPhase() {
        firstInserted = facets.size();
        firstDeleted = deletedPositions.size();
    }

    template<typename Number, bool Euclidian>
    void ExactQuickhull<Number, Euclidian>::FacetSpace::markForDeletion(facet_ind_t facet_i) {
        deletedPositions.push_back(facet_i);
    }

    template<typename Number, bool Euclidian>
    std::string ExactQuickhull<Number, Euclidian>::FacetSpace::printAll() {
        std::stringstream out;
        for (auto &facet: facets) {
            out << printFacet(facet);
        }
        return out.str();
    }

    template<typename Number, bool Euclidian>
    std::string ExactQuickhull<Number, Euclidian>::FacetSpace::printFacet(Facet const &facet) {
        std::stringstream out;

        char var = 'y';

        out << "(" << carl::convert<mpq_class, double>(facet.mNormal[0]) << ")x";
        for (size_t i = 1; i < dimension; ++i, ++var) {
            out << " + (" << carl::convert<mpq_class, double>(facet.mNormal[i]) << ")" << var;
        }

        out << " = " << carl::convert<mpq_class, double>(facet.mOffset) << std::endl;

        return out.str();
    }

    template<typename Number, bool Euclidian>
    void ExactQuickhull<Number, Euclidian>::FacetSpace::containsVertices(Facet &facet) {
        bitset_t visited(facets.size());
        containsVertices(facet, facet, visited);
    }

    template<typename Number, bool Euclidian>
    void ExactQuickhull<Number, Euclidian>::FacetSpace::containsVertices(Facet &facet, Facet &currentFacet,
                                                                         bitset_t &visited) {
        for (point_ind_t point_i: currentFacet.mVertices) {
            if (facet.visible(points[point_i])) {
                TRACE("quickhull", "NON CONTAINMENT" << std::endl
                                                     << points[point_i] << std::endl
                                                     << "Facet:" << std::endl
                                                     << printFacet(facet));
                TRACE("quickhull", "point_i " << point_i);
                assert(false);
            }
        }

        for (facet_ind_t neighbor_i: facet.mNeighbors) {
            if (!visited[neighbor_i]) {
                visited.set(neighbor_i);
                containsVertices(facet, facets[neighbor_i], visited);
            }
        }
    }

    template<typename Number, bool Euclidian>
    void ExactQuickhull<Number, Euclidian>::FacetSpace::containsAllPoints(Facet &facet, bool inverted) {
        bitset_t checked(points.size());

        for (Facet &facet: facets) {
            for (point_ind_t point_i: facet.mOutsideSet) {
                checked.set(point_i);
            }
        }

        for (point_ind_t point_i = 0; point_i < points.size(); ++point_i) {
            if (!checked[point_i] && facet.visible(points[point_i])) {
                TRACE("quickhull", "NON CONTAINMENT" << std::endl
                                                     << points[point_i] << std::endl
                                                     << "Facet:" << std::endl
                                                     << printFacet(facet));
                TRACE("quickhull", "point_i " << point_i);
                TRACE("quickhull", "Checking inverted facet.");

                if (!inverted) {
                    facet.invert();
                    containsAllPoints(facet, true);
                }

                assert(false);
            }
        }
    }

}  // namespace hypro
