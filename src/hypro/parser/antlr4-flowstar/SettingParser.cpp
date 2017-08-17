
// Generated from Setting.g4 by ANTLR 4.7



#include "SettingParser.h"


using namespace antlrcpp;
using namespace antlr4;

SettingParser::SettingParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

SettingParser::~SettingParser() {
  delete _interpreter;
}

std::string SettingParser::getGrammarFileName() const {
  return "Setting.g4";
}

const std::vector<std::string>& SettingParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& SettingParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- SettingContext ------------------------------------------------------------------

SettingParser::SettingContext::SettingContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SettingParser::FixedstepsContext* SettingParser::SettingContext::fixedsteps() {
  return getRuleContext<SettingParser::FixedstepsContext>(0);
}

SettingParser::TimeContext* SettingParser::SettingContext::time() {
  return getRuleContext<SettingParser::TimeContext>(0);
}

SettingParser::RemainderContext* SettingParser::SettingContext::remainder() {
  return getRuleContext<SettingParser::RemainderContext>(0);
}

SettingParser::IdentityContext* SettingParser::SettingContext::identity() {
  return getRuleContext<SettingParser::IdentityContext>(0);
}

SettingParser::PlotsettingContext* SettingParser::SettingContext::plotsetting() {
  return getRuleContext<SettingParser::PlotsettingContext>(0);
}

SettingParser::FixedordersContext* SettingParser::SettingContext::fixedorders() {
  return getRuleContext<SettingParser::FixedordersContext>(0);
}

SettingParser::CutoffContext* SettingParser::SettingContext::cutoff() {
  return getRuleContext<SettingParser::CutoffContext>(0);
}

SettingParser::PrecisionContext* SettingParser::SettingContext::precision() {
  return getRuleContext<SettingParser::PrecisionContext>(0);
}

SettingParser::FilenameContext* SettingParser::SettingContext::filename() {
  return getRuleContext<SettingParser::FilenameContext>(0);
}

SettingParser::MaxjumpsContext* SettingParser::SettingContext::maxjumps() {
  return getRuleContext<SettingParser::MaxjumpsContext>(0);
}

SettingParser::PrintContext* SettingParser::SettingContext::print() {
  return getRuleContext<SettingParser::PrintContext>(0);
}


size_t SettingParser::SettingContext::getRuleIndex() const {
  return SettingParser::RuleSetting;
}


