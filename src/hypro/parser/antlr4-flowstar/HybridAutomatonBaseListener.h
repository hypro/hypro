
// Generated from HybridAutomaton.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "HybridAutomatonListener.h"


/**
 * This class provides an empty implementation of HybridAutomatonListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  HybridAutomatonBaseListener : public HybridAutomatonListener {
public:

  virtual void enterStart(HybridAutomatonParser::StartContext * /*ctx*/) override { }
  virtual void exitStart(HybridAutomatonParser::StartContext * /*ctx*/) override { }

  virtual void enterOld(HybridAutomatonParser::OldContext * /*ctx*/) override { }
  virtual void exitOld(HybridAutomatonParser::OldContext * /*ctx*/) override { }

  virtual void enterAutomaton(HybridAutomatonParser::AutomatonContext * /*ctx*/) override { }
  virtual void exitAutomaton(HybridAutomatonParser::AutomatonContext * /*ctx*/) override { }

  virtual void enterComp(HybridAutomatonParser::CompContext * /*ctx*/) override { }
  virtual void exitComp(HybridAutomatonParser::CompContext * /*ctx*/) override { }

  virtual void enterVardeclaration(HybridAutomatonParser::VardeclarationContext * /*ctx*/) override { }
  virtual void exitVardeclaration(HybridAutomatonParser::VardeclarationContext * /*ctx*/) override { }

  virtual void enterConstantdeclaration(HybridAutomatonParser::ConstantdeclarationContext * /*ctx*/) override { }
  virtual void exitConstantdeclaration(HybridAutomatonParser::ConstantdeclarationContext * /*ctx*/) override { }

  virtual void enterGlobalvardeclaration(HybridAutomatonParser::GlobalvardeclarationContext * /*ctx*/) override { }
  virtual void exitGlobalvardeclaration(HybridAutomatonParser::GlobalvardeclarationContext * /*ctx*/) override { }

  virtual void enterComponent(HybridAutomatonParser::ComponentContext * /*ctx*/) override { }
  virtual void exitComponent(HybridAutomatonParser::ComponentContext * /*ctx*/) override { }

  virtual void enterModes(HybridAutomatonParser::ModesContext * /*ctx*/) override { }
  virtual void exitModes(HybridAutomatonParser::ModesContext * /*ctx*/) override { }

  virtual void enterLocation(HybridAutomatonParser::LocationContext * /*ctx*/) override { }
  virtual void exitLocation(HybridAutomatonParser::LocationContext * /*ctx*/) override { }

  virtual void enterActivities(HybridAutomatonParser::ActivitiesContext * /*ctx*/) override { }
  virtual void exitActivities(HybridAutomatonParser::ActivitiesContext * /*ctx*/) override { }

  virtual void enterInvariants(HybridAutomatonParser::InvariantsContext * /*ctx*/) override { }
  virtual void exitInvariants(HybridAutomatonParser::InvariantsContext * /*ctx*/) override { }

  virtual void enterConstantexpr(HybridAutomatonParser::ConstantexprContext * /*ctx*/) override { }
  virtual void exitConstantexpr(HybridAutomatonParser::ConstantexprContext * /*ctx*/) override { }

  virtual void enterConnector(HybridAutomatonParser::ConnectorContext * /*ctx*/) override { }
  virtual void exitConnector(HybridAutomatonParser::ConnectorContext * /*ctx*/) override { }

  virtual void enterTerm(HybridAutomatonParser::TermContext * /*ctx*/) override { }
  virtual void exitTerm(HybridAutomatonParser::TermContext * /*ctx*/) override { }

  virtual void enterPolynom(HybridAutomatonParser::PolynomContext * /*ctx*/) override { }
  virtual void exitPolynom(HybridAutomatonParser::PolynomContext * /*ctx*/) override { }

  virtual void enterInterval(HybridAutomatonParser::IntervalContext * /*ctx*/) override { }
  virtual void exitInterval(HybridAutomatonParser::IntervalContext * /*ctx*/) override { }

  virtual void enterEquation(HybridAutomatonParser::EquationContext * /*ctx*/) override { }
  virtual void exitEquation(HybridAutomatonParser::EquationContext * /*ctx*/) override { }

  virtual void enterConstraint(HybridAutomatonParser::ConstraintContext * /*ctx*/) override { }
  virtual void exitConstraint(HybridAutomatonParser::ConstraintContext * /*ctx*/) override { }

  virtual void enterIntervalexpr(HybridAutomatonParser::IntervalexprContext * /*ctx*/) override { }
  virtual void exitIntervalexpr(HybridAutomatonParser::IntervalexprContext * /*ctx*/) override { }

  virtual void enterConstrset(HybridAutomatonParser::ConstrsetContext * /*ctx*/) override { }
  virtual void exitConstrset(HybridAutomatonParser::ConstrsetContext * /*ctx*/) override { }

  virtual void enterReplacedexpr(HybridAutomatonParser::ReplacedexprContext * /*ctx*/) override { }
  virtual void exitReplacedexpr(HybridAutomatonParser::ReplacedexprContext * /*ctx*/) override { }

  virtual void enterInit(HybridAutomatonParser::InitContext * /*ctx*/) override { }
  virtual void exitInit(HybridAutomatonParser::InitContext * /*ctx*/) override { }

  virtual void enterInitstate(HybridAutomatonParser::InitstateContext * /*ctx*/) override { }
  virtual void exitInitstate(HybridAutomatonParser::InitstateContext * /*ctx*/) override { }

  virtual void enterUnsafeset(HybridAutomatonParser::UnsafesetContext * /*ctx*/) override { }
  virtual void exitUnsafeset(HybridAutomatonParser::UnsafesetContext * /*ctx*/) override { }

  virtual void enterLbadstate(HybridAutomatonParser::LbadstateContext * /*ctx*/) override { }
  virtual void exitLbadstate(HybridAutomatonParser::LbadstateContext * /*ctx*/) override { }

  virtual void enterGbadstate(HybridAutomatonParser::GbadstateContext * /*ctx*/) override { }
  virtual void exitGbadstate(HybridAutomatonParser::GbadstateContext * /*ctx*/) override { }

  virtual void enterJumps(HybridAutomatonParser::JumpsContext * /*ctx*/) override { }
  virtual void exitJumps(HybridAutomatonParser::JumpsContext * /*ctx*/) override { }

  virtual void enterTransition(HybridAutomatonParser::TransitionContext * /*ctx*/) override { }
  virtual void exitTransition(HybridAutomatonParser::TransitionContext * /*ctx*/) override { }

  virtual void enterFromto(HybridAutomatonParser::FromtoContext * /*ctx*/) override { }
  virtual void exitFromto(HybridAutomatonParser::FromtoContext * /*ctx*/) override { }

  virtual void enterUrgent(HybridAutomatonParser::UrgentContext * /*ctx*/) override { }
  virtual void exitUrgent(HybridAutomatonParser::UrgentContext * /*ctx*/) override { }

  virtual void enterGuard(HybridAutomatonParser::GuardContext * /*ctx*/) override { }
  virtual void exitGuard(HybridAutomatonParser::GuardContext * /*ctx*/) override { }

  virtual void enterAllocation(HybridAutomatonParser::AllocationContext * /*ctx*/) override { }
  virtual void exitAllocation(HybridAutomatonParser::AllocationContext * /*ctx*/) override { }

  virtual void enterResetfct(HybridAutomatonParser::ResetfctContext * /*ctx*/) override { }
  virtual void exitResetfct(HybridAutomatonParser::ResetfctContext * /*ctx*/) override { }

  virtual void enterAggregation(HybridAutomatonParser::AggregationContext * /*ctx*/) override { }
  virtual void exitAggregation(HybridAutomatonParser::AggregationContext * /*ctx*/) override { }

  virtual void enterLabels(HybridAutomatonParser::LabelsContext * /*ctx*/) override { }
  virtual void exitLabels(HybridAutomatonParser::LabelsContext * /*ctx*/) override { }

  virtual void enterLabel(HybridAutomatonParser::LabelContext * /*ctx*/) override { }
  virtual void exitLabel(HybridAutomatonParser::LabelContext * /*ctx*/) override { }

  virtual void enterSetting(HybridAutomatonParser::SettingContext * /*ctx*/) override { }
  virtual void exitSetting(HybridAutomatonParser::SettingContext * /*ctx*/) override { }

  virtual void enterFixedsteps(HybridAutomatonParser::FixedstepsContext * /*ctx*/) override { }
  virtual void exitFixedsteps(HybridAutomatonParser::FixedstepsContext * /*ctx*/) override { }

  virtual void enterTime(HybridAutomatonParser::TimeContext * /*ctx*/) override { }
  virtual void exitTime(HybridAutomatonParser::TimeContext * /*ctx*/) override { }

  virtual void enterPlotsetting(HybridAutomatonParser::PlotsettingContext * /*ctx*/) override { }
  virtual void exitPlotsetting(HybridAutomatonParser::PlotsettingContext * /*ctx*/) override { }

  virtual void enterFilename(HybridAutomatonParser::FilenameContext * /*ctx*/) override { }
  virtual void exitFilename(HybridAutomatonParser::FilenameContext * /*ctx*/) override { }

  virtual void enterMaxjumps(HybridAutomatonParser::MaxjumpsContext * /*ctx*/) override { }
  virtual void exitMaxjumps(HybridAutomatonParser::MaxjumpsContext * /*ctx*/) override { }

  virtual void enterPrint(HybridAutomatonParser::PrintContext * /*ctx*/) override { }
  virtual void exitPrint(HybridAutomatonParser::PrintContext * /*ctx*/) override { }

  virtual void enterRemainder(HybridAutomatonParser::RemainderContext * /*ctx*/) override { }
  virtual void exitRemainder(HybridAutomatonParser::RemainderContext * /*ctx*/) override { }

  virtual void enterIdentity(HybridAutomatonParser::IdentityContext * /*ctx*/) override { }
  virtual void exitIdentity(HybridAutomatonParser::IdentityContext * /*ctx*/) override { }

  virtual void enterFixedorders(HybridAutomatonParser::FixedordersContext * /*ctx*/) override { }
  virtual void exitFixedorders(HybridAutomatonParser::FixedordersContext * /*ctx*/) override { }

  virtual void enterCutoff(HybridAutomatonParser::CutoffContext * /*ctx*/) override { }
  virtual void exitCutoff(HybridAutomatonParser::CutoffContext * /*ctx*/) override { }

  virtual void enterPrecision(HybridAutomatonParser::PrecisionContext * /*ctx*/) override { }
  virtual void exitPrecision(HybridAutomatonParser::PrecisionContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

