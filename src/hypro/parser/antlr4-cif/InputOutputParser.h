
// Generated from InputOutput.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"




class  InputOutputParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, T__16 = 17, T__17 = 18, T__18 = 19, T__19 = 20, 
    T__20 = 21, T__21 = 22, T__22 = 23, T__23 = 24, T__24 = 25, T__25 = 26, 
    T__26 = 27, T__27 = 28, T__28 = 29, T__29 = 30, T__30 = 31, T__31 = 32, 
    T__32 = 33, T__33 = 34, T__34 = 35, T__35 = 36, T__36 = 37, T__37 = 38, 
    T__38 = 39, T__39 = 40, T__40 = 41, T__41 = 42, T__42 = 43, T__43 = 44, 
    T__44 = 45, T__45 = 46, T__46 = 47, T__47 = 48, T__48 = 49, T__49 = 50, 
    T__50 = 51, T__51 = 52, T__52 = 53, T__53 = 54, T__54 = 55, T__55 = 56, 
    T__56 = 57, T__57 = 58, T__58 = 59, T__59 = 60, T__60 = 61, T__61 = 62, 
    T__62 = 63, T__63 = 64, T__64 = 65, T__65 = 66, T__66 = 67, T__67 = 68, 
    T__68 = 69, T__69 = 70, T__70 = 71, T__71 = 72, T__72 = 73, T__73 = 74, 
    T__74 = 75, T__75 = 76, T__76 = 77, T__77 = 78, T__78 = 79, T__79 = 80, 
    T__80 = 81, T__81 = 82, T__82 = 83, T__83 = 84, T__84 = 85, T__85 = 86, 
    T__86 = 87, T__87 = 88, T__88 = 89, T__89 = 90, T__90 = 91, T__91 = 92, 
    T__92 = 93, T__93 = 94, T__94 = 95, T__95 = 96, T__96 = 97, T__97 = 98, 
    T__98 = 99, T__99 = 100, T__100 = 101, T__101 = 102, T__102 = 103, T__103 = 104, 
    T__104 = 105, T__105 = 106, T__106 = 107, NUMBER = 108, REALNUBER = 109, 
    STRING = 110, IDENTIFIER = 111, RELATIVENAME = 112, ABSOLUTENAME = 113, 
    ROOTNAME = 114, WS = 115
  };

  enum {
    RuleOptIoDecls = 0, RuleIoDecls = 1, RuleSvgFile = 2, RuleOptSvgFile = 3, 
    RuleSvgCopy = 4, RuleOptSvgCopyPre = 5, RuleOptSvgCopyPost = 6, RuleSvgMove = 7, 
    RuleSvgOut = 8, RuleSvgAttr = 9, RuleSvgIn = 10, RuleSvgInEvent = 11, 
    RuleOptSvgInEventElifs = 12, RuleSvgInEventElifs = 13, RulePrintFile = 14, 
    RulePrint = 15, RulePrintTxt = 16, RuleOptPrintFors = 17, RulePrintFors = 18, 
    RulePrintFor = 19, RuleOptPrintWhen = 20, RuleOptPrintFile = 21, RuleExpressions = 22, 
    RuleOptExpression = 23, RuleExpression = 24, RuleOrExpression = 25, 
    RuleAndExpression = 26, RuleCompareExpression = 27, RuleAddExpression = 28, 
    RuleMulExpression = 29, RuleUnaryExpression = 30, RuleFuncExpression = 31, 
    RuleExpressionFactor = 32, RuleNonEmptySetExpression = 33, RuleDictPairs = 34, 
    RuleOptElifExprs = 35, RuleSwitchBody = 36, RuleSwitchCases = 37, RuleTypes = 38, 
    RuleType = 39, RuleFields = 40, RuleField = 41, RuleNameSet = 42, RuleNames = 43, 
    RuleName = 44, RuleOptSupKind = 45, RuleSupKind = 46, RuleIdentifier = 47, 
    RuleStringToken = 48, RuleStdLibFunction = 49
  };

  InputOutputParser(antlr4::TokenStream *input);
  ~InputOutputParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class OptIoDeclsContext;
  class IoDeclsContext;
  class SvgFileContext;
  class OptSvgFileContext;
  class SvgCopyContext;
  class OptSvgCopyPreContext;
  class OptSvgCopyPostContext;
  class SvgMoveContext;
  class SvgOutContext;
  class SvgAttrContext;
  class SvgInContext;
  class SvgInEventContext;
  class OptSvgInEventElifsContext;
  class SvgInEventElifsContext;
  class PrintFileContext;
  class PrintContext;
  class PrintTxtContext;
  class OptPrintForsContext;
  class PrintForsContext;
  class PrintForContext;
  class OptPrintWhenContext;
  class OptPrintFileContext;
  class ExpressionsContext;
  class OptExpressionContext;
  class ExpressionContext;
  class OrExpressionContext;
  class AndExpressionContext;
  class CompareExpressionContext;
  class AddExpressionContext;
  class MulExpressionContext;
  class UnaryExpressionContext;
  class FuncExpressionContext;
  class ExpressionFactorContext;
  class NonEmptySetExpressionContext;
  class DictPairsContext;
  class OptElifExprsContext;
  class SwitchBodyContext;
  class SwitchCasesContext;
  class TypesContext;
  class TypeContext;
  class FieldsContext;
  class FieldContext;
  class NameSetContext;
  class NamesContext;
  class NameContext;
  class OptSupKindContext;
  class SupKindContext;
  class IdentifierContext;
  class StringTokenContext;
  class StdLibFunctionContext; 

  class  OptIoDeclsContext : public antlr4::ParserRuleContext {
  public:
    OptIoDeclsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<IoDeclsContext *> ioDecls();
    IoDeclsContext* ioDecls(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OptIoDeclsContext* optIoDecls();

  class  IoDeclsContext : public antlr4::ParserRuleContext {
  public:
    IoDeclsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SvgFileContext *svgFile();
    SvgCopyContext *svgCopy();
    SvgMoveContext *svgMove();
    SvgOutContext *svgOut();
    SvgInContext *svgIn();
    PrintFileContext *printFile();
    PrintContext *print();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IoDeclsContext* ioDecls();

  class  SvgFileContext : public antlr4::ParserRuleContext {
  public:
    SvgFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StringTokenContext *stringToken();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SvgFileContext* svgFile();

  class  OptSvgFileContext : public antlr4::ParserRuleContext {
  public:
    OptSvgFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StringTokenContext *stringToken();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OptSvgFileContext* optSvgFile();

  class  SvgCopyContext : public antlr4::ParserRuleContext {
  public:
    SvgCopyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    OptSvgCopyPreContext *optSvgCopyPre();
    OptSvgCopyPostContext *optSvgCopyPost();
    OptSvgFileContext *optSvgFile();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SvgCopyContext* svgCopy();

  class  OptSvgCopyPreContext : public antlr4::ParserRuleContext {
  public:
    OptSvgCopyPreContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OptSvgCopyPreContext* optSvgCopyPre();

  class  OptSvgCopyPostContext : public antlr4::ParserRuleContext {
  public:
    OptSvgCopyPostContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OptSvgCopyPostContext* optSvgCopyPost();

  class  SvgMoveContext : public antlr4::ParserRuleContext {
  public:
    SvgMoveContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    SvgFileContext *svgFile();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SvgMoveContext* svgMove();

  class  SvgOutContext : public antlr4::ParserRuleContext {
  public:
    SvgOutContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    SvgAttrContext *svgAttr();
    OptSvgFileContext *optSvgFile();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SvgOutContext* svgOut();

  class  SvgAttrContext : public antlr4::ParserRuleContext {
  public:
    SvgAttrContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StringTokenContext *stringToken();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SvgAttrContext* svgAttr();

  class  SvgInContext : public antlr4::ParserRuleContext {
  public:
    SvgInContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    SvgInEventContext *svgInEvent();
    OptSvgFileContext *optSvgFile();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SvgInContext* svgIn();

  class  SvgInEventContext : public antlr4::ParserRuleContext {
  public:
    SvgInEventContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<NameContext *> name();
    NameContext* name(size_t i);
    ExpressionContext *expression();
    OptSvgInEventElifsContext *optSvgInEventElifs();
    SvgInEventElifsContext *svgInEventElifs();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SvgInEventContext* svgInEvent();

  class  OptSvgInEventElifsContext : public antlr4::ParserRuleContext {
  public:
    OptSvgInEventElifsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SvgInEventElifsContext *svgInEventElifs();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OptSvgInEventElifsContext* optSvgInEventElifs();

  class  SvgInEventElifsContext : public antlr4::ParserRuleContext {
  public:
    SvgInEventElifsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    std::vector<NameContext *> name();
    NameContext* name(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SvgInEventElifsContext* svgInEventElifs();

  class  PrintFileContext : public antlr4::ParserRuleContext {
  public:
    PrintFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StringTokenContext *stringToken();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PrintFileContext* printFile();

  class  PrintContext : public antlr4::ParserRuleContext {
  public:
    PrintContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PrintTxtContext *printTxt();
    OptPrintForsContext *optPrintFors();
    OptPrintWhenContext *optPrintWhen();
    OptPrintFileContext *optPrintFile();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PrintContext* print();

  class  PrintTxtContext : public antlr4::ParserRuleContext {
  public:
    PrintTxtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PrintTxtContext* printTxt();

  class  OptPrintForsContext : public antlr4::ParserRuleContext {
  public:
    OptPrintForsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PrintForsContext *printFors();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OptPrintForsContext* optPrintFors();

  class  PrintForsContext : public antlr4::ParserRuleContext {
  public:
    PrintForsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<PrintForContext *> printFor();
    PrintForContext* printFor(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PrintForsContext* printFors();

  class  PrintForContext : public antlr4::ParserRuleContext {
  public:
    PrintForContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NameContext *name();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PrintForContext* printFor();

  class  OptPrintWhenContext : public antlr4::ParserRuleContext {
  public:
    OptPrintWhenContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OptPrintWhenContext* optPrintWhen();

  class  OptPrintFileContext : public antlr4::ParserRuleContext {
  public:
    OptPrintFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StringTokenContext *stringToken();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OptPrintFileContext* optPrintFile();

  class  ExpressionsContext : public antlr4::ParserRuleContext {
  public:
    ExpressionsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExpressionsContext* expressions();

  class  OptExpressionContext : public antlr4::ParserRuleContext {
  public:
    OptExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OptExpressionContext* optExpression();

  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<OrExpressionContext *> orExpression();
    OrExpressionContext* orExpression(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExpressionContext* expression();

  class  OrExpressionContext : public antlr4::ParserRuleContext {
  public:
    OrExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<AndExpressionContext *> andExpression();
    AndExpressionContext* andExpression(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OrExpressionContext* orExpression();

  class  AndExpressionContext : public antlr4::ParserRuleContext {
  public:
    AndExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<CompareExpressionContext *> compareExpression();
    CompareExpressionContext* compareExpression(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AndExpressionContext* andExpression();

  class  CompareExpressionContext : public antlr4::ParserRuleContext {
  public:
    CompareExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<AddExpressionContext *> addExpression();
    AddExpressionContext* addExpression(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CompareExpressionContext* compareExpression();

  class  AddExpressionContext : public antlr4::ParserRuleContext {
  public:
    AddExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<MulExpressionContext *> mulExpression();
    MulExpressionContext* mulExpression(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AddExpressionContext* addExpression();

  class  MulExpressionContext : public antlr4::ParserRuleContext {
  public:
    MulExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<UnaryExpressionContext *> unaryExpression();
    UnaryExpressionContext* unaryExpression(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MulExpressionContext* mulExpression();

  class  UnaryExpressionContext : public antlr4::ParserRuleContext {
  public:
    UnaryExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FuncExpressionContext *funcExpression();
    UnaryExpressionContext *unaryExpression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UnaryExpressionContext* unaryExpression();

  class  FuncExpressionContext : public antlr4::ParserRuleContext {
  public:
    FuncExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionFactorContext *expressionFactor();
    StdLibFunctionContext *stdLibFunction();
    std::vector<ExpressionsContext *> expressions();
    ExpressionsContext* expressions(size_t i);
    std::vector<OptExpressionContext *> optExpression();
    OptExpressionContext* optExpression(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FuncExpressionContext* funcExpression();

  class  ExpressionFactorContext : public antlr4::ParserRuleContext {
  public:
    ExpressionFactorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NUMBER();
    antlr4::tree::TerminalNode *REALNUBER();
    StringTokenContext *stringToken();
    ExpressionsContext *expressions();
    NonEmptySetExpressionContext *nonEmptySetExpression();
    DictPairsContext *dictPairs();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    TypeContext *type();
    ExpressionFactorContext *expressionFactor();
    OptElifExprsContext *optElifExprs();
    SwitchBodyContext *switchBody();
    NameContext *name();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExpressionFactorContext* expressionFactor();

  class  NonEmptySetExpressionContext : public antlr4::ParserRuleContext {
  public:
    NonEmptySetExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionsContext *expressions();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NonEmptySetExpressionContext* nonEmptySetExpression();

  class  DictPairsContext : public antlr4::ParserRuleContext {
  public:
    DictPairsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DictPairsContext* dictPairs();

  class  OptElifExprsContext : public antlr4::ParserRuleContext {
  public:
    OptElifExprsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OptElifExprsContext* optElifExprs();

  class  SwitchBodyContext : public antlr4::ParserRuleContext {
  public:
    SwitchBodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SwitchCasesContext *switchCases();
    ExpressionContext *expression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SwitchBodyContext* switchBody();

  class  SwitchCasesContext : public antlr4::ParserRuleContext {
  public:
    SwitchCasesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SwitchCasesContext* switchCases();

  class  TypesContext : public antlr4::ParserRuleContext {
  public:
    TypesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TypeContext *> type();
    TypeContext* type(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypesContext* types();

  class  TypeContext : public antlr4::ParserRuleContext {
  public:
    TypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    std::vector<TypeContext *> type();
    TypeContext* type(size_t i);
    FieldsContext *fields();
    TypesContext *types();
    NameContext *name();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeContext* type();

  class  FieldsContext : public antlr4::ParserRuleContext {
  public:
    FieldsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<FieldContext *> field();
    FieldContext* field(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FieldsContext* fields();

  class  FieldContext : public antlr4::ParserRuleContext {
  public:
    FieldContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeContext *type();
    IdentifierContext *identifier();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FieldContext* field();

  class  NameSetContext : public antlr4::ParserRuleContext {
  public:
    NameSetContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NamesContext *names();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NameSetContext* nameSet();

  class  NamesContext : public antlr4::ParserRuleContext {
  public:
    NamesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<NameContext *> name();
    NameContext* name(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NamesContext* names();

  class  NameContext : public antlr4::ParserRuleContext {
  public:
    NameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    antlr4::tree::TerminalNode *RELATIVENAME();
    antlr4::tree::TerminalNode *ABSOLUTENAME();
    antlr4::tree::TerminalNode *ROOTNAME();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NameContext* name();

  class  OptSupKindContext : public antlr4::ParserRuleContext {
  public:
    OptSupKindContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SupKindContext *supKind();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OptSupKindContext* optSupKind();

  class  SupKindContext : public antlr4::ParserRuleContext {
  public:
    SupKindContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SupKindContext* supKind();

  class  IdentifierContext : public antlr4::ParserRuleContext {
  public:
    IdentifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IdentifierContext* identifier();

  class  StringTokenContext : public antlr4::ParserRuleContext {
  public:
    StringTokenContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRING();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StringTokenContext* stringToken();

  class  StdLibFunctionContext : public antlr4::ParserRuleContext {
  public:
    StdLibFunctionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StdLibFunctionContext* stdLibFunction();


private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

