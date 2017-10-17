
// Generated from CIFLocation.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"




class  CIFLocationParser : public antlr4::Parser {
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
    T__92 = 93, T__93 = 94, MULOP = 95, ADDOP = 96, COMPOP = 97, NUMBER = 98, 
    REALNUMBER = 99, STRING = 100, IDENTIFIER = 101, RELATIVENAME = 102, 
    ABSOLUTENAME = 103, ROOTNAME = 104, WS = 105
  };

  enum {
    RuleLocations = 0, RuleLocation = 1, RuleLocationElements = 2, RuleLocationElement = 3, 
    RuleCoreEdge = 4, RuleOptEdgeGuard = 5, RuleOptEdgeUrgent = 6, RuleOptEdgeUpdate = 7, 
    RuleEdgeEvents = 8, RuleEdgeEvent = 9, RuleInvariantDecls = 10, RuleInvariants = 11, 
    RuleInvariant = 12, RuleUpdates = 13, RuleUpdate = 14, RuleOptElifUpdates = 15, 
    RuleOptElseUpdate = 16, RuleAdressables = 17, RuleAdressable = 18, RuleProjections = 19, 
    RuleProjection = 20, RuleExpressions = 21, RuleOptExpression = 22, RuleExpression = 23, 
    RuleEquations = 24, RuleEquation = 25, RuleOrExpression = 26, RuleAndExpression = 27, 
    RuleCompareExpression = 28, RuleAddExpression = 29, RuleMulExpression = 30, 
    RuleUnaryExpression = 31, RuleFuncExpression = 32, RuleExpressionFactor = 33, 
    RuleNonEmptySetExpression = 34, RuleDictPairs = 35, RuleOptElifExprs = 36, 
    RuleSwitchBody = 37, RuleSwitchCases = 38, RuleTypes = 39, RuleType = 40, 
    RuleFields = 41, RuleField = 42, RuleNameSet = 43, RuleNames = 44, RuleName = 45, 
    RuleOptSupKind = 46, RuleSupKind = 47, RuleIdentifier = 48, RuleStringToken = 49, 
    RuleStdLibFunction = 50
  };

  CIFLocationParser(antlr4::TokenStream *input);
  ~CIFLocationParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class LocationsContext;
  class LocationContext;
  class LocationElementsContext;
  class LocationElementContext;
  class CoreEdgeContext;
  class OptEdgeGuardContext;
  class OptEdgeUrgentContext;
  class OptEdgeUpdateContext;
  class EdgeEventsContext;
  class EdgeEventContext;
  class InvariantDeclsContext;
  class InvariantsContext;
  class InvariantContext;
  class UpdatesContext;
  class UpdateContext;
  class OptElifUpdatesContext;
  class OptElseUpdateContext;
  class AdressablesContext;
  class AdressableContext;
  class ProjectionsContext;
  class ProjectionContext;
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

  class  LocationsContext : public antlr4::ParserRuleContext {
  public:
    LocationsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<LocationContext *> location();
    LocationContext* location(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LocationsContext* locations();

  class  LocationContext : public antlr4::ParserRuleContext {
  public:
    LocationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    LocationContext() : antlr4::ParserRuleContext() { }
    void copyFrom(LocationContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  LocElemContext : public LocationContext {
  public:
    LocElemContext(LocationContext *ctx);

    LocationElementsContext *locationElements();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LocContext : public LocationContext {
  public:
    LocContext(LocationContext *ctx);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LocIdElemContext : public LocationContext {
  public:
    LocIdElemContext(LocationContext *ctx);

    IdentifierContext *identifier();
    LocationElementsContext *locationElements();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LocIdContext : public LocationContext {
  public:
    LocIdContext(LocationContext *ctx);

    IdentifierContext *identifier();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  LocationContext* location();

  class  LocationElementsContext : public antlr4::ParserRuleContext {
  public:
    LocationElementsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<LocationElementContext *> locationElement();
    LocationElementContext* locationElement(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LocationElementsContext* locationElements();

  class  LocationElementContext : public antlr4::ParserRuleContext {
  public:
    LocationElementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    LocationElementContext() : antlr4::ParserRuleContext() { }
    void copyFrom(LocationElementContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  LocElemEdgeToContext : public LocationElementContext {
  public:
    LocElemEdgeToContext(LocationElementContext *ctx);

    CoreEdgeContext *coreEdge();
    IdentifierContext *identifier();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LocElemMarkedContext : public LocationElementContext {
  public:
    LocElemMarkedContext(LocationElementContext *ctx);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LocElemInvContext : public LocationElementContext {
  public:
    LocElemInvContext(LocationElementContext *ctx);

    InvariantDeclsContext *invariantDecls();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LocElemMarkedExprContext : public LocationElementContext {
  public:
    LocElemMarkedExprContext(LocationElementContext *ctx);

    ExpressionsContext *expressions();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LocElemUrgentContext : public LocationElementContext {
  public:
    LocElemUrgentContext(LocationElementContext *ctx);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LocElemLoopContext : public LocationElementContext {
  public:
    LocElemLoopContext(LocationElementContext *ctx);

    CoreEdgeContext *coreEdge();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LocElemInitialFlagContext : public LocationElementContext {
  public:
    LocElemInitialFlagContext(LocationElementContext *ctx);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LocElemInitialFlagExprContext : public LocationElementContext {
  public:
    LocElemInitialFlagExprContext(LocationElementContext *ctx);

    ExpressionsContext *expressions();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LocElemEqsContext : public LocationElementContext {
  public:
    LocElemEqsContext(LocationElementContext *ctx);

    EquationsContext *equations();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  LocationElementContext* locationElement();

  class  CoreEdgeContext : public antlr4::ParserRuleContext {
  public:
    CoreEdgeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    EdgeEventsContext *edgeEvents();
    OptEdgeGuardContext *optEdgeGuard();
    OptEdgeUrgentContext *optEdgeUrgent();
    OptEdgeUpdateContext *optEdgeUpdate();
    ExpressionsContext *expressions();
    UpdatesContext *updates();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CoreEdgeContext* coreEdge();

  class  OptEdgeGuardContext : public antlr4::ParserRuleContext {
  public:
    OptEdgeGuardContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionsContext *expressions();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OptEdgeGuardContext* optEdgeGuard();

  class  OptEdgeUrgentContext : public antlr4::ParserRuleContext {
  public:
    OptEdgeUrgentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OptEdgeUrgentContext* optEdgeUrgent();

  class  OptEdgeUpdateContext : public antlr4::ParserRuleContext {
  public:
    OptEdgeUpdateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    UpdatesContext *updates();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OptEdgeUpdateContext* optEdgeUpdate();

  class  EdgeEventsContext : public antlr4::ParserRuleContext {
  public:
    EdgeEventsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<EdgeEventContext *> edgeEvent();
    EdgeEventContext* edgeEvent(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EdgeEventsContext* edgeEvents();

  class  EdgeEventContext : public antlr4::ParserRuleContext {
  public:
    EdgeEventContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NameContext *name();
    ExpressionContext *expression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EdgeEventContext* edgeEvent();

  class  InvariantDeclsContext : public antlr4::ParserRuleContext {
  public:
    InvariantDeclsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    OptSupKindContext *optSupKind();
    InvariantsContext *invariants();
    SupKindContext *supKind();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InvariantDeclsContext* invariantDecls();

  class  InvariantsContext : public antlr4::ParserRuleContext {
  public:
    InvariantsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<InvariantContext *> invariant();
    InvariantContext* invariant(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InvariantsContext* invariants();

  class  InvariantContext : public antlr4::ParserRuleContext {
  public:
    InvariantContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    InvariantContext() : antlr4::ParserRuleContext() { }
    void copyFrom(InvariantContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  InvNeedsContext : public InvariantContext {
  public:
    InvNeedsContext(InvariantContext *ctx);

    NameContext *name();
    ExpressionContext *expression();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  InvExprContext : public InvariantContext {
  public:
    InvExprContext(InvariantContext *ctx);

    ExpressionContext *expression();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  InvDisablesContext : public InvariantContext {
  public:
    InvDisablesContext(InvariantContext *ctx);

    ExpressionContext *expression();
    NameContext *name();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  InvNeedsSetContext : public InvariantContext {
  public:
    InvNeedsSetContext(InvariantContext *ctx);

    NonEmptySetExpressionContext *nonEmptySetExpression();
    ExpressionContext *expression();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  InvDisablesSetContext : public InvariantContext {
  public:
    InvDisablesSetContext(InvariantContext *ctx);

    ExpressionContext *expression();
    NameSetContext *nameSet();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  InvariantContext* invariant();

  class  UpdatesContext : public antlr4::ParserRuleContext {
  public:
    UpdatesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<UpdateContext *> update();
    UpdateContext* update(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UpdatesContext* updates();

  class  UpdateContext : public antlr4::ParserRuleContext {
  public:
    UpdateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    UpdateContext() : antlr4::ParserRuleContext() { }
    void copyFrom(UpdateContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  UpdateNonIfContext : public UpdateContext {
  public:
    UpdateNonIfContext(UpdateContext *ctx);

    AdressableContext *adressable();
    ExpressionContext *expression();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  UpdateIfContext : public UpdateContext {
  public:
    UpdateIfContext(UpdateContext *ctx);

    ExpressionsContext *expressions();
    UpdatesContext *updates();
    OptElifUpdatesContext *optElifUpdates();
    OptElseUpdateContext *optElseUpdate();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  UpdateContext* update();

  class  OptElifUpdatesContext : public antlr4::ParserRuleContext {
  public:
    OptElifUpdatesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionsContext *> expressions();
    ExpressionsContext* expressions(size_t i);
    std::vector<UpdatesContext *> updates();
    UpdatesContext* updates(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OptElifUpdatesContext* optElifUpdates();

  class  OptElseUpdateContext : public antlr4::ParserRuleContext {
  public:
    OptElseUpdateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    UpdateContext *update();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OptElseUpdateContext* optElseUpdate();

  class  AdressablesContext : public antlr4::ParserRuleContext {
  public:
    AdressablesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<AdressableContext *> adressable();
    AdressableContext* adressable(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AdressablesContext* adressables();

  class  AdressableContext : public antlr4::ParserRuleContext {
  public:
    AdressableContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    AdressableContext() : antlr4::ParserRuleContext() { }
    void copyFrom(AdressableContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  AdressableIdContext : public AdressableContext {
  public:
    AdressableIdContext(AdressableContext *ctx);

    IdentifierContext *identifier();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AdressableProjContext : public AdressableContext {
  public:
    AdressableProjContext(AdressableContext *ctx);

    IdentifierContext *identifier();
    ProjectionsContext *projections();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AdressablePairContext : public AdressableContext {
  public:
    AdressablePairContext(AdressableContext *ctx);

    std::vector<AdressableContext *> adressable();
    AdressableContext* adressable(size_t i);
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  AdressableContext* adressable();

  class  ProjectionsContext : public antlr4::ParserRuleContext {
  public:
    ProjectionsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ProjectionContext *> projection();
    ProjectionContext* projection(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProjectionsContext* projections();

  class  ProjectionContext : public antlr4::ParserRuleContext {
  public:
    ProjectionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProjectionContext* projection();

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

