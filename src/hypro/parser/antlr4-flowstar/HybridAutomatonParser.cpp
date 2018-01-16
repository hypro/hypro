
// Generated from HybridAutomaton.g4 by ANTLR 4.7


#include "HybridAutomatonVisitor.h"

#include "HybridAutomatonParser.h"


	#include <map>
	#include <string>


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

HybridAutomatonParser::OldContext* HybridAutomatonParser::StartContext::old() {
  return getRuleContext<HybridAutomatonParser::OldContext>(0);
}

HybridAutomatonParser::CompContext* HybridAutomatonParser::StartContext::comp() {
  return getRuleContext<HybridAutomatonParser::CompContext>(0);
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
    setState(100);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case HybridAutomatonParser::T__0: {
        enterOuterAlt(_localctx, 1);
        setState(98);
        old();
        break;
      }

      case HybridAutomatonParser::T__17: {
        enterOuterAlt(_localctx, 2);
        setState(99);
        comp();
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

//----------------- OldContext ------------------------------------------------------------------

HybridAutomatonParser::OldContext::OldContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HybridAutomatonParser::OldContext::CBOPEN() {
  return getToken(HybridAutomatonParser::CBOPEN, 0);
}

HybridAutomatonParser::AutomatonContext* HybridAutomatonParser::OldContext::automaton() {
  return getRuleContext<HybridAutomatonParser::AutomatonContext>(0);
}

tree::TerminalNode* HybridAutomatonParser::OldContext::CBCLOSE() {
  return getToken(HybridAutomatonParser::CBCLOSE, 0);
}

HybridAutomatonParser::UnsafesetContext* HybridAutomatonParser::OldContext::unsafeset() {
  return getRuleContext<HybridAutomatonParser::UnsafesetContext>(0);
}


size_t HybridAutomatonParser::OldContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleOld;
}

antlrcpp::Any HybridAutomatonParser::OldContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitOld(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::OldContext* HybridAutomatonParser::old() {
  OldContext *_localctx = _tracker.createInstance<OldContext>(_ctx, getState());
  enterRule(_localctx, 2, HybridAutomatonParser::RuleOld);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(102);
    match(HybridAutomatonParser::T__0);
    setState(103);
    match(HybridAutomatonParser::CBOPEN);
    setState(104);
    automaton();
    setState(105);
    match(HybridAutomatonParser::CBCLOSE);
    setState(107);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HybridAutomatonParser::T__11) {
      setState(106);
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

//----------------- AutomatonContext ------------------------------------------------------------------

HybridAutomatonParser::AutomatonContext::AutomatonContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HybridAutomatonParser::VardeclarationContext* HybridAutomatonParser::AutomatonContext::vardeclaration() {
  return getRuleContext<HybridAutomatonParser::VardeclarationContext>(0);
}

HybridAutomatonParser::ModesContext* HybridAutomatonParser::AutomatonContext::modes() {
  return getRuleContext<HybridAutomatonParser::ModesContext>(0);
}

HybridAutomatonParser::JumpsContext* HybridAutomatonParser::AutomatonContext::jumps() {
  return getRuleContext<HybridAutomatonParser::JumpsContext>(0);
}

HybridAutomatonParser::ConstantdeclarationContext* HybridAutomatonParser::AutomatonContext::constantdeclaration() {
  return getRuleContext<HybridAutomatonParser::ConstantdeclarationContext>(0);
}

HybridAutomatonParser::SettingContext* HybridAutomatonParser::AutomatonContext::setting() {
  return getRuleContext<HybridAutomatonParser::SettingContext>(0);
}

std::vector<HybridAutomatonParser::InitContext *> HybridAutomatonParser::AutomatonContext::init() {
  return getRuleContexts<HybridAutomatonParser::InitContext>();
}

HybridAutomatonParser::InitContext* HybridAutomatonParser::AutomatonContext::init(size_t i) {
  return getRuleContext<HybridAutomatonParser::InitContext>(i);
}


size_t HybridAutomatonParser::AutomatonContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleAutomaton;
}

antlrcpp::Any HybridAutomatonParser::AutomatonContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitAutomaton(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::AutomatonContext* HybridAutomatonParser::automaton() {
  AutomatonContext *_localctx = _tracker.createInstance<AutomatonContext>(_ctx, getState());
  enterRule(_localctx, 4, HybridAutomatonParser::RuleAutomaton);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(109);
    vardeclaration();
    setState(111);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HybridAutomatonParser::PAR) {
      setState(110);
      constantdeclaration();
    }
    setState(114);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HybridAutomatonParser::T__17) {
      setState(113);
      setting();
    }
    setState(116);
    modes();
    setState(117);
    jumps();
    setState(119); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(118);
      init();
      setState(121); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == HybridAutomatonParser::T__10);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CompContext ------------------------------------------------------------------

HybridAutomatonParser::CompContext::CompContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HybridAutomatonParser::SettingContext* HybridAutomatonParser::CompContext::setting() {
  return getRuleContext<HybridAutomatonParser::SettingContext>(0);
}

std::vector<tree::TerminalNode *> HybridAutomatonParser::CompContext::CBOPEN() {
  return getTokens(HybridAutomatonParser::CBOPEN);
}

tree::TerminalNode* HybridAutomatonParser::CompContext::CBOPEN(size_t i) {
  return getToken(HybridAutomatonParser::CBOPEN, i);
}

std::vector<tree::TerminalNode *> HybridAutomatonParser::CompContext::CBCLOSE() {
  return getTokens(HybridAutomatonParser::CBCLOSE);
}

tree::TerminalNode* HybridAutomatonParser::CompContext::CBCLOSE(size_t i) {
  return getToken(HybridAutomatonParser::CBCLOSE, i);
}

HybridAutomatonParser::GlobalvardeclarationContext* HybridAutomatonParser::CompContext::globalvardeclaration() {
  return getRuleContext<HybridAutomatonParser::GlobalvardeclarationContext>(0);
}

std::vector<HybridAutomatonParser::ComponentContext *> HybridAutomatonParser::CompContext::component() {
  return getRuleContexts<HybridAutomatonParser::ComponentContext>();
}

HybridAutomatonParser::ComponentContext* HybridAutomatonParser::CompContext::component(size_t i) {
  return getRuleContext<HybridAutomatonParser::ComponentContext>(i);
}


size_t HybridAutomatonParser::CompContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleComp;
}

antlrcpp::Any HybridAutomatonParser::CompContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitComp(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::CompContext* HybridAutomatonParser::comp() {
  CompContext *_localctx = _tracker.createInstance<CompContext>(_ctx, getState());
  enterRule(_localctx, 6, HybridAutomatonParser::RuleComp);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(123);
    setting();
    setState(124);
    match(HybridAutomatonParser::T__0);
    setState(125);
    match(HybridAutomatonParser::CBOPEN);
    setState(127);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HybridAutomatonParser::T__3) {
      setState(126);
      globalvardeclaration();
    }
    setState(129);
    match(HybridAutomatonParser::T__1);
    setState(130);
    match(HybridAutomatonParser::CBOPEN);
    setState(132); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(131);
      component();
      setState(134); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == HybridAutomatonParser::VARIABLE);
    setState(136);
    match(HybridAutomatonParser::CBCLOSE);
    setState(137);
    match(HybridAutomatonParser::CBCLOSE);
   
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

std::vector<tree::TerminalNode *> HybridAutomatonParser::VardeclarationContext::COMMA() {
  return getTokens(HybridAutomatonParser::COMMA);
}

tree::TerminalNode* HybridAutomatonParser::VardeclarationContext::COMMA(size_t i) {
  return getToken(HybridAutomatonParser::COMMA, i);
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
  enterRule(_localctx, 8, HybridAutomatonParser::RuleVardeclaration);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(139);
    match(HybridAutomatonParser::T__2);
    setState(140);
    match(HybridAutomatonParser::VARIABLE);
    setState(147);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HybridAutomatonParser::COMMA) {
      setState(143); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(141);
        match(HybridAutomatonParser::COMMA);
        setState(142);
        match(HybridAutomatonParser::VARIABLE);
        setState(145); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == HybridAutomatonParser::COMMA);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstantdeclarationContext ------------------------------------------------------------------

HybridAutomatonParser::ConstantdeclarationContext::ConstantdeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HybridAutomatonParser::ConstantdeclarationContext::PAR() {
  return getToken(HybridAutomatonParser::PAR, 0);
}

tree::TerminalNode* HybridAutomatonParser::ConstantdeclarationContext::CBOPEN() {
  return getToken(HybridAutomatonParser::CBOPEN, 0);
}

tree::TerminalNode* HybridAutomatonParser::ConstantdeclarationContext::CBCLOSE() {
  return getToken(HybridAutomatonParser::CBCLOSE, 0);
}

std::vector<HybridAutomatonParser::ConstantexprContext *> HybridAutomatonParser::ConstantdeclarationContext::constantexpr() {
  return getRuleContexts<HybridAutomatonParser::ConstantexprContext>();
}

HybridAutomatonParser::ConstantexprContext* HybridAutomatonParser::ConstantdeclarationContext::constantexpr(size_t i) {
  return getRuleContext<HybridAutomatonParser::ConstantexprContext>(i);
}

std::vector<HybridAutomatonParser::ReplacedexprContext *> HybridAutomatonParser::ConstantdeclarationContext::replacedexpr() {
  return getRuleContexts<HybridAutomatonParser::ReplacedexprContext>();
}

HybridAutomatonParser::ReplacedexprContext* HybridAutomatonParser::ConstantdeclarationContext::replacedexpr(size_t i) {
  return getRuleContext<HybridAutomatonParser::ReplacedexprContext>(i);
}


size_t HybridAutomatonParser::ConstantdeclarationContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleConstantdeclaration;
}

