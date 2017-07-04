
// Generated from Location.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"




class  LocationParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, IN = 6, EQUALS = 7, 
    BOOLRELATION = 8, PLUS = 9, TIMES = 10, VARIABLE = 11, NUMBER = 12, 
    INTERVAL = 13, WS = 14
  };

  enum {
    RuleModes = 0, RuleLocation = 1, RuleActivities = 2, RuleInvariants = 3, 
    RuleAdd = 4, RuleMult = 5, RuleTerm = 6, RuleEquation = 7, RuleBoolexpr = 8, 
    RuleIntervalexpr = 9, RuleFormula = 10
  };

  LocationParser(antlr4::TokenStream *input);
  ~LocationParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class ModesContext;
  class LocationContext;
  class ActivitiesContext;
  class InvariantsContext;
  class AddContext;
  class MultContext;
  class TermContext;
  class EquationContext;
  class BoolexprContext;
  class IntervalexprContext;
  class FormulaContext; 

  class  ModesContext : public antlr4::ParserRuleContext {
  public:
    ModesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<LocationContext *> location();
    LocationContext* location(size_t i);

   
  };

  ModesContext* modes();

  class  LocationContext : public antlr4::ParserRuleContext {
  public:
    LocationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VARIABLE();
    ActivitiesContext *activities();
    InvariantsContext *invariants();

   
  };

  LocationContext* location();

  class  ActivitiesContext : public antlr4::ParserRuleContext {
  public:
    ActivitiesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<EquationContext *> equation();
    EquationContext* equation(size_t i);

   
  };

  ActivitiesContext* activities();

  class  InvariantsContext : public antlr4::ParserRuleContext {
  public:
    InvariantsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<BoolexprContext *> boolexpr();
    BoolexprContext* boolexpr(size_t i);
    std::vector<IntervalexprContext *> intervalexpr();
    IntervalexprContext* intervalexpr(size_t i);

   
  };

  InvariantsContext* invariants();

  class  AddContext : public antlr4::ParserRuleContext {
  public:
    AddContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PLUS();
    TermContext *term();

   
  };

  AddContext* add();

  class  MultContext : public antlr4::ParserRuleContext {
  public:
    MultContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> NUMBER();
    antlr4::tree::TerminalNode* NUMBER(size_t i);
    std::vector<antlr4::tree::TerminalNode *> VARIABLE();
    antlr4::tree::TerminalNode* VARIABLE(size_t i);
    std::vector<antlr4::tree::TerminalNode *> TIMES();
    antlr4::tree::TerminalNode* TIMES(size_t i);

   
  };

  MultContext* mult();

  class  TermContext : public antlr4::ParserRuleContext {
  public:
    TermContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    MultContext *mult();
    std::vector<AddContext *> add();
    AddContext* add(size_t i);

   
  };

  TermContext* term();

  class  EquationContext : public antlr4::ParserRuleContext {
  public:
    EquationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VARIABLE();
    antlr4::tree::TerminalNode *EQUALS();
    TermContext *term();

   
  };

  EquationContext* equation();

  class  BoolexprContext : public antlr4::ParserRuleContext {
  public:
    BoolexprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TermContext *term();
    antlr4::tree::TerminalNode *BOOLRELATION();
    antlr4::tree::TerminalNode *NUMBER();

   
  };

  BoolexprContext* boolexpr();

  class  IntervalexprContext : public antlr4::ParserRuleContext {
  public:
    IntervalexprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TermContext *term();
    antlr4::tree::TerminalNode *IN();
    antlr4::tree::TerminalNode *INTERVAL();

   
  };

  IntervalexprContext* intervalexpr();

  class  FormulaContext : public antlr4::ParserRuleContext {
  public:
    FormulaContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    EquationContext *equation();
    BoolexprContext *boolexpr();
    IntervalexprContext *intervalexpr();

   
  };

  FormulaContext* formula();


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

