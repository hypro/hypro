
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
    setState(60);
    expression();
    setState(65);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ExpressionsParser::T__0) {
      setState(61);
      match(ExpressionsParser::T__0);
      setState(62);
      expression();
      setState(67);
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
    setState(69);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << ExpressionsParser::T__7)
      | (1ULL << ExpressionsParser::T__8)
      | (1ULL << ExpressionsParser::T__9)
      | (1ULL << ExpressionsParser::T__10)
      | (1ULL << ExpressionsParser::T__11)
      | (1ULL << ExpressionsParser::T__13)
      | (1ULL << ExpressionsParser::T__16)
      | (1ULL << ExpressionsParser::T__17)
      | (1ULL << ExpressionsParser::T__18)
      | (1ULL << ExpressionsParser::T__19)
      | (1ULL << ExpressionsParser::T__21)
      | (1ULL << ExpressionsParser::T__23)
      | (1ULL << ExpressionsParser::T__26)
      | (1ULL << ExpressionsParser::T__27)
      | (1ULL << ExpressionsParser::T__28)
      | (1ULL << ExpressionsParser::T__45)
      | (1ULL << ExpressionsParser::T__46)
      | (1ULL << ExpressionsParser::T__47)
      | (1ULL << ExpressionsParser::T__48)
      | (1ULL << ExpressionsParser::T__49)
      | (1ULL << ExpressionsParser::T__50)
      | (1ULL << ExpressionsParser::T__51)
      | (1ULL << ExpressionsParser::T__52)
      | (1ULL << ExpressionsParser::T__53)
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
      | (1ULL << (ExpressionsParser::NUMBER - 64))
      | (1ULL << (ExpressionsParser::REALNUMBER - 64))
      | (1ULL << (ExpressionsParser::STRING - 64))
      | (1ULL << (ExpressionsParser::IDENTIFIER - 64))
      | (1ULL << (ExpressionsParser::RELATIVENAME - 64))
      | (1ULL << (ExpressionsParser::ABSOLUTENAME - 64))
      | (1ULL << (ExpressionsParser::ROOTNAME - 64)))) != 0)) {
      setState(68);
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
    setState(80);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(71);
      orExpression();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(72);
      orExpression();
      setState(73);
      match(ExpressionsParser::T__1);
      setState(74);
      orExpression();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(76);
      orExpression();
      setState(77);
      match(ExpressionsParser::T__2);
      setState(78);
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

ExpressionsParser::EquationsContext::EquationsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ExpressionsParser::EquationContext *> ExpressionsParser::EquationsContext::equation() {
  return getRuleContexts<ExpressionsParser::EquationContext>();
}

ExpressionsParser::EquationContext* ExpressionsParser::EquationsContext::equation(size_t i) {
  return getRuleContext<ExpressionsParser::EquationContext>(i);
}


size_t ExpressionsParser::EquationsContext::getRuleIndex() const {
  return ExpressionsParser::RuleEquations;
}

antlrcpp::Any ExpressionsParser::EquationsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExpressionsVisitor*>(visitor))
    return parserVisitor->visitEquations(this);
  else
    return visitor->visitChildren(this);
}

ExpressionsParser::EquationsContext* ExpressionsParser::equations() {
  EquationsContext *_localctx = _tracker.createInstance<EquationsContext>(_ctx, getState());
  enterRule(_localctx, 6, ExpressionsParser::RuleEquations);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(82);
    equation();
    setState(87);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ExpressionsParser::T__0) {
      setState(83);
      match(ExpressionsParser::T__0);
      setState(84);
      equation();
      setState(89);
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

ExpressionsParser::EquationContext::EquationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ExpressionsParser::EquationContext::getRuleIndex() const {
  return ExpressionsParser::RuleEquation;
}

void ExpressionsParser::EquationContext::copyFrom(EquationContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- EquationDerivateContext ------------------------------------------------------------------

ExpressionsParser::IdentifierContext* ExpressionsParser::EquationDerivateContext::identifier() {
  return getRuleContext<ExpressionsParser::IdentifierContext>(0);
}

ExpressionsParser::ExpressionContext* ExpressionsParser::EquationDerivateContext::expression() {
  return getRuleContext<ExpressionsParser::ExpressionContext>(0);
}

ExpressionsParser::EquationDerivateContext::EquationDerivateContext(EquationContext *ctx) { copyFrom(ctx); }

antlrcpp::Any ExpressionsParser::EquationDerivateContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExpressionsVisitor*>(visitor))
    return parserVisitor->visitEquationDerivate(this);
  else
    return visitor->visitChildren(this);
}
//----------------- EquationNonDerivateContext ------------------------------------------------------------------

ExpressionsParser::IdentifierContext* ExpressionsParser::EquationNonDerivateContext::identifier() {
  return getRuleContext<ExpressionsParser::IdentifierContext>(0);
}

ExpressionsParser::ExpressionContext* ExpressionsParser::EquationNonDerivateContext::expression() {
  return getRuleContext<ExpressionsParser::ExpressionContext>(0);
}

ExpressionsParser::EquationNonDerivateContext::EquationNonDerivateContext(EquationContext *ctx) { copyFrom(ctx); }

