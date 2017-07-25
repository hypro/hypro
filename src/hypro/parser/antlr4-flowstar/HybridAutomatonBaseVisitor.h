
// Generated from HybridAutomaton.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "HybridAutomatonVisitor.h"


/**
 * This class provides an empty implementation of HybridAutomatonVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  HybridAutomatonBaseVisitor : public HybridAutomatonVisitor {
public:

  virtual antlrcpp::Any visitStart(HybridAutomatonParser::StartContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVardeclaration(HybridAutomatonParser::VardeclarationContext *ctx) override {
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

  virtual antlrcpp::Any visitTerm(HybridAutomatonParser::TermContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPolynom(HybridAutomatonParser::PolynomContext *ctx) override {
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


};

