
// Generated from Expressions.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"




class  ExpressionsParser : public antlr4::Parser {
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
    T__74 = 75, T__75 = 76, T__76 = 77, MULOP = 78, ADDOP = 79, COMPOP = 80, 
    NUMBER = 81, REALNUMBER = 82, STRING = 83, IDENTIFIER = 84, RELATIVENAME = 85, 
    ABSOLUTENAME = 86, ROOTNAME = 87, WS = 88
  };

  enum {
    RuleExpressions = 0, RuleOptExpression = 1, RuleExpression = 2, RuleEquations = 3, 
    RuleEquation = 4, RuleOrExpression = 5, RuleAndExpression = 6, RuleCompareExpression = 7, 
    RuleAddExpression = 8, RuleMulExpression = 9, RuleUnaryExpression = 10, 
    RuleFuncExpression = 11, RuleExpressionFactor = 12, RuleNonEmptySetExpression = 13, 
    RuleDictPairs = 14, RuleOptElifExprs = 15, RuleSwitchBody = 16, RuleSwitchCases = 17, 
    RuleTypes = 18, RuleType = 19, RuleFields = 20, RuleField = 21, RuleNameSet = 22, 
    RuleNames = 23, RuleName = 24, RuleOptSupKind = 25, RuleSupKind = 26, 
    RuleIdentifier = 27, RuleStringToken = 28, RuleStdLibFunction = 29
  };

  ExpressionsParser(antlr4::TokenStream *input);
  ~ExpressionsParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class ExpressionsContext;
  class OptExpressionContext;
  class ExpressionContext;
  class EquationsContext;
  class EquationContext;
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

  class  EquationsContext : public antlr4::ParserRuleContext {
  public:
    EquationsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<EquationContext *> equation();
    EquationContext* equation(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EquationsContext* equations();

  class  EquationContext : public antlr4::ParserRuleContext {
  public:
    EquationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    EquationContext() : antlr4::ParserRuleContext() { }
    void copyFrom(EquationContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  EquationDerivateContext : public EquationContext {
  public:
    EquationDerivateContext(EquationContext *ctx);

    IdentifierContext *identifier();
    ExpressionContext *expression();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  EquationNonDerivateContext : public EquationContext {
  public:
    EquationNonDerivateContext(EquationContext *ctx);

    IdentifierContext *identifier();
    ExpressionContext *expression();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  EquationContext* equation();

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
    std::vector<antlr4::tree::TerminalNode *> COMPOP();
    antlr4::tree::TerminalNode* COMPOP(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CompareExpressionContext* compareExpression();

  class  AddExpressionContext : public antlr4::ParserRuleContext {
  public:
    AddExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<MulExpressionContext *> mulExpression();
    MulExpressionContext* mulExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> ADDOP();
    antlr4::tree::TerminalNode* ADDOP(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AddExpressionContext* addExpression();

  class  MulExpressionContext : public antlr4::ParserRuleContext {
  public:
    MulExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<UnaryExpressionContext *> unaryExpression();
    UnaryExpressionContext* unaryExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> MULOP();
    antlr4::tree::TerminalNode* MULOP(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MulExpressionContext* mulExpression();

  class  UnaryExpressionContext : public antlr4::ParserRuleContext {
  public:
    UnaryExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    UnaryExpressionContext() : antlr4::ParserRuleContext() { }
    void copyFrom(UnaryExpressionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  UnaryExprContext : public UnaryExpressionContext {
  public:
    UnaryExprContext(UnaryExpressionContext *ctx);

    UnaryExpressionContext *unaryExpression();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  UnaryExprFuncContext : public UnaryExpressionContext {
  public:
    UnaryExprFuncContext(UnaryExpressionContext *ctx);

    FuncExpressionContext *funcExpression();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  UnaryExprMinusContext : public UnaryExpressionContext {
  public:
    UnaryExprMinusContext(UnaryExpressionContext *ctx);

    UnaryExpressionContext *unaryExpression();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  UnaryExprPlusContext : public UnaryExpressionContext {
  public:
    UnaryExprPlusContext(UnaryExpressionContext *ctx);

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
   
    ExpressionFactorContext() : antlr4::ParserRuleContext() { }
    void copyFrom(ExpressionFactorContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ExprFactNumberContext : public ExpressionFactorContext {
  public:
    ExprFactNumberContext(ExpressionFactorContext *ctx);

    antlr4::tree::TerminalNode *NUMBER();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprFactContext : public ExpressionFactorContext {
  public:
    ExprFactContext(ExpressionFactorContext *ctx);

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

  class  ExprFactRealNumberContext : public ExpressionFactorContext {
  public:
    ExprFactRealNumberContext(ExpressionFactorContext *ctx);

    antlr4::tree::TerminalNode *REALNUMBER();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprFactNameContext : public ExpressionFactorContext {
  public:
    ExprFactNameContext(ExpressionFactorContext *ctx);

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

