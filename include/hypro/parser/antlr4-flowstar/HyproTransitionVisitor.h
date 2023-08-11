/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * HyproTransitionVisitor.h
 *
 * Collects information to build a Transition set which can be
 * given to the HAVisitor in order to build a HybridAutomaton.
 *
 * @author Phillip Tse
 * @date 26.7.2017
 */

#pragma once

#include "../../datastructures/HybridAutomaton/Location.h"
#include "../../datastructures/HybridAutomaton/StochasticLocation.h"
#include "../../datastructures/HybridAutomaton/Transition.h"
#include "../../datastructures/HybridAutomaton/StochasticTransition.h"
#include "../../types.h"
#include "HybridAutomatonBaseVisitor.h"
#include "HyproFormulaVisitor.h"

using namespace antlr4;

namespace hypro {

    template<typename Number>
    class HyproHAVisitor;

    template<typename Number>
    class HyproTransitionVisitor : public HybridAutomatonBaseVisitor {

        friend class HyproHAVisitor<Number>;

    private:

        //A vector of all variables that are defined
        std::vector<std::string> &vars;

        //The set of possible locations
        const std::set<Location<Number> *> &locSet;

        //Inherited
        antlrcpp::Any visitTransition(HybridAutomatonParser::TransitionContext *ctx) override;

        antlrcpp::Any visitFromto(HybridAutomatonParser::FromtoContext *ctx) override;

        antlrcpp::Any visitGuard(HybridAutomatonParser::GuardContext *ctx) override;

        antlrcpp::Any visitLabels(HybridAutomatonParser::LabelsContext *ctx) override;

        antlrcpp::Any visitAllocation(HybridAutomatonParser::AllocationContext *ctx) override;

        antlrcpp::Any visitResetfct(HybridAutomatonParser::ResetfctContext *ctx) override;

        antlrcpp::Any visitAggregation(HybridAutomatonParser::AggregationContext *ctx) override;

        antlrcpp::Any visitStochastictransition(HybridAutomatonParser::StochastictransitionContext *ctx) override;

        antlrcpp::Any visitProbtransition(HybridAutomatonParser::ProbtransitionContext *ctx) override;

        antlrcpp::Any visitProbfrom(HybridAutomatonParser::ProbfromContext *ctx) override;

        antlrcpp::Any visitProbto(HybridAutomatonParser::ProbtoContext *ctx) override;

    public:

        //Constructor and Destructor
        HyproTransitionVisitor(std::vector<std::string> &varVec, const std::set<Location<Number> *> &lSet);

        ~HyproTransitionVisitor();

        //Inherited from HybridAutomatonBaseVisitor - stays public for testing/debugging
        antlrcpp::Any visitJumps(HybridAutomatonParser::JumpsContext *ctx) override;

    };


} //namespace hypro

#include "HyproTransitionVisitor.tpp"
