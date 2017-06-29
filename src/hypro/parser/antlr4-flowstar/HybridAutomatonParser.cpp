
// Generated from HybridAutomaton.g4 by ANTLR 4.7


#include "HybridAutomatonListener.h"

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


size_t HybridAutomatonParser::StartContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleStart;
}

void HybridAutomatonParser::StartContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HybridAutomatonListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStart(this);
}

void HybridAutomatonParser::StartContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HybridAutomatonListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStart(this);
}

HybridAutomatonParser::StartContext* HybridAutomatonParser::start() {
  StartContext *_localctx = _tracker.createInstance<StartContext>(_ctx, getState());
  enterRule(_localctx, 0, HybridAutomatonParser::RuleStart);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(22);
    match(HybridAutomatonParser::T__0);
    setState(23);
    match(HybridAutomatonParser::T__1);
    setState(24);
    vardeclaration();
    setState(25);
    modes();
    setState(26);
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

void HybridAutomatonParser::VardeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HybridAutomatonListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVardeclaration(this);
}

void HybridAutomatonParser::VardeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HybridAutomatonListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVardeclaration(this);
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
    setState(28);
    match(HybridAutomatonParser::T__3);
    setState(29);
    match(HybridAutomatonParser::VARIABLE);
    setState(36);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HybridAutomatonParser::T__4) {
      setState(32); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(30);
        match(HybridAutomatonParser::T__4);
        setState(31);
        match(HybridAutomatonParser::VARIABLE);
        setState(34); 
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

void HybridAutomatonParser::ModesContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HybridAutomatonListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterModes(this);
}

void HybridAutomatonParser::ModesContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HybridAutomatonListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitModes(this);
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
    setState(38);
    match(HybridAutomatonParser::T__5);
    setState(39);
    match(HybridAutomatonParser::T__1);
    setState(43);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HybridAutomatonParser::VARIABLE) {
      setState(40);
      location();
      setState(45);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(46);
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

void HybridAutomatonParser::LocationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HybridAutomatonListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLocation(this);
}

void HybridAutomatonParser::LocationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HybridAutomatonListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLocation(this);
}

HybridAutomatonParser::LocationContext* HybridAutomatonParser::location() {
  LocationContext *_localctx = _tracker.createInstance<LocationContext>(_ctx, getState());
  enterRule(_localctx, 6, HybridAutomatonParser::RuleLocation);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(48);
    match(HybridAutomatonParser::VARIABLE);
    setState(49);
    match(HybridAutomatonParser::T__1);
    setState(50);
    activities();
    setState(51);
    invariants();
    setState(52);
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

void HybridAutomatonParser::ActivitiesContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HybridAutomatonListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterActivities(this);
}

void HybridAutomatonParser::ActivitiesContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HybridAutomatonListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitActivities(this);
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
    setState(54);
    match(HybridAutomatonParser::T__6);
    setState(55);
    match(HybridAutomatonParser::T__1);
    setState(59);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HybridAutomatonParser::VARIABLE) {
      setState(56);
      equation();
      setState(61);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(62);
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

std::vector<HybridAutomatonParser::BoolexprContext *> HybridAutomatonParser::InvariantsContext::boolexpr() {
  return getRuleContexts<HybridAutomatonParser::BoolexprContext>();
}

HybridAutomatonParser::BoolexprContext* HybridAutomatonParser::InvariantsContext::boolexpr(size_t i) {
  return getRuleContext<HybridAutomatonParser::BoolexprContext>(i);
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

void HybridAutomatonParser::InvariantsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HybridAutomatonListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInvariants(this);
}

void HybridAutomatonParser::InvariantsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HybridAutomatonListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInvariants(this);
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
    setState(64);
    match(HybridAutomatonParser::T__7);
    setState(65);
    match(HybridAutomatonParser::T__1);
    setState(70);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HybridAutomatonParser::VARIABLE

    || _la == HybridAutomatonParser::NUMBER) {
      setState(68);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
      case 1: {
        setState(66);
        boolexpr();
        break;
      }

      case 2: {
        setState(67);
        intervalexpr();
        break;
      }

      }
      setState(72);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(73);
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

