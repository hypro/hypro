
// Generated from Location.g4 by ANTLR 4.7



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
    setState(24);
    match(LocationParser::T__0);
    setState(25);
    match(LocationParser::T__1);
    setState(29);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LocationParser::VARIABLE) {
      setState(26);
      location();
      setState(31);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(32);
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

std::vector<LocationParser::InvariantsContext *> LocationParser::LocationContext::invariants() {
  return getRuleContexts<LocationParser::InvariantsContext>();
}

LocationParser::InvariantsContext* LocationParser::LocationContext::invariants(size_t i) {
  return getRuleContext<LocationParser::InvariantsContext>(i);
}


size_t LocationParser::LocationContext::getRuleIndex() const {
  return LocationParser::RuleLocation;
}


LocationParser::LocationContext* LocationParser::location() {
  LocationContext *_localctx = _tracker.createInstance<LocationContext>(_ctx, getState());
  enterRule(_localctx, 2, LocationParser::RuleLocation);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(34);
    match(LocationParser::VARIABLE);
    setState(35);
    match(LocationParser::T__1);
    setState(36);
    activities();
    setState(40);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LocationParser::T__7) {
      setState(37);
      invariants();
      setState(42);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(43);
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
    setState(45);
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
    setState(46);
    match(LocationParser::T__1);
    setState(50);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LocationParser::VARIABLE) {
      setState(47);
      equation();
      setState(52);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(53);
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

LocationParser::ConstrsetContext* LocationParser::InvariantsContext::constrset() {
  return getRuleContext<LocationParser::ConstrsetContext>(0);
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
    setState(55);
    match(LocationParser::T__7);
    setState(56);
    match(LocationParser::T__1);
    setState(58);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << LocationParser::PLUS)
      | (1ULL << LocationParser::MINUS)
      | (1ULL << LocationParser::NUMBER)
      | (1ULL << LocationParser::VARIABLE))) != 0)) {
      setState(57);
      constrset();
    }
    setState(60);
    match(LocationParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConnectorContext ------------------------------------------------------------------

LocationParser::ConnectorContext::ConnectorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LocationParser::ConnectorContext::PLUS() {
  return getToken(LocationParser::PLUS, 0);
}

tree::TerminalNode* LocationParser::ConnectorContext::MINUS() {
  return getToken(LocationParser::MINUS, 0);
}


size_t LocationParser::ConnectorContext::getRuleIndex() const {
  return LocationParser::RuleConnector;
}


LocationParser::ConnectorContext* LocationParser::connector() {
  ConnectorContext *_localctx = _tracker.createInstance<ConnectorContext>(_ctx, getState());
  enterRule(_localctx, 8, LocationParser::RuleConnector);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(62);
    _la = _input->LA(1);
    if (!(_la == LocationParser::PLUS

    || _la == LocationParser::MINUS)) {
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

std::vector<LocationParser::ConnectorContext *> LocationParser::TermContext::connector() {
  return getRuleContexts<LocationParser::ConnectorContext>();
}

LocationParser::ConnectorContext* LocationParser::TermContext::connector(size_t i) {
  return getRuleContext<LocationParser::ConnectorContext>(i);
}


size_t LocationParser::TermContext::getRuleIndex() const {
  return LocationParser::RuleTerm;
}


LocationParser::TermContext* LocationParser::term() {
  TermContext *_localctx = _tracker.createInstance<TermContext>(_ctx, getState());
  enterRule(_localctx, 10, LocationParser::RuleTerm);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(64);
    _la = _input->LA(1);
    if (!(_la == LocationParser::NUMBER

    || _la == LocationParser::VARIABLE)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(75);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LocationParser::TIMES) {
      setState(65);
      match(LocationParser::TIMES);
      setState(69);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == LocationParser::PLUS

      || _la == LocationParser::MINUS) {
        setState(66);
        connector();
        setState(71);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(72);
      _la = _input->LA(1);
      if (!(_la == LocationParser::NUMBER

      || _la == LocationParser::VARIABLE)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(77);
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

std::vector<LocationParser::ConnectorContext *> LocationParser::PolynomContext::connector() {
  return getRuleContexts<LocationParser::ConnectorContext>();
}

LocationParser::ConnectorContext* LocationParser::PolynomContext::connector(size_t i) {
  return getRuleContext<LocationParser::ConnectorContext>(i);
}


size_t LocationParser::PolynomContext::getRuleIndex() const {
  return LocationParser::RulePolynom;
}


LocationParser::PolynomContext* LocationParser::polynom() {
  PolynomContext *_localctx = _tracker.createInstance<PolynomContext>(_ctx, getState());
  enterRule(_localctx, 12, LocationParser::RulePolynom);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(81);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LocationParser::PLUS

    || _la == LocationParser::MINUS) {
      setState(78);
      connector();
      setState(83);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(84);
    term();
    setState(94);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(86); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(85);
          connector();
          setState(88); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == LocationParser::PLUS

        || _la == LocationParser::MINUS);
        setState(90);
        term(); 
      }
      setState(96);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx);
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

LocationParser::IntervalContext::IntervalContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> LocationParser::IntervalContext::NUMBER() {
  return getTokens(LocationParser::NUMBER);
}

tree::TerminalNode* LocationParser::IntervalContext::NUMBER(size_t i) {
  return getToken(LocationParser::NUMBER, i);
}

std::vector<tree::TerminalNode *> LocationParser::IntervalContext::MINUS() {
  return getTokens(LocationParser::MINUS);
}

tree::TerminalNode* LocationParser::IntervalContext::MINUS(size_t i) {
  return getToken(LocationParser::MINUS, i);
}


size_t LocationParser::IntervalContext::getRuleIndex() const {
  return LocationParser::RuleInterval;
}


LocationParser::IntervalContext* LocationParser::interval() {
  IntervalContext *_localctx = _tracker.createInstance<IntervalContext>(_ctx, getState());
  enterRule(_localctx, 14, LocationParser::RuleInterval);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(97);
    match(LocationParser::T__8);
    setState(99);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LocationParser::MINUS) {
      setState(98);
      match(LocationParser::MINUS);
    }
    setState(101);
    match(LocationParser::NUMBER);
    setState(102);
    match(LocationParser::T__9);
    setState(104);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LocationParser::MINUS) {
      setState(103);
      match(LocationParser::MINUS);
    }
    setState(106);
    match(LocationParser::NUMBER);
    setState(107);
    match(LocationParser::T__10);
   
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
  enterRule(_localctx, 16, LocationParser::RuleEquation);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(109);
    match(LocationParser::VARIABLE);
    setState(110);
    match(LocationParser::EQUALS);
    setState(111);
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
  enterRule(_localctx, 18, LocationParser::RuleConstraint);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(113);
    polynom();
    setState(114);
    _la = _input->LA(1);
    if (!(_la == LocationParser::EQUALS

    || _la == LocationParser::BOOLRELATION)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(115);
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
  enterRule(_localctx, 20, LocationParser::RuleIntervalexpr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(117);
    match(LocationParser::VARIABLE);
    setState(118);
    match(LocationParser::IN);
    setState(119);
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

LocationParser::ConstrsetContext::ConstrsetContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<LocationParser::ConstraintContext *> LocationParser::ConstrsetContext::constraint() {
  return getRuleContexts<LocationParser::ConstraintContext>();
}

LocationParser::ConstraintContext* LocationParser::ConstrsetContext::constraint(size_t i) {
  return getRuleContext<LocationParser::ConstraintContext>(i);
}

std::vector<LocationParser::IntervalexprContext *> LocationParser::ConstrsetContext::intervalexpr() {
  return getRuleContexts<LocationParser::IntervalexprContext>();
}

LocationParser::IntervalexprContext* LocationParser::ConstrsetContext::intervalexpr(size_t i) {
  return getRuleContext<LocationParser::IntervalexprContext>(i);
}


size_t LocationParser::ConstrsetContext::getRuleIndex() const {
  return LocationParser::RuleConstrset;
}


LocationParser::ConstrsetContext* LocationParser::constrset() {
  ConstrsetContext *_localctx = _tracker.createInstance<ConstrsetContext>(_ctx, getState());
  enterRule(_localctx, 22, LocationParser::RuleConstrset);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(123); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(123);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
      case 1: {
        setState(121);
        constraint();
        break;
      }

      case 2: {
        setState(122);
        intervalexpr();
        break;
      }

      }
      setState(125); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << LocationParser::PLUS)
      | (1ULL << LocationParser::MINUS)
      | (1ULL << LocationParser::NUMBER)
      | (1ULL << LocationParser::VARIABLE))) != 0));
   
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
  "modes", "location", "activities", "invariants", "connector", "term", 
  "polynom", "interval", "equation", "constraint", "intervalexpr", "constrset"
};

