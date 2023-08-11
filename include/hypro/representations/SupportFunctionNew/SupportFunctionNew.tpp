/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "SupportFunctionNew.h"

namespace hypro {

/***************************************************************************
 * Constructors
 **************************************************************************/

    template<typename Number, typename Converter, typename Setting>
    SupportFunctionNewT<Number, Converter, Setting>::SupportFunctionNewT() {}

// copy constructor
    template<typename Number, typename Converter, typename Setting>
    SupportFunctionNewT<Number, Converter, Setting>::SupportFunctionNewT(
            const SupportFunctionNewT<Number, Converter, Setting> &orig)
            : GeometricObjectBase(orig), mRoot(orig.getRoot()) {
        if (orig.isTemplateSet()) {
            mMatrix = orig.matrix();
            mVector = orig.vector();
            mTemplateSet = true;
        }
    }

// move constructor
    template<typename Number, typename Converter, typename Setting>
    SupportFunctionNewT<Number, Converter, Setting>::SupportFunctionNewT(
            SupportFunctionNewT<Number, Converter, Setting> &&orig)
            : mRoot(std::move(orig.getRoot())) {
        if (orig.isTemplateSet()) {
            mMatrix = std::move(orig.matrix());
            mVector = std::move(orig.vector());
            mTemplateSet = true;
        }
        orig.clear();
    }

// settings constructor
    template<typename Number, typename Converter, typename Setting>
    template<typename SettingRhs, carl::DisableIf<std::is_same<Setting, SettingRhs>>>
    SupportFunctionNewT<Number, Converter, Setting>::SupportFunctionNewT(
            const SupportFunctionNewT<Number, Converter, SettingRhs> &orig) {
        if (orig.getRoot() == nullptr) {
            mRoot = nullptr;
        } else {
            using RGNPtr = RootGrowNode<Number, Converter, SettingRhs> *;
            using SharedRGNPtr = std::shared_ptr<RootGrowNode<Number, Converter, Setting>>;

            // Do nothing
            std::function<void(RGNPtr)> doNothing = [](RGNPtr) {};

            // Convert settings of leaves
            std::function<SharedRGNPtr(RGNPtr)> convertLeaves =
                    [](RGNPtr n) -> SharedRGNPtr {
                        return convertSettings<Number, Converter, Setting, SettingRhs>(n);
                    };

            // Convert settings of operations, then add their children, then add the dimension
            std::function<SharedRGNPtr(RGNPtr, std::vector<SharedRGNPtr> &)> convertOps =
                    [](RGNPtr n, std::vector<SharedRGNPtr> &v) -> SharedRGNPtr {
                        SharedRGNPtr convertedOp = convertSettings<Number, Converter, Setting, SettingRhs>(n);
                        for (auto &child: v) {
                            convertedOp->addToChildren(child);
                        }
                        convertedOp->setDimension(v.front()->getDimension());
                        return convertedOp;
                    };

            mRoot = orig.traverse(std::move(doNothing), std::move(convertLeaves), std::move(convertOps));
        }
    }

// constructor for adding a new node
    template<typename Number, typename Converter, typename Setting>
    SupportFunctionNewT<Number, Converter, Setting>::SupportFunctionNewT(
            const std::shared_ptr<RootGrowNode<Number, Converter, Setting>> &root)
            : mRoot(root) {}

// Halfspace constructor
    template<typename Number, typename Converter, typename Setting>
    SupportFunctionNewT<Number, Converter, Setting>::SupportFunctionNewT(const Halfspace<Number> &hspace)
            : mMatrix(hspace.matrix()), mVector(hspace.vector()), mTemplateSet(true) {
        Halfspace<Number> tmp(hspace);
        mRoot = std::make_shared<Leaf<Number, Converter, Setting, Halfspace<Number>>>(tmp);
    }

// Generic Leaf constructor
    template<typename Number, typename Converter, typename Setting>
    template<typename Representation>
    SupportFunctionNewT<Number, Converter, Setting>::SupportFunctionNewT(const Representation &r) {
        DEBUG("hypro.representations", "SFN generic leaf constr, got r:\n"
                << r);
        if (r.empty()) {
            mRoot = std::make_shared<Leaf<Number, Converter, Setting, typename Converter::Box>>(
                    std::make_shared<typename Converter::Box>(Converter::Box::Empty(r.dimension())));
        } else {
            std::tuple<bool, std::vector<carl::Interval<Number>>> areArgsBox = isBox(r.matrix(), r.vector());
            if (std::get<0>(areArgsBox) && Setting::DETECT_BOX) {
                mRoot = std::make_shared<Leaf<Number, Converter, Setting, typename Converter::Box>>(
                        std::make_shared<typename Converter::Box>(std::get<1>(areArgsBox)));
            } else {
                using HPolyWithOptimizerCaching = HPolytopeT<Number, Converter, HPolytopeOptimizerCaching>;
                mRoot = std::make_shared<Leaf<Number, Converter, Setting, HPolyWithOptimizerCaching>>(
                        std::make_shared<HPolyWithOptimizerCaching>(r.matrix(), r.vector()));
                // mRoot = std::make_shared<Leaf<Number, Converter, Setting, Representation>>( std::make_shared<Representation>(tmp) );
            }
        }
        assert(mRoot != nullptr);
    }

// Matrix vector constructor
    template<typename Number, typename Converter, typename Setting>
    SupportFunctionNewT<Number, Converter, Setting>::SupportFunctionNewT(const matrix_t<Number> &mat,
                                                                         const vector_t<Number> &vec) {
        INFO("hypro.representations", "SFN mat-vec-constr: mat: \n"
                << mat << " and vec: \n"
                << vec);
        std::tuple<bool, std::vector<carl::Interval<Number>>> areArgsBox = isBox(mat, vec);
        if (Setting::DETECT_BOX && std::get<0>(areArgsBox)) {
            if (std::get<1>(areArgsBox).size() == 0) {
                mRoot = std::make_shared<Leaf<Number, Converter, Setting, typename Converter::Box>>(
                        std::make_shared<typename Converter::Box>(Converter::Box::Empty()));
                assert(false);
            } else {
                INFO("hypro.representations", "SFN mat-vec-constr: constraints were box!")
                mRoot = std::make_shared<Leaf<Number, Converter, Setting, typename Converter::Box>>(
                        std::make_shared<typename Converter::Box>(std::get<1>(areArgsBox)));
            }
        } else {
            INFO("hypro.representations", "SFN mat-vec-constr: constraints were tpoly!")
            using HPolyWithOptimizerCaching = HPolytopeT<Number, Converter, HPolytopeOptimizerCaching>;
            mRoot = std::make_shared<Leaf<Number, Converter, Setting, HPolyWithOptimizerCaching>>(
                    std::make_shared<HPolyWithOptimizerCaching>(mat, vec));
        }
        assert(mRoot != nullptr);
        INFO("hypro.representations", "SFN mat-vec-constr: leaf is:\n"
                << *mRoot);
        mMatrix = mat;
        mVector = vec;
        mTemplateSet = true;
    }

// Halfspace vector constructor
/*TODO: Optimize hspace constructor with isBox(), this ctor is never used but needed for compilation */
    template<typename Number, typename Converter, typename Setting>
    SupportFunctionNewT<Number, Converter, Setting>::SupportFunctionNewT(
            const std::vector<Halfspace<Number>> &hspaces) {
        using HPolyWithOptimizerCaching = HPolytopeT<Number, Converter, HPolytopeOptimizerCaching>;
        mRoot = std::make_shared<Leaf<Number, Converter, Setting, HPolyWithOptimizerCaching>>(
                std::make_shared<HPolyWithOptimizerCaching>(hspaces));
    }

/***************************************************************************
 * Getters & setters
 **************************************************************************/

