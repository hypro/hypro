
// Generated from CIFLocation.g4 by ANTLR 4.7


#include "CIFLocationVisitor.h"

#include "CIFLocationParser.h"


using namespace antlrcpp;
using namespace antlr4;

CIFLocationParser::CIFLocationParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

CIFLocationParser::~CIFLocationParser() {
  delete _interpreter;
}

std::string CIFLocationParser::getGrammarFileName() const {
  return "CIFLocation.g4";
}

const std::vector<std::string>& CIFLocationParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& CIFLocationParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- LocationsContext ------------------------------------------------------------------

CIFLocationParser::LocationsContext::LocationsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CIFLocationParser::LocationContext *> CIFLocationParser::LocationsContext::location() {
  return getRuleContexts<CIFLocationParser::LocationContext>();
}

CIFLocationParser::LocationContext* CIFLocationParser::LocationsContext::location(size_t i) {
  return getRuleContext<CIFLocationParser::LocationContext>(i);
}


size_t CIFLocationParser::LocationsContext::getRuleIndex() const {
  return CIFLocationParser::RuleLocations;
}

antlrcpp::Any CIFLocationParser::LocationsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitLocations(this);
  else
    return visitor->visitChildren(this);
}

CIFLocationParser::LocationsContext* CIFLocationParser::locations() {
  LocationsContext *_localctx = _tracker.createInstance<LocationsContext>(_ctx, getState());
  enterRule(_localctx, 0, CIFLocationParser::RuleLocations);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(103); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(102);
      location();
      setState(105); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == CIFLocationParser::T__0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LocationContext ------------------------------------------------------------------

CIFLocationParser::LocationContext::LocationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CIFLocationParser::LocationContext::getRuleIndex() const {
  return CIFLocationParser::RuleLocation;
}

void CIFLocationParser::LocationContext::copyFrom(LocationContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- LocElemContext ------------------------------------------------------------------

CIFLocationParser::LocationElementsContext* CIFLocationParser::LocElemContext::locationElements() {
  return getRuleContext<CIFLocationParser::LocationElementsContext>(0);
}

CIFLocationParser::LocElemContext::LocElemContext(LocationContext *ctx) { copyFrom(ctx); }

antlrcpp::Any CIFLocationParser::LocElemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitLocElem(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LocContext ------------------------------------------------------------------

CIFLocationParser::LocContext::LocContext(LocationContext *ctx) { copyFrom(ctx); }

antlrcpp::Any CIFLocationParser::LocContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitLoc(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LocIdElemContext ------------------------------------------------------------------

CIFLocationParser::IdentifierContext* CIFLocationParser::LocIdElemContext::identifier() {
  return getRuleContext<CIFLocationParser::IdentifierContext>(0);
}

CIFLocationParser::LocationElementsContext* CIFLocationParser::LocIdElemContext::locationElements() {
  return getRuleContext<CIFLocationParser::LocationElementsContext>(0);
}

CIFLocationParser::LocIdElemContext::LocIdElemContext(LocationContext *ctx) { copyFrom(ctx); }

antlrcpp::Any CIFLocationParser::LocIdElemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitLocIdElem(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LocIdContext ------------------------------------------------------------------

CIFLocationParser::IdentifierContext* CIFLocationParser::LocIdContext::identifier() {
  return getRuleContext<CIFLocationParser::IdentifierContext>(0);
}

CIFLocationParser::LocIdContext::LocIdContext(LocationContext *ctx) { copyFrom(ctx); }

antlrcpp::Any CIFLocationParser::LocIdContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitLocId(this);
  else
    return visitor->visitChildren(this);
}
CIFLocationParser::LocationContext* CIFLocationParser::location() {
  LocationContext *_localctx = _tracker.createInstance<LocationContext>(_ctx, getState());
  enterRule(_localctx, 2, CIFLocationParser::RuleLocation);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(121);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<LocationContext *>(_tracker.createInstance<CIFLocationParser::LocContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(107);
      match(CIFLocationParser::T__0);
      setState(108);
      match(CIFLocationParser::T__1);
      break;
    }

    case 2: {
      _localctx = dynamic_cast<LocationContext *>(_tracker.createInstance<CIFLocationParser::LocIdContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(109);
      match(CIFLocationParser::T__0);
      setState(110);
      identifier();
      setState(111);
      match(CIFLocationParser::T__1);
      break;
    }

    case 3: {
      _localctx = dynamic_cast<LocationContext *>(_tracker.createInstance<CIFLocationParser::LocElemContext>(_localctx));
      enterOuterAlt(_localctx, 3);
      setState(113);
      match(CIFLocationParser::T__0);
      setState(114);
      match(CIFLocationParser::T__2);
      setState(115);
      locationElements();
      break;
    }

    case 4: {
      _localctx = dynamic_cast<LocationContext *>(_tracker.createInstance<CIFLocationParser::LocIdElemContext>(_localctx));
      enterOuterAlt(_localctx, 4);
      setState(116);
      match(CIFLocationParser::T__0);
      setState(117);
      identifier();
      setState(118);
      match(CIFLocationParser::T__2);
      setState(119);
      locationElements();
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

//----------------- LocationElementsContext ------------------------------------------------------------------

CIFLocationParser::LocationElementsContext::LocationElementsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CIFLocationParser::LocationElementContext *> CIFLocationParser::LocationElementsContext::locationElement() {
  return getRuleContexts<CIFLocationParser::LocationElementContext>();
}

CIFLocationParser::LocationElementContext* CIFLocationParser::LocationElementsContext::locationElement(size_t i) {
  return getRuleContext<CIFLocationParser::LocationElementContext>(i);
}


size_t CIFLocationParser::LocationElementsContext::getRuleIndex() const {
  return CIFLocationParser::RuleLocationElements;
}

antlrcpp::Any CIFLocationParser::LocationElementsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitLocationElements(this);
  else
    return visitor->visitChildren(this);
}

CIFLocationParser::LocationElementsContext* CIFLocationParser::locationElements() {
  LocationElementsContext *_localctx = _tracker.createInstance<LocationElementsContext>(_ctx, getState());
  enterRule(_localctx, 4, CIFLocationParser::RuleLocationElements);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(124); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(123);
      locationElement();
      setState(126); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CIFLocationParser::T__3)
      | (1ULL << CIFLocationParser::T__4)
      | (1ULL << CIFLocationParser::T__5)
      | (1ULL << CIFLocationParser::T__6)
      | (1ULL << CIFLocationParser::T__7)
      | (1ULL << CIFLocationParser::T__16)
      | (1ULL << CIFLocationParser::T__59)
      | (1ULL << CIFLocationParser::T__60)
      | (1ULL << CIFLocationParser::T__61))) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LocationElementContext ------------------------------------------------------------------

CIFLocationParser::LocationElementContext::LocationElementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CIFLocationParser::LocationElementContext::getRuleIndex() const {
  return CIFLocationParser::RuleLocationElement;
}

void CIFLocationParser::LocationElementContext::copyFrom(LocationElementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- LocElemEdgeToContext ------------------------------------------------------------------

CIFLocationParser::CoreEdgeContext* CIFLocationParser::LocElemEdgeToContext::coreEdge() {
  return getRuleContext<CIFLocationParser::CoreEdgeContext>(0);
}

CIFLocationParser::IdentifierContext* CIFLocationParser::LocElemEdgeToContext::identifier() {
  return getRuleContext<CIFLocationParser::IdentifierContext>(0);
}

CIFLocationParser::LocElemEdgeToContext::LocElemEdgeToContext(LocationElementContext *ctx) { copyFrom(ctx); }

antlrcpp::Any CIFLocationParser::LocElemEdgeToContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitLocElemEdgeTo(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LocElemMarkedContext ------------------------------------------------------------------

CIFLocationParser::LocElemMarkedContext::LocElemMarkedContext(LocationElementContext *ctx) { copyFrom(ctx); }

antlrcpp::Any CIFLocationParser::LocElemMarkedContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitLocElemMarked(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LocElemInvContext ------------------------------------------------------------------

CIFLocationParser::InvariantDeclsContext* CIFLocationParser::LocElemInvContext::invariantDecls() {
  return getRuleContext<CIFLocationParser::InvariantDeclsContext>(0);
}

CIFLocationParser::LocElemInvContext::LocElemInvContext(LocationElementContext *ctx) { copyFrom(ctx); }

antlrcpp::Any CIFLocationParser::LocElemInvContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitLocElemInv(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LocElemMarkedExprContext ------------------------------------------------------------------

CIFLocationParser::ExpressionsContext* CIFLocationParser::LocElemMarkedExprContext::expressions() {
  return getRuleContext<CIFLocationParser::ExpressionsContext>(0);
}

CIFLocationParser::LocElemMarkedExprContext::LocElemMarkedExprContext(LocationElementContext *ctx) { copyFrom(ctx); }

antlrcpp::Any CIFLocationParser::LocElemMarkedExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitLocElemMarkedExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LocElemUrgentContext ------------------------------------------------------------------

CIFLocationParser::LocElemUrgentContext::LocElemUrgentContext(LocationElementContext *ctx) { copyFrom(ctx); }

antlrcpp::Any CIFLocationParser::LocElemUrgentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitLocElemUrgent(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LocElemLoopContext ------------------------------------------------------------------

CIFLocationParser::CoreEdgeContext* CIFLocationParser::LocElemLoopContext::coreEdge() {
  return getRuleContext<CIFLocationParser::CoreEdgeContext>(0);
}

CIFLocationParser::LocElemLoopContext::LocElemLoopContext(LocationElementContext *ctx) { copyFrom(ctx); }

antlrcpp::Any CIFLocationParser::LocElemLoopContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitLocElemLoop(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LocElemInitialFlagContext ------------------------------------------------------------------

CIFLocationParser::LocElemInitialFlagContext::LocElemInitialFlagContext(LocationElementContext *ctx) { copyFrom(ctx); }

antlrcpp::Any CIFLocationParser::LocElemInitialFlagContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitLocElemInitialFlag(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LocElemInitialFlagExprContext ------------------------------------------------------------------

CIFLocationParser::ExpressionsContext* CIFLocationParser::LocElemInitialFlagExprContext::expressions() {
  return getRuleContext<CIFLocationParser::ExpressionsContext>(0);
}

CIFLocationParser::LocElemInitialFlagExprContext::LocElemInitialFlagExprContext(LocationElementContext *ctx) { copyFrom(ctx); }

antlrcpp::Any CIFLocationParser::LocElemInitialFlagExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitLocElemInitialFlagExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LocElemEqsContext ------------------------------------------------------------------

CIFLocationParser::EquationsContext* CIFLocationParser::LocElemEqsContext::equations() {
  return getRuleContext<CIFLocationParser::EquationsContext>(0);
}

CIFLocationParser::LocElemEqsContext::LocElemEqsContext(LocationElementContext *ctx) { copyFrom(ctx); }

antlrcpp::Any CIFLocationParser::LocElemEqsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitLocElemEqs(this);
  else
    return visitor->visitChildren(this);
}
CIFLocationParser::LocationElementContext* CIFLocationParser::locationElement() {
  LocationElementContext *_localctx = _tracker.createInstance<LocationElementContext>(_ctx, getState());
  enterRule(_localctx, 6, CIFLocationParser::RuleLocationElement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(157);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<LocationElementContext *>(_tracker.createInstance<CIFLocationParser::LocElemInitialFlagContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(128);
      match(CIFLocationParser::T__3);
      setState(129);
      match(CIFLocationParser::T__1);
      break;
    }

    case 2: {
      _localctx = dynamic_cast<LocationElementContext *>(_tracker.createInstance<CIFLocationParser::LocElemInitialFlagExprContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(130);
      match(CIFLocationParser::T__3);
      setState(131);
      expressions();
      setState(132);
      match(CIFLocationParser::T__1);
      break;
    }

    case 3: {
      _localctx = dynamic_cast<LocationElementContext *>(_tracker.createInstance<CIFLocationParser::LocElemInvContext>(_localctx));
      enterOuterAlt(_localctx, 3);
      setState(134);
      invariantDecls();
      break;
    }

    case 4: {
      _localctx = dynamic_cast<LocationElementContext *>(_tracker.createInstance<CIFLocationParser::LocElemEqsContext>(_localctx));
      enterOuterAlt(_localctx, 4);
      setState(135);
      match(CIFLocationParser::T__4);
      setState(136);
      equations();
      setState(137);
      match(CIFLocationParser::T__1);
      break;
    }

    case 5: {
      _localctx = dynamic_cast<LocationElementContext *>(_tracker.createInstance<CIFLocationParser::LocElemMarkedContext>(_localctx));
      enterOuterAlt(_localctx, 5);
      setState(139);
      match(CIFLocationParser::T__5);
      setState(140);
      match(CIFLocationParser::T__1);
      break;
    }

    case 6: {
      _localctx = dynamic_cast<LocationElementContext *>(_tracker.createInstance<CIFLocationParser::LocElemMarkedExprContext>(_localctx));
      enterOuterAlt(_localctx, 6);
      setState(141);
      match(CIFLocationParser::T__5);
      setState(142);
      expressions();
      setState(143);
      match(CIFLocationParser::T__1);
      break;
    }

    case 7: {
      _localctx = dynamic_cast<LocationElementContext *>(_tracker.createInstance<CIFLocationParser::LocElemUrgentContext>(_localctx));
      enterOuterAlt(_localctx, 7);
      setState(145);
      match(CIFLocationParser::T__6);
      setState(146);
      match(CIFLocationParser::T__1);
      break;
    }

    case 8: {
      _localctx = dynamic_cast<LocationElementContext *>(_tracker.createInstance<CIFLocationParser::LocElemEdgeToContext>(_localctx));
      enterOuterAlt(_localctx, 8);
      setState(147);
      match(CIFLocationParser::T__7);
      setState(148);
      coreEdge();
      setState(149);
      match(CIFLocationParser::T__8);
      setState(150);
      identifier();
      setState(151);
      match(CIFLocationParser::T__1);
      break;
    }

    case 9: {
      _localctx = dynamic_cast<LocationElementContext *>(_tracker.createInstance<CIFLocationParser::LocElemLoopContext>(_localctx));
      enterOuterAlt(_localctx, 9);
      setState(153);
      match(CIFLocationParser::T__7);
      setState(154);
      coreEdge();
      setState(155);
      match(CIFLocationParser::T__1);
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

//----------------- CoreEdgeContext ------------------------------------------------------------------

CIFLocationParser::CoreEdgeContext::CoreEdgeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CIFLocationParser::EdgeEventsContext* CIFLocationParser::CoreEdgeContext::edgeEvents() {
  return getRuleContext<CIFLocationParser::EdgeEventsContext>(0);
}

CIFLocationParser::OptEdgeGuardContext* CIFLocationParser::CoreEdgeContext::optEdgeGuard() {
  return getRuleContext<CIFLocationParser::OptEdgeGuardContext>(0);
}

CIFLocationParser::OptEdgeUrgentContext* CIFLocationParser::CoreEdgeContext::optEdgeUrgent() {
  return getRuleContext<CIFLocationParser::OptEdgeUrgentContext>(0);
}

CIFLocationParser::OptEdgeUpdateContext* CIFLocationParser::CoreEdgeContext::optEdgeUpdate() {
  return getRuleContext<CIFLocationParser::OptEdgeUpdateContext>(0);
}

CIFLocationParser::ExpressionsContext* CIFLocationParser::CoreEdgeContext::expressions() {
  return getRuleContext<CIFLocationParser::ExpressionsContext>(0);
}

CIFLocationParser::UpdatesContext* CIFLocationParser::CoreEdgeContext::updates() {
  return getRuleContext<CIFLocationParser::UpdatesContext>(0);
}


size_t CIFLocationParser::CoreEdgeContext::getRuleIndex() const {
  return CIFLocationParser::RuleCoreEdge;
}

antlrcpp::Any CIFLocationParser::CoreEdgeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitCoreEdge(this);
  else
    return visitor->visitChildren(this);
}

CIFLocationParser::CoreEdgeContext* CIFLocationParser::coreEdge() {
  CoreEdgeContext *_localctx = _tracker.createInstance<CoreEdgeContext>(_ctx, getState());
  enterRule(_localctx, 8, CIFLocationParser::RuleCoreEdge);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(173);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CIFLocationParser::T__13:
      case CIFLocationParser::IDENTIFIER:
      case CIFLocationParser::RELATIVENAME:
      case CIFLocationParser::ABSOLUTENAME:
      case CIFLocationParser::ROOTNAME: {
        enterOuterAlt(_localctx, 1);
        setState(159);
        edgeEvents();
        setState(160);
        optEdgeGuard();
        setState(161);
        optEdgeUrgent();
        setState(162);
        optEdgeUpdate();
        break;
      }

      case CIFLocationParser::T__9: {
        enterOuterAlt(_localctx, 2);
        setState(164);
        match(CIFLocationParser::T__9);
        setState(165);
        expressions();
        setState(166);
        optEdgeUrgent();
        setState(167);
        optEdgeUpdate();
        break;
      }

      case CIFLocationParser::T__10: {
        enterOuterAlt(_localctx, 3);
        setState(169);
        match(CIFLocationParser::T__10);
        setState(170);
        optEdgeUpdate();
        break;
      }

      case CIFLocationParser::T__11: {
        enterOuterAlt(_localctx, 4);
        setState(171);
        match(CIFLocationParser::T__11);
        setState(172);
        updates();
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

//----------------- OptEdgeGuardContext ------------------------------------------------------------------

CIFLocationParser::OptEdgeGuardContext::OptEdgeGuardContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CIFLocationParser::ExpressionsContext* CIFLocationParser::OptEdgeGuardContext::expressions() {
  return getRuleContext<CIFLocationParser::ExpressionsContext>(0);
}


size_t CIFLocationParser::OptEdgeGuardContext::getRuleIndex() const {
  return CIFLocationParser::RuleOptEdgeGuard;
}

antlrcpp::Any CIFLocationParser::OptEdgeGuardContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitOptEdgeGuard(this);
  else
    return visitor->visitChildren(this);
}

CIFLocationParser::OptEdgeGuardContext* CIFLocationParser::optEdgeGuard() {
  OptEdgeGuardContext *_localctx = _tracker.createInstance<OptEdgeGuardContext>(_ctx, getState());
  enterRule(_localctx, 10, CIFLocationParser::RuleOptEdgeGuard);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(177);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CIFLocationParser::T__9) {
      setState(175);
      match(CIFLocationParser::T__9);
      setState(176);
      expressions();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OptEdgeUrgentContext ------------------------------------------------------------------

CIFLocationParser::OptEdgeUrgentContext::OptEdgeUrgentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CIFLocationParser::OptEdgeUrgentContext::getRuleIndex() const {
  return CIFLocationParser::RuleOptEdgeUrgent;
}

antlrcpp::Any CIFLocationParser::OptEdgeUrgentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitOptEdgeUrgent(this);
  else
    return visitor->visitChildren(this);
}

CIFLocationParser::OptEdgeUrgentContext* CIFLocationParser::optEdgeUrgent() {
  OptEdgeUrgentContext *_localctx = _tracker.createInstance<OptEdgeUrgentContext>(_ctx, getState());
  enterRule(_localctx, 12, CIFLocationParser::RuleOptEdgeUrgent);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(180);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CIFLocationParser::T__10) {
      setState(179);
      match(CIFLocationParser::T__10);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OptEdgeUpdateContext ------------------------------------------------------------------

CIFLocationParser::OptEdgeUpdateContext::OptEdgeUpdateContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CIFLocationParser::UpdatesContext* CIFLocationParser::OptEdgeUpdateContext::updates() {
  return getRuleContext<CIFLocationParser::UpdatesContext>(0);
}


size_t CIFLocationParser::OptEdgeUpdateContext::getRuleIndex() const {
  return CIFLocationParser::RuleOptEdgeUpdate;
}

antlrcpp::Any CIFLocationParser::OptEdgeUpdateContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitOptEdgeUpdate(this);
  else
    return visitor->visitChildren(this);
}

CIFLocationParser::OptEdgeUpdateContext* CIFLocationParser::optEdgeUpdate() {
  OptEdgeUpdateContext *_localctx = _tracker.createInstance<OptEdgeUpdateContext>(_ctx, getState());
  enterRule(_localctx, 14, CIFLocationParser::RuleOptEdgeUpdate);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(184);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CIFLocationParser::T__11) {
      setState(182);
      match(CIFLocationParser::T__11);
      setState(183);
      updates();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EdgeEventsContext ------------------------------------------------------------------

CIFLocationParser::EdgeEventsContext::EdgeEventsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CIFLocationParser::EdgeEventContext *> CIFLocationParser::EdgeEventsContext::edgeEvent() {
  return getRuleContexts<CIFLocationParser::EdgeEventContext>();
}

CIFLocationParser::EdgeEventContext* CIFLocationParser::EdgeEventsContext::edgeEvent(size_t i) {
  return getRuleContext<CIFLocationParser::EdgeEventContext>(i);
}


size_t CIFLocationParser::EdgeEventsContext::getRuleIndex() const {
  return CIFLocationParser::RuleEdgeEvents;
}

antlrcpp::Any CIFLocationParser::EdgeEventsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitEdgeEvents(this);
  else
    return visitor->visitChildren(this);
}

CIFLocationParser::EdgeEventsContext* CIFLocationParser::edgeEvents() {
  EdgeEventsContext *_localctx = _tracker.createInstance<EdgeEventsContext>(_ctx, getState());
  enterRule(_localctx, 16, CIFLocationParser::RuleEdgeEvents);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(186);
    edgeEvent();
    setState(191);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CIFLocationParser::T__12) {
      setState(187);
      match(CIFLocationParser::T__12);
      setState(188);
      edgeEvent();
      setState(193);
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

//----------------- EdgeEventContext ------------------------------------------------------------------

CIFLocationParser::EdgeEventContext::EdgeEventContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CIFLocationParser::NameContext* CIFLocationParser::EdgeEventContext::name() {
  return getRuleContext<CIFLocationParser::NameContext>(0);
}

CIFLocationParser::ExpressionContext* CIFLocationParser::EdgeEventContext::expression() {
  return getRuleContext<CIFLocationParser::ExpressionContext>(0);
}


size_t CIFLocationParser::EdgeEventContext::getRuleIndex() const {
  return CIFLocationParser::RuleEdgeEvent;
}

antlrcpp::Any CIFLocationParser::EdgeEventContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitEdgeEvent(this);
  else
    return visitor->visitChildren(this);
}

CIFLocationParser::EdgeEventContext* CIFLocationParser::edgeEvent() {
  EdgeEventContext *_localctx = _tracker.createInstance<EdgeEventContext>(_ctx, getState());
  enterRule(_localctx, 18, CIFLocationParser::RuleEdgeEvent);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(206);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(194);
      match(CIFLocationParser::T__13);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(195);
      name();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(196);
      name();
      setState(197);
      match(CIFLocationParser::T__14);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(199);
      name();
      setState(200);
      match(CIFLocationParser::T__14);
      setState(201);
      expression();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(203);
      name();
      setState(204);
      match(CIFLocationParser::T__15);
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

//----------------- InvariantDeclsContext ------------------------------------------------------------------

CIFLocationParser::InvariantDeclsContext::InvariantDeclsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CIFLocationParser::OptSupKindContext* CIFLocationParser::InvariantDeclsContext::optSupKind() {
  return getRuleContext<CIFLocationParser::OptSupKindContext>(0);
}

CIFLocationParser::InvariantsContext* CIFLocationParser::InvariantDeclsContext::invariants() {
  return getRuleContext<CIFLocationParser::InvariantsContext>(0);
}

CIFLocationParser::SupKindContext* CIFLocationParser::InvariantDeclsContext::supKind() {
  return getRuleContext<CIFLocationParser::SupKindContext>(0);
}


size_t CIFLocationParser::InvariantDeclsContext::getRuleIndex() const {
  return CIFLocationParser::RuleInvariantDecls;
}

antlrcpp::Any CIFLocationParser::InvariantDeclsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitInvariantDecls(this);
  else
    return visitor->visitChildren(this);
}

CIFLocationParser::InvariantDeclsContext* CIFLocationParser::invariantDecls() {
  InvariantDeclsContext *_localctx = _tracker.createInstance<InvariantDeclsContext>(_ctx, getState());
  enterRule(_localctx, 20, CIFLocationParser::RuleInvariantDecls);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(217);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(208);
      optSupKind();
      setState(209);
      match(CIFLocationParser::T__16);
      setState(210);
      invariants();
      setState(211);
      match(CIFLocationParser::T__1);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(213);
      supKind();
      setState(214);
      invariants();
      setState(215);
      match(CIFLocationParser::T__1);
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

//----------------- InvariantsContext ------------------------------------------------------------------

CIFLocationParser::InvariantsContext::InvariantsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CIFLocationParser::InvariantContext *> CIFLocationParser::InvariantsContext::invariant() {
  return getRuleContexts<CIFLocationParser::InvariantContext>();
}

CIFLocationParser::InvariantContext* CIFLocationParser::InvariantsContext::invariant(size_t i) {
  return getRuleContext<CIFLocationParser::InvariantContext>(i);
}


size_t CIFLocationParser::InvariantsContext::getRuleIndex() const {
  return CIFLocationParser::RuleInvariants;
}

antlrcpp::Any CIFLocationParser::InvariantsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitInvariants(this);
  else
    return visitor->visitChildren(this);
}

CIFLocationParser::InvariantsContext* CIFLocationParser::invariants() {
  InvariantsContext *_localctx = _tracker.createInstance<InvariantsContext>(_ctx, getState());
  enterRule(_localctx, 22, CIFLocationParser::RuleInvariants);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(219);
    invariant();
    setState(224);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CIFLocationParser::T__12) {
      setState(220);
      match(CIFLocationParser::T__12);
      setState(221);
      invariant();
      setState(226);
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

//----------------- InvariantContext ------------------------------------------------------------------

CIFLocationParser::InvariantContext::InvariantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CIFLocationParser::InvariantContext::getRuleIndex() const {
  return CIFLocationParser::RuleInvariant;
}

void CIFLocationParser::InvariantContext::copyFrom(InvariantContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- InvNeedsContext ------------------------------------------------------------------

CIFLocationParser::NameContext* CIFLocationParser::InvNeedsContext::name() {
  return getRuleContext<CIFLocationParser::NameContext>(0);
}

CIFLocationParser::ExpressionContext* CIFLocationParser::InvNeedsContext::expression() {
  return getRuleContext<CIFLocationParser::ExpressionContext>(0);
}

CIFLocationParser::InvNeedsContext::InvNeedsContext(InvariantContext *ctx) { copyFrom(ctx); }

antlrcpp::Any CIFLocationParser::InvNeedsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitInvNeeds(this);
  else
    return visitor->visitChildren(this);
}
//----------------- InvExprContext ------------------------------------------------------------------

CIFLocationParser::ExpressionContext* CIFLocationParser::InvExprContext::expression() {
  return getRuleContext<CIFLocationParser::ExpressionContext>(0);
}

CIFLocationParser::InvExprContext::InvExprContext(InvariantContext *ctx) { copyFrom(ctx); }

antlrcpp::Any CIFLocationParser::InvExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitInvExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- InvDisablesContext ------------------------------------------------------------------

CIFLocationParser::ExpressionContext* CIFLocationParser::InvDisablesContext::expression() {
  return getRuleContext<CIFLocationParser::ExpressionContext>(0);
}

CIFLocationParser::NameContext* CIFLocationParser::InvDisablesContext::name() {
  return getRuleContext<CIFLocationParser::NameContext>(0);
}

CIFLocationParser::InvDisablesContext::InvDisablesContext(InvariantContext *ctx) { copyFrom(ctx); }

antlrcpp::Any CIFLocationParser::InvDisablesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitInvDisables(this);
  else
    return visitor->visitChildren(this);
}
//----------------- InvNeedsSetContext ------------------------------------------------------------------

CIFLocationParser::NonEmptySetExpressionContext* CIFLocationParser::InvNeedsSetContext::nonEmptySetExpression() {
  return getRuleContext<CIFLocationParser::NonEmptySetExpressionContext>(0);
}

CIFLocationParser::ExpressionContext* CIFLocationParser::InvNeedsSetContext::expression() {
  return getRuleContext<CIFLocationParser::ExpressionContext>(0);
}

CIFLocationParser::InvNeedsSetContext::InvNeedsSetContext(InvariantContext *ctx) { copyFrom(ctx); }

antlrcpp::Any CIFLocationParser::InvNeedsSetContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitInvNeedsSet(this);
  else
    return visitor->visitChildren(this);
}
//----------------- InvDisablesSetContext ------------------------------------------------------------------

CIFLocationParser::ExpressionContext* CIFLocationParser::InvDisablesSetContext::expression() {
  return getRuleContext<CIFLocationParser::ExpressionContext>(0);
}

CIFLocationParser::NameSetContext* CIFLocationParser::InvDisablesSetContext::nameSet() {
  return getRuleContext<CIFLocationParser::NameSetContext>(0);
}

CIFLocationParser::InvDisablesSetContext::InvDisablesSetContext(InvariantContext *ctx) { copyFrom(ctx); }

antlrcpp::Any CIFLocationParser::InvDisablesSetContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitInvDisablesSet(this);
  else
    return visitor->visitChildren(this);
}
CIFLocationParser::InvariantContext* CIFLocationParser::invariant() {
  InvariantContext *_localctx = _tracker.createInstance<InvariantContext>(_ctx, getState());
  enterRule(_localctx, 24, CIFLocationParser::RuleInvariant);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(244);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<InvariantContext *>(_tracker.createInstance<CIFLocationParser::InvExprContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(227);
      expression();
      break;
    }

    case 2: {
      _localctx = dynamic_cast<InvariantContext *>(_tracker.createInstance<CIFLocationParser::InvNeedsContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(228);
      name();
      setState(229);
      match(CIFLocationParser::T__17);
      setState(230);
      expression();
      break;
    }

    case 3: {
      _localctx = dynamic_cast<InvariantContext *>(_tracker.createInstance<CIFLocationParser::InvNeedsSetContext>(_localctx));
      enterOuterAlt(_localctx, 3);
      setState(232);
      nonEmptySetExpression();
      setState(233);
      match(CIFLocationParser::T__17);
      setState(234);
      expression();
      break;
    }

    case 4: {
      _localctx = dynamic_cast<InvariantContext *>(_tracker.createInstance<CIFLocationParser::InvDisablesContext>(_localctx));
      enterOuterAlt(_localctx, 4);
      setState(236);
      expression();
      setState(237);
      match(CIFLocationParser::T__18);
      setState(238);
      name();
      break;
    }

    case 5: {
      _localctx = dynamic_cast<InvariantContext *>(_tracker.createInstance<CIFLocationParser::InvDisablesSetContext>(_localctx));
      enterOuterAlt(_localctx, 5);
      setState(240);
      expression();
      setState(241);
      match(CIFLocationParser::T__18);
      setState(242);
      nameSet();
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

//----------------- UpdatesContext ------------------------------------------------------------------

CIFLocationParser::UpdatesContext::UpdatesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CIFLocationParser::UpdateContext *> CIFLocationParser::UpdatesContext::update() {
  return getRuleContexts<CIFLocationParser::UpdateContext>();
}

CIFLocationParser::UpdateContext* CIFLocationParser::UpdatesContext::update(size_t i) {
  return getRuleContext<CIFLocationParser::UpdateContext>(i);
}


size_t CIFLocationParser::UpdatesContext::getRuleIndex() const {
  return CIFLocationParser::RuleUpdates;
}

antlrcpp::Any CIFLocationParser::UpdatesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitUpdates(this);
  else
    return visitor->visitChildren(this);
}

CIFLocationParser::UpdatesContext* CIFLocationParser::updates() {
  UpdatesContext *_localctx = _tracker.createInstance<UpdatesContext>(_ctx, getState());
  enterRule(_localctx, 26, CIFLocationParser::RuleUpdates);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(246);
    update();
    setState(251);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CIFLocationParser::T__12) {
      setState(247);
      match(CIFLocationParser::T__12);
      setState(248);
      update();
      setState(253);
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

//----------------- UpdateContext ------------------------------------------------------------------

CIFLocationParser::UpdateContext::UpdateContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CIFLocationParser::UpdateContext::getRuleIndex() const {
  return CIFLocationParser::RuleUpdate;
}

void CIFLocationParser::UpdateContext::copyFrom(UpdateContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- UpdateNonIfContext ------------------------------------------------------------------

CIFLocationParser::AdressableContext* CIFLocationParser::UpdateNonIfContext::adressable() {
  return getRuleContext<CIFLocationParser::AdressableContext>(0);
}

CIFLocationParser::ExpressionContext* CIFLocationParser::UpdateNonIfContext::expression() {
  return getRuleContext<CIFLocationParser::ExpressionContext>(0);
}

CIFLocationParser::UpdateNonIfContext::UpdateNonIfContext(UpdateContext *ctx) { copyFrom(ctx); }

antlrcpp::Any CIFLocationParser::UpdateNonIfContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitUpdateNonIf(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UpdateIfContext ------------------------------------------------------------------

CIFLocationParser::ExpressionsContext* CIFLocationParser::UpdateIfContext::expressions() {
  return getRuleContext<CIFLocationParser::ExpressionsContext>(0);
}

CIFLocationParser::UpdatesContext* CIFLocationParser::UpdateIfContext::updates() {
  return getRuleContext<CIFLocationParser::UpdatesContext>(0);
}

CIFLocationParser::OptElifUpdatesContext* CIFLocationParser::UpdateIfContext::optElifUpdates() {
  return getRuleContext<CIFLocationParser::OptElifUpdatesContext>(0);
}

CIFLocationParser::OptElseUpdateContext* CIFLocationParser::UpdateIfContext::optElseUpdate() {
  return getRuleContext<CIFLocationParser::OptElseUpdateContext>(0);
}

CIFLocationParser::UpdateIfContext::UpdateIfContext(UpdateContext *ctx) { copyFrom(ctx); }

antlrcpp::Any CIFLocationParser::UpdateIfContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitUpdateIf(this);
  else
    return visitor->visitChildren(this);
}
CIFLocationParser::UpdateContext* CIFLocationParser::update() {
  UpdateContext *_localctx = _tracker.createInstance<UpdateContext>(_ctx, getState());
  enterRule(_localctx, 28, CIFLocationParser::RuleUpdate);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(266);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CIFLocationParser::T__24:
      case CIFLocationParser::IDENTIFIER: {
        _localctx = dynamic_cast<UpdateContext *>(_tracker.createInstance<CIFLocationParser::UpdateNonIfContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(254);
        adressable();
        setState(255);
        match(CIFLocationParser::T__19);
        setState(256);
        expression();
        break;
      }

      case CIFLocationParser::T__20: {
        _localctx = dynamic_cast<UpdateContext *>(_tracker.createInstance<CIFLocationParser::UpdateIfContext>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(258);
        match(CIFLocationParser::T__20);
        setState(259);
        expressions();
        setState(260);
        match(CIFLocationParser::T__2);
        setState(261);
        updates();
        setState(262);
        optElifUpdates();
        setState(263);
        optElseUpdate();
        setState(264);
        match(CIFLocationParser::T__21);
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

//----------------- OptElifUpdatesContext ------------------------------------------------------------------

CIFLocationParser::OptElifUpdatesContext::OptElifUpdatesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CIFLocationParser::ExpressionsContext *> CIFLocationParser::OptElifUpdatesContext::expressions() {
  return getRuleContexts<CIFLocationParser::ExpressionsContext>();
}

CIFLocationParser::ExpressionsContext* CIFLocationParser::OptElifUpdatesContext::expressions(size_t i) {
  return getRuleContext<CIFLocationParser::ExpressionsContext>(i);
}

std::vector<CIFLocationParser::UpdatesContext *> CIFLocationParser::OptElifUpdatesContext::updates() {
  return getRuleContexts<CIFLocationParser::UpdatesContext>();
}

CIFLocationParser::UpdatesContext* CIFLocationParser::OptElifUpdatesContext::updates(size_t i) {
  return getRuleContext<CIFLocationParser::UpdatesContext>(i);
}


size_t CIFLocationParser::OptElifUpdatesContext::getRuleIndex() const {
  return CIFLocationParser::RuleOptElifUpdates;
}

antlrcpp::Any CIFLocationParser::OptElifUpdatesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitOptElifUpdates(this);
  else
    return visitor->visitChildren(this);
}

CIFLocationParser::OptElifUpdatesContext* CIFLocationParser::optElifUpdates() {
  OptElifUpdatesContext *_localctx = _tracker.createInstance<OptElifUpdatesContext>(_ctx, getState());
  enterRule(_localctx, 30, CIFLocationParser::RuleOptElifUpdates);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(275);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CIFLocationParser::T__22) {
      setState(268);
      match(CIFLocationParser::T__22);
      setState(269);
      expressions();
      setState(270);
      match(CIFLocationParser::T__2);
      setState(271);
      updates();
      setState(277);
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

//----------------- OptElseUpdateContext ------------------------------------------------------------------

CIFLocationParser::OptElseUpdateContext::OptElseUpdateContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CIFLocationParser::UpdateContext* CIFLocationParser::OptElseUpdateContext::update() {
  return getRuleContext<CIFLocationParser::UpdateContext>(0);
}


size_t CIFLocationParser::OptElseUpdateContext::getRuleIndex() const {
  return CIFLocationParser::RuleOptElseUpdate;
}

antlrcpp::Any CIFLocationParser::OptElseUpdateContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitOptElseUpdate(this);
  else
    return visitor->visitChildren(this);
}

CIFLocationParser::OptElseUpdateContext* CIFLocationParser::optElseUpdate() {
  OptElseUpdateContext *_localctx = _tracker.createInstance<OptElseUpdateContext>(_ctx, getState());
  enterRule(_localctx, 32, CIFLocationParser::RuleOptElseUpdate);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(280);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CIFLocationParser::T__23) {
      setState(278);
      match(CIFLocationParser::T__23);
      setState(279);
      update();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AdressablesContext ------------------------------------------------------------------

CIFLocationParser::AdressablesContext::AdressablesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CIFLocationParser::AdressableContext *> CIFLocationParser::AdressablesContext::adressable() {
  return getRuleContexts<CIFLocationParser::AdressableContext>();
}

CIFLocationParser::AdressableContext* CIFLocationParser::AdressablesContext::adressable(size_t i) {
  return getRuleContext<CIFLocationParser::AdressableContext>(i);
}


size_t CIFLocationParser::AdressablesContext::getRuleIndex() const {
  return CIFLocationParser::RuleAdressables;
}

antlrcpp::Any CIFLocationParser::AdressablesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitAdressables(this);
  else
    return visitor->visitChildren(this);
}

CIFLocationParser::AdressablesContext* CIFLocationParser::adressables() {
  AdressablesContext *_localctx = _tracker.createInstance<AdressablesContext>(_ctx, getState());
  enterRule(_localctx, 34, CIFLocationParser::RuleAdressables);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(282);
    adressable();
    setState(287);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CIFLocationParser::T__12) {
      setState(283);
      match(CIFLocationParser::T__12);
      setState(284);
      adressable();
      setState(289);
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

//----------------- AdressableContext ------------------------------------------------------------------

CIFLocationParser::AdressableContext::AdressableContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CIFLocationParser::AdressableContext::getRuleIndex() const {
  return CIFLocationParser::RuleAdressable;
}

void CIFLocationParser::AdressableContext::copyFrom(AdressableContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- AdressableIdContext ------------------------------------------------------------------

CIFLocationParser::IdentifierContext* CIFLocationParser::AdressableIdContext::identifier() {
  return getRuleContext<CIFLocationParser::IdentifierContext>(0);
}

CIFLocationParser::AdressableIdContext::AdressableIdContext(AdressableContext *ctx) { copyFrom(ctx); }

antlrcpp::Any CIFLocationParser::AdressableIdContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitAdressableId(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AdressableProjContext ------------------------------------------------------------------

CIFLocationParser::IdentifierContext* CIFLocationParser::AdressableProjContext::identifier() {
  return getRuleContext<CIFLocationParser::IdentifierContext>(0);
}

CIFLocationParser::ProjectionsContext* CIFLocationParser::AdressableProjContext::projections() {
  return getRuleContext<CIFLocationParser::ProjectionsContext>(0);
}

CIFLocationParser::AdressableProjContext::AdressableProjContext(AdressableContext *ctx) { copyFrom(ctx); }

antlrcpp::Any CIFLocationParser::AdressableProjContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitAdressableProj(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AdressablePairContext ------------------------------------------------------------------

std::vector<CIFLocationParser::AdressableContext *> CIFLocationParser::AdressablePairContext::adressable() {
  return getRuleContexts<CIFLocationParser::AdressableContext>();
}

CIFLocationParser::AdressableContext* CIFLocationParser::AdressablePairContext::adressable(size_t i) {
  return getRuleContext<CIFLocationParser::AdressableContext>(i);
}

CIFLocationParser::AdressablePairContext::AdressablePairContext(AdressableContext *ctx) { copyFrom(ctx); }

antlrcpp::Any CIFLocationParser::AdressablePairContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitAdressablePair(this);
  else
    return visitor->visitChildren(this);
}
CIFLocationParser::AdressableContext* CIFLocationParser::adressable() {
  AdressableContext *_localctx = _tracker.createInstance<AdressableContext>(_ctx, getState());
  enterRule(_localctx, 36, CIFLocationParser::RuleAdressable);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(300);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<AdressableContext *>(_tracker.createInstance<CIFLocationParser::AdressableIdContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(290);
      identifier();
      break;
    }

    case 2: {
      _localctx = dynamic_cast<AdressableContext *>(_tracker.createInstance<CIFLocationParser::AdressableProjContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(291);
      identifier();
      setState(292);
      projections();
      break;
    }

    case 3: {
      _localctx = dynamic_cast<AdressableContext *>(_tracker.createInstance<CIFLocationParser::AdressablePairContext>(_localctx));
      enterOuterAlt(_localctx, 3);
      setState(294);
      match(CIFLocationParser::T__24);
      setState(295);
      adressable();
      setState(296);
      match(CIFLocationParser::T__12);
      setState(297);
      adressable();
      setState(298);
      match(CIFLocationParser::T__25);
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

//----------------- ProjectionsContext ------------------------------------------------------------------

CIFLocationParser::ProjectionsContext::ProjectionsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CIFLocationParser::ProjectionContext *> CIFLocationParser::ProjectionsContext::projection() {
  return getRuleContexts<CIFLocationParser::ProjectionContext>();
}

CIFLocationParser::ProjectionContext* CIFLocationParser::ProjectionsContext::projection(size_t i) {
  return getRuleContext<CIFLocationParser::ProjectionContext>(i);
}


size_t CIFLocationParser::ProjectionsContext::getRuleIndex() const {
  return CIFLocationParser::RuleProjections;
}

antlrcpp::Any CIFLocationParser::ProjectionsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitProjections(this);
  else
    return visitor->visitChildren(this);
}

CIFLocationParser::ProjectionsContext* CIFLocationParser::projections() {
  ProjectionsContext *_localctx = _tracker.createInstance<ProjectionsContext>(_ctx, getState());
  enterRule(_localctx, 38, CIFLocationParser::RuleProjections);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(305);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CIFLocationParser::T__26) {
      setState(302);
      projection();
      setState(307);
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

//----------------- ProjectionContext ------------------------------------------------------------------

CIFLocationParser::ProjectionContext::ProjectionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CIFLocationParser::ExpressionContext* CIFLocationParser::ProjectionContext::expression() {
  return getRuleContext<CIFLocationParser::ExpressionContext>(0);
}


size_t CIFLocationParser::ProjectionContext::getRuleIndex() const {
  return CIFLocationParser::RuleProjection;
}

antlrcpp::Any CIFLocationParser::ProjectionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitProjection(this);
  else
    return visitor->visitChildren(this);
}

CIFLocationParser::ProjectionContext* CIFLocationParser::projection() {
  ProjectionContext *_localctx = _tracker.createInstance<ProjectionContext>(_ctx, getState());
  enterRule(_localctx, 40, CIFLocationParser::RuleProjection);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(308);
    match(CIFLocationParser::T__26);
    setState(309);
    expression();
    setState(310);
    match(CIFLocationParser::T__27);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionsContext ------------------------------------------------------------------

CIFLocationParser::ExpressionsContext::ExpressionsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CIFLocationParser::ExpressionContext *> CIFLocationParser::ExpressionsContext::expression() {
  return getRuleContexts<CIFLocationParser::ExpressionContext>();
}

CIFLocationParser::ExpressionContext* CIFLocationParser::ExpressionsContext::expression(size_t i) {
  return getRuleContext<CIFLocationParser::ExpressionContext>(i);
}


size_t CIFLocationParser::ExpressionsContext::getRuleIndex() const {
  return CIFLocationParser::RuleExpressions;
}

antlrcpp::Any CIFLocationParser::ExpressionsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitExpressions(this);
  else
    return visitor->visitChildren(this);
}

CIFLocationParser::ExpressionsContext* CIFLocationParser::expressions() {
  ExpressionsContext *_localctx = _tracker.createInstance<ExpressionsContext>(_ctx, getState());
  enterRule(_localctx, 42, CIFLocationParser::RuleExpressions);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(312);
    expression();
    setState(317);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CIFLocationParser::T__12) {
      setState(313);
      match(CIFLocationParser::T__12);
      setState(314);
      expression();
      setState(319);
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

//----------------- OptExpressionContext ------------------------------------------------------------------

CIFLocationParser::OptExpressionContext::OptExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CIFLocationParser::ExpressionContext* CIFLocationParser::OptExpressionContext::expression() {
  return getRuleContext<CIFLocationParser::ExpressionContext>(0);
}


size_t CIFLocationParser::OptExpressionContext::getRuleIndex() const {
  return CIFLocationParser::RuleOptExpression;
}

antlrcpp::Any CIFLocationParser::OptExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitOptExpression(this);
  else
    return visitor->visitChildren(this);
}

CIFLocationParser::OptExpressionContext* CIFLocationParser::optExpression() {
  OptExpressionContext *_localctx = _tracker.createInstance<OptExpressionContext>(_ctx, getState());
  enterRule(_localctx, 44, CIFLocationParser::RuleOptExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(321);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CIFLocationParser::T__15)
      | (1ULL << CIFLocationParser::T__20)
      | (1ULL << CIFLocationParser::T__24)
      | (1ULL << CIFLocationParser::T__26)
      | (1ULL << CIFLocationParser::T__34)
      | (1ULL << CIFLocationParser::T__35)
      | (1ULL << CIFLocationParser::T__36)
      | (1ULL << CIFLocationParser::T__37)
      | (1ULL << CIFLocationParser::T__38)
      | (1ULL << CIFLocationParser::T__39)
      | (1ULL << CIFLocationParser::T__40)
      | (1ULL << CIFLocationParser::T__41)
      | (1ULL << CIFLocationParser::T__43)
      | (1ULL << CIFLocationParser::T__45)
      | (1ULL << CIFLocationParser::T__46)
      | (1ULL << CIFLocationParser::T__62))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (CIFLocationParser::T__63 - 64))
      | (1ULL << (CIFLocationParser::T__64 - 64))
      | (1ULL << (CIFLocationParser::T__65 - 64))
      | (1ULL << (CIFLocationParser::T__66 - 64))
      | (1ULL << (CIFLocationParser::T__67 - 64))
      | (1ULL << (CIFLocationParser::T__68 - 64))
      | (1ULL << (CIFLocationParser::T__69 - 64))
      | (1ULL << (CIFLocationParser::T__70 - 64))
      | (1ULL << (CIFLocationParser::T__71 - 64))
      | (1ULL << (CIFLocationParser::T__72 - 64))
      | (1ULL << (CIFLocationParser::T__73 - 64))
      | (1ULL << (CIFLocationParser::T__74 - 64))
      | (1ULL << (CIFLocationParser::T__75 - 64))
      | (1ULL << (CIFLocationParser::T__76 - 64))
      | (1ULL << (CIFLocationParser::T__77 - 64))
      | (1ULL << (CIFLocationParser::T__78 - 64))
      | (1ULL << (CIFLocationParser::T__79 - 64))
      | (1ULL << (CIFLocationParser::T__80 - 64))
      | (1ULL << (CIFLocationParser::T__81 - 64))
      | (1ULL << (CIFLocationParser::T__82 - 64))
      | (1ULL << (CIFLocationParser::T__83 - 64))
      | (1ULL << (CIFLocationParser::T__84 - 64))
      | (1ULL << (CIFLocationParser::T__85 - 64))
      | (1ULL << (CIFLocationParser::T__86 - 64))
      | (1ULL << (CIFLocationParser::T__87 - 64))
      | (1ULL << (CIFLocationParser::T__88 - 64))
      | (1ULL << (CIFLocationParser::T__89 - 64))
      | (1ULL << (CIFLocationParser::T__90 - 64))
      | (1ULL << (CIFLocationParser::T__91 - 64))
      | (1ULL << (CIFLocationParser::T__92 - 64))
      | (1ULL << (CIFLocationParser::T__93 - 64))
      | (1ULL << (CIFLocationParser::NUMBER - 64))
      | (1ULL << (CIFLocationParser::REALNUMBER - 64))
      | (1ULL << (CIFLocationParser::STRING - 64))
      | (1ULL << (CIFLocationParser::IDENTIFIER - 64))
      | (1ULL << (CIFLocationParser::RELATIVENAME - 64))
      | (1ULL << (CIFLocationParser::ABSOLUTENAME - 64))
      | (1ULL << (CIFLocationParser::ROOTNAME - 64)))) != 0)) {
      setState(320);
      expression();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

CIFLocationParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CIFLocationParser::OrExpressionContext *> CIFLocationParser::ExpressionContext::orExpression() {
  return getRuleContexts<CIFLocationParser::OrExpressionContext>();
}

CIFLocationParser::OrExpressionContext* CIFLocationParser::ExpressionContext::orExpression(size_t i) {
  return getRuleContext<CIFLocationParser::OrExpressionContext>(i);
}


size_t CIFLocationParser::ExpressionContext::getRuleIndex() const {
  return CIFLocationParser::RuleExpression;
}

antlrcpp::Any CIFLocationParser::ExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitExpression(this);
  else
    return visitor->visitChildren(this);
}

CIFLocationParser::ExpressionContext* CIFLocationParser::expression() {
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 46, CIFLocationParser::RuleExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(332);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(323);
      orExpression();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(324);
      orExpression();
      setState(325);
      match(CIFLocationParser::T__28);
      setState(326);
      orExpression();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(328);
      orExpression();
      setState(329);
      match(CIFLocationParser::T__29);
      setState(330);
      orExpression();
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

//----------------- EquationsContext ------------------------------------------------------------------

CIFLocationParser::EquationsContext::EquationsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CIFLocationParser::EquationContext *> CIFLocationParser::EquationsContext::equation() {
  return getRuleContexts<CIFLocationParser::EquationContext>();
}

CIFLocationParser::EquationContext* CIFLocationParser::EquationsContext::equation(size_t i) {
  return getRuleContext<CIFLocationParser::EquationContext>(i);
}


size_t CIFLocationParser::EquationsContext::getRuleIndex() const {
  return CIFLocationParser::RuleEquations;
}

antlrcpp::Any CIFLocationParser::EquationsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitEquations(this);
  else
    return visitor->visitChildren(this);
}

CIFLocationParser::EquationsContext* CIFLocationParser::equations() {
  EquationsContext *_localctx = _tracker.createInstance<EquationsContext>(_ctx, getState());
  enterRule(_localctx, 48, CIFLocationParser::RuleEquations);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(334);
    equation();
    setState(339);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CIFLocationParser::T__12) {
      setState(335);
      match(CIFLocationParser::T__12);
      setState(336);
      equation();
      setState(341);
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

CIFLocationParser::EquationContext::EquationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CIFLocationParser::EquationContext::getRuleIndex() const {
  return CIFLocationParser::RuleEquation;
}

void CIFLocationParser::EquationContext::copyFrom(EquationContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- EquationDerivateContext ------------------------------------------------------------------

CIFLocationParser::IdentifierContext* CIFLocationParser::EquationDerivateContext::identifier() {
  return getRuleContext<CIFLocationParser::IdentifierContext>(0);
}

CIFLocationParser::ExpressionContext* CIFLocationParser::EquationDerivateContext::expression() {
  return getRuleContext<CIFLocationParser::ExpressionContext>(0);
}

CIFLocationParser::EquationDerivateContext::EquationDerivateContext(EquationContext *ctx) { copyFrom(ctx); }

antlrcpp::Any CIFLocationParser::EquationDerivateContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitEquationDerivate(this);
  else
    return visitor->visitChildren(this);
}
//----------------- EquationNonDerivateContext ------------------------------------------------------------------

CIFLocationParser::IdentifierContext* CIFLocationParser::EquationNonDerivateContext::identifier() {
  return getRuleContext<CIFLocationParser::IdentifierContext>(0);
}

CIFLocationParser::ExpressionContext* CIFLocationParser::EquationNonDerivateContext::expression() {
  return getRuleContext<CIFLocationParser::ExpressionContext>(0);
}

CIFLocationParser::EquationNonDerivateContext::EquationNonDerivateContext(EquationContext *ctx) { copyFrom(ctx); }

antlrcpp::Any CIFLocationParser::EquationNonDerivateContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitEquationNonDerivate(this);
  else
    return visitor->visitChildren(this);
}
CIFLocationParser::EquationContext* CIFLocationParser::equation() {
  EquationContext *_localctx = _tracker.createInstance<EquationContext>(_ctx, getState());
  enterRule(_localctx, 50, CIFLocationParser::RuleEquation);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(351);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<EquationContext *>(_tracker.createInstance<CIFLocationParser::EquationDerivateContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(342);
      identifier();
      setState(343);
      match(CIFLocationParser::T__30);
      setState(344);
      match(CIFLocationParser::T__31);
      setState(345);
      expression();
      break;
    }

    case 2: {
      _localctx = dynamic_cast<EquationContext *>(_tracker.createInstance<CIFLocationParser::EquationNonDerivateContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(347);
      identifier();
      setState(348);
      match(CIFLocationParser::T__31);
      setState(349);
      expression();
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

//----------------- OrExpressionContext ------------------------------------------------------------------

CIFLocationParser::OrExpressionContext::OrExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CIFLocationParser::AndExpressionContext *> CIFLocationParser::OrExpressionContext::andExpression() {
  return getRuleContexts<CIFLocationParser::AndExpressionContext>();
}

CIFLocationParser::AndExpressionContext* CIFLocationParser::OrExpressionContext::andExpression(size_t i) {
  return getRuleContext<CIFLocationParser::AndExpressionContext>(i);
}


size_t CIFLocationParser::OrExpressionContext::getRuleIndex() const {
  return CIFLocationParser::RuleOrExpression;
}

antlrcpp::Any CIFLocationParser::OrExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitOrExpression(this);
  else
    return visitor->visitChildren(this);
}

CIFLocationParser::OrExpressionContext* CIFLocationParser::orExpression() {
  OrExpressionContext *_localctx = _tracker.createInstance<OrExpressionContext>(_ctx, getState());
  enterRule(_localctx, 52, CIFLocationParser::RuleOrExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(353);
    andExpression();
    setState(358);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CIFLocationParser::T__32) {
      setState(354);
      match(CIFLocationParser::T__32);
      setState(355);
      andExpression();
      setState(360);
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

//----------------- AndExpressionContext ------------------------------------------------------------------

CIFLocationParser::AndExpressionContext::AndExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CIFLocationParser::CompareExpressionContext *> CIFLocationParser::AndExpressionContext::compareExpression() {
  return getRuleContexts<CIFLocationParser::CompareExpressionContext>();
}

CIFLocationParser::CompareExpressionContext* CIFLocationParser::AndExpressionContext::compareExpression(size_t i) {
  return getRuleContext<CIFLocationParser::CompareExpressionContext>(i);
}


size_t CIFLocationParser::AndExpressionContext::getRuleIndex() const {
  return CIFLocationParser::RuleAndExpression;
}

antlrcpp::Any CIFLocationParser::AndExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitAndExpression(this);
  else
    return visitor->visitChildren(this);
}

CIFLocationParser::AndExpressionContext* CIFLocationParser::andExpression() {
  AndExpressionContext *_localctx = _tracker.createInstance<AndExpressionContext>(_ctx, getState());
  enterRule(_localctx, 54, CIFLocationParser::RuleAndExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(361);
    compareExpression();
    setState(366);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CIFLocationParser::T__33) {
      setState(362);
      match(CIFLocationParser::T__33);
      setState(363);
      compareExpression();
      setState(368);
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

//----------------- CompareExpressionContext ------------------------------------------------------------------

CIFLocationParser::CompareExpressionContext::CompareExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CIFLocationParser::AddExpressionContext *> CIFLocationParser::CompareExpressionContext::addExpression() {
  return getRuleContexts<CIFLocationParser::AddExpressionContext>();
}

CIFLocationParser::AddExpressionContext* CIFLocationParser::CompareExpressionContext::addExpression(size_t i) {
  return getRuleContext<CIFLocationParser::AddExpressionContext>(i);
}

std::vector<tree::TerminalNode *> CIFLocationParser::CompareExpressionContext::COMPOP() {
  return getTokens(CIFLocationParser::COMPOP);
}

tree::TerminalNode* CIFLocationParser::CompareExpressionContext::COMPOP(size_t i) {
  return getToken(CIFLocationParser::COMPOP, i);
}


size_t CIFLocationParser::CompareExpressionContext::getRuleIndex() const {
  return CIFLocationParser::RuleCompareExpression;
}

antlrcpp::Any CIFLocationParser::CompareExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitCompareExpression(this);
  else
    return visitor->visitChildren(this);
}

CIFLocationParser::CompareExpressionContext* CIFLocationParser::compareExpression() {
  CompareExpressionContext *_localctx = _tracker.createInstance<CompareExpressionContext>(_ctx, getState());
  enterRule(_localctx, 56, CIFLocationParser::RuleCompareExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(369);
    addExpression();
    setState(374);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CIFLocationParser::COMPOP) {
      setState(370);
      match(CIFLocationParser::COMPOP);
      setState(371);
      addExpression();
      setState(376);
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

//----------------- AddExpressionContext ------------------------------------------------------------------

CIFLocationParser::AddExpressionContext::AddExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CIFLocationParser::MulExpressionContext *> CIFLocationParser::AddExpressionContext::mulExpression() {
  return getRuleContexts<CIFLocationParser::MulExpressionContext>();
}

CIFLocationParser::MulExpressionContext* CIFLocationParser::AddExpressionContext::mulExpression(size_t i) {
  return getRuleContext<CIFLocationParser::MulExpressionContext>(i);
}

std::vector<tree::TerminalNode *> CIFLocationParser::AddExpressionContext::ADDOP() {
  return getTokens(CIFLocationParser::ADDOP);
}

tree::TerminalNode* CIFLocationParser::AddExpressionContext::ADDOP(size_t i) {
  return getToken(CIFLocationParser::ADDOP, i);
}


size_t CIFLocationParser::AddExpressionContext::getRuleIndex() const {
  return CIFLocationParser::RuleAddExpression;
}

antlrcpp::Any CIFLocationParser::AddExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitAddExpression(this);
  else
    return visitor->visitChildren(this);
}

CIFLocationParser::AddExpressionContext* CIFLocationParser::addExpression() {
  AddExpressionContext *_localctx = _tracker.createInstance<AddExpressionContext>(_ctx, getState());
  enterRule(_localctx, 58, CIFLocationParser::RuleAddExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(377);
    mulExpression();
    setState(382);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CIFLocationParser::ADDOP) {
      setState(378);
      match(CIFLocationParser::ADDOP);
      setState(379);
      mulExpression();
      setState(384);
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

//----------------- MulExpressionContext ------------------------------------------------------------------

CIFLocationParser::MulExpressionContext::MulExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CIFLocationParser::UnaryExpressionContext *> CIFLocationParser::MulExpressionContext::unaryExpression() {
  return getRuleContexts<CIFLocationParser::UnaryExpressionContext>();
}

CIFLocationParser::UnaryExpressionContext* CIFLocationParser::MulExpressionContext::unaryExpression(size_t i) {
  return getRuleContext<CIFLocationParser::UnaryExpressionContext>(i);
}

std::vector<tree::TerminalNode *> CIFLocationParser::MulExpressionContext::MULOP() {
  return getTokens(CIFLocationParser::MULOP);
}

tree::TerminalNode* CIFLocationParser::MulExpressionContext::MULOP(size_t i) {
  return getToken(CIFLocationParser::MULOP, i);
}


size_t CIFLocationParser::MulExpressionContext::getRuleIndex() const {
  return CIFLocationParser::RuleMulExpression;
}

antlrcpp::Any CIFLocationParser::MulExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitMulExpression(this);
  else
    return visitor->visitChildren(this);
}

CIFLocationParser::MulExpressionContext* CIFLocationParser::mulExpression() {
  MulExpressionContext *_localctx = _tracker.createInstance<MulExpressionContext>(_ctx, getState());
  enterRule(_localctx, 60, CIFLocationParser::RuleMulExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(385);
    unaryExpression();
    setState(390);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CIFLocationParser::MULOP) {
      setState(386);
      match(CIFLocationParser::MULOP);
      setState(387);
      unaryExpression();
      setState(392);
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

//----------------- UnaryExpressionContext ------------------------------------------------------------------

CIFLocationParser::UnaryExpressionContext::UnaryExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CIFLocationParser::UnaryExpressionContext::getRuleIndex() const {
  return CIFLocationParser::RuleUnaryExpression;
}

void CIFLocationParser::UnaryExpressionContext::copyFrom(UnaryExpressionContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- UnaryExprContext ------------------------------------------------------------------

CIFLocationParser::UnaryExpressionContext* CIFLocationParser::UnaryExprContext::unaryExpression() {
  return getRuleContext<CIFLocationParser::UnaryExpressionContext>(0);
}

CIFLocationParser::UnaryExprContext::UnaryExprContext(UnaryExpressionContext *ctx) { copyFrom(ctx); }

antlrcpp::Any CIFLocationParser::UnaryExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitUnaryExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UnaryExprFuncContext ------------------------------------------------------------------

CIFLocationParser::FuncExpressionContext* CIFLocationParser::UnaryExprFuncContext::funcExpression() {
  return getRuleContext<CIFLocationParser::FuncExpressionContext>(0);
}

CIFLocationParser::UnaryExprFuncContext::UnaryExprFuncContext(UnaryExpressionContext *ctx) { copyFrom(ctx); }

antlrcpp::Any CIFLocationParser::UnaryExprFuncContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitUnaryExprFunc(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UnaryExprMinusContext ------------------------------------------------------------------

CIFLocationParser::UnaryExpressionContext* CIFLocationParser::UnaryExprMinusContext::unaryExpression() {
  return getRuleContext<CIFLocationParser::UnaryExpressionContext>(0);
}

CIFLocationParser::UnaryExprMinusContext::UnaryExprMinusContext(UnaryExpressionContext *ctx) { copyFrom(ctx); }

antlrcpp::Any CIFLocationParser::UnaryExprMinusContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitUnaryExprMinus(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UnaryExprPlusContext ------------------------------------------------------------------

CIFLocationParser::UnaryExpressionContext* CIFLocationParser::UnaryExprPlusContext::unaryExpression() {
  return getRuleContext<CIFLocationParser::UnaryExpressionContext>(0);
}

CIFLocationParser::UnaryExprPlusContext::UnaryExprPlusContext(UnaryExpressionContext *ctx) { copyFrom(ctx); }

antlrcpp::Any CIFLocationParser::UnaryExprPlusContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitUnaryExprPlus(this);
  else
    return visitor->visitChildren(this);
}
CIFLocationParser::UnaryExpressionContext* CIFLocationParser::unaryExpression() {
  UnaryExpressionContext *_localctx = _tracker.createInstance<UnaryExpressionContext>(_ctx, getState());
  enterRule(_localctx, 62, CIFLocationParser::RuleUnaryExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(402);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CIFLocationParser::T__15:
      case CIFLocationParser::T__20:
      case CIFLocationParser::T__24:
      case CIFLocationParser::T__26:
      case CIFLocationParser::T__38:
      case CIFLocationParser::T__39:
      case CIFLocationParser::T__40:
      case CIFLocationParser::T__41:
      case CIFLocationParser::T__43:
      case CIFLocationParser::T__45:
      case CIFLocationParser::T__46:
      case CIFLocationParser::T__62:
      case CIFLocationParser::T__63:
      case CIFLocationParser::T__64:
      case CIFLocationParser::T__65:
      case CIFLocationParser::T__66:
      case CIFLocationParser::T__67:
      case CIFLocationParser::T__68:
      case CIFLocationParser::T__69:
      case CIFLocationParser::T__70:
      case CIFLocationParser::T__71:
      case CIFLocationParser::T__72:
      case CIFLocationParser::T__73:
      case CIFLocationParser::T__74:
      case CIFLocationParser::T__75:
      case CIFLocationParser::T__76:
      case CIFLocationParser::T__77:
      case CIFLocationParser::T__78:
      case CIFLocationParser::T__79:
      case CIFLocationParser::T__80:
      case CIFLocationParser::T__81:
      case CIFLocationParser::T__82:
      case CIFLocationParser::T__83:
      case CIFLocationParser::T__84:
      case CIFLocationParser::T__85:
      case CIFLocationParser::T__86:
      case CIFLocationParser::T__87:
      case CIFLocationParser::T__88:
      case CIFLocationParser::T__89:
      case CIFLocationParser::T__90:
      case CIFLocationParser::T__91:
      case CIFLocationParser::T__92:
      case CIFLocationParser::T__93:
      case CIFLocationParser::NUMBER:
      case CIFLocationParser::REALNUMBER:
      case CIFLocationParser::STRING:
      case CIFLocationParser::IDENTIFIER:
      case CIFLocationParser::RELATIVENAME:
      case CIFLocationParser::ABSOLUTENAME:
      case CIFLocationParser::ROOTNAME: {
        _localctx = dynamic_cast<UnaryExpressionContext *>(_tracker.createInstance<CIFLocationParser::UnaryExprFuncContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(393);
        funcExpression();
        break;
      }

      case CIFLocationParser::T__34: {
        _localctx = dynamic_cast<UnaryExpressionContext *>(_tracker.createInstance<CIFLocationParser::UnaryExprMinusContext>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(394);
        match(CIFLocationParser::T__34);
        setState(395);
        unaryExpression();
        break;
      }

      case CIFLocationParser::T__35: {
        _localctx = dynamic_cast<UnaryExpressionContext *>(_tracker.createInstance<CIFLocationParser::UnaryExprPlusContext>(_localctx));
        enterOuterAlt(_localctx, 3);
        setState(396);
        match(CIFLocationParser::T__35);
        setState(397);
        unaryExpression();
        break;
      }

      case CIFLocationParser::T__36: {
        _localctx = dynamic_cast<UnaryExpressionContext *>(_tracker.createInstance<CIFLocationParser::UnaryExprContext>(_localctx));
        enterOuterAlt(_localctx, 4);
        setState(398);
        match(CIFLocationParser::T__36);
        setState(399);
        unaryExpression();
        break;
      }

      case CIFLocationParser::T__37: {
        _localctx = dynamic_cast<UnaryExpressionContext *>(_tracker.createInstance<CIFLocationParser::UnaryExprContext>(_localctx));
        enterOuterAlt(_localctx, 5);
        setState(400);
        match(CIFLocationParser::T__37);
        setState(401);
        unaryExpression();
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

//----------------- FuncExpressionContext ------------------------------------------------------------------

CIFLocationParser::FuncExpressionContext::FuncExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CIFLocationParser::ExpressionFactorContext* CIFLocationParser::FuncExpressionContext::expressionFactor() {
  return getRuleContext<CIFLocationParser::ExpressionFactorContext>(0);
}

CIFLocationParser::StdLibFunctionContext* CIFLocationParser::FuncExpressionContext::stdLibFunction() {
  return getRuleContext<CIFLocationParser::StdLibFunctionContext>(0);
}

std::vector<CIFLocationParser::ExpressionsContext *> CIFLocationParser::FuncExpressionContext::expressions() {
  return getRuleContexts<CIFLocationParser::ExpressionsContext>();
}

CIFLocationParser::ExpressionsContext* CIFLocationParser::FuncExpressionContext::expressions(size_t i) {
  return getRuleContext<CIFLocationParser::ExpressionsContext>(i);
}

std::vector<CIFLocationParser::OptExpressionContext *> CIFLocationParser::FuncExpressionContext::optExpression() {
  return getRuleContexts<CIFLocationParser::OptExpressionContext>();
}

CIFLocationParser::OptExpressionContext* CIFLocationParser::FuncExpressionContext::optExpression(size_t i) {
  return getRuleContext<CIFLocationParser::OptExpressionContext>(i);
}


size_t CIFLocationParser::FuncExpressionContext::getRuleIndex() const {
  return CIFLocationParser::RuleFuncExpression;
}

antlrcpp::Any CIFLocationParser::FuncExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitFuncExpression(this);
  else
    return visitor->visitChildren(this);
}

CIFLocationParser::FuncExpressionContext* CIFLocationParser::funcExpression() {
  FuncExpressionContext *_localctx = _tracker.createInstance<FuncExpressionContext>(_ctx, getState());
  enterRule(_localctx, 64, CIFLocationParser::RuleFuncExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(414);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx)) {
    case 1: {
      setState(404);
      expressionFactor();
      break;
    }

    case 2: {
      setState(405);
      stdLibFunction();
      setState(406);
      match(CIFLocationParser::T__24);
      setState(407);
      match(CIFLocationParser::T__25);
      break;
    }

    case 3: {
      setState(409);
      stdLibFunction();
      setState(410);
      match(CIFLocationParser::T__24);
      setState(411);
      expressions();
      setState(412);
      match(CIFLocationParser::T__25);
      break;
    }

    }
    setState(434);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(432);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)) {
        case 1: {
          setState(416);
          match(CIFLocationParser::T__26);
          setState(417);
          expressions();
          setState(418);
          match(CIFLocationParser::T__27);
          break;
        }

        case 2: {
          setState(420);
          match(CIFLocationParser::T__26);
          setState(421);
          optExpression();
          setState(422);
          match(CIFLocationParser::T__2);
          setState(423);
          optExpression();
          setState(424);
          match(CIFLocationParser::T__27);
          break;
        }

        case 3: {
          setState(426);
          match(CIFLocationParser::T__24);
          setState(427);
          match(CIFLocationParser::T__25);
          break;
        }

        case 4: {
          setState(428);
          match(CIFLocationParser::T__24);
          setState(429);
          expressions();
          setState(430);
          match(CIFLocationParser::T__25);
          break;
        }

        } 
      }
      setState(436);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionFactorContext ------------------------------------------------------------------

CIFLocationParser::ExpressionFactorContext::ExpressionFactorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CIFLocationParser::ExpressionFactorContext::getRuleIndex() const {
  return CIFLocationParser::RuleExpressionFactor;
}

void CIFLocationParser::ExpressionFactorContext::copyFrom(ExpressionFactorContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ExprFactNumberContext ------------------------------------------------------------------

tree::TerminalNode* CIFLocationParser::ExprFactNumberContext::NUMBER() {
  return getToken(CIFLocationParser::NUMBER, 0);
}

CIFLocationParser::ExprFactNumberContext::ExprFactNumberContext(ExpressionFactorContext *ctx) { copyFrom(ctx); }

antlrcpp::Any CIFLocationParser::ExprFactNumberContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitExprFactNumber(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprFactContext ------------------------------------------------------------------

CIFLocationParser::StringTokenContext* CIFLocationParser::ExprFactContext::stringToken() {
  return getRuleContext<CIFLocationParser::StringTokenContext>(0);
}

CIFLocationParser::ExpressionsContext* CIFLocationParser::ExprFactContext::expressions() {
  return getRuleContext<CIFLocationParser::ExpressionsContext>(0);
}

CIFLocationParser::NonEmptySetExpressionContext* CIFLocationParser::ExprFactContext::nonEmptySetExpression() {
  return getRuleContext<CIFLocationParser::NonEmptySetExpressionContext>(0);
}

CIFLocationParser::DictPairsContext* CIFLocationParser::ExprFactContext::dictPairs() {
  return getRuleContext<CIFLocationParser::DictPairsContext>(0);
}

std::vector<CIFLocationParser::ExpressionContext *> CIFLocationParser::ExprFactContext::expression() {
  return getRuleContexts<CIFLocationParser::ExpressionContext>();
}

CIFLocationParser::ExpressionContext* CIFLocationParser::ExprFactContext::expression(size_t i) {
  return getRuleContext<CIFLocationParser::ExpressionContext>(i);
}

CIFLocationParser::TypeContext* CIFLocationParser::ExprFactContext::type() {
  return getRuleContext<CIFLocationParser::TypeContext>(0);
}

CIFLocationParser::ExpressionFactorContext* CIFLocationParser::ExprFactContext::expressionFactor() {
  return getRuleContext<CIFLocationParser::ExpressionFactorContext>(0);
}

CIFLocationParser::OptElifExprsContext* CIFLocationParser::ExprFactContext::optElifExprs() {
  return getRuleContext<CIFLocationParser::OptElifExprsContext>(0);
}

CIFLocationParser::SwitchBodyContext* CIFLocationParser::ExprFactContext::switchBody() {
  return getRuleContext<CIFLocationParser::SwitchBodyContext>(0);
}

CIFLocationParser::NameContext* CIFLocationParser::ExprFactContext::name() {
  return getRuleContext<CIFLocationParser::NameContext>(0);
}

CIFLocationParser::ExprFactContext::ExprFactContext(ExpressionFactorContext *ctx) { copyFrom(ctx); }

antlrcpp::Any CIFLocationParser::ExprFactContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitExprFact(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprFactRealNumberContext ------------------------------------------------------------------

tree::TerminalNode* CIFLocationParser::ExprFactRealNumberContext::REALNUMBER() {
  return getToken(CIFLocationParser::REALNUMBER, 0);
}

CIFLocationParser::ExprFactRealNumberContext::ExprFactRealNumberContext(ExpressionFactorContext *ctx) { copyFrom(ctx); }

antlrcpp::Any CIFLocationParser::ExprFactRealNumberContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitExprFactRealNumber(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprFactNameContext ------------------------------------------------------------------

CIFLocationParser::NameContext* CIFLocationParser::ExprFactNameContext::name() {
  return getRuleContext<CIFLocationParser::NameContext>(0);
}

CIFLocationParser::ExprFactNameContext::ExprFactNameContext(ExpressionFactorContext *ctx) { copyFrom(ctx); }

antlrcpp::Any CIFLocationParser::ExprFactNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitExprFactName(this);
  else
    return visitor->visitChildren(this);
}
CIFLocationParser::ExpressionFactorContext* CIFLocationParser::expressionFactor() {
  ExpressionFactorContext *_localctx = _tracker.createInstance<ExpressionFactorContext>(_ctx, getState());
  enterRule(_localctx, 66, CIFLocationParser::RuleExpressionFactor);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(492);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<CIFLocationParser::ExprFactContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(437);
      match(CIFLocationParser::T__38);
      break;
    }

    case 2: {
      _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<CIFLocationParser::ExprFactContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(438);
      match(CIFLocationParser::T__39);
      break;
    }

    case 3: {
      _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<CIFLocationParser::ExprFactNumberContext>(_localctx));
      enterOuterAlt(_localctx, 3);
      setState(439);
      match(CIFLocationParser::NUMBER);
      break;
    }

    case 4: {
      _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<CIFLocationParser::ExprFactRealNumberContext>(_localctx));
      enterOuterAlt(_localctx, 4);
      setState(440);
      match(CIFLocationParser::REALNUMBER);
      break;
    }

    case 5: {
      _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<CIFLocationParser::ExprFactNameContext>(_localctx));
      enterOuterAlt(_localctx, 5);
      setState(441);
      name();
      break;
    }

    case 6: {
      _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<CIFLocationParser::ExprFactContext>(_localctx));
      enterOuterAlt(_localctx, 6);
      setState(442);
      stringToken();
      break;
    }

    case 7: {
      _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<CIFLocationParser::ExprFactContext>(_localctx));
      enterOuterAlt(_localctx, 7);
      setState(443);
      match(CIFLocationParser::T__40);
      break;
    }

    case 8: {
      _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<CIFLocationParser::ExprFactContext>(_localctx));
      enterOuterAlt(_localctx, 8);
      setState(444);
      match(CIFLocationParser::T__26);
      setState(445);
      match(CIFLocationParser::T__27);
      break;
    }

    case 9: {
      _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<CIFLocationParser::ExprFactContext>(_localctx));
      enterOuterAlt(_localctx, 9);
      setState(446);
      match(CIFLocationParser::T__26);
      setState(447);
      expressions();
      setState(448);
      match(CIFLocationParser::T__27);
      break;
    }

    case 10: {
      _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<CIFLocationParser::ExprFactContext>(_localctx));
      enterOuterAlt(_localctx, 10);
      setState(450);
      match(CIFLocationParser::T__41);
      setState(451);
      match(CIFLocationParser::T__42);
      break;
    }

    case 11: {
      _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<CIFLocationParser::ExprFactContext>(_localctx));
      enterOuterAlt(_localctx, 11);
      setState(452);
      nonEmptySetExpression();
      break;
    }

    case 12: {
      _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<CIFLocationParser::ExprFactContext>(_localctx));
      enterOuterAlt(_localctx, 12);
      setState(453);
      match(CIFLocationParser::T__41);
      setState(454);
      dictPairs();
      setState(455);
      match(CIFLocationParser::T__42);
      break;
    }

    case 13: {
      _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<CIFLocationParser::ExprFactContext>(_localctx));
      enterOuterAlt(_localctx, 13);
      setState(457);
      match(CIFLocationParser::T__24);
      setState(458);
      expression();
      setState(459);
      match(CIFLocationParser::T__12);
      setState(460);
      expression();
      setState(461);
      match(CIFLocationParser::T__25);
      break;
    }

    case 14: {
      _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<CIFLocationParser::ExprFactContext>(_localctx));
      enterOuterAlt(_localctx, 14);
      setState(463);
      match(CIFLocationParser::T__43);
      setState(464);
      type();
      setState(465);
      match(CIFLocationParser::T__44);
      setState(466);
      expressionFactor();
      break;
    }

    case 15: {
      _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<CIFLocationParser::ExprFactContext>(_localctx));
      enterOuterAlt(_localctx, 15);
      setState(468);
      match(CIFLocationParser::T__20);
      setState(469);
      expressions();
      setState(470);
      match(CIFLocationParser::T__2);
      setState(471);
      expression();
      setState(472);
      optElifExprs();
      setState(473);
      match(CIFLocationParser::T__23);
      setState(474);
      expression();
      setState(475);
      match(CIFLocationParser::T__21);
      break;
    }

    case 16: {
      _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<CIFLocationParser::ExprFactContext>(_localctx));
      enterOuterAlt(_localctx, 16);
      setState(477);
      match(CIFLocationParser::T__45);
      setState(478);
      expression();
      setState(479);
      match(CIFLocationParser::T__2);
      setState(480);
      switchBody();
      setState(481);
      match(CIFLocationParser::T__21);
      break;
    }

    case 17: {
      _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<CIFLocationParser::ExprFactContext>(_localctx));
      enterOuterAlt(_localctx, 17);
      setState(483);
      match(CIFLocationParser::T__24);
      setState(484);
      expression();
      setState(485);
      match(CIFLocationParser::T__25);
      break;
    }

    case 18: {
      _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<CIFLocationParser::ExprFactContext>(_localctx));
      enterOuterAlt(_localctx, 18);
      setState(487);
      name();
      setState(488);
      match(CIFLocationParser::T__30);
      break;
    }

    case 19: {
      _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<CIFLocationParser::ExprFactContext>(_localctx));
      enterOuterAlt(_localctx, 19);
      setState(490);
      match(CIFLocationParser::T__15);
      break;
    }

    case 20: {
      _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<CIFLocationParser::ExprFactContext>(_localctx));
      enterOuterAlt(_localctx, 20);
      setState(491);
      match(CIFLocationParser::T__46);
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

//----------------- NonEmptySetExpressionContext ------------------------------------------------------------------

CIFLocationParser::NonEmptySetExpressionContext::NonEmptySetExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CIFLocationParser::ExpressionsContext* CIFLocationParser::NonEmptySetExpressionContext::expressions() {
  return getRuleContext<CIFLocationParser::ExpressionsContext>(0);
}


size_t CIFLocationParser::NonEmptySetExpressionContext::getRuleIndex() const {
  return CIFLocationParser::RuleNonEmptySetExpression;
}

antlrcpp::Any CIFLocationParser::NonEmptySetExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitNonEmptySetExpression(this);
  else
    return visitor->visitChildren(this);
}

CIFLocationParser::NonEmptySetExpressionContext* CIFLocationParser::nonEmptySetExpression() {
  NonEmptySetExpressionContext *_localctx = _tracker.createInstance<NonEmptySetExpressionContext>(_ctx, getState());
  enterRule(_localctx, 68, CIFLocationParser::RuleNonEmptySetExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(494);
    match(CIFLocationParser::T__41);
    setState(495);
    expressions();
    setState(496);
    match(CIFLocationParser::T__42);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DictPairsContext ------------------------------------------------------------------

CIFLocationParser::DictPairsContext::DictPairsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CIFLocationParser::ExpressionContext *> CIFLocationParser::DictPairsContext::expression() {
  return getRuleContexts<CIFLocationParser::ExpressionContext>();
}

CIFLocationParser::ExpressionContext* CIFLocationParser::DictPairsContext::expression(size_t i) {
  return getRuleContext<CIFLocationParser::ExpressionContext>(i);
}


size_t CIFLocationParser::DictPairsContext::getRuleIndex() const {
  return CIFLocationParser::RuleDictPairs;
}

antlrcpp::Any CIFLocationParser::DictPairsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitDictPairs(this);
  else
    return visitor->visitChildren(this);
}

CIFLocationParser::DictPairsContext* CIFLocationParser::dictPairs() {
  DictPairsContext *_localctx = _tracker.createInstance<DictPairsContext>(_ctx, getState());
  enterRule(_localctx, 70, CIFLocationParser::RuleDictPairs);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(498);
    expression();
    setState(499);
    match(CIFLocationParser::T__2);
    setState(500);
    expression();

    setState(501);
    match(CIFLocationParser::T__12);
    setState(502);
    expression();
    setState(503);
    match(CIFLocationParser::T__2);
    setState(504);
    expression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OptElifExprsContext ------------------------------------------------------------------

CIFLocationParser::OptElifExprsContext::OptElifExprsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CIFLocationParser::ExpressionContext *> CIFLocationParser::OptElifExprsContext::expression() {
  return getRuleContexts<CIFLocationParser::ExpressionContext>();
}

CIFLocationParser::ExpressionContext* CIFLocationParser::OptElifExprsContext::expression(size_t i) {
  return getRuleContext<CIFLocationParser::ExpressionContext>(i);
}


size_t CIFLocationParser::OptElifExprsContext::getRuleIndex() const {
  return CIFLocationParser::RuleOptElifExprs;
}

antlrcpp::Any CIFLocationParser::OptElifExprsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitOptElifExprs(this);
  else
    return visitor->visitChildren(this);
}

CIFLocationParser::OptElifExprsContext* CIFLocationParser::optElifExprs() {
  OptElifExprsContext *_localctx = _tracker.createInstance<OptElifExprsContext>(_ctx, getState());
  enterRule(_localctx, 72, CIFLocationParser::RuleOptElifExprs);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(513);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CIFLocationParser::T__15)
      | (1ULL << CIFLocationParser::T__20)
      | (1ULL << CIFLocationParser::T__24)
      | (1ULL << CIFLocationParser::T__26)
      | (1ULL << CIFLocationParser::T__34)
      | (1ULL << CIFLocationParser::T__35)
      | (1ULL << CIFLocationParser::T__36)
      | (1ULL << CIFLocationParser::T__37)
      | (1ULL << CIFLocationParser::T__38)
      | (1ULL << CIFLocationParser::T__39)
      | (1ULL << CIFLocationParser::T__40)
      | (1ULL << CIFLocationParser::T__41)
      | (1ULL << CIFLocationParser::T__43)
      | (1ULL << CIFLocationParser::T__45)
      | (1ULL << CIFLocationParser::T__46)
      | (1ULL << CIFLocationParser::T__62))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (CIFLocationParser::T__63 - 64))
      | (1ULL << (CIFLocationParser::T__64 - 64))
      | (1ULL << (CIFLocationParser::T__65 - 64))
      | (1ULL << (CIFLocationParser::T__66 - 64))
      | (1ULL << (CIFLocationParser::T__67 - 64))
      | (1ULL << (CIFLocationParser::T__68 - 64))
      | (1ULL << (CIFLocationParser::T__69 - 64))
      | (1ULL << (CIFLocationParser::T__70 - 64))
      | (1ULL << (CIFLocationParser::T__71 - 64))
      | (1ULL << (CIFLocationParser::T__72 - 64))
      | (1ULL << (CIFLocationParser::T__73 - 64))
      | (1ULL << (CIFLocationParser::T__74 - 64))
      | (1ULL << (CIFLocationParser::T__75 - 64))
      | (1ULL << (CIFLocationParser::T__76 - 64))
      | (1ULL << (CIFLocationParser::T__77 - 64))
      | (1ULL << (CIFLocationParser::T__78 - 64))
      | (1ULL << (CIFLocationParser::T__79 - 64))
      | (1ULL << (CIFLocationParser::T__80 - 64))
      | (1ULL << (CIFLocationParser::T__81 - 64))
      | (1ULL << (CIFLocationParser::T__82 - 64))
      | (1ULL << (CIFLocationParser::T__83 - 64))
      | (1ULL << (CIFLocationParser::T__84 - 64))
      | (1ULL << (CIFLocationParser::T__85 - 64))
      | (1ULL << (CIFLocationParser::T__86 - 64))
      | (1ULL << (CIFLocationParser::T__87 - 64))
      | (1ULL << (CIFLocationParser::T__88 - 64))
      | (1ULL << (CIFLocationParser::T__89 - 64))
      | (1ULL << (CIFLocationParser::T__90 - 64))
      | (1ULL << (CIFLocationParser::T__91 - 64))
      | (1ULL << (CIFLocationParser::T__92 - 64))
      | (1ULL << (CIFLocationParser::T__93 - 64))
      | (1ULL << (CIFLocationParser::NUMBER - 64))
      | (1ULL << (CIFLocationParser::REALNUMBER - 64))
      | (1ULL << (CIFLocationParser::STRING - 64))
      | (1ULL << (CIFLocationParser::IDENTIFIER - 64))
      | (1ULL << (CIFLocationParser::RELATIVENAME - 64))
      | (1ULL << (CIFLocationParser::ABSOLUTENAME - 64))
      | (1ULL << (CIFLocationParser::ROOTNAME - 64)))) != 0)) {
      setState(506);
      expression();
      setState(507);
      match(CIFLocationParser::T__2);
      setState(508);
      expression();
      setState(509);
      match(CIFLocationParser::T__22);
      setState(515);
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

//----------------- SwitchBodyContext ------------------------------------------------------------------

CIFLocationParser::SwitchBodyContext::SwitchBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CIFLocationParser::SwitchCasesContext* CIFLocationParser::SwitchBodyContext::switchCases() {
  return getRuleContext<CIFLocationParser::SwitchCasesContext>(0);
}

CIFLocationParser::ExpressionContext* CIFLocationParser::SwitchBodyContext::expression() {
  return getRuleContext<CIFLocationParser::ExpressionContext>(0);
}


size_t CIFLocationParser::SwitchBodyContext::getRuleIndex() const {
  return CIFLocationParser::RuleSwitchBody;
}

antlrcpp::Any CIFLocationParser::SwitchBodyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitSwitchBody(this);
  else
    return visitor->visitChildren(this);
}

CIFLocationParser::SwitchBodyContext* CIFLocationParser::switchBody() {
  SwitchBodyContext *_localctx = _tracker.createInstance<SwitchBodyContext>(_ctx, getState());
  enterRule(_localctx, 74, CIFLocationParser::RuleSwitchBody);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(523);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(516);
      switchCases();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(517);
      switchCases();
      setState(518);
      match(CIFLocationParser::T__23);
      setState(519);
      expression();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(521);
      match(CIFLocationParser::T__23);
      setState(522);
      expression();
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

//----------------- SwitchCasesContext ------------------------------------------------------------------

CIFLocationParser::SwitchCasesContext::SwitchCasesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CIFLocationParser::ExpressionContext *> CIFLocationParser::SwitchCasesContext::expression() {
  return getRuleContexts<CIFLocationParser::ExpressionContext>();
}

CIFLocationParser::ExpressionContext* CIFLocationParser::SwitchCasesContext::expression(size_t i) {
  return getRuleContext<CIFLocationParser::ExpressionContext>(i);
}


size_t CIFLocationParser::SwitchCasesContext::getRuleIndex() const {
  return CIFLocationParser::RuleSwitchCases;
}

antlrcpp::Any CIFLocationParser::SwitchCasesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitSwitchCases(this);
  else
    return visitor->visitChildren(this);
}

CIFLocationParser::SwitchCasesContext* CIFLocationParser::switchCases() {
  SwitchCasesContext *_localctx = _tracker.createInstance<SwitchCasesContext>(_ctx, getState());
  enterRule(_localctx, 76, CIFLocationParser::RuleSwitchCases);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(530); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(525);
      match(CIFLocationParser::T__47);
      setState(526);
      expression();
      setState(527);
      match(CIFLocationParser::T__2);
      setState(528);
      expression();
      setState(532); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == CIFLocationParser::T__47);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypesContext ------------------------------------------------------------------

CIFLocationParser::TypesContext::TypesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CIFLocationParser::TypeContext *> CIFLocationParser::TypesContext::type() {
  return getRuleContexts<CIFLocationParser::TypeContext>();
}

CIFLocationParser::TypeContext* CIFLocationParser::TypesContext::type(size_t i) {
  return getRuleContext<CIFLocationParser::TypeContext>(i);
}


size_t CIFLocationParser::TypesContext::getRuleIndex() const {
  return CIFLocationParser::RuleTypes;
}

antlrcpp::Any CIFLocationParser::TypesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitTypes(this);
  else
    return visitor->visitChildren(this);
}

CIFLocationParser::TypesContext* CIFLocationParser::types() {
  TypesContext *_localctx = _tracker.createInstance<TypesContext>(_ctx, getState());
  enterRule(_localctx, 78, CIFLocationParser::RuleTypes);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(534);
    type();
    setState(539);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CIFLocationParser::T__12) {
      setState(535);
      match(CIFLocationParser::T__12);
      setState(536);
      type();
      setState(541);
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

//----------------- TypeContext ------------------------------------------------------------------

CIFLocationParser::TypeContext::TypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CIFLocationParser::ExpressionContext *> CIFLocationParser::TypeContext::expression() {
  return getRuleContexts<CIFLocationParser::ExpressionContext>();
}

CIFLocationParser::ExpressionContext* CIFLocationParser::TypeContext::expression(size_t i) {
  return getRuleContext<CIFLocationParser::ExpressionContext>(i);
}

std::vector<CIFLocationParser::TypeContext *> CIFLocationParser::TypeContext::type() {
  return getRuleContexts<CIFLocationParser::TypeContext>();
}

CIFLocationParser::TypeContext* CIFLocationParser::TypeContext::type(size_t i) {
  return getRuleContext<CIFLocationParser::TypeContext>(i);
}

CIFLocationParser::FieldsContext* CIFLocationParser::TypeContext::fields() {
  return getRuleContext<CIFLocationParser::FieldsContext>(0);
}

CIFLocationParser::TypesContext* CIFLocationParser::TypeContext::types() {
  return getRuleContext<CIFLocationParser::TypesContext>(0);
}

CIFLocationParser::NameContext* CIFLocationParser::TypeContext::name() {
  return getRuleContext<CIFLocationParser::NameContext>(0);
}


size_t CIFLocationParser::TypeContext::getRuleIndex() const {
  return CIFLocationParser::RuleType;
}

antlrcpp::Any CIFLocationParser::TypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitType(this);
  else
    return visitor->visitChildren(this);
}

CIFLocationParser::TypeContext* CIFLocationParser::type() {
  TypeContext *_localctx = _tracker.createInstance<TypeContext>(_ctx, getState());
  enterRule(_localctx, 80, CIFLocationParser::RuleType);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(597);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(542);
      match(CIFLocationParser::T__48);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(543);
      match(CIFLocationParser::T__49);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(544);
      match(CIFLocationParser::T__49);
      setState(545);
      match(CIFLocationParser::T__26);
      setState(546);
      expression();
      setState(547);
      match(CIFLocationParser::T__50);
      setState(548);
      expression();
      setState(549);
      match(CIFLocationParser::T__27);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(551);
      match(CIFLocationParser::T__51);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(552);
      match(CIFLocationParser::T__52);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(553);
      match(CIFLocationParser::T__53);
      setState(554);
      type();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(555);
      match(CIFLocationParser::T__53);
      setState(556);
      match(CIFLocationParser::T__26);
      setState(557);
      expression();
      setState(558);
      match(CIFLocationParser::T__27);
      setState(559);
      type();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(561);
      match(CIFLocationParser::T__53);
      setState(562);
      match(CIFLocationParser::T__26);
      setState(563);
      expression();
      setState(564);
      match(CIFLocationParser::T__50);
      setState(565);
      expression();
      setState(566);
      match(CIFLocationParser::T__27);
      setState(567);
      type();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(569);
      match(CIFLocationParser::T__54);
      setState(570);
      type();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(571);
      match(CIFLocationParser::T__55);
      setState(572);
      match(CIFLocationParser::T__24);
      setState(573);
      type();
      setState(574);
      match(CIFLocationParser::T__2);
      setState(575);
      type();
      setState(576);
      match(CIFLocationParser::T__25);
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(578);
      match(CIFLocationParser::T__56);
      setState(579);
      match(CIFLocationParser::T__24);
      setState(580);
      fields();
      setState(581);
      match(CIFLocationParser::T__25);
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(583);
      match(CIFLocationParser::T__57);
      setState(584);
      type();
      setState(585);
      match(CIFLocationParser::T__24);
      setState(586);
      match(CIFLocationParser::T__25);
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(588);
      match(CIFLocationParser::T__57);
      setState(589);
      type();
      setState(590);
      match(CIFLocationParser::T__24);
      setState(591);
      types();
      setState(592);
      match(CIFLocationParser::T__25);
      break;
    }

    case 14: {
      enterOuterAlt(_localctx, 14);
      setState(594);
      match(CIFLocationParser::T__58);
      setState(595);
      type();
      break;
    }

    case 15: {
      enterOuterAlt(_localctx, 15);
      setState(596);
      name();
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

//----------------- FieldsContext ------------------------------------------------------------------

CIFLocationParser::FieldsContext::FieldsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CIFLocationParser::FieldContext *> CIFLocationParser::FieldsContext::field() {
  return getRuleContexts<CIFLocationParser::FieldContext>();
}

CIFLocationParser::FieldContext* CIFLocationParser::FieldsContext::field(size_t i) {
  return getRuleContext<CIFLocationParser::FieldContext>(i);
}


size_t CIFLocationParser::FieldsContext::getRuleIndex() const {
  return CIFLocationParser::RuleFields;
}

antlrcpp::Any CIFLocationParser::FieldsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitFields(this);
  else
    return visitor->visitChildren(this);
}

CIFLocationParser::FieldsContext* CIFLocationParser::fields() {
  FieldsContext *_localctx = _tracker.createInstance<FieldsContext>(_ctx, getState());
  enterRule(_localctx, 82, CIFLocationParser::RuleFields);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(599);
    field();
    setState(604);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CIFLocationParser::T__12) {
      setState(600);
      match(CIFLocationParser::T__12);
      setState(601);
      field();
      setState(606);
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

//----------------- FieldContext ------------------------------------------------------------------

CIFLocationParser::FieldContext::FieldContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CIFLocationParser::TypeContext* CIFLocationParser::FieldContext::type() {
  return getRuleContext<CIFLocationParser::TypeContext>(0);
}

CIFLocationParser::IdentifierContext* CIFLocationParser::FieldContext::identifier() {
  return getRuleContext<CIFLocationParser::IdentifierContext>(0);
}


size_t CIFLocationParser::FieldContext::getRuleIndex() const {
  return CIFLocationParser::RuleField;
}

antlrcpp::Any CIFLocationParser::FieldContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitField(this);
  else
    return visitor->visitChildren(this);
}

CIFLocationParser::FieldContext* CIFLocationParser::field() {
  FieldContext *_localctx = _tracker.createInstance<FieldContext>(_ctx, getState());
  enterRule(_localctx, 84, CIFLocationParser::RuleField);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(607);
    type();
    setState(608);
    identifier();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NameSetContext ------------------------------------------------------------------

CIFLocationParser::NameSetContext::NameSetContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CIFLocationParser::NamesContext* CIFLocationParser::NameSetContext::names() {
  return getRuleContext<CIFLocationParser::NamesContext>(0);
}


size_t CIFLocationParser::NameSetContext::getRuleIndex() const {
  return CIFLocationParser::RuleNameSet;
}

antlrcpp::Any CIFLocationParser::NameSetContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitNameSet(this);
  else
    return visitor->visitChildren(this);
}

CIFLocationParser::NameSetContext* CIFLocationParser::nameSet() {
  NameSetContext *_localctx = _tracker.createInstance<NameSetContext>(_ctx, getState());
  enterRule(_localctx, 86, CIFLocationParser::RuleNameSet);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(610);
    match(CIFLocationParser::T__41);
    setState(611);
    names();
    setState(612);
    match(CIFLocationParser::T__42);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NamesContext ------------------------------------------------------------------

CIFLocationParser::NamesContext::NamesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CIFLocationParser::NameContext *> CIFLocationParser::NamesContext::name() {
  return getRuleContexts<CIFLocationParser::NameContext>();
}

CIFLocationParser::NameContext* CIFLocationParser::NamesContext::name(size_t i) {
  return getRuleContext<CIFLocationParser::NameContext>(i);
}


size_t CIFLocationParser::NamesContext::getRuleIndex() const {
  return CIFLocationParser::RuleNames;
}

antlrcpp::Any CIFLocationParser::NamesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitNames(this);
  else
    return visitor->visitChildren(this);
}

CIFLocationParser::NamesContext* CIFLocationParser::names() {
  NamesContext *_localctx = _tracker.createInstance<NamesContext>(_ctx, getState());
  enterRule(_localctx, 88, CIFLocationParser::RuleNames);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(614);
    name();
    setState(619);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CIFLocationParser::T__12) {
      setState(615);
      match(CIFLocationParser::T__12);
      setState(616);
      name();
      setState(621);
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

//----------------- NameContext ------------------------------------------------------------------

CIFLocationParser::NameContext::NameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CIFLocationParser::IdentifierContext* CIFLocationParser::NameContext::identifier() {
  return getRuleContext<CIFLocationParser::IdentifierContext>(0);
}

tree::TerminalNode* CIFLocationParser::NameContext::RELATIVENAME() {
  return getToken(CIFLocationParser::RELATIVENAME, 0);
}

tree::TerminalNode* CIFLocationParser::NameContext::ABSOLUTENAME() {
  return getToken(CIFLocationParser::ABSOLUTENAME, 0);
}

tree::TerminalNode* CIFLocationParser::NameContext::ROOTNAME() {
  return getToken(CIFLocationParser::ROOTNAME, 0);
}


size_t CIFLocationParser::NameContext::getRuleIndex() const {
  return CIFLocationParser::RuleName;
}

antlrcpp::Any CIFLocationParser::NameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitName(this);
  else
    return visitor->visitChildren(this);
}

CIFLocationParser::NameContext* CIFLocationParser::name() {
  NameContext *_localctx = _tracker.createInstance<NameContext>(_ctx, getState());
  enterRule(_localctx, 90, CIFLocationParser::RuleName);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(626);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CIFLocationParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(622);
        identifier();
        break;
      }

      case CIFLocationParser::RELATIVENAME: {
        enterOuterAlt(_localctx, 2);
        setState(623);
        match(CIFLocationParser::RELATIVENAME);
        break;
      }

      case CIFLocationParser::ABSOLUTENAME: {
        enterOuterAlt(_localctx, 3);
        setState(624);
        match(CIFLocationParser::ABSOLUTENAME);
        break;
      }

      case CIFLocationParser::ROOTNAME: {
        enterOuterAlt(_localctx, 4);
        setState(625);
        match(CIFLocationParser::ROOTNAME);
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

//----------------- OptSupKindContext ------------------------------------------------------------------

CIFLocationParser::OptSupKindContext::OptSupKindContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CIFLocationParser::SupKindContext* CIFLocationParser::OptSupKindContext::supKind() {
  return getRuleContext<CIFLocationParser::SupKindContext>(0);
}


size_t CIFLocationParser::OptSupKindContext::getRuleIndex() const {
  return CIFLocationParser::RuleOptSupKind;
}

antlrcpp::Any CIFLocationParser::OptSupKindContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitOptSupKind(this);
  else
    return visitor->visitChildren(this);
}

CIFLocationParser::OptSupKindContext* CIFLocationParser::optSupKind() {
  OptSupKindContext *_localctx = _tracker.createInstance<OptSupKindContext>(_ctx, getState());
  enterRule(_localctx, 92, CIFLocationParser::RuleOptSupKind);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(629);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CIFLocationParser::T__59)
      | (1ULL << CIFLocationParser::T__60)
      | (1ULL << CIFLocationParser::T__61))) != 0)) {
      setState(628);
      supKind();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SupKindContext ------------------------------------------------------------------

CIFLocationParser::SupKindContext::SupKindContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CIFLocationParser::SupKindContext::getRuleIndex() const {
  return CIFLocationParser::RuleSupKind;
}

antlrcpp::Any CIFLocationParser::SupKindContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitSupKind(this);
  else
    return visitor->visitChildren(this);
}

CIFLocationParser::SupKindContext* CIFLocationParser::supKind() {
  SupKindContext *_localctx = _tracker.createInstance<SupKindContext>(_ctx, getState());
  enterRule(_localctx, 94, CIFLocationParser::RuleSupKind);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(631);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CIFLocationParser::T__59)
      | (1ULL << CIFLocationParser::T__60)
      | (1ULL << CIFLocationParser::T__61))) != 0))) {
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

//----------------- IdentifierContext ------------------------------------------------------------------

CIFLocationParser::IdentifierContext::IdentifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CIFLocationParser::IdentifierContext::IDENTIFIER() {
  return getToken(CIFLocationParser::IDENTIFIER, 0);
}


size_t CIFLocationParser::IdentifierContext::getRuleIndex() const {
  return CIFLocationParser::RuleIdentifier;
}

antlrcpp::Any CIFLocationParser::IdentifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitIdentifier(this);
  else
    return visitor->visitChildren(this);
}

