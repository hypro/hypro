
// Generated from HybridAutomaton.g4 by ANTLR 4.7


#include "HybridAutomatonVisitor.h"

#include "HybridAutomatonParser.h"


using namespace antlrcpp;
using namespace antlr4;

HybridAutomatonParser::HybridAutomatonParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

HybridAutomatonParser::~HybridAutomatonParser() {
  delete _interpreter;
}

std::string HybridAutomatonParser::getGrammarFileName() const {
  return "HybridAutomaton.g4";
}

const std::vector<std::string>& HybridAutomatonParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& HybridAutomatonParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- StartContext ------------------------------------------------------------------

HybridAutomatonParser::StartContext::StartContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HybridAutomatonParser::VardeclarationContext* HybridAutomatonParser::StartContext::vardeclaration() {
  return getRuleContext<HybridAutomatonParser::VardeclarationContext>(0);
}

HybridAutomatonParser::ModesContext* HybridAutomatonParser::StartContext::modes() {
  return getRuleContext<HybridAutomatonParser::ModesContext>(0);
}

HybridAutomatonParser::JumpsContext* HybridAutomatonParser::StartContext::jumps() {
  return getRuleContext<HybridAutomatonParser::JumpsContext>(0);
}

HybridAutomatonParser::InitContext* HybridAutomatonParser::StartContext::init() {
  return getRuleContext<HybridAutomatonParser::InitContext>(0);
}


size_t HybridAutomatonParser::StartContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleStart;
}