    template<typename Number, typename Converter, typename Setting>
    void SupportFunctionNewT<Number, Converter, Setting>::addOperation(
            RootGrowNode<Number, Converter, Setting> *newRoot) const {
        assert(newRoot->getOriginCount() == 1);
        if (newRoot) {
            newRoot->addToChildren(mRoot);
            assert(newRoot->getChildren().size() == 1);
        }
    }

    template<typename Number, typename Converter, typename Setting>
    void
    SupportFunctionNewT<Number, Converter, Setting>::addOperation(RootGrowNode<Number, Converter, Setting> *newRoot,
                                                                  const std::vector<SupportFunctionNewT<Number, Converter, Setting>> &rhs) const {
        assert(newRoot != nullptr);
        assert(newRoot->getOriginCount() <= rhs.size() + newRoot->getChildren().size() + 1);
        newRoot->addToChildren(mRoot);
        for (const auto &sf: rhs) {
            newRoot->addToChildren(sf.getRoot());
        }
        assert(newRoot->getChildren().size() >= newRoot->getOriginCount());
    }

/***************************************************************************
 * Tree Traversal
 **************************************************************************/

// When Result type and Param type = void
    template<typename Number, typename Converter, typename Setting>
    void SupportFunctionNewT<Number, Converter, Setting>::traverse(
            std::function<void(RootGrowNode<Number, Converter, Setting> *)> &&transform,
            std::function<void(RootGrowNode<Number, Converter, Setting> *)> &&compute,
            std::function<void(RootGrowNode<Number, Converter, Setting> *)> &&aggregate) const {
        std::function<Parameters<Dummy>(RootGrowNode<Number, Converter, Setting> *, Parameters<Dummy> &)> tNotVoid =
                [&](RootGrowNode<Number, Converter, Setting> *n, Parameters<Dummy> &) -> Parameters<Dummy> {
                    transform(n);
                    return Parameters<Dummy>(Dummy());
                };
        std::function<Parameters<Dummy>(RootGrowNode<Number, Converter, Setting> *, Parameters<Dummy> &)> cNotVoid =
                [&](RootGrowNode<Number, Converter, Setting> *n, Parameters<Dummy> &) -> Parameters<Dummy> {
                    compute(n);
                    return Parameters<Dummy>(Dummy());
                };
        std::function<Parameters<Dummy>(RootGrowNode<Number, Converter, Setting> *, std::vector<Parameters<Dummy>> &,
                                        Parameters<Dummy> &)> aNotVoid =
                [&](RootGrowNode<Number, Converter, Setting> *n, std::vector<Parameters<Dummy>> &,
                    Parameters<Dummy> &) -> Parameters<Dummy> {
                    aggregate(n);
                    return Parameters<Dummy>(Dummy());
                };
        Parameters<Dummy> noInitParams = Parameters<Dummy>(Dummy());
        traverse(std::move(tNotVoid), std::move(cNotVoid), std::move(aNotVoid), noInitParams);
    }

// When Param type = void, but Result type not
    template<typename Number, typename Converter, typename Setting>
    template<typename Result>
    Result SupportFunctionNewT<Number, Converter, Setting>::traverse(
            std::function<void(RootGrowNode<Number, Converter, Setting> *)> &&transform,
            std::function<Result(RootGrowNode<Number, Converter, Setting> *)> &&compute,
            std::function<Result(RootGrowNode<Number, Converter, Setting> *,
                                 std::vector<Result> &)> &&aggregate) const {
        std::function<Parameters<Dummy>(RootGrowNode<Number, Converter, Setting> *, Parameters<Dummy> &)> tNotVoid =
                [&](RootGrowNode<Number, Converter, Setting> *n, Parameters<Dummy> &) -> Parameters<Dummy> {
                    transform(n);
                    return Parameters<Dummy>(Dummy());
                };
        std::function<Result(RootGrowNode<Number, Converter, Setting> * , Parameters<Dummy> & )> cNotVoid =
                [&](RootGrowNode<Number, Converter, Setting> *n, Parameters<Dummy> &) -> Result {
                    return compute(n);
                };
        std::function<Result(RootGrowNode<Number, Converter, Setting> * , std::vector<Result> & ,
                             Parameters<Dummy> & )> aWithParams =
                [&](RootGrowNode<Number, Converter, Setting> *n, std::vector<Result> &v,
                    Parameters<Dummy> &) -> Result {
                    return aggregate(n, v);
                };
        Parameters<Dummy> noInitParams = Parameters<Dummy>(Dummy());
        return traverse(std::move(tNotVoid), std::move(cNotVoid), std::move(aWithParams), std::move(noInitParams));
    }

// When Result type = void, but Param type not
    template<typename Number, typename Converter, typename Setting>
    template<typename... Rargs>
    void SupportFunctionNewT<Number, Converter, Setting>::traverse(
            std::function<Parameters<Rargs...>(RootGrowNode<Number, Converter, Setting> *,
                                               Parameters<Rargs...> &)> &&transform,
            std::function<void(RootGrowNode<Number, Converter, Setting> *, Parameters<Rargs...> &)> &&compute,
            std::function<void(RootGrowNode<Number, Converter, Setting> *, Parameters<Rargs...> &)> &&aggregate,
            Parameters<Rargs...> &&initParams) const {
        std::function<Parameters<Dummy>(RootGrowNode<Number, Converter, Setting> *, Parameters<Rargs...> &)> cNotVoid =
                [&](RootGrowNode<Number, Converter, Setting> *n, Parameters<Rargs...> &p) -> Parameters<Dummy> {
                    compute(n, p);
                    return Parameters<Dummy>(Dummy());
                };
        std::function<Parameters<Dummy>(RootGrowNode<Number, Converter, Setting> *, std::vector<Parameters<Dummy>> &,
                                        Parameters<Rargs...> &)> aNotVoid =
                [&](RootGrowNode<Number, Converter, Setting> *n, std::vector<Parameters<Dummy>> &v,
                    Parameters<Rargs...> &p) -> Parameters<Dummy> {
                    aggregate(n, p);
                    return Parameters<Dummy>(Dummy());
                };
        traverse(std::move(transform), std::move(cNotVoid), std::move(aNotVoid), initParams);
    }

// Actual traverse function. Result type and Param type not void
    template<typename Number, typename Converter, typename Setting>
    template<typename Result, typename... Rargs>
    Result SupportFunctionNewT<Number, Converter, Setting>::traverse(
            std::function<Parameters<Rargs...>(RootGrowNode<Number, Converter, Setting> *,
                                               Parameters<Rargs...> &)> &&transform,
            std::function<Result(RootGrowNode<Number, Converter, Setting> *, Parameters<Rargs...> &)> &&compute,
            std::function<Result(RootGrowNode<Number, Converter, Setting> *, std::vector<Result> &,
                                 Parameters<Rargs...> &)> &&aggregate,
            Parameters<Rargs...> &&initParams) const {
        // Usings
        using Node = RootGrowNode<Number, Converter, Setting> *;
        using Param = Parameters<Rargs...>;
        using Res = Result;

        // Prepare Stacks
        std::vector<Node> callStack;
        std::vector<Param> paramStack;
        std::vector<std::pair<int, std::vector<Res>>> resultStack;
        callStack.push_back(mRoot.get());
        paramStack.push_back(initParams);
        resultStack.push_back(std::make_pair(-1, std::vector<Res>()));

        // Traversal loop
        while (!callStack.empty()) {
            Node cur = callStack.back();
            Param currentParam = paramStack.back();

            if (cur->getOriginCount() == 0) {
                std::pair<int, std::vector<Res>> currentResult = resultStack.back();

                // If leaf and end of stack is reached
                if (currentResult.first == -1) {
                    return std::apply(compute, std::forward_as_tuple(cur, currentParam));

                    // If leaf and not end of stack is reached
                } else {
                    resultStack.at(currentResult.first).second.push_back(
                            std::apply(compute, std::forward_as_tuple(cur, currentParam)));
                }

                // delete result frame and close recursive call
                callStack.pop_back();
                paramStack.pop_back();
                resultStack.pop_back();

            } else {
                // If enough arguments for operation of node and #arguments != 0
                if (resultStack.back().second.size() >= cur->getOriginCount()) {
                    Res accumulatedResult = std::apply(aggregate, std::forward_as_tuple(cur, resultStack.back().second,
                                                                                        currentParam));

                    // we reached the top, exit
                    if (resultStack.back().first == -1) {
                        return accumulatedResult;
                    }

                    // forward result.
                    resultStack.at(resultStack.back().first).second.emplace_back(accumulatedResult);

                    // delete result frame and close recursive call
                    callStack.pop_back();
                    paramStack.pop_back();
                    resultStack.pop_back();

                    // Every other case (recursive call)
                } else {
                    // here we create the new stack levels.
                    std::size_t callingFrame = callStack.size() - 1;
                    for (auto &c: cur->rGetChildren()) {
                        callStack.push_back(c.get());
                        paramStack.push_back(std::apply(transform, std::forward_as_tuple(cur, currentParam)));
                        resultStack.push_back(std::make_pair(callingFrame, std::vector<Res>()));
                    }
                }
            }
        }
        std::cout << "THIS SHOULD NOT HAPPEN." << std::endl;
        return Res();
    }

/***************************************************************************
 * Evaluation
 **************************************************************************/

