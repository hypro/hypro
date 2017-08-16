
// Generated from Expressions.g4 by ANTLR 4.7


#include "ExpressionsVisitor.h"

#include "ExpressionsParser.h"


using namespace antlrcpp;
using namespace antlr4;

ExpressionsParser::ExpressionsParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

ExpressionsParser::~ExpressionsParser() {
  delete _interpreter;
}

std::string ExpressionsParser::getGrammarFileName() const {
  return "Expressions.g4";
}

const std::vector<std::string>& ExpressionsParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& ExpressionsParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- ExpressionsContext ------------------------------------------------------------------

ExpressionsParser::ExpressionsContext::ExpressionsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ExpressionsParser::ExpressionContext *> ExpressionsParser::ExpressionsContext::expression() {
  return getRuleContexts<ExpressionsParser::ExpressionContext>();
}

ExpressionsParser::ExpressionContext* ExpressionsParser::ExpressionsContext::expression(size_t i) {
  return getRuleContext<ExpressionsParser::ExpressionContext>(i);
}


size_t ExpressionsParser::ExpressionsContext::getRuleIndex() const {
  return ExpressionsParser::RuleExpressions;
}

antlrcpp::Any ExpressionsParser::ExpressionsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExpressionsVisitor*>(visitor))
    return parserVisitor->visitExpressions(this);
  else
    return visitor->visitChildren(this);
}

ExpressionsParser::ExpressionsContext* ExpressionsParser::expressions() {
  ExpressionsContext *_localctx = _tracker.createInstance<ExpressionsContext>(_ctx, getState());
  enterRule(_localctx, 0, ExpressionsParser::RuleExpressions);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(56);
    expression();
    setState(61);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ExpressionsParser::T__0) {
      setState(57);
      match(ExpressionsParser::T__0);
      setState(58);
      expression();
      setState(63);
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

ExpressionsParser::OptExpressionContext::OptExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ExpressionsParser::ExpressionContext* ExpressionsParser::OptExpressionContext::expression() {
  return getRuleContext<ExpressionsParser::ExpressionContext>(0);
}


size_t ExpressionsParser::OptExpressionContext::getRuleIndex() const {
  return ExpressionsParser::RuleOptExpression;
}

antlrcpp::Any ExpressionsParser::OptExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExpressionsVisitor*>(visitor))
    return parserVisitor->visitOptExpression(this);
  else
    return visitor->visitChildren(this);
}

ExpressionsParser::OptExpressionContext* ExpressionsParser::optExpression() {
  OptExpressionContext *_localctx = _tracker.createInstance<OptExpressionContext>(_ctx, getState());
  enterRule(_localctx, 2, ExpressionsParser::RuleOptExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(65);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << ExpressionsParser::T__5)
      | (1ULL << ExpressionsParser::T__13)
      | (1ULL << ExpressionsParser::T__14)
      | (1ULL << ExpressionsParser::T__19)
      | (1ULL << ExpressionsParser::T__20)
      | (1ULL << ExpressionsParser::T__21)
      | (1ULL << ExpressionsParser::T__23)
      | (1ULL << ExpressionsParser::T__26)
      | (1ULL << ExpressionsParser::T__27)
      | (1ULL << ExpressionsParser::T__28)
      | (1ULL << ExpressionsParser::T__29)
      | (1ULL << ExpressionsParser::T__31)
      | (1ULL << ExpressionsParser::T__34)
      | (1ULL << ExpressionsParser::T__36)
      | (1ULL << ExpressionsParser::T__37)
      | (1ULL << ExpressionsParser::T__54)
      | (1ULL << ExpressionsParser::T__55)
      | (1ULL << ExpressionsParser::T__56)
      | (1ULL << ExpressionsParser::T__57)
      | (1ULL << ExpressionsParser::T__58)
      | (1ULL << ExpressionsParser::T__59)
      | (1ULL << ExpressionsParser::T__60)
      | (1ULL << ExpressionsParser::T__61)
      | (1ULL << ExpressionsParser::T__62))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (ExpressionsParser::T__63 - 64))
      | (1ULL << (ExpressionsParser::T__64 - 64))
      | (1ULL << (ExpressionsParser::T__65 - 64))
      | (1ULL << (ExpressionsParser::T__66 - 64))
      | (1ULL << (ExpressionsParser::T__67 - 64))
      | (1ULL << (ExpressionsParser::T__68 - 64))
      | (1ULL << (ExpressionsParser::T__69 - 64))
      | (1ULL << (ExpressionsParser::T__70 - 64))
      | (1ULL << (ExpressionsParser::T__71 - 64))
      | (1ULL << (ExpressionsParser::T__72 - 64))
      | (1ULL << (ExpressionsParser::T__73 - 64))
      | (1ULL << (ExpressionsParser::T__74 - 64))
      | (1ULL << (ExpressionsParser::T__75 - 64))
      | (1ULL << (ExpressionsParser::T__76 - 64))
      | (1ULL << (ExpressionsParser::T__77 - 64))
      | (1ULL << (ExpressionsParser::T__78 - 64))
      | (1ULL << (ExpressionsParser::T__79 - 64))
      | (1ULL << (ExpressionsParser::T__80 - 64))
      | (1ULL << (ExpressionsParser::T__81 - 64))
      | (1ULL << (ExpressionsParser::T__82 - 64))
      | (1ULL << (ExpressionsParser::T__83 - 64))
      | (1ULL << (ExpressionsParser::T__84 - 64))
      | (1ULL << (ExpressionsParser::T__85 - 64))
      | (1ULL << (ExpressionsParser::NUMBER - 64))
      | (1ULL << (ExpressionsParser::REALNUBER - 64))
      | (1ULL << (ExpressionsParser::STRING - 64))
      | (1ULL << (ExpressionsParser::IDENTIFIER - 64))
      | (1ULL << (ExpressionsParser::RELATIVENAME - 64))
      | (1ULL << (ExpressionsParser::ABSOLUTENAME - 64))
      | (1ULL << (ExpressionsParser::ROOTNAME - 64)))) != 0)) {
      setState(64);
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

ExpressionsParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ExpressionsParser::OrExpressionContext *> ExpressionsParser::ExpressionContext::orExpression() {
  return getRuleContexts<ExpressionsParser::OrExpressionContext>();
}

ExpressionsParser::OrExpressionContext* ExpressionsParser::ExpressionContext::orExpression(size_t i) {
  return getRuleContext<ExpressionsParser::OrExpressionContext>(i);
}


size_t ExpressionsParser::ExpressionContext::getRuleIndex() const {
  return ExpressionsParser::RuleExpression;
}

antlrcpp::Any ExpressionsParser::ExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExpressionsVisitor*>(visitor))
    return parserVisitor->visitExpression(this);
  else
    return visitor->visitChildren(this);
}

ExpressionsParser::ExpressionContext* ExpressionsParser::expression() {
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 4, ExpressionsParser::RuleExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(76);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(67);
      orExpression();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(68);
      orExpression();
      setState(69);
      match(ExpressionsParser::T__1);
      setState(70);
      orExpression();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(72);
      orExpression();
      setState(73);
      match(ExpressionsParser::T__2);
      setState(74);
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

//----------------- OrExpressionContext ------------------------------------------------------------------

ExpressionsParser::OrExpressionContext::OrExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ExpressionsParser::AndExpressionContext *> ExpressionsParser::OrExpressionContext::andExpression() {
  return getRuleContexts<ExpressionsParser::AndExpressionContext>();
}

ExpressionsParser::AndExpressionContext* ExpressionsParser::OrExpressionContext::andExpression(size_t i) {
  return getRuleContext<ExpressionsParser::AndExpressionContext>(i);
}


size_t ExpressionsParser::OrExpressionContext::getRuleIndex() const {
  return ExpressionsParser::RuleOrExpression;
}

antlrcpp::Any ExpressionsParser::OrExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExpressionsVisitor*>(visitor))
    return parserVisitor->visitOrExpression(this);
  else
    return visitor->visitChildren(this);
}

ExpressionsParser::OrExpressionContext* ExpressionsParser::orExpression() {
  OrExpressionContext *_localctx = _tracker.createInstance<OrExpressionContext>(_ctx, getState());
  enterRule(_localctx, 6, ExpressionsParser::RuleOrExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(78);
    andExpression();
    setState(83);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ExpressionsParser::T__3) {
      setState(79);
      match(ExpressionsParser::T__3);
      setState(80);
      andExpression();
      setState(85);
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

ExpressionsParser::AndExpressionContext::AndExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ExpressionsParser::CompareExpressionContext *> ExpressionsParser::AndExpressionContext::compareExpression() {
  return getRuleContexts<ExpressionsParser::CompareExpressionContext>();
}

ExpressionsParser::CompareExpressionContext* ExpressionsParser::AndExpressionContext::compareExpression(size_t i) {
  return getRuleContext<ExpressionsParser::CompareExpressionContext>(i);
}


size_t ExpressionsParser::AndExpressionContext::getRuleIndex() const {
  return ExpressionsParser::RuleAndExpression;
}

antlrcpp::Any ExpressionsParser::AndExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExpressionsVisitor*>(visitor))
    return parserVisitor->visitAndExpression(this);
  else
    return visitor->visitChildren(this);
}

ExpressionsParser::AndExpressionContext* ExpressionsParser::andExpression() {
  AndExpressionContext *_localctx = _tracker.createInstance<AndExpressionContext>(_ctx, getState());
  enterRule(_localctx, 8, ExpressionsParser::RuleAndExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(86);
    compareExpression();
    setState(91);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ExpressionsParser::T__4) {
      setState(87);
      match(ExpressionsParser::T__4);
      setState(88);
      compareExpression();
      setState(93);
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

ExpressionsParser::CompareExpressionContext::CompareExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ExpressionsParser::AddExpressionContext *> ExpressionsParser::CompareExpressionContext::addExpression() {
  return getRuleContexts<ExpressionsParser::AddExpressionContext>();
}

ExpressionsParser::AddExpressionContext* ExpressionsParser::CompareExpressionContext::addExpression(size_t i) {
  return getRuleContext<ExpressionsParser::AddExpressionContext>(i);
}


size_t ExpressionsParser::CompareExpressionContext::getRuleIndex() const {
  return ExpressionsParser::RuleCompareExpression;
}

antlrcpp::Any ExpressionsParser::CompareExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExpressionsVisitor*>(visitor))
    return parserVisitor->visitCompareExpression(this);
  else
    return visitor->visitChildren(this);
}

ExpressionsParser::CompareExpressionContext* ExpressionsParser::compareExpression() {
  CompareExpressionContext *_localctx = _tracker.createInstance<CompareExpressionContext>(_ctx, getState());
  enterRule(_localctx, 10, ExpressionsParser::RuleCompareExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(94);
    addExpression();
    setState(99);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(95);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << ExpressionsParser::T__5)
          | (1ULL << ExpressionsParser::T__6)
          | (1ULL << ExpressionsParser::T__7)
          | (1ULL << ExpressionsParser::T__8)
          | (1ULL << ExpressionsParser::T__9)
          | (1ULL << ExpressionsParser::T__10)
          | (1ULL << ExpressionsParser::T__11)
          | (1ULL << ExpressionsParser::T__12))) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(96);
        addExpression(); 
      }
      setState(101);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
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

ExpressionsParser::AddExpressionContext::AddExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ExpressionsParser::MulExpressionContext *> ExpressionsParser::AddExpressionContext::mulExpression() {
  return getRuleContexts<ExpressionsParser::MulExpressionContext>();
}

