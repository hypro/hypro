/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "HyproBadStatesVisitor.h"

namespace hypro {

    //////////////// Constructor & Destructor

    template<typename Number>
    HyproBadStatesVisitor<Number>::HyproBadStatesVisitor(std::vector<std::string> &varVec,
                                                         std::set<Location<Number> *> &lSet) :
            vars(varVec),
            locSet(lSet),
            gBadStates() {}

    template<typename Number>
    HyproBadStatesVisitor<Number>::~HyproBadStatesVisitor() {}

    /////////////// Inherited from HybridAutomatonBaseVisitor

    template<typename Number>
    antlrcpp::Any HyproBadStatesVisitor<Number>::visitUnsafeset(HybridAutomatonParser::UnsafesetContext *ctx) {

        //1.Collect badState information. NOTE: There can be multiple denoted badstates for one location.
        typename HybridAutomaton<Number>::locationConditionMap lcMap;
        if (ctx->lbadstate().size() > 0) {
            for (auto bState: ctx->lbadstate()) {
                std::pair<Location<Number> *, Condition<Number>> badStateInfo = visit(
                        bState).template as<std::pair<Location<Number> *, Condition<Number>>>();
                std::size_t lcMapSize = lcMap.size();
                //lcMap.insert(badStateInfo);
                lcMap.emplace(badStateInfo);
                //Case that nothing has been inserted as location already existed in map:
                //Extend condition matrix and vector of condition that is already in map
                if (lcMapSize == lcMap.size()) {

                    auto it = lcMap.find(badStateInfo.first);
                    assert(it != lcMap.end());

                    // if either the new condition or the
// existing one is already true, do nothing.
                    if (it->second.isTrue()) {
                        continue;
                    }
                    if (badStateInfo.second.isTrue()) {
                        it->second = Condition<Number>();
                        continue;
                    }

                    //Extend inMapCondition.matrix with badStateInfo.matrix
                    matrix_t<Number> newMat = it->second.getMatrix();
                    Eigen::Index newMatRowsBefore = newMat.rows();
                    matrix_t<Number> currbStateMat = badStateInfo.second.getMatrix();
                    assert(newMat.cols() == currbStateMat
                            .cols() || newMat.cols() == Eigen::Index(0) || currbStateMat.cols() ==
                                                                           Eigen::Index(0));
                    newMat.conservativeResize((newMat
                                                       .rows() + currbStateMat.rows()),
                                              std::max(newMat.cols(), currbStateMat.cols()));
                    for (Eigen::Index i = newMat.rows() - currbStateMat.rows(); i < newMat.rows(); i++) {
                        newMat.row(i) = currbStateMat.row(i - newMatRowsBefore);
                    }

                    //Extend inMapCondition.vector with badStateInfo.vector
                    vector_t<Number> newVec = it->second.getVector();
                    vector_t<Number> currbStateVec = badStateInfo.second.getVector();
                    newVec.conservativeResize(newVec.rows() + currbStateVec.rows());
                    for (Eigen::Index i = newVec.rows() - currbStateVec.rows(); i < newVec.rows(); i++) {
                        newVec(i) = currbStateVec(i - newMatRowsBefore);
                    }

                    it->second.setMatrix(newMat);
                    it->second.setVector(newVec);

                }
            }
        }
        if (ctx->gbadstate().size() > 0) {
            std::vector<Condition<Number>> allGlobalBadStates;
            for (const auto &g: ctx->gbadstate()) {
                Condition<Number> gBadStateInfo = visit(g).template as<Condition<Number>>();
                allGlobalBadStates.push_back(gBadStateInfo);
            }
            gBadStates = allGlobalBadStates;
        }
        return lcMap;
    }

    template<typename Number>
    antlrcpp::Any HyproBadStatesVisitor<Number>::visitLbadstate(HybridAutomatonParser::LbadstateContext *ctx) {

        //0.Check if given loc name exists and get meant location where bad states can occur
        bool found = false;
        Location<Number> *badLoc;
        for (const auto &loc: locSet) {
            if (ctx->VARIABLE()->getText() == loc->getName()) {
                found = true;
                badLoc = loc;
                break;
            }
        }
        if (!found) {
            std::cerr << "ERROR: Given location name in unsafe set does not exist." << std::endl;
            exit(0);
        }

        //1.Get the conditions under which we enter a bad state.
        if (ctx->constrset() != NULL && ctx->constrset()->getText() != "") {
            HyproFormulaVisitor<Number> visitor(vars);
            std::pair<matrix_t<Number>, vector_t<Number>> badStatePair = visitor.visit(
                    ctx->constrset()).template as<std::pair<matrix_t<Number>, vector_t<Number>>>();
            Condition<Number> badStateConditions(badStatePair.first, badStatePair.second);
            return std::make_pair(badLoc, badStateConditions);
        } else {
            return std::make_pair(badLoc, Condition<Number>::True());
        }

    }

    template<typename Number>
    antlrcpp::Any HyproBadStatesVisitor<Number>::visitGbadstate(HybridAutomatonParser::GbadstateContext *ctx) {
        HyproFormulaVisitor<Number> visitor(vars);
        std::pair<matrix_t<Number>, vector_t<Number>> gBadStatePair = visitor.visit(
                ctx->constrset()).template as<std::pair<matrix_t<Number>, vector_t<Number>>>();
        return Condition<Number>(gBadStatePair.first, gBadStatePair.second);
    }

} //namespace hypro
