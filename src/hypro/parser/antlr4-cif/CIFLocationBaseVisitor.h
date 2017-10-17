
// Generated from CIFLocation.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "CIFLocationVisitor.h"


/**
 * This class provides an empty implementation of CIFLocationVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  CIFLocationBaseVisitor : public CIFLocationVisitor {
public:

  virtual antlrcpp::Any visitLocations(CIFLocationParser::LocationsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLoc(CIFLocationParser::LocContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLocId(CIFLocationParser::LocIdContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLocElem(CIFLocationParser::LocElemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLocIdElem(CIFLocationParser::LocIdElemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLocationElements(CIFLocationParser::LocationElementsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLocElemInitialFlag(CIFLocationParser::LocElemInitialFlagContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLocElemInitialFlagExpr(CIFLocationParser::LocElemInitialFlagExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLocElemInv(CIFLocationParser::LocElemInvContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLocElemEqs(CIFLocationParser::LocElemEqsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLocElemMarked(CIFLocationParser::LocElemMarkedContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLocElemMarkedExpr(CIFLocationParser::LocElemMarkedExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLocElemUrgent(CIFLocationParser::LocElemUrgentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLocElemEdgeTo(CIFLocationParser::LocElemEdgeToContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLocElemLoop(CIFLocationParser::LocElemLoopContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCoreEdge(CIFLocationParser::CoreEdgeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOptEdgeGuard(CIFLocationParser::OptEdgeGuardContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOptEdgeUrgent(CIFLocationParser::OptEdgeUrgentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOptEdgeUpdate(CIFLocationParser::OptEdgeUpdateContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEdgeEvents(CIFLocationParser::EdgeEventsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEdgeEvent(CIFLocationParser::EdgeEventContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInvariantDecls(CIFLocationParser::InvariantDeclsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInvariants(CIFLocationParser::InvariantsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInvExpr(CIFLocationParser::InvExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInvNeeds(CIFLocationParser::InvNeedsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInvNeedsSet(CIFLocationParser::InvNeedsSetContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInvDisables(CIFLocationParser::InvDisablesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInvDisablesSet(CIFLocationParser::InvDisablesSetContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUpdates(CIFLocationParser::UpdatesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUpdateNonIf(CIFLocationParser::UpdateNonIfContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUpdateIf(CIFLocationParser::UpdateIfContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOptElifUpdates(CIFLocationParser::OptElifUpdatesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOptElseUpdate(CIFLocationParser::OptElseUpdateContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAdressables(CIFLocationParser::AdressablesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAdressableId(CIFLocationParser::AdressableIdContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAdressableProj(CIFLocationParser::AdressableProjContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAdressablePair(CIFLocationParser::AdressablePairContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProjections(CIFLocationParser::ProjectionsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProjection(CIFLocationParser::ProjectionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExpressions(CIFLocationParser::ExpressionsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOptExpression(CIFLocationParser::OptExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExpression(CIFLocationParser::ExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEquations(CIFLocationParser::EquationsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEquationDerivate(CIFLocationParser::EquationDerivateContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEquationNonDerivate(CIFLocationParser::EquationNonDerivateContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOrExpression(CIFLocationParser::OrExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAndExpression(CIFLocationParser::AndExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCompareExpression(CIFLocationParser::CompareExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAddExpression(CIFLocationParser::AddExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMulExpression(CIFLocationParser::MulExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUnaryExprFunc(CIFLocationParser::UnaryExprFuncContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUnaryExprMinus(CIFLocationParser::UnaryExprMinusContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUnaryExprPlus(CIFLocationParser::UnaryExprPlusContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUnaryExpr(CIFLocationParser::UnaryExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFuncExpression(CIFLocationParser::FuncExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprFact(CIFLocationParser::ExprFactContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprFactNumber(CIFLocationParser::ExprFactNumberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprFactRealNumber(CIFLocationParser::ExprFactRealNumberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprFactName(CIFLocationParser::ExprFactNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNonEmptySetExpression(CIFLocationParser::NonEmptySetExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDictPairs(CIFLocationParser::DictPairsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOptElifExprs(CIFLocationParser::OptElifExprsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSwitchBody(CIFLocationParser::SwitchBodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSwitchCases(CIFLocationParser::SwitchCasesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTypes(CIFLocationParser::TypesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitType(CIFLocationParser::TypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFields(CIFLocationParser::FieldsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitField(CIFLocationParser::FieldContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNameSet(CIFLocationParser::NameSetContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNames(CIFLocationParser::NamesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitName(CIFLocationParser::NameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOptSupKind(CIFLocationParser::OptSupKindContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSupKind(CIFLocationParser::SupKindContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIdentifier(CIFLocationParser::IdentifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStringToken(CIFLocationParser::StringTokenContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStdLibFunction(CIFLocationParser::StdLibFunctionContext *ctx) override {
    return visitChildren(ctx);
  }


};