ExpressionsParser::MulExpressionContext* ExpressionsParser::AddExpressionContext::mulExpression(size_t i) {
  return getRuleContext<ExpressionsParser::MulExpressionContext>(i);
}


size_t ExpressionsParser::AddExpressionContext::getRuleIndex() const {
  return ExpressionsParser::RuleAddExpression;
}

antlrcpp::Any ExpressionsParser::AddExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExpressionsVisitor*>(visitor))
    return parserVisitor->visitAddExpression(this);
  else
    return visitor->visitChildren(this);
}

ExpressionsParser::AddExpressionContext* ExpressionsParser::addExpression() {
  AddExpressionContext *_localctx = _tracker.createInstance<AddExpressionContext>(_ctx, getState());
  enterRule(_localctx, 12, ExpressionsParser::RuleAddExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(102);
    mulExpression();
    setState(107);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(103);
        _la = _input->LA(1);
        if (!(_la == ExpressionsParser::T__13

        || _la == ExpressionsParser::T__14)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(104);
        mulExpression(); 
      }
      setState(109);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
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

ExpressionsParser::MulExpressionContext::MulExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ExpressionsParser::UnaryExpressionContext *> ExpressionsParser::MulExpressionContext::unaryExpression() {
  return getRuleContexts<ExpressionsParser::UnaryExpressionContext>();
}

ExpressionsParser::UnaryExpressionContext* ExpressionsParser::MulExpressionContext::unaryExpression(size_t i) {
  return getRuleContext<ExpressionsParser::UnaryExpressionContext>(i);
}


size_t ExpressionsParser::MulExpressionContext::getRuleIndex() const {
  return ExpressionsParser::RuleMulExpression;
}

antlrcpp::Any ExpressionsParser::MulExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExpressionsVisitor*>(visitor))
    return parserVisitor->visitMulExpression(this);
  else
    return visitor->visitChildren(this);
}

ExpressionsParser::MulExpressionContext* ExpressionsParser::mulExpression() {
  MulExpressionContext *_localctx = _tracker.createInstance<MulExpressionContext>(_ctx, getState());
  enterRule(_localctx, 14, ExpressionsParser::RuleMulExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(110);
    unaryExpression();
    setState(115);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << ExpressionsParser::T__15)
      | (1ULL << ExpressionsParser::T__16)
      | (1ULL << ExpressionsParser::T__17)
      | (1ULL << ExpressionsParser::T__18))) != 0)) {
      setState(111);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << ExpressionsParser::T__15)
        | (1ULL << ExpressionsParser::T__16)
        | (1ULL << ExpressionsParser::T__17)
        | (1ULL << ExpressionsParser::T__18))) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(112);
      unaryExpression();
      setState(117);
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

ExpressionsParser::UnaryExpressionContext::UnaryExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ExpressionsParser::FuncExpressionContext* ExpressionsParser::UnaryExpressionContext::funcExpression() {
  return getRuleContext<ExpressionsParser::FuncExpressionContext>(0);
}

ExpressionsParser::UnaryExpressionContext* ExpressionsParser::UnaryExpressionContext::unaryExpression() {
  return getRuleContext<ExpressionsParser::UnaryExpressionContext>(0);
}


size_t ExpressionsParser::UnaryExpressionContext::getRuleIndex() const {
  return ExpressionsParser::RuleUnaryExpression;
}

antlrcpp::Any ExpressionsParser::UnaryExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExpressionsVisitor*>(visitor))
    return parserVisitor->visitUnaryExpression(this);
  else
    return visitor->visitChildren(this);
}

ExpressionsParser::UnaryExpressionContext* ExpressionsParser::unaryExpression() {
  UnaryExpressionContext *_localctx = _tracker.createInstance<UnaryExpressionContext>(_ctx, getState());
  enterRule(_localctx, 16, ExpressionsParser::RuleUnaryExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(127);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ExpressionsParser::T__5:
      case ExpressionsParser::T__21:
      case ExpressionsParser::T__23:
      case ExpressionsParser::T__26:
      case ExpressionsParser::T__27:
      case ExpressionsParser::T__28:
      case ExpressionsParser::T__29:
      case ExpressionsParser::T__31:
      case ExpressionsParser::T__34:
      case ExpressionsParser::T__36:
      case ExpressionsParser::T__37:
      case ExpressionsParser::T__54:
      case ExpressionsParser::T__55:
      case ExpressionsParser::T__56:
      case ExpressionsParser::T__57:
      case ExpressionsParser::T__58:
      case ExpressionsParser::T__59:
      case ExpressionsParser::T__60:
      case ExpressionsParser::T__61:
      case ExpressionsParser::T__62:
      case ExpressionsParser::T__63:
      case ExpressionsParser::T__64:
      case ExpressionsParser::T__65:
      case ExpressionsParser::T__66:
      case ExpressionsParser::T__67:
      case ExpressionsParser::T__68:
      case ExpressionsParser::T__69:
      case ExpressionsParser::T__70:
      case ExpressionsParser::T__71:
      case ExpressionsParser::T__72:
      case ExpressionsParser::T__73:
      case ExpressionsParser::T__74:
      case ExpressionsParser::T__75:
      case ExpressionsParser::T__76:
      case ExpressionsParser::T__77:
      case ExpressionsParser::T__78:
      case ExpressionsParser::T__79:
      case ExpressionsParser::T__80:
      case ExpressionsParser::T__81:
      case ExpressionsParser::T__82:
      case ExpressionsParser::T__83:
      case ExpressionsParser::T__84:
      case ExpressionsParser::T__85:
      case ExpressionsParser::NUMBER:
      case ExpressionsParser::REALNUBER:
      case ExpressionsParser::STRING:
      case ExpressionsParser::IDENTIFIER:
      case ExpressionsParser::RELATIVENAME:
      case ExpressionsParser::ABSOLUTENAME:
      case ExpressionsParser::ROOTNAME: {
        enterOuterAlt(_localctx, 1);
        setState(118);
        funcExpression();
        break;
      }

      case ExpressionsParser::T__14: {
        enterOuterAlt(_localctx, 2);
        setState(119);
        match(ExpressionsParser::T__14);
        setState(120);
        unaryExpression();
        break;
      }

      case ExpressionsParser::T__13: {
        enterOuterAlt(_localctx, 3);
        setState(121);
        match(ExpressionsParser::T__13);
        setState(122);
        unaryExpression();
        break;
      }

      case ExpressionsParser::T__19: {
        enterOuterAlt(_localctx, 4);
        setState(123);
        match(ExpressionsParser::T__19);
        setState(124);
        unaryExpression();
        break;
      }

      case ExpressionsParser::T__20: {
        enterOuterAlt(_localctx, 5);
        setState(125);
        match(ExpressionsParser::T__20);
        setState(126);
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

ExpressionsParser::FuncExpressionContext::FuncExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ExpressionsParser::ExpressionFactorContext* ExpressionsParser::FuncExpressionContext::expressionFactor() {
  return getRuleContext<ExpressionsParser::ExpressionFactorContext>(0);
}

ExpressionsParser::StdLibFunctionContext* ExpressionsParser::FuncExpressionContext::stdLibFunction() {
  return getRuleContext<ExpressionsParser::StdLibFunctionContext>(0);
}

std::vector<ExpressionsParser::ExpressionsContext *> ExpressionsParser::FuncExpressionContext::expressions() {
  return getRuleContexts<ExpressionsParser::ExpressionsContext>();
}

ExpressionsParser::ExpressionsContext* ExpressionsParser::FuncExpressionContext::expressions(size_t i) {
  return getRuleContext<ExpressionsParser::ExpressionsContext>(i);
}

std::vector<ExpressionsParser::OptExpressionContext *> ExpressionsParser::FuncExpressionContext::optExpression() {
  return getRuleContexts<ExpressionsParser::OptExpressionContext>();
}

ExpressionsParser::OptExpressionContext* ExpressionsParser::FuncExpressionContext::optExpression(size_t i) {
  return getRuleContext<ExpressionsParser::OptExpressionContext>(i);
}


size_t ExpressionsParser::FuncExpressionContext::getRuleIndex() const {
  return ExpressionsParser::RuleFuncExpression;
}

antlrcpp::Any ExpressionsParser::FuncExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExpressionsVisitor*>(visitor))
    return parserVisitor->visitFuncExpression(this);
  else
    return visitor->visitChildren(this);
}

ExpressionsParser::FuncExpressionContext* ExpressionsParser::funcExpression() {
  FuncExpressionContext *_localctx = _tracker.createInstance<FuncExpressionContext>(_ctx, getState());
  enterRule(_localctx, 18, ExpressionsParser::RuleFuncExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(139);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      setState(129);
      expressionFactor();
      break;
    }

    case 2: {
      setState(130);
      stdLibFunction();
      setState(131);
      match(ExpressionsParser::T__21);
      setState(132);
      match(ExpressionsParser::T__22);
      break;
    }

    case 3: {
      setState(134);
      stdLibFunction();
      setState(135);
      match(ExpressionsParser::T__21);
      setState(136);
      expressions();
      setState(137);
      match(ExpressionsParser::T__22);
      break;
    }

    }
    setState(159);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(157);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
        case 1: {
          setState(141);
          match(ExpressionsParser::T__23);
          setState(142);
          expressions();
          setState(143);
          match(ExpressionsParser::T__24);
          break;
        }

        case 2: {
          setState(145);
          match(ExpressionsParser::T__23);
          setState(146);
          optExpression();
          setState(147);
          match(ExpressionsParser::T__25);
          setState(148);
          optExpression();
          setState(149);
          match(ExpressionsParser::T__24);
          break;
        }

        case 3: {
          setState(151);
          match(ExpressionsParser::T__21);
          setState(152);
          match(ExpressionsParser::T__22);
          break;
        }

        case 4: {
          setState(153);
          match(ExpressionsParser::T__21);
          setState(154);
          expressions();
          setState(155);
          match(ExpressionsParser::T__22);
          break;
        }

        } 
      }
      setState(161);
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

//----------------- ExpressionFactorContext ------------------------------------------------------------------

ExpressionsParser::ExpressionFactorContext::ExpressionFactorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ExpressionsParser::ExpressionFactorContext::NUMBER() {
  return getToken(ExpressionsParser::NUMBER, 0);
}

tree::TerminalNode* ExpressionsParser::ExpressionFactorContext::REALNUBER() {
  return getToken(ExpressionsParser::REALNUBER, 0);
}

ExpressionsParser::StringTokenContext* ExpressionsParser::ExpressionFactorContext::stringToken() {
  return getRuleContext<ExpressionsParser::StringTokenContext>(0);
}

ExpressionsParser::ExpressionsContext* ExpressionsParser::ExpressionFactorContext::expressions() {
  return getRuleContext<ExpressionsParser::ExpressionsContext>(0);
}

ExpressionsParser::NonEmptySetExpressionContext* ExpressionsParser::ExpressionFactorContext::nonEmptySetExpression() {
  return getRuleContext<ExpressionsParser::NonEmptySetExpressionContext>(0);
}

ExpressionsParser::DictPairsContext* ExpressionsParser::ExpressionFactorContext::dictPairs() {
  return getRuleContext<ExpressionsParser::DictPairsContext>(0);
}

std::vector<ExpressionsParser::ExpressionContext *> ExpressionsParser::ExpressionFactorContext::expression() {
  return getRuleContexts<ExpressionsParser::ExpressionContext>();
}

ExpressionsParser::ExpressionContext* ExpressionsParser::ExpressionFactorContext::expression(size_t i) {
  return getRuleContext<ExpressionsParser::ExpressionContext>(i);
}

ExpressionsParser::TypeContext* ExpressionsParser::ExpressionFactorContext::type() {
  return getRuleContext<ExpressionsParser::TypeContext>(0);
}

