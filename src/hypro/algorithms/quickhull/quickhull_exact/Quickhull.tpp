/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "Quickhull.h"

namespace hypro {
    template<typename Number, bool Euclidian>
    ExactQuickhull<Number, Euclidian>::QuickhullAlgorithm( pointVector_t
    & points,
    dimension_t dimension
    )
    :

    points ( points )
    , dimension(dimension)
    , fSpace(points, dimension) {
#ifndef NDEBUG
        assert(!points.empty());
        if constexpr(Euclidian)
        {
            assert(points[0].rows() == (int) dimension);
        } else {
            assert(points[0].rows() == (int) dimension + 1);
        }
#endif
    }

    template<typename Number, bool Euclidian>
    void ExactQuickhull<Number, Euclidian>::compute() {
        TRACE("quickhull", points);
        removeDuplicateInputs();

        // There's only a single point, so we fix it from both sides.
        if (dimension == 1 && points.size() == 1) {
            makeTrivialHull();
            return;
        }

        buildInitialPolytope();
#ifdef HYPRO_LOGGING
        for ( Facet& facet : fSpace.facets ) {
            TRACE( "quickhull", "furthest " << facet.furthestPoint << std::endl
                                            << " distance " << facet.furthestPointDistance );
        }
#endif

        processPoints();
#ifndef NDEBUG
        TRACE("quickhull", "ALL facets:" << std::endl
                                         << fSpace.printAll());
#endif

        fSpace.compressVector();
        fSpace.removeCoplanarFacets();

#ifndef NDEBUG
        TRACE("quickhull", "ALL facets:" << std::endl
                                         << fSpace.printAll());

        for (facet_ind_t facet_i = 0; facet_i < fSpace.facets.size(); ++facet_i) {
            Facet &facet = fSpace.facets[facet_i];
            for (point_ind_t point_i = 0; point_i < points.size(); ++point_i) {
                point_t point = points[point_i];
                if (facet.visible(point)) {
                    TRACE("quickhull", "NON CONTAINMENT" << std::endl
                                                         << point << std::endl
                                                         << "Facet:" << std::endl
                                                         << fSpace.printFacet(facet));
                    TRACE("quickhull", "facet_i: " << facet_i);
                    TRACE("quickhull", "distance" << std::endl
                                                  << facet.distance(point));
                    assert(false);
                }
            }
        }
#endif
    }

    template<typename Number, bool Euclidian>
    void ExactQuickhull<Number, Euclidian>::removeDuplicateInputs() {
        for (point_ind_t point_i = 0; point_i < points.size(); ++point_i) {
            for (point_ind_t point_j = point_i + 1; point_j < points.size(); ++point_j) {
                if (points[point_i] == points[point_j]) {
                    points.erase(points.begin() + point_j);
                }
            }
        }
    }

    template<typename Number, bool Euclidian>
    void ExactQuickhull<Number, Euclidian>::makeTrivialHull() {
        fSpace.insertTrivialFacet(points[0][0]);
        fSpace.insertTrivialFacet(points[0][0]);
        fSpace.facets.back().invert();
    }

    template<typename Number, bool Euclidian>
    void ExactQuickhull<Number, Euclidian>::buildInitialPolytope() {
        if (constructInitialFacet()) return;

        // Find furthest away point
        auto [onPlane, furthestPoint_i] = findFurthestPoint(fSpace.facets.back());

        TRACE("quickhull", "onPlane " << onPlane << " furthestPoint_i " << furthestPoint_i);

        // Since the number type is exact, check if the furthest away point is on the inital facet.
        if (onPlane) {
            constructLowerDimensional();
            return;
        }

        // calculate barycenter of initial polytope, which is the baryCenter vertices of the initial facet and the furthest away point
        //  baryCenter = points[furthestPoint_i];

        // for(size_t vertexPos = 0; vertexPos < dimension; ++vertexPos) {
        //     baryCenter += points[fSpace.facets.back().mVertices[vertexPos]];
        // }

        // baryCenter /= dimension + 1;

        // Set orientation
        if (fSpace.facets.front().visible(points[furthestPoint_i])) {
            fSpace.facets.front().invert();
        }

        fSpace.endModificationPhase();

        // Create cone from the new point
        for (size_t i = 0; i < dimension; ++i) {
            size_t insertedAt = fSpace.insertConePart(0, furthestPoint_i, i);
            Facet &createdFacet = fSpace.facets.back();

            fSpace.facets.front().mNeighbors[i] =
                    fSpace.facets.size() - 1;     // Set i-th neighbor of initial facet to the created facet.

#ifndef NDEBUG
            for (facet_ind_t other_i = 0; other_i < fSpace.facets.size() - 1; ++other_i) {
                if constexpr(Euclidian)
                {
                    assert(fSpace.facets[other_i].mNormal != createdFacet.mNormal);
                } else {
                    assert(fSpace.facets[other_i].mNormal != createdFacet.mNormal ||
                           fSpace.facets[other_i].mOffset != createdFacet.mOffset);
                }
            }
#endif

            createdFacet.mNeighbors[insertedAt] = 0;
            findConeNeighbors(fSpace.facets.size() - 1);
        }

        initialPartition();

        fSpace.endModificationPhase();
    }

