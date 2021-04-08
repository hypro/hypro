
// Generated from HybridAutomaton.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"


	#include <map>
	#include <string>


namespace hypro {


class  HybridAutomatonParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, T__16 = 17, T__17 = 18, T__18 = 19, T__19 = 20, 
    T__20 = 21, T__21 = 22, T__22 = 23, POLY = 24, LINEAR = 25, NONLINEAR = 26, 
    NONPOLY = 27, LTI = 28, ODE = 29, URGENT = 30, IN = 31, TRUE = 32, FALSE = 33, 
    PAR = 34, JUMPS = 35, GUARD = 36, RESET = 37, PARALLELOTOPE = 38, BOX = 39, 
    JUMP = 40, DEFINE = 41, COMMENT = 42, EQUALS = 43, BOOLRELATION = 44, 
    PLUS = 45, MINUS = 46, TIMES = 47, DIVIDE = 48, SBOPEN = 49, SBCLOSE = 50, 
    CBOPEN = 51, CBCLOSE = 52, RBOPEN = 53, RBCLOSE = 54, COMMA = 55, NUMBER = 56, 
    CONSTANT = 57, VARIABLE = 58, WS = 59, INTERVALAGG = 60, EXPONENTIAL = 61
  };

  enum {
    RuleStart = 0, RuleVardeclaration = 1, RuleConstantdeclaration = 2, 
    RuleModes = 3, RuleLocation = 4, RuleActivities = 5, RuleInvariants = 6, 
    RuleLoc_labels = 7, RuleReplacedexpr = 8, RuleConstantexpr = 9, RuleConnector = 10, 
    RuleTerm = 11, RuleBracketExpression = 12, RulePolynom = 13, RuleExpression = 14, 
    RuleEquation = 15, RuleConstraint = 16, RuleInterval = 17, RuleIntervalexpr = 18, 
    RuleConstrset = 19, RuleInit = 20, RuleInitstate = 21, RuleUnsafeset = 22, 
    RuleLbadstate = 23, RuleGbadstate = 24, RuleJumps = 25, RuleTransition = 26, 
    RuleFromto = 27, RuleUrgent = 28, RuleGuard = 29, RuleLabels = 30, RuleAllocation = 31, 
    RuleResetfct = 32, RuleAggregation = 33, RuleSetting = 34, RuleFixedsteps = 35, 
    RuleTime = 36, RulePlotsetting = 37, RuleFilename = 38, RuleMaxjumps = 39, 
    RulePrint = 40, RuleRemainder = 41, RuleIdentity = 42, RuleQrprecond = 43, 
    RuleFixedorders = 44, RuleAdaptiveorders = 45, RuleCutoff = 46, RulePrecision = 47
  };

  HybridAutomatonParser(antlr4::TokenStream *input);
  ~HybridAutomatonParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  	inline const std::map<std::string, std::string>& getConstants() const { return constants; }


  class StartContext;
  class VardeclarationContext;
  class ConstantdeclarationContext;
  class ModesContext;
  class LocationContext;
  class ActivitiesContext;
  class InvariantsContext;
  class Loc_labelsContext;
  class ReplacedexprContext;
  class ConstantexprContext;
  class ConnectorContext;
  class TermContext;
  class BracketExpressionContext;
  class PolynomContext;
  class ExpressionContext;
  class EquationContext;
  class ConstraintContext;
  class IntervalContext;
  class IntervalexprContext;
  class ConstrsetContext;
  class InitContext;
  class InitstateContext;
  class UnsafesetContext;
  class LbadstateContext;
  class GbadstateContext;
  class JumpsContext;
  class TransitionContext;
  class FromtoContext;
  class UrgentContext;
  class GuardContext;
  class LabelsContext;
  class AllocationContext;
  class ResetfctContext;
  class AggregationContext;
  class SettingContext;
  class FixedstepsContext;
  class TimeContext;
  class PlotsettingContext;
  class FilenameContext;
  class MaxjumpsContext;
  class PrintContext;
  class RemainderContext;
  class IdentityContext;
  class QrprecondContext;
  class FixedordersContext;
  class AdaptiveordersContext;
  class CutoffContext;
  class PrecisionContext; 

  class  StartContext : public antlr4::ParserRuleContext {
  public:
    StartContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CBOPEN();
    VardeclarationContext *vardeclaration();
    SettingContext *setting();
    ModesContext *modes();
    JumpsContext *jumps();
    antlr4::tree::TerminalNode *CBCLOSE();
    ConstantdeclarationContext *constantdeclaration();
    std::vector<InitContext *> init();
    InitContext* init(size_t i);
    UnsafesetContext *unsafeset();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StartContext* start();

  class  VardeclarationContext : public antlr4::ParserRuleContext {
  public:
    VardeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> VARIABLE();
    antlr4::tree::TerminalNode* VARIABLE(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VardeclarationContext* vardeclaration();

  class  ConstantdeclarationContext : public antlr4::ParserRuleContext {
  public:
    ConstantdeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PAR();
    antlr4::tree::TerminalNode *CBOPEN();
    antlr4::tree::TerminalNode *CBCLOSE();
    std::vector<ConstantexprContext *> constantexpr();
    ConstantexprContext* constantexpr(size_t i);
    std::vector<ReplacedexprContext *> replacedexpr();
    ReplacedexprContext* replacedexpr(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConstantdeclarationContext* constantdeclaration();

  class  ModesContext : public antlr4::ParserRuleContext {
  public:
    ModesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CBOPEN();
    antlr4::tree::TerminalNode *CBCLOSE();
    std::vector<LocationContext *> location();
    LocationContext* location(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ModesContext* modes();

  class  LocationContext : public antlr4::ParserRuleContext {
  public:
    LocationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VARIABLE();
    antlr4::tree::TerminalNode *CBOPEN();
    ActivitiesContext *activities();
    Loc_labelsContext *loc_labels();
    antlr4::tree::TerminalNode *CBCLOSE();
    std::vector<InvariantsContext *> invariants();
    InvariantsContext* invariants(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LocationContext* location();

  class  ActivitiesContext : public antlr4::ParserRuleContext {
  public:
    ActivitiesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ODE();
    antlr4::tree::TerminalNode *CBOPEN();
    antlr4::tree::TerminalNode *CBCLOSE();
    antlr4::tree::TerminalNode *POLY();
    antlr4::tree::TerminalNode *LINEAR();
    antlr4::tree::TerminalNode *NONLINEAR();
    antlr4::tree::TerminalNode *NONPOLY();
    antlr4::tree::TerminalNode *LTI();
    std::vector<antlr4::tree::TerminalNode *> NUMBER();
    antlr4::tree::TerminalNode* NUMBER(size_t i);
    std::vector<EquationContext *> equation();
    EquationContext* equation(size_t i);
    std::vector<IntervalexprContext *> intervalexpr();
    IntervalexprContext* intervalexpr(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ActivitiesContext* activities();

  class  InvariantsContext : public antlr4::ParserRuleContext {
  public:
    InvariantsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CBOPEN();
    antlr4::tree::TerminalNode *CBCLOSE();
    ConstrsetContext *constrset();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InvariantsContext* invariants();

  class  Loc_labelsContext : public antlr4::ParserRuleContext {
  public:
    Loc_labelsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *URGENT();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Loc_labelsContext* loc_labels();

  class  ReplacedexprContext : public antlr4::ParserRuleContext {
  public:
    ReplacedexprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> NUMBER();
    antlr4::tree::TerminalNode* NUMBER(size_t i);
    antlr4::tree::TerminalNode *EQUALS();
    std::vector<antlr4::tree::TerminalNode *> MINUS();
    antlr4::tree::TerminalNode* MINUS(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ReplacedexprContext* replacedexpr();

  class  ConstantexprContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *constantToken = nullptr;;
    antlr4::Token *minusToken = nullptr;;
    antlr4::Token *numberToken = nullptr;;
    ConstantexprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CONSTANT();
    antlr4::tree::TerminalNode *EQUALS();
    antlr4::tree::TerminalNode *NUMBER();
    antlr4::tree::TerminalNode *MINUS();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConstantexprContext* constantexpr();

  class  ConnectorContext : public antlr4::ParserRuleContext {
  public:
    ConnectorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *MINUS();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConnectorContext* connector();

  class  TermContext : public antlr4::ParserRuleContext {
  public:
    TermContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> NUMBER();
    antlr4::tree::TerminalNode* NUMBER(size_t i);
    std::vector<antlr4::tree::TerminalNode *> VARIABLE();
    antlr4::tree::TerminalNode* VARIABLE(size_t i);
    antlr4::tree::TerminalNode *MINUS();
    std::vector<antlr4::tree::TerminalNode *> TIMES();
    antlr4::tree::TerminalNode* TIMES(size_t i);
    std::vector<ConnectorContext *> connector();
    ConnectorContext* connector(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TermContext* term();

  class  BracketExpressionContext : public antlr4::ParserRuleContext {
  public:
    BracketExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *RBOPEN();
    PolynomContext *polynom();
    antlr4::tree::TerminalNode *RBCLOSE();
    std::vector<antlr4::tree::TerminalNode *> NUMBER();
    antlr4::tree::TerminalNode* NUMBER(size_t i);
    std::vector<antlr4::tree::TerminalNode *> TIMES();
    antlr4::tree::TerminalNode* TIMES(size_t i);
    antlr4::tree::TerminalNode *DIVIDE();
    std::vector<antlr4::tree::TerminalNode *> MINUS();
    antlr4::tree::TerminalNode* MINUS(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BracketExpressionContext* bracketExpression();

  class  PolynomContext : public antlr4::ParserRuleContext {
  public:
    PolynomContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TermContext *> term();
    TermContext* term(size_t i);
    std::vector<BracketExpressionContext *> bracketExpression();
    BracketExpressionContext* bracketExpression(size_t i);
    std::vector<ConnectorContext *> connector();
    ConnectorContext* connector(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PolynomContext* polynom();

  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PolynomContext *polynom();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExpressionContext* expression();

  class  EquationContext : public antlr4::ParserRuleContext {
  public:
    EquationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VARIABLE();
    antlr4::tree::TerminalNode *EQUALS();
    ExpressionContext *expression();
    ConnectorContext *connector();
    IntervalContext *interval();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EquationContext* equation();

  class  ConstraintContext : public antlr4::ParserRuleContext {
  public:
    ConstraintContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *BOOLRELATION();
    antlr4::tree::TerminalNode *EQUALS();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConstraintContext* constraint();

  class  IntervalContext : public antlr4::ParserRuleContext {
  public:
    IntervalContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SBOPEN();
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *SBCLOSE();
    std::vector<antlr4::tree::TerminalNode *> NUMBER();
    antlr4::tree::TerminalNode* NUMBER(size_t i);
    std::vector<antlr4::tree::TerminalNode *> VARIABLE();
    antlr4::tree::TerminalNode* VARIABLE(size_t i);
    std::vector<antlr4::tree::TerminalNode *> MINUS();
    antlr4::tree::TerminalNode* MINUS(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IntervalContext* interval();

  class  IntervalexprContext : public antlr4::ParserRuleContext {
  public:
    IntervalexprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VARIABLE();
    antlr4::tree::TerminalNode *IN();
    IntervalContext *interval();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IntervalexprContext* intervalexpr();

  class  ConstrsetContext : public antlr4::ParserRuleContext {
  public:
    ConstrsetContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TRUE();
    antlr4::tree::TerminalNode *FALSE();
    std::vector<ConstraintContext *> constraint();
    ConstraintContext* constraint(size_t i);
    std::vector<IntervalexprContext *> intervalexpr();
    IntervalexprContext* intervalexpr(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConstrsetContext* constrset();

  class  InitContext : public antlr4::ParserRuleContext {
  public:
    InitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CBOPEN();
    antlr4::tree::TerminalNode *CBCLOSE();
    std::vector<InitstateContext *> initstate();
    InitstateContext* initstate(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InitContext* init();

  class  InitstateContext : public antlr4::ParserRuleContext {
  public:
    InitstateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VARIABLE();
    antlr4::tree::TerminalNode *CBOPEN();
    ConstrsetContext *constrset();
    antlr4::tree::TerminalNode *CBCLOSE();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InitstateContext* initstate();

  class  UnsafesetContext : public antlr4::ParserRuleContext {
  public:
    UnsafesetContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CBOPEN();
    antlr4::tree::TerminalNode *CBCLOSE();
    std::vector<GbadstateContext *> gbadstate();
    GbadstateContext* gbadstate(size_t i);
    std::vector<LbadstateContext *> lbadstate();
    LbadstateContext* lbadstate(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UnsafesetContext* unsafeset();

  class  LbadstateContext : public antlr4::ParserRuleContext {
  public:
    LbadstateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VARIABLE();
    antlr4::tree::TerminalNode *CBOPEN();
    antlr4::tree::TerminalNode *CBCLOSE();
    ConstrsetContext *constrset();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LbadstateContext* lbadstate();

  class  GbadstateContext : public antlr4::ParserRuleContext {
  public:
    GbadstateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConstrsetContext *constrset();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GbadstateContext* gbadstate();

  class  JumpsContext : public antlr4::ParserRuleContext {
  public:
    JumpsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *JUMPS();
    antlr4::tree::TerminalNode *CBOPEN();
    antlr4::tree::TerminalNode *CBCLOSE();
    std::vector<TransitionContext *> transition();
    TransitionContext* transition(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  JumpsContext* jumps();

  class  TransitionContext : public antlr4::ParserRuleContext {
  public:
    TransitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FromtoContext *fromto();
    std::vector<UrgentContext *> urgent();
    UrgentContext* urgent(size_t i);
    std::vector<GuardContext *> guard();
    GuardContext* guard(size_t i);
    std::vector<LabelsContext *> labels();
    LabelsContext* labels(size_t i);
    std::vector<ResetfctContext *> resetfct();
    ResetfctContext* resetfct(size_t i);
    std::vector<AggregationContext *> aggregation();
    AggregationContext* aggregation(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TransitionContext* transition();

  class  FromtoContext : public antlr4::ParserRuleContext {
  public:
    FromtoContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> VARIABLE();
    antlr4::tree::TerminalNode* VARIABLE(size_t i);
    antlr4::tree::TerminalNode *JUMP();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FromtoContext* fromto();

  class  UrgentContext : public antlr4::ParserRuleContext {
  public:
    UrgentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *URGENT();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UrgentContext* urgent();

  class  GuardContext : public antlr4::ParserRuleContext {
  public:
    GuardContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *GUARD();
    antlr4::tree::TerminalNode *CBOPEN();
    antlr4::tree::TerminalNode *CBCLOSE();
    ConstrsetContext *constrset();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GuardContext* guard();

  class  LabelsContext : public antlr4::ParserRuleContext {
  public:
    LabelsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CBOPEN();
    antlr4::tree::TerminalNode *CBCLOSE();
    std::vector<antlr4::tree::TerminalNode *> VARIABLE();
    antlr4::tree::TerminalNode* VARIABLE(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LabelsContext* labels();

  class  AllocationContext : public antlr4::ParserRuleContext {
  public:
    AllocationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VARIABLE();
    antlr4::tree::TerminalNode *DEFINE();
    PolynomContext *polynom();
    IntervalContext *interval();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AllocationContext* allocation();

  class  ResetfctContext : public antlr4::ParserRuleContext {
  public:
    ResetfctContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *RESET();
    antlr4::tree::TerminalNode *CBOPEN();
    antlr4::tree::TerminalNode *CBCLOSE();
    std::vector<AllocationContext *> allocation();
    AllocationContext* allocation(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ResetfctContext* resetfct();

  class  AggregationContext : public antlr4::ParserRuleContext {
  public:
    AggregationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CBOPEN();
    antlr4::tree::TerminalNode *CBCLOSE();
    antlr4::tree::TerminalNode *PARALLELOTOPE();
    antlr4::tree::TerminalNode *BOX();
    antlr4::tree::TerminalNode *INTERVALAGG();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AggregationContext* aggregation();

  class  SettingContext : public antlr4::ParserRuleContext {
  public:
    SettingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CBOPEN();
    antlr4::tree::TerminalNode *CBCLOSE();
    std::vector<FixedstepsContext *> fixedsteps();
    FixedstepsContext* fixedsteps(size_t i);
    std::vector<TimeContext *> time();
    TimeContext* time(size_t i);
    std::vector<RemainderContext *> remainder();
    RemainderContext* remainder(size_t i);
    std::vector<IdentityContext *> identity();
    IdentityContext* identity(size_t i);
    std::vector<QrprecondContext *> qrprecond();
    QrprecondContext* qrprecond(size_t i);
    std::vector<PlotsettingContext *> plotsetting();
    PlotsettingContext* plotsetting(size_t i);
    std::vector<FixedordersContext *> fixedorders();
    FixedordersContext* fixedorders(size_t i);
    std::vector<AdaptiveordersContext *> adaptiveorders();
    AdaptiveordersContext* adaptiveorders(size_t i);
    std::vector<CutoffContext *> cutoff();
    CutoffContext* cutoff(size_t i);
    std::vector<PrecisionContext *> precision();
    PrecisionContext* precision(size_t i);
    std::vector<FilenameContext *> filename();
    FilenameContext* filename(size_t i);
    std::vector<MaxjumpsContext *> maxjumps();
    MaxjumpsContext* maxjumps(size_t i);
    std::vector<PrintContext *> print();
    PrintContext* print(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SettingContext* setting();

  class  FixedstepsContext : public antlr4::ParserRuleContext {
  public:
    FixedstepsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NUMBER();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FixedstepsContext* fixedsteps();

  class  TimeContext : public antlr4::ParserRuleContext {
  public:
    TimeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NUMBER();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TimeContext* time();

  class  PlotsettingContext : public antlr4::ParserRuleContext {
  public:
    PlotsettingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> VARIABLE();
    antlr4::tree::TerminalNode* VARIABLE(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PlotsettingContext* plotsetting();

  class  FilenameContext : public antlr4::ParserRuleContext {
  public:
    FilenameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VARIABLE();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FilenameContext* filename();

  class  MaxjumpsContext : public antlr4::ParserRuleContext {
  public:
    MaxjumpsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NUMBER();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MaxjumpsContext* maxjumps();

  class  PrintContext : public antlr4::ParserRuleContext {
  public:
    PrintContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VARIABLE();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PrintContext* print();

  class  RemainderContext : public antlr4::ParserRuleContext {
  public:
    RemainderContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EXPONENTIAL();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RemainderContext* remainder();

  class  IdentityContext : public antlr4::ParserRuleContext {
  public:
    IdentityContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IdentityContext* identity();

  class  QrprecondContext : public antlr4::ParserRuleContext {
  public:
    QrprecondContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  QrprecondContext* qrprecond();

  class  FixedordersContext : public antlr4::ParserRuleContext {
  public:
    FixedordersContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NUMBER();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FixedordersContext* fixedorders();

  class  AdaptiveordersContext : public antlr4::ParserRuleContext {
  public:
    AdaptiveordersContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CBOPEN();
    std::vector<antlr4::tree::TerminalNode *> NUMBER();
    antlr4::tree::TerminalNode* NUMBER(size_t i);
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *CBCLOSE();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AdaptiveordersContext* adaptiveorders();

  class  CutoffContext : public antlr4::ParserRuleContext {
  public:
    CutoffContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EXPONENTIAL();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CutoffContext* cutoff();

  class  PrecisionContext : public antlr4::ParserRuleContext {
  public:
    PrecisionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NUMBER();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PrecisionContext* precision();


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


  	std::map<std::string, std::string> constants;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

}  // namespace hypro
