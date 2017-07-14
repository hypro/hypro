
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

  virtual void enterVardeclaration(HybridAutomatonParser::VardeclarationContext *ctx) = 0;
  virtual void exitVardeclaration(HybridAutomatonParser::VardeclarationContext *ctx) = 0;

  virtual void enterModes(HybridAutomatonParser::ModesContext *ctx) = 0;
  virtual void exitModes(HybridAutomatonParser::ModesContext *ctx) = 0;

  virtual void enterLocation(HybridAutomatonParser::LocationContext *ctx) = 0;
  virtual void exitLocation(HybridAutomatonParser::LocationContext *ctx) = 0;

  virtual void enterActivities(HybridAutomatonParser::ActivitiesContext *ctx) = 0;
  virtual void exitActivities(HybridAutomatonParser::ActivitiesContext *ctx) = 0;

  virtual void enterInvariants(HybridAutomatonParser::InvariantsContext *ctx) = 0;
  virtual void exitInvariants(HybridAutomatonParser::InvariantsContext *ctx) = 0;

  virtual void enterTerm(HybridAutomatonParser::TermContext *ctx) = 0;
  virtual void exitTerm(HybridAutomatonParser::TermContext *ctx) = 0;

  virtual void enterPolynom(HybridAutomatonParser::PolynomContext *ctx) = 0;
  virtual void exitPolynom(HybridAutomatonParser::PolynomContext *ctx) = 0;

  virtual void enterEquation(HybridAutomatonParser::EquationContext *ctx) = 0;
  virtual void exitEquation(HybridAutomatonParser::EquationContext *ctx) = 0;

  virtual void enterConstraint(HybridAutomatonParser::ConstraintContext *ctx) = 0;
  virtual void exitConstraint(HybridAutomatonParser::ConstraintContext *ctx) = 0;

  virtual void enterIntervalexpr(HybridAutomatonParser::IntervalexprContext *ctx) = 0;
  virtual void exitIntervalexpr(HybridAutomatonParser::IntervalexprContext *ctx) = 0;


};

