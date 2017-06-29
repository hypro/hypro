
// Generated from Formula.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"




class  FormulaParser : public antlr4::Parser {
public:
  enum {
    IN = 1, EQUALS = 2, BOOLRELATION = 3, BINOPERATOR = 4, VARIABLE = 5, 
    NUMBER = 6, INTERVAL = 7, WS = 8
  };

  enum {
    RuleTerm = 0, RuleEquation = 1, RuleBoolexpr = 2, RuleIntervalexpr = 3, 
    RuleFormula = 4
  };

  FormulaParser(antlr4::TokenStream *input);
  ~FormulaParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class TermContext;
  class EquationContext;
  class BoolexprContext;
  class IntervalexprContext;
  class FormulaContext; 

  class  TermContext : public antlr4::ParserRuleContext {
  public:
    TermContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> NUMBER();
    antlr4::tree::TerminalNode* NUMBER(size_t i);
    std::vector<antlr4::tree::TerminalNode *> VARIABLE();
    antlr4::tree::TerminalNode* VARIABLE(size_t i);
    std::vector<antlr4::tree::TerminalNode *> BINOPERATOR();
    antlr4::tree::TerminalNode* BINOPERATOR(size_t i);

   
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