    template<typename Number, typename Converter, typename Setting>
    bool SupportFunctionNewT<Number, Converter, Setting>::empty() const {
        if (mRoot == nullptr) return true;

        if (mEmptyState != SETSTATE::UNKNOWN) return (mEmptyState == SETSTATE::EMPTY);

        // first function - parameters are not transformed
        std::function<void(RootGrowNode<Number, Converter, Setting> *)> doNothing = [](
                RootGrowNode<Number, Converter, Setting> *) {};

        // if leaf - call empty function of representation
        std::function<bool(RootGrowNode<Number, Converter, Setting> *)> leafEmpty =
                [](RootGrowNode<Number, Converter, Setting> *n) -> bool {
                    return n->empty();
                };

        // if not leaf - not empty if all children not empty
        std::function<bool(RootGrowNode<Number, Converter, Setting> *, std::vector<bool> &)> childrenEmpty =
                [](RootGrowNode<Number, Converter, Setting> *n, std::vector<bool> &childrenEmpty) -> bool {
                    return n->empty(childrenEmpty);
                };

        mEmptyState = traverse(std::move(doNothing), std::move(leafEmpty), std::move(childrenEmpty)) ? SETSTATE::EMPTY
                                                                                                     : SETSTATE::NONEMPTY;
        assert(mEmptyState != SETSTATE::UNKNOWN);
        return (mEmptyState == SETSTATE::EMPTY);
    }

    template<typename Number, typename Converter, typename Setting>
    Number SupportFunctionNewT<Number, Converter, Setting>::supremum() const {
        if (mRoot == nullptr) return Number(0);

        // first function - parameters are not transformed
        std::function<void(RootGrowNode<Number, Converter, Setting> *)> doNothing = [](
                RootGrowNode<Number, Converter, Setting> *) {};

        // leaves compute the supremum point
        std::function<Point<Number>(RootGrowNode<Number, Converter, Setting> *)> supremumPointLeaf =
                [](RootGrowNode<Number, Converter, Setting> *n) -> Point<Number> {
                    assert(n->getType() == SFNEW_TYPE::LEAF);
                    return n->supremumPoint();
                };

        // operations call their own supremum functions
        std::function<Point<Number>(RootGrowNode<Number, Converter, Setting> *,
                                    std::vector<Point<Number>> &)> supremumPointOp =
                [](RootGrowNode<Number, Converter, Setting> *n, std::vector<Point<Number>> &v) -> Point<Number> {
                    return n->supremumPoint(v);
                };

        Point<Number> res = traverse(std::move(doNothing), std::move(supremumPointLeaf), std::move(supremumPointOp));
        Number resNorm = Point<Number>::inftyNorm(res);
        return resNorm;
    }

    template<typename Number, typename Converter, typename Setting>
    std::vector<Point<Number>>
    SupportFunctionNewT<Number, Converter, Setting>::vertices(const matrix_t<Number> &additionalDirections) const {
        std::vector<vector_t<Number>> additionalDirectionVector;
        for (unsigned rowIndex = 0; rowIndex < additionalDirections.rows(); ++rowIndex) {
            additionalDirectionVector.push_back(vector_t<Number>(additionalDirections.row(rowIndex)));
        }
        auto tmp = Converter::toHPolytope(*this, additionalDirectionVector);
        return tmp.vertices();
    }

