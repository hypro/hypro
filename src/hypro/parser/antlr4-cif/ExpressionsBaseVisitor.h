
// Generated from Expressions.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "ExpressionsVisitor.h"


/**
 * This class provides an empty implementation of ExpressionsVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  ExpressionsBaseVisitor : public ExpressionsVisitor {
public:

  virtual antlrcpp::Any visitExpressions(ExpressionsParser::ExpressionsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOptExpression(ExpressionsParser::OptExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExpression(ExpressionsParser::ExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEquations(ExpressionsParser::EquationsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEquationDerivate(ExpressionsParser::EquationDerivateContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEquationNonDerivate(ExpressionsParser::EquationNonDerivateContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOrExpression(ExpressionsParser::OrExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAndExpression(ExpressionsParser::AndExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCompareExpression(ExpressionsParser::CompareExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAddExpression(ExpressionsParser::AddExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMulExpression(ExpressionsParser::MulExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUnaryExprFunc(ExpressionsParser::UnaryExprFuncContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUnaryExprMinus(ExpressionsParser::UnaryExprMinusContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUnaryExprPlus(ExpressionsParser::UnaryExprPlusContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUnaryExpr(ExpressionsParser::UnaryExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFuncExpression(ExpressionsParser::FuncExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprFact(ExpressionsParser::ExprFactContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprFactNumber(ExpressionsParser::ExprFactNumberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprFactRealNumber(ExpressionsParser::ExprFactRealNumberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprFactName(ExpressionsParser::ExprFactNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNonEmptySetExpression(ExpressionsParser::NonEmptySetExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDictPairs(ExpressionsParser::DictPairsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOptElifExprs(ExpressionsParser::OptElifExprsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSwitchBody(ExpressionsParser::SwitchBodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSwitchCases(ExpressionsParser::SwitchCasesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTypes(ExpressionsParser::TypesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitType(ExpressionsParser::TypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFields(ExpressionsParser::FieldsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitField(ExpressionsParser::FieldContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNameSet(ExpressionsParser::NameSetContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNames(ExpressionsParser::NamesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitName(ExpressionsParser::NameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOptSupKind(ExpressionsParser::OptSupKindContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSupKind(ExpressionsParser::SupKindContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIdentifier(ExpressionsParser::IdentifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStringToken(ExpressionsParser::StringTokenContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStdLibFunction(ExpressionsParser::StdLibFunctionContext *ctx) override {
    return visitChildren(ctx);
  }


};