SettingParser::SettingContext* SettingParser::setting() {
  SettingContext *_localctx = _tracker.createInstance<SettingContext>(_ctx, getState());
  enterRule(_localctx, 0, SettingParser::RuleSetting);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(38);
    match(SettingParser::T__0);
    setState(39);
    match(SettingParser::T__1);
    setState(40);
    fixedsteps();
    setState(41);
    time();
    setState(42);
    remainder();
    setState(43);
    identity();
    setState(44);
    plotsetting();
    setState(45);
    fixedorders();
    setState(46);
    cutoff();
    setState(47);
    precision();
    setState(48);
    filename();
    setState(49);
    maxjumps();
    setState(50);
    print();
    setState(51);
    match(SettingParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FixedstepsContext ------------------------------------------------------------------

SettingParser::FixedstepsContext::FixedstepsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SettingParser::FixedstepsContext::NUMBER() {
  return getToken(SettingParser::NUMBER, 0);
}


size_t SettingParser::FixedstepsContext::getRuleIndex() const {
  return SettingParser::RuleFixedsteps;
}


SettingParser::FixedstepsContext* SettingParser::fixedsteps() {
  FixedstepsContext *_localctx = _tracker.createInstance<FixedstepsContext>(_ctx, getState());
  enterRule(_localctx, 2, SettingParser::RuleFixedsteps);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(53);
    match(SettingParser::T__3);
    setState(54);
    match(SettingParser::NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TimeContext ------------------------------------------------------------------

SettingParser::TimeContext::TimeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SettingParser::TimeContext::NUMBER() {
  return getToken(SettingParser::NUMBER, 0);
}


size_t SettingParser::TimeContext::getRuleIndex() const {
  return SettingParser::RuleTime;
}


SettingParser::TimeContext* SettingParser::time() {
  TimeContext *_localctx = _tracker.createInstance<TimeContext>(_ctx, getState());
  enterRule(_localctx, 4, SettingParser::RuleTime);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(56);
    match(SettingParser::T__4);
    setState(57);
    match(SettingParser::NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PlotsettingContext ------------------------------------------------------------------

SettingParser::PlotsettingContext::PlotsettingContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> SettingParser::PlotsettingContext::VARIABLE() {
  return getTokens(SettingParser::VARIABLE);
}

tree::TerminalNode* SettingParser::PlotsettingContext::VARIABLE(size_t i) {
  return getToken(SettingParser::VARIABLE, i);
}


size_t SettingParser::PlotsettingContext::getRuleIndex() const {
  return SettingParser::RulePlotsetting;
}


SettingParser::PlotsettingContext* SettingParser::plotsetting() {
  PlotsettingContext *_localctx = _tracker.createInstance<PlotsettingContext>(_ctx, getState());
  enterRule(_localctx, 6, SettingParser::RulePlotsetting);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(59);
    match(SettingParser::T__5);
    setState(60);
    match(SettingParser::VARIABLE);
    setState(67);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SettingParser::T__6) {
      setState(63); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(61);
        match(SettingParser::T__6);
        setState(62);
        match(SettingParser::VARIABLE);
        setState(65); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == SettingParser::T__6);
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

SettingParser::FilenameContext::FilenameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SettingParser::FilenameContext::VARIABLE() {
  return getToken(SettingParser::VARIABLE, 0);
}


size_t SettingParser::FilenameContext::getRuleIndex() const {
  return SettingParser::RuleFilename;
}


SettingParser::FilenameContext* SettingParser::filename() {
  FilenameContext *_localctx = _tracker.createInstance<FilenameContext>(_ctx, getState());
  enterRule(_localctx, 8, SettingParser::RuleFilename);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(69);
    match(SettingParser::T__7);
    setState(70);
    match(SettingParser::VARIABLE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MaxjumpsContext ------------------------------------------------------------------

SettingParser::MaxjumpsContext::MaxjumpsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SettingParser::MaxjumpsContext::NUMBER() {
  return getToken(SettingParser::NUMBER, 0);
}


size_t SettingParser::MaxjumpsContext::getRuleIndex() const {
  return SettingParser::RuleMaxjumps;
}


SettingParser::MaxjumpsContext* SettingParser::maxjumps() {
  MaxjumpsContext *_localctx = _tracker.createInstance<MaxjumpsContext>(_ctx, getState());
  enterRule(_localctx, 10, SettingParser::RuleMaxjumps);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(72);
    match(SettingParser::T__8);
    setState(73);
    match(SettingParser::NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrintContext ------------------------------------------------------------------

SettingParser::PrintContext::PrintContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SettingParser::PrintContext::VARIABLE() {
  return getToken(SettingParser::VARIABLE, 0);
}


size_t SettingParser::PrintContext::getRuleIndex() const {
  return SettingParser::RulePrint;
}


SettingParser::PrintContext* SettingParser::print() {
  PrintContext *_localctx = _tracker.createInstance<PrintContext>(_ctx, getState());
  enterRule(_localctx, 12, SettingParser::RulePrint);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(75);
    match(SettingParser::T__9);
    setState(76);
    match(SettingParser::VARIABLE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RemainderContext ------------------------------------------------------------------

SettingParser::RemainderContext::RemainderContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SettingParser::RemainderContext::EXPONENTIAL() {
  return getToken(SettingParser::EXPONENTIAL, 0);
}


size_t SettingParser::RemainderContext::getRuleIndex() const {
  return SettingParser::RuleRemainder;
}


SettingParser::RemainderContext* SettingParser::remainder() {
  RemainderContext *_localctx = _tracker.createInstance<RemainderContext>(_ctx, getState());
  enterRule(_localctx, 14, SettingParser::RuleRemainder);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(78);
    match(SettingParser::T__10);
    setState(79);
    match(SettingParser::EXPONENTIAL);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdentityContext ------------------------------------------------------------------

SettingParser::IdentityContext::IdentityContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SettingParser::IdentityContext::getRuleIndex() const {
  return SettingParser::RuleIdentity;
}


SettingParser::IdentityContext* SettingParser::identity() {
  IdentityContext *_localctx = _tracker.createInstance<IdentityContext>(_ctx, getState());
  enterRule(_localctx, 16, SettingParser::RuleIdentity);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(81);
    match(SettingParser::T__11);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FixedordersContext ------------------------------------------------------------------

SettingParser::FixedordersContext::FixedordersContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SettingParser::FixedordersContext::NUMBER() {
  return getToken(SettingParser::NUMBER, 0);
}


size_t SettingParser::FixedordersContext::getRuleIndex() const {
  return SettingParser::RuleFixedorders;
}


SettingParser::FixedordersContext* SettingParser::fixedorders() {
  FixedordersContext *_localctx = _tracker.createInstance<FixedordersContext>(_ctx, getState());
  enterRule(_localctx, 18, SettingParser::RuleFixedorders);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(83);
    match(SettingParser::T__12);
    setState(84);
    match(SettingParser::NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CutoffContext ------------------------------------------------------------------

SettingParser::CutoffContext::CutoffContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SettingParser::CutoffContext::EXPONENTIAL() {
  return getToken(SettingParser::EXPONENTIAL, 0);
}


size_t SettingParser::CutoffContext::getRuleIndex() const {
  return SettingParser::RuleCutoff;
}


SettingParser::CutoffContext* SettingParser::cutoff() {
  CutoffContext *_localctx = _tracker.createInstance<CutoffContext>(_ctx, getState());
  enterRule(_localctx, 20, SettingParser::RuleCutoff);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(86);
    match(SettingParser::T__13);
    setState(87);
    match(SettingParser::EXPONENTIAL);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrecisionContext ------------------------------------------------------------------

SettingParser::PrecisionContext::PrecisionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SettingParser::PrecisionContext::NUMBER() {
  return getToken(SettingParser::NUMBER, 0);
}


size_t SettingParser::PrecisionContext::getRuleIndex() const {
  return SettingParser::RulePrecision;
}


SettingParser::PrecisionContext* SettingParser::precision() {
  PrecisionContext *_localctx = _tracker.createInstance<PrecisionContext>(_ctx, getState());
  enterRule(_localctx, 22, SettingParser::RulePrecision);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(89);
    match(SettingParser::T__14);
    setState(90);
    match(SettingParser::NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TermContext ------------------------------------------------------------------

SettingParser::TermContext::TermContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> SettingParser::TermContext::NUMBER() {
  return getTokens(SettingParser::NUMBER);
}

tree::TerminalNode* SettingParser::TermContext::NUMBER(size_t i) {
  return getToken(SettingParser::NUMBER, i);
}

std::vector<tree::TerminalNode *> SettingParser::TermContext::VARIABLE() {
  return getTokens(SettingParser::VARIABLE);
}

tree::TerminalNode* SettingParser::TermContext::VARIABLE(size_t i) {
  return getToken(SettingParser::VARIABLE, i);
}

std::vector<tree::TerminalNode *> SettingParser::TermContext::TIMES() {
  return getTokens(SettingParser::TIMES);
}

tree::TerminalNode* SettingParser::TermContext::TIMES(size_t i) {
  return getToken(SettingParser::TIMES, i);
}


size_t SettingParser::TermContext::getRuleIndex() const {
  return SettingParser::RuleTerm;
}


SettingParser::TermContext* SettingParser::term() {
  TermContext *_localctx = _tracker.createInstance<TermContext>(_ctx, getState());
  enterRule(_localctx, 24, SettingParser::RuleTerm);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(92);
    _la = _input->LA(1);
    if (!(_la == SettingParser::NUMBER

    || _la == SettingParser::VARIABLE)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(97);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SettingParser::TIMES) {
      setState(93);
      match(SettingParser::TIMES);
      setState(94);
      _la = _input->LA(1);
      if (!(_la == SettingParser::NUMBER

      || _la == SettingParser::VARIABLE)) {
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

SettingParser::PolynomContext::PolynomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SettingParser::TermContext *> SettingParser::PolynomContext::term() {
  return getRuleContexts<SettingParser::TermContext>();
}

SettingParser::TermContext* SettingParser::PolynomContext::term(size_t i) {
  return getRuleContext<SettingParser::TermContext>(i);
}

std::vector<tree::TerminalNode *> SettingParser::PolynomContext::PLUS() {
  return getTokens(SettingParser::PLUS);
}

tree::TerminalNode* SettingParser::PolynomContext::PLUS(size_t i) {
  return getToken(SettingParser::PLUS, i);
}


size_t SettingParser::PolynomContext::getRuleIndex() const {
  return SettingParser::RulePolynom;
}


SettingParser::PolynomContext* SettingParser::polynom() {
  PolynomContext *_localctx = _tracker.createInstance<PolynomContext>(_ctx, getState());
  enterRule(_localctx, 26, SettingParser::RulePolynom);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(100);
    term();
    setState(105);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SettingParser::PLUS) {
      setState(101);
      match(SettingParser::PLUS);
      setState(102);
      term();
      setState(107);
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

SettingParser::IntervalContext::IntervalContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> SettingParser::IntervalContext::NUMBER() {
  return getTokens(SettingParser::NUMBER);
}

tree::TerminalNode* SettingParser::IntervalContext::NUMBER(size_t i) {
  return getToken(SettingParser::NUMBER, i);
}


size_t SettingParser::IntervalContext::getRuleIndex() const {
  return SettingParser::RuleInterval;
}


SettingParser::IntervalContext* SettingParser::interval() {
  IntervalContext *_localctx = _tracker.createInstance<IntervalContext>(_ctx, getState());
  enterRule(_localctx, 28, SettingParser::RuleInterval);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(108);
    match(SettingParser::T__15);
    setState(109);
    match(SettingParser::NUMBER);
    setState(110);
    match(SettingParser::T__6);
    setState(111);
    match(SettingParser::NUMBER);
    setState(112);
    match(SettingParser::T__16);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EquationContext ------------------------------------------------------------------

SettingParser::EquationContext::EquationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SettingParser::EquationContext::VARIABLE() {
  return getToken(SettingParser::VARIABLE, 0);
}

tree::TerminalNode* SettingParser::EquationContext::EQUALS() {
  return getToken(SettingParser::EQUALS, 0);
}

SettingParser::PolynomContext* SettingParser::EquationContext::polynom() {
  return getRuleContext<SettingParser::PolynomContext>(0);
}


size_t SettingParser::EquationContext::getRuleIndex() const {
  return SettingParser::RuleEquation;
}


SettingParser::EquationContext* SettingParser::equation() {
  EquationContext *_localctx = _tracker.createInstance<EquationContext>(_ctx, getState());
  enterRule(_localctx, 30, SettingParser::RuleEquation);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(114);
    match(SettingParser::VARIABLE);
    setState(115);
    match(SettingParser::EQUALS);
    setState(116);
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

SettingParser::ConstraintContext::ConstraintContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SettingParser::PolynomContext *> SettingParser::ConstraintContext::polynom() {
  return getRuleContexts<SettingParser::PolynomContext>();
}

SettingParser::PolynomContext* SettingParser::ConstraintContext::polynom(size_t i) {
  return getRuleContext<SettingParser::PolynomContext>(i);
}

tree::TerminalNode* SettingParser::ConstraintContext::BOOLRELATION() {
  return getToken(SettingParser::BOOLRELATION, 0);
}

tree::TerminalNode* SettingParser::ConstraintContext::EQUALS() {
  return getToken(SettingParser::EQUALS, 0);
}


size_t SettingParser::ConstraintContext::getRuleIndex() const {
  return SettingParser::RuleConstraint;
}


SettingParser::ConstraintContext* SettingParser::constraint() {
  ConstraintContext *_localctx = _tracker.createInstance<ConstraintContext>(_ctx, getState());
  enterRule(_localctx, 32, SettingParser::RuleConstraint);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(118);
    polynom();
    setState(119);
    _la = _input->LA(1);
    if (!(_la == SettingParser::EQUALS

    || _la == SettingParser::BOOLRELATION)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(120);
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

SettingParser::IntervalexprContext::IntervalexprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SettingParser::IntervalexprContext::VARIABLE() {
  return getToken(SettingParser::VARIABLE, 0);
}

tree::TerminalNode* SettingParser::IntervalexprContext::IN() {
  return getToken(SettingParser::IN, 0);
}

SettingParser::IntervalContext* SettingParser::IntervalexprContext::interval() {
  return getRuleContext<SettingParser::IntervalContext>(0);
}


size_t SettingParser::IntervalexprContext::getRuleIndex() const {
  return SettingParser::RuleIntervalexpr;
}


SettingParser::IntervalexprContext* SettingParser::intervalexpr() {
  IntervalexprContext *_localctx = _tracker.createInstance<IntervalexprContext>(_ctx, getState());
  enterRule(_localctx, 34, SettingParser::RuleIntervalexpr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(122);
    match(SettingParser::VARIABLE);
    setState(123);
    match(SettingParser::IN);
    setState(124);
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

SettingParser::ConstrsetContext::ConstrsetContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SettingParser::ConstraintContext *> SettingParser::ConstrsetContext::constraint() {
  return getRuleContexts<SettingParser::ConstraintContext>();
}

SettingParser::ConstraintContext* SettingParser::ConstrsetContext::constraint(size_t i) {
  return getRuleContext<SettingParser::ConstraintContext>(i);
}

std::vector<SettingParser::IntervalexprContext *> SettingParser::ConstrsetContext::intervalexpr() {
  return getRuleContexts<SettingParser::IntervalexprContext>();
}

SettingParser::IntervalexprContext* SettingParser::ConstrsetContext::intervalexpr(size_t i) {
  return getRuleContext<SettingParser::IntervalexprContext>(i);
}


size_t SettingParser::ConstrsetContext::getRuleIndex() const {
  return SettingParser::RuleConstrset;
}


SettingParser::ConstrsetContext* SettingParser::constrset() {
  ConstrsetContext *_localctx = _tracker.createInstance<ConstrsetContext>(_ctx, getState());
  enterRule(_localctx, 36, SettingParser::RuleConstrset);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(130);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SettingParser::NUMBER

    || _la == SettingParser::VARIABLE) {
      setState(128);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
      case 1: {
        setState(126);
        constraint();
        break;
      }

      case 2: {
        setState(127);
        intervalexpr();
        break;
      }

      }
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

// Static vars and initialization.
std::vector<dfa::DFA> SettingParser::_decisionToDFA;
atn::PredictionContextCache SettingParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN SettingParser::_atn;
std::vector<uint16_t> SettingParser::_serializedATN;

std::vector<std::string> SettingParser::_ruleNames = {
  "setting", "fixedsteps", "time", "plotsetting", "filename", "maxjumps", 
  "print", "remainder", "identity", "fixedorders", "cutoff", "precision", 
  "term", "polynom", "interval", "equation", "constraint", "intervalexpr", 
  "constrset"
};

std::vector<std::string> SettingParser::_literalNames = {
  "", "'setting'", "'{'", "'}'", "'fixed steps'", "'time'", "'gnuplot octagon'", 
  "','", "'output'", "'max jumps'", "'print'", "'remainder estimation'", 
  "'identity precondition'", "'fixed orders'", "'cutoff'", "'precision'", 
  "'['", "']'", "", "'in'", "", "'='", "", "'+'", "'*'"
};

std::vector<std::string> SettingParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "EXPONENTIAL", "IN", "COMMENT", "EQUALS", "BOOLRELATION", "PLUS", "TIMES", 
  "NUMBER", "VARIABLE", "WS"
};

dfa::Vocabulary SettingParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> SettingParser::_tokenNames;

SettingParser::Initializer::Initializer() {
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
    0x3, 0x1d, 0x88, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 0x4, 
    0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 0x12, 
    0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x3, 0x2, 0x3, 
    0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 
    0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x5, 0x3, 
    0x5, 0x3, 0x5, 0x3, 0x5, 0x6, 0x5, 0x42, 0xa, 0x5, 0xd, 0x5, 0xe, 0x5, 
    0x43, 0x5, 0x5, 0x46, 0xa, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x9, 0x3, 0x9, 
    0x3, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xc, 
    0x3, 0xc, 0x3, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xe, 0x3, 0xe, 
    0x3, 0xe, 0x7, 0xe, 0x62, 0xa, 0xe, 0xc, 0xe, 0xe, 0xe, 0x65, 0xb, 0xe, 
    0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x7, 0xf, 0x6a, 0xa, 0xf, 0xc, 0xf, 0xe, 
    0xf, 0x6d, 0xb, 0xf, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 
    0x10, 0x3, 0x10, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x12, 
    0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 
    0x13, 0x3, 0x14, 0x3, 0x14, 0x7, 0x14, 0x83, 0xa, 0x14, 0xc, 0x14, 0xe, 
    0x14, 0x86, 0xb, 0x14, 0x3, 0x14, 0x2, 0x2, 0x15, 0x2, 0x4, 0x6, 0x8, 
    0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 
    0x22, 0x24, 0x26, 0x2, 0x4, 0x3, 0x2, 0x1b, 0x1c, 0x3, 0x2, 0x17, 0x18, 
    0x2, 0x7a, 0x2, 0x28, 0x3, 0x2, 0x2, 0x2, 0x4, 0x37, 0x3, 0x2, 0x2, 
    0x2, 0x6, 0x3a, 0x3, 0x2, 0x2, 0x2, 0x8, 0x3d, 0x3, 0x2, 0x2, 0x2, 0xa, 
    0x47, 0x3, 0x2, 0x2, 0x2, 0xc, 0x4a, 0x3, 0x2, 0x2, 0x2, 0xe, 0x4d, 
    0x3, 0x2, 0x2, 0x2, 0x10, 0x50, 0x3, 0x2, 0x2, 0x2, 0x12, 0x53, 0x3, 
    0x2, 0x2, 0x2, 0x14, 0x55, 0x3, 0x2, 0x2, 0x2, 0x16, 0x58, 0x3, 0x2, 
    0x2, 0x2, 0x18, 0x5b, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x5e, 0x3, 0x2, 0x2, 
    0x2, 0x1c, 0x66, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x6e, 0x3, 0x2, 0x2, 0x2, 
    0x20, 0x74, 0x3, 0x2, 0x2, 0x2, 0x22, 0x78, 0x3, 0x2, 0x2, 0x2, 0x24, 
    0x7c, 0x3, 0x2, 0x2, 0x2, 0x26, 0x84, 0x3, 0x2, 0x2, 0x2, 0x28, 0x29, 
    0x7, 0x3, 0x2, 0x2, 0x29, 0x2a, 0x7, 0x4, 0x2, 0x2, 0x2a, 0x2b, 0x5, 
    0x4, 0x3, 0x2, 0x2b, 0x2c, 0x5, 0x6, 0x4, 0x2, 0x2c, 0x2d, 0x5, 0x10, 
    0x9, 0x2, 0x2d, 0x2e, 0x5, 0x12, 0xa, 0x2, 0x2e, 0x2f, 0x5, 0x8, 0x5, 
    0x2, 0x2f, 0x30, 0x5, 0x14, 0xb, 0x2, 0x30, 0x31, 0x5, 0x16, 0xc, 0x2, 
    0x31, 0x32, 0x5, 0x18, 0xd, 0x2, 0x32, 0x33, 0x5, 0xa, 0x6, 0x2, 0x33, 
    0x34, 0x5, 0xc, 0x7, 0x2, 0x34, 0x35, 0x5, 0xe, 0x8, 0x2, 0x35, 0x36, 
    0x7, 0x5, 0x2, 0x2, 0x36, 0x3, 0x3, 0x2, 0x2, 0x2, 0x37, 0x38, 0x7, 
    0x6, 0x2, 0x2, 0x38, 0x39, 0x7, 0x1b, 0x2, 0x2, 0x39, 0x5, 0x3, 0x2, 
    0x2, 0x2, 0x3a, 0x3b, 0x7, 0x7, 0x2, 0x2, 0x3b, 0x3c, 0x7, 0x1b, 0x2, 
    0x2, 0x3c, 0x7, 0x3, 0x2, 0x2, 0x2, 0x3d, 0x3e, 0x7, 0x8, 0x2, 0x2, 
    0x3e, 0x45, 0x7, 0x1c, 0x2, 0x2, 0x3f, 0x40, 0x7, 0x9, 0x2, 0x2, 0x40, 
    0x42, 0x7, 0x1c, 0x2, 0x2, 0x41, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x42, 0x43, 
    0x3, 0x2, 0x2, 0x2, 0x43, 0x41, 0x3, 0x2, 0x2, 0x2, 0x43, 0x44, 0x3, 
    0x2, 0x2, 0x2, 0x44, 0x46, 0x3, 0x2, 0x2, 0x2, 0x45, 0x41, 0x3, 0x2, 
    0x2, 0x2, 0x45, 0x46, 0x3, 0x2, 0x2, 0x2, 0x46, 0x9, 0x3, 0x2, 0x2, 
    0x2, 0x47, 0x48, 0x7, 0xa, 0x2, 0x2, 0x48, 0x49, 0x7, 0x1c, 0x2, 0x2, 
    0x49, 0xb, 0x3, 0x2, 0x2, 0x2, 0x4a, 0x4b, 0x7, 0xb, 0x2, 0x2, 0x4b, 
    0x4c, 0x7, 0x1b, 0x2, 0x2, 0x4c, 0xd, 0x3, 0x2, 0x2, 0x2, 0x4d, 0x4e, 
    0x7, 0xc, 0x2, 0x2, 0x4e, 0x4f, 0x7, 0x1c, 0x2, 0x2, 0x4f, 0xf, 0x3, 
    0x2, 0x2, 0x2, 0x50, 0x51, 0x7, 0xd, 0x2, 0x2, 0x51, 0x52, 0x7, 0x14, 
    0x2, 0x2, 0x52, 0x11, 0x3, 0x2, 0x2, 0x2, 0x53, 0x54, 0x7, 0xe, 0x2, 
    0x2, 0x54, 0x13, 0x3, 0x2, 0x2, 0x2, 0x55, 0x56, 0x7, 0xf, 0x2, 0x2, 
    0x56, 0x57, 0x7, 0x1b, 0x2, 0x2, 0x57, 0x15, 0x3, 0x2, 0x2, 0x2, 0x58, 
    0x59, 0x7, 0x10, 0x2, 0x2, 0x59, 0x5a, 0x7, 0x14, 0x2, 0x2, 0x5a, 0x17, 
    0x3, 0x2, 0x2, 0x2, 0x5b, 0x5c, 0x7, 0x11, 0x2, 0x2, 0x5c, 0x5d, 0x7, 
    0x1b, 0x2, 0x2, 0x5d, 0x19, 0x3, 0x2, 0x2, 0x2, 0x5e, 0x63, 0x9, 0x2, 
    0x2, 0x2, 0x5f, 0x60, 0x7, 0x1a, 0x2, 0x2, 0x60, 0x62, 0x9, 0x2, 0x2, 
    0x2, 0x61, 0x5f, 0x3, 0x2, 0x2, 0x2, 0x62, 0x65, 0x3, 0x2, 0x2, 0x2, 
    0x63, 0x61, 0x3, 0x2, 0x2, 0x2, 0x63, 0x64, 0x3, 0x2, 0x2, 0x2, 0x64, 
    0x1b, 0x3, 0x2, 0x2, 0x2, 0x65, 0x63, 0x3, 0x2, 0x2, 0x2, 0x66, 0x6b, 
    0x5, 0x1a, 0xe, 0x2, 0x67, 0x68, 0x7, 0x19, 0x2, 0x2, 0x68, 0x6a, 0x5, 
    0x1a, 0xe, 0x2, 0x69, 0x67, 0x3, 0x2, 0x2, 0x2, 0x6a, 0x6d, 0x3, 0x2, 
    0x2, 0x2, 0x6b, 0x69, 0x3, 0x2, 0x2, 0x2, 0x6b, 0x6c, 0x3, 0x2, 0x2, 
    0x2, 0x6c, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x6d, 0x6b, 0x3, 0x2, 0x2, 0x2, 
    0x6e, 0x6f, 0x7, 0x12, 0x2, 0x2, 0x6f, 0x70, 0x7, 0x1b, 0x2, 0x2, 0x70, 
    0x71, 0x7, 0x9, 0x2, 0x2, 0x71, 0x72, 0x7, 0x1b, 0x2, 0x2, 0x72, 0x73, 
    0x7, 0x13, 0x2, 0x2, 0x73, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x74, 0x75, 0x7, 
    0x1c, 0x2, 0x2, 0x75, 0x76, 0x7, 0x17, 0x2, 0x2, 0x76, 0x77, 0x5, 0x1c, 
    0xf, 0x2, 0x77, 0x21, 0x3, 0x2, 0x2, 0x2, 0x78, 0x79, 0x5, 0x1c, 0xf, 
    0x2, 0x79, 0x7a, 0x9, 0x3, 0x2, 0x2, 0x7a, 0x7b, 0x5, 0x1c, 0xf, 0x2, 
    0x7b, 0x23, 0x3, 0x2, 0x2, 0x2, 0x7c, 0x7d, 0x7, 0x1c, 0x2, 0x2, 0x7d, 
    0x7e, 0x7, 0x15, 0x2, 0x2, 0x7e, 0x7f, 0x5, 0x1e, 0x10, 0x2, 0x7f, 0x25, 
    0x3, 0x2, 0x2, 0x2, 0x80, 0x83, 0x5, 0x22, 0x12, 0x2, 0x81, 0x83, 0x5, 
    0x24, 0x13, 0x2, 0x82, 0x80, 0x3, 0x2, 0x2, 0x2, 0x82, 0x81, 0x3, 0x2, 
    0x2, 0x2, 0x83, 0x86, 0x3, 0x2, 0x2, 0x2, 0x84, 0x82, 0x3, 0x2, 0x2, 
    0x2, 0x84, 0x85, 0x3, 0x2, 0x2, 0x2, 0x85, 0x27, 0x3, 0x2, 0x2, 0x2, 
    0x86, 0x84, 0x3, 0x2, 0x2, 0x2, 0x8, 0x43, 0x45, 0x63, 0x6b, 0x82, 0x84, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

SettingParser::Initializer SettingParser::_init;