    template<typename Number, typename Converter, typename Setting>
    EvaluationResult<Number>
    SupportFunctionNewT<Number, Converter, Setting>::evaluate(const vector_t<Number> &_direction, bool useExact) const {
        if (mRoot == nullptr) {
            return EvaluationResult<Number>();
        }
        if (_direction == vector_t<Number>::Zero(_direction.rows())) {
            return EvaluationResult<Number>(SOLUTION::INFTY);
        }
        matrix_t<Number> dirAsMatrix = matrix_t<Number>::Zero(1, _direction.rows());
        dirAsMatrix << _direction.transpose();
        return multiEvaluate(dirAsMatrix, useExact).front();
    }

    template<typename Number, typename Converter, typename Setting>
    std::vector<EvaluationResult<Number>>
    SupportFunctionNewT<Number, Converter, Setting>::multiEvaluate(const matrix_t<Number> &_directions,
                                                                   bool useExact) const {
        if (mRoot == nullptr) {
            return std::vector<EvaluationResult<Number>>();
        }
        if (_directions.isApprox(matrix_t<Number>::Zero(_directions.rows(), _directions.cols()))) {
            return std::vector<EvaluationResult<Number>>();
        }

        using Matrix = Parameters<matrix_t<Number>>;
        using RGNPtr = RootGrowNode<Number, Converter, Setting> *;
        using EvalVec = std::vector<EvaluationResult<Number>>;

        // Define lambda functions that will call the functions transform, compute and aggregate dependent on the current node type
        std::function<Matrix(RGNPtr, Matrix &)> trans =
                [&](RGNPtr n, Matrix &param) -> Matrix {
                    return n->transform(std::get<0>(param.args));
                };

        std::function<EvalVec(RGNPtr, Matrix &)> comp =
                [&](RGNPtr n, Matrix &dir) -> EvalVec {
                    return n->compute(std::get<0>(dir.args), useExact);
                };

        std::function<EvalVec(RGNPtr, std::vector<EvalVec> &, Matrix &)> agg =
                [&](RGNPtr n, std::vector<EvalVec> &resultStackBack, Matrix &currentParam) -> EvalVec {
                    return n->aggregate(resultStackBack, std::get<0>(currentParam.args));
                };

        // Traverse the underlying SupportFunctionNewT with the three functions and given directions as initial parameters.
        Parameters<matrix_t<Number>> params = Parameters<matrix_t<Number>>(_directions);
        return traverse(std::move(trans), std::move(comp), std::move(agg), std::move(params));
    }

// Find out if tree has at least one trafoOp and if yes, update the linTrafoParameters
    template<typename Number, typename Converter, typename Setting>
    bool SupportFunctionNewT<Number, Converter, Setting>::hasTrafo(
            std::shared_ptr<const LinTrafoParameters<Number, Setting>> &ltParam, const matrix_t<Number> &A,
            const vector_t<Number> &b) const {
        if (mRoot == nullptr) return false;

        // first function - parameters are not transformed
        std::function<void(RootGrowNode<Number, Converter, Setting> *)> doNothing = [](
                RootGrowNode<Number, Converter, Setting> *) {};

        // second function - leaves cannot be operations
        std::function<bool(RootGrowNode<Number, Converter, Setting> *)> leavesAreNotTrafoOps =
                [](RootGrowNode<Number, Converter, Setting> *) -> bool {
                    return false;
                };

        // third function - if current node type or given result is TRAFO, then update and return true
        std::function<bool(RootGrowNode<Number, Converter, Setting> *, std::vector<bool> &)> checkAndUpdateTrafo =
                [&](RootGrowNode<Number, Converter, Setting> *n, std::vector<bool> &haveSubtreesTrafo) -> bool {
                    if (n->getType() == SFNEW_TYPE::TRAFO) {
                        return static_cast<TrafoOp<Number, Converter, Setting> *>( n )->hasTrafo(ltParam, A, b);
                    } else {
                        for (const auto &hasSubTreeTrafo: haveSubtreesTrafo) {
                            if (hasSubTreeTrafo) {
                                return true;
                            }
                        }
                    }
                    return false;
                };

        return traverse(std::move(doNothing), std::move(leavesAreNotTrafoOps), std::move(checkAndUpdateTrafo));
    }

/***************************************************************************
 * General Interface
 **************************************************************************/

    template<typename Number, typename Converter, typename Setting>
    std::size_t SupportFunctionNewT<Number, Converter, Setting>::dimension() const {
        if (mRoot == nullptr) return std::size_t(0);
        return mRoot->getDimension();
    }

    template<typename Number, typename Converter, typename Setting>
    matrix_t<Number> SupportFunctionNewT<Number, Converter, Setting>::matrix() const {
        if (mRoot == nullptr) return matrix_t<Number>::Zero(0, 0);
        if (!mTemplateSet) {
            evaluateTemplate();
        }
        return mMatrix;
    }

    template<typename Number, typename Converter, typename Setting>
    vector_t<Number> SupportFunctionNewT<Number, Converter, Setting>::vector() const {
        if (mRoot == nullptr) return vector_t<Number>::Zero(0);
        if (!mTemplateSet) {
            evaluateTemplate();
        }
        return mVector;
    }

// template<typename Number, typename Converter, typename Setting>
// void SupportFunctionNewT<Number,Converter,Setting>::removeRedundancy() {
//	// Support functions are already non-redundant (Polytope support functions are made non-redundant upon construction).
// }

    template<typename Number, typename Converter, typename Setting>
    std::size_t SupportFunctionNewT<Number, Converter, Setting>::size() const {
        if (mRoot == nullptr) return std::size_t(0);

        // first function - parameters are not transformed
        std::function<void(RootGrowNode<Number, Converter, Setting> *)> doNothing = [](
                RootGrowNode<Number, Converter, Setting> *) {};

        // leaves compute their storage size
        std::function<std::size_t(RootGrowNode<Number, Converter, Setting> *)> sizeofLeaf =
                [](RootGrowNode<Number, Converter, Setting> *n) -> std::size_t {
                    assert(n->getType() == SFNEW_TYPE::LEAF);
                    return sizeof(*n);
                };

        // operations compute their storage size and add it to the ones of their children
        std::function<std::size_t(RootGrowNode<Number, Converter, Setting> *, std::vector<std::size_t> &)> sizeofOp =
                [](RootGrowNode<Number, Converter, Setting> *n, std::vector<std::size_t> &v) -> std::size_t {
                    std::size_t storage = 0;
                    for (const auto &childStorageSize: v) {
                        storage += childStorageSize;
                    }
                    return storage + sizeof(*n);
                };

        return traverse(std::move(doNothing), std::move(sizeofLeaf), std::move(sizeofOp));
    }

// template<typename Number, typename Converter, typename Setting>
// const SupportFunctionNewT<Number,Converter,Setting>& SupportFunctionNewT<Number,Converter,Setting>::reduceNumberRepresentation() { }