std::vector<tree::TerminalNode *> HybridAutomatonParser::TermContext::BINOPERATOR() {
  return getTokens(HybridAutomatonParser::BINOPERATOR);
}

tree::TerminalNode* HybridAutomatonParser::TermContext::BINOPERATOR(size_t i) {
  return getToken(HybridAutomatonParser::BINOPERATOR, i);
}


size_t HybridAutomatonParser::TermContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleTerm;
}

void HybridAutomatonParser::TermContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HybridAutomatonListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTerm(this);
}

void HybridAutomatonParser::TermContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HybridAutomatonListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTerm(this);
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
    setState(75);
    _la = _input->LA(1);
    if (!(_la == HybridAutomatonParser::VARIABLE

    || _la == HybridAutomatonParser::NUMBER)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(82);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HybridAutomatonParser::BINOPERATOR) {
      setState(78); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(76);
        match(HybridAutomatonParser::BINOPERATOR);
        setState(77);
        _la = _input->LA(1);
        if (!(_la == HybridAutomatonParser::VARIABLE

        || _la == HybridAutomatonParser::NUMBER)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(80); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == HybridAutomatonParser::BINOPERATOR);
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

HybridAutomatonParser::EquationContext::EquationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HybridAutomatonParser::EquationContext::VARIABLE() {
  return getToken(HybridAutomatonParser::VARIABLE, 0);
}

tree::TerminalNode* HybridAutomatonParser::EquationContext::EQUALS() {
  return getToken(HybridAutomatonParser::EQUALS, 0);
}

HybridAutomatonParser::TermContext* HybridAutomatonParser::EquationContext::term() {
  return getRuleContext<HybridAutomatonParser::TermContext>(0);
}


size_t HybridAutomatonParser::EquationContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleEquation;
}

void HybridAutomatonParser::EquationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HybridAutomatonListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEquation(this);
}

void HybridAutomatonParser::EquationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HybridAutomatonListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEquation(this);
}

HybridAutomatonParser::EquationContext* HybridAutomatonParser::equation() {
  EquationContext *_localctx = _tracker.createInstance<EquationContext>(_ctx, getState());
  enterRule(_localctx, 14, HybridAutomatonParser::RuleEquation);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(84);
    match(HybridAutomatonParser::VARIABLE);
    setState(85);
    match(HybridAutomatonParser::EQUALS);
    setState(86);
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

HybridAutomatonParser::BoolexprContext::BoolexprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HybridAutomatonParser::TermContext* HybridAutomatonParser::BoolexprContext::term() {
  return getRuleContext<HybridAutomatonParser::TermContext>(0);
}

tree::TerminalNode* HybridAutomatonParser::BoolexprContext::BOOLRELATION() {
  return getToken(HybridAutomatonParser::BOOLRELATION, 0);
}

tree::TerminalNode* HybridAutomatonParser::BoolexprContext::NUMBER() {
  return getToken(HybridAutomatonParser::NUMBER, 0);
}


size_t HybridAutomatonParser::BoolexprContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleBoolexpr;
}

void HybridAutomatonParser::BoolexprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HybridAutomatonListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBoolexpr(this);
}

void HybridAutomatonParser::BoolexprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HybridAutomatonListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBoolexpr(this);
}

HybridAutomatonParser::BoolexprContext* HybridAutomatonParser::boolexpr() {
  BoolexprContext *_localctx = _tracker.createInstance<BoolexprContext>(_ctx, getState());
  enterRule(_localctx, 16, HybridAutomatonParser::RuleBoolexpr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(88);
    term();
    setState(89);
    match(HybridAutomatonParser::BOOLRELATION);
    setState(90);
    match(HybridAutomatonParser::NUMBER);
   
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

HybridAutomatonParser::TermContext* HybridAutomatonParser::IntervalexprContext::term() {
  return getRuleContext<HybridAutomatonParser::TermContext>(0);
}

tree::TerminalNode* HybridAutomatonParser::IntervalexprContext::IN() {
  return getToken(HybridAutomatonParser::IN, 0);
}

tree::TerminalNode* HybridAutomatonParser::IntervalexprContext::INTERVAL() {
  return getToken(HybridAutomatonParser::INTERVAL, 0);
}


size_t HybridAutomatonParser::IntervalexprContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleIntervalexpr;
}

void HybridAutomatonParser::IntervalexprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HybridAutomatonListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIntervalexpr(this);
}