antlrcpp::Any HybridAutomatonParser::ConstantdeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitConstantdeclaration(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::ConstantdeclarationContext* HybridAutomatonParser::constantdeclaration() {
  ConstantdeclarationContext *_localctx = _tracker.createInstance<ConstantdeclarationContext>(_ctx, getState());
  enterRule(_localctx, 10, HybridAutomatonParser::RuleConstantdeclaration);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(149);
    match(HybridAutomatonParser::PAR);
    setState(150);
    match(HybridAutomatonParser::CBOPEN);
    setState(155);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << HybridAutomatonParser::MINUS)
      | (1ULL << HybridAutomatonParser::NUMBER)
      | (1ULL << HybridAutomatonParser::CONSTANT))) != 0)) {
      setState(153);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case HybridAutomatonParser::CONSTANT: {
          setState(151);
          constantexpr();
          break;
        }

        case HybridAutomatonParser::MINUS:
        case HybridAutomatonParser::NUMBER: {
          setState(152);
          replacedexpr();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(157);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(158);
    match(HybridAutomatonParser::CBCLOSE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GlobalvardeclarationContext ------------------------------------------------------------------

HybridAutomatonParser::GlobalvardeclarationContext::GlobalvardeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> HybridAutomatonParser::GlobalvardeclarationContext::VARIABLE() {
  return getTokens(HybridAutomatonParser::VARIABLE);
}

tree::TerminalNode* HybridAutomatonParser::GlobalvardeclarationContext::VARIABLE(size_t i) {
  return getToken(HybridAutomatonParser::VARIABLE, i);
}

std::vector<tree::TerminalNode *> HybridAutomatonParser::GlobalvardeclarationContext::COMMA() {
  return getTokens(HybridAutomatonParser::COMMA);
}

tree::TerminalNode* HybridAutomatonParser::GlobalvardeclarationContext::COMMA(size_t i) {
  return getToken(HybridAutomatonParser::COMMA, i);
}


size_t HybridAutomatonParser::GlobalvardeclarationContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleGlobalvardeclaration;
}

antlrcpp::Any HybridAutomatonParser::GlobalvardeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitGlobalvardeclaration(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::GlobalvardeclarationContext* HybridAutomatonParser::globalvardeclaration() {
  GlobalvardeclarationContext *_localctx = _tracker.createInstance<GlobalvardeclarationContext>(_ctx, getState());
  enterRule(_localctx, 12, HybridAutomatonParser::RuleGlobalvardeclaration);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(160);
    match(HybridAutomatonParser::T__3);
    setState(161);
    match(HybridAutomatonParser::VARIABLE);
    setState(168);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HybridAutomatonParser::COMMA) {
      setState(164); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(162);
        match(HybridAutomatonParser::COMMA);
        setState(163);
        match(HybridAutomatonParser::VARIABLE);
        setState(166); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == HybridAutomatonParser::COMMA);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ComponentContext ------------------------------------------------------------------

HybridAutomatonParser::ComponentContext::ComponentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HybridAutomatonParser::ComponentContext::VARIABLE() {
  return getToken(HybridAutomatonParser::VARIABLE, 0);
}

tree::TerminalNode* HybridAutomatonParser::ComponentContext::CBOPEN() {
  return getToken(HybridAutomatonParser::CBOPEN, 0);
}

HybridAutomatonParser::AutomatonContext* HybridAutomatonParser::ComponentContext::automaton() {
  return getRuleContext<HybridAutomatonParser::AutomatonContext>(0);
}

tree::TerminalNode* HybridAutomatonParser::ComponentContext::CBCLOSE() {
  return getToken(HybridAutomatonParser::CBCLOSE, 0);
}


size_t HybridAutomatonParser::ComponentContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleComponent;
}

antlrcpp::Any HybridAutomatonParser::ComponentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitComponent(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::ComponentContext* HybridAutomatonParser::component() {
  ComponentContext *_localctx = _tracker.createInstance<ComponentContext>(_ctx, getState());
  enterRule(_localctx, 14, HybridAutomatonParser::RuleComponent);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(170);
    match(HybridAutomatonParser::VARIABLE);
    setState(171);
    match(HybridAutomatonParser::CBOPEN);
    setState(172);
    automaton();
    setState(173);
    match(HybridAutomatonParser::CBCLOSE);
   
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
  enterRule(_localctx, 16, HybridAutomatonParser::RuleModes);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(175);
    match(HybridAutomatonParser::T__4);
    setState(176);
    match(HybridAutomatonParser::CBOPEN);
    setState(180);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HybridAutomatonParser::VARIABLE) {
      setState(177);
      location();
      setState(182);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(183);
    match(HybridAutomatonParser::CBCLOSE);
   
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
  enterRule(_localctx, 18, HybridAutomatonParser::RuleLocation);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(185);
    match(HybridAutomatonParser::VARIABLE);
    setState(186);
    match(HybridAutomatonParser::CBOPEN);
    setState(187);
    activities();
    setState(191);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HybridAutomatonParser::T__9) {
      setState(188);
      invariants();
      setState(193);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(194);
    match(HybridAutomatonParser::CBCLOSE);
   
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
  enterRule(_localctx, 20, HybridAutomatonParser::RuleActivities);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(196);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << HybridAutomatonParser::T__5)
      | (1ULL << HybridAutomatonParser::T__6)
      | (1ULL << HybridAutomatonParser::T__7)
      | (1ULL << HybridAutomatonParser::T__8))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(197);
    match(HybridAutomatonParser::CBOPEN);
    setState(199); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(198);
      equation();
      setState(201); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == HybridAutomatonParser::VARIABLE);
    setState(203);
    match(HybridAutomatonParser::CBCLOSE);
   
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
  enterRule(_localctx, 22, HybridAutomatonParser::RuleInvariants);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(205);
    match(HybridAutomatonParser::T__9);
    setState(206);
    match(HybridAutomatonParser::CBOPEN);
    setState(208);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << HybridAutomatonParser::TRUE)
      | (1ULL << HybridAutomatonParser::FALSE)
      | (1ULL << HybridAutomatonParser::PLUS)
      | (1ULL << HybridAutomatonParser::MINUS)
      | (1ULL << HybridAutomatonParser::NUMBER)
      | (1ULL << HybridAutomatonParser::VARIABLE))) != 0)) {
      setState(207);
      constrset();
    }
    setState(210);
    match(HybridAutomatonParser::CBCLOSE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstantexprContext ------------------------------------------------------------------

HybridAutomatonParser::ConstantexprContext::ConstantexprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HybridAutomatonParser::ConstantexprContext::CONSTANT() {
  return getToken(HybridAutomatonParser::CONSTANT, 0);
}

tree::TerminalNode* HybridAutomatonParser::ConstantexprContext::EQUALS() {
  return getToken(HybridAutomatonParser::EQUALS, 0);
}

tree::TerminalNode* HybridAutomatonParser::ConstantexprContext::NUMBER() {
  return getToken(HybridAutomatonParser::NUMBER, 0);
}

tree::TerminalNode* HybridAutomatonParser::ConstantexprContext::MINUS() {
  return getToken(HybridAutomatonParser::MINUS, 0);
}


size_t HybridAutomatonParser::ConstantexprContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleConstantexpr;
}

