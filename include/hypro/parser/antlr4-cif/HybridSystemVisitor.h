
/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

// Generated from HybridSystem.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "HybridSystemParser.h"


namespace hypro {

/**
 * This class defines an abstract visitor for a parse tree
 * produced by HybridSystemParser.
 */
    class HybridSystemVisitor : public antlr4::tree::AbstractParseTreeVisitor {
    public:

        /**
         * Visit parse trees produced by HybridSystemParser.
         */
        virtual antlrcpp::Any visitSpecification(HybridSystemParser::SpecificationContext *context) = 0;

        virtual antlrcpp::Any visitGroupBody(HybridSystemParser::GroupBodyContext *context) = 0;

        virtual antlrcpp::Any visitAutomatonBody(HybridSystemParser::AutomatonBodyContext *context) = 0;

        virtual antlrcpp::Any visitOptGroupDecls(HybridSystemParser::OptGroupDeclsContext *context) = 0;

        virtual antlrcpp::Any visitGroupDecl(HybridSystemParser::GroupDeclContext *context) = 0;

        virtual antlrcpp::Any visitOptAutDecls(HybridSystemParser::OptAutDeclsContext *context) = 0;

        virtual antlrcpp::Any visitAutDecl(HybridSystemParser::AutDeclContext *context) = 0;

        virtual antlrcpp::Any visitDecl(HybridSystemParser::DeclContext *context) = 0;

        virtual antlrcpp::Any visitImports(HybridSystemParser::ImportsContext *context) = 0;

        virtual antlrcpp::Any visitTypeDefs(HybridSystemParser::TypeDefsContext *context) = 0;

        virtual antlrcpp::Any visitEnumDefs(HybridSystemParser::EnumDefsContext *context) = 0;

        virtual antlrcpp::Any visitConstantDefs(HybridSystemParser::ConstantDefsContext *context) = 0;

        virtual antlrcpp::Any visitAlgVarsDefs(HybridSystemParser::AlgVarsDefsContext *context) = 0;

        virtual antlrcpp::Any visitFuncParams(HybridSystemParser::FuncParamsContext *context) = 0;

        virtual antlrcpp::Any visitFuncParamDecls(HybridSystemParser::FuncParamDeclsContext *context) = 0;

        virtual antlrcpp::Any visitFuncBody(HybridSystemParser::FuncBodyContext *context) = 0;

        virtual antlrcpp::Any visitFuncVarDecls(HybridSystemParser::FuncVarDeclsContext *context) = 0;

        virtual antlrcpp::Any visitFuncVarDecl(HybridSystemParser::FuncVarDeclContext *context) = 0;

        virtual antlrcpp::Any visitFuncStatements(HybridSystemParser::FuncStatementsContext *context) = 0;

        virtual antlrcpp::Any visitFuncStatement(HybridSystemParser::FuncStatementContext *context) = 0;

        virtual antlrcpp::Any visitOptElifFuncStats(HybridSystemParser::OptElifFuncStatsContext *context) = 0;

        virtual antlrcpp::Any visitOptElseFuncStat(HybridSystemParser::OptElseFuncStatContext *context) = 0;

        virtual antlrcpp::Any visitEvents(HybridSystemParser::EventsContext *context) = 0;

        virtual antlrcpp::Any visitActualParms(HybridSystemParser::ActualParmsContext *context) = 0;

        virtual antlrcpp::Any visitFormalParms(HybridSystemParser::FormalParmsContext *context) = 0;

        virtual antlrcpp::Any visitFormalDecls(HybridSystemParser::FormalDeclsContext *context) = 0;

        virtual antlrcpp::Any visitFormalDeclaration(HybridSystemParser::FormalDeclarationContext *context) = 0;

        virtual antlrcpp::Any visitDiscDecls(HybridSystemParser::DiscDeclsContext *context) = 0;

        virtual antlrcpp::Any visitDiscDecl(HybridSystemParser::DiscDeclContext *context) = 0;

        virtual antlrcpp::Any visitContDecls(HybridSystemParser::ContDeclsContext *context) = 0;

