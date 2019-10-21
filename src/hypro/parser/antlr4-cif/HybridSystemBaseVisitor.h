
// Generated from HybridSystem.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "HybridSystemVisitor.h"


namespace hypro {

/**
 * This class provides an empty implementation of HybridSystemVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  HybridSystemBaseVisitor : public HybridSystemVisitor {
public:

  virtual antlrcpp::Any visitSpecification(HybridSystemParser::SpecificationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGroupBody(HybridSystemParser::GroupBodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAutomatonBody(HybridSystemParser::AutomatonBodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOptGroupDecls(HybridSystemParser::OptGroupDeclsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGroupDecl(HybridSystemParser::GroupDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOptAutDecls(HybridSystemParser::OptAutDeclsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAutDecl(HybridSystemParser::AutDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDecl(HybridSystemParser::DeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitImports(HybridSystemParser::ImportsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTypeDefs(HybridSystemParser::TypeDefsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEnumDefs(HybridSystemParser::EnumDefsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConstantDefs(HybridSystemParser::ConstantDefsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAlgVarsDefs(HybridSystemParser::AlgVarsDefsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFuncParams(HybridSystemParser::FuncParamsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFuncParamDecls(HybridSystemParser::FuncParamDeclsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFuncBody(HybridSystemParser::FuncBodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFuncVarDecls(HybridSystemParser::FuncVarDeclsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFuncVarDecl(HybridSystemParser::FuncVarDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFuncStatements(HybridSystemParser::FuncStatementsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFuncStatement(HybridSystemParser::FuncStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOptElifFuncStats(HybridSystemParser::OptElifFuncStatsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOptElseFuncStat(HybridSystemParser::OptElseFuncStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEvents(HybridSystemParser::EventsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitActualParms(HybridSystemParser::ActualParmsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFormalParms(HybridSystemParser::FormalParmsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFormalDecls(HybridSystemParser::FormalDeclsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFormalDeclaration(HybridSystemParser::FormalDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDiscDecls(HybridSystemParser::DiscDeclsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDiscDecl(HybridSystemParser::DiscDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitContDecls(HybridSystemParser::ContDeclsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitContDecl(HybridSystemParser::ContDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOptDerivate(HybridSystemParser::OptDerivateContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOptControllability(HybridSystemParser::OptControllabilityContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitControllability(HybridSystemParser::ControllabilityContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEventType(HybridSystemParser::EventTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExpressions(HybridSystemParser::ExpressionsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOptExpression(HybridSystemParser::OptExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExpression(HybridSystemParser::ExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEquations(HybridSystemParser::EquationsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEquationDerivate(HybridSystemParser::EquationDerivateContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEquationNonDerivate(HybridSystemParser::EquationNonDerivateContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOrExpression(HybridSystemParser::OrExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAndExpression(HybridSystemParser::AndExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCompareExpression(HybridSystemParser::CompareExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAddExpression(HybridSystemParser::AddExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMulExpression(HybridSystemParser::MulExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUnaryExprFunc(HybridSystemParser::UnaryExprFuncContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUnaryExprMinus(HybridSystemParser::UnaryExprMinusContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUnaryExprPlus(HybridSystemParser::UnaryExprPlusContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUnaryExpr(HybridSystemParser::UnaryExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFuncExpression(HybridSystemParser::FuncExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprFact(HybridSystemParser::ExprFactContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprFactNumber(HybridSystemParser::ExprFactNumberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprFactRealNumber(HybridSystemParser::ExprFactRealNumberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprFactName(HybridSystemParser::ExprFactNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNonEmptySetExpression(HybridSystemParser::NonEmptySetExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDictPairs(HybridSystemParser::DictPairsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOptElifExprs(HybridSystemParser::OptElifExprsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSwitchBody(HybridSystemParser::SwitchBodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSwitchCases(HybridSystemParser::SwitchCasesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTypes(HybridSystemParser::TypesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitType(HybridSystemParser::TypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFields(HybridSystemParser::FieldsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitField(HybridSystemParser::FieldContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNameSet(HybridSystemParser::NameSetContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNames(HybridSystemParser::NamesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitName(HybridSystemParser::NameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOptSupKind(HybridSystemParser::OptSupKindContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSupKind(HybridSystemParser::SupKindContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIdentifier(HybridSystemParser::IdentifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStringToken(HybridSystemParser::StringTokenContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStdLibFunction(HybridSystemParser::StdLibFunctionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLocations(HybridSystemParser::LocationsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLoc(HybridSystemParser::LocContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLocId(HybridSystemParser::LocIdContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLocElem(HybridSystemParser::LocElemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLocIdElem(HybridSystemParser::LocIdElemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLocationElements(HybridSystemParser::LocationElementsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLocElemInitialFlag(HybridSystemParser::LocElemInitialFlagContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLocElemInitialFlagExpr(HybridSystemParser::LocElemInitialFlagExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLocElemInv(HybridSystemParser::LocElemInvContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLocElemEqs(HybridSystemParser::LocElemEqsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLocElemMarked(HybridSystemParser::LocElemMarkedContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLocElemMarkedExpr(HybridSystemParser::LocElemMarkedExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLocElemUrgent(HybridSystemParser::LocElemUrgentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLocElemEdgeTo(HybridSystemParser::LocElemEdgeToContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLocElemLoop(HybridSystemParser::LocElemLoopContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCoreEdge(HybridSystemParser::CoreEdgeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOptEdgeGuard(HybridSystemParser::OptEdgeGuardContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOptEdgeUrgent(HybridSystemParser::OptEdgeUrgentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOptEdgeUpdate(HybridSystemParser::OptEdgeUpdateContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEdgeEvents(HybridSystemParser::EdgeEventsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEdgeEvent(HybridSystemParser::EdgeEventContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInvariantDecls(HybridSystemParser::InvariantDeclsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInvariants(HybridSystemParser::InvariantsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInvExpr(HybridSystemParser::InvExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInvNeeds(HybridSystemParser::InvNeedsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInvNeedsSet(HybridSystemParser::InvNeedsSetContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInvDisables(HybridSystemParser::InvDisablesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInvDisablesSet(HybridSystemParser::InvDisablesSetContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUpdates(HybridSystemParser::UpdatesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUpdateNonIf(HybridSystemParser::UpdateNonIfContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUpdateIf(HybridSystemParser::UpdateIfContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOptElifUpdates(HybridSystemParser::OptElifUpdatesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOptElseUpdate(HybridSystemParser::OptElseUpdateContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAdressables(HybridSystemParser::AdressablesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAdressableId(HybridSystemParser::AdressableIdContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAdressableProj(HybridSystemParser::AdressableProjContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAdressablePair(HybridSystemParser::AdressablePairContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProjections(HybridSystemParser::ProjectionsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProjection(HybridSystemParser::ProjectionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOptIoDecls(HybridSystemParser::OptIoDeclsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIoDecls(HybridSystemParser::IoDeclsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSvgFile(HybridSystemParser::SvgFileContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOptSvgFile(HybridSystemParser::OptSvgFileContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSvgCopy(HybridSystemParser::SvgCopyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOptSvgCopyPre(HybridSystemParser::OptSvgCopyPreContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOptSvgCopyPost(HybridSystemParser::OptSvgCopyPostContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSvgMove(HybridSystemParser::SvgMoveContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSvgOut(HybridSystemParser::SvgOutContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSvgAttr(HybridSystemParser::SvgAttrContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSvgIn(HybridSystemParser::SvgInContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSvgInEvent(HybridSystemParser::SvgInEventContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOptSvgInEventElifs(HybridSystemParser::OptSvgInEventElifsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSvgInEventElifs(HybridSystemParser::SvgInEventElifsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPrintFile(HybridSystemParser::PrintFileContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPrint(HybridSystemParser::PrintContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPrintTxt(HybridSystemParser::PrintTxtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOptPrintFors(HybridSystemParser::OptPrintForsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPrintFors(HybridSystemParser::PrintForsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPrintFor(HybridSystemParser::PrintForContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOptPrintWhen(HybridSystemParser::OptPrintWhenContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOptPrintFile(HybridSystemParser::OptPrintFileContext *ctx) override {
    return visitChildren(ctx);
  }


};

}  // namespace hypro
