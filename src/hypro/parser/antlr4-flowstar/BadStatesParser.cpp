
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

std::vector<BadStatesParser::GbadstateContext *> BadStatesParser::UnsafesetContext::gbadstate() {
  return getRuleContexts<BadStatesParser::GbadstateContext>();
}

BadStatesParser::GbadstateContext* BadStatesParser::UnsafesetContext::gbadstate(size_t i) {
  return getRuleContext<BadStatesParser::GbadstateContext>(i);
}

std::vector<BadStatesParser::LbadstateContext *> BadStatesParser::UnsafesetContext::lbadstate() {
  return getRuleContexts<BadStatesParser::LbadstateContext>();
}

BadStatesParser::LbadstateContext* BadStatesParser::UnsafesetContext::lbadstate(size_t i) {
  return getRuleContext<BadStatesParser::LbadstateContext>(i);
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
    setState(22);
    match(BadStatesParser::T__0);
    setState(23);
    match(BadStatesParser::T__1);
    setState(28);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << BadStatesParser::PLUS)
      | (1ULL << BadStatesParser::MINUS)
      | (1ULL << BadStatesParser::NUMBER)
      | (1ULL << BadStatesParser::VARIABLE))) != 0)) {
      setState(26);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
      case 1: {
        setState(24);
        gbadstate();
        break;
      }

      case 2: {
        setState(25);
        lbadstate();
        break;
      }

      }
      setState(30);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(31);
    match(BadStatesParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LbadstateContext ------------------------------------------------------------------

BadStatesParser::LbadstateContext::LbadstateContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BadStatesParser::LbadstateContext::VARIABLE() {
  return getToken(BadStatesParser::VARIABLE, 0);
}

BadStatesParser::ConstrsetContext* BadStatesParser::LbadstateContext::constrset() {
  return getRuleContext<BadStatesParser::ConstrsetContext>(0);
}


size_t BadStatesParser::LbadstateContext::getRuleIndex() const {
  return BadStatesParser::RuleLbadstate;
}


BadStatesParser::LbadstateContext* BadStatesParser::lbadstate() {
  LbadstateContext *_localctx = _tracker.createInstance<LbadstateContext>(_ctx, getState());
  enterRule(_localctx, 2, BadStatesParser::RuleLbadstate);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(33);
    match(BadStatesParser::VARIABLE);
    setState(34);
    match(BadStatesParser::T__1);
    setState(36);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << BadStatesParser::PLUS)
      | (1ULL << BadStatesParser::MINUS)
      | (1ULL << BadStatesParser::NUMBER)
      | (1ULL << BadStatesParser::VARIABLE))) != 0)) {
      setState(35);
      constrset();
    }
    setState(38);
    match(BadStatesParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GbadstateContext ------------------------------------------------------------------

BadStatesParser::GbadstateContext::GbadstateContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

BadStatesParser::ConstrsetContext* BadStatesParser::GbadstateContext::constrset() {
  return getRuleContext<BadStatesParser::ConstrsetContext>(0);
}


size_t BadStatesParser::GbadstateContext::getRuleIndex() const {
  return BadStatesParser::RuleGbadstate;
}


BadStatesParser::GbadstateContext* BadStatesParser::gbadstate() {
  GbadstateContext *_localctx = _tracker.createInstance<GbadstateContext>(_ctx, getState());
  enterRule(_localctx, 4, BadStatesParser::RuleGbadstate);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(40);
    constrset();
   
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
  enterRule(_localctx, 6, BadStatesParser::RuleConnector);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(42);
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
  enterRule(_localctx, 8, BadStatesParser::RuleTerm);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(44);
    _la = _input->LA(1);
    if (!(_la == BadStatesParser::NUMBER

    || _la == BadStatesParser::VARIABLE)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(55);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == BadStatesParser::TIMES) {
      setState(45);
      match(BadStatesParser::TIMES);
      setState(49);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == BadStatesParser::PLUS

      || _la == BadStatesParser::MINUS) {
        setState(46);
        connector();
        setState(51);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(52);
      _la = _input->LA(1);
      if (!(_la == BadStatesParser::NUMBER

      || _la == BadStatesParser::VARIABLE)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(57);
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
  enterRule(_localctx, 10, BadStatesParser::RulePolynom);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(61);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == BadStatesParser::PLUS

    || _la == BadStatesParser::MINUS) {
      setState(58);
      connector();
      setState(63);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(64);
    term();
    setState(74);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(66); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(65);
          connector();
          setState(68); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == BadStatesParser::PLUS

        || _la == BadStatesParser::MINUS);
        setState(70);
        term(); 
      }
      setState(76);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
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

std::vector<tree::TerminalNode *> BadStatesParser::IntervalContext::MINUS() {
  return getTokens(BadStatesParser::MINUS);
}

tree::TerminalNode* BadStatesParser::IntervalContext::MINUS(size_t i) {
  return getToken(BadStatesParser::MINUS, i);
}


size_t BadStatesParser::IntervalContext::getRuleIndex() const {
  return BadStatesParser::RuleInterval;
}


BadStatesParser::IntervalContext* BadStatesParser::interval() {
  IntervalContext *_localctx = _tracker.createInstance<IntervalContext>(_ctx, getState());
  enterRule(_localctx, 12, BadStatesParser::RuleInterval);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(77);
    match(BadStatesParser::T__3);
    setState(79);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == BadStatesParser::MINUS) {
      setState(78);
      match(BadStatesParser::MINUS);
    }
    setState(81);
    match(BadStatesParser::NUMBER);
    setState(82);
    match(BadStatesParser::T__4);
    setState(84);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == BadStatesParser::MINUS) {
      setState(83);
      match(BadStatesParser::MINUS);
    }
    setState(86);
    match(BadStatesParser::NUMBER);
    setState(87);
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

BadStatesParser::ConnectorContext* BadStatesParser::EquationContext::connector() {
  return getRuleContext<BadStatesParser::ConnectorContext>(0);
}

BadStatesParser::IntervalContext* BadStatesParser::EquationContext::interval() {
  return getRuleContext<BadStatesParser::IntervalContext>(0);
}


size_t BadStatesParser::EquationContext::getRuleIndex() const {
  return BadStatesParser::RuleEquation;
}


BadStatesParser::EquationContext* BadStatesParser::equation() {
  EquationContext *_localctx = _tracker.createInstance<EquationContext>(_ctx, getState());
  enterRule(_localctx, 14, BadStatesParser::RuleEquation);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(89);
    match(BadStatesParser::VARIABLE);
    setState(90);
    match(BadStatesParser::EQUALS);
    setState(91);
    polynom();
    setState(95);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == BadStatesParser::PLUS

    || _la == BadStatesParser::MINUS) {
      setState(92);
      connector();
      setState(93);
      interval();
    }
   
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
  enterRule(_localctx, 16, BadStatesParser::RuleConstraint);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(97);
    polynom();
    setState(98);
    _la = _input->LA(1);
    if (!(_la == BadStatesParser::EQUALS

    || _la == BadStatesParser::BOOLRELATION)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(99);
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
  enterRule(_localctx, 18, BadStatesParser::RuleIntervalexpr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(101);
    match(BadStatesParser::VARIABLE);
    setState(102);
    match(BadStatesParser::IN);
    setState(103);
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
  enterRule(_localctx, 20, BadStatesParser::RuleConstrset);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(107); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(107);
              _errHandler->sync(this);
              switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
              case 1: {
                setState(105);
                constraint();
                break;
              }

              case 2: {
                setState(106);
                intervalexpr();
                break;
              }

              }
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(109); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
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
  "unsafeset", "lbadstate", "gbadstate", "connector", "term", "polynom", 
  "interval", "equation", "constraint", "intervalexpr", "constrset"
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
    0x3, 0x12, 0x72, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x7, 
    0x2, 0x1d, 0xa, 0x2, 0xc, 0x2, 0xe, 0x2, 0x20, 0xb, 0x2, 0x3, 0x2, 0x3, 
    0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x27, 0xa, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 
    0x3, 0x6, 0x7, 0x6, 0x32, 0xa, 0x6, 0xc, 0x6, 0xe, 0x6, 0x35, 0xb, 0x6, 
    0x3, 0x6, 0x7, 0x6, 0x38, 0xa, 0x6, 0xc, 0x6, 0xe, 0x6, 0x3b, 0xb, 0x6, 
    0x3, 0x7, 0x7, 0x7, 0x3e, 0xa, 0x7, 0xc, 0x7, 0xe, 0x7, 0x41, 0xb, 0x7, 
    0x3, 0x7, 0x3, 0x7, 0x6, 0x7, 0x45, 0xa, 0x7, 0xd, 0x7, 0xe, 0x7, 0x46, 
    0x3, 0x7, 0x3, 0x7, 0x7, 0x7, 0x4b, 0xa, 0x7, 0xc, 0x7, 0xe, 0x7, 0x4e, 
    0xb, 0x7, 0x3, 0x8, 0x3, 0x8, 0x5, 0x8, 0x52, 0xa, 0x8, 0x3, 0x8, 0x3, 
    0x8, 0x3, 0x8, 0x5, 0x8, 0x57, 0xa, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 
    0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 
    0x62, 0xa, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xb, 0x3, 
    0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xc, 0x3, 0xc, 0x6, 0xc, 0x6e, 0xa, 0xc, 
    0xd, 0xc, 0xe, 0xc, 0x6f, 0x3, 0xc, 0x2, 0x2, 0xd, 0x2, 0x4, 0x6, 0x8, 
    0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x2, 0x5, 0x3, 0x2, 0xd, 0xe, 
    0x3, 0x2, 0x10, 0x11, 0x3, 0x2, 0xb, 0xc, 0x2, 0x73, 0x2, 0x18, 0x3, 
    0x2, 0x2, 0x2, 0x4, 0x23, 0x3, 0x2, 0x2, 0x2, 0x6, 0x2a, 0x3, 0x2, 0x2, 
    0x2, 0x8, 0x2c, 0x3, 0x2, 0x2, 0x2, 0xa, 0x2e, 0x3, 0x2, 0x2, 0x2, 0xc, 
    0x3f, 0x3, 0x2, 0x2, 0x2, 0xe, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x10, 0x5b, 
    0x3, 0x2, 0x2, 0x2, 0x12, 0x63, 0x3, 0x2, 0x2, 0x2, 0x14, 0x67, 0x3, 
    0x2, 0x2, 0x2, 0x16, 0x6d, 0x3, 0x2, 0x2, 0x2, 0x18, 0x19, 0x7, 0x3, 
    0x2, 0x2, 0x19, 0x1e, 0x7, 0x4, 0x2, 0x2, 0x1a, 0x1d, 0x5, 0x6, 0x4, 
    0x2, 0x1b, 0x1d, 0x5, 0x4, 0x3, 0x2, 0x1c, 0x1a, 0x3, 0x2, 0x2, 0x2, 
    0x1c, 0x1b, 0x3, 0x2, 0x2, 0x2, 0x1d, 0x20, 0x3, 0x2, 0x2, 0x2, 0x1e, 
    0x1c, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x1f, 0x21, 
    0x3, 0x2, 0x2, 0x2, 0x20, 0x1e, 0x3, 0x2, 0x2, 0x2, 0x21, 0x22, 0x7, 
    0x5, 0x2, 0x2, 0x22, 0x3, 0x3, 0x2, 0x2, 0x2, 0x23, 0x24, 0x7, 0x11, 
    0x2, 0x2, 0x24, 0x26, 0x7, 0x4, 0x2, 0x2, 0x25, 0x27, 0x5, 0x16, 0xc, 
    0x2, 0x26, 0x25, 0x3, 0x2, 0x2, 0x2, 0x26, 0x27, 0x3, 0x2, 0x2, 0x2, 
    0x27, 0x28, 0x3, 0x2, 0x2, 0x2, 0x28, 0x29, 0x7, 0x5, 0x2, 0x2, 0x29, 
    0x5, 0x3, 0x2, 0x2, 0x2, 0x2a, 0x2b, 0x5, 0x16, 0xc, 0x2, 0x2b, 0x7, 
    0x3, 0x2, 0x2, 0x2, 0x2c, 0x2d, 0x9, 0x2, 0x2, 0x2, 0x2d, 0x9, 0x3, 
    0x2, 0x2, 0x2, 0x2e, 0x39, 0x9, 0x3, 0x2, 0x2, 0x2f, 0x33, 0x7, 0xf, 
    0x2, 0x2, 0x30, 0x32, 0x5, 0x8, 0x5, 0x2, 0x31, 0x30, 0x3, 0x2, 0x2, 
    0x2, 0x32, 0x35, 0x3, 0x2, 0x2, 0x2, 0x33, 0x31, 0x3, 0x2, 0x2, 0x2, 
    0x33, 0x34, 0x3, 0x2, 0x2, 0x2, 0x34, 0x36, 0x3, 0x2, 0x2, 0x2, 0x35, 
    0x33, 0x3, 0x2, 0x2, 0x2, 0x36, 0x38, 0x9, 0x3, 0x2, 0x2, 0x37, 0x2f, 
    0x3, 0x2, 0x2, 0x2, 0x38, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x39, 0x37, 0x3, 
    0x2, 0x2, 0x2, 0x39, 0x3a, 0x3, 0x2, 0x2, 0x2, 0x3a, 0xb, 0x3, 0x2, 
    0x2, 0x2, 0x3b, 0x39, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x3e, 0x5, 0x8, 0x5, 
    0x2, 0x3d, 0x3c, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x41, 0x3, 0x2, 0x2, 0x2, 
    0x3f, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x3f, 0x40, 0x3, 0x2, 0x2, 0x2, 0x40, 
    0x42, 0x3, 0x2, 0x2, 0x2, 0x41, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x42, 0x4c, 
    0x5, 0xa, 0x6, 0x2, 0x43, 0x45, 0x5, 0x8, 0x5, 0x2, 0x44, 0x43, 0x3, 
    0x2, 0x2, 0x2, 0x45, 0x46, 0x3, 0x2, 0x2, 0x2, 0x46, 0x44, 0x3, 0x2, 
    0x2, 0x2, 0x46, 0x47, 0x3, 0x2, 0x2, 0x2, 0x47, 0x48, 0x3, 0x2, 0x2, 
    0x2, 0x48, 0x49, 0x5, 0xa, 0x6, 0x2, 0x49, 0x4b, 0x3, 0x2, 0x2, 0x2, 
    0x4a, 0x44, 0x3, 0x2, 0x2, 0x2, 0x4b, 0x4e, 0x3, 0x2, 0x2, 0x2, 0x4c, 
    0x4a, 0x3, 0x2, 0x2, 0x2, 0x4c, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x4d, 0xd, 
    0x3, 0x2, 0x2, 0x2, 0x4e, 0x4c, 0x3, 0x2, 0x2, 0x2, 0x4f, 0x51, 0x7, 
    0x6, 0x2, 0x2, 0x50, 0x52, 0x7, 0xe, 0x2, 0x2, 0x51, 0x50, 0x3, 0x2, 
    0x2, 0x2, 0x51, 0x52, 0x3, 0x2, 0x2, 0x2, 0x52, 0x53, 0x3, 0x2, 0x2, 
    0x2, 0x53, 0x54, 0x7, 0x10, 0x2, 0x2, 0x54, 0x56, 0x7, 0x7, 0x2, 0x2, 
    0x55, 0x57, 0x7, 0xe, 0x2, 0x2, 0x56, 0x55, 0x3, 0x2, 0x2, 0x2, 0x56, 
    0x57, 0x3, 0x2, 0x2, 0x2, 0x57, 0x58, 0x3, 0x2, 0x2, 0x2, 0x58, 0x59, 
    0x7, 0x10, 0x2, 0x2, 0x59, 0x5a, 0x7, 0x8, 0x2, 0x2, 0x5a, 0xf, 0x3, 
    0x2, 0x2, 0x2, 0x5b, 0x5c, 0x7, 0x11, 0x2, 0x2, 0x5c, 0x5d, 0x7, 0xb, 
    0x2, 0x2, 0x5d, 0x61, 0x5, 0xc, 0x7, 0x2, 0x5e, 0x5f, 0x5, 0x8, 0x5, 
    0x2, 0x5f, 0x60, 0x5, 0xe, 0x8, 0x2, 0x60, 0x62, 0x3, 0x2, 0x2, 0x2, 
    0x61, 0x5e, 0x3, 0x2, 0x2, 0x2, 0x61, 0x62, 0x3, 0x2, 0x2, 0x2, 0x62, 
    0x11, 0x3, 0x2, 0x2, 0x2, 0x63, 0x64, 0x5, 0xc, 0x7, 0x2, 0x64, 0x65, 
    0x9, 0x4, 0x2, 0x2, 0x65, 0x66, 0x5, 0xc, 0x7, 0x2, 0x66, 0x13, 0x3, 
    0x2, 0x2, 0x2, 0x67, 0x68, 0x7, 0x11, 0x2, 0x2, 0x68, 0x69, 0x7, 0x9, 
    0x2, 0x2, 0x69, 0x6a, 0x5, 0xe, 0x8, 0x2, 0x6a, 0x15, 0x3, 0x2, 0x2, 
    0x2, 0x6b, 0x6e, 0x5, 0x12, 0xa, 0x2, 0x6c, 0x6e, 0x5, 0x14, 0xb, 0x2, 
    0x6d, 0x6b, 0x3, 0x2, 0x2, 0x2, 0x6d, 0x6c, 0x3, 0x2, 0x2, 0x2, 0x6e, 
    0x6f, 0x3, 0x2, 0x2, 0x2, 0x6f, 0x6d, 0x3, 0x2, 0x2, 0x2, 0x6f, 0x70, 
    0x3, 0x2, 0x2, 0x2, 0x70, 0x17, 0x3, 0x2, 0x2, 0x2, 0xf, 0x1c, 0x1e, 
    0x26, 0x33, 0x39, 0x3f, 0x46, 0x4c, 0x51, 0x56, 0x61, 0x6d, 0x6f, 
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
