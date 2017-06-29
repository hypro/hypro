
// Generated from Formula.g4 by ANTLR 4.7



#include "FormulaParser.h"


using namespace antlrcpp;
using namespace antlr4;

FormulaParser::FormulaParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

FormulaParser::~FormulaParser() {
  delete _interpreter;
}

std::string FormulaParser::getGrammarFileName() const {
  return "Formula.g4";
}

const std::vector<std::string>& FormulaParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& FormulaParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- TermContext ------------------------------------------------------------------

FormulaParser::TermContext::TermContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> FormulaParser::TermContext::NUMBER() {
  return getTokens(FormulaParser::NUMBER);
}

tree::TerminalNode* FormulaParser::TermContext::NUMBER(size_t i) {
  return getToken(FormulaParser::NUMBER, i);
}

std::vector<tree::TerminalNode *> FormulaParser::TermContext::VARIABLE() {
  return getTokens(FormulaParser::VARIABLE);
}

tree::TerminalNode* FormulaParser::TermContext::VARIABLE(size_t i) {
  return getToken(FormulaParser::VARIABLE, i);
}

std::vector<tree::TerminalNode *> FormulaParser::TermContext::BINOPERATOR() {
  return getTokens(FormulaParser::BINOPERATOR);
}

tree::TerminalNode* FormulaParser::TermContext::BINOPERATOR(size_t i) {
  return getToken(FormulaParser::BINOPERATOR, i);
}


size_t FormulaParser::TermContext::getRuleIndex() const {
  return FormulaParser::RuleTerm;
}


