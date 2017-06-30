
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


//----------------- AddContext ------------------------------------------------------------------

FormulaParser::AddContext::AddContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* FormulaParser::AddContext::PLUS() {
  return getToken(FormulaParser::PLUS, 0);
}

FormulaParser::TermContext* FormulaParser::AddContext::term() {
  return getRuleContext<FormulaParser::TermContext>(0);
}


size_t FormulaParser::AddContext::getRuleIndex() const {
  return FormulaParser::RuleAdd;
}


FormulaParser::AddContext* FormulaParser::add() {
  AddContext *_localctx = _tracker.createInstance<AddContext>(_ctx, getState());
  enterRule(_localctx, 0, FormulaParser::RuleAdd);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(14);
    match(FormulaParser::PLUS);
    setState(15);
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

FormulaParser::MultContext::MultContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> FormulaParser::MultContext::NUMBER() {
  return getTokens(FormulaParser::NUMBER);
}

tree::TerminalNode* FormulaParser::MultContext::NUMBER(size_t i) {
  return getToken(FormulaParser::NUMBER, i);
}

std::vector<tree::TerminalNode *> FormulaParser::MultContext::VARIABLE() {
  return getTokens(FormulaParser::VARIABLE);
}

tree::TerminalNode* FormulaParser::MultContext::VARIABLE(size_t i) {
  return getToken(FormulaParser::VARIABLE, i);
}

std::vector<tree::TerminalNode *> FormulaParser::MultContext::TIMES() {
  return getTokens(FormulaParser::TIMES);
}

tree::TerminalNode* FormulaParser::MultContext::TIMES(size_t i) {
  return getToken(FormulaParser::TIMES, i);
}


size_t FormulaParser::MultContext::getRuleIndex() const {
  return FormulaParser::RuleMult;
}


FormulaParser::MultContext* FormulaParser::mult() {
  MultContext *_localctx = _tracker.createInstance<MultContext>(_ctx, getState());
  enterRule(_localctx, 2, FormulaParser::RuleMult);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(17);
    _la = _input->LA(1);
    if (!(_la == FormulaParser::VARIABLE

    || _la == FormulaParser::NUMBER)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(22);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx);
    while (alt != 1 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1 + 1) {
        setState(18);
        match(FormulaParser::TIMES);
        setState(19);
        _la = _input->LA(1);
        if (!(_la == FormulaParser::VARIABLE

        || _la == FormulaParser::NUMBER)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        } 
      }
      setState(24);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx);
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

FormulaParser::MultContext* FormulaParser::TermContext::mult() {
  return getRuleContext<FormulaParser::MultContext>(0);
}

std::vector<FormulaParser::AddContext *> FormulaParser::TermContext::add() {
  return getRuleContexts<FormulaParser::AddContext>();
}

FormulaParser::AddContext* FormulaParser::TermContext::add(size_t i) {
  return getRuleContext<FormulaParser::AddContext>(i);
}


size_t FormulaParser::TermContext::getRuleIndex() const {
  return FormulaParser::RuleTerm;
}


FormulaParser::TermContext* FormulaParser::term() {
  TermContext *_localctx = _tracker.createInstance<TermContext>(_ctx, getState());
  enterRule(_localctx, 4, FormulaParser::RuleTerm);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(25);
    mult();
    setState(29);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx);
    while (alt != 1 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1 + 1) {
        setState(26);
        add(); 
      }
      setState(31);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx);
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

FormulaParser::TermContext* FormulaParser::EquationContext::term() {
  return getRuleContext<FormulaParser::TermContext>(0);
}


size_t FormulaParser::EquationContext::getRuleIndex() const {
  return FormulaParser::RuleEquation;
}


