
// Generated from Transition.g4 by ANTLR 4.7



#include "TransitionParser.h"


using namespace antlrcpp;
using namespace antlr4;

TransitionParser::TransitionParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

TransitionParser::~TransitionParser() {
  delete _interpreter;
}

std::string TransitionParser::getGrammarFileName() const {
  return "Transition.g4";
}

const std::vector<std::string>& TransitionParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& TransitionParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- JumpsContext ------------------------------------------------------------------

TransitionParser::JumpsContext::JumpsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<TransitionParser::TransitionContext *> TransitionParser::JumpsContext::transition() {
  return getRuleContexts<TransitionParser::TransitionContext>();
}

TransitionParser::TransitionContext* TransitionParser::JumpsContext::transition(size_t i) {
  return getRuleContext<TransitionParser::TransitionContext>(i);
}


size_t TransitionParser::JumpsContext::getRuleIndex() const {
  return TransitionParser::RuleJumps;
}


TransitionParser::JumpsContext* TransitionParser::jumps() {
  JumpsContext *_localctx = _tracker.createInstance<JumpsContext>(_ctx, getState());
  enterRule(_localctx, 0, TransitionParser::RuleJumps);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(32);
    match(TransitionParser::T__0);
    setState(33);
    match(TransitionParser::T__1);
    setState(37);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == TransitionParser::VARIABLE) {
      setState(34);
      transition();
      setState(39);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(40);
    match(TransitionParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TransitionContext ------------------------------------------------------------------

TransitionParser::TransitionContext::TransitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TransitionParser::FromtoContext* TransitionParser::TransitionContext::fromto() {
  return getRuleContext<TransitionParser::FromtoContext>(0);
}

std::vector<TransitionParser::UrgentContext *> TransitionParser::TransitionContext::urgent() {
  return getRuleContexts<TransitionParser::UrgentContext>();
}

TransitionParser::UrgentContext* TransitionParser::TransitionContext::urgent(size_t i) {
  return getRuleContext<TransitionParser::UrgentContext>(i);
}

std::vector<TransitionParser::GuardContext *> TransitionParser::TransitionContext::guard() {
  return getRuleContexts<TransitionParser::GuardContext>();
}

TransitionParser::GuardContext* TransitionParser::TransitionContext::guard(size_t i) {
  return getRuleContext<TransitionParser::GuardContext>(i);
}

std::vector<TransitionParser::ResetfctContext *> TransitionParser::TransitionContext::resetfct() {
  return getRuleContexts<TransitionParser::ResetfctContext>();
}

TransitionParser::ResetfctContext* TransitionParser::TransitionContext::resetfct(size_t i) {
  return getRuleContext<TransitionParser::ResetfctContext>(i);
}

std::vector<TransitionParser::AggregationContext *> TransitionParser::TransitionContext::aggregation() {
  return getRuleContexts<TransitionParser::AggregationContext>();
}

TransitionParser::AggregationContext* TransitionParser::TransitionContext::aggregation(size_t i) {
  return getRuleContext<TransitionParser::AggregationContext>(i);
}


size_t TransitionParser::TransitionContext::getRuleIndex() const {
  return TransitionParser::RuleTransition;
}


TransitionParser::TransitionContext* TransitionParser::transition() {
  TransitionContext *_localctx = _tracker.createInstance<TransitionContext>(_ctx, getState());
  enterRule(_localctx, 2, TransitionParser::RuleTransition);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(42);
    fromto();
    setState(49);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << TransitionParser::T__3)
      | (1ULL << TransitionParser::T__4)
      | (1ULL << TransitionParser::T__5)
      | (1ULL << TransitionParser::PARALLELOTOPE)
      | (1ULL << TransitionParser::BOX))) != 0)) {
      setState(47);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case TransitionParser::T__3: {
          setState(43);
          urgent();
          break;
        }

        case TransitionParser::T__4: {
          setState(44);
          guard();
          break;
        }

        case TransitionParser::T__5: {
          setState(45);
          resetfct();
          break;
        }

        case TransitionParser::PARALLELOTOPE:
        case TransitionParser::BOX: {
          setState(46);
          aggregation();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(51);
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

TransitionParser::FromtoContext::FromtoContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> TransitionParser::FromtoContext::VARIABLE() {
  return getTokens(TransitionParser::VARIABLE);
}

tree::TerminalNode* TransitionParser::FromtoContext::VARIABLE(size_t i) {
  return getToken(TransitionParser::VARIABLE, i);
}

tree::TerminalNode* TransitionParser::FromtoContext::JUMP() {
  return getToken(TransitionParser::JUMP, 0);
}


size_t TransitionParser::FromtoContext::getRuleIndex() const {
  return TransitionParser::RuleFromto;
}


TransitionParser::FromtoContext* TransitionParser::fromto() {
  FromtoContext *_localctx = _tracker.createInstance<FromtoContext>(_ctx, getState());
  enterRule(_localctx, 4, TransitionParser::RuleFromto);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(52);
    match(TransitionParser::VARIABLE);
    setState(53);
    match(TransitionParser::JUMP);
    setState(54);
    match(TransitionParser::VARIABLE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UrgentContext ------------------------------------------------------------------

TransitionParser::UrgentContext::UrgentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t TransitionParser::UrgentContext::getRuleIndex() const {
  return TransitionParser::RuleUrgent;
}


TransitionParser::UrgentContext* TransitionParser::urgent() {
  UrgentContext *_localctx = _tracker.createInstance<UrgentContext>(_ctx, getState());
  enterRule(_localctx, 6, TransitionParser::RuleUrgent);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(56);
    match(TransitionParser::T__3);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GuardContext ------------------------------------------------------------------

TransitionParser::GuardContext::GuardContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TransitionParser::ConstrsetContext* TransitionParser::GuardContext::constrset() {
  return getRuleContext<TransitionParser::ConstrsetContext>(0);
}


size_t TransitionParser::GuardContext::getRuleIndex() const {
  return TransitionParser::RuleGuard;
}


TransitionParser::GuardContext* TransitionParser::guard() {
  GuardContext *_localctx = _tracker.createInstance<GuardContext>(_ctx, getState());
  enterRule(_localctx, 8, TransitionParser::RuleGuard);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(58);
    match(TransitionParser::T__4);
    setState(59);
    match(TransitionParser::T__1);
    setState(60);
    constrset();
    setState(61);
    match(TransitionParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AllocationContext ------------------------------------------------------------------

TransitionParser::AllocationContext::AllocationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TransitionParser::AllocationContext::VARIABLE() {
  return getToken(TransitionParser::VARIABLE, 0);
}

tree::TerminalNode* TransitionParser::AllocationContext::DEFINE() {
  return getToken(TransitionParser::DEFINE, 0);
}

TransitionParser::PolynomContext* TransitionParser::AllocationContext::polynom() {
  return getRuleContext<TransitionParser::PolynomContext>(0);
}

TransitionParser::IntervalContext* TransitionParser::AllocationContext::interval() {
  return getRuleContext<TransitionParser::IntervalContext>(0);
}


size_t TransitionParser::AllocationContext::getRuleIndex() const {
  return TransitionParser::RuleAllocation;
}


TransitionParser::AllocationContext* TransitionParser::allocation() {
  AllocationContext *_localctx = _tracker.createInstance<AllocationContext>(_ctx, getState());
  enterRule(_localctx, 10, TransitionParser::RuleAllocation);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(63);
    match(TransitionParser::VARIABLE);
    setState(64);
    match(TransitionParser::DEFINE);
    setState(67);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case TransitionParser::PLUS:
      case TransitionParser::MINUS:
      case TransitionParser::NUMBER:
      case TransitionParser::VARIABLE: {
        setState(65);
        polynom();
        break;
      }

      case TransitionParser::T__6: {
        setState(66);
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

TransitionParser::ResetfctContext::ResetfctContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<TransitionParser::AllocationContext *> TransitionParser::ResetfctContext::allocation() {
  return getRuleContexts<TransitionParser::AllocationContext>();
}

TransitionParser::AllocationContext* TransitionParser::ResetfctContext::allocation(size_t i) {
  return getRuleContext<TransitionParser::AllocationContext>(i);
}


size_t TransitionParser::ResetfctContext::getRuleIndex() const {
  return TransitionParser::RuleResetfct;
}


TransitionParser::ResetfctContext* TransitionParser::resetfct() {
  ResetfctContext *_localctx = _tracker.createInstance<ResetfctContext>(_ctx, getState());
  enterRule(_localctx, 12, TransitionParser::RuleResetfct);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(69);
    match(TransitionParser::T__5);
    setState(70);
    match(TransitionParser::T__1);
    setState(74);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == TransitionParser::VARIABLE) {
      setState(71);
      allocation();
      setState(76);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(77);
    match(TransitionParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AggregationContext ------------------------------------------------------------------

TransitionParser::AggregationContext::AggregationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TransitionParser::AggregationContext::PARALLELOTOPE() {
  return getToken(TransitionParser::PARALLELOTOPE, 0);
}

tree::TerminalNode* TransitionParser::AggregationContext::BOX() {
  return getToken(TransitionParser::BOX, 0);
}


size_t TransitionParser::AggregationContext::getRuleIndex() const {
  return TransitionParser::RuleAggregation;
}


TransitionParser::AggregationContext* TransitionParser::aggregation() {
  AggregationContext *_localctx = _tracker.createInstance<AggregationContext>(_ctx, getState());
  enterRule(_localctx, 14, TransitionParser::RuleAggregation);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(79);
    _la = _input->LA(1);
    if (!(_la == TransitionParser::PARALLELOTOPE

    || _la == TransitionParser::BOX)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(80);
    match(TransitionParser::T__1);
    setState(81);
    match(TransitionParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConnectorContext ------------------------------------------------------------------

TransitionParser::ConnectorContext::ConnectorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TransitionParser::ConnectorContext::PLUS() {
  return getToken(TransitionParser::PLUS, 0);
}

tree::TerminalNode* TransitionParser::ConnectorContext::MINUS() {
  return getToken(TransitionParser::MINUS, 0);
}


size_t TransitionParser::ConnectorContext::getRuleIndex() const {
  return TransitionParser::RuleConnector;
}


TransitionParser::ConnectorContext* TransitionParser::connector() {
  ConnectorContext *_localctx = _tracker.createInstance<ConnectorContext>(_ctx, getState());
  enterRule(_localctx, 16, TransitionParser::RuleConnector);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(83);
    _la = _input->LA(1);
    if (!(_la == TransitionParser::PLUS

    || _la == TransitionParser::MINUS)) {
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

TransitionParser::TermContext::TermContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> TransitionParser::TermContext::NUMBER() {
  return getTokens(TransitionParser::NUMBER);
}

tree::TerminalNode* TransitionParser::TermContext::NUMBER(size_t i) {
  return getToken(TransitionParser::NUMBER, i);
}

std::vector<tree::TerminalNode *> TransitionParser::TermContext::VARIABLE() {
  return getTokens(TransitionParser::VARIABLE);
}

tree::TerminalNode* TransitionParser::TermContext::VARIABLE(size_t i) {
  return getToken(TransitionParser::VARIABLE, i);
}

std::vector<tree::TerminalNode *> TransitionParser::TermContext::TIMES() {
  return getTokens(TransitionParser::TIMES);
}

tree::TerminalNode* TransitionParser::TermContext::TIMES(size_t i) {
  return getToken(TransitionParser::TIMES, i);
}

std::vector<TransitionParser::ConnectorContext *> TransitionParser::TermContext::connector() {
  return getRuleContexts<TransitionParser::ConnectorContext>();
}

TransitionParser::ConnectorContext* TransitionParser::TermContext::connector(size_t i) {
  return getRuleContext<TransitionParser::ConnectorContext>(i);
}


size_t TransitionParser::TermContext::getRuleIndex() const {
  return TransitionParser::RuleTerm;
}


TransitionParser::TermContext* TransitionParser::term() {
  TermContext *_localctx = _tracker.createInstance<TermContext>(_ctx, getState());
  enterRule(_localctx, 18, TransitionParser::RuleTerm);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(85);
    _la = _input->LA(1);
    if (!(_la == TransitionParser::NUMBER

    || _la == TransitionParser::VARIABLE)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(96);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == TransitionParser::TIMES) {
      setState(86);
      match(TransitionParser::TIMES);
      setState(90);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == TransitionParser::PLUS

      || _la == TransitionParser::MINUS) {
        setState(87);
        connector();
        setState(92);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(93);
      _la = _input->LA(1);
      if (!(_la == TransitionParser::NUMBER

      || _la == TransitionParser::VARIABLE)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(98);
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

TransitionParser::PolynomContext::PolynomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<TransitionParser::TermContext *> TransitionParser::PolynomContext::term() {
  return getRuleContexts<TransitionParser::TermContext>();
}

TransitionParser::TermContext* TransitionParser::PolynomContext::term(size_t i) {
  return getRuleContext<TransitionParser::TermContext>(i);
}

std::vector<TransitionParser::ConnectorContext *> TransitionParser::PolynomContext::connector() {
  return getRuleContexts<TransitionParser::ConnectorContext>();
}

TransitionParser::ConnectorContext* TransitionParser::PolynomContext::connector(size_t i) {
  return getRuleContext<TransitionParser::ConnectorContext>(i);
}


size_t TransitionParser::PolynomContext::getRuleIndex() const {
  return TransitionParser::RulePolynom;
}


TransitionParser::PolynomContext* TransitionParser::polynom() {
  PolynomContext *_localctx = _tracker.createInstance<PolynomContext>(_ctx, getState());
  enterRule(_localctx, 20, TransitionParser::RulePolynom);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(102);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == TransitionParser::PLUS

    || _la == TransitionParser::MINUS) {
      setState(99);
      connector();
      setState(104);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(105);
    term();
    setState(115);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(107); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(106);
          connector();
          setState(109); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == TransitionParser::PLUS

        || _la == TransitionParser::MINUS);
        setState(111);
        term(); 
      }
      setState(117);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
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

TransitionParser::IntervalContext::IntervalContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> TransitionParser::IntervalContext::NUMBER() {
  return getTokens(TransitionParser::NUMBER);
}

tree::TerminalNode* TransitionParser::IntervalContext::NUMBER(size_t i) {
  return getToken(TransitionParser::NUMBER, i);
}


size_t TransitionParser::IntervalContext::getRuleIndex() const {
  return TransitionParser::RuleInterval;
}


TransitionParser::IntervalContext* TransitionParser::interval() {
  IntervalContext *_localctx = _tracker.createInstance<IntervalContext>(_ctx, getState());
  enterRule(_localctx, 22, TransitionParser::RuleInterval);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(118);
    match(TransitionParser::T__6);
    setState(119);
    match(TransitionParser::NUMBER);
    setState(120);
    match(TransitionParser::T__7);
    setState(121);
    match(TransitionParser::NUMBER);
    setState(122);
    match(TransitionParser::T__8);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EquationContext ------------------------------------------------------------------

TransitionParser::EquationContext::EquationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TransitionParser::EquationContext::VARIABLE() {
  return getToken(TransitionParser::VARIABLE, 0);
}

tree::TerminalNode* TransitionParser::EquationContext::EQUALS() {
  return getToken(TransitionParser::EQUALS, 0);
}

TransitionParser::PolynomContext* TransitionParser::EquationContext::polynom() {
  return getRuleContext<TransitionParser::PolynomContext>(0);
}


size_t TransitionParser::EquationContext::getRuleIndex() const {
  return TransitionParser::RuleEquation;
}


TransitionParser::EquationContext* TransitionParser::equation() {
  EquationContext *_localctx = _tracker.createInstance<EquationContext>(_ctx, getState());
  enterRule(_localctx, 24, TransitionParser::RuleEquation);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(124);
    match(TransitionParser::VARIABLE);
    setState(125);
    match(TransitionParser::EQUALS);
    setState(126);
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

TransitionParser::ConstraintContext::ConstraintContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<TransitionParser::PolynomContext *> TransitionParser::ConstraintContext::polynom() {
  return getRuleContexts<TransitionParser::PolynomContext>();
}

TransitionParser::PolynomContext* TransitionParser::ConstraintContext::polynom(size_t i) {
  return getRuleContext<TransitionParser::PolynomContext>(i);
}

tree::TerminalNode* TransitionParser::ConstraintContext::BOOLRELATION() {
  return getToken(TransitionParser::BOOLRELATION, 0);
}

tree::TerminalNode* TransitionParser::ConstraintContext::EQUALS() {
  return getToken(TransitionParser::EQUALS, 0);
}


size_t TransitionParser::ConstraintContext::getRuleIndex() const {
  return TransitionParser::RuleConstraint;
}


TransitionParser::ConstraintContext* TransitionParser::constraint() {
  ConstraintContext *_localctx = _tracker.createInstance<ConstraintContext>(_ctx, getState());
  enterRule(_localctx, 26, TransitionParser::RuleConstraint);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(128);
    polynom();
    setState(129);
    _la = _input->LA(1);
    if (!(_la == TransitionParser::EQUALS

    || _la == TransitionParser::BOOLRELATION)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(130);
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

TransitionParser::IntervalexprContext::IntervalexprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TransitionParser::IntervalexprContext::VARIABLE() {
  return getToken(TransitionParser::VARIABLE, 0);
}

tree::TerminalNode* TransitionParser::IntervalexprContext::IN() {
  return getToken(TransitionParser::IN, 0);
}

TransitionParser::IntervalContext* TransitionParser::IntervalexprContext::interval() {
  return getRuleContext<TransitionParser::IntervalContext>(0);
}


size_t TransitionParser::IntervalexprContext::getRuleIndex() const {
  return TransitionParser::RuleIntervalexpr;
}


TransitionParser::IntervalexprContext* TransitionParser::intervalexpr() {
  IntervalexprContext *_localctx = _tracker.createInstance<IntervalexprContext>(_ctx, getState());
  enterRule(_localctx, 28, TransitionParser::RuleIntervalexpr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(132);
    match(TransitionParser::VARIABLE);
    setState(133);
    match(TransitionParser::IN);
    setState(134);
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

TransitionParser::ConstrsetContext::ConstrsetContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<TransitionParser::ConstraintContext *> TransitionParser::ConstrsetContext::constraint() {
  return getRuleContexts<TransitionParser::ConstraintContext>();
}

TransitionParser::ConstraintContext* TransitionParser::ConstrsetContext::constraint(size_t i) {
  return getRuleContext<TransitionParser::ConstraintContext>(i);
}

std::vector<TransitionParser::IntervalexprContext *> TransitionParser::ConstrsetContext::intervalexpr() {
  return getRuleContexts<TransitionParser::IntervalexprContext>();
}

TransitionParser::IntervalexprContext* TransitionParser::ConstrsetContext::intervalexpr(size_t i) {
  return getRuleContext<TransitionParser::IntervalexprContext>(i);
}


size_t TransitionParser::ConstrsetContext::getRuleIndex() const {
  return TransitionParser::RuleConstrset;
}


TransitionParser::ConstrsetContext* TransitionParser::constrset() {
  ConstrsetContext *_localctx = _tracker.createInstance<ConstrsetContext>(_ctx, getState());
  enterRule(_localctx, 30, TransitionParser::RuleConstrset);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(140);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << TransitionParser::PLUS)
      | (1ULL << TransitionParser::MINUS)
      | (1ULL << TransitionParser::NUMBER)
      | (1ULL << TransitionParser::VARIABLE))) != 0)) {
      setState(138);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
      case 1: {
        setState(136);
        constraint();
        break;
      }

      case 2: {
        setState(137);
        intervalexpr();
        break;
      }

      }
      setState(142);
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
std::vector<dfa::DFA> TransitionParser::_decisionToDFA;
atn::PredictionContextCache TransitionParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN TransitionParser::_atn;
std::vector<uint16_t> TransitionParser::_serializedATN;

std::vector<std::string> TransitionParser::_ruleNames = {
  "jumps", "transition", "fromto", "urgent", "guard", "allocation", "resetfct", 
  "aggregation", "connector", "term", "polynom", "interval", "equation", 
  "constraint", "intervalexpr", "constrset"
};

std::vector<std::string> TransitionParser::_literalNames = {
  "", "'jumps'", "'{'", "'}'", "'urgent'", "'guard'", "'reset'", "'['", 
  "','", "']'", "'parallelotope aggregation'", "'box aggregation'", "'->'", 
  "':='", "'in'", "", "'='", "", "'+'", "'-'", "'*'"
};

std::vector<std::string> TransitionParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "PARALLELOTOPE", "BOX", "JUMP", 
  "DEFINE", "IN", "COMMENT", "EQUALS", "BOOLRELATION", "PLUS", "MINUS", 
  "TIMES", "NUMBER", "VARIABLE", "WS"
};

dfa::Vocabulary TransitionParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> TransitionParser::_tokenNames;

TransitionParser::Initializer::Initializer() {
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
    0x3, 0x19, 0x92, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 0x4, 
    0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x3, 0x2, 
    0x3, 0x2, 0x3, 0x2, 0x7, 0x2, 0x26, 0xa, 0x2, 0xc, 0x2, 0xe, 0x2, 0x29, 
    0xb, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x7, 0x3, 0x32, 0xa, 0x3, 0xc, 0x3, 0xe, 0x3, 0x35, 0xb, 0x3, 
    0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 
    0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 
    0x3, 0x7, 0x5, 0x7, 0x46, 0xa, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x7, 
    0x8, 0x4b, 0xa, 0x8, 0xc, 0x8, 0xe, 0x8, 0x4e, 0xb, 0x8, 0x3, 0x8, 0x3, 
    0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xb, 0x3, 0xb, 0x3, 0xb, 0x7, 0xb, 0x5b, 0xa, 0xb, 0xc, 0xb, 0xe, 0xb, 
    0x5e, 0xb, 0xb, 0x3, 0xb, 0x7, 0xb, 0x61, 0xa, 0xb, 0xc, 0xb, 0xe, 0xb, 
    0x64, 0xb, 0xb, 0x3, 0xc, 0x7, 0xc, 0x67, 0xa, 0xc, 0xc, 0xc, 0xe, 0xc, 
    0x6a, 0xb, 0xc, 0x3, 0xc, 0x3, 0xc, 0x6, 0xc, 0x6e, 0xa, 0xc, 0xd, 0xc, 
    0xe, 0xc, 0x6f, 0x3, 0xc, 0x3, 0xc, 0x7, 0xc, 0x74, 0xa, 0xc, 0xc, 0xc, 
    0xe, 0xc, 0x77, 0xb, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 
    0xd, 0x3, 0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xf, 0x3, 
    0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 
    0x3, 0x11, 0x3, 0x11, 0x7, 0x11, 0x8d, 0xa, 0x11, 0xc, 0x11, 0xe, 0x11, 
    0x90, 0xb, 0x11, 0x3, 0x11, 0x2, 0x2, 0x12, 0x2, 0x4, 0x6, 0x8, 0xa, 
    0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x2, 
    0x6, 0x3, 0x2, 0xc, 0xd, 0x3, 0x2, 0x14, 0x15, 0x3, 0x2, 0x17, 0x18, 
    0x3, 0x2, 0x12, 0x13, 0x2, 0x8f, 0x2, 0x22, 0x3, 0x2, 0x2, 0x2, 0x4, 
    0x2c, 0x3, 0x2, 0x2, 0x2, 0x6, 0x36, 0x3, 0x2, 0x2, 0x2, 0x8, 0x3a, 
    0x3, 0x2, 0x2, 0x2, 0xa, 0x3c, 0x3, 0x2, 0x2, 0x2, 0xc, 0x41, 0x3, 0x2, 
    0x2, 0x2, 0xe, 0x47, 0x3, 0x2, 0x2, 0x2, 0x10, 0x51, 0x3, 0x2, 0x2, 
    0x2, 0x12, 0x55, 0x3, 0x2, 0x2, 0x2, 0x14, 0x57, 0x3, 0x2, 0x2, 0x2, 
    0x16, 0x68, 0x3, 0x2, 0x2, 0x2, 0x18, 0x78, 0x3, 0x2, 0x2, 0x2, 0x1a, 
    0x7e, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x82, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x86, 
    0x3, 0x2, 0x2, 0x2, 0x20, 0x8e, 0x3, 0x2, 0x2, 0x2, 0x22, 0x23, 0x7, 
    0x3, 0x2, 0x2, 0x23, 0x27, 0x7, 0x4, 0x2, 0x2, 0x24, 0x26, 0x5, 0x4, 
    0x3, 0x2, 0x25, 0x24, 0x3, 0x2, 0x2, 0x2, 0x26, 0x29, 0x3, 0x2, 0x2, 
    0x2, 0x27, 0x25, 0x3, 0x2, 0x2, 0x2, 0x27, 0x28, 0x3, 0x2, 0x2, 0x2, 
    0x28, 0x2a, 0x3, 0x2, 0x2, 0x2, 0x29, 0x27, 0x3, 0x2, 0x2, 0x2, 0x2a, 
    0x2b, 0x7, 0x5, 0x2, 0x2, 0x2b, 0x3, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x33, 
    0x5, 0x6, 0x4, 0x2, 0x2d, 0x32, 0x5, 0x8, 0x5, 0x2, 0x2e, 0x32, 0x5, 
    0xa, 0x6, 0x2, 0x2f, 0x32, 0x5, 0xe, 0x8, 0x2, 0x30, 0x32, 0x5, 0x10, 
    0x9, 0x2, 0x31, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x31, 0x2e, 0x3, 0x2, 0x2, 
    0x2, 0x31, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x31, 0x30, 0x3, 0x2, 0x2, 0x2, 
    0x32, 0x35, 0x3, 0x2, 0x2, 0x2, 0x33, 0x31, 0x3, 0x2, 0x2, 0x2, 0x33, 
    0x34, 0x3, 0x2, 0x2, 0x2, 0x34, 0x5, 0x3, 0x2, 0x2, 0x2, 0x35, 0x33, 
    0x3, 0x2, 0x2, 0x2, 0x36, 0x37, 0x7, 0x18, 0x2, 0x2, 0x37, 0x38, 0x7, 
    0xe, 0x2, 0x2, 0x38, 0x39, 0x7, 0x18, 0x2, 0x2, 0x39, 0x7, 0x3, 0x2, 
    0x2, 0x2, 0x3a, 0x3b, 0x7, 0x6, 0x2, 0x2, 0x3b, 0x9, 0x3, 0x2, 0x2, 
    0x2, 0x3c, 0x3d, 0x7, 0x7, 0x2, 0x2, 0x3d, 0x3e, 0x7, 0x4, 0x2, 0x2, 
    0x3e, 0x3f, 0x5, 0x20, 0x11, 0x2, 0x3f, 0x40, 0x7, 0x5, 0x2, 0x2, 0x40, 
    0xb, 0x3, 0x2, 0x2, 0x2, 0x41, 0x42, 0x7, 0x18, 0x2, 0x2, 0x42, 0x45, 
    0x7, 0xf, 0x2, 0x2, 0x43, 0x46, 0x5, 0x16, 0xc, 0x2, 0x44, 0x46, 0x5, 
    0x18, 0xd, 0x2, 0x45, 0x43, 0x3, 0x2, 0x2, 0x2, 0x45, 0x44, 0x3, 0x2, 
    0x2, 0x2, 0x46, 0xd, 0x3, 0x2, 0x2, 0x2, 0x47, 0x48, 0x7, 0x8, 0x2, 
    0x2, 0x48, 0x4c, 0x7, 0x4, 0x2, 0x2, 0x49, 0x4b, 0x5, 0xc, 0x7, 0x2, 
    0x4a, 0x49, 0x3, 0x2, 0x2, 0x2, 0x4b, 0x4e, 0x3, 0x2, 0x2, 0x2, 0x4c, 
    0x4a, 0x3, 0x2, 0x2, 0x2, 0x4c, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x4d, 0x4f, 
    0x3, 0x2, 0x2, 0x2, 0x4e, 0x4c, 0x3, 0x2, 0x2, 0x2, 0x4f, 0x50, 0x7, 
    0x5, 0x2, 0x2, 0x50, 0xf, 0x3, 0x2, 0x2, 0x2, 0x51, 0x52, 0x9, 0x2, 
    0x2, 0x2, 0x52, 0x53, 0x7, 0x4, 0x2, 0x2, 0x53, 0x54, 0x7, 0x5, 0x2, 
    0x2, 0x54, 0x11, 0x3, 0x2, 0x2, 0x2, 0x55, 0x56, 0x9, 0x3, 0x2, 0x2, 
    0x56, 0x13, 0x3, 0x2, 0x2, 0x2, 0x57, 0x62, 0x9, 0x4, 0x2, 0x2, 0x58, 
    0x5c, 0x7, 0x16, 0x2, 0x2, 0x59, 0x5b, 0x5, 0x12, 0xa, 0x2, 0x5a, 0x59, 
    0x3, 0x2, 0x2, 0x2, 0x5b, 0x5e, 0x3, 0x2, 0x2, 0x2, 0x5c, 0x5a, 0x3, 
    0x2, 0x2, 0x2, 0x5c, 0x5d, 0x3, 0x2, 0x2, 0x2, 0x5d, 0x5f, 0x3, 0x2, 
    0x2, 0x2, 0x5e, 0x5c, 0x3, 0x2, 0x2, 0x2, 0x5f, 0x61, 0x9, 0x4, 0x2, 
    0x2, 0x60, 0x58, 0x3, 0x2, 0x2, 0x2, 0x61, 0x64, 0x3, 0x2, 0x2, 0x2, 
    0x62, 0x60, 0x3, 0x2, 0x2, 0x2, 0x62, 0x63, 0x3, 0x2, 0x2, 0x2, 0x63, 
    0x15, 0x3, 0x2, 0x2, 0x2, 0x64, 0x62, 0x3, 0x2, 0x2, 0x2, 0x65, 0x67, 
    0x5, 0x12, 0xa, 0x2, 0x66, 0x65, 0x3, 0x2, 0x2, 0x2, 0x67, 0x6a, 0x3, 
    0x2, 0x2, 0x2, 0x68, 0x66, 0x3, 0x2, 0x2, 0x2, 0x68, 0x69, 0x3, 0x2, 
    0x2, 0x2, 0x69, 0x6b, 0x3, 0x2, 0x2, 0x2, 0x6a, 0x68, 0x3, 0x2, 0x2, 
    0x2, 0x6b, 0x75, 0x5, 0x14, 0xb, 0x2, 0x6c, 0x6e, 0x5, 0x12, 0xa, 0x2, 
    0x6d, 0x6c, 0x3, 0x2, 0x2, 0x2, 0x6e, 0x6f, 0x3, 0x2, 0x2, 0x2, 0x6f, 
    0x6d, 0x3, 0x2, 0x2, 0x2, 0x6f, 0x70, 0x3, 0x2, 0x2, 0x2, 0x70, 0x71, 
    0x3, 0x2, 0x2, 0x2, 0x71, 0x72, 0x5, 0x14, 0xb, 0x2, 0x72, 0x74, 0x3, 
    0x2, 0x2, 0x2, 0x73, 0x6d, 0x3, 0x2, 0x2, 0x2, 0x74, 0x77, 0x3, 0x2, 
    0x2, 0x2, 0x75, 0x73, 0x3, 0x2, 0x2, 0x2, 0x75, 0x76, 0x3, 0x2, 0x2, 
    0x2, 0x76, 0x17, 0x3, 0x2, 0x2, 0x2, 0x77, 0x75, 0x3, 0x2, 0x2, 0x2, 
    0x78, 0x79, 0x7, 0x9, 0x2, 0x2, 0x79, 0x7a, 0x7, 0x17, 0x2, 0x2, 0x7a, 
    0x7b, 0x7, 0xa, 0x2, 0x2, 0x7b, 0x7c, 0x7, 0x17, 0x2, 0x2, 0x7c, 0x7d, 
    0x7, 0xb, 0x2, 0x2, 0x7d, 0x19, 0x3, 0x2, 0x2, 0x2, 0x7e, 0x7f, 0x7, 
    0x18, 0x2, 0x2, 0x7f, 0x80, 0x7, 0x12, 0x2, 0x2, 0x80, 0x81, 0x5, 0x16, 
    0xc, 0x2, 0x81, 0x1b, 0x3, 0x2, 0x2, 0x2, 0x82, 0x83, 0x5, 0x16, 0xc, 
    0x2, 0x83, 0x84, 0x9, 0x5, 0x2, 0x2, 0x84, 0x85, 0x5, 0x16, 0xc, 0x2, 
    0x85, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x86, 0x87, 0x7, 0x18, 0x2, 0x2, 0x87, 
    0x88, 0x7, 0x10, 0x2, 0x2, 0x88, 0x89, 0x5, 0x18, 0xd, 0x2, 0x89, 0x1f, 
    0x3, 0x2, 0x2, 0x2, 0x8a, 0x8d, 0x5, 0x1c, 0xf, 0x2, 0x8b, 0x8d, 0x5, 
    0x1e, 0x10, 0x2, 0x8c, 0x8a, 0x3, 0x2, 0x2, 0x2, 0x8c, 0x8b, 0x3, 0x2, 
    0x2, 0x2, 0x8d, 0x90, 0x3, 0x2, 0x2, 0x2, 0x8e, 0x8c, 0x3, 0x2, 0x2, 
    0x2, 0x8e, 0x8f, 0x3, 0x2, 0x2, 0x2, 0x8f, 0x21, 0x3, 0x2, 0x2, 0x2, 
    0x90, 0x8e, 0x3, 0x2, 0x2, 0x2, 0xe, 0x27, 0x31, 0x33, 0x45, 0x4c, 0x5c, 
    0x62, 0x68, 0x6f, 0x75, 0x8c, 0x8e, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

TransitionParser::Initializer TransitionParser::_init;