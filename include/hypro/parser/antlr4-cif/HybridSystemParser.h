
// Generated from HybridSystem.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"


namespace hypro {


class  HybridSystemParser : public antlr4::Parser {
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
    T__104 = 105, T__105 = 106, T__106 = 107, T__107 = 108, T__108 = 109, 
    T__109 = 110, T__110 = 111, T__111 = 112, T__112 = 113, T__113 = 114, 
    T__114 = 115, T__115 = 116, T__116 = 117, T__117 = 118, T__118 = 119, 
    T__119 = 120, T__120 = 121, T__121 = 122, T__122 = 123, T__123 = 124, 
    T__124 = 125, T__125 = 126, T__126 = 127, T__127 = 128, T__128 = 129, 
    T__129 = 130, T__130 = 131, T__131 = 132, T__132 = 133, T__133 = 134, 
    T__134 = 135, T__135 = 136, MULOP = 137, ADDOP = 138, COMPOP = 139, 
    NUMBER = 140, REALNUMBER = 141, STRING = 142, IDENTIFIER = 143, RELATIVENAME = 144, 
    ABSOLUTENAME = 145, ROOTNAME = 146, WS = 147
  };

  enum {
    RuleSpecification = 0, RuleGroupBody = 1, RuleAutomatonBody = 2, RuleOptGroupDecls = 3, 
    RuleGroupDecl = 4, RuleOptAutDecls = 5, RuleAutDecl = 6, RuleDecl = 7, 
    RuleImports = 8, RuleTypeDefs = 9, RuleEnumDefs = 10, RuleConstantDefs = 11, 
    RuleAlgVarsDefs = 12, RuleFuncParams = 13, RuleFuncParamDecls = 14, 
    RuleFuncBody = 15, RuleFuncVarDecls = 16, RuleFuncVarDecl = 17, RuleFuncStatements = 18, 
    RuleFuncStatement = 19, RuleOptElifFuncStats = 20, RuleOptElseFuncStat = 21, 
    RuleEvents = 22, RuleActualParms = 23, RuleFormalParms = 24, RuleFormalDecls = 25, 
    RuleFormalDeclaration = 26, RuleDiscDecls = 27, RuleDiscDecl = 28, RuleContDecls = 29, 
    RuleContDecl = 30, RuleOptDerivate = 31, RuleOptControllability = 32, 
    RuleControllability = 33, RuleEventType = 34, RuleExpressions = 35, 
    RuleOptExpression = 36, RuleExpression = 37, RuleEquations = 38, RuleEquation = 39, 
    RuleOrExpression = 40, RuleAndExpression = 41, RuleCompareExpression = 42, 
    RuleAddExpression = 43, RuleMulExpression = 44, RuleUnaryExpression = 45, 
    RuleFuncExpression = 46, RuleExpressionFactor = 47, RuleNonEmptySetExpression = 48, 
    RuleDictPairs = 49, RuleOptElifExprs = 50, RuleSwitchBody = 51, RuleSwitchCases = 52, 
    RuleTypes = 53, RuleType = 54, RuleFields = 55, RuleField = 56, RuleNameSet = 57, 
    RuleNames = 58, RuleName = 59, RuleOptSupKind = 60, RuleSupKind = 61, 
    RuleIdentifier = 62, RuleStringToken = 63, RuleStdLibFunction = 64, 
    RuleLocations = 65, RuleLocation = 66, RuleLocationElements = 67, RuleLocationElement = 68, 
    RuleCoreEdge = 69, RuleOptEdgeGuard = 70, RuleOptEdgeUrgent = 71, RuleOptEdgeUpdate = 72, 
    RuleEdgeEvents = 73, RuleEdgeEvent = 74, RuleInvariantDecls = 75, RuleInvariants = 76, 
    RuleInvariant = 77, RuleUpdates = 78, RuleUpdate = 79, RuleOptElifUpdates = 80, 
    RuleOptElseUpdate = 81, RuleAdressables = 82, RuleAdressable = 83, RuleProjections = 84, 
    RuleProjection = 85, RuleOptIoDecls = 86, RuleIoDecls = 87, RuleSvgFile = 88, 
    RuleOptSvgFile = 89, RuleSvgCopy = 90, RuleOptSvgCopyPre = 91, RuleOptSvgCopyPost = 92, 
    RuleSvgMove = 93, RuleSvgOut = 94, RuleSvgAttr = 95, RuleSvgIn = 96, 
    RuleSvgInEvent = 97, RuleOptSvgInEventElifs = 98, RuleSvgInEventElifs = 99, 
    RulePrintFile = 100, RulePrint = 101, RulePrintTxt = 102, RuleOptPrintFors = 103, 
    RulePrintFors = 104, RulePrintFor = 105, RuleOptPrintWhen = 106, RuleOptPrintFile = 107
  };

