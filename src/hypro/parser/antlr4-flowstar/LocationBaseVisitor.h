
// Generated from Location.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "LocationVisitor.h"


/**
 * This class provides an empty implementation of LocationVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  LocationBaseVisitor : public LocationVisitor {
public:

  virtual antlrcpp::Any visitModes(LocationParser::ModesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLocation(LocationParser::LocationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitActivities(LocationParser::ActivitiesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInvariants(LocationParser::InvariantsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTerm(LocationParser::TermContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPolynom(LocationParser::PolynomContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEquation(LocationParser::EquationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConstraint(LocationParser::ConstraintContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInterval(LocationParser::IntervalContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIntervalexpr(LocationParser::IntervalexprContext *ctx) override {
    return visitChildren(ctx);
  }


};

