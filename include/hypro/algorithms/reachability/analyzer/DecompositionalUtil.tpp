/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "DecompositionalUtil.h"

namespace hypro {

    inline bool isSegmentedSubspace(const DynamicType dynamics) {
        return (dynamics == DynamicType::affine || dynamics == DynamicType::linear);
    }

    inline std::size_t getVarIndexWithoutDiscrete(std::size_t index, const Decomposition &decomposition) {
        std::size_t res = 0;
        for (std::size_t i = 0; i < index; ++i) {
            // get subspace of index i
            for (std::size_t s = 0; s < decomposition.subspaces.size(); ++s) {
                if (std::find(decomposition.subspaces[s].begin(), decomposition.subspaces[s].end(), i) !=
                    decomposition.subspaces[s].end()) {
                    if (decomposition.subspaceTypes[s] != DynamicType::discrete) {
                        res += 1;
                    }
                }
            }
        }
        return res;
    }

    namespace detail {

        template<typename Representation>
        HPolytope<typename Representation::NumberType>
        composeSubspaceConstraints(const std::vector<Representation> &subspaceSets,
                                   const Condition<typename Representation::NumberType> &dependencies,
                                   const Decomposition &decomposition, std::size_t clockCount) {
            using Number = typename Representation::NumberType;
            if (std::any_of(subspaceSets.begin(), subspaceSets.end(), [](const auto &set) { return set.empty(); })) {
                return HPolytope<Number>::Empty();
            }
            // variable order in subspace sets with clocks: x_i1, x_i2,...,x_ik,x_i1^0,...,x_ik^0,c_i^1,...,c_i^clockCount
            // variable order in dependencies: (x_1^0,...,x_n^init)
            // create composed polytope with dimension dim(S_1) + ... + dim(S_n)
            // variable order in composed set: x_1,...,x_n,x_1^0,...,x_n^0,c_1^1,...,c_1^clockCount,c_2^1,..,c_n^clockCount

            std::size_t varCount = std::accumulate(decomposition.subspaces.begin(), decomposition.subspaces.end(), 0,
                                                   [](std::size_t cur, const auto &subspace) {
                                                       return cur + subspace.size();
                                                   });

            std::size_t clockedSubspaceCount = std::accumulate(decomposition.subspaceTypes.begin(),
                                                               decomposition.subspaceTypes.end(), 0,
                                                               [](std::size_t cur, const auto &dynamic) {
                                                                   return dynamic == DynamicType::discrete ? cur : cur +
                                                                                                                   1;
                                                               });

            // number of rows in full poytope
            std::size_t compRows = 0;
            compRows += std::accumulate(subspaceSets.begin(), subspaceSets.end(), 0,
                                        [](std::size_t cur, const auto &sSet) { return cur + sSet.matrix().rows(); });
            if (!dependencies.isTrue()) {
                compRows += dependencies.getMatrix().rows();
            }
            // 2 inequalities for each equation c_1 = c_i in the subspaces i != 1 (per clock c)
            compRows += 2 * (clockCount * (clockedSubspaceCount - 1));
            // number of columns in full polytope
            // additional dimensions for discrete initial variables
            std::size_t compDim = clockCount > 0 ? 2 * varCount + clockCount * clockedSubspaceCount : varCount;
            //std::size_t compDim = std::accumulate( subspaceSets.begin(), subspaceSets.end(), 0,
            //    []( std::size_t cur, const auto& segment ) { return cur + segment.dimension(); } );
            assert(clockCount > 0 || varCount == compDim);
            matrix_t<Number> compMat = matrix_t<Number>::Zero(compRows, compDim);
            vector_t<Number> compVec = vector_t<Number>::Zero(compRows);

            std::size_t initVarOffset = varCount;
            std::size_t clockOffset = 2 * varCount;

            std::size_t accRows = 0;
            std::size_t clockedSubspaceCounter = 0;
            for (std::size_t i = 0; i < subspaceSets.size(); ++i) {
                auto subspaceMatrix = subspaceSets[i].matrix();
                auto subspaceVector = subspaceSets[i].vector();
                auto subspaceVars = decomposition.subspaces[i];
                compVec.segment(accRows, subspaceVector.rows()) = subspaceVector;
                for (std::size_t row = 0; row < (std::size_t) subspaceMatrix.rows(); ++row) {
                    for (std::size_t varIndex = 0; varIndex < subspaceVars.size(); ++varIndex) {
                        compMat(accRows, subspaceVars[varIndex]) = subspaceMatrix(row, varIndex);
                        if (clockCount > 0 && decomposition.subspaceTypes[i] != DynamicType::discrete) {
                            compMat(accRows, initVarOffset + subspaceVars[varIndex]) = subspaceMatrix(row,
                                                                                                      subspaceVars.size() +
                                                                                                      varIndex);
                        }
                    }
                    if (decomposition.subspaceTypes[i] != DynamicType::discrete) {
                        for (std::size_t clockIndex = 0; clockIndex < clockCount; ++clockIndex) {
                            compMat(accRows,
                                    clockOffset + clockedSubspaceCounter * clockCount + clockIndex) = subspaceMatrix(
                                    row, 2 * subspaceVars.size() + clockIndex);
                        }
                    }
                    accRows += 1;
                }
                if (decomposition.subspaceTypes[i] != DynamicType::discrete) {
                    clockedSubspaceCounter += 1;
                }
            }

            if (!dependencies.isTrue()) {
                assert(dependencies.dimension() == varCount);
                assert(clockCount > 0);
                // add constraints of dependencies on x_i^init
                compMat.block(accRows, initVarOffset, dependencies.getMatrix().rows(),
                              dependencies.getMatrix().cols()) = dependencies.getMatrix();
                compVec.segment(accRows, dependencies.getVector().rows()) = dependencies.getVector();
                accRows += dependencies.getMatrix().rows();
            }

            // if all subspaces are discrete, we are done. Else: find first subspace that is not discrete
            std::size_t clockedSubspace = 0;
            while (clockedSubspace < decomposition.subspaces.size() &&
                   decomposition.subspaceTypes[clockedSubspace] == DynamicType::discrete) {
                clockedSubspace += 1;
            }
            // add constraints for clock equality
            for (std::size_t clockIndex = 0; clockIndex < clockCount; ++clockIndex) {
                // counts how many clocked subspaces are synchronized. 1 because first subspace is always synchronized with itself
                std::size_t synchronizedSubspaces = 1;
                for (std::size_t subspace = clockedSubspace + 1;
                     subspace < decomposition.subspaces.size(); ++subspace) {
                    if (decomposition.subspaceTypes[subspace] == DynamicType::discrete) continue;
                    // clockedSubspace has the first clock, because all lower subspaces are discrete
                    compMat(accRows, clockOffset + clockIndex) = 1;
                    compMat(accRows, clockOffset + clockCount * synchronizedSubspaces + clockIndex) = -1;
                    compMat(accRows + 1, clockOffset + clockIndex) = -1;
                    compMat(accRows + 1, clockOffset + clockCount * synchronizedSubspaces + clockIndex) = 1;
                    accRows += 2;
                    synchronizedSubspaces += 1;
                }
            }
            return HPolytope<Number>(compMat, compVec);
        }

