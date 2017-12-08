
// Generated from Setting.g4 by ANTLR 4.7



#include "SettingParser.h"


	#include <map>
	#include <string>


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

std::vector<SettingParser::FixedstepsContext *> SettingParser::SettingContext::fixedsteps() {
  return getRuleContexts<SettingParser::FixedstepsContext>();
}

SettingParser::FixedstepsContext* SettingParser::SettingContext::fixedsteps(size_t i) {
  return getRuleContext<SettingParser::FixedstepsContext>(i);
}

std::vector<SettingParser::TimeContext *> SettingParser::SettingContext::time() {
  return getRuleContexts<SettingParser::TimeContext>();
}

SettingParser::TimeContext* SettingParser::SettingContext::time(size_t i) {
  return getRuleContext<SettingParser::TimeContext>(i);
}

std::vector<SettingParser::RemainderContext *> SettingParser::SettingContext::remainder() {
  return getRuleContexts<SettingParser::RemainderContext>();
}

SettingParser::RemainderContext* SettingParser::SettingContext::remainder(size_t i) {
  return getRuleContext<SettingParser::RemainderContext>(i);
}

std::vector<SettingParser::IdentityContext *> SettingParser::SettingContext::identity() {
  return getRuleContexts<SettingParser::IdentityContext>();
}

SettingParser::IdentityContext* SettingParser::SettingContext::identity(size_t i) {
  return getRuleContext<SettingParser::IdentityContext>(i);
}

std::vector<SettingParser::PlotsettingContext *> SettingParser::SettingContext::plotsetting() {
  return getRuleContexts<SettingParser::PlotsettingContext>();
}

SettingParser::PlotsettingContext* SettingParser::SettingContext::plotsetting(size_t i) {
  return getRuleContext<SettingParser::PlotsettingContext>(i);
}

std::vector<SettingParser::FixedordersContext *> SettingParser::SettingContext::fixedorders() {
  return getRuleContexts<SettingParser::FixedordersContext>();
}

SettingParser::FixedordersContext* SettingParser::SettingContext::fixedorders(size_t i) {
  return getRuleContext<SettingParser::FixedordersContext>(i);
}

std::vector<SettingParser::CutoffContext *> SettingParser::SettingContext::cutoff() {
  return getRuleContexts<SettingParser::CutoffContext>();
}

SettingParser::CutoffContext* SettingParser::SettingContext::cutoff(size_t i) {
  return getRuleContext<SettingParser::CutoffContext>(i);
}

std::vector<SettingParser::PrecisionContext *> SettingParser::SettingContext::precision() {
  return getRuleContexts<SettingParser::PrecisionContext>();
}

SettingParser::PrecisionContext* SettingParser::SettingContext::precision(size_t i) {
  return getRuleContext<SettingParser::PrecisionContext>(i);
}

std::vector<SettingParser::FilenameContext *> SettingParser::SettingContext::filename() {
  return getRuleContexts<SettingParser::FilenameContext>();
}

SettingParser::FilenameContext* SettingParser::SettingContext::filename(size_t i) {
  return getRuleContext<SettingParser::FilenameContext>(i);
}

std::vector<SettingParser::MaxjumpsContext *> SettingParser::SettingContext::maxjumps() {
  return getRuleContexts<SettingParser::MaxjumpsContext>();
}

SettingParser::MaxjumpsContext* SettingParser::SettingContext::maxjumps(size_t i) {
  return getRuleContext<SettingParser::MaxjumpsContext>(i);
}

std::vector<SettingParser::PrintContext *> SettingParser::SettingContext::print() {
  return getRuleContexts<SettingParser::PrintContext>();
}

SettingParser::PrintContext* SettingParser::SettingContext::print(size_t i) {
  return getRuleContext<SettingParser::PrintContext>(i);
}


size_t SettingParser::SettingContext::getRuleIndex() const {
  return SettingParser::RuleSetting;
}


