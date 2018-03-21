
// Generated from HybridAutomaton.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"




class  HybridAutomatonLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, T__16 = 17, T__17 = 18, T__18 = 19, T__19 = 20, 
    T__20 = 21, T__21 = 22, IN = 23, TRUE = 24, FALSE = 25, PAR = 26, JUMPS = 27, 
    URGENT = 28, GUARD = 29, RESET = 30, PARALLELOTOPE = 31, BOX = 32, JUMP = 33, 
    DEFINE = 34, COMMENT = 35, EQUALS = 36, BOOLRELATION = 37, PLUS = 38, 
    MINUS = 39, TIMES = 40, SBOPEN = 41, SBCLOSE = 42, CBOPEN = 43, CBCLOSE = 44, 
    COMMA = 45, NUMBER = 46, CONSTANT = 47, VARIABLE = 48, WS = 49, INTERVALAGG = 50, 
    EXPONENTIAL = 51
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

