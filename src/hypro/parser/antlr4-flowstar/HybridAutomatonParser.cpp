
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

HybridAutomatonParser::SettingContext* HybridAutomatonParser::StartContext::setting() {
  return getRuleContext<HybridAutomatonParser::SettingContext>(0);
}

HybridAutomatonParser::ModesContext* HybridAutomatonParser::StartContext::modes() {
  return getRuleContext<HybridAutomatonParser::ModesContext>(0);
}

HybridAutomatonParser::JumpsContext* HybridAutomatonParser::StartContext::jumps() {
  return getRuleContext<HybridAutomatonParser::JumpsContext>(0);
}

std::vector<HybridAutomatonParser::InitContext *> HybridAutomatonParser::StartContext::init() {
  return getRuleContexts<HybridAutomatonParser::InitContext>();
}

HybridAutomatonParser::InitContext* HybridAutomatonParser::StartContext::init(size_t i) {
  return getRuleContext<HybridAutomatonParser::InitContext>(i);
}

HybridAutomatonParser::UnsafesetContext* HybridAutomatonParser::StartContext::unsafeset() {
  return getRuleContext<HybridAutomatonParser::UnsafesetContext>(0);
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
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(76);
    match(HybridAutomatonParser::T__0);
    setState(77);
    match(HybridAutomatonParser::T__1);
    setState(78);
    vardeclaration();
    setState(79);
    setting();
    setState(80);
    modes();
    setState(81);
    jumps();
    setState(83); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(82);
      init();
      setState(85); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == HybridAutomatonParser::T__29);
    setState(87);
    match(HybridAutomatonParser::T__2);
    setState(89);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HybridAutomatonParser::T__30) {
      setState(88);
      unsafeset();
    }
   
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
    setState(91);
    match(HybridAutomatonParser::T__3);
    setState(92);
    match(HybridAutomatonParser::VARIABLE);
    setState(99);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HybridAutomatonParser::T__4) {
      setState(95); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(93);
        match(HybridAutomatonParser::T__4);
        setState(94);
        match(HybridAutomatonParser::VARIABLE);
        setState(97); 
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
  enterRule(_localctx, 4, HybridAutomatonParser::RuleJumps);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(101);
    match(HybridAutomatonParser::T__5);
    setState(102);
    match(HybridAutomatonParser::T__1);
    setState(106);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HybridAutomatonParser::VARIABLE) {
      setState(103);
      transition();
      setState(108);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(109);
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
  enterRule(_localctx, 6, HybridAutomatonParser::RuleTransition);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(111);
    fromto();
    setState(118);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << HybridAutomatonParser::T__6)
      | (1ULL << HybridAutomatonParser::T__7)
      | (1ULL << HybridAutomatonParser::T__8)
      | (1ULL << HybridAutomatonParser::PARALLELOTOPE)
      | (1ULL << HybridAutomatonParser::BOX))) != 0)) {
      setState(116);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case HybridAutomatonParser::T__6: {
          setState(112);
          urgent();
          break;
        }

        case HybridAutomatonParser::T__7: {
          setState(113);
          guard();
          break;
        }

        case HybridAutomatonParser::T__8: {
          setState(114);
          resetfct();
          break;
        }

        case HybridAutomatonParser::PARALLELOTOPE:
        case HybridAutomatonParser::BOX: {
          setState(115);
          aggregation();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(120);
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
  enterRule(_localctx, 8, HybridAutomatonParser::RuleFromto);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(121);
    match(HybridAutomatonParser::VARIABLE);
    setState(122);
    match(HybridAutomatonParser::JUMP);
    setState(123);
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
  enterRule(_localctx, 10, HybridAutomatonParser::RuleUrgent);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(125);
    match(HybridAutomatonParser::T__6);
   
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

HybridAutomatonParser::ConstrsetContext* HybridAutomatonParser::GuardContext::constrset() {
  return getRuleContext<HybridAutomatonParser::ConstrsetContext>(0);
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
  enterRule(_localctx, 12, HybridAutomatonParser::RuleGuard);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(127);
    match(HybridAutomatonParser::T__7);
    setState(128);
    match(HybridAutomatonParser::T__1);
    setState(129);
    constrset();
    setState(130);
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
  enterRule(_localctx, 14, HybridAutomatonParser::RuleAllocation);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(132);
    match(HybridAutomatonParser::VARIABLE);
    setState(133);
    match(HybridAutomatonParser::DEFINE);
    setState(136);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case HybridAutomatonParser::PLUS:
      case HybridAutomatonParser::MINUS:
      case HybridAutomatonParser::NUMBER:
      case HybridAutomatonParser::VARIABLE: {
        setState(134);
        polynom();
        break;
      }

      case HybridAutomatonParser::T__9: {
        setState(135);
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
  enterRule(_localctx, 16, HybridAutomatonParser::RuleResetfct);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(138);
    match(HybridAutomatonParser::T__8);
    setState(139);
    match(HybridAutomatonParser::T__1);
    setState(143);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HybridAutomatonParser::VARIABLE) {
      setState(140);
      allocation();
      setState(145);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(146);
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
  enterRule(_localctx, 18, HybridAutomatonParser::RuleAggregation);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(148);
    _la = _input->LA(1);
    if (!(_la == HybridAutomatonParser::PARALLELOTOPE

    || _la == HybridAutomatonParser::BOX)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(149);
    match(HybridAutomatonParser::T__1);
    setState(150);
    match(HybridAutomatonParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConnectorContext ------------------------------------------------------------------

HybridAutomatonParser::ConnectorContext::ConnectorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HybridAutomatonParser::ConnectorContext::PLUS() {
  return getToken(HybridAutomatonParser::PLUS, 0);
}

tree::TerminalNode* HybridAutomatonParser::ConnectorContext::MINUS() {
  return getToken(HybridAutomatonParser::MINUS, 0);
}


size_t HybridAutomatonParser::ConnectorContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleConnector;
}

antlrcpp::Any HybridAutomatonParser::ConnectorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitConnector(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::ConnectorContext* HybridAutomatonParser::connector() {
  ConnectorContext *_localctx = _tracker.createInstance<ConnectorContext>(_ctx, getState());
  enterRule(_localctx, 20, HybridAutomatonParser::RuleConnector);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(152);
    _la = _input->LA(1);
    if (!(_la == HybridAutomatonParser::PLUS

    || _la == HybridAutomatonParser::MINUS)) {
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

std::vector<HybridAutomatonParser::ConnectorContext *> HybridAutomatonParser::TermContext::connector() {
  return getRuleContexts<HybridAutomatonParser::ConnectorContext>();
}

HybridAutomatonParser::ConnectorContext* HybridAutomatonParser::TermContext::connector(size_t i) {
  return getRuleContext<HybridAutomatonParser::ConnectorContext>(i);
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
  enterRule(_localctx, 22, HybridAutomatonParser::RuleTerm);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(154);
    _la = _input->LA(1);
    if (!(_la == HybridAutomatonParser::NUMBER

    || _la == HybridAutomatonParser::VARIABLE)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(165);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HybridAutomatonParser::TIMES) {
      setState(155);
      match(HybridAutomatonParser::TIMES);
      setState(159);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == HybridAutomatonParser::PLUS

      || _la == HybridAutomatonParser::MINUS) {
        setState(156);
        connector();
        setState(161);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(162);
      _la = _input->LA(1);
      if (!(_la == HybridAutomatonParser::NUMBER

      || _la == HybridAutomatonParser::VARIABLE)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(167);
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

std::vector<HybridAutomatonParser::ConnectorContext *> HybridAutomatonParser::PolynomContext::connector() {
  return getRuleContexts<HybridAutomatonParser::ConnectorContext>();
}

HybridAutomatonParser::ConnectorContext* HybridAutomatonParser::PolynomContext::connector(size_t i) {
  return getRuleContext<HybridAutomatonParser::ConnectorContext>(i);
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
  enterRule(_localctx, 24, HybridAutomatonParser::RulePolynom);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(171);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HybridAutomatonParser::PLUS

    || _la == HybridAutomatonParser::MINUS) {
      setState(168);
      connector();
      setState(173);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(174);
    term();
    setState(184);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(176); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(175);
          connector();
          setState(178); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == HybridAutomatonParser::PLUS

        || _la == HybridAutomatonParser::MINUS);
        setState(180);
        term(); 
      }
      setState(186);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx);
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
  enterRule(_localctx, 26, HybridAutomatonParser::RuleInterval);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(187);
    match(HybridAutomatonParser::T__9);
    setState(188);
    match(HybridAutomatonParser::NUMBER);
    setState(189);
    match(HybridAutomatonParser::T__4);
    setState(190);
    match(HybridAutomatonParser::NUMBER);
    setState(191);
    match(HybridAutomatonParser::T__10);
   
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
  enterRule(_localctx, 28, HybridAutomatonParser::RuleEquation);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(193);
    match(HybridAutomatonParser::VARIABLE);
    setState(194);
    match(HybridAutomatonParser::EQUALS);
    setState(195);
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
  enterRule(_localctx, 30, HybridAutomatonParser::RuleConstraint);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(197);
    polynom();
    setState(198);
    _la = _input->LA(1);
    if (!(_la == HybridAutomatonParser::EQUALS

    || _la == HybridAutomatonParser::BOOLRELATION)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(199);
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
  enterRule(_localctx, 32, HybridAutomatonParser::RuleIntervalexpr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(201);
    match(HybridAutomatonParser::VARIABLE);
    setState(202);
    match(HybridAutomatonParser::IN);
    setState(203);
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

HybridAutomatonParser::ConstrsetContext::ConstrsetContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridAutomatonParser::ConstraintContext *> HybridAutomatonParser::ConstrsetContext::constraint() {
  return getRuleContexts<HybridAutomatonParser::ConstraintContext>();
}

HybridAutomatonParser::ConstraintContext* HybridAutomatonParser::ConstrsetContext::constraint(size_t i) {
  return getRuleContext<HybridAutomatonParser::ConstraintContext>(i);
}

std::vector<HybridAutomatonParser::IntervalexprContext *> HybridAutomatonParser::ConstrsetContext::intervalexpr() {
  return getRuleContexts<HybridAutomatonParser::IntervalexprContext>();
}

HybridAutomatonParser::IntervalexprContext* HybridAutomatonParser::ConstrsetContext::intervalexpr(size_t i) {
  return getRuleContext<HybridAutomatonParser::IntervalexprContext>(i);
}


size_t HybridAutomatonParser::ConstrsetContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleConstrset;
}

antlrcpp::Any HybridAutomatonParser::ConstrsetContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitConstrset(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::ConstrsetContext* HybridAutomatonParser::constrset() {
  ConstrsetContext *_localctx = _tracker.createInstance<ConstrsetContext>(_ctx, getState());
  enterRule(_localctx, 34, HybridAutomatonParser::RuleConstrset);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(209);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << HybridAutomatonParser::PLUS)
      | (1ULL << HybridAutomatonParser::MINUS)
      | (1ULL << HybridAutomatonParser::NUMBER)
      | (1ULL << HybridAutomatonParser::VARIABLE))) != 0)) {
      setState(207);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
      case 1: {
        setState(205);
        constraint();
        break;
      }

      case 2: {
        setState(206);
        intervalexpr();
        break;
      }

      }
      setState(211);
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

//----------------- SettingContext ------------------------------------------------------------------

HybridAutomatonParser::SettingContext::SettingContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridAutomatonParser::FixedstepsContext *> HybridAutomatonParser::SettingContext::fixedsteps() {
  return getRuleContexts<HybridAutomatonParser::FixedstepsContext>();
}

HybridAutomatonParser::FixedstepsContext* HybridAutomatonParser::SettingContext::fixedsteps(size_t i) {
  return getRuleContext<HybridAutomatonParser::FixedstepsContext>(i);
}

std::vector<HybridAutomatonParser::TimeContext *> HybridAutomatonParser::SettingContext::time() {
  return getRuleContexts<HybridAutomatonParser::TimeContext>();
}

HybridAutomatonParser::TimeContext* HybridAutomatonParser::SettingContext::time(size_t i) {
  return getRuleContext<HybridAutomatonParser::TimeContext>(i);
}

std::vector<HybridAutomatonParser::RemainderContext *> HybridAutomatonParser::SettingContext::remainder() {
  return getRuleContexts<HybridAutomatonParser::RemainderContext>();
}

HybridAutomatonParser::RemainderContext* HybridAutomatonParser::SettingContext::remainder(size_t i) {
  return getRuleContext<HybridAutomatonParser::RemainderContext>(i);
}

std::vector<HybridAutomatonParser::IdentityContext *> HybridAutomatonParser::SettingContext::identity() {
  return getRuleContexts<HybridAutomatonParser::IdentityContext>();
}

HybridAutomatonParser::IdentityContext* HybridAutomatonParser::SettingContext::identity(size_t i) {
  return getRuleContext<HybridAutomatonParser::IdentityContext>(i);
}

std::vector<HybridAutomatonParser::PlotsettingContext *> HybridAutomatonParser::SettingContext::plotsetting() {
  return getRuleContexts<HybridAutomatonParser::PlotsettingContext>();
}

HybridAutomatonParser::PlotsettingContext* HybridAutomatonParser::SettingContext::plotsetting(size_t i) {
  return getRuleContext<HybridAutomatonParser::PlotsettingContext>(i);
}

std::vector<HybridAutomatonParser::FixedordersContext *> HybridAutomatonParser::SettingContext::fixedorders() {
  return getRuleContexts<HybridAutomatonParser::FixedordersContext>();
}

HybridAutomatonParser::FixedordersContext* HybridAutomatonParser::SettingContext::fixedorders(size_t i) {
  return getRuleContext<HybridAutomatonParser::FixedordersContext>(i);
}

std::vector<HybridAutomatonParser::CutoffContext *> HybridAutomatonParser::SettingContext::cutoff() {
  return getRuleContexts<HybridAutomatonParser::CutoffContext>();
}

HybridAutomatonParser::CutoffContext* HybridAutomatonParser::SettingContext::cutoff(size_t i) {
  return getRuleContext<HybridAutomatonParser::CutoffContext>(i);
}

std::vector<HybridAutomatonParser::PrecisionContext *> HybridAutomatonParser::SettingContext::precision() {
  return getRuleContexts<HybridAutomatonParser::PrecisionContext>();
}

HybridAutomatonParser::PrecisionContext* HybridAutomatonParser::SettingContext::precision(size_t i) {
  return getRuleContext<HybridAutomatonParser::PrecisionContext>(i);
}

std::vector<HybridAutomatonParser::FilenameContext *> HybridAutomatonParser::SettingContext::filename() {
  return getRuleContexts<HybridAutomatonParser::FilenameContext>();
}

HybridAutomatonParser::FilenameContext* HybridAutomatonParser::SettingContext::filename(size_t i) {
  return getRuleContext<HybridAutomatonParser::FilenameContext>(i);
}

std::vector<HybridAutomatonParser::MaxjumpsContext *> HybridAutomatonParser::SettingContext::maxjumps() {
  return getRuleContexts<HybridAutomatonParser::MaxjumpsContext>();
}

HybridAutomatonParser::MaxjumpsContext* HybridAutomatonParser::SettingContext::maxjumps(size_t i) {
  return getRuleContext<HybridAutomatonParser::MaxjumpsContext>(i);
}

std::vector<HybridAutomatonParser::PrintContext *> HybridAutomatonParser::SettingContext::print() {
  return getRuleContexts<HybridAutomatonParser::PrintContext>();
}

HybridAutomatonParser::PrintContext* HybridAutomatonParser::SettingContext::print(size_t i) {
  return getRuleContext<HybridAutomatonParser::PrintContext>(i);
}


size_t HybridAutomatonParser::SettingContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleSetting;
}

antlrcpp::Any HybridAutomatonParser::SettingContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitSetting(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::SettingContext* HybridAutomatonParser::setting() {
  SettingContext *_localctx = _tracker.createInstance<SettingContext>(_ctx, getState());
  enterRule(_localctx, 36, HybridAutomatonParser::RuleSetting);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(212);
    match(HybridAutomatonParser::T__11);
    setState(213);
    match(HybridAutomatonParser::T__1);
    setState(227);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << HybridAutomatonParser::T__12)
      | (1ULL << HybridAutomatonParser::T__13)
      | (1ULL << HybridAutomatonParser::T__14)
      | (1ULL << HybridAutomatonParser::T__15)
      | (1ULL << HybridAutomatonParser::T__16)
      | (1ULL << HybridAutomatonParser::T__17)
      | (1ULL << HybridAutomatonParser::T__18)
      | (1ULL << HybridAutomatonParser::T__19)
      | (1ULL << HybridAutomatonParser::T__20)
      | (1ULL << HybridAutomatonParser::T__21)
      | (1ULL << HybridAutomatonParser::T__22))) != 0)) {
      setState(225);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case HybridAutomatonParser::T__12: {
          setState(214);
          fixedsteps();
          break;
        }

        case HybridAutomatonParser::T__13: {
          setState(215);
          time();
          break;
        }

        case HybridAutomatonParser::T__18: {
          setState(216);
          remainder();
          break;
        }

        case HybridAutomatonParser::T__19: {
          setState(217);
          identity();
          break;
        }

        case HybridAutomatonParser::T__14: {
          setState(218);
          plotsetting();
          break;
        }

        case HybridAutomatonParser::T__20: {
          setState(219);
          fixedorders();
          break;
        }

        case HybridAutomatonParser::T__21: {
          setState(220);
          cutoff();
          break;
        }

        case HybridAutomatonParser::T__22: {
          setState(221);
          precision();
          break;
        }

        case HybridAutomatonParser::T__15: {
          setState(222);
          filename();
          break;
        }

        case HybridAutomatonParser::T__16: {
          setState(223);
          maxjumps();
          break;
        }

        case HybridAutomatonParser::T__17: {
          setState(224);
          print();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(229);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(230);
    match(HybridAutomatonParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FixedstepsContext ------------------------------------------------------------------

HybridAutomatonParser::FixedstepsContext::FixedstepsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HybridAutomatonParser::FixedstepsContext::NUMBER() {
  return getToken(HybridAutomatonParser::NUMBER, 0);
}


size_t HybridAutomatonParser::FixedstepsContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleFixedsteps;
}

antlrcpp::Any HybridAutomatonParser::FixedstepsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitFixedsteps(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::FixedstepsContext* HybridAutomatonParser::fixedsteps() {
  FixedstepsContext *_localctx = _tracker.createInstance<FixedstepsContext>(_ctx, getState());
  enterRule(_localctx, 38, HybridAutomatonParser::RuleFixedsteps);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(232);
    match(HybridAutomatonParser::T__12);
    setState(233);
    match(HybridAutomatonParser::NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TimeContext ------------------------------------------------------------------

HybridAutomatonParser::TimeContext::TimeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HybridAutomatonParser::TimeContext::NUMBER() {
  return getToken(HybridAutomatonParser::NUMBER, 0);
}


size_t HybridAutomatonParser::TimeContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleTime;
}

antlrcpp::Any HybridAutomatonParser::TimeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitTime(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::TimeContext* HybridAutomatonParser::time() {
  TimeContext *_localctx = _tracker.createInstance<TimeContext>(_ctx, getState());
  enterRule(_localctx, 40, HybridAutomatonParser::RuleTime);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(235);
    match(HybridAutomatonParser::T__13);
    setState(236);
    match(HybridAutomatonParser::NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PlotsettingContext ------------------------------------------------------------------

HybridAutomatonParser::PlotsettingContext::PlotsettingContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> HybridAutomatonParser::PlotsettingContext::VARIABLE() {
  return getTokens(HybridAutomatonParser::VARIABLE);
}

tree::TerminalNode* HybridAutomatonParser::PlotsettingContext::VARIABLE(size_t i) {
  return getToken(HybridAutomatonParser::VARIABLE, i);
}


size_t HybridAutomatonParser::PlotsettingContext::getRuleIndex() const {
  return HybridAutomatonParser::RulePlotsetting;
}

antlrcpp::Any HybridAutomatonParser::PlotsettingContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitPlotsetting(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::PlotsettingContext* HybridAutomatonParser::plotsetting() {
  PlotsettingContext *_localctx = _tracker.createInstance<PlotsettingContext>(_ctx, getState());
  enterRule(_localctx, 42, HybridAutomatonParser::RulePlotsetting);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(238);
    match(HybridAutomatonParser::T__14);
    setState(239);
    match(HybridAutomatonParser::VARIABLE);
    setState(246);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HybridAutomatonParser::T__4) {
      setState(242); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(240);
        match(HybridAutomatonParser::T__4);
        setState(241);
        match(HybridAutomatonParser::VARIABLE);
        setState(244); 
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

//----------------- FilenameContext ------------------------------------------------------------------

HybridAutomatonParser::FilenameContext::FilenameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HybridAutomatonParser::FilenameContext::VARIABLE() {
  return getToken(HybridAutomatonParser::VARIABLE, 0);
}


size_t HybridAutomatonParser::FilenameContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleFilename;
}

antlrcpp::Any HybridAutomatonParser::FilenameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitFilename(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::FilenameContext* HybridAutomatonParser::filename() {
  FilenameContext *_localctx = _tracker.createInstance<FilenameContext>(_ctx, getState());
  enterRule(_localctx, 44, HybridAutomatonParser::RuleFilename);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(248);
    match(HybridAutomatonParser::T__15);
    setState(249);
    match(HybridAutomatonParser::VARIABLE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MaxjumpsContext ------------------------------------------------------------------

HybridAutomatonParser::MaxjumpsContext::MaxjumpsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HybridAutomatonParser::MaxjumpsContext::NUMBER() {
  return getToken(HybridAutomatonParser::NUMBER, 0);
}


size_t HybridAutomatonParser::MaxjumpsContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleMaxjumps;
}

antlrcpp::Any HybridAutomatonParser::MaxjumpsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitMaxjumps(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::MaxjumpsContext* HybridAutomatonParser::maxjumps() {
  MaxjumpsContext *_localctx = _tracker.createInstance<MaxjumpsContext>(_ctx, getState());
  enterRule(_localctx, 46, HybridAutomatonParser::RuleMaxjumps);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(251);
    match(HybridAutomatonParser::T__16);
    setState(252);
    match(HybridAutomatonParser::NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrintContext ------------------------------------------------------------------

HybridAutomatonParser::PrintContext::PrintContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HybridAutomatonParser::PrintContext::VARIABLE() {
  return getToken(HybridAutomatonParser::VARIABLE, 0);
}


size_t HybridAutomatonParser::PrintContext::getRuleIndex() const {
  return HybridAutomatonParser::RulePrint;
}

antlrcpp::Any HybridAutomatonParser::PrintContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitPrint(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::PrintContext* HybridAutomatonParser::print() {
  PrintContext *_localctx = _tracker.createInstance<PrintContext>(_ctx, getState());
  enterRule(_localctx, 48, HybridAutomatonParser::RulePrint);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(254);
    match(HybridAutomatonParser::T__17);
    setState(255);
    match(HybridAutomatonParser::VARIABLE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RemainderContext ------------------------------------------------------------------

HybridAutomatonParser::RemainderContext::RemainderContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HybridAutomatonParser::RemainderContext::EXPONENTIAL() {
  return getToken(HybridAutomatonParser::EXPONENTIAL, 0);
}


size_t HybridAutomatonParser::RemainderContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleRemainder;
}

antlrcpp::Any HybridAutomatonParser::RemainderContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitRemainder(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::RemainderContext* HybridAutomatonParser::remainder() {
  RemainderContext *_localctx = _tracker.createInstance<RemainderContext>(_ctx, getState());
  enterRule(_localctx, 50, HybridAutomatonParser::RuleRemainder);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(257);
    match(HybridAutomatonParser::T__18);
    setState(258);
    match(HybridAutomatonParser::EXPONENTIAL);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdentityContext ------------------------------------------------------------------

HybridAutomatonParser::IdentityContext::IdentityContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t HybridAutomatonParser::IdentityContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleIdentity;
}

antlrcpp::Any HybridAutomatonParser::IdentityContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitIdentity(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::IdentityContext* HybridAutomatonParser::identity() {
  IdentityContext *_localctx = _tracker.createInstance<IdentityContext>(_ctx, getState());
  enterRule(_localctx, 52, HybridAutomatonParser::RuleIdentity);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(260);
    match(HybridAutomatonParser::T__19);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FixedordersContext ------------------------------------------------------------------

HybridAutomatonParser::FixedordersContext::FixedordersContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HybridAutomatonParser::FixedordersContext::NUMBER() {
  return getToken(HybridAutomatonParser::NUMBER, 0);
}


size_t HybridAutomatonParser::FixedordersContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleFixedorders;
}

antlrcpp::Any HybridAutomatonParser::FixedordersContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitFixedorders(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::FixedordersContext* HybridAutomatonParser::fixedorders() {
  FixedordersContext *_localctx = _tracker.createInstance<FixedordersContext>(_ctx, getState());
  enterRule(_localctx, 54, HybridAutomatonParser::RuleFixedorders);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(262);
    match(HybridAutomatonParser::T__20);
    setState(263);
    match(HybridAutomatonParser::NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CutoffContext ------------------------------------------------------------------

HybridAutomatonParser::CutoffContext::CutoffContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HybridAutomatonParser::CutoffContext::EXPONENTIAL() {
  return getToken(HybridAutomatonParser::EXPONENTIAL, 0);
}


size_t HybridAutomatonParser::CutoffContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleCutoff;
}

antlrcpp::Any HybridAutomatonParser::CutoffContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitCutoff(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::CutoffContext* HybridAutomatonParser::cutoff() {
  CutoffContext *_localctx = _tracker.createInstance<CutoffContext>(_ctx, getState());
  enterRule(_localctx, 56, HybridAutomatonParser::RuleCutoff);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(265);
    match(HybridAutomatonParser::T__21);
    setState(266);
    match(HybridAutomatonParser::EXPONENTIAL);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrecisionContext ------------------------------------------------------------------

HybridAutomatonParser::PrecisionContext::PrecisionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HybridAutomatonParser::PrecisionContext::NUMBER() {
  return getToken(HybridAutomatonParser::NUMBER, 0);
}


size_t HybridAutomatonParser::PrecisionContext::getRuleIndex() const {
  return HybridAutomatonParser::RulePrecision;
}

antlrcpp::Any HybridAutomatonParser::PrecisionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitPrecision(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::PrecisionContext* HybridAutomatonParser::precision() {
  PrecisionContext *_localctx = _tracker.createInstance<PrecisionContext>(_ctx, getState());
  enterRule(_localctx, 58, HybridAutomatonParser::RulePrecision);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(268);
    match(HybridAutomatonParser::T__22);
    setState(269);
    match(HybridAutomatonParser::NUMBER);
   
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
  enterRule(_localctx, 60, HybridAutomatonParser::RuleModes);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(271);
    match(HybridAutomatonParser::T__23);
    setState(272);
    match(HybridAutomatonParser::T__1);
    setState(276);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HybridAutomatonParser::VARIABLE) {
      setState(273);
      location();
      setState(278);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(279);
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

std::vector<HybridAutomatonParser::InvariantsContext *> HybridAutomatonParser::LocationContext::invariants() {
  return getRuleContexts<HybridAutomatonParser::InvariantsContext>();
}

HybridAutomatonParser::InvariantsContext* HybridAutomatonParser::LocationContext::invariants(size_t i) {
  return getRuleContext<HybridAutomatonParser::InvariantsContext>(i);
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
  enterRule(_localctx, 62, HybridAutomatonParser::RuleLocation);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(281);
    match(HybridAutomatonParser::VARIABLE);
    setState(282);
    match(HybridAutomatonParser::T__1);
    setState(283);
    activities();
    setState(287);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HybridAutomatonParser::T__28) {
      setState(284);
      invariants();
      setState(289);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(290);
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
  enterRule(_localctx, 64, HybridAutomatonParser::RuleActivities);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(292);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << HybridAutomatonParser::T__24)
      | (1ULL << HybridAutomatonParser::T__25)
      | (1ULL << HybridAutomatonParser::T__26)
      | (1ULL << HybridAutomatonParser::T__27))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(293);
    match(HybridAutomatonParser::T__1);
    setState(297);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HybridAutomatonParser::VARIABLE) {
      setState(294);
      equation();
      setState(299);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(300);
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

HybridAutomatonParser::ConstrsetContext* HybridAutomatonParser::InvariantsContext::constrset() {
  return getRuleContext<HybridAutomatonParser::ConstrsetContext>(0);
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
  enterRule(_localctx, 66, HybridAutomatonParser::RuleInvariants);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(302);
    match(HybridAutomatonParser::T__28);
    setState(303);
    match(HybridAutomatonParser::T__1);
    setState(305);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
    case 1: {
      setState(304);
      constrset();
      break;
    }

    }
    setState(307);
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

std::vector<HybridAutomatonParser::InitstateContext *> HybridAutomatonParser::InitContext::initstate() {
  return getRuleContexts<HybridAutomatonParser::InitstateContext>();
}

HybridAutomatonParser::InitstateContext* HybridAutomatonParser::InitContext::initstate(size_t i) {
  return getRuleContext<HybridAutomatonParser::InitstateContext>(i);
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
  enterRule(_localctx, 68, HybridAutomatonParser::RuleInit);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(309);
    match(HybridAutomatonParser::T__29);
    setState(310);
    match(HybridAutomatonParser::T__1);
    setState(312); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(311);
      initstate();
      setState(314); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == HybridAutomatonParser::VARIABLE);
    setState(316);
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

HybridAutomatonParser::ConstrsetContext* HybridAutomatonParser::InitstateContext::constrset() {
  return getRuleContext<HybridAutomatonParser::ConstrsetContext>(0);
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
  enterRule(_localctx, 70, HybridAutomatonParser::RuleInitstate);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(318);
    match(HybridAutomatonParser::VARIABLE);
    setState(319);
    match(HybridAutomatonParser::T__1);
    setState(320);
    constrset();
    setState(321);
    match(HybridAutomatonParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnsafesetContext ------------------------------------------------------------------

HybridAutomatonParser::UnsafesetContext::UnsafesetContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridAutomatonParser::BadstateContext *> HybridAutomatonParser::UnsafesetContext::badstate() {
  return getRuleContexts<HybridAutomatonParser::BadstateContext>();
}

HybridAutomatonParser::BadstateContext* HybridAutomatonParser::UnsafesetContext::badstate(size_t i) {
  return getRuleContext<HybridAutomatonParser::BadstateContext>(i);
}


size_t HybridAutomatonParser::UnsafesetContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleUnsafeset;
}

antlrcpp::Any HybridAutomatonParser::UnsafesetContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitUnsafeset(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::UnsafesetContext* HybridAutomatonParser::unsafeset() {
  UnsafesetContext *_localctx = _tracker.createInstance<UnsafesetContext>(_ctx, getState());
  enterRule(_localctx, 72, HybridAutomatonParser::RuleUnsafeset);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(323);
    match(HybridAutomatonParser::T__30);
    setState(324);
    match(HybridAutomatonParser::T__1);
    setState(328);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HybridAutomatonParser::VARIABLE) {
      setState(325);
      badstate();
      setState(330);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(331);
    match(HybridAutomatonParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BadstateContext ------------------------------------------------------------------

HybridAutomatonParser::BadstateContext::BadstateContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HybridAutomatonParser::BadstateContext::VARIABLE() {
  return getToken(HybridAutomatonParser::VARIABLE, 0);
}

HybridAutomatonParser::ConstrsetContext* HybridAutomatonParser::BadstateContext::constrset() {
  return getRuleContext<HybridAutomatonParser::ConstrsetContext>(0);
}


size_t HybridAutomatonParser::BadstateContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleBadstate;
}

antlrcpp::Any HybridAutomatonParser::BadstateContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitBadstate(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::BadstateContext* HybridAutomatonParser::badstate() {
  BadstateContext *_localctx = _tracker.createInstance<BadstateContext>(_ctx, getState());
  enterRule(_localctx, 74, HybridAutomatonParser::RuleBadstate);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(333);
    match(HybridAutomatonParser::VARIABLE);
    setState(334);
    match(HybridAutomatonParser::T__1);
    setState(336);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
    case 1: {
      setState(335);
      constrset();
      break;
    }

    }
    setState(338);
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
  "start", "vardeclaration", "jumps", "transition", "fromto", "urgent", 
  "guard", "allocation", "resetfct", "aggregation", "connector", "term", 
  "polynom", "interval", "equation", "constraint", "intervalexpr", "constrset", 
  "setting", "fixedsteps", "time", "plotsetting", "filename", "maxjumps", 
  "print", "remainder", "identity", "fixedorders", "cutoff", "precision", 
  "modes", "location", "activities", "invariants", "init", "initstate", 
  "unsafeset", "badstate"
};

std::vector<std::string> HybridAutomatonParser::_literalNames = {
  "", "'hybrid reachability'", "'{'", "'}'", "'state var'", "','", "'jumps'", 
  "'urgent'", "'guard'", "'reset'", "'['", "']'", "'setting'", "'fixed steps'", 
  "'time'", "'gnuplot octagon'", "'output'", "'max jumps'", "'print'", "'remainder estimation'", 
  "'identity precondition'", "'fixed orders'", "'cutoff'", "'precision'", 
  "'modes'", "'poly ode 1'", "'poly ode 2'", "'poly ode 3'", "'linear ode'", 
  "'inv'", "'init'", "'unsafe set'", "'parallelotope aggregation'", "'box aggregation'", 
  "'->'", "':='", "'in'", "", "'='", "", "'+'", "'-'", "'*'"
};

std::vector<std::string> HybridAutomatonParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "PARALLELOTOPE", 
  "BOX", "JUMP", "DEFINE", "IN", "COMMENT", "EQUALS", "BOOLRELATION", "PLUS", 
  "MINUS", "TIMES", "NUMBER", "VARIABLE", "WS", "EXPONENTIAL"
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
    0x3, 0x30, 0x157, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
    0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 
    0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 
    0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 
    0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 
    0x12, 0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x4, 0x15, 
    0x9, 0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 0x9, 0x17, 0x4, 0x18, 0x9, 
    0x18, 0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 0x9, 0x1a, 0x4, 0x1b, 0x9, 0x1b, 
    0x4, 0x1c, 0x9, 0x1c, 0x4, 0x1d, 0x9, 0x1d, 0x4, 0x1e, 0x9, 0x1e, 0x4, 
    0x1f, 0x9, 0x1f, 0x4, 0x20, 0x9, 0x20, 0x4, 0x21, 0x9, 0x21, 0x4, 0x22, 
    0x9, 0x22, 0x4, 0x23, 0x9, 0x23, 0x4, 0x24, 0x9, 0x24, 0x4, 0x25, 0x9, 
    0x25, 0x4, 0x26, 0x9, 0x26, 0x4, 0x27, 0x9, 0x27, 0x3, 0x2, 0x3, 0x2, 
    0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x6, 0x2, 0x56, 0xa, 
    0x2, 0xd, 0x2, 0xe, 0x2, 0x57, 0x3, 0x2, 0x3, 0x2, 0x5, 0x2, 0x5c, 0xa, 
    0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x6, 0x3, 0x62, 0xa, 0x3, 
    0xd, 0x3, 0xe, 0x3, 0x63, 0x5, 0x3, 0x66, 0xa, 0x3, 0x3, 0x4, 0x3, 0x4, 
    0x3, 0x4, 0x7, 0x4, 0x6b, 0xa, 0x4, 0xc, 0x4, 0xe, 0x4, 0x6e, 0xb, 0x4, 
    0x3, 0x4, 0x3, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 
    0x7, 0x5, 0x77, 0xa, 0x5, 0xc, 0x5, 0xe, 0x5, 0x7a, 0xb, 0x5, 0x3, 0x6, 
    0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 0x8, 
    0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 
    0x5, 0x9, 0x8b, 0xa, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x7, 0xa, 0x90, 
    0xa, 0xa, 0xc, 0xa, 0xe, 0xa, 0x93, 0xb, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xd, 0x3, 
    0xd, 0x3, 0xd, 0x7, 0xd, 0xa0, 0xa, 0xd, 0xc, 0xd, 0xe, 0xd, 0xa3, 0xb, 
    0xd, 0x3, 0xd, 0x7, 0xd, 0xa6, 0xa, 0xd, 0xc, 0xd, 0xe, 0xd, 0xa9, 0xb, 
    0xd, 0x3, 0xe, 0x7, 0xe, 0xac, 0xa, 0xe, 0xc, 0xe, 0xe, 0xe, 0xaf, 0xb, 
    0xe, 0x3, 0xe, 0x3, 0xe, 0x6, 0xe, 0xb3, 0xa, 0xe, 0xd, 0xe, 0xe, 0xe, 
    0xb4, 0x3, 0xe, 0x3, 0xe, 0x7, 0xe, 0xb9, 0xa, 0xe, 0xc, 0xe, 0xe, 0xe, 
    0xbc, 0xb, 0xe, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 
    0xf, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x11, 0x3, 0x11, 
    0x3, 0x11, 0x3, 0x11, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 
    0x13, 0x3, 0x13, 0x7, 0x13, 0xd2, 0xa, 0x13, 0xc, 0x13, 0xe, 0x13, 0xd5, 
    0xb, 0x13, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 
    0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 
    0x3, 0x14, 0x7, 0x14, 0xe4, 0xa, 0x14, 0xc, 0x14, 0xe, 0x14, 0xe7, 0xb, 
    0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x16, 
    0x3, 0x16, 0x3, 0x16, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x6, 
    0x17, 0xf5, 0xa, 0x17, 0xd, 0x17, 0xe, 0x17, 0xf6, 0x5, 0x17, 0xf9, 
    0xa, 0x17, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x19, 0x3, 0x19, 0x3, 
    0x19, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 
    0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1e, 0x3, 
    0x1e, 0x3, 0x1e, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x20, 0x3, 0x20, 
    0x3, 0x20, 0x7, 0x20, 0x115, 0xa, 0x20, 0xc, 0x20, 0xe, 0x20, 0x118, 
    0xb, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x3, 
    0x21, 0x7, 0x21, 0x120, 0xa, 0x21, 0xc, 0x21, 0xe, 0x21, 0x123, 0xb, 
    0x21, 0x3, 0x21, 0x3, 0x21, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x7, 0x22, 
    0x12a, 0xa, 0x22, 0xc, 0x22, 0xe, 0x22, 0x12d, 0xb, 0x22, 0x3, 0x22, 
    0x3, 0x22, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x5, 0x23, 0x134, 0xa, 0x23, 
    0x3, 0x23, 0x3, 0x23, 0x3, 0x24, 0x3, 0x24, 0x3, 0x24, 0x6, 0x24, 0x13b, 
    0xa, 0x24, 0xd, 0x24, 0xe, 0x24, 0x13c, 0x3, 0x24, 0x3, 0x24, 0x3, 0x25, 
    0x3, 0x25, 0x3, 0x25, 0x3, 0x25, 0x3, 0x25, 0x3, 0x26, 0x3, 0x26, 0x3, 
    0x26, 0x7, 0x26, 0x149, 0xa, 0x26, 0xc, 0x26, 0xe, 0x26, 0x14c, 0xb, 
    0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x5, 0x27, 
    0x153, 0xa, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x2, 0x2, 0x28, 0x2, 
    0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 
    0x1e, 0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e, 0x30, 0x32, 0x34, 
    0x36, 0x38, 0x3a, 0x3c, 0x3e, 0x40, 0x42, 0x44, 0x46, 0x48, 0x4a, 0x4c, 
    0x2, 0x7, 0x3, 0x2, 0x22, 0x23, 0x3, 0x2, 0x2a, 0x2b, 0x3, 0x2, 0x2d, 
    0x2e, 0x3, 0x2, 0x28, 0x29, 0x3, 0x2, 0x1b, 0x1e, 0x2, 0x156, 0x2, 0x4e, 
    0x3, 0x2, 0x2, 0x2, 0x4, 0x5d, 0x3, 0x2, 0x2, 0x2, 0x6, 0x67, 0x3, 0x2, 
    0x2, 0x2, 0x8, 0x71, 0x3, 0x2, 0x2, 0x2, 0xa, 0x7b, 0x3, 0x2, 0x2, 0x2, 
    0xc, 0x7f, 0x3, 0x2, 0x2, 0x2, 0xe, 0x81, 0x3, 0x2, 0x2, 0x2, 0x10, 
    0x86, 0x3, 0x2, 0x2, 0x2, 0x12, 0x8c, 0x3, 0x2, 0x2, 0x2, 0x14, 0x96, 
    0x3, 0x2, 0x2, 0x2, 0x16, 0x9a, 0x3, 0x2, 0x2, 0x2, 0x18, 0x9c, 0x3, 
    0x2, 0x2, 0x2, 0x1a, 0xad, 0x3, 0x2, 0x2, 0x2, 0x1c, 0xbd, 0x3, 0x2, 
    0x2, 0x2, 0x1e, 0xc3, 0x3, 0x2, 0x2, 0x2, 0x20, 0xc7, 0x3, 0x2, 0x2, 
    0x2, 0x22, 0xcb, 0x3, 0x2, 0x2, 0x2, 0x24, 0xd3, 0x3, 0x2, 0x2, 0x2, 
    0x26, 0xd6, 0x3, 0x2, 0x2, 0x2, 0x28, 0xea, 0x3, 0x2, 0x2, 0x2, 0x2a, 
    0xed, 0x3, 0x2, 0x2, 0x2, 0x2c, 0xf0, 0x3, 0x2, 0x2, 0x2, 0x2e, 0xfa, 
    0x3, 0x2, 0x2, 0x2, 0x30, 0xfd, 0x3, 0x2, 0x2, 0x2, 0x32, 0x100, 0x3, 
    0x2, 0x2, 0x2, 0x34, 0x103, 0x3, 0x2, 0x2, 0x2, 0x36, 0x106, 0x3, 0x2, 
    0x2, 0x2, 0x38, 0x108, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x10b, 0x3, 0x2, 0x2, 
    0x2, 0x3c, 0x10e, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x111, 0x3, 0x2, 0x2, 0x2, 
    0x40, 0x11b, 0x3, 0x2, 0x2, 0x2, 0x42, 0x126, 0x3, 0x2, 0x2, 0x2, 0x44, 
    0x130, 0x3, 0x2, 0x2, 0x2, 0x46, 0x137, 0x3, 0x2, 0x2, 0x2, 0x48, 0x140, 
    0x3, 0x2, 0x2, 0x2, 0x4a, 0x145, 0x3, 0x2, 0x2, 0x2, 0x4c, 0x14f, 0x3, 
    0x2, 0x2, 0x2, 0x4e, 0x4f, 0x7, 0x3, 0x2, 0x2, 0x4f, 0x50, 0x7, 0x4, 
    0x2, 0x2, 0x50, 0x51, 0x5, 0x4, 0x3, 0x2, 0x51, 0x52, 0x5, 0x26, 0x14, 
    0x2, 0x52, 0x53, 0x5, 0x3e, 0x20, 0x2, 0x53, 0x55, 0x5, 0x6, 0x4, 0x2, 
    0x54, 0x56, 0x5, 0x46, 0x24, 0x2, 0x55, 0x54, 0x3, 0x2, 0x2, 0x2, 0x56, 
    0x57, 0x3, 0x2, 0x2, 0x2, 0x57, 0x55, 0x3, 0x2, 0x2, 0x2, 0x57, 0x58, 
    0x3, 0x2, 0x2, 0x2, 0x58, 0x59, 0x3, 0x2, 0x2, 0x2, 0x59, 0x5b, 0x7, 
    0x5, 0x2, 0x2, 0x5a, 0x5c, 0x5, 0x4a, 0x26, 0x2, 0x5b, 0x5a, 0x3, 0x2, 
    0x2, 0x2, 0x5b, 0x5c, 0x3, 0x2, 0x2, 0x2, 0x5c, 0x3, 0x3, 0x2, 0x2, 
    0x2, 0x5d, 0x5e, 0x7, 0x6, 0x2, 0x2, 0x5e, 0x65, 0x7, 0x2e, 0x2, 0x2, 
    0x5f, 0x60, 0x7, 0x7, 0x2, 0x2, 0x60, 0x62, 0x7, 0x2e, 0x2, 0x2, 0x61, 
    0x5f, 0x3, 0x2, 0x2, 0x2, 0x62, 0x63, 0x3, 0x2, 0x2, 0x2, 0x63, 0x61, 
    0x3, 0x2, 0x2, 0x2, 0x63, 0x64, 0x3, 0x2, 0x2, 0x2, 0x64, 0x66, 0x3, 
    0x2, 0x2, 0x2, 0x65, 0x61, 0x3, 0x2, 0x2, 0x2, 0x65, 0x66, 0x3, 0x2, 
    0x2, 0x2, 0x66, 0x5, 0x3, 0x2, 0x2, 0x2, 0x67, 0x68, 0x7, 0x8, 0x2, 
    0x2, 0x68, 0x6c, 0x7, 0x4, 0x2, 0x2, 0x69, 0x6b, 0x5, 0x8, 0x5, 0x2, 
    0x6a, 0x69, 0x3, 0x2, 0x2, 0x2, 0x6b, 0x6e, 0x3, 0x2, 0x2, 0x2, 0x6c, 
    0x6a, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x6d, 0x3, 0x2, 0x2, 0x2, 0x6d, 0x6f, 
    0x3, 0x2, 0x2, 0x2, 0x6e, 0x6c, 0x3, 0x2, 0x2, 0x2, 0x6f, 0x70, 0x7, 
    0x5, 0x2, 0x2, 0x70, 0x7, 0x3, 0x2, 0x2, 0x2, 0x71, 0x78, 0x5, 0xa, 
    0x6, 0x2, 0x72, 0x77, 0x5, 0xc, 0x7, 0x2, 0x73, 0x77, 0x5, 0xe, 0x8, 
    0x2, 0x74, 0x77, 0x5, 0x12, 0xa, 0x2, 0x75, 0x77, 0x5, 0x14, 0xb, 0x2, 
    0x76, 0x72, 0x3, 0x2, 0x2, 0x2, 0x76, 0x73, 0x3, 0x2, 0x2, 0x2, 0x76, 
    0x74, 0x3, 0x2, 0x2, 0x2, 0x76, 0x75, 0x3, 0x2, 0x2, 0x2, 0x77, 0x7a, 
    0x3, 0x2, 0x2, 0x2, 0x78, 0x76, 0x3, 0x2, 0x2, 0x2, 0x78, 0x79, 0x3, 
    0x2, 0x2, 0x2, 0x79, 0x9, 0x3, 0x2, 0x2, 0x2, 0x7a, 0x78, 0x3, 0x2, 
    0x2, 0x2, 0x7b, 0x7c, 0x7, 0x2e, 0x2, 0x2, 0x7c, 0x7d, 0x7, 0x24, 0x2, 
    0x2, 0x7d, 0x7e, 0x7, 0x2e, 0x2, 0x2, 0x7e, 0xb, 0x3, 0x2, 0x2, 0x2, 
    0x7f, 0x80, 0x7, 0x9, 0x2, 0x2, 0x80, 0xd, 0x3, 0x2, 0x2, 0x2, 0x81, 
    0x82, 0x7, 0xa, 0x2, 0x2, 0x82, 0x83, 0x7, 0x4, 0x2, 0x2, 0x83, 0x84, 
    0x5, 0x24, 0x13, 0x2, 0x84, 0x85, 0x7, 0x5, 0x2, 0x2, 0x85, 0xf, 0x3, 
    0x2, 0x2, 0x2, 0x86, 0x87, 0x7, 0x2e, 0x2, 0x2, 0x87, 0x8a, 0x7, 0x25, 
    0x2, 0x2, 0x88, 0x8b, 0x5, 0x1a, 0xe, 0x2, 0x89, 0x8b, 0x5, 0x1c, 0xf, 
    0x2, 0x8a, 0x88, 0x3, 0x2, 0x2, 0x2, 0x8a, 0x89, 0x3, 0x2, 0x2, 0x2, 
    0x8b, 0x11, 0x3, 0x2, 0x2, 0x2, 0x8c, 0x8d, 0x7, 0xb, 0x2, 0x2, 0x8d, 
    0x91, 0x7, 0x4, 0x2, 0x2, 0x8e, 0x90, 0x5, 0x10, 0x9, 0x2, 0x8f, 0x8e, 
    0x3, 0x2, 0x2, 0x2, 0x90, 0x93, 0x3, 0x2, 0x2, 0x2, 0x91, 0x8f, 0x3, 
    0x2, 0x2, 0x2, 0x91, 0x92, 0x3, 0x2, 0x2, 0x2, 0x92, 0x94, 0x3, 0x2, 
    0x2, 0x2, 0x93, 0x91, 0x3, 0x2, 0x2, 0x2, 0x94, 0x95, 0x7, 0x5, 0x2, 
    0x2, 0x95, 0x13, 0x3, 0x2, 0x2, 0x2, 0x96, 0x97, 0x9, 0x2, 0x2, 0x2, 
    0x97, 0x98, 0x7, 0x4, 0x2, 0x2, 0x98, 0x99, 0x7, 0x5, 0x2, 0x2, 0x99, 
    0x15, 0x3, 0x2, 0x2, 0x2, 0x9a, 0x9b, 0x9, 0x3, 0x2, 0x2, 0x9b, 0x17, 
    0x3, 0x2, 0x2, 0x2, 0x9c, 0xa7, 0x9, 0x4, 0x2, 0x2, 0x9d, 0xa1, 0x7, 
    0x2c, 0x2, 0x2, 0x9e, 0xa0, 0x5, 0x16, 0xc, 0x2, 0x9f, 0x9e, 0x3, 0x2, 
    0x2, 0x2, 0xa0, 0xa3, 0x3, 0x2, 0x2, 0x2, 0xa1, 0x9f, 0x3, 0x2, 0x2, 
    0x2, 0xa1, 0xa2, 0x3, 0x2, 0x2, 0x2, 0xa2, 0xa4, 0x3, 0x2, 0x2, 0x2, 
    0xa3, 0xa1, 0x3, 0x2, 0x2, 0x2, 0xa4, 0xa6, 0x9, 0x4, 0x2, 0x2, 0xa5, 
    0x9d, 0x3, 0x2, 0x2, 0x2, 0xa6, 0xa9, 0x3, 0x2, 0x2, 0x2, 0xa7, 0xa5, 
    0x3, 0x2, 0x2, 0x2, 0xa7, 0xa8, 0x3, 0x2, 0x2, 0x2, 0xa8, 0x19, 0x3, 
    0x2, 0x2, 0x2, 0xa9, 0xa7, 0x3, 0x2, 0x2, 0x2, 0xaa, 0xac, 0x5, 0x16, 
    0xc, 0x2, 0xab, 0xaa, 0x3, 0x2, 0x2, 0x2, 0xac, 0xaf, 0x3, 0x2, 0x2, 
    0x2, 0xad, 0xab, 0x3, 0x2, 0x2, 0x2, 0xad, 0xae, 0x3, 0x2, 0x2, 0x2, 
    0xae, 0xb0, 0x3, 0x2, 0x2, 0x2, 0xaf, 0xad, 0x3, 0x2, 0x2, 0x2, 0xb0, 
    0xba, 0x5, 0x18, 0xd, 0x2, 0xb1, 0xb3, 0x5, 0x16, 0xc, 0x2, 0xb2, 0xb1, 
    0x3, 0x2, 0x2, 0x2, 0xb3, 0xb4, 0x3, 0x2, 0x2, 0x2, 0xb4, 0xb2, 0x3, 
    0x2, 0x2, 0x2, 0xb4, 0xb5, 0x3, 0x2, 0x2, 0x2, 0xb5, 0xb6, 0x3, 0x2, 
    0x2, 0x2, 0xb6, 0xb7, 0x5, 0x18, 0xd, 0x2, 0xb7, 0xb9, 0x3, 0x2, 0x2, 
    0x2, 0xb8, 0xb2, 0x3, 0x2, 0x2, 0x2, 0xb9, 0xbc, 0x3, 0x2, 0x2, 0x2, 
    0xba, 0xb8, 0x3, 0x2, 0x2, 0x2, 0xba, 0xbb, 0x3, 0x2, 0x2, 0x2, 0xbb, 
    0x1b, 0x3, 0x2, 0x2, 0x2, 0xbc, 0xba, 0x3, 0x2, 0x2, 0x2, 0xbd, 0xbe, 
    0x7, 0xc, 0x2, 0x2, 0xbe, 0xbf, 0x7, 0x2d, 0x2, 0x2, 0xbf, 0xc0, 0x7, 
    0x7, 0x2, 0x2, 0xc0, 0xc1, 0x7, 0x2d, 0x2, 0x2, 0xc1, 0xc2, 0x7, 0xd, 
    0x2, 0x2, 0xc2, 0x1d, 0x3, 0x2, 0x2, 0x2, 0xc3, 0xc4, 0x7, 0x2e, 0x2, 
    0x2, 0xc4, 0xc5, 0x7, 0x28, 0x2, 0x2, 0xc5, 0xc6, 0x5, 0x1a, 0xe, 0x2, 
    0xc6, 0x1f, 0x3, 0x2, 0x2, 0x2, 0xc7, 0xc8, 0x5, 0x1a, 0xe, 0x2, 0xc8, 
    0xc9, 0x9, 0x5, 0x2, 0x2, 0xc9, 0xca, 0x5, 0x1a, 0xe, 0x2, 0xca, 0x21, 
    0x3, 0x2, 0x2, 0x2, 0xcb, 0xcc, 0x7, 0x2e, 0x2, 0x2, 0xcc, 0xcd, 0x7, 
    0x26, 0x2, 0x2, 0xcd, 0xce, 0x5, 0x1c, 0xf, 0x2, 0xce, 0x23, 0x3, 0x2, 
    0x2, 0x2, 0xcf, 0xd2, 0x5, 0x20, 0x11, 0x2, 0xd0, 0xd2, 0x5, 0x22, 0x12, 
    0x2, 0xd1, 0xcf, 0x3, 0x2, 0x2, 0x2, 0xd1, 0xd0, 0x3, 0x2, 0x2, 0x2, 
    0xd2, 0xd5, 0x3, 0x2, 0x2, 0x2, 0xd3, 0xd1, 0x3, 0x2, 0x2, 0x2, 0xd3, 
    0xd4, 0x3, 0x2, 0x2, 0x2, 0xd4, 0x25, 0x3, 0x2, 0x2, 0x2, 0xd5, 0xd3, 
    0x3, 0x2, 0x2, 0x2, 0xd6, 0xd7, 0x7, 0xe, 0x2, 0x2, 0xd7, 0xe5, 0x7, 
    0x4, 0x2, 0x2, 0xd8, 0xe4, 0x5, 0x28, 0x15, 0x2, 0xd9, 0xe4, 0x5, 0x2a, 
    0x16, 0x2, 0xda, 0xe4, 0x5, 0x34, 0x1b, 0x2, 0xdb, 0xe4, 0x5, 0x36, 
    0x1c, 0x2, 0xdc, 0xe4, 0x5, 0x2c, 0x17, 0x2, 0xdd, 0xe4, 0x5, 0x38, 
    0x1d, 0x2, 0xde, 0xe4, 0x5, 0x3a, 0x1e, 0x2, 0xdf, 0xe4, 0x5, 0x3c, 
    0x1f, 0x2, 0xe0, 0xe4, 0x5, 0x2e, 0x18, 0x2, 0xe1, 0xe4, 0x5, 0x30, 
    0x19, 0x2, 0xe2, 0xe4, 0x5, 0x32, 0x1a, 0x2, 0xe3, 0xd8, 0x3, 0x2, 0x2, 
    0x2, 0xe3, 0xd9, 0x3, 0x2, 0x2, 0x2, 0xe3, 0xda, 0x3, 0x2, 0x2, 0x2, 
    0xe3, 0xdb, 0x3, 0x2, 0x2, 0x2, 0xe3, 0xdc, 0x3, 0x2, 0x2, 0x2, 0xe3, 
    0xdd, 0x3, 0x2, 0x2, 0x2, 0xe3, 0xde, 0x3, 0x2, 0x2, 0x2, 0xe3, 0xdf, 
    0x3, 0x2, 0x2, 0x2, 0xe3, 0xe0, 0x3, 0x2, 0x2, 0x2, 0xe3, 0xe1, 0x3, 
    0x2, 0x2, 0x2, 0xe3, 0xe2, 0x3, 0x2, 0x2, 0x2, 0xe4, 0xe7, 0x3, 0x2, 
    0x2, 0x2, 0xe5, 0xe3, 0x3, 0x2, 0x2, 0x2, 0xe5, 0xe6, 0x3, 0x2, 0x2, 
    0x2, 0xe6, 0xe8, 0x3, 0x2, 0x2, 0x2, 0xe7, 0xe5, 0x3, 0x2, 0x2, 0x2, 
    0xe8, 0xe9, 0x7, 0x5, 0x2, 0x2, 0xe9, 0x27, 0x3, 0x2, 0x2, 0x2, 0xea, 
    0xeb, 0x7, 0xf, 0x2, 0x2, 0xeb, 0xec, 0x7, 0x2d, 0x2, 0x2, 0xec, 0x29, 
    0x3, 0x2, 0x2, 0x2, 0xed, 0xee, 0x7, 0x10, 0x2, 0x2, 0xee, 0xef, 0x7, 
    0x2d, 0x2, 0x2, 0xef, 0x2b, 0x3, 0x2, 0x2, 0x2, 0xf0, 0xf1, 0x7, 0x11, 
    0x2, 0x2, 0xf1, 0xf8, 0x7, 0x2e, 0x2, 0x2, 0xf2, 0xf3, 0x7, 0x7, 0x2, 
    0x2, 0xf3, 0xf5, 0x7, 0x2e, 0x2, 0x2, 0xf4, 0xf2, 0x3, 0x2, 0x2, 0x2, 
    0xf5, 0xf6, 0x3, 0x2, 0x2, 0x2, 0xf6, 0xf4, 0x3, 0x2, 0x2, 0x2, 0xf6, 
    0xf7, 0x3, 0x2, 0x2, 0x2, 0xf7, 0xf9, 0x3, 0x2, 0x2, 0x2, 0xf8, 0xf4, 
    0x3, 0x2, 0x2, 0x2, 0xf8, 0xf9, 0x3, 0x2, 0x2, 0x2, 0xf9, 0x2d, 0x3, 
    0x2, 0x2, 0x2, 0xfa, 0xfb, 0x7, 0x12, 0x2, 0x2, 0xfb, 0xfc, 0x7, 0x2e, 
    0x2, 0x2, 0xfc, 0x2f, 0x3, 0x2, 0x2, 0x2, 0xfd, 0xfe, 0x7, 0x13, 0x2, 
    0x2, 0xfe, 0xff, 0x7, 0x2d, 0x2, 0x2, 0xff, 0x31, 0x3, 0x2, 0x2, 0x2, 
    0x100, 0x101, 0x7, 0x14, 0x2, 0x2, 0x101, 0x102, 0x7, 0x2e, 0x2, 0x2, 
    0x102, 0x33, 0x3, 0x2, 0x2, 0x2, 0x103, 0x104, 0x7, 0x15, 0x2, 0x2, 
    0x104, 0x105, 0x7, 0x30, 0x2, 0x2, 0x105, 0x35, 0x3, 0x2, 0x2, 0x2, 
    0x106, 0x107, 0x7, 0x16, 0x2, 0x2, 0x107, 0x37, 0x3, 0x2, 0x2, 0x2, 
    0x108, 0x109, 0x7, 0x17, 0x2, 0x2, 0x109, 0x10a, 0x7, 0x2d, 0x2, 0x2, 
    0x10a, 0x39, 0x3, 0x2, 0x2, 0x2, 0x10b, 0x10c, 0x7, 0x18, 0x2, 0x2, 
    0x10c, 0x10d, 0x7, 0x30, 0x2, 0x2, 0x10d, 0x3b, 0x3, 0x2, 0x2, 0x2, 
    0x10e, 0x10f, 0x7, 0x19, 0x2, 0x2, 0x10f, 0x110, 0x7, 0x2d, 0x2, 0x2, 
    0x110, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x111, 0x112, 0x7, 0x1a, 0x2, 0x2, 
    0x112, 0x116, 0x7, 0x4, 0x2, 0x2, 0x113, 0x115, 0x5, 0x40, 0x21, 0x2, 
    0x114, 0x113, 0x3, 0x2, 0x2, 0x2, 0x115, 0x118, 0x3, 0x2, 0x2, 0x2, 
    0x116, 0x114, 0x3, 0x2, 0x2, 0x2, 0x116, 0x117, 0x3, 0x2, 0x2, 0x2, 
    0x117, 0x119, 0x3, 0x2, 0x2, 0x2, 0x118, 0x116, 0x3, 0x2, 0x2, 0x2, 
    0x119, 0x11a, 0x7, 0x5, 0x2, 0x2, 0x11a, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x11b, 
    0x11c, 0x7, 0x2e, 0x2, 0x2, 0x11c, 0x11d, 0x7, 0x4, 0x2, 0x2, 0x11d, 
    0x121, 0x5, 0x42, 0x22, 0x2, 0x11e, 0x120, 0x5, 0x44, 0x23, 0x2, 0x11f, 
    0x11e, 0x3, 0x2, 0x2, 0x2, 0x120, 0x123, 0x3, 0x2, 0x2, 0x2, 0x121, 
    0x11f, 0x3, 0x2, 0x2, 0x2, 0x121, 0x122, 0x3, 0x2, 0x2, 0x2, 0x122, 
    0x124, 0x3, 0x2, 0x2, 0x2, 0x123, 0x121, 0x3, 0x2, 0x2, 0x2, 0x124, 
    0x125, 0x7, 0x5, 0x2, 0x2, 0x125, 0x41, 0x3, 0x2, 0x2, 0x2, 0x126, 0x127, 
    0x9, 0x6, 0x2, 0x2, 0x127, 0x12b, 0x7, 0x4, 0x2, 0x2, 0x128, 0x12a, 
    0x5, 0x1e, 0x10, 0x2, 0x129, 0x128, 0x3, 0x2, 0x2, 0x2, 0x12a, 0x12d, 
    0x3, 0x2, 0x2, 0x2, 0x12b, 0x129, 0x3, 0x2, 0x2, 0x2, 0x12b, 0x12c, 
    0x3, 0x2, 0x2, 0x2, 0x12c, 0x12e, 0x3, 0x2, 0x2, 0x2, 0x12d, 0x12b, 
    0x3, 0x2, 0x2, 0x2, 0x12e, 0x12f, 0x7, 0x5, 0x2, 0x2, 0x12f, 0x43, 0x3, 
    0x2, 0x2, 0x2, 0x130, 0x131, 0x7, 0x1f, 0x2, 0x2, 0x131, 0x133, 0x7, 
    0x4, 0x2, 0x2, 0x132, 0x134, 0x5, 0x24, 0x13, 0x2, 0x133, 0x132, 0x3, 
    0x2, 0x2, 0x2, 0x133, 0x134, 0x3, 0x2, 0x2, 0x2, 0x134, 0x135, 0x3, 
    0x2, 0x2, 0x2, 0x135, 0x136, 0x7, 0x5, 0x2, 0x2, 0x136, 0x45, 0x3, 0x2, 
    0x2, 0x2, 0x137, 0x138, 0x7, 0x20, 0x2, 0x2, 0x138, 0x13a, 0x7, 0x4, 
    0x2, 0x2, 0x139, 0x13b, 0x5, 0x48, 0x25, 0x2, 0x13a, 0x139, 0x3, 0x2, 
    0x2, 0x2, 0x13b, 0x13c, 0x3, 0x2, 0x2, 0x2, 0x13c, 0x13a, 0x3, 0x2, 
    0x2, 0x2, 0x13c, 0x13d, 0x3, 0x2, 0x2, 0x2, 0x13d, 0x13e, 0x3, 0x2, 
    0x2, 0x2, 0x13e, 0x13f, 0x7, 0x5, 0x2, 0x2, 0x13f, 0x47, 0x3, 0x2, 0x2, 
    0x2, 0x140, 0x141, 0x7, 0x2e, 0x2, 0x2, 0x141, 0x142, 0x7, 0x4, 0x2, 
    0x2, 0x142, 0x143, 0x5, 0x24, 0x13, 0x2, 0x143, 0x144, 0x7, 0x5, 0x2, 
    0x2, 0x144, 0x49, 0x3, 0x2, 0x2, 0x2, 0x145, 0x146, 0x7, 0x21, 0x2, 
    0x2, 0x146, 0x14a, 0x7, 0x4, 0x2, 0x2, 0x147, 0x149, 0x5, 0x4c, 0x27, 
    0x2, 0x148, 0x147, 0x3, 0x2, 0x2, 0x2, 0x149, 0x14c, 0x3, 0x2, 0x2, 
    0x2, 0x14a, 0x148, 0x3, 0x2, 0x2, 0x2, 0x14a, 0x14b, 0x3, 0x2, 0x2, 
    0x2, 0x14b, 0x14d, 0x3, 0x2, 0x2, 0x2, 0x14c, 0x14a, 0x3, 0x2, 0x2, 
    0x2, 0x14d, 0x14e, 0x7, 0x5, 0x2, 0x2, 0x14e, 0x4b, 0x3, 0x2, 0x2, 0x2, 
    0x14f, 0x150, 0x7, 0x2e, 0x2, 0x2, 0x150, 0x152, 0x7, 0x4, 0x2, 0x2, 
    0x151, 0x153, 0x5, 0x24, 0x13, 0x2, 0x152, 0x151, 0x3, 0x2, 0x2, 0x2, 
    0x152, 0x153, 0x3, 0x2, 0x2, 0x2, 0x153, 0x154, 0x3, 0x2, 0x2, 0x2, 
    0x154, 0x155, 0x7, 0x5, 0x2, 0x2, 0x155, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x1d, 
    0x57, 0x5b, 0x63, 0x65, 0x6c, 0x76, 0x78, 0x8a, 0x91, 0xa1, 0xa7, 0xad, 
    0xb4, 0xba, 0xd1, 0xd3, 0xe3, 0xe5, 0xf6, 0xf8, 0x116, 0x121, 0x12b, 
    0x133, 0x13c, 0x14a, 0x152, 
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