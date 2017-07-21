
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
    setState(22);
    match(LocationParser::T__0);
    setState(23);
    match(LocationParser::T__1);
    setState(27);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LocationParser::VARIABLE) {
      setState(24);
      location();
      setState(29);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(30);
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
    setState(32);
    match(LocationParser::VARIABLE);
    setState(33);
    match(LocationParser::T__1);
    setState(34);
    activities();
    setState(35);
    invariants();
    setState(36);
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
    setState(38);
    match(LocationParser::T__3);
    setState(39);
    match(LocationParser::T__1);
    setState(43);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LocationParser::VARIABLE) {
      setState(40);
      equation();
      setState(45);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(46);
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

std::vector<LocationParser::BoolexprContext *> LocationParser::InvariantsContext::boolexpr() {
  return getRuleContexts<LocationParser::BoolexprContext>();
}

LocationParser::BoolexprContext* LocationParser::InvariantsContext::boolexpr(size_t i) {
  return getRuleContext<LocationParser::BoolexprContext>(i);
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
    setState(48);
    match(LocationParser::T__4);
    setState(49);
    match(LocationParser::T__1);
    setState(54);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LocationParser::VARIABLE

    || _la == LocationParser::NUMBER) {
      setState(52);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
      case 1: {
        setState(50);
        boolexpr();
        break;
      }

      case 2: {
        setState(51);
        intervalexpr();
        break;
      }

      }
      setState(56);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(57);
    match(LocationParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AddContext ------------------------------------------------------------------

LocationParser::AddContext::AddContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LocationParser::AddContext::PLUS() {
  return getToken(LocationParser::PLUS, 0);
}

LocationParser::TermContext* LocationParser::AddContext::term() {
  return getRuleContext<LocationParser::TermContext>(0);
}


size_t LocationParser::AddContext::getRuleIndex() const {
  return LocationParser::RuleAdd;
}


LocationParser::AddContext* LocationParser::add() {
  AddContext *_localctx = _tracker.createInstance<AddContext>(_ctx, getState());
  enterRule(_localctx, 8, LocationParser::RuleAdd);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(59);
    match(LocationParser::PLUS);
    setState(60);
    term();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MultContext ------------------------------------------------------------------

LocationParser::MultContext::MultContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> LocationParser::MultContext::NUMBER() {
  return getTokens(LocationParser::NUMBER);
}

tree::TerminalNode* LocationParser::MultContext::NUMBER(size_t i) {
  return getToken(LocationParser::NUMBER, i);
}

std::vector<tree::TerminalNode *> LocationParser::MultContext::VARIABLE() {
  return getTokens(LocationParser::VARIABLE);
}

tree::TerminalNode* LocationParser::MultContext::VARIABLE(size_t i) {
  return getToken(LocationParser::VARIABLE, i);
}

std::vector<tree::TerminalNode *> LocationParser::MultContext::TIMES() {
  return getTokens(LocationParser::TIMES);
}

tree::TerminalNode* LocationParser::MultContext::TIMES(size_t i) {
  return getToken(LocationParser::TIMES, i);
}


size_t LocationParser::MultContext::getRuleIndex() const {
  return LocationParser::RuleMult;
}


LocationParser::MultContext* LocationParser::mult() {
  MultContext *_localctx = _tracker.createInstance<MultContext>(_ctx, getState());
  enterRule(_localctx, 10, LocationParser::RuleMult);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(62);
    _la = _input->LA(1);
    if (!(_la == LocationParser::VARIABLE

    || _la == LocationParser::NUMBER)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(67);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    while (alt != 1 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1 + 1) {
        setState(63);
        match(LocationParser::TIMES);
        setState(64);
        _la = _input->LA(1);
        if (!(_la == LocationParser::VARIABLE

        || _la == LocationParser::NUMBER)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        } 
      }
      setState(69);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
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

LocationParser::MultContext* LocationParser::TermContext::mult() {
  return getRuleContext<LocationParser::MultContext>(0);
}

std::vector<LocationParser::AddContext *> LocationParser::TermContext::add() {
  return getRuleContexts<LocationParser::AddContext>();
}

LocationParser::AddContext* LocationParser::TermContext::add(size_t i) {
  return getRuleContext<LocationParser::AddContext>(i);
}


size_t LocationParser::TermContext::getRuleIndex() const {
  return LocationParser::RuleTerm;
}


LocationParser::TermContext* LocationParser::term() {
  TermContext *_localctx = _tracker.createInstance<TermContext>(_ctx, getState());
  enterRule(_localctx, 12, LocationParser::RuleTerm);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(70);
    mult();
    setState(74);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    while (alt != 1 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1 + 1) {
        setState(71);
        add(); 
      }
      setState(76);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
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

LocationParser::TermContext* LocationParser::EquationContext::term() {
  return getRuleContext<LocationParser::TermContext>(0);
}


size_t LocationParser::EquationContext::getRuleIndex() const {
  return LocationParser::RuleEquation;
}


LocationParser::EquationContext* LocationParser::equation() {
  EquationContext *_localctx = _tracker.createInstance<EquationContext>(_ctx, getState());
  enterRule(_localctx, 14, LocationParser::RuleEquation);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(77);
    match(LocationParser::VARIABLE);
    setState(78);
    match(LocationParser::EQUALS);
    setState(79);
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

LocationParser::BoolexprContext::BoolexprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LocationParser::TermContext* LocationParser::BoolexprContext::term() {
  return getRuleContext<LocationParser::TermContext>(0);
}

tree::TerminalNode* LocationParser::BoolexprContext::BOOLRELATION() {
  return getToken(LocationParser::BOOLRELATION, 0);
}

tree::TerminalNode* LocationParser::BoolexprContext::NUMBER() {
  return getToken(LocationParser::NUMBER, 0);
}


size_t LocationParser::BoolexprContext::getRuleIndex() const {
  return LocationParser::RuleBoolexpr;
}


LocationParser::BoolexprContext* LocationParser::boolexpr() {
  BoolexprContext *_localctx = _tracker.createInstance<BoolexprContext>(_ctx, getState());
  enterRule(_localctx, 16, LocationParser::RuleBoolexpr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(81);
    term();
    setState(82);
    match(LocationParser::BOOLRELATION);
    setState(83);
    match(LocationParser::NUMBER);
   
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

LocationParser::TermContext* LocationParser::IntervalexprContext::term() {
  return getRuleContext<LocationParser::TermContext>(0);
}

tree::TerminalNode* LocationParser::IntervalexprContext::IN() {
  return getToken(LocationParser::IN, 0);
}

tree::TerminalNode* LocationParser::IntervalexprContext::INTERVAL() {
  return getToken(LocationParser::INTERVAL, 0);
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
    setState(85);
    term();
    setState(86);
    match(LocationParser::IN);
    setState(87);
    match(LocationParser::INTERVAL);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FormulaContext ------------------------------------------------------------------

LocationParser::FormulaContext::FormulaContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LocationParser::EquationContext* LocationParser::FormulaContext::equation() {
  return getRuleContext<LocationParser::EquationContext>(0);
}

LocationParser::BoolexprContext* LocationParser::FormulaContext::boolexpr() {
  return getRuleContext<LocationParser::BoolexprContext>(0);
}

LocationParser::IntervalexprContext* LocationParser::FormulaContext::intervalexpr() {
  return getRuleContext<LocationParser::IntervalexprContext>(0);
}


size_t LocationParser::FormulaContext::getRuleIndex() const {
  return LocationParser::RuleFormula;
}


LocationParser::FormulaContext* LocationParser::formula() {
  FormulaContext *_localctx = _tracker.createInstance<FormulaContext>(_ctx, getState());
  enterRule(_localctx, 20, LocationParser::RuleFormula);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(92);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(89);
      equation();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(90);
      boolexpr();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(91);
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
std::vector<dfa::DFA> LocationParser::_decisionToDFA;
atn::PredictionContextCache LocationParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN LocationParser::_atn;
std::vector<uint16_t> LocationParser::_serializedATN;

std::vector<std::string> LocationParser::_ruleNames = {
  "modes", "location", "activities", "invariants", "add", "mult", "term", 
  "equation", "boolexpr", "intervalexpr", "formula"
};

std::vector<std::string> LocationParser::_literalNames = {
  "", "'modes'", "'{'", "'}'", "'poly ode 1'", "'inv'", "'in'", "'='", "", 
  "'+'", "'*'"
};

std::vector<std::string> LocationParser::_symbolicNames = {
  "", "", "", "", "", "", "IN", "EQUALS", "BOOLRELATION", "PLUS", "TIMES", 
  "VARIABLE", "NUMBER", "INTERVAL", "WS"
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
    0x3, 0x10, 0x61, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x7, 0x2, 0x1c, 
    0xa, 0x2, 0xc, 0x2, 0xe, 0x2, 0x1f, 0xb, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x4, 0x3, 
    0x4, 0x3, 0x4, 0x7, 0x4, 0x2c, 0xa, 0x4, 0xc, 0x4, 0xe, 0x4, 0x2f, 0xb, 
    0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x7, 
    0x5, 0x37, 0xa, 0x5, 0xc, 0x5, 0xe, 0x5, 0x3a, 0xb, 0x5, 0x3, 0x5, 0x3, 
    0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x7, 
    0x7, 0x44, 0xa, 0x7, 0xc, 0x7, 0xe, 0x7, 0x47, 0xb, 0x7, 0x3, 0x8, 0x3, 
    0x8, 0x7, 0x8, 0x4b, 0xa, 0x8, 0xc, 0x8, 0xe, 0x8, 0x4e, 0xb, 0x8, 0x3, 
    0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 
    0xc, 0x5, 0xc, 0x5f, 0xa, 0xc, 0x3, 0xc, 0x4, 0x45, 0x4c, 0x2, 0xd, 
    0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x2, 0x3, 
    0x3, 0x2, 0xd, 0xe, 0x2, 0x5d, 0x2, 0x18, 0x3, 0x2, 0x2, 0x2, 0x4, 0x22, 
    0x3, 0x2, 0x2, 0x2, 0x6, 0x28, 0x3, 0x2, 0x2, 0x2, 0x8, 0x32, 0x3, 0x2, 
    0x2, 0x2, 0xa, 0x3d, 0x3, 0x2, 0x2, 0x2, 0xc, 0x40, 0x3, 0x2, 0x2, 0x2, 
    0xe, 0x48, 0x3, 0x2, 0x2, 0x2, 0x10, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x12, 
    0x53, 0x3, 0x2, 0x2, 0x2, 0x14, 0x57, 0x3, 0x2, 0x2, 0x2, 0x16, 0x5e, 
    0x3, 0x2, 0x2, 0x2, 0x18, 0x19, 0x7, 0x3, 0x2, 0x2, 0x19, 0x1d, 0x7, 
    0x4, 0x2, 0x2, 0x1a, 0x1c, 0x5, 0x4, 0x3, 0x2, 0x1b, 0x1a, 0x3, 0x2, 
    0x2, 0x2, 0x1c, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x1d, 0x1b, 0x3, 0x2, 0x2, 
    0x2, 0x1d, 0x1e, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x20, 0x3, 0x2, 0x2, 0x2, 
    0x1f, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x20, 0x21, 0x7, 0x5, 0x2, 0x2, 0x21, 
    0x3, 0x3, 0x2, 0x2, 0x2, 0x22, 0x23, 0x7, 0xd, 0x2, 0x2, 0x23, 0x24, 
    0x7, 0x4, 0x2, 0x2, 0x24, 0x25, 0x5, 0x6, 0x4, 0x2, 0x25, 0x26, 0x5, 
    0x8, 0x5, 0x2, 0x26, 0x27, 0x7, 0x5, 0x2, 0x2, 0x27, 0x5, 0x3, 0x2, 
    0x2, 0x2, 0x28, 0x29, 0x7, 0x6, 0x2, 0x2, 0x29, 0x2d, 0x7, 0x4, 0x2, 
    0x2, 0x2a, 0x2c, 0x5, 0x10, 0x9, 0x2, 0x2b, 0x2a, 0x3, 0x2, 0x2, 0x2, 
    0x2c, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x2d, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x2d, 
    0x2e, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x30, 0x3, 0x2, 0x2, 0x2, 0x2f, 0x2d, 
    0x3, 0x2, 0x2, 0x2, 0x30, 0x31, 0x7, 0x5, 0x2, 0x2, 0x31, 0x7, 0x3, 
    0x2, 0x2, 0x2, 0x32, 0x33, 0x7, 0x7, 0x2, 0x2, 0x33, 0x38, 0x7, 0x4, 
    0x2, 0x2, 0x34, 0x37, 0x5, 0x12, 0xa, 0x2, 0x35, 0x37, 0x5, 0x14, 0xb, 
    0x2, 0x36, 0x34, 0x3, 0x2, 0x2, 0x2, 0x36, 0x35, 0x3, 0x2, 0x2, 0x2, 
    0x37, 0x3a, 0x3, 0x2, 0x2, 0x2, 0x38, 0x36, 0x3, 0x2, 0x2, 0x2, 0x38, 
    0x39, 0x3, 0x2, 0x2, 0x2, 0x39, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x38, 
    0x3, 0x2, 0x2, 0x2, 0x3b, 0x3c, 0x7, 0x5, 0x2, 0x2, 0x3c, 0x9, 0x3, 
    0x2, 0x2, 0x2, 0x3d, 0x3e, 0x7, 0xb, 0x2, 0x2, 0x3e, 0x3f, 0x5, 0xe, 
    0x8, 0x2, 0x3f, 0xb, 0x3, 0x2, 0x2, 0x2, 0x40, 0x45, 0x9, 0x2, 0x2, 
    0x2, 0x41, 0x42, 0x7, 0xc, 0x2, 0x2, 0x42, 0x44, 0x9, 0x2, 0x2, 0x2, 
    0x43, 0x41, 0x3, 0x2, 0x2, 0x2, 0x44, 0x47, 0x3, 0x2, 0x2, 0x2, 0x45, 
    0x46, 0x3, 0x2, 0x2, 0x2, 0x45, 0x43, 0x3, 0x2, 0x2, 0x2, 0x46, 0xd, 
    0x3, 0x2, 0x2, 0x2, 0x47, 0x45, 0x3, 0x2, 0x2, 0x2, 0x48, 0x4c, 0x5, 
    0xc, 0x7, 0x2, 0x49, 0x4b, 0x5, 0xa, 0x6, 0x2, 0x4a, 0x49, 0x3, 0x2, 
    0x2, 0x2, 0x4b, 0x4e, 0x3, 0x2, 0x2, 0x2, 0x4c, 0x4d, 0x3, 0x2, 0x2, 
    0x2, 0x4c, 0x4a, 0x3, 0x2, 0x2, 0x2, 0x4d, 0xf, 0x3, 0x2, 0x2, 0x2, 
    0x4e, 0x4c, 0x3, 0x2, 0x2, 0x2, 0x4f, 0x50, 0x7, 0xd, 0x2, 0x2, 0x50, 
    0x51, 0x7, 0x9, 0x2, 0x2, 0x51, 0x52, 0x5, 0xe, 0x8, 0x2, 0x52, 0x11, 
    0x3, 0x2, 0x2, 0x2, 0x53, 0x54, 0x5, 0xe, 0x8, 0x2, 0x54, 0x55, 0x7, 
    0xa, 0x2, 0x2, 0x55, 0x56, 0x7, 0xe, 0x2, 0x2, 0x56, 0x13, 0x3, 0x2, 
    0x2, 0x2, 0x57, 0x58, 0x5, 0xe, 0x8, 0x2, 0x58, 0x59, 0x7, 0x8, 0x2, 
    0x2, 0x59, 0x5a, 0x7, 0xf, 0x2, 0x2, 0x5a, 0x15, 0x3, 0x2, 0x2, 0x2, 
    0x5b, 0x5f, 0x5, 0x10, 0x9, 0x2, 0x5c, 0x5f, 0x5, 0x12, 0xa, 0x2, 0x5d, 
    0x5f, 0x5, 0x14, 0xb, 0x2, 0x5e, 0x5b, 0x3, 0x2, 0x2, 0x2, 0x5e, 0x5c, 
    0x3, 0x2, 0x2, 0x2, 0x5e, 0x5d, 0x3, 0x2, 0x2, 0x2, 0x5f, 0x17, 0x3, 
    0x2, 0x2, 0x2, 0x9, 0x1d, 0x2d, 0x36, 0x38, 0x45, 0x4c, 0x5e, 
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
