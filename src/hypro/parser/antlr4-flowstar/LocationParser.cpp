
// Generated from Location.g4 by ANTLR 4.7



#include "LocationParser.h"


	#include <map>
	#include <string>


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
    setState(28);
    match(LocationParser::T__0);
    setState(29);
    match(LocationParser::CBOPEN);
    setState(33);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LocationParser::VARIABLE) {
      setState(30);
      location();
      setState(35);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(36);
    match(LocationParser::CBCLOSE);
   
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
    setState(38);
    match(LocationParser::VARIABLE);
    setState(39);
    match(LocationParser::CBOPEN);
    setState(40);
    activities();
    setState(44);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LocationParser::T__5) {
      setState(41);
      invariants();
      setState(46);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(47);
    match(LocationParser::CBCLOSE);
   
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
    setState(49);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << LocationParser::T__1)
      | (1ULL << LocationParser::T__2)
      | (1ULL << LocationParser::T__3)
      | (1ULL << LocationParser::T__4))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(50);
    match(LocationParser::CBOPEN);
    setState(54);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LocationParser::VARIABLE) {
      setState(51);
      equation();
      setState(56);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(57);
    match(LocationParser::CBCLOSE);
   
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
    setState(59);
    match(LocationParser::T__5);
    setState(60);
    match(LocationParser::CBOPEN);
    setState(62);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << LocationParser::PLUS)
      | (1ULL << LocationParser::MINUS)
      | (1ULL << LocationParser::NUMBER)
      | (1ULL << LocationParser::VARIABLE))) != 0)) {
      setState(61);
      constrset();
    }
    setState(64);
    match(LocationParser::CBCLOSE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReplacedexprContext ------------------------------------------------------------------

LocationParser::ReplacedexprContext::ReplacedexprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> LocationParser::ReplacedexprContext::NUMBER() {
  return getTokens(LocationParser::NUMBER);
}

tree::TerminalNode* LocationParser::ReplacedexprContext::NUMBER(size_t i) {
  return getToken(LocationParser::NUMBER, i);
}

tree::TerminalNode* LocationParser::ReplacedexprContext::EQUALS() {
  return getToken(LocationParser::EQUALS, 0);
}

std::vector<tree::TerminalNode *> LocationParser::ReplacedexprContext::MINUS() {
  return getTokens(LocationParser::MINUS);
}

tree::TerminalNode* LocationParser::ReplacedexprContext::MINUS(size_t i) {
  return getToken(LocationParser::MINUS, i);
}


size_t LocationParser::ReplacedexprContext::getRuleIndex() const {
  return LocationParser::RuleReplacedexpr;
}


LocationParser::ReplacedexprContext* LocationParser::replacedexpr() {
  ReplacedexprContext *_localctx = _tracker.createInstance<ReplacedexprContext>(_ctx, getState());
  enterRule(_localctx, 8, LocationParser::RuleReplacedexpr);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(67);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LocationParser::MINUS) {
      setState(66);
      match(LocationParser::MINUS);
    }
    setState(69);
    match(LocationParser::NUMBER);
    setState(70);
    match(LocationParser::EQUALS);
    setState(72);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LocationParser::MINUS) {
      setState(71);
      match(LocationParser::MINUS);
    }
    setState(74);
    match(LocationParser::NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstantexprContext ------------------------------------------------------------------

LocationParser::ConstantexprContext::ConstantexprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LocationParser::ConstantexprContext::CONSTANT() {
  return getToken(LocationParser::CONSTANT, 0);
}

tree::TerminalNode* LocationParser::ConstantexprContext::EQUALS() {
  return getToken(LocationParser::EQUALS, 0);
}

tree::TerminalNode* LocationParser::ConstantexprContext::NUMBER() {
  return getToken(LocationParser::NUMBER, 0);
}

tree::TerminalNode* LocationParser::ConstantexprContext::MINUS() {
  return getToken(LocationParser::MINUS, 0);
}


size_t LocationParser::ConstantexprContext::getRuleIndex() const {
  return LocationParser::RuleConstantexpr;
}


LocationParser::ConstantexprContext* LocationParser::constantexpr() {
  ConstantexprContext *_localctx = _tracker.createInstance<ConstantexprContext>(_ctx, getState());
  enterRule(_localctx, 10, LocationParser::RuleConstantexpr);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(76);
    dynamic_cast<ConstantexprContext *>(_localctx)->constantToken = match(LocationParser::CONSTANT);
    setState(77);
    match(LocationParser::EQUALS);
    setState(79);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LocationParser::MINUS) {
      setState(78);
      dynamic_cast<ConstantexprContext *>(_localctx)->minusToken = match(LocationParser::MINUS);
    }
    setState(81);
    dynamic_cast<ConstantexprContext *>(_localctx)->numberToken = match(LocationParser::NUMBER);

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
  enterRule(_localctx, 12, LocationParser::RuleConnector);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(84);
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
  enterRule(_localctx, 14, LocationParser::RuleTerm);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(86);
    _la = _input->LA(1);
    if (!(_la == LocationParser::NUMBER

    || _la == LocationParser::VARIABLE)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(97);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LocationParser::TIMES) {
      setState(87);
      match(LocationParser::TIMES);
      setState(91);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == LocationParser::PLUS

      || _la == LocationParser::MINUS) {
        setState(88);
        connector();
        setState(93);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(94);
      _la = _input->LA(1);
      if (!(_la == LocationParser::NUMBER

      || _la == LocationParser::VARIABLE)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(99);
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
  enterRule(_localctx, 16, LocationParser::RulePolynom);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(103);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LocationParser::PLUS

    || _la == LocationParser::MINUS) {
      setState(100);
      connector();
      setState(105);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(106);
    term();
    setState(116);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(108); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(107);
          connector();
          setState(110); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == LocationParser::PLUS

        || _la == LocationParser::MINUS);
        setState(112);
        term(); 
      }
      setState(118);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
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
  enterRule(_localctx, 18, LocationParser::RuleInterval);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(119);
    match(LocationParser::SBOPEN);
    setState(121);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LocationParser::MINUS) {
      setState(120);
      match(LocationParser::MINUS);
    }
    setState(123);
    match(LocationParser::NUMBER);
    setState(124);
    match(LocationParser::COMMA);
    setState(126);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LocationParser::MINUS) {
      setState(125);
      match(LocationParser::MINUS);
    }
    setState(128);
    match(LocationParser::NUMBER);
    setState(129);
    match(LocationParser::SBCLOSE);
   
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

