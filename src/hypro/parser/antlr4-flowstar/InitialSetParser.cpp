
// Generated from InitialSet.g4 by ANTLR 4.7



#include "InitialSetParser.h"


using namespace antlrcpp;
using namespace antlr4;

InitialSetParser::InitialSetParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

InitialSetParser::~InitialSetParser() {
  delete _interpreter;
}

std::string InitialSetParser::getGrammarFileName() const {
  return "InitialSet.g4";
}

const std::vector<std::string>& InitialSetParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& InitialSetParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- InitContext ------------------------------------------------------------------

InitialSetParser::InitContext::InitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<InitialSetParser::InitstateContext *> InitialSetParser::InitContext::initstate() {
  return getRuleContexts<InitialSetParser::InitstateContext>();
}

InitialSetParser::InitstateContext* InitialSetParser::InitContext::initstate(size_t i) {
  return getRuleContext<InitialSetParser::InitstateContext>(i);
}


size_t InitialSetParser::InitContext::getRuleIndex() const {
  return InitialSetParser::RuleInit;
}


InitialSetParser::InitContext* InitialSetParser::init() {
  InitContext *_localctx = _tracker.createInstance<InitContext>(_ctx, getState());
  enterRule(_localctx, 0, InitialSetParser::RuleInit);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(20);
    match(InitialSetParser::T__0);
    setState(21);
    match(InitialSetParser::T__1);
    setState(23); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(22);
      initstate();
      setState(25); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == InitialSetParser::VARIABLE);
    setState(27);
    match(InitialSetParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InitstateContext ------------------------------------------------------------------

InitialSetParser::InitstateContext::InitstateContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* InitialSetParser::InitstateContext::VARIABLE() {
  return getToken(InitialSetParser::VARIABLE, 0);
}

InitialSetParser::ConstrsetContext* InitialSetParser::InitstateContext::constrset() {
  return getRuleContext<InitialSetParser::ConstrsetContext>(0);
}


size_t InitialSetParser::InitstateContext::getRuleIndex() const {
  return InitialSetParser::RuleInitstate;
}


InitialSetParser::InitstateContext* InitialSetParser::initstate() {
  InitstateContext *_localctx = _tracker.createInstance<InitstateContext>(_ctx, getState());
  enterRule(_localctx, 2, InitialSetParser::RuleInitstate);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(29);
    match(InitialSetParser::VARIABLE);
    setState(30);
    match(InitialSetParser::T__1);
    setState(31);
    constrset();
    setState(32);
    match(InitialSetParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConnectorContext ------------------------------------------------------------------

InitialSetParser::ConnectorContext::ConnectorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* InitialSetParser::ConnectorContext::PLUS() {
  return getToken(InitialSetParser::PLUS, 0);
}

tree::TerminalNode* InitialSetParser::ConnectorContext::MINUS() {
  return getToken(InitialSetParser::MINUS, 0);
}


size_t InitialSetParser::ConnectorContext::getRuleIndex() const {
  return InitialSetParser::RuleConnector;
}


InitialSetParser::ConnectorContext* InitialSetParser::connector() {
  ConnectorContext *_localctx = _tracker.createInstance<ConnectorContext>(_ctx, getState());
  enterRule(_localctx, 4, InitialSetParser::RuleConnector);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(34);
    _la = _input->LA(1);
    if (!(_la == InitialSetParser::PLUS

    || _la == InitialSetParser::MINUS)) {
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

InitialSetParser::TermContext::TermContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> InitialSetParser::TermContext::NUMBER() {
  return getTokens(InitialSetParser::NUMBER);
}

tree::TerminalNode* InitialSetParser::TermContext::NUMBER(size_t i) {
  return getToken(InitialSetParser::NUMBER, i);
}

std::vector<tree::TerminalNode *> InitialSetParser::TermContext::VARIABLE() {
  return getTokens(InitialSetParser::VARIABLE);
}

tree::TerminalNode* InitialSetParser::TermContext::VARIABLE(size_t i) {
  return getToken(InitialSetParser::VARIABLE, i);
}

std::vector<tree::TerminalNode *> InitialSetParser::TermContext::TIMES() {
  return getTokens(InitialSetParser::TIMES);
}

tree::TerminalNode* InitialSetParser::TermContext::TIMES(size_t i) {
  return getToken(InitialSetParser::TIMES, i);
}

std::vector<InitialSetParser::ConnectorContext *> InitialSetParser::TermContext::connector() {
  return getRuleContexts<InitialSetParser::ConnectorContext>();
}

InitialSetParser::ConnectorContext* InitialSetParser::TermContext::connector(size_t i) {
  return getRuleContext<InitialSetParser::ConnectorContext>(i);
}


size_t InitialSetParser::TermContext::getRuleIndex() const {
  return InitialSetParser::RuleTerm;
}


InitialSetParser::TermContext* InitialSetParser::term() {
  TermContext *_localctx = _tracker.createInstance<TermContext>(_ctx, getState());
  enterRule(_localctx, 6, InitialSetParser::RuleTerm);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(36);
    _la = _input->LA(1);
    if (!(_la == InitialSetParser::NUMBER

    || _la == InitialSetParser::VARIABLE)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(47);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == InitialSetParser::TIMES) {
      setState(37);
      match(InitialSetParser::TIMES);
      setState(41);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == InitialSetParser::PLUS

      || _la == InitialSetParser::MINUS) {
        setState(38);
        connector();
        setState(43);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(44);
      _la = _input->LA(1);
      if (!(_la == InitialSetParser::NUMBER

      || _la == InitialSetParser::VARIABLE)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(49);
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

InitialSetParser::PolynomContext::PolynomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<InitialSetParser::TermContext *> InitialSetParser::PolynomContext::term() {
  return getRuleContexts<InitialSetParser::TermContext>();
}

InitialSetParser::TermContext* InitialSetParser::PolynomContext::term(size_t i) {
  return getRuleContext<InitialSetParser::TermContext>(i);
}

std::vector<InitialSetParser::ConnectorContext *> InitialSetParser::PolynomContext::connector() {
  return getRuleContexts<InitialSetParser::ConnectorContext>();
}

InitialSetParser::ConnectorContext* InitialSetParser::PolynomContext::connector(size_t i) {
  return getRuleContext<InitialSetParser::ConnectorContext>(i);
}


size_t InitialSetParser::PolynomContext::getRuleIndex() const {
  return InitialSetParser::RulePolynom;
}


InitialSetParser::PolynomContext* InitialSetParser::polynom() {
  PolynomContext *_localctx = _tracker.createInstance<PolynomContext>(_ctx, getState());
  enterRule(_localctx, 8, InitialSetParser::RulePolynom);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(53);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == InitialSetParser::PLUS

    || _la == InitialSetParser::MINUS) {
      setState(50);
      connector();
      setState(55);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(56);
    term();
    setState(66);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(58); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(57);
          connector();
          setState(60); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == InitialSetParser::PLUS

        || _la == InitialSetParser::MINUS);
        setState(62);
        term(); 
      }
      setState(68);
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

//----------------- IntervalContext ------------------------------------------------------------------

InitialSetParser::IntervalContext::IntervalContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> InitialSetParser::IntervalContext::NUMBER() {
  return getTokens(InitialSetParser::NUMBER);
}

tree::TerminalNode* InitialSetParser::IntervalContext::NUMBER(size_t i) {
  return getToken(InitialSetParser::NUMBER, i);
}

std::vector<tree::TerminalNode *> InitialSetParser::IntervalContext::MINUS() {
  return getTokens(InitialSetParser::MINUS);
}

tree::TerminalNode* InitialSetParser::IntervalContext::MINUS(size_t i) {
  return getToken(InitialSetParser::MINUS, i);
}


size_t InitialSetParser::IntervalContext::getRuleIndex() const {
  return InitialSetParser::RuleInterval;
}


InitialSetParser::IntervalContext* InitialSetParser::interval() {
  IntervalContext *_localctx = _tracker.createInstance<IntervalContext>(_ctx, getState());
  enterRule(_localctx, 10, InitialSetParser::RuleInterval);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(69);
    match(InitialSetParser::T__3);
    setState(71);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == InitialSetParser::MINUS) {
      setState(70);
      match(InitialSetParser::MINUS);
    }
    setState(73);
    match(InitialSetParser::NUMBER);
    setState(74);
    match(InitialSetParser::T__4);
    setState(76);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == InitialSetParser::MINUS) {
      setState(75);
      match(InitialSetParser::MINUS);
    }
    setState(78);
    match(InitialSetParser::NUMBER);
    setState(79);
    match(InitialSetParser::T__5);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EquationContext ------------------------------------------------------------------

InitialSetParser::EquationContext::EquationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* InitialSetParser::EquationContext::VARIABLE() {
  return getToken(InitialSetParser::VARIABLE, 0);
}

tree::TerminalNode* InitialSetParser::EquationContext::EQUALS() {
  return getToken(InitialSetParser::EQUALS, 0);
}

InitialSetParser::PolynomContext* InitialSetParser::EquationContext::polynom() {
  return getRuleContext<InitialSetParser::PolynomContext>(0);
}

InitialSetParser::ConnectorContext* InitialSetParser::EquationContext::connector() {
  return getRuleContext<InitialSetParser::ConnectorContext>(0);
}

InitialSetParser::IntervalContext* InitialSetParser::EquationContext::interval() {
  return getRuleContext<InitialSetParser::IntervalContext>(0);
}


size_t InitialSetParser::EquationContext::getRuleIndex() const {
  return InitialSetParser::RuleEquation;
}


InitialSetParser::EquationContext* InitialSetParser::equation() {
  EquationContext *_localctx = _tracker.createInstance<EquationContext>(_ctx, getState());
  enterRule(_localctx, 12, InitialSetParser::RuleEquation);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(81);
    match(InitialSetParser::VARIABLE);
    setState(82);
    match(InitialSetParser::EQUALS);
    setState(83);
    polynom();
    setState(87);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == InitialSetParser::PLUS

    || _la == InitialSetParser::MINUS) {
      setState(84);
      connector();
      setState(85);
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

InitialSetParser::ConstraintContext::ConstraintContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<InitialSetParser::PolynomContext *> InitialSetParser::ConstraintContext::polynom() {
  return getRuleContexts<InitialSetParser::PolynomContext>();
}

InitialSetParser::PolynomContext* InitialSetParser::ConstraintContext::polynom(size_t i) {
  return getRuleContext<InitialSetParser::PolynomContext>(i);
}

tree::TerminalNode* InitialSetParser::ConstraintContext::BOOLRELATION() {
  return getToken(InitialSetParser::BOOLRELATION, 0);
}

tree::TerminalNode* InitialSetParser::ConstraintContext::EQUALS() {
  return getToken(InitialSetParser::EQUALS, 0);
}


size_t InitialSetParser::ConstraintContext::getRuleIndex() const {
  return InitialSetParser::RuleConstraint;
}


InitialSetParser::ConstraintContext* InitialSetParser::constraint() {
  ConstraintContext *_localctx = _tracker.createInstance<ConstraintContext>(_ctx, getState());
  enterRule(_localctx, 14, InitialSetParser::RuleConstraint);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(89);
    polynom();
    setState(90);
    _la = _input->LA(1);
    if (!(_la == InitialSetParser::EQUALS

    || _la == InitialSetParser::BOOLRELATION)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(91);
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

InitialSetParser::IntervalexprContext::IntervalexprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* InitialSetParser::IntervalexprContext::VARIABLE() {
  return getToken(InitialSetParser::VARIABLE, 0);
}

tree::TerminalNode* InitialSetParser::IntervalexprContext::IN() {
  return getToken(InitialSetParser::IN, 0);
}

InitialSetParser::IntervalContext* InitialSetParser::IntervalexprContext::interval() {
  return getRuleContext<InitialSetParser::IntervalContext>(0);
}


size_t InitialSetParser::IntervalexprContext::getRuleIndex() const {
  return InitialSetParser::RuleIntervalexpr;
}


InitialSetParser::IntervalexprContext* InitialSetParser::intervalexpr() {
  IntervalexprContext *_localctx = _tracker.createInstance<IntervalexprContext>(_ctx, getState());
  enterRule(_localctx, 16, InitialSetParser::RuleIntervalexpr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(93);
    match(InitialSetParser::VARIABLE);
    setState(94);
    match(InitialSetParser::IN);
    setState(95);
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

InitialSetParser::ConstrsetContext::ConstrsetContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<InitialSetParser::ConstraintContext *> InitialSetParser::ConstrsetContext::constraint() {
  return getRuleContexts<InitialSetParser::ConstraintContext>();
}

InitialSetParser::ConstraintContext* InitialSetParser::ConstrsetContext::constraint(size_t i) {
  return getRuleContext<InitialSetParser::ConstraintContext>(i);
}

std::vector<InitialSetParser::IntervalexprContext *> InitialSetParser::ConstrsetContext::intervalexpr() {
  return getRuleContexts<InitialSetParser::IntervalexprContext>();
}

InitialSetParser::IntervalexprContext* InitialSetParser::ConstrsetContext::intervalexpr(size_t i) {
  return getRuleContext<InitialSetParser::IntervalexprContext>(i);
}


size_t InitialSetParser::ConstrsetContext::getRuleIndex() const {
  return InitialSetParser::RuleConstrset;
}


InitialSetParser::ConstrsetContext* InitialSetParser::constrset() {
  ConstrsetContext *_localctx = _tracker.createInstance<ConstrsetContext>(_ctx, getState());
  enterRule(_localctx, 18, InitialSetParser::RuleConstrset);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(99); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(99);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
      case 1: {
        setState(97);
        constraint();
        break;
      }

      case 2: {
        setState(98);
        intervalexpr();
        break;
      }

      }
      setState(101); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << InitialSetParser::PLUS)
      | (1ULL << InitialSetParser::MINUS)
      | (1ULL << InitialSetParser::NUMBER)
      | (1ULL << InitialSetParser::VARIABLE))) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> InitialSetParser::_decisionToDFA;
atn::PredictionContextCache InitialSetParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN InitialSetParser::_atn;
std::vector<uint16_t> InitialSetParser::_serializedATN;

std::vector<std::string> InitialSetParser::_ruleNames = {
  "init", "initstate", "connector", "term", "polynom", "interval", "equation", 
  "constraint", "intervalexpr", "constrset"
};

std::vector<std::string> InitialSetParser::_literalNames = {
  "", "'init'", "'{'", "'}'", "'['", "','", "']'", "'in'", "", "'='", "", 
  "'+'", "'-'", "'*'"
};

std::vector<std::string> InitialSetParser::_symbolicNames = {
  "", "", "", "", "", "", "", "IN", "COMMENT", "EQUALS", "BOOLRELATION", 
  "PLUS", "MINUS", "TIMES", "NUMBER", "VARIABLE", "WS"
};

dfa::Vocabulary InitialSetParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> InitialSetParser::_tokenNames;

InitialSetParser::Initializer::Initializer() {
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
    0x3, 0x12, 0x6a, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x6, 0x2, 0x1a, 0xa, 0x2, 0xd, 0x2, 
    0xe, 0x2, 0x1b, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x7, 
    0x5, 0x2a, 0xa, 0x5, 0xc, 0x5, 0xe, 0x5, 0x2d, 0xb, 0x5, 0x3, 0x5, 0x7, 
    0x5, 0x30, 0xa, 0x5, 0xc, 0x5, 0xe, 0x5, 0x33, 0xb, 0x5, 0x3, 0x6, 0x7, 
    0x6, 0x36, 0xa, 0x6, 0xc, 0x6, 0xe, 0x6, 0x39, 0xb, 0x6, 0x3, 0x6, 0x3, 
    0x6, 0x6, 0x6, 0x3d, 0xa, 0x6, 0xd, 0x6, 0xe, 0x6, 0x3e, 0x3, 0x6, 0x3, 
    0x6, 0x7, 0x6, 0x43, 0xa, 0x6, 0xc, 0x6, 0xe, 0x6, 0x46, 0xb, 0x6, 0x3, 
    0x7, 0x3, 0x7, 0x5, 0x7, 0x4a, 0xa, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 
    0x5, 0x7, 0x4f, 0xa, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 
    0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x5, 0x8, 0x5a, 0xa, 0x8, 
    0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 
    0x3, 0xa, 0x3, 0xb, 0x3, 0xb, 0x6, 0xb, 0x66, 0xa, 0xb, 0xd, 0xb, 0xe, 
    0xb, 0x67, 0x3, 0xb, 0x2, 0x2, 0xc, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 
    0x10, 0x12, 0x14, 0x2, 0x5, 0x3, 0x2, 0xd, 0xe, 0x3, 0x2, 0x10, 0x11, 
    0x3, 0x2, 0xb, 0xc, 0x2, 0x6a, 0x2, 0x16, 0x3, 0x2, 0x2, 0x2, 0x4, 0x1f, 
    0x3, 0x2, 0x2, 0x2, 0x6, 0x24, 0x3, 0x2, 0x2, 0x2, 0x8, 0x26, 0x3, 0x2, 
    0x2, 0x2, 0xa, 0x37, 0x3, 0x2, 0x2, 0x2, 0xc, 0x47, 0x3, 0x2, 0x2, 0x2, 
    0xe, 0x53, 0x3, 0x2, 0x2, 0x2, 0x10, 0x5b, 0x3, 0x2, 0x2, 0x2, 0x12, 
    0x5f, 0x3, 0x2, 0x2, 0x2, 0x14, 0x65, 0x3, 0x2, 0x2, 0x2, 0x16, 0x17, 
    0x7, 0x3, 0x2, 0x2, 0x17, 0x19, 0x7, 0x4, 0x2, 0x2, 0x18, 0x1a, 0x5, 
    0x4, 0x3, 0x2, 0x19, 0x18, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x1b, 0x3, 0x2, 
    0x2, 0x2, 0x1b, 0x19, 0x3, 0x2, 0x2, 0x2, 0x1b, 0x1c, 0x3, 0x2, 0x2, 
    0x2, 0x1c, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x1d, 0x1e, 0x7, 0x5, 0x2, 0x2, 
    0x1e, 0x3, 0x3, 0x2, 0x2, 0x2, 0x1f, 0x20, 0x7, 0x11, 0x2, 0x2, 0x20, 
    0x21, 0x7, 0x4, 0x2, 0x2, 0x21, 0x22, 0x5, 0x14, 0xb, 0x2, 0x22, 0x23, 
    0x7, 0x5, 0x2, 0x2, 0x23, 0x5, 0x3, 0x2, 0x2, 0x2, 0x24, 0x25, 0x9, 
    0x2, 0x2, 0x2, 0x25, 0x7, 0x3, 0x2, 0x2, 0x2, 0x26, 0x31, 0x9, 0x3, 
    0x2, 0x2, 0x27, 0x2b, 0x7, 0xf, 0x2, 0x2, 0x28, 0x2a, 0x5, 0x6, 0x4, 
    0x2, 0x29, 0x28, 0x3, 0x2, 0x2, 0x2, 0x2a, 0x2d, 0x3, 0x2, 0x2, 0x2, 
    0x2b, 0x29, 0x3, 0x2, 0x2, 0x2, 0x2b, 0x2c, 0x3, 0x2, 0x2, 0x2, 0x2c, 
    0x2e, 0x3, 0x2, 0x2, 0x2, 0x2d, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x30, 
    0x9, 0x3, 0x2, 0x2, 0x2f, 0x27, 0x3, 0x2, 0x2, 0x2, 0x30, 0x33, 0x3, 
    0x2, 0x2, 0x2, 0x31, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x31, 0x32, 0x3, 0x2, 
    0x2, 0x2, 0x32, 0x9, 0x3, 0x2, 0x2, 0x2, 0x33, 0x31, 0x3, 0x2, 0x2, 
    0x2, 0x34, 0x36, 0x5, 0x6, 0x4, 0x2, 0x35, 0x34, 0x3, 0x2, 0x2, 0x2, 
    0x36, 0x39, 0x3, 0x2, 0x2, 0x2, 0x37, 0x35, 0x3, 0x2, 0x2, 0x2, 0x37, 
    0x38, 0x3, 0x2, 0x2, 0x2, 0x38, 0x3a, 0x3, 0x2, 0x2, 0x2, 0x39, 0x37, 
    0x3, 0x2, 0x2, 0x2, 0x3a, 0x44, 0x5, 0x8, 0x5, 0x2, 0x3b, 0x3d, 0x5, 
    0x6, 0x4, 0x2, 0x3c, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x3d, 0x3e, 0x3, 0x2, 
    0x2, 0x2, 0x3e, 0x3c, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x3f, 0x3, 0x2, 0x2, 
    0x2, 0x3f, 0x40, 0x3, 0x2, 0x2, 0x2, 0x40, 0x41, 0x5, 0x8, 0x5, 0x2, 
    0x41, 0x43, 0x3, 0x2, 0x2, 0x2, 0x42, 0x3c, 0x3, 0x2, 0x2, 0x2, 0x43, 
    0x46, 0x3, 0x2, 0x2, 0x2, 0x44, 0x42, 0x3, 0x2, 0x2, 0x2, 0x44, 0x45, 
    0x3, 0x2, 0x2, 0x2, 0x45, 0xb, 0x3, 0x2, 0x2, 0x2, 0x46, 0x44, 0x3, 
    0x2, 0x2, 0x2, 0x47, 0x49, 0x7, 0x6, 0x2, 0x2, 0x48, 0x4a, 0x7, 0xe, 
    0x2, 0x2, 0x49, 0x48, 0x3, 0x2, 0x2, 0x2, 0x49, 0x4a, 0x3, 0x2, 0x2, 
    0x2, 0x4a, 0x4b, 0x3, 0x2, 0x2, 0x2, 0x4b, 0x4c, 0x7, 0x10, 0x2, 0x2, 
    0x4c, 0x4e, 0x7, 0x7, 0x2, 0x2, 0x4d, 0x4f, 0x7, 0xe, 0x2, 0x2, 0x4e, 
    0x4d, 0x3, 0x2, 0x2, 0x2, 0x4e, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x4f, 0x50, 
    0x3, 0x2, 0x2, 0x2, 0x50, 0x51, 0x7, 0x10, 0x2, 0x2, 0x51, 0x52, 0x7, 
    0x8, 0x2, 0x2, 0x52, 0xd, 0x3, 0x2, 0x2, 0x2, 0x53, 0x54, 0x7, 0x11, 
    0x2, 0x2, 0x54, 0x55, 0x7, 0xb, 0x2, 0x2, 0x55, 0x59, 0x5, 0xa, 0x6, 
    0x2, 0x56, 0x57, 0x5, 0x6, 0x4, 0x2, 0x57, 0x58, 0x5, 0xc, 0x7, 0x2, 
    0x58, 0x5a, 0x3, 0x2, 0x2, 0x2, 0x59, 0x56, 0x3, 0x2, 0x2, 0x2, 0x59, 
    0x5a, 0x3, 0x2, 0x2, 0x2, 0x5a, 0xf, 0x3, 0x2, 0x2, 0x2, 0x5b, 0x5c, 
    0x5, 0xa, 0x6, 0x2, 0x5c, 0x5d, 0x9, 0x4, 0x2, 0x2, 0x5d, 0x5e, 0x5, 
    0xa, 0x6, 0x2, 0x5e, 0x11, 0x3, 0x2, 0x2, 0x2, 0x5f, 0x60, 0x7, 0x11, 
    0x2, 0x2, 0x60, 0x61, 0x7, 0x9, 0x2, 0x2, 0x61, 0x62, 0x5, 0xc, 0x7, 
    0x2, 0x62, 0x13, 0x3, 0x2, 0x2, 0x2, 0x63, 0x66, 0x5, 0x10, 0x9, 0x2, 
    0x64, 0x66, 0x5, 0x12, 0xa, 0x2, 0x65, 0x63, 0x3, 0x2, 0x2, 0x2, 0x65, 
    0x64, 0x3, 0x2, 0x2, 0x2, 0x66, 0x67, 0x3, 0x2, 0x2, 0x2, 0x67, 0x65, 
    0x3, 0x2, 0x2, 0x2, 0x67, 0x68, 0x3, 0x2, 0x2, 0x2, 0x68, 0x15, 0x3, 
    0x2, 0x2, 0x2, 0xd, 0x1b, 0x2b, 0x31, 0x37, 0x3e, 0x44, 0x49, 0x4e, 
    0x59, 0x65, 0x67, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

InitialSetParser::Initializer InitialSetParser::_init;