void HybridAutomatonParser::IntervalexprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HybridAutomatonListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIntervalexpr(this);
}

HybridAutomatonParser::IntervalexprContext* HybridAutomatonParser::intervalexpr() {
  IntervalexprContext *_localctx = _tracker.createInstance<IntervalexprContext>(_ctx, getState());
  enterRule(_localctx, 18, HybridAutomatonParser::RuleIntervalexpr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(92);
    term();
    setState(93);
    match(HybridAutomatonParser::IN);
    setState(94);
    match(HybridAutomatonParser::INTERVAL);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FormulaContext ------------------------------------------------------------------

HybridAutomatonParser::FormulaContext::FormulaContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HybridAutomatonParser::EquationContext* HybridAutomatonParser::FormulaContext::equation() {
  return getRuleContext<HybridAutomatonParser::EquationContext>(0);
}

HybridAutomatonParser::BoolexprContext* HybridAutomatonParser::FormulaContext::boolexpr() {
  return getRuleContext<HybridAutomatonParser::BoolexprContext>(0);
}

HybridAutomatonParser::IntervalexprContext* HybridAutomatonParser::FormulaContext::intervalexpr() {
  return getRuleContext<HybridAutomatonParser::IntervalexprContext>(0);
}


size_t HybridAutomatonParser::FormulaContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleFormula;
}

void HybridAutomatonParser::FormulaContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HybridAutomatonListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFormula(this);
}

void HybridAutomatonParser::FormulaContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HybridAutomatonListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFormula(this);
}

