
/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

// Generated from HybridAutomaton.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "HybridAutomatonVisitor.h"


namespace hypro {

/**
 * This class provides an empty implementation of HybridAutomatonVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
    class HybridAutomatonBaseVisitor : public HybridAutomatonVisitor {
    public:

        virtual antlrcpp::Any visitStart(HybridAutomatonParser::StartContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitVardeclaration(HybridAutomatonParser::VardeclarationContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any
        visitConstantdeclaration(HybridAutomatonParser::ConstantdeclarationContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitModes(HybridAutomatonParser::ModesContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitLocation(HybridAutomatonParser::LocationContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitActivities(HybridAutomatonParser::ActivitiesContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitInvariants(HybridAutomatonParser::InvariantsContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitStochasticlocation(HybridAutomatonParser::StochasticlocationContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitProbdistribution(HybridAutomatonParser::ProbdistributionContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitLoc_labels(HybridAutomatonParser::Loc_labelsContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitReplacedexpr(HybridAutomatonParser::ReplacedexprContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitConstantexpr(HybridAutomatonParser::ConstantexprContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitConnector(HybridAutomatonParser::ConnectorContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitTerm(HybridAutomatonParser::TermContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitBracketExpression(HybridAutomatonParser::BracketExpressionContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitPolynom(HybridAutomatonParser::PolynomContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitExpression(HybridAutomatonParser::ExpressionContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitEquation(HybridAutomatonParser::EquationContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitConstraint(HybridAutomatonParser::ConstraintContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitInterval(HybridAutomatonParser::IntervalContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitIntervalexpr(HybridAutomatonParser::IntervalexprContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitConstrset(HybridAutomatonParser::ConstrsetContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitInit(HybridAutomatonParser::InitContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitInitstate(HybridAutomatonParser::InitstateContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitProbinitstate(HybridAutomatonParser::ProbinitstateContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitUnsafeset(HybridAutomatonParser::UnsafesetContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitLbadstate(HybridAutomatonParser::LbadstateContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitGbadstate(HybridAutomatonParser::GbadstateContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitJumps(HybridAutomatonParser::JumpsContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitTransition(HybridAutomatonParser::TransitionContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitFromto(HybridAutomatonParser::FromtoContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitUrgent(HybridAutomatonParser::UrgentContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitGuard(HybridAutomatonParser::GuardContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitLabels(HybridAutomatonParser::LabelsContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitAllocation(HybridAutomatonParser::AllocationContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitResetfct(HybridAutomatonParser::ResetfctContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitAggregation(HybridAutomatonParser::AggregationContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any
        visitStochastictransition(HybridAutomatonParser::StochastictransitionContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitProbtransition(HybridAutomatonParser::ProbtransitionContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitProbfrom(HybridAutomatonParser::ProbfromContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitProbto(HybridAutomatonParser::ProbtoContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitSetting(HybridAutomatonParser::SettingContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitFixedsteps(HybridAutomatonParser::FixedstepsContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitTime(HybridAutomatonParser::TimeContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitPlotsetting(HybridAutomatonParser::PlotsettingContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitFilename(HybridAutomatonParser::FilenameContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitMaxjumps(HybridAutomatonParser::MaxjumpsContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitPrint(HybridAutomatonParser::PrintContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitRemainder(HybridAutomatonParser::RemainderContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitIdentity(HybridAutomatonParser::IdentityContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitQrprecond(HybridAutomatonParser::QrprecondContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitFixedorders(HybridAutomatonParser::FixedordersContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitAdaptiveorders(HybridAutomatonParser::AdaptiveordersContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitCutoff(HybridAutomatonParser::CutoffContext *ctx) override {
            return visitChildren(ctx);
        }

        virtual antlrcpp::Any visitPrecision(HybridAutomatonParser::PrecisionContext *ctx) override {
            return visitChildren(ctx);
        }


    };

}  // namespace hypro
