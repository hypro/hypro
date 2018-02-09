
// Generated from BadStates.g4 by ANTLR 4.7



#include "BadStatesParser.h"


	#include <map>
	#include <string>


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
    setState(26);
    match(BadStatesParser::T__0);
    setState(27);
    match(BadStatesParser::CBOPEN);
    setState(32);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << BadStatesParser::PLUS)
      | (1ULL << BadStatesParser::MINUS)
      | (1ULL << BadStatesParser::NUMBER)
      | (1ULL << BadStatesParser::VARIABLE))) != 0)) {
      setState(30);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
      case 1: {
        setState(28);
        gbadstate();
        break;
      }

      case 2: {
        setState(29);
        lbadstate();
        break;
      }

      }
      setState(34);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(35);
    match(BadStatesParser::CBCLOSE);
   
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
    setState(37);
    match(BadStatesParser::VARIABLE);
    setState(38);
    match(BadStatesParser::CBOPEN);
    setState(40);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << BadStatesParser::PLUS)
      | (1ULL << BadStatesParser::MINUS)
      | (1ULL << BadStatesParser::NUMBER)
      | (1ULL << BadStatesParser::VARIABLE))) != 0)) {
      setState(39);
      constrset();
    }
    setState(42);
    match(BadStatesParser::CBCLOSE);
   
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
    setState(44);
    constrset();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReplacedexprContext ------------------------------------------------------------------

BadStatesParser::ReplacedexprContext::ReplacedexprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> BadStatesParser::ReplacedexprContext::NUMBER() {
  return getTokens(BadStatesParser::NUMBER);
}

tree::TerminalNode* BadStatesParser::ReplacedexprContext::NUMBER(size_t i) {
  return getToken(BadStatesParser::NUMBER, i);
}

tree::TerminalNode* BadStatesParser::ReplacedexprContext::EQUALS() {
  return getToken(BadStatesParser::EQUALS, 0);
}

std::vector<tree::TerminalNode *> BadStatesParser::ReplacedexprContext::MINUS() {
  return getTokens(BadStatesParser::MINUS);
}

tree::TerminalNode* BadStatesParser::ReplacedexprContext::MINUS(size_t i) {
  return getToken(BadStatesParser::MINUS, i);
}


size_t BadStatesParser::ReplacedexprContext::getRuleIndex() const {
  return BadStatesParser::RuleReplacedexpr;
}