ExpressionsParser::ExpressionFactorContext* ExpressionsParser::ExpressionFactorContext::expressionFactor() {
  return getRuleContext<ExpressionsParser::ExpressionFactorContext>(0);
}

ExpressionsParser::OptElifExprsContext* ExpressionsParser::ExpressionFactorContext::optElifExprs() {
  return getRuleContext<ExpressionsParser::OptElifExprsContext>(0);
}

ExpressionsParser::SwitchBodyContext* ExpressionsParser::ExpressionFactorContext::switchBody() {
  return getRuleContext<ExpressionsParser::SwitchBodyContext>(0);
}

ExpressionsParser::NameContext* ExpressionsParser::ExpressionFactorContext::name() {
  return getRuleContext<ExpressionsParser::NameContext>(0);
}


size_t ExpressionsParser::ExpressionFactorContext::getRuleIndex() const {
  return ExpressionsParser::RuleExpressionFactor;
}

antlrcpp::Any ExpressionsParser::ExpressionFactorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExpressionsVisitor*>(visitor))
    return parserVisitor->visitExpressionFactor(this);
  else
    return visitor->visitChildren(this);
}

ExpressionsParser::ExpressionFactorContext* ExpressionsParser::expressionFactor() {
  ExpressionFactorContext *_localctx = _tracker.createInstance<ExpressionFactorContext>(_ctx, getState());
  enterRule(_localctx, 20, ExpressionsParser::RuleExpressionFactor);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(217);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(162);
      match(ExpressionsParser::T__26);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(163);
      match(ExpressionsParser::T__27);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(164);
      match(ExpressionsParser::NUMBER);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(165);
      match(ExpressionsParser::REALNUBER);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(166);
      stringToken();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(167);
      match(ExpressionsParser::T__28);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(168);
      match(ExpressionsParser::T__23);
      setState(169);
      match(ExpressionsParser::T__24);
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(170);
      match(ExpressionsParser::T__23);
      setState(171);
      expressions();
      setState(172);
      match(ExpressionsParser::T__24);
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(174);
      match(ExpressionsParser::T__29);
      setState(175);
      match(ExpressionsParser::T__30);
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(176);
      nonEmptySetExpression();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(177);
      match(ExpressionsParser::T__29);
      setState(178);
      dictPairs();
      setState(179);
      match(ExpressionsParser::T__30);
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(181);
      match(ExpressionsParser::T__21);
      setState(182);
      expression();
      setState(183);
      match(ExpressionsParser::T__0);
      setState(184);
      expression();
      setState(185);
      match(ExpressionsParser::T__22);
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(187);
      match(ExpressionsParser::T__5);
      setState(188);
      type();
      setState(189);
      match(ExpressionsParser::T__10);
      setState(190);
      expressionFactor();
      break;
    }

    case 14: {
      enterOuterAlt(_localctx, 14);
      setState(192);
      match(ExpressionsParser::T__31);
      setState(193);
      expressions();
      setState(194);
      match(ExpressionsParser::T__25);
      setState(195);
      expression();
      setState(196);
      optElifExprs();
      setState(197);
      match(ExpressionsParser::T__32);
      setState(198);
      expression();
      setState(199);
      match(ExpressionsParser::T__33);
      break;
    }

    case 15: {
      enterOuterAlt(_localctx, 15);
      setState(201);
      match(ExpressionsParser::T__34);
      setState(202);
      expression();
      setState(203);
      match(ExpressionsParser::T__25);
      setState(204);
      switchBody();
      setState(205);
      match(ExpressionsParser::T__33);
      break;
    }

    case 16: {
      enterOuterAlt(_localctx, 16);
      setState(207);
      match(ExpressionsParser::T__21);
      setState(208);
      expression();
      setState(209);
      match(ExpressionsParser::T__22);
      break;
    }

    case 17: {
      enterOuterAlt(_localctx, 17);
      setState(211);
      name();
      break;
    }

    case 18: {
      enterOuterAlt(_localctx, 18);
      setState(212);
      name();
      setState(213);
      match(ExpressionsParser::T__35);
      break;
    }

    case 19: {
      enterOuterAlt(_localctx, 19);
      setState(215);
      match(ExpressionsParser::T__36);
      break;
    }

    case 20: {
      enterOuterAlt(_localctx, 20);
      setState(216);
      match(ExpressionsParser::T__37);
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

ExpressionsParser::NonEmptySetExpressionContext::NonEmptySetExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ExpressionsParser::ExpressionsContext* ExpressionsParser::NonEmptySetExpressionContext::expressions() {
  return getRuleContext<ExpressionsParser::ExpressionsContext>(0);
}


size_t ExpressionsParser::NonEmptySetExpressionContext::getRuleIndex() const {
  return ExpressionsParser::RuleNonEmptySetExpression;
}

antlrcpp::Any ExpressionsParser::NonEmptySetExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExpressionsVisitor*>(visitor))
    return parserVisitor->visitNonEmptySetExpression(this);
  else
    return visitor->visitChildren(this);
}

ExpressionsParser::NonEmptySetExpressionContext* ExpressionsParser::nonEmptySetExpression() {
  NonEmptySetExpressionContext *_localctx = _tracker.createInstance<NonEmptySetExpressionContext>(_ctx, getState());
  enterRule(_localctx, 22, ExpressionsParser::RuleNonEmptySetExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(219);
    match(ExpressionsParser::T__29);
    setState(220);
    expressions();
    setState(221);
    match(ExpressionsParser::T__30);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DictPairsContext ------------------------------------------------------------------

ExpressionsParser::DictPairsContext::DictPairsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ExpressionsParser::ExpressionContext *> ExpressionsParser::DictPairsContext::expression() {
  return getRuleContexts<ExpressionsParser::ExpressionContext>();
}

ExpressionsParser::ExpressionContext* ExpressionsParser::DictPairsContext::expression(size_t i) {
  return getRuleContext<ExpressionsParser::ExpressionContext>(i);
}


size_t ExpressionsParser::DictPairsContext::getRuleIndex() const {
  return ExpressionsParser::RuleDictPairs;
}

antlrcpp::Any ExpressionsParser::DictPairsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExpressionsVisitor*>(visitor))
    return parserVisitor->visitDictPairs(this);
  else
    return visitor->visitChildren(this);
}

ExpressionsParser::DictPairsContext* ExpressionsParser::dictPairs() {
  DictPairsContext *_localctx = _tracker.createInstance<DictPairsContext>(_ctx, getState());
  enterRule(_localctx, 24, ExpressionsParser::RuleDictPairs);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(223);
    expression();
    setState(224);
    match(ExpressionsParser::T__25);
    setState(225);
    expression();

    setState(226);
    match(ExpressionsParser::T__0);
    setState(227);
    expression();
    setState(228);
    match(ExpressionsParser::T__25);
    setState(229);
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

ExpressionsParser::OptElifExprsContext::OptElifExprsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ExpressionsParser::ExpressionContext *> ExpressionsParser::OptElifExprsContext::expression() {
  return getRuleContexts<ExpressionsParser::ExpressionContext>();
}

ExpressionsParser::ExpressionContext* ExpressionsParser::OptElifExprsContext::expression(size_t i) {
  return getRuleContext<ExpressionsParser::ExpressionContext>(i);
}


size_t ExpressionsParser::OptElifExprsContext::getRuleIndex() const {
  return ExpressionsParser::RuleOptElifExprs;
}

antlrcpp::Any ExpressionsParser::OptElifExprsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExpressionsVisitor*>(visitor))
    return parserVisitor->visitOptElifExprs(this);
  else
    return visitor->visitChildren(this);
}

ExpressionsParser::OptElifExprsContext* ExpressionsParser::optElifExprs() {
  OptElifExprsContext *_localctx = _tracker.createInstance<OptElifExprsContext>(_ctx, getState());
  enterRule(_localctx, 26, ExpressionsParser::RuleOptElifExprs);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(238);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << ExpressionsParser::T__5)
      | (1ULL << ExpressionsParser::T__13)
      | (1ULL << ExpressionsParser::T__14)
      | (1ULL << ExpressionsParser::T__19)
      | (1ULL << ExpressionsParser::T__20)
      | (1ULL << ExpressionsParser::T__21)
      | (1ULL << ExpressionsParser::T__23)
      | (1ULL << ExpressionsParser::T__26)
      | (1ULL << ExpressionsParser::T__27)
      | (1ULL << ExpressionsParser::T__28)
      | (1ULL << ExpressionsParser::T__29)
      | (1ULL << ExpressionsParser::T__31)
      | (1ULL << ExpressionsParser::T__34)
      | (1ULL << ExpressionsParser::T__36)
      | (1ULL << ExpressionsParser::T__37)
      | (1ULL << ExpressionsParser::T__54)
      | (1ULL << ExpressionsParser::T__55)
      | (1ULL << ExpressionsParser::T__56)
      | (1ULL << ExpressionsParser::T__57)
      | (1ULL << ExpressionsParser::T__58)
      | (1ULL << ExpressionsParser::T__59)
      | (1ULL << ExpressionsParser::T__60)
      | (1ULL << ExpressionsParser::T__61)
      | (1ULL << ExpressionsParser::T__62))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (ExpressionsParser::T__63 - 64))
      | (1ULL << (ExpressionsParser::T__64 - 64))
      | (1ULL << (ExpressionsParser::T__65 - 64))
      | (1ULL << (ExpressionsParser::T__66 - 64))
      | (1ULL << (ExpressionsParser::T__67 - 64))
      | (1ULL << (ExpressionsParser::T__68 - 64))
      | (1ULL << (ExpressionsParser::T__69 - 64))
      | (1ULL << (ExpressionsParser::T__70 - 64))
      | (1ULL << (ExpressionsParser::T__71 - 64))
      | (1ULL << (ExpressionsParser::T__72 - 64))
      | (1ULL << (ExpressionsParser::T__73 - 64))
      | (1ULL << (ExpressionsParser::T__74 - 64))
      | (1ULL << (ExpressionsParser::T__75 - 64))
      | (1ULL << (ExpressionsParser::T__76 - 64))
      | (1ULL << (ExpressionsParser::T__77 - 64))
      | (1ULL << (ExpressionsParser::T__78 - 64))
      | (1ULL << (ExpressionsParser::T__79 - 64))
      | (1ULL << (ExpressionsParser::T__80 - 64))
      | (1ULL << (ExpressionsParser::T__81 - 64))
      | (1ULL << (ExpressionsParser::T__82 - 64))
      | (1ULL << (ExpressionsParser::T__83 - 64))
      | (1ULL << (ExpressionsParser::T__84 - 64))
      | (1ULL << (ExpressionsParser::T__85 - 64))
      | (1ULL << (ExpressionsParser::NUMBER - 64))
      | (1ULL << (ExpressionsParser::REALNUBER - 64))
      | (1ULL << (ExpressionsParser::STRING - 64))
      | (1ULL << (ExpressionsParser::IDENTIFIER - 64))
      | (1ULL << (ExpressionsParser::RELATIVENAME - 64))
      | (1ULL << (ExpressionsParser::ABSOLUTENAME - 64))
      | (1ULL << (ExpressionsParser::ROOTNAME - 64)))) != 0)) {
      setState(231);
      expression();
      setState(232);
      match(ExpressionsParser::T__25);
      setState(233);
      expression();
      setState(234);
      match(ExpressionsParser::T__38);
      setState(240);
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

ExpressionsParser::SwitchBodyContext::SwitchBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ExpressionsParser::SwitchCasesContext* ExpressionsParser::SwitchBodyContext::switchCases() {
  return getRuleContext<ExpressionsParser::SwitchCasesContext>(0);
}

ExpressionsParser::ExpressionContext* ExpressionsParser::SwitchBodyContext::expression() {
  return getRuleContext<ExpressionsParser::ExpressionContext>(0);
}


size_t ExpressionsParser::SwitchBodyContext::getRuleIndex() const {
  return ExpressionsParser::RuleSwitchBody;
}

antlrcpp::Any ExpressionsParser::SwitchBodyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExpressionsVisitor*>(visitor))
    return parserVisitor->visitSwitchBody(this);
  else
    return visitor->visitChildren(this);
}