        virtual antlrcpp::Any visitContDecl(HybridSystemParser::ContDeclContext *context) = 0;

        virtual antlrcpp::Any visitOptDerivate(HybridSystemParser::OptDerivateContext *context) = 0;

        virtual antlrcpp::Any visitOptControllability(HybridSystemParser::OptControllabilityContext *context) = 0;

        virtual antlrcpp::Any visitControllability(HybridSystemParser::ControllabilityContext *context) = 0;

        virtual antlrcpp::Any visitEventType(HybridSystemParser::EventTypeContext *context) = 0;

        virtual antlrcpp::Any visitExpressions(HybridSystemParser::ExpressionsContext *context) = 0;

        virtual antlrcpp::Any visitOptExpression(HybridSystemParser::OptExpressionContext *context) = 0;

        virtual antlrcpp::Any visitExpression(HybridSystemParser::ExpressionContext *context) = 0;

        virtual antlrcpp::Any visitEquations(HybridSystemParser::EquationsContext *context) = 0;

        virtual antlrcpp::Any visitEquationDerivate(HybridSystemParser::EquationDerivateContext *context) = 0;

        virtual antlrcpp::Any visitEquationNonDerivate(HybridSystemParser::EquationNonDerivateContext *context) = 0;

        virtual antlrcpp::Any visitOrExpression(HybridSystemParser::OrExpressionContext *context) = 0;

        virtual antlrcpp::Any visitAndExpression(HybridSystemParser::AndExpressionContext *context) = 0;

        virtual antlrcpp::Any visitCompareExpression(HybridSystemParser::CompareExpressionContext *context) = 0;

        virtual antlrcpp::Any visitAddExpression(HybridSystemParser::AddExpressionContext *context) = 0;

        virtual antlrcpp::Any visitMulExpression(HybridSystemParser::MulExpressionContext *context) = 0;

        virtual antlrcpp::Any visitUnaryExprFunc(HybridSystemParser::UnaryExprFuncContext *context) = 0;

        virtual antlrcpp::Any visitUnaryExprMinus(HybridSystemParser::UnaryExprMinusContext *context) = 0;

        virtual antlrcpp::Any visitUnaryExprPlus(HybridSystemParser::UnaryExprPlusContext *context) = 0;

        virtual antlrcpp::Any visitUnaryExpr(HybridSystemParser::UnaryExprContext *context) = 0;

        virtual antlrcpp::Any visitFuncExpression(HybridSystemParser::FuncExpressionContext *context) = 0;

        virtual antlrcpp::Any visitExprFact(HybridSystemParser::ExprFactContext *context) = 0;

        virtual antlrcpp::Any visitExprFactNumber(HybridSystemParser::ExprFactNumberContext *context) = 0;

        virtual antlrcpp::Any visitExprFactRealNumber(HybridSystemParser::ExprFactRealNumberContext *context) = 0;

        virtual antlrcpp::Any visitExprFactName(HybridSystemParser::ExprFactNameContext *context) = 0;

        virtual antlrcpp::Any visitNonEmptySetExpression(HybridSystemParser::NonEmptySetExpressionContext *context) = 0;

        virtual antlrcpp::Any visitDictPairs(HybridSystemParser::DictPairsContext *context) = 0;

        virtual antlrcpp::Any visitOptElifExprs(HybridSystemParser::OptElifExprsContext *context) = 0;

        virtual antlrcpp::Any visitSwitchBody(HybridSystemParser::SwitchBodyContext *context) = 0;

        virtual antlrcpp::Any visitSwitchCases(HybridSystemParser::SwitchCasesContext *context) = 0;

        virtual antlrcpp::Any visitTypes(HybridSystemParser::TypesContext *context) = 0;

        virtual antlrcpp::Any visitType(HybridSystemParser::TypeContext *context) = 0;

        virtual antlrcpp::Any visitFields(HybridSystemParser::FieldsContext *context) = 0;

        virtual antlrcpp::Any visitField(HybridSystemParser::FieldContext *context) = 0;

        virtual antlrcpp::Any visitNameSet(HybridSystemParser::NameSetContext *context) = 0;

