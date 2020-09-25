
// Generated from HybridAutomaton.g4 by ANTLR 4.8

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
    T__20 = 21, T__21 = 22, T__22 = 23, T__23 = 24, POLY = 25, LINEAR = 26, 
    NONLINEAR = 27, NONPOLY = 28, LTI = 29, ODE = 30, IN = 31, TRUE = 32, 
    FALSE = 33, PAR = 34, JUMPS = 35, URGENT = 36, GUARD = 37, RESET = 38, 
    PARALLELOTOPE = 39, BOX = 40, JUMP = 41, DEFINE = 42, COMMENT = 43, 
    EQUALS = 44, BOOLRELATION = 45, PLUS = 46, MINUS = 47, TIMES = 48, DIVIDE = 49, 
    SBOPEN = 50, SBCLOSE = 51, CBOPEN = 52, CBCLOSE = 53, RBOPEN = 54, RBCLOSE = 55, 
    COMMA = 56, NUMBER = 57, CONSTANT = 58, VARIABLE = 59, WS = 60, INTERVALAGG = 61, 
    EXPONENTIAL = 62
  };

  enum {
    RuleStart = 0, RuleVardeclaration = 1, RuleConstantdeclaration = 2, 
    RuleModes = 3, RuleLocation = 4, RuleActivities = 5, RuleInvariants = 6, 
    RuleStochasticlocation = 7, RuleProbdistribution = 8, RuleReplacedexpr = 9, 
    RuleConstantexpr = 10, RuleConnector = 11, RuleTerm = 12, RuleBracketExpression = 13, 
    RulePolynom = 14, RuleExpression = 15, RuleEquation = 16, RuleConstraint = 17, 
    RuleInterval = 18, RuleIntervalexpr = 19, RuleConstrset = 20, RuleInit = 21, 
    RuleInitstate = 22, RuleProbinitstate = 23, RuleUnsafeset = 24, RuleLbadstate = 25, 
    RuleGbadstate = 26, RuleJumps = 27, RuleTransition = 28, RuleFromto = 29, 
    RuleUrgent = 30, RuleGuard = 31, RuleLabels = 32, RuleAllocation = 33, 
    RuleResetfct = 34, RuleAggregation = 35, RuleStochastictransition = 36, 
    RuleProbtransition = 37, RuleProbfrom = 38, RuleProbto = 39, RuleSetting = 40, 
    RuleFixedsteps = 41, RuleTime = 42, RulePlotsetting = 43, RuleFilename = 44, 
    RuleMaxjumps = 45, RulePrint = 46, RuleRemainder = 47, RuleIdentity = 48, 
    RuleQrprecond = 49, RuleFixedorders = 50, RuleAdaptiveorders = 51, RuleCutoff = 52, 
    RulePrecision = 53
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
  class StochasticlocationContext;
  class ProbdistributionContext;
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
  class ProbinitstateContext;
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
  class StochastictransitionContext;
  class ProbtransitionContext;
  class ProbfromContext;
  class ProbtoContext;
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
    std::vector<StochasticlocationContext *> stochasticlocation();
    StochasticlocationContext* stochasticlocation(size_t i);


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

  class  StochasticlocationContext : public antlr4::ParserRuleContext {
  public:
    StochasticlocationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VARIABLE();
    antlr4::tree::TerminalNode *CBOPEN();
    ActivitiesContext *activities();
    std::vector<InvariantsContext *> invariants();
    InvariantsContext* invariants(size_t i);
    antlr4::tree::TerminalNode *CBCLOSE();
    ProbdistributionContext *probdistribution();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StochasticlocationContext* stochasticlocation();

  class  ProbdistributionContext : public antlr4::ParserRuleContext {
  public:
    ProbdistributionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CBOPEN();
    std::vector<EquationContext *> equation();
    EquationContext* equation(size_t i);
    antlr4::tree::TerminalNode *CBCLOSE();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProbdistributionContext* probdistribution();

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
    antlr4::Token *constantToken = nullptr;
    antlr4::Token *minusToken = nullptr;
    antlr4::Token *numberToken = nullptr;
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
    std::vector<ProbinitstateContext *> probinitstate();
    ProbinitstateContext* probinitstate(size_t i);


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

  class  ProbinitstateContext : public antlr4::ParserRuleContext {
  public:
    ProbinitstateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NUMBER();
    antlr4::tree::TerminalNode *JUMP();
    antlr4::tree::TerminalNode *VARIABLE();
    antlr4::tree::TerminalNode *CBOPEN();
    ConstrsetContext *constrset();
    antlr4::tree::TerminalNode *CBCLOSE();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProbinitstateContext* probinitstate();

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
    std::vector<StochastictransitionContext *> stochastictransition();
    StochastictransitionContext* stochastictransition(size_t i);


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

  class  StochastictransitionContext : public antlr4::ParserRuleContext {
  public:
    StochastictransitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ProbfromContext *probfrom();
    antlr4::tree::TerminalNode *CBOPEN();
    antlr4::tree::TerminalNode *CBCLOSE();
    std::vector<UrgentContext *> urgent();
    UrgentContext* urgent(size_t i);
    std::vector<GuardContext *> guard();
    GuardContext* guard(size_t i);
    std::vector<LabelsContext *> labels();
    LabelsContext* labels(size_t i);
    std::vector<ProbtransitionContext *> probtransition();
    ProbtransitionContext* probtransition(size_t i);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StochastictransitionContext* stochastictransition();

  class  ProbtransitionContext : public antlr4::ParserRuleContext {
  public:
    ProbtransitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ProbtoContext *probto();
    std::vector<ResetfctContext *> resetfct();
    ResetfctContext* resetfct(size_t i);
    std::vector<AggregationContext *> aggregation();
    AggregationContext* aggregation(size_t i);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProbtransitionContext* probtransition();

  class  ProbfromContext : public antlr4::ParserRuleContext {
  public:
    ProbfromContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VARIABLE();
    std::vector<antlr4::tree::TerminalNode *> MINUS();
    antlr4::tree::TerminalNode* MINUS(size_t i);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProbfromContext* probfrom();

  class  ProbtoContext : public antlr4::ParserRuleContext {
  public:
    ProbtoContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NUMBER();
    antlr4::tree::TerminalNode *JUMP();
    antlr4::tree::TerminalNode *VARIABLE();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProbtoContext* probto();

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
