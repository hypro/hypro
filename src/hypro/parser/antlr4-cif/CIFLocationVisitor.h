
// Generated from CIFLocation.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "CIFLocationParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by CIFLocationParser.
 */
class  CIFLocationVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by CIFLocationParser.
   */
    virtual antlrcpp::Any visitLocations(CIFLocationParser::LocationsContext *context) = 0;

    virtual antlrcpp::Any visitLoc(CIFLocationParser::LocContext *context) = 0;

    virtual antlrcpp::Any visitLocId(CIFLocationParser::LocIdContext *context) = 0;

    virtual antlrcpp::Any visitLocElem(CIFLocationParser::LocElemContext *context) = 0;

    virtual antlrcpp::Any visitLocIdElem(CIFLocationParser::LocIdElemContext *context) = 0;

    virtual antlrcpp::Any visitLocationElements(CIFLocationParser::LocationElementsContext *context) = 0;

    virtual antlrcpp::Any visitLocElemInitialFlag(CIFLocationParser::LocElemInitialFlagContext *context) = 0;

    virtual antlrcpp::Any visitLocElemInitialFlagExpr(CIFLocationParser::LocElemInitialFlagExprContext *context) = 0;

    virtual antlrcpp::Any visitLocElemInv(CIFLocationParser::LocElemInvContext *context) = 0;

    virtual antlrcpp::Any visitLocElemEqs(CIFLocationParser::LocElemEqsContext *context) = 0;

    virtual antlrcpp::Any visitLocElemMarked(CIFLocationParser::LocElemMarkedContext *context) = 0;

    virtual antlrcpp::Any visitLocElemMarkedExpr(CIFLocationParser::LocElemMarkedExprContext *context) = 0;

    virtual antlrcpp::Any visitLocElemUrgent(CIFLocationParser::LocElemUrgentContext *context) = 0;

    virtual antlrcpp::Any visitLocElemEdgeTo(CIFLocationParser::LocElemEdgeToContext *context) = 0;

    virtual antlrcpp::Any visitLocElemLoop(CIFLocationParser::LocElemLoopContext *context) = 0;

    virtual antlrcpp::Any visitCoreEdge(CIFLocationParser::CoreEdgeContext *context) = 0;

    virtual antlrcpp::Any visitOptEdgeGuard(CIFLocationParser::OptEdgeGuardContext *context) = 0;

    virtual antlrcpp::Any visitOptEdgeUrgent(CIFLocationParser::OptEdgeUrgentContext *context) = 0;

    virtual antlrcpp::Any visitOptEdgeUpdate(CIFLocationParser::OptEdgeUpdateContext *context) = 0;

    virtual antlrcpp::Any visitEdgeEvents(CIFLocationParser::EdgeEventsContext *context) = 0;

    virtual antlrcpp::Any visitEdgeEvent(CIFLocationParser::EdgeEventContext *context) = 0;

    virtual antlrcpp::Any visitInvariantDecls(CIFLocationParser::InvariantDeclsContext *context) = 0;

    virtual antlrcpp::Any visitInvariants(CIFLocationParser::InvariantsContext *context) = 0;

    virtual antlrcpp::Any visitInvExpr(CIFLocationParser::InvExprContext *context) = 0;

    virtual antlrcpp::Any visitInvNeeds(CIFLocationParser::InvNeedsContext *context) = 0;

    virtual antlrcpp::Any visitInvNeedsSet(CIFLocationParser::InvNeedsSetContext *context) = 0;

    virtual antlrcpp::Any visitInvDisables(CIFLocationParser::InvDisablesContext *context) = 0;

    virtual antlrcpp::Any visitInvDisablesSet(CIFLocationParser::InvDisablesSetContext *context) = 0;

    virtual antlrcpp::Any visitUpdates(CIFLocationParser::UpdatesContext *context) = 0;

    virtual antlrcpp::Any visitUpdateNonIf(CIFLocationParser::UpdateNonIfContext *context) = 0;

    virtual antlrcpp::Any visitUpdateIf(CIFLocationParser::UpdateIfContext *context) = 0;

    virtual antlrcpp::Any visitOptElifUpdates(CIFLocationParser::OptElifUpdatesContext *context) = 0;

    virtual antlrcpp::Any visitOptElseUpdate(CIFLocationParser::OptElseUpdateContext *context) = 0;

    virtual antlrcpp::Any visitAdressables(CIFLocationParser::AdressablesContext *context) = 0;

    virtual antlrcpp::Any visitAdressableId(CIFLocationParser::AdressableIdContext *context) = 0;

    virtual antlrcpp::Any visitAdressableProj(CIFLocationParser::AdressableProjContext *context) = 0;

    virtual antlrcpp::Any visitAdressablePair(CIFLocationParser::AdressablePairContext *context) = 0;

    virtual antlrcpp::Any visitProjections(CIFLocationParser::ProjectionsContext *context) = 0;

    virtual antlrcpp::Any visitProjection(CIFLocationParser::ProjectionContext *context) = 0;

    virtual antlrcpp::Any visitExpressions(CIFLocationParser::ExpressionsContext *context) = 0;

    virtual antlrcpp::Any visitOptExpression(CIFLocationParser::OptExpressionContext *context) = 0;

    virtual antlrcpp::Any visitExpression(CIFLocationParser::ExpressionContext *context) = 0;

    virtual antlrcpp::Any visitEquations(CIFLocationParser::EquationsContext *context) = 0;

    virtual antlrcpp::Any visitEquationDerivate(CIFLocationParser::EquationDerivateContext *context) = 0;

    virtual antlrcpp::Any visitEquationNonDerivate(CIFLocationParser::EquationNonDerivateContext *context) = 0;

    virtual antlrcpp::Any visitOrExpression(CIFLocationParser::OrExpressionContext *context) = 0;

    virtual antlrcpp::Any visitAndExpression(CIFLocationParser::AndExpressionContext *context) = 0;

    virtual antlrcpp::Any visitCompareExpression(CIFLocationParser::CompareExpressionContext *context) = 0;

    virtual antlrcpp::Any visitAddExpression(CIFLocationParser::AddExpressionContext *context) = 0;

    virtual antlrcpp::Any visitMulExpression(CIFLocationParser::MulExpressionContext *context) = 0;

    virtual antlrcpp::Any visitUnaryExprFunc(CIFLocationParser::UnaryExprFuncContext *context) = 0;

    virtual antlrcpp::Any visitUnaryExprMinus(CIFLocationParser::UnaryExprMinusContext *context) = 0;

    virtual antlrcpp::Any visitUnaryExprPlus(CIFLocationParser::UnaryExprPlusContext *context) = 0;

    virtual antlrcpp::Any visitUnaryExpr(CIFLocationParser::UnaryExprContext *context) = 0;

    virtual antlrcpp::Any visitFuncExpression(CIFLocationParser::FuncExpressionContext *context) = 0;

    virtual antlrcpp::Any visitExprFact(CIFLocationParser::ExprFactContext *context) = 0;

    virtual antlrcpp::Any visitExprFactNumber(CIFLocationParser::ExprFactNumberContext *context) = 0;

    virtual antlrcpp::Any visitExprFactRealNumber(CIFLocationParser::ExprFactRealNumberContext *context) = 0;

    virtual antlrcpp::Any visitExprFactName(CIFLocationParser::ExprFactNameContext *context) = 0;

    virtual antlrcpp::Any visitNonEmptySetExpression(CIFLocationParser::NonEmptySetExpressionContext *context) = 0;

    virtual antlrcpp::Any visitDictPairs(CIFLocationParser::DictPairsContext *context) = 0;

    virtual antlrcpp::Any visitOptElifExprs(CIFLocationParser::OptElifExprsContext *context) = 0;

    virtual antlrcpp::Any visitSwitchBody(CIFLocationParser::SwitchBodyContext *context) = 0;

    virtual antlrcpp::Any visitSwitchCases(CIFLocationParser::SwitchCasesContext *context) = 0;

    virtual antlrcpp::Any visitTypes(CIFLocationParser::TypesContext *context) = 0;

    virtual antlrcpp::Any visitType(CIFLocationParser::TypeContext *context) = 0;

    virtual antlrcpp::Any visitFields(CIFLocationParser::FieldsContext *context) = 0;

    virtual antlrcpp::Any visitField(CIFLocationParser::FieldContext *context) = 0;

    virtual antlrcpp::Any visitNameSet(CIFLocationParser::NameSetContext *context) = 0;

    virtual antlrcpp::Any visitNames(CIFLocationParser::NamesContext *context) = 0;

    virtual antlrcpp::Any visitName(CIFLocationParser::NameContext *context) = 0;

    virtual antlrcpp::Any visitOptSupKind(CIFLocationParser::OptSupKindContext *context) = 0;

    virtual antlrcpp::Any visitSupKind(CIFLocationParser::SupKindContext *context) = 0;

    virtual antlrcpp::Any visitIdentifier(CIFLocationParser::IdentifierContext *context) = 0;

    virtual antlrcpp::Any visitStringToken(CIFLocationParser::StringTokenContext *context) = 0;

    virtual antlrcpp::Any visitStdLibFunction(CIFLocationParser::StdLibFunctionContext *context) = 0;


};