antlrcpp::Any HybridAutomatonParser::ConstantexprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitConstantexpr(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::ConstantexprContext* HybridAutomatonParser::constantexpr() {
  ConstantexprContext *_localctx = _tracker.createInstance<ConstantexprContext>(_ctx, getState());
  enterRule(_localctx, 24, HybridAutomatonParser::RuleConstantexpr);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(212);
    dynamic_cast<ConstantexprContext *>(_localctx)->constantToken = match(HybridAutomatonParser::CONSTANT);
    setState(213);
    match(HybridAutomatonParser::EQUALS);
    setState(215);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HybridAutomatonParser::MINUS) {
      setState(214);
      dynamic_cast<ConstantexprContext *>(_localctx)->minusToken = match(HybridAutomatonParser::MINUS);
    }
    setState(217);
    dynamic_cast<ConstantexprContext *>(_localctx)->numberToken = match(HybridAutomatonParser::NUMBER);

    	//std::cout << "In constantexpr! MINUS text is: " << (dynamic_cast<ConstantexprContext *>(_localctx)->minusToken != nullptr ? dynamic_cast<ConstantexprContext *>(_localctx)->minusToken->getText() : "") << std::endl;
    	if((dynamic_cast<ConstantexprContext *>(_localctx)->minusToken != nullptr ? dynamic_cast<ConstantexprContext *>(_localctx)->minusToken->getText() : "") != ""){
    		constants.insert({(dynamic_cast<ConstantexprContext *>(_localctx)->constantToken != nullptr ? dynamic_cast<ConstantexprContext *>(_localctx)->constantToken->getText() : ""), (dynamic_cast<ConstantexprContext *>(_localctx)->minusToken != nullptr ? dynamic_cast<ConstantexprContext *>(_localctx)->minusToken->getText() : "").append((dynamic_cast<ConstantexprContext *>(_localctx)->numberToken != nullptr ? dynamic_cast<ConstantexprContext *>(_localctx)->numberToken->getText() : ""))});
    		//std::cout << "Constant " << (dynamic_cast<ConstantexprContext *>(_localctx)->constantToken != nullptr ? dynamic_cast<ConstantexprContext *>(_localctx)->constantToken->getText() : "") << " with value " << (dynamic_cast<ConstantexprContext *>(_localctx)->minusToken != nullptr ? dynamic_cast<ConstantexprContext *>(_localctx)->minusToken->getText() : "").append((dynamic_cast<ConstantexprContext *>(_localctx)->numberToken != nullptr ? dynamic_cast<ConstantexprContext *>(_localctx)->numberToken->getText() : "")) << " was put in map!\n";
    	} else {
    		constants.insert({(dynamic_cast<ConstantexprContext *>(_localctx)->constantToken != nullptr ? dynamic_cast<ConstantexprContext *>(_localctx)->constantToken->getText() : ""), (dynamic_cast<ConstantexprContext *>(_localctx)->numberToken != nullptr ? dynamic_cast<ConstantexprContext *>(_localctx)->numberToken->getText() : "")});
    		//std::cout << "Constant " << (dynamic_cast<ConstantexprContext *>(_localctx)->constantToken != nullptr ? dynamic_cast<ConstantexprContext *>(_localctx)->constantToken->getText() : "") << " with value " << (dynamic_cast<ConstantexprContext *>(_localctx)->numberToken != nullptr ? dynamic_cast<ConstantexprContext *>(_localctx)->numberToken->getText() : "") << " was put in map!\n";
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
  enterRule(_localctx, 26, HybridAutomatonParser::RuleConnector);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(220);
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
  enterRule(_localctx, 28, HybridAutomatonParser::RuleTerm);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(222);
    _la = _input->LA(1);
    if (!(_la == HybridAutomatonParser::NUMBER

    || _la == HybridAutomatonParser::VARIABLE)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(233);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HybridAutomatonParser::TIMES) {
      setState(223);
      match(HybridAutomatonParser::TIMES);
      setState(227);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == HybridAutomatonParser::PLUS

      || _la == HybridAutomatonParser::MINUS) {
        setState(224);
        connector();
        setState(229);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(230);
      _la = _input->LA(1);
      if (!(_la == HybridAutomatonParser::NUMBER

      || _la == HybridAutomatonParser::VARIABLE)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(235);
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
  enterRule(_localctx, 30, HybridAutomatonParser::RulePolynom);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(239);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HybridAutomatonParser::PLUS

    || _la == HybridAutomatonParser::MINUS) {
      setState(236);
      connector();
      setState(241);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(242);
    term();
    setState(252);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(244); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(243);
          connector();
          setState(246); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == HybridAutomatonParser::PLUS

        || _la == HybridAutomatonParser::MINUS);
        setState(248);
        term(); 
      }
      setState(254);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx);
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

std::vector<tree::TerminalNode *> HybridAutomatonParser::IntervalContext::VARIABLE() {
  return getTokens(HybridAutomatonParser::VARIABLE);
}

tree::TerminalNode* HybridAutomatonParser::IntervalContext::VARIABLE(size_t i) {
  return getToken(HybridAutomatonParser::VARIABLE, i);
}

std::vector<tree::TerminalNode *> HybridAutomatonParser::IntervalContext::MINUS() {
  return getTokens(HybridAutomatonParser::MINUS);
}

tree::TerminalNode* HybridAutomatonParser::IntervalContext::MINUS(size_t i) {
  return getToken(HybridAutomatonParser::MINUS, i);
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
  enterRule(_localctx, 32, HybridAutomatonParser::RuleInterval);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(255);
    match(HybridAutomatonParser::SBOPEN);
    setState(257);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HybridAutomatonParser::MINUS) {
      setState(256);
      match(HybridAutomatonParser::MINUS);
    }
    setState(259);
    _la = _input->LA(1);
    if (!(_la == HybridAutomatonParser::NUMBER

    || _la == HybridAutomatonParser::VARIABLE)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(260);
    match(HybridAutomatonParser::COMMA);
    setState(262);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HybridAutomatonParser::MINUS) {
      setState(261);
      match(HybridAutomatonParser::MINUS);
    }
    setState(264);
    _la = _input->LA(1);
    if (!(_la == HybridAutomatonParser::NUMBER

    || _la == HybridAutomatonParser::VARIABLE)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(265);
    match(HybridAutomatonParser::SBCLOSE);
   
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

HybridAutomatonParser::ConnectorContext* HybridAutomatonParser::EquationContext::connector() {
  return getRuleContext<HybridAutomatonParser::ConnectorContext>(0);
}

HybridAutomatonParser::IntervalContext* HybridAutomatonParser::EquationContext::interval() {
  return getRuleContext<HybridAutomatonParser::IntervalContext>(0);
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
  enterRule(_localctx, 34, HybridAutomatonParser::RuleEquation);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(267);
    match(HybridAutomatonParser::VARIABLE);
    setState(268);
    match(HybridAutomatonParser::EQUALS);
    setState(269);
    polynom();
    setState(273);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HybridAutomatonParser::PLUS

    || _la == HybridAutomatonParser::MINUS) {
      setState(270);
      connector();
      setState(271);
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
  enterRule(_localctx, 36, HybridAutomatonParser::RuleConstraint);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(275);
    polynom();
    setState(276);
    _la = _input->LA(1);
    if (!(_la == HybridAutomatonParser::EQUALS

    || _la == HybridAutomatonParser::BOOLRELATION)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(277);
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
  enterRule(_localctx, 38, HybridAutomatonParser::RuleIntervalexpr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(279);
    match(HybridAutomatonParser::VARIABLE);
    setState(280);
    match(HybridAutomatonParser::IN);
    setState(281);
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

tree::TerminalNode* HybridAutomatonParser::ConstrsetContext::TRUE() {
  return getToken(HybridAutomatonParser::TRUE, 0);
}

tree::TerminalNode* HybridAutomatonParser::ConstrsetContext::FALSE() {
  return getToken(HybridAutomatonParser::FALSE, 0);
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
  enterRule(_localctx, 40, HybridAutomatonParser::RuleConstrset);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    setState(291);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case HybridAutomatonParser::PLUS:
      case HybridAutomatonParser::MINUS:
      case HybridAutomatonParser::NUMBER:
      case HybridAutomatonParser::VARIABLE: {
        enterOuterAlt(_localctx, 1);
        setState(285); 
        _errHandler->sync(this);
        alt = 1;
        do {
          switch (alt) {
            case 1: {
                  setState(285);
                  _errHandler->sync(this);
                  switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
                  case 1: {
                    setState(283);
                    constraint();
                    break;
                  }

                  case 2: {
                    setState(284);
                    intervalexpr();
                    break;
                  }

                  }
                  break;
                }

          default:
            throw NoViableAltException(this);
          }
          setState(287); 
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx);
        } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
        break;
      }

      case HybridAutomatonParser::TRUE: {
        enterOuterAlt(_localctx, 2);
        setState(289);
        match(HybridAutomatonParser::TRUE);
        break;
      }

      case HybridAutomatonParser::FALSE: {
        enterOuterAlt(_localctx, 3);
        setState(290);
        match(HybridAutomatonParser::FALSE);
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

//----------------- ReplacedexprContext ------------------------------------------------------------------

HybridAutomatonParser::ReplacedexprContext::ReplacedexprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> HybridAutomatonParser::ReplacedexprContext::NUMBER() {
  return getTokens(HybridAutomatonParser::NUMBER);
}

tree::TerminalNode* HybridAutomatonParser::ReplacedexprContext::NUMBER(size_t i) {
  return getToken(HybridAutomatonParser::NUMBER, i);
}

tree::TerminalNode* HybridAutomatonParser::ReplacedexprContext::EQUALS() {
  return getToken(HybridAutomatonParser::EQUALS, 0);
}

std::vector<tree::TerminalNode *> HybridAutomatonParser::ReplacedexprContext::MINUS() {
  return getTokens(HybridAutomatonParser::MINUS);
}

tree::TerminalNode* HybridAutomatonParser::ReplacedexprContext::MINUS(size_t i) {
  return getToken(HybridAutomatonParser::MINUS, i);
}


size_t HybridAutomatonParser::ReplacedexprContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleReplacedexpr;
}

antlrcpp::Any HybridAutomatonParser::ReplacedexprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitReplacedexpr(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::ReplacedexprContext* HybridAutomatonParser::replacedexpr() {
  ReplacedexprContext *_localctx = _tracker.createInstance<ReplacedexprContext>(_ctx, getState());
  enterRule(_localctx, 42, HybridAutomatonParser::RuleReplacedexpr);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(294);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HybridAutomatonParser::MINUS) {
      setState(293);
      match(HybridAutomatonParser::MINUS);
    }
    setState(296);
    match(HybridAutomatonParser::NUMBER);
    setState(297);
    match(HybridAutomatonParser::EQUALS);
    setState(299);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HybridAutomatonParser::MINUS) {
      setState(298);
      match(HybridAutomatonParser::MINUS);
    }
    setState(301);
    match(HybridAutomatonParser::NUMBER);
   
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
  enterRule(_localctx, 44, HybridAutomatonParser::RuleInit);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(303);
    match(HybridAutomatonParser::T__10);
    setState(304);
    match(HybridAutomatonParser::CBOPEN);
    setState(306); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(305);
      initstate();
      setState(308); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == HybridAutomatonParser::VARIABLE);
    setState(310);
    match(HybridAutomatonParser::CBCLOSE);
   
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
  enterRule(_localctx, 46, HybridAutomatonParser::RuleInitstate);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(312);
    match(HybridAutomatonParser::VARIABLE);
    setState(313);
    match(HybridAutomatonParser::CBOPEN);
    setState(314);
    constrset();
    setState(315);
    match(HybridAutomatonParser::CBCLOSE);
   
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

std::vector<HybridAutomatonParser::GbadstateContext *> HybridAutomatonParser::UnsafesetContext::gbadstate() {
  return getRuleContexts<HybridAutomatonParser::GbadstateContext>();
}

HybridAutomatonParser::GbadstateContext* HybridAutomatonParser::UnsafesetContext::gbadstate(size_t i) {
  return getRuleContext<HybridAutomatonParser::GbadstateContext>(i);
}

std::vector<HybridAutomatonParser::LbadstateContext *> HybridAutomatonParser::UnsafesetContext::lbadstate() {
  return getRuleContexts<HybridAutomatonParser::LbadstateContext>();
}

HybridAutomatonParser::LbadstateContext* HybridAutomatonParser::UnsafesetContext::lbadstate(size_t i) {
  return getRuleContext<HybridAutomatonParser::LbadstateContext>(i);
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
  enterRule(_localctx, 48, HybridAutomatonParser::RuleUnsafeset);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(317);
    match(HybridAutomatonParser::T__11);
    setState(318);
    match(HybridAutomatonParser::CBOPEN);
    setState(323);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << HybridAutomatonParser::TRUE)
      | (1ULL << HybridAutomatonParser::FALSE)
      | (1ULL << HybridAutomatonParser::PLUS)
      | (1ULL << HybridAutomatonParser::MINUS)
      | (1ULL << HybridAutomatonParser::NUMBER)
      | (1ULL << HybridAutomatonParser::VARIABLE))) != 0)) {
      setState(321);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)) {
      case 1: {
        setState(319);
        gbadstate();
        break;
      }

      case 2: {
        setState(320);
        lbadstate();
        break;
      }

      }
      setState(325);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(326);
    match(HybridAutomatonParser::CBCLOSE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LbadstateContext ------------------------------------------------------------------

HybridAutomatonParser::LbadstateContext::LbadstateContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HybridAutomatonParser::LbadstateContext::VARIABLE() {
  return getToken(HybridAutomatonParser::VARIABLE, 0);
}

HybridAutomatonParser::ConstrsetContext* HybridAutomatonParser::LbadstateContext::constrset() {
  return getRuleContext<HybridAutomatonParser::ConstrsetContext>(0);
}


size_t HybridAutomatonParser::LbadstateContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleLbadstate;
}

antlrcpp::Any HybridAutomatonParser::LbadstateContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitLbadstate(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::LbadstateContext* HybridAutomatonParser::lbadstate() {
  LbadstateContext *_localctx = _tracker.createInstance<LbadstateContext>(_ctx, getState());
  enterRule(_localctx, 50, HybridAutomatonParser::RuleLbadstate);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(328);
    match(HybridAutomatonParser::VARIABLE);
    setState(329);
    match(HybridAutomatonParser::CBOPEN);
    setState(331);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << HybridAutomatonParser::TRUE)
      | (1ULL << HybridAutomatonParser::FALSE)
      | (1ULL << HybridAutomatonParser::PLUS)
      | (1ULL << HybridAutomatonParser::MINUS)
      | (1ULL << HybridAutomatonParser::NUMBER)
      | (1ULL << HybridAutomatonParser::VARIABLE))) != 0)) {
      setState(330);
      constrset();
    }
    setState(333);
    match(HybridAutomatonParser::CBCLOSE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GbadstateContext ------------------------------------------------------------------

HybridAutomatonParser::GbadstateContext::GbadstateContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HybridAutomatonParser::ConstrsetContext* HybridAutomatonParser::GbadstateContext::constrset() {
  return getRuleContext<HybridAutomatonParser::ConstrsetContext>(0);
}


size_t HybridAutomatonParser::GbadstateContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleGbadstate;
}