        template<typename Representation>
        Representation composeSubspaces(const std::vector<Representation> &subspaceSets,
                                        const Condition<typename Representation::NumberType> &dependencies,
                                        const Decomposition &decomposition, std::size_t clockCount) {
            if (std::any_of(subspaceSets.begin(), subspaceSets.end(), [](const auto &set) { return set.empty(); })) {
                return Representation::Empty();
            }
            START_BENCHMARK_OPERATION("ComposeConstraints");
            auto pol = composeSubspaceConstraints(subspaceSets, dependencies, decomposition, clockCount);
            STOP_BENCHMARK_OPERATION("ComposeConstraints");
            std::size_t varCount = std::accumulate(decomposition.subspaces.begin(), decomposition.subspaces.end(), 0,
                                                   [](std::size_t cur, const auto &subspace) {
                                                       return cur + subspace.size();
                                                   });
            std::vector<std::size_t> varIndices(varCount);
            for (std::size_t i = 0; i < varIndices.size(); ++i) {
                varIndices[i] = i;
            }
            // todo: keep as polytopes for projection, convert after
            Representation comp;
            convert(pol, comp);
            START_BENCHMARK_OPERATION("ProjectComposed");
            auto res = projectOnDimensions(comp, varIndices);
            STOP_BENCHMARK_OPERATION("ProjectComposed");
            return res;
        }