antlrcpp::Any ExpressionsParser::EquationNonDerivateContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExpressionsVisitor*>(visitor))
    return parserVisitor->visitEquationNonDerivate(this);
  else
    return visitor->visitChildren(this);
}
ExpressionsParser::EquationContext* ExpressionsParser::equation() {
  EquationContext *_localctx = _tracker.createInstance<EquationContext>(_ctx, getState());
  enterRule(_localctx, 8, ExpressionsParser::RuleEquation);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(99);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<EquationContext *>(_tracker.createInstance<ExpressionsParser::EquationDerivateContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(90);
      identifier();
      setState(91);
      match(ExpressionsParser::T__3);
      setState(92);
      match(ExpressionsParser::T__4);
      setState(93);
      expression();
      break;
    }

    case 2: {
      _localctx = dynamic_cast<EquationContext *>(_tracker.createInstance<ExpressionsParser::EquationNonDerivateContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(95);
      identifier();
      setState(96);
      match(ExpressionsParser::T__4);
      setState(97);
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
  enterRule(_localctx, 10, ExpressionsParser::RuleOrExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(101);
    andExpression();
    setState(106);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ExpressionsParser::T__5) {
      setState(102);
      match(ExpressionsParser::T__5);
      setState(103);
      andExpression();
      setState(108);
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
  enterRule(_localctx, 12, ExpressionsParser::RuleAndExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(109);
    compareExpression();
    setState(114);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ExpressionsParser::T__6) {
      setState(110);
      match(ExpressionsParser::T__6);
      setState(111);
      compareExpression();
      setState(116);
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

std::vector<tree::TerminalNode *> ExpressionsParser::CompareExpressionContext::COMPOP() {
  return getTokens(ExpressionsParser::COMPOP);
}

tree::TerminalNode* ExpressionsParser::CompareExpressionContext::COMPOP(size_t i) {
  return getToken(ExpressionsParser::COMPOP, i);
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
  enterRule(_localctx, 14, ExpressionsParser::RuleCompareExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(117);
    addExpression();
    setState(122);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ExpressionsParser::COMPOP) {
      setState(118);
      match(ExpressionsParser::COMPOP);
      setState(119);
      addExpression();
      setState(124);
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

ExpressionsParser::AddExpressionContext::AddExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ExpressionsParser::MulExpressionContext *> ExpressionsParser::AddExpressionContext::mulExpression() {
  return getRuleContexts<ExpressionsParser::MulExpressionContext>();
}

ExpressionsParser::MulExpressionContext* ExpressionsParser::AddExpressionContext::mulExpression(size_t i) {
  return getRuleContext<ExpressionsParser::MulExpressionContext>(i);
}

std::vector<tree::TerminalNode *> ExpressionsParser::AddExpressionContext::ADDOP() {
  return getTokens(ExpressionsParser::ADDOP);
}

tree::TerminalNode* ExpressionsParser::AddExpressionContext::ADDOP(size_t i) {
  return getToken(ExpressionsParser::ADDOP, i);
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
  enterRule(_localctx, 16, ExpressionsParser::RuleAddExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(125);
    mulExpression();
    setState(130);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ExpressionsParser::ADDOP) {
      setState(126);
      match(ExpressionsParser::ADDOP);
      setState(127);
      mulExpression();
      setState(132);
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

ExpressionsParser::MulExpressionContext::MulExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ExpressionsParser::UnaryExpressionContext *> ExpressionsParser::MulExpressionContext::unaryExpression() {
  return getRuleContexts<ExpressionsParser::UnaryExpressionContext>();
}

ExpressionsParser::UnaryExpressionContext* ExpressionsParser::MulExpressionContext::unaryExpression(size_t i) {
  return getRuleContext<ExpressionsParser::UnaryExpressionContext>(i);
}

std::vector<tree::TerminalNode *> ExpressionsParser::MulExpressionContext::MULOP() {
  return getTokens(ExpressionsParser::MULOP);
}

tree::TerminalNode* ExpressionsParser::MulExpressionContext::MULOP(size_t i) {
  return getToken(ExpressionsParser::MULOP, i);
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
  enterRule(_localctx, 18, ExpressionsParser::RuleMulExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(133);
    unaryExpression();
    setState(138);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ExpressionsParser::MULOP) {
      setState(134);
      match(ExpressionsParser::MULOP);
      setState(135);
      unaryExpression();
      setState(140);
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


size_t ExpressionsParser::UnaryExpressionContext::getRuleIndex() const {
  return ExpressionsParser::RuleUnaryExpression;
}

void ExpressionsParser::UnaryExpressionContext::copyFrom(UnaryExpressionContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- UnaryExprContext ------------------------------------------------------------------

ExpressionsParser::UnaryExpressionContext* ExpressionsParser::UnaryExprContext::unaryExpression() {
  return getRuleContext<ExpressionsParser::UnaryExpressionContext>(0);
}

ExpressionsParser::UnaryExprContext::UnaryExprContext(UnaryExpressionContext *ctx) { copyFrom(ctx); }

antlrcpp::Any ExpressionsParser::UnaryExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExpressionsVisitor*>(visitor))
    return parserVisitor->visitUnaryExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UnaryExprFuncContext ------------------------------------------------------------------

ExpressionsParser::FuncExpressionContext* ExpressionsParser::UnaryExprFuncContext::funcExpression() {
  return getRuleContext<ExpressionsParser::FuncExpressionContext>(0);
}

ExpressionsParser::UnaryExprFuncContext::UnaryExprFuncContext(UnaryExpressionContext *ctx) { copyFrom(ctx); }

antlrcpp::Any ExpressionsParser::UnaryExprFuncContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExpressionsVisitor*>(visitor))
    return parserVisitor->visitUnaryExprFunc(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UnaryExprMinusContext ------------------------------------------------------------------

ExpressionsParser::UnaryExpressionContext* ExpressionsParser::UnaryExprMinusContext::unaryExpression() {
  return getRuleContext<ExpressionsParser::UnaryExpressionContext>(0);
}

ExpressionsParser::UnaryExprMinusContext::UnaryExprMinusContext(UnaryExpressionContext *ctx) { copyFrom(ctx); }

antlrcpp::Any ExpressionsParser::UnaryExprMinusContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExpressionsVisitor*>(visitor))
    return parserVisitor->visitUnaryExprMinus(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UnaryExprPlusContext ------------------------------------------------------------------

ExpressionsParser::UnaryExpressionContext* ExpressionsParser::UnaryExprPlusContext::unaryExpression() {
  return getRuleContext<ExpressionsParser::UnaryExpressionContext>(0);
}

ExpressionsParser::UnaryExprPlusContext::UnaryExprPlusContext(UnaryExpressionContext *ctx) { copyFrom(ctx); }

antlrcpp::Any ExpressionsParser::UnaryExprPlusContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExpressionsVisitor*>(visitor))
    return parserVisitor->visitUnaryExprPlus(this);
  else
    return visitor->visitChildren(this);
}
ExpressionsParser::UnaryExpressionContext* ExpressionsParser::unaryExpression() {
  UnaryExpressionContext *_localctx = _tracker.createInstance<UnaryExpressionContext>(_ctx, getState());
  enterRule(_localctx, 20, ExpressionsParser::RuleUnaryExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(150);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ExpressionsParser::T__11:
      case ExpressionsParser::T__13:
      case ExpressionsParser::T__16:
      case ExpressionsParser::T__17:
      case ExpressionsParser::T__18:
      case ExpressionsParser::T__19:
      case ExpressionsParser::T__21:
      case ExpressionsParser::T__23:
      case ExpressionsParser::T__26:
      case ExpressionsParser::T__27:
      case ExpressionsParser::T__28:
      case ExpressionsParser::T__45:
      case ExpressionsParser::T__46:
      case ExpressionsParser::T__47:
      case ExpressionsParser::T__48:
      case ExpressionsParser::T__49:
      case ExpressionsParser::T__50:
      case ExpressionsParser::T__51:
      case ExpressionsParser::T__52:
      case ExpressionsParser::T__53:
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
      case ExpressionsParser::NUMBER:
      case ExpressionsParser::REALNUMBER:
      case ExpressionsParser::STRING:
      case ExpressionsParser::IDENTIFIER:
      case ExpressionsParser::RELATIVENAME:
      case ExpressionsParser::ABSOLUTENAME:
      case ExpressionsParser::ROOTNAME: {
        _localctx = dynamic_cast<UnaryExpressionContext *>(_tracker.createInstance<ExpressionsParser::UnaryExprFuncContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(141);
        funcExpression();
        break;
      }

      case ExpressionsParser::T__7: {
        _localctx = dynamic_cast<UnaryExpressionContext *>(_tracker.createInstance<ExpressionsParser::UnaryExprMinusContext>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(142);
        match(ExpressionsParser::T__7);
        setState(143);
        unaryExpression();
        break;
      }

      case ExpressionsParser::T__8: {
        _localctx = dynamic_cast<UnaryExpressionContext *>(_tracker.createInstance<ExpressionsParser::UnaryExprPlusContext>(_localctx));
        enterOuterAlt(_localctx, 3);
        setState(144);
        match(ExpressionsParser::T__8);
        setState(145);
        unaryExpression();
        break;
      }

      case ExpressionsParser::T__9: {
        _localctx = dynamic_cast<UnaryExpressionContext *>(_tracker.createInstance<ExpressionsParser::UnaryExprContext>(_localctx));
        enterOuterAlt(_localctx, 4);
        setState(146);
        match(ExpressionsParser::T__9);
        setState(147);
        unaryExpression();
        break;
      }

      case ExpressionsParser::T__10: {
        _localctx = dynamic_cast<UnaryExpressionContext *>(_tracker.createInstance<ExpressionsParser::UnaryExprContext>(_localctx));
        enterOuterAlt(_localctx, 5);
        setState(148);
        match(ExpressionsParser::T__10);
        setState(149);
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
  enterRule(_localctx, 22, ExpressionsParser::RuleFuncExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(162);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      setState(152);
      expressionFactor();
      break;
    }

    case 2: {
      setState(153);
      stdLibFunction();
      setState(154);
      match(ExpressionsParser::T__11);
      setState(155);
      match(ExpressionsParser::T__12);
      break;
    }

    case 3: {
      setState(157);
      stdLibFunction();
      setState(158);
      match(ExpressionsParser::T__11);
      setState(159);
      expressions();
      setState(160);
      match(ExpressionsParser::T__12);
      break;
    }

    }
    setState(182);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(180);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
        case 1: {
          setState(164);
          match(ExpressionsParser::T__13);
          setState(165);
          expressions();
          setState(166);
          match(ExpressionsParser::T__14);
          break;
        }

        case 2: {
          setState(168);
          match(ExpressionsParser::T__13);
          setState(169);
          optExpression();
          setState(170);
          match(ExpressionsParser::T__15);
          setState(171);
          optExpression();
          setState(172);
          match(ExpressionsParser::T__14);
          break;
        }

        case 3: {
          setState(174);
          match(ExpressionsParser::T__11);
          setState(175);
          match(ExpressionsParser::T__12);
          break;
        }

        case 4: {
          setState(176);
          match(ExpressionsParser::T__11);
          setState(177);
          expressions();
          setState(178);
          match(ExpressionsParser::T__12);
          break;
        }

        } 
      }
      setState(184);
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

//----------------- ExpressionFactorContext ------------------------------------------------------------------

ExpressionsParser::ExpressionFactorContext::ExpressionFactorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ExpressionsParser::ExpressionFactorContext::getRuleIndex() const {
  return ExpressionsParser::RuleExpressionFactor;
}

void ExpressionsParser::ExpressionFactorContext::copyFrom(ExpressionFactorContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ExprFactNumberContext ------------------------------------------------------------------

tree::TerminalNode* ExpressionsParser::ExprFactNumberContext::NUMBER() {
  return getToken(ExpressionsParser::NUMBER, 0);
}

ExpressionsParser::ExprFactNumberContext::ExprFactNumberContext(ExpressionFactorContext *ctx) { copyFrom(ctx); }

antlrcpp::Any ExpressionsParser::ExprFactNumberContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExpressionsVisitor*>(visitor))
    return parserVisitor->visitExprFactNumber(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprFactContext ------------------------------------------------------------------

ExpressionsParser::StringTokenContext* ExpressionsParser::ExprFactContext::stringToken() {
  return getRuleContext<ExpressionsParser::StringTokenContext>(0);
}

ExpressionsParser::ExpressionsContext* ExpressionsParser::ExprFactContext::expressions() {
  return getRuleContext<ExpressionsParser::ExpressionsContext>(0);
}

ExpressionsParser::NonEmptySetExpressionContext* ExpressionsParser::ExprFactContext::nonEmptySetExpression() {
  return getRuleContext<ExpressionsParser::NonEmptySetExpressionContext>(0);
}

ExpressionsParser::DictPairsContext* ExpressionsParser::ExprFactContext::dictPairs() {
  return getRuleContext<ExpressionsParser::DictPairsContext>(0);
}

std::vector<ExpressionsParser::ExpressionContext *> ExpressionsParser::ExprFactContext::expression() {
  return getRuleContexts<ExpressionsParser::ExpressionContext>();
}

ExpressionsParser::ExpressionContext* ExpressionsParser::ExprFactContext::expression(size_t i) {
  return getRuleContext<ExpressionsParser::ExpressionContext>(i);
}

ExpressionsParser::TypeContext* ExpressionsParser::ExprFactContext::type() {
  return getRuleContext<ExpressionsParser::TypeContext>(0);
}

ExpressionsParser::ExpressionFactorContext* ExpressionsParser::ExprFactContext::expressionFactor() {
  return getRuleContext<ExpressionsParser::ExpressionFactorContext>(0);
}

ExpressionsParser::OptElifExprsContext* ExpressionsParser::ExprFactContext::optElifExprs() {
  return getRuleContext<ExpressionsParser::OptElifExprsContext>(0);
}

ExpressionsParser::SwitchBodyContext* ExpressionsParser::ExprFactContext::switchBody() {
  return getRuleContext<ExpressionsParser::SwitchBodyContext>(0);
}

ExpressionsParser::NameContext* ExpressionsParser::ExprFactContext::name() {
  return getRuleContext<ExpressionsParser::NameContext>(0);
}

ExpressionsParser::ExprFactContext::ExprFactContext(ExpressionFactorContext *ctx) { copyFrom(ctx); }

antlrcpp::Any ExpressionsParser::ExprFactContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExpressionsVisitor*>(visitor))
    return parserVisitor->visitExprFact(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprFactRealNumberContext ------------------------------------------------------------------

tree::TerminalNode* ExpressionsParser::ExprFactRealNumberContext::REALNUMBER() {
  return getToken(ExpressionsParser::REALNUMBER, 0);
}

ExpressionsParser::ExprFactRealNumberContext::ExprFactRealNumberContext(ExpressionFactorContext *ctx) { copyFrom(ctx); }

antlrcpp::Any ExpressionsParser::ExprFactRealNumberContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExpressionsVisitor*>(visitor))
    return parserVisitor->visitExprFactRealNumber(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprFactNameContext ------------------------------------------------------------------

ExpressionsParser::NameContext* ExpressionsParser::ExprFactNameContext::name() {
  return getRuleContext<ExpressionsParser::NameContext>(0);
}

ExpressionsParser::ExprFactNameContext::ExprFactNameContext(ExpressionFactorContext *ctx) { copyFrom(ctx); }

antlrcpp::Any ExpressionsParser::ExprFactNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExpressionsVisitor*>(visitor))
    return parserVisitor->visitExprFactName(this);
  else
    return visitor->visitChildren(this);
}
ExpressionsParser::ExpressionFactorContext* ExpressionsParser::expressionFactor() {
  ExpressionFactorContext *_localctx = _tracker.createInstance<ExpressionFactorContext>(_ctx, getState());
  enterRule(_localctx, 24, ExpressionsParser::RuleExpressionFactor);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(240);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<ExpressionsParser::ExprFactContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(185);
      match(ExpressionsParser::T__16);
      break;
    }

    case 2: {
      _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<ExpressionsParser::ExprFactContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(186);
      match(ExpressionsParser::T__17);
      break;
    }

    case 3: {
      _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<ExpressionsParser::ExprFactNumberContext>(_localctx));
      enterOuterAlt(_localctx, 3);
      setState(187);
      match(ExpressionsParser::NUMBER);
      break;
    }

    case 4: {
      _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<ExpressionsParser::ExprFactRealNumberContext>(_localctx));
      enterOuterAlt(_localctx, 4);
      setState(188);
      match(ExpressionsParser::REALNUMBER);
      break;
    }

    case 5: {
      _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<ExpressionsParser::ExprFactNameContext>(_localctx));
      enterOuterAlt(_localctx, 5);
      setState(189);
      name();
      break;
    }

    case 6: {
      _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<ExpressionsParser::ExprFactContext>(_localctx));
      enterOuterAlt(_localctx, 6);
      setState(190);
      stringToken();
      break;
    }

    case 7: {
      _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<ExpressionsParser::ExprFactContext>(_localctx));
      enterOuterAlt(_localctx, 7);
      setState(191);
      match(ExpressionsParser::T__18);
      break;
    }

    case 8: {
      _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<ExpressionsParser::ExprFactContext>(_localctx));
      enterOuterAlt(_localctx, 8);
      setState(192);
      match(ExpressionsParser::T__13);
      setState(193);
      match(ExpressionsParser::T__14);
      break;
    }

    case 9: {
      _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<ExpressionsParser::ExprFactContext>(_localctx));
      enterOuterAlt(_localctx, 9);
      setState(194);
      match(ExpressionsParser::T__13);
      setState(195);
      expressions();
      setState(196);
      match(ExpressionsParser::T__14);
      break;
    }

    case 10: {
      _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<ExpressionsParser::ExprFactContext>(_localctx));
      enterOuterAlt(_localctx, 10);
      setState(198);
      match(ExpressionsParser::T__19);
      setState(199);
      match(ExpressionsParser::T__20);
      break;
    }

    case 11: {
      _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<ExpressionsParser::ExprFactContext>(_localctx));
      enterOuterAlt(_localctx, 11);
      setState(200);
      nonEmptySetExpression();
      break;
    }

    case 12: {
      _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<ExpressionsParser::ExprFactContext>(_localctx));
      enterOuterAlt(_localctx, 12);
      setState(201);
      match(ExpressionsParser::T__19);
      setState(202);
      dictPairs();
      setState(203);
      match(ExpressionsParser::T__20);
      break;
    }

    case 13: {
      _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<ExpressionsParser::ExprFactContext>(_localctx));
      enterOuterAlt(_localctx, 13);
      setState(205);
      match(ExpressionsParser::T__11);
      setState(206);
      expression();
      setState(207);
      match(ExpressionsParser::T__0);
      setState(208);
      expression();
      setState(209);
      match(ExpressionsParser::T__12);
      break;
    }

    case 14: {
      _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<ExpressionsParser::ExprFactContext>(_localctx));
      enterOuterAlt(_localctx, 14);
      setState(211);
      match(ExpressionsParser::T__21);
      setState(212);
      type();
      setState(213);
      match(ExpressionsParser::T__22);
      setState(214);
      expressionFactor();
      break;
    }

    case 15: {
      _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<ExpressionsParser::ExprFactContext>(_localctx));
      enterOuterAlt(_localctx, 15);
      setState(216);
      match(ExpressionsParser::T__23);
      setState(217);
      expressions();
      setState(218);
      match(ExpressionsParser::T__15);
      setState(219);
      expression();
      setState(220);
      optElifExprs();
      setState(221);
      match(ExpressionsParser::T__24);
      setState(222);
      expression();
      setState(223);
      match(ExpressionsParser::T__25);
      break;
    }

    case 16: {
      _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<ExpressionsParser::ExprFactContext>(_localctx));
      enterOuterAlt(_localctx, 16);
      setState(225);
      match(ExpressionsParser::T__26);
      setState(226);
      expression();
      setState(227);
      match(ExpressionsParser::T__15);
      setState(228);
      switchBody();
      setState(229);
      match(ExpressionsParser::T__25);
      break;
    }

    case 17: {
      _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<ExpressionsParser::ExprFactContext>(_localctx));
      enterOuterAlt(_localctx, 17);
      setState(231);
      match(ExpressionsParser::T__11);
      setState(232);
      expression();
      setState(233);
      match(ExpressionsParser::T__12);
      break;
    }

    case 18: {
      _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<ExpressionsParser::ExprFactContext>(_localctx));
      enterOuterAlt(_localctx, 18);
      setState(235);
      name();
      setState(236);
      match(ExpressionsParser::T__3);
      break;
    }

    case 19: {
      _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<ExpressionsParser::ExprFactContext>(_localctx));
      enterOuterAlt(_localctx, 19);
      setState(238);
      match(ExpressionsParser::T__27);
      break;
    }

    case 20: {
      _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<ExpressionsParser::ExprFactContext>(_localctx));
      enterOuterAlt(_localctx, 20);
      setState(239);
      match(ExpressionsParser::T__28);
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
  enterRule(_localctx, 26, ExpressionsParser::RuleNonEmptySetExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(242);
    match(ExpressionsParser::T__19);
    setState(243);
    expressions();
    setState(244);
    match(ExpressionsParser::T__20);
   
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
  enterRule(_localctx, 28, ExpressionsParser::RuleDictPairs);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(246);
    expression();
    setState(247);
    match(ExpressionsParser::T__15);
    setState(248);
    expression();

    setState(249);
    match(ExpressionsParser::T__0);
    setState(250);
    expression();
    setState(251);
    match(ExpressionsParser::T__15);
    setState(252);
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
  enterRule(_localctx, 30, ExpressionsParser::RuleOptElifExprs);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(261);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << ExpressionsParser::T__7)
      | (1ULL << ExpressionsParser::T__8)
      | (1ULL << ExpressionsParser::T__9)
      | (1ULL << ExpressionsParser::T__10)
      | (1ULL << ExpressionsParser::T__11)
      | (1ULL << ExpressionsParser::T__13)
      | (1ULL << ExpressionsParser::T__16)
      | (1ULL << ExpressionsParser::T__17)
      | (1ULL << ExpressionsParser::T__18)
      | (1ULL << ExpressionsParser::T__19)
      | (1ULL << ExpressionsParser::T__21)
      | (1ULL << ExpressionsParser::T__23)
      | (1ULL << ExpressionsParser::T__26)
      | (1ULL << ExpressionsParser::T__27)
      | (1ULL << ExpressionsParser::T__28)
      | (1ULL << ExpressionsParser::T__45)
      | (1ULL << ExpressionsParser::T__46)
      | (1ULL << ExpressionsParser::T__47)
      | (1ULL << ExpressionsParser::T__48)
      | (1ULL << ExpressionsParser::T__49)
      | (1ULL << ExpressionsParser::T__50)
      | (1ULL << ExpressionsParser::T__51)
      | (1ULL << ExpressionsParser::T__52)
      | (1ULL << ExpressionsParser::T__53)
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
      | (1ULL << (ExpressionsParser::NUMBER - 64))
      | (1ULL << (ExpressionsParser::REALNUMBER - 64))
      | (1ULL << (ExpressionsParser::STRING - 64))
      | (1ULL << (ExpressionsParser::IDENTIFIER - 64))
      | (1ULL << (ExpressionsParser::RELATIVENAME - 64))
      | (1ULL << (ExpressionsParser::ABSOLUTENAME - 64))
      | (1ULL << (ExpressionsParser::ROOTNAME - 64)))) != 0)) {
      setState(254);
      expression();
      setState(255);
      match(ExpressionsParser::T__15);
      setState(256);
      expression();
      setState(257);
      match(ExpressionsParser::T__29);
      setState(263);
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
  enterRule(_localctx, 32, ExpressionsParser::RuleSwitchBody);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(271);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(264);
      switchCases();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(265);
      switchCases();
      setState(266);
      match(ExpressionsParser::T__24);
      setState(267);
      expression();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(269);
      match(ExpressionsParser::T__24);
      setState(270);
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
  enterRule(_localctx, 34, ExpressionsParser::RuleSwitchCases);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(278); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(273);
      match(ExpressionsParser::T__30);
      setState(274);
      expression();
      setState(275);
      match(ExpressionsParser::T__15);
      setState(276);
      expression();
      setState(280); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == ExpressionsParser::T__30);
   
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
  enterRule(_localctx, 36, ExpressionsParser::RuleTypes);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(282);
    type();
    setState(287);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ExpressionsParser::T__0) {
      setState(283);
      match(ExpressionsParser::T__0);
      setState(284);
      type();
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
  enterRule(_localctx, 38, ExpressionsParser::RuleType);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(345);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(290);
      match(ExpressionsParser::T__31);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(291);
      match(ExpressionsParser::T__32);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(292);
      match(ExpressionsParser::T__32);
      setState(293);
      match(ExpressionsParser::T__13);
      setState(294);
      expression();
      setState(295);
      match(ExpressionsParser::T__33);
      setState(296);
      expression();
      setState(297);
      match(ExpressionsParser::T__14);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(299);
      match(ExpressionsParser::T__34);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(300);
      match(ExpressionsParser::T__35);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(301);
      match(ExpressionsParser::T__36);
      setState(302);
      type();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(303);
      match(ExpressionsParser::T__36);
      setState(304);
      match(ExpressionsParser::T__13);
      setState(305);
      expression();
      setState(306);
      match(ExpressionsParser::T__14);
      setState(307);
      type();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(309);
      match(ExpressionsParser::T__36);
      setState(310);
      match(ExpressionsParser::T__13);
      setState(311);
      expression();
      setState(312);
      match(ExpressionsParser::T__33);
      setState(313);
      expression();
      setState(314);
      match(ExpressionsParser::T__14);
      setState(315);
      type();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(317);
      match(ExpressionsParser::T__37);
      setState(318);
      type();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(319);
      match(ExpressionsParser::T__38);
      setState(320);
      match(ExpressionsParser::T__11);
      setState(321);
      type();
      setState(322);
      match(ExpressionsParser::T__15);
      setState(323);
      type();
      setState(324);
      match(ExpressionsParser::T__12);
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(326);
      match(ExpressionsParser::T__39);
      setState(327);
      match(ExpressionsParser::T__11);
      setState(328);
      fields();
      setState(329);
      match(ExpressionsParser::T__12);
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(331);
      match(ExpressionsParser::T__40);
      setState(332);
      type();
      setState(333);
      match(ExpressionsParser::T__11);
      setState(334);
      match(ExpressionsParser::T__12);
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(336);
      match(ExpressionsParser::T__40);
      setState(337);
      type();
      setState(338);
      match(ExpressionsParser::T__11);
      setState(339);
      types();
      setState(340);
      match(ExpressionsParser::T__12);
      break;
    }

    case 14: {
      enterOuterAlt(_localctx, 14);
      setState(342);
      match(ExpressionsParser::T__41);
      setState(343);
      type();
      break;
    }

    case 15: {
      enterOuterAlt(_localctx, 15);
      setState(344);
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
  enterRule(_localctx, 40, ExpressionsParser::RuleFields);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(347);
    field();
    setState(352);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ExpressionsParser::T__0) {
      setState(348);
      match(ExpressionsParser::T__0);
      setState(349);
      field();
      setState(354);
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
  enterRule(_localctx, 42, ExpressionsParser::RuleField);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(355);
    type();
    setState(356);
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
  enterRule(_localctx, 44, ExpressionsParser::RuleNameSet);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(358);
    match(ExpressionsParser::T__19);
    setState(359);
    names();
    setState(360);
    match(ExpressionsParser::T__20);
   
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
  enterRule(_localctx, 46, ExpressionsParser::RuleNames);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(362);
    name();
    setState(367);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ExpressionsParser::T__0) {
      setState(363);
      match(ExpressionsParser::T__0);
      setState(364);
      name();
      setState(369);
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
  enterRule(_localctx, 48, ExpressionsParser::RuleName);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(374);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ExpressionsParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(370);
        identifier();
        break;
      }

      case ExpressionsParser::RELATIVENAME: {
        enterOuterAlt(_localctx, 2);
        setState(371);
        match(ExpressionsParser::RELATIVENAME);
        break;
      }

      case ExpressionsParser::ABSOLUTENAME: {
        enterOuterAlt(_localctx, 3);
        setState(372);
        match(ExpressionsParser::ABSOLUTENAME);
        break;
      }

      case ExpressionsParser::ROOTNAME: {
        enterOuterAlt(_localctx, 4);
        setState(373);
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
  enterRule(_localctx, 50, ExpressionsParser::RuleOptSupKind);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(377);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << ExpressionsParser::T__42)
      | (1ULL << ExpressionsParser::T__43)
      | (1ULL << ExpressionsParser::T__44))) != 0)) {
      setState(376);
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
  enterRule(_localctx, 52, ExpressionsParser::RuleSupKind);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(379);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << ExpressionsParser::T__42)
      | (1ULL << ExpressionsParser::T__43)
      | (1ULL << ExpressionsParser::T__44))) != 0))) {
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
  enterRule(_localctx, 54, ExpressionsParser::RuleIdentifier);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(381);
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
  enterRule(_localctx, 56, ExpressionsParser::RuleStringToken);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(383);
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
  enterRule(_localctx, 58, ExpressionsParser::RuleStdLibFunction);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(385);
    _la = _input->LA(1);
    if (!(((((_la - 46) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 46)) & ((1ULL << (ExpressionsParser::T__45 - 46))
      | (1ULL << (ExpressionsParser::T__46 - 46))
      | (1ULL << (ExpressionsParser::T__47 - 46))
      | (1ULL << (ExpressionsParser::T__48 - 46))
      | (1ULL << (ExpressionsParser::T__49 - 46))
      | (1ULL << (ExpressionsParser::T__50 - 46))
      | (1ULL << (ExpressionsParser::T__51 - 46))
      | (1ULL << (ExpressionsParser::T__52 - 46))
      | (1ULL << (ExpressionsParser::T__53 - 46))
      | (1ULL << (ExpressionsParser::T__54 - 46))
      | (1ULL << (ExpressionsParser::T__55 - 46))
      | (1ULL << (ExpressionsParser::T__56 - 46))
      | (1ULL << (ExpressionsParser::T__57 - 46))
      | (1ULL << (ExpressionsParser::T__58 - 46))
      | (1ULL << (ExpressionsParser::T__59 - 46))
      | (1ULL << (ExpressionsParser::T__60 - 46))
      | (1ULL << (ExpressionsParser::T__61 - 46))
      | (1ULL << (ExpressionsParser::T__62 - 46))
      | (1ULL << (ExpressionsParser::T__63 - 46))
      | (1ULL << (ExpressionsParser::T__64 - 46))
      | (1ULL << (ExpressionsParser::T__65 - 46))
      | (1ULL << (ExpressionsParser::T__66 - 46))
      | (1ULL << (ExpressionsParser::T__67 - 46))
      | (1ULL << (ExpressionsParser::T__68 - 46))
      | (1ULL << (ExpressionsParser::T__69 - 46))
      | (1ULL << (ExpressionsParser::T__70 - 46))
      | (1ULL << (ExpressionsParser::T__71 - 46))
      | (1ULL << (ExpressionsParser::T__72 - 46))
      | (1ULL << (ExpressionsParser::T__73 - 46))
      | (1ULL << (ExpressionsParser::T__74 - 46))
      | (1ULL << (ExpressionsParser::T__75 - 46))
      | (1ULL << (ExpressionsParser::T__76 - 46)))) != 0))) {
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
  "expressions", "optExpression", "expression", "equations", "equation", 
  "orExpression", "andExpression", "compareExpression", "addExpression", 
  "mulExpression", "unaryExpression", "funcExpression", "expressionFactor", 
  "nonEmptySetExpression", "dictPairs", "optElifExprs", "switchBody", "switchCases", 
  "types", "type", "fields", "field", "nameSet", "names", "name", "optSupKind", 
  "supKind", "identifier", "stringToken", "stdLibFunction"
};