std::vector<std::string> LocationParser::_literalNames = {
  "", "'modes'", "'{'", "'}'", "'poly ode 1'", "'poly ode 2'", "'poly ode 3'", 
  "'linear ode'", "'inv'", "'['", "','", "']'", "'in'", "", "'='", "", "'+'", 
  "'-'", "'*'"
};

std::vector<std::string> LocationParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "IN", "COMMENT", "EQUALS", 
  "BOOLRELATION", "PLUS", "MINUS", "TIMES", "NUMBER", "VARIABLE", "WS"
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
    0x3, 0x17, 0x82, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x3, 0x2, 0x3, 0x2, 0x3, 
    0x2, 0x7, 0x2, 0x1e, 0xa, 0x2, 0xc, 0x2, 0xe, 0x2, 0x21, 0xb, 0x2, 0x3, 
    0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x7, 0x3, 0x29, 
    0xa, 0x3, 0xc, 0x3, 0xe, 0x3, 0x2c, 0xb, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x4, 0x3, 0x4, 0x3, 0x4, 0x7, 0x4, 0x33, 0xa, 0x4, 0xc, 0x4, 0xe, 0x4, 
    0x36, 0xb, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x5, 
    0x5, 0x3d, 0xa, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x7, 0x7, 0x7, 0x46, 0xa, 0x7, 0xc, 0x7, 0xe, 0x7, 0x49, 
    0xb, 0x7, 0x3, 0x7, 0x7, 0x7, 0x4c, 0xa, 0x7, 0xc, 0x7, 0xe, 0x7, 0x4f, 
    0xb, 0x7, 0x3, 0x8, 0x7, 0x8, 0x52, 0xa, 0x8, 0xc, 0x8, 0xe, 0x8, 0x55, 
    0xb, 0x8, 0x3, 0x8, 0x3, 0x8, 0x6, 0x8, 0x59, 0xa, 0x8, 0xd, 0x8, 0xe, 
    0x8, 0x5a, 0x3, 0x8, 0x3, 0x8, 0x7, 0x8, 0x5f, 0xa, 0x8, 0xc, 0x8, 0xe, 
    0x8, 0x62, 0xb, 0x8, 0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 0x66, 0xa, 0x9, 0x3, 
    0x9, 0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 0x6b, 0xa, 0x9, 0x3, 0x9, 0x3, 0x9, 
    0x3, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xb, 0x3, 0xb, 
    0x3, 0xb, 0x3, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xd, 
    0x3, 0xd, 0x6, 0xd, 0x7e, 0xa, 0xd, 0xd, 0xd, 0xe, 0xd, 0x7f, 0x3, 0xd, 
    0x2, 0x2, 0xe, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 
    0x16, 0x18, 0x2, 0x6, 0x3, 0x2, 0x6, 0x9, 0x3, 0x2, 0x12, 0x13, 0x3, 
    0x2, 0x15, 0x16, 0x3, 0x2, 0x10, 0x11, 0x2, 0x82, 0x2, 0x1a, 0x3, 0x2, 
    0x2, 0x2, 0x4, 0x24, 0x3, 0x2, 0x2, 0x2, 0x6, 0x2f, 0x3, 0x2, 0x2, 0x2, 
    0x8, 0x39, 0x3, 0x2, 0x2, 0x2, 0xa, 0x40, 0x3, 0x2, 0x2, 0x2, 0xc, 0x42, 
    0x3, 0x2, 0x2, 0x2, 0xe, 0x53, 0x3, 0x2, 0x2, 0x2, 0x10, 0x63, 0x3, 
    0x2, 0x2, 0x2, 0x12, 0x6f, 0x3, 0x2, 0x2, 0x2, 0x14, 0x73, 0x3, 0x2, 
    0x2, 0x2, 0x16, 0x77, 0x3, 0x2, 0x2, 0x2, 0x18, 0x7d, 0x3, 0x2, 0x2, 
    0x2, 0x1a, 0x1b, 0x7, 0x3, 0x2, 0x2, 0x1b, 0x1f, 0x7, 0x4, 0x2, 0x2, 
    0x1c, 0x1e, 0x5, 0x4, 0x3, 0x2, 0x1d, 0x1c, 0x3, 0x2, 0x2, 0x2, 0x1e, 
    0x21, 0x3, 0x2, 0x2, 0x2, 0x1f, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x1f, 0x20, 
    0x3, 0x2, 0x2, 0x2, 0x20, 0x22, 0x3, 0x2, 0x2, 0x2, 0x21, 0x1f, 0x3, 
    0x2, 0x2, 0x2, 0x22, 0x23, 0x7, 0x5, 0x2, 0x2, 0x23, 0x3, 0x3, 0x2, 
    0x2, 0x2, 0x24, 0x25, 0x7, 0x16, 0x2, 0x2, 0x25, 0x26, 0x7, 0x4, 0x2, 
    0x2, 0x26, 0x2a, 0x5, 0x6, 0x4, 0x2, 0x27, 0x29, 0x5, 0x8, 0x5, 0x2, 
    0x28, 0x27, 0x3, 0x2, 0x2, 0x2, 0x29, 0x2c, 0x3, 0x2, 0x2, 0x2, 0x2a, 
    0x28, 0x3, 0x2, 0x2, 0x2, 0x2a, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x2b, 0x2d, 
    0x3, 0x2, 0x2, 0x2, 0x2c, 0x2a, 0x3, 0x2, 0x2, 0x2, 0x2d, 0x2e, 0x7, 
    0x5, 0x2, 0x2, 0x2e, 0x5, 0x3, 0x2, 0x2, 0x2, 0x2f, 0x30, 0x9, 0x2, 
    0x2, 0x2, 0x30, 0x34, 0x7, 0x4, 0x2, 0x2, 0x31, 0x33, 0x5, 0x12, 0xa, 
    0x2, 0x32, 0x31, 0x3, 0x2, 0x2, 0x2, 0x33, 0x36, 0x3, 0x2, 0x2, 0x2, 
    0x34, 0x32, 0x3, 0x2, 0x2, 0x2, 0x34, 0x35, 0x3, 0x2, 0x2, 0x2, 0x35, 
    0x37, 0x3, 0x2, 0x2, 0x2, 0x36, 0x34, 0x3, 0x2, 0x2, 0x2, 0x37, 0x38, 
    0x7, 0x5, 0x2, 0x2, 0x38, 0x7, 0x3, 0x2, 0x2, 0x2, 0x39, 0x3a, 0x7, 
    0xa, 0x2, 0x2, 0x3a, 0x3c, 0x7, 0x4, 0x2, 0x2, 0x3b, 0x3d, 0x5, 0x18, 
    0xd, 0x2, 0x3c, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x3d, 0x3, 0x2, 0x2, 
    0x2, 0x3d, 0x3e, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x3f, 0x7, 0x5, 0x2, 0x2, 
    0x3f, 0x9, 0x3, 0x2, 0x2, 0x2, 0x40, 0x41, 0x9, 0x3, 0x2, 0x2, 0x41, 
    0xb, 0x3, 0x2, 0x2, 0x2, 0x42, 0x4d, 0x9, 0x4, 0x2, 0x2, 0x43, 0x47, 
    0x7, 0x14, 0x2, 0x2, 0x44, 0x46, 0x5, 0xa, 0x6, 0x2, 0x45, 0x44, 0x3, 
    0x2, 0x2, 0x2, 0x46, 0x49, 0x3, 0x2, 0x2, 0x2, 0x47, 0x45, 0x3, 0x2, 
    0x2, 0x2, 0x47, 0x48, 0x3, 0x2, 0x2, 0x2, 0x48, 0x4a, 0x3, 0x2, 0x2, 
    0x2, 0x49, 0x47, 0x3, 0x2, 0x2, 0x2, 0x4a, 0x4c, 0x9, 0x4, 0x2, 0x2, 
    0x4b, 0x43, 0x3, 0x2, 0x2, 0x2, 0x4c, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x4d, 
    0x4b, 0x3, 0x2, 0x2, 0x2, 0x4d, 0x4e, 0x3, 0x2, 0x2, 0x2, 0x4e, 0xd, 
    0x3, 0x2, 0x2, 0x2, 0x4f, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x50, 0x52, 0x5, 
    0xa, 0x6, 0x2, 0x51, 0x50, 0x3, 0x2, 0x2, 0x2, 0x52, 0x55, 0x3, 0x2, 
    0x2, 0x2, 0x53, 0x51, 0x3, 0x2, 0x2, 0x2, 0x53, 0x54, 0x3, 0x2, 0x2, 
    0x2, 0x54, 0x56, 0x3, 0x2, 0x2, 0x2, 0x55, 0x53, 0x3, 0x2, 0x2, 0x2, 
    0x56, 0x60, 0x5, 0xc, 0x7, 0x2, 0x57, 0x59, 0x5, 0xa, 0x6, 0x2, 0x58, 
    0x57, 0x3, 0x2, 0x2, 0x2, 0x59, 0x5a, 0x3, 0x2, 0x2, 0x2, 0x5a, 0x58, 
    0x3, 0x2, 0x2, 0x2, 0x5a, 0x5b, 0x3, 0x2, 0x2, 0x2, 0x5b, 0x5c, 0x3, 
    0x2, 0x2, 0x2, 0x5c, 0x5d, 0x5, 0xc, 0x7, 0x2, 0x5d, 0x5f, 0x3, 0x2, 
    0x2, 0x2, 0x5e, 0x58, 0x3, 0x2, 0x2, 0x2, 0x5f, 0x62, 0x3, 0x2, 0x2, 
    0x2, 0x60, 0x5e, 0x3, 0x2, 0x2, 0x2, 0x60, 0x61, 0x3, 0x2, 0x2, 0x2, 
    0x61, 0xf, 0x3, 0x2, 0x2, 0x2, 0x62, 0x60, 0x3, 0x2, 0x2, 0x2, 0x63, 
    0x65, 0x7, 0xb, 0x2, 0x2, 0x64, 0x66, 0x7, 0x13, 0x2, 0x2, 0x65, 0x64, 
    0x3, 0x2, 0x2, 0x2, 0x65, 0x66, 0x3, 0x2, 0x2, 0x2, 0x66, 0x67, 0x3, 
    0x2, 0x2, 0x2, 0x67, 0x68, 0x7, 0x15, 0x2, 0x2, 0x68, 0x6a, 0x7, 0xc, 
    0x2, 0x2, 0x69, 0x6b, 0x7, 0x13, 0x2, 0x2, 0x6a, 0x69, 0x3, 0x2, 0x2, 
    0x2, 0x6a, 0x6b, 0x3, 0x2, 0x2, 0x2, 0x6b, 0x6c, 0x3, 0x2, 0x2, 0x2, 
    0x6c, 0x6d, 0x7, 0x15, 0x2, 0x2, 0x6d, 0x6e, 0x7, 0xd, 0x2, 0x2, 0x6e, 
    0x11, 0x3, 0x2, 0x2, 0x2, 0x6f, 0x70, 0x7, 0x16, 0x2, 0x2, 0x70, 0x71, 
    0x7, 0x10, 0x2, 0x2, 0x71, 0x72, 0x5, 0xe, 0x8, 0x2, 0x72, 0x13, 0x3, 
    0x2, 0x2, 0x2, 0x73, 0x74, 0x5, 0xe, 0x8, 0x2, 0x74, 0x75, 0x9, 0x5, 
    0x2, 0x2, 0x75, 0x76, 0x5, 0xe, 0x8, 0x2, 0x76, 0x15, 0x3, 0x2, 0x2, 
    0x2, 0x77, 0x78, 0x7, 0x16, 0x2, 0x2, 0x78, 0x79, 0x7, 0xe, 0x2, 0x2, 
    0x79, 0x7a, 0x5, 0x10, 0x9, 0x2, 0x7a, 0x17, 0x3, 0x2, 0x2, 0x2, 0x7b, 
    0x7e, 0x5, 0x14, 0xb, 0x2, 0x7c, 0x7e, 0x5, 0x16, 0xc, 0x2, 0x7d, 0x7b, 
    0x3, 0x2, 0x2, 0x2, 0x7d, 0x7c, 0x3, 0x2, 0x2, 0x2, 0x7e, 0x7f, 0x3, 
    0x2, 0x2, 0x2, 0x7f, 0x7d, 0x3, 0x2, 0x2, 0x2, 0x7f, 0x80, 0x3, 0x2, 
    0x2, 0x2, 0x80, 0x19, 0x3, 0x2, 0x2, 0x2, 0xf, 0x1f, 0x2a, 0x34, 0x3c, 
    0x47, 0x4d, 0x53, 0x5a, 0x60, 0x65, 0x6a, 0x7d, 0x7f, 
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
