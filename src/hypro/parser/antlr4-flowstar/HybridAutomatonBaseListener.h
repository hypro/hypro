
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

  virtual void enterVardeclaration(HybridAutomatonParser::VardeclarationContext * /*ctx*/) override { }
  virtual void exitVardeclaration(HybridAutomatonParser::VardeclarationContext * /*ctx*/) override { }

  virtual void enterModes(HybridAutomatonParser::ModesContext * /*ctx*/) override { }
  virtual void exitModes(HybridAutomatonParser::ModesContext * /*ctx*/) override { }

  virtual void enterLocation(HybridAutomatonParser::LocationContext * /*ctx*/) override { }
  virtual void exitLocation(HybridAutomatonParser::LocationContext * /*ctx*/) override { }

  virtual void enterActivities(HybridAutomatonParser::ActivitiesContext * /*ctx*/) override { }
  virtual void exitActivities(HybridAutomatonParser::ActivitiesContext * /*ctx*/) override { }

  virtual void enterInvariants(HybridAutomatonParser::InvariantsContext * /*ctx*/) override { }
  virtual void exitInvariants(HybridAutomatonParser::InvariantsContext * /*ctx*/) override { }

  virtual void enterTerm(HybridAutomatonParser::TermContext * /*ctx*/) override { }
  virtual void exitTerm(HybridAutomatonParser::TermContext * /*ctx*/) override { }

  virtual void enterEquation(HybridAutomatonParser::EquationContext * /*ctx*/) override { }
  virtual void exitEquation(HybridAutomatonParser::EquationContext * /*ctx*/) override { }

  virtual void enterBoolexpr(HybridAutomatonParser::BoolexprContext * /*ctx*/) override { }
  virtual void exitBoolexpr(HybridAutomatonParser::BoolexprContext * /*ctx*/) override { }

  virtual void enterIntervalexpr(HybridAutomatonParser::IntervalexprContext * /*ctx*/) override { }
  virtual void exitIntervalexpr(HybridAutomatonParser::IntervalexprContext * /*ctx*/) override { }

  virtual void enterFormula(HybridAutomatonParser::FormulaContext * /*ctx*/) override { }
  virtual void exitFormula(HybridAutomatonParser::FormulaContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