FormulaParser::EquationContext* FormulaParser::equation() {
  EquationContext *_localctx = _tracker.createInstance<EquationContext>(_ctx, getState());
  enterRule(_localctx, 6, FormulaParser::RuleEquation);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(32);
    match(FormulaParser::VARIABLE);
    setState(33);
    match(FormulaParser::EQUALS);
    setState(34);
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

FormulaParser::BoolexprContext::BoolexprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

FormulaParser::TermContext* FormulaParser::BoolexprContext::term() {
  return getRuleContext<FormulaParser::TermContext>(0);
}

tree::TerminalNode* FormulaParser::BoolexprContext::BOOLRELATION() {
  return getToken(FormulaParser::BOOLRELATION, 0);
}

tree::TerminalNode* FormulaParser::BoolexprContext::NUMBER() {
  return getToken(FormulaParser::NUMBER, 0);
}


size_t FormulaParser::BoolexprContext::getRuleIndex() const {
  return FormulaParser::RuleBoolexpr;
}


FormulaParser::BoolexprContext* FormulaParser::boolexpr() {
  BoolexprContext *_localctx = _tracker.createInstance<BoolexprContext>(_ctx, getState());
  enterRule(_localctx, 8, FormulaParser::RuleBoolexpr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(36);
    term();
    setState(37);
    match(FormulaParser::BOOLRELATION);
    setState(38);
    match(FormulaParser::NUMBER);
   
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

FormulaParser::TermContext* FormulaParser::IntervalexprContext::term() {
  return getRuleContext<FormulaParser::TermContext>(0);
}

tree::TerminalNode* FormulaParser::IntervalexprContext::IN() {
  return getToken(FormulaParser::IN, 0);
}

tree::TerminalNode* FormulaParser::IntervalexprContext::INTERVAL() {
  return getToken(FormulaParser::INTERVAL, 0);
}


size_t FormulaParser::IntervalexprContext::getRuleIndex() const {
  return FormulaParser::RuleIntervalexpr;
}


FormulaParser::IntervalexprContext* FormulaParser::intervalexpr() {
  IntervalexprContext *_localctx = _tracker.createInstance<IntervalexprContext>(_ctx, getState());
  enterRule(_localctx, 10, FormulaParser::RuleIntervalexpr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(40);
    term();
    setState(41);
    match(FormulaParser::IN);
    setState(42);
    match(FormulaParser::INTERVAL);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FormulaContext ------------------------------------------------------------------

FormulaParser::FormulaContext::FormulaContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

FormulaParser::EquationContext* FormulaParser::FormulaContext::equation() {
  return getRuleContext<FormulaParser::EquationContext>(0);
}

FormulaParser::BoolexprContext* FormulaParser::FormulaContext::boolexpr() {
  return getRuleContext<FormulaParser::BoolexprContext>(0);
}

FormulaParser::IntervalexprContext* FormulaParser::FormulaContext::intervalexpr() {
  return getRuleContext<FormulaParser::IntervalexprContext>(0);
}


size_t FormulaParser::FormulaContext::getRuleIndex() const {
  return FormulaParser::RuleFormula;
}


FormulaParser::FormulaContext* FormulaParser::formula() {
  FormulaContext *_localctx = _tracker.createInstance<FormulaContext>(_ctx, getState());
  enterRule(_localctx, 12, FormulaParser::RuleFormula);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(47);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(44);
      equation();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(45);
      boolexpr();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(46);
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
std::vector<dfa::DFA> FormulaParser::_decisionToDFA;
atn::PredictionContextCache FormulaParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN FormulaParser::_atn;
std::vector<uint16_t> FormulaParser::_serializedATN;

std::vector<std::string> FormulaParser::_ruleNames = {
  "add", "mult", "term", "equation", "boolexpr", "intervalexpr", "formula"
};

std::vector<std::string> FormulaParser::_literalNames = {
  "", "'in'", "'='", "", "'+'", "'*'"
};

std::vector<std::string> FormulaParser::_symbolicNames = {
  "", "IN", "EQUALS", "BOOLRELATION", "PLUS", "TIMES", "VARIABLE", "NUMBER", 
  "INTERVAL", "WS"
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
    0x3, 0xb, 0x34, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x7, 0x3, 0x17, 0xa, 0x3, 0xc, 0x3, 0xe, 0x3, 0x1a, 0xb, 0x3, 0x3, 
    0x4, 0x3, 0x4, 0x7, 0x4, 0x1e, 0xa, 0x4, 0xc, 0x4, 0xe, 0x4, 0x21, 0xb, 
    0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 
    0x6, 0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 
    0x8, 0x3, 0x8, 0x5, 0x8, 0x32, 0xa, 0x8, 0x3, 0x8, 0x4, 0x18, 0x1f, 
    0x2, 0x9, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x2, 0x3, 0x3, 0x2, 0x8, 
    0x9, 0x2, 0x30, 0x2, 0x10, 0x3, 0x2, 0x2, 0x2, 0x4, 0x13, 0x3, 0x2, 
    0x2, 0x2, 0x6, 0x1b, 0x3, 0x2, 0x2, 0x2, 0x8, 0x22, 0x3, 0x2, 0x2, 0x2, 
    0xa, 0x26, 0x3, 0x2, 0x2, 0x2, 0xc, 0x2a, 0x3, 0x2, 0x2, 0x2, 0xe, 0x31, 
    0x3, 0x2, 0x2, 0x2, 0x10, 0x11, 0x7, 0x6, 0x2, 0x2, 0x11, 0x12, 0x5, 
    0x6, 0x4, 0x2, 0x12, 0x3, 0x3, 0x2, 0x2, 0x2, 0x13, 0x18, 0x9, 0x2, 
    0x2, 0x2, 0x14, 0x15, 0x7, 0x7, 0x2, 0x2, 0x15, 0x17, 0x9, 0x2, 0x2, 
    0x2, 0x16, 0x14, 0x3, 0x2, 0x2, 0x2, 0x17, 0x1a, 0x3, 0x2, 0x2, 0x2, 
    0x18, 0x19, 0x3, 0x2, 0x2, 0x2, 0x18, 0x16, 0x3, 0x2, 0x2, 0x2, 0x19, 
    0x5, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x18, 0x3, 0x2, 0x2, 0x2, 0x1b, 0x1f, 
    0x5, 0x4, 0x3, 0x2, 0x1c, 0x1e, 0x5, 0x2, 0x2, 0x2, 0x1d, 0x1c, 0x3, 
    0x2, 0x2, 0x2, 0x1e, 0x21, 0x3, 0x2, 0x2, 0x2, 0x1f, 0x20, 0x3, 0x2, 
    0x2, 0x2, 0x1f, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x20, 0x7, 0x3, 0x2, 0x2, 
    0x2, 0x21, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x22, 0x23, 0x7, 0x8, 0x2, 0x2, 
    0x23, 0x24, 0x7, 0x4, 0x2, 0x2, 0x24, 0x25, 0x5, 0x6, 0x4, 0x2, 0x25, 
    0x9, 0x3, 0x2, 0x2, 0x2, 0x26, 0x27, 0x5, 0x6, 0x4, 0x2, 0x27, 0x28, 
    0x7, 0x5, 0x2, 0x2, 0x28, 0x29, 0x7, 0x9, 0x2, 0x2, 0x29, 0xb, 0x3, 
    0x2, 0x2, 0x2, 0x2a, 0x2b, 0x5, 0x6, 0x4, 0x2, 0x2b, 0x2c, 0x7, 0x3, 
    0x2, 0x2, 0x2c, 0x2d, 0x7, 0xa, 0x2, 0x2, 0x2d, 0xd, 0x3, 0x2, 0x2, 
    0x2, 0x2e, 0x32, 0x5, 0x8, 0x5, 0x2, 0x2f, 0x32, 0x5, 0xa, 0x6, 0x2, 
    0x30, 0x32, 0x5, 0xc, 0x7, 0x2, 0x31, 0x2e, 0x3, 0x2, 0x2, 0x2, 0x31, 
    0x2f, 0x3, 0x2, 0x2, 0x2, 0x31, 0x30, 0x3, 0x2, 0x2, 0x2, 0x32, 0xf, 
    0x3, 0x2, 0x2, 0x2, 0x5, 0x18, 0x1f, 0x31, 
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