BadStatesParser::ReplacedexprContext* BadStatesParser::replacedexpr() {
  ReplacedexprContext *_localctx = _tracker.createInstance<ReplacedexprContext>(_ctx, getState());
  enterRule(_localctx, 6, BadStatesParser::RuleReplacedexpr);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(47);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == BadStatesParser::MINUS) {
      setState(46);
      match(BadStatesParser::MINUS);
    }
    setState(49);
    match(BadStatesParser::NUMBER);
    setState(50);
    match(BadStatesParser::EQUALS);
    setState(52);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == BadStatesParser::MINUS) {
      setState(51);
      match(BadStatesParser::MINUS);
    }
    setState(54);
    match(BadStatesParser::NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstantexprContext ------------------------------------------------------------------

BadStatesParser::ConstantexprContext::ConstantexprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* BadStatesParser::ConstantexprContext::CONSTANT() {
  return getToken(BadStatesParser::CONSTANT, 0);
}

tree::TerminalNode* BadStatesParser::ConstantexprContext::EQUALS() {
  return getToken(BadStatesParser::EQUALS, 0);
}

tree::TerminalNode* BadStatesParser::ConstantexprContext::NUMBER() {
  return getToken(BadStatesParser::NUMBER, 0);
}

tree::TerminalNode* BadStatesParser::ConstantexprContext::MINUS() {
  return getToken(BadStatesParser::MINUS, 0);
}


size_t BadStatesParser::ConstantexprContext::getRuleIndex() const {
  return BadStatesParser::RuleConstantexpr;
}


BadStatesParser::ConstantexprContext* BadStatesParser::constantexpr() {
  ConstantexprContext *_localctx = _tracker.createInstance<ConstantexprContext>(_ctx, getState());
  enterRule(_localctx, 8, BadStatesParser::RuleConstantexpr);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(56);
    dynamic_cast<ConstantexprContext *>(_localctx)->constantToken = match(BadStatesParser::CONSTANT);
    setState(57);
    match(BadStatesParser::EQUALS);
    setState(59);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == BadStatesParser::MINUS) {
      setState(58);
      dynamic_cast<ConstantexprContext *>(_localctx)->minusToken = match(BadStatesParser::MINUS);
    }
    setState(61);
    dynamic_cast<ConstantexprContext *>(_localctx)->numberToken = match(BadStatesParser::NUMBER);

    	std::cout << "In constantexpr! MINUS text is: " << (dynamic_cast<ConstantexprContext *>(_localctx)->minusToken != nullptr ? dynamic_cast<ConstantexprContext *>(_localctx)->minusToken->getText() : "") << std::endl;
    	if((dynamic_cast<ConstantexprContext *>(_localctx)->minusToken != nullptr ? dynamic_cast<ConstantexprContext *>(_localctx)->minusToken->getText() : "") != ""){
    		constants.insert({(dynamic_cast<ConstantexprContext *>(_localctx)->constantToken != nullptr ? dynamic_cast<ConstantexprContext *>(_localctx)->constantToken->getText() : ""), (dynamic_cast<ConstantexprContext *>(_localctx)->minusToken != nullptr ? dynamic_cast<ConstantexprContext *>(_localctx)->minusToken->getText() : "").append((dynamic_cast<ConstantexprContext *>(_localctx)->numberToken != nullptr ? dynamic_cast<ConstantexprContext *>(_localctx)->numberToken->getText() : ""))});
    		std::cout << "Constant " << (dynamic_cast<ConstantexprContext *>(_localctx)->constantToken != nullptr ? dynamic_cast<ConstantexprContext *>(_localctx)->constantToken->getText() : "") << " with value " << (dynamic_cast<ConstantexprContext *>(_localctx)->minusToken != nullptr ? dynamic_cast<ConstantexprContext *>(_localctx)->minusToken->getText() : "").append((dynamic_cast<ConstantexprContext *>(_localctx)->numberToken != nullptr ? dynamic_cast<ConstantexprContext *>(_localctx)->numberToken->getText() : "")) << " was put in map!\n";
    	} else {
    		constants.insert({(dynamic_cast<ConstantexprContext *>(_localctx)->constantToken != nullptr ? dynamic_cast<ConstantexprContext *>(_localctx)->constantToken->getText() : ""), (dynamic_cast<ConstantexprContext *>(_localctx)->numberToken != nullptr ? dynamic_cast<ConstantexprContext *>(_localctx)->numberToken->getText() : "")});
    		std::cout << "Constant " << (dynamic_cast<ConstantexprContext *>(_localctx)->constantToken != nullptr ? dynamic_cast<ConstantexprContext *>(_localctx)->constantToken->getText() : "") << " with value " << (dynamic_cast<ConstantexprContext *>(_localctx)->numberToken != nullptr ? dynamic_cast<ConstantexprContext *>(_localctx)->numberToken->getText() : "") << " was put in map!\n";
    	}

   
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
  enterRule(_localctx, 10, BadStatesParser::RuleConnector);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(64);
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
  enterRule(_localctx, 12, BadStatesParser::RuleTerm);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(66);
    _la = _input->LA(1);
    if (!(_la == BadStatesParser::NUMBER

    || _la == BadStatesParser::VARIABLE)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(77);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == BadStatesParser::TIMES) {
      setState(67);
      match(BadStatesParser::TIMES);
      setState(71);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == BadStatesParser::PLUS

      || _la == BadStatesParser::MINUS) {
        setState(68);
        connector();
        setState(73);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(74);
      _la = _input->LA(1);
      if (!(_la == BadStatesParser::NUMBER

      || _la == BadStatesParser::VARIABLE)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(79);
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
  enterRule(_localctx, 14, BadStatesParser::RulePolynom);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(83);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == BadStatesParser::PLUS

    || _la == BadStatesParser::MINUS) {
      setState(80);
      connector();
      setState(85);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(86);
    term();
    setState(96);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(88); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(87);
          connector();
          setState(90); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == BadStatesParser::PLUS

        || _la == BadStatesParser::MINUS);
        setState(92);
        term(); 
      }
      setState(98);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
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
  enterRule(_localctx, 16, BadStatesParser::RuleInterval);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(99);
    match(BadStatesParser::SBOPEN);
    setState(101);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == BadStatesParser::MINUS) {
      setState(100);
      match(BadStatesParser::MINUS);
    }
    setState(103);
    match(BadStatesParser::NUMBER);
    setState(104);
    match(BadStatesParser::COMMA);
    setState(106);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == BadStatesParser::MINUS) {
      setState(105);
      match(BadStatesParser::MINUS);
    }
    setState(108);
    match(BadStatesParser::NUMBER);
    setState(109);
    match(BadStatesParser::SBCLOSE);
   
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
  enterRule(_localctx, 18, BadStatesParser::RuleEquation);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(111);
    match(BadStatesParser::VARIABLE);
    setState(112);
    match(BadStatesParser::EQUALS);
    setState(113);
    polynom();
    setState(117);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == BadStatesParser::PLUS

    || _la == BadStatesParser::MINUS) {
      setState(114);
      connector();
      setState(115);
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
  enterRule(_localctx, 20, BadStatesParser::RuleConstraint);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(119);
    polynom();
    setState(120);
    _la = _input->LA(1);
    if (!(_la == BadStatesParser::EQUALS

    || _la == BadStatesParser::BOOLRELATION)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(121);
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
  enterRule(_localctx, 22, BadStatesParser::RuleIntervalexpr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(123);
    match(BadStatesParser::VARIABLE);
    setState(124);
    match(BadStatesParser::IN);
    setState(125);
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
  enterRule(_localctx, 24, BadStatesParser::RuleConstrset);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(129); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(129);
              _errHandler->sync(this);
              switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
              case 1: {
                setState(127);
                constraint();
                break;
              }

              case 2: {
                setState(128);
                intervalexpr();
                break;
              }

              }
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(131); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx);
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
  "unsafeset", "lbadstate", "gbadstate", "replacedexpr", "constantexpr", 
  "connector", "term", "polynom", "interval", "equation", "constraint", 
  "intervalexpr", "constrset"
};

