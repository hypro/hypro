
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


//----------------- ConnectorContext ------------------------------------------------------------------

FormulaParser::ConnectorContext::ConnectorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* FormulaParser::ConnectorContext::PLUS() {
  return getToken(FormulaParser::PLUS, 0);
}

tree::TerminalNode* FormulaParser::ConnectorContext::MINUS() {
  return getToken(FormulaParser::MINUS, 0);
}


size_t FormulaParser::ConnectorContext::getRuleIndex() const {
  return FormulaParser::RuleConnector;
}


FormulaParser::ConnectorContext* FormulaParser::connector() {
  ConnectorContext *_localctx = _tracker.createInstance<ConnectorContext>(_ctx, getState());
  enterRule(_localctx, 0, FormulaParser::RuleConnector);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(16);
    _la = _input->LA(1);
    if (!(_la == FormulaParser::PLUS

    || _la == FormulaParser::MINUS)) {
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

std::vector<FormulaParser::ConnectorContext *> FormulaParser::TermContext::connector() {
  return getRuleContexts<FormulaParser::ConnectorContext>();
}

FormulaParser::ConnectorContext* FormulaParser::TermContext::connector(size_t i) {
  return getRuleContext<FormulaParser::ConnectorContext>(i);
}


size_t FormulaParser::TermContext::getRuleIndex() const {
  return FormulaParser::RuleTerm;
}


FormulaParser::TermContext* FormulaParser::term() {
  TermContext *_localctx = _tracker.createInstance<TermContext>(_ctx, getState());
  enterRule(_localctx, 2, FormulaParser::RuleTerm);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(18);
    _la = _input->LA(1);
    if (!(_la == FormulaParser::NUMBER

    || _la == FormulaParser::VARIABLE)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(29);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == FormulaParser::TIMES) {
      setState(19);
      match(FormulaParser::TIMES);
      setState(23);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == FormulaParser::PLUS

      || _la == FormulaParser::MINUS) {
        setState(20);
        connector();
        setState(25);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(26);
      _la = _input->LA(1);
      if (!(_la == FormulaParser::NUMBER

      || _la == FormulaParser::VARIABLE)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(31);
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

std::vector<FormulaParser::ConnectorContext *> FormulaParser::PolynomContext::connector() {
  return getRuleContexts<FormulaParser::ConnectorContext>();
}

FormulaParser::ConnectorContext* FormulaParser::PolynomContext::connector(size_t i) {
  return getRuleContext<FormulaParser::ConnectorContext>(i);
}


size_t FormulaParser::PolynomContext::getRuleIndex() const {
  return FormulaParser::RulePolynom;
}


FormulaParser::PolynomContext* FormulaParser::polynom() {
  PolynomContext *_localctx = _tracker.createInstance<PolynomContext>(_ctx, getState());
  enterRule(_localctx, 4, FormulaParser::RulePolynom);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(35);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == FormulaParser::PLUS

    || _la == FormulaParser::MINUS) {
      setState(32);
      connector();
      setState(37);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(38);
    term();
    setState(48);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(40); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(39);
          connector();
          setState(42); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == FormulaParser::PLUS

        || _la == FormulaParser::MINUS);
        setState(44);
        term(); 
      }
      setState(50);
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

std::vector<tree::TerminalNode *> FormulaParser::IntervalContext::MINUS() {
  return getTokens(FormulaParser::MINUS);
}

tree::TerminalNode* FormulaParser::IntervalContext::MINUS(size_t i) {
  return getToken(FormulaParser::MINUS, i);
}


size_t FormulaParser::IntervalContext::getRuleIndex() const {
  return FormulaParser::RuleInterval;
}


FormulaParser::IntervalContext* FormulaParser::interval() {
  IntervalContext *_localctx = _tracker.createInstance<IntervalContext>(_ctx, getState());
  enterRule(_localctx, 6, FormulaParser::RuleInterval);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(51);
    match(FormulaParser::T__0);
    setState(53);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == FormulaParser::MINUS) {
      setState(52);
      match(FormulaParser::MINUS);
    }
    setState(55);
    match(FormulaParser::NUMBER);
    setState(56);
    match(FormulaParser::T__1);
    setState(58);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == FormulaParser::MINUS) {
      setState(57);
      match(FormulaParser::MINUS);
    }
    setState(60);
    match(FormulaParser::NUMBER);
    setState(61);
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
  enterRule(_localctx, 8, FormulaParser::RuleEquation);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(63);
    match(FormulaParser::VARIABLE);
    setState(64);
    match(FormulaParser::EQUALS);
    setState(65);
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
  enterRule(_localctx, 10, FormulaParser::RuleConstraint);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(67);
    polynom();
    setState(68);
    _la = _input->LA(1);
    if (!(_la == FormulaParser::EQUALS

    || _la == FormulaParser::BOOLRELATION)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(69);
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
  enterRule(_localctx, 12, FormulaParser::RuleIntervalexpr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(71);
    match(FormulaParser::VARIABLE);
    setState(72);
    match(FormulaParser::IN);
    setState(73);
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
  enterRule(_localctx, 14, FormulaParser::RuleConstrset);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(77); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(77);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
      case 1: {
        setState(75);
        constraint();
        break;
      }

      case 2: {
        setState(76);
        intervalexpr();
        break;
      }

      }
      setState(79); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << FormulaParser::PLUS)
      | (1ULL << FormulaParser::MINUS)
      | (1ULL << FormulaParser::NUMBER)
      | (1ULL << FormulaParser::VARIABLE))) != 0));
   
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
  "connector", "term", "polynom", "interval", "equation", "constraint", 
  "intervalexpr", "constrset"
};

