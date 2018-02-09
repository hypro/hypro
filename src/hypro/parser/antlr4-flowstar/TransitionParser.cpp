
// Generated from Transition.g4 by ANTLR 4.7



#include "TransitionParser.h"


	#include <map>
	#include <string>


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
    setState(36);
    match(TransitionParser::JUMPS);
    setState(37);
    match(TransitionParser::CBOPEN);
    setState(41);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == TransitionParser::VARIABLE) {
      setState(38);
      transition();
      setState(43);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(44);
    match(TransitionParser::CBCLOSE);
   
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
    setState(46);
    fromto();
    setState(53);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << TransitionParser::PARALLELOTOPE)
      | (1ULL << TransitionParser::BOX)
      | (1ULL << TransitionParser::URGENT)
      | (1ULL << TransitionParser::GUARD)
      | (1ULL << TransitionParser::RESET))) != 0)) {
      setState(51);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case TransitionParser::URGENT: {
          setState(47);
          urgent();
          break;
        }

        case TransitionParser::GUARD: {
          setState(48);
          guard();
          break;
        }

        case TransitionParser::RESET: {
          setState(49);
          resetfct();
          break;
        }

        case TransitionParser::PARALLELOTOPE:
        case TransitionParser::BOX: {
          setState(50);
          aggregation();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(55);
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
    setState(56);
    match(TransitionParser::VARIABLE);
    setState(57);
    match(TransitionParser::JUMP);
    setState(58);
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
    setState(60);
    match(TransitionParser::URGENT);
   
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
    setState(62);
    match(TransitionParser::GUARD);
    setState(63);
    match(TransitionParser::CBOPEN);
    setState(64);
    constrset();
    setState(65);
    match(TransitionParser::CBCLOSE);
   
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
    setState(67);
    match(TransitionParser::VARIABLE);
    setState(68);
    match(TransitionParser::DEFINE);
    setState(71);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case TransitionParser::PLUS:
      case TransitionParser::MINUS:
      case TransitionParser::NUMBER:
      case TransitionParser::VARIABLE: {
        setState(69);
        polynom();
        break;
      }

      case TransitionParser::SBOPEN: {
        setState(70);
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
    setState(73);
    match(TransitionParser::RESET);
    setState(74);
    match(TransitionParser::CBOPEN);
    setState(78);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == TransitionParser::VARIABLE) {
      setState(75);
      allocation();
      setState(80);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(81);
    match(TransitionParser::CBCLOSE);
   
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
    setState(83);
    _la = _input->LA(1);
    if (!(_la == TransitionParser::PARALLELOTOPE

    || _la == TransitionParser::BOX)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(84);
    match(TransitionParser::CBOPEN);
    setState(85);
    match(TransitionParser::CBCLOSE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReplacedexprContext ------------------------------------------------------------------

TransitionParser::ReplacedexprContext::ReplacedexprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> TransitionParser::ReplacedexprContext::NUMBER() {
  return getTokens(TransitionParser::NUMBER);
}

tree::TerminalNode* TransitionParser::ReplacedexprContext::NUMBER(size_t i) {
  return getToken(TransitionParser::NUMBER, i);
}

tree::TerminalNode* TransitionParser::ReplacedexprContext::EQUALS() {
  return getToken(TransitionParser::EQUALS, 0);
}

std::vector<tree::TerminalNode *> TransitionParser::ReplacedexprContext::MINUS() {
  return getTokens(TransitionParser::MINUS);
}

tree::TerminalNode* TransitionParser::ReplacedexprContext::MINUS(size_t i) {
  return getToken(TransitionParser::MINUS, i);
}


size_t TransitionParser::ReplacedexprContext::getRuleIndex() const {
  return TransitionParser::RuleReplacedexpr;
}


TransitionParser::ReplacedexprContext* TransitionParser::replacedexpr() {
  ReplacedexprContext *_localctx = _tracker.createInstance<ReplacedexprContext>(_ctx, getState());
  enterRule(_localctx, 16, TransitionParser::RuleReplacedexpr);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(88);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TransitionParser::MINUS) {
      setState(87);
      match(TransitionParser::MINUS);
    }
    setState(90);
    match(TransitionParser::NUMBER);
    setState(91);
    match(TransitionParser::EQUALS);
    setState(93);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TransitionParser::MINUS) {
      setState(92);
      match(TransitionParser::MINUS);
    }
    setState(95);
    match(TransitionParser::NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstantexprContext ------------------------------------------------------------------

TransitionParser::ConstantexprContext::ConstantexprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TransitionParser::ConstantexprContext::CONSTANT() {
  return getToken(TransitionParser::CONSTANT, 0);
}

tree::TerminalNode* TransitionParser::ConstantexprContext::EQUALS() {
  return getToken(TransitionParser::EQUALS, 0);
}

tree::TerminalNode* TransitionParser::ConstantexprContext::NUMBER() {
  return getToken(TransitionParser::NUMBER, 0);
}

tree::TerminalNode* TransitionParser::ConstantexprContext::MINUS() {
  return getToken(TransitionParser::MINUS, 0);
}


size_t TransitionParser::ConstantexprContext::getRuleIndex() const {
  return TransitionParser::RuleConstantexpr;
}


TransitionParser::ConstantexprContext* TransitionParser::constantexpr() {
  ConstantexprContext *_localctx = _tracker.createInstance<ConstantexprContext>(_ctx, getState());
  enterRule(_localctx, 18, TransitionParser::RuleConstantexpr);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(97);
    dynamic_cast<ConstantexprContext *>(_localctx)->constantToken = match(TransitionParser::CONSTANT);
    setState(98);
    match(TransitionParser::EQUALS);
    setState(100);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TransitionParser::MINUS) {
      setState(99);
      dynamic_cast<ConstantexprContext *>(_localctx)->minusToken = match(TransitionParser::MINUS);
    }
    setState(102);
    dynamic_cast<ConstantexprContext *>(_localctx)->numberToken = match(TransitionParser::NUMBER);

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
  enterRule(_localctx, 20, TransitionParser::RuleConnector);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(105);
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
  enterRule(_localctx, 22, TransitionParser::RuleTerm);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(107);
    _la = _input->LA(1);
    if (!(_la == TransitionParser::NUMBER

    || _la == TransitionParser::VARIABLE)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(118);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == TransitionParser::TIMES) {
      setState(108);
      match(TransitionParser::TIMES);
      setState(112);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == TransitionParser::PLUS

      || _la == TransitionParser::MINUS) {
        setState(109);
        connector();
        setState(114);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(115);
      _la = _input->LA(1);
      if (!(_la == TransitionParser::NUMBER

      || _la == TransitionParser::VARIABLE)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
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
  enterRule(_localctx, 24, TransitionParser::RulePolynom);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(124);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == TransitionParser::PLUS

    || _la == TransitionParser::MINUS) {
      setState(121);
      connector();
      setState(126);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(127);
    term();
    setState(137);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(129); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(128);
          connector();
          setState(131); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == TransitionParser::PLUS

        || _la == TransitionParser::MINUS);
        setState(133);
        term(); 
      }
      setState(139);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx);
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

std::vector<tree::TerminalNode *> TransitionParser::IntervalContext::MINUS() {
  return getTokens(TransitionParser::MINUS);
}

tree::TerminalNode* TransitionParser::IntervalContext::MINUS(size_t i) {
  return getToken(TransitionParser::MINUS, i);
}


size_t TransitionParser::IntervalContext::getRuleIndex() const {
  return TransitionParser::RuleInterval;
}


TransitionParser::IntervalContext* TransitionParser::interval() {
  IntervalContext *_localctx = _tracker.createInstance<IntervalContext>(_ctx, getState());
  enterRule(_localctx, 26, TransitionParser::RuleInterval);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(140);
    match(TransitionParser::SBOPEN);
    setState(142);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TransitionParser::MINUS) {
      setState(141);
      match(TransitionParser::MINUS);
    }
    setState(144);
    match(TransitionParser::NUMBER);
    setState(145);
    match(TransitionParser::COMMA);
    setState(147);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TransitionParser::MINUS) {
      setState(146);
      match(TransitionParser::MINUS);
    }
    setState(149);
    match(TransitionParser::NUMBER);
    setState(150);
    match(TransitionParser::SBCLOSE);
   
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

TransitionParser::ConnectorContext* TransitionParser::EquationContext::connector() {
  return getRuleContext<TransitionParser::ConnectorContext>(0);
}

TransitionParser::IntervalContext* TransitionParser::EquationContext::interval() {
  return getRuleContext<TransitionParser::IntervalContext>(0);
}


size_t TransitionParser::EquationContext::getRuleIndex() const {
  return TransitionParser::RuleEquation;
}


TransitionParser::EquationContext* TransitionParser::equation() {
  EquationContext *_localctx = _tracker.createInstance<EquationContext>(_ctx, getState());
  enterRule(_localctx, 28, TransitionParser::RuleEquation);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(152);
    match(TransitionParser::VARIABLE);
    setState(153);
    match(TransitionParser::EQUALS);
    setState(154);
    polynom();
    setState(158);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TransitionParser::PLUS

    || _la == TransitionParser::MINUS) {
      setState(155);
      connector();
      setState(156);
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
  enterRule(_localctx, 30, TransitionParser::RuleConstraint);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(160);
    polynom();
    setState(161);
    _la = _input->LA(1);
    if (!(_la == TransitionParser::EQUALS

    || _la == TransitionParser::BOOLRELATION)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(162);
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
  enterRule(_localctx, 32, TransitionParser::RuleIntervalexpr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(164);
    match(TransitionParser::VARIABLE);
    setState(165);
    match(TransitionParser::IN);
    setState(166);
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
  enterRule(_localctx, 34, TransitionParser::RuleConstrset);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(170); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(170);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
      case 1: {
        setState(168);
        constraint();
        break;
      }

      case 2: {
        setState(169);
        intervalexpr();
        break;
      }

      }
      setState(172); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << TransitionParser::PLUS)
      | (1ULL << TransitionParser::MINUS)
      | (1ULL << TransitionParser::NUMBER)
      | (1ULL << TransitionParser::VARIABLE))) != 0));
   
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
  "aggregation", "replacedexpr", "constantexpr", "connector", "term", "polynom", 
  "interval", "equation", "constraint", "intervalexpr", "constrset"
};