std::vector<std::string> BadStatesParser::_literalNames = {
  "", "'unsafe set'", "'in'", "'par'", "'jumps'", "'urgent'", "'guard'", 
  "'reset'", "'parallelotope aggregation'", "'box aggregation'", "'->'", 
  "':='", "", "'='", "", "'+'", "'-'", "'*'", "'['", "']'", "'{'", "'}'", 
  "','"
};

std::vector<std::string> BadStatesParser::_symbolicNames = {
  "", "", "IN", "PAR", "JUMPS", "URGENT", "GUARD", "RESET", "PARALLELOTOPE", 
  "BOX", "JUMP", "DEFINE", "COMMENT", "EQUALS", "BOOLRELATION", "PLUS", 
  "MINUS", "TIMES", "SBOPEN", "SBCLOSE", "CBOPEN", "CBCLOSE", "COMMA", "NUMBER", 
  "CONSTANT", "VARIABLE", "WS"
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
    0x3, 0x1c, 0x88, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 0x3, 
    0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x7, 0x2, 0x21, 0xa, 0x2, 0xc, 0x2, 
    0xe, 0x2, 0x24, 0xb, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x5, 0x3, 0x2b, 0xa, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x4, 0x3, 0x4, 
    0x3, 0x5, 0x5, 0x5, 0x32, 0xa, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x5, 
    0x5, 0x37, 0xa, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 
    0x5, 0x6, 0x3e, 0xa, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 0x3, 
    0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x7, 0x8, 0x48, 0xa, 0x8, 0xc, 0x8, 
    0xe, 0x8, 0x4b, 0xb, 0x8, 0x3, 0x8, 0x7, 0x8, 0x4e, 0xa, 0x8, 0xc, 0x8, 
    0xe, 0x8, 0x51, 0xb, 0x8, 0x3, 0x9, 0x7, 0x9, 0x54, 0xa, 0x9, 0xc, 0x9, 
    0xe, 0x9, 0x57, 0xb, 0x9, 0x3, 0x9, 0x3, 0x9, 0x6, 0x9, 0x5b, 0xa, 0x9, 
    0xd, 0x9, 0xe, 0x9, 0x5c, 0x3, 0x9, 0x3, 0x9, 0x7, 0x9, 0x61, 0xa, 0x9, 
    0xc, 0x9, 0xe, 0x9, 0x64, 0xb, 0x9, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0x68, 
    0xa, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0x6d, 0xa, 0xa, 0x3, 
    0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 
    0xb, 0x3, 0xb, 0x5, 0xb, 0x78, 0xa, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 
    0x3, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xe, 0x3, 0xe, 
    0x6, 0xe, 0x84, 0xa, 0xe, 0xd, 0xe, 0xe, 0xe, 0x85, 0x3, 0xe, 0x2, 0x2, 
    0xf, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 
    0x1a, 0x2, 0x5, 0x3, 0x2, 0x11, 0x12, 0x4, 0x2, 0x19, 0x19, 0x1b, 0x1b, 
    0x3, 0x2, 0xf, 0x10, 0x2, 0x8a, 0x2, 0x1c, 0x3, 0x2, 0x2, 0x2, 0x4, 
    0x27, 0x3, 0x2, 0x2, 0x2, 0x6, 0x2e, 0x3, 0x2, 0x2, 0x2, 0x8, 0x31, 
    0x3, 0x2, 0x2, 0x2, 0xa, 0x3a, 0x3, 0x2, 0x2, 0x2, 0xc, 0x42, 0x3, 0x2, 
    0x2, 0x2, 0xe, 0x44, 0x3, 0x2, 0x2, 0x2, 0x10, 0x55, 0x3, 0x2, 0x2, 
    0x2, 0x12, 0x65, 0x3, 0x2, 0x2, 0x2, 0x14, 0x71, 0x3, 0x2, 0x2, 0x2, 
    0x16, 0x79, 0x3, 0x2, 0x2, 0x2, 0x18, 0x7d, 0x3, 0x2, 0x2, 0x2, 0x1a, 
    0x83, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x1d, 0x7, 0x3, 0x2, 0x2, 0x1d, 0x22, 
    0x7, 0x16, 0x2, 0x2, 0x1e, 0x21, 0x5, 0x6, 0x4, 0x2, 0x1f, 0x21, 0x5, 
    0x4, 0x3, 0x2, 0x20, 0x1e, 0x3, 0x2, 0x2, 0x2, 0x20, 0x1f, 0x3, 0x2, 
    0x2, 0x2, 0x21, 0x24, 0x3, 0x2, 0x2, 0x2, 0x22, 0x20, 0x3, 0x2, 0x2, 
    0x2, 0x22, 0x23, 0x3, 0x2, 0x2, 0x2, 0x23, 0x25, 0x3, 0x2, 0x2, 0x2, 
    0x24, 0x22, 0x3, 0x2, 0x2, 0x2, 0x25, 0x26, 0x7, 0x17, 0x2, 0x2, 0x26, 
    0x3, 0x3, 0x2, 0x2, 0x2, 0x27, 0x28, 0x7, 0x1b, 0x2, 0x2, 0x28, 0x2a, 
    0x7, 0x16, 0x2, 0x2, 0x29, 0x2b, 0x5, 0x1a, 0xe, 0x2, 0x2a, 0x29, 0x3, 
    0x2, 0x2, 0x2, 0x2a, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x2b, 0x2c, 0x3, 0x2, 
    0x2, 0x2, 0x2c, 0x2d, 0x7, 0x17, 0x2, 0x2, 0x2d, 0x5, 0x3, 0x2, 0x2, 
    0x2, 0x2e, 0x2f, 0x5, 0x1a, 0xe, 0x2, 0x2f, 0x7, 0x3, 0x2, 0x2, 0x2, 
    0x30, 0x32, 0x7, 0x12, 0x2, 0x2, 0x31, 0x30, 0x3, 0x2, 0x2, 0x2, 0x31, 
    0x32, 0x3, 0x2, 0x2, 0x2, 0x32, 0x33, 0x3, 0x2, 0x2, 0x2, 0x33, 0x34, 
    0x7, 0x19, 0x2, 0x2, 0x34, 0x36, 0x7, 0xf, 0x2, 0x2, 0x35, 0x37, 0x7, 
    0x12, 0x2, 0x2, 0x36, 0x35, 0x3, 0x2, 0x2, 0x2, 0x36, 0x37, 0x3, 0x2, 
    0x2, 0x2, 0x37, 0x38, 0x3, 0x2, 0x2, 0x2, 0x38, 0x39, 0x7, 0x19, 0x2, 
    0x2, 0x39, 0x9, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x3b, 0x7, 0x1a, 0x2, 0x2, 
    0x3b, 0x3d, 0x7, 0xf, 0x2, 0x2, 0x3c, 0x3e, 0x7, 0x12, 0x2, 0x2, 0x3d, 
    0x3c, 0x3, 0x2, 0x2, 0x2, 0x3d, 0x3e, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x3f, 
    0x3, 0x2, 0x2, 0x2, 0x3f, 0x40, 0x7, 0x19, 0x2, 0x2, 0x40, 0x41, 0x8, 
    0x6, 0x1, 0x2, 0x41, 0xb, 0x3, 0x2, 0x2, 0x2, 0x42, 0x43, 0x9, 0x2, 
    0x2, 0x2, 0x43, 0xd, 0x3, 0x2, 0x2, 0x2, 0x44, 0x4f, 0x9, 0x3, 0x2, 
    0x2, 0x45, 0x49, 0x7, 0x13, 0x2, 0x2, 0x46, 0x48, 0x5, 0xc, 0x7, 0x2, 
    0x47, 0x46, 0x3, 0x2, 0x2, 0x2, 0x48, 0x4b, 0x3, 0x2, 0x2, 0x2, 0x49, 
    0x47, 0x3, 0x2, 0x2, 0x2, 0x49, 0x4a, 0x3, 0x2, 0x2, 0x2, 0x4a, 0x4c, 
    0x3, 0x2, 0x2, 0x2, 0x4b, 0x49, 0x3, 0x2, 0x2, 0x2, 0x4c, 0x4e, 0x9, 
    0x3, 0x2, 0x2, 0x4d, 0x45, 0x3, 0x2, 0x2, 0x2, 0x4e, 0x51, 0x3, 0x2, 
    0x2, 0x2, 0x4f, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x4f, 0x50, 0x3, 0x2, 0x2, 
    0x2, 0x50, 0xf, 0x3, 0x2, 0x2, 0x2, 0x51, 0x4f, 0x3, 0x2, 0x2, 0x2, 
    0x52, 0x54, 0x5, 0xc, 0x7, 0x2, 0x53, 0x52, 0x3, 0x2, 0x2, 0x2, 0x54, 
    0x57, 0x3, 0x2, 0x2, 0x2, 0x55, 0x53, 0x3, 0x2, 0x2, 0x2, 0x55, 0x56, 
    0x3, 0x2, 0x2, 0x2, 0x56, 0x58, 0x3, 0x2, 0x2, 0x2, 0x57, 0x55, 0x3, 
    0x2, 0x2, 0x2, 0x58, 0x62, 0x5, 0xe, 0x8, 0x2, 0x59, 0x5b, 0x5, 0xc, 
    0x7, 0x2, 0x5a, 0x59, 0x3, 0x2, 0x2, 0x2, 0x5b, 0x5c, 0x3, 0x2, 0x2, 
    0x2, 0x5c, 0x5a, 0x3, 0x2, 0x2, 0x2, 0x5c, 0x5d, 0x3, 0x2, 0x2, 0x2, 
    0x5d, 0x5e, 0x3, 0x2, 0x2, 0x2, 0x5e, 0x5f, 0x5, 0xe, 0x8, 0x2, 0x5f, 
    0x61, 0x3, 0x2, 0x2, 0x2, 0x60, 0x5a, 0x3, 0x2, 0x2, 0x2, 0x61, 0x64, 
    0x3, 0x2, 0x2, 0x2, 0x62, 0x60, 0x3, 0x2, 0x2, 0x2, 0x62, 0x63, 0x3, 
    0x2, 0x2, 0x2, 0x63, 0x11, 0x3, 0x2, 0x2, 0x2, 0x64, 0x62, 0x3, 0x2, 
    0x2, 0x2, 0x65, 0x67, 0x7, 0x14, 0x2, 0x2, 0x66, 0x68, 0x7, 0x12, 0x2, 
    0x2, 0x67, 0x66, 0x3, 0x2, 0x2, 0x2, 0x67, 0x68, 0x3, 0x2, 0x2, 0x2, 
    0x68, 0x69, 0x3, 0x2, 0x2, 0x2, 0x69, 0x6a, 0x7, 0x19, 0x2, 0x2, 0x6a, 
    0x6c, 0x7, 0x18, 0x2, 0x2, 0x6b, 0x6d, 0x7, 0x12, 0x2, 0x2, 0x6c, 0x6b, 
    0x3, 0x2, 0x2, 0x2, 0x6c, 0x6d, 0x3, 0x2, 0x2, 0x2, 0x6d, 0x6e, 0x3, 
    0x2, 0x2, 0x2, 0x6e, 0x6f, 0x7, 0x19, 0x2, 0x2, 0x6f, 0x70, 0x7, 0x15, 
    0x2, 0x2, 0x70, 0x13, 0x3, 0x2, 0x2, 0x2, 0x71, 0x72, 0x7, 0x1b, 0x2, 
    0x2, 0x72, 0x73, 0x7, 0xf, 0x2, 0x2, 0x73, 0x77, 0x5, 0x10, 0x9, 0x2, 
    0x74, 0x75, 0x5, 0xc, 0x7, 0x2, 0x75, 0x76, 0x5, 0x12, 0xa, 0x2, 0x76, 
    0x78, 0x3, 0x2, 0x2, 0x2, 0x77, 0x74, 0x3, 0x2, 0x2, 0x2, 0x77, 0x78, 
    0x3, 0x2, 0x2, 0x2, 0x78, 0x15, 0x3, 0x2, 0x2, 0x2, 0x79, 0x7a, 0x5, 
    0x10, 0x9, 0x2, 0x7a, 0x7b, 0x9, 0x4, 0x2, 0x2, 0x7b, 0x7c, 0x5, 0x10, 
    0x9, 0x2, 0x7c, 0x17, 0x3, 0x2, 0x2, 0x2, 0x7d, 0x7e, 0x7, 0x1b, 0x2, 
    0x2, 0x7e, 0x7f, 0x7, 0x4, 0x2, 0x2, 0x7f, 0x80, 0x5, 0x12, 0xa, 0x2, 
    0x80, 0x19, 0x3, 0x2, 0x2, 0x2, 0x81, 0x84, 0x5, 0x16, 0xc, 0x2, 0x82, 
    0x84, 0x5, 0x18, 0xd, 0x2, 0x83, 0x81, 0x3, 0x2, 0x2, 0x2, 0x83, 0x82, 
    0x3, 0x2, 0x2, 0x2, 0x84, 0x85, 0x3, 0x2, 0x2, 0x2, 0x85, 0x83, 0x3, 
    0x2, 0x2, 0x2, 0x85, 0x86, 0x3, 0x2, 0x2, 0x2, 0x86, 0x1b, 0x3, 0x2, 
    0x2, 0x2, 0x12, 0x20, 0x22, 0x2a, 0x31, 0x36, 0x3d, 0x49, 0x4f, 0x55, 
    0x5c, 0x62, 0x67, 0x6c, 0x77, 0x83, 0x85, 
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
