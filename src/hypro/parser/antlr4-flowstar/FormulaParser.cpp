
// Generated from Formula.g4 by ANTLR 4.7


#include "FormulaVisitor.h"

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

antlrcpp::Any FormulaParser::TermContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<FormulaVisitor*>(visitor))
    return parserVisitor->visitTerm(this);
  else
    return visitor->visitChildren(this);
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
    setState(12);
    _la = _input->LA(1);
    if (!(_la == FormulaParser::NUMBER

    || _la == FormulaParser::VARIABLE)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(17);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == FormulaParser::TIMES) {
      setState(13);
      match(FormulaParser::TIMES);
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

antlrcpp::Any FormulaParser::PolynomContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<FormulaVisitor*>(visitor))
    return parserVisitor->visitPolynom(this);
  else
    return visitor->visitChildren(this);
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
    setState(20);
    term();
    setState(25);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == FormulaParser::PLUS) {
      setState(21);
      match(FormulaParser::PLUS);
      setState(22);
      term();
      setState(27);
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

antlrcpp::Any FormulaParser::EquationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<FormulaVisitor*>(visitor))
    return parserVisitor->visitEquation(this);
  else
    return visitor->visitChildren(this);
}

FormulaParser::EquationContext* FormulaParser::equation() {
  EquationContext *_localctx = _tracker.createInstance<EquationContext>(_ctx, getState());
  enterRule(_localctx, 4, FormulaParser::RuleEquation);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(28);
    match(FormulaParser::VARIABLE);
    setState(29);
    match(FormulaParser::EQUALS);
    setState(30);
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

antlrcpp::Any FormulaParser::ConstraintContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<FormulaVisitor*>(visitor))
    return parserVisitor->visitConstraint(this);
  else
    return visitor->visitChildren(this);
}

FormulaParser::ConstraintContext* FormulaParser::constraint() {
  ConstraintContext *_localctx = _tracker.createInstance<ConstraintContext>(_ctx, getState());
  enterRule(_localctx, 6, FormulaParser::RuleConstraint);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(32);
    polynom();
    setState(33);
    _la = _input->LA(1);
    if (!(_la == FormulaParser::EQUALS

    || _la == FormulaParser::BOOLRELATION)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(34);
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

antlrcpp::Any FormulaParser::IntervalContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<FormulaVisitor*>(visitor))
    return parserVisitor->visitInterval(this);
  else
    return visitor->visitChildren(this);
}

FormulaParser::IntervalContext* FormulaParser::interval() {
  IntervalContext *_localctx = _tracker.createInstance<IntervalContext>(_ctx, getState());
  enterRule(_localctx, 8, FormulaParser::RuleInterval);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(36);
    match(FormulaParser::T__0);
    setState(37);
    match(FormulaParser::NUMBER);
    setState(38);
    match(FormulaParser::T__1);
    setState(39);
    match(FormulaParser::NUMBER);
    setState(40);
    match(FormulaParser::T__2);
   
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

antlrcpp::Any FormulaParser::IntervalexprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<FormulaVisitor*>(visitor))
    return parserVisitor->visitIntervalexpr(this);
  else
    return visitor->visitChildren(this);
}