    template<typename Number, bool Euclidian>
    bool ExactQuickhull<Number, Euclidian>::constructInitialFacet() {
        Facet &facet = fSpace.insertNew();

        Eigen::FullPivLU <matrix_t<Number>> lu(dimension, dimension + 1);
        matrix_t <Number> matrix = matrix_t<Number>::Zero(dimension, dimension + 1);

        // Do first iteration
        facet.mVertices[0] = 0;

        // Set the first row
        if constexpr(Euclidian)
        {
            matrix.row(0).head(dimension) = points[0].transpose();
            matrix(0, dimension) = 1;
        } else {
            matrix.row(0) = points[0].transpose();
        }

        // Compute normal and offset
        lu.compute(matrix);
        vector_t <Number> result = lu.kernel().col(0);

        facet.mNormal = result.head(dimension);
        facet.mOffset = -result[dimension];

        for (size_t d = 1; d < dimension; ++d) {
            auto [onPlane, furthestPoint_i] = findFurthestPoint(facet);

            if (onPlane) {
                constructLowerDimensional();
                return true;
            }

            facet.mVertices[d] = furthestPoint_i;
            // Set the (d+1)-th row
            if constexpr(Euclidian)
            {
                matrix.row(d).head(dimension) = points[furthestPoint_i].transpose();
                matrix(d, dimension) = 1;
            } else {
                matrix.row(d) = points[furthestPoint_i].transpose();
            }

            // Compute normal and offset
            lu.compute(matrix);
            result = lu.kernel().col(0);

            facet.mNormal = result.head(dimension);
            facet.mOffset = -result[dimension];
        }
        std::sort(facet.mVertices.begin(), facet.mVertices.end());

        return false;
    }

    template<typename Number, bool Euclidian>
    std::tuple<bool, size_t> ExactQuickhull<Number, Euclidian>::findFurthestPoint(Facet &facet) {
        point_ind_t furthestPoint = 0;
        Number furthestDistance = 0;

        for (point_ind_t point_i = 0; point_i < points.size(); ++point_i) {
            Number distance = carl::abs(facet.distance(points[point_i]));

            if constexpr(!Euclidian)
            {
                if (distance > 0 && points[point_i][dimension] == 0) {
                    return std::make_tuple(false, point_i);
                }
            }

            if (distance > furthestDistance) {
                furthestDistance = distance;
                furthestPoint = point_i;
            }
        }

        return std::make_tuple(furthestDistance == 0, furthestPoint);
    }

    template<typename Number, bool Euclidian>
    void ExactQuickhull<Number, Euclidian>::processPoints() {
        facet_ind_t facetToProcess_i = getFacetToProcess();

        while (facetToProcess_i != fSpace.facets.size()) {
            bitset_t visited{fSpace.facets.size()};
            visited.set(facetToProcess_i);
            buildCone(facetToProcess_i, fSpace.facets[facetToProcess_i].furthestPoint, visited);

            partitionAllVertices();
            fSpace.endModificationPhase();

            facetToProcess_i = getFacetToProcess();
        }
    }

    template<typename Number, bool Euclidian>
    typename ExactQuickhull<Number, Euclidian>::facet_ind_t ExactQuickhull<Number, Euclidian>::getFacetToProcess() {
        return fSpace.findFacet([](Facet &facet) {
            return !facet.mOutsideSet.empty();
        });
    }