CIFLocationParser::IdentifierContext* CIFLocationParser::identifier() {
  IdentifierContext *_localctx = _tracker.createInstance<IdentifierContext>(_ctx, getState());
  enterRule(_localctx, 96, CIFLocationParser::RuleIdentifier);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(633);
    match(CIFLocationParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StringTokenContext ------------------------------------------------------------------

CIFLocationParser::StringTokenContext::StringTokenContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CIFLocationParser::StringTokenContext::STRING() {
  return getToken(CIFLocationParser::STRING, 0);
}


size_t CIFLocationParser::StringTokenContext::getRuleIndex() const {
  return CIFLocationParser::RuleStringToken;
}

antlrcpp::Any CIFLocationParser::StringTokenContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitStringToken(this);
  else
    return visitor->visitChildren(this);
}

CIFLocationParser::StringTokenContext* CIFLocationParser::stringToken() {
  StringTokenContext *_localctx = _tracker.createInstance<StringTokenContext>(_ctx, getState());
  enterRule(_localctx, 98, CIFLocationParser::RuleStringToken);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(635);
    match(CIFLocationParser::STRING);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StdLibFunctionContext ------------------------------------------------------------------

CIFLocationParser::StdLibFunctionContext::StdLibFunctionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CIFLocationParser::StdLibFunctionContext::getRuleIndex() const {
  return CIFLocationParser::RuleStdLibFunction;
}

antlrcpp::Any CIFLocationParser::StdLibFunctionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CIFLocationVisitor*>(visitor))
    return parserVisitor->visitStdLibFunction(this);
  else
    return visitor->visitChildren(this);
}

