
// Generated from Formula.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "FormulaVisitor.h"


/**
 * This class provides an empty implementation of FormulaVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  FormulaBaseVisitor : public FormulaVisitor {
public:

  virtual antlrcpp::Any visitTerm(FormulaParser::TermContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPolynom(FormulaParser::PolynomContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEquation(FormulaParser::EquationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConstraint(FormulaParser::ConstraintContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInterval(FormulaParser::IntervalContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIntervalexpr(FormulaParser::IntervalexprContext *ctx) override {
    return visitChildren(ctx);
  }


};