    template<typename Number, bool Euclidian>
    void ExactQuickhull<Number, Euclidian>::buildCone(facet_ind_t currentFacet_i, point_ind_t visiblePoint_i,
                                                      bitset_t &visited) {
        fSpace.deleteFacet(currentFacet_i);

        point_t &visiblePoint = points[visiblePoint_i];

        for (size_t neighbor_pos = 0; neighbor_pos < dimension; ++neighbor_pos) {
            facet_ind_t neighbor_i = fSpace.facets[currentFacet_i].mNeighbors[neighbor_pos];

            if (!visited[neighbor_i]) {
                // neighbor is "inside" horizon
                if (fSpace.facets[neighbor_i].visible(visiblePoint)) {
                    visited.set(neighbor_i);
                    buildCone(neighbor_i, visiblePoint_i, visited);
                } else {
                    // this ridge to the neighbor is part of the horizon

                    // Find the index of the ridge from the facet outside the horizon (neighbor_i) to the facet inside the horizon (currentFacet_i).
                    size_t ridgeIndex_outer_inner = fSpace.facets[neighbor_i].findNeighborIndex(currentFacet_i);

                    size_t differentiatingPosition = fSpace.insertConePart(neighbor_i, visiblePoint_i,
                                                                           ridgeIndex_outer_inner);

#ifndef NDEBUG
                    fSpace.containsAllPoints(fSpace.facets.back());
#endif
                    // Set the outside facet as neighbor of the new facet at the index where the differentiating point was inserted.
                    fSpace.facets.back().mNeighbors[differentiatingPosition] = neighbor_i;
                    // Replace the facet inside the horizon (currentFacet_i) as neighbor of neighbor_i with the newly created facet.
                    fSpace.facets[neighbor_i].mNeighbors[ridgeIndex_outer_inner] =
                            fSpace.facets.size() - 1 /*The index of the new facet*/;

                    findConeNeighbors(fSpace.facets.size() - 1);
                }
            }
        }
    }

    template<typename Number, bool Euclidian>
    void ExactQuickhull<Number, Euclidian>::constructLowerDimensional() {
        if constexpr(!Euclidian)
        return;

        TRACE("quickhull", "dropping from d=" << dimension << " to d=" << dimension - 1);

        // Copy first facet
        fSpace.facets.push_back(fSpace.facets.front());
        fSpace.facets.back().invert();

        size_t reducableDimension = 0;
        for (; reducableDimension < dimension; ++reducableDimension) {
            if (fSpace.facets.front().mNormal[reducableDimension] != 0) break;
        }

        assert(fSpace.facets.front().mNormal != point_t::Zero(dimension));
        assert(reducableDimension < dimension);

        pointVector_t reducedPoints;

        std::transform(points.begin(), points.end(), std::back_inserter<pointVector_t>(reducedPoints),
                       [reducableDimension, this](point_t &point) {
                           point_t reducedPoint{pointSize() - 1};

                           for (size_t i = 0, j = 0; i < pointSize() - 1; ++i, ++j) {
                               if (j == reducableDimension) j += 1;
                               reducedPoint[i] = point[j];
                           }

                           // Should be RVO'd
                           return reducedPoint;
                       });

        // TODO I have no idea how the 'Euclidian' template argument of Quickhull us inferred here.
        QuickhullAlgorithm <Number, Euclidian> qh{reducedPoints, dimension - 1};

        qh.compute();

        for (Facet const &facet: qh.getFacets()) {
            fSpace.insertReduced(facet, pointSize(), reducableDimension);
        }
    }

    template<typename Number, bool Euclidian>
    void ExactQuickhull<Number, Euclidian>::findConeNeighbors(facet_ind_t facet_i) {
        // We always ignore the last one
        for (facet_ind_t inserted_i = fSpace.firstInserted; inserted_i < fSpace.facets.size() - 1; ++inserted_i) {
            fSpace.establishNeighborhood(facet_i, inserted_i);
        }
    }

    template<typename Number, bool Euclidian>
    void ExactQuickhull<Number, Euclidian>::partitionAllVertices() {
        for (facet_ind_t deleted_i: fSpace.deletedPositions) {
            for (point_ind_t outside_i: fSpace.facets[deleted_i].mOutsideSet) {
                for (facet_ind_t inserted_i = fSpace.firstInserted; inserted_i < fSpace.facets.size(); ++inserted_i) {
                    if (fSpace.tryAddToOutsideSet(fSpace.facets[inserted_i], outside_i)) break;
                }
            }

            fSpace.facets[deleted_i].mOutsideSet.clear();
        }
    }

    template<typename Number, bool Euclidian>
    void ExactQuickhull<Number, Euclidian>::initialPartition() {
        for (point_ind_t point_i = 0; point_i < points.size(); ++point_i) {
            for (Facet &facet: fSpace.facets) {
                if (fSpace.tryAddToOutsideSet(facet, point_i)) break;
            }
        }
    }

    template<typename Number, bool Euclidian>
    typename ExactQuickhull<Number, Euclidian>::facetVector_t &ExactQuickhull<Number, Euclidian>::getFacets() {
        return fSpace.facets;
    }

    template<typename Number, bool Euclidian>
    size_t ExactQuickhull<Number, Euclidian>::pointSize() {
        if constexpr(Euclidian)
        {
            return dimension;
        } else {
            return dimension + 1;
        }
    }
}  // namespace hypro