    template<typename Number, typename Converter, typename Setting>
    std::pair<CONTAINMENT, SupportFunctionNewT<Number, Converter, Setting>>
    SupportFunctionNewT<Number, Converter, Setting>::satisfiesHalfspace(const Halfspace<Number> &rhs) const {
        TRACE("hypro.representations.supportFunctionNew", "Halfspace: " << rhs);
        // std::cout << "SFN::satisfiesHalfspace, this mat: \n" << this->matrix() << "vector: \n" << this->vector() << "halfspace: \n" << rhs << std::endl;
        if (mRoot == nullptr) {
            return std::make_pair(CONTAINMENT::BOT, *this);
        }
        if (this->empty()) {
            return std::make_pair(CONTAINMENT::NO, *this);
        }
        // Check for emptiness not needed here since satisfiesHalfspace() is only called via satisfiedHalfspaces(), which already checks emptiness
        bool limiting = false;
        EvaluationResult<Number> planeEvalRes = this->evaluate(rhs.normal(), false);
        // std::cout << "SFN::satisfiesHalfspace, planeEvalRes: " << planeEvalRes << " rhs offset: " << rhs.offset() << std::endl;
        if (planeEvalRes.errorCode == SOLUTION::INFEAS) {
            // std::cout << "SFN::satisfiesHalfspace, Is infeasible (should not happen)." << std::endl;
            ////std::cout << "Set is (Hpoly): " << std::endl << Converter::toHPolytope(*this) << std::endl;
            // assert(Converter::toHPolytope(*this).empty());
            return std::make_pair(CONTAINMENT::NO, *this);
        } else if (planeEvalRes.supportValue > rhs.offset()) {
            // std::cout << "SFN::satisfiesHalfspace, Object will be limited. " << std::endl;
            //  the actual object will be limited by the new plane
            limiting = true;
            // //std::cout << "evaluate(" << convert<Number,double>(-(_mat.row(rowI))) << ") <=  " << -(_vec(rowI)) << ": " << this->evaluate(-(_mat.row(rowI))).supportValue << " <= " << -(_vec(rowI)) << std::endl;
            // //std::cout << __func__ <<  ": Limiting plane " << convert<Number,double>(_mat.row(rowI)).transpose() << " <= " << toDouble(_vec(rowI)) << std::endl;
            if (this->evaluate(-(rhs.normal()), false).supportValue < -(rhs.offset())) {
                // the object lies fully outside one of the planes -> return false
                // std::cout << "SFN::satisfiesHalfspace, fullyOutside " << std::endl;
                return std::make_pair(CONTAINMENT::NO, this->intersectHalfspace(rhs));
            }
        }
        if (limiting) {
            // std::cout << "SFN::satisfiesHalfspace, partial containment" << std::endl;
            return std::make_pair(CONTAINMENT::PARTIAL, this->intersectHalfspace(rhs));
        } else {
            // std::cout << "SFN::satisfiesHalfspace, full containment" << std::endl;
            return std::make_pair(CONTAINMENT::FULL, *this);
        }
    }

    template<typename Number, typename Converter, typename Setting>
    std::pair<CONTAINMENT, SupportFunctionNewT<Number, Converter, Setting>>
    SupportFunctionNewT<Number, Converter, Setting>::satisfiesHalfspaces(const matrix_t<Number> &_mat,
                                                                         const vector_t<Number> &_vec) const {
        DEBUG("hypro.representations.supportFunctionNew", "Matrix: " << _mat << std::endl
                                                                     << " <= " << _vec);
        if (mRoot == nullptr) {  // TODO: What is this case referring to?
            return std::make_pair(CONTAINMENT::BOT, *this);
        }
        if (this->empty()) {
            return std::make_pair(CONTAINMENT::NO, *this);
        }
        if (_mat.rows() == 0) {
            return std::make_pair(CONTAINMENT::FULL, *this);
        }

        assert(_mat.rows() == _vec.rows());
        assert(_mat.cols() == Eigen::Index(dimension()) || this->empty());
        if (_mat.rows() == 1 && _vec.rows() == 1) {
            return satisfiesHalfspace(Halfspace<Number>(vector_t<Number>(_mat.row(0)), _vec(0)));
        }

        // auto res = this->intersectHalfspaces( _mat, _vec );
        // CONTAINMENT empty = res.empty() ? CONTAINMENT::NO : CONTAINMENT::YES;
        // return std::make_pair( empty, res );

        std::vector<unsigned> limitingPlanes;
        for (unsigned rowI = 0; rowI < _mat.rows(); ++rowI) {
            DEBUG("hypro.representations.supportFunctionNew", "Evaluate against plane " << rowI);
            EvaluationResult<Number> planeEvalRes = this->evaluate(_mat.row(rowI), false);
            DEBUG("hypro.representations.supportFunctionNew", "Return from evaluate.");
            if (planeEvalRes.errorCode == SOLUTION::INFEAS) {
                TRACE("hypro.representations.supportFunctionNew", "Is infeasible (should not happen).");
                // std::cout << "SFN::satisfiesHalfspaces, infeas" << std::endl;
                return std::make_pair(CONTAINMENT::NO, *this);
                // return std::make_pair(CONTAINMENT::NO, this->intersectHalfspaces(_mat,_vec) );
            } else if (!carl::AlmostEqual2sComplement(planeEvalRes.supportValue, _vec(rowI), 2) &&
                       planeEvalRes.supportValue > _vec(rowI)) {
                TRACE("hypro.representations.supportFunctionNew",
                      "Object will be limited, as " << planeEvalRes.supportValue << " > " << _vec(rowI));
                // std::cout << "SFN::satisfiesHalfspaces, limited" << std::endl;
                //  the actual object will be limited by the new plane
                limitingPlanes.push_back(rowI);
                Number invDirVal = this->evaluate(-(_mat.row(rowI)), true).supportValue;
                // TRACE("hypro.representations.supportFunctionNew", "evaluate(" << -(_mat.row(rowI)) << ") <=  " << -(_vec(rowI)) << ": " << invDirVal << " <= " << -(_vec(rowI)));
                // TRACE("hypro.representations.supportFunctionNew", ": Limiting plane " << _mat.row(rowI).transpose() << " <= " << toDouble(_vec(rowI)));
                if (-invDirVal > _vec(rowI)) {
                    return std::make_pair(CONTAINMENT::NO, this->intersectHalfspaces(_mat, _vec));
                }
                // if ( !carl::AlmostEqual2sComplement( invDirVal, Number( -( _vec( rowI ) ) ), 2 ) && -invDirVal > _vec( rowI ) ) {
                //	// exact verification in case the values are close to each other
                //	if ( carl::AlmostEqual2sComplement( Number( -invDirVal ), planeEvalRes.supportValue, 16 ) ) {
                //		EvaluationResult<Number> secndPosEval = this->evaluate( _mat.row( rowI ), true );
                //		if ( secndPosEval.supportValue > _vec( rowI ) ) {
                //			EvaluationResult<Number> secndNegEval = this->evaluate( -( _mat.row( rowI ) ), true );
                //			if ( secndNegEval.supportValue < -( _vec( rowI ) ) ) {
                //				TRACE( "hypro.representations.supportFunctionNew", "fullyOutside" );
                //				// the object lies fully outside one of the planes -> return false
                //				//std::cout << "SFN::satisfiesHalfspaces, exact fullyOutside" << std::endl;
                //				return std::make_pair( CONTAINMENT::NO, this->intersectHalfspaces( _mat, _vec ) );
                //			}
                //		}
                //	} else {
                //		// the values are far enough away from each other to make this result a false negative.
                //		TRACE( "hypro.representations.supportFunctionNew", "fullyOutside, as " << invDirVal << " >= " << -( _vec( rowI ) ) );
                //		// the object lies fully outside one of the planes -> return false
                //		//std::cout << "SFN::satisfiesHalfspaces, non exact fullyOutside" << std::endl;
                //		return std::make_pair( CONTAINMENT::NO, this->intersectHalfspaces( _mat, _vec ) );
                //	}
                // }
            }
        }
        if (limitingPlanes.size() < unsigned(_mat.rows())) {
            if (limitingPlanes.size() == 0) {
                TRACE("hypro.representations.supportFunctionNew", " Object will stay the same");
                // std::cout << "SFN::satisfiesHalfspaces, full inside since no liming planes" << std::endl;
                return std::make_pair(CONTAINMENT::FULL, *this);
            }
            TRACE("hypro.representations.supportFunctionNew",
                  " Object will be limited but not empty (" << limitingPlanes.size() << " planes)");
            // if the result is not fullyOutside, only add planes, which affect the object
            matrix_t<Number> planes = matrix_t<Number>(limitingPlanes.size(), _mat.cols());
            vector_t<Number> distances = vector_t<Number>(limitingPlanes.size());
            for (unsigned i = 0; i < distances.rows(); ++i) {
                // std::cout << "Set row " << i << " to plane " << limitingPlanes.back() << std::endl;
                planes.row(i) = _mat.row(limitingPlanes.back());
                distances(i) = _vec(limitingPlanes.back());
                limitingPlanes.pop_back();
            }
            assert(limitingPlanes.empty());
            TRACE("hypro.representations.supportFunctionNew", "Intersect with " << planes << ", " << distances);
            return std::make_pair(CONTAINMENT::PARTIAL, this->intersectHalfspaces(planes, distances));
        } else {
            TRACE("hypro.representations.supportFunctionNew", " Object will be fully limited but not empty");
            assert(limitingPlanes.size() == unsigned(_mat.rows()));
            TRACE("hypro.representations.supportFunctionNew", "Intersect with " << _mat << ", " << _vec);
            return std::make_pair(CONTAINMENT::PARTIAL, this->intersectHalfspaces(_mat, _vec));
        }
    }

