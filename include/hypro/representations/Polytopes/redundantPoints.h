/*
 * Copyright (c) 2023-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "../../types.h"
#include "../../util/linearOptimization/Optimizer.h"

namespace hypro {

    namespace detail {
        /**
         * Applies heuristics to quickly identify points that are definitely vertices.
         * @details Currently, this function searches for extremal points per dimension.
         * @tparam Number The used number type
         * @param points The set of points to be searched
         * @param nonRedundantVertices A reference to a set of indices which identify definitive vertices
         */
        template<typename Number>
        void heuristicSearchNonredundantPoints(const std::vector<Point<Number>> &points,
                                               std::set<std::size_t> &nonRedundantVertices) {
            // find extremal points per dimension
            std::vector<std::vector<std::size_t>> minIndices(points.front().dimension(),
                                                             std::vector<std::size_t>(1, 0));
            std::vector<std::vector<std::size_t>> maxIndices(points.front().dimension(),
                                                             std::vector<std::size_t>(1, 0));
            std::size_t dim = points.front().dimension();
            for (std::size_t pointIndex = 1; pointIndex < points.size(); ++pointIndex) {
                for (std::size_t d = 0; d < dim; ++d) {
                    // Minimum extremal points
                    // if smaller than min, erase current list, replace by new list with only the current vertex index
                    if (points[pointIndex][d] < minIndices[d].front()) {
                        minIndices[d] = std::vector<std::size_t>{1, pointIndex};
                    } else if (points[pointIndex][d] == minIndices[d].front()) {
                        // append, if equal
                        minIndices[d].push_back(pointIndex);
                    }
                    // Maximum extremal points
                    // if greater than max, erase current list, replace by new list with only the current vertex index
                    if (points[pointIndex][d] > maxIndices[d].front()) {
                        maxIndices[d] = std::vector<std::size_t>{1, pointIndex};
                    } else if (points[pointIndex][d] == maxIndices[d].front()) {
                        // append, if equal
                        maxIndices[d].push_back(pointIndex);
                    }
                }
            }
            // write to result set
            for (std::size_t i = 0; i < dim; ++i) {
                std::for_each(std::begin(minIndices[i]), std::end(minIndices[i]),
                              [&nonRedundantVertices](auto idx) { nonRedundantVertices.insert(idx); });
                std::for_each(std::begin(maxIndices[i]), std::end(maxIndices[i]),
                              [&nonRedundantVertices](auto idx) { nonRedundantVertices.insert(idx); });
            }
        }
    } // namespace detail

    /**
     * Searches and removes redundant points in the passed point set.
     * @details A point is redundant, if it is not an extreme point/vertex. This property can be checked by validating,
     * whether said point can be represented as a convex combination of all other points. If this is the case, the point
     * is not a vertex.
     * @tparam Number The used number type
     * @param points The list of points to be checked for redundancy
     * @return A list of points that is redundancy-free
     */
    template<typename Number, bool useHeuristics = true>
    std::vector<Point<Number>> removeRedundantPoints(const std::vector<Point<Number>> &points) {
        if (!points.empty()) {
            // Find redundant vertices by checking whether a vertex can be represented as convex combination of the other vertices
            std::size_t vertexCount = points.size();
            // indices of points that are known to be redundant
            std::vector<std::size_t> redundantVertices{};
            // indices of points which are definitely vertices according to some fast heuristic
            std::set<std::size_t> nonRedundantVertices{};
            // apply fast heuristics
            if constexpr (useHeuristics) {
                detail::heuristicSearchNonredundantPoints(points, nonRedundantVertices);
            }

            for (std::size_t vertexIndex = 0; vertexIndex < vertexCount; ++vertexIndex) {
                if (vertexCount - redundantVertices.size() == 1) {
                    // Only one vertex remaining
                    break;
                }
                // if vertex can be excluded due to some heuristics, skip it
                if constexpr (useHeuristics) {
                    if (nonRedundantVertices.find(vertexIndex) != std::end(nonRedundantVertices)) {
                        continue;
                    }
                }

                // set up lp-problem
                matrix_t<Number> A = matrix_t<Number>(points[0].dimension(),
                                                      vertexCount - redundantVertices.size() - 1);
                Eigen::Index colIndex = 0;
                for (std::size_t i = 0; i < vertexCount; ++i) {
                    // Only use other non-redundant for convex combination
                    if (i != vertexIndex &&
                        std::find(redundantVertices.begin(), redundantVertices.end(), i) == redundantVertices.end()) {
                        A.col(colIndex) = points[i].rawCoordinates();
                        colIndex += 1;
                    }
                }

                // Convex combination should equal the current vertex
                Optimizer<Number> opt(A, points[vertexIndex].rawCoordinates());
                opt.setRelations(std::vector<carl::Relation>(points[0].dimension(), carl::Relation::EQ));

                // Bound columns
                for (Eigen::Index colIndex = 0; colIndex < A.cols(); ++colIndex) {
                    vector_t<Number> constraint = vector_t<Number>::Zero(A.cols());
                    constraint(colIndex) = 1;
                    opt.addConstraint(constraint, 1, carl::Relation::LEQ);
                    opt.addConstraint(constraint, 0, carl::Relation::GEQ);
                }
                // Add constraint that all coefficients add up to 1
                vector_t<Number> constraint = vector_t<Number>::Ones(A.cols());
                opt.addConstraint(constraint, 1, carl::Relation::EQ);

                if (opt.checkConsistency()) {
                    redundantVertices.push_back(vertexIndex);
                }
            }

            // Create new list of vertices that only contains the non-redundant ones
            std::vector<Point<Number>> reducedVertices(vertexCount - redundantVertices.size());
            std::size_t reducedIndex = 0;
            for (std::size_t vIndex = 0; vIndex < vertexCount; ++vIndex) {
                if (std::find(redundantVertices.begin(), redundantVertices.end(), vIndex) == redundantVertices.end()) {
                    reducedVertices[reducedIndex] = points[vIndex];
                    reducedIndex += 1;
                }
            }

            return reducedVertices;
        }
        return points;
    }

}  // namespace hypro