        template<typename Representation>
        Condition<typename Representation::NumberType>
        getDependencies(const Representation &composedSet, const Decomposition &decomposition) {
            using Number = typename Representation::NumberType;
            if (composedSet.empty()) {
                assert(false && "getDependencies called with empty set");
            }

            std::vector<Eigen::Index> depIndices;
            auto composedMatrix = composedSet.matrix();
            for (Eigen::Index row = 0; row < composedMatrix.rows(); ++row) {
                std::vector<Eigen::Index> nonZeroCols;
                for (Eigen::Index col = 0; col < composedMatrix.cols(); ++col) {
                    if (composedMatrix(row, col) != 0) {
                        nonZeroCols.push_back(col);
                    }
                }
                if (isDependency<Representation>(nonZeroCols, decomposition)) {
                    depIndices.push_back(row);
                }
            }
            if (depIndices.size() == 0) {
                return Condition<Number>(ConstraintSetT<Number>());
            }

            matrix_t<Number> depMatrix(depIndices.size(), composedSet.dimension());
            vector_t<Number> depVector(depIndices.size());
            for (std::size_t row = 0; row < depIndices.size(); ++row) {
                depMatrix.row(row) = composedMatrix.row(depIndices[row]);
                depVector(row) = composedSet.vector()(depIndices[row]);
            }
            Condition<Number> dependencies(depMatrix, depVector);
            return dependencies;
        }

        template<typename Representation>
        bool isDependency(const std::vector<Eigen::Index> &dimensions, const Decomposition &decomposition) {
            if (dimensions.size() == 0) {
                return false;
            }
            std::vector<std::vector<std::size_t>> subspaces = decomposition.subspaces;
            std::set<std::size_t> involvedSubspaces;
            for (auto dim: dimensions) {
                for (std::size_t subspace = 0; subspace < subspaces.size(); ++subspace) {
                    if (std::find(subspaces[subspace].begin(), subspaces[subspace].end(), dim) !=
                        subspaces[subspace].end()) {
                        involvedSubspaces.insert(subspace);
                    }
                }
            }
            return involvedSubspaces.size() > 1;
        }

        template<typename Representation>
        std::vector<Representation>
        decompose(const Representation &composedSet, const Decomposition &decomposition, std::size_t clockCount) {
            assert(!composedSet.empty() && "Decompose called with empty set");

            // holds projected sets
            std::vector<Representation> subspaceSets(decomposition.subspaces.size());

            // sort subspace indices by size of subspaces in descending order
            std::vector<std::size_t> subspaceIndices(decomposition.subspaces.size());
            for (std::size_t i = 0; i < subspaceIndices.size(); ++i) {
                subspaceIndices[i] = i;
            }
            std::sort(subspaceIndices.begin(), subspaceIndices.end(), [=](auto i, auto j) {
                return decomposition.subspaces[i] > decomposition.subspaces[j];
            });

            // copy subspaces for index shifting: when variables are eliminated from the workset
            // the indices of other variables need to be shifted, because the workset now has smaller dimension
            auto subspaceCopy = decomposition.subspaces;
            Representation workset = composedSet;
            for (auto i: subspaceIndices) {
                // get subspace set for subspace i and add clocks
                auto projectedSet = projectOnDimensions(workset, subspaceCopy[i]);
                if (decomposition.subspaceTypes[i] != DynamicType::discrete) {
                    subspaceSets[i] = addClocksAndInitial(projectedSet, clockCount);
                } else {
                    subspaceSets[i] = projectedSet;
                }
                // no more subspaces after this
                if (i == subspaceIndices.back()) break;
                // eliminate variables from workset
                HPolytope<typename Representation::NumberType> worksetPol;
                convert(workset, worksetPol);
                worksetPol = worksetPol.projectOut(subspaceCopy[i]);
                convert(worksetPol, workset);
                // shift indices
                for (auto j: subspaceIndices) {
                    if (j == i) continue;
                    for (auto &varIndex: subspaceCopy[j]) {
                        std::size_t shift = std::accumulate(subspaceCopy[i].begin(), subspaceCopy[i].end(), 0,
                                                            [=](std::size_t cur, std::size_t eliminatedIndex) {
                                                                return eliminatedIndex < varIndex ? cur + 1 : cur;
                                                            });
                        varIndex = varIndex - shift;
                    }
                }
            }
            return subspaceSets;
        }