CIFLocationParser::StdLibFunctionContext* CIFLocationParser::stdLibFunction() {
  StdLibFunctionContext *_localctx = _tracker.createInstance<StdLibFunctionContext>(_ctx, getState());
  enterRule(_localctx, 100, CIFLocationParser::RuleStdLibFunction);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(637);
    _la = _input->LA(1);
    if (!(((((_la - 63) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 63)) & ((1ULL << (CIFLocationParser::T__62 - 63))
      | (1ULL << (CIFLocationParser::T__63 - 63))
      | (1ULL << (CIFLocationParser::T__64 - 63))
      | (1ULL << (CIFLocationParser::T__65 - 63))
      | (1ULL << (CIFLocationParser::T__66 - 63))
      | (1ULL << (CIFLocationParser::T__67 - 63))
      | (1ULL << (CIFLocationParser::T__68 - 63))
      | (1ULL << (CIFLocationParser::T__69 - 63))
      | (1ULL << (CIFLocationParser::T__70 - 63))
      | (1ULL << (CIFLocationParser::T__71 - 63))
      | (1ULL << (CIFLocationParser::T__72 - 63))
      | (1ULL << (CIFLocationParser::T__73 - 63))
      | (1ULL << (CIFLocationParser::T__74 - 63))
      | (1ULL << (CIFLocationParser::T__75 - 63))
      | (1ULL << (CIFLocationParser::T__76 - 63))
      | (1ULL << (CIFLocationParser::T__77 - 63))
      | (1ULL << (CIFLocationParser::T__78 - 63))
      | (1ULL << (CIFLocationParser::T__79 - 63))
      | (1ULL << (CIFLocationParser::T__80 - 63))
      | (1ULL << (CIFLocationParser::T__81 - 63))
      | (1ULL << (CIFLocationParser::T__82 - 63))
      | (1ULL << (CIFLocationParser::T__83 - 63))
      | (1ULL << (CIFLocationParser::T__84 - 63))
      | (1ULL << (CIFLocationParser::T__85 - 63))
      | (1ULL << (CIFLocationParser::T__86 - 63))
      | (1ULL << (CIFLocationParser::T__87 - 63))
      | (1ULL << (CIFLocationParser::T__88 - 63))
      | (1ULL << (CIFLocationParser::T__89 - 63))
      | (1ULL << (CIFLocationParser::T__90 - 63))
      | (1ULL << (CIFLocationParser::T__91 - 63))
      | (1ULL << (CIFLocationParser::T__92 - 63))
      | (1ULL << (CIFLocationParser::T__93 - 63)))) != 0))) {
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

// Static vars and initialization.
std::vector<dfa::DFA> CIFLocationParser::_decisionToDFA;
atn::PredictionContextCache CIFLocationParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN CIFLocationParser::_atn;
std::vector<uint16_t> CIFLocationParser::_serializedATN;

std::vector<std::string> CIFLocationParser::_ruleNames = {
  "locations", "location", "locationElements", "locationElement", "coreEdge", 
  "optEdgeGuard", "optEdgeUrgent", "optEdgeUpdate", "edgeEvents", "edgeEvent", 
  "invariantDecls", "invariants", "invariant", "updates", "update", "optElifUpdates", 
  "optElseUpdate", "adressables", "adressable", "projections", "projection", 
  "expressions", "optExpression", "expression", "equations", "equation", 
  "orExpression", "andExpression", "compareExpression", "addExpression", 
  "mulExpression", "unaryExpression", "funcExpression", "expressionFactor", 
  "nonEmptySetExpression", "dictPairs", "optElifExprs", "switchBody", "switchCases", 
  "types", "type", "fields", "field", "nameSet", "names", "name", "optSupKind", 
  "supKind", "identifier", "stringToken", "stdLibFunction"
};

std::vector<std::string> CIFLocationParser::_literalNames = {
  "", "'location'", "';'", "':'", "'initial'", "'equation'", "'marked'", 
  "'urgent'", "'edge'", "'goto'", "'when'", "'now'", "'do'", "','", "'tau'", 
  "'!'", "'?'", "'invariant'", "'needs'", "'disables'", "':='", "'if'", 
  "'end'", "'elif'", "'else'", "'('", "')'", "'['", "']'", "'=>'", "'<=>'", 
  "'''", "'='", "'or'", "'and'", "'-'", "'+'", "'not'", "'sample'", "'true'", 
  "'false'", "'time'", "'{'", "'}'", "'<'", "'>'", "'switch'", "'self'", 
  "'case'", "'bool'", "'int'", "'..'", "'real'", "'string'", "'list'", "'set'", 
  "'dict'", "'tuple'", "'func'", "'dist'", "'plant'", "'requirement'", "'supervisor'", 
  "'acosh'", "'acos'", "'asinh'", "'asin'", "'atanh'", "'cosh'", "'cos'", 
  "'sinh'", "'sin'", "'tanh'", "'tan'", "'abs'", "'cbrt'", "'ceil'", "'del'", 
  "'empty'", "'exp'", "'floor'", "'fmt'", "'ln'", "'log'", "'max'", "'min'", 
  "'pop'", "'pow'", "'round'", "'scale'", "'sign'", "'size'", "'sqrt'", 
  "'bernoulli'", "'beta'"
};

std::vector<std::string> CIFLocationParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "MULOP", "ADDOP", "COMPOP", "NUMBER", "REALNUMBER", 
  "STRING", "IDENTIFIER", "RELATIVENAME", "ABSOLUTENAME", "ROOTNAME", "WS"
};