antlrcpp::Any HybridAutomatonParser::StartContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitStart(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::StartContext* HybridAutomatonParser::start() {
  StartContext *_localctx = _tracker.createInstance<StartContext>(_ctx, getState());
  enterRule(_localctx, 0, HybridAutomatonParser::RuleStart);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(44);
    match(HybridAutomatonParser::T__0);
    setState(45);
    match(HybridAutomatonParser::T__1);
    setState(46);
    vardeclaration();
    setState(47);
    modes();
    setState(48);
    jumps();
    setState(49);
    init();
    setState(50);
    match(HybridAutomatonParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VardeclarationContext ------------------------------------------------------------------

HybridAutomatonParser::VardeclarationContext::VardeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> HybridAutomatonParser::VardeclarationContext::VARIABLE() {
  return getTokens(HybridAutomatonParser::VARIABLE);
}

tree::TerminalNode* HybridAutomatonParser::VardeclarationContext::VARIABLE(size_t i) {
  return getToken(HybridAutomatonParser::VARIABLE, i);
}


size_t HybridAutomatonParser::VardeclarationContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleVardeclaration;
}

antlrcpp::Any HybridAutomatonParser::VardeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitVardeclaration(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::VardeclarationContext* HybridAutomatonParser::vardeclaration() {
  VardeclarationContext *_localctx = _tracker.createInstance<VardeclarationContext>(_ctx, getState());
  enterRule(_localctx, 2, HybridAutomatonParser::RuleVardeclaration);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(52);
    match(HybridAutomatonParser::T__3);
    setState(53);
    match(HybridAutomatonParser::VARIABLE);
    setState(60);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HybridAutomatonParser::T__4) {
      setState(56); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(54);
        match(HybridAutomatonParser::T__4);
        setState(55);
        match(HybridAutomatonParser::VARIABLE);
        setState(58); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == HybridAutomatonParser::T__4);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ModesContext ------------------------------------------------------------------

HybridAutomatonParser::ModesContext::ModesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridAutomatonParser::LocationContext *> HybridAutomatonParser::ModesContext::location() {
  return getRuleContexts<HybridAutomatonParser::LocationContext>();
}

HybridAutomatonParser::LocationContext* HybridAutomatonParser::ModesContext::location(size_t i) {
  return getRuleContext<HybridAutomatonParser::LocationContext>(i);
}


size_t HybridAutomatonParser::ModesContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleModes;
}

antlrcpp::Any HybridAutomatonParser::ModesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitModes(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::ModesContext* HybridAutomatonParser::modes() {
  ModesContext *_localctx = _tracker.createInstance<ModesContext>(_ctx, getState());
  enterRule(_localctx, 4, HybridAutomatonParser::RuleModes);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(62);
    match(HybridAutomatonParser::T__5);
    setState(63);
    match(HybridAutomatonParser::T__1);
    setState(67);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HybridAutomatonParser::VARIABLE) {
      setState(64);
      location();
      setState(69);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(70);
    match(HybridAutomatonParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LocationContext ------------------------------------------------------------------

HybridAutomatonParser::LocationContext::LocationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HybridAutomatonParser::LocationContext::VARIABLE() {
  return getToken(HybridAutomatonParser::VARIABLE, 0);
}

HybridAutomatonParser::ActivitiesContext* HybridAutomatonParser::LocationContext::activities() {
  return getRuleContext<HybridAutomatonParser::ActivitiesContext>(0);
}

HybridAutomatonParser::InvariantsContext* HybridAutomatonParser::LocationContext::invariants() {
  return getRuleContext<HybridAutomatonParser::InvariantsContext>(0);
}


size_t HybridAutomatonParser::LocationContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleLocation;
}

antlrcpp::Any HybridAutomatonParser::LocationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitLocation(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::LocationContext* HybridAutomatonParser::location() {
  LocationContext *_localctx = _tracker.createInstance<LocationContext>(_ctx, getState());
  enterRule(_localctx, 6, HybridAutomatonParser::RuleLocation);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(72);
    match(HybridAutomatonParser::VARIABLE);
    setState(73);
    match(HybridAutomatonParser::T__1);
    setState(74);
    activities();
    setState(75);
    invariants();
    setState(76);
    match(HybridAutomatonParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ActivitiesContext ------------------------------------------------------------------

HybridAutomatonParser::ActivitiesContext::ActivitiesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridAutomatonParser::EquationContext *> HybridAutomatonParser::ActivitiesContext::equation() {
  return getRuleContexts<HybridAutomatonParser::EquationContext>();
}

HybridAutomatonParser::EquationContext* HybridAutomatonParser::ActivitiesContext::equation(size_t i) {
  return getRuleContext<HybridAutomatonParser::EquationContext>(i);
}


size_t HybridAutomatonParser::ActivitiesContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleActivities;
}

antlrcpp::Any HybridAutomatonParser::ActivitiesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitActivities(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::ActivitiesContext* HybridAutomatonParser::activities() {
  ActivitiesContext *_localctx = _tracker.createInstance<ActivitiesContext>(_ctx, getState());
  enterRule(_localctx, 8, HybridAutomatonParser::RuleActivities);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(78);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << HybridAutomatonParser::T__6)
      | (1ULL << HybridAutomatonParser::T__7)
      | (1ULL << HybridAutomatonParser::T__8)
      | (1ULL << HybridAutomatonParser::T__9))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(79);
    match(HybridAutomatonParser::T__1);
    setState(83);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HybridAutomatonParser::VARIABLE) {
      setState(80);
      equation();
      setState(85);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(86);
    match(HybridAutomatonParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InvariantsContext ------------------------------------------------------------------

HybridAutomatonParser::InvariantsContext::InvariantsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridAutomatonParser::ConstraintContext *> HybridAutomatonParser::InvariantsContext::constraint() {
  return getRuleContexts<HybridAutomatonParser::ConstraintContext>();
}

HybridAutomatonParser::ConstraintContext* HybridAutomatonParser::InvariantsContext::constraint(size_t i) {
  return getRuleContext<HybridAutomatonParser::ConstraintContext>(i);
}

std::vector<HybridAutomatonParser::IntervalexprContext *> HybridAutomatonParser::InvariantsContext::intervalexpr() {
  return getRuleContexts<HybridAutomatonParser::IntervalexprContext>();
}

HybridAutomatonParser::IntervalexprContext* HybridAutomatonParser::InvariantsContext::intervalexpr(size_t i) {
  return getRuleContext<HybridAutomatonParser::IntervalexprContext>(i);
}


size_t HybridAutomatonParser::InvariantsContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleInvariants;
}

antlrcpp::Any HybridAutomatonParser::InvariantsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitInvariants(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::InvariantsContext* HybridAutomatonParser::invariants() {
  InvariantsContext *_localctx = _tracker.createInstance<InvariantsContext>(_ctx, getState());
  enterRule(_localctx, 10, HybridAutomatonParser::RuleInvariants);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(88);
    match(HybridAutomatonParser::T__10);
    setState(89);
    match(HybridAutomatonParser::T__1);
    setState(94);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HybridAutomatonParser::NUMBER

    || _la == HybridAutomatonParser::VARIABLE) {
      setState(92);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
      case 1: {
        setState(90);
        constraint();
        break;
      }

      case 2: {
        setState(91);
        intervalexpr();
        break;
      }

      }
      setState(96);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(97);
    match(HybridAutomatonParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TermContext ------------------------------------------------------------------

HybridAutomatonParser::TermContext::TermContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> HybridAutomatonParser::TermContext::NUMBER() {
  return getTokens(HybridAutomatonParser::NUMBER);
}

tree::TerminalNode* HybridAutomatonParser::TermContext::NUMBER(size_t i) {
  return getToken(HybridAutomatonParser::NUMBER, i);
}

std::vector<tree::TerminalNode *> HybridAutomatonParser::TermContext::VARIABLE() {
  return getTokens(HybridAutomatonParser::VARIABLE);
}

tree::TerminalNode* HybridAutomatonParser::TermContext::VARIABLE(size_t i) {
  return getToken(HybridAutomatonParser::VARIABLE, i);
}

std::vector<tree::TerminalNode *> HybridAutomatonParser::TermContext::TIMES() {
  return getTokens(HybridAutomatonParser::TIMES);
}

tree::TerminalNode* HybridAutomatonParser::TermContext::TIMES(size_t i) {
  return getToken(HybridAutomatonParser::TIMES, i);
}


size_t HybridAutomatonParser::TermContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleTerm;
}

antlrcpp::Any HybridAutomatonParser::TermContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitTerm(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::TermContext* HybridAutomatonParser::term() {
  TermContext *_localctx = _tracker.createInstance<TermContext>(_ctx, getState());
  enterRule(_localctx, 12, HybridAutomatonParser::RuleTerm);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(99);
    _la = _input->LA(1);
    if (!(_la == HybridAutomatonParser::NUMBER

    || _la == HybridAutomatonParser::VARIABLE)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(104);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HybridAutomatonParser::TIMES) {
      setState(100);
      match(HybridAutomatonParser::TIMES);
      setState(101);
      _la = _input->LA(1);
      if (!(_la == HybridAutomatonParser::NUMBER

      || _la == HybridAutomatonParser::VARIABLE)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(106);
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

HybridAutomatonParser::PolynomContext::PolynomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridAutomatonParser::TermContext *> HybridAutomatonParser::PolynomContext::term() {
  return getRuleContexts<HybridAutomatonParser::TermContext>();
}

HybridAutomatonParser::TermContext* HybridAutomatonParser::PolynomContext::term(size_t i) {
  return getRuleContext<HybridAutomatonParser::TermContext>(i);
}

std::vector<tree::TerminalNode *> HybridAutomatonParser::PolynomContext::PLUS() {
  return getTokens(HybridAutomatonParser::PLUS);
}

tree::TerminalNode* HybridAutomatonParser::PolynomContext::PLUS(size_t i) {
  return getToken(HybridAutomatonParser::PLUS, i);
}


size_t HybridAutomatonParser::PolynomContext::getRuleIndex() const {
  return HybridAutomatonParser::RulePolynom;
}

antlrcpp::Any HybridAutomatonParser::PolynomContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitPolynom(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::PolynomContext* HybridAutomatonParser::polynom() {
  PolynomContext *_localctx = _tracker.createInstance<PolynomContext>(_ctx, getState());
  enterRule(_localctx, 14, HybridAutomatonParser::RulePolynom);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(107);
    term();
    setState(112);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HybridAutomatonParser::PLUS) {
      setState(108);
      match(HybridAutomatonParser::PLUS);
      setState(109);
      term();
      setState(114);
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

HybridAutomatonParser::IntervalContext::IntervalContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> HybridAutomatonParser::IntervalContext::NUMBER() {
  return getTokens(HybridAutomatonParser::NUMBER);
}

tree::TerminalNode* HybridAutomatonParser::IntervalContext::NUMBER(size_t i) {
  return getToken(HybridAutomatonParser::NUMBER, i);
}


size_t HybridAutomatonParser::IntervalContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleInterval;
}

antlrcpp::Any HybridAutomatonParser::IntervalContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitInterval(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::IntervalContext* HybridAutomatonParser::interval() {
  IntervalContext *_localctx = _tracker.createInstance<IntervalContext>(_ctx, getState());
  enterRule(_localctx, 16, HybridAutomatonParser::RuleInterval);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(115);
    match(HybridAutomatonParser::T__11);
    setState(116);
    match(HybridAutomatonParser::NUMBER);
    setState(117);
    match(HybridAutomatonParser::T__4);
    setState(118);
    match(HybridAutomatonParser::NUMBER);
    setState(119);
    match(HybridAutomatonParser::T__12);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EquationContext ------------------------------------------------------------------

HybridAutomatonParser::EquationContext::EquationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HybridAutomatonParser::EquationContext::VARIABLE() {
  return getToken(HybridAutomatonParser::VARIABLE, 0);
}

tree::TerminalNode* HybridAutomatonParser::EquationContext::EQUALS() {
  return getToken(HybridAutomatonParser::EQUALS, 0);
}

HybridAutomatonParser::PolynomContext* HybridAutomatonParser::EquationContext::polynom() {
  return getRuleContext<HybridAutomatonParser::PolynomContext>(0);
}


size_t HybridAutomatonParser::EquationContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleEquation;
}

antlrcpp::Any HybridAutomatonParser::EquationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitEquation(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::EquationContext* HybridAutomatonParser::equation() {
  EquationContext *_localctx = _tracker.createInstance<EquationContext>(_ctx, getState());
  enterRule(_localctx, 18, HybridAutomatonParser::RuleEquation);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(121);
    match(HybridAutomatonParser::VARIABLE);
    setState(122);
    match(HybridAutomatonParser::EQUALS);
    setState(123);
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

HybridAutomatonParser::ConstraintContext::ConstraintContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridAutomatonParser::PolynomContext *> HybridAutomatonParser::ConstraintContext::polynom() {
  return getRuleContexts<HybridAutomatonParser::PolynomContext>();
}

HybridAutomatonParser::PolynomContext* HybridAutomatonParser::ConstraintContext::polynom(size_t i) {
  return getRuleContext<HybridAutomatonParser::PolynomContext>(i);
}

tree::TerminalNode* HybridAutomatonParser::ConstraintContext::BOOLRELATION() {
  return getToken(HybridAutomatonParser::BOOLRELATION, 0);
}

tree::TerminalNode* HybridAutomatonParser::ConstraintContext::EQUALS() {
  return getToken(HybridAutomatonParser::EQUALS, 0);
}


size_t HybridAutomatonParser::ConstraintContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleConstraint;
}

antlrcpp::Any HybridAutomatonParser::ConstraintContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitConstraint(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::ConstraintContext* HybridAutomatonParser::constraint() {
  ConstraintContext *_localctx = _tracker.createInstance<ConstraintContext>(_ctx, getState());
  enterRule(_localctx, 20, HybridAutomatonParser::RuleConstraint);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(125);
    polynom();
    setState(126);
    _la = _input->LA(1);
    if (!(_la == HybridAutomatonParser::EQUALS

    || _la == HybridAutomatonParser::BOOLRELATION)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(127);
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

HybridAutomatonParser::IntervalexprContext::IntervalexprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HybridAutomatonParser::IntervalexprContext::VARIABLE() {
  return getToken(HybridAutomatonParser::VARIABLE, 0);
}

tree::TerminalNode* HybridAutomatonParser::IntervalexprContext::IN() {
  return getToken(HybridAutomatonParser::IN, 0);
}

HybridAutomatonParser::IntervalContext* HybridAutomatonParser::IntervalexprContext::interval() {
  return getRuleContext<HybridAutomatonParser::IntervalContext>(0);
}


size_t HybridAutomatonParser::IntervalexprContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleIntervalexpr;
}

antlrcpp::Any HybridAutomatonParser::IntervalexprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitIntervalexpr(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::IntervalexprContext* HybridAutomatonParser::intervalexpr() {
  IntervalexprContext *_localctx = _tracker.createInstance<IntervalexprContext>(_ctx, getState());
  enterRule(_localctx, 22, HybridAutomatonParser::RuleIntervalexpr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(129);
    match(HybridAutomatonParser::VARIABLE);
    setState(130);
    match(HybridAutomatonParser::IN);
    setState(131);
    interval();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- JumpsContext ------------------------------------------------------------------

HybridAutomatonParser::JumpsContext::JumpsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridAutomatonParser::TransitionContext *> HybridAutomatonParser::JumpsContext::transition() {
  return getRuleContexts<HybridAutomatonParser::TransitionContext>();
}

HybridAutomatonParser::TransitionContext* HybridAutomatonParser::JumpsContext::transition(size_t i) {
  return getRuleContext<HybridAutomatonParser::TransitionContext>(i);
}


size_t HybridAutomatonParser::JumpsContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleJumps;
}

antlrcpp::Any HybridAutomatonParser::JumpsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitJumps(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::JumpsContext* HybridAutomatonParser::jumps() {
  JumpsContext *_localctx = _tracker.createInstance<JumpsContext>(_ctx, getState());
  enterRule(_localctx, 24, HybridAutomatonParser::RuleJumps);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(133);
    match(HybridAutomatonParser::T__13);
    setState(134);
    match(HybridAutomatonParser::T__1);
    setState(138);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HybridAutomatonParser::VARIABLE) {
      setState(135);
      transition();
      setState(140);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(141);
    match(HybridAutomatonParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TransitionContext ------------------------------------------------------------------

HybridAutomatonParser::TransitionContext::TransitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HybridAutomatonParser::FromtoContext* HybridAutomatonParser::TransitionContext::fromto() {
  return getRuleContext<HybridAutomatonParser::FromtoContext>(0);
}

std::vector<HybridAutomatonParser::UrgentContext *> HybridAutomatonParser::TransitionContext::urgent() {
  return getRuleContexts<HybridAutomatonParser::UrgentContext>();
}

HybridAutomatonParser::UrgentContext* HybridAutomatonParser::TransitionContext::urgent(size_t i) {
  return getRuleContext<HybridAutomatonParser::UrgentContext>(i);
}

std::vector<HybridAutomatonParser::GuardContext *> HybridAutomatonParser::TransitionContext::guard() {
  return getRuleContexts<HybridAutomatonParser::GuardContext>();
}

HybridAutomatonParser::GuardContext* HybridAutomatonParser::TransitionContext::guard(size_t i) {
  return getRuleContext<HybridAutomatonParser::GuardContext>(i);
}

std::vector<HybridAutomatonParser::ResetfctContext *> HybridAutomatonParser::TransitionContext::resetfct() {
  return getRuleContexts<HybridAutomatonParser::ResetfctContext>();
}

HybridAutomatonParser::ResetfctContext* HybridAutomatonParser::TransitionContext::resetfct(size_t i) {
  return getRuleContext<HybridAutomatonParser::ResetfctContext>(i);
}

std::vector<HybridAutomatonParser::AggregationContext *> HybridAutomatonParser::TransitionContext::aggregation() {
  return getRuleContexts<HybridAutomatonParser::AggregationContext>();
}

HybridAutomatonParser::AggregationContext* HybridAutomatonParser::TransitionContext::aggregation(size_t i) {
  return getRuleContext<HybridAutomatonParser::AggregationContext>(i);
}


size_t HybridAutomatonParser::TransitionContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleTransition;
}

antlrcpp::Any HybridAutomatonParser::TransitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitTransition(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::TransitionContext* HybridAutomatonParser::transition() {
  TransitionContext *_localctx = _tracker.createInstance<TransitionContext>(_ctx, getState());
  enterRule(_localctx, 26, HybridAutomatonParser::RuleTransition);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(143);
    fromto();
    setState(150);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << HybridAutomatonParser::T__14)
      | (1ULL << HybridAutomatonParser::T__15)
      | (1ULL << HybridAutomatonParser::T__16)
      | (1ULL << HybridAutomatonParser::PARALLELOTOPE)
      | (1ULL << HybridAutomatonParser::BOX))) != 0)) {
      setState(148);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case HybridAutomatonParser::T__14: {
          setState(144);
          urgent();
          break;
        }

        case HybridAutomatonParser::T__15: {
          setState(145);
          guard();
          break;
        }

        case HybridAutomatonParser::T__16: {
          setState(146);
          resetfct();
          break;
        }

        case HybridAutomatonParser::PARALLELOTOPE:
        case HybridAutomatonParser::BOX: {
          setState(147);
          aggregation();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(152);
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

//----------------- FromtoContext ------------------------------------------------------------------

HybridAutomatonParser::FromtoContext::FromtoContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> HybridAutomatonParser::FromtoContext::VARIABLE() {
  return getTokens(HybridAutomatonParser::VARIABLE);
}

tree::TerminalNode* HybridAutomatonParser::FromtoContext::VARIABLE(size_t i) {
  return getToken(HybridAutomatonParser::VARIABLE, i);
}

tree::TerminalNode* HybridAutomatonParser::FromtoContext::JUMP() {
  return getToken(HybridAutomatonParser::JUMP, 0);
}


size_t HybridAutomatonParser::FromtoContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleFromto;
}

antlrcpp::Any HybridAutomatonParser::FromtoContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitFromto(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::FromtoContext* HybridAutomatonParser::fromto() {
  FromtoContext *_localctx = _tracker.createInstance<FromtoContext>(_ctx, getState());
  enterRule(_localctx, 28, HybridAutomatonParser::RuleFromto);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(153);
    match(HybridAutomatonParser::VARIABLE);
    setState(154);
    match(HybridAutomatonParser::JUMP);
    setState(155);
    match(HybridAutomatonParser::VARIABLE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UrgentContext ------------------------------------------------------------------

HybridAutomatonParser::UrgentContext::UrgentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t HybridAutomatonParser::UrgentContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleUrgent;
}

antlrcpp::Any HybridAutomatonParser::UrgentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitUrgent(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::UrgentContext* HybridAutomatonParser::urgent() {
  UrgentContext *_localctx = _tracker.createInstance<UrgentContext>(_ctx, getState());
  enterRule(_localctx, 30, HybridAutomatonParser::RuleUrgent);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(157);
    match(HybridAutomatonParser::T__14);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GuardContext ------------------------------------------------------------------

HybridAutomatonParser::GuardContext::GuardContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridAutomatonParser::ConstraintContext *> HybridAutomatonParser::GuardContext::constraint() {
  return getRuleContexts<HybridAutomatonParser::ConstraintContext>();
}

HybridAutomatonParser::ConstraintContext* HybridAutomatonParser::GuardContext::constraint(size_t i) {
  return getRuleContext<HybridAutomatonParser::ConstraintContext>(i);
}

std::vector<HybridAutomatonParser::IntervalexprContext *> HybridAutomatonParser::GuardContext::intervalexpr() {
  return getRuleContexts<HybridAutomatonParser::IntervalexprContext>();
}

HybridAutomatonParser::IntervalexprContext* HybridAutomatonParser::GuardContext::intervalexpr(size_t i) {
  return getRuleContext<HybridAutomatonParser::IntervalexprContext>(i);
}


size_t HybridAutomatonParser::GuardContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleGuard;
}

antlrcpp::Any HybridAutomatonParser::GuardContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitGuard(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::GuardContext* HybridAutomatonParser::guard() {
  GuardContext *_localctx = _tracker.createInstance<GuardContext>(_ctx, getState());
  enterRule(_localctx, 32, HybridAutomatonParser::RuleGuard);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(159);
    match(HybridAutomatonParser::T__15);
    setState(160);
    match(HybridAutomatonParser::T__1);
    setState(165);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HybridAutomatonParser::NUMBER

    || _la == HybridAutomatonParser::VARIABLE) {
      setState(163);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
      case 1: {
        setState(161);
        constraint();
        break;
      }

      case 2: {
        setState(162);
        intervalexpr();
        break;
      }

      }
      setState(167);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(168);
    match(HybridAutomatonParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AllocationContext ------------------------------------------------------------------

HybridAutomatonParser::AllocationContext::AllocationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HybridAutomatonParser::AllocationContext::VARIABLE() {
  return getToken(HybridAutomatonParser::VARIABLE, 0);
}

tree::TerminalNode* HybridAutomatonParser::AllocationContext::DEFINE() {
  return getToken(HybridAutomatonParser::DEFINE, 0);
}

HybridAutomatonParser::PolynomContext* HybridAutomatonParser::AllocationContext::polynom() {
  return getRuleContext<HybridAutomatonParser::PolynomContext>(0);
}

HybridAutomatonParser::IntervalContext* HybridAutomatonParser::AllocationContext::interval() {
  return getRuleContext<HybridAutomatonParser::IntervalContext>(0);
}


size_t HybridAutomatonParser::AllocationContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleAllocation;
}

antlrcpp::Any HybridAutomatonParser::AllocationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitAllocation(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::AllocationContext* HybridAutomatonParser::allocation() {
  AllocationContext *_localctx = _tracker.createInstance<AllocationContext>(_ctx, getState());
  enterRule(_localctx, 34, HybridAutomatonParser::RuleAllocation);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(170);
    match(HybridAutomatonParser::VARIABLE);
    setState(171);
    match(HybridAutomatonParser::DEFINE);
    setState(174);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case HybridAutomatonParser::NUMBER:
      case HybridAutomatonParser::VARIABLE: {
        setState(172);
        polynom();
        break;
      }

      case HybridAutomatonParser::T__11: {
        setState(173);
        interval();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ResetfctContext ------------------------------------------------------------------

HybridAutomatonParser::ResetfctContext::ResetfctContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridAutomatonParser::AllocationContext *> HybridAutomatonParser::ResetfctContext::allocation() {
  return getRuleContexts<HybridAutomatonParser::AllocationContext>();
}

HybridAutomatonParser::AllocationContext* HybridAutomatonParser::ResetfctContext::allocation(size_t i) {
  return getRuleContext<HybridAutomatonParser::AllocationContext>(i);
}


size_t HybridAutomatonParser::ResetfctContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleResetfct;
}

antlrcpp::Any HybridAutomatonParser::ResetfctContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitResetfct(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::ResetfctContext* HybridAutomatonParser::resetfct() {
  ResetfctContext *_localctx = _tracker.createInstance<ResetfctContext>(_ctx, getState());
  enterRule(_localctx, 36, HybridAutomatonParser::RuleResetfct);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(176);
    match(HybridAutomatonParser::T__16);
    setState(177);
    match(HybridAutomatonParser::T__1);
    setState(181);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HybridAutomatonParser::VARIABLE) {
      setState(178);
      allocation();
      setState(183);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(184);
    match(HybridAutomatonParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AggregationContext ------------------------------------------------------------------

HybridAutomatonParser::AggregationContext::AggregationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HybridAutomatonParser::AggregationContext::PARALLELOTOPE() {
  return getToken(HybridAutomatonParser::PARALLELOTOPE, 0);
}

tree::TerminalNode* HybridAutomatonParser::AggregationContext::BOX() {
  return getToken(HybridAutomatonParser::BOX, 0);
}


size_t HybridAutomatonParser::AggregationContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleAggregation;
}

antlrcpp::Any HybridAutomatonParser::AggregationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitAggregation(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::AggregationContext* HybridAutomatonParser::aggregation() {
  AggregationContext *_localctx = _tracker.createInstance<AggregationContext>(_ctx, getState());
  enterRule(_localctx, 38, HybridAutomatonParser::RuleAggregation);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(186);
    _la = _input->LA(1);
    if (!(_la == HybridAutomatonParser::PARALLELOTOPE

    || _la == HybridAutomatonParser::BOX)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(187);
    match(HybridAutomatonParser::T__1);
    setState(188);
    match(HybridAutomatonParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InitContext ------------------------------------------------------------------

HybridAutomatonParser::InitContext::InitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HybridAutomatonParser::InitstateContext* HybridAutomatonParser::InitContext::initstate() {
  return getRuleContext<HybridAutomatonParser::InitstateContext>(0);
}


size_t HybridAutomatonParser::InitContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleInit;
}

antlrcpp::Any HybridAutomatonParser::InitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitInit(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::InitContext* HybridAutomatonParser::init() {
  InitContext *_localctx = _tracker.createInstance<InitContext>(_ctx, getState());
  enterRule(_localctx, 40, HybridAutomatonParser::RuleInit);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(190);
    match(HybridAutomatonParser::T__17);
    setState(191);
    match(HybridAutomatonParser::T__1);
    setState(192);
    initstate();
    setState(193);
    match(HybridAutomatonParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InitstateContext ------------------------------------------------------------------

HybridAutomatonParser::InitstateContext::InitstateContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HybridAutomatonParser::InitstateContext::VARIABLE() {
  return getToken(HybridAutomatonParser::VARIABLE, 0);
}

std::vector<HybridAutomatonParser::ConstraintContext *> HybridAutomatonParser::InitstateContext::constraint() {
  return getRuleContexts<HybridAutomatonParser::ConstraintContext>();
}

HybridAutomatonParser::ConstraintContext* HybridAutomatonParser::InitstateContext::constraint(size_t i) {
  return getRuleContext<HybridAutomatonParser::ConstraintContext>(i);
}

std::vector<HybridAutomatonParser::IntervalexprContext *> HybridAutomatonParser::InitstateContext::intervalexpr() {
  return getRuleContexts<HybridAutomatonParser::IntervalexprContext>();
}

HybridAutomatonParser::IntervalexprContext* HybridAutomatonParser::InitstateContext::intervalexpr(size_t i) {
  return getRuleContext<HybridAutomatonParser::IntervalexprContext>(i);
}


size_t HybridAutomatonParser::InitstateContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleInitstate;
}

antlrcpp::Any HybridAutomatonParser::InitstateContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitInitstate(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::InitstateContext* HybridAutomatonParser::initstate() {
  InitstateContext *_localctx = _tracker.createInstance<InitstateContext>(_ctx, getState());
  enterRule(_localctx, 42, HybridAutomatonParser::RuleInitstate);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(195);
    match(HybridAutomatonParser::VARIABLE);
    setState(196);
    match(HybridAutomatonParser::T__1);
    setState(201);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HybridAutomatonParser::NUMBER

    || _la == HybridAutomatonParser::VARIABLE) {
      setState(199);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
      case 1: {
        setState(197);
        constraint();
        break;
      }

      case 2: {
        setState(198);
        intervalexpr();
        break;
      }

      }
      setState(203);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(204);
    match(HybridAutomatonParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> HybridAutomatonParser::_decisionToDFA;
atn::PredictionContextCache HybridAutomatonParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN HybridAutomatonParser::_atn;
std::vector<uint16_t> HybridAutomatonParser::_serializedATN;

std::vector<std::string> HybridAutomatonParser::_ruleNames = {
  "start", "vardeclaration", "modes", "location", "activities", "invariants", 
  "term", "polynom", "interval", "equation", "constraint", "intervalexpr", 
  "jumps", "transition", "fromto", "urgent", "guard", "allocation", "resetfct", 
  "aggregation", "init", "initstate"
};

std::vector<std::string> HybridAutomatonParser::_literalNames = {
  "", "'hybrid reachability'", "'{'", "'}'", "'state var'", "','", "'modes'", 
  "'poly ode 1'", "'poly ode 2'", "'poly ode 3'", "'linear ode'", "'inv'", 
  "'['", "']'", "'jumps'", "'urgent'", "'guard'", "'reset'", "'init'", "'in'", 
  "", "'='", "", "'+'", "'*'", "", "", "", "'parallelotope aggregation'", 
  "'box aggregation'", "'->'", "':='"
};

std::vector<std::string> HybridAutomatonParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "IN", "COMMENT", "EQUALS", "BOOLRELATION", "PLUS", "TIMES", "NUMBER", 
  "VARIABLE", "WS", "PARALLELOTOPE", "BOX", "JUMP", "DEFINE"
};

dfa::Vocabulary HybridAutomatonParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> HybridAutomatonParser::_tokenNames;

HybridAutomatonParser::Initializer::Initializer() {
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
    0x3, 0x21, 0xd1, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 0x4, 
    0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 0x12, 
    0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x4, 0x15, 0x9, 
    0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 0x9, 0x17, 0x3, 0x2, 0x3, 0x2, 
    0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x6, 0x3, 0x3b, 0xa, 0x3, 0xd, 0x3, 0xe, 
    0x3, 0x3c, 0x5, 0x3, 0x3f, 0xa, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x7, 
    0x4, 0x44, 0xa, 0x4, 0xc, 0x4, 0xe, 0x4, 0x47, 0xb, 0x4, 0x3, 0x4, 0x3, 
    0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 
    0x6, 0x3, 0x6, 0x3, 0x6, 0x7, 0x6, 0x54, 0xa, 0x6, 0xc, 0x6, 0xe, 0x6, 
    0x57, 0xb, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 
    0x7, 0x7, 0x7, 0x5f, 0xa, 0x7, 0xc, 0x7, 0xe, 0x7, 0x62, 0xb, 0x7, 0x3, 
    0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x7, 0x8, 0x69, 0xa, 0x8, 
    0xc, 0x8, 0xe, 0x8, 0x6c, 0xb, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x7, 
    0x9, 0x71, 0xa, 0x9, 0xc, 0x9, 0xe, 0x9, 0x74, 0xb, 0x9, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 
    0xb, 0x3, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xd, 0x3, 
    0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x7, 0xe, 0x8b, 
    0xa, 0xe, 0xc, 0xe, 0xe, 0xe, 0x8e, 0xb, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 
    0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x7, 0xf, 0x97, 0xa, 0xf, 
    0xc, 0xf, 0xe, 0xf, 0x9a, 0xb, 0xf, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 
    0x3, 0x10, 0x3, 0x11, 0x3, 0x11, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 
    0x12, 0x7, 0x12, 0xa6, 0xa, 0x12, 0xc, 0x12, 0xe, 0x12, 0xa9, 0xb, 0x12, 
    0x3, 0x12, 0x3, 0x12, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x5, 
    0x13, 0xb1, 0xa, 0x13, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x7, 0x14, 0xb6, 
    0xa, 0x14, 0xc, 0x14, 0xe, 0x14, 0xb9, 0xb, 0x14, 0x3, 0x14, 0x3, 0x14, 
    0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x16, 0x3, 0x16, 0x3, 
    0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 
    0x7, 0x17, 0xca, 0xa, 0x17, 0xc, 0x17, 0xe, 0x17, 0xcd, 0xb, 0x17, 0x3, 
    0x17, 0x3, 0x17, 0x3, 0x17, 0x2, 0x2, 0x18, 0x2, 0x4, 0x6, 0x8, 0xa, 
    0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 
    0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2, 0x6, 0x3, 0x2, 0x9, 0xc, 0x3, 0x2, 
    0x1b, 0x1c, 0x3, 0x2, 0x17, 0x18, 0x3, 0x2, 0x1e, 0x1f, 0x2, 0xcd, 0x2, 
    0x2e, 0x3, 0x2, 0x2, 0x2, 0x4, 0x36, 0x3, 0x2, 0x2, 0x2, 0x6, 0x40, 
    0x3, 0x2, 0x2, 0x2, 0x8, 0x4a, 0x3, 0x2, 0x2, 0x2, 0xa, 0x50, 0x3, 0x2, 
    0x2, 0x2, 0xc, 0x5a, 0x3, 0x2, 0x2, 0x2, 0xe, 0x65, 0x3, 0x2, 0x2, 0x2, 
    0x10, 0x6d, 0x3, 0x2, 0x2, 0x2, 0x12, 0x75, 0x3, 0x2, 0x2, 0x2, 0x14, 
    0x7b, 0x3, 0x2, 0x2, 0x2, 0x16, 0x7f, 0x3, 0x2, 0x2, 0x2, 0x18, 0x83, 
    0x3, 0x2, 0x2, 0x2, 0x1a, 0x87, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x91, 0x3, 
    0x2, 0x2, 0x2, 0x1e, 0x9b, 0x3, 0x2, 0x2, 0x2, 0x20, 0x9f, 0x3, 0x2, 
    0x2, 0x2, 0x22, 0xa1, 0x3, 0x2, 0x2, 0x2, 0x24, 0xac, 0x3, 0x2, 0x2, 
    0x2, 0x26, 0xb2, 0x3, 0x2, 0x2, 0x2, 0x28, 0xbc, 0x3, 0x2, 0x2, 0x2, 
    0x2a, 0xc0, 0x3, 0x2, 0x2, 0x2, 0x2c, 0xc5, 0x3, 0x2, 0x2, 0x2, 0x2e, 
    0x2f, 0x7, 0x3, 0x2, 0x2, 0x2f, 0x30, 0x7, 0x4, 0x2, 0x2, 0x30, 0x31, 
    0x5, 0x4, 0x3, 0x2, 0x31, 0x32, 0x5, 0x6, 0x4, 0x2, 0x32, 0x33, 0x5, 
    0x1a, 0xe, 0x2, 0x33, 0x34, 0x5, 0x2a, 0x16, 0x2, 0x34, 0x35, 0x7, 0x5, 
    0x2, 0x2, 0x35, 0x3, 0x3, 0x2, 0x2, 0x2, 0x36, 0x37, 0x7, 0x6, 0x2, 
    0x2, 0x37, 0x3e, 0x7, 0x1c, 0x2, 0x2, 0x38, 0x39, 0x7, 0x7, 0x2, 0x2, 
    0x39, 0x3b, 0x7, 0x1c, 0x2, 0x2, 0x3a, 0x38, 0x3, 0x2, 0x2, 0x2, 0x3b, 
    0x3c, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x3a, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x3d, 
    0x3, 0x2, 0x2, 0x2, 0x3d, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x3a, 0x3, 
    0x2, 0x2, 0x2, 0x3e, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x3f, 0x5, 0x3, 0x2, 
    0x2, 0x2, 0x40, 0x41, 0x7, 0x8, 0x2, 0x2, 0x41, 0x45, 0x7, 0x4, 0x2, 
    0x2, 0x42, 0x44, 0x5, 0x8, 0x5, 0x2, 0x43, 0x42, 0x3, 0x2, 0x2, 0x2, 
    0x44, 0x47, 0x3, 0x2, 0x2, 0x2, 0x45, 0x43, 0x3, 0x2, 0x2, 0x2, 0x45, 
    0x46, 0x3, 0x2, 0x2, 0x2, 0x46, 0x48, 0x3, 0x2, 0x2, 0x2, 0x47, 0x45, 
    0x3, 0x2, 0x2, 0x2, 0x48, 0x49, 0x7, 0x5, 0x2, 0x2, 0x49, 0x7, 0x3, 
    0x2, 0x2, 0x2, 0x4a, 0x4b, 0x7, 0x1c, 0x2, 0x2, 0x4b, 0x4c, 0x7, 0x4, 
    0x2, 0x2, 0x4c, 0x4d, 0x5, 0xa, 0x6, 0x2, 0x4d, 0x4e, 0x5, 0xc, 0x7, 
    0x2, 0x4e, 0x4f, 0x7, 0x5, 0x2, 0x2, 0x4f, 0x9, 0x3, 0x2, 0x2, 0x2, 
    0x50, 0x51, 0x9, 0x2, 0x2, 0x2, 0x51, 0x55, 0x7, 0x4, 0x2, 0x2, 0x52, 
    0x54, 0x5, 0x14, 0xb, 0x2, 0x53, 0x52, 0x3, 0x2, 0x2, 0x2, 0x54, 0x57, 
    0x3, 0x2, 0x2, 0x2, 0x55, 0x53, 0x3, 0x2, 0x2, 0x2, 0x55, 0x56, 0x3, 
    0x2, 0x2, 0x2, 0x56, 0x58, 0x3, 0x2, 0x2, 0x2, 0x57, 0x55, 0x3, 0x2, 
    0x2, 0x2, 0x58, 0x59, 0x7, 0x5, 0x2, 0x2, 0x59, 0xb, 0x3, 0x2, 0x2, 
    0x2, 0x5a, 0x5b, 0x7, 0xd, 0x2, 0x2, 0x5b, 0x60, 0x7, 0x4, 0x2, 0x2, 
    0x5c, 0x5f, 0x5, 0x16, 0xc, 0x2, 0x5d, 0x5f, 0x5, 0x18, 0xd, 0x2, 0x5e, 
    0x5c, 0x3, 0x2, 0x2, 0x2, 0x5e, 0x5d, 0x3, 0x2, 0x2, 0x2, 0x5f, 0x62, 
    0x3, 0x2, 0x2, 0x2, 0x60, 0x5e, 0x3, 0x2, 0x2, 0x2, 0x60, 0x61, 0x3, 
    0x2, 0x2, 0x2, 0x61, 0x63, 0x3, 0x2, 0x2, 0x2, 0x62, 0x60, 0x3, 0x2, 
    0x2, 0x2, 0x63, 0x64, 0x7, 0x5, 0x2, 0x2, 0x64, 0xd, 0x3, 0x2, 0x2, 
    0x2, 0x65, 0x6a, 0x9, 0x3, 0x2, 0x2, 0x66, 0x67, 0x7, 0x1a, 0x2, 0x2, 
    0x67, 0x69, 0x9, 0x3, 0x2, 0x2, 0x68, 0x66, 0x3, 0x2, 0x2, 0x2, 0x69, 
    0x6c, 0x3, 0x2, 0x2, 0x2, 0x6a, 0x68, 0x3, 0x2, 0x2, 0x2, 0x6a, 0x6b, 
    0x3, 0x2, 0x2, 0x2, 0x6b, 0xf, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x6a, 0x3, 
    0x2, 0x2, 0x2, 0x6d, 0x72, 0x5, 0xe, 0x8, 0x2, 0x6e, 0x6f, 0x7, 0x19, 
    0x2, 0x2, 0x6f, 0x71, 0x5, 0xe, 0x8, 0x2, 0x70, 0x6e, 0x3, 0x2, 0x2, 
    0x2, 0x71, 0x74, 0x3, 0x2, 0x2, 0x2, 0x72, 0x70, 0x3, 0x2, 0x2, 0x2, 
    0x72, 0x73, 0x3, 0x2, 0x2, 0x2, 0x73, 0x11, 0x3, 0x2, 0x2, 0x2, 0x74, 
    0x72, 0x3, 0x2, 0x2, 0x2, 0x75, 0x76, 0x7, 0xe, 0x2, 0x2, 0x76, 0x77, 
    0x7, 0x1b, 0x2, 0x2, 0x77, 0x78, 0x7, 0x7, 0x2, 0x2, 0x78, 0x79, 0x7, 
    0x1b, 0x2, 0x2, 0x79, 0x7a, 0x7, 0xf, 0x2, 0x2, 0x7a, 0x13, 0x3, 0x2, 
    0x2, 0x2, 0x7b, 0x7c, 0x7, 0x1c, 0x2, 0x2, 0x7c, 0x7d, 0x7, 0x17, 0x2, 
    0x2, 0x7d, 0x7e, 0x5, 0x10, 0x9, 0x2, 0x7e, 0x15, 0x3, 0x2, 0x2, 0x2, 
    0x7f, 0x80, 0x5, 0x10, 0x9, 0x2, 0x80, 0x81, 0x9, 0x4, 0x2, 0x2, 0x81, 
    0x82, 0x5, 0x10, 0x9, 0x2, 0x82, 0x17, 0x3, 0x2, 0x2, 0x2, 0x83, 0x84, 
    0x7, 0x1c, 0x2, 0x2, 0x84, 0x85, 0x7, 0x15, 0x2, 0x2, 0x85, 0x86, 0x5, 
    0x12, 0xa, 0x2, 0x86, 0x19, 0x3, 0x2, 0x2, 0x2, 0x87, 0x88, 0x7, 0x10, 
    0x2, 0x2, 0x88, 0x8c, 0x7, 0x4, 0x2, 0x2, 0x89, 0x8b, 0x5, 0x1c, 0xf, 
    0x2, 0x8a, 0x89, 0x3, 0x2, 0x2, 0x2, 0x8b, 0x8e, 0x3, 0x2, 0x2, 0x2, 
    0x8c, 0x8a, 0x3, 0x2, 0x2, 0x2, 0x8c, 0x8d, 0x3, 0x2, 0x2, 0x2, 0x8d, 
    0x8f, 0x3, 0x2, 0x2, 0x2, 0x8e, 0x8c, 0x3, 0x2, 0x2, 0x2, 0x8f, 0x90, 
    0x7, 0x5, 0x2, 0x2, 0x90, 0x1b, 0x3, 0x2, 0x2, 0x2, 0x91, 0x98, 0x5, 
    0x1e, 0x10, 0x2, 0x92, 0x97, 0x5, 0x20, 0x11, 0x2, 0x93, 0x97, 0x5, 
    0x22, 0x12, 0x2, 0x94, 0x97, 0x5, 0x26, 0x14, 0x2, 0x95, 0x97, 0x5, 
    0x28, 0x15, 0x2, 0x96, 0x92, 0x3, 0x2, 0x2, 0x2, 0x96, 0x93, 0x3, 0x2, 
    0x2, 0x2, 0x96, 0x94, 0x3, 0x2, 0x2, 0x2, 0x96, 0x95, 0x3, 0x2, 0x2, 
    0x2, 0x97, 0x9a, 0x3, 0x2, 0x2, 0x2, 0x98, 0x96, 0x3, 0x2, 0x2, 0x2, 
    0x98, 0x99, 0x3, 0x2, 0x2, 0x2, 0x99, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x9a, 
    0x98, 0x3, 0x2, 0x2, 0x2, 0x9b, 0x9c, 0x7, 0x1c, 0x2, 0x2, 0x9c, 0x9d, 
    0x7, 0x20, 0x2, 0x2, 0x9d, 0x9e, 0x7, 0x1c, 0x2, 0x2, 0x9e, 0x1f, 0x3, 
    0x2, 0x2, 0x2, 0x9f, 0xa0, 0x7, 0x11, 0x2, 0x2, 0xa0, 0x21, 0x3, 0x2, 
    0x2, 0x2, 0xa1, 0xa2, 0x7, 0x12, 0x2, 0x2, 0xa2, 0xa7, 0x7, 0x4, 0x2, 
    0x2, 0xa3, 0xa6, 0x5, 0x16, 0xc, 0x2, 0xa4, 0xa6, 0x5, 0x18, 0xd, 0x2, 
    0xa5, 0xa3, 0x3, 0x2, 0x2, 0x2, 0xa5, 0xa4, 0x3, 0x2, 0x2, 0x2, 0xa6, 
    0xa9, 0x3, 0x2, 0x2, 0x2, 0xa7, 0xa5, 0x3, 0x2, 0x2, 0x2, 0xa7, 0xa8, 
    0x3, 0x2, 0x2, 0x2, 0xa8, 0xaa, 0x3, 0x2, 0x2, 0x2, 0xa9, 0xa7, 0x3, 
    0x2, 0x2, 0x2, 0xaa, 0xab, 0x7, 0x5, 0x2, 0x2, 0xab, 0x23, 0x3, 0x2, 
    0x2, 0x2, 0xac, 0xad, 0x7, 0x1c, 0x2, 0x2, 0xad, 0xb0, 0x7, 0x21, 0x2, 
    0x2, 0xae, 0xb1, 0x5, 0x10, 0x9, 0x2, 0xaf, 0xb1, 0x5, 0x12, 0xa, 0x2, 
    0xb0, 0xae, 0x3, 0x2, 0x2, 0x2, 0xb0, 0xaf, 0x3, 0x2, 0x2, 0x2, 0xb1, 
    0x25, 0x3, 0x2, 0x2, 0x2, 0xb2, 0xb3, 0x7, 0x13, 0x2, 0x2, 0xb3, 0xb7, 
    0x7, 0x4, 0x2, 0x2, 0xb4, 0xb6, 0x5, 0x24, 0x13, 0x2, 0xb5, 0xb4, 0x3, 
    0x2, 0x2, 0x2, 0xb6, 0xb9, 0x3, 0x2, 0x2, 0x2, 0xb7, 0xb5, 0x3, 0x2, 
    0x2, 0x2, 0xb7, 0xb8, 0x3, 0x2, 0x2, 0x2, 0xb8, 0xba, 0x3, 0x2, 0x2, 
    0x2, 0xb9, 0xb7, 0x3, 0x2, 0x2, 0x2, 0xba, 0xbb, 0x7, 0x5, 0x2, 0x2, 
    0xbb, 0x27, 0x3, 0x2, 0x2, 0x2, 0xbc, 0xbd, 0x9, 0x5, 0x2, 0x2, 0xbd, 
    0xbe, 0x7, 0x4, 0x2, 0x2, 0xbe, 0xbf, 0x7, 0x5, 0x2, 0x2, 0xbf, 0x29, 
    0x3, 0x2, 0x2, 0x2, 0xc0, 0xc1, 0x7, 0x14, 0x2, 0x2, 0xc1, 0xc2, 0x7, 
    0x4, 0x2, 0x2, 0xc2, 0xc3, 0x5, 0x2c, 0x17, 0x2, 0xc3, 0xc4, 0x7, 0x5, 
    0x2, 0x2, 0xc4, 0x2b, 0x3, 0x2, 0x2, 0x2, 0xc5, 0xc6, 0x7, 0x1c, 0x2, 
    0x2, 0xc6, 0xcb, 0x7, 0x4, 0x2, 0x2, 0xc7, 0xca, 0x5, 0x16, 0xc, 0x2, 
    0xc8, 0xca, 0x5, 0x18, 0xd, 0x2, 0xc9, 0xc7, 0x3, 0x2, 0x2, 0x2, 0xc9, 
    0xc8, 0x3, 0x2, 0x2, 0x2, 0xca, 0xcd, 0x3, 0x2, 0x2, 0x2, 0xcb, 0xc9, 
    0x3, 0x2, 0x2, 0x2, 0xcb, 0xcc, 0x3, 0x2, 0x2, 0x2, 0xcc, 0xce, 0x3, 
    0x2, 0x2, 0x2, 0xcd, 0xcb, 0x3, 0x2, 0x2, 0x2, 0xce, 0xcf, 0x7, 0x5, 
    0x2, 0x2, 0xcf, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x13, 0x3c, 0x3e, 0x45, 0x55, 
    0x5e, 0x60, 0x6a, 0x72, 0x8c, 0x96, 0x98, 0xa5, 0xa7, 0xb0, 0xb7, 0xc9, 
    0xcb, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

HybridAutomatonParser::Initializer HybridAutomatonParser::_init;