    template<typename Number, typename Converter, typename Setting>
    SupportFunctionNewT<Number, Converter, Setting>
    SupportFunctionNewT<Number, Converter, Setting>::projectOn(const std::vector<std::size_t> &dimensions) const {
        if (mRoot == nullptr) return SupportFunctionNewT<Number, Converter, Setting>();

        // check for full projection
        bool fullProjection = true;
        if (dimensions.size() == this->dimension()) {
            for (unsigned i = 0; i < this->dimension(); ++i) {
                if (dimensions.at(i) != i) {
                    fullProjection = false;
                    break;
                }
            }
        } else {
            fullProjection = false;
        }
        if (!fullProjection) {
            DEBUG("hypro.representations.supportFunction", "No full projection, create.");
            std::shared_ptr<ProjectOp<Number, Converter, Setting>> proj = std::make_shared<ProjectOp<Number, Converter, Setting>>(
                    *this, dimensions);
            std::shared_ptr<RootGrowNode<Number, Converter, Setting>> projPtr = std::static_pointer_cast<RootGrowNode<Number, Converter, Setting>>(
                    proj);
            SupportFunctionNewT<Number, Converter, Setting> sf = SupportFunctionNewT<Number, Converter, Setting>(
                    projPtr);
            return sf;
        }
        DEBUG("hypro.representations.supportFunction", "Full projection, copy.");
        return *this;
    }

    template<typename Number, typename Converter, typename Setting>
    SupportFunctionNewT<Number, Converter, Setting>
    SupportFunctionNewT<Number, Converter, Setting>::linearTransformation(const matrix_t<Number> &A) const {
        std::shared_ptr<TrafoOp<Number, Converter, Setting>> trafo = std::make_shared<TrafoOp<Number, Converter, Setting>>(
                *this, A, vector_t<Number>::Zero(A.rows()));
        std::shared_ptr<RootGrowNode<Number, Converter, Setting>> trafoPtr = std::static_pointer_cast<RootGrowNode<Number, Converter, Setting>>(
                trafo);
        SupportFunctionNewT<Number, Converter, Setting> sf = SupportFunctionNewT<Number, Converter, Setting>(trafoPtr);
        return sf;
    }

    template<typename Number, typename Converter, typename Setting>
    SupportFunctionNewT<Number, Converter, Setting>
    SupportFunctionNewT<Number, Converter, Setting>::affineTransformation(const matrix_t<Number> &A,
                                                                          const vector_t<Number> &b) const {
        std::shared_ptr<TrafoOp<Number, Converter, Setting>> trafo = std::make_shared<TrafoOp<Number, Converter, Setting>>(
                *this, A, b);
        std::shared_ptr<RootGrowNode<Number, Converter, Setting>> trafoPtr = std::static_pointer_cast<RootGrowNode<Number, Converter, Setting>>(
                trafo);
        SupportFunctionNewT<Number, Converter, Setting> sf = SupportFunctionNewT<Number, Converter, Setting>(trafoPtr);
        assert(trafo && trafoPtr && sf.getRoot());
        return sf;
    }

    template<typename Number, typename Converter, typename Setting>
    SupportFunctionNewT<Number, Converter, Setting> SupportFunctionNewT<Number, Converter, Setting>::minkowskiSum(
            const SupportFunctionNewT<Number, Converter, Setting> &rhs) const {
        std::shared_ptr<SumOp<Number, Converter, Setting>> sum = std::make_shared<SumOp<Number, Converter, Setting>>(
                *this, rhs);
        std::shared_ptr<RootGrowNode<Number, Converter, Setting>> sumPtr = std::static_pointer_cast<RootGrowNode<Number, Converter, Setting>>(
                sum);
        SupportFunctionNewT<Number, Converter, Setting> sf = SupportFunctionNewT<Number, Converter, Setting>(sumPtr);
        return sf;
    }