        template<typename Representation>
        Representation
        projectOnDimensions(const Representation &composedSet, const std::vector<std::size_t> &dimensions) {
            using Number = typename Representation::NumberType;
            if (composedSet.dimension() == dimensions.size()) {
                return composedSet;
            }

            assert(!composedSet.empty() && "Projection called with empty set");
            std::vector<std::size_t> toProjectOut(composedSet.dimension() - dimensions.size());
            std::size_t i = 0;
            for (std::size_t dim = 0; dim < composedSet.dimension(); ++dim) {
                if (std::find(dimensions.begin(), dimensions.end(), dim) == dimensions.end()) {
                    toProjectOut[toProjectOut.size() - (i + 1)] = dim;
                    ++i;
                }
            }

            HPolytope<Number> composedPolytope;
            convert(composedSet, composedPolytope);
            composedPolytope = composedPolytope.projectOut(toProjectOut);
            Representation res;
            convert(composedPolytope, res);
            return res;
        }

        template<typename Representation>
        Representation addClocksAndInitial(const Representation &set, std::size_t clockCount) {
            using Number = typename Representation::NumberType;
            if (clockCount == 0) {
                return set;
            }

            matrix_t<Number> newMat = matrix_t<Number>::Zero(set.matrix().rows() + 2 * set.dimension() + 2 * clockCount,
                                                             2 * set.dimension() + clockCount);
            vector_t<Number> newVec = vector_t<Number>::Zero(
                    set.matrix().rows() + 2 * set.dimension() + 2 * clockCount);

            newMat.topLeftCorner(set.matrix().rows(), set.matrix().cols()) = set.matrix();
            newVec.head(set.vector().rows()) = set.vector();

            std::size_t nextRow = set.matrix().rows();
            for (std::size_t varIndex = 0; varIndex < set.dimension(); ++varIndex) {
                newMat(nextRow, varIndex) = 1;
                newMat(nextRow, set.dimension() + varIndex) = -1;
                newMat(nextRow + 1, varIndex) = -1;
                newMat(nextRow + 1, set.dimension() + varIndex) = 1;
                nextRow += 2;
            }
            for (std::size_t clockIndex = 0; clockIndex < clockCount; ++clockIndex) {
                newMat(nextRow, 2 * set.dimension() + clockIndex) = 1;
                newMat(nextRow + 1, 2 * set.dimension() + clockIndex) = -1;
                nextRow += 2;
            }

            HPolytope<Number> resPolytope(newMat, newVec);
            Representation res;
            convert(resPolytope, res);
            return res;
        }

        template<typename Representation>
        TimeInformation<typename Representation::NumberType>
        getClockValues(const Representation &segment, std::size_t clockCount) {
            using Number = typename Representation::NumberType;
            TimeInformation<Number> clockValues(clockCount);
            if (segment.empty()) {
                return clockValues;
            }

            for (std::size_t clockIndex = 0; clockIndex < clockCount; ++clockIndex) {
                vector_t<Number> clockDirection = vector_t<Number>::Zero(segment.dimension());
                clockDirection(segment.dimension() - clockCount + clockIndex) = 1;
                Number clockUpper = segment.evaluate(clockDirection).supportValue;
                Number clockLower = -1 * segment.evaluate(-1 * clockDirection).supportValue;
                clockValues.setTimeInterval(clockIndex, carl::Interval<Number>(clockLower, clockUpper));
            }
            return clockValues;
        }