std::vector<std::string> FormulaParser::_literalNames = {
  "", "'['", "','", "']'", "'in'", "", "'='", "", "'+'", "'-'", "'*'"
};

std::vector<std::string> FormulaParser::_symbolicNames = {
  "", "", "", "", "IN", "COMMENT", "EQUALS", "BOOLRELATION", "PLUS", "MINUS", 
  "TIMES", "NUMBER", "VARIABLE", "WS"
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
    0x3, 0xf, 0x54, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x7, 0x3, 0x18, 0xa, 0x3, 0xc, 0x3, 0xe, 0x3, 0x1b, 0xb, 
    0x3, 0x3, 0x3, 0x7, 0x3, 0x1e, 0xa, 0x3, 0xc, 0x3, 0xe, 0x3, 0x21, 0xb, 
    0x3, 0x3, 0x4, 0x7, 0x4, 0x24, 0xa, 0x4, 0xc, 0x4, 0xe, 0x4, 0x27, 0xb, 
    0x4, 0x3, 0x4, 0x3, 0x4, 0x6, 0x4, 0x2b, 0xa, 0x4, 0xd, 0x4, 0xe, 0x4, 
    0x2c, 0x3, 0x4, 0x3, 0x4, 0x7, 0x4, 0x31, 0xa, 0x4, 0xc, 0x4, 0xe, 0x4, 
    0x34, 0xb, 0x4, 0x3, 0x5, 0x3, 0x5, 0x5, 0x5, 0x38, 0xa, 0x5, 0x3, 0x5, 
    0x3, 0x5, 0x3, 0x5, 0x5, 0x5, 0x3d, 0xa, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 
    0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 
    0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x9, 0x3, 
    0x9, 0x6, 0x9, 0x50, 0xa, 0x9, 0xd, 0x9, 0xe, 0x9, 0x51, 0x3, 0x9, 0x2, 
    0x2, 0xa, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x2, 0x5, 0x3, 0x2, 
    0xa, 0xb, 0x3, 0x2, 0xd, 0xe, 0x3, 0x2, 0x8, 0x9, 0x2, 0x54, 0x2, 0x12, 
    0x3, 0x2, 0x2, 0x2, 0x4, 0x14, 0x3, 0x2, 0x2, 0x2, 0x6, 0x25, 0x3, 0x2, 
    0x2, 0x2, 0x8, 0x35, 0x3, 0x2, 0x2, 0x2, 0xa, 0x41, 0x3, 0x2, 0x2, 0x2, 
    0xc, 0x45, 0x3, 0x2, 0x2, 0x2, 0xe, 0x49, 0x3, 0x2, 0x2, 0x2, 0x10, 
    0x4f, 0x3, 0x2, 0x2, 0x2, 0x12, 0x13, 0x9, 0x2, 0x2, 0x2, 0x13, 0x3, 
    0x3, 0x2, 0x2, 0x2, 0x14, 0x1f, 0x9, 0x3, 0x2, 0x2, 0x15, 0x19, 0x7, 
    0xc, 0x2, 0x2, 0x16, 0x18, 0x5, 0x2, 0x2, 0x2, 0x17, 0x16, 0x3, 0x2, 
    0x2, 0x2, 0x18, 0x1b, 0x3, 0x2, 0x2, 0x2, 0x19, 0x17, 0x3, 0x2, 0x2, 
    0x2, 0x19, 0x1a, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x1c, 0x3, 0x2, 0x2, 0x2, 
    0x1b, 0x19, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x1e, 0x9, 0x3, 0x2, 0x2, 0x1d, 
    0x15, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x21, 0x3, 0x2, 0x2, 0x2, 0x1f, 0x1d, 
    0x3, 0x2, 0x2, 0x2, 0x1f, 0x20, 0x3, 0x2, 0x2, 0x2, 0x20, 0x5, 0x3, 
    0x2, 0x2, 0x2, 0x21, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x22, 0x24, 0x5, 0x2, 
    0x2, 0x2, 0x23, 0x22, 0x3, 0x2, 0x2, 0x2, 0x24, 0x27, 0x3, 0x2, 0x2, 
    0x2, 0x25, 0x23, 0x3, 0x2, 0x2, 0x2, 0x25, 0x26, 0x3, 0x2, 0x2, 0x2, 
    0x26, 0x28, 0x3, 0x2, 0x2, 0x2, 0x27, 0x25, 0x3, 0x2, 0x2, 0x2, 0x28, 
    0x32, 0x5, 0x4, 0x3, 0x2, 0x29, 0x2b, 0x5, 0x2, 0x2, 0x2, 0x2a, 0x29, 
    0x3, 0x2, 0x2, 0x2, 0x2b, 0x2c, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x2a, 0x3, 
    0x2, 0x2, 0x2, 0x2c, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x2d, 0x2e, 0x3, 0x2, 
    0x2, 0x2, 0x2e, 0x2f, 0x5, 0x4, 0x3, 0x2, 0x2f, 0x31, 0x3, 0x2, 0x2, 
    0x2, 0x30, 0x2a, 0x3, 0x2, 0x2, 0x2, 0x31, 0x34, 0x3, 0x2, 0x2, 0x2, 
    0x32, 0x30, 0x3, 0x2, 0x2, 0x2, 0x32, 0x33, 0x3, 0x2, 0x2, 0x2, 0x33, 
    0x7, 0x3, 0x2, 0x2, 0x2, 0x34, 0x32, 0x3, 0x2, 0x2, 0x2, 0x35, 0x37, 
    0x7, 0x3, 0x2, 0x2, 0x36, 0x38, 0x7, 0xb, 0x2, 0x2, 0x37, 0x36, 0x3, 
    0x2, 0x2, 0x2, 0x37, 0x38, 0x3, 0x2, 0x2, 0x2, 0x38, 0x39, 0x3, 0x2, 
    0x2, 0x2, 0x39, 0x3a, 0x7, 0xd, 0x2, 0x2, 0x3a, 0x3c, 0x7, 0x4, 0x2, 
    0x2, 0x3b, 0x3d, 0x7, 0xb, 0x2, 0x2, 0x3c, 0x3b, 0x3, 0x2, 0x2, 0x2, 
    0x3c, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x3d, 0x3e, 0x3, 0x2, 0x2, 0x2, 0x3e, 
    0x3f, 0x7, 0xd, 0x2, 0x2, 0x3f, 0x40, 0x7, 0x5, 0x2, 0x2, 0x40, 0x9, 
    0x3, 0x2, 0x2, 0x2, 0x41, 0x42, 0x7, 0xe, 0x2, 0x2, 0x42, 0x43, 0x7, 
    0x8, 0x2, 0x2, 0x43, 0x44, 0x5, 0x6, 0x4, 0x2, 0x44, 0xb, 0x3, 0x2, 
    0x2, 0x2, 0x45, 0x46, 0x5, 0x6, 0x4, 0x2, 0x46, 0x47, 0x9, 0x4, 0x2, 
    0x2, 0x47, 0x48, 0x5, 0x6, 0x4, 0x2, 0x48, 0xd, 0x3, 0x2, 0x2, 0x2, 
    0x49, 0x4a, 0x7, 0xe, 0x2, 0x2, 0x4a, 0x4b, 0x7, 0x6, 0x2, 0x2, 0x4b, 
    0x4c, 0x5, 0x8, 0x5, 0x2, 0x4c, 0xf, 0x3, 0x2, 0x2, 0x2, 0x4d, 0x50, 
    0x5, 0xc, 0x7, 0x2, 0x4e, 0x50, 0x5, 0xe, 0x8, 0x2, 0x4f, 0x4d, 0x3, 
    0x2, 0x2, 0x2, 0x4f, 0x4e, 0x3, 0x2, 0x2, 0x2, 0x50, 0x51, 0x3, 0x2, 
    0x2, 0x2, 0x51, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x51, 0x52, 0x3, 0x2, 0x2, 
    0x2, 0x52, 0x11, 0x3, 0x2, 0x2, 0x2, 0xb, 0x19, 0x1f, 0x25, 0x2c, 0x32, 
    0x37, 0x3c, 0x4f, 0x51, 
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