  HybridSystemParser(antlr4::TokenStream *input);
  ~HybridSystemParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class SpecificationContext;
  class GroupBodyContext;
  class AutomatonBodyContext;
  class OptGroupDeclsContext;
  class GroupDeclContext;
  class OptAutDeclsContext;
  class AutDeclContext;
  class DeclContext;
  class ImportsContext;
  class TypeDefsContext;
  class EnumDefsContext;
  class ConstantDefsContext;
  class AlgVarsDefsContext;
  class FuncParamsContext;
  class FuncParamDeclsContext;
  class FuncBodyContext;
  class FuncVarDeclsContext;
  class FuncVarDeclContext;
  class FuncStatementsContext;
  class FuncStatementContext;
  class OptElifFuncStatsContext;
  class OptElseFuncStatContext;
  class EventsContext;
  class ActualParmsContext;
  class FormalParmsContext;
  class FormalDeclsContext;
  class FormalDeclarationContext;
  class DiscDeclsContext;
  class DiscDeclContext;
  class ContDeclsContext;
  class ContDeclContext;
  class OptDerivateContext;
  class OptControllabilityContext;
  class ControllabilityContext;
  class EventTypeContext;
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

  class  SpecificationContext : public antlr4::ParserRuleContext {
  public:
    SpecificationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    GroupBodyContext *groupBody();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SpecificationContext* specification();

  class  GroupBodyContext : public antlr4::ParserRuleContext {
  public:
    GroupBodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    OptGroupDeclsContext *optGroupDecls();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GroupBodyContext* groupBody();

  class  AutomatonBodyContext : public antlr4::ParserRuleContext {
  public:
    AutomatonBodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    OptAutDeclsContext *optAutDecls();
    LocationsContext *locations();
    OptIoDeclsContext *optIoDecls();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AutomatonBodyContext* automatonBody();

