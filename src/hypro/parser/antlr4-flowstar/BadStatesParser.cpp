
// Generated from BadStates.g4 by ANTLR 4.7



#include "BadStatesParser.h"


using namespace antlrcpp;
using namespace antlr4;

BadStatesParser::BadStatesParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

BadStatesParser::~BadStatesParser() {
  delete _interpreter;
}

std::string BadStatesParser::getGrammarFileName() const {
  return "BadStates.g4";
}

const std::vector<std::string>& BadStatesParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& BadStatesParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- UnsafesetContext ------------------------------------------------------------------

BadStatesParser::UnsafesetContext::UnsafesetContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<BadStatesParser::BadstateContext *> BadStatesParser::UnsafesetContext::badstate() {
  return getRuleContexts<BadStatesParser::BadstateContext>();
}

BadStatesParser::BadstateContext* BadStatesParser::UnsafesetContext::badstate(size_t i) {
  return getRuleContext<BadStatesParser::BadstateContext>(i);
}


size_t BadStatesParser::UnsafesetContext::getRuleIndex() const {
  return BadStatesParser::RuleUnsafeset;
}


BadStatesParser::UnsafesetContext* BadStatesParser::unsafeset() {
  UnsafesetContext *_localctx = _tracker.createInstance<UnsafesetContext>(_ctx, getState());
  enterRule(_localctx, 0, BadStatesParser::RuleUnsafeset);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(18);
    match(BadStatesParser::T__0);
    setState(19);
    match(BadStatesParser::T__1);
    setState(23);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == BadStatesParser::VARIABLE) {
      setState(20);
      badstate();
      setState(25);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(26);
    match(BadStatesParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BadstateContext ------------------------------------------------------------------

BadStatesParser::BadstateContext::BadstateContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BadStatesParser::BadstateContext::VARIABLE() {
  return getToken(BadStatesParser::VARIABLE, 0);
}

BadStatesParser::ConstrsetContext* BadStatesParser::BadstateContext::constrset() {
  return getRuleContext<BadStatesParser::ConstrsetContext>(0);
}


size_t BadStatesParser::BadstateContext::getRuleIndex() const {
  return BadStatesParser::RuleBadstate;
}


BadStatesParser::BadstateContext* BadStatesParser::badstate() {
  BadstateContext *_localctx = _tracker.createInstance<BadstateContext>(_ctx, getState());
  enterRule(_localctx, 2, BadStatesParser::RuleBadstate);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(28);
    match(BadStatesParser::VARIABLE);
    setState(29);
    match(BadStatesParser::T__1);
    setState(31);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      setState(30);
      constrset();
      break;
    }

    }
    setState(33);
    match(BadStatesParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TermContext ------------------------------------------------------------------

BadStatesParser::TermContext::TermContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> BadStatesParser::TermContext::NUMBER() {
  return getTokens(BadStatesParser::NUMBER);
}

tree::TerminalNode* BadStatesParser::TermContext::NUMBER(size_t i) {
  return getToken(BadStatesParser::NUMBER, i);
}

std::vector<tree::TerminalNode *> BadStatesParser::TermContext::VARIABLE() {
  return getTokens(BadStatesParser::VARIABLE);
}

tree::TerminalNode* BadStatesParser::TermContext::VARIABLE(size_t i) {
  return getToken(BadStatesParser::VARIABLE, i);
}

std::vector<tree::TerminalNode *> BadStatesParser::TermContext::TIMES() {
  return getTokens(BadStatesParser::TIMES);
}

tree::TerminalNode* BadStatesParser::TermContext::TIMES(size_t i) {
  return getToken(BadStatesParser::TIMES, i);
}


size_t BadStatesParser::TermContext::getRuleIndex() const {
  return BadStatesParser::RuleTerm;
}


BadStatesParser::TermContext* BadStatesParser::term() {
  TermContext *_localctx = _tracker.createInstance<TermContext>(_ctx, getState());
  enterRule(_localctx, 4, BadStatesParser::RuleTerm);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(35);
    _la = _input->LA(1);
    if (!(_la == BadStatesParser::NUMBER

    || _la == BadStatesParser::VARIABLE)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(40);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == BadStatesParser::TIMES) {
      setState(36);
      match(BadStatesParser::TIMES);
      setState(37);
      _la = _input->LA(1);
      if (!(_la == BadStatesParser::NUMBER

      || _la == BadStatesParser::VARIABLE)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(42);
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

BadStatesParser::PolynomContext::PolynomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<BadStatesParser::TermContext *> BadStatesParser::PolynomContext::term() {
  return getRuleContexts<BadStatesParser::TermContext>();
}

BadStatesParser::TermContext* BadStatesParser::PolynomContext::term(size_t i) {
  return getRuleContext<BadStatesParser::TermContext>(i);
}

std::vector<tree::TerminalNode *> BadStatesParser::PolynomContext::PLUS() {
  return getTokens(BadStatesParser::PLUS);
}

tree::TerminalNode* BadStatesParser::PolynomContext::PLUS(size_t i) {
  return getToken(BadStatesParser::PLUS, i);
}


size_t BadStatesParser::PolynomContext::getRuleIndex() const {
  return BadStatesParser::RulePolynom;
}


BadStatesParser::PolynomContext* BadStatesParser::polynom() {
  PolynomContext *_localctx = _tracker.createInstance<PolynomContext>(_ctx, getState());
  enterRule(_localctx, 6, BadStatesParser::RulePolynom);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(43);
    term();
    setState(48);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == BadStatesParser::PLUS) {
      setState(44);
      match(BadStatesParser::PLUS);
      setState(45);
      term();
      setState(50);
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

BadStatesParser::IntervalContext::IntervalContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> BadStatesParser::IntervalContext::NUMBER() {
  return getTokens(BadStatesParser::NUMBER);
}

tree::TerminalNode* BadStatesParser::IntervalContext::NUMBER(size_t i) {
  return getToken(BadStatesParser::NUMBER, i);
}


size_t BadStatesParser::IntervalContext::getRuleIndex() const {
  return BadStatesParser::RuleInterval;
}


BadStatesParser::IntervalContext* BadStatesParser::interval() {
  IntervalContext *_localctx = _tracker.createInstance<IntervalContext>(_ctx, getState());
  enterRule(_localctx, 8, BadStatesParser::RuleInterval);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(51);
    match(BadStatesParser::T__3);
    setState(52);
    match(BadStatesParser::NUMBER);
    setState(53);
    match(BadStatesParser::T__4);
    setState(54);
    match(BadStatesParser::NUMBER);
    setState(55);
    match(BadStatesParser::T__5);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EquationContext ------------------------------------------------------------------

BadStatesParser::EquationContext::EquationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BadStatesParser::EquationContext::VARIABLE() {
  return getToken(BadStatesParser::VARIABLE, 0);
}

tree::TerminalNode* BadStatesParser::EquationContext::EQUALS() {
  return getToken(BadStatesParser::EQUALS, 0);
}

BadStatesParser::PolynomContext* BadStatesParser::EquationContext::polynom() {
  return getRuleContext<BadStatesParser::PolynomContext>(0);
}


size_t BadStatesParser::EquationContext::getRuleIndex() const {
  return BadStatesParser::RuleEquation;
}


BadStatesParser::EquationContext* BadStatesParser::equation() {
  EquationContext *_localctx = _tracker.createInstance<EquationContext>(_ctx, getState());
  enterRule(_localctx, 10, BadStatesParser::RuleEquation);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(57);
    match(BadStatesParser::VARIABLE);
    setState(58);
    match(BadStatesParser::EQUALS);
    setState(59);
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

BadStatesParser::ConstraintContext::ConstraintContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<BadStatesParser::PolynomContext *> BadStatesParser::ConstraintContext::polynom() {
  return getRuleContexts<BadStatesParser::PolynomContext>();
}

BadStatesParser::PolynomContext* BadStatesParser::ConstraintContext::polynom(size_t i) {
  return getRuleContext<BadStatesParser::PolynomContext>(i);
}

tree::TerminalNode* BadStatesParser::ConstraintContext::BOOLRELATION() {
  return getToken(BadStatesParser::BOOLRELATION, 0);
}

tree::TerminalNode* BadStatesParser::ConstraintContext::EQUALS() {
  return getToken(BadStatesParser::EQUALS, 0);
}


size_t BadStatesParser::ConstraintContext::getRuleIndex() const {
  return BadStatesParser::RuleConstraint;
}


BadStatesParser::ConstraintContext* BadStatesParser::constraint() {
  ConstraintContext *_localctx = _tracker.createInstance<ConstraintContext>(_ctx, getState());
  enterRule(_localctx, 12, BadStatesParser::RuleConstraint);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(61);
    polynom();
    setState(62);
    _la = _input->LA(1);
    if (!(_la == BadStatesParser::EQUALS

    || _la == BadStatesParser::BOOLRELATION)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(63);
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

BadStatesParser::IntervalexprContext::IntervalexprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BadStatesParser::IntervalexprContext::VARIABLE() {
  return getToken(BadStatesParser::VARIABLE, 0);
}

tree::TerminalNode* BadStatesParser::IntervalexprContext::IN() {
  return getToken(BadStatesParser::IN, 0);
}

BadStatesParser::IntervalContext* BadStatesParser::IntervalexprContext::interval() {
  return getRuleContext<BadStatesParser::IntervalContext>(0);
}


size_t BadStatesParser::IntervalexprContext::getRuleIndex() const {
  return BadStatesParser::RuleIntervalexpr;
}


BadStatesParser::IntervalexprContext* BadStatesParser::intervalexpr() {
  IntervalexprContext *_localctx = _tracker.createInstance<IntervalexprContext>(_ctx, getState());
  enterRule(_localctx, 14, BadStatesParser::RuleIntervalexpr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(65);
    match(BadStatesParser::VARIABLE);
    setState(66);
    match(BadStatesParser::IN);
    setState(67);
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

BadStatesParser::ConstrsetContext::ConstrsetContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<BadStatesParser::ConstraintContext *> BadStatesParser::ConstrsetContext::constraint() {
  return getRuleContexts<BadStatesParser::ConstraintContext>();
}

BadStatesParser::ConstraintContext* BadStatesParser::ConstrsetContext::constraint(size_t i) {
  return getRuleContext<BadStatesParser::ConstraintContext>(i);
}

std::vector<BadStatesParser::IntervalexprContext *> BadStatesParser::ConstrsetContext::intervalexpr() {
  return getRuleContexts<BadStatesParser::IntervalexprContext>();
}

BadStatesParser::IntervalexprContext* BadStatesParser::ConstrsetContext::intervalexpr(size_t i) {
  return getRuleContext<BadStatesParser::IntervalexprContext>(i);
}


size_t BadStatesParser::ConstrsetContext::getRuleIndex() const {
  return BadStatesParser::RuleConstrset;
}


BadStatesParser::ConstrsetContext* BadStatesParser::constrset() {
  ConstrsetContext *_localctx = _tracker.createInstance<ConstrsetContext>(_ctx, getState());
  enterRule(_localctx, 16, BadStatesParser::RuleConstrset);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(73);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == BadStatesParser::NUMBER

    || _la == BadStatesParser::VARIABLE) {
      setState(71);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
      case 1: {
        setState(69);
        constraint();
        break;
      }

      case 2: {
        setState(70);
        intervalexpr();
        break;
      }

      }
      setState(75);
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
std::vector<dfa::DFA> BadStatesParser::_decisionToDFA;
atn::PredictionContextCache BadStatesParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN BadStatesParser::_atn;
std::vector<uint16_t> BadStatesParser::_serializedATN;

std::vector<std::string> BadStatesParser::_ruleNames = {
  "unsafeset", "badstate", "term", "polynom", "interval", "equation", "constraint", 
  "intervalexpr", "constrset"
};

std::vector<std::string> BadStatesParser::_literalNames = {
  "", "'unsafe set'", "'{'", "'}'", "'['", "','", "']'", "'in'", "", "'='", 
  "", "'+'", "'*'"
};

std::vector<std::string> BadStatesParser::_symbolicNames = {
  "", "", "", "", "", "", "", "IN", "COMMENT", "EQUALS", "BOOLRELATION", 
  "PLUS", "TIMES", "NUMBER", "VARIABLE", "WS"
};

dfa::Vocabulary BadStatesParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> BadStatesParser::_tokenNames;

BadStatesParser::Initializer::Initializer() {
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
    0x3, 0x11, 0x4f, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x3, 0x2, 0x3, 
    0x2, 0x3, 0x2, 0x7, 0x2, 0x18, 0xa, 0x2, 0xc, 0x2, 0xe, 0x2, 0x1b, 0xb, 
    0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x22, 
    0xa, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x7, 0x4, 
    0x29, 0xa, 0x4, 0xc, 0x4, 0xe, 0x4, 0x2c, 0xb, 0x4, 0x3, 0x5, 0x3, 0x5, 
    0x3, 0x5, 0x7, 0x5, 0x31, 0xa, 0x5, 0xc, 0x5, 0xe, 0x5, 0x34, 0xb, 0x5, 
    0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 
    0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0xa, 0x3, 0xa, 0x7, 0xa, 
    0x4a, 0xa, 0xa, 0xc, 0xa, 0xe, 0xa, 0x4d, 0xb, 0xa, 0x3, 0xa, 0x2, 0x2, 
    0xb, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x2, 0x4, 0x3, 0x2, 
    0xf, 0x10, 0x3, 0x2, 0xb, 0xc, 0x2, 0x4b, 0x2, 0x14, 0x3, 0x2, 0x2, 
    0x2, 0x4, 0x1e, 0x3, 0x2, 0x2, 0x2, 0x6, 0x25, 0x3, 0x2, 0x2, 0x2, 0x8, 
    0x2d, 0x3, 0x2, 0x2, 0x2, 0xa, 0x35, 0x3, 0x2, 0x2, 0x2, 0xc, 0x3b, 
    0x3, 0x2, 0x2, 0x2, 0xe, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x10, 0x43, 0x3, 
    0x2, 0x2, 0x2, 0x12, 0x4b, 0x3, 0x2, 0x2, 0x2, 0x14, 0x15, 0x7, 0x3, 
    0x2, 0x2, 0x15, 0x19, 0x7, 0x4, 0x2, 0x2, 0x16, 0x18, 0x5, 0x4, 0x3, 
    0x2, 0x17, 0x16, 0x3, 0x2, 0x2, 0x2, 0x18, 0x1b, 0x3, 0x2, 0x2, 0x2, 
    0x19, 0x17, 0x3, 0x2, 0x2, 0x2, 0x19, 0x1a, 0x3, 0x2, 0x2, 0x2, 0x1a, 
    0x1c, 0x3, 0x2, 0x2, 0x2, 0x1b, 0x19, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x1d, 
    0x7, 0x5, 0x2, 0x2, 0x1d, 0x3, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x1f, 0x7, 
    0x10, 0x2, 0x2, 0x1f, 0x21, 0x7, 0x4, 0x2, 0x2, 0x20, 0x22, 0x5, 0x12, 
    0xa, 0x2, 0x21, 0x20, 0x3, 0x2, 0x2, 0x2, 0x21, 0x22, 0x3, 0x2, 0x2, 
    0x2, 0x22, 0x23, 0x3, 0x2, 0x2, 0x2, 0x23, 0x24, 0x7, 0x5, 0x2, 0x2, 
    0x24, 0x5, 0x3, 0x2, 0x2, 0x2, 0x25, 0x2a, 0x9, 0x2, 0x2, 0x2, 0x26, 
    0x27, 0x7, 0xe, 0x2, 0x2, 0x27, 0x29, 0x9, 0x2, 0x2, 0x2, 0x28, 0x26, 
    0x3, 0x2, 0x2, 0x2, 0x29, 0x2c, 0x3, 0x2, 0x2, 0x2, 0x2a, 0x28, 0x3, 
    0x2, 0x2, 0x2, 0x2a, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x2b, 0x7, 0x3, 0x2, 
    0x2, 0x2, 0x2c, 0x2a, 0x3, 0x2, 0x2, 0x2, 0x2d, 0x32, 0x5, 0x6, 0x4, 
    0x2, 0x2e, 0x2f, 0x7, 0xd, 0x2, 0x2, 0x2f, 0x31, 0x5, 0x6, 0x4, 0x2, 
    0x30, 0x2e, 0x3, 0x2, 0x2, 0x2, 0x31, 0x34, 0x3, 0x2, 0x2, 0x2, 0x32, 
    0x30, 0x3, 0x2, 0x2, 0x2, 0x32, 0x33, 0x3, 0x2, 0x2, 0x2, 0x33, 0x9, 
    0x3, 0x2, 0x2, 0x2, 0x34, 0x32, 0x3, 0x2, 0x2, 0x2, 0x35, 0x36, 0x7, 
    0x6, 0x2, 0x2, 0x36, 0x37, 0x7, 0xf, 0x2, 0x2, 0x37, 0x38, 0x7, 0x7, 
    0x2, 0x2, 0x38, 0x39, 0x7, 0xf, 0x2, 0x2, 0x39, 0x3a, 0x7, 0x8, 0x2, 
    0x2, 0x3a, 0xb, 0x3, 0x2, 0x2, 0x2, 0x3b, 0x3c, 0x7, 0x10, 0x2, 0x2, 
    0x3c, 0x3d, 0x7, 0xb, 0x2, 0x2, 0x3d, 0x3e, 0x5, 0x8, 0x5, 0x2, 0x3e, 
    0xd, 0x3, 0x2, 0x2, 0x2, 0x3f, 0x40, 0x5, 0x8, 0x5, 0x2, 0x40, 0x41, 
    0x9, 0x3, 0x2, 0x2, 0x41, 0x42, 0x5, 0x8, 0x5, 0x2, 0x42, 0xf, 0x3, 
    0x2, 0x2, 0x2, 0x43, 0x44, 0x7, 0x10, 0x2, 0x2, 0x44, 0x45, 0x7, 0x9, 
    0x2, 0x2, 0x45, 0x46, 0x5, 0xa, 0x6, 0x2, 0x46, 0x11, 0x3, 0x2, 0x2, 
    0x2, 0x47, 0x4a, 0x5, 0xe, 0x8, 0x2, 0x48, 0x4a, 0x5, 0x10, 0x9, 0x2, 
    0x49, 0x47, 0x3, 0x2, 0x2, 0x2, 0x49, 0x48, 0x3, 0x2, 0x2, 0x2, 0x4a, 
    0x4d, 0x3, 0x2, 0x2, 0x2, 0x4b, 0x49, 0x3, 0x2, 0x2, 0x2, 0x4b, 0x4c, 
    0x3, 0x2, 0x2, 0x2, 0x4c, 0x13, 0x3, 0x2, 0x2, 0x2, 0x4d, 0x4b, 0x3, 
    0x2, 0x2, 0x2, 0x8, 0x19, 0x21, 0x2a, 0x32, 0x49, 0x4b, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

BadStatesParser::Initializer BadStatesParser::_init;