LocationParser::ConnectorContext* LocationParser::EquationContext::connector() {
  return getRuleContext<LocationParser::ConnectorContext>(0);
}

LocationParser::IntervalContext* LocationParser::EquationContext::interval() {
  return getRuleContext<LocationParser::IntervalContext>(0);
}


size_t LocationParser::EquationContext::getRuleIndex() const {
  return LocationParser::RuleEquation;
}


LocationParser::EquationContext* LocationParser::equation() {
  EquationContext *_localctx = _tracker.createInstance<EquationContext>(_ctx, getState());
  enterRule(_localctx, 20, LocationParser::RuleEquation);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(131);
    match(LocationParser::VARIABLE);
    setState(132);
    match(LocationParser::EQUALS);
    setState(133);
    polynom();
    setState(137);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LocationParser::PLUS

    || _la == LocationParser::MINUS) {
      setState(134);
      connector();
      setState(135);
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
  enterRule(_localctx, 22, LocationParser::RuleConstraint);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(139);
    polynom();
    setState(140);
    _la = _input->LA(1);
    if (!(_la == LocationParser::EQUALS

    || _la == LocationParser::BOOLRELATION)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(141);
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
  enterRule(_localctx, 24, LocationParser::RuleIntervalexpr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(143);
    match(LocationParser::VARIABLE);
    setState(144);
    match(LocationParser::IN);
    setState(145);
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
  enterRule(_localctx, 26, LocationParser::RuleConstrset);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(149); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(149);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
      case 1: {
        setState(147);
        constraint();
        break;
      }

      case 2: {
        setState(148);
        intervalexpr();
        break;
      }

      }
      setState(151); 
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
  "modes", "location", "activities", "invariants", "replacedexpr", "constantexpr", 
  "connector", "term", "polynom", "interval", "equation", "constraint", 
  "intervalexpr", "constrset"
};

std::vector<std::string> LocationParser::_literalNames = {
  "", "'modes'", "'poly ode 1'", "'poly ode 2'", "'poly ode 3'", "'linear ode'", 
  "'inv'", "'in'", "'par'", "'jumps'", "'urgent'", "'guard'", "'reset'", 
  "'parallelotope aggregation'", "'box aggregation'", "'->'", "':='", "", 
  "'='", "", "'+'", "'-'", "'*'", "'['", "']'", "'{'", "'}'", "','"
};

std::vector<std::string> LocationParser::_symbolicNames = {
  "", "", "", "", "", "", "", "IN", "PAR", "JUMPS", "URGENT", "GUARD", "RESET", 
  "PARALLELOTOPE", "BOX", "JUMP", "DEFINE", "COMMENT", "EQUALS", "BOOLRELATION", 
  "PLUS", "MINUS", "TIMES", "SBOPEN", "SBCLOSE", "CBOPEN", "CBCLOSE", "COMMA", 
  "NUMBER", "CONSTANT", "VARIABLE", "WS"
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
    0x3, 0x21, 0x9c, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 0x4, 
    0xf, 0x9, 0xf, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x7, 0x2, 0x22, 0xa, 0x2, 
    0xc, 0x2, 0xe, 0x2, 0x25, 0xb, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x7, 0x3, 0x2d, 0xa, 0x3, 0xc, 0x3, 0xe, 0x3, 
    0x30, 0xb, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x7, 
    0x4, 0x37, 0xa, 0x4, 0xc, 0x4, 0xe, 0x4, 0x3a, 0xb, 0x4, 0x3, 0x4, 0x3, 
    0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x5, 0x5, 0x41, 0xa, 0x5, 0x3, 0x5, 
    0x3, 0x5, 0x3, 0x6, 0x5, 0x6, 0x46, 0xa, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 
    0x6, 0x5, 0x6, 0x4b, 0xa, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 
    0x3, 0x7, 0x5, 0x7, 0x52, 0xa, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 
    0x8, 0x3, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x7, 0x9, 0x5c, 0xa, 0x9, 
    0xc, 0x9, 0xe, 0x9, 0x5f, 0xb, 0x9, 0x3, 0x9, 0x7, 0x9, 0x62, 0xa, 0x9, 
    0xc, 0x9, 0xe, 0x9, 0x65, 0xb, 0x9, 0x3, 0xa, 0x7, 0xa, 0x68, 0xa, 0xa, 
    0xc, 0xa, 0xe, 0xa, 0x6b, 0xb, 0xa, 0x3, 0xa, 0x3, 0xa, 0x6, 0xa, 0x6f, 
    0xa, 0xa, 0xd, 0xa, 0xe, 0xa, 0x70, 0x3, 0xa, 0x3, 0xa, 0x7, 0xa, 0x75, 
    0xa, 0xa, 0xc, 0xa, 0xe, 0xa, 0x78, 0xb, 0xa, 0x3, 0xb, 0x3, 0xb, 0x5, 
    0xb, 0x7c, 0xa, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x5, 0xb, 0x81, 0xa, 
    0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 
    0xc, 0x3, 0xc, 0x3, 0xc, 0x5, 0xc, 0x8c, 0xa, 0xc, 0x3, 0xd, 0x3, 0xd, 
    0x3, 0xd, 0x3, 0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xf, 
    0x3, 0xf, 0x6, 0xf, 0x98, 0xa, 0xf, 0xd, 0xf, 0xe, 0xf, 0x99, 0x3, 0xf, 
    0x2, 0x2, 0x10, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 
    0x16, 0x18, 0x1a, 0x1c, 0x2, 0x6, 0x3, 0x2, 0x4, 0x7, 0x3, 0x2, 0x16, 
    0x17, 0x4, 0x2, 0x1e, 0x1e, 0x20, 0x20, 0x3, 0x2, 0x14, 0x15, 0x2, 0x9e, 
    0x2, 0x1e, 0x3, 0x2, 0x2, 0x2, 0x4, 0x28, 0x3, 0x2, 0x2, 0x2, 0x6, 0x33, 
    0x3, 0x2, 0x2, 0x2, 0x8, 0x3d, 0x3, 0x2, 0x2, 0x2, 0xa, 0x45, 0x3, 0x2, 
    0x2, 0x2, 0xc, 0x4e, 0x3, 0x2, 0x2, 0x2, 0xe, 0x56, 0x3, 0x2, 0x2, 0x2, 
    0x10, 0x58, 0x3, 0x2, 0x2, 0x2, 0x12, 0x69, 0x3, 0x2, 0x2, 0x2, 0x14, 
    0x79, 0x3, 0x2, 0x2, 0x2, 0x16, 0x85, 0x3, 0x2, 0x2, 0x2, 0x18, 0x8d, 
    0x3, 0x2, 0x2, 0x2, 0x1a, 0x91, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x97, 0x3, 
    0x2, 0x2, 0x2, 0x1e, 0x1f, 0x7, 0x3, 0x2, 0x2, 0x1f, 0x23, 0x7, 0x1b, 
    0x2, 0x2, 0x20, 0x22, 0x5, 0x4, 0x3, 0x2, 0x21, 0x20, 0x3, 0x2, 0x2, 
    0x2, 0x22, 0x25, 0x3, 0x2, 0x2, 0x2, 0x23, 0x21, 0x3, 0x2, 0x2, 0x2, 
    0x23, 0x24, 0x3, 0x2, 0x2, 0x2, 0x24, 0x26, 0x3, 0x2, 0x2, 0x2, 0x25, 
    0x23, 0x3, 0x2, 0x2, 0x2, 0x26, 0x27, 0x7, 0x1c, 0x2, 0x2, 0x27, 0x3, 
    0x3, 0x2, 0x2, 0x2, 0x28, 0x29, 0x7, 0x20, 0x2, 0x2, 0x29, 0x2a, 0x7, 
    0x1b, 0x2, 0x2, 0x2a, 0x2e, 0x5, 0x6, 0x4, 0x2, 0x2b, 0x2d, 0x5, 0x8, 
    0x5, 0x2, 0x2c, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x2d, 0x30, 0x3, 0x2, 0x2, 
    0x2, 0x2e, 0x2c, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x2f, 0x3, 0x2, 0x2, 0x2, 
    0x2f, 0x31, 0x3, 0x2, 0x2, 0x2, 0x30, 0x2e, 0x3, 0x2, 0x2, 0x2, 0x31, 
    0x32, 0x7, 0x1c, 0x2, 0x2, 0x32, 0x5, 0x3, 0x2, 0x2, 0x2, 0x33, 0x34, 
    0x9, 0x2, 0x2, 0x2, 0x34, 0x38, 0x7, 0x1b, 0x2, 0x2, 0x35, 0x37, 0x5, 
    0x16, 0xc, 0x2, 0x36, 0x35, 0x3, 0x2, 0x2, 0x2, 0x37, 0x3a, 0x3, 0x2, 
    0x2, 0x2, 0x38, 0x36, 0x3, 0x2, 0x2, 0x2, 0x38, 0x39, 0x3, 0x2, 0x2, 
    0x2, 0x39, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x38, 0x3, 0x2, 0x2, 0x2, 
    0x3b, 0x3c, 0x7, 0x1c, 0x2, 0x2, 0x3c, 0x7, 0x3, 0x2, 0x2, 0x2, 0x3d, 
    0x3e, 0x7, 0x8, 0x2, 0x2, 0x3e, 0x40, 0x7, 0x1b, 0x2, 0x2, 0x3f, 0x41, 
    0x5, 0x1c, 0xf, 0x2, 0x40, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x40, 0x41, 0x3, 
    0x2, 0x2, 0x2, 0x41, 0x42, 0x3, 0x2, 0x2, 0x2, 0x42, 0x43, 0x7, 0x1c, 
    0x2, 0x2, 0x43, 0x9, 0x3, 0x2, 0x2, 0x2, 0x44, 0x46, 0x7, 0x17, 0x2, 
    0x2, 0x45, 0x44, 0x3, 0x2, 0x2, 0x2, 0x45, 0x46, 0x3, 0x2, 0x2, 0x2, 
    0x46, 0x47, 0x3, 0x2, 0x2, 0x2, 0x47, 0x48, 0x7, 0x1e, 0x2, 0x2, 0x48, 
    0x4a, 0x7, 0x14, 0x2, 0x2, 0x49, 0x4b, 0x7, 0x17, 0x2, 0x2, 0x4a, 0x49, 
    0x3, 0x2, 0x2, 0x2, 0x4a, 0x4b, 0x3, 0x2, 0x2, 0x2, 0x4b, 0x4c, 0x3, 
    0x2, 0x2, 0x2, 0x4c, 0x4d, 0x7, 0x1e, 0x2, 0x2, 0x4d, 0xb, 0x3, 0x2, 
    0x2, 0x2, 0x4e, 0x4f, 0x7, 0x1f, 0x2, 0x2, 0x4f, 0x51, 0x7, 0x14, 0x2, 
    0x2, 0x50, 0x52, 0x7, 0x17, 0x2, 0x2, 0x51, 0x50, 0x3, 0x2, 0x2, 0x2, 
    0x51, 0x52, 0x3, 0x2, 0x2, 0x2, 0x52, 0x53, 0x3, 0x2, 0x2, 0x2, 0x53, 
    0x54, 0x7, 0x1e, 0x2, 0x2, 0x54, 0x55, 0x8, 0x7, 0x1, 0x2, 0x55, 0xd, 
    0x3, 0x2, 0x2, 0x2, 0x56, 0x57, 0x9, 0x3, 0x2, 0x2, 0x57, 0xf, 0x3, 
    0x2, 0x2, 0x2, 0x58, 0x63, 0x9, 0x4, 0x2, 0x2, 0x59, 0x5d, 0x7, 0x18, 
    0x2, 0x2, 0x5a, 0x5c, 0x5, 0xe, 0x8, 0x2, 0x5b, 0x5a, 0x3, 0x2, 0x2, 
    0x2, 0x5c, 0x5f, 0x3, 0x2, 0x2, 0x2, 0x5d, 0x5b, 0x3, 0x2, 0x2, 0x2, 
    0x5d, 0x5e, 0x3, 0x2, 0x2, 0x2, 0x5e, 0x60, 0x3, 0x2, 0x2, 0x2, 0x5f, 
    0x5d, 0x3, 0x2, 0x2, 0x2, 0x60, 0x62, 0x9, 0x4, 0x2, 0x2, 0x61, 0x59, 
    0x3, 0x2, 0x2, 0x2, 0x62, 0x65, 0x3, 0x2, 0x2, 0x2, 0x63, 0x61, 0x3, 
    0x2, 0x2, 0x2, 0x63, 0x64, 0x3, 0x2, 0x2, 0x2, 0x64, 0x11, 0x3, 0x2, 
    0x2, 0x2, 0x65, 0x63, 0x3, 0x2, 0x2, 0x2, 0x66, 0x68, 0x5, 0xe, 0x8, 
    0x2, 0x67, 0x66, 0x3, 0x2, 0x2, 0x2, 0x68, 0x6b, 0x3, 0x2, 0x2, 0x2, 
    0x69, 0x67, 0x3, 0x2, 0x2, 0x2, 0x69, 0x6a, 0x3, 0x2, 0x2, 0x2, 0x6a, 
    0x6c, 0x3, 0x2, 0x2, 0x2, 0x6b, 0x69, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x76, 
    0x5, 0x10, 0x9, 0x2, 0x6d, 0x6f, 0x5, 0xe, 0x8, 0x2, 0x6e, 0x6d, 0x3, 
    0x2, 0x2, 0x2, 0x6f, 0x70, 0x3, 0x2, 0x2, 0x2, 0x70, 0x6e, 0x3, 0x2, 
    0x2, 0x2, 0x70, 0x71, 0x3, 0x2, 0x2, 0x2, 0x71, 0x72, 0x3, 0x2, 0x2, 
    0x2, 0x72, 0x73, 0x5, 0x10, 0x9, 0x2, 0x73, 0x75, 0x3, 0x2, 0x2, 0x2, 
    0x74, 0x6e, 0x3, 0x2, 0x2, 0x2, 0x75, 0x78, 0x3, 0x2, 0x2, 0x2, 0x76, 
    0x74, 0x3, 0x2, 0x2, 0x2, 0x76, 0x77, 0x3, 0x2, 0x2, 0x2, 0x77, 0x13, 
    0x3, 0x2, 0x2, 0x2, 0x78, 0x76, 0x3, 0x2, 0x2, 0x2, 0x79, 0x7b, 0x7, 
    0x19, 0x2, 0x2, 0x7a, 0x7c, 0x7, 0x17, 0x2, 0x2, 0x7b, 0x7a, 0x3, 0x2, 
    0x2, 0x2, 0x7b, 0x7c, 0x3, 0x2, 0x2, 0x2, 0x7c, 0x7d, 0x3, 0x2, 0x2, 
    0x2, 0x7d, 0x7e, 0x7, 0x1e, 0x2, 0x2, 0x7e, 0x80, 0x7, 0x1d, 0x2, 0x2, 
    0x7f, 0x81, 0x7, 0x17, 0x2, 0x2, 0x80, 0x7f, 0x3, 0x2, 0x2, 0x2, 0x80, 
    0x81, 0x3, 0x2, 0x2, 0x2, 0x81, 0x82, 0x3, 0x2, 0x2, 0x2, 0x82, 0x83, 
    0x7, 0x1e, 0x2, 0x2, 0x83, 0x84, 0x7, 0x1a, 0x2, 0x2, 0x84, 0x15, 0x3, 
    0x2, 0x2, 0x2, 0x85, 0x86, 0x7, 0x20, 0x2, 0x2, 0x86, 0x87, 0x7, 0x14, 
    0x2, 0x2, 0x87, 0x8b, 0x5, 0x12, 0xa, 0x2, 0x88, 0x89, 0x5, 0xe, 0x8, 
    0x2, 0x89, 0x8a, 0x5, 0x14, 0xb, 0x2, 0x8a, 0x8c, 0x3, 0x2, 0x2, 0x2, 
    0x8b, 0x88, 0x3, 0x2, 0x2, 0x2, 0x8b, 0x8c, 0x3, 0x2, 0x2, 0x2, 0x8c, 
    0x17, 0x3, 0x2, 0x2, 0x2, 0x8d, 0x8e, 0x5, 0x12, 0xa, 0x2, 0x8e, 0x8f, 
    0x9, 0x5, 0x2, 0x2, 0x8f, 0x90, 0x5, 0x12, 0xa, 0x2, 0x90, 0x19, 0x3, 
    0x2, 0x2, 0x2, 0x91, 0x92, 0x7, 0x20, 0x2, 0x2, 0x92, 0x93, 0x7, 0x9, 
    0x2, 0x2, 0x93, 0x94, 0x5, 0x14, 0xb, 0x2, 0x94, 0x1b, 0x3, 0x2, 0x2, 
    0x2, 0x95, 0x98, 0x5, 0x18, 0xd, 0x2, 0x96, 0x98, 0x5, 0x1a, 0xe, 0x2, 
    0x97, 0x95, 0x3, 0x2, 0x2, 0x2, 0x97, 0x96, 0x3, 0x2, 0x2, 0x2, 0x98, 
    0x99, 0x3, 0x2, 0x2, 0x2, 0x99, 0x97, 0x3, 0x2, 0x2, 0x2, 0x99, 0x9a, 
    0x3, 0x2, 0x2, 0x2, 0x9a, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x13, 0x23, 0x2e, 
    0x38, 0x40, 0x45, 0x4a, 0x51, 0x5d, 0x63, 0x69, 0x70, 0x76, 0x7b, 0x80, 
    0x8b, 0x97, 0x99, 
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
