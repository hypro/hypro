
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

std::vector<tree::TerminalNode *> FormulaParser::TermContext::TIMES() {
  return getTokens(FormulaParser::TIMES);
}

tree::TerminalNode* FormulaParser::TermContext::TIMES(size_t i) {
  return getToken(FormulaParser::TIMES, i);
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
    setState(14);
    _la = _input->LA(1);
    if (!(_la == FormulaParser::NUMBER

    || _la == FormulaParser::VARIABLE)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(19);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == FormulaParser::TIMES) {
      setState(15);
      match(FormulaParser::TIMES);
      setState(16);
      _la = _input->LA(1);
      if (!(_la == FormulaParser::NUMBER

      || _la == FormulaParser::VARIABLE)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(21);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PolynomContext ------------------------------------------------------------------

FormulaParser::PolynomContext::PolynomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<FormulaParser::TermContext *> FormulaParser::PolynomContext::term() {
  return getRuleContexts<FormulaParser::TermContext>();
}

FormulaParser::TermContext* FormulaParser::PolynomContext::term(size_t i) {
  return getRuleContext<FormulaParser::TermContext>(i);
}

std::vector<tree::TerminalNode *> FormulaParser::PolynomContext::PLUS() {
  return getTokens(FormulaParser::PLUS);
}

tree::TerminalNode* FormulaParser::PolynomContext::PLUS(size_t i) {
  return getToken(FormulaParser::PLUS, i);
}


size_t FormulaParser::PolynomContext::getRuleIndex() const {
  return FormulaParser::RulePolynom;
}


FormulaParser::PolynomContext* FormulaParser::polynom() {
  PolynomContext *_localctx = _tracker.createInstance<PolynomContext>(_ctx, getState());
  enterRule(_localctx, 2, FormulaParser::RulePolynom);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(22);
    term();
    setState(27);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == FormulaParser::PLUS) {
      setState(23);
      match(FormulaParser::PLUS);
      setState(24);
      term();
      setState(29);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IntervalContext ------------------------------------------------------------------

FormulaParser::IntervalContext::IntervalContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> FormulaParser::IntervalContext::NUMBER() {
  return getTokens(FormulaParser::NUMBER);
}

tree::TerminalNode* FormulaParser::IntervalContext::NUMBER(size_t i) {
  return getToken(FormulaParser::NUMBER, i);
}


size_t FormulaParser::IntervalContext::getRuleIndex() const {
  return FormulaParser::RuleInterval;
}


FormulaParser::IntervalContext* FormulaParser::interval() {
  IntervalContext *_localctx = _tracker.createInstance<IntervalContext>(_ctx, getState());
  enterRule(_localctx, 4, FormulaParser::RuleInterval);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(30);
    match(FormulaParser::T__0);
    setState(31);
    match(FormulaParser::NUMBER);
    setState(32);
    match(FormulaParser::T__1);
    setState(33);
    match(FormulaParser::NUMBER);
    setState(34);
    match(FormulaParser::T__2);
   
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

FormulaParser::PolynomContext* FormulaParser::EquationContext::polynom() {
  return getRuleContext<FormulaParser::PolynomContext>(0);
}


size_t FormulaParser::EquationContext::getRuleIndex() const {
  return FormulaParser::RuleEquation;
}


FormulaParser::EquationContext* FormulaParser::equation() {
  EquationContext *_localctx = _tracker.createInstance<EquationContext>(_ctx, getState());
  enterRule(_localctx, 6, FormulaParser::RuleEquation);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(36);
    match(FormulaParser::VARIABLE);
    setState(37);
    match(FormulaParser::EQUALS);
    setState(38);
    polynom();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstraintContext ------------------------------------------------------------------

FormulaParser::ConstraintContext::ConstraintContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<FormulaParser::PolynomContext *> FormulaParser::ConstraintContext::polynom() {
  return getRuleContexts<FormulaParser::PolynomContext>();
}

FormulaParser::PolynomContext* FormulaParser::ConstraintContext::polynom(size_t i) {
  return getRuleContext<FormulaParser::PolynomContext>(i);
}

tree::TerminalNode* FormulaParser::ConstraintContext::BOOLRELATION() {
  return getToken(FormulaParser::BOOLRELATION, 0);
}

tree::TerminalNode* FormulaParser::ConstraintContext::EQUALS() {
  return getToken(FormulaParser::EQUALS, 0);
}


size_t FormulaParser::ConstraintContext::getRuleIndex() const {
  return FormulaParser::RuleConstraint;
}


FormulaParser::ConstraintContext* FormulaParser::constraint() {
  ConstraintContext *_localctx = _tracker.createInstance<ConstraintContext>(_ctx, getState());
  enterRule(_localctx, 8, FormulaParser::RuleConstraint);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(40);
    polynom();
    setState(41);
    _la = _input->LA(1);
    if (!(_la == FormulaParser::EQUALS

    || _la == FormulaParser::BOOLRELATION)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(42);
    polynom();
   
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

tree::TerminalNode* FormulaParser::IntervalexprContext::VARIABLE() {
  return getToken(FormulaParser::VARIABLE, 0);
}

tree::TerminalNode* FormulaParser::IntervalexprContext::IN() {
  return getToken(FormulaParser::IN, 0);
}

FormulaParser::IntervalContext* FormulaParser::IntervalexprContext::interval() {
  return getRuleContext<FormulaParser::IntervalContext>(0);
}


size_t FormulaParser::IntervalexprContext::getRuleIndex() const {
  return FormulaParser::RuleIntervalexpr;
}


FormulaParser::IntervalexprContext* FormulaParser::intervalexpr() {
  IntervalexprContext *_localctx = _tracker.createInstance<IntervalexprContext>(_ctx, getState());
  enterRule(_localctx, 10, FormulaParser::RuleIntervalexpr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(44);
    match(FormulaParser::VARIABLE);
    setState(45);
    match(FormulaParser::IN);
    setState(46);
    interval();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstrsetContext ------------------------------------------------------------------

FormulaParser::ConstrsetContext::ConstrsetContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<FormulaParser::ConstraintContext *> FormulaParser::ConstrsetContext::constraint() {
  return getRuleContexts<FormulaParser::ConstraintContext>();
}

FormulaParser::ConstraintContext* FormulaParser::ConstrsetContext::constraint(size_t i) {
  return getRuleContext<FormulaParser::ConstraintContext>(i);
}

std::vector<FormulaParser::IntervalexprContext *> FormulaParser::ConstrsetContext::intervalexpr() {
  return getRuleContexts<FormulaParser::IntervalexprContext>();
}

FormulaParser::IntervalexprContext* FormulaParser::ConstrsetContext::intervalexpr(size_t i) {
  return getRuleContext<FormulaParser::IntervalexprContext>(i);
}


size_t FormulaParser::ConstrsetContext::getRuleIndex() const {
  return FormulaParser::RuleConstrset;
}


FormulaParser::ConstrsetContext* FormulaParser::constrset() {
  ConstrsetContext *_localctx = _tracker.createInstance<ConstrsetContext>(_ctx, getState());
  enterRule(_localctx, 12, FormulaParser::RuleConstrset);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(52);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == FormulaParser::NUMBER

    || _la == FormulaParser::VARIABLE) {
      setState(50);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
      case 1: {
        setState(48);
        constraint();
        break;
      }

      case 2: {
        setState(49);
        intervalexpr();
        break;
      }

      }
      setState(54);
      _errHandler->sync(this);
      _la = _input->LA(1);
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
  "term", "polynom", "interval", "equation", "constraint", "intervalexpr", 
  "constrset"
};

std::vector<std::string> FormulaParser::_literalNames = {
  "", "'['", "','", "']'", "'in'", "", "'='", "", "'+'", "'*'"
};

std::vector<std::string> FormulaParser::_symbolicNames = {
  "", "", "", "", "IN", "COMMENT", "EQUALS", "BOOLRELATION", "PLUS", "TIMES", 
  "NUMBER", "VARIABLE", "WS"
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
    0x3, 0xe, 0x3a, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x7, 0x2, 0x14, 0xa, 0x2, 
    0xc, 0x2, 0xe, 0x2, 0x17, 0xb, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x7, 
    0x3, 0x1c, 0xa, 0x3, 0xc, 0x3, 0xe, 0x3, 0x1f, 0xb, 0x3, 0x3, 0x4, 0x3, 
    0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 
    0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 0x3, 
    0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 0x8, 0x7, 0x8, 0x35, 0xa, 0x8, 
    0xc, 0x8, 0xe, 0x8, 0x38, 0xb, 0x8, 0x3, 0x8, 0x2, 0x2, 0x9, 0x2, 0x4, 
    0x6, 0x8, 0xa, 0xc, 0xe, 0x2, 0x4, 0x3, 0x2, 0xc, 0xd, 0x3, 0x2, 0x8, 
    0x9, 0x2, 0x36, 0x2, 0x10, 0x3, 0x2, 0x2, 0x2, 0x4, 0x18, 0x3, 0x2, 
    0x2, 0x2, 0x6, 0x20, 0x3, 0x2, 0x2, 0x2, 0x8, 0x26, 0x3, 0x2, 0x2, 0x2, 
    0xa, 0x2a, 0x3, 0x2, 0x2, 0x2, 0xc, 0x2e, 0x3, 0x2, 0x2, 0x2, 0xe, 0x36, 
    0x3, 0x2, 0x2, 0x2, 0x10, 0x15, 0x9, 0x2, 0x2, 0x2, 0x11, 0x12, 0x7, 
    0xb, 0x2, 0x2, 0x12, 0x14, 0x9, 0x2, 0x2, 0x2, 0x13, 0x11, 0x3, 0x2, 
    0x2, 0x2, 0x14, 0x17, 0x3, 0x2, 0x2, 0x2, 0x15, 0x13, 0x3, 0x2, 0x2, 
    0x2, 0x15, 0x16, 0x3, 0x2, 0x2, 0x2, 0x16, 0x3, 0x3, 0x2, 0x2, 0x2, 
    0x17, 0x15, 0x3, 0x2, 0x2, 0x2, 0x18, 0x1d, 0x5, 0x2, 0x2, 0x2, 0x19, 
    0x1a, 0x7, 0xa, 0x2, 0x2, 0x1a, 0x1c, 0x5, 0x2, 0x2, 0x2, 0x1b, 0x19, 
    0x3, 0x2, 0x2, 0x2, 0x1c, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x1d, 0x1b, 0x3, 
    0x2, 0x2, 0x2, 0x1d, 0x1e, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x5, 0x3, 0x2, 
    0x2, 0x2, 0x1f, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x20, 0x21, 0x7, 0x3, 0x2, 
    0x2, 0x21, 0x22, 0x7, 0xc, 0x2, 0x2, 0x22, 0x23, 0x7, 0x4, 0x2, 0x2, 
    0x23, 0x24, 0x7, 0xc, 0x2, 0x2, 0x24, 0x25, 0x7, 0x5, 0x2, 0x2, 0x25, 
    0x7, 0x3, 0x2, 0x2, 0x2, 0x26, 0x27, 0x7, 0xd, 0x2, 0x2, 0x27, 0x28, 
    0x7, 0x8, 0x2, 0x2, 0x28, 0x29, 0x5, 0x4, 0x3, 0x2, 0x29, 0x9, 0x3, 
    0x2, 0x2, 0x2, 0x2a, 0x2b, 0x5, 0x4, 0x3, 0x2, 0x2b, 0x2c, 0x9, 0x3, 
    0x2, 0x2, 0x2c, 0x2d, 0x5, 0x4, 0x3, 0x2, 0x2d, 0xb, 0x3, 0x2, 0x2, 
    0x2, 0x2e, 0x2f, 0x7, 0xd, 0x2, 0x2, 0x2f, 0x30, 0x7, 0x6, 0x2, 0x2, 
    0x30, 0x31, 0x5, 0x6, 0x4, 0x2, 0x31, 0xd, 0x3, 0x2, 0x2, 0x2, 0x32, 
    0x35, 0x5, 0xa, 0x6, 0x2, 0x33, 0x35, 0x5, 0xc, 0x7, 0x2, 0x34, 0x32, 
    0x3, 0x2, 0x2, 0x2, 0x34, 0x33, 0x3, 0x2, 0x2, 0x2, 0x35, 0x38, 0x3, 
    0x2, 0x2, 0x2, 0x36, 0x34, 0x3, 0x2, 0x2, 0x2, 0x36, 0x37, 0x3, 0x2, 
    0x2, 0x2, 0x37, 0xf, 0x3, 0x2, 0x2, 0x2, 0x38, 0x36, 0x3, 0x2, 0x2, 
    0x2, 0x6, 0x15, 0x1d, 0x34, 0x36, 
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