ExpressionsParser::SwitchBodyContext* ExpressionsParser::switchBody() {
  SwitchBodyContext *_localctx = _tracker.createInstance<SwitchBodyContext>(_ctx, getState());
  enterRule(_localctx, 28, ExpressionsParser::RuleSwitchBody);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(248);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(241);
      switchCases();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(242);
      switchCases();
      setState(243);
      match(ExpressionsParser::T__32);
      setState(244);
      expression();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(246);
      match(ExpressionsParser::T__32);
      setState(247);
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

ExpressionsParser::SwitchCasesContext::SwitchCasesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ExpressionsParser::ExpressionContext *> ExpressionsParser::SwitchCasesContext::expression() {
  return getRuleContexts<ExpressionsParser::ExpressionContext>();
}

ExpressionsParser::ExpressionContext* ExpressionsParser::SwitchCasesContext::expression(size_t i) {
  return getRuleContext<ExpressionsParser::ExpressionContext>(i);
}


size_t ExpressionsParser::SwitchCasesContext::getRuleIndex() const {
  return ExpressionsParser::RuleSwitchCases;
}

antlrcpp::Any ExpressionsParser::SwitchCasesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExpressionsVisitor*>(visitor))
    return parserVisitor->visitSwitchCases(this);
  else
    return visitor->visitChildren(this);
}

ExpressionsParser::SwitchCasesContext* ExpressionsParser::switchCases() {
  SwitchCasesContext *_localctx = _tracker.createInstance<SwitchCasesContext>(_ctx, getState());
  enterRule(_localctx, 30, ExpressionsParser::RuleSwitchCases);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(255); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(250);
      match(ExpressionsParser::T__39);
      setState(251);
      expression();
      setState(252);
      match(ExpressionsParser::T__25);
      setState(253);
      expression();
      setState(257); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == ExpressionsParser::T__39);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypesContext ------------------------------------------------------------------

ExpressionsParser::TypesContext::TypesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ExpressionsParser::TypeContext *> ExpressionsParser::TypesContext::type() {
  return getRuleContexts<ExpressionsParser::TypeContext>();
}

ExpressionsParser::TypeContext* ExpressionsParser::TypesContext::type(size_t i) {
  return getRuleContext<ExpressionsParser::TypeContext>(i);
}


size_t ExpressionsParser::TypesContext::getRuleIndex() const {
  return ExpressionsParser::RuleTypes;
}

antlrcpp::Any ExpressionsParser::TypesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExpressionsVisitor*>(visitor))
    return parserVisitor->visitTypes(this);
  else
    return visitor->visitChildren(this);
}

ExpressionsParser::TypesContext* ExpressionsParser::types() {
  TypesContext *_localctx = _tracker.createInstance<TypesContext>(_ctx, getState());
  enterRule(_localctx, 32, ExpressionsParser::RuleTypes);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(259);
    type();
    setState(264);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ExpressionsParser::T__0) {
      setState(260);
      match(ExpressionsParser::T__0);
      setState(261);
      type();
      setState(266);
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

ExpressionsParser::TypeContext::TypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ExpressionsParser::ExpressionContext *> ExpressionsParser::TypeContext::expression() {
  return getRuleContexts<ExpressionsParser::ExpressionContext>();
}

ExpressionsParser::ExpressionContext* ExpressionsParser::TypeContext::expression(size_t i) {
  return getRuleContext<ExpressionsParser::ExpressionContext>(i);
}

std::vector<ExpressionsParser::TypeContext *> ExpressionsParser::TypeContext::type() {
  return getRuleContexts<ExpressionsParser::TypeContext>();
}

ExpressionsParser::TypeContext* ExpressionsParser::TypeContext::type(size_t i) {
  return getRuleContext<ExpressionsParser::TypeContext>(i);
}

ExpressionsParser::FieldsContext* ExpressionsParser::TypeContext::fields() {
  return getRuleContext<ExpressionsParser::FieldsContext>(0);
}

ExpressionsParser::TypesContext* ExpressionsParser::TypeContext::types() {
  return getRuleContext<ExpressionsParser::TypesContext>(0);
}

ExpressionsParser::NameContext* ExpressionsParser::TypeContext::name() {
  return getRuleContext<ExpressionsParser::NameContext>(0);
}


size_t ExpressionsParser::TypeContext::getRuleIndex() const {
  return ExpressionsParser::RuleType;
}

antlrcpp::Any ExpressionsParser::TypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExpressionsVisitor*>(visitor))
    return parserVisitor->visitType(this);
  else
    return visitor->visitChildren(this);
}

ExpressionsParser::TypeContext* ExpressionsParser::type() {
  TypeContext *_localctx = _tracker.createInstance<TypeContext>(_ctx, getState());
  enterRule(_localctx, 34, ExpressionsParser::RuleType);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(322);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(267);
      match(ExpressionsParser::T__40);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(268);
      match(ExpressionsParser::T__41);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(269);
      match(ExpressionsParser::T__41);
      setState(270);
      match(ExpressionsParser::T__23);
      setState(271);
      expression();
      setState(272);
      match(ExpressionsParser::T__42);
      setState(273);
      expression();
      setState(274);
      match(ExpressionsParser::T__24);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(276);
      match(ExpressionsParser::T__43);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(277);
      match(ExpressionsParser::T__44);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(278);
      match(ExpressionsParser::T__45);
      setState(279);
      type();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(280);
      match(ExpressionsParser::T__45);
      setState(281);
      match(ExpressionsParser::T__23);
      setState(282);
      expression();
      setState(283);
      match(ExpressionsParser::T__24);
      setState(284);
      type();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(286);
      match(ExpressionsParser::T__45);
      setState(287);
      match(ExpressionsParser::T__23);
      setState(288);
      expression();
      setState(289);
      match(ExpressionsParser::T__42);
      setState(290);
      expression();
      setState(291);
      match(ExpressionsParser::T__24);
      setState(292);
      type();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(294);
      match(ExpressionsParser::T__46);
      setState(295);
      type();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(296);
      match(ExpressionsParser::T__47);
      setState(297);
      match(ExpressionsParser::T__21);
      setState(298);
      type();
      setState(299);
      match(ExpressionsParser::T__25);
      setState(300);
      type();
      setState(301);
      match(ExpressionsParser::T__22);
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(303);
      match(ExpressionsParser::T__48);
      setState(304);
      match(ExpressionsParser::T__21);
      setState(305);
      fields();
      setState(306);
      match(ExpressionsParser::T__22);
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(308);
      match(ExpressionsParser::T__49);
      setState(309);
      type();
      setState(310);
      match(ExpressionsParser::T__21);
      setState(311);
      match(ExpressionsParser::T__22);
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(313);
      match(ExpressionsParser::T__49);
      setState(314);
      type();
      setState(315);
      match(ExpressionsParser::T__21);
      setState(316);
      types();
      setState(317);
      match(ExpressionsParser::T__22);
      break;
    }

    case 14: {
      enterOuterAlt(_localctx, 14);
      setState(319);
      match(ExpressionsParser::T__50);
      setState(320);
      type();
      break;
    }

    case 15: {
      enterOuterAlt(_localctx, 15);
      setState(321);
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

ExpressionsParser::FieldsContext::FieldsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ExpressionsParser::FieldContext *> ExpressionsParser::FieldsContext::field() {
  return getRuleContexts<ExpressionsParser::FieldContext>();
}

ExpressionsParser::FieldContext* ExpressionsParser::FieldsContext::field(size_t i) {
  return getRuleContext<ExpressionsParser::FieldContext>(i);
}


size_t ExpressionsParser::FieldsContext::getRuleIndex() const {
  return ExpressionsParser::RuleFields;
}

antlrcpp::Any ExpressionsParser::FieldsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExpressionsVisitor*>(visitor))
    return parserVisitor->visitFields(this);
  else
    return visitor->visitChildren(this);
}

ExpressionsParser::FieldsContext* ExpressionsParser::fields() {
  FieldsContext *_localctx = _tracker.createInstance<FieldsContext>(_ctx, getState());
  enterRule(_localctx, 36, ExpressionsParser::RuleFields);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(324);
    field();
    setState(329);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ExpressionsParser::T__0) {
      setState(325);
      match(ExpressionsParser::T__0);
      setState(326);
      field();
      setState(331);
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

ExpressionsParser::FieldContext::FieldContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ExpressionsParser::TypeContext* ExpressionsParser::FieldContext::type() {
  return getRuleContext<ExpressionsParser::TypeContext>(0);
}

ExpressionsParser::IdentifierContext* ExpressionsParser::FieldContext::identifier() {
  return getRuleContext<ExpressionsParser::IdentifierContext>(0);
}


size_t ExpressionsParser::FieldContext::getRuleIndex() const {
  return ExpressionsParser::RuleField;
}

antlrcpp::Any ExpressionsParser::FieldContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExpressionsVisitor*>(visitor))
    return parserVisitor->visitField(this);
  else
    return visitor->visitChildren(this);
}

ExpressionsParser::FieldContext* ExpressionsParser::field() {
  FieldContext *_localctx = _tracker.createInstance<FieldContext>(_ctx, getState());
  enterRule(_localctx, 38, ExpressionsParser::RuleField);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(332);
    type();
    setState(333);
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

ExpressionsParser::NameSetContext::NameSetContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ExpressionsParser::NamesContext* ExpressionsParser::NameSetContext::names() {
  return getRuleContext<ExpressionsParser::NamesContext>(0);
}


size_t ExpressionsParser::NameSetContext::getRuleIndex() const {
  return ExpressionsParser::RuleNameSet;
}

antlrcpp::Any ExpressionsParser::NameSetContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExpressionsVisitor*>(visitor))
    return parserVisitor->visitNameSet(this);
  else
    return visitor->visitChildren(this);
}

ExpressionsParser::NameSetContext* ExpressionsParser::nameSet() {
  NameSetContext *_localctx = _tracker.createInstance<NameSetContext>(_ctx, getState());
  enterRule(_localctx, 40, ExpressionsParser::RuleNameSet);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(335);
    match(ExpressionsParser::T__29);
    setState(336);
    names();
    setState(337);
    match(ExpressionsParser::T__30);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NamesContext ------------------------------------------------------------------

ExpressionsParser::NamesContext::NamesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ExpressionsParser::NameContext *> ExpressionsParser::NamesContext::name() {
  return getRuleContexts<ExpressionsParser::NameContext>();
}

ExpressionsParser::NameContext* ExpressionsParser::NamesContext::name(size_t i) {
  return getRuleContext<ExpressionsParser::NameContext>(i);
}


size_t ExpressionsParser::NamesContext::getRuleIndex() const {
  return ExpressionsParser::RuleNames;
}

antlrcpp::Any ExpressionsParser::NamesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExpressionsVisitor*>(visitor))
    return parserVisitor->visitNames(this);
  else
    return visitor->visitChildren(this);
}