        virtual antlrcpp::Any visitNames(HybridSystemParser::NamesContext *context) = 0;

        virtual antlrcpp::Any visitName(HybridSystemParser::NameContext *context) = 0;

        virtual antlrcpp::Any visitOptSupKind(HybridSystemParser::OptSupKindContext *context) = 0;

        virtual antlrcpp::Any visitSupKind(HybridSystemParser::SupKindContext *context) = 0;

        virtual antlrcpp::Any visitIdentifier(HybridSystemParser::IdentifierContext *context) = 0;

        virtual antlrcpp::Any visitStringToken(HybridSystemParser::StringTokenContext *context) = 0;

        virtual antlrcpp::Any visitStdLibFunction(HybridSystemParser::StdLibFunctionContext *context) = 0;

        virtual antlrcpp::Any visitLocations(HybridSystemParser::LocationsContext *context) = 0;

        virtual antlrcpp::Any visitLoc(HybridSystemParser::LocContext *context) = 0;

        virtual antlrcpp::Any visitLocId(HybridSystemParser::LocIdContext *context) = 0;

        virtual antlrcpp::Any visitLocElem(HybridSystemParser::LocElemContext *context) = 0;

        virtual antlrcpp::Any visitLocIdElem(HybridSystemParser::LocIdElemContext *context) = 0;

        virtual antlrcpp::Any visitLocationElements(HybridSystemParser::LocationElementsContext *context) = 0;

        virtual antlrcpp::Any visitLocElemInitialFlag(HybridSystemParser::LocElemInitialFlagContext *context) = 0;

        virtual antlrcpp::Any
        visitLocElemInitialFlagExpr(HybridSystemParser::LocElemInitialFlagExprContext *context) = 0;

        virtual antlrcpp::Any visitLocElemInv(HybridSystemParser::LocElemInvContext *context) = 0;

        virtual antlrcpp::Any visitLocElemEqs(HybridSystemParser::LocElemEqsContext *context) = 0;

        virtual antlrcpp::Any visitLocElemMarked(HybridSystemParser::LocElemMarkedContext *context) = 0;

        virtual antlrcpp::Any visitLocElemMarkedExpr(HybridSystemParser::LocElemMarkedExprContext *context) = 0;

        virtual antlrcpp::Any visitLocElemUrgent(HybridSystemParser::LocElemUrgentContext *context) = 0;

        virtual antlrcpp::Any visitLocElemEdgeTo(HybridSystemParser::LocElemEdgeToContext *context) = 0;

        virtual antlrcpp::Any visitLocElemLoop(HybridSystemParser::LocElemLoopContext *context) = 0;

        virtual antlrcpp::Any visitCoreEdge(HybridSystemParser::CoreEdgeContext *context) = 0;

        virtual antlrcpp::Any visitOptEdgeGuard(HybridSystemParser::OptEdgeGuardContext *context) = 0;

        virtual antlrcpp::Any visitOptEdgeUrgent(HybridSystemParser::OptEdgeUrgentContext *context) = 0;

        virtual antlrcpp::Any visitOptEdgeUpdate(HybridSystemParser::OptEdgeUpdateContext *context) = 0;

        virtual antlrcpp::Any visitEdgeEvents(HybridSystemParser::EdgeEventsContext *context) = 0;

        virtual antlrcpp::Any visitEdgeEvent(HybridSystemParser::EdgeEventContext *context) = 0;

        virtual antlrcpp::Any visitInvariantDecls(HybridSystemParser::InvariantDeclsContext *context) = 0;

        virtual antlrcpp::Any visitInvariants(HybridSystemParser::InvariantsContext *context) = 0;

        virtual antlrcpp::Any visitInvExpr(HybridSystemParser::InvExprContext *context) = 0;

        virtual antlrcpp::Any visitInvNeeds(HybridSystemParser::InvNeedsContext *context) = 0;

        virtual antlrcpp::Any visitInvNeedsSet(HybridSystemParser::InvNeedsSetContext *context) = 0;

        virtual antlrcpp::Any visitInvDisables(HybridSystemParser::InvDisablesContext *context) = 0;

