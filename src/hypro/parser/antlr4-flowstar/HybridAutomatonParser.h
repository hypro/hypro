
// Generated from HybridAutomaton.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"


	#include <map>
	#include <string>




class  HybridAutomatonParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, T__16 = 17, T__17 = 18, T__18 = 19, T__19 = 20, 
    T__20 = 21, T__21 = 22, T__22 = 23, T__23 = 24, T__24 = 25, T__25 = 26, 
    T__26 = 27, T__27 = 28, T__28 = 29, IN = 30, TRUE = 31, FALSE = 32, 
    PAR = 33, COMMENT = 34, EQUALS = 35, BOOLRELATION = 36, PLUS = 37, MINUS = 38, 
    TIMES = 39, SBOPEN = 40, SBCLOSE = 41, CBOPEN = 42, CBCLOSE = 43, COMMA = 44, 
    NUMBER = 45, CONSTANT = 46, VARIABLE = 47, WS = 48, PARALLELOTOPE = 49, 
    INTERVALAGG = 50, BOX = 51, JUMP = 52, DEFINE = 53, EXPONENTIAL = 54
  };

  enum {
    RuleStart = 0, RuleOld = 1, RuleAutomaton = 2, RuleComp = 3, RuleVardeclaration = 4, 
    RuleConstantdeclaration = 5, RuleGlobalvardeclaration = 6, RuleComponent = 7, 
    RuleModes = 8, RuleLocation = 9, RuleActivities = 10, RuleInvariants = 11, 
    RuleConstantexpr = 12, RuleConnector = 13, RuleTerm = 14, RulePolynom = 15, 
    RuleInterval = 16, RuleEquation = 17, RuleConstraint = 18, RuleIntervalexpr = 19, 
    RuleConstrset = 20, RuleReplacedexpr = 21, RuleInit = 22, RuleInitstate = 23, 
    RuleUnsafeset = 24, RuleLbadstate = 25, RuleGbadstate = 26, RuleJumps = 27, 
    RuleTransition = 28, RuleFromto = 29, RuleUrgent = 30, RuleGuard = 31, 
    RuleAllocation = 32, RuleResetfct = 33, RuleAggregation = 34, RuleLabels = 35, 
    RuleLabel = 36, RuleSetting = 37, RuleFixedsteps = 38, RuleTime = 39, 
    RulePlotsetting = 40, RuleFilename = 41, RuleMaxjumps = 42, RulePrint = 43, 
    RuleRemainder = 44, RuleIdentity = 45, RuleFixedorders = 46, RuleCutoff = 47, 
    RulePrecision = 48
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
  class OldContext;
  class AutomatonContext;
  class CompContext;
  class VardeclarationContext;
  class ConstantdeclarationContext;
  class GlobalvardeclarationContext;
  class ComponentContext;
  class ModesContext;
  class LocationContext;
  class ActivitiesContext;
  class InvariantsContext;
  class ConstantexprContext;
  class ConnectorContext;
  class TermContext;
  class PolynomContext;
  class IntervalContext;
  class EquationContext;
  class ConstraintContext;
  class IntervalexprContext;
  class ConstrsetContext;
  class ReplacedexprContext;
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
  class AllocationContext;
  class ResetfctContext;
  class AggregationContext;
  class LabelsContext;
  class LabelContext;
  class SettingContext;
  class FixedstepsContext;
  class TimeContext;
  class PlotsettingContext;
  class FilenameContext;
  class MaxjumpsContext;
  class PrintContext;
  class RemainderContext;
  class IdentityContext;
  class FixedordersContext;
  class CutoffContext;
  class PrecisionContext; 

  class  StartContext : public antlr4::ParserRuleContext {
  public:
    StartContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    OldContext *old();
    CompContext *comp();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StartContext* start();

  class  OldContext : public antlr4::ParserRuleContext {
  public:
    OldContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CBOPEN();
    AutomatonContext *automaton();
    antlr4::tree::TerminalNode *CBCLOSE();
    UnsafesetContext *unsafeset();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OldContext* old();

  class  AutomatonContext : public antlr4::ParserRuleContext {
  public:
    AutomatonContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VardeclarationContext *vardeclaration();
    ModesContext *modes();
    JumpsContext *jumps();
    ConstantdeclarationContext *constantdeclaration();
    SettingContext *setting();
    std::vector<InitContext *> init();
    InitContext* init(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AutomatonContext* automaton();

  class  CompContext : public antlr4::ParserRuleContext {
  public:
    CompContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SettingContext *setting();
    std::vector<antlr4::tree::TerminalNode *> CBOPEN();
    antlr4::tree::TerminalNode* CBOPEN(size_t i);
    std::vector<antlr4::tree::TerminalNode *> CBCLOSE();
    antlr4::tree::TerminalNode* CBCLOSE(size_t i);
    GlobalvardeclarationContext *globalvardeclaration();
    std::vector<ComponentContext *> component();
    ComponentContext* component(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CompContext* comp();

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

  class  GlobalvardeclarationContext : public antlr4::ParserRuleContext {
  public:
    GlobalvardeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> VARIABLE();
    antlr4::tree::TerminalNode* VARIABLE(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GlobalvardeclarationContext* globalvardeclaration();

  class  ComponentContext : public antlr4::ParserRuleContext {
  public:
    ComponentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VARIABLE();
    antlr4::tree::TerminalNode *CBOPEN();
    AutomatonContext *automaton();
    antlr4::tree::TerminalNode *CBCLOSE();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ComponentContext* component();

  class  ModesContext : public antlr4::ParserRuleContext {
  public:
    ModesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
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
    ActivitiesContext *activities();
    std::vector<InvariantsContext *> invariants();
    InvariantsContext* invariants(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LocationContext* location();

  class  ActivitiesContext : public antlr4::ParserRuleContext {
  public:
    ActivitiesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<EquationContext *> equation();
    EquationContext* equation(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ActivitiesContext* activities();

  class  InvariantsContext : public antlr4::ParserRuleContext {
  public:
    InvariantsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConstrsetContext *constrset();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InvariantsContext* invariants();

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
    std::vector<antlr4::tree::TerminalNode *> TIMES();
    antlr4::tree::TerminalNode* TIMES(size_t i);
    std::vector<ConnectorContext *> connector();
    ConnectorContext* connector(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TermContext* term();

  class  PolynomContext : public antlr4::ParserRuleContext {
  public:
    PolynomContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TermContext *> term();
    TermContext* term(size_t i);
    std::vector<ConnectorContext *> connector();
    ConnectorContext* connector(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PolynomContext* polynom();

  class  IntervalContext : public antlr4::ParserRuleContext {
  public:
    IntervalContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> NUMBER();
    antlr4::tree::TerminalNode* NUMBER(size_t i);
    std::vector<antlr4::tree::TerminalNode *> VARIABLE();
    antlr4::tree::TerminalNode* VARIABLE(size_t i);
    std::vector<antlr4::tree::TerminalNode *> MINUS();
    antlr4::tree::TerminalNode* MINUS(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IntervalContext* interval();

  class  EquationContext : public antlr4::ParserRuleContext {
  public:
    EquationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VARIABLE();
    antlr4::tree::TerminalNode *EQUALS();
    PolynomContext *polynom();
    ConnectorContext *connector();
    IntervalContext *interval();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EquationContext* equation();

  class  ConstraintContext : public antlr4::ParserRuleContext {
  public:
    ConstraintContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<PolynomContext *> polynom();
    PolynomContext* polynom(size_t i);
    antlr4::tree::TerminalNode *BOOLRELATION();
    antlr4::tree::TerminalNode *EQUALS();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConstraintContext* constraint();

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
    std::vector<ConstraintContext *> constraint();
    ConstraintContext* constraint(size_t i);
    std::vector<IntervalexprContext *> intervalexpr();
    IntervalexprContext* intervalexpr(size_t i);
    antlr4::tree::TerminalNode *TRUE();
    antlr4::tree::TerminalNode *FALSE();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConstrsetContext* constrset();

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

  class  InitContext : public antlr4::ParserRuleContext {
  public:
    InitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
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
    ConstrsetContext *constrset();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InitstateContext* initstate();

  class  UnsafesetContext : public antlr4::ParserRuleContext {
  public:
    UnsafesetContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
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
    std::vector<ResetfctContext *> resetfct();
    ResetfctContext* resetfct(size_t i);
    std::vector<AggregationContext *> aggregation();
    AggregationContext* aggregation(size_t i);
    std::vector<LabelsContext *> labels();
    LabelsContext* labels(size_t i);

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

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UrgentContext* urgent();

  class  GuardContext : public antlr4::ParserRuleContext {
  public:
    GuardContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConstrsetContext *constrset();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GuardContext* guard();

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
    std::vector<AllocationContext *> allocation();
    AllocationContext* allocation(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ResetfctContext* resetfct();

  class  AggregationContext : public antlr4::ParserRuleContext {
  public:
    AggregationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PARALLELOTOPE();
    antlr4::tree::TerminalNode *BOX();
    antlr4::tree::TerminalNode *INTERVALAGG();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AggregationContext* aggregation();

  class  LabelsContext : public antlr4::ParserRuleContext {
  public:
    LabelsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<LabelContext *> label();
    LabelContext* label(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LabelsContext* labels();

  class  LabelContext : public antlr4::ParserRuleContext {
  public:
    LabelContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VARIABLE();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LabelContext* label();

  class  SettingContext : public antlr4::ParserRuleContext {
  public:
    SettingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<FixedstepsContext *> fixedsteps();
    FixedstepsContext* fixedsteps(size_t i);
    std::vector<TimeContext *> time();
    TimeContext* time(size_t i);
    std::vector<RemainderContext *> remainder();
    RemainderContext* remainder(size_t i);
    std::vector<IdentityContext *> identity();
    IdentityContext* identity(size_t i);
    std::vector<PlotsettingContext *> plotsetting();
    PlotsettingContext* plotsetting(size_t i);
    std::vector<FixedordersContext *> fixedorders();
    FixedordersContext* fixedorders(size_t i);
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

  class  FixedordersContext : public antlr4::ParserRuleContext {
  public:
    FixedordersContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NUMBER();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FixedordersContext* fixedorders();

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