antlrcpp::Any HybridAutomatonParser::GbadstateContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitGbadstate(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::GbadstateContext* HybridAutomatonParser::gbadstate() {
  GbadstateContext *_localctx = _tracker.createInstance<GbadstateContext>(_ctx, getState());
  enterRule(_localctx, 52, HybridAutomatonParser::RuleGbadstate);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(335);
    constrset();
   
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
  enterRule(_localctx, 54, HybridAutomatonParser::RuleJumps);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(337);
    match(HybridAutomatonParser::T__12);
    setState(338);
    match(HybridAutomatonParser::CBOPEN);
    setState(342);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HybridAutomatonParser::VARIABLE) {
      setState(339);
      transition();
      setState(344);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(345);
    match(HybridAutomatonParser::CBCLOSE);
   
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

std::vector<HybridAutomatonParser::LabelsContext *> HybridAutomatonParser::TransitionContext::labels() {
  return getRuleContexts<HybridAutomatonParser::LabelsContext>();
}

HybridAutomatonParser::LabelsContext* HybridAutomatonParser::TransitionContext::labels(size_t i) {
  return getRuleContext<HybridAutomatonParser::LabelsContext>(i);
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
  enterRule(_localctx, 56, HybridAutomatonParser::RuleTransition);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(347);
    fromto();
    setState(355);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << HybridAutomatonParser::T__13)
      | (1ULL << HybridAutomatonParser::T__14)
      | (1ULL << HybridAutomatonParser::T__15)
      | (1ULL << HybridAutomatonParser::T__16)
      | (1ULL << HybridAutomatonParser::PARALLELOTOPE)
      | (1ULL << HybridAutomatonParser::INTERVALAGG)
      | (1ULL << HybridAutomatonParser::BOX))) != 0)) {
      setState(353);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case HybridAutomatonParser::T__13: {
          setState(348);
          urgent();
          break;
        }

        case HybridAutomatonParser::T__14: {
          setState(349);
          guard();
          break;
        }

        case HybridAutomatonParser::T__15: {
          setState(350);
          resetfct();
          break;
        }

        case HybridAutomatonParser::PARALLELOTOPE:
        case HybridAutomatonParser::INTERVALAGG:
        case HybridAutomatonParser::BOX: {
          setState(351);
          aggregation();
          break;
        }

        case HybridAutomatonParser::T__16: {
          setState(352);
          labels();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(357);
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
  enterRule(_localctx, 58, HybridAutomatonParser::RuleFromto);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(358);
    match(HybridAutomatonParser::VARIABLE);
    setState(359);
    match(HybridAutomatonParser::JUMP);
    setState(360);
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
  enterRule(_localctx, 60, HybridAutomatonParser::RuleUrgent);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(362);
    match(HybridAutomatonParser::T__13);
   
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
  enterRule(_localctx, 62, HybridAutomatonParser::RuleGuard);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(364);
    match(HybridAutomatonParser::T__14);
    setState(365);
    match(HybridAutomatonParser::CBOPEN);
    setState(367);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << HybridAutomatonParser::TRUE)
      | (1ULL << HybridAutomatonParser::FALSE)
      | (1ULL << HybridAutomatonParser::PLUS)
      | (1ULL << HybridAutomatonParser::MINUS)
      | (1ULL << HybridAutomatonParser::NUMBER)
      | (1ULL << HybridAutomatonParser::VARIABLE))) != 0)) {
      setState(366);
      constrset();
    }
    setState(369);
    match(HybridAutomatonParser::CBCLOSE);
   
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
  enterRule(_localctx, 64, HybridAutomatonParser::RuleAllocation);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(371);
    match(HybridAutomatonParser::VARIABLE);
    setState(372);
    match(HybridAutomatonParser::DEFINE);
    setState(375);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case HybridAutomatonParser::PLUS:
      case HybridAutomatonParser::MINUS:
      case HybridAutomatonParser::NUMBER:
      case HybridAutomatonParser::VARIABLE: {
        setState(373);
        polynom();
        break;
      }

      case HybridAutomatonParser::SBOPEN: {
        setState(374);
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
  enterRule(_localctx, 66, HybridAutomatonParser::RuleResetfct);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(377);
    match(HybridAutomatonParser::T__15);
    setState(378);
    match(HybridAutomatonParser::CBOPEN);
    setState(382);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HybridAutomatonParser::VARIABLE) {
      setState(379);
      allocation();
      setState(384);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(385);
    match(HybridAutomatonParser::CBCLOSE);
   
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

tree::TerminalNode* HybridAutomatonParser::AggregationContext::INTERVALAGG() {
  return getToken(HybridAutomatonParser::INTERVALAGG, 0);
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
  enterRule(_localctx, 68, HybridAutomatonParser::RuleAggregation);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(387);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << HybridAutomatonParser::PARALLELOTOPE)
      | (1ULL << HybridAutomatonParser::INTERVALAGG)
      | (1ULL << HybridAutomatonParser::BOX))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(388);
    match(HybridAutomatonParser::CBOPEN);
    setState(389);
    match(HybridAutomatonParser::CBCLOSE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LabelsContext ------------------------------------------------------------------

HybridAutomatonParser::LabelsContext::LabelsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridAutomatonParser::LabelContext *> HybridAutomatonParser::LabelsContext::label() {
  return getRuleContexts<HybridAutomatonParser::LabelContext>();
}

HybridAutomatonParser::LabelContext* HybridAutomatonParser::LabelsContext::label(size_t i) {
  return getRuleContext<HybridAutomatonParser::LabelContext>(i);
}


size_t HybridAutomatonParser::LabelsContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleLabels;
}

antlrcpp::Any HybridAutomatonParser::LabelsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitLabels(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::LabelsContext* HybridAutomatonParser::labels() {
  LabelsContext *_localctx = _tracker.createInstance<LabelsContext>(_ctx, getState());
  enterRule(_localctx, 70, HybridAutomatonParser::RuleLabels);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(391);
    match(HybridAutomatonParser::T__16);
    setState(392);
    match(HybridAutomatonParser::CBOPEN);
    setState(396);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HybridAutomatonParser::VARIABLE) {
      setState(393);
      label();
      setState(398);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(399);
    match(HybridAutomatonParser::CBCLOSE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LabelContext ------------------------------------------------------------------

HybridAutomatonParser::LabelContext::LabelContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HybridAutomatonParser::LabelContext::VARIABLE() {
  return getToken(HybridAutomatonParser::VARIABLE, 0);
}


size_t HybridAutomatonParser::LabelContext::getRuleIndex() const {
  return HybridAutomatonParser::RuleLabel;
}

antlrcpp::Any HybridAutomatonParser::LabelContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HybridAutomatonVisitor*>(visitor))
    return parserVisitor->visitLabel(this);
  else
    return visitor->visitChildren(this);
}

HybridAutomatonParser::LabelContext* HybridAutomatonParser::label() {
  LabelContext *_localctx = _tracker.createInstance<LabelContext>(_ctx, getState());
  enterRule(_localctx, 72, HybridAutomatonParser::RuleLabel);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(401);
    match(HybridAutomatonParser::VARIABLE);
   
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
  enterRule(_localctx, 74, HybridAutomatonParser::RuleSetting);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(403);
    match(HybridAutomatonParser::T__17);
    setState(404);
    match(HybridAutomatonParser::CBOPEN);
    setState(418);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << HybridAutomatonParser::T__18)
      | (1ULL << HybridAutomatonParser::T__19)
      | (1ULL << HybridAutomatonParser::T__20)
      | (1ULL << HybridAutomatonParser::T__21)
      | (1ULL << HybridAutomatonParser::T__22)
      | (1ULL << HybridAutomatonParser::T__23)
      | (1ULL << HybridAutomatonParser::T__24)
      | (1ULL << HybridAutomatonParser::T__25)
      | (1ULL << HybridAutomatonParser::T__26)
      | (1ULL << HybridAutomatonParser::T__27)
      | (1ULL << HybridAutomatonParser::T__28))) != 0)) {
      setState(416);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case HybridAutomatonParser::T__18: {
          setState(405);
          fixedsteps();
          break;
        }

        case HybridAutomatonParser::T__19: {
          setState(406);
          time();
          break;
        }

        case HybridAutomatonParser::T__24: {
          setState(407);
          remainder();
          break;
        }

        case HybridAutomatonParser::T__25: {
          setState(408);
          identity();
          break;
        }

        case HybridAutomatonParser::T__20: {
          setState(409);
          plotsetting();
          break;
        }

        case HybridAutomatonParser::T__26: {
          setState(410);
          fixedorders();
          break;
        }

        case HybridAutomatonParser::T__27: {
          setState(411);
          cutoff();
          break;
        }

        case HybridAutomatonParser::T__28: {
          setState(412);
          precision();
          break;
        }

        case HybridAutomatonParser::T__21: {
          setState(413);
          filename();
          break;
        }

        case HybridAutomatonParser::T__22: {
          setState(414);
          maxjumps();
          break;
        }

        case HybridAutomatonParser::T__23: {
          setState(415);
          print();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(420);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(421);
    match(HybridAutomatonParser::CBCLOSE);
   
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
  enterRule(_localctx, 76, HybridAutomatonParser::RuleFixedsteps);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(423);
    match(HybridAutomatonParser::T__18);
    setState(424);
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
  enterRule(_localctx, 78, HybridAutomatonParser::RuleTime);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(426);
    match(HybridAutomatonParser::T__19);
    setState(427);
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
  enterRule(_localctx, 80, HybridAutomatonParser::RulePlotsetting);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(429);
    match(HybridAutomatonParser::T__20);
    setState(430);
    match(HybridAutomatonParser::VARIABLE);
    setState(437);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HybridAutomatonParser::COMMA) {
      setState(433); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(431);
        match(HybridAutomatonParser::COMMA);
        setState(432);
        match(HybridAutomatonParser::VARIABLE);
        setState(435); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == HybridAutomatonParser::COMMA);
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
  enterRule(_localctx, 82, HybridAutomatonParser::RuleFilename);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(439);
    match(HybridAutomatonParser::T__21);
    setState(440);
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
  enterRule(_localctx, 84, HybridAutomatonParser::RuleMaxjumps);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(442);
    match(HybridAutomatonParser::T__22);
    setState(443);
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
  enterRule(_localctx, 86, HybridAutomatonParser::RulePrint);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(445);
    match(HybridAutomatonParser::T__23);
    setState(446);
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
  enterRule(_localctx, 88, HybridAutomatonParser::RuleRemainder);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(448);
    match(HybridAutomatonParser::T__24);
    setState(449);
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
  enterRule(_localctx, 90, HybridAutomatonParser::RuleIdentity);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(451);
    match(HybridAutomatonParser::T__25);
   
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
  enterRule(_localctx, 92, HybridAutomatonParser::RuleFixedorders);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(453);
    match(HybridAutomatonParser::T__26);
    setState(454);
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
  enterRule(_localctx, 94, HybridAutomatonParser::RuleCutoff);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(456);
    match(HybridAutomatonParser::T__27);
    setState(457);
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
  enterRule(_localctx, 96, HybridAutomatonParser::RulePrecision);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(459);
    match(HybridAutomatonParser::T__28);
    setState(460);
    match(HybridAutomatonParser::NUMBER);
   
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
  "start", "old", "automaton", "comp", "vardeclaration", "constantdeclaration", 
  "globalvardeclaration", "component", "modes", "location", "activities", 
  "invariants", "constantexpr", "connector", "term", "polynom", "interval", 
  "equation", "constraint", "intervalexpr", "constrset", "replacedexpr", 
  "init", "initstate", "unsafeset", "lbadstate", "gbadstate", "jumps", "transition", 
  "fromto", "urgent", "guard", "allocation", "resetfct", "aggregation", 
  "labels", "label", "setting", "fixedsteps", "time", "plotsetting", "filename", 
  "maxjumps", "print", "remainder", "identity", "fixedorders", "cutoff", 
  "precision"
};

std::vector<std::string> HybridAutomatonParser::_literalNames = {
  "", "'hybrid reachability'", "'components'", "'state var'", "'global state var'", 
  "'modes'", "'poly ode 1'", "'poly ode 2'", "'poly ode 3'", "'linear ode'", 
  "'inv'", "'init'", "'unsafe set'", "'jumps'", "'urgent'", "'guard'", "'reset'", 
  "'label'", "'setting'", "'fixed steps'", "'time'", "'gnuplot octagon'", 
  "'output'", "'max jumps'", "'print'", "'remainder estimation'", "'identity precondition'", 
  "'fixed orders'", "'cutoff'", "'precision'", "'in'", "'true'", "'false'", 
  "'par'", "", "'='", "", "'+'", "'-'", "'*'", "'['", "']'", "'{'", "'}'", 
  "','", "", "", "", "", "'parallelotope aggregation'", "'interval aggregation'", 
  "'box aggregation'", "'->'", "':='"
};