    template<typename Number, typename Converter, typename Setting>
    SupportFunctionNewT<Number, Converter, Setting> SupportFunctionNewT<Number, Converter, Setting>::minkowskiSum(
            const std::vector<SupportFunctionNewT<Number, Converter, Setting>> &rhs) const {
        std::shared_ptr<SumOp<Number, Converter, Setting>> sum = std::make_shared<SumOp<Number, Converter, Setting>>(
                *this, rhs);
        std::shared_ptr<RootGrowNode<Number, Converter, Setting>> sumPtr = std::static_pointer_cast<RootGrowNode<Number, Converter, Setting>>(
                sum);
        SupportFunctionNewT<Number, Converter, Setting> sf = SupportFunctionNewT<Number, Converter, Setting>(sumPtr);
        return sf;
    }

    template<typename Number, typename Converter, typename Setting>
    SupportFunctionNewT<Number, Converter, Setting>
    SupportFunctionNewT<Number, Converter, Setting>::scale(const Number &factor) const {
        std::shared_ptr<ScaleOp<Number, Converter, Setting>> scale = std::make_shared<ScaleOp<Number, Converter, Setting>>(
                *this, factor);
        std::shared_ptr<RootGrowNode<Number, Converter, Setting>> scalePtr = std::static_pointer_cast<RootGrowNode<Number, Converter, Setting>>(
                scale);
        SupportFunctionNewT<Number, Converter, Setting> sf = SupportFunctionNewT<Number, Converter, Setting>(scalePtr);
        return sf;
    }

    template<typename Number, typename Converter, typename Setting>
    SupportFunctionNewT<Number, Converter, Setting> SupportFunctionNewT<Number, Converter, Setting>::intersect(
            const SupportFunctionNewT<Number, Converter, Setting> &rhs) const {
        std::shared_ptr<IntersectOp<Number, Converter, Setting>> intersec = std::make_shared<IntersectOp<Number, Converter, Setting>>(
                *this, rhs);
        std::shared_ptr<RootGrowNode<Number, Converter, Setting>> intersecPtr = std::static_pointer_cast<RootGrowNode<Number, Converter, Setting>>(
                intersec);
        SupportFunctionNewT<Number, Converter, Setting> sf = SupportFunctionNewT<Number, Converter, Setting>(
                intersecPtr);
        return sf;
    }

    template<typename Number, typename Converter, typename Setting>
    SupportFunctionNewT<Number, Converter, Setting> SupportFunctionNewT<Number, Converter, Setting>::intersect(
            const std::vector<SupportFunctionNewT<Number, Converter, Setting>> &rhs) const {
        std::shared_ptr<IntersectOp<Number, Converter, Setting>> intersec = std::make_shared<IntersectOp<Number, Converter, Setting>>(
                *this, rhs);
        std::shared_ptr<RootGrowNode<Number, Converter, Setting>> intersecPtr = std::static_pointer_cast<RootGrowNode<Number, Converter, Setting>>(
                intersec);
        SupportFunctionNewT<Number, Converter, Setting> sf = SupportFunctionNewT<Number, Converter, Setting>(
                intersecPtr);
        return sf;
    }

    template<typename Number, typename Converter, typename Setting>
    SupportFunctionNewT<Number, Converter, Setting>
    SupportFunctionNewT<Number, Converter, Setting>::intersectHalfspace(const Halfspace<Number> &hspace) const {
        if (Setting::LE_GUERNIC_HSPACE_INTERSECTION) {
            std::shared_ptr<IntersectHalfspaceOp<Number, Converter, Setting>> intersecthspace = std::make_shared<IntersectHalfspaceOp<Number, Converter, Setting>>(
                    *this, hspace);
            std::shared_ptr<RootGrowNode<Number, Converter, Setting>> intersecthspacePtr = std::static_pointer_cast<RootGrowNode<Number, Converter, Setting>>(
                    intersecthspace);
            SupportFunctionNewT<Number, Converter, Setting> sf = SupportFunctionNewT<Number, Converter, Setting>(
                    intersecthspacePtr);
            return sf;
        } else {
            Halfspace<Number> copy(hspace);
            return intersect(SupportFunctionNewT<Number, Converter, Setting>(copy));
        }
    }

    template<typename Number, typename Converter, typename Setting>
    SupportFunctionNewT<Number, Converter, Setting>
    SupportFunctionNewT<Number, Converter, Setting>::intersectHalfspaces(const matrix_t<Number> &_mat,
                                                                         const vector_t<Number> &_vec) const {
        if (_mat.rows() == 1 && _vec.rows() == 1) {
            Halfspace<Number> hspace(_mat.row(0), _vec(0));
            return intersectHalfspace(hspace);
        }
        return intersect(SupportFunctionNewT<Number, Converter, Setting>(_mat, _vec));
    }

    template<typename Number, typename Converter, typename Setting>
    bool SupportFunctionNewT<Number, Converter, Setting>::contains(const vector_t<Number> &point) const {
        if (mRoot == nullptr) return false;

        // first function - Parameters are backtransformed into the domain space of the given operation
        std::function<Parameters<vector_t<Number>>(RootGrowNode<Number, Converter, Setting> *,
                                                   Parameters<vector_t<Number>> &)> reverseOp =
                [](RootGrowNode<Number, Converter, Setting> *n,
                   Parameters<vector_t<Number>> &p) -> Parameters<vector_t<Number>> {
                    return Parameters<vector_t<Number>>(n->reverseOp(std::get<0>(p.args)));
                };

        // second function - calls contains() of leaf
        std::function<bool(RootGrowNode<Number, Converter, Setting> *,
                           Parameters<vector_t<Number>> &)> doesLeafContain =
                [](RootGrowNode<Number, Converter, Setting> *n, Parameters<vector_t<Number>> &p) -> bool {
                    return n->contains(std::get<0>(p.args));
                };

        // third function - calls contains() of operations
        std::function<bool(RootGrowNode<Number, Converter, Setting> *, std::vector<bool> &,
                           Parameters<vector_t<Number>> &)> aggregate =
                [](RootGrowNode<Number, Converter, Setting> *n, std::vector<bool> &v, Parameters<vector_t<Number>> &p) {
                    return n->contains(v, std::get<0>(p.args));
                };

        Parameters<vector_t<Number>> initParams = Parameters<vector_t<Number>>(point);
        return traverse(std::move(reverseOp), std::move(doesLeafContain), std::move(aggregate), std::move(initParams));
    }