std::vector<std::string> TransitionParser::_literalNames = {
  "", "'parallelotope aggregation'", "'box aggregation'", "'->'", "':='", 
  "'in'", "'par'", "'jumps'", "'urgent'", "'guard'", "'reset'", "", "'='", 
  "", "'+'", "'-'", "'*'", "'['", "']'", "'{'", "'}'", "','"
};

std::vector<std::string> TransitionParser::_symbolicNames = {
  "", "PARALLELOTOPE", "BOX", "JUMP", "DEFINE", "IN", "PAR", "JUMPS", "URGENT", 
  "GUARD", "RESET", "COMMENT", "EQUALS", "BOOLRELATION", "PLUS", "MINUS", 
  "TIMES", "SBOPEN", "SBCLOSE", "CBOPEN", "CBCLOSE", "COMMA", "NUMBER", 
  "CONSTANT", "VARIABLE", "WS"
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
    0x3, 0x1b, 0xb1, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 0x4, 
    0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 0x12, 
    0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x7, 
    0x2, 0x2a, 0xa, 0x2, 0xc, 0x2, 0xe, 0x2, 0x2d, 0xb, 0x2, 0x3, 0x2, 0x3, 
    0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x7, 0x3, 0x36, 
    0xa, 0x3, 0xc, 0x3, 0xe, 0x3, 0x39, 0xb, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 
    0x4, 0x3, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 
    0x6, 0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x5, 0x7, 0x4a, 
    0xa, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x7, 0x8, 0x4f, 0xa, 0x8, 0xc, 
    0x8, 0xe, 0x8, 0x52, 0xb, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x9, 0x3, 0x9, 
    0x3, 0x9, 0x3, 0x9, 0x3, 0xa, 0x5, 0xa, 0x5b, 0xa, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xa, 0x5, 0xa, 0x60, 0xa, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xb, 
    0x3, 0xb, 0x3, 0xb, 0x5, 0xb, 0x67, 0xa, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 
    0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x7, 0xd, 0x71, 
    0xa, 0xd, 0xc, 0xd, 0xe, 0xd, 0x74, 0xb, 0xd, 0x3, 0xd, 0x7, 0xd, 0x77, 
    0xa, 0xd, 0xc, 0xd, 0xe, 0xd, 0x7a, 0xb, 0xd, 0x3, 0xe, 0x7, 0xe, 0x7d, 
    0xa, 0xe, 0xc, 0xe, 0xe, 0xe, 0x80, 0xb, 0xe, 0x3, 0xe, 0x3, 0xe, 0x6, 
    0xe, 0x84, 0xa, 0xe, 0xd, 0xe, 0xe, 0xe, 0x85, 0x3, 0xe, 0x3, 0xe, 0x7, 
    0xe, 0x8a, 0xa, 0xe, 0xc, 0xe, 0xe, 0xe, 0x8d, 0xb, 0xe, 0x3, 0xf, 0x3, 
    0xf, 0x5, 0xf, 0x91, 0xa, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x5, 0xf, 
    0x96, 0xa, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0x10, 0x3, 0x10, 
    0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x5, 0x10, 0xa1, 0xa, 0x10, 
    0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x12, 0x3, 0x12, 0x3, 
    0x12, 0x3, 0x12, 0x3, 0x13, 0x3, 0x13, 0x6, 0x13, 0xad, 0xa, 0x13, 0xd, 
    0x13, 0xe, 0x13, 0xae, 0x3, 0x13, 0x2, 0x2, 0x14, 0x2, 0x4, 0x6, 0x8, 
    0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 
    0x22, 0x24, 0x2, 0x6, 0x3, 0x2, 0x3, 0x4, 0x3, 0x2, 0x10, 0x11, 0x4, 
    0x2, 0x18, 0x18, 0x1a, 0x1a, 0x3, 0x2, 0xe, 0xf, 0x2, 0xb2, 0x2, 0x26, 
    0x3, 0x2, 0x2, 0x2, 0x4, 0x30, 0x3, 0x2, 0x2, 0x2, 0x6, 0x3a, 0x3, 0x2, 
    0x2, 0x2, 0x8, 0x3e, 0x3, 0x2, 0x2, 0x2, 0xa, 0x40, 0x3, 0x2, 0x2, 0x2, 
    0xc, 0x45, 0x3, 0x2, 0x2, 0x2, 0xe, 0x4b, 0x3, 0x2, 0x2, 0x2, 0x10, 
    0x55, 0x3, 0x2, 0x2, 0x2, 0x12, 0x5a, 0x3, 0x2, 0x2, 0x2, 0x14, 0x63, 
    0x3, 0x2, 0x2, 0x2, 0x16, 0x6b, 0x3, 0x2, 0x2, 0x2, 0x18, 0x6d, 0x3, 
    0x2, 0x2, 0x2, 0x1a, 0x7e, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x8e, 0x3, 0x2, 
    0x2, 0x2, 0x1e, 0x9a, 0x3, 0x2, 0x2, 0x2, 0x20, 0xa2, 0x3, 0x2, 0x2, 
    0x2, 0x22, 0xa6, 0x3, 0x2, 0x2, 0x2, 0x24, 0xac, 0x3, 0x2, 0x2, 0x2, 
    0x26, 0x27, 0x7, 0x9, 0x2, 0x2, 0x27, 0x2b, 0x7, 0x15, 0x2, 0x2, 0x28, 
    0x2a, 0x5, 0x4, 0x3, 0x2, 0x29, 0x28, 0x3, 0x2, 0x2, 0x2, 0x2a, 0x2d, 
    0x3, 0x2, 0x2, 0x2, 0x2b, 0x29, 0x3, 0x2, 0x2, 0x2, 0x2b, 0x2c, 0x3, 
    0x2, 0x2, 0x2, 0x2c, 0x2e, 0x3, 0x2, 0x2, 0x2, 0x2d, 0x2b, 0x3, 0x2, 
    0x2, 0x2, 0x2e, 0x2f, 0x7, 0x16, 0x2, 0x2, 0x2f, 0x3, 0x3, 0x2, 0x2, 
    0x2, 0x30, 0x37, 0x5, 0x6, 0x4, 0x2, 0x31, 0x36, 0x5, 0x8, 0x5, 0x2, 
    0x32, 0x36, 0x5, 0xa, 0x6, 0x2, 0x33, 0x36, 0x5, 0xe, 0x8, 0x2, 0x34, 
    0x36, 0x5, 0x10, 0x9, 0x2, 0x35, 0x31, 0x3, 0x2, 0x2, 0x2, 0x35, 0x32, 
    0x3, 0x2, 0x2, 0x2, 0x35, 0x33, 0x3, 0x2, 0x2, 0x2, 0x35, 0x34, 0x3, 
    0x2, 0x2, 0x2, 0x36, 0x39, 0x3, 0x2, 0x2, 0x2, 0x37, 0x35, 0x3, 0x2, 
    0x2, 0x2, 0x37, 0x38, 0x3, 0x2, 0x2, 0x2, 0x38, 0x5, 0x3, 0x2, 0x2, 
    0x2, 0x39, 0x37, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x3b, 0x7, 0x1a, 0x2, 0x2, 
    0x3b, 0x3c, 0x7, 0x5, 0x2, 0x2, 0x3c, 0x3d, 0x7, 0x1a, 0x2, 0x2, 0x3d, 
    0x7, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x3f, 0x7, 0xa, 0x2, 0x2, 0x3f, 0x9, 
    0x3, 0x2, 0x2, 0x2, 0x40, 0x41, 0x7, 0xb, 0x2, 0x2, 0x41, 0x42, 0x7, 
    0x15, 0x2, 0x2, 0x42, 0x43, 0x5, 0x24, 0x13, 0x2, 0x43, 0x44, 0x7, 0x16, 
    0x2, 0x2, 0x44, 0xb, 0x3, 0x2, 0x2, 0x2, 0x45, 0x46, 0x7, 0x1a, 0x2, 
    0x2, 0x46, 0x49, 0x7, 0x6, 0x2, 0x2, 0x47, 0x4a, 0x5, 0x1a, 0xe, 0x2, 
    0x48, 0x4a, 0x5, 0x1c, 0xf, 0x2, 0x49, 0x47, 0x3, 0x2, 0x2, 0x2, 0x49, 
    0x48, 0x3, 0x2, 0x2, 0x2, 0x4a, 0xd, 0x3, 0x2, 0x2, 0x2, 0x4b, 0x4c, 
    0x7, 0xc, 0x2, 0x2, 0x4c, 0x50, 0x7, 0x15, 0x2, 0x2, 0x4d, 0x4f, 0x5, 
    0xc, 0x7, 0x2, 0x4e, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x4f, 0x52, 0x3, 0x2, 
    0x2, 0x2, 0x50, 0x4e, 0x3, 0x2, 0x2, 0x2, 0x50, 0x51, 0x3, 0x2, 0x2, 
    0x2, 0x51, 0x53, 0x3, 0x2, 0x2, 0x2, 0x52, 0x50, 0x3, 0x2, 0x2, 0x2, 
    0x53, 0x54, 0x7, 0x16, 0x2, 0x2, 0x54, 0xf, 0x3, 0x2, 0x2, 0x2, 0x55, 
    0x56, 0x9, 0x2, 0x2, 0x2, 0x56, 0x57, 0x7, 0x15, 0x2, 0x2, 0x57, 0x58, 
    0x7, 0x16, 0x2, 0x2, 0x58, 0x11, 0x3, 0x2, 0x2, 0x2, 0x59, 0x5b, 0x7, 
    0x11, 0x2, 0x2, 0x5a, 0x59, 0x3, 0x2, 0x2, 0x2, 0x5a, 0x5b, 0x3, 0x2, 
    0x2, 0x2, 0x5b, 0x5c, 0x3, 0x2, 0x2, 0x2, 0x5c, 0x5d, 0x7, 0x18, 0x2, 
    0x2, 0x5d, 0x5f, 0x7, 0xe, 0x2, 0x2, 0x5e, 0x60, 0x7, 0x11, 0x2, 0x2, 
    0x5f, 0x5e, 0x3, 0x2, 0x2, 0x2, 0x5f, 0x60, 0x3, 0x2, 0x2, 0x2, 0x60, 
    0x61, 0x3, 0x2, 0x2, 0x2, 0x61, 0x62, 0x7, 0x18, 0x2, 0x2, 0x62, 0x13, 
    0x3, 0x2, 0x2, 0x2, 0x63, 0x64, 0x7, 0x19, 0x2, 0x2, 0x64, 0x66, 0x7, 
    0xe, 0x2, 0x2, 0x65, 0x67, 0x7, 0x11, 0x2, 0x2, 0x66, 0x65, 0x3, 0x2, 
    0x2, 0x2, 0x66, 0x67, 0x3, 0x2, 0x2, 0x2, 0x67, 0x68, 0x3, 0x2, 0x2, 
    0x2, 0x68, 0x69, 0x7, 0x18, 0x2, 0x2, 0x69, 0x6a, 0x8, 0xb, 0x1, 0x2, 
    0x6a, 0x15, 0x3, 0x2, 0x2, 0x2, 0x6b, 0x6c, 0x9, 0x3, 0x2, 0x2, 0x6c, 
    0x17, 0x3, 0x2, 0x2, 0x2, 0x6d, 0x78, 0x9, 0x4, 0x2, 0x2, 0x6e, 0x72, 
    0x7, 0x12, 0x2, 0x2, 0x6f, 0x71, 0x5, 0x16, 0xc, 0x2, 0x70, 0x6f, 0x3, 
    0x2, 0x2, 0x2, 0x71, 0x74, 0x3, 0x2, 0x2, 0x2, 0x72, 0x70, 0x3, 0x2, 
    0x2, 0x2, 0x72, 0x73, 0x3, 0x2, 0x2, 0x2, 0x73, 0x75, 0x3, 0x2, 0x2, 
    0x2, 0x74, 0x72, 0x3, 0x2, 0x2, 0x2, 0x75, 0x77, 0x9, 0x4, 0x2, 0x2, 
    0x76, 0x6e, 0x3, 0x2, 0x2, 0x2, 0x77, 0x7a, 0x3, 0x2, 0x2, 0x2, 0x78, 
    0x76, 0x3, 0x2, 0x2, 0x2, 0x78, 0x79, 0x3, 0x2, 0x2, 0x2, 0x79, 0x19, 
    0x3, 0x2, 0x2, 0x2, 0x7a, 0x78, 0x3, 0x2, 0x2, 0x2, 0x7b, 0x7d, 0x5, 
    0x16, 0xc, 0x2, 0x7c, 0x7b, 0x3, 0x2, 0x2, 0x2, 0x7d, 0x80, 0x3, 0x2, 
    0x2, 0x2, 0x7e, 0x7c, 0x3, 0x2, 0x2, 0x2, 0x7e, 0x7f, 0x3, 0x2, 0x2, 
    0x2, 0x7f, 0x81, 0x3, 0x2, 0x2, 0x2, 0x80, 0x7e, 0x3, 0x2, 0x2, 0x2, 
    0x81, 0x8b, 0x5, 0x18, 0xd, 0x2, 0x82, 0x84, 0x5, 0x16, 0xc, 0x2, 0x83, 
    0x82, 0x3, 0x2, 0x2, 0x2, 0x84, 0x85, 0x3, 0x2, 0x2, 0x2, 0x85, 0x83, 
    0x3, 0x2, 0x2, 0x2, 0x85, 0x86, 0x3, 0x2, 0x2, 0x2, 0x86, 0x87, 0x3, 
    0x2, 0x2, 0x2, 0x87, 0x88, 0x5, 0x18, 0xd, 0x2, 0x88, 0x8a, 0x3, 0x2, 
    0x2, 0x2, 0x89, 0x83, 0x3, 0x2, 0x2, 0x2, 0x8a, 0x8d, 0x3, 0x2, 0x2, 
    0x2, 0x8b, 0x89, 0x3, 0x2, 0x2, 0x2, 0x8b, 0x8c, 0x3, 0x2, 0x2, 0x2, 
    0x8c, 0x1b, 0x3, 0x2, 0x2, 0x2, 0x8d, 0x8b, 0x3, 0x2, 0x2, 0x2, 0x8e, 
    0x90, 0x7, 0x13, 0x2, 0x2, 0x8f, 0x91, 0x7, 0x11, 0x2, 0x2, 0x90, 0x8f, 
    0x3, 0x2, 0x2, 0x2, 0x90, 0x91, 0x3, 0x2, 0x2, 0x2, 0x91, 0x92, 0x3, 
    0x2, 0x2, 0x2, 0x92, 0x93, 0x7, 0x18, 0x2, 0x2, 0x93, 0x95, 0x7, 0x17, 
    0x2, 0x2, 0x94, 0x96, 0x7, 0x11, 0x2, 0x2, 0x95, 0x94, 0x3, 0x2, 0x2, 
    0x2, 0x95, 0x96, 0x3, 0x2, 0x2, 0x2, 0x96, 0x97, 0x3, 0x2, 0x2, 0x2, 
    0x97, 0x98, 0x7, 0x18, 0x2, 0x2, 0x98, 0x99, 0x7, 0x14, 0x2, 0x2, 0x99, 
    0x1d, 0x3, 0x2, 0x2, 0x2, 0x9a, 0x9b, 0x7, 0x1a, 0x2, 0x2, 0x9b, 0x9c, 
    0x7, 0xe, 0x2, 0x2, 0x9c, 0xa0, 0x5, 0x1a, 0xe, 0x2, 0x9d, 0x9e, 0x5, 
    0x16, 0xc, 0x2, 0x9e, 0x9f, 0x5, 0x1c, 0xf, 0x2, 0x9f, 0xa1, 0x3, 0x2, 
    0x2, 0x2, 0xa0, 0x9d, 0x3, 0x2, 0x2, 0x2, 0xa0, 0xa1, 0x3, 0x2, 0x2, 
    0x2, 0xa1, 0x1f, 0x3, 0x2, 0x2, 0x2, 0xa2, 0xa3, 0x5, 0x1a, 0xe, 0x2, 
    0xa3, 0xa4, 0x9, 0x5, 0x2, 0x2, 0xa4, 0xa5, 0x5, 0x1a, 0xe, 0x2, 0xa5, 
    0x21, 0x3, 0x2, 0x2, 0x2, 0xa6, 0xa7, 0x7, 0x1a, 0x2, 0x2, 0xa7, 0xa8, 
    0x7, 0x7, 0x2, 0x2, 0xa8, 0xa9, 0x5, 0x1c, 0xf, 0x2, 0xa9, 0x23, 0x3, 
    0x2, 0x2, 0x2, 0xaa, 0xad, 0x5, 0x20, 0x11, 0x2, 0xab, 0xad, 0x5, 0x22, 
    0x12, 0x2, 0xac, 0xaa, 0x3, 0x2, 0x2, 0x2, 0xac, 0xab, 0x3, 0x2, 0x2, 
    0x2, 0xad, 0xae, 0x3, 0x2, 0x2, 0x2, 0xae, 0xac, 0x3, 0x2, 0x2, 0x2, 
    0xae, 0xaf, 0x3, 0x2, 0x2, 0x2, 0xaf, 0x25, 0x3, 0x2, 0x2, 0x2, 0x14, 
    0x2b, 0x35, 0x37, 0x49, 0x50, 0x5a, 0x5f, 0x66, 0x72, 0x78, 0x7e, 0x85, 
    0x8b, 0x90, 0x95, 0xa0, 0xac, 0xae, 
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