ExpressionsParser::NamesContext* ExpressionsParser::names() {
  NamesContext *_localctx = _tracker.createInstance<NamesContext>(_ctx, getState());
  enterRule(_localctx, 42, ExpressionsParser::RuleNames);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(339);
    name();
    setState(344);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ExpressionsParser::T__0) {
      setState(340);
      match(ExpressionsParser::T__0);
      setState(341);
      name();
      setState(346);
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

ExpressionsParser::NameContext::NameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ExpressionsParser::IdentifierContext* ExpressionsParser::NameContext::identifier() {
  return getRuleContext<ExpressionsParser::IdentifierContext>(0);
}

tree::TerminalNode* ExpressionsParser::NameContext::RELATIVENAME() {
  return getToken(ExpressionsParser::RELATIVENAME, 0);
}

tree::TerminalNode* ExpressionsParser::NameContext::ABSOLUTENAME() {
  return getToken(ExpressionsParser::ABSOLUTENAME, 0);
}

tree::TerminalNode* ExpressionsParser::NameContext::ROOTNAME() {
  return getToken(ExpressionsParser::ROOTNAME, 0);
}


size_t ExpressionsParser::NameContext::getRuleIndex() const {
  return ExpressionsParser::RuleName;
}

antlrcpp::Any ExpressionsParser::NameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExpressionsVisitor*>(visitor))
    return parserVisitor->visitName(this);
  else
    return visitor->visitChildren(this);
}

ExpressionsParser::NameContext* ExpressionsParser::name() {
  NameContext *_localctx = _tracker.createInstance<NameContext>(_ctx, getState());
  enterRule(_localctx, 44, ExpressionsParser::RuleName);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(351);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ExpressionsParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(347);
        identifier();
        break;
      }

      case ExpressionsParser::RELATIVENAME: {
        enterOuterAlt(_localctx, 2);
        setState(348);
        match(ExpressionsParser::RELATIVENAME);
        break;
      }

      case ExpressionsParser::ABSOLUTENAME: {
        enterOuterAlt(_localctx, 3);
        setState(349);
        match(ExpressionsParser::ABSOLUTENAME);
        break;
      }

      case ExpressionsParser::ROOTNAME: {
        enterOuterAlt(_localctx, 4);
        setState(350);
        match(ExpressionsParser::ROOTNAME);
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

ExpressionsParser::OptSupKindContext::OptSupKindContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ExpressionsParser::SupKindContext* ExpressionsParser::OptSupKindContext::supKind() {
  return getRuleContext<ExpressionsParser::SupKindContext>(0);
}


size_t ExpressionsParser::OptSupKindContext::getRuleIndex() const {
  return ExpressionsParser::RuleOptSupKind;
}

antlrcpp::Any ExpressionsParser::OptSupKindContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExpressionsVisitor*>(visitor))
    return parserVisitor->visitOptSupKind(this);
  else
    return visitor->visitChildren(this);
}

ExpressionsParser::OptSupKindContext* ExpressionsParser::optSupKind() {
  OptSupKindContext *_localctx = _tracker.createInstance<OptSupKindContext>(_ctx, getState());
  enterRule(_localctx, 46, ExpressionsParser::RuleOptSupKind);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(354);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << ExpressionsParser::T__51)
      | (1ULL << ExpressionsParser::T__52)
      | (1ULL << ExpressionsParser::T__53))) != 0)) {
      setState(353);
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

ExpressionsParser::SupKindContext::SupKindContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ExpressionsParser::SupKindContext::getRuleIndex() const {
  return ExpressionsParser::RuleSupKind;
}

antlrcpp::Any ExpressionsParser::SupKindContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExpressionsVisitor*>(visitor))
    return parserVisitor->visitSupKind(this);
  else
    return visitor->visitChildren(this);
}

ExpressionsParser::SupKindContext* ExpressionsParser::supKind() {
  SupKindContext *_localctx = _tracker.createInstance<SupKindContext>(_ctx, getState());
  enterRule(_localctx, 48, ExpressionsParser::RuleSupKind);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(356);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << ExpressionsParser::T__51)
      | (1ULL << ExpressionsParser::T__52)
      | (1ULL << ExpressionsParser::T__53))) != 0))) {
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

ExpressionsParser::IdentifierContext::IdentifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ExpressionsParser::IdentifierContext::IDENTIFIER() {
  return getToken(ExpressionsParser::IDENTIFIER, 0);
}


size_t ExpressionsParser::IdentifierContext::getRuleIndex() const {
  return ExpressionsParser::RuleIdentifier;
}

antlrcpp::Any ExpressionsParser::IdentifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExpressionsVisitor*>(visitor))
    return parserVisitor->visitIdentifier(this);
  else
    return visitor->visitChildren(this);
}

ExpressionsParser::IdentifierContext* ExpressionsParser::identifier() {
  IdentifierContext *_localctx = _tracker.createInstance<IdentifierContext>(_ctx, getState());
  enterRule(_localctx, 50, ExpressionsParser::RuleIdentifier);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(358);
    match(ExpressionsParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StringTokenContext ------------------------------------------------------------------

ExpressionsParser::StringTokenContext::StringTokenContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ExpressionsParser::StringTokenContext::STRING() {
  return getToken(ExpressionsParser::STRING, 0);
}


size_t ExpressionsParser::StringTokenContext::getRuleIndex() const {
  return ExpressionsParser::RuleStringToken;
}

antlrcpp::Any ExpressionsParser::StringTokenContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExpressionsVisitor*>(visitor))
    return parserVisitor->visitStringToken(this);
  else
    return visitor->visitChildren(this);
}

ExpressionsParser::StringTokenContext* ExpressionsParser::stringToken() {
  StringTokenContext *_localctx = _tracker.createInstance<StringTokenContext>(_ctx, getState());
  enterRule(_localctx, 52, ExpressionsParser::RuleStringToken);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(360);
    match(ExpressionsParser::STRING);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StdLibFunctionContext ------------------------------------------------------------------

ExpressionsParser::StdLibFunctionContext::StdLibFunctionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ExpressionsParser::StdLibFunctionContext::getRuleIndex() const {
  return ExpressionsParser::RuleStdLibFunction;
}

antlrcpp::Any ExpressionsParser::StdLibFunctionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExpressionsVisitor*>(visitor))
    return parserVisitor->visitStdLibFunction(this);
  else
    return visitor->visitChildren(this);
}

ExpressionsParser::StdLibFunctionContext* ExpressionsParser::stdLibFunction() {
  StdLibFunctionContext *_localctx = _tracker.createInstance<StdLibFunctionContext>(_ctx, getState());
  enterRule(_localctx, 54, ExpressionsParser::RuleStdLibFunction);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(362);
    _la = _input->LA(1);
    if (!(((((_la - 55) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 55)) & ((1ULL << (ExpressionsParser::T__54 - 55))
      | (1ULL << (ExpressionsParser::T__55 - 55))
      | (1ULL << (ExpressionsParser::T__56 - 55))
      | (1ULL << (ExpressionsParser::T__57 - 55))
      | (1ULL << (ExpressionsParser::T__58 - 55))
      | (1ULL << (ExpressionsParser::T__59 - 55))
      | (1ULL << (ExpressionsParser::T__60 - 55))
      | (1ULL << (ExpressionsParser::T__61 - 55))
      | (1ULL << (ExpressionsParser::T__62 - 55))
      | (1ULL << (ExpressionsParser::T__63 - 55))
      | (1ULL << (ExpressionsParser::T__64 - 55))
      | (1ULL << (ExpressionsParser::T__65 - 55))
      | (1ULL << (ExpressionsParser::T__66 - 55))
      | (1ULL << (ExpressionsParser::T__67 - 55))
      | (1ULL << (ExpressionsParser::T__68 - 55))
      | (1ULL << (ExpressionsParser::T__69 - 55))
      | (1ULL << (ExpressionsParser::T__70 - 55))
      | (1ULL << (ExpressionsParser::T__71 - 55))
      | (1ULL << (ExpressionsParser::T__72 - 55))
      | (1ULL << (ExpressionsParser::T__73 - 55))
      | (1ULL << (ExpressionsParser::T__74 - 55))
      | (1ULL << (ExpressionsParser::T__75 - 55))
      | (1ULL << (ExpressionsParser::T__76 - 55))
      | (1ULL << (ExpressionsParser::T__77 - 55))
      | (1ULL << (ExpressionsParser::T__78 - 55))
      | (1ULL << (ExpressionsParser::T__79 - 55))
      | (1ULL << (ExpressionsParser::T__80 - 55))
      | (1ULL << (ExpressionsParser::T__81 - 55))
      | (1ULL << (ExpressionsParser::T__82 - 55))
      | (1ULL << (ExpressionsParser::T__83 - 55))
      | (1ULL << (ExpressionsParser::T__84 - 55))
      | (1ULL << (ExpressionsParser::T__85 - 55)))) != 0))) {
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
std::vector<dfa::DFA> ExpressionsParser::_decisionToDFA;
atn::PredictionContextCache ExpressionsParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN ExpressionsParser::_atn;
std::vector<uint16_t> ExpressionsParser::_serializedATN;

std::vector<std::string> ExpressionsParser::_ruleNames = {
  "expressions", "optExpression", "expression", "orExpression", "andExpression", 
  "compareExpression", "addExpression", "mulExpression", "unaryExpression", 
  "funcExpression", "expressionFactor", "nonEmptySetExpression", "dictPairs", 
  "optElifExprs", "switchBody", "switchCases", "types", "type", "fields", 
  "field", "nameSet", "names", "name", "optSupKind", "supKind", "identifier", 
  "stringToken", "stdLibFunction"
};

std::vector<std::string> ExpressionsParser::_literalNames = {
  "", "','", "'=>'", "'<=>'", "'or'", "'and'", "'<'", "'<='", "'='", "'!='", 
  "'>='", "'>'", "'in'", "'sub'", "'+'", "'-'", "'*'", "'/'", "'div'", "'mod'", 
  "'not'", "'sample'", "'('", "')'", "'['", "']'", "':'", "'true'", "'false'", 
  "'time'", "'{'", "'}'", "'if'", "'else'", "'end'", "'switch'", "'''", 
  "'?'", "'self'", "'elif'", "'case'", "'bool'", "'int'", "'..'", "'real'", 
  "'string'", "'list'", "'set'", "'dict'", "'tuple'", "'func'", "'dist'", 
  "'plant'", "'requirement'", "'supervisor'", "'acosh'", "'acos'", "'asinh'", 
  "'asin'", "'atanh'", "'cosh'", "'cos'", "'sinh'", "'sin'", "'tanh'", "'tan'", 
  "'abs'", "'cbrt'", "'ceil'", "'del'", "'empty'", "'exp'", "'floor'", "'fmt'", 
  "'ln'", "'log'", "'max'", "'min'", "'pop'", "'pow'", "'round'", "'scale'", 
  "'sign'", "'size'", "'sqrt'", "'bernoulli'", "'beta'"
};

std::vector<std::string> ExpressionsParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "NUMBER", 
  "REALNUBER", "STRING", "IDENTIFIER", "RELATIVENAME", "ABSOLUTENAME", "ROOTNAME", 
  "WS"
};

dfa::Vocabulary ExpressionsParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> ExpressionsParser::_tokenNames;