  class  OptGroupDeclsContext : public antlr4::ParserRuleContext {
  public:
    OptGroupDeclsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<GroupDeclContext *> groupDecl();
    GroupDeclContext* groupDecl(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OptGroupDeclsContext* optGroupDecls();

  class  GroupDeclContext : public antlr4::ParserRuleContext {
  public:
    GroupDeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DeclContext *decl();
    ImportsContext *imports();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *RELATIVENAME();
    TypesContext *types();
    IdentifierContext *identifier();
    FuncParamsContext *funcParams();
    FuncBodyContext *funcBody();
    NameContext *name();
    ActualParmsContext *actualParms();
    FormalParmsContext *formalParms();
    GroupBodyContext *groupBody();
    OptSupKindContext *optSupKind();
    AutomatonBodyContext *automatonBody();
    SupKindContext *supKind();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GroupDeclContext* groupDecl();

  class  OptAutDeclsContext : public antlr4::ParserRuleContext {
  public:
    OptAutDeclsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<AutDeclContext *> autDecl();
    AutDeclContext* autDecl(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OptAutDeclsContext* optAutDecls();

  class  AutDeclContext : public antlr4::ParserRuleContext {
  public:
    AutDeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DeclContext *decl();
    EventsContext *events();
    TypeContext *type();
    DiscDeclsContext *discDecls();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AutDeclContext* autDecl();

  class  DeclContext : public antlr4::ParserRuleContext {
  public:
    DeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeDefsContext *typeDefs();
    EnumDefsContext *enumDefs();
    OptControllabilityContext *optControllability();
    IdentifierContext *identifier();
    EventTypeContext *eventType();
    ControllabilityContext *controllability();
    TypeContext *type();
    ConstantDefsContext *constantDefs();
    AlgVarsDefsContext *algVarsDefs();
    ContDeclsContext *contDecls();
    EquationsContext *equations();
    ExpressionsContext *expressions();
    InvariantDeclsContext *invariantDecls();
    IoDeclsContext *ioDecls();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DeclContext* decl();

  class  ImportsContext : public antlr4::ParserRuleContext {
  public:
    ImportsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<StringTokenContext *> stringToken();
    StringTokenContext* stringToken(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ImportsContext* imports();

  class  TypeDefsContext : public antlr4::ParserRuleContext {
  public:
    TypeDefsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<IdentifierContext *> identifier();
    IdentifierContext* identifier(size_t i);
    std::vector<TypeContext *> type();
    TypeContext* type(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeDefsContext* typeDefs();

  class  EnumDefsContext : public antlr4::ParserRuleContext {
  public:
    EnumDefsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<IdentifierContext *> identifier();
    IdentifierContext* identifier(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EnumDefsContext* enumDefs();

  class  ConstantDefsContext : public antlr4::ParserRuleContext {
  public:
    ConstantDefsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<IdentifierContext *> identifier();
    IdentifierContext* identifier(size_t i);
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConstantDefsContext* constantDefs();

  class  AlgVarsDefsContext : public antlr4::ParserRuleContext {
  public:
    AlgVarsDefsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<IdentifierContext *> identifier();
    IdentifierContext* identifier(size_t i);
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AlgVarsDefsContext* algVarsDefs();

  class  FuncParamsContext : public antlr4::ParserRuleContext {
  public:
    FuncParamsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FuncParamDeclsContext *funcParamDecls();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FuncParamsContext* funcParams();

  class  FuncParamDeclsContext : public antlr4::ParserRuleContext {
  public:
    FuncParamDeclsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TypeContext *> type();
    TypeContext* type(size_t i);
    std::vector<IdentifierContext *> identifier();
    IdentifierContext* identifier(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FuncParamDeclsContext* funcParamDecls();

  class  FuncBodyContext : public antlr4::ParserRuleContext {
  public:
    FuncBodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FuncVarDeclsContext *funcVarDecls();
    FuncStatementsContext *funcStatements();
    StringTokenContext *stringToken();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FuncBodyContext* funcBody();

  class  FuncVarDeclsContext : public antlr4::ParserRuleContext {
  public:
    FuncVarDeclsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TypeContext *> type();
    TypeContext* type(size_t i);
    std::vector<FuncVarDeclContext *> funcVarDecl();
    FuncVarDeclContext* funcVarDecl(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FuncVarDeclsContext* funcVarDecls();

  class  FuncVarDeclContext : public antlr4::ParserRuleContext {
  public:
    FuncVarDeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<IdentifierContext *> identifier();
    IdentifierContext* identifier(size_t i);
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FuncVarDeclContext* funcVarDecl();

  class  FuncStatementsContext : public antlr4::ParserRuleContext {
  public:
    FuncStatementsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<FuncStatementContext *> funcStatement();
    FuncStatementContext* funcStatement(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FuncStatementsContext* funcStatements();

  class  FuncStatementContext : public antlr4::ParserRuleContext {
  public:
    FuncStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AdressablesContext *adressables();
    ExpressionsContext *expressions();
    FuncStatementsContext *funcStatements();
    OptElifFuncStatsContext *optElifFuncStats();
    OptElseFuncStatContext *optElseFuncStat();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FuncStatementContext* funcStatement();

  class  OptElifFuncStatsContext : public antlr4::ParserRuleContext {
  public:
    OptElifFuncStatsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    std::vector<FuncStatementsContext *> funcStatements();
    FuncStatementsContext* funcStatements(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OptElifFuncStatsContext* optElifFuncStats();

  class  OptElseFuncStatContext : public antlr4::ParserRuleContext {
  public:
    OptElseFuncStatContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FuncStatementsContext *funcStatements();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OptElseFuncStatContext* optElseFuncStat();

  class  EventsContext : public antlr4::ParserRuleContext {
  public:
    EventsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<NameContext *> name();
    NameContext* name(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EventsContext* events();

  class  ActualParmsContext : public antlr4::ParserRuleContext {
  public:
    ActualParmsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionsContext *expressions();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ActualParmsContext* actualParms();

  class  FormalParmsContext : public antlr4::ParserRuleContext {
  public:
    FormalParmsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FormalDeclsContext *formalDecls();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FormalParmsContext* formalParms();

  class  FormalDeclsContext : public antlr4::ParserRuleContext {
  public:
    FormalDeclsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<FormalDeclarationContext *> formalDeclaration();
    FormalDeclarationContext* formalDeclaration(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FormalDeclsContext* formalDecls();

  class  FormalDeclarationContext : public antlr4::ParserRuleContext {
  public:
    FormalDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    OptControllabilityContext *optControllability();
    IdentifierContext *identifier();
    EventTypeContext *eventType();
    ControllabilityContext *controllability();
    NameContext *name();
    TypeContext *type();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FormalDeclarationContext* formalDeclaration();

  class  DiscDeclsContext : public antlr4::ParserRuleContext {
  public:
    DiscDeclsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<DiscDeclContext *> discDecl();
    DiscDeclContext* discDecl(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DiscDeclsContext* discDecls();

  class  DiscDeclContext : public antlr4::ParserRuleContext {
  public:
    DiscDeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    ExpressionContext *expression();
    ExpressionsContext *expressions();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DiscDeclContext* discDecl();

  class  ContDeclsContext : public antlr4::ParserRuleContext {
  public:
    ContDeclsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ContDeclContext *> contDecl();
    ContDeclContext* contDecl(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ContDeclsContext* contDecls();

  class  ContDeclContext : public antlr4::ParserRuleContext {
  public:
    ContDeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    OptDerivateContext *optDerivate();
    ExpressionContext *expression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ContDeclContext* contDecl();

  class  OptDerivateContext : public antlr4::ParserRuleContext {
  public:
    OptDerivateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OptDerivateContext* optDerivate();

  class  OptControllabilityContext : public antlr4::ParserRuleContext {
  public:
    OptControllabilityContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ControllabilityContext *controllability();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OptControllabilityContext* optControllability();

  class  ControllabilityContext : public antlr4::ParserRuleContext {
  public:
    ControllabilityContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ControllabilityContext* controllability();

  class  EventTypeContext : public antlr4::ParserRuleContext {
  public:
    EventTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeContext *type();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EventTypeContext* eventType();

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
   
    EquationContext() = default;
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
   
    UnaryExpressionContext() = default;
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
   
    ExpressionFactorContext() = default;
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
   
    LocationContext() = default;
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
   
    LocationElementContext() = default;
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
   
    InvariantContext() = default;
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
   
    UpdateContext() = default;
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
   
    AdressableContext() = default;
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

}  // namespace hypro
