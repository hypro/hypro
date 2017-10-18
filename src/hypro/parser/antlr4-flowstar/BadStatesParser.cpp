
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
    setState(20);
    match(BadStatesParser::T__0);
    setState(21);
    match(BadStatesParser::T__1);
    setState(25);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == BadStatesParser::VARIABLE) {
      setState(22);
      badstate();
      setState(27);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(28);
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
    setState(30);
    match(BadStatesParser::VARIABLE);
    setState(31);
    match(BadStatesParser::T__1);
    setState(33);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      setState(32);
      constrset();
      break;
    }

    }
    setState(35);
    match(BadStatesParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConnectorContext ------------------------------------------------------------------

BadStatesParser::ConnectorContext::ConnectorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BadStatesParser::ConnectorContext::PLUS() {
  return getToken(BadStatesParser::PLUS, 0);
}

tree::TerminalNode* BadStatesParser::ConnectorContext::MINUS() {
  return getToken(BadStatesParser::MINUS, 0);
}


size_t BadStatesParser::ConnectorContext::getRuleIndex() const {
  return BadStatesParser::RuleConnector;
}


BadStatesParser::ConnectorContext* BadStatesParser::connector() {
  ConnectorContext *_localctx = _tracker.createInstance<ConnectorContext>(_ctx, getState());
  enterRule(_localctx, 4, BadStatesParser::RuleConnector);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(37);
    _la = _input->LA(1);
    if (!(_la == BadStatesParser::PLUS

    || _la == BadStatesParser::MINUS)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
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

std::vector<BadStatesParser::ConnectorContext *> BadStatesParser::TermContext::connector() {
  return getRuleContexts<BadStatesParser::ConnectorContext>();
}

BadStatesParser::ConnectorContext* BadStatesParser::TermContext::connector(size_t i) {
  return getRuleContext<BadStatesParser::ConnectorContext>(i);
}


size_t BadStatesParser::TermContext::getRuleIndex() const {
  return BadStatesParser::RuleTerm;
}


BadStatesParser::TermContext* BadStatesParser::term() {
  TermContext *_localctx = _tracker.createInstance<TermContext>(_ctx, getState());
  enterRule(_localctx, 6, BadStatesParser::RuleTerm);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(39);
    _la = _input->LA(1);
    if (!(_la == BadStatesParser::NUMBER

    || _la == BadStatesParser::VARIABLE)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(50);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == BadStatesParser::TIMES) {
      setState(40);
      match(BadStatesParser::TIMES);
      setState(44);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == BadStatesParser::PLUS

      || _la == BadStatesParser::MINUS) {
        setState(41);
        connector();
        setState(46);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(47);
      _la = _input->LA(1);
      if (!(_la == BadStatesParser::NUMBER

      || _la == BadStatesParser::VARIABLE)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(52);
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

std::vector<BadStatesParser::ConnectorContext *> BadStatesParser::PolynomContext::connector() {
  return getRuleContexts<BadStatesParser::ConnectorContext>();
}

BadStatesParser::ConnectorContext* BadStatesParser::PolynomContext::connector(size_t i) {
  return getRuleContext<BadStatesParser::ConnectorContext>(i);
}


size_t BadStatesParser::PolynomContext::getRuleIndex() const {
  return BadStatesParser::RulePolynom;
}


BadStatesParser::PolynomContext* BadStatesParser::polynom() {
  PolynomContext *_localctx = _tracker.createInstance<PolynomContext>(_ctx, getState());
  enterRule(_localctx, 8, BadStatesParser::RulePolynom);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(56);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == BadStatesParser::PLUS

    || _la == BadStatesParser::MINUS) {
      setState(53);
      connector();
      setState(58);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(59);
    term();
    setState(69);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(61); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(60);
          connector();
          setState(63); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == BadStatesParser::PLUS

        || _la == BadStatesParser::MINUS);
        setState(65);
        term(); 
      }
      setState(71);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
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
  enterRule(_localctx, 10, BadStatesParser::RuleInterval);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(72);
    match(BadStatesParser::T__3);
    setState(73);
    match(BadStatesParser::NUMBER);
    setState(74);
    match(BadStatesParser::T__4);
    setState(75);
    match(BadStatesParser::NUMBER);
    setState(76);
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
  enterRule(_localctx, 12, BadStatesParser::RuleEquation);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(78);
    match(BadStatesParser::VARIABLE);
    setState(79);
    match(BadStatesParser::EQUALS);
    setState(80);
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
  enterRule(_localctx, 14, BadStatesParser::RuleConstraint);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(82);
    polynom();
    setState(83);
    _la = _input->LA(1);
    if (!(_la == BadStatesParser::EQUALS

    || _la == BadStatesParser::BOOLRELATION)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(84);
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
  enterRule(_localctx, 16, BadStatesParser::RuleIntervalexpr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(86);
    match(BadStatesParser::VARIABLE);
    setState(87);
    match(BadStatesParser::IN);
    setState(88);
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
  enterRule(_localctx, 18, BadStatesParser::RuleConstrset);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(94);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << BadStatesParser::PLUS)
      | (1ULL << BadStatesParser::MINUS)
      | (1ULL << BadStatesParser::NUMBER)
      | (1ULL << BadStatesParser::VARIABLE))) != 0)) {
      setState(92);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
      case 1: {
        setState(90);
        constraint();
        break;
      }

      case 2: {
        setState(91);
        intervalexpr();
        break;
      }

      }
      setState(96);
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
  "unsafeset", "badstate", "connector", "term", "polynom", "interval", "equation", 
  "constraint", "intervalexpr", "constrset"
};

std::vector<std::string> BadStatesParser::_literalNames = {
  "", "'unsafe set'", "'{'", "'}'", "'['", "','", "']'", "'in'", "", "'='", 
  "", "'+'", "'-'", "'*'"
};

std::vector<std::string> BadStatesParser::_symbolicNames = {
  "", "", "", "", "", "", "", "IN", "COMMENT", "EQUALS", "BOOLRELATION", 
  "PLUS", "MINUS", "TIMES", "NUMBER", "VARIABLE", "WS"
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
    0x3, 0x12, 0x64, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x7, 0x2, 0x1a, 0xa, 0x2, 0xc, 0x2, 
    0xe, 0x2, 0x1d, 0xb, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x5, 0x3, 0x24, 0xa, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x4, 0x3, 0x4, 
    0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x7, 0x5, 0x2d, 0xa, 0x5, 0xc, 0x5, 0xe, 
    0x5, 0x30, 0xb, 0x5, 0x3, 0x5, 0x7, 0x5, 0x33, 0xa, 0x5, 0xc, 0x5, 0xe, 
    0x5, 0x36, 0xb, 0x5, 0x3, 0x6, 0x7, 0x6, 0x39, 0xa, 0x6, 0xc, 0x6, 0xe, 
    0x6, 0x3c, 0xb, 0x6, 0x3, 0x6, 0x3, 0x6, 0x6, 0x6, 0x40, 0xa, 0x6, 0xd, 
    0x6, 0xe, 0x6, 0x41, 0x3, 0x6, 0x3, 0x6, 0x7, 0x6, 0x46, 0xa, 0x6, 0xc, 
    0x6, 0xe, 0x6, 0x49, 0xb, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x9, 
    0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 
    0x3, 0xb, 0x3, 0xb, 0x7, 0xb, 0x5f, 0xa, 0xb, 0xc, 0xb, 0xe, 0xb, 0x62, 
    0xb, 0xb, 0x3, 0xb, 0x2, 0x2, 0xc, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 
    0x10, 0x12, 0x14, 0x2, 0x5, 0x3, 0x2, 0xd, 0xe, 0x3, 0x2, 0x10, 0x11, 
    0x3, 0x2, 0xb, 0xc, 0x2, 0x62, 0x2, 0x16, 0x3, 0x2, 0x2, 0x2, 0x4, 0x20, 
    0x3, 0x2, 0x2, 0x2, 0x6, 0x27, 0x3, 0x2, 0x2, 0x2, 0x8, 0x29, 0x3, 0x2, 
    0x2, 0x2, 0xa, 0x3a, 0x3, 0x2, 0x2, 0x2, 0xc, 0x4a, 0x3, 0x2, 0x2, 0x2, 
    0xe, 0x50, 0x3, 0x2, 0x2, 0x2, 0x10, 0x54, 0x3, 0x2, 0x2, 0x2, 0x12, 
    0x58, 0x3, 0x2, 0x2, 0x2, 0x14, 0x60, 0x3, 0x2, 0x2, 0x2, 0x16, 0x17, 
    0x7, 0x3, 0x2, 0x2, 0x17, 0x1b, 0x7, 0x4, 0x2, 0x2, 0x18, 0x1a, 0x5, 
    0x4, 0x3, 0x2, 0x19, 0x18, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x1d, 0x3, 0x2, 
    0x2, 0x2, 0x1b, 0x19, 0x3, 0x2, 0x2, 0x2, 0x1b, 0x1c, 0x3, 0x2, 0x2, 
    0x2, 0x1c, 0x1e, 0x3, 0x2, 0x2, 0x2, 0x1d, 0x1b, 0x3, 0x2, 0x2, 0x2, 
    0x1e, 0x1f, 0x7, 0x5, 0x2, 0x2, 0x1f, 0x3, 0x3, 0x2, 0x2, 0x2, 0x20, 
    0x21, 0x7, 0x11, 0x2, 0x2, 0x21, 0x23, 0x7, 0x4, 0x2, 0x2, 0x22, 0x24, 
    0x5, 0x14, 0xb, 0x2, 0x23, 0x22, 0x3, 0x2, 0x2, 0x2, 0x23, 0x24, 0x3, 
    0x2, 0x2, 0x2, 0x24, 0x25, 0x3, 0x2, 0x2, 0x2, 0x25, 0x26, 0x7, 0x5, 
    0x2, 0x2, 0x26, 0x5, 0x3, 0x2, 0x2, 0x2, 0x27, 0x28, 0x9, 0x2, 0x2, 
    0x2, 0x28, 0x7, 0x3, 0x2, 0x2, 0x2, 0x29, 0x34, 0x9, 0x3, 0x2, 0x2, 
    0x2a, 0x2e, 0x7, 0xf, 0x2, 0x2, 0x2b, 0x2d, 0x5, 0x6, 0x4, 0x2, 0x2c, 
    0x2b, 0x3, 0x2, 0x2, 0x2, 0x2d, 0x30, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x2c, 
    0x3, 0x2, 0x2, 0x2, 0x2e, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x2f, 0x31, 0x3, 
    0x2, 0x2, 0x2, 0x30, 0x2e, 0x3, 0x2, 0x2, 0x2, 0x31, 0x33, 0x9, 0x3, 
    0x2, 0x2, 0x32, 0x2a, 0x3, 0x2, 0x2, 0x2, 0x33, 0x36, 0x3, 0x2, 0x2, 
    0x2, 0x34, 0x32, 0x3, 0x2, 0x2, 0x2, 0x34, 0x35, 0x3, 0x2, 0x2, 0x2, 
    0x35, 0x9, 0x3, 0x2, 0x2, 0x2, 0x36, 0x34, 0x3, 0x2, 0x2, 0x2, 0x37, 
    0x39, 0x5, 0x6, 0x4, 0x2, 0x38, 0x37, 0x3, 0x2, 0x2, 0x2, 0x39, 0x3c, 
    0x3, 0x2, 0x2, 0x2, 0x3a, 0x38, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x3b, 0x3, 
    0x2, 0x2, 0x2, 0x3b, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x3a, 0x3, 0x2, 
    0x2, 0x2, 0x3d, 0x47, 0x5, 0x8, 0x5, 0x2, 0x3e, 0x40, 0x5, 0x6, 0x4, 
    0x2, 0x3f, 0x3e, 0x3, 0x2, 0x2, 0x2, 0x40, 0x41, 0x3, 0x2, 0x2, 0x2, 
    0x41, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x41, 0x42, 0x3, 0x2, 0x2, 0x2, 0x42, 
    0x43, 0x3, 0x2, 0x2, 0x2, 0x43, 0x44, 0x5, 0x8, 0x5, 0x2, 0x44, 0x46, 
    0x3, 0x2, 0x2, 0x2, 0x45, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x46, 0x49, 0x3, 
    0x2, 0x2, 0x2, 0x47, 0x45, 0x3, 0x2, 0x2, 0x2, 0x47, 0x48, 0x3, 0x2, 
    0x2, 0x2, 0x48, 0xb, 0x3, 0x2, 0x2, 0x2, 0x49, 0x47, 0x3, 0x2, 0x2, 
    0x2, 0x4a, 0x4b, 0x7, 0x6, 0x2, 0x2, 0x4b, 0x4c, 0x7, 0x10, 0x2, 0x2, 
    0x4c, 0x4d, 0x7, 0x7, 0x2, 0x2, 0x4d, 0x4e, 0x7, 0x10, 0x2, 0x2, 0x4e, 
    0x4f, 0x7, 0x8, 0x2, 0x2, 0x4f, 0xd, 0x3, 0x2, 0x2, 0x2, 0x50, 0x51, 
    0x7, 0x11, 0x2, 0x2, 0x51, 0x52, 0x7, 0xb, 0x2, 0x2, 0x52, 0x53, 0x5, 
    0xa, 0x6, 0x2, 0x53, 0xf, 0x3, 0x2, 0x2, 0x2, 0x54, 0x55, 0x5, 0xa, 
    0x6, 0x2, 0x55, 0x56, 0x9, 0x4, 0x2, 0x2, 0x56, 0x57, 0x5, 0xa, 0x6, 
    0x2, 0x57, 0x11, 0x3, 0x2, 0x2, 0x2, 0x58, 0x59, 0x7, 0x11, 0x2, 0x2, 
    0x59, 0x5a, 0x7, 0x9, 0x2, 0x2, 0x5a, 0x5b, 0x5, 0xc, 0x7, 0x2, 0x5b, 
    0x13, 0x3, 0x2, 0x2, 0x2, 0x5c, 0x5f, 0x5, 0x10, 0x9, 0x2, 0x5d, 0x5f, 
    0x5, 0x12, 0xa, 0x2, 0x5e, 0x5c, 0x3, 0x2, 0x2, 0x2, 0x5e, 0x5d, 0x3, 
    0x2, 0x2, 0x2, 0x5f, 0x62, 0x3, 0x2, 0x2, 0x2, 0x60, 0x5e, 0x3, 0x2, 
    0x2, 0x2, 0x60, 0x61, 0x3, 0x2, 0x2, 0x2, 0x61, 0x15, 0x3, 0x2, 0x2, 
    0x2, 0x62, 0x60, 0x3, 0x2, 0x2, 0x2, 0xb, 0x1b, 0x23, 0x2e, 0x34, 0x3a, 
    0x41, 0x47, 0x5e, 0x60, 
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
