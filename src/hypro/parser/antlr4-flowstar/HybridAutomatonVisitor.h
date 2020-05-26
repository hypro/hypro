
// Generated from HybridAutomaton.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "HybridAutomatonParser.h"


namespace hypro {

/**
 * This class defines an abstract visitor for a parse tree
 * produced by HybridAutomatonParser.
 */
class  HybridAutomatonVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by HybridAutomatonParser.
   */
    virtual antlrcpp::Any visitStart(HybridAutomatonParser::StartContext *context) = 0;

    virtual antlrcpp::Any visitVardeclaration(HybridAutomatonParser::VardeclarationContext *context) = 0;

    virtual antlrcpp::Any visitConstantdeclaration(HybridAutomatonParser::ConstantdeclarationContext *context) = 0;

    virtual antlrcpp::Any visitModes(HybridAutomatonParser::ModesContext *context) = 0;

    virtual antlrcpp::Any visitLocation(HybridAutomatonParser::LocationContext *context) = 0;

    virtual antlrcpp::Any visitActivities(HybridAutomatonParser::ActivitiesContext *context) = 0;

    virtual antlrcpp::Any visitInvariants(HybridAutomatonParser::InvariantsContext *context) = 0;

    virtual antlrcpp::Any visitReplacedexpr(HybridAutomatonParser::ReplacedexprContext *context) = 0;

    virtual antlrcpp::Any visitConstantexpr(HybridAutomatonParser::ConstantexprContext *context) = 0;

    virtual antlrcpp::Any visitConnector(HybridAutomatonParser::ConnectorContext *context) = 0;

    virtual antlrcpp::Any visitTerm(HybridAutomatonParser::TermContext *context) = 0;

    virtual antlrcpp::Any visitPolynom(HybridAutomatonParser::PolynomContext *context) = 0;

    virtual antlrcpp::Any visitInterval(HybridAutomatonParser::IntervalContext *context) = 0;

    virtual antlrcpp::Any visitEquation(HybridAutomatonParser::EquationContext *context) = 0;

    virtual antlrcpp::Any visitConstraint(HybridAutomatonParser::ConstraintContext *context) = 0;

    virtual antlrcpp::Any visitIntervalexpr(HybridAutomatonParser::IntervalexprContext *context) = 0;

    virtual antlrcpp::Any visitConstrset(HybridAutomatonParser::ConstrsetContext *context) = 0;

    virtual antlrcpp::Any visitInit(HybridAutomatonParser::InitContext *context) = 0;

    virtual antlrcpp::Any visitInitstate(HybridAutomatonParser::InitstateContext *context) = 0;

    virtual antlrcpp::Any visitUnsafeset(HybridAutomatonParser::UnsafesetContext *context) = 0;

    virtual antlrcpp::Any visitLbadstate(HybridAutomatonParser::LbadstateContext *context) = 0;

    virtual antlrcpp::Any visitGbadstate(HybridAutomatonParser::GbadstateContext *context) = 0;

    virtual antlrcpp::Any visitJumps(HybridAutomatonParser::JumpsContext *context) = 0;

    virtual antlrcpp::Any visitTransition(HybridAutomatonParser::TransitionContext *context) = 0;

    virtual antlrcpp::Any visitFromto(HybridAutomatonParser::FromtoContext *context) = 0;

    virtual antlrcpp::Any visitUrgent(HybridAutomatonParser::UrgentContext *context) = 0;

    virtual antlrcpp::Any visitGuard(HybridAutomatonParser::GuardContext *context) = 0;

    virtual antlrcpp::Any visitLabels(HybridAutomatonParser::LabelsContext *context) = 0;

    virtual antlrcpp::Any visitAllocation(HybridAutomatonParser::AllocationContext *context) = 0;

    virtual antlrcpp::Any visitResetfct(HybridAutomatonParser::ResetfctContext *context) = 0;

    virtual antlrcpp::Any visitAggregation(HybridAutomatonParser::AggregationContext *context) = 0;

    virtual antlrcpp::Any visitSetting(HybridAutomatonParser::SettingContext *context) = 0;

    virtual antlrcpp::Any visitFixedsteps(HybridAutomatonParser::FixedstepsContext *context) = 0;

    virtual antlrcpp::Any visitTime(HybridAutomatonParser::TimeContext *context) = 0;

    virtual antlrcpp::Any visitPlotsetting(HybridAutomatonParser::PlotsettingContext *context) = 0;

    virtual antlrcpp::Any visitFilename(HybridAutomatonParser::FilenameContext *context) = 0;

    virtual antlrcpp::Any visitMaxjumps(HybridAutomatonParser::MaxjumpsContext *context) = 0;

    virtual antlrcpp::Any visitPrint(HybridAutomatonParser::PrintContext *context) = 0;

    virtual antlrcpp::Any visitRemainder(HybridAutomatonParser::RemainderContext *context) = 0;

    virtual antlrcpp::Any visitIdentity(HybridAutomatonParser::IdentityContext *context) = 0;

    virtual antlrcpp::Any visitQrprecond(HybridAutomatonParser::QrprecondContext *context) = 0;

    virtual antlrcpp::Any visitFixedorders(HybridAutomatonParser::FixedordersContext *context) = 0;

    virtual antlrcpp::Any visitAdaptiveorders(HybridAutomatonParser::AdaptiveordersContext *context) = 0;

    virtual antlrcpp::Any visitCutoff(HybridAutomatonParser::CutoffContext *context) = 0;

    virtual antlrcpp::Any visitPrecision(HybridAutomatonParser::PrecisionContext *context) = 0;


};

}  // namespace hypro