        template<typename Representation>
        Representation intersectSegmentWithClock(
                const Representation &segment, TimeInformation<typename Representation::NumberType> clockValues,
                std::size_t clockCount) {
            using Number = typename Representation::NumberType;
            if (segment.empty()) {
                return segment;
            }
            if (clockCount == 0) {
                return segment;
            }
            matrix_t<Number> clockConstraint = matrix_t<Number>::Zero(2 * clockCount, segment.dimension());
            vector_t<Number> clockConstant(2 * clockCount);
            for (std::size_t clockIndex = 0; clockIndex < clockCount; ++clockIndex) {
                clockConstraint(2 * clockIndex, segment.dimension() - clockCount + clockIndex) = 1;
                clockConstraint(2 * clockIndex + 1, segment.dimension() - clockCount + clockIndex) = -1;
                clockConstant(2 * clockIndex) = clockValues.getTimeInterval(clockIndex).upper();
                clockConstant(2 * clockIndex + 1) = -1 * clockValues.getTimeInterval(clockIndex).lower();
            }
            return segment.intersectHalfspaces(clockConstraint, clockConstant);
        }

        template<typename Number>
        std::vector<Condition<Number>>
        collectBadStates(const HybridAutomaton<Number> *ha, const Location<Number> *loc) {
            auto badStates = ha->getGlobalBadStates();
            auto localBadState = ha->getLocalBadStates().find(loc);
            if (localBadState != ha->getLocalBadStates().end()) {
                badStates.push_back(localBadState->second);
            }
            return badStates;
        }

    }  // namespace detail

    template<typename Representation, typename Location>
    struct DecompositionalSegmentGen {
        using Number = typename Representation::NumberType;
        std::vector<typename boost::iterator_range<TreeIterator<ReachTreeNode<Representation, Location>>>::iterator> nodeIterators;
        std::vector<typename boost::iterator_range<TreeIterator<ReachTreeNode<Representation, Location>>>::iterator> nodeIteratorEndings;
        typename boost::iterator_range<TreeIterator<ReachTreeNode<Condition<Number>, Location>>>::iterator dependencyIterator;
        typename boost::iterator_range<TreeIterator<ReachTreeNode<Condition<Number>, Location>>>::iterator dependencyIteratorEnd;

        std::size_t segmentIndex = 0;
        Decomposition decomposition;
        std::size_t clockCount;
        Decomposition noDiscreteDecomp;
        // contains all non-discrete variables in one subspace and all discrete in the other
        Decomposition aggregatedDecomp{{std::vector<std::size_t>(), std::vector<std::size_t>()},
                                       {DynamicType::mixed,         DynamicType::discrete}};
        int discreteSubspace = -1;    // assume a single discrete subspaces (-1 if none)

        DecompositionalSegmentGen(std::vector<std::vector<ReachTreeNode<Representation, Location>>> &roots,
                                  std::vector<ReachTreeNode<Condition<Number>, Location>> &depRoots,
                                  Decomposition decomp, std::size_t clocks)
                : decomposition(decomp), clockCount(clocks) {
            // initialize iterators for subspace trees
            nodeIterators.resize(decomposition.subspaces.size());
            nodeIteratorEndings.resize(decomposition.subspaces.size());
            for (std::size_t subspace = 0; subspace < decomposition.subspaces.size(); ++subspace) {
                std::vector<ReachTreeNode<Representation, Location> *> subspaceRoots;
                for (auto &root: roots) {
                    subspaceRoots.push_back(&root[subspace]);
                }
                auto orderedRoots = preorder(subspaceRoots);
                nodeIterators[subspace] = orderedRoots.begin();
                nodeIteratorEndings[subspace] = orderedRoots.end();
                if (decomposition.subspaceTypes[subspace] != DynamicType::discrete) {
                    noDiscreteDecomp.subspaceTypes.push_back(decomposition.subspaceTypes[subspace]);
                    noDiscreteDecomp.subspaces.push_back(std::vector<std::size_t>());
                    for (auto varIndex: decomposition.subspaces[subspace]) {
                        noDiscreteDecomp.subspaces.back().push_back(
                                getVarIndexWithoutDiscrete(varIndex, decomposition));
                        aggregatedDecomp.subspaces[0].push_back(varIndex);
                    }
                } else {
                    assert(aggregatedDecomp.subspaces[1].empty() && "Separate discrete subspaces not supported");
                    aggregatedDecomp.subspaces[1] = decomposition.subspaces[subspace];
                    discreteSubspace = subspace;
                }
            }
            // initialize iterator for dependency tree
            auto orderedDep = preorder(depRoots);
            dependencyIterator = orderedDep.begin();
            dependencyIteratorEnd = orderedDep.end();
        }

