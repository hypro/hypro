
// Generated from Formula.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "FormulaParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by FormulaParser.
 */
class  FormulaVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by FormulaParser.
   */
    virtual antlrcpp::Any visitTerm(FormulaParser::TermContext *context) = 0;

    virtual antlrcpp::Any visitPolynom(FormulaParser::PolynomContext *context) = 0;

    virtual antlrcpp::Any visitEquation(FormulaParser::EquationContext *context) = 0;

    virtual antlrcpp::Any visitConstraint(FormulaParser::ConstraintContext *context) = 0;

    virtual antlrcpp::Any visitInterval(FormulaParser::IntervalContext *context) = 0;

    virtual antlrcpp::Any visitIntervalexpr(FormulaParser::IntervalexprContext *context) = 0;


};

