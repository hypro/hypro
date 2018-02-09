
// Generated from InitialSet.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"




class  InitialSetLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, IN = 2, PAR = 3, JUMPS = 4, URGENT = 5, GUARD = 6, RESET = 7, 
    PARALLELOTOPE = 8, BOX = 9, JUMP = 10, DEFINE = 11, COMMENT = 12, EQUALS = 13, 
    BOOLRELATION = 14, PLUS = 15, MINUS = 16, TIMES = 17, SBOPEN = 18, SBCLOSE = 19, 
    CBOPEN = 20, CBCLOSE = 21, COMMA = 22, NUMBER = 23, CONSTANT = 24, VARIABLE = 25, 
    WS = 26
  };

  InitialSetLexer(antlr4::CharStream *input);
  ~InitialSetLexer();


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