        void incrementNodes() {
            // reset index to 0 for next nodes in trees and increment all iterators
            segmentIndex = 0;
            for (std::size_t subspace = 0; subspace < nodeIterators.size(); ++subspace) {
                ++nodeIterators[subspace];
            }
            ++dependencyIterator;
        }

        // generate next segment if it exists
        std::optional<HPolytope<Number>> next() {
            // reached end of tree nodes. All trees have the exact same structure, so it
            // suffices to only compare the first node iterator.
            if (nodeIterators[0] == nodeIteratorEndings[0]) {
                return std::nullopt;
            }
            assert(dependencyIterator != dependencyIteratorEnd);
            // collect next subspace sets in non-discrete subspaces to compose segment
            std::vector<HPolytope<Number>> toCompose;
            for (std::size_t subspace = 0; subspace < decomposition.subspaces.size(); ++subspace) {
                assert(nodeIterators[subspace] != nodeIteratorEndings[subspace]);
                if (decomposition.subspaceTypes[subspace] != DynamicType::discrete) {
                    if (isSegmentedSubspace(decomposition.subspaceTypes[subspace])) {
                        if (segmentIndex >= nodeIterators[subspace]->getFlowpipe().size()) {
                            incrementNodes();
                            return next();
                        }
                        toCompose.push_back(std::visit(genericConvertAndGetVisitor<HPolytope<Number>>(),
                                                       nodeIterators[subspace]->getFlowpipe()[segmentIndex].getSet()));
                    } else {
                        if (nodeIterators[subspace]->getFlowpipe().size() == 0) {
                            // this shouldn't happen (flowpipe computation was skipped, so initial set was empty), but check just in case.
                            incrementNodes();
                            return next();
                        }
                        toCompose.push_back(std::visit(genericConvertAndGetVisitor<HPolytope<Number>>(),
                                                       nodeIterators[subspace]->getFlowpipe()[0].getSet()));
                    }
                }
            }
            // compose with dependency
            HPolytope<Number> composed = detail::composeSubspaces(toCompose, dependencyIterator->getInitialSet(),
                                                                  noDiscreteDecomp, clockCount);

            // finally we need to add the discrete subspaces
            // use composition function with two subspaces (all non-discrete and all discrete) without clocks (they are already projected out)
            if (false && discreteSubspace >= 0) {
                auto discreteSet = std::visit(genericConvertAndGetVisitor<HPolytope<Number>>(),
                                              nodeIterators[discreteSubspace]->getFlowpipe()[0].getSet());
                composed = detail::composeSubspaces<HPolytope<Number>>({composed, discreteSet},
                                                                       Condition<Number>(ConstraintSetT<Number>()),
                                                                       aggregatedDecomp, 0);
            }
            // increase segment index
            // if no subspace is segmented (linear or affine) then one segment per node is always enough. Otherwise, increase segmentIndex
            if (!std::any_of(decomposition.subspaceTypes.begin(), decomposition.subspaceTypes.end(),
                             [](const auto &dynamic) { return isSegmentedSubspace(dynamic); })) {
                incrementNodes();
            } else {
                ++segmentIndex;
            }
            return composed;
        }
    };

}  // namespace hypro
