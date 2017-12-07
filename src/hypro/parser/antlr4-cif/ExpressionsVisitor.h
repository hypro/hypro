
// Generated from Expressions.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "ExpressionsParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by ExpressionsParser.
 */
class  ExpressionsVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by ExpressionsParser.
   */
    virtual antlrcpp::Any visitExpressions(ExpressionsParser::ExpressionsContext *context) = 0;

    virtual antlrcpp::Any visitOptExpression(ExpressionsParser::OptExpressionContext *context) = 0;

    virtual antlrcpp::Any visitExpression(ExpressionsParser::ExpressionContext *context) = 0;

    virtual antlrcpp::Any visitEquations(ExpressionsParser::EquationsContext *context) = 0;

    virtual antlrcpp::Any visitEquationDerivate(ExpressionsParser::EquationDerivateContext *context) = 0;

    virtual antlrcpp::Any visitEquationNonDerivate(ExpressionsParser::EquationNonDerivateContext *context) = 0;

    virtual antlrcpp::Any visitOrExpression(ExpressionsParser::OrExpressionContext *context) = 0;

    virtual antlrcpp::Any visitAndExpression(ExpressionsParser::AndExpressionContext *context) = 0;

    virtual antlrcpp::Any visitCompareExpression(ExpressionsParser::CompareExpressionContext *context) = 0;

    virtual antlrcpp::Any visitAddExpression(ExpressionsParser::AddExpressionContext *context) = 0;

    virtual antlrcpp::Any visitMulExpression(ExpressionsParser::MulExpressionContext *context) = 0;

    virtual antlrcpp::Any visitUnaryExprFunc(ExpressionsParser::UnaryExprFuncContext *context) = 0;

    virtual antlrcpp::Any visitUnaryExprMinus(ExpressionsParser::UnaryExprMinusContext *context) = 0;

    virtual antlrcpp::Any visitUnaryExprPlus(ExpressionsParser::UnaryExprPlusContext *context) = 0;

    virtual antlrcpp::Any visitUnaryExpr(ExpressionsParser::UnaryExprContext *context) = 0;

    virtual antlrcpp::Any visitFuncExpression(ExpressionsParser::FuncExpressionContext *context) = 0;

    virtual antlrcpp::Any visitExprFact(ExpressionsParser::ExprFactContext *context) = 0;

    virtual antlrcpp::Any visitExprFactNumber(ExpressionsParser::ExprFactNumberContext *context) = 0;

    virtual antlrcpp::Any visitExprFactRealNumber(ExpressionsParser::ExprFactRealNumberContext *context) = 0;

    virtual antlrcpp::Any visitExprFactName(ExpressionsParser::ExprFactNameContext *context) = 0;

    virtual antlrcpp::Any visitNonEmptySetExpression(ExpressionsParser::NonEmptySetExpressionContext *context) = 0;

    virtual antlrcpp::Any visitDictPairs(ExpressionsParser::DictPairsContext *context) = 0;

    virtual antlrcpp::Any visitOptElifExprs(ExpressionsParser::OptElifExprsContext *context) = 0;

    virtual antlrcpp::Any visitSwitchBody(ExpressionsParser::SwitchBodyContext *context) = 0;

    virtual antlrcpp::Any visitSwitchCases(ExpressionsParser::SwitchCasesContext *context) = 0;

    virtual antlrcpp::Any visitTypes(ExpressionsParser::TypesContext *context) = 0;

    virtual antlrcpp::Any visitType(ExpressionsParser::TypeContext *context) = 0;

    virtual antlrcpp::Any visitFields(ExpressionsParser::FieldsContext *context) = 0;

    virtual antlrcpp::Any visitField(ExpressionsParser::FieldContext *context) = 0;

    virtual antlrcpp::Any visitNameSet(ExpressionsParser::NameSetContext *context) = 0;

    virtual antlrcpp::Any visitNames(ExpressionsParser::NamesContext *context) = 0;

    virtual antlrcpp::Any visitName(ExpressionsParser::NameContext *context) = 0;

    virtual antlrcpp::Any visitOptSupKind(ExpressionsParser::OptSupKindContext *context) = 0;

    virtual antlrcpp::Any visitSupKind(ExpressionsParser::SupKindContext *context) = 0;

    virtual antlrcpp::Any visitIdentifier(ExpressionsParser::IdentifierContext *context) = 0;

    virtual antlrcpp::Any visitStringToken(ExpressionsParser::StringTokenContext *context) = 0;

    virtual antlrcpp::Any visitStdLibFunction(ExpressionsParser::StdLibFunctionContext *context) = 0;


};