std::vector<std::string> HybridAutomatonParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "IN", "TRUE", "FALSE", 
  "PAR", "COMMENT", "EQUALS", "BOOLRELATION", "PLUS", "MINUS", "TIMES", 
  "SBOPEN", "SBCLOSE", "CBOPEN", "CBCLOSE", "COMMA", "NUMBER", "CONSTANT", 
  "VARIABLE", "WS", "PARALLELOTOPE", "INTERVALAGG", "BOX", "JUMP", "DEFINE", 
  "EXPONENTIAL"
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
    0x3, 0x38, 0x1d1, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
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
    0x32, 0x3, 0x2, 0x3, 0x2, 0x5, 0x2, 0x67, 0xa, 0x2, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x6e, 0xa, 0x3, 0x3, 0x4, 0x3, 
    0x4, 0x5, 0x4, 0x72, 0xa, 0x4, 0x3, 0x4, 0x5, 0x4, 0x75, 0xa, 0x4, 0x3, 
    0x4, 0x3, 0x4, 0x3, 0x4, 0x6, 0x4, 0x7a, 0xa, 0x4, 0xd, 0x4, 0xe, 0x4, 
    0x7b, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x5, 0x5, 0x82, 0xa, 0x5, 
    0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x6, 0x5, 0x87, 0xa, 0x5, 0xd, 0x5, 0xe, 
    0x5, 0x88, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 
    0x3, 0x6, 0x6, 0x6, 0x92, 0xa, 0x6, 0xd, 0x6, 0xe, 0x6, 0x93, 0x5, 0x6, 
    0x96, 0xa, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x7, 0x7, 0x9c, 
    0xa, 0x7, 0xc, 0x7, 0xe, 0x7, 0x9f, 0xb, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 
    0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x6, 0x8, 0xa7, 0xa, 0x8, 0xd, 0x8, 
    0xe, 0x8, 0xa8, 0x5, 0x8, 0xab, 0xa, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 
    0x3, 0x9, 0x3, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x7, 0xa, 0xb5, 0xa, 
    0xa, 0xc, 0xa, 0xe, 0xa, 0xb8, 0xb, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xb, 
    0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x7, 0xb, 0xc0, 0xa, 0xb, 0xc, 0xb, 0xe, 
    0xb, 0xc3, 0xb, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 
    0x6, 0xc, 0xca, 0xa, 0xc, 0xd, 0xc, 0xe, 0xc, 0xcb, 0x3, 0xc, 0x3, 0xc, 
    0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x5, 0xd, 0xd3, 0xa, 0xd, 0x3, 0xd, 0x3, 
    0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x5, 0xe, 0xda, 0xa, 0xe, 0x3, 0xe, 
    0x3, 0xe, 0x3, 0xe, 0x3, 0xf, 0x3, 0xf, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 
    0x7, 0x10, 0xe4, 0xa, 0x10, 0xc, 0x10, 0xe, 0x10, 0xe7, 0xb, 0x10, 0x3, 
    0x10, 0x7, 0x10, 0xea, 0xa, 0x10, 0xc, 0x10, 0xe, 0x10, 0xed, 0xb, 0x10, 
    0x3, 0x11, 0x7, 0x11, 0xf0, 0xa, 0x11, 0xc, 0x11, 0xe, 0x11, 0xf3, 0xb, 
    0x11, 0x3, 0x11, 0x3, 0x11, 0x6, 0x11, 0xf7, 0xa, 0x11, 0xd, 0x11, 0xe, 
    0x11, 0xf8, 0x3, 0x11, 0x3, 0x11, 0x7, 0x11, 0xfd, 0xa, 0x11, 0xc, 0x11, 
    0xe, 0x11, 0x100, 0xb, 0x11, 0x3, 0x12, 0x3, 0x12, 0x5, 0x12, 0x104, 
    0xa, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x5, 0x12, 0x109, 0xa, 0x12, 
    0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 
    0x13, 0x3, 0x13, 0x3, 0x13, 0x5, 0x13, 0x114, 0xa, 0x13, 0x3, 0x14, 
    0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 
    0x15, 0x3, 0x16, 0x3, 0x16, 0x6, 0x16, 0x120, 0xa, 0x16, 0xd, 0x16, 
    0xe, 0x16, 0x121, 0x3, 0x16, 0x3, 0x16, 0x5, 0x16, 0x126, 0xa, 0x16, 
    0x3, 0x17, 0x5, 0x17, 0x129, 0xa, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 
    0x5, 0x17, 0x12e, 0xa, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x18, 0x3, 0x18, 
    0x3, 0x18, 0x6, 0x18, 0x135, 0xa, 0x18, 0xd, 0x18, 0xe, 0x18, 0x136, 
    0x3, 0x18, 0x3, 0x18, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 
    0x19, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x7, 0x1a, 0x144, 
    0xa, 0x1a, 0xc, 0x1a, 0xe, 0x1a, 0x147, 0xb, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 
    0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x5, 0x1b, 0x14e, 0xa, 0x1b, 0x3, 0x1b, 
    0x3, 0x1b, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x7, 
    0x1d, 0x157, 0xa, 0x1d, 0xc, 0x1d, 0xe, 0x1d, 0x15a, 0xb, 0x1d, 0x3, 
    0x1d, 0x3, 0x1d, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 
    0x3, 0x1e, 0x7, 0x1e, 0x164, 0xa, 0x1e, 0xc, 0x1e, 0xe, 0x1e, 0x167, 
    0xb, 0x1e, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x20, 0x3, 
    0x20, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x5, 0x21, 0x172, 0xa, 0x21, 
    0x3, 0x21, 0x3, 0x21, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x5, 
    0x22, 0x17a, 0xa, 0x22, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x7, 0x23, 
    0x17f, 0xa, 0x23, 0xc, 0x23, 0xe, 0x23, 0x182, 0xb, 0x23, 0x3, 0x23, 
    0x3, 0x23, 0x3, 0x24, 0x3, 0x24, 0x3, 0x24, 0x3, 0x24, 0x3, 0x25, 0x3, 
    0x25, 0x3, 0x25, 0x7, 0x25, 0x18d, 0xa, 0x25, 0xc, 0x25, 0xe, 0x25, 
    0x190, 0xb, 0x25, 0x3, 0x25, 0x3, 0x25, 0x3, 0x26, 0x3, 0x26, 0x3, 0x27, 
    0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 
    0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x7, 0x27, 
    0x1a3, 0xa, 0x27, 0xc, 0x27, 0xe, 0x27, 0x1a6, 0xb, 0x27, 0x3, 0x27, 
    0x3, 0x27, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 0x3, 0x29, 0x3, 0x29, 0x3, 
    0x29, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x6, 0x2a, 0x1b4, 
    0xa, 0x2a, 0xd, 0x2a, 0xe, 0x2a, 0x1b5, 0x5, 0x2a, 0x1b8, 0xa, 0x2a, 
    0x3, 0x2b, 0x3, 0x2b, 0x3, 0x2b, 0x3, 0x2c, 0x3, 0x2c, 0x3, 0x2c, 0x3, 
    0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2f, 
    0x3, 0x2f, 0x3, 0x30, 0x3, 0x30, 0x3, 0x30, 0x3, 0x31, 0x3, 0x31, 0x3, 
    0x31, 0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 0x2, 0x2, 0x33, 0x2, 
    0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 
    0x1e, 0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e, 0x30, 0x32, 0x34, 
    0x36, 0x38, 0x3a, 0x3c, 0x3e, 0x40, 0x42, 0x44, 0x46, 0x48, 0x4a, 0x4c, 
    0x4e, 0x50, 0x52, 0x54, 0x56, 0x58, 0x5a, 0x5c, 0x5e, 0x60, 0x62, 0x2, 
    0x7, 0x3, 0x2, 0x8, 0xb, 0x3, 0x2, 0x27, 0x28, 0x4, 0x2, 0x2f, 0x2f, 
    0x31, 0x31, 0x3, 0x2, 0x25, 0x26, 0x3, 0x2, 0x33, 0x35, 0x2, 0x1da, 
    0x2, 0x66, 0x3, 0x2, 0x2, 0x2, 0x4, 0x68, 0x3, 0x2, 0x2, 0x2, 0x6, 0x6f, 
    0x3, 0x2, 0x2, 0x2, 0x8, 0x7d, 0x3, 0x2, 0x2, 0x2, 0xa, 0x8d, 0x3, 0x2, 
    0x2, 0x2, 0xc, 0x97, 0x3, 0x2, 0x2, 0x2, 0xe, 0xa2, 0x3, 0x2, 0x2, 0x2, 
    0x10, 0xac, 0x3, 0x2, 0x2, 0x2, 0x12, 0xb1, 0x3, 0x2, 0x2, 0x2, 0x14, 
    0xbb, 0x3, 0x2, 0x2, 0x2, 0x16, 0xc6, 0x3, 0x2, 0x2, 0x2, 0x18, 0xcf, 
    0x3, 0x2, 0x2, 0x2, 0x1a, 0xd6, 0x3, 0x2, 0x2, 0x2, 0x1c, 0xde, 0x3, 
    0x2, 0x2, 0x2, 0x1e, 0xe0, 0x3, 0x2, 0x2, 0x2, 0x20, 0xf1, 0x3, 0x2, 
    0x2, 0x2, 0x22, 0x101, 0x3, 0x2, 0x2, 0x2, 0x24, 0x10d, 0x3, 0x2, 0x2, 
    0x2, 0x26, 0x115, 0x3, 0x2, 0x2, 0x2, 0x28, 0x119, 0x3, 0x2, 0x2, 0x2, 
    0x2a, 0x125, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x128, 0x3, 0x2, 0x2, 0x2, 0x2e, 
    0x131, 0x3, 0x2, 0x2, 0x2, 0x30, 0x13a, 0x3, 0x2, 0x2, 0x2, 0x32, 0x13f, 
    0x3, 0x2, 0x2, 0x2, 0x34, 0x14a, 0x3, 0x2, 0x2, 0x2, 0x36, 0x151, 0x3, 
    0x2, 0x2, 0x2, 0x38, 0x153, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x15d, 0x3, 0x2, 
    0x2, 0x2, 0x3c, 0x168, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x16c, 0x3, 0x2, 0x2, 
    0x2, 0x40, 0x16e, 0x3, 0x2, 0x2, 0x2, 0x42, 0x175, 0x3, 0x2, 0x2, 0x2, 
    0x44, 0x17b, 0x3, 0x2, 0x2, 0x2, 0x46, 0x185, 0x3, 0x2, 0x2, 0x2, 0x48, 
    0x189, 0x3, 0x2, 0x2, 0x2, 0x4a, 0x193, 0x3, 0x2, 0x2, 0x2, 0x4c, 0x195, 
    0x3, 0x2, 0x2, 0x2, 0x4e, 0x1a9, 0x3, 0x2, 0x2, 0x2, 0x50, 0x1ac, 0x3, 
    0x2, 0x2, 0x2, 0x52, 0x1af, 0x3, 0x2, 0x2, 0x2, 0x54, 0x1b9, 0x3, 0x2, 
    0x2, 0x2, 0x56, 0x1bc, 0x3, 0x2, 0x2, 0x2, 0x58, 0x1bf, 0x3, 0x2, 0x2, 
    0x2, 0x5a, 0x1c2, 0x3, 0x2, 0x2, 0x2, 0x5c, 0x1c5, 0x3, 0x2, 0x2, 0x2, 
    0x5e, 0x1c7, 0x3, 0x2, 0x2, 0x2, 0x60, 0x1ca, 0x3, 0x2, 0x2, 0x2, 0x62, 
    0x1cd, 0x3, 0x2, 0x2, 0x2, 0x64, 0x67, 0x5, 0x4, 0x3, 0x2, 0x65, 0x67, 
    0x5, 0x8, 0x5, 0x2, 0x66, 0x64, 0x3, 0x2, 0x2, 0x2, 0x66, 0x65, 0x3, 
    0x2, 0x2, 0x2, 0x67, 0x3, 0x3, 0x2, 0x2, 0x2, 0x68, 0x69, 0x7, 0x3, 
    0x2, 0x2, 0x69, 0x6a, 0x7, 0x2c, 0x2, 0x2, 0x6a, 0x6b, 0x5, 0x6, 0x4, 
    0x2, 0x6b, 0x6d, 0x7, 0x2d, 0x2, 0x2, 0x6c, 0x6e, 0x5, 0x32, 0x1a, 0x2, 
    0x6d, 0x6c, 0x3, 0x2, 0x2, 0x2, 0x6d, 0x6e, 0x3, 0x2, 0x2, 0x2, 0x6e, 
    0x5, 0x3, 0x2, 0x2, 0x2, 0x6f, 0x71, 0x5, 0xa, 0x6, 0x2, 0x70, 0x72, 
    0x5, 0xc, 0x7, 0x2, 0x71, 0x70, 0x3, 0x2, 0x2, 0x2, 0x71, 0x72, 0x3, 
    0x2, 0x2, 0x2, 0x72, 0x74, 0x3, 0x2, 0x2, 0x2, 0x73, 0x75, 0x5, 0x4c, 
    0x27, 0x2, 0x74, 0x73, 0x3, 0x2, 0x2, 0x2, 0x74, 0x75, 0x3, 0x2, 0x2, 
    0x2, 0x75, 0x76, 0x3, 0x2, 0x2, 0x2, 0x76, 0x77, 0x5, 0x12, 0xa, 0x2, 
    0x77, 0x79, 0x5, 0x38, 0x1d, 0x2, 0x78, 0x7a, 0x5, 0x2e, 0x18, 0x2, 
    0x79, 0x78, 0x3, 0x2, 0x2, 0x2, 0x7a, 0x7b, 0x3, 0x2, 0x2, 0x2, 0x7b, 
    0x79, 0x3, 0x2, 0x2, 0x2, 0x7b, 0x7c, 0x3, 0x2, 0x2, 0x2, 0x7c, 0x7, 
    0x3, 0x2, 0x2, 0x2, 0x7d, 0x7e, 0x5, 0x4c, 0x27, 0x2, 0x7e, 0x7f, 0x7, 
    0x3, 0x2, 0x2, 0x7f, 0x81, 0x7, 0x2c, 0x2, 0x2, 0x80, 0x82, 0x5, 0xe, 
    0x8, 0x2, 0x81, 0x80, 0x3, 0x2, 0x2, 0x2, 0x81, 0x82, 0x3, 0x2, 0x2, 
    0x2, 0x82, 0x83, 0x3, 0x2, 0x2, 0x2, 0x83, 0x84, 0x7, 0x4, 0x2, 0x2, 
    0x84, 0x86, 0x7, 0x2c, 0x2, 0x2, 0x85, 0x87, 0x5, 0x10, 0x9, 0x2, 0x86, 
    0x85, 0x3, 0x2, 0x2, 0x2, 0x87, 0x88, 0x3, 0x2, 0x2, 0x2, 0x88, 0x86, 
    0x3, 0x2, 0x2, 0x2, 0x88, 0x89, 0x3, 0x2, 0x2, 0x2, 0x89, 0x8a, 0x3, 
    0x2, 0x2, 0x2, 0x8a, 0x8b, 0x7, 0x2d, 0x2, 0x2, 0x8b, 0x8c, 0x7, 0x2d, 
    0x2, 0x2, 0x8c, 0x9, 0x3, 0x2, 0x2, 0x2, 0x8d, 0x8e, 0x7, 0x5, 0x2, 
    0x2, 0x8e, 0x95, 0x7, 0x31, 0x2, 0x2, 0x8f, 0x90, 0x7, 0x2e, 0x2, 0x2, 
    0x90, 0x92, 0x7, 0x31, 0x2, 0x2, 0x91, 0x8f, 0x3, 0x2, 0x2, 0x2, 0x92, 
    0x93, 0x3, 0x2, 0x2, 0x2, 0x93, 0x91, 0x3, 0x2, 0x2, 0x2, 0x93, 0x94, 
    0x3, 0x2, 0x2, 0x2, 0x94, 0x96, 0x3, 0x2, 0x2, 0x2, 0x95, 0x91, 0x3, 
    0x2, 0x2, 0x2, 0x95, 0x96, 0x3, 0x2, 0x2, 0x2, 0x96, 0xb, 0x3, 0x2, 
    0x2, 0x2, 0x97, 0x98, 0x7, 0x23, 0x2, 0x2, 0x98, 0x9d, 0x7, 0x2c, 0x2, 
    0x2, 0x99, 0x9c, 0x5, 0x1a, 0xe, 0x2, 0x9a, 0x9c, 0x5, 0x2c, 0x17, 0x2, 
    0x9b, 0x99, 0x3, 0x2, 0x2, 0x2, 0x9b, 0x9a, 0x3, 0x2, 0x2, 0x2, 0x9c, 
    0x9f, 0x3, 0x2, 0x2, 0x2, 0x9d, 0x9b, 0x3, 0x2, 0x2, 0x2, 0x9d, 0x9e, 
    0x3, 0x2, 0x2, 0x2, 0x9e, 0xa0, 0x3, 0x2, 0x2, 0x2, 0x9f, 0x9d, 0x3, 
    0x2, 0x2, 0x2, 0xa0, 0xa1, 0x7, 0x2d, 0x2, 0x2, 0xa1, 0xd, 0x3, 0x2, 
    0x2, 0x2, 0xa2, 0xa3, 0x7, 0x6, 0x2, 0x2, 0xa3, 0xaa, 0x7, 0x31, 0x2, 
    0x2, 0xa4, 0xa5, 0x7, 0x2e, 0x2, 0x2, 0xa5, 0xa7, 0x7, 0x31, 0x2, 0x2, 
    0xa6, 0xa4, 0x3, 0x2, 0x2, 0x2, 0xa7, 0xa8, 0x3, 0x2, 0x2, 0x2, 0xa8, 
    0xa6, 0x3, 0x2, 0x2, 0x2, 0xa8, 0xa9, 0x3, 0x2, 0x2, 0x2, 0xa9, 0xab, 
    0x3, 0x2, 0x2, 0x2, 0xaa, 0xa6, 0x3, 0x2, 0x2, 0x2, 0xaa, 0xab, 0x3, 
    0x2, 0x2, 0x2, 0xab, 0xf, 0x3, 0x2, 0x2, 0x2, 0xac, 0xad, 0x7, 0x31, 
    0x2, 0x2, 0xad, 0xae, 0x7, 0x2c, 0x2, 0x2, 0xae, 0xaf, 0x5, 0x6, 0x4, 
    0x2, 0xaf, 0xb0, 0x7, 0x2d, 0x2, 0x2, 0xb0, 0x11, 0x3, 0x2, 0x2, 0x2, 
    0xb1, 0xb2, 0x7, 0x7, 0x2, 0x2, 0xb2, 0xb6, 0x7, 0x2c, 0x2, 0x2, 0xb3, 
    0xb5, 0x5, 0x14, 0xb, 0x2, 0xb4, 0xb3, 0x3, 0x2, 0x2, 0x2, 0xb5, 0xb8, 
    0x3, 0x2, 0x2, 0x2, 0xb6, 0xb4, 0x3, 0x2, 0x2, 0x2, 0xb6, 0xb7, 0x3, 
    0x2, 0x2, 0x2, 0xb7, 0xb9, 0x3, 0x2, 0x2, 0x2, 0xb8, 0xb6, 0x3, 0x2, 
    0x2, 0x2, 0xb9, 0xba, 0x7, 0x2d, 0x2, 0x2, 0xba, 0x13, 0x3, 0x2, 0x2, 
    0x2, 0xbb, 0xbc, 0x7, 0x31, 0x2, 0x2, 0xbc, 0xbd, 0x7, 0x2c, 0x2, 0x2, 
    0xbd, 0xc1, 0x5, 0x16, 0xc, 0x2, 0xbe, 0xc0, 0x5, 0x18, 0xd, 0x2, 0xbf, 
    0xbe, 0x3, 0x2, 0x2, 0x2, 0xc0, 0xc3, 0x3, 0x2, 0x2, 0x2, 0xc1, 0xbf, 
    0x3, 0x2, 0x2, 0x2, 0xc1, 0xc2, 0x3, 0x2, 0x2, 0x2, 0xc2, 0xc4, 0x3, 
    0x2, 0x2, 0x2, 0xc3, 0xc1, 0x3, 0x2, 0x2, 0x2, 0xc4, 0xc5, 0x7, 0x2d, 
    0x2, 0x2, 0xc5, 0x15, 0x3, 0x2, 0x2, 0x2, 0xc6, 0xc7, 0x9, 0x2, 0x2, 
    0x2, 0xc7, 0xc9, 0x7, 0x2c, 0x2, 0x2, 0xc8, 0xca, 0x5, 0x24, 0x13, 0x2, 
    0xc9, 0xc8, 0x3, 0x2, 0x2, 0x2, 0xca, 0xcb, 0x3, 0x2, 0x2, 0x2, 0xcb, 
    0xc9, 0x3, 0x2, 0x2, 0x2, 0xcb, 0xcc, 0x3, 0x2, 0x2, 0x2, 0xcc, 0xcd, 
    0x3, 0x2, 0x2, 0x2, 0xcd, 0xce, 0x7, 0x2d, 0x2, 0x2, 0xce, 0x17, 0x3, 
    0x2, 0x2, 0x2, 0xcf, 0xd0, 0x7, 0xc, 0x2, 0x2, 0xd0, 0xd2, 0x7, 0x2c, 
    0x2, 0x2, 0xd1, 0xd3, 0x5, 0x2a, 0x16, 0x2, 0xd2, 0xd1, 0x3, 0x2, 0x2, 
    0x2, 0xd2, 0xd3, 0x3, 0x2, 0x2, 0x2, 0xd3, 0xd4, 0x3, 0x2, 0x2, 0x2, 
    0xd4, 0xd5, 0x7, 0x2d, 0x2, 0x2, 0xd5, 0x19, 0x3, 0x2, 0x2, 0x2, 0xd6, 
    0xd7, 0x7, 0x30, 0x2, 0x2, 0xd7, 0xd9, 0x7, 0x25, 0x2, 0x2, 0xd8, 0xda, 
    0x7, 0x28, 0x2, 0x2, 0xd9, 0xd8, 0x3, 0x2, 0x2, 0x2, 0xd9, 0xda, 0x3, 
    0x2, 0x2, 0x2, 0xda, 0xdb, 0x3, 0x2, 0x2, 0x2, 0xdb, 0xdc, 0x7, 0x2f, 
    0x2, 0x2, 0xdc, 0xdd, 0x8, 0xe, 0x1, 0x2, 0xdd, 0x1b, 0x3, 0x2, 0x2, 
    0x2, 0xde, 0xdf, 0x9, 0x3, 0x2, 0x2, 0xdf, 0x1d, 0x3, 0x2, 0x2, 0x2, 
    0xe0, 0xeb, 0x9, 0x4, 0x2, 0x2, 0xe1, 0xe5, 0x7, 0x29, 0x2, 0x2, 0xe2, 
    0xe4, 0x5, 0x1c, 0xf, 0x2, 0xe3, 0xe2, 0x3, 0x2, 0x2, 0x2, 0xe4, 0xe7, 
    0x3, 0x2, 0x2, 0x2, 0xe5, 0xe3, 0x3, 0x2, 0x2, 0x2, 0xe5, 0xe6, 0x3, 
    0x2, 0x2, 0x2, 0xe6, 0xe8, 0x3, 0x2, 0x2, 0x2, 0xe7, 0xe5, 0x3, 0x2, 
    0x2, 0x2, 0xe8, 0xea, 0x9, 0x4, 0x2, 0x2, 0xe9, 0xe1, 0x3, 0x2, 0x2, 
    0x2, 0xea, 0xed, 0x3, 0x2, 0x2, 0x2, 0xeb, 0xe9, 0x3, 0x2, 0x2, 0x2, 
    0xeb, 0xec, 0x3, 0x2, 0x2, 0x2, 0xec, 0x1f, 0x3, 0x2, 0x2, 0x2, 0xed, 
    0xeb, 0x3, 0x2, 0x2, 0x2, 0xee, 0xf0, 0x5, 0x1c, 0xf, 0x2, 0xef, 0xee, 
    0x3, 0x2, 0x2, 0x2, 0xf0, 0xf3, 0x3, 0x2, 0x2, 0x2, 0xf1, 0xef, 0x3, 
    0x2, 0x2, 0x2, 0xf1, 0xf2, 0x3, 0x2, 0x2, 0x2, 0xf2, 0xf4, 0x3, 0x2, 
    0x2, 0x2, 0xf3, 0xf1, 0x3, 0x2, 0x2, 0x2, 0xf4, 0xfe, 0x5, 0x1e, 0x10, 
    0x2, 0xf5, 0xf7, 0x5, 0x1c, 0xf, 0x2, 0xf6, 0xf5, 0x3, 0x2, 0x2, 0x2, 
    0xf7, 0xf8, 0x3, 0x2, 0x2, 0x2, 0xf8, 0xf6, 0x3, 0x2, 0x2, 0x2, 0xf8, 
    0xf9, 0x3, 0x2, 0x2, 0x2, 0xf9, 0xfa, 0x3, 0x2, 0x2, 0x2, 0xfa, 0xfb, 
    0x5, 0x1e, 0x10, 0x2, 0xfb, 0xfd, 0x3, 0x2, 0x2, 0x2, 0xfc, 0xf6, 0x3, 
    0x2, 0x2, 0x2, 0xfd, 0x100, 0x3, 0x2, 0x2, 0x2, 0xfe, 0xfc, 0x3, 0x2, 
    0x2, 0x2, 0xfe, 0xff, 0x3, 0x2, 0x2, 0x2, 0xff, 0x21, 0x3, 0x2, 0x2, 
    0x2, 0x100, 0xfe, 0x3, 0x2, 0x2, 0x2, 0x101, 0x103, 0x7, 0x2a, 0x2, 
    0x2, 0x102, 0x104, 0x7, 0x28, 0x2, 0x2, 0x103, 0x102, 0x3, 0x2, 0x2, 
    0x2, 0x103, 0x104, 0x3, 0x2, 0x2, 0x2, 0x104, 0x105, 0x3, 0x2, 0x2, 
    0x2, 0x105, 0x106, 0x9, 0x4, 0x2, 0x2, 0x106, 0x108, 0x7, 0x2e, 0x2, 
    0x2, 0x107, 0x109, 0x7, 0x28, 0x2, 0x2, 0x108, 0x107, 0x3, 0x2, 0x2, 
    0x2, 0x108, 0x109, 0x3, 0x2, 0x2, 0x2, 0x109, 0x10a, 0x3, 0x2, 0x2, 
    0x2, 0x10a, 0x10b, 0x9, 0x4, 0x2, 0x2, 0x10b, 0x10c, 0x7, 0x2b, 0x2, 
    0x2, 0x10c, 0x23, 0x3, 0x2, 0x2, 0x2, 0x10d, 0x10e, 0x7, 0x31, 0x2, 
    0x2, 0x10e, 0x10f, 0x7, 0x25, 0x2, 0x2, 0x10f, 0x113, 0x5, 0x20, 0x11, 
    0x2, 0x110, 0x111, 0x5, 0x1c, 0xf, 0x2, 0x111, 0x112, 0x5, 0x22, 0x12, 
    0x2, 0x112, 0x114, 0x3, 0x2, 0x2, 0x2, 0x113, 0x110, 0x3, 0x2, 0x2, 
    0x2, 0x113, 0x114, 0x3, 0x2, 0x2, 0x2, 0x114, 0x25, 0x3, 0x2, 0x2, 0x2, 
    0x115, 0x116, 0x5, 0x20, 0x11, 0x2, 0x116, 0x117, 0x9, 0x5, 0x2, 0x2, 
    0x117, 0x118, 0x5, 0x20, 0x11, 0x2, 0x118, 0x27, 0x3, 0x2, 0x2, 0x2, 
    0x119, 0x11a, 0x7, 0x31, 0x2, 0x2, 0x11a, 0x11b, 0x7, 0x20, 0x2, 0x2, 
    0x11b, 0x11c, 0x5, 0x22, 0x12, 0x2, 0x11c, 0x29, 0x3, 0x2, 0x2, 0x2, 
    0x11d, 0x120, 0x5, 0x26, 0x14, 0x2, 0x11e, 0x120, 0x5, 0x28, 0x15, 0x2, 
    0x11f, 0x11d, 0x3, 0x2, 0x2, 0x2, 0x11f, 0x11e, 0x3, 0x2, 0x2, 0x2, 
    0x120, 0x121, 0x3, 0x2, 0x2, 0x2, 0x121, 0x11f, 0x3, 0x2, 0x2, 0x2, 
    0x121, 0x122, 0x3, 0x2, 0x2, 0x2, 0x122, 0x126, 0x3, 0x2, 0x2, 0x2, 
    0x123, 0x126, 0x7, 0x21, 0x2, 0x2, 0x124, 0x126, 0x7, 0x22, 0x2, 0x2, 
    0x125, 0x11f, 0x3, 0x2, 0x2, 0x2, 0x125, 0x123, 0x3, 0x2, 0x2, 0x2, 
    0x125, 0x124, 0x3, 0x2, 0x2, 0x2, 0x126, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x127, 
    0x129, 0x7, 0x28, 0x2, 0x2, 0x128, 0x127, 0x3, 0x2, 0x2, 0x2, 0x128, 
    0x129, 0x3, 0x2, 0x2, 0x2, 0x129, 0x12a, 0x3, 0x2, 0x2, 0x2, 0x12a, 
    0x12b, 0x7, 0x2f, 0x2, 0x2, 0x12b, 0x12d, 0x7, 0x25, 0x2, 0x2, 0x12c, 
    0x12e, 0x7, 0x28, 0x2, 0x2, 0x12d, 0x12c, 0x3, 0x2, 0x2, 0x2, 0x12d, 
    0x12e, 0x3, 0x2, 0x2, 0x2, 0x12e, 0x12f, 0x3, 0x2, 0x2, 0x2, 0x12f, 
    0x130, 0x7, 0x2f, 0x2, 0x2, 0x130, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x131, 
    0x132, 0x7, 0xd, 0x2, 0x2, 0x132, 0x134, 0x7, 0x2c, 0x2, 0x2, 0x133, 
    0x135, 0x5, 0x30, 0x19, 0x2, 0x134, 0x133, 0x3, 0x2, 0x2, 0x2, 0x135, 
    0x136, 0x3, 0x2, 0x2, 0x2, 0x136, 0x134, 0x3, 0x2, 0x2, 0x2, 0x136, 
    0x137, 0x3, 0x2, 0x2, 0x2, 0x137, 0x138, 0x3, 0x2, 0x2, 0x2, 0x138, 
    0x139, 0x7, 0x2d, 0x2, 0x2, 0x139, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x13a, 
    0x13b, 0x7, 0x31, 0x2, 0x2, 0x13b, 0x13c, 0x7, 0x2c, 0x2, 0x2, 0x13c, 
    0x13d, 0x5, 0x2a, 0x16, 0x2, 0x13d, 0x13e, 0x7, 0x2d, 0x2, 0x2, 0x13e, 
    0x31, 0x3, 0x2, 0x2, 0x2, 0x13f, 0x140, 0x7, 0xe, 0x2, 0x2, 0x140, 0x145, 
    0x7, 0x2c, 0x2, 0x2, 0x141, 0x144, 0x5, 0x36, 0x1c, 0x2, 0x142, 0x144, 
    0x5, 0x34, 0x1b, 0x2, 0x143, 0x141, 0x3, 0x2, 0x2, 0x2, 0x143, 0x142, 
    0x3, 0x2, 0x2, 0x2, 0x144, 0x147, 0x3, 0x2, 0x2, 0x2, 0x145, 0x143, 
    0x3, 0x2, 0x2, 0x2, 0x145, 0x146, 0x3, 0x2, 0x2, 0x2, 0x146, 0x148, 
    0x3, 0x2, 0x2, 0x2, 0x147, 0x145, 0x3, 0x2, 0x2, 0x2, 0x148, 0x149, 
    0x7, 0x2d, 0x2, 0x2, 0x149, 0x33, 0x3, 0x2, 0x2, 0x2, 0x14a, 0x14b, 
    0x7, 0x31, 0x2, 0x2, 0x14b, 0x14d, 0x7, 0x2c, 0x2, 0x2, 0x14c, 0x14e, 
    0x5, 0x2a, 0x16, 0x2, 0x14d, 0x14c, 0x3, 0x2, 0x2, 0x2, 0x14d, 0x14e, 
    0x3, 0x2, 0x2, 0x2, 0x14e, 0x14f, 0x3, 0x2, 0x2, 0x2, 0x14f, 0x150, 
    0x7, 0x2d, 0x2, 0x2, 0x150, 0x35, 0x3, 0x2, 0x2, 0x2, 0x151, 0x152, 
    0x5, 0x2a, 0x16, 0x2, 0x152, 0x37, 0x3, 0x2, 0x2, 0x2, 0x153, 0x154, 
    0x7, 0xf, 0x2, 0x2, 0x154, 0x158, 0x7, 0x2c, 0x2, 0x2, 0x155, 0x157, 
    0x5, 0x3a, 0x1e, 0x2, 0x156, 0x155, 0x3, 0x2, 0x2, 0x2, 0x157, 0x15a, 
    0x3, 0x2, 0x2, 0x2, 0x158, 0x156, 0x3, 0x2, 0x2, 0x2, 0x158, 0x159, 
    0x3, 0x2, 0x2, 0x2, 0x159, 0x15b, 0x3, 0x2, 0x2, 0x2, 0x15a, 0x158, 
    0x3, 0x2, 0x2, 0x2, 0x15b, 0x15c, 0x7, 0x2d, 0x2, 0x2, 0x15c, 0x39, 
    0x3, 0x2, 0x2, 0x2, 0x15d, 0x165, 0x5, 0x3c, 0x1f, 0x2, 0x15e, 0x164, 
    0x5, 0x3e, 0x20, 0x2, 0x15f, 0x164, 0x5, 0x40, 0x21, 0x2, 0x160, 0x164, 
    0x5, 0x44, 0x23, 0x2, 0x161, 0x164, 0x5, 0x46, 0x24, 0x2, 0x162, 0x164, 
    0x5, 0x48, 0x25, 0x2, 0x163, 0x15e, 0x3, 0x2, 0x2, 0x2, 0x163, 0x15f, 
    0x3, 0x2, 0x2, 0x2, 0x163, 0x160, 0x3, 0x2, 0x2, 0x2, 0x163, 0x161, 
    0x3, 0x2, 0x2, 0x2, 0x163, 0x162, 0x3, 0x2, 0x2, 0x2, 0x164, 0x167, 
    0x3, 0x2, 0x2, 0x2, 0x165, 0x163, 0x3, 0x2, 0x2, 0x2, 0x165, 0x166, 
    0x3, 0x2, 0x2, 0x2, 0x166, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x167, 0x165, 0x3, 
    0x2, 0x2, 0x2, 0x168, 0x169, 0x7, 0x31, 0x2, 0x2, 0x169, 0x16a, 0x7, 
    0x36, 0x2, 0x2, 0x16a, 0x16b, 0x7, 0x31, 0x2, 0x2, 0x16b, 0x3d, 0x3, 
    0x2, 0x2, 0x2, 0x16c, 0x16d, 0x7, 0x10, 0x2, 0x2, 0x16d, 0x3f, 0x3, 
    0x2, 0x2, 0x2, 0x16e, 0x16f, 0x7, 0x11, 0x2, 0x2, 0x16f, 0x171, 0x7, 
    0x2c, 0x2, 0x2, 0x170, 0x172, 0x5, 0x2a, 0x16, 0x2, 0x171, 0x170, 0x3, 
    0x2, 0x2, 0x2, 0x171, 0x172, 0x3, 0x2, 0x2, 0x2, 0x172, 0x173, 0x3, 
    0x2, 0x2, 0x2, 0x173, 0x174, 0x7, 0x2d, 0x2, 0x2, 0x174, 0x41, 0x3, 
    0x2, 0x2, 0x2, 0x175, 0x176, 0x7, 0x31, 0x2, 0x2, 0x176, 0x179, 0x7, 
    0x37, 0x2, 0x2, 0x177, 0x17a, 0x5, 0x20, 0x11, 0x2, 0x178, 0x17a, 0x5, 
    0x22, 0x12, 0x2, 0x179, 0x177, 0x3, 0x2, 0x2, 0x2, 0x179, 0x178, 0x3, 
    0x2, 0x2, 0x2, 0x17a, 0x43, 0x3, 0x2, 0x2, 0x2, 0x17b, 0x17c, 0x7, 0x12, 
    0x2, 0x2, 0x17c, 0x180, 0x7, 0x2c, 0x2, 0x2, 0x17d, 0x17f, 0x5, 0x42, 
    0x22, 0x2, 0x17e, 0x17d, 0x3, 0x2, 0x2, 0x2, 0x17f, 0x182, 0x3, 0x2, 
    0x2, 0x2, 0x180, 0x17e, 0x3, 0x2, 0x2, 0x2, 0x180, 0x181, 0x3, 0x2, 
    0x2, 0x2, 0x181, 0x183, 0x3, 0x2, 0x2, 0x2, 0x182, 0x180, 0x3, 0x2, 
    0x2, 0x2, 0x183, 0x184, 0x7, 0x2d, 0x2, 0x2, 0x184, 0x45, 0x3, 0x2, 
    0x2, 0x2, 0x185, 0x186, 0x9, 0x6, 0x2, 0x2, 0x186, 0x187, 0x7, 0x2c, 
    0x2, 0x2, 0x187, 0x188, 0x7, 0x2d, 0x2, 0x2, 0x188, 0x47, 0x3, 0x2, 
    0x2, 0x2, 0x189, 0x18a, 0x7, 0x13, 0x2, 0x2, 0x18a, 0x18e, 0x7, 0x2c, 
    0x2, 0x2, 0x18b, 0x18d, 0x5, 0x4a, 0x26, 0x2, 0x18c, 0x18b, 0x3, 0x2, 
    0x2, 0x2, 0x18d, 0x190, 0x3, 0x2, 0x2, 0x2, 0x18e, 0x18c, 0x3, 0x2, 
    0x2, 0x2, 0x18e, 0x18f, 0x3, 0x2, 0x2, 0x2, 0x18f, 0x191, 0x3, 0x2, 
    0x2, 0x2, 0x190, 0x18e, 0x3, 0x2, 0x2, 0x2, 0x191, 0x192, 0x7, 0x2d, 
    0x2, 0x2, 0x192, 0x49, 0x3, 0x2, 0x2, 0x2, 0x193, 0x194, 0x7, 0x31, 
    0x2, 0x2, 0x194, 0x4b, 0x3, 0x2, 0x2, 0x2, 0x195, 0x196, 0x7, 0x14, 
    0x2, 0x2, 0x196, 0x1a4, 0x7, 0x2c, 0x2, 0x2, 0x197, 0x1a3, 0x5, 0x4e, 
    0x28, 0x2, 0x198, 0x1a3, 0x5, 0x50, 0x29, 0x2, 0x199, 0x1a3, 0x5, 0x5a, 
    0x2e, 0x2, 0x19a, 0x1a3, 0x5, 0x5c, 0x2f, 0x2, 0x19b, 0x1a3, 0x5, 0x52, 
    0x2a, 0x2, 0x19c, 0x1a3, 0x5, 0x5e, 0x30, 0x2, 0x19d, 0x1a3, 0x5, 0x60, 
    0x31, 0x2, 0x19e, 0x1a3, 0x5, 0x62, 0x32, 0x2, 0x19f, 0x1a3, 0x5, 0x54, 
    0x2b, 0x2, 0x1a0, 0x1a3, 0x5, 0x56, 0x2c, 0x2, 0x1a1, 0x1a3, 0x5, 0x58, 
    0x2d, 0x2, 0x1a2, 0x197, 0x3, 0x2, 0x2, 0x2, 0x1a2, 0x198, 0x3, 0x2, 
    0x2, 0x2, 0x1a2, 0x199, 0x3, 0x2, 0x2, 0x2, 0x1a2, 0x19a, 0x3, 0x2, 
    0x2, 0x2, 0x1a2, 0x19b, 0x3, 0x2, 0x2, 0x2, 0x1a2, 0x19c, 0x3, 0x2, 
    0x2, 0x2, 0x1a2, 0x19d, 0x3, 0x2, 0x2, 0x2, 0x1a2, 0x19e, 0x3, 0x2, 
    0x2, 0x2, 0x1a2, 0x19f, 0x3, 0x2, 0x2, 0x2, 0x1a2, 0x1a0, 0x3, 0x2, 
    0x2, 0x2, 0x1a2, 0x1a1, 0x3, 0x2, 0x2, 0x2, 0x1a3, 0x1a6, 0x3, 0x2, 
    0x2, 0x2, 0x1a4, 0x1a2, 0x3, 0x2, 0x2, 0x2, 0x1a4, 0x1a5, 0x3, 0x2, 
    0x2, 0x2, 0x1a5, 0x1a7, 0x3, 0x2, 0x2, 0x2, 0x1a6, 0x1a4, 0x3, 0x2, 
    0x2, 0x2, 0x1a7, 0x1a8, 0x7, 0x2d, 0x2, 0x2, 0x1a8, 0x4d, 0x3, 0x2, 
    0x2, 0x2, 0x1a9, 0x1aa, 0x7, 0x15, 0x2, 0x2, 0x1aa, 0x1ab, 0x7, 0x2f, 
    0x2, 0x2, 0x1ab, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x1ac, 0x1ad, 0x7, 0x16, 
    0x2, 0x2, 0x1ad, 0x1ae, 0x7, 0x2f, 0x2, 0x2, 0x1ae, 0x51, 0x3, 0x2, 
    0x2, 0x2, 0x1af, 0x1b0, 0x7, 0x17, 0x2, 0x2, 0x1b0, 0x1b7, 0x7, 0x31, 
    0x2, 0x2, 0x1b1, 0x1b2, 0x7, 0x2e, 0x2, 0x2, 0x1b2, 0x1b4, 0x7, 0x31, 
    0x2, 0x2, 0x1b3, 0x1b1, 0x3, 0x2, 0x2, 0x2, 0x1b4, 0x1b5, 0x3, 0x2, 
    0x2, 0x2, 0x1b5, 0x1b3, 0x3, 0x2, 0x2, 0x2, 0x1b5, 0x1b6, 0x3, 0x2, 
    0x2, 0x2, 0x1b6, 0x1b8, 0x3, 0x2, 0x2, 0x2, 0x1b7, 0x1b3, 0x3, 0x2, 
    0x2, 0x2, 0x1b7, 0x1b8, 0x3, 0x2, 0x2, 0x2, 0x1b8, 0x53, 0x3, 0x2, 0x2, 
    0x2, 0x1b9, 0x1ba, 0x7, 0x18, 0x2, 0x2, 0x1ba, 0x1bb, 0x7, 0x31, 0x2, 
    0x2, 0x1bb, 0x55, 0x3, 0x2, 0x2, 0x2, 0x1bc, 0x1bd, 0x7, 0x19, 0x2, 
    0x2, 0x1bd, 0x1be, 0x7, 0x2f, 0x2, 0x2, 0x1be, 0x57, 0x3, 0x2, 0x2, 
    0x2, 0x1bf, 0x1c0, 0x7, 0x1a, 0x2, 0x2, 0x1c0, 0x1c1, 0x7, 0x31, 0x2, 
    0x2, 0x1c1, 0x59, 0x3, 0x2, 0x2, 0x2, 0x1c2, 0x1c3, 0x7, 0x1b, 0x2, 
    0x2, 0x1c3, 0x1c4, 0x7, 0x38, 0x2, 0x2, 0x1c4, 0x5b, 0x3, 0x2, 0x2, 
    0x2, 0x1c5, 0x1c6, 0x7, 0x1c, 0x2, 0x2, 0x1c6, 0x5d, 0x3, 0x2, 0x2, 
    0x2, 0x1c7, 0x1c8, 0x7, 0x1d, 0x2, 0x2, 0x1c8, 0x1c9, 0x7, 0x2f, 0x2, 
    0x2, 0x1c9, 0x5f, 0x3, 0x2, 0x2, 0x2, 0x1ca, 0x1cb, 0x7, 0x1e, 0x2, 
    0x2, 0x1cb, 0x1cc, 0x7, 0x38, 0x2, 0x2, 0x1cc, 0x61, 0x3, 0x2, 0x2, 
    0x2, 0x1cd, 0x1ce, 0x7, 0x1f, 0x2, 0x2, 0x1ce, 0x1cf, 0x7, 0x2f, 0x2, 
    0x2, 0x1cf, 0x63, 0x3, 0x2, 0x2, 0x2, 0x30, 0x66, 0x6d, 0x71, 0x74, 
    0x7b, 0x81, 0x88, 0x93, 0x95, 0x9b, 0x9d, 0xa8, 0xaa, 0xb6, 0xc1, 0xcb, 
    0xd2, 0xd9, 0xe5, 0xeb, 0xf1, 0xf8, 0xfe, 0x103, 0x108, 0x113, 0x11f, 
    0x121, 0x125, 0x128, 0x12d, 0x136, 0x143, 0x145, 0x14d, 0x158, 0x163, 
    0x165, 0x171, 0x179, 0x180, 0x18e, 0x1a2, 0x1a4, 0x1b5, 0x1b7, 
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