SettingParser::SettingContext* SettingParser::setting() {
  SettingContext *_localctx = _tracker.createInstance<SettingContext>(_ctx, getState());
  enterRule(_localctx, 0, SettingParser::RuleSetting);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(44);
    match(SettingParser::T__0);
    setState(45);
    match(SettingParser::CBOPEN);
    setState(59);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SettingParser::T__1)
      | (1ULL << SettingParser::T__2)
      | (1ULL << SettingParser::T__3)
      | (1ULL << SettingParser::T__4)
      | (1ULL << SettingParser::T__5)
      | (1ULL << SettingParser::T__6)
      | (1ULL << SettingParser::T__7)
      | (1ULL << SettingParser::T__8)
      | (1ULL << SettingParser::T__9)
      | (1ULL << SettingParser::T__10)
      | (1ULL << SettingParser::T__11))) != 0)) {
      setState(57);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case SettingParser::T__1: {
          setState(46);
          fixedsteps();
          break;
        }

        case SettingParser::T__2: {
          setState(47);
          time();
          break;
        }

        case SettingParser::T__7: {
          setState(48);
          remainder();
          break;
        }

        case SettingParser::T__8: {
          setState(49);
          identity();
          break;
        }

        case SettingParser::T__3: {
          setState(50);
          plotsetting();
          break;
        }

        case SettingParser::T__9: {
          setState(51);
          fixedorders();
          break;
        }

        case SettingParser::T__10: {
          setState(52);
          cutoff();
          break;
        }

        case SettingParser::T__11: {
          setState(53);
          precision();
          break;
        }

        case SettingParser::T__4: {
          setState(54);
          filename();
          break;
        }

        case SettingParser::T__5: {
          setState(55);
          maxjumps();
          break;
        }

        case SettingParser::T__6: {
          setState(56);
          print();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(61);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(62);
    match(SettingParser::CBCLOSE);
   
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
    setState(64);
    match(SettingParser::T__1);
    setState(65);
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
    setState(67);
    match(SettingParser::T__2);
    setState(68);
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
    setState(70);
    match(SettingParser::T__3);
    setState(71);
    match(SettingParser::VARIABLE);
    setState(78);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SettingParser::COMMA) {
      setState(74); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(72);
        match(SettingParser::COMMA);
        setState(73);
        match(SettingParser::VARIABLE);
        setState(76); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == SettingParser::COMMA);
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
    setState(80);
    match(SettingParser::T__4);
    setState(81);
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
    setState(83);
    match(SettingParser::T__5);
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
    setState(86);
    match(SettingParser::T__6);
    setState(87);
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
    setState(89);
    match(SettingParser::T__7);
    setState(90);
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
    setState(92);
    match(SettingParser::T__8);
   
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
    setState(94);
    match(SettingParser::T__9);
    setState(95);
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
    setState(97);
    match(SettingParser::T__10);
    setState(98);
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
    setState(100);
    match(SettingParser::T__11);
    setState(101);
    match(SettingParser::NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReplacedexprContext ------------------------------------------------------------------

SettingParser::ReplacedexprContext::ReplacedexprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> SettingParser::ReplacedexprContext::NUMBER() {
  return getTokens(SettingParser::NUMBER);
}

tree::TerminalNode* SettingParser::ReplacedexprContext::NUMBER(size_t i) {
  return getToken(SettingParser::NUMBER, i);
}

tree::TerminalNode* SettingParser::ReplacedexprContext::EQUALS() {
  return getToken(SettingParser::EQUALS, 0);
}

std::vector<tree::TerminalNode *> SettingParser::ReplacedexprContext::MINUS() {
  return getTokens(SettingParser::MINUS);
}

tree::TerminalNode* SettingParser::ReplacedexprContext::MINUS(size_t i) {
  return getToken(SettingParser::MINUS, i);
}


size_t SettingParser::ReplacedexprContext::getRuleIndex() const {
  return SettingParser::RuleReplacedexpr;
}


SettingParser::ReplacedexprContext* SettingParser::replacedexpr() {
  ReplacedexprContext *_localctx = _tracker.createInstance<ReplacedexprContext>(_ctx, getState());
  enterRule(_localctx, 24, SettingParser::RuleReplacedexpr);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(104);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SettingParser::MINUS) {
      setState(103);
      match(SettingParser::MINUS);
    }
    setState(106);
    match(SettingParser::NUMBER);
    setState(107);
    match(SettingParser::EQUALS);
    setState(109);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SettingParser::MINUS) {
      setState(108);
      match(SettingParser::MINUS);
    }
    setState(111);
    match(SettingParser::NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstantexprContext ------------------------------------------------------------------

SettingParser::ConstantexprContext::ConstantexprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SettingParser::ConstantexprContext::CONSTANT() {
  return getToken(SettingParser::CONSTANT, 0);
}

tree::TerminalNode* SettingParser::ConstantexprContext::EQUALS() {
  return getToken(SettingParser::EQUALS, 0);
}

tree::TerminalNode* SettingParser::ConstantexprContext::NUMBER() {
  return getToken(SettingParser::NUMBER, 0);
}

tree::TerminalNode* SettingParser::ConstantexprContext::MINUS() {
  return getToken(SettingParser::MINUS, 0);
}


size_t SettingParser::ConstantexprContext::getRuleIndex() const {
  return SettingParser::RuleConstantexpr;
}


SettingParser::ConstantexprContext* SettingParser::constantexpr() {
  ConstantexprContext *_localctx = _tracker.createInstance<ConstantexprContext>(_ctx, getState());
  enterRule(_localctx, 26, SettingParser::RuleConstantexpr);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(113);
    dynamic_cast<ConstantexprContext *>(_localctx)->constantToken = match(SettingParser::CONSTANT);
    setState(114);
    match(SettingParser::EQUALS);
    setState(116);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SettingParser::MINUS) {
      setState(115);
      dynamic_cast<ConstantexprContext *>(_localctx)->minusToken = match(SettingParser::MINUS);
    }
    setState(118);
    dynamic_cast<ConstantexprContext *>(_localctx)->numberToken = match(SettingParser::NUMBER);

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

SettingParser::ConnectorContext::ConnectorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SettingParser::ConnectorContext::PLUS() {
  return getToken(SettingParser::PLUS, 0);
}

tree::TerminalNode* SettingParser::ConnectorContext::MINUS() {
  return getToken(SettingParser::MINUS, 0);
}


size_t SettingParser::ConnectorContext::getRuleIndex() const {
  return SettingParser::RuleConnector;
}


SettingParser::ConnectorContext* SettingParser::connector() {
  ConnectorContext *_localctx = _tracker.createInstance<ConnectorContext>(_ctx, getState());
  enterRule(_localctx, 28, SettingParser::RuleConnector);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(121);
    _la = _input->LA(1);
    if (!(_la == SettingParser::PLUS

    || _la == SettingParser::MINUS)) {
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

std::vector<SettingParser::ConnectorContext *> SettingParser::TermContext::connector() {
  return getRuleContexts<SettingParser::ConnectorContext>();
}

SettingParser::ConnectorContext* SettingParser::TermContext::connector(size_t i) {
  return getRuleContext<SettingParser::ConnectorContext>(i);
}


size_t SettingParser::TermContext::getRuleIndex() const {
  return SettingParser::RuleTerm;
}


SettingParser::TermContext* SettingParser::term() {
  TermContext *_localctx = _tracker.createInstance<TermContext>(_ctx, getState());
  enterRule(_localctx, 30, SettingParser::RuleTerm);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(123);
    _la = _input->LA(1);
    if (!(_la == SettingParser::NUMBER

    || _la == SettingParser::VARIABLE)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(134);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SettingParser::TIMES) {
      setState(124);
      match(SettingParser::TIMES);
      setState(128);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == SettingParser::PLUS

      || _la == SettingParser::MINUS) {
        setState(125);
        connector();
        setState(130);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(131);
      _la = _input->LA(1);
      if (!(_la == SettingParser::NUMBER

      || _la == SettingParser::VARIABLE)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(136);
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

std::vector<SettingParser::ConnectorContext *> SettingParser::PolynomContext::connector() {
  return getRuleContexts<SettingParser::ConnectorContext>();
}

SettingParser::ConnectorContext* SettingParser::PolynomContext::connector(size_t i) {
  return getRuleContext<SettingParser::ConnectorContext>(i);
}


size_t SettingParser::PolynomContext::getRuleIndex() const {
  return SettingParser::RulePolynom;
}


SettingParser::PolynomContext* SettingParser::polynom() {
  PolynomContext *_localctx = _tracker.createInstance<PolynomContext>(_ctx, getState());
  enterRule(_localctx, 32, SettingParser::RulePolynom);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(140);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SettingParser::PLUS

    || _la == SettingParser::MINUS) {
      setState(137);
      connector();
      setState(142);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(143);
    term();
    setState(153);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(145); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(144);
          connector();
          setState(147); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == SettingParser::PLUS

        || _la == SettingParser::MINUS);
        setState(149);
        term(); 
      }
      setState(155);
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

SettingParser::IntervalContext::IntervalContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> SettingParser::IntervalContext::NUMBER() {
  return getTokens(SettingParser::NUMBER);
}

tree::TerminalNode* SettingParser::IntervalContext::NUMBER(size_t i) {
  return getToken(SettingParser::NUMBER, i);
}

std::vector<tree::TerminalNode *> SettingParser::IntervalContext::MINUS() {
  return getTokens(SettingParser::MINUS);
}

tree::TerminalNode* SettingParser::IntervalContext::MINUS(size_t i) {
  return getToken(SettingParser::MINUS, i);
}


size_t SettingParser::IntervalContext::getRuleIndex() const {
  return SettingParser::RuleInterval;
}


SettingParser::IntervalContext* SettingParser::interval() {
  IntervalContext *_localctx = _tracker.createInstance<IntervalContext>(_ctx, getState());
  enterRule(_localctx, 34, SettingParser::RuleInterval);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(156);
    match(SettingParser::SBOPEN);
    setState(158);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SettingParser::MINUS) {
      setState(157);
      match(SettingParser::MINUS);
    }
    setState(160);
    match(SettingParser::NUMBER);
    setState(161);
    match(SettingParser::COMMA);
    setState(163);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SettingParser::MINUS) {
      setState(162);
      match(SettingParser::MINUS);
    }
    setState(165);
    match(SettingParser::NUMBER);
    setState(166);
    match(SettingParser::SBCLOSE);
   
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

SettingParser::ConnectorContext* SettingParser::EquationContext::connector() {
  return getRuleContext<SettingParser::ConnectorContext>(0);
}

SettingParser::IntervalContext* SettingParser::EquationContext::interval() {
  return getRuleContext<SettingParser::IntervalContext>(0);
}


size_t SettingParser::EquationContext::getRuleIndex() const {
  return SettingParser::RuleEquation;
}


SettingParser::EquationContext* SettingParser::equation() {
  EquationContext *_localctx = _tracker.createInstance<EquationContext>(_ctx, getState());
  enterRule(_localctx, 36, SettingParser::RuleEquation);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(168);
    match(SettingParser::VARIABLE);
    setState(169);
    match(SettingParser::EQUALS);
    setState(170);
    polynom();
    setState(174);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SettingParser::PLUS

    || _la == SettingParser::MINUS) {
      setState(171);
      connector();
      setState(172);
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
  enterRule(_localctx, 38, SettingParser::RuleConstraint);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(176);
    polynom();
    setState(177);
    _la = _input->LA(1);
    if (!(_la == SettingParser::EQUALS

    || _la == SettingParser::BOOLRELATION)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(178);
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
  enterRule(_localctx, 40, SettingParser::RuleIntervalexpr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(180);
    match(SettingParser::VARIABLE);
    setState(181);
    match(SettingParser::IN);
    setState(182);
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
  enterRule(_localctx, 42, SettingParser::RuleConstrset);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(186); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(186);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
      case 1: {
        setState(184);
        constraint();
        break;
      }

      case 2: {
        setState(185);
        intervalexpr();
        break;
      }

      }
      setState(188); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << SettingParser::PLUS)
      | (1ULL << SettingParser::MINUS)
      | (1ULL << SettingParser::NUMBER)
      | (1ULL << SettingParser::VARIABLE))) != 0));
   
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
  "replacedexpr", "constantexpr", "connector", "term", "polynom", "interval", 
  "equation", "constraint", "intervalexpr", "constrset"
};

std::vector<std::string> SettingParser::_literalNames = {
  "", "'setting'", "'fixed steps'", "'time'", "'gnuplot octagon'", "'output'", 
  "'max jumps'", "'print'", "'remainder estimation'", "'identity precondition'", 
  "'fixed orders'", "'cutoff'", "'precision'", "", "'in'", "'par'", "'jumps'", 
  "'urgent'", "'guard'", "'reset'", "'parallelotope aggregation'", "'box aggregation'", 
  "'->'", "':='", "", "'='", "", "'+'", "'-'", "'*'", "'['", "']'", "'{'", 
  "'}'", "','"
};

std::vector<std::string> SettingParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "", "EXPONENTIAL", "IN", 
  "PAR", "JUMPS", "URGENT", "GUARD", "RESET", "PARALLELOTOPE", "BOX", "JUMP", 
  "DEFINE", "COMMENT", "EQUALS", "BOOLRELATION", "PLUS", "MINUS", "TIMES", 
  "SBOPEN", "SBCLOSE", "CBOPEN", "CBCLOSE", "COMMA", "NUMBER", "CONSTANT", 
  "VARIABLE", "WS"
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
    0x3, 0x28, 0xc1, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 0x4, 
    0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 0x12, 
    0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x4, 0x15, 0x9, 
    0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 0x9, 0x17, 0x3, 0x2, 0x3, 0x2, 
    0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 
    0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x7, 0x2, 0x3c, 0xa, 0x2, 0xc, 
    0x2, 0xe, 0x2, 0x3f, 0xb, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 
    0x3, 0x5, 0x6, 0x5, 0x4d, 0xa, 0x5, 0xd, 0x5, 0xe, 0x5, 0x4e, 0x5, 0x5, 
    0x51, 0xa, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 
    0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 
    0xa, 0x3, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 
    0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xe, 0x5, 0xe, 0x6b, 0xa, 0xe, 
    0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x5, 0xe, 0x70, 0xa, 0xe, 0x3, 0xe, 0x3, 
    0xe, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x5, 0xf, 0x77, 0xa, 0xf, 0x3, 0xf, 
    0x3, 0xf, 0x3, 0xf, 0x3, 0x10, 0x3, 0x10, 0x3, 0x11, 0x3, 0x11, 0x3, 
    0x11, 0x7, 0x11, 0x81, 0xa, 0x11, 0xc, 0x11, 0xe, 0x11, 0x84, 0xb, 0x11, 
    0x3, 0x11, 0x7, 0x11, 0x87, 0xa, 0x11, 0xc, 0x11, 0xe, 0x11, 0x8a, 0xb, 
    0x11, 0x3, 0x12, 0x7, 0x12, 0x8d, 0xa, 0x12, 0xc, 0x12, 0xe, 0x12, 0x90, 
    0xb, 0x12, 0x3, 0x12, 0x3, 0x12, 0x6, 0x12, 0x94, 0xa, 0x12, 0xd, 0x12, 
    0xe, 0x12, 0x95, 0x3, 0x12, 0x3, 0x12, 0x7, 0x12, 0x9a, 0xa, 0x12, 0xc, 
    0x12, 0xe, 0x12, 0x9d, 0xb, 0x12, 0x3, 0x13, 0x3, 0x13, 0x5, 0x13, 0xa1, 
    0xa, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x5, 0x13, 0xa6, 0xa, 0x13, 
    0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 
    0x14, 0x3, 0x14, 0x3, 0x14, 0x5, 0x14, 0xb1, 0xa, 0x14, 0x3, 0x15, 0x3, 
    0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 
    0x3, 0x17, 0x3, 0x17, 0x6, 0x17, 0xbd, 0xa, 0x17, 0xd, 0x17, 0xe, 0x17, 
    0xbe, 0x3, 0x17, 0x2, 0x2, 0x18, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 
    0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x24, 0x26, 
    0x28, 0x2a, 0x2c, 0x2, 0x5, 0x3, 0x2, 0x1d, 0x1e, 0x4, 0x2, 0x25, 0x25, 
    0x27, 0x27, 0x3, 0x2, 0x1b, 0x1c, 0x2, 0xc4, 0x2, 0x2e, 0x3, 0x2, 0x2, 
    0x2, 0x4, 0x42, 0x3, 0x2, 0x2, 0x2, 0x6, 0x45, 0x3, 0x2, 0x2, 0x2, 0x8, 
    0x48, 0x3, 0x2, 0x2, 0x2, 0xa, 0x52, 0x3, 0x2, 0x2, 0x2, 0xc, 0x55, 
    0x3, 0x2, 0x2, 0x2, 0xe, 0x58, 0x3, 0x2, 0x2, 0x2, 0x10, 0x5b, 0x3, 
    0x2, 0x2, 0x2, 0x12, 0x5e, 0x3, 0x2, 0x2, 0x2, 0x14, 0x60, 0x3, 0x2, 
    0x2, 0x2, 0x16, 0x63, 0x3, 0x2, 0x2, 0x2, 0x18, 0x66, 0x3, 0x2, 0x2, 
    0x2, 0x1a, 0x6a, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x73, 0x3, 0x2, 0x2, 0x2, 
    0x1e, 0x7b, 0x3, 0x2, 0x2, 0x2, 0x20, 0x7d, 0x3, 0x2, 0x2, 0x2, 0x22, 
    0x8e, 0x3, 0x2, 0x2, 0x2, 0x24, 0x9e, 0x3, 0x2, 0x2, 0x2, 0x26, 0xaa, 
    0x3, 0x2, 0x2, 0x2, 0x28, 0xb2, 0x3, 0x2, 0x2, 0x2, 0x2a, 0xb6, 0x3, 
    0x2, 0x2, 0x2, 0x2c, 0xbc, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x2f, 0x7, 0x3, 
    0x2, 0x2, 0x2f, 0x3d, 0x7, 0x22, 0x2, 0x2, 0x30, 0x3c, 0x5, 0x4, 0x3, 
    0x2, 0x31, 0x3c, 0x5, 0x6, 0x4, 0x2, 0x32, 0x3c, 0x5, 0x10, 0x9, 0x2, 
    0x33, 0x3c, 0x5, 0x12, 0xa, 0x2, 0x34, 0x3c, 0x5, 0x8, 0x5, 0x2, 0x35, 
    0x3c, 0x5, 0x14, 0xb, 0x2, 0x36, 0x3c, 0x5, 0x16, 0xc, 0x2, 0x37, 0x3c, 
    0x5, 0x18, 0xd, 0x2, 0x38, 0x3c, 0x5, 0xa, 0x6, 0x2, 0x39, 0x3c, 0x5, 
    0xc, 0x7, 0x2, 0x3a, 0x3c, 0x5, 0xe, 0x8, 0x2, 0x3b, 0x30, 0x3, 0x2, 
    0x2, 0x2, 0x3b, 0x31, 0x3, 0x2, 0x2, 0x2, 0x3b, 0x32, 0x3, 0x2, 0x2, 
    0x2, 0x3b, 0x33, 0x3, 0x2, 0x2, 0x2, 0x3b, 0x34, 0x3, 0x2, 0x2, 0x2, 
    0x3b, 0x35, 0x3, 0x2, 0x2, 0x2, 0x3b, 0x36, 0x3, 0x2, 0x2, 0x2, 0x3b, 
    0x37, 0x3, 0x2, 0x2, 0x2, 0x3b, 0x38, 0x3, 0x2, 0x2, 0x2, 0x3b, 0x39, 
    0x3, 0x2, 0x2, 0x2, 0x3b, 0x3a, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x3f, 0x3, 
    0x2, 0x2, 0x2, 0x3d, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x3d, 0x3e, 0x3, 0x2, 
    0x2, 0x2, 0x3e, 0x40, 0x3, 0x2, 0x2, 0x2, 0x3f, 0x3d, 0x3, 0x2, 0x2, 
    0x2, 0x40, 0x41, 0x7, 0x23, 0x2, 0x2, 0x41, 0x3, 0x3, 0x2, 0x2, 0x2, 
    0x42, 0x43, 0x7, 0x4, 0x2, 0x2, 0x43, 0x44, 0x7, 0x25, 0x2, 0x2, 0x44, 
    0x5, 0x3, 0x2, 0x2, 0x2, 0x45, 0x46, 0x7, 0x5, 0x2, 0x2, 0x46, 0x47, 
    0x7, 0x25, 0x2, 0x2, 0x47, 0x7, 0x3, 0x2, 0x2, 0x2, 0x48, 0x49, 0x7, 
    0x6, 0x2, 0x2, 0x49, 0x50, 0x7, 0x27, 0x2, 0x2, 0x4a, 0x4b, 0x7, 0x24, 
    0x2, 0x2, 0x4b, 0x4d, 0x7, 0x27, 0x2, 0x2, 0x4c, 0x4a, 0x3, 0x2, 0x2, 
    0x2, 0x4d, 0x4e, 0x3, 0x2, 0x2, 0x2, 0x4e, 0x4c, 0x3, 0x2, 0x2, 0x2, 
    0x4e, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x4f, 0x51, 0x3, 0x2, 0x2, 0x2, 0x50, 
    0x4c, 0x3, 0x2, 0x2, 0x2, 0x50, 0x51, 0x3, 0x2, 0x2, 0x2, 0x51, 0x9, 
    0x3, 0x2, 0x2, 0x2, 0x52, 0x53, 0x7, 0x7, 0x2, 0x2, 0x53, 0x54, 0x7, 
    0x27, 0x2, 0x2, 0x54, 0xb, 0x3, 0x2, 0x2, 0x2, 0x55, 0x56, 0x7, 0x8, 
    0x2, 0x2, 0x56, 0x57, 0x7, 0x25, 0x2, 0x2, 0x57, 0xd, 0x3, 0x2, 0x2, 
    0x2, 0x58, 0x59, 0x7, 0x9, 0x2, 0x2, 0x59, 0x5a, 0x7, 0x27, 0x2, 0x2, 
    0x5a, 0xf, 0x3, 0x2, 0x2, 0x2, 0x5b, 0x5c, 0x7, 0xa, 0x2, 0x2, 0x5c, 
    0x5d, 0x7, 0xf, 0x2, 0x2, 0x5d, 0x11, 0x3, 0x2, 0x2, 0x2, 0x5e, 0x5f, 
    0x7, 0xb, 0x2, 0x2, 0x5f, 0x13, 0x3, 0x2, 0x2, 0x2, 0x60, 0x61, 0x7, 
    0xc, 0x2, 0x2, 0x61, 0x62, 0x7, 0x25, 0x2, 0x2, 0x62, 0x15, 0x3, 0x2, 
    0x2, 0x2, 0x63, 0x64, 0x7, 0xd, 0x2, 0x2, 0x64, 0x65, 0x7, 0xf, 0x2, 
    0x2, 0x65, 0x17, 0x3, 0x2, 0x2, 0x2, 0x66, 0x67, 0x7, 0xe, 0x2, 0x2, 
    0x67, 0x68, 0x7, 0x25, 0x2, 0x2, 0x68, 0x19, 0x3, 0x2, 0x2, 0x2, 0x69, 
    0x6b, 0x7, 0x1e, 0x2, 0x2, 0x6a, 0x69, 0x3, 0x2, 0x2, 0x2, 0x6a, 0x6b, 
    0x3, 0x2, 0x2, 0x2, 0x6b, 0x6c, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x6d, 0x7, 
    0x25, 0x2, 0x2, 0x6d, 0x6f, 0x7, 0x1b, 0x2, 0x2, 0x6e, 0x70, 0x7, 0x1e, 
    0x2, 0x2, 0x6f, 0x6e, 0x3, 0x2, 0x2, 0x2, 0x6f, 0x70, 0x3, 0x2, 0x2, 
    0x2, 0x70, 0x71, 0x3, 0x2, 0x2, 0x2, 0x71, 0x72, 0x7, 0x25, 0x2, 0x2, 
    0x72, 0x1b, 0x3, 0x2, 0x2, 0x2, 0x73, 0x74, 0x7, 0x26, 0x2, 0x2, 0x74, 
    0x76, 0x7, 0x1b, 0x2, 0x2, 0x75, 0x77, 0x7, 0x1e, 0x2, 0x2, 0x76, 0x75, 
    0x3, 0x2, 0x2, 0x2, 0x76, 0x77, 0x3, 0x2, 0x2, 0x2, 0x77, 0x78, 0x3, 
    0x2, 0x2, 0x2, 0x78, 0x79, 0x7, 0x25, 0x2, 0x2, 0x79, 0x7a, 0x8, 0xf, 
    0x1, 0x2, 0x7a, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x7b, 0x7c, 0x9, 0x2, 0x2, 
    0x2, 0x7c, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x7d, 0x88, 0x9, 0x3, 0x2, 0x2, 
    0x7e, 0x82, 0x7, 0x1f, 0x2, 0x2, 0x7f, 0x81, 0x5, 0x1e, 0x10, 0x2, 0x80, 
    0x7f, 0x3, 0x2, 0x2, 0x2, 0x81, 0x84, 0x3, 0x2, 0x2, 0x2, 0x82, 0x80, 
    0x3, 0x2, 0x2, 0x2, 0x82, 0x83, 0x3, 0x2, 0x2, 0x2, 0x83, 0x85, 0x3, 
    0x2, 0x2, 0x2, 0x84, 0x82, 0x3, 0x2, 0x2, 0x2, 0x85, 0x87, 0x9, 0x3, 
    0x2, 0x2, 0x86, 0x7e, 0x3, 0x2, 0x2, 0x2, 0x87, 0x8a, 0x3, 0x2, 0x2, 
    0x2, 0x88, 0x86, 0x3, 0x2, 0x2, 0x2, 0x88, 0x89, 0x3, 0x2, 0x2, 0x2, 
    0x89, 0x21, 0x3, 0x2, 0x2, 0x2, 0x8a, 0x88, 0x3, 0x2, 0x2, 0x2, 0x8b, 
    0x8d, 0x5, 0x1e, 0x10, 0x2, 0x8c, 0x8b, 0x3, 0x2, 0x2, 0x2, 0x8d, 0x90, 
    0x3, 0x2, 0x2, 0x2, 0x8e, 0x8c, 0x3, 0x2, 0x2, 0x2, 0x8e, 0x8f, 0x3, 
    0x2, 0x2, 0x2, 0x8f, 0x91, 0x3, 0x2, 0x2, 0x2, 0x90, 0x8e, 0x3, 0x2, 
    0x2, 0x2, 0x91, 0x9b, 0x5, 0x20, 0x11, 0x2, 0x92, 0x94, 0x5, 0x1e, 0x10, 
    0x2, 0x93, 0x92, 0x3, 0x2, 0x2, 0x2, 0x94, 0x95, 0x3, 0x2, 0x2, 0x2, 
    0x95, 0x93, 0x3, 0x2, 0x2, 0x2, 0x95, 0x96, 0x3, 0x2, 0x2, 0x2, 0x96, 
    0x97, 0x3, 0x2, 0x2, 0x2, 0x97, 0x98, 0x5, 0x20, 0x11, 0x2, 0x98, 0x9a, 
    0x3, 0x2, 0x2, 0x2, 0x99, 0x93, 0x3, 0x2, 0x2, 0x2, 0x9a, 0x9d, 0x3, 
    0x2, 0x2, 0x2, 0x9b, 0x99, 0x3, 0x2, 0x2, 0x2, 0x9b, 0x9c, 0x3, 0x2, 
    0x2, 0x2, 0x9c, 0x23, 0x3, 0x2, 0x2, 0x2, 0x9d, 0x9b, 0x3, 0x2, 0x2, 
    0x2, 0x9e, 0xa0, 0x7, 0x20, 0x2, 0x2, 0x9f, 0xa1, 0x7, 0x1e, 0x2, 0x2, 
    0xa0, 0x9f, 0x3, 0x2, 0x2, 0x2, 0xa0, 0xa1, 0x3, 0x2, 0x2, 0x2, 0xa1, 
    0xa2, 0x3, 0x2, 0x2, 0x2, 0xa2, 0xa3, 0x7, 0x25, 0x2, 0x2, 0xa3, 0xa5, 
    0x7, 0x24, 0x2, 0x2, 0xa4, 0xa6, 0x7, 0x1e, 0x2, 0x2, 0xa5, 0xa4, 0x3, 
    0x2, 0x2, 0x2, 0xa5, 0xa6, 0x3, 0x2, 0x2, 0x2, 0xa6, 0xa7, 0x3, 0x2, 
    0x2, 0x2, 0xa7, 0xa8, 0x7, 0x25, 0x2, 0x2, 0xa8, 0xa9, 0x7, 0x21, 0x2, 
    0x2, 0xa9, 0x25, 0x3, 0x2, 0x2, 0x2, 0xaa, 0xab, 0x7, 0x27, 0x2, 0x2, 
    0xab, 0xac, 0x7, 0x1b, 0x2, 0x2, 0xac, 0xb0, 0x5, 0x22, 0x12, 0x2, 0xad, 
    0xae, 0x5, 0x1e, 0x10, 0x2, 0xae, 0xaf, 0x5, 0x24, 0x13, 0x2, 0xaf, 
    0xb1, 0x3, 0x2, 0x2, 0x2, 0xb0, 0xad, 0x3, 0x2, 0x2, 0x2, 0xb0, 0xb1, 
    0x3, 0x2, 0x2, 0x2, 0xb1, 0x27, 0x3, 0x2, 0x2, 0x2, 0xb2, 0xb3, 0x5, 
    0x22, 0x12, 0x2, 0xb3, 0xb4, 0x9, 0x4, 0x2, 0x2, 0xb4, 0xb5, 0x5, 0x22, 
    0x12, 0x2, 0xb5, 0x29, 0x3, 0x2, 0x2, 0x2, 0xb6, 0xb7, 0x7, 0x27, 0x2, 
    0x2, 0xb7, 0xb8, 0x7, 0x10, 0x2, 0x2, 0xb8, 0xb9, 0x5, 0x24, 0x13, 0x2, 
    0xb9, 0x2b, 0x3, 0x2, 0x2, 0x2, 0xba, 0xbd, 0x5, 0x28, 0x15, 0x2, 0xbb, 
    0xbd, 0x5, 0x2a, 0x16, 0x2, 0xbc, 0xba, 0x3, 0x2, 0x2, 0x2, 0xbc, 0xbb, 
    0x3, 0x2, 0x2, 0x2, 0xbd, 0xbe, 0x3, 0x2, 0x2, 0x2, 0xbe, 0xbc, 0x3, 
    0x2, 0x2, 0x2, 0xbe, 0xbf, 0x3, 0x2, 0x2, 0x2, 0xbf, 0x2d, 0x3, 0x2, 
    0x2, 0x2, 0x13, 0x3b, 0x3d, 0x4e, 0x50, 0x6a, 0x6f, 0x76, 0x82, 0x88, 
    0x8e, 0x95, 0x9b, 0xa0, 0xa5, 0xb0, 0xbc, 0xbe, 
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
