
// Generated from Location.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "LocationParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by LocationParser.
 */
class  LocationVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by LocationParser.
   */
    virtual antlrcpp::Any visitModes(LocationParser::ModesContext *context) = 0;

    virtual antlrcpp::Any visitLocation(LocationParser::LocationContext *context) = 0;

    virtual antlrcpp::Any visitActivities(LocationParser::ActivitiesContext *context) = 0;

    virtual antlrcpp::Any visitInvariants(LocationParser::InvariantsContext *context) = 0;

    virtual antlrcpp::Any visitTerm(LocationParser::TermContext *context) = 0;

    virtual antlrcpp::Any visitPolynom(LocationParser::PolynomContext *context) = 0;

    virtual antlrcpp::Any visitEquation(LocationParser::EquationContext *context) = 0;

    virtual antlrcpp::Any visitConstraint(LocationParser::ConstraintContext *context) = 0;

    virtual antlrcpp::Any visitInterval(LocationParser::IntervalContext *context) = 0;

    virtual antlrcpp::Any visitIntervalexpr(LocationParser::IntervalexprContext *context) = 0;


};