        virtual antlrcpp::Any visitInvDisablesSet(HybridSystemParser::InvDisablesSetContext *context) = 0;

        virtual antlrcpp::Any visitUpdates(HybridSystemParser::UpdatesContext *context) = 0;

        virtual antlrcpp::Any visitUpdateNonIf(HybridSystemParser::UpdateNonIfContext *context) = 0;

        virtual antlrcpp::Any visitUpdateIf(HybridSystemParser::UpdateIfContext *context) = 0;

        virtual antlrcpp::Any visitOptElifUpdates(HybridSystemParser::OptElifUpdatesContext *context) = 0;

        virtual antlrcpp::Any visitOptElseUpdate(HybridSystemParser::OptElseUpdateContext *context) = 0;

        virtual antlrcpp::Any visitAdressables(HybridSystemParser::AdressablesContext *context) = 0;

        virtual antlrcpp::Any visitAdressableId(HybridSystemParser::AdressableIdContext *context) = 0;

        virtual antlrcpp::Any visitAdressableProj(HybridSystemParser::AdressableProjContext *context) = 0;

        virtual antlrcpp::Any visitAdressablePair(HybridSystemParser::AdressablePairContext *context) = 0;

        virtual antlrcpp::Any visitProjections(HybridSystemParser::ProjectionsContext *context) = 0;

        virtual antlrcpp::Any visitProjection(HybridSystemParser::ProjectionContext *context) = 0;

        virtual antlrcpp::Any visitOptIoDecls(HybridSystemParser::OptIoDeclsContext *context) = 0;

        virtual antlrcpp::Any visitIoDecls(HybridSystemParser::IoDeclsContext *context) = 0;

        virtual antlrcpp::Any visitSvgFile(HybridSystemParser::SvgFileContext *context) = 0;

        virtual antlrcpp::Any visitOptSvgFile(HybridSystemParser::OptSvgFileContext *context) = 0;

        virtual antlrcpp::Any visitSvgCopy(HybridSystemParser::SvgCopyContext *context) = 0;

        virtual antlrcpp::Any visitOptSvgCopyPre(HybridSystemParser::OptSvgCopyPreContext *context) = 0;

        virtual antlrcpp::Any visitOptSvgCopyPost(HybridSystemParser::OptSvgCopyPostContext *context) = 0;

        virtual antlrcpp::Any visitSvgMove(HybridSystemParser::SvgMoveContext *context) = 0;

        virtual antlrcpp::Any visitSvgOut(HybridSystemParser::SvgOutContext *context) = 0;

        virtual antlrcpp::Any visitSvgAttr(HybridSystemParser::SvgAttrContext *context) = 0;

        virtual antlrcpp::Any visitSvgIn(HybridSystemParser::SvgInContext *context) = 0;

        virtual antlrcpp::Any visitSvgInEvent(HybridSystemParser::SvgInEventContext *context) = 0;

        virtual antlrcpp::Any visitOptSvgInEventElifs(HybridSystemParser::OptSvgInEventElifsContext *context) = 0;

        virtual antlrcpp::Any visitSvgInEventElifs(HybridSystemParser::SvgInEventElifsContext *context) = 0;

        virtual antlrcpp::Any visitPrintFile(HybridSystemParser::PrintFileContext *context) = 0;

        virtual antlrcpp::Any visitPrint(HybridSystemParser::PrintContext *context) = 0;

        virtual antlrcpp::Any visitPrintTxt(HybridSystemParser::PrintTxtContext *context) = 0;

        virtual antlrcpp::Any visitOptPrintFors(HybridSystemParser::OptPrintForsContext *context) = 0;

        virtual antlrcpp::Any visitPrintFors(HybridSystemParser::PrintForsContext *context) = 0;

        virtual antlrcpp::Any visitPrintFor(HybridSystemParser::PrintForContext *context) = 0;

        virtual antlrcpp::Any visitOptPrintWhen(HybridSystemParser::OptPrintWhenContext *context) = 0;

        virtual antlrcpp::Any visitOptPrintFile(HybridSystemParser::OptPrintFileContext *context) = 0;


    };

}  // namespace hypro