ExpressionsParser::Initializer::Initializer() {
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
    0x3, 0x60, 0x16f, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
    0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 
    0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 
    0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 
    0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 
    0x12, 0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x4, 0x15, 
    0x9, 0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 0x9, 0x17, 0x4, 0x18, 0x9, 
    0x18, 0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 0x9, 0x1a, 0x4, 0x1b, 0x9, 0x1b, 
    0x4, 0x1c, 0x9, 0x1c, 0x4, 0x1d, 0x9, 0x1d, 0x3, 0x2, 0x3, 0x2, 0x3, 
    0x2, 0x7, 0x2, 0x3e, 0xa, 0x2, 0xc, 0x2, 0xe, 0x2, 0x41, 0xb, 0x2, 0x3, 
    0x3, 0x5, 0x3, 0x44, 0xa, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 
    0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 0x4f, 0xa, 
    0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x7, 0x5, 0x54, 0xa, 0x5, 0xc, 0x5, 
    0xe, 0x5, 0x57, 0xb, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x7, 0x6, 0x5c, 
    0xa, 0x6, 0xc, 0x6, 0xe, 0x6, 0x5f, 0xb, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 
    0x7, 0x7, 0x7, 0x64, 0xa, 0x7, 0xc, 0x7, 0xe, 0x7, 0x67, 0xb, 0x7, 0x3, 
    0x8, 0x3, 0x8, 0x3, 0x8, 0x7, 0x8, 0x6c, 0xa, 0x8, 0xc, 0x8, 0xe, 0x8, 
    0x6f, 0xb, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x7, 0x9, 0x74, 0xa, 0x9, 
    0xc, 0x9, 0xe, 0x9, 0x77, 0xb, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0x82, 
    0xa, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 
    0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x5, 0xb, 0x8e, 0xa, 0xb, 0x3, 
    0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 
    0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 
    0xb, 0x3, 0xb, 0x7, 0xb, 0xa0, 0xa, 0xb, 0xc, 0xb, 0xe, 0xb, 0xa3, 0xb, 
    0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 
    0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 
    0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 
    0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 
    0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 
    0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 
    0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 
    0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x5, 
    0xc, 0xdc, 0xa, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xe, 
    0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 
    0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x7, 0xf, 0xef, 0xa, 
    0xf, 0xc, 0xf, 0xe, 0xf, 0xf2, 0xb, 0xf, 0x3, 0x10, 0x3, 0x10, 0x3, 
    0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x5, 0x10, 0xfb, 0xa, 
    0x10, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x6, 0x11, 
    0x102, 0xa, 0x11, 0xd, 0x11, 0xe, 0x11, 0x103, 0x3, 0x12, 0x3, 0x12, 
    0x3, 0x12, 0x7, 0x12, 0x109, 0xa, 0x12, 0xc, 0x12, 0xe, 0x12, 0x10c, 
    0xb, 0x12, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 
    0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 
    0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 
    0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 
    0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 
    0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 
    0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 
    0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 
    0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x5, 0x13, 0x145, 0xa, 0x13, 
    0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x7, 0x14, 0x14a, 0xa, 0x14, 0xc, 0x14, 
    0xe, 0x14, 0x14d, 0xb, 0x14, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x16, 
    0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x7, 
    0x17, 0x159, 0xa, 0x17, 0xc, 0x17, 0xe, 0x17, 0x15c, 0xb, 0x17, 0x3, 
    0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x5, 0x18, 0x162, 0xa, 0x18, 
    0x3, 0x19, 0x5, 0x19, 0x165, 0xa, 0x19, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1b, 
    0x3, 0x1b, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x2, 
    0x2, 0x1e, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 
    0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e, 
    0x30, 0x32, 0x34, 0x36, 0x38, 0x2, 0x7, 0x3, 0x2, 0x8, 0xf, 0x3, 0x2, 
    0x10, 0x11, 0x3, 0x2, 0x12, 0x15, 0x3, 0x2, 0x36, 0x38, 0x3, 0x2, 0x39, 
    0x58, 0x2, 0x191, 0x2, 0x3a, 0x3, 0x2, 0x2, 0x2, 0x4, 0x43, 0x3, 0x2, 
    0x2, 0x2, 0x6, 0x4e, 0x3, 0x2, 0x2, 0x2, 0x8, 0x50, 0x3, 0x2, 0x2, 0x2, 
    0xa, 0x58, 0x3, 0x2, 0x2, 0x2, 0xc, 0x60, 0x3, 0x2, 0x2, 0x2, 0xe, 0x68, 
    0x3, 0x2, 0x2, 0x2, 0x10, 0x70, 0x3, 0x2, 0x2, 0x2, 0x12, 0x81, 0x3, 
    0x2, 0x2, 0x2, 0x14, 0x8d, 0x3, 0x2, 0x2, 0x2, 0x16, 0xdb, 0x3, 0x2, 
    0x2, 0x2, 0x18, 0xdd, 0x3, 0x2, 0x2, 0x2, 0x1a, 0xe1, 0x3, 0x2, 0x2, 
    0x2, 0x1c, 0xf0, 0x3, 0x2, 0x2, 0x2, 0x1e, 0xfa, 0x3, 0x2, 0x2, 0x2, 
    0x20, 0x101, 0x3, 0x2, 0x2, 0x2, 0x22, 0x105, 0x3, 0x2, 0x2, 0x2, 0x24, 
    0x144, 0x3, 0x2, 0x2, 0x2, 0x26, 0x146, 0x3, 0x2, 0x2, 0x2, 0x28, 0x14e, 
    0x3, 0x2, 0x2, 0x2, 0x2a, 0x151, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x155, 0x3, 
    0x2, 0x2, 0x2, 0x2e, 0x161, 0x3, 0x2, 0x2, 0x2, 0x30, 0x164, 0x3, 0x2, 
    0x2, 0x2, 0x32, 0x166, 0x3, 0x2, 0x2, 0x2, 0x34, 0x168, 0x3, 0x2, 0x2, 
    0x2, 0x36, 0x16a, 0x3, 0x2, 0x2, 0x2, 0x38, 0x16c, 0x3, 0x2, 0x2, 0x2, 
    0x3a, 0x3f, 0x5, 0x6, 0x4, 0x2, 0x3b, 0x3c, 0x7, 0x3, 0x2, 0x2, 0x3c, 
    0x3e, 0x5, 0x6, 0x4, 0x2, 0x3d, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x41, 
    0x3, 0x2, 0x2, 0x2, 0x3f, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x3f, 0x40, 0x3, 
    0x2, 0x2, 0x2, 0x40, 0x3, 0x3, 0x2, 0x2, 0x2, 0x41, 0x3f, 0x3, 0x2, 
    0x2, 0x2, 0x42, 0x44, 0x5, 0x6, 0x4, 0x2, 0x43, 0x42, 0x3, 0x2, 0x2, 
    0x2, 0x43, 0x44, 0x3, 0x2, 0x2, 0x2, 0x44, 0x5, 0x3, 0x2, 0x2, 0x2, 
    0x45, 0x4f, 0x5, 0x8, 0x5, 0x2, 0x46, 0x47, 0x5, 0x8, 0x5, 0x2, 0x47, 
    0x48, 0x7, 0x4, 0x2, 0x2, 0x48, 0x49, 0x5, 0x8, 0x5, 0x2, 0x49, 0x4f, 
    0x3, 0x2, 0x2, 0x2, 0x4a, 0x4b, 0x5, 0x8, 0x5, 0x2, 0x4b, 0x4c, 0x7, 
    0x5, 0x2, 0x2, 0x4c, 0x4d, 0x5, 0x8, 0x5, 0x2, 0x4d, 0x4f, 0x3, 0x2, 
    0x2, 0x2, 0x4e, 0x45, 0x3, 0x2, 0x2, 0x2, 0x4e, 0x46, 0x3, 0x2, 0x2, 
    0x2, 0x4e, 0x4a, 0x3, 0x2, 0x2, 0x2, 0x4f, 0x7, 0x3, 0x2, 0x2, 0x2, 
    0x50, 0x55, 0x5, 0xa, 0x6, 0x2, 0x51, 0x52, 0x7, 0x6, 0x2, 0x2, 0x52, 
    0x54, 0x5, 0xa, 0x6, 0x2, 0x53, 0x51, 0x3, 0x2, 0x2, 0x2, 0x54, 0x57, 
    0x3, 0x2, 0x2, 0x2, 0x55, 0x53, 0x3, 0x2, 0x2, 0x2, 0x55, 0x56, 0x3, 
    0x2, 0x2, 0x2, 0x56, 0x9, 0x3, 0x2, 0x2, 0x2, 0x57, 0x55, 0x3, 0x2, 
    0x2, 0x2, 0x58, 0x5d, 0x5, 0xc, 0x7, 0x2, 0x59, 0x5a, 0x7, 0x7, 0x2, 
    0x2, 0x5a, 0x5c, 0x5, 0xc, 0x7, 0x2, 0x5b, 0x59, 0x3, 0x2, 0x2, 0x2, 
    0x5c, 0x5f, 0x3, 0x2, 0x2, 0x2, 0x5d, 0x5b, 0x3, 0x2, 0x2, 0x2, 0x5d, 
    0x5e, 0x3, 0x2, 0x2, 0x2, 0x5e, 0xb, 0x3, 0x2, 0x2, 0x2, 0x5f, 0x5d, 
    0x3, 0x2, 0x2, 0x2, 0x60, 0x65, 0x5, 0xe, 0x8, 0x2, 0x61, 0x62, 0x9, 
    0x2, 0x2, 0x2, 0x62, 0x64, 0x5, 0xe, 0x8, 0x2, 0x63, 0x61, 0x3, 0x2, 
    0x2, 0x2, 0x64, 0x67, 0x3, 0x2, 0x2, 0x2, 0x65, 0x63, 0x3, 0x2, 0x2, 
    0x2, 0x65, 0x66, 0x3, 0x2, 0x2, 0x2, 0x66, 0xd, 0x3, 0x2, 0x2, 0x2, 
    0x67, 0x65, 0x3, 0x2, 0x2, 0x2, 0x68, 0x6d, 0x5, 0x10, 0x9, 0x2, 0x69, 
    0x6a, 0x9, 0x3, 0x2, 0x2, 0x6a, 0x6c, 0x5, 0x10, 0x9, 0x2, 0x6b, 0x69, 
    0x3, 0x2, 0x2, 0x2, 0x6c, 0x6f, 0x3, 0x2, 0x2, 0x2, 0x6d, 0x6b, 0x3, 
    0x2, 0x2, 0x2, 0x6d, 0x6e, 0x3, 0x2, 0x2, 0x2, 0x6e, 0xf, 0x3, 0x2, 
    0x2, 0x2, 0x6f, 0x6d, 0x3, 0x2, 0x2, 0x2, 0x70, 0x75, 0x5, 0x12, 0xa, 
    0x2, 0x71, 0x72, 0x9, 0x4, 0x2, 0x2, 0x72, 0x74, 0x5, 0x12, 0xa, 0x2, 
    0x73, 0x71, 0x3, 0x2, 0x2, 0x2, 0x74, 0x77, 0x3, 0x2, 0x2, 0x2, 0x75, 
    0x73, 0x3, 0x2, 0x2, 0x2, 0x75, 0x76, 0x3, 0x2, 0x2, 0x2, 0x76, 0x11, 
    0x3, 0x2, 0x2, 0x2, 0x77, 0x75, 0x3, 0x2, 0x2, 0x2, 0x78, 0x82, 0x5, 
    0x14, 0xb, 0x2, 0x79, 0x7a, 0x7, 0x11, 0x2, 0x2, 0x7a, 0x82, 0x5, 0x12, 
    0xa, 0x2, 0x7b, 0x7c, 0x7, 0x10, 0x2, 0x2, 0x7c, 0x82, 0x5, 0x12, 0xa, 
    0x2, 0x7d, 0x7e, 0x7, 0x16, 0x2, 0x2, 0x7e, 0x82, 0x5, 0x12, 0xa, 0x2, 
    0x7f, 0x80, 0x7, 0x17, 0x2, 0x2, 0x80, 0x82, 0x5, 0x12, 0xa, 0x2, 0x81, 
    0x78, 0x3, 0x2, 0x2, 0x2, 0x81, 0x79, 0x3, 0x2, 0x2, 0x2, 0x81, 0x7b, 
    0x3, 0x2, 0x2, 0x2, 0x81, 0x7d, 0x3, 0x2, 0x2, 0x2, 0x81, 0x7f, 0x3, 
    0x2, 0x2, 0x2, 0x82, 0x13, 0x3, 0x2, 0x2, 0x2, 0x83, 0x8e, 0x5, 0x16, 
    0xc, 0x2, 0x84, 0x85, 0x5, 0x38, 0x1d, 0x2, 0x85, 0x86, 0x7, 0x18, 0x2, 
    0x2, 0x86, 0x87, 0x7, 0x19, 0x2, 0x2, 0x87, 0x8e, 0x3, 0x2, 0x2, 0x2, 
    0x88, 0x89, 0x5, 0x38, 0x1d, 0x2, 0x89, 0x8a, 0x7, 0x18, 0x2, 0x2, 0x8a, 
    0x8b, 0x5, 0x2, 0x2, 0x2, 0x8b, 0x8c, 0x7, 0x19, 0x2, 0x2, 0x8c, 0x8e, 
    0x3, 0x2, 0x2, 0x2, 0x8d, 0x83, 0x3, 0x2, 0x2, 0x2, 0x8d, 0x84, 0x3, 
    0x2, 0x2, 0x2, 0x8d, 0x88, 0x3, 0x2, 0x2, 0x2, 0x8e, 0xa1, 0x3, 0x2, 
    0x2, 0x2, 0x8f, 0x90, 0x7, 0x1a, 0x2, 0x2, 0x90, 0x91, 0x5, 0x2, 0x2, 
    0x2, 0x91, 0x92, 0x7, 0x1b, 0x2, 0x2, 0x92, 0xa0, 0x3, 0x2, 0x2, 0x2, 
    0x93, 0x94, 0x7, 0x1a, 0x2, 0x2, 0x94, 0x95, 0x5, 0x4, 0x3, 0x2, 0x95, 
    0x96, 0x7, 0x1c, 0x2, 0x2, 0x96, 0x97, 0x5, 0x4, 0x3, 0x2, 0x97, 0x98, 
    0x7, 0x1b, 0x2, 0x2, 0x98, 0xa0, 0x3, 0x2, 0x2, 0x2, 0x99, 0x9a, 0x7, 
    0x18, 0x2, 0x2, 0x9a, 0xa0, 0x7, 0x19, 0x2, 0x2, 0x9b, 0x9c, 0x7, 0x18, 
    0x2, 0x2, 0x9c, 0x9d, 0x5, 0x2, 0x2, 0x2, 0x9d, 0x9e, 0x7, 0x19, 0x2, 
    0x2, 0x9e, 0xa0, 0x3, 0x2, 0x2, 0x2, 0x9f, 0x8f, 0x3, 0x2, 0x2, 0x2, 
    0x9f, 0x93, 0x3, 0x2, 0x2, 0x2, 0x9f, 0x99, 0x3, 0x2, 0x2, 0x2, 0x9f, 
    0x9b, 0x3, 0x2, 0x2, 0x2, 0xa0, 0xa3, 0x3, 0x2, 0x2, 0x2, 0xa1, 0x9f, 
    0x3, 0x2, 0x2, 0x2, 0xa1, 0xa2, 0x3, 0x2, 0x2, 0x2, 0xa2, 0x15, 0x3, 
    0x2, 0x2, 0x2, 0xa3, 0xa1, 0x3, 0x2, 0x2, 0x2, 0xa4, 0xdc, 0x7, 0x1d, 
    0x2, 0x2, 0xa5, 0xdc, 0x7, 0x1e, 0x2, 0x2, 0xa6, 0xdc, 0x7, 0x59, 0x2, 
    0x2, 0xa7, 0xdc, 0x7, 0x5a, 0x2, 0x2, 0xa8, 0xdc, 0x5, 0x36, 0x1c, 0x2, 
    0xa9, 0xdc, 0x7, 0x1f, 0x2, 0x2, 0xaa, 0xab, 0x7, 0x1a, 0x2, 0x2, 0xab, 
    0xdc, 0x7, 0x1b, 0x2, 0x2, 0xac, 0xad, 0x7, 0x1a, 0x2, 0x2, 0xad, 0xae, 
    0x5, 0x2, 0x2, 0x2, 0xae, 0xaf, 0x7, 0x1b, 0x2, 0x2, 0xaf, 0xdc, 0x3, 
    0x2, 0x2, 0x2, 0xb0, 0xb1, 0x7, 0x20, 0x2, 0x2, 0xb1, 0xdc, 0x7, 0x21, 
    0x2, 0x2, 0xb2, 0xdc, 0x5, 0x18, 0xd, 0x2, 0xb3, 0xb4, 0x7, 0x20, 0x2, 
    0x2, 0xb4, 0xb5, 0x5, 0x1a, 0xe, 0x2, 0xb5, 0xb6, 0x7, 0x21, 0x2, 0x2, 
    0xb6, 0xdc, 0x3, 0x2, 0x2, 0x2, 0xb7, 0xb8, 0x7, 0x18, 0x2, 0x2, 0xb8, 
    0xb9, 0x5, 0x6, 0x4, 0x2, 0xb9, 0xba, 0x7, 0x3, 0x2, 0x2, 0xba, 0xbb, 
    0x5, 0x6, 0x4, 0x2, 0xbb, 0xbc, 0x7, 0x19, 0x2, 0x2, 0xbc, 0xdc, 0x3, 
    0x2, 0x2, 0x2, 0xbd, 0xbe, 0x7, 0x8, 0x2, 0x2, 0xbe, 0xbf, 0x5, 0x24, 
    0x13, 0x2, 0xbf, 0xc0, 0x7, 0xd, 0x2, 0x2, 0xc0, 0xc1, 0x5, 0x16, 0xc, 
    0x2, 0xc1, 0xdc, 0x3, 0x2, 0x2, 0x2, 0xc2, 0xc3, 0x7, 0x22, 0x2, 0x2, 
    0xc3, 0xc4, 0x5, 0x2, 0x2, 0x2, 0xc4, 0xc5, 0x7, 0x1c, 0x2, 0x2, 0xc5, 
    0xc6, 0x5, 0x6, 0x4, 0x2, 0xc6, 0xc7, 0x5, 0x1c, 0xf, 0x2, 0xc7, 0xc8, 
    0x7, 0x23, 0x2, 0x2, 0xc8, 0xc9, 0x5, 0x6, 0x4, 0x2, 0xc9, 0xca, 0x7, 
    0x24, 0x2, 0x2, 0xca, 0xdc, 0x3, 0x2, 0x2, 0x2, 0xcb, 0xcc, 0x7, 0x25, 
    0x2, 0x2, 0xcc, 0xcd, 0x5, 0x6, 0x4, 0x2, 0xcd, 0xce, 0x7, 0x1c, 0x2, 
    0x2, 0xce, 0xcf, 0x5, 0x1e, 0x10, 0x2, 0xcf, 0xd0, 0x7, 0x24, 0x2, 0x2, 
    0xd0, 0xdc, 0x3, 0x2, 0x2, 0x2, 0xd1, 0xd2, 0x7, 0x18, 0x2, 0x2, 0xd2, 
    0xd3, 0x5, 0x6, 0x4, 0x2, 0xd3, 0xd4, 0x7, 0x19, 0x2, 0x2, 0xd4, 0xdc, 
    0x3, 0x2, 0x2, 0x2, 0xd5, 0xdc, 0x5, 0x2e, 0x18, 0x2, 0xd6, 0xd7, 0x5, 
    0x2e, 0x18, 0x2, 0xd7, 0xd8, 0x7, 0x26, 0x2, 0x2, 0xd8, 0xdc, 0x3, 0x2, 
    0x2, 0x2, 0xd9, 0xdc, 0x7, 0x27, 0x2, 0x2, 0xda, 0xdc, 0x7, 0x28, 0x2, 
    0x2, 0xdb, 0xa4, 0x3, 0x2, 0x2, 0x2, 0xdb, 0xa5, 0x3, 0x2, 0x2, 0x2, 
    0xdb, 0xa6, 0x3, 0x2, 0x2, 0x2, 0xdb, 0xa7, 0x3, 0x2, 0x2, 0x2, 0xdb, 
    0xa8, 0x3, 0x2, 0x2, 0x2, 0xdb, 0xa9, 0x3, 0x2, 0x2, 0x2, 0xdb, 0xaa, 
    0x3, 0x2, 0x2, 0x2, 0xdb, 0xac, 0x3, 0x2, 0x2, 0x2, 0xdb, 0xb0, 0x3, 
    0x2, 0x2, 0x2, 0xdb, 0xb2, 0x3, 0x2, 0x2, 0x2, 0xdb, 0xb3, 0x3, 0x2, 
    0x2, 0x2, 0xdb, 0xb7, 0x3, 0x2, 0x2, 0x2, 0xdb, 0xbd, 0x3, 0x2, 0x2, 
    0x2, 0xdb, 0xc2, 0x3, 0x2, 0x2, 0x2, 0xdb, 0xcb, 0x3, 0x2, 0x2, 0x2, 
    0xdb, 0xd1, 0x3, 0x2, 0x2, 0x2, 0xdb, 0xd5, 0x3, 0x2, 0x2, 0x2, 0xdb, 
    0xd6, 0x3, 0x2, 0x2, 0x2, 0xdb, 0xd9, 0x3, 0x2, 0x2, 0x2, 0xdb, 0xda, 
    0x3, 0x2, 0x2, 0x2, 0xdc, 0x17, 0x3, 0x2, 0x2, 0x2, 0xdd, 0xde, 0x7, 
    0x20, 0x2, 0x2, 0xde, 0xdf, 0x5, 0x2, 0x2, 0x2, 0xdf, 0xe0, 0x7, 0x21, 
    0x2, 0x2, 0xe0, 0x19, 0x3, 0x2, 0x2, 0x2, 0xe1, 0xe2, 0x5, 0x6, 0x4, 
    0x2, 0xe2, 0xe3, 0x7, 0x1c, 0x2, 0x2, 0xe3, 0xe4, 0x5, 0x6, 0x4, 0x2, 
    0xe4, 0xe5, 0x7, 0x3, 0x2, 0x2, 0xe5, 0xe6, 0x5, 0x6, 0x4, 0x2, 0xe6, 
    0xe7, 0x7, 0x1c, 0x2, 0x2, 0xe7, 0xe8, 0x5, 0x6, 0x4, 0x2, 0xe8, 0x1b, 
    0x3, 0x2, 0x2, 0x2, 0xe9, 0xea, 0x5, 0x6, 0x4, 0x2, 0xea, 0xeb, 0x7, 
    0x1c, 0x2, 0x2, 0xeb, 0xec, 0x5, 0x6, 0x4, 0x2, 0xec, 0xed, 0x7, 0x29, 
    0x2, 0x2, 0xed, 0xef, 0x3, 0x2, 0x2, 0x2, 0xee, 0xe9, 0x3, 0x2, 0x2, 
    0x2, 0xef, 0xf2, 0x3, 0x2, 0x2, 0x2, 0xf0, 0xee, 0x3, 0x2, 0x2, 0x2, 
    0xf0, 0xf1, 0x3, 0x2, 0x2, 0x2, 0xf1, 0x1d, 0x3, 0x2, 0x2, 0x2, 0xf2, 
    0xf0, 0x3, 0x2, 0x2, 0x2, 0xf3, 0xfb, 0x5, 0x20, 0x11, 0x2, 0xf4, 0xf5, 
    0x5, 0x20, 0x11, 0x2, 0xf5, 0xf6, 0x7, 0x23, 0x2, 0x2, 0xf6, 0xf7, 0x5, 
    0x6, 0x4, 0x2, 0xf7, 0xfb, 0x3, 0x2, 0x2, 0x2, 0xf8, 0xf9, 0x7, 0x23, 
    0x2, 0x2, 0xf9, 0xfb, 0x5, 0x6, 0x4, 0x2, 0xfa, 0xf3, 0x3, 0x2, 0x2, 
    0x2, 0xfa, 0xf4, 0x3, 0x2, 0x2, 0x2, 0xfa, 0xf8, 0x3, 0x2, 0x2, 0x2, 
    0xfb, 0x1f, 0x3, 0x2, 0x2, 0x2, 0xfc, 0xfd, 0x7, 0x2a, 0x2, 0x2, 0xfd, 
    0xfe, 0x5, 0x6, 0x4, 0x2, 0xfe, 0xff, 0x7, 0x1c, 0x2, 0x2, 0xff, 0x100, 
    0x5, 0x6, 0x4, 0x2, 0x100, 0x102, 0x3, 0x2, 0x2, 0x2, 0x101, 0xfc, 0x3, 
    0x2, 0x2, 0x2, 0x102, 0x103, 0x3, 0x2, 0x2, 0x2, 0x103, 0x101, 0x3, 
    0x2, 0x2, 0x2, 0x103, 0x104, 0x3, 0x2, 0x2, 0x2, 0x104, 0x21, 0x3, 0x2, 
    0x2, 0x2, 0x105, 0x10a, 0x5, 0x24, 0x13, 0x2, 0x106, 0x107, 0x7, 0x3, 
    0x2, 0x2, 0x107, 0x109, 0x5, 0x24, 0x13, 0x2, 0x108, 0x106, 0x3, 0x2, 
    0x2, 0x2, 0x109, 0x10c, 0x3, 0x2, 0x2, 0x2, 0x10a, 0x108, 0x3, 0x2, 
    0x2, 0x2, 0x10a, 0x10b, 0x3, 0x2, 0x2, 0x2, 0x10b, 0x23, 0x3, 0x2, 0x2, 
    0x2, 0x10c, 0x10a, 0x3, 0x2, 0x2, 0x2, 0x10d, 0x145, 0x7, 0x2b, 0x2, 
    0x2, 0x10e, 0x145, 0x7, 0x2c, 0x2, 0x2, 0x10f, 0x110, 0x7, 0x2c, 0x2, 
    0x2, 0x110, 0x111, 0x7, 0x1a, 0x2, 0x2, 0x111, 0x112, 0x5, 0x6, 0x4, 
    0x2, 0x112, 0x113, 0x7, 0x2d, 0x2, 0x2, 0x113, 0x114, 0x5, 0x6, 0x4, 
    0x2, 0x114, 0x115, 0x7, 0x1b, 0x2, 0x2, 0x115, 0x145, 0x3, 0x2, 0x2, 
    0x2, 0x116, 0x145, 0x7, 0x2e, 0x2, 0x2, 0x117, 0x145, 0x7, 0x2f, 0x2, 
    0x2, 0x118, 0x119, 0x7, 0x30, 0x2, 0x2, 0x119, 0x145, 0x5, 0x24, 0x13, 
    0x2, 0x11a, 0x11b, 0x7, 0x30, 0x2, 0x2, 0x11b, 0x11c, 0x7, 0x1a, 0x2, 
    0x2, 0x11c, 0x11d, 0x5, 0x6, 0x4, 0x2, 0x11d, 0x11e, 0x7, 0x1b, 0x2, 
    0x2, 0x11e, 0x11f, 0x5, 0x24, 0x13, 0x2, 0x11f, 0x145, 0x3, 0x2, 0x2, 
    0x2, 0x120, 0x121, 0x7, 0x30, 0x2, 0x2, 0x121, 0x122, 0x7, 0x1a, 0x2, 
    0x2, 0x122, 0x123, 0x5, 0x6, 0x4, 0x2, 0x123, 0x124, 0x7, 0x2d, 0x2, 
    0x2, 0x124, 0x125, 0x5, 0x6, 0x4, 0x2, 0x125, 0x126, 0x7, 0x1b, 0x2, 
    0x2, 0x126, 0x127, 0x5, 0x24, 0x13, 0x2, 0x127, 0x145, 0x3, 0x2, 0x2, 
    0x2, 0x128, 0x129, 0x7, 0x31, 0x2, 0x2, 0x129, 0x145, 0x5, 0x24, 0x13, 
    0x2, 0x12a, 0x12b, 0x7, 0x32, 0x2, 0x2, 0x12b, 0x12c, 0x7, 0x18, 0x2, 
    0x2, 0x12c, 0x12d, 0x5, 0x24, 0x13, 0x2, 0x12d, 0x12e, 0x7, 0x1c, 0x2, 
    0x2, 0x12e, 0x12f, 0x5, 0x24, 0x13, 0x2, 0x12f, 0x130, 0x7, 0x19, 0x2, 
    0x2, 0x130, 0x145, 0x3, 0x2, 0x2, 0x2, 0x131, 0x132, 0x7, 0x33, 0x2, 
    0x2, 0x132, 0x133, 0x7, 0x18, 0x2, 0x2, 0x133, 0x134, 0x5, 0x26, 0x14, 
    0x2, 0x134, 0x135, 0x7, 0x19, 0x2, 0x2, 0x135, 0x145, 0x3, 0x2, 0x2, 
    0x2, 0x136, 0x137, 0x7, 0x34, 0x2, 0x2, 0x137, 0x138, 0x5, 0x24, 0x13, 
    0x2, 0x138, 0x139, 0x7, 0x18, 0x2, 0x2, 0x139, 0x13a, 0x7, 0x19, 0x2, 
    0x2, 0x13a, 0x145, 0x3, 0x2, 0x2, 0x2, 0x13b, 0x13c, 0x7, 0x34, 0x2, 
    0x2, 0x13c, 0x13d, 0x5, 0x24, 0x13, 0x2, 0x13d, 0x13e, 0x7, 0x18, 0x2, 
    0x2, 0x13e, 0x13f, 0x5, 0x22, 0x12, 0x2, 0x13f, 0x140, 0x7, 0x19, 0x2, 
    0x2, 0x140, 0x145, 0x3, 0x2, 0x2, 0x2, 0x141, 0x142, 0x7, 0x35, 0x2, 
    0x2, 0x142, 0x145, 0x5, 0x24, 0x13, 0x2, 0x143, 0x145, 0x5, 0x2e, 0x18, 
    0x2, 0x144, 0x10d, 0x3, 0x2, 0x2, 0x2, 0x144, 0x10e, 0x3, 0x2, 0x2, 
    0x2, 0x144, 0x10f, 0x3, 0x2, 0x2, 0x2, 0x144, 0x116, 0x3, 0x2, 0x2, 
    0x2, 0x144, 0x117, 0x3, 0x2, 0x2, 0x2, 0x144, 0x118, 0x3, 0x2, 0x2, 
    0x2, 0x144, 0x11a, 0x3, 0x2, 0x2, 0x2, 0x144, 0x120, 0x3, 0x2, 0x2, 
    0x2, 0x144, 0x128, 0x3, 0x2, 0x2, 0x2, 0x144, 0x12a, 0x3, 0x2, 0x2, 
    0x2, 0x144, 0x131, 0x3, 0x2, 0x2, 0x2, 0x144, 0x136, 0x3, 0x2, 0x2, 
    0x2, 0x144, 0x13b, 0x3, 0x2, 0x2, 0x2, 0x144, 0x141, 0x3, 0x2, 0x2, 
    0x2, 0x144, 0x143, 0x3, 0x2, 0x2, 0x2, 0x145, 0x25, 0x3, 0x2, 0x2, 0x2, 
    0x146, 0x14b, 0x5, 0x28, 0x15, 0x2, 0x147, 0x148, 0x7, 0x3, 0x2, 0x2, 
    0x148, 0x14a, 0x5, 0x28, 0x15, 0x2, 0x149, 0x147, 0x3, 0x2, 0x2, 0x2, 
    0x14a, 0x14d, 0x3, 0x2, 0x2, 0x2, 0x14b, 0x149, 0x3, 0x2, 0x2, 0x2, 
    0x14b, 0x14c, 0x3, 0x2, 0x2, 0x2, 0x14c, 0x27, 0x3, 0x2, 0x2, 0x2, 0x14d, 
    0x14b, 0x3, 0x2, 0x2, 0x2, 0x14e, 0x14f, 0x5, 0x24, 0x13, 0x2, 0x14f, 
    0x150, 0x5, 0x34, 0x1b, 0x2, 0x150, 0x29, 0x3, 0x2, 0x2, 0x2, 0x151, 
    0x152, 0x7, 0x20, 0x2, 0x2, 0x152, 0x153, 0x5, 0x2c, 0x17, 0x2, 0x153, 
    0x154, 0x7, 0x21, 0x2, 0x2, 0x154, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x155, 
    0x15a, 0x5, 0x2e, 0x18, 0x2, 0x156, 0x157, 0x7, 0x3, 0x2, 0x2, 0x157, 
    0x159, 0x5, 0x2e, 0x18, 0x2, 0x158, 0x156, 0x3, 0x2, 0x2, 0x2, 0x159, 
    0x15c, 0x3, 0x2, 0x2, 0x2, 0x15a, 0x158, 0x3, 0x2, 0x2, 0x2, 0x15a, 
    0x15b, 0x3, 0x2, 0x2, 0x2, 0x15b, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x15c, 0x15a, 
    0x3, 0x2, 0x2, 0x2, 0x15d, 0x162, 0x5, 0x34, 0x1b, 0x2, 0x15e, 0x162, 
    0x7, 0x5d, 0x2, 0x2, 0x15f, 0x162, 0x7, 0x5e, 0x2, 0x2, 0x160, 0x162, 
    0x7, 0x5f, 0x2, 0x2, 0x161, 0x15d, 0x3, 0x2, 0x2, 0x2, 0x161, 0x15e, 
    0x3, 0x2, 0x2, 0x2, 0x161, 0x15f, 0x3, 0x2, 0x2, 0x2, 0x161, 0x160, 
    0x3, 0x2, 0x2, 0x2, 0x162, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x163, 0x165, 0x5, 
    0x32, 0x1a, 0x2, 0x164, 0x163, 0x3, 0x2, 0x2, 0x2, 0x164, 0x165, 0x3, 
    0x2, 0x2, 0x2, 0x165, 0x31, 0x3, 0x2, 0x2, 0x2, 0x166, 0x167, 0x9, 0x5, 
    0x2, 0x2, 0x167, 0x33, 0x3, 0x2, 0x2, 0x2, 0x168, 0x169, 0x7, 0x5c, 
    0x2, 0x2, 0x169, 0x35, 0x3, 0x2, 0x2, 0x2, 0x16a, 0x16b, 0x7, 0x5b, 
    0x2, 0x2, 0x16b, 0x37, 0x3, 0x2, 0x2, 0x2, 0x16c, 0x16d, 0x9, 0x6, 0x2, 
    0x2, 0x16d, 0x39, 0x3, 0x2, 0x2, 0x2, 0x18, 0x3f, 0x43, 0x4e, 0x55, 
    0x5d, 0x65, 0x6d, 0x75, 0x81, 0x8d, 0x9f, 0xa1, 0xdb, 0xf0, 0xfa, 0x103, 
    0x10a, 0x144, 0x14b, 0x15a, 0x161, 0x164, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

ExpressionsParser::Initializer ExpressionsParser::_init;