FormulaParser::TermContext* FormulaParser::term() {
  TermContext *_localctx = _tracker.createInstance<TermContext>(_ctx, getState());
  enterRule(_localctx, 0, FormulaParser::RuleTerm);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(10);
    _la = _input->LA(1);
    if (!(_la == FormulaParser::VARIABLE

    || _la == FormulaParser::NUMBER)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(17);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == FormulaParser::BINOPERATOR) {
      setState(13); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(11);
        match(FormulaParser::BINOPERATOR);
        setState(12);
        _la = _input->LA(1);
        if (!(_la == FormulaParser::VARIABLE

        || _la == FormulaParser::NUMBER)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(15); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == FormulaParser::BINOPERATOR);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EquationContext ------------------------------------------------------------------

FormulaParser::EquationContext::EquationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* FormulaParser::EquationContext::VARIABLE() {
  return getToken(FormulaParser::VARIABLE, 0);
}

tree::TerminalNode* FormulaParser::EquationContext::EQUALS() {
  return getToken(FormulaParser::EQUALS, 0);
}

FormulaParser::TermContext* FormulaParser::EquationContext::term() {
  return getRuleContext<FormulaParser::TermContext>(0);
}


size_t FormulaParser::EquationContext::getRuleIndex() const {
  return FormulaParser::RuleEquation;
}


FormulaParser::EquationContext* FormulaParser::equation() {
  EquationContext *_localctx = _tracker.createInstance<EquationContext>(_ctx, getState());
  enterRule(_localctx, 2, FormulaParser::RuleEquation);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(19);
    match(FormulaParser::VARIABLE);
    setState(20);
    match(FormulaParser::EQUALS);
    setState(21);
    term();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BoolexprContext ------------------------------------------------------------------

FormulaParser::BoolexprContext::BoolexprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

FormulaParser::TermContext* FormulaParser::BoolexprContext::term() {
  return getRuleContext<FormulaParser::TermContext>(0);
}

tree::TerminalNode* FormulaParser::BoolexprContext::BOOLRELATION() {
  return getToken(FormulaParser::BOOLRELATION, 0);
}

tree::TerminalNode* FormulaParser::BoolexprContext::NUMBER() {
  return getToken(FormulaParser::NUMBER, 0);
}


size_t FormulaParser::BoolexprContext::getRuleIndex() const {
  return FormulaParser::RuleBoolexpr;
}


FormulaParser::BoolexprContext* FormulaParser::boolexpr() {
  BoolexprContext *_localctx = _tracker.createInstance<BoolexprContext>(_ctx, getState());
  enterRule(_localctx, 4, FormulaParser::RuleBoolexpr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(23);
    term();
    setState(24);
    match(FormulaParser::BOOLRELATION);
    setState(25);
    match(FormulaParser::NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IntervalexprContext ------------------------------------------------------------------

FormulaParser::IntervalexprContext::IntervalexprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

FormulaParser::TermContext* FormulaParser::IntervalexprContext::term() {
  return getRuleContext<FormulaParser::TermContext>(0);
}

tree::TerminalNode* FormulaParser::IntervalexprContext::IN() {
  return getToken(FormulaParser::IN, 0);
}

tree::TerminalNode* FormulaParser::IntervalexprContext::INTERVAL() {
  return getToken(FormulaParser::INTERVAL, 0);
}


size_t FormulaParser::IntervalexprContext::getRuleIndex() const {
  return FormulaParser::RuleIntervalexpr;
}


FormulaParser::IntervalexprContext* FormulaParser::intervalexpr() {
  IntervalexprContext *_localctx = _tracker.createInstance<IntervalexprContext>(_ctx, getState());
  enterRule(_localctx, 6, FormulaParser::RuleIntervalexpr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(27);
    term();
    setState(28);
    match(FormulaParser::IN);
    setState(29);
    match(FormulaParser::INTERVAL);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FormulaContext ------------------------------------------------------------------

FormulaParser::FormulaContext::FormulaContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

FormulaParser::EquationContext* FormulaParser::FormulaContext::equation() {
  return getRuleContext<FormulaParser::EquationContext>(0);
}

FormulaParser::BoolexprContext* FormulaParser::FormulaContext::boolexpr() {
  return getRuleContext<FormulaParser::BoolexprContext>(0);
}

FormulaParser::IntervalexprContext* FormulaParser::FormulaContext::intervalexpr() {
  return getRuleContext<FormulaParser::IntervalexprContext>(0);
}


size_t FormulaParser::FormulaContext::getRuleIndex() const {
  return FormulaParser::RuleFormula;
}


FormulaParser::FormulaContext* FormulaParser::formula() {
  FormulaContext *_localctx = _tracker.createInstance<FormulaContext>(_ctx, getState());
  enterRule(_localctx, 8, FormulaParser::RuleFormula);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(34);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(31);
      equation();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(32);
      boolexpr();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(33);
      intervalexpr();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> FormulaParser::_decisionToDFA;
atn::PredictionContextCache FormulaParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN FormulaParser::_atn;
std::vector<uint16_t> FormulaParser::_serializedATN;

std::vector<std::string> FormulaParser::_ruleNames = {
  "term", "equation", "boolexpr", "intervalexpr", "formula"
};

std::vector<std::string> FormulaParser::_literalNames = {
  "", "'in'", "'='"
};

std::vector<std::string> FormulaParser::_symbolicNames = {
  "", "IN", "EQUALS", "BOOLRELATION", "BINOPERATOR", "VARIABLE", "NUMBER", 
  "INTERVAL", "WS"
};

dfa::Vocabulary FormulaParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> FormulaParser::_tokenNames;

FormulaParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0xa, 0x27, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x3, 0x2, 0x3, 0x2, 0x3, 
    0x2, 0x6, 0x2, 0x10, 0xa, 0x2, 0xd, 0x2, 0xe, 0x2, 0x11, 0x5, 0x2, 0x14, 
    0xa, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x4, 0x3, 0x4, 
    0x3, 0x4, 0x3, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 
    0x3, 0x6, 0x3, 0x6, 0x5, 0x6, 0x25, 0xa, 0x6, 0x3, 0x6, 0x2, 0x2, 0x7, 
    0x2, 0x4, 0x6, 0x8, 0xa, 0x2, 0x3, 0x3, 0x2, 0x7, 0x8, 0x2, 0x25, 0x2, 
    0xc, 0x3, 0x2, 0x2, 0x2, 0x4, 0x15, 0x3, 0x2, 0x2, 0x2, 0x6, 0x19, 0x3, 
    0x2, 0x2, 0x2, 0x8, 0x1d, 0x3, 0x2, 0x2, 0x2, 0xa, 0x24, 0x3, 0x2, 0x2, 
    0x2, 0xc, 0x13, 0x9, 0x2, 0x2, 0x2, 0xd, 0xe, 0x7, 0x6, 0x2, 0x2, 0xe, 
    0x10, 0x9, 0x2, 0x2, 0x2, 0xf, 0xd, 0x3, 0x2, 0x2, 0x2, 0x10, 0x11, 
    0x3, 0x2, 0x2, 0x2, 0x11, 0xf, 0x3, 0x2, 0x2, 0x2, 0x11, 0x12, 0x3, 
    0x2, 0x2, 0x2, 0x12, 0x14, 0x3, 0x2, 0x2, 0x2, 0x13, 0xf, 0x3, 0x2, 
    0x2, 0x2, 0x13, 0x14, 0x3, 0x2, 0x2, 0x2, 0x14, 0x3, 0x3, 0x2, 0x2, 
    0x2, 0x15, 0x16, 0x7, 0x7, 0x2, 0x2, 0x16, 0x17, 0x7, 0x4, 0x2, 0x2, 
    0x17, 0x18, 0x5, 0x2, 0x2, 0x2, 0x18, 0x5, 0x3, 0x2, 0x2, 0x2, 0x19, 
    0x1a, 0x5, 0x2, 0x2, 0x2, 0x1a, 0x1b, 0x7, 0x5, 0x2, 0x2, 0x1b, 0x1c, 
    0x7, 0x8, 0x2, 0x2, 0x1c, 0x7, 0x3, 0x2, 0x2, 0x2, 0x1d, 0x1e, 0x5, 
    0x2, 0x2, 0x2, 0x1e, 0x1f, 0x7, 0x3, 0x2, 0x2, 0x1f, 0x20, 0x7, 0x9, 
    0x2, 0x2, 0x20, 0x9, 0x3, 0x2, 0x2, 0x2, 0x21, 0x25, 0x5, 0x4, 0x3, 
    0x2, 0x22, 0x25, 0x5, 0x6, 0x4, 0x2, 0x23, 0x25, 0x5, 0x8, 0x5, 0x2, 
    0x24, 0x21, 0x3, 0x2, 0x2, 0x2, 0x24, 0x22, 0x3, 0x2, 0x2, 0x2, 0x24, 
    0x23, 0x3, 0x2, 0x2, 0x2, 0x25, 0xb, 0x3, 0x2, 0x2, 0x2, 0x5, 0x11, 
    0x13, 0x24, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

FormulaParser::Initializer FormulaParser::_init;