    template<typename Number, typename Converter, typename Setting>
    bool SupportFunctionNewT<Number, Converter, Setting>::contains(const Point<Number> &point) const {
        return contains(point.rawCoordinates());
    }

    template<typename Number, typename Converter, typename Setting>
    bool SupportFunctionNewT<Number, Converter, Setting>::contains(
            const SupportFunctionNewT<Number, Converter, Setting> &rhs, std::size_t directions) const {
        std::vector<vector_t<Number>> templateDirections = computeTemplate<Number>(this->dimension(), directions);
        for (const auto &direction: templateDirections) {
            EvaluationResult<Number> thisRes = this->evaluate(direction, true);
            EvaluationResult<Number> rhsRes = rhs.evaluate(direction, true);
            assert(thisRes.errorCode != SOLUTION::INFTY && rhsRes.errorCode != SOLUTION::INFTY);
            if (thisRes.errorCode == SOLUTION::FEAS) {
                if (rhsRes.errorCode == SOLUTION::FEAS) {
                    if (thisRes < rhsRes) {
                        return false;
                    }
                } else {
                    // If this is bound and rhs is unbound, then this does not contain rhs on this side and therefore overall
                    return false;
                }
            }
            // If this is unbound and rhs bound, then rhs is still contained on this side
            // If both are unbound, then both SFs are halfspaces and are only contained in each other, if the normals point to the same direction
            // while the offset of rhs is smaller than of this.
        }
        return true;
    }

    template<typename Number, typename Converter, typename Setting>
    bool SupportFunctionNewT<Number, Converter, Setting>::contains(
            const SupportFunctionNewT<Number, Converter, Setting> &rhs) const {
        return contains(rhs, 8);
    }

    template<typename Number, typename Converter, typename Setting>
    SupportFunctionNewT<Number, Converter, Setting> SupportFunctionNewT<Number, Converter, Setting>::unite(
            const SupportFunctionNewT<Number, Converter, Setting> &rhs) const {
        std::shared_ptr<UnionOp<Number, Converter, Setting>> unio = std::make_shared<UnionOp<Number, Converter, Setting>>(
                *this, rhs);
        std::shared_ptr<RootGrowNode<Number, Converter, Setting>> unioPtr = std::static_pointer_cast<RootGrowNode<Number, Converter, Setting>>(
                unio);
        SupportFunctionNewT<Number, Converter, Setting> sf = SupportFunctionNewT<Number, Converter, Setting>(unioPtr);
        return sf;
    }

    template<typename Number, typename Converter, typename Setting>
    SupportFunctionNewT<Number, Converter, Setting> SupportFunctionNewT<Number, Converter, Setting>::unite(
            const std::vector<SupportFunctionNewT<Number, Converter, Setting>> &rhs) const {
        std::shared_ptr<UnionOp<Number, Converter, Setting>> unio = std::make_shared<UnionOp<Number, Converter, Setting>>(
                *this, rhs);
        std::shared_ptr<RootGrowNode<Number, Converter, Setting>> unioPtr = std::static_pointer_cast<RootGrowNode<Number, Converter, Setting>>(
                unio);
        SupportFunctionNewT<Number, Converter, Setting> sf = SupportFunctionNewT<Number, Converter, Setting>(unioPtr);
        return sf;
    }

    template<typename Number, typename Converter, typename Setting>
    void SupportFunctionNewT<Number, Converter, Setting>::reduceRepresentation() {
        if (Setting::APPROXIMATE_AS_BOX) {
            this->evaluateTemplate(4, true);
        } else {
            this->evaluateTemplate(8, false);
        }
    }

    template<typename Number, typename Converter, typename Setting>
    void SupportFunctionNewT<Number, Converter, Setting>::clear() {
        mRoot = nullptr;
        mMatrix = matrix_t<Number>::Zero(0, 0);
        mVector = vector_t<Number>::Zero(0);
        mTemplateSet = false;
    }

    template<typename Number, typename Converter, typename Setting>
    std::vector<std::size_t> SupportFunctionNewT<Number, Converter, Setting>::collectProjections() const {
        // TODO: Check if right
        if (mRoot == nullptr) return std::vector<std::size_t>();

        // first function - do nothing
        std::function<void(RootGrowNode<Number, Converter, Setting> *)> doNothing = [](
                RootGrowNode<Number, Converter, Setting> *) {};

        // second function - leaves return a vector of ascending dimensions
        std::function<std::vector<std::size_t>(RootGrowNode<Number, Converter, Setting> *)> collectLeafDimensions =
                [](RootGrowNode<Number, Converter, Setting> *n) -> std::vector<std::size_t> {
                    std::vector<std::size_t> res;
                    for (std::size_t i = 0; i < n->getDimension(); ++i) {
                        res.emplace_back(i);
                    }
                    return res;
                };

        // third function - call the respective function of the node which sorts out unwanted dimensions
        std::function<std::vector<std::size_t>(RootGrowNode<Number, Converter, Setting> *,
                                               std::vector<std::vector<std::size_t>> &)> intersectDims =
                [](RootGrowNode<Number, Converter, Setting> *n,
                   std::vector<std::vector<std::size_t>> &dims) -> std::vector<std::size_t> {
                    return n->intersectDims(dims);
                };

        return traverse(std::move(doNothing), std::move(collectLeafDimensions), std::move(intersectDims));
    }

    template<typename Number, typename Converter, typename Setting>
    void
    SupportFunctionNewT<Number, Converter, Setting>::evaluateTemplate(std::size_t directionCount, bool force) const {
        if (!mTemplateSet || force) {
            std::vector<vector_t<Number>> templateDirections = computeTemplate<Number>(this->dimension(),
                                                                                       directionCount);

            matrix_t<Number> templateDirectionMatrix = createMatrix(templateDirections);

            // lets the support function evaluate the offset of the halfspaces for each direction
            std::vector<EvaluationResult<Number>> offsets = this->multiEvaluate(templateDirectionMatrix);

            std::vector<std::size_t> boundedConstraints;
            for (unsigned offsetIndex = 0; offsetIndex < offsets.size(); ++offsetIndex) {
                if (offsets[offsetIndex].errorCode != SOLUTION::INFTY) {
                    boundedConstraints.push_back(offsetIndex);
                }
            }
            matrix_t<Number> constraints = matrix_t<Number>(boundedConstraints.size(), this->dimension());
            vector_t<Number> constants = vector_t<Number>(boundedConstraints.size());
            std::size_t pos = boundedConstraints.size() - 1;
            while (!boundedConstraints.empty()) {
                constraints.row(pos) = templateDirectionMatrix.row(boundedConstraints.back());
                constants(pos) = offsets[boundedConstraints.back()].supportValue;
                boundedConstraints.pop_back();
                --pos;
            }

            mMatrix = constraints;
            mVector = constants;
            mTemplateSet = true;
        }
    }

}  // namespace hypro