std::vector<std::string> ExpressionsParser::_literalNames = {
  "", "','", "'=>'", "'<=>'", "'''", "'='", "'or'", "'and'", "'-'", "'+'", 
  "'not'", "'sample'", "'('", "')'", "'['", "']'", "':'", "'true'", "'false'", 
  "'time'", "'{'", "'}'", "'<'", "'>'", "'if'", "'else'", "'end'", "'switch'", 
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
  "", "", "", "", "", "", "MULOP", "ADDOP", "COMPOP", "NUMBER", "REALNUMBER", 
  "STRING", "IDENTIFIER", "RELATIVENAME", "ABSOLUTENAME", "ROOTNAME", "WS"
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
    0x3, 0x5a, 0x186, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
    0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 
    0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 
    0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 
    0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 
    0x12, 0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x4, 0x15, 
    0x9, 0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 0x9, 0x17, 0x4, 0x18, 0x9, 
    0x18, 0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 0x9, 0x1a, 0x4, 0x1b, 0x9, 0x1b, 
    0x4, 0x1c, 0x9, 0x1c, 0x4, 0x1d, 0x9, 0x1d, 0x4, 0x1e, 0x9, 0x1e, 0x4, 
    0x1f, 0x9, 0x1f, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x7, 0x2, 0x42, 0xa, 
    0x2, 0xc, 0x2, 0xe, 0x2, 0x45, 0xb, 0x2, 0x3, 0x3, 0x5, 0x3, 0x48, 0xa, 
    0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 
    0x4, 0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 0x53, 0xa, 0x4, 0x3, 0x5, 0x3, 0x5, 
    0x3, 0x5, 0x7, 0x5, 0x58, 0xa, 0x5, 0xc, 0x5, 0xe, 0x5, 0x5b, 0xb, 0x5, 
    0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 
    0x3, 0x6, 0x3, 0x6, 0x5, 0x6, 0x66, 0xa, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 
    0x7, 0x7, 0x7, 0x6b, 0xa, 0x7, 0xc, 0x7, 0xe, 0x7, 0x6e, 0xb, 0x7, 0x3, 
    0x8, 0x3, 0x8, 0x3, 0x8, 0x7, 0x8, 0x73, 0xa, 0x8, 0xc, 0x8, 0xe, 0x8, 
    0x76, 0xb, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x7, 0x9, 0x7b, 0xa, 0x9, 
    0xc, 0x9, 0xe, 0x9, 0x7e, 0xb, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x7, 
    0xa, 0x83, 0xa, 0xa, 0xc, 0xa, 0xe, 0xa, 0x86, 0xb, 0xa, 0x3, 0xb, 0x3, 
    0xb, 0x3, 0xb, 0x7, 0xb, 0x8b, 0xa, 0xb, 0xc, 0xb, 0xe, 0xb, 0x8e, 0xb, 
    0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 
    0xc, 0x3, 0xc, 0x3, 0xc, 0x5, 0xc, 0x99, 0xa, 0xc, 0x3, 0xd, 0x3, 0xd, 
    0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 
    0x3, 0xd, 0x5, 0xd, 0xa5, 0xa, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 
    0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 
    0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x7, 0xd, 0xb7, 
    0xa, 0xd, 0xc, 0xd, 0xe, 0xd, 0xba, 0xb, 0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 
    0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 
    0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 
    0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 
    0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 
    0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 
    0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 
    0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 
    0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x5, 0xe, 0xf3, 0xa, 0xe, 0x3, 0xf, 
    0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 
    0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x11, 0x3, 0x11, 
    0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x7, 0x11, 0x106, 0xa, 0x11, 0xc, 0x11, 
    0xe, 0x11, 0x109, 0xb, 0x11, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 
    0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x5, 0x12, 0x112, 0xa, 0x12, 0x3, 0x13, 
    0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x6, 0x13, 0x119, 0xa, 0x13, 
    0xd, 0x13, 0xe, 0x13, 0x11a, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x7, 0x14, 
    0x120, 0xa, 0x14, 0xc, 0x14, 0xe, 0x14, 0x123, 0xb, 0x14, 0x3, 0x15, 
    0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 
    0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 
    0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 
    0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 
    0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 
    0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 
    0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 
    0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 
    0x3, 0x15, 0x3, 0x15, 0x5, 0x15, 0x15c, 0xa, 0x15, 0x3, 0x16, 0x3, 0x16, 
    0x3, 0x16, 0x7, 0x16, 0x161, 0xa, 0x16, 0xc, 0x16, 0xe, 0x16, 0x164, 
    0xb, 0x16, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x18, 0x3, 0x18, 0x3, 
    0x18, 0x3, 0x18, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x7, 0x19, 0x170, 
    0xa, 0x19, 0xc, 0x19, 0xe, 0x19, 0x173, 0xb, 0x19, 0x3, 0x1a, 0x3, 0x1a, 
    0x3, 0x1a, 0x3, 0x1a, 0x5, 0x1a, 0x179, 0xa, 0x1a, 0x3, 0x1b, 0x5, 0x1b, 
    0x17c, 0xa, 0x1b, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1e, 
    0x3, 0x1e, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x2, 0x2, 0x20, 0x2, 0x4, 
    0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 
    0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e, 0x30, 0x32, 0x34, 0x36, 
    0x38, 0x3a, 0x3c, 0x2, 0x4, 0x3, 0x2, 0x2d, 0x2f, 0x3, 0x2, 0x30, 0x4f, 
    0x2, 0x1a8, 0x2, 0x3e, 0x3, 0x2, 0x2, 0x2, 0x4, 0x47, 0x3, 0x2, 0x2, 
    0x2, 0x6, 0x52, 0x3, 0x2, 0x2, 0x2, 0x8, 0x54, 0x3, 0x2, 0x2, 0x2, 0xa, 
    0x65, 0x3, 0x2, 0x2, 0x2, 0xc, 0x67, 0x3, 0x2, 0x2, 0x2, 0xe, 0x6f, 
    0x3, 0x2, 0x2, 0x2, 0x10, 0x77, 0x3, 0x2, 0x2, 0x2, 0x12, 0x7f, 0x3, 
    0x2, 0x2, 0x2, 0x14, 0x87, 0x3, 0x2, 0x2, 0x2, 0x16, 0x98, 0x3, 0x2, 
    0x2, 0x2, 0x18, 0xa4, 0x3, 0x2, 0x2, 0x2, 0x1a, 0xf2, 0x3, 0x2, 0x2, 
    0x2, 0x1c, 0xf4, 0x3, 0x2, 0x2, 0x2, 0x1e, 0xf8, 0x3, 0x2, 0x2, 0x2, 
    0x20, 0x107, 0x3, 0x2, 0x2, 0x2, 0x22, 0x111, 0x3, 0x2, 0x2, 0x2, 0x24, 
    0x118, 0x3, 0x2, 0x2, 0x2, 0x26, 0x11c, 0x3, 0x2, 0x2, 0x2, 0x28, 0x15b, 
    0x3, 0x2, 0x2, 0x2, 0x2a, 0x15d, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x165, 0x3, 
    0x2, 0x2, 0x2, 0x2e, 0x168, 0x3, 0x2, 0x2, 0x2, 0x30, 0x16c, 0x3, 0x2, 
    0x2, 0x2, 0x32, 0x178, 0x3, 0x2, 0x2, 0x2, 0x34, 0x17b, 0x3, 0x2, 0x2, 
    0x2, 0x36, 0x17d, 0x3, 0x2, 0x2, 0x2, 0x38, 0x17f, 0x3, 0x2, 0x2, 0x2, 
    0x3a, 0x181, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x183, 0x3, 0x2, 0x2, 0x2, 0x3e, 
    0x43, 0x5, 0x6, 0x4, 0x2, 0x3f, 0x40, 0x7, 0x3, 0x2, 0x2, 0x40, 0x42, 
    0x5, 0x6, 0x4, 0x2, 0x41, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x42, 0x45, 0x3, 
    0x2, 0x2, 0x2, 0x43, 0x41, 0x3, 0x2, 0x2, 0x2, 0x43, 0x44, 0x3, 0x2, 
    0x2, 0x2, 0x44, 0x3, 0x3, 0x2, 0x2, 0x2, 0x45, 0x43, 0x3, 0x2, 0x2, 
    0x2, 0x46, 0x48, 0x5, 0x6, 0x4, 0x2, 0x47, 0x46, 0x3, 0x2, 0x2, 0x2, 
    0x47, 0x48, 0x3, 0x2, 0x2, 0x2, 0x48, 0x5, 0x3, 0x2, 0x2, 0x2, 0x49, 
    0x53, 0x5, 0xc, 0x7, 0x2, 0x4a, 0x4b, 0x5, 0xc, 0x7, 0x2, 0x4b, 0x4c, 
    0x7, 0x4, 0x2, 0x2, 0x4c, 0x4d, 0x5, 0xc, 0x7, 0x2, 0x4d, 0x53, 0x3, 
    0x2, 0x2, 0x2, 0x4e, 0x4f, 0x5, 0xc, 0x7, 0x2, 0x4f, 0x50, 0x7, 0x5, 
    0x2, 0x2, 0x50, 0x51, 0x5, 0xc, 0x7, 0x2, 0x51, 0x53, 0x3, 0x2, 0x2, 
    0x2, 0x52, 0x49, 0x3, 0x2, 0x2, 0x2, 0x52, 0x4a, 0x3, 0x2, 0x2, 0x2, 
    0x52, 0x4e, 0x3, 0x2, 0x2, 0x2, 0x53, 0x7, 0x3, 0x2, 0x2, 0x2, 0x54, 
    0x59, 0x5, 0xa, 0x6, 0x2, 0x55, 0x56, 0x7, 0x3, 0x2, 0x2, 0x56, 0x58, 
    0x5, 0xa, 0x6, 0x2, 0x57, 0x55, 0x3, 0x2, 0x2, 0x2, 0x58, 0x5b, 0x3, 
    0x2, 0x2, 0x2, 0x59, 0x57, 0x3, 0x2, 0x2, 0x2, 0x59, 0x5a, 0x3, 0x2, 
    0x2, 0x2, 0x5a, 0x9, 0x3, 0x2, 0x2, 0x2, 0x5b, 0x59, 0x3, 0x2, 0x2, 
    0x2, 0x5c, 0x5d, 0x5, 0x38, 0x1d, 0x2, 0x5d, 0x5e, 0x7, 0x6, 0x2, 0x2, 
    0x5e, 0x5f, 0x7, 0x7, 0x2, 0x2, 0x5f, 0x60, 0x5, 0x6, 0x4, 0x2, 0x60, 
    0x66, 0x3, 0x2, 0x2, 0x2, 0x61, 0x62, 0x5, 0x38, 0x1d, 0x2, 0x62, 0x63, 
    0x7, 0x7, 0x2, 0x2, 0x63, 0x64, 0x5, 0x6, 0x4, 0x2, 0x64, 0x66, 0x3, 
    0x2, 0x2, 0x2, 0x65, 0x5c, 0x3, 0x2, 0x2, 0x2, 0x65, 0x61, 0x3, 0x2, 
    0x2, 0x2, 0x66, 0xb, 0x3, 0x2, 0x2, 0x2, 0x67, 0x6c, 0x5, 0xe, 0x8, 
    0x2, 0x68, 0x69, 0x7, 0x8, 0x2, 0x2, 0x69, 0x6b, 0x5, 0xe, 0x8, 0x2, 
    0x6a, 0x68, 0x3, 0x2, 0x2, 0x2, 0x6b, 0x6e, 0x3, 0x2, 0x2, 0x2, 0x6c, 
    0x6a, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x6d, 0x3, 0x2, 0x2, 0x2, 0x6d, 0xd, 
    0x3, 0x2, 0x2, 0x2, 0x6e, 0x6c, 0x3, 0x2, 0x2, 0x2, 0x6f, 0x74, 0x5, 
    0x10, 0x9, 0x2, 0x70, 0x71, 0x7, 0x9, 0x2, 0x2, 0x71, 0x73, 0x5, 0x10, 
    0x9, 0x2, 0x72, 0x70, 0x3, 0x2, 0x2, 0x2, 0x73, 0x76, 0x3, 0x2, 0x2, 
    0x2, 0x74, 0x72, 0x3, 0x2, 0x2, 0x2, 0x74, 0x75, 0x3, 0x2, 0x2, 0x2, 
    0x75, 0xf, 0x3, 0x2, 0x2, 0x2, 0x76, 0x74, 0x3, 0x2, 0x2, 0x2, 0x77, 
    0x7c, 0x5, 0x12, 0xa, 0x2, 0x78, 0x79, 0x7, 0x52, 0x2, 0x2, 0x79, 0x7b, 
    0x5, 0x12, 0xa, 0x2, 0x7a, 0x78, 0x3, 0x2, 0x2, 0x2, 0x7b, 0x7e, 0x3, 
    0x2, 0x2, 0x2, 0x7c, 0x7a, 0x3, 0x2, 0x2, 0x2, 0x7c, 0x7d, 0x3, 0x2, 
    0x2, 0x2, 0x7d, 0x11, 0x3, 0x2, 0x2, 0x2, 0x7e, 0x7c, 0x3, 0x2, 0x2, 
    0x2, 0x7f, 0x84, 0x5, 0x14, 0xb, 0x2, 0x80, 0x81, 0x7, 0x51, 0x2, 0x2, 
    0x81, 0x83, 0x5, 0x14, 0xb, 0x2, 0x82, 0x80, 0x3, 0x2, 0x2, 0x2, 0x83, 
    0x86, 0x3, 0x2, 0x2, 0x2, 0x84, 0x82, 0x3, 0x2, 0x2, 0x2, 0x84, 0x85, 
    0x3, 0x2, 0x2, 0x2, 0x85, 0x13, 0x3, 0x2, 0x2, 0x2, 0x86, 0x84, 0x3, 
    0x2, 0x2, 0x2, 0x87, 0x8c, 0x5, 0x16, 0xc, 0x2, 0x88, 0x89, 0x7, 0x50, 
    0x2, 0x2, 0x89, 0x8b, 0x5, 0x16, 0xc, 0x2, 0x8a, 0x88, 0x3, 0x2, 0x2, 
    0x2, 0x8b, 0x8e, 0x3, 0x2, 0x2, 0x2, 0x8c, 0x8a, 0x3, 0x2, 0x2, 0x2, 
    0x8c, 0x8d, 0x3, 0x2, 0x2, 0x2, 0x8d, 0x15, 0x3, 0x2, 0x2, 0x2, 0x8e, 
    0x8c, 0x3, 0x2, 0x2, 0x2, 0x8f, 0x99, 0x5, 0x18, 0xd, 0x2, 0x90, 0x91, 
    0x7, 0xa, 0x2, 0x2, 0x91, 0x99, 0x5, 0x16, 0xc, 0x2, 0x92, 0x93, 0x7, 
    0xb, 0x2, 0x2, 0x93, 0x99, 0x5, 0x16, 0xc, 0x2, 0x94, 0x95, 0x7, 0xc, 
    0x2, 0x2, 0x95, 0x99, 0x5, 0x16, 0xc, 0x2, 0x96, 0x97, 0x7, 0xd, 0x2, 
    0x2, 0x97, 0x99, 0x5, 0x16, 0xc, 0x2, 0x98, 0x8f, 0x3, 0x2, 0x2, 0x2, 
    0x98, 0x90, 0x3, 0x2, 0x2, 0x2, 0x98, 0x92, 0x3, 0x2, 0x2, 0x2, 0x98, 
    0x94, 0x3, 0x2, 0x2, 0x2, 0x98, 0x96, 0x3, 0x2, 0x2, 0x2, 0x99, 0x17, 
    0x3, 0x2, 0x2, 0x2, 0x9a, 0xa5, 0x5, 0x1a, 0xe, 0x2, 0x9b, 0x9c, 0x5, 
    0x3c, 0x1f, 0x2, 0x9c, 0x9d, 0x7, 0xe, 0x2, 0x2, 0x9d, 0x9e, 0x7, 0xf, 
    0x2, 0x2, 0x9e, 0xa5, 0x3, 0x2, 0x2, 0x2, 0x9f, 0xa0, 0x5, 0x3c, 0x1f, 
    0x2, 0xa0, 0xa1, 0x7, 0xe, 0x2, 0x2, 0xa1, 0xa2, 0x5, 0x2, 0x2, 0x2, 
    0xa2, 0xa3, 0x7, 0xf, 0x2, 0x2, 0xa3, 0xa5, 0x3, 0x2, 0x2, 0x2, 0xa4, 
    0x9a, 0x3, 0x2, 0x2, 0x2, 0xa4, 0x9b, 0x3, 0x2, 0x2, 0x2, 0xa4, 0x9f, 
    0x3, 0x2, 0x2, 0x2, 0xa5, 0xb8, 0x3, 0x2, 0x2, 0x2, 0xa6, 0xa7, 0x7, 
    0x10, 0x2, 0x2, 0xa7, 0xa8, 0x5, 0x2, 0x2, 0x2, 0xa8, 0xa9, 0x7, 0x11, 
    0x2, 0x2, 0xa9, 0xb7, 0x3, 0x2, 0x2, 0x2, 0xaa, 0xab, 0x7, 0x10, 0x2, 
    0x2, 0xab, 0xac, 0x5, 0x4, 0x3, 0x2, 0xac, 0xad, 0x7, 0x12, 0x2, 0x2, 
    0xad, 0xae, 0x5, 0x4, 0x3, 0x2, 0xae, 0xaf, 0x7, 0x11, 0x2, 0x2, 0xaf, 
    0xb7, 0x3, 0x2, 0x2, 0x2, 0xb0, 0xb1, 0x7, 0xe, 0x2, 0x2, 0xb1, 0xb7, 
    0x7, 0xf, 0x2, 0x2, 0xb2, 0xb3, 0x7, 0xe, 0x2, 0x2, 0xb3, 0xb4, 0x5, 
    0x2, 0x2, 0x2, 0xb4, 0xb5, 0x7, 0xf, 0x2, 0x2, 0xb5, 0xb7, 0x3, 0x2, 
    0x2, 0x2, 0xb6, 0xa6, 0x3, 0x2, 0x2, 0x2, 0xb6, 0xaa, 0x3, 0x2, 0x2, 
    0x2, 0xb6, 0xb0, 0x3, 0x2, 0x2, 0x2, 0xb6, 0xb2, 0x3, 0x2, 0x2, 0x2, 
    0xb7, 0xba, 0x3, 0x2, 0x2, 0x2, 0xb8, 0xb6, 0x3, 0x2, 0x2, 0x2, 0xb8, 
    0xb9, 0x3, 0x2, 0x2, 0x2, 0xb9, 0x19, 0x3, 0x2, 0x2, 0x2, 0xba, 0xb8, 
    0x3, 0x2, 0x2, 0x2, 0xbb, 0xf3, 0x7, 0x13, 0x2, 0x2, 0xbc, 0xf3, 0x7, 
    0x14, 0x2, 0x2, 0xbd, 0xf3, 0x7, 0x53, 0x2, 0x2, 0xbe, 0xf3, 0x7, 0x54, 
    0x2, 0x2, 0xbf, 0xf3, 0x5, 0x32, 0x1a, 0x2, 0xc0, 0xf3, 0x5, 0x3a, 0x1e, 
    0x2, 0xc1, 0xf3, 0x7, 0x15, 0x2, 0x2, 0xc2, 0xc3, 0x7, 0x10, 0x2, 0x2, 
    0xc3, 0xf3, 0x7, 0x11, 0x2, 0x2, 0xc4, 0xc5, 0x7, 0x10, 0x2, 0x2, 0xc5, 
    0xc6, 0x5, 0x2, 0x2, 0x2, 0xc6, 0xc7, 0x7, 0x11, 0x2, 0x2, 0xc7, 0xf3, 
    0x3, 0x2, 0x2, 0x2, 0xc8, 0xc9, 0x7, 0x16, 0x2, 0x2, 0xc9, 0xf3, 0x7, 
    0x17, 0x2, 0x2, 0xca, 0xf3, 0x5, 0x1c, 0xf, 0x2, 0xcb, 0xcc, 0x7, 0x16, 
    0x2, 0x2, 0xcc, 0xcd, 0x5, 0x1e, 0x10, 0x2, 0xcd, 0xce, 0x7, 0x17, 0x2, 
    0x2, 0xce, 0xf3, 0x3, 0x2, 0x2, 0x2, 0xcf, 0xd0, 0x7, 0xe, 0x2, 0x2, 
    0xd0, 0xd1, 0x5, 0x6, 0x4, 0x2, 0xd1, 0xd2, 0x7, 0x3, 0x2, 0x2, 0xd2, 
    0xd3, 0x5, 0x6, 0x4, 0x2, 0xd3, 0xd4, 0x7, 0xf, 0x2, 0x2, 0xd4, 0xf3, 
    0x3, 0x2, 0x2, 0x2, 0xd5, 0xd6, 0x7, 0x18, 0x2, 0x2, 0xd6, 0xd7, 0x5, 
    0x28, 0x15, 0x2, 0xd7, 0xd8, 0x7, 0x19, 0x2, 0x2, 0xd8, 0xd9, 0x5, 0x1a, 
    0xe, 0x2, 0xd9, 0xf3, 0x3, 0x2, 0x2, 0x2, 0xda, 0xdb, 0x7, 0x1a, 0x2, 
    0x2, 0xdb, 0xdc, 0x5, 0x2, 0x2, 0x2, 0xdc, 0xdd, 0x7, 0x12, 0x2, 0x2, 
    0xdd, 0xde, 0x5, 0x6, 0x4, 0x2, 0xde, 0xdf, 0x5, 0x20, 0x11, 0x2, 0xdf, 
    0xe0, 0x7, 0x1b, 0x2, 0x2, 0xe0, 0xe1, 0x5, 0x6, 0x4, 0x2, 0xe1, 0xe2, 
    0x7, 0x1c, 0x2, 0x2, 0xe2, 0xf3, 0x3, 0x2, 0x2, 0x2, 0xe3, 0xe4, 0x7, 
    0x1d, 0x2, 0x2, 0xe4, 0xe5, 0x5, 0x6, 0x4, 0x2, 0xe5, 0xe6, 0x7, 0x12, 
    0x2, 0x2, 0xe6, 0xe7, 0x5, 0x22, 0x12, 0x2, 0xe7, 0xe8, 0x7, 0x1c, 0x2, 
    0x2, 0xe8, 0xf3, 0x3, 0x2, 0x2, 0x2, 0xe9, 0xea, 0x7, 0xe, 0x2, 0x2, 
    0xea, 0xeb, 0x5, 0x6, 0x4, 0x2, 0xeb, 0xec, 0x7, 0xf, 0x2, 0x2, 0xec, 
    0xf3, 0x3, 0x2, 0x2, 0x2, 0xed, 0xee, 0x5, 0x32, 0x1a, 0x2, 0xee, 0xef, 
    0x7, 0x6, 0x2, 0x2, 0xef, 0xf3, 0x3, 0x2, 0x2, 0x2, 0xf0, 0xf3, 0x7, 
    0x1e, 0x2, 0x2, 0xf1, 0xf3, 0x7, 0x1f, 0x2, 0x2, 0xf2, 0xbb, 0x3, 0x2, 
    0x2, 0x2, 0xf2, 0xbc, 0x3, 0x2, 0x2, 0x2, 0xf2, 0xbd, 0x3, 0x2, 0x2, 
    0x2, 0xf2, 0xbe, 0x3, 0x2, 0x2, 0x2, 0xf2, 0xbf, 0x3, 0x2, 0x2, 0x2, 
    0xf2, 0xc0, 0x3, 0x2, 0x2, 0x2, 0xf2, 0xc1, 0x3, 0x2, 0x2, 0x2, 0xf2, 
    0xc2, 0x3, 0x2, 0x2, 0x2, 0xf2, 0xc4, 0x3, 0x2, 0x2, 0x2, 0xf2, 0xc8, 
    0x3, 0x2, 0x2, 0x2, 0xf2, 0xca, 0x3, 0x2, 0x2, 0x2, 0xf2, 0xcb, 0x3, 
    0x2, 0x2, 0x2, 0xf2, 0xcf, 0x3, 0x2, 0x2, 0x2, 0xf2, 0xd5, 0x3, 0x2, 
    0x2, 0x2, 0xf2, 0xda, 0x3, 0x2, 0x2, 0x2, 0xf2, 0xe3, 0x3, 0x2, 0x2, 
    0x2, 0xf2, 0xe9, 0x3, 0x2, 0x2, 0x2, 0xf2, 0xed, 0x3, 0x2, 0x2, 0x2, 
    0xf2, 0xf0, 0x3, 0x2, 0x2, 0x2, 0xf2, 0xf1, 0x3, 0x2, 0x2, 0x2, 0xf3, 
    0x1b, 0x3, 0x2, 0x2, 0x2, 0xf4, 0xf5, 0x7, 0x16, 0x2, 0x2, 0xf5, 0xf6, 
    0x5, 0x2, 0x2, 0x2, 0xf6, 0xf7, 0x7, 0x17, 0x2, 0x2, 0xf7, 0x1d, 0x3, 
    0x2, 0x2, 0x2, 0xf8, 0xf9, 0x5, 0x6, 0x4, 0x2, 0xf9, 0xfa, 0x7, 0x12, 
    0x2, 0x2, 0xfa, 0xfb, 0x5, 0x6, 0x4, 0x2, 0xfb, 0xfc, 0x7, 0x3, 0x2, 
    0x2, 0xfc, 0xfd, 0x5, 0x6, 0x4, 0x2, 0xfd, 0xfe, 0x7, 0x12, 0x2, 0x2, 
    0xfe, 0xff, 0x5, 0x6, 0x4, 0x2, 0xff, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x100, 
    0x101, 0x5, 0x6, 0x4, 0x2, 0x101, 0x102, 0x7, 0x12, 0x2, 0x2, 0x102, 
    0x103, 0x5, 0x6, 0x4, 0x2, 0x103, 0x104, 0x7, 0x20, 0x2, 0x2, 0x104, 
    0x106, 0x3, 0x2, 0x2, 0x2, 0x105, 0x100, 0x3, 0x2, 0x2, 0x2, 0x106, 
    0x109, 0x3, 0x2, 0x2, 0x2, 0x107, 0x105, 0x3, 0x2, 0x2, 0x2, 0x107, 
    0x108, 0x3, 0x2, 0x2, 0x2, 0x108, 0x21, 0x3, 0x2, 0x2, 0x2, 0x109, 0x107, 
    0x3, 0x2, 0x2, 0x2, 0x10a, 0x112, 0x5, 0x24, 0x13, 0x2, 0x10b, 0x10c, 
    0x5, 0x24, 0x13, 0x2, 0x10c, 0x10d, 0x7, 0x1b, 0x2, 0x2, 0x10d, 0x10e, 
    0x5, 0x6, 0x4, 0x2, 0x10e, 0x112, 0x3, 0x2, 0x2, 0x2, 0x10f, 0x110, 
    0x7, 0x1b, 0x2, 0x2, 0x110, 0x112, 0x5, 0x6, 0x4, 0x2, 0x111, 0x10a, 
    0x3, 0x2, 0x2, 0x2, 0x111, 0x10b, 0x3, 0x2, 0x2, 0x2, 0x111, 0x10f, 
    0x3, 0x2, 0x2, 0x2, 0x112, 0x23, 0x3, 0x2, 0x2, 0x2, 0x113, 0x114, 0x7, 
    0x21, 0x2, 0x2, 0x114, 0x115, 0x5, 0x6, 0x4, 0x2, 0x115, 0x116, 0x7, 
    0x12, 0x2, 0x2, 0x116, 0x117, 0x5, 0x6, 0x4, 0x2, 0x117, 0x119, 0x3, 
    0x2, 0x2, 0x2, 0x118, 0x113, 0x3, 0x2, 0x2, 0x2, 0x119, 0x11a, 0x3, 
    0x2, 0x2, 0x2, 0x11a, 0x118, 0x3, 0x2, 0x2, 0x2, 0x11a, 0x11b, 0x3, 
    0x2, 0x2, 0x2, 0x11b, 0x25, 0x3, 0x2, 0x2, 0x2, 0x11c, 0x121, 0x5, 0x28, 
    0x15, 0x2, 0x11d, 0x11e, 0x7, 0x3, 0x2, 0x2, 0x11e, 0x120, 0x5, 0x28, 
    0x15, 0x2, 0x11f, 0x11d, 0x3, 0x2, 0x2, 0x2, 0x120, 0x123, 0x3, 0x2, 
    0x2, 0x2, 0x121, 0x11f, 0x3, 0x2, 0x2, 0x2, 0x121, 0x122, 0x3, 0x2, 
    0x2, 0x2, 0x122, 0x27, 0x3, 0x2, 0x2, 0x2, 0x123, 0x121, 0x3, 0x2, 0x2, 
    0x2, 0x124, 0x15c, 0x7, 0x22, 0x2, 0x2, 0x125, 0x15c, 0x7, 0x23, 0x2, 
    0x2, 0x126, 0x127, 0x7, 0x23, 0x2, 0x2, 0x127, 0x128, 0x7, 0x10, 0x2, 
    0x2, 0x128, 0x129, 0x5, 0x6, 0x4, 0x2, 0x129, 0x12a, 0x7, 0x24, 0x2, 
    0x2, 0x12a, 0x12b, 0x5, 0x6, 0x4, 0x2, 0x12b, 0x12c, 0x7, 0x11, 0x2, 
    0x2, 0x12c, 0x15c, 0x3, 0x2, 0x2, 0x2, 0x12d, 0x15c, 0x7, 0x25, 0x2, 
    0x2, 0x12e, 0x15c, 0x7, 0x26, 0x2, 0x2, 0x12f, 0x130, 0x7, 0x27, 0x2, 
    0x2, 0x130, 0x15c, 0x5, 0x28, 0x15, 0x2, 0x131, 0x132, 0x7, 0x27, 0x2, 
    0x2, 0x132, 0x133, 0x7, 0x10, 0x2, 0x2, 0x133, 0x134, 0x5, 0x6, 0x4, 
    0x2, 0x134, 0x135, 0x7, 0x11, 0x2, 0x2, 0x135, 0x136, 0x5, 0x28, 0x15, 
    0x2, 0x136, 0x15c, 0x3, 0x2, 0x2, 0x2, 0x137, 0x138, 0x7, 0x27, 0x2, 
    0x2, 0x138, 0x139, 0x7, 0x10, 0x2, 0x2, 0x139, 0x13a, 0x5, 0x6, 0x4, 
    0x2, 0x13a, 0x13b, 0x7, 0x24, 0x2, 0x2, 0x13b, 0x13c, 0x5, 0x6, 0x4, 
    0x2, 0x13c, 0x13d, 0x7, 0x11, 0x2, 0x2, 0x13d, 0x13e, 0x5, 0x28, 0x15, 
    0x2, 0x13e, 0x15c, 0x3, 0x2, 0x2, 0x2, 0x13f, 0x140, 0x7, 0x28, 0x2, 
    0x2, 0x140, 0x15c, 0x5, 0x28, 0x15, 0x2, 0x141, 0x142, 0x7, 0x29, 0x2, 
    0x2, 0x142, 0x143, 0x7, 0xe, 0x2, 0x2, 0x143, 0x144, 0x5, 0x28, 0x15, 
    0x2, 0x144, 0x145, 0x7, 0x12, 0x2, 0x2, 0x145, 0x146, 0x5, 0x28, 0x15, 
    0x2, 0x146, 0x147, 0x7, 0xf, 0x2, 0x2, 0x147, 0x15c, 0x3, 0x2, 0x2, 
    0x2, 0x148, 0x149, 0x7, 0x2a, 0x2, 0x2, 0x149, 0x14a, 0x7, 0xe, 0x2, 
    0x2, 0x14a, 0x14b, 0x5, 0x2a, 0x16, 0x2, 0x14b, 0x14c, 0x7, 0xf, 0x2, 
    0x2, 0x14c, 0x15c, 0x3, 0x2, 0x2, 0x2, 0x14d, 0x14e, 0x7, 0x2b, 0x2, 
    0x2, 0x14e, 0x14f, 0x5, 0x28, 0x15, 0x2, 0x14f, 0x150, 0x7, 0xe, 0x2, 
    0x2, 0x150, 0x151, 0x7, 0xf, 0x2, 0x2, 0x151, 0x15c, 0x3, 0x2, 0x2, 
    0x2, 0x152, 0x153, 0x7, 0x2b, 0x2, 0x2, 0x153, 0x154, 0x5, 0x28, 0x15, 
    0x2, 0x154, 0x155, 0x7, 0xe, 0x2, 0x2, 0x155, 0x156, 0x5, 0x26, 0x14, 
    0x2, 0x156, 0x157, 0x7, 0xf, 0x2, 0x2, 0x157, 0x15c, 0x3, 0x2, 0x2, 
    0x2, 0x158, 0x159, 0x7, 0x2c, 0x2, 0x2, 0x159, 0x15c, 0x5, 0x28, 0x15, 
    0x2, 0x15a, 0x15c, 0x5, 0x32, 0x1a, 0x2, 0x15b, 0x124, 0x3, 0x2, 0x2, 
    0x2, 0x15b, 0x125, 0x3, 0x2, 0x2, 0x2, 0x15b, 0x126, 0x3, 0x2, 0x2, 
    0x2, 0x15b, 0x12d, 0x3, 0x2, 0x2, 0x2, 0x15b, 0x12e, 0x3, 0x2, 0x2, 
    0x2, 0x15b, 0x12f, 0x3, 0x2, 0x2, 0x2, 0x15b, 0x131, 0x3, 0x2, 0x2, 
    0x2, 0x15b, 0x137, 0x3, 0x2, 0x2, 0x2, 0x15b, 0x13f, 0x3, 0x2, 0x2, 
    0x2, 0x15b, 0x141, 0x3, 0x2, 0x2, 0x2, 0x15b, 0x148, 0x3, 0x2, 0x2, 
    0x2, 0x15b, 0x14d, 0x3, 0x2, 0x2, 0x2, 0x15b, 0x152, 0x3, 0x2, 0x2, 
    0x2, 0x15b, 0x158, 0x3, 0x2, 0x2, 0x2, 0x15b, 0x15a, 0x3, 0x2, 0x2, 
    0x2, 0x15c, 0x29, 0x3, 0x2, 0x2, 0x2, 0x15d, 0x162, 0x5, 0x2c, 0x17, 
    0x2, 0x15e, 0x15f, 0x7, 0x3, 0x2, 0x2, 0x15f, 0x161, 0x5, 0x2c, 0x17, 
    0x2, 0x160, 0x15e, 0x3, 0x2, 0x2, 0x2, 0x161, 0x164, 0x3, 0x2, 0x2, 
    0x2, 0x162, 0x160, 0x3, 0x2, 0x2, 0x2, 0x162, 0x163, 0x3, 0x2, 0x2, 
    0x2, 0x163, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x164, 0x162, 0x3, 0x2, 0x2, 0x2, 
    0x165, 0x166, 0x5, 0x28, 0x15, 0x2, 0x166, 0x167, 0x5, 0x38, 0x1d, 0x2, 
    0x167, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x168, 0x169, 0x7, 0x16, 0x2, 0x2, 
    0x169, 0x16a, 0x5, 0x30, 0x19, 0x2, 0x16a, 0x16b, 0x7, 0x17, 0x2, 0x2, 
    0x16b, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x16c, 0x171, 0x5, 0x32, 0x1a, 0x2, 
    0x16d, 0x16e, 0x7, 0x3, 0x2, 0x2, 0x16e, 0x170, 0x5, 0x32, 0x1a, 0x2, 
    0x16f, 0x16d, 0x3, 0x2, 0x2, 0x2, 0x170, 0x173, 0x3, 0x2, 0x2, 0x2, 
    0x171, 0x16f, 0x3, 0x2, 0x2, 0x2, 0x171, 0x172, 0x3, 0x2, 0x2, 0x2, 
    0x172, 0x31, 0x3, 0x2, 0x2, 0x2, 0x173, 0x171, 0x3, 0x2, 0x2, 0x2, 0x174, 
    0x179, 0x5, 0x38, 0x1d, 0x2, 0x175, 0x179, 0x7, 0x57, 0x2, 0x2, 0x176, 
    0x179, 0x7, 0x58, 0x2, 0x2, 0x177, 0x179, 0x7, 0x59, 0x2, 0x2, 0x178, 
    0x174, 0x3, 0x2, 0x2, 0x2, 0x178, 0x175, 0x3, 0x2, 0x2, 0x2, 0x178, 
    0x176, 0x3, 0x2, 0x2, 0x2, 0x178, 0x177, 0x3, 0x2, 0x2, 0x2, 0x179, 
    0x33, 0x3, 0x2, 0x2, 0x2, 0x17a, 0x17c, 0x5, 0x36, 0x1c, 0x2, 0x17b, 
    0x17a, 0x3, 0x2, 0x2, 0x2, 0x17b, 0x17c, 0x3, 0x2, 0x2, 0x2, 0x17c, 
    0x35, 0x3, 0x2, 0x2, 0x2, 0x17d, 0x17e, 0x9, 0x2, 0x2, 0x2, 0x17e, 0x37, 
    0x3, 0x2, 0x2, 0x2, 0x17f, 0x180, 0x7, 0x56, 0x2, 0x2, 0x180, 0x39, 
    0x3, 0x2, 0x2, 0x2, 0x181, 0x182, 0x7, 0x55, 0x2, 0x2, 0x182, 0x3b, 
    0x3, 0x2, 0x2, 0x2, 0x183, 0x184, 0x9, 0x3, 0x2, 0x2, 0x184, 0x3d, 0x3, 
    0x2, 0x2, 0x2, 0x1a, 0x43, 0x47, 0x52, 0x59, 0x65, 0x6c, 0x74, 0x7c, 
    0x84, 0x8c, 0x98, 0xa4, 0xb6, 0xb8, 0xf2, 0x107, 0x111, 0x11a, 0x121, 
    0x15b, 0x162, 0x171, 0x178, 0x17b, 
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
