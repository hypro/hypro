
// Generated from HybridAutomaton.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"


namespace hypro {


class  HybridAutomatonLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, T__16 = 17, T__17 = 18, T__18 = 19, T__19 = 20, 
    T__20 = 21, T__21 = 22, T__22 = 23, POLY = 24, LINEAR = 25, NONLINEAR = 26, 
    NONPOLY = 27, LTI = 28, ODE = 29, IN = 30, TRUE = 31, FALSE = 32, PAR = 33, 
    JUMPS = 34, URGENT = 35, GUARD = 36, RESET = 37, PARALLELOTOPE = 38, 
    BOX = 39, JUMP = 40, DEFINE = 41, COMMENT = 42, EQUALS = 43, BOOLRELATION = 44, 
    PLUS = 45, MINUS = 46, TIMES = 47, DIVIDE = 48, SBOPEN = 49, SBCLOSE = 50, 
    CBOPEN = 51, CBCLOSE = 52, RBOPEN = 53, RBCLOSE = 54, COMMA = 55, NUMBER = 56, 
    CONSTANT = 57, VARIABLE = 58, WS = 59, INTERVALAGG = 60, EXPONENTIAL = 61
  };

  HybridAutomatonLexer(antlr4::CharStream *input);
  ~HybridAutomatonLexer();


  	bool parsingConstants = false;

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

  virtual void action(antlr4::RuleContext *context, size_t ruleIndex, size_t actionIndex) override;
private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.
  void PARAction(antlr4::RuleContext *context, size_t actionIndex);
  void CBCLOSEAction(antlr4::RuleContext *context, size_t actionIndex);
  void CONSTANTAction(antlr4::RuleContext *context, size_t actionIndex);
  void VARIABLEAction(antlr4::RuleContext *context, size_t actionIndex);

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

}  // namespace hypro
