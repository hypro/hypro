
// Generated from HybridAutomaton.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "HybridAutomatonParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by HybridAutomatonParser.
 */
class  HybridAutomatonListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterStart(HybridAutomatonParser::StartContext *ctx) = 0;
  virtual void exitStart(HybridAutomatonParser::StartContext *ctx) = 0;

  virtual void enterOld(HybridAutomatonParser::OldContext *ctx) = 0;
  virtual void exitOld(HybridAutomatonParser::OldContext *ctx) = 0;

  virtual void enterAutomaton(HybridAutomatonParser::AutomatonContext *ctx) = 0;
  virtual void exitAutomaton(HybridAutomatonParser::AutomatonContext *ctx) = 0;

  virtual void enterComp(HybridAutomatonParser::CompContext *ctx) = 0;
  virtual void exitComp(HybridAutomatonParser::CompContext *ctx) = 0;

  virtual void enterVardeclaration(HybridAutomatonParser::VardeclarationContext *ctx) = 0;
  virtual void exitVardeclaration(HybridAutomatonParser::VardeclarationContext *ctx) = 0;

  virtual void enterConstantdeclaration(HybridAutomatonParser::ConstantdeclarationContext *ctx) = 0;
  virtual void exitConstantdeclaration(HybridAutomatonParser::ConstantdeclarationContext *ctx) = 0;

  virtual void enterGlobalvardeclaration(HybridAutomatonParser::GlobalvardeclarationContext *ctx) = 0;
  virtual void exitGlobalvardeclaration(HybridAutomatonParser::GlobalvardeclarationContext *ctx) = 0;

  virtual void enterComponent(HybridAutomatonParser::ComponentContext *ctx) = 0;
  virtual void exitComponent(HybridAutomatonParser::ComponentContext *ctx) = 0;

  virtual void enterModes(HybridAutomatonParser::ModesContext *ctx) = 0;
  virtual void exitModes(HybridAutomatonParser::ModesContext *ctx) = 0;

  virtual void enterLocation(HybridAutomatonParser::LocationContext *ctx) = 0;
  virtual void exitLocation(HybridAutomatonParser::LocationContext *ctx) = 0;

  virtual void enterActivities(HybridAutomatonParser::ActivitiesContext *ctx) = 0;
  virtual void exitActivities(HybridAutomatonParser::ActivitiesContext *ctx) = 0;

  virtual void enterInvariants(HybridAutomatonParser::InvariantsContext *ctx) = 0;
  virtual void exitInvariants(HybridAutomatonParser::InvariantsContext *ctx) = 0;

  virtual void enterConstantexpr(HybridAutomatonParser::ConstantexprContext *ctx) = 0;
  virtual void exitConstantexpr(HybridAutomatonParser::ConstantexprContext *ctx) = 0;

  virtual void enterConnector(HybridAutomatonParser::ConnectorContext *ctx) = 0;
  virtual void exitConnector(HybridAutomatonParser::ConnectorContext *ctx) = 0;

  virtual void enterTerm(HybridAutomatonParser::TermContext *ctx) = 0;
  virtual void exitTerm(HybridAutomatonParser::TermContext *ctx) = 0;

  virtual void enterPolynom(HybridAutomatonParser::PolynomContext *ctx) = 0;
  virtual void exitPolynom(HybridAutomatonParser::PolynomContext *ctx) = 0;

  virtual void enterInterval(HybridAutomatonParser::IntervalContext *ctx) = 0;
  virtual void exitInterval(HybridAutomatonParser::IntervalContext *ctx) = 0;

  virtual void enterEquation(HybridAutomatonParser::EquationContext *ctx) = 0;
  virtual void exitEquation(HybridAutomatonParser::EquationContext *ctx) = 0;

  virtual void enterConstraint(HybridAutomatonParser::ConstraintContext *ctx) = 0;
  virtual void exitConstraint(HybridAutomatonParser::ConstraintContext *ctx) = 0;

  virtual void enterIntervalexpr(HybridAutomatonParser::IntervalexprContext *ctx) = 0;
  virtual void exitIntervalexpr(HybridAutomatonParser::IntervalexprContext *ctx) = 0;

  virtual void enterConstrset(HybridAutomatonParser::ConstrsetContext *ctx) = 0;
  virtual void exitConstrset(HybridAutomatonParser::ConstrsetContext *ctx) = 0;

  virtual void enterReplacedexpr(HybridAutomatonParser::ReplacedexprContext *ctx) = 0;
  virtual void exitReplacedexpr(HybridAutomatonParser::ReplacedexprContext *ctx) = 0;

  virtual void enterInit(HybridAutomatonParser::InitContext *ctx) = 0;
  virtual void exitInit(HybridAutomatonParser::InitContext *ctx) = 0;

  virtual void enterInitstate(HybridAutomatonParser::InitstateContext *ctx) = 0;
  virtual void exitInitstate(HybridAutomatonParser::InitstateContext *ctx) = 0;

  virtual void enterUnsafeset(HybridAutomatonParser::UnsafesetContext *ctx) = 0;
  virtual void exitUnsafeset(HybridAutomatonParser::UnsafesetContext *ctx) = 0;

  virtual void enterLbadstate(HybridAutomatonParser::LbadstateContext *ctx) = 0;
  virtual void exitLbadstate(HybridAutomatonParser::LbadstateContext *ctx) = 0;

  virtual void enterGbadstate(HybridAutomatonParser::GbadstateContext *ctx) = 0;
  virtual void exitGbadstate(HybridAutomatonParser::GbadstateContext *ctx) = 0;

  virtual void enterJumps(HybridAutomatonParser::JumpsContext *ctx) = 0;
  virtual void exitJumps(HybridAutomatonParser::JumpsContext *ctx) = 0;

  virtual void enterTransition(HybridAutomatonParser::TransitionContext *ctx) = 0;
  virtual void exitTransition(HybridAutomatonParser::TransitionContext *ctx) = 0;

  virtual void enterFromto(HybridAutomatonParser::FromtoContext *ctx) = 0;
  virtual void exitFromto(HybridAutomatonParser::FromtoContext *ctx) = 0;

  virtual void enterUrgent(HybridAutomatonParser::UrgentContext *ctx) = 0;
  virtual void exitUrgent(HybridAutomatonParser::UrgentContext *ctx) = 0;

  virtual void enterGuard(HybridAutomatonParser::GuardContext *ctx) = 0;
  virtual void exitGuard(HybridAutomatonParser::GuardContext *ctx) = 0;

  virtual void enterAllocation(HybridAutomatonParser::AllocationContext *ctx) = 0;
  virtual void exitAllocation(HybridAutomatonParser::AllocationContext *ctx) = 0;

  virtual void enterResetfct(HybridAutomatonParser::ResetfctContext *ctx) = 0;
  virtual void exitResetfct(HybridAutomatonParser::ResetfctContext *ctx) = 0;

  virtual void enterAggregation(HybridAutomatonParser::AggregationContext *ctx) = 0;
  virtual void exitAggregation(HybridAutomatonParser::AggregationContext *ctx) = 0;

  virtual void enterLabels(HybridAutomatonParser::LabelsContext *ctx) = 0;
  virtual void exitLabels(HybridAutomatonParser::LabelsContext *ctx) = 0;

  virtual void enterLabel(HybridAutomatonParser::LabelContext *ctx) = 0;
  virtual void exitLabel(HybridAutomatonParser::LabelContext *ctx) = 0;

  virtual void enterSetting(HybridAutomatonParser::SettingContext *ctx) = 0;
  virtual void exitSetting(HybridAutomatonParser::SettingContext *ctx) = 0;

  virtual void enterFixedsteps(HybridAutomatonParser::FixedstepsContext *ctx) = 0;
  virtual void exitFixedsteps(HybridAutomatonParser::FixedstepsContext *ctx) = 0;

  virtual void enterTime(HybridAutomatonParser::TimeContext *ctx) = 0;
  virtual void exitTime(HybridAutomatonParser::TimeContext *ctx) = 0;

  virtual void enterPlotsetting(HybridAutomatonParser::PlotsettingContext *ctx) = 0;
  virtual void exitPlotsetting(HybridAutomatonParser::PlotsettingContext *ctx) = 0;

  virtual void enterFilename(HybridAutomatonParser::FilenameContext *ctx) = 0;
  virtual void exitFilename(HybridAutomatonParser::FilenameContext *ctx) = 0;

  virtual void enterMaxjumps(HybridAutomatonParser::MaxjumpsContext *ctx) = 0;
  virtual void exitMaxjumps(HybridAutomatonParser::MaxjumpsContext *ctx) = 0;

  virtual void enterPrint(HybridAutomatonParser::PrintContext *ctx) = 0;
  virtual void exitPrint(HybridAutomatonParser::PrintContext *ctx) = 0;

  virtual void enterRemainder(HybridAutomatonParser::RemainderContext *ctx) = 0;
  virtual void exitRemainder(HybridAutomatonParser::RemainderContext *ctx) = 0;

  virtual void enterIdentity(HybridAutomatonParser::IdentityContext *ctx) = 0;
  virtual void exitIdentity(HybridAutomatonParser::IdentityContext *ctx) = 0;

  virtual void enterFixedorders(HybridAutomatonParser::FixedordersContext *ctx) = 0;
  virtual void exitFixedorders(HybridAutomatonParser::FixedordersContext *ctx) = 0;

  virtual void enterCutoff(HybridAutomatonParser::CutoffContext *ctx) = 0;
  virtual void exitCutoff(HybridAutomatonParser::CutoffContext *ctx) = 0;

  virtual void enterPrecision(HybridAutomatonParser::PrecisionContext *ctx) = 0;
  virtual void exitPrecision(HybridAutomatonParser::PrecisionContext *ctx) = 0;


};