HybridAutomatonParser::FormulaContext* HybridAutomatonParser::formula() {
  FormulaContext *_localctx = _tracker.createInstance<FormulaContext>(_ctx, getState());
  enterRule(_localctx, 20, HybridAutomatonParser::RuleFormula);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(99);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(96);
      equation();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(97);
      boolexpr();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(98);
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
std::vector<dfa::DFA> HybridAutomatonParser::_decisionToDFA;
atn::PredictionContextCache HybridAutomatonParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN HybridAutomatonParser::_atn;
std::vector<uint16_t> HybridAutomatonParser::_serializedATN;

std::vector<std::string> HybridAutomatonParser::_ruleNames = {
  "start", "vardeclaration", "modes", "location", "activities", "invariants", 
  "term", "equation", "boolexpr", "intervalexpr", "formula"
};

std::vector<std::string> HybridAutomatonParser::_literalNames = {
  "", "'hybrid reachability'", "'{'", "'}'", "'state var'", "','", "'modes'", 
  "'poly ode 1'", "'inv'", "'in'", "'='"
};

std::vector<std::string> HybridAutomatonParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "IN", "EQUALS", "BOOLRELATION", "BINOPERATOR", 
  "VARIABLE", "NUMBER", "INTERVAL", "WS"
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
    0x3, 0x12, 0x68, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 
    0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x6, 0x3, 0x23, 
    0xa, 0x3, 0xd, 0x3, 0xe, 0x3, 0x24, 0x5, 0x3, 0x27, 0xa, 0x3, 0x3, 0x4, 
    0x3, 0x4, 0x3, 0x4, 0x7, 0x4, 0x2c, 0xa, 0x4, 0xc, 0x4, 0xe, 0x4, 0x2f, 
    0xb, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 
    0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x7, 0x6, 0x3c, 0xa, 
    0x6, 0xc, 0x6, 0xe, 0x6, 0x3f, 0xb, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x7, 0x7, 0x47, 0xa, 0x7, 0xc, 0x7, 0xe, 
    0x7, 0x4a, 0xb, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 
    0x6, 0x8, 0x51, 0xa, 0x8, 0xd, 0x8, 0xe, 0x8, 0x52, 0x5, 0x8, 0x55, 
    0xa, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0xa, 0x3, 0xa, 
    0x3, 0xa, 0x3, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xc, 
    0x3, 0xc, 0x3, 0xc, 0x5, 0xc, 0x66, 0xa, 0xc, 0x3, 0xc, 0x2, 0x2, 0xd, 
    0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x2, 0x3, 
    0x3, 0x2, 0xf, 0x10, 0x2, 0x66, 0x2, 0x18, 0x3, 0x2, 0x2, 0x2, 0x4, 
    0x1e, 0x3, 0x2, 0x2, 0x2, 0x6, 0x28, 0x3, 0x2, 0x2, 0x2, 0x8, 0x32, 
    0x3, 0x2, 0x2, 0x2, 0xa, 0x38, 0x3, 0x2, 0x2, 0x2, 0xc, 0x42, 0x3, 0x2, 
    0x2, 0x2, 0xe, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x10, 0x56, 0x3, 0x2, 0x2, 
    0x2, 0x12, 0x5a, 0x3, 0x2, 0x2, 0x2, 0x14, 0x5e, 0x3, 0x2, 0x2, 0x2, 
    0x16, 0x65, 0x3, 0x2, 0x2, 0x2, 0x18, 0x19, 0x7, 0x3, 0x2, 0x2, 0x19, 
    0x1a, 0x7, 0x4, 0x2, 0x2, 0x1a, 0x1b, 0x5, 0x4, 0x3, 0x2, 0x1b, 0x1c, 
    0x5, 0x6, 0x4, 0x2, 0x1c, 0x1d, 0x7, 0x5, 0x2, 0x2, 0x1d, 0x3, 0x3, 
    0x2, 0x2, 0x2, 0x1e, 0x1f, 0x7, 0x6, 0x2, 0x2, 0x1f, 0x26, 0x7, 0xf, 
    0x2, 0x2, 0x20, 0x21, 0x7, 0x7, 0x2, 0x2, 0x21, 0x23, 0x7, 0xf, 0x2, 
    0x2, 0x22, 0x20, 0x3, 0x2, 0x2, 0x2, 0x23, 0x24, 0x3, 0x2, 0x2, 0x2, 
    0x24, 0x22, 0x3, 0x2, 0x2, 0x2, 0x24, 0x25, 0x3, 0x2, 0x2, 0x2, 0x25, 
    0x27, 0x3, 0x2, 0x2, 0x2, 0x26, 0x22, 0x3, 0x2, 0x2, 0x2, 0x26, 0x27, 
    0x3, 0x2, 0x2, 0x2, 0x27, 0x5, 0x3, 0x2, 0x2, 0x2, 0x28, 0x29, 0x7, 
    0x8, 0x2, 0x2, 0x29, 0x2d, 0x7, 0x4, 0x2, 0x2, 0x2a, 0x2c, 0x5, 0x8, 
    0x5, 0x2, 0x2b, 0x2a, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x2f, 0x3, 0x2, 0x2, 
    0x2, 0x2d, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x2d, 0x2e, 0x3, 0x2, 0x2, 0x2, 
    0x2e, 0x30, 0x3, 0x2, 0x2, 0x2, 0x2f, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x30, 
    0x31, 0x7, 0x5, 0x2, 0x2, 0x31, 0x7, 0x3, 0x2, 0x2, 0x2, 0x32, 0x33, 
    0x7, 0xf, 0x2, 0x2, 0x33, 0x34, 0x7, 0x4, 0x2, 0x2, 0x34, 0x35, 0x5, 
    0xa, 0x6, 0x2, 0x35, 0x36, 0x5, 0xc, 0x7, 0x2, 0x36, 0x37, 0x7, 0x5, 
    0x2, 0x2, 0x37, 0x9, 0x3, 0x2, 0x2, 0x2, 0x38, 0x39, 0x7, 0x9, 0x2, 
    0x2, 0x39, 0x3d, 0x7, 0x4, 0x2, 0x2, 0x3a, 0x3c, 0x5, 0x10, 0x9, 0x2, 
    0x3b, 0x3a, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x3d, 
    0x3b, 0x3, 0x2, 0x2, 0x2, 0x3d, 0x3e, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x40, 
    0x3, 0x2, 0x2, 0x2, 0x3f, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x40, 0x41, 0x7, 
    0x5, 0x2, 0x2, 0x41, 0xb, 0x3, 0x2, 0x2, 0x2, 0x42, 0x43, 0x7, 0xa, 
    0x2, 0x2, 0x43, 0x48, 0x7, 0x4, 0x2, 0x2, 0x44, 0x47, 0x5, 0x12, 0xa, 
    0x2, 0x45, 0x47, 0x5, 0x14, 0xb, 0x2, 0x46, 0x44, 0x3, 0x2, 0x2, 0x2, 
    0x46, 0x45, 0x3, 0x2, 0x2, 0x2, 0x47, 0x4a, 0x3, 0x2, 0x2, 0x2, 0x48, 
    0x46, 0x3, 0x2, 0x2, 0x2, 0x48, 0x49, 0x3, 0x2, 0x2, 0x2, 0x49, 0x4b, 
    0x3, 0x2, 0x2, 0x2, 0x4a, 0x48, 0x3, 0x2, 0x2, 0x2, 0x4b, 0x4c, 0x7, 
    0x5, 0x2, 0x2, 0x4c, 0xd, 0x3, 0x2, 0x2, 0x2, 0x4d, 0x54, 0x9, 0x2, 
    0x2, 0x2, 0x4e, 0x4f, 0x7, 0xe, 0x2, 0x2, 0x4f, 0x51, 0x9, 0x2, 0x2, 
    0x2, 0x50, 0x4e, 0x3, 0x2, 0x2, 0x2, 0x51, 0x52, 0x3, 0x2, 0x2, 0x2, 
    0x52, 0x50, 0x3, 0x2, 0x2, 0x2, 0x52, 0x53, 0x3, 0x2, 0x2, 0x2, 0x53, 
    0x55, 0x3, 0x2, 0x2, 0x2, 0x54, 0x50, 0x3, 0x2, 0x2, 0x2, 0x54, 0x55, 
    0x3, 0x2, 0x2, 0x2, 0x55, 0xf, 0x3, 0x2, 0x2, 0x2, 0x56, 0x57, 0x7, 
    0xf, 0x2, 0x2, 0x57, 0x58, 0x7, 0xc, 0x2, 0x2, 0x58, 0x59, 0x5, 0xe, 
    0x8, 0x2, 0x59, 0x11, 0x3, 0x2, 0x2, 0x2, 0x5a, 0x5b, 0x5, 0xe, 0x8, 
    0x2, 0x5b, 0x5c, 0x7, 0xd, 0x2, 0x2, 0x5c, 0x5d, 0x7, 0x10, 0x2, 0x2, 
    0x5d, 0x13, 0x3, 0x2, 0x2, 0x2, 0x5e, 0x5f, 0x5, 0xe, 0x8, 0x2, 0x5f, 
    0x60, 0x7, 0xb, 0x2, 0x2, 0x60, 0x61, 0x7, 0x11, 0x2, 0x2, 0x61, 0x15, 
    0x3, 0x2, 0x2, 0x2, 0x62, 0x66, 0x5, 0x10, 0x9, 0x2, 0x63, 0x66, 0x5, 
    0x12, 0xa, 0x2, 0x64, 0x66, 0x5, 0x14, 0xb, 0x2, 0x65, 0x62, 0x3, 0x2, 
    0x2, 0x2, 0x65, 0x63, 0x3, 0x2, 0x2, 0x2, 0x65, 0x64, 0x3, 0x2, 0x2, 
    0x2, 0x66, 0x17, 0x3, 0x2, 0x2, 0x2, 0xb, 0x24, 0x26, 0x2d, 0x3d, 0x46, 
    0x48, 0x52, 0x54, 0x65, 
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
