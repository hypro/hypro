
// Generated from InputOutput.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "InputOutputParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by InputOutputParser.
 */
class  InputOutputVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by InputOutputParser.
   */
    virtual antlrcpp::Any visitOptIoDecls(InputOutputParser::OptIoDeclsContext *context) = 0;

    virtual antlrcpp::Any visitIoDecls(InputOutputParser::IoDeclsContext *context) = 0;

    virtual antlrcpp::Any visitSvgFile(InputOutputParser::SvgFileContext *context) = 0;

    virtual antlrcpp::Any visitOptSvgFile(InputOutputParser::OptSvgFileContext *context) = 0;

    virtual antlrcpp::Any visitSvgCopy(InputOutputParser::SvgCopyContext *context) = 0;

    virtual antlrcpp::Any visitOptSvgCopyPre(InputOutputParser::OptSvgCopyPreContext *context) = 0;

    virtual antlrcpp::Any visitOptSvgCopyPost(InputOutputParser::OptSvgCopyPostContext *context) = 0;

    virtual antlrcpp::Any visitSvgMove(InputOutputParser::SvgMoveContext *context) = 0;

    virtual antlrcpp::Any visitSvgOut(InputOutputParser::SvgOutContext *context) = 0;

    virtual antlrcpp::Any visitSvgAttr(InputOutputParser::SvgAttrContext *context) = 0;

    virtual antlrcpp::Any visitSvgIn(InputOutputParser::SvgInContext *context) = 0;

    virtual antlrcpp::Any visitSvgInEvent(InputOutputParser::SvgInEventContext *context) = 0;

    virtual antlrcpp::Any visitOptSvgInEventElifs(InputOutputParser::OptSvgInEventElifsContext *context) = 0;

    virtual antlrcpp::Any visitSvgInEventElifs(InputOutputParser::SvgInEventElifsContext *context) = 0;

    virtual antlrcpp::Any visitPrintFile(InputOutputParser::PrintFileContext *context) = 0;

    virtual antlrcpp::Any visitPrint(InputOutputParser::PrintContext *context) = 0;

    virtual antlrcpp::Any visitPrintTxt(InputOutputParser::PrintTxtContext *context) = 0;

    virtual antlrcpp::Any visitOptPrintFors(InputOutputParser::OptPrintForsContext *context) = 0;

    virtual antlrcpp::Any visitPrintFors(InputOutputParser::PrintForsContext *context) = 0;

    virtual antlrcpp::Any visitPrintFor(InputOutputParser::PrintForContext *context) = 0;

    virtual antlrcpp::Any visitOptPrintWhen(InputOutputParser::OptPrintWhenContext *context) = 0;

    virtual antlrcpp::Any visitOptPrintFile(InputOutputParser::OptPrintFileContext *context) = 0;

    virtual antlrcpp::Any visitExpressions(InputOutputParser::ExpressionsContext *context) = 0;

    virtual antlrcpp::Any visitOptExpression(InputOutputParser::OptExpressionContext *context) = 0;

    virtual antlrcpp::Any visitExpression(InputOutputParser::ExpressionContext *context) = 0;

    virtual antlrcpp::Any visitOrExpression(InputOutputParser::OrExpressionContext *context) = 0;

    virtual antlrcpp::Any visitAndExpression(InputOutputParser::AndExpressionContext *context) = 0;

    virtual antlrcpp::Any visitCompareExpression(InputOutputParser::CompareExpressionContext *context) = 0;

    virtual antlrcpp::Any visitAddExpression(InputOutputParser::AddExpressionContext *context) = 0;

    virtual antlrcpp::Any visitMulExpression(InputOutputParser::MulExpressionContext *context) = 0;

    virtual antlrcpp::Any visitUnaryExpression(InputOutputParser::UnaryExpressionContext *context) = 0;

    virtual antlrcpp::Any visitFuncExpression(InputOutputParser::FuncExpressionContext *context) = 0;

    virtual antlrcpp::Any visitExpressionFactor(InputOutputParser::ExpressionFactorContext *context) = 0;

    virtual antlrcpp::Any visitNonEmptySetExpression(InputOutputParser::NonEmptySetExpressionContext *context) = 0;

    virtual antlrcpp::Any visitDictPairs(InputOutputParser::DictPairsContext *context) = 0;

    virtual antlrcpp::Any visitOptElifExprs(InputOutputParser::OptElifExprsContext *context) = 0;

    virtual antlrcpp::Any visitSwitchBody(InputOutputParser::SwitchBodyContext *context) = 0;

    virtual antlrcpp::Any visitSwitchCases(InputOutputParser::SwitchCasesContext *context) = 0;

    virtual antlrcpp::Any visitTypes(InputOutputParser::TypesContext *context) = 0;

    virtual antlrcpp::Any visitType(InputOutputParser::TypeContext *context) = 0;

    virtual antlrcpp::Any visitFields(InputOutputParser::FieldsContext *context) = 0;

    virtual antlrcpp::Any visitField(InputOutputParser::FieldContext *context) = 0;

    virtual antlrcpp::Any visitNameSet(InputOutputParser::NameSetContext *context) = 0;

    virtual antlrcpp::Any visitNames(InputOutputParser::NamesContext *context) = 0;

    virtual antlrcpp::Any visitName(InputOutputParser::NameContext *context) = 0;

    virtual antlrcpp::Any visitOptSupKind(InputOutputParser::OptSupKindContext *context) = 0;

    virtual antlrcpp::Any visitSupKind(InputOutputParser::SupKindContext *context) = 0;

    virtual antlrcpp::Any visitIdentifier(InputOutputParser::IdentifierContext *context) = 0;

    virtual antlrcpp::Any visitStringToken(InputOutputParser::StringTokenContext *context) = 0;

    virtual antlrcpp::Any visitStdLibFunction(InputOutputParser::StdLibFunctionContext *context) = 0;


};

