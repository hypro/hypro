
// Generated from ../src/hypro/parser/antlr4-flowstar/Location.g4 by ANTLR 4.7



#include "LocationParser.h"


using namespace antlrcpp;
using namespace antlr4;

LocationParser::LocationParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

LocationParser::~LocationParser() {
  delete _interpreter;
}

std::string LocationParser::getGrammarFileName() const {
  return "Location.g4";
}

const std::vector<std::string>& LocationParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& LocationParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- ModesContext ------------------------------------------------------------------

LocationParser::ModesContext::ModesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<LocationParser::LocationContext *> LocationParser::ModesContext::location() {
  return getRuleContexts<LocationParser::LocationContext>();
}

LocationParser::LocationContext* LocationParser::ModesContext::location(size_t i) {
  return getRuleContext<LocationParser::LocationContext>(i);
}


size_t LocationParser::ModesContext::getRuleIndex() const {
  return LocationParser::RuleModes;
}


LocationParser::ModesContext* LocationParser::modes() {
  ModesContext *_localctx = _tracker.createInstance<ModesContext>(_ctx, getState());
  enterRule(_localctx, 0, LocationParser::RuleModes);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(20);
    match(LocationParser::T__0);
    setState(21);
    match(LocationParser::T__1);
    setState(25);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LocationParser::VARIABLE) {
      setState(22);
      location();
      setState(27);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(28);
    match(LocationParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LocationContext ------------------------------------------------------------------

LocationParser::LocationContext::LocationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LocationParser::LocationContext::VARIABLE() {
  return getToken(LocationParser::VARIABLE, 0);
}

LocationParser::ActivitiesContext* LocationParser::LocationContext::activities() {
  return getRuleContext<LocationParser::ActivitiesContext>(0);
}

LocationParser::InvariantsContext* LocationParser::LocationContext::invariants() {
  return getRuleContext<LocationParser::InvariantsContext>(0);
}


size_t LocationParser::LocationContext::getRuleIndex() const {
  return LocationParser::RuleLocation;
}


LocationParser::LocationContext* LocationParser::location() {
  LocationContext *_localctx = _tracker.createInstance<LocationContext>(_ctx, getState());
  enterRule(_localctx, 2, LocationParser::RuleLocation);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(30);
    match(LocationParser::VARIABLE);
    setState(31);
    match(LocationParser::T__1);
    setState(32);
    activities();
    setState(33);
    invariants();
    setState(34);
    match(LocationParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ActivitiesContext ------------------------------------------------------------------

LocationParser::ActivitiesContext::ActivitiesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<LocationParser::EquationContext *> LocationParser::ActivitiesContext::equation() {
  return getRuleContexts<LocationParser::EquationContext>();
}

LocationParser::EquationContext* LocationParser::ActivitiesContext::equation(size_t i) {
  return getRuleContext<LocationParser::EquationContext>(i);
}


size_t LocationParser::ActivitiesContext::getRuleIndex() const {
  return LocationParser::RuleActivities;
}


LocationParser::ActivitiesContext* LocationParser::activities() {
  ActivitiesContext *_localctx = _tracker.createInstance<ActivitiesContext>(_ctx, getState());
  enterRule(_localctx, 4, LocationParser::RuleActivities);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(36);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << LocationParser::T__3)
      | (1ULL << LocationParser::T__4)
      | (1ULL << LocationParser::T__5)
      | (1ULL << LocationParser::T__6))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(37);
    match(LocationParser::T__1);
    setState(41);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LocationParser::VARIABLE) {
      setState(38);
      equation();
      setState(43);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(44);
    match(LocationParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InvariantsContext ------------------------------------------------------------------

LocationParser::InvariantsContext::InvariantsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<LocationParser::ConstraintContext *> LocationParser::InvariantsContext::constraint() {
  return getRuleContexts<LocationParser::ConstraintContext>();
}

LocationParser::ConstraintContext* LocationParser::InvariantsContext::constraint(size_t i) {
  return getRuleContext<LocationParser::ConstraintContext>(i);
}

std::vector<LocationParser::IntervalexprContext *> LocationParser::InvariantsContext::intervalexpr() {
  return getRuleContexts<LocationParser::IntervalexprContext>();
}

LocationParser::IntervalexprContext* LocationParser::InvariantsContext::intervalexpr(size_t i) {
  return getRuleContext<LocationParser::IntervalexprContext>(i);
}


size_t LocationParser::InvariantsContext::getRuleIndex() const {
  return LocationParser::RuleInvariants;
}


LocationParser::InvariantsContext* LocationParser::invariants() {
  InvariantsContext *_localctx = _tracker.createInstance<InvariantsContext>(_ctx, getState());
  enterRule(_localctx, 6, LocationParser::RuleInvariants);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(46);
    match(LocationParser::T__7);
    setState(47);
    match(LocationParser::T__1);
    setState(52);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LocationParser::NUMBER

    || _la == LocationParser::VARIABLE) {
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
    setState(55);
    match(LocationParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TermContext ------------------------------------------------------------------

LocationParser::TermContext::TermContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> LocationParser::TermContext::NUMBER() {
  return getTokens(LocationParser::NUMBER);
}

tree::TerminalNode* LocationParser::TermContext::NUMBER(size_t i) {
  return getToken(LocationParser::NUMBER, i);
}

std::vector<tree::TerminalNode *> LocationParser::TermContext::VARIABLE() {
  return getTokens(LocationParser::VARIABLE);
}

tree::TerminalNode* LocationParser::TermContext::VARIABLE(size_t i) {
  return getToken(LocationParser::VARIABLE, i);
}

std::vector<tree::TerminalNode *> LocationParser::TermContext::TIMES() {
  return getTokens(LocationParser::TIMES);
}

tree::TerminalNode* LocationParser::TermContext::TIMES(size_t i) {
  return getToken(LocationParser::TIMES, i);
}


size_t LocationParser::TermContext::getRuleIndex() const {
  return LocationParser::RuleTerm;
}


LocationParser::TermContext* LocationParser::term() {
  TermContext *_localctx = _tracker.createInstance<TermContext>(_ctx, getState());
  enterRule(_localctx, 8, LocationParser::RuleTerm);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(57);
    _la = _input->LA(1);
    if (!(_la == LocationParser::NUMBER

    || _la == LocationParser::VARIABLE)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(62);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LocationParser::TIMES) {
      setState(58);
      match(LocationParser::TIMES);
      setState(59);
      _la = _input->LA(1);
      if (!(_la == LocationParser::NUMBER

      || _la == LocationParser::VARIABLE)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(64);
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

LocationParser::PolynomContext::PolynomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<LocationParser::TermContext *> LocationParser::PolynomContext::term() {
  return getRuleContexts<LocationParser::TermContext>();
}

LocationParser::TermContext* LocationParser::PolynomContext::term(size_t i) {
  return getRuleContext<LocationParser::TermContext>(i);
}

std::vector<tree::TerminalNode *> LocationParser::PolynomContext::PLUS() {
  return getTokens(LocationParser::PLUS);
}

tree::TerminalNode* LocationParser::PolynomContext::PLUS(size_t i) {
  return getToken(LocationParser::PLUS, i);
}


size_t LocationParser::PolynomContext::getRuleIndex() const {
  return LocationParser::RulePolynom;
}


LocationParser::PolynomContext* LocationParser::polynom() {
  PolynomContext *_localctx = _tracker.createInstance<PolynomContext>(_ctx, getState());
  enterRule(_localctx, 10, LocationParser::RulePolynom);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(65);
    term();
    setState(70);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LocationParser::PLUS) {
      setState(66);
      match(LocationParser::PLUS);
      setState(67);
      term();
      setState(72);
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

//----------------- EquationContext ------------------------------------------------------------------

LocationParser::EquationContext::EquationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LocationParser::EquationContext::VARIABLE() {
  return getToken(LocationParser::VARIABLE, 0);
}

tree::TerminalNode* LocationParser::EquationContext::EQUALS() {
  return getToken(LocationParser::EQUALS, 0);
}

LocationParser::PolynomContext* LocationParser::EquationContext::polynom() {
  return getRuleContext<LocationParser::PolynomContext>(0);
}


size_t LocationParser::EquationContext::getRuleIndex() const {
  return LocationParser::RuleEquation;
}


LocationParser::EquationContext* LocationParser::equation() {
  EquationContext *_localctx = _tracker.createInstance<EquationContext>(_ctx, getState());
  enterRule(_localctx, 12, LocationParser::RuleEquation);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(73);
    match(LocationParser::VARIABLE);
    setState(74);
    match(LocationParser::EQUALS);
    setState(75);
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

LocationParser::ConstraintContext::ConstraintContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<LocationParser::PolynomContext *> LocationParser::ConstraintContext::polynom() {
  return getRuleContexts<LocationParser::PolynomContext>();
}

LocationParser::PolynomContext* LocationParser::ConstraintContext::polynom(size_t i) {
  return getRuleContext<LocationParser::PolynomContext>(i);
}

tree::TerminalNode* LocationParser::ConstraintContext::BOOLRELATION() {
  return getToken(LocationParser::BOOLRELATION, 0);
}

tree::TerminalNode* LocationParser::ConstraintContext::EQUALS() {
  return getToken(LocationParser::EQUALS, 0);
}


size_t LocationParser::ConstraintContext::getRuleIndex() const {
  return LocationParser::RuleConstraint;
}


LocationParser::ConstraintContext* LocationParser::constraint() {
  ConstraintContext *_localctx = _tracker.createInstance<ConstraintContext>(_ctx, getState());
  enterRule(_localctx, 14, LocationParser::RuleConstraint);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(77);
    polynom();
    setState(78);
    _la = _input->LA(1);
    if (!(_la == LocationParser::EQUALS

    || _la == LocationParser::BOOLRELATION)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(79);
    polynom();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IntervalContext ------------------------------------------------------------------

LocationParser::IntervalContext::IntervalContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> LocationParser::IntervalContext::NUMBER() {
  return getTokens(LocationParser::NUMBER);
}

tree::TerminalNode* LocationParser::IntervalContext::NUMBER(size_t i) {
  return getToken(LocationParser::NUMBER, i);
}


size_t LocationParser::IntervalContext::getRuleIndex() const {
  return LocationParser::RuleInterval;
}


LocationParser::IntervalContext* LocationParser::interval() {
  IntervalContext *_localctx = _tracker.createInstance<IntervalContext>(_ctx, getState());
  enterRule(_localctx, 16, LocationParser::RuleInterval);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(81);
    match(LocationParser::T__8);
    setState(82);
    match(LocationParser::NUMBER);
    setState(83);
    match(LocationParser::T__9);
    setState(84);
    match(LocationParser::NUMBER);
    setState(85);
    match(LocationParser::T__10);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IntervalexprContext ------------------------------------------------------------------

LocationParser::IntervalexprContext::IntervalexprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LocationParser::IntervalexprContext::VARIABLE() {
  return getToken(LocationParser::VARIABLE, 0);
}

tree::TerminalNode* LocationParser::IntervalexprContext::IN() {
  return getToken(LocationParser::IN, 0);
}

LocationParser::IntervalContext* LocationParser::IntervalexprContext::interval() {
  return getRuleContext<LocationParser::IntervalContext>(0);
}


size_t LocationParser::IntervalexprContext::getRuleIndex() const {
  return LocationParser::RuleIntervalexpr;
}


LocationParser::IntervalexprContext* LocationParser::intervalexpr() {
  IntervalexprContext *_localctx = _tracker.createInstance<IntervalexprContext>(_ctx, getState());
  enterRule(_localctx, 18, LocationParser::RuleIntervalexpr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(87);
    match(LocationParser::VARIABLE);
    setState(88);
    match(LocationParser::IN);
    setState(89);
    interval();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> LocationParser::_decisionToDFA;
atn::PredictionContextCache LocationParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN LocationParser::_atn;
std::vector<uint16_t> LocationParser::_serializedATN;

std::vector<std::string> LocationParser::_ruleNames = {
  "modes", "location", "activities", "invariants", "term", "polynom", "equation", 
  "constraint", "interval", "intervalexpr"
};

std::vector<std::string> LocationParser::_literalNames = {
  "", "'modes'", "'{'", "'}'", "'poly ode 1'", "'poly ode 2'", "'poly ode 3'", 
  "'linear ode'", "'inv'", "'['", "','", "']'", "'in'", "'='", "", "'+'", 
  "'*'"
};

std::vector<std::string> LocationParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "IN", "EQUALS", "BOOLRELATION", 
  "PLUS", "TIMES", "NUMBER", "VARIABLE", "WS"
};

dfa::Vocabulary LocationParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> LocationParser::_tokenNames;

LocationParser::Initializer::Initializer() {
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
    0x3, 0x15, 0x5e, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x7, 0x2, 0x1a, 0xa, 0x2, 0xc, 0x2, 
    0xe, 0x2, 0x1d, 0xb, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x7, 
    0x4, 0x2a, 0xa, 0x4, 0xc, 0x4, 0xe, 0x4, 0x2d, 0xb, 0x4, 0x3, 0x4, 0x3, 
    0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x7, 0x5, 0x35, 0xa, 0x5, 
    0xc, 0x5, 0xe, 0x5, 0x38, 0xb, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 
    0x6, 0x3, 0x6, 0x7, 0x6, 0x3f, 0xa, 0x6, 0xc, 0x6, 0xe, 0x6, 0x42, 0xb, 
    0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x7, 0x7, 0x47, 0xa, 0x7, 0xc, 0x7, 
    0xe, 0x7, 0x4a, 0xb, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 
    0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 
    0xb, 0x2, 0x2, 0xc, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 
    0x2, 0x5, 0x3, 0x2, 0x6, 0x9, 0x3, 0x2, 0x13, 0x14, 0x3, 0x2, 0xf, 0x10, 
    0x2, 0x59, 0x2, 0x16, 0x3, 0x2, 0x2, 0x2, 0x4, 0x20, 0x3, 0x2, 0x2, 
    0x2, 0x6, 0x26, 0x3, 0x2, 0x2, 0x2, 0x8, 0x30, 0x3, 0x2, 0x2, 0x2, 0xa, 
    0x3b, 0x3, 0x2, 0x2, 0x2, 0xc, 0x43, 0x3, 0x2, 0x2, 0x2, 0xe, 0x4b, 
    0x3, 0x2, 0x2, 0x2, 0x10, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x12, 0x53, 0x3, 
    0x2, 0x2, 0x2, 0x14, 0x59, 0x3, 0x2, 0x2, 0x2, 0x16, 0x17, 0x7, 0x3, 
    0x2, 0x2, 0x17, 0x1b, 0x7, 0x4, 0x2, 0x2, 0x18, 0x1a, 0x5, 0x4, 0x3, 
    0x2, 0x19, 0x18, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x1d, 0x3, 0x2, 0x2, 0x2, 
    0x1b, 0x19, 0x3, 0x2, 0x2, 0x2, 0x1b, 0x1c, 0x3, 0x2, 0x2, 0x2, 0x1c, 
    0x1e, 0x3, 0x2, 0x2, 0x2, 0x1d, 0x1b, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x1f, 
    0x7, 0x5, 0x2, 0x2, 0x1f, 0x3, 0x3, 0x2, 0x2, 0x2, 0x20, 0x21, 0x7, 
    0x14, 0x2, 0x2, 0x21, 0x22, 0x7, 0x4, 0x2, 0x2, 0x22, 0x23, 0x5, 0x6, 
    0x4, 0x2, 0x23, 0x24, 0x5, 0x8, 0x5, 0x2, 0x24, 0x25, 0x7, 0x5, 0x2, 
    0x2, 0x25, 0x5, 0x3, 0x2, 0x2, 0x2, 0x26, 0x27, 0x9, 0x2, 0x2, 0x2, 
    0x27, 0x2b, 0x7, 0x4, 0x2, 0x2, 0x28, 0x2a, 0x5, 0xe, 0x8, 0x2, 0x29, 
    0x28, 0x3, 0x2, 0x2, 0x2, 0x2a, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x2b, 0x29, 
    0x3, 0x2, 0x2, 0x2, 0x2b, 0x2c, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x2e, 0x3, 
    0x2, 0x2, 0x2, 0x2d, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x2f, 0x7, 0x5, 
    0x2, 0x2, 0x2f, 0x7, 0x3, 0x2, 0x2, 0x2, 0x30, 0x31, 0x7, 0xa, 0x2, 
    0x2, 0x31, 0x36, 0x7, 0x4, 0x2, 0x2, 0x32, 0x35, 0x5, 0x10, 0x9, 0x2, 
    0x33, 0x35, 0x5, 0x14, 0xb, 0x2, 0x34, 0x32, 0x3, 0x2, 0x2, 0x2, 0x34, 
    0x33, 0x3, 0x2, 0x2, 0x2, 0x35, 0x38, 0x3, 0x2, 0x2, 0x2, 0x36, 0x34, 
    0x3, 0x2, 0x2, 0x2, 0x36, 0x37, 0x3, 0x2, 0x2, 0x2, 0x37, 0x39, 0x3, 
    0x2, 0x2, 0x2, 0x38, 0x36, 0x3, 0x2, 0x2, 0x2, 0x39, 0x3a, 0x7, 0x5, 
    0x2, 0x2, 0x3a, 0x9, 0x3, 0x2, 0x2, 0x2, 0x3b, 0x40, 0x9, 0x3, 0x2, 
    0x2, 0x3c, 0x3d, 0x7, 0x12, 0x2, 0x2, 0x3d, 0x3f, 0x9, 0x3, 0x2, 0x2, 
    0x3e, 0x3c, 0x3, 0x2, 0x2, 0x2, 0x3f, 0x42, 0x3, 0x2, 0x2, 0x2, 0x40, 
    0x3e, 0x3, 0x2, 0x2, 0x2, 0x40, 0x41, 0x3, 0x2, 0x2, 0x2, 0x41, 0xb, 
    0x3, 0x2, 0x2, 0x2, 0x42, 0x40, 0x3, 0x2, 0x2, 0x2, 0x43, 0x48, 0x5, 
    0xa, 0x6, 0x2, 0x44, 0x45, 0x7, 0x11, 0x2, 0x2, 0x45, 0x47, 0x5, 0xa, 
    0x6, 0x2, 0x46, 0x44, 0x3, 0x2, 0x2, 0x2, 0x47, 0x4a, 0x3, 0x2, 0x2, 
    0x2, 0x48, 0x46, 0x3, 0x2, 0x2, 0x2, 0x48, 0x49, 0x3, 0x2, 0x2, 0x2, 
    0x49, 0xd, 0x3, 0x2, 0x2, 0x2, 0x4a, 0x48, 0x3, 0x2, 0x2, 0x2, 0x4b, 
    0x4c, 0x7, 0x14, 0x2, 0x2, 0x4c, 0x4d, 0x7, 0xf, 0x2, 0x2, 0x4d, 0x4e, 
    0x5, 0xc, 0x7, 0x2, 0x4e, 0xf, 0x3, 0x2, 0x2, 0x2, 0x4f, 0x50, 0x5, 
    0xc, 0x7, 0x2, 0x50, 0x51, 0x9, 0x4, 0x2, 0x2, 0x51, 0x52, 0x5, 0xc, 
    0x7, 0x2, 0x52, 0x11, 0x3, 0x2, 0x2, 0x2, 0x53, 0x54, 0x7, 0xb, 0x2, 
    0x2, 0x54, 0x55, 0x7, 0x13, 0x2, 0x2, 0x55, 0x56, 0x7, 0xc, 0x2, 0x2, 
    0x56, 0x57, 0x7, 0x13, 0x2, 0x2, 0x57, 0x58, 0x7, 0xd, 0x2, 0x2, 0x58, 
    0x13, 0x3, 0x2, 0x2, 0x2, 0x59, 0x5a, 0x7, 0x14, 0x2, 0x2, 0x5a, 0x5b, 
    0x7, 0xe, 0x2, 0x2, 0x5b, 0x5c, 0x5, 0x12, 0xa, 0x2, 0x5c, 0x15, 0x3, 
    0x2, 0x2, 0x2, 0x8, 0x1b, 0x2b, 0x34, 0x36, 0x40, 0x48, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

LocationParser::Initializer LocationParser::_init;