dfa::Vocabulary CIFLocationParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> CIFLocationParser::_tokenNames;

CIFLocationParser::Initializer::Initializer() {
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
    0x3, 0x6b, 0x282, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
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
    0x25, 0x4, 0x26, 0x9, 0x26, 0x4, 0x27, 0x9, 0x27, 0x4, 0x28, 0x9, 0x28, 
    0x4, 0x29, 0x9, 0x29, 0x4, 0x2a, 0x9, 0x2a, 0x4, 0x2b, 0x9, 0x2b, 0x4, 
    0x2c, 0x9, 0x2c, 0x4, 0x2d, 0x9, 0x2d, 0x4, 0x2e, 0x9, 0x2e, 0x4, 0x2f, 
    0x9, 0x2f, 0x4, 0x30, 0x9, 0x30, 0x4, 0x31, 0x9, 0x31, 0x4, 0x32, 0x9, 
    0x32, 0x4, 0x33, 0x9, 0x33, 0x4, 0x34, 0x9, 0x34, 0x3, 0x2, 0x6, 0x2, 
    0x6a, 0xa, 0x2, 0xd, 0x2, 0xe, 0x2, 0x6b, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x7c, 0xa, 0x3, 0x3, 
    0x4, 0x6, 0x4, 0x7f, 0xa, 0x4, 0xd, 0x4, 0xe, 0x4, 0x80, 0x3, 0x5, 0x3, 
    0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 
    0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 
    0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 
    0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x5, 
    0x5, 0xa0, 0xa, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 
    0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 
    0x3, 0x6, 0x3, 0x6, 0x5, 0x6, 0xb0, 0xa, 0x6, 0x3, 0x7, 0x3, 0x7, 0x5, 
    0x7, 0xb4, 0xa, 0x7, 0x3, 0x8, 0x5, 0x8, 0xb7, 0xa, 0x8, 0x3, 0x9, 0x3, 
    0x9, 0x5, 0x9, 0xbb, 0xa, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x7, 0xa, 
    0xc0, 0xa, 0xa, 0xc, 0xa, 0xe, 0xa, 0xc3, 0xb, 0xa, 0x3, 0xb, 0x3, 0xb, 
    0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 
    0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x5, 0xb, 0xd1, 0xa, 0xb, 0x3, 0xc, 0x3, 
    0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 
    0xc, 0x5, 0xc, 0xdc, 0xa, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x7, 0xd, 
    0xe1, 0xa, 0xd, 0xc, 0xd, 0xe, 0xd, 0xe4, 0xb, 0xd, 0x3, 0xe, 0x3, 0xe, 
    0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 
    0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 
    0x3, 0xe, 0x5, 0xe, 0xf7, 0xa, 0xe, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x7, 
    0xf, 0xfc, 0xa, 0xf, 0xc, 0xf, 0xe, 0xf, 0xff, 0xb, 0xf, 0x3, 0x10, 
    0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 
    0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x5, 0x10, 0x10d, 
    0xa, 0x10, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x7, 
    0x11, 0x114, 0xa, 0x11, 0xc, 0x11, 0xe, 0x11, 0x117, 0xb, 0x11, 0x3, 
    0x12, 0x3, 0x12, 0x5, 0x12, 0x11b, 0xa, 0x12, 0x3, 0x13, 0x3, 0x13, 
    0x3, 0x13, 0x7, 0x13, 0x120, 0xa, 0x13, 0xc, 0x13, 0xe, 0x13, 0x123, 
    0xb, 0x13, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 
    0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x5, 0x14, 0x12f, 
    0xa, 0x14, 0x3, 0x15, 0x7, 0x15, 0x132, 0xa, 0x15, 0xc, 0x15, 0xe, 0x15, 
    0x135, 0xb, 0x15, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x17, 
    0x3, 0x17, 0x3, 0x17, 0x7, 0x17, 0x13e, 0xa, 0x17, 0xc, 0x17, 0xe, 0x17, 
    0x141, 0xb, 0x17, 0x3, 0x18, 0x5, 0x18, 0x144, 0xa, 0x18, 0x3, 0x19, 
    0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 
    0x19, 0x3, 0x19, 0x5, 0x19, 0x14f, 0xa, 0x19, 0x3, 0x1a, 0x3, 0x1a, 
    0x3, 0x1a, 0x7, 0x1a, 0x154, 0xa, 0x1a, 0xc, 0x1a, 0xe, 0x1a, 0x157, 
    0xb, 0x1a, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 
    0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x5, 0x1b, 0x162, 0xa, 0x1b, 
    0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x7, 0x1c, 0x167, 0xa, 0x1c, 0xc, 0x1c, 
    0xe, 0x1c, 0x16a, 0xb, 0x1c, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x7, 0x1d, 
    0x16f, 0xa, 0x1d, 0xc, 0x1d, 0xe, 0x1d, 0x172, 0xb, 0x1d, 0x3, 0x1e, 
    0x3, 0x1e, 0x3, 0x1e, 0x7, 0x1e, 0x177, 0xa, 0x1e, 0xc, 0x1e, 0xe, 0x1e, 
    0x17a, 0xb, 0x1e, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x7, 0x1f, 0x17f, 
    0xa, 0x1f, 0xc, 0x1f, 0xe, 0x1f, 0x182, 0xb, 0x1f, 0x3, 0x20, 0x3, 0x20, 
    0x3, 0x20, 0x7, 0x20, 0x187, 0xa, 0x20, 0xc, 0x20, 0xe, 0x20, 0x18a, 
    0xb, 0x20, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x3, 
    0x21, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x5, 0x21, 0x195, 0xa, 0x21, 
    0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 
    0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x5, 0x22, 0x1a1, 0xa, 0x22, 
    0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 
    0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 
    0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x7, 0x22, 0x1b3, 0xa, 0x22, 0xc, 0x22, 
    0xe, 0x22, 0x1b6, 0xb, 0x22, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 
    0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 
    0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 
    0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 
    0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 
    0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 
    0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 
    0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 
    0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x5, 0x23, 
    0x1ef, 0xa, 0x23, 0x3, 0x24, 0x3, 0x24, 0x3, 0x24, 0x3, 0x24, 0x3, 0x25, 
    0x3, 0x25, 0x3, 0x25, 0x3, 0x25, 0x3, 0x25, 0x3, 0x25, 0x3, 0x25, 0x3, 
    0x25, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x7, 0x26, 
    0x202, 0xa, 0x26, 0xc, 0x26, 0xe, 0x26, 0x205, 0xb, 0x26, 0x3, 0x27, 
    0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x5, 
    0x27, 0x20e, 0xa, 0x27, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 
    0x3, 0x28, 0x6, 0x28, 0x215, 0xa, 0x28, 0xd, 0x28, 0xe, 0x28, 0x216, 
    0x3, 0x29, 0x3, 0x29, 0x3, 0x29, 0x7, 0x29, 0x21c, 0xa, 0x29, 0xc, 0x29, 
    0xe, 0x29, 0x21f, 0xb, 0x29, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 
    0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 
    0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 
    0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 
    0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 
    0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 
    0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 
    0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 
    0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x5, 0x2a, 
    0x258, 0xa, 0x2a, 0x3, 0x2b, 0x3, 0x2b, 0x3, 0x2b, 0x7, 0x2b, 0x25d, 
    0xa, 0x2b, 0xc, 0x2b, 0xe, 0x2b, 0x260, 0xb, 0x2b, 0x3, 0x2c, 0x3, 0x2c, 
    0x3, 0x2c, 0x3, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x3, 0x2e, 0x3, 
    0x2e, 0x3, 0x2e, 0x7, 0x2e, 0x26c, 0xa, 0x2e, 0xc, 0x2e, 0xe, 0x2e, 
    0x26f, 0xb, 0x2e, 0x3, 0x2f, 0x3, 0x2f, 0x3, 0x2f, 0x3, 0x2f, 0x5, 0x2f, 
    0x275, 0xa, 0x2f, 0x3, 0x30, 0x5, 0x30, 0x278, 0xa, 0x30, 0x3, 0x31, 
    0x3, 0x31, 0x3, 0x32, 0x3, 0x32, 0x3, 0x33, 0x3, 0x33, 0x3, 0x34, 0x3, 
    0x34, 0x3, 0x34, 0x2, 0x2, 0x35, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 
    0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x24, 0x26, 
    0x28, 0x2a, 0x2c, 0x2e, 0x30, 0x32, 0x34, 0x36, 0x38, 0x3a, 0x3c, 0x3e, 
    0x40, 0x42, 0x44, 0x46, 0x48, 0x4a, 0x4c, 0x4e, 0x50, 0x52, 0x54, 0x56, 
    0x58, 0x5a, 0x5c, 0x5e, 0x60, 0x62, 0x64, 0x66, 0x2, 0x4, 0x3, 0x2, 
    0x3e, 0x40, 0x3, 0x2, 0x41, 0x60, 0x2, 0x2b5, 0x2, 0x69, 0x3, 0x2, 0x2, 
    0x2, 0x4, 0x7b, 0x3, 0x2, 0x2, 0x2, 0x6, 0x7e, 0x3, 0x2, 0x2, 0x2, 0x8, 
    0x9f, 0x3, 0x2, 0x2, 0x2, 0xa, 0xaf, 0x3, 0x2, 0x2, 0x2, 0xc, 0xb3, 
    0x3, 0x2, 0x2, 0x2, 0xe, 0xb6, 0x3, 0x2, 0x2, 0x2, 0x10, 0xba, 0x3, 
    0x2, 0x2, 0x2, 0x12, 0xbc, 0x3, 0x2, 0x2, 0x2, 0x14, 0xd0, 0x3, 0x2, 
    0x2, 0x2, 0x16, 0xdb, 0x3, 0x2, 0x2, 0x2, 0x18, 0xdd, 0x3, 0x2, 0x2, 
    0x2, 0x1a, 0xf6, 0x3, 0x2, 0x2, 0x2, 0x1c, 0xf8, 0x3, 0x2, 0x2, 0x2, 
    0x1e, 0x10c, 0x3, 0x2, 0x2, 0x2, 0x20, 0x115, 0x3, 0x2, 0x2, 0x2, 0x22, 
    0x11a, 0x3, 0x2, 0x2, 0x2, 0x24, 0x11c, 0x3, 0x2, 0x2, 0x2, 0x26, 0x12e, 
    0x3, 0x2, 0x2, 0x2, 0x28, 0x133, 0x3, 0x2, 0x2, 0x2, 0x2a, 0x136, 0x3, 
    0x2, 0x2, 0x2, 0x2c, 0x13a, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x143, 0x3, 0x2, 
    0x2, 0x2, 0x30, 0x14e, 0x3, 0x2, 0x2, 0x2, 0x32, 0x150, 0x3, 0x2, 0x2, 
    0x2, 0x34, 0x161, 0x3, 0x2, 0x2, 0x2, 0x36, 0x163, 0x3, 0x2, 0x2, 0x2, 
    0x38, 0x16b, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x173, 0x3, 0x2, 0x2, 0x2, 0x3c, 
    0x17b, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x183, 0x3, 0x2, 0x2, 0x2, 0x40, 0x194, 
    0x3, 0x2, 0x2, 0x2, 0x42, 0x1a0, 0x3, 0x2, 0x2, 0x2, 0x44, 0x1ee, 0x3, 
    0x2, 0x2, 0x2, 0x46, 0x1f0, 0x3, 0x2, 0x2, 0x2, 0x48, 0x1f4, 0x3, 0x2, 
    0x2, 0x2, 0x4a, 0x203, 0x3, 0x2, 0x2, 0x2, 0x4c, 0x20d, 0x3, 0x2, 0x2, 
    0x2, 0x4e, 0x214, 0x3, 0x2, 0x2, 0x2, 0x50, 0x218, 0x3, 0x2, 0x2, 0x2, 
    0x52, 0x257, 0x3, 0x2, 0x2, 0x2, 0x54, 0x259, 0x3, 0x2, 0x2, 0x2, 0x56, 
    0x261, 0x3, 0x2, 0x2, 0x2, 0x58, 0x264, 0x3, 0x2, 0x2, 0x2, 0x5a, 0x268, 
    0x3, 0x2, 0x2, 0x2, 0x5c, 0x274, 0x3, 0x2, 0x2, 0x2, 0x5e, 0x277, 0x3, 
    0x2, 0x2, 0x2, 0x60, 0x279, 0x3, 0x2, 0x2, 0x2, 0x62, 0x27b, 0x3, 0x2, 
    0x2, 0x2, 0x64, 0x27d, 0x3, 0x2, 0x2, 0x2, 0x66, 0x27f, 0x3, 0x2, 0x2, 
    0x2, 0x68, 0x6a, 0x5, 0x4, 0x3, 0x2, 0x69, 0x68, 0x3, 0x2, 0x2, 0x2, 
    0x6a, 0x6b, 0x3, 0x2, 0x2, 0x2, 0x6b, 0x69, 0x3, 0x2, 0x2, 0x2, 0x6b, 
    0x6c, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x3, 0x3, 0x2, 0x2, 0x2, 0x6d, 0x6e, 
    0x7, 0x3, 0x2, 0x2, 0x6e, 0x7c, 0x7, 0x4, 0x2, 0x2, 0x6f, 0x70, 0x7, 
    0x3, 0x2, 0x2, 0x70, 0x71, 0x5, 0x62, 0x32, 0x2, 0x71, 0x72, 0x7, 0x4, 
    0x2, 0x2, 0x72, 0x7c, 0x3, 0x2, 0x2, 0x2, 0x73, 0x74, 0x7, 0x3, 0x2, 
    0x2, 0x74, 0x75, 0x7, 0x5, 0x2, 0x2, 0x75, 0x7c, 0x5, 0x6, 0x4, 0x2, 
    0x76, 0x77, 0x7, 0x3, 0x2, 0x2, 0x77, 0x78, 0x5, 0x62, 0x32, 0x2, 0x78, 
    0x79, 0x7, 0x5, 0x2, 0x2, 0x79, 0x7a, 0x5, 0x6, 0x4, 0x2, 0x7a, 0x7c, 
    0x3, 0x2, 0x2, 0x2, 0x7b, 0x6d, 0x3, 0x2, 0x2, 0x2, 0x7b, 0x6f, 0x3, 
    0x2, 0x2, 0x2, 0x7b, 0x73, 0x3, 0x2, 0x2, 0x2, 0x7b, 0x76, 0x3, 0x2, 
    0x2, 0x2, 0x7c, 0x5, 0x3, 0x2, 0x2, 0x2, 0x7d, 0x7f, 0x5, 0x8, 0x5, 
    0x2, 0x7e, 0x7d, 0x3, 0x2, 0x2, 0x2, 0x7f, 0x80, 0x3, 0x2, 0x2, 0x2, 
    0x80, 0x7e, 0x3, 0x2, 0x2, 0x2, 0x80, 0x81, 0x3, 0x2, 0x2, 0x2, 0x81, 
    0x7, 0x3, 0x2, 0x2, 0x2, 0x82, 0x83, 0x7, 0x6, 0x2, 0x2, 0x83, 0xa0, 
    0x7, 0x4, 0x2, 0x2, 0x84, 0x85, 0x7, 0x6, 0x2, 0x2, 0x85, 0x86, 0x5, 
    0x2c, 0x17, 0x2, 0x86, 0x87, 0x7, 0x4, 0x2, 0x2, 0x87, 0xa0, 0x3, 0x2, 
    0x2, 0x2, 0x88, 0xa0, 0x5, 0x16, 0xc, 0x2, 0x89, 0x8a, 0x7, 0x7, 0x2, 
    0x2, 0x8a, 0x8b, 0x5, 0x32, 0x1a, 0x2, 0x8b, 0x8c, 0x7, 0x4, 0x2, 0x2, 
    0x8c, 0xa0, 0x3, 0x2, 0x2, 0x2, 0x8d, 0x8e, 0x7, 0x8, 0x2, 0x2, 0x8e, 
    0xa0, 0x7, 0x4, 0x2, 0x2, 0x8f, 0x90, 0x7, 0x8, 0x2, 0x2, 0x90, 0x91, 
    0x5, 0x2c, 0x17, 0x2, 0x91, 0x92, 0x7, 0x4, 0x2, 0x2, 0x92, 0xa0, 0x3, 
    0x2, 0x2, 0x2, 0x93, 0x94, 0x7, 0x9, 0x2, 0x2, 0x94, 0xa0, 0x7, 0x4, 
    0x2, 0x2, 0x95, 0x96, 0x7, 0xa, 0x2, 0x2, 0x96, 0x97, 0x5, 0xa, 0x6, 
    0x2, 0x97, 0x98, 0x7, 0xb, 0x2, 0x2, 0x98, 0x99, 0x5, 0x62, 0x32, 0x2, 
    0x99, 0x9a, 0x7, 0x4, 0x2, 0x2, 0x9a, 0xa0, 0x3, 0x2, 0x2, 0x2, 0x9b, 
    0x9c, 0x7, 0xa, 0x2, 0x2, 0x9c, 0x9d, 0x5, 0xa, 0x6, 0x2, 0x9d, 0x9e, 
    0x7, 0x4, 0x2, 0x2, 0x9e, 0xa0, 0x3, 0x2, 0x2, 0x2, 0x9f, 0x82, 0x3, 
    0x2, 0x2, 0x2, 0x9f, 0x84, 0x3, 0x2, 0x2, 0x2, 0x9f, 0x88, 0x3, 0x2, 
    0x2, 0x2, 0x9f, 0x89, 0x3, 0x2, 0x2, 0x2, 0x9f, 0x8d, 0x3, 0x2, 0x2, 
    0x2, 0x9f, 0x8f, 0x3, 0x2, 0x2, 0x2, 0x9f, 0x93, 0x3, 0x2, 0x2, 0x2, 
    0x9f, 0x95, 0x3, 0x2, 0x2, 0x2, 0x9f, 0x9b, 0x3, 0x2, 0x2, 0x2, 0xa0, 
    0x9, 0x3, 0x2, 0x2, 0x2, 0xa1, 0xa2, 0x5, 0x12, 0xa, 0x2, 0xa2, 0xa3, 
    0x5, 0xc, 0x7, 0x2, 0xa3, 0xa4, 0x5, 0xe, 0x8, 0x2, 0xa4, 0xa5, 0x5, 
    0x10, 0x9, 0x2, 0xa5, 0xb0, 0x3, 0x2, 0x2, 0x2, 0xa6, 0xa7, 0x7, 0xc, 
    0x2, 0x2, 0xa7, 0xa8, 0x5, 0x2c, 0x17, 0x2, 0xa8, 0xa9, 0x5, 0xe, 0x8, 
    0x2, 0xa9, 0xaa, 0x5, 0x10, 0x9, 0x2, 0xaa, 0xb0, 0x3, 0x2, 0x2, 0x2, 
    0xab, 0xac, 0x7, 0xd, 0x2, 0x2, 0xac, 0xb0, 0x5, 0x10, 0x9, 0x2, 0xad, 
    0xae, 0x7, 0xe, 0x2, 0x2, 0xae, 0xb0, 0x5, 0x1c, 0xf, 0x2, 0xaf, 0xa1, 
    0x3, 0x2, 0x2, 0x2, 0xaf, 0xa6, 0x3, 0x2, 0x2, 0x2, 0xaf, 0xab, 0x3, 
    0x2, 0x2, 0x2, 0xaf, 0xad, 0x3, 0x2, 0x2, 0x2, 0xb0, 0xb, 0x3, 0x2, 
    0x2, 0x2, 0xb1, 0xb2, 0x7, 0xc, 0x2, 0x2, 0xb2, 0xb4, 0x5, 0x2c, 0x17, 
    0x2, 0xb3, 0xb1, 0x3, 0x2, 0x2, 0x2, 0xb3, 0xb4, 0x3, 0x2, 0x2, 0x2, 
    0xb4, 0xd, 0x3, 0x2, 0x2, 0x2, 0xb5, 0xb7, 0x7, 0xd, 0x2, 0x2, 0xb6, 
    0xb5, 0x3, 0x2, 0x2, 0x2, 0xb6, 0xb7, 0x3, 0x2, 0x2, 0x2, 0xb7, 0xf, 
    0x3, 0x2, 0x2, 0x2, 0xb8, 0xb9, 0x7, 0xe, 0x2, 0x2, 0xb9, 0xbb, 0x5, 
    0x1c, 0xf, 0x2, 0xba, 0xb8, 0x3, 0x2, 0x2, 0x2, 0xba, 0xbb, 0x3, 0x2, 
    0x2, 0x2, 0xbb, 0x11, 0x3, 0x2, 0x2, 0x2, 0xbc, 0xc1, 0x5, 0x14, 0xb, 
    0x2, 0xbd, 0xbe, 0x7, 0xf, 0x2, 0x2, 0xbe, 0xc0, 0x5, 0x14, 0xb, 0x2, 
    0xbf, 0xbd, 0x3, 0x2, 0x2, 0x2, 0xc0, 0xc3, 0x3, 0x2, 0x2, 0x2, 0xc1, 
    0xbf, 0x3, 0x2, 0x2, 0x2, 0xc1, 0xc2, 0x3, 0x2, 0x2, 0x2, 0xc2, 0x13, 
    0x3, 0x2, 0x2, 0x2, 0xc3, 0xc1, 0x3, 0x2, 0x2, 0x2, 0xc4, 0xd1, 0x7, 
    0x10, 0x2, 0x2, 0xc5, 0xd1, 0x5, 0x5c, 0x2f, 0x2, 0xc6, 0xc7, 0x5, 0x5c, 
    0x2f, 0x2, 0xc7, 0xc8, 0x7, 0x11, 0x2, 0x2, 0xc8, 0xd1, 0x3, 0x2, 0x2, 
    0x2, 0xc9, 0xca, 0x5, 0x5c, 0x2f, 0x2, 0xca, 0xcb, 0x7, 0x11, 0x2, 0x2, 
    0xcb, 0xcc, 0x5, 0x30, 0x19, 0x2, 0xcc, 0xd1, 0x3, 0x2, 0x2, 0x2, 0xcd, 
    0xce, 0x5, 0x5c, 0x2f, 0x2, 0xce, 0xcf, 0x7, 0x12, 0x2, 0x2, 0xcf, 0xd1, 
    0x3, 0x2, 0x2, 0x2, 0xd0, 0xc4, 0x3, 0x2, 0x2, 0x2, 0xd0, 0xc5, 0x3, 
    0x2, 0x2, 0x2, 0xd0, 0xc6, 0x3, 0x2, 0x2, 0x2, 0xd0, 0xc9, 0x3, 0x2, 
    0x2, 0x2, 0xd0, 0xcd, 0x3, 0x2, 0x2, 0x2, 0xd1, 0x15, 0x3, 0x2, 0x2, 
    0x2, 0xd2, 0xd3, 0x5, 0x5e, 0x30, 0x2, 0xd3, 0xd4, 0x7, 0x13, 0x2, 0x2, 
    0xd4, 0xd5, 0x5, 0x18, 0xd, 0x2, 0xd5, 0xd6, 0x7, 0x4, 0x2, 0x2, 0xd6, 
    0xdc, 0x3, 0x2, 0x2, 0x2, 0xd7, 0xd8, 0x5, 0x60, 0x31, 0x2, 0xd8, 0xd9, 
    0x5, 0x18, 0xd, 0x2, 0xd9, 0xda, 0x7, 0x4, 0x2, 0x2, 0xda, 0xdc, 0x3, 
    0x2, 0x2, 0x2, 0xdb, 0xd2, 0x3, 0x2, 0x2, 0x2, 0xdb, 0xd7, 0x3, 0x2, 
    0x2, 0x2, 0xdc, 0x17, 0x3, 0x2, 0x2, 0x2, 0xdd, 0xe2, 0x5, 0x1a, 0xe, 
    0x2, 0xde, 0xdf, 0x7, 0xf, 0x2, 0x2, 0xdf, 0xe1, 0x5, 0x1a, 0xe, 0x2, 
    0xe0, 0xde, 0x3, 0x2, 0x2, 0x2, 0xe1, 0xe4, 0x3, 0x2, 0x2, 0x2, 0xe2, 
    0xe0, 0x3, 0x2, 0x2, 0x2, 0xe2, 0xe3, 0x3, 0x2, 0x2, 0x2, 0xe3, 0x19, 
    0x3, 0x2, 0x2, 0x2, 0xe4, 0xe2, 0x3, 0x2, 0x2, 0x2, 0xe5, 0xf7, 0x5, 
    0x30, 0x19, 0x2, 0xe6, 0xe7, 0x5, 0x5c, 0x2f, 0x2, 0xe7, 0xe8, 0x7, 
    0x14, 0x2, 0x2, 0xe8, 0xe9, 0x5, 0x30, 0x19, 0x2, 0xe9, 0xf7, 0x3, 0x2, 
    0x2, 0x2, 0xea, 0xeb, 0x5, 0x46, 0x24, 0x2, 0xeb, 0xec, 0x7, 0x14, 0x2, 
    0x2, 0xec, 0xed, 0x5, 0x30, 0x19, 0x2, 0xed, 0xf7, 0x3, 0x2, 0x2, 0x2, 
    0xee, 0xef, 0x5, 0x30, 0x19, 0x2, 0xef, 0xf0, 0x7, 0x15, 0x2, 0x2, 0xf0, 
    0xf1, 0x5, 0x5c, 0x2f, 0x2, 0xf1, 0xf7, 0x3, 0x2, 0x2, 0x2, 0xf2, 0xf3, 
    0x5, 0x30, 0x19, 0x2, 0xf3, 0xf4, 0x7, 0x15, 0x2, 0x2, 0xf4, 0xf5, 0x5, 
    0x58, 0x2d, 0x2, 0xf5, 0xf7, 0x3, 0x2, 0x2, 0x2, 0xf6, 0xe5, 0x3, 0x2, 
    0x2, 0x2, 0xf6, 0xe6, 0x3, 0x2, 0x2, 0x2, 0xf6, 0xea, 0x3, 0x2, 0x2, 
    0x2, 0xf6, 0xee, 0x3, 0x2, 0x2, 0x2, 0xf6, 0xf2, 0x3, 0x2, 0x2, 0x2, 
    0xf7, 0x1b, 0x3, 0x2, 0x2, 0x2, 0xf8, 0xfd, 0x5, 0x1e, 0x10, 0x2, 0xf9, 
    0xfa, 0x7, 0xf, 0x2, 0x2, 0xfa, 0xfc, 0x5, 0x1e, 0x10, 0x2, 0xfb, 0xf9, 
    0x3, 0x2, 0x2, 0x2, 0xfc, 0xff, 0x3, 0x2, 0x2, 0x2, 0xfd, 0xfb, 0x3, 
    0x2, 0x2, 0x2, 0xfd, 0xfe, 0x3, 0x2, 0x2, 0x2, 0xfe, 0x1d, 0x3, 0x2, 
    0x2, 0x2, 0xff, 0xfd, 0x3, 0x2, 0x2, 0x2, 0x100, 0x101, 0x5, 0x26, 0x14, 
    0x2, 0x101, 0x102, 0x7, 0x16, 0x2, 0x2, 0x102, 0x103, 0x5, 0x30, 0x19, 
    0x2, 0x103, 0x10d, 0x3, 0x2, 0x2, 0x2, 0x104, 0x105, 0x7, 0x17, 0x2, 
    0x2, 0x105, 0x106, 0x5, 0x2c, 0x17, 0x2, 0x106, 0x107, 0x7, 0x5, 0x2, 
    0x2, 0x107, 0x108, 0x5, 0x1c, 0xf, 0x2, 0x108, 0x109, 0x5, 0x20, 0x11, 
    0x2, 0x109, 0x10a, 0x5, 0x22, 0x12, 0x2, 0x10a, 0x10b, 0x7, 0x18, 0x2, 
    0x2, 0x10b, 0x10d, 0x3, 0x2, 0x2, 0x2, 0x10c, 0x100, 0x3, 0x2, 0x2, 
    0x2, 0x10c, 0x104, 0x3, 0x2, 0x2, 0x2, 0x10d, 0x1f, 0x3, 0x2, 0x2, 0x2, 
    0x10e, 0x10f, 0x7, 0x19, 0x2, 0x2, 0x10f, 0x110, 0x5, 0x2c, 0x17, 0x2, 
    0x110, 0x111, 0x7, 0x5, 0x2, 0x2, 0x111, 0x112, 0x5, 0x1c, 0xf, 0x2, 
    0x112, 0x114, 0x3, 0x2, 0x2, 0x2, 0x113, 0x10e, 0x3, 0x2, 0x2, 0x2, 
    0x114, 0x117, 0x3, 0x2, 0x2, 0x2, 0x115, 0x113, 0x3, 0x2, 0x2, 0x2, 
    0x115, 0x116, 0x3, 0x2, 0x2, 0x2, 0x116, 0x21, 0x3, 0x2, 0x2, 0x2, 0x117, 
    0x115, 0x3, 0x2, 0x2, 0x2, 0x118, 0x119, 0x7, 0x1a, 0x2, 0x2, 0x119, 
    0x11b, 0x5, 0x1e, 0x10, 0x2, 0x11a, 0x118, 0x3, 0x2, 0x2, 0x2, 0x11a, 
    0x11b, 0x3, 0x2, 0x2, 0x2, 0x11b, 0x23, 0x3, 0x2, 0x2, 0x2, 0x11c, 0x121, 
    0x5, 0x26, 0x14, 0x2, 0x11d, 0x11e, 0x7, 0xf, 0x2, 0x2, 0x11e, 0x120, 
    0x5, 0x26, 0x14, 0x2, 0x11f, 0x11d, 0x3, 0x2, 0x2, 0x2, 0x120, 0x123, 
    0x3, 0x2, 0x2, 0x2, 0x121, 0x11f, 0x3, 0x2, 0x2, 0x2, 0x121, 0x122, 
    0x3, 0x2, 0x2, 0x2, 0x122, 0x25, 0x3, 0x2, 0x2, 0x2, 0x123, 0x121, 0x3, 
    0x2, 0x2, 0x2, 0x124, 0x12f, 0x5, 0x62, 0x32, 0x2, 0x125, 0x126, 0x5, 
    0x62, 0x32, 0x2, 0x126, 0x127, 0x5, 0x28, 0x15, 0x2, 0x127, 0x12f, 0x3, 
    0x2, 0x2, 0x2, 0x128, 0x129, 0x7, 0x1b, 0x2, 0x2, 0x129, 0x12a, 0x5, 
    0x26, 0x14, 0x2, 0x12a, 0x12b, 0x7, 0xf, 0x2, 0x2, 0x12b, 0x12c, 0x5, 
    0x26, 0x14, 0x2, 0x12c, 0x12d, 0x7, 0x1c, 0x2, 0x2, 0x12d, 0x12f, 0x3, 
    0x2, 0x2, 0x2, 0x12e, 0x124, 0x3, 0x2, 0x2, 0x2, 0x12e, 0x125, 0x3, 
    0x2, 0x2, 0x2, 0x12e, 0x128, 0x3, 0x2, 0x2, 0x2, 0x12f, 0x27, 0x3, 0x2, 
    0x2, 0x2, 0x130, 0x132, 0x5, 0x2a, 0x16, 0x2, 0x131, 0x130, 0x3, 0x2, 
    0x2, 0x2, 0x132, 0x135, 0x3, 0x2, 0x2, 0x2, 0x133, 0x131, 0x3, 0x2, 
    0x2, 0x2, 0x133, 0x134, 0x3, 0x2, 0x2, 0x2, 0x134, 0x29, 0x3, 0x2, 0x2, 
    0x2, 0x135, 0x133, 0x3, 0x2, 0x2, 0x2, 0x136, 0x137, 0x7, 0x1d, 0x2, 
    0x2, 0x137, 0x138, 0x5, 0x30, 0x19, 0x2, 0x138, 0x139, 0x7, 0x1e, 0x2, 
    0x2, 0x139, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x13a, 0x13f, 0x5, 0x30, 0x19, 
    0x2, 0x13b, 0x13c, 0x7, 0xf, 0x2, 0x2, 0x13c, 0x13e, 0x5, 0x30, 0x19, 
    0x2, 0x13d, 0x13b, 0x3, 0x2, 0x2, 0x2, 0x13e, 0x141, 0x3, 0x2, 0x2, 
    0x2, 0x13f, 0x13d, 0x3, 0x2, 0x2, 0x2, 0x13f, 0x140, 0x3, 0x2, 0x2, 
    0x2, 0x140, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x141, 0x13f, 0x3, 0x2, 0x2, 0x2, 
    0x142, 0x144, 0x5, 0x30, 0x19, 0x2, 0x143, 0x142, 0x3, 0x2, 0x2, 0x2, 
    0x143, 0x144, 0x3, 0x2, 0x2, 0x2, 0x144, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x145, 
    0x14f, 0x5, 0x36, 0x1c, 0x2, 0x146, 0x147, 0x5, 0x36, 0x1c, 0x2, 0x147, 
    0x148, 0x7, 0x1f, 0x2, 0x2, 0x148, 0x149, 0x5, 0x36, 0x1c, 0x2, 0x149, 
    0x14f, 0x3, 0x2, 0x2, 0x2, 0x14a, 0x14b, 0x5, 0x36, 0x1c, 0x2, 0x14b, 
    0x14c, 0x7, 0x20, 0x2, 0x2, 0x14c, 0x14d, 0x5, 0x36, 0x1c, 0x2, 0x14d, 
    0x14f, 0x3, 0x2, 0x2, 0x2, 0x14e, 0x145, 0x3, 0x2, 0x2, 0x2, 0x14e, 
    0x146, 0x3, 0x2, 0x2, 0x2, 0x14e, 0x14a, 0x3, 0x2, 0x2, 0x2, 0x14f, 
    0x31, 0x3, 0x2, 0x2, 0x2, 0x150, 0x155, 0x5, 0x34, 0x1b, 0x2, 0x151, 
    0x152, 0x7, 0xf, 0x2, 0x2, 0x152, 0x154, 0x5, 0x34, 0x1b, 0x2, 0x153, 
    0x151, 0x3, 0x2, 0x2, 0x2, 0x154, 0x157, 0x3, 0x2, 0x2, 0x2, 0x155, 
    0x153, 0x3, 0x2, 0x2, 0x2, 0x155, 0x156, 0x3, 0x2, 0x2, 0x2, 0x156, 
    0x33, 0x3, 0x2, 0x2, 0x2, 0x157, 0x155, 0x3, 0x2, 0x2, 0x2, 0x158, 0x159, 
    0x5, 0x62, 0x32, 0x2, 0x159, 0x15a, 0x7, 0x21, 0x2, 0x2, 0x15a, 0x15b, 
    0x7, 0x22, 0x2, 0x2, 0x15b, 0x15c, 0x5, 0x30, 0x19, 0x2, 0x15c, 0x162, 
    0x3, 0x2, 0x2, 0x2, 0x15d, 0x15e, 0x5, 0x62, 0x32, 0x2, 0x15e, 0x15f, 
    0x7, 0x22, 0x2, 0x2, 0x15f, 0x160, 0x5, 0x30, 0x19, 0x2, 0x160, 0x162, 
    0x3, 0x2, 0x2, 0x2, 0x161, 0x158, 0x3, 0x2, 0x2, 0x2, 0x161, 0x15d, 
    0x3, 0x2, 0x2, 0x2, 0x162, 0x35, 0x3, 0x2, 0x2, 0x2, 0x163, 0x168, 0x5, 
    0x38, 0x1d, 0x2, 0x164, 0x165, 0x7, 0x23, 0x2, 0x2, 0x165, 0x167, 0x5, 
    0x38, 0x1d, 0x2, 0x166, 0x164, 0x3, 0x2, 0x2, 0x2, 0x167, 0x16a, 0x3, 
    0x2, 0x2, 0x2, 0x168, 0x166, 0x3, 0x2, 0x2, 0x2, 0x168, 0x169, 0x3, 
    0x2, 0x2, 0x2, 0x169, 0x37, 0x3, 0x2, 0x2, 0x2, 0x16a, 0x168, 0x3, 0x2, 
    0x2, 0x2, 0x16b, 0x170, 0x5, 0x3a, 0x1e, 0x2, 0x16c, 0x16d, 0x7, 0x24, 
    0x2, 0x2, 0x16d, 0x16f, 0x5, 0x3a, 0x1e, 0x2, 0x16e, 0x16c, 0x3, 0x2, 
    0x2, 0x2, 0x16f, 0x172, 0x3, 0x2, 0x2, 0x2, 0x170, 0x16e, 0x3, 0x2, 
    0x2, 0x2, 0x170, 0x171, 0x3, 0x2, 0x2, 0x2, 0x171, 0x39, 0x3, 0x2, 0x2, 
    0x2, 0x172, 0x170, 0x3, 0x2, 0x2, 0x2, 0x173, 0x178, 0x5, 0x3c, 0x1f, 
    0x2, 0x174, 0x175, 0x7, 0x63, 0x2, 0x2, 0x175, 0x177, 0x5, 0x3c, 0x1f, 
    0x2, 0x176, 0x174, 0x3, 0x2, 0x2, 0x2, 0x177, 0x17a, 0x3, 0x2, 0x2, 
    0x2, 0x178, 0x176, 0x3, 0x2, 0x2, 0x2, 0x178, 0x179, 0x3, 0x2, 0x2, 
    0x2, 0x179, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x17a, 0x178, 0x3, 0x2, 0x2, 0x2, 
    0x17b, 0x180, 0x5, 0x3e, 0x20, 0x2, 0x17c, 0x17d, 0x7, 0x62, 0x2, 0x2, 
    0x17d, 0x17f, 0x5, 0x3e, 0x20, 0x2, 0x17e, 0x17c, 0x3, 0x2, 0x2, 0x2, 
    0x17f, 0x182, 0x3, 0x2, 0x2, 0x2, 0x180, 0x17e, 0x3, 0x2, 0x2, 0x2, 
    0x180, 0x181, 0x3, 0x2, 0x2, 0x2, 0x181, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x182, 
    0x180, 0x3, 0x2, 0x2, 0x2, 0x183, 0x188, 0x5, 0x40, 0x21, 0x2, 0x184, 
    0x185, 0x7, 0x61, 0x2, 0x2, 0x185, 0x187, 0x5, 0x40, 0x21, 0x2, 0x186, 
    0x184, 0x3, 0x2, 0x2, 0x2, 0x187, 0x18a, 0x3, 0x2, 0x2, 0x2, 0x188, 
    0x186, 0x3, 0x2, 0x2, 0x2, 0x188, 0x189, 0x3, 0x2, 0x2, 0x2, 0x189, 
    0x3f, 0x3, 0x2, 0x2, 0x2, 0x18a, 0x188, 0x3, 0x2, 0x2, 0x2, 0x18b, 0x195, 
    0x5, 0x42, 0x22, 0x2, 0x18c, 0x18d, 0x7, 0x25, 0x2, 0x2, 0x18d, 0x195, 
    0x5, 0x40, 0x21, 0x2, 0x18e, 0x18f, 0x7, 0x26, 0x2, 0x2, 0x18f, 0x195, 
    0x5, 0x40, 0x21, 0x2, 0x190, 0x191, 0x7, 0x27, 0x2, 0x2, 0x191, 0x195, 
    0x5, 0x40, 0x21, 0x2, 0x192, 0x193, 0x7, 0x28, 0x2, 0x2, 0x193, 0x195, 
    0x5, 0x40, 0x21, 0x2, 0x194, 0x18b, 0x3, 0x2, 0x2, 0x2, 0x194, 0x18c, 
    0x3, 0x2, 0x2, 0x2, 0x194, 0x18e, 0x3, 0x2, 0x2, 0x2, 0x194, 0x190, 
    0x3, 0x2, 0x2, 0x2, 0x194, 0x192, 0x3, 0x2, 0x2, 0x2, 0x195, 0x41, 0x3, 
    0x2, 0x2, 0x2, 0x196, 0x1a1, 0x5, 0x44, 0x23, 0x2, 0x197, 0x198, 0x5, 
    0x66, 0x34, 0x2, 0x198, 0x199, 0x7, 0x1b, 0x2, 0x2, 0x199, 0x19a, 0x7, 
    0x1c, 0x2, 0x2, 0x19a, 0x1a1, 0x3, 0x2, 0x2, 0x2, 0x19b, 0x19c, 0x5, 
    0x66, 0x34, 0x2, 0x19c, 0x19d, 0x7, 0x1b, 0x2, 0x2, 0x19d, 0x19e, 0x5, 
    0x2c, 0x17, 0x2, 0x19e, 0x19f, 0x7, 0x1c, 0x2, 0x2, 0x19f, 0x1a1, 0x3, 
    0x2, 0x2, 0x2, 0x1a0, 0x196, 0x3, 0x2, 0x2, 0x2, 0x1a0, 0x197, 0x3, 
    0x2, 0x2, 0x2, 0x1a0, 0x19b, 0x3, 0x2, 0x2, 0x2, 0x1a1, 0x1b4, 0x3, 
    0x2, 0x2, 0x2, 0x1a2, 0x1a3, 0x7, 0x1d, 0x2, 0x2, 0x1a3, 0x1a4, 0x5, 
    0x2c, 0x17, 0x2, 0x1a4, 0x1a5, 0x7, 0x1e, 0x2, 0x2, 0x1a5, 0x1b3, 0x3, 
    0x2, 0x2, 0x2, 0x1a6, 0x1a7, 0x7, 0x1d, 0x2, 0x2, 0x1a7, 0x1a8, 0x5, 
    0x2e, 0x18, 0x2, 0x1a8, 0x1a9, 0x7, 0x5, 0x2, 0x2, 0x1a9, 0x1aa, 0x5, 
    0x2e, 0x18, 0x2, 0x1aa, 0x1ab, 0x7, 0x1e, 0x2, 0x2, 0x1ab, 0x1b3, 0x3, 
    0x2, 0x2, 0x2, 0x1ac, 0x1ad, 0x7, 0x1b, 0x2, 0x2, 0x1ad, 0x1b3, 0x7, 
    0x1c, 0x2, 0x2, 0x1ae, 0x1af, 0x7, 0x1b, 0x2, 0x2, 0x1af, 0x1b0, 0x5, 
    0x2c, 0x17, 0x2, 0x1b0, 0x1b1, 0x7, 0x1c, 0x2, 0x2, 0x1b1, 0x1b3, 0x3, 
    0x2, 0x2, 0x2, 0x1b2, 0x1a2, 0x3, 0x2, 0x2, 0x2, 0x1b2, 0x1a6, 0x3, 
    0x2, 0x2, 0x2, 0x1b2, 0x1ac, 0x3, 0x2, 0x2, 0x2, 0x1b2, 0x1ae, 0x3, 
    0x2, 0x2, 0x2, 0x1b3, 0x1b6, 0x3, 0x2, 0x2, 0x2, 0x1b4, 0x1b2, 0x3, 
    0x2, 0x2, 0x2, 0x1b4, 0x1b5, 0x3, 0x2, 0x2, 0x2, 0x1b5, 0x43, 0x3, 0x2, 
    0x2, 0x2, 0x1b6, 0x1b4, 0x3, 0x2, 0x2, 0x2, 0x1b7, 0x1ef, 0x7, 0x29, 
    0x2, 0x2, 0x1b8, 0x1ef, 0x7, 0x2a, 0x2, 0x2, 0x1b9, 0x1ef, 0x7, 0x64, 
    0x2, 0x2, 0x1ba, 0x1ef, 0x7, 0x65, 0x2, 0x2, 0x1bb, 0x1ef, 0x5, 0x5c, 
    0x2f, 0x2, 0x1bc, 0x1ef, 0x5, 0x64, 0x33, 0x2, 0x1bd, 0x1ef, 0x7, 0x2b, 
    0x2, 0x2, 0x1be, 0x1bf, 0x7, 0x1d, 0x2, 0x2, 0x1bf, 0x1ef, 0x7, 0x1e, 
    0x2, 0x2, 0x1c0, 0x1c1, 0x7, 0x1d, 0x2, 0x2, 0x1c1, 0x1c2, 0x5, 0x2c, 
    0x17, 0x2, 0x1c2, 0x1c3, 0x7, 0x1e, 0x2, 0x2, 0x1c3, 0x1ef, 0x3, 0x2, 
    0x2, 0x2, 0x1c4, 0x1c5, 0x7, 0x2c, 0x2, 0x2, 0x1c5, 0x1ef, 0x7, 0x2d, 
    0x2, 0x2, 0x1c6, 0x1ef, 0x5, 0x46, 0x24, 0x2, 0x1c7, 0x1c8, 0x7, 0x2c, 
    0x2, 0x2, 0x1c8, 0x1c9, 0x5, 0x48, 0x25, 0x2, 0x1c9, 0x1ca, 0x7, 0x2d, 
    0x2, 0x2, 0x1ca, 0x1ef, 0x3, 0x2, 0x2, 0x2, 0x1cb, 0x1cc, 0x7, 0x1b, 
    0x2, 0x2, 0x1cc, 0x1cd, 0x5, 0x30, 0x19, 0x2, 0x1cd, 0x1ce, 0x7, 0xf, 
    0x2, 0x2, 0x1ce, 0x1cf, 0x5, 0x30, 0x19, 0x2, 0x1cf, 0x1d0, 0x7, 0x1c, 
    0x2, 0x2, 0x1d0, 0x1ef, 0x3, 0x2, 0x2, 0x2, 0x1d1, 0x1d2, 0x7, 0x2e, 
    0x2, 0x2, 0x1d2, 0x1d3, 0x5, 0x52, 0x2a, 0x2, 0x1d3, 0x1d4, 0x7, 0x2f, 
    0x2, 0x2, 0x1d4, 0x1d5, 0x5, 0x44, 0x23, 0x2, 0x1d5, 0x1ef, 0x3, 0x2, 
    0x2, 0x2, 0x1d6, 0x1d7, 0x7, 0x17, 0x2, 0x2, 0x1d7, 0x1d8, 0x5, 0x2c, 
    0x17, 0x2, 0x1d8, 0x1d9, 0x7, 0x5, 0x2, 0x2, 0x1d9, 0x1da, 0x5, 0x30, 
    0x19, 0x2, 0x1da, 0x1db, 0x5, 0x4a, 0x26, 0x2, 0x1db, 0x1dc, 0x7, 0x1a, 
    0x2, 0x2, 0x1dc, 0x1dd, 0x5, 0x30, 0x19, 0x2, 0x1dd, 0x1de, 0x7, 0x18, 
    0x2, 0x2, 0x1de, 0x1ef, 0x3, 0x2, 0x2, 0x2, 0x1df, 0x1e0, 0x7, 0x30, 
    0x2, 0x2, 0x1e0, 0x1e1, 0x5, 0x30, 0x19, 0x2, 0x1e1, 0x1e2, 0x7, 0x5, 
    0x2, 0x2, 0x1e2, 0x1e3, 0x5, 0x4c, 0x27, 0x2, 0x1e3, 0x1e4, 0x7, 0x18, 
    0x2, 0x2, 0x1e4, 0x1ef, 0x3, 0x2, 0x2, 0x2, 0x1e5, 0x1e6, 0x7, 0x1b, 
    0x2, 0x2, 0x1e6, 0x1e7, 0x5, 0x30, 0x19, 0x2, 0x1e7, 0x1e8, 0x7, 0x1c, 
    0x2, 0x2, 0x1e8, 0x1ef, 0x3, 0x2, 0x2, 0x2, 0x1e9, 0x1ea, 0x5, 0x5c, 
    0x2f, 0x2, 0x1ea, 0x1eb, 0x7, 0x21, 0x2, 0x2, 0x1eb, 0x1ef, 0x3, 0x2, 
    0x2, 0x2, 0x1ec, 0x1ef, 0x7, 0x12, 0x2, 0x2, 0x1ed, 0x1ef, 0x7, 0x31, 
    0x2, 0x2, 0x1ee, 0x1b7, 0x3, 0x2, 0x2, 0x2, 0x1ee, 0x1b8, 0x3, 0x2, 
    0x2, 0x2, 0x1ee, 0x1b9, 0x3, 0x2, 0x2, 0x2, 0x1ee, 0x1ba, 0x3, 0x2, 
    0x2, 0x2, 0x1ee, 0x1bb, 0x3, 0x2, 0x2, 0x2, 0x1ee, 0x1bc, 0x3, 0x2, 
    0x2, 0x2, 0x1ee, 0x1bd, 0x3, 0x2, 0x2, 0x2, 0x1ee, 0x1be, 0x3, 0x2, 
    0x2, 0x2, 0x1ee, 0x1c0, 0x3, 0x2, 0x2, 0x2, 0x1ee, 0x1c4, 0x3, 0x2, 
    0x2, 0x2, 0x1ee, 0x1c6, 0x3, 0x2, 0x2, 0x2, 0x1ee, 0x1c7, 0x3, 0x2, 
    0x2, 0x2, 0x1ee, 0x1cb, 0x3, 0x2, 0x2, 0x2, 0x1ee, 0x1d1, 0x3, 0x2, 
    0x2, 0x2, 0x1ee, 0x1d6, 0x3, 0x2, 0x2, 0x2, 0x1ee, 0x1df, 0x3, 0x2, 
    0x2, 0x2, 0x1ee, 0x1e5, 0x3, 0x2, 0x2, 0x2, 0x1ee, 0x1e9, 0x3, 0x2, 
    0x2, 0x2, 0x1ee, 0x1ec, 0x3, 0x2, 0x2, 0x2, 0x1ee, 0x1ed, 0x3, 0x2, 
    0x2, 0x2, 0x1ef, 0x45, 0x3, 0x2, 0x2, 0x2, 0x1f0, 0x1f1, 0x7, 0x2c, 
    0x2, 0x2, 0x1f1, 0x1f2, 0x5, 0x2c, 0x17, 0x2, 0x1f2, 0x1f3, 0x7, 0x2d, 
    0x2, 0x2, 0x1f3, 0x47, 0x3, 0x2, 0x2, 0x2, 0x1f4, 0x1f5, 0x5, 0x30, 
    0x19, 0x2, 0x1f5, 0x1f6, 0x7, 0x5, 0x2, 0x2, 0x1f6, 0x1f7, 0x5, 0x30, 
    0x19, 0x2, 0x1f7, 0x1f8, 0x7, 0xf, 0x2, 0x2, 0x1f8, 0x1f9, 0x5, 0x30, 
    0x19, 0x2, 0x1f9, 0x1fa, 0x7, 0x5, 0x2, 0x2, 0x1fa, 0x1fb, 0x5, 0x30, 
    0x19, 0x2, 0x1fb, 0x49, 0x3, 0x2, 0x2, 0x2, 0x1fc, 0x1fd, 0x5, 0x30, 
    0x19, 0x2, 0x1fd, 0x1fe, 0x7, 0x5, 0x2, 0x2, 0x1fe, 0x1ff, 0x5, 0x30, 
    0x19, 0x2, 0x1ff, 0x200, 0x7, 0x19, 0x2, 0x2, 0x200, 0x202, 0x3, 0x2, 
    0x2, 0x2, 0x201, 0x1fc, 0x3, 0x2, 0x2, 0x2, 0x202, 0x205, 0x3, 0x2, 
    0x2, 0x2, 0x203, 0x201, 0x3, 0x2, 0x2, 0x2, 0x203, 0x204, 0x3, 0x2, 
    0x2, 0x2, 0x204, 0x4b, 0x3, 0x2, 0x2, 0x2, 0x205, 0x203, 0x3, 0x2, 0x2, 
    0x2, 0x206, 0x20e, 0x5, 0x4e, 0x28, 0x2, 0x207, 0x208, 0x5, 0x4e, 0x28, 
    0x2, 0x208, 0x209, 0x7, 0x1a, 0x2, 0x2, 0x209, 0x20a, 0x5, 0x30, 0x19, 
    0x2, 0x20a, 0x20e, 0x3, 0x2, 0x2, 0x2, 0x20b, 0x20c, 0x7, 0x1a, 0x2, 
    0x2, 0x20c, 0x20e, 0x5, 0x30, 0x19, 0x2, 0x20d, 0x206, 0x3, 0x2, 0x2, 
    0x2, 0x20d, 0x207, 0x3, 0x2, 0x2, 0x2, 0x20d, 0x20b, 0x3, 0x2, 0x2, 
    0x2, 0x20e, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x20f, 0x210, 0x7, 0x32, 0x2, 
    0x2, 0x210, 0x211, 0x5, 0x30, 0x19, 0x2, 0x211, 0x212, 0x7, 0x5, 0x2, 
    0x2, 0x212, 0x213, 0x5, 0x30, 0x19, 0x2, 0x213, 0x215, 0x3, 0x2, 0x2, 
    0x2, 0x214, 0x20f, 0x3, 0x2, 0x2, 0x2, 0x215, 0x216, 0x3, 0x2, 0x2, 
    0x2, 0x216, 0x214, 0x3, 0x2, 0x2, 0x2, 0x216, 0x217, 0x3, 0x2, 0x2, 
    0x2, 0x217, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x218, 0x21d, 0x5, 0x52, 0x2a, 
    0x2, 0x219, 0x21a, 0x7, 0xf, 0x2, 0x2, 0x21a, 0x21c, 0x5, 0x52, 0x2a, 
    0x2, 0x21b, 0x219, 0x3, 0x2, 0x2, 0x2, 0x21c, 0x21f, 0x3, 0x2, 0x2, 
    0x2, 0x21d, 0x21b, 0x3, 0x2, 0x2, 0x2, 0x21d, 0x21e, 0x3, 0x2, 0x2, 
    0x2, 0x21e, 0x51, 0x3, 0x2, 0x2, 0x2, 0x21f, 0x21d, 0x3, 0x2, 0x2, 0x2, 
    0x220, 0x258, 0x7, 0x33, 0x2, 0x2, 0x221, 0x258, 0x7, 0x34, 0x2, 0x2, 
    0x222, 0x223, 0x7, 0x34, 0x2, 0x2, 0x223, 0x224, 0x7, 0x1d, 0x2, 0x2, 
    0x224, 0x225, 0x5, 0x30, 0x19, 0x2, 0x225, 0x226, 0x7, 0x35, 0x2, 0x2, 
    0x226, 0x227, 0x5, 0x30, 0x19, 0x2, 0x227, 0x228, 0x7, 0x1e, 0x2, 0x2, 
    0x228, 0x258, 0x3, 0x2, 0x2, 0x2, 0x229, 0x258, 0x7, 0x36, 0x2, 0x2, 
    0x22a, 0x258, 0x7, 0x37, 0x2, 0x2, 0x22b, 0x22c, 0x7, 0x38, 0x2, 0x2, 
    0x22c, 0x258, 0x5, 0x52, 0x2a, 0x2, 0x22d, 0x22e, 0x7, 0x38, 0x2, 0x2, 
    0x22e, 0x22f, 0x7, 0x1d, 0x2, 0x2, 0x22f, 0x230, 0x5, 0x30, 0x19, 0x2, 
    0x230, 0x231, 0x7, 0x1e, 0x2, 0x2, 0x231, 0x232, 0x5, 0x52, 0x2a, 0x2, 
    0x232, 0x258, 0x3, 0x2, 0x2, 0x2, 0x233, 0x234, 0x7, 0x38, 0x2, 0x2, 
    0x234, 0x235, 0x7, 0x1d, 0x2, 0x2, 0x235, 0x236, 0x5, 0x30, 0x19, 0x2, 
    0x236, 0x237, 0x7, 0x35, 0x2, 0x2, 0x237, 0x238, 0x5, 0x30, 0x19, 0x2, 
    0x238, 0x239, 0x7, 0x1e, 0x2, 0x2, 0x239, 0x23a, 0x5, 0x52, 0x2a, 0x2, 
    0x23a, 0x258, 0x3, 0x2, 0x2, 0x2, 0x23b, 0x23c, 0x7, 0x39, 0x2, 0x2, 
    0x23c, 0x258, 0x5, 0x52, 0x2a, 0x2, 0x23d, 0x23e, 0x7, 0x3a, 0x2, 0x2, 
    0x23e, 0x23f, 0x7, 0x1b, 0x2, 0x2, 0x23f, 0x240, 0x5, 0x52, 0x2a, 0x2, 
    0x240, 0x241, 0x7, 0x5, 0x2, 0x2, 0x241, 0x242, 0x5, 0x52, 0x2a, 0x2, 
    0x242, 0x243, 0x7, 0x1c, 0x2, 0x2, 0x243, 0x258, 0x3, 0x2, 0x2, 0x2, 
    0x244, 0x245, 0x7, 0x3b, 0x2, 0x2, 0x245, 0x246, 0x7, 0x1b, 0x2, 0x2, 
    0x246, 0x247, 0x5, 0x54, 0x2b, 0x2, 0x247, 0x248, 0x7, 0x1c, 0x2, 0x2, 
    0x248, 0x258, 0x3, 0x2, 0x2, 0x2, 0x249, 0x24a, 0x7, 0x3c, 0x2, 0x2, 
    0x24a, 0x24b, 0x5, 0x52, 0x2a, 0x2, 0x24b, 0x24c, 0x7, 0x1b, 0x2, 0x2, 
    0x24c, 0x24d, 0x7, 0x1c, 0x2, 0x2, 0x24d, 0x258, 0x3, 0x2, 0x2, 0x2, 
    0x24e, 0x24f, 0x7, 0x3c, 0x2, 0x2, 0x24f, 0x250, 0x5, 0x52, 0x2a, 0x2, 
    0x250, 0x251, 0x7, 0x1b, 0x2, 0x2, 0x251, 0x252, 0x5, 0x50, 0x29, 0x2, 
    0x252, 0x253, 0x7, 0x1c, 0x2, 0x2, 0x253, 0x258, 0x3, 0x2, 0x2, 0x2, 
    0x254, 0x255, 0x7, 0x3d, 0x2, 0x2, 0x255, 0x258, 0x5, 0x52, 0x2a, 0x2, 
    0x256, 0x258, 0x5, 0x5c, 0x2f, 0x2, 0x257, 0x220, 0x3, 0x2, 0x2, 0x2, 
    0x257, 0x221, 0x3, 0x2, 0x2, 0x2, 0x257, 0x222, 0x3, 0x2, 0x2, 0x2, 
    0x257, 0x229, 0x3, 0x2, 0x2, 0x2, 0x257, 0x22a, 0x3, 0x2, 0x2, 0x2, 
    0x257, 0x22b, 0x3, 0x2, 0x2, 0x2, 0x257, 0x22d, 0x3, 0x2, 0x2, 0x2, 
    0x257, 0x233, 0x3, 0x2, 0x2, 0x2, 0x257, 0x23b, 0x3, 0x2, 0x2, 0x2, 
    0x257, 0x23d, 0x3, 0x2, 0x2, 0x2, 0x257, 0x244, 0x3, 0x2, 0x2, 0x2, 
    0x257, 0x249, 0x3, 0x2, 0x2, 0x2, 0x257, 0x24e, 0x3, 0x2, 0x2, 0x2, 
    0x257, 0x254, 0x3, 0x2, 0x2, 0x2, 0x257, 0x256, 0x3, 0x2, 0x2, 0x2, 
    0x258, 0x53, 0x3, 0x2, 0x2, 0x2, 0x259, 0x25e, 0x5, 0x56, 0x2c, 0x2, 
    0x25a, 0x25b, 0x7, 0xf, 0x2, 0x2, 0x25b, 0x25d, 0x5, 0x56, 0x2c, 0x2, 
    0x25c, 0x25a, 0x3, 0x2, 0x2, 0x2, 0x25d, 0x260, 0x3, 0x2, 0x2, 0x2, 
    0x25e, 0x25c, 0x3, 0x2, 0x2, 0x2, 0x25e, 0x25f, 0x3, 0x2, 0x2, 0x2, 
    0x25f, 0x55, 0x3, 0x2, 0x2, 0x2, 0x260, 0x25e, 0x3, 0x2, 0x2, 0x2, 0x261, 
    0x262, 0x5, 0x52, 0x2a, 0x2, 0x262, 0x263, 0x5, 0x62, 0x32, 0x2, 0x263, 
    0x57, 0x3, 0x2, 0x2, 0x2, 0x264, 0x265, 0x7, 0x2c, 0x2, 0x2, 0x265, 
    0x266, 0x5, 0x5a, 0x2e, 0x2, 0x266, 0x267, 0x7, 0x2d, 0x2, 0x2, 0x267, 
    0x59, 0x3, 0x2, 0x2, 0x2, 0x268, 0x26d, 0x5, 0x5c, 0x2f, 0x2, 0x269, 
    0x26a, 0x7, 0xf, 0x2, 0x2, 0x26a, 0x26c, 0x5, 0x5c, 0x2f, 0x2, 0x26b, 
    0x269, 0x3, 0x2, 0x2, 0x2, 0x26c, 0x26f, 0x3, 0x2, 0x2, 0x2, 0x26d, 
    0x26b, 0x3, 0x2, 0x2, 0x2, 0x26d, 0x26e, 0x3, 0x2, 0x2, 0x2, 0x26e, 
    0x5b, 0x3, 0x2, 0x2, 0x2, 0x26f, 0x26d, 0x3, 0x2, 0x2, 0x2, 0x270, 0x275, 
    0x5, 0x62, 0x32, 0x2, 0x271, 0x275, 0x7, 0x68, 0x2, 0x2, 0x272, 0x275, 
    0x7, 0x69, 0x2, 0x2, 0x273, 0x275, 0x7, 0x6a, 0x2, 0x2, 0x274, 0x270, 
    0x3, 0x2, 0x2, 0x2, 0x274, 0x271, 0x3, 0x2, 0x2, 0x2, 0x274, 0x272, 
    0x3, 0x2, 0x2, 0x2, 0x274, 0x273, 0x3, 0x2, 0x2, 0x2, 0x275, 0x5d, 0x3, 
    0x2, 0x2, 0x2, 0x276, 0x278, 0x5, 0x60, 0x31, 0x2, 0x277, 0x276, 0x3, 
    0x2, 0x2, 0x2, 0x277, 0x278, 0x3, 0x2, 0x2, 0x2, 0x278, 0x5f, 0x3, 0x2, 
    0x2, 0x2, 0x279, 0x27a, 0x9, 0x2, 0x2, 0x2, 0x27a, 0x61, 0x3, 0x2, 0x2, 
    0x2, 0x27b, 0x27c, 0x7, 0x67, 0x2, 0x2, 0x27c, 0x63, 0x3, 0x2, 0x2, 
    0x2, 0x27d, 0x27e, 0x7, 0x66, 0x2, 0x2, 0x27e, 0x65, 0x3, 0x2, 0x2, 
    0x2, 0x27f, 0x280, 0x9, 0x3, 0x2, 0x2, 0x280, 0x67, 0x3, 0x2, 0x2, 0x2, 
    0x2e, 0x6b, 0x7b, 0x80, 0x9f, 0xaf, 0xb3, 0xb6, 0xba, 0xc1, 0xd0, 0xdb, 
    0xe2, 0xf6, 0xfd, 0x10c, 0x115, 0x11a, 0x121, 0x12e, 0x133, 0x13f, 0x143, 
    0x14e, 0x155, 0x161, 0x168, 0x170, 0x178, 0x180, 0x188, 0x194, 0x1a0, 
    0x1b2, 0x1b4, 0x1ee, 0x203, 0x20d, 0x216, 0x21d, 0x257, 0x25e, 0x26d, 
    0x274, 0x277, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

CIFLocationParser::Initializer CIFLocationParser::_init;