FormulaParser::IntervalexprContext* FormulaParser::intervalexpr() {
  IntervalexprContext *_localctx = _tracker.createInstance<IntervalexprContext>(_ctx, getState());
  enterRule(_localctx, 10, FormulaParser::RuleIntervalexpr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(42);
    match(FormulaParser::VARIABLE);
    setState(43);
    match(FormulaParser::IN);
    setState(44);
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
std::vector<dfa::DFA> FormulaParser::_decisionToDFA;
atn::PredictionContextCache FormulaParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN FormulaParser::_atn;
std::vector<uint16_t> FormulaParser::_serializedATN;

std::vector<std::string> FormulaParser::_ruleNames = {
  "term", "polynom", "equation", "constraint", "interval", "intervalexpr"
};

std::vector<std::string> FormulaParser::_literalNames = {
  "", "'['", "','", "']'", "'in'", "'='", "", "'+'", "'*'"
};

std::vector<std::string> FormulaParser::_symbolicNames = {
  "", "", "", "", "IN", "EQUALS", "BOOLRELATION", "PLUS", "TIMES", "NUMBER", 
  "VARIABLE", "WS"
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
    0x3, 0xd, 0x31, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x3, 
    0x2, 0x3, 0x2, 0x3, 0x2, 0x7, 0x2, 0x12, 0xa, 0x2, 0xc, 0x2, 0xe, 0x2, 
    0x15, 0xb, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x7, 0x3, 0x1a, 0xa, 0x3, 
    0xc, 0x3, 0xe, 0x3, 0x1d, 0xb, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 
    0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 
    0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 
    0x7, 0x3, 0x7, 0x2, 0x2, 0x8, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0x2, 0x4, 
    0x3, 0x2, 0xb, 0xc, 0x3, 0x2, 0x7, 0x8, 0x2, 0x2c, 0x2, 0xe, 0x3, 0x2, 
    0x2, 0x2, 0x4, 0x16, 0x3, 0x2, 0x2, 0x2, 0x6, 0x1e, 0x3, 0x2, 0x2, 0x2, 
    0x8, 0x22, 0x3, 0x2, 0x2, 0x2, 0xa, 0x26, 0x3, 0x2, 0x2, 0x2, 0xc, 0x2c, 
    0x3, 0x2, 0x2, 0x2, 0xe, 0x13, 0x9, 0x2, 0x2, 0x2, 0xf, 0x10, 0x7, 0xa, 
    0x2, 0x2, 0x10, 0x12, 0x9, 0x2, 0x2, 0x2, 0x11, 0xf, 0x3, 0x2, 0x2, 
    0x2, 0x12, 0x15, 0x3, 0x2, 0x2, 0x2, 0x13, 0x11, 0x3, 0x2, 0x2, 0x2, 
    0x13, 0x14, 0x3, 0x2, 0x2, 0x2, 0x14, 0x3, 0x3, 0x2, 0x2, 0x2, 0x15, 
    0x13, 0x3, 0x2, 0x2, 0x2, 0x16, 0x1b, 0x5, 0x2, 0x2, 0x2, 0x17, 0x18, 
    0x7, 0x9, 0x2, 0x2, 0x18, 0x1a, 0x5, 0x2, 0x2, 0x2, 0x19, 0x17, 0x3, 
    0x2, 0x2, 0x2, 0x1a, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x1b, 0x19, 0x3, 0x2, 
    0x2, 0x2, 0x1b, 0x1c, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x5, 0x3, 0x2, 0x2, 
    0x2, 0x1d, 0x1b, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x1f, 0x7, 0xc, 0x2, 0x2, 
    0x1f, 0x20, 0x7, 0x7, 0x2, 0x2, 0x20, 0x21, 0x5, 0x4, 0x3, 0x2, 0x21, 
    0x7, 0x3, 0x2, 0x2, 0x2, 0x22, 0x23, 0x5, 0x4, 0x3, 0x2, 0x23, 0x24, 
    0x9, 0x3, 0x2, 0x2, 0x24, 0x25, 0x5, 0x4, 0x3, 0x2, 0x25, 0x9, 0x3, 
    0x2, 0x2, 0x2, 0x26, 0x27, 0x7, 0x3, 0x2, 0x2, 0x27, 0x28, 0x7, 0xb, 
    0x2, 0x2, 0x28, 0x29, 0x7, 0x4, 0x2, 0x2, 0x29, 0x2a, 0x7, 0xb, 0x2, 
    0x2, 0x2a, 0x2b, 0x7, 0x5, 0x2, 0x2, 0x2b, 0xb, 0x3, 0x2, 0x2, 0x2, 
    0x2c, 0x2d, 0x7, 0xc, 0x2, 0x2, 0x2d, 0x2e, 0x7, 0x6, 0x2, 0x2, 0x2e, 
    0x2f, 0x5, 0xa, 0x6, 0x2, 0x2f, 0xd, 0x3, 0x2, 0x2, 0x2, 0x4, 0x13, 
    0x1b, 
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
