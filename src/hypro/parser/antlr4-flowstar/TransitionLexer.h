
// Generated from Transition.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"




class  TransitionLexer : public antlr4::Lexer {
public:
  enum {
    PARALLELOTOPE = 1, BOX = 2, JUMP = 3, DEFINE = 4, IN = 5, PAR = 6, JUMPS = 7, 
    URGENT = 8, GUARD = 9, RESET = 10, COMMENT = 11, EQUALS = 12, BOOLRELATION = 13, 
    PLUS = 14, MINUS = 15, TIMES = 16, SBOPEN = 17, SBCLOSE = 18, CBOPEN = 19, 
    CBCLOSE = 20, COMMA = 21, NUMBER = 22, CONSTANT = 23, VARIABLE = 24, 
    WS = 25
  };

  TransitionLexer(antlr4::CharStream *input);
  ~TransitionLexer();


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

