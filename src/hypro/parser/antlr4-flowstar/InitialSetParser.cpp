
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

InitialSetParser::InitstateContext* InitialSetParser::InitContext::initstate() {
  return getRuleContext<InitialSetParser::InitstateContext>(0);
}


size_t InitialSetParser::InitContext::getRuleIndex() const {
  return InitialSetParser::RuleInit;
}


InitialSetParser::InitContext* InitialSetParser::init() {
  InitContext *_localctx = _tracker.createInstance<InitContext>(_ctx, getState());
  enterRule(_localctx, 0, InitialSetParser::RuleInit);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(18);
    match(InitialSetParser::T__0);
    setState(19);
    match(InitialSetParser::T__1);
    setState(20);
    initstate();
    setState(21);
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
    setState(23);
    match(InitialSetParser::VARIABLE);
    setState(24);
    match(InitialSetParser::T__1);
    setState(25);
    constrset();
    setState(26);
    match(InitialSetParser::T__2);
   
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


size_t InitialSetParser::TermContext::getRuleIndex() const {
  return InitialSetParser::RuleTerm;
}


InitialSetParser::TermContext* InitialSetParser::term() {
  TermContext *_localctx = _tracker.createInstance<TermContext>(_ctx, getState());
  enterRule(_localctx, 4, InitialSetParser::RuleTerm);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(28);
    _la = _input->LA(1);
    if (!(_la == InitialSetParser::NUMBER

    || _la == InitialSetParser::VARIABLE)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(33);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == InitialSetParser::TIMES) {
      setState(29);
      match(InitialSetParser::TIMES);
      setState(30);
      _la = _input->LA(1);
      if (!(_la == InitialSetParser::NUMBER

      || _la == InitialSetParser::VARIABLE)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(35);
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

std::vector<tree::TerminalNode *> InitialSetParser::PolynomContext::PLUS() {
  return getTokens(InitialSetParser::PLUS);
}

tree::TerminalNode* InitialSetParser::PolynomContext::PLUS(size_t i) {
  return getToken(InitialSetParser::PLUS, i);
}


size_t InitialSetParser::PolynomContext::getRuleIndex() const {
  return InitialSetParser::RulePolynom;
}


InitialSetParser::PolynomContext* InitialSetParser::polynom() {
  PolynomContext *_localctx = _tracker.createInstance<PolynomContext>(_ctx, getState());
  enterRule(_localctx, 6, InitialSetParser::RulePolynom);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(36);
    term();
    setState(41);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == InitialSetParser::PLUS) {
      setState(37);
      match(InitialSetParser::PLUS);
      setState(38);
      term();
      setState(43);
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

InitialSetParser::IntervalContext::IntervalContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> InitialSetParser::IntervalContext::NUMBER() {
  return getTokens(InitialSetParser::NUMBER);
}

tree::TerminalNode* InitialSetParser::IntervalContext::NUMBER(size_t i) {
  return getToken(InitialSetParser::NUMBER, i);
}


size_t InitialSetParser::IntervalContext::getRuleIndex() const {
  return InitialSetParser::RuleInterval;
}


InitialSetParser::IntervalContext* InitialSetParser::interval() {
  IntervalContext *_localctx = _tracker.createInstance<IntervalContext>(_ctx, getState());
  enterRule(_localctx, 8, InitialSetParser::RuleInterval);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(44);
    match(InitialSetParser::T__3);
    setState(45);
    match(InitialSetParser::NUMBER);
    setState(46);
    match(InitialSetParser::T__4);
    setState(47);
    match(InitialSetParser::NUMBER);
    setState(48);
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


size_t InitialSetParser::EquationContext::getRuleIndex() const {
  return InitialSetParser::RuleEquation;
}


InitialSetParser::EquationContext* InitialSetParser::equation() {
  EquationContext *_localctx = _tracker.createInstance<EquationContext>(_ctx, getState());
  enterRule(_localctx, 10, InitialSetParser::RuleEquation);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(50);
    match(InitialSetParser::VARIABLE);
    setState(51);
    match(InitialSetParser::EQUALS);
    setState(52);
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
  enterRule(_localctx, 12, InitialSetParser::RuleConstraint);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(54);
    polynom();
    setState(55);
    _la = _input->LA(1);
    if (!(_la == InitialSetParser::EQUALS

    || _la == InitialSetParser::BOOLRELATION)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(56);
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
  enterRule(_localctx, 14, InitialSetParser::RuleIntervalexpr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(58);
    match(InitialSetParser::VARIABLE);
    setState(59);
    match(InitialSetParser::IN);
    setState(60);
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
  enterRule(_localctx, 16, InitialSetParser::RuleConstrset);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(66);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == InitialSetParser::NUMBER

    || _la == InitialSetParser::VARIABLE) {
      setState(64);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
      case 1: {
        setState(62);
        constraint();
        break;
      }

      case 2: {
        setState(63);
        intervalexpr();
        break;
      }

      }
      setState(68);
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
std::vector<dfa::DFA> InitialSetParser::_decisionToDFA;
atn::PredictionContextCache InitialSetParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN InitialSetParser::_atn;
std::vector<uint16_t> InitialSetParser::_serializedATN;

std::vector<std::string> InitialSetParser::_ruleNames = {
  "init", "initstate", "term", "polynom", "interval", "equation", "constraint", 
  "intervalexpr", "constrset"
};

std::vector<std::string> InitialSetParser::_literalNames = {
  "", "'init'", "'{'", "'}'", "'['", "','", "']'", "'in'", "", "'='", "", 
  "'+'", "'*'"
};

std::vector<std::string> InitialSetParser::_symbolicNames = {
  "", "", "", "", "", "", "", "IN", "COMMENT", "EQUALS", "BOOLRELATION", 
  "PLUS", "TIMES", "NUMBER", "VARIABLE", "WS"
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
    0x3, 0x11, 0x48, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x3, 0x2, 0x3, 
    0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x7, 0x4, 0x22, 0xa, 0x4, 
    0xc, 0x4, 0xe, 0x4, 0x25, 0xb, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x7, 
    0x5, 0x2a, 0xa, 0x5, 0xc, 0x5, 0xe, 0x5, 0x2d, 0xb, 0x5, 0x3, 0x6, 0x3, 
    0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 
    0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x9, 0x3, 
    0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0xa, 0x3, 0xa, 0x7, 0xa, 0x43, 0xa, 0xa, 
    0xc, 0xa, 0xe, 0xa, 0x46, 0xb, 0xa, 0x3, 0xa, 0x2, 0x2, 0xb, 0x2, 0x4, 
    0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x2, 0x4, 0x3, 0x2, 0xf, 0x10, 
    0x3, 0x2, 0xb, 0xc, 0x2, 0x42, 0x2, 0x14, 0x3, 0x2, 0x2, 0x2, 0x4, 0x19, 
    0x3, 0x2, 0x2, 0x2, 0x6, 0x1e, 0x3, 0x2, 0x2, 0x2, 0x8, 0x26, 0x3, 0x2, 
    0x2, 0x2, 0xa, 0x2e, 0x3, 0x2, 0x2, 0x2, 0xc, 0x34, 0x3, 0x2, 0x2, 0x2, 
    0xe, 0x38, 0x3, 0x2, 0x2, 0x2, 0x10, 0x3c, 0x3, 0x2, 0x2, 0x2, 0x12, 
    0x44, 0x3, 0x2, 0x2, 0x2, 0x14, 0x15, 0x7, 0x3, 0x2, 0x2, 0x15, 0x16, 
    0x7, 0x4, 0x2, 0x2, 0x16, 0x17, 0x5, 0x4, 0x3, 0x2, 0x17, 0x18, 0x7, 
    0x5, 0x2, 0x2, 0x18, 0x3, 0x3, 0x2, 0x2, 0x2, 0x19, 0x1a, 0x7, 0x10, 
    0x2, 0x2, 0x1a, 0x1b, 0x7, 0x4, 0x2, 0x2, 0x1b, 0x1c, 0x5, 0x12, 0xa, 
    0x2, 0x1c, 0x1d, 0x7, 0x5, 0x2, 0x2, 0x1d, 0x5, 0x3, 0x2, 0x2, 0x2, 
    0x1e, 0x23, 0x9, 0x2, 0x2, 0x2, 0x1f, 0x20, 0x7, 0xe, 0x2, 0x2, 0x20, 
    0x22, 0x9, 0x2, 0x2, 0x2, 0x21, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x22, 0x25, 
    0x3, 0x2, 0x2, 0x2, 0x23, 0x21, 0x3, 0x2, 0x2, 0x2, 0x23, 0x24, 0x3, 
    0x2, 0x2, 0x2, 0x24, 0x7, 0x3, 0x2, 0x2, 0x2, 0x25, 0x23, 0x3, 0x2, 
    0x2, 0x2, 0x26, 0x2b, 0x5, 0x6, 0x4, 0x2, 0x27, 0x28, 0x7, 0xd, 0x2, 
    0x2, 0x28, 0x2a, 0x5, 0x6, 0x4, 0x2, 0x29, 0x27, 0x3, 0x2, 0x2, 0x2, 
    0x2a, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x2b, 0x29, 0x3, 0x2, 0x2, 0x2, 0x2b, 
    0x2c, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x9, 0x3, 0x2, 0x2, 0x2, 0x2d, 0x2b, 
    0x3, 0x2, 0x2, 0x2, 0x2e, 0x2f, 0x7, 0x6, 0x2, 0x2, 0x2f, 0x30, 0x7, 
    0xf, 0x2, 0x2, 0x30, 0x31, 0x7, 0x7, 0x2, 0x2, 0x31, 0x32, 0x7, 0xf, 
    0x2, 0x2, 0x32, 0x33, 0x7, 0x8, 0x2, 0x2, 0x33, 0xb, 0x3, 0x2, 0x2, 
    0x2, 0x34, 0x35, 0x7, 0x10, 0x2, 0x2, 0x35, 0x36, 0x7, 0xb, 0x2, 0x2, 
    0x36, 0x37, 0x5, 0x8, 0x5, 0x2, 0x37, 0xd, 0x3, 0x2, 0x2, 0x2, 0x38, 
    0x39, 0x5, 0x8, 0x5, 0x2, 0x39, 0x3a, 0x9, 0x3, 0x2, 0x2, 0x3a, 0x3b, 
    0x5, 0x8, 0x5, 0x2, 0x3b, 0xf, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x3d, 0x7, 
    0x10, 0x2, 0x2, 0x3d, 0x3e, 0x7, 0x9, 0x2, 0x2, 0x3e, 0x3f, 0x5, 0xa, 
    0x6, 0x2, 0x3f, 0x11, 0x3, 0x2, 0x2, 0x2, 0x40, 0x43, 0x5, 0xe, 0x8, 
    0x2, 0x41, 0x43, 0x5, 0x10, 0x9, 0x2, 0x42, 0x40, 0x3, 0x2, 0x2, 0x2, 
    0x42, 0x41, 0x3, 0x2, 0x2, 0x2, 0x43, 0x46, 0x3, 0x2, 0x2, 0x2, 0x44, 
    0x42, 0x3, 0x2, 0x2, 0x2, 0x44, 0x45, 0x3, 0x2, 0x2, 0x2, 0x45, 0x13, 
    0x3, 0x2, 0x2, 0x2, 0x46, 0x44, 0x3, 0x2, 0x2, 0x2, 0x6, 0x23, 0x2b, 
    0x42, 0x44, 
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
