
// Generated from HybridAutomaton.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "HybridAutomatonParser.h"



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

    virtual antlrcpp::Any visitModes(HybridAutomatonParser::ModesContext *context) = 0;

    virtual antlrcpp::Any visitLocation(HybridAutomatonParser::LocationContext *context) = 0;

    virtual antlrcpp::Any visitActivities(HybridAutomatonParser::ActivitiesContext *context) = 0;

    virtual antlrcpp::Any visitInvariants(HybridAutomatonParser::InvariantsContext *context) = 0;

    virtual antlrcpp::Any visitTerm(HybridAutomatonParser::TermContext *context) = 0;

    virtual antlrcpp::Any visitPolynom(HybridAutomatonParser::PolynomContext *context) = 0;

    virtual antlrcpp::Any visitEquation(HybridAutomatonParser::EquationContext *context) = 0;

    virtual antlrcpp::Any visitConstraint(HybridAutomatonParser::ConstraintContext *context) = 0;

    virtual antlrcpp::Any visitInterval(HybridAutomatonParser::IntervalContext *context) = 0;

    virtual antlrcpp::Any visitIntervalexpr(HybridAutomatonParser::IntervalexprContext *context) = 0;


};

