
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
    T__20 = 21, T__21 = 22, T__22 = 23, POLY = 24, LINEAR = 25, ODE = 26, 
    IN = 27, TRUE = 28, FALSE = 29, PAR = 30, JUMPS = 31, URGENT = 32, GUARD = 33, 
    RESET = 34, PARALLELOTOPE = 35, BOX = 36, JUMP = 37, DEFINE = 38, COMMENT = 39, 
    EQUALS = 40, BOOLRELATION = 41, PLUS = 42, MINUS = 43, TIMES = 44, SBOPEN = 45, 
    SBCLOSE = 46, CBOPEN = 47, CBCLOSE = 48, COMMA = 49, NUMBER = 50, CONSTANT = 51, 
    VARIABLE = 52, WS = 53, INTERVALAGG = 54, EXPONENTIAL = 55
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
