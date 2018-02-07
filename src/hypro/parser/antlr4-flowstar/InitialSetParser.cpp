
// Generated from InitialSet.g4 by ANTLR 4.7



#include "InitialSetParser.h"


	#include <map>
	#include <string>


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
    setState(24);
    match(InitialSetParser::T__0);
    setState(25);
    match(InitialSetParser::CBOPEN);
    setState(27); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(26);
      initstate();
      setState(29); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == InitialSetParser::VARIABLE);
    setState(31);
    match(InitialSetParser::CBCLOSE);
   
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
    setState(33);
    match(InitialSetParser::VARIABLE);
    setState(34);
    match(InitialSetParser::CBOPEN);
    setState(35);
    constrset();
    setState(36);
    match(InitialSetParser::CBCLOSE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReplacedexprContext ------------------------------------------------------------------

InitialSetParser::ReplacedexprContext::ReplacedexprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> InitialSetParser::ReplacedexprContext::NUMBER() {
  return getTokens(InitialSetParser::NUMBER);
}

tree::TerminalNode* InitialSetParser::ReplacedexprContext::NUMBER(size_t i) {
  return getToken(InitialSetParser::NUMBER, i);
}

tree::TerminalNode* InitialSetParser::ReplacedexprContext::EQUALS() {
  return getToken(InitialSetParser::EQUALS, 0);
}

std::vector<tree::TerminalNode *> InitialSetParser::ReplacedexprContext::MINUS() {
  return getTokens(InitialSetParser::MINUS);
}

tree::TerminalNode* InitialSetParser::ReplacedexprContext::MINUS(size_t i) {
  return getToken(InitialSetParser::MINUS, i);
}


size_t InitialSetParser::ReplacedexprContext::getRuleIndex() const {
  return InitialSetParser::RuleReplacedexpr;
}


InitialSetParser::ReplacedexprContext* InitialSetParser::replacedexpr() {
  ReplacedexprContext *_localctx = _tracker.createInstance<ReplacedexprContext>(_ctx, getState());
  enterRule(_localctx, 4, InitialSetParser::RuleReplacedexpr);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(39);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == InitialSetParser::MINUS) {
      setState(38);
      match(InitialSetParser::MINUS);
    }
    setState(41);
    match(InitialSetParser::NUMBER);
    setState(42);
    match(InitialSetParser::EQUALS);
    setState(44);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == InitialSetParser::MINUS) {
      setState(43);
      match(InitialSetParser::MINUS);
    }
    setState(46);
    match(InitialSetParser::NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstantexprContext ------------------------------------------------------------------

InitialSetParser::ConstantexprContext::ConstantexprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* InitialSetParser::ConstantexprContext::CONSTANT() {
  return getToken(InitialSetParser::CONSTANT, 0);
}

tree::TerminalNode* InitialSetParser::ConstantexprContext::EQUALS() {
  return getToken(InitialSetParser::EQUALS, 0);
}

tree::TerminalNode* InitialSetParser::ConstantexprContext::NUMBER() {
  return getToken(InitialSetParser::NUMBER, 0);
}

tree::TerminalNode* InitialSetParser::ConstantexprContext::MINUS() {
  return getToken(InitialSetParser::MINUS, 0);
}


size_t InitialSetParser::ConstantexprContext::getRuleIndex() const {
  return InitialSetParser::RuleConstantexpr;
}


InitialSetParser::ConstantexprContext* InitialSetParser::constantexpr() {
  ConstantexprContext *_localctx = _tracker.createInstance<ConstantexprContext>(_ctx, getState());
  enterRule(_localctx, 6, InitialSetParser::RuleConstantexpr);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(48);
    dynamic_cast<ConstantexprContext *>(_localctx)->constantToken = match(InitialSetParser::CONSTANT);
    setState(49);
    match(InitialSetParser::EQUALS);
    setState(51);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == InitialSetParser::MINUS) {
      setState(50);
      dynamic_cast<ConstantexprContext *>(_localctx)->minusToken = match(InitialSetParser::MINUS);
    }
    setState(53);
    dynamic_cast<ConstantexprContext *>(_localctx)->numberToken = match(InitialSetParser::NUMBER);

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
  enterRule(_localctx, 8, InitialSetParser::RuleConnector);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(56);
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
  enterRule(_localctx, 10, InitialSetParser::RuleTerm);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(58);
    _la = _input->LA(1);
    if (!(_la == InitialSetParser::NUMBER

    || _la == InitialSetParser::VARIABLE)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(69);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == InitialSetParser::TIMES) {
      setState(59);
      match(InitialSetParser::TIMES);
      setState(63);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == InitialSetParser::PLUS

      || _la == InitialSetParser::MINUS) {
        setState(60);
        connector();
        setState(65);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(66);
      _la = _input->LA(1);
      if (!(_la == InitialSetParser::NUMBER

      || _la == InitialSetParser::VARIABLE)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(71);
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
  enterRule(_localctx, 12, InitialSetParser::RulePolynom);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(75);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == InitialSetParser::PLUS

    || _la == InitialSetParser::MINUS) {
      setState(72);
      connector();
      setState(77);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(78);
    term();
    setState(88);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(80); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(79);
          connector();
          setState(82); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == InitialSetParser::PLUS

        || _la == InitialSetParser::MINUS);
        setState(84);
        term(); 
      }
      setState(90);
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
  enterRule(_localctx, 14, InitialSetParser::RuleInterval);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(91);
    match(InitialSetParser::SBOPEN);
    setState(93);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == InitialSetParser::MINUS) {
      setState(92);
      match(InitialSetParser::MINUS);
    }
    setState(95);
    match(InitialSetParser::NUMBER);
    setState(96);
    match(InitialSetParser::COMMA);
    setState(98);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == InitialSetParser::MINUS) {
      setState(97);
      match(InitialSetParser::MINUS);
    }
    setState(100);
    match(InitialSetParser::NUMBER);
    setState(101);
    match(InitialSetParser::SBCLOSE);
   
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
  enterRule(_localctx, 16, InitialSetParser::RuleEquation);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(103);
    match(InitialSetParser::VARIABLE);
    setState(104);
    match(InitialSetParser::EQUALS);
    setState(105);
    polynom();
    setState(109);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == InitialSetParser::PLUS

    || _la == InitialSetParser::MINUS) {
      setState(106);
      connector();
      setState(107);
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
  enterRule(_localctx, 18, InitialSetParser::RuleConstraint);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(111);
    polynom();
    setState(112);
    _la = _input->LA(1);
    if (!(_la == InitialSetParser::EQUALS

    || _la == InitialSetParser::BOOLRELATION)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(113);
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
  enterRule(_localctx, 20, InitialSetParser::RuleIntervalexpr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(115);
    match(InitialSetParser::VARIABLE);
    setState(116);
    match(InitialSetParser::IN);
    setState(117);
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
  enterRule(_localctx, 22, InitialSetParser::RuleConstrset);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(121); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(121);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
      case 1: {
        setState(119);
        constraint();
        break;
      }

      case 2: {
        setState(120);
        intervalexpr();
        break;
      }

      }
      setState(123); 
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
  "init", "initstate", "replacedexpr", "constantexpr", "connector", "term", 
  "polynom", "interval", "equation", "constraint", "intervalexpr", "constrset"
};

std::vector<std::string> InitialSetParser::_literalNames = {
  "", "'init'", "'in'", "'par'", "'jumps'", "'urgent'", "'guard'", "'reset'", 
  "'parallelotope aggregation'", "'box aggregation'", "'->'", "':='", "", 
  "'='", "", "'+'", "'-'", "'*'", "'['", "']'", "'{'", "'}'", "','"
};

std::vector<std::string> InitialSetParser::_symbolicNames = {
  "", "", "IN", "PAR", "JUMPS", "URGENT", "GUARD", "RESET", "PARALLELOTOPE", 
  "BOX", "JUMP", "DEFINE", "COMMENT", "EQUALS", "BOOLRELATION", "PLUS", 
  "MINUS", "TIMES", "SBOPEN", "SBCLOSE", "CBOPEN", "CBCLOSE", "COMMA", "NUMBER", 
  "CONSTANT", "VARIABLE", "WS"
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
    0x3, 0x1c, 0x80, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x3, 0x2, 0x3, 0x2, 0x3, 
    0x2, 0x6, 0x2, 0x1e, 0xa, 0x2, 0xd, 0x2, 0xe, 0x2, 0x1f, 0x3, 0x2, 0x3, 
    0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x4, 0x5, 
    0x4, 0x2a, 0xa, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 0x2f, 0xa, 
    0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x5, 0x5, 0x36, 
    0xa, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x7, 0x7, 0x7, 0x40, 0xa, 0x7, 0xc, 0x7, 0xe, 0x7, 0x43, 
    0xb, 0x7, 0x3, 0x7, 0x7, 0x7, 0x46, 0xa, 0x7, 0xc, 0x7, 0xe, 0x7, 0x49, 
    0xb, 0x7, 0x3, 0x8, 0x7, 0x8, 0x4c, 0xa, 0x8, 0xc, 0x8, 0xe, 0x8, 0x4f, 
    0xb, 0x8, 0x3, 0x8, 0x3, 0x8, 0x6, 0x8, 0x53, 0xa, 0x8, 0xd, 0x8, 0xe, 
    0x8, 0x54, 0x3, 0x8, 0x3, 0x8, 0x7, 0x8, 0x59, 0xa, 0x8, 0xc, 0x8, 0xe, 
    0x8, 0x5c, 0xb, 0x8, 0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 0x60, 0xa, 0x9, 0x3, 
    0x9, 0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 0x65, 0xa, 0x9, 0x3, 0x9, 0x3, 0x9, 
    0x3, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 
    0x5, 0xa, 0x70, 0xa, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 
    0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xd, 0x3, 0xd, 0x6, 0xd, 0x7c, 
    0xa, 0xd, 0xd, 0xd, 0xe, 0xd, 0x7d, 0x3, 0xd, 0x2, 0x2, 0xe, 0x2, 0x4, 
    0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x2, 0x5, 0x3, 
    0x2, 0x11, 0x12, 0x4, 0x2, 0x19, 0x19, 0x1b, 0x1b, 0x3, 0x2, 0xf, 0x10, 
    0x2, 0x81, 0x2, 0x1a, 0x3, 0x2, 0x2, 0x2, 0x4, 0x23, 0x3, 0x2, 0x2, 
    0x2, 0x6, 0x29, 0x3, 0x2, 0x2, 0x2, 0x8, 0x32, 0x3, 0x2, 0x2, 0x2, 0xa, 
    0x3a, 0x3, 0x2, 0x2, 0x2, 0xc, 0x3c, 0x3, 0x2, 0x2, 0x2, 0xe, 0x4d, 
    0x3, 0x2, 0x2, 0x2, 0x10, 0x5d, 0x3, 0x2, 0x2, 0x2, 0x12, 0x69, 0x3, 
    0x2, 0x2, 0x2, 0x14, 0x71, 0x3, 0x2, 0x2, 0x2, 0x16, 0x75, 0x3, 0x2, 
    0x2, 0x2, 0x18, 0x7b, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x1b, 0x7, 0x3, 0x2, 
    0x2, 0x1b, 0x1d, 0x7, 0x16, 0x2, 0x2, 0x1c, 0x1e, 0x5, 0x4, 0x3, 0x2, 
    0x1d, 0x1c, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x1f, 
    0x1d, 0x3, 0x2, 0x2, 0x2, 0x1f, 0x20, 0x3, 0x2, 0x2, 0x2, 0x20, 0x21, 
    0x3, 0x2, 0x2, 0x2, 0x21, 0x22, 0x7, 0x17, 0x2, 0x2, 0x22, 0x3, 0x3, 
    0x2, 0x2, 0x2, 0x23, 0x24, 0x7, 0x1b, 0x2, 0x2, 0x24, 0x25, 0x7, 0x16, 
    0x2, 0x2, 0x25, 0x26, 0x5, 0x18, 0xd, 0x2, 0x26, 0x27, 0x7, 0x17, 0x2, 
    0x2, 0x27, 0x5, 0x3, 0x2, 0x2, 0x2, 0x28, 0x2a, 0x7, 0x12, 0x2, 0x2, 
    0x29, 0x28, 0x3, 0x2, 0x2, 0x2, 0x29, 0x2a, 0x3, 0x2, 0x2, 0x2, 0x2a, 
    0x2b, 0x3, 0x2, 0x2, 0x2, 0x2b, 0x2c, 0x7, 0x19, 0x2, 0x2, 0x2c, 0x2e, 
    0x7, 0xf, 0x2, 0x2, 0x2d, 0x2f, 0x7, 0x12, 0x2, 0x2, 0x2e, 0x2d, 0x3, 
    0x2, 0x2, 0x2, 0x2e, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x2f, 0x30, 0x3, 0x2, 
    0x2, 0x2, 0x30, 0x31, 0x7, 0x19, 0x2, 0x2, 0x31, 0x7, 0x3, 0x2, 0x2, 
    0x2, 0x32, 0x33, 0x7, 0x1a, 0x2, 0x2, 0x33, 0x35, 0x7, 0xf, 0x2, 0x2, 
    0x34, 0x36, 0x7, 0x12, 0x2, 0x2, 0x35, 0x34, 0x3, 0x2, 0x2, 0x2, 0x35, 
    0x36, 0x3, 0x2, 0x2, 0x2, 0x36, 0x37, 0x3, 0x2, 0x2, 0x2, 0x37, 0x38, 
    0x7, 0x19, 0x2, 0x2, 0x38, 0x39, 0x8, 0x5, 0x1, 0x2, 0x39, 0x9, 0x3, 
    0x2, 0x2, 0x2, 0x3a, 0x3b, 0x9, 0x2, 0x2, 0x2, 0x3b, 0xb, 0x3, 0x2, 
    0x2, 0x2, 0x3c, 0x47, 0x9, 0x3, 0x2, 0x2, 0x3d, 0x41, 0x7, 0x13, 0x2, 
    0x2, 0x3e, 0x40, 0x5, 0xa, 0x6, 0x2, 0x3f, 0x3e, 0x3, 0x2, 0x2, 0x2, 
    0x40, 0x43, 0x3, 0x2, 0x2, 0x2, 0x41, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x41, 
    0x42, 0x3, 0x2, 0x2, 0x2, 0x42, 0x44, 0x3, 0x2, 0x2, 0x2, 0x43, 0x41, 
    0x3, 0x2, 0x2, 0x2, 0x44, 0x46, 0x9, 0x3, 0x2, 0x2, 0x45, 0x3d, 0x3, 
    0x2, 0x2, 0x2, 0x46, 0x49, 0x3, 0x2, 0x2, 0x2, 0x47, 0x45, 0x3, 0x2, 
    0x2, 0x2, 0x47, 0x48, 0x3, 0x2, 0x2, 0x2, 0x48, 0xd, 0x3, 0x2, 0x2, 
    0x2, 0x49, 0x47, 0x3, 0x2, 0x2, 0x2, 0x4a, 0x4c, 0x5, 0xa, 0x6, 0x2, 
    0x4b, 0x4a, 0x3, 0x2, 0x2, 0x2, 0x4c, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x4d, 
    0x4b, 0x3, 0x2, 0x2, 0x2, 0x4d, 0x4e, 0x3, 0x2, 0x2, 0x2, 0x4e, 0x50, 
    0x3, 0x2, 0x2, 0x2, 0x4f, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x50, 0x5a, 0x5, 
    0xc, 0x7, 0x2, 0x51, 0x53, 0x5, 0xa, 0x6, 0x2, 0x52, 0x51, 0x3, 0x2, 
    0x2, 0x2, 0x53, 0x54, 0x3, 0x2, 0x2, 0x2, 0x54, 0x52, 0x3, 0x2, 0x2, 
    0x2, 0x54, 0x55, 0x3, 0x2, 0x2, 0x2, 0x55, 0x56, 0x3, 0x2, 0x2, 0x2, 
    0x56, 0x57, 0x5, 0xc, 0x7, 0x2, 0x57, 0x59, 0x3, 0x2, 0x2, 0x2, 0x58, 
    0x52, 0x3, 0x2, 0x2, 0x2, 0x59, 0x5c, 0x3, 0x2, 0x2, 0x2, 0x5a, 0x58, 
    0x3, 0x2, 0x2, 0x2, 0x5a, 0x5b, 0x3, 0x2, 0x2, 0x2, 0x5b, 0xf, 0x3, 
    0x2, 0x2, 0x2, 0x5c, 0x5a, 0x3, 0x2, 0x2, 0x2, 0x5d, 0x5f, 0x7, 0x14, 
    0x2, 0x2, 0x5e, 0x60, 0x7, 0x12, 0x2, 0x2, 0x5f, 0x5e, 0x3, 0x2, 0x2, 
    0x2, 0x5f, 0x60, 0x3, 0x2, 0x2, 0x2, 0x60, 0x61, 0x3, 0x2, 0x2, 0x2, 
    0x61, 0x62, 0x7, 0x19, 0x2, 0x2, 0x62, 0x64, 0x7, 0x18, 0x2, 0x2, 0x63, 
    0x65, 0x7, 0x12, 0x2, 0x2, 0x64, 0x63, 0x3, 0x2, 0x2, 0x2, 0x64, 0x65, 
    0x3, 0x2, 0x2, 0x2, 0x65, 0x66, 0x3, 0x2, 0x2, 0x2, 0x66, 0x67, 0x7, 
    0x19, 0x2, 0x2, 0x67, 0x68, 0x7, 0x15, 0x2, 0x2, 0x68, 0x11, 0x3, 0x2, 
    0x2, 0x2, 0x69, 0x6a, 0x7, 0x1b, 0x2, 0x2, 0x6a, 0x6b, 0x7, 0xf, 0x2, 
    0x2, 0x6b, 0x6f, 0x5, 0xe, 0x8, 0x2, 0x6c, 0x6d, 0x5, 0xa, 0x6, 0x2, 
    0x6d, 0x6e, 0x5, 0x10, 0x9, 0x2, 0x6e, 0x70, 0x3, 0x2, 0x2, 0x2, 0x6f, 
    0x6c, 0x3, 0x2, 0x2, 0x2, 0x6f, 0x70, 0x3, 0x2, 0x2, 0x2, 0x70, 0x13, 
    0x3, 0x2, 0x2, 0x2, 0x71, 0x72, 0x5, 0xe, 0x8, 0x2, 0x72, 0x73, 0x9, 
    0x4, 0x2, 0x2, 0x73, 0x74, 0x5, 0xe, 0x8, 0x2, 0x74, 0x15, 0x3, 0x2, 
    0x2, 0x2, 0x75, 0x76, 0x7, 0x1b, 0x2, 0x2, 0x76, 0x77, 0x7, 0x4, 0x2, 
    0x2, 0x77, 0x78, 0x5, 0x10, 0x9, 0x2, 0x78, 0x17, 0x3, 0x2, 0x2, 0x2, 
    0x79, 0x7c, 0x5, 0x14, 0xb, 0x2, 0x7a, 0x7c, 0x5, 0x16, 0xc, 0x2, 0x7b, 
    0x79, 0x3, 0x2, 0x2, 0x2, 0x7b, 0x7a, 0x3, 0x2, 0x2, 0x2, 0x7c, 0x7d, 
    0x3, 0x2, 0x2, 0x2, 0x7d, 0x7b, 0x3, 0x2, 0x2, 0x2, 0x7d, 0x7e, 0x3, 
    0x2, 0x2, 0x2, 0x7e, 0x19, 0x3, 0x2, 0x2, 0x2, 0x10, 0x1f, 0x29, 0x2e, 
    0x35, 0x41, 0x47, 0x4d, 0x54, 0x5a, 0x5f, 0x64, 0x6f, 0x7b, 0x7d, 
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
