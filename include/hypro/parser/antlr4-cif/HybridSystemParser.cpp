
/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

// Generated from HybridSystem.g4 by ANTLR 4.7.2


#include "HybridSystemVisitor.h"

#include "HybridSystemParser.h"


using namespace antlrcpp;
using namespace hypro;
using namespace antlr4;

HybridSystemParser::HybridSystemParser(TokenStream *input) : Parser(input) {
    _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

HybridSystemParser::~HybridSystemParser() {
    delete _interpreter;
}

std::string HybridSystemParser::getGrammarFileName() const {
    return "HybridSystem.g4";
}

const std::vector <std::string> &HybridSystemParser::getRuleNames() const {
    return _ruleNames;
}

dfa::Vocabulary &HybridSystemParser::getVocabulary() const {
    return _vocabulary;
}


//----------------- SpecificationContext ------------------------------------------------------------------

HybridSystemParser::SpecificationContext::SpecificationContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::GroupBodyContext *HybridSystemParser::SpecificationContext::groupBody() {
    return getRuleContext<HybridSystemParser::GroupBodyContext>(0);
}


size_t HybridSystemParser::SpecificationContext::getRuleIndex() const {
    return HybridSystemParser::RuleSpecification;
}

antlrcpp::Any HybridSystemParser::SpecificationContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitSpecification(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::SpecificationContext *HybridSystemParser::specification() {
    SpecificationContext *_localctx = _tracker.createInstance<SpecificationContext>(_ctx, getState());
    enterRule(_localctx, 0, HybridSystemParser::RuleSpecification);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(216);
        groupBody();

    }
    catch (RecognitionException &e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- GroupBodyContext ------------------------------------------------------------------

HybridSystemParser::GroupBodyContext::GroupBodyContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::OptGroupDeclsContext *HybridSystemParser::GroupBodyContext::optGroupDecls() {
    return getRuleContext<HybridSystemParser::OptGroupDeclsContext>(0);
}


size_t HybridSystemParser::GroupBodyContext::getRuleIndex() const {
    return HybridSystemParser::RuleGroupBody;
}

antlrcpp::Any HybridSystemParser::GroupBodyContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitGroupBody(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::GroupBodyContext *HybridSystemParser::groupBody() {
    GroupBodyContext *_localctx = _tracker.createInstance<GroupBodyContext>(_ctx, getState());
    enterRule(_localctx, 2, HybridSystemParser::RuleGroupBody);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(218);
        optGroupDecls();

    }
    catch (RecognitionException &e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- AutomatonBodyContext ------------------------------------------------------------------

HybridSystemParser::AutomatonBodyContext::AutomatonBodyContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::OptAutDeclsContext *HybridSystemParser::AutomatonBodyContext::optAutDecls() {
    return getRuleContext<HybridSystemParser::OptAutDeclsContext>(0);
}

HybridSystemParser::LocationsContext *HybridSystemParser::AutomatonBodyContext::locations() {
    return getRuleContext<HybridSystemParser::LocationsContext>(0);
}

HybridSystemParser::OptIoDeclsContext *HybridSystemParser::AutomatonBodyContext::optIoDecls() {
    return getRuleContext<HybridSystemParser::OptIoDeclsContext>(0);
}


size_t HybridSystemParser::AutomatonBodyContext::getRuleIndex() const {
    return HybridSystemParser::RuleAutomatonBody;
}

antlrcpp::Any HybridSystemParser::AutomatonBodyContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitAutomatonBody(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::AutomatonBodyContext *HybridSystemParser::automatonBody() {
    AutomatonBodyContext *_localctx = _tracker.createInstance<AutomatonBodyContext>(_ctx, getState());
    enterRule(_localctx, 4, HybridSystemParser::RuleAutomatonBody);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(220);
        optAutDecls();
        setState(221);
        locations();
        setState(222);
        optIoDecls();

    }
    catch (RecognitionException &e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- OptGroupDeclsContext ------------------------------------------------------------------

HybridSystemParser::OptGroupDeclsContext::OptGroupDeclsContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::GroupDeclContext *> HybridSystemParser::OptGroupDeclsContext::groupDecl() {
    return getRuleContexts<HybridSystemParser::GroupDeclContext>();
}

HybridSystemParser::GroupDeclContext *HybridSystemParser::OptGroupDeclsContext::groupDecl(size_t i) {
    return getRuleContext<HybridSystemParser::GroupDeclContext>(i);
}


size_t HybridSystemParser::OptGroupDeclsContext::getRuleIndex() const {
    return HybridSystemParser::RuleOptGroupDecls;
}

antlrcpp::Any HybridSystemParser::OptGroupDeclsContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitOptGroupDecls(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::OptGroupDeclsContext *HybridSystemParser::optGroupDecls() {
    OptGroupDeclsContext *_localctx = _tracker.createInstance<OptGroupDeclsContext>(_ctx, getState());
    enterRule(_localctx, 6, HybridSystemParser::RuleOptGroupDecls);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(227);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~0x3fULL) == 0) &&
                ((1ULL << _la) & ((1ULL << HybridSystemParser::T__0)
                                  | (1ULL << HybridSystemParser::T__2)
                                  | (1ULL << HybridSystemParser::T__3)
                                  | (1ULL << HybridSystemParser::T__5)
                                  | (1ULL << HybridSystemParser::T__8)
                                  | (1ULL << HybridSystemParser::T__12)
                                  | (1ULL << HybridSystemParser::T__13)
                                  | (1ULL << HybridSystemParser::T__14)
                                  | (1ULL << HybridSystemParser::T__15)
                                  | (1ULL << HybridSystemParser::T__16)
                                  | (1ULL << HybridSystemParser::T__17)
                                  | (1ULL << HybridSystemParser::T__18)
                                  | (1ULL << HybridSystemParser::T__19)
                                  | (1ULL << HybridSystemParser::T__20)
                                  | (1ULL << HybridSystemParser::T__21)
                                  | (1ULL << HybridSystemParser::T__40)
                                  | (1ULL << HybridSystemParser::T__41))) != 0) || ((((_la - 74) & ~0x3fULL) == 0) &&
                                                                                    ((1ULL << (_la - 74)) & ((1ULL
                                                                                            << (HybridSystemParser::T__73 -
                                                                                                74))
                                                                                                             | (1ULL
                                                                                            << (HybridSystemParser::T__74 -
                                                                                                74))
                                                                                                             | (1ULL
                                                                                            << (HybridSystemParser::T__75 -
                                                                                                74))
                                                                                                             | (1ULL
                                                                                            << (HybridSystemParser::T__116 -
                                                                                                74))
                                                                                                             | (1ULL
                                                                                            << (HybridSystemParser::T__119 -
                                                                                                74))
                                                                                                             | (1ULL
                                                                                            << (HybridSystemParser::T__121 -
                                                                                                74))
                                                                                                             | (1ULL
                                                                                            << (HybridSystemParser::T__125 -
                                                                                                74))
                                                                                                             | (1ULL
                                                                                            << (HybridSystemParser::T__127 -
                                                                                                74))
                                                                                                             | (1ULL
                                                                                            << (HybridSystemParser::T__131 -
                                                                                                74))
                                                                                                             | (1ULL
                                                                                            << (HybridSystemParser::T__132 -
                                                                                                74))
                                                                                                             | (1ULL
                                                                                            << (HybridSystemParser::T__133 -
                                                                                                74)))) != 0) ||
               _la == HybridSystemParser::IDENTIFIER) {
            setState(224);
            groupDecl();
            setState(229);
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

//----------------- GroupDeclContext ------------------------------------------------------------------

HybridSystemParser::GroupDeclContext::GroupDeclContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::DeclContext *HybridSystemParser::GroupDeclContext::decl() {
    return getRuleContext<HybridSystemParser::DeclContext>(0);
}

HybridSystemParser::ImportsContext *HybridSystemParser::GroupDeclContext::imports() {
    return getRuleContext<HybridSystemParser::ImportsContext>(0);
}

tree::TerminalNode *HybridSystemParser::GroupDeclContext::IDENTIFIER() {
    return getToken(HybridSystemParser::IDENTIFIER, 0);
}

tree::TerminalNode *HybridSystemParser::GroupDeclContext::RELATIVENAME() {
    return getToken(HybridSystemParser::RELATIVENAME, 0);
}

HybridSystemParser::TypesContext *HybridSystemParser::GroupDeclContext::types() {
    return getRuleContext<HybridSystemParser::TypesContext>(0);
}

HybridSystemParser::IdentifierContext *HybridSystemParser::GroupDeclContext::identifier() {
    return getRuleContext<HybridSystemParser::IdentifierContext>(0);
}

HybridSystemParser::FuncParamsContext *HybridSystemParser::GroupDeclContext::funcParams() {
    return getRuleContext<HybridSystemParser::FuncParamsContext>(0);
}

HybridSystemParser::FuncBodyContext *HybridSystemParser::GroupDeclContext::funcBody() {
    return getRuleContext<HybridSystemParser::FuncBodyContext>(0);
}

HybridSystemParser::NameContext *HybridSystemParser::GroupDeclContext::name() {
    return getRuleContext<HybridSystemParser::NameContext>(0);
}

HybridSystemParser::ActualParmsContext *HybridSystemParser::GroupDeclContext::actualParms() {
    return getRuleContext<HybridSystemParser::ActualParmsContext>(0);
}

HybridSystemParser::FormalParmsContext *HybridSystemParser::GroupDeclContext::formalParms() {
    return getRuleContext<HybridSystemParser::FormalParmsContext>(0);
}

HybridSystemParser::GroupBodyContext *HybridSystemParser::GroupDeclContext::groupBody() {
    return getRuleContext<HybridSystemParser::GroupBodyContext>(0);
}

HybridSystemParser::OptSupKindContext *HybridSystemParser::GroupDeclContext::optSupKind() {
    return getRuleContext<HybridSystemParser::OptSupKindContext>(0);
}

HybridSystemParser::AutomatonBodyContext *HybridSystemParser::GroupDeclContext::automatonBody() {
    return getRuleContext<HybridSystemParser::AutomatonBodyContext>(0);
}

HybridSystemParser::SupKindContext *HybridSystemParser::GroupDeclContext::supKind() {
    return getRuleContext<HybridSystemParser::SupKindContext>(0);
}


size_t HybridSystemParser::GroupDeclContext::getRuleIndex() const {
    return HybridSystemParser::RuleGroupDecl;
}

antlrcpp::Any HybridSystemParser::GroupDeclContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitGroupDecl(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::GroupDeclContext *HybridSystemParser::groupDecl() {
    GroupDeclContext *_localctx = _tracker.createInstance<GroupDeclContext>(_ctx, getState());
    enterRule(_localctx, 8, HybridSystemParser::RuleGroupDecl);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        setState(291);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
            case 1: {
                enterOuterAlt(_localctx, 1);
                setState(230);
                decl();
                break;
            }

            case 2: {
                enterOuterAlt(_localctx, 2);
                setState(231);
                match(HybridSystemParser::T__0);
                setState(232);
                imports();
                setState(233);
                match(HybridSystemParser::T__1);
                break;
            }

            case 3: {
                enterOuterAlt(_localctx, 3);
                setState(235);
                match(HybridSystemParser::T__2);
                setState(236);
                match(HybridSystemParser::IDENTIFIER);
                setState(237);
                match(HybridSystemParser::T__1);
                break;
            }

            case 4: {
                enterOuterAlt(_localctx, 4);
                setState(238);
                match(HybridSystemParser::T__2);
                setState(239);
                match(HybridSystemParser::RELATIVENAME);
                setState(240);
                match(HybridSystemParser::T__1);
                break;
            }

            case 5: {
                enterOuterAlt(_localctx, 5);
                setState(241);
                match(HybridSystemParser::T__3);
                setState(242);
                types();
                setState(243);
                identifier();
                setState(244);
                funcParams();
                setState(245);
                match(HybridSystemParser::T__4);
                setState(246);
                funcBody();
                break;
            }

            case 6: {
                enterOuterAlt(_localctx, 6);
                setState(248);
                identifier();
                setState(249);
                match(HybridSystemParser::T__4);
                setState(250);
                name();
                setState(251);
                actualParms();
                setState(252);
                match(HybridSystemParser::T__1);
                break;
            }

            case 7: {
                enterOuterAlt(_localctx, 7);
                setState(254);
                match(HybridSystemParser::T__5);
                setState(255);
                match(HybridSystemParser::T__6);
                setState(256);
                identifier();
                setState(257);
                formalParms();
                setState(258);
                match(HybridSystemParser::T__4);
                setState(259);
                groupBody();
                setState(260);
                match(HybridSystemParser::T__7);
                break;
            }

            case 8: {
                enterOuterAlt(_localctx, 8);
                setState(262);
                optSupKind();
                setState(263);
                match(HybridSystemParser::T__8);
                setState(264);
                match(HybridSystemParser::T__6);
                setState(265);
                identifier();
                setState(266);
                formalParms();
                setState(267);
                match(HybridSystemParser::T__4);
                setState(268);
                automatonBody();
                setState(269);
                match(HybridSystemParser::T__7);
                break;
            }

            case 9: {
                enterOuterAlt(_localctx, 9);
                setState(271);
                supKind();
                setState(272);
                match(HybridSystemParser::T__6);
                setState(273);
                identifier();
                setState(274);
                match(HybridSystemParser::T__4);
                setState(275);
                groupBody();
                setState(276);
                match(HybridSystemParser::T__7);
                break;
            }

            case 10: {
                enterOuterAlt(_localctx, 10);
                setState(278);
                optSupKind();
                setState(279);
                match(HybridSystemParser::T__8);
                setState(280);
                identifier();
                setState(281);
                match(HybridSystemParser::T__4);
                setState(282);
                automatonBody();
                setState(283);
                match(HybridSystemParser::T__7);
                break;
            }

            case 11: {
                enterOuterAlt(_localctx, 11);
                setState(285);
                supKind();
                setState(286);
                identifier();
                setState(287);
                match(HybridSystemParser::T__4);
                setState(288);
                automatonBody();
                setState(289);
                match(HybridSystemParser::T__7);
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

//----------------- OptAutDeclsContext ------------------------------------------------------------------

HybridSystemParser::OptAutDeclsContext::OptAutDeclsContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::AutDeclContext *> HybridSystemParser::OptAutDeclsContext::autDecl() {
    return getRuleContexts<HybridSystemParser::AutDeclContext>();
}

HybridSystemParser::AutDeclContext *HybridSystemParser::OptAutDeclsContext::autDecl(size_t i) {
    return getRuleContext<HybridSystemParser::AutDeclContext>(i);
}


size_t HybridSystemParser::OptAutDeclsContext::getRuleIndex() const {
    return HybridSystemParser::RuleOptAutDecls;
}

antlrcpp::Any HybridSystemParser::OptAutDeclsContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitOptAutDecls(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::OptAutDeclsContext *HybridSystemParser::optAutDecls() {
    OptAutDeclsContext *_localctx = _tracker.createInstance<OptAutDeclsContext>(_ctx, getState());
    enterRule(_localctx, 10, HybridSystemParser::RuleOptAutDecls);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(296);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~0x3fULL) == 0) &&
                ((1ULL << _la) & ((1ULL << HybridSystemParser::T__9)
                                  | (1ULL << HybridSystemParser::T__10)
                                  | (1ULL << HybridSystemParser::T__11)
                                  | (1ULL << HybridSystemParser::T__12)
                                  | (1ULL << HybridSystemParser::T__13)
                                  | (1ULL << HybridSystemParser::T__14)
                                  | (1ULL << HybridSystemParser::T__15)
                                  | (1ULL << HybridSystemParser::T__16)
                                  | (1ULL << HybridSystemParser::T__17)
                                  | (1ULL << HybridSystemParser::T__18)
                                  | (1ULL << HybridSystemParser::T__19)
                                  | (1ULL << HybridSystemParser::T__20)
                                  | (1ULL << HybridSystemParser::T__21)
                                  | (1ULL << HybridSystemParser::T__40)
                                  | (1ULL << HybridSystemParser::T__41))) != 0) || ((((_la - 74) & ~0x3fULL) == 0) &&
                                                                                    ((1ULL << (_la - 74)) & ((1ULL
                                                                                            << (HybridSystemParser::T__73 -
                                                                                                74))
                                                                                                             | (1ULL
                                                                                            << (HybridSystemParser::T__74 -
                                                                                                74))
                                                                                                             | (1ULL
                                                                                            << (HybridSystemParser::T__75 -
                                                                                                74))
                                                                                                             | (1ULL
                                                                                            << (HybridSystemParser::T__116 -
                                                                                                74))
                                                                                                             | (1ULL
                                                                                            << (HybridSystemParser::T__119 -
                                                                                                74))
                                                                                                             | (1ULL
                                                                                            << (HybridSystemParser::T__121 -
                                                                                                74))
                                                                                                             | (1ULL
                                                                                            << (HybridSystemParser::T__125 -
                                                                                                74))
                                                                                                             | (1ULL
                                                                                            << (HybridSystemParser::T__127 -
                                                                                                74))
                                                                                                             | (1ULL
                                                                                            << (HybridSystemParser::T__131 -
                                                                                                74))
                                                                                                             | (1ULL
                                                                                            << (HybridSystemParser::T__132 -
                                                                                                74))
                                                                                                             | (1ULL
                                                                                            << (HybridSystemParser::T__133 -
                                                                                                74)))) != 0)) {
            setState(293);
            autDecl();
            setState(298);
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

//----------------- AutDeclContext ------------------------------------------------------------------

HybridSystemParser::AutDeclContext::AutDeclContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::DeclContext *HybridSystemParser::AutDeclContext::decl() {
    return getRuleContext<HybridSystemParser::DeclContext>(0);
}

HybridSystemParser::EventsContext *HybridSystemParser::AutDeclContext::events() {
    return getRuleContext<HybridSystemParser::EventsContext>(0);
}

HybridSystemParser::TypeContext *HybridSystemParser::AutDeclContext::type() {
    return getRuleContext<HybridSystemParser::TypeContext>(0);
}

HybridSystemParser::DiscDeclsContext *HybridSystemParser::AutDeclContext::discDecls() {
    return getRuleContext<HybridSystemParser::DiscDeclsContext>(0);
}


size_t HybridSystemParser::AutDeclContext::getRuleIndex() const {
    return HybridSystemParser::RuleAutDecl;
}

antlrcpp::Any HybridSystemParser::AutDeclContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitAutDecl(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::AutDeclContext *HybridSystemParser::autDecl() {
    AutDeclContext *_localctx = _tracker.createInstance<AutDeclContext>(_ctx, getState());
    enterRule(_localctx, 12, HybridSystemParser::RuleAutDecl);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        setState(317);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
            case 1: {
                enterOuterAlt(_localctx, 1);
                setState(299);
                decl();
                break;
            }

            case 2: {
                enterOuterAlt(_localctx, 2);
                setState(300);
                match(HybridSystemParser::T__9);
                setState(301);
                events();
                setState(302);
                match(HybridSystemParser::T__1);
                break;
            }

            case 3: {
                enterOuterAlt(_localctx, 3);
                setState(304);
                match(HybridSystemParser::T__9);
                setState(305);
                match(HybridSystemParser::T__1);
                break;
            }

            case 4: {
                enterOuterAlt(_localctx, 4);
                setState(306);
                match(HybridSystemParser::T__10);
                setState(307);
                events();
                setState(308);
                match(HybridSystemParser::T__1);
                break;
            }

            case 5: {
                enterOuterAlt(_localctx, 5);
                setState(310);
                match(HybridSystemParser::T__10);
                setState(311);
                match(HybridSystemParser::T__1);
                break;
            }

            case 6: {
                enterOuterAlt(_localctx, 6);
                setState(312);
                match(HybridSystemParser::T__11);
                setState(313);
                type();
                setState(314);
                discDecls();
                setState(315);
                match(HybridSystemParser::T__1);
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

//----------------- DeclContext ------------------------------------------------------------------

HybridSystemParser::DeclContext::DeclContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::TypeDefsContext *HybridSystemParser::DeclContext::typeDefs() {
    return getRuleContext<HybridSystemParser::TypeDefsContext>(0);
}

HybridSystemParser::EnumDefsContext *HybridSystemParser::DeclContext::enumDefs() {
    return getRuleContext<HybridSystemParser::EnumDefsContext>(0);
}

HybridSystemParser::OptControllabilityContext *HybridSystemParser::DeclContext::optControllability() {
    return getRuleContext<HybridSystemParser::OptControllabilityContext>(0);
}

HybridSystemParser::IdentifierContext *HybridSystemParser::DeclContext::identifier() {
    return getRuleContext<HybridSystemParser::IdentifierContext>(0);
}

HybridSystemParser::EventTypeContext *HybridSystemParser::DeclContext::eventType() {
    return getRuleContext<HybridSystemParser::EventTypeContext>(0);
}

HybridSystemParser::ControllabilityContext *HybridSystemParser::DeclContext::controllability() {
    return getRuleContext<HybridSystemParser::ControllabilityContext>(0);
}

HybridSystemParser::TypeContext *HybridSystemParser::DeclContext::type() {
    return getRuleContext<HybridSystemParser::TypeContext>(0);
}

HybridSystemParser::ConstantDefsContext *HybridSystemParser::DeclContext::constantDefs() {
    return getRuleContext<HybridSystemParser::ConstantDefsContext>(0);
}

HybridSystemParser::AlgVarsDefsContext *HybridSystemParser::DeclContext::algVarsDefs() {
    return getRuleContext<HybridSystemParser::AlgVarsDefsContext>(0);
}

HybridSystemParser::ContDeclsContext *HybridSystemParser::DeclContext::contDecls() {
    return getRuleContext<HybridSystemParser::ContDeclsContext>(0);
}

HybridSystemParser::EquationsContext *HybridSystemParser::DeclContext::equations() {
    return getRuleContext<HybridSystemParser::EquationsContext>(0);
}

HybridSystemParser::ExpressionsContext *HybridSystemParser::DeclContext::expressions() {
    return getRuleContext<HybridSystemParser::ExpressionsContext>(0);
}

HybridSystemParser::InvariantDeclsContext *HybridSystemParser::DeclContext::invariantDecls() {
    return getRuleContext<HybridSystemParser::InvariantDeclsContext>(0);
}

HybridSystemParser::IoDeclsContext *HybridSystemParser::DeclContext::ioDecls() {
    return getRuleContext<HybridSystemParser::IoDeclsContext>(0);
}


size_t HybridSystemParser::DeclContext::getRuleIndex() const {
    return HybridSystemParser::RuleDecl;
}

antlrcpp::Any HybridSystemParser::DeclContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitDecl(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::DeclContext *HybridSystemParser::decl() {
    DeclContext *_localctx = _tracker.createInstance<DeclContext>(_ctx, getState());
    enterRule(_localctx, 14, HybridSystemParser::RuleDecl);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        setState(380);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
            case 1: {
                enterOuterAlt(_localctx, 1);
                setState(319);
                match(HybridSystemParser::T__12);
                setState(320);
                typeDefs();
                setState(321);
                match(HybridSystemParser::T__1);
                break;
            }

            case 2: {
                enterOuterAlt(_localctx, 2);
                setState(323);
                match(HybridSystemParser::T__13);
                setState(324);
                enumDefs();
                setState(325);
                match(HybridSystemParser::T__1);
                break;
            }

            case 3: {
                enterOuterAlt(_localctx, 3);
                setState(327);
                optControllability();
                setState(328);
                match(HybridSystemParser::T__14);
                setState(329);
                identifier();
                setState(330);
                match(HybridSystemParser::T__1);
                break;
            }

            case 4: {
                enterOuterAlt(_localctx, 4);
                setState(332);
                optControllability();
                setState(333);
                match(HybridSystemParser::T__14);
                setState(334);
                eventType();
                setState(335);
                identifier();
                setState(336);
                match(HybridSystemParser::T__1);
                break;
            }

            case 5: {
                enterOuterAlt(_localctx, 5);
                setState(338);
                controllability();
                setState(339);
                identifier();
                setState(340);
                match(HybridSystemParser::T__1);
                break;
            }

            case 6: {
                enterOuterAlt(_localctx, 6);
                setState(342);
                controllability();
                setState(343);
                eventType();
                setState(344);
                identifier();
                setState(345);
                match(HybridSystemParser::T__1);
                break;
            }

            case 7: {
                enterOuterAlt(_localctx, 7);
                setState(347);
                match(HybridSystemParser::T__15);
                setState(348);
                type();
                setState(349);
                constantDefs();
                setState(350);
                match(HybridSystemParser::T__1);
                break;
            }

            case 8: {
                enterOuterAlt(_localctx, 8);
                setState(352);
                match(HybridSystemParser::T__16);
                setState(353);
                type();
                setState(354);
                algVarsDefs();
                setState(355);
                match(HybridSystemParser::T__1);
                break;
            }

            case 9: {
                enterOuterAlt(_localctx, 9);
                setState(357);
                match(HybridSystemParser::T__17);
                setState(358);
                type();
                setState(359);
                identifier();
                setState(360);
                match(HybridSystemParser::T__1);
                break;
            }

            case 10: {
                enterOuterAlt(_localctx, 10);
                setState(362);
                match(HybridSystemParser::T__18);
                setState(363);
                contDecls();
                setState(364);
                match(HybridSystemParser::T__1);
                break;
            }

            case 11: {
                enterOuterAlt(_localctx, 11);
                setState(366);
                match(HybridSystemParser::T__19);
                setState(367);
                equations();
                setState(368);
                match(HybridSystemParser::T__1);
                break;
            }

            case 12: {
                enterOuterAlt(_localctx, 12);
                setState(370);
                match(HybridSystemParser::T__20);
                setState(371);
                expressions();
                setState(372);
                match(HybridSystemParser::T__1);
                break;
            }

            case 13: {
                enterOuterAlt(_localctx, 13);
                setState(374);
                invariantDecls();
                break;
            }

            case 14: {
                enterOuterAlt(_localctx, 14);
                setState(375);
                match(HybridSystemParser::T__21);
                setState(376);
                expressions();
                setState(377);
                match(HybridSystemParser::T__1);
                break;
            }

            case 15: {
                enterOuterAlt(_localctx, 15);
                setState(379);
                ioDecls();
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

//----------------- ImportsContext ------------------------------------------------------------------

HybridSystemParser::ImportsContext::ImportsContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::StringTokenContext *> HybridSystemParser::ImportsContext::stringToken() {
    return getRuleContexts<HybridSystemParser::StringTokenContext>();
}

HybridSystemParser::StringTokenContext *HybridSystemParser::ImportsContext::stringToken(size_t i) {
    return getRuleContext<HybridSystemParser::StringTokenContext>(i);
}


size_t HybridSystemParser::ImportsContext::getRuleIndex() const {
    return HybridSystemParser::RuleImports;
}

antlrcpp::Any HybridSystemParser::ImportsContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitImports(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::ImportsContext *HybridSystemParser::imports() {
    ImportsContext *_localctx = _tracker.createInstance<ImportsContext>(_ctx, getState());
    enterRule(_localctx, 16, HybridSystemParser::RuleImports);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(382);
        stringToken();
        setState(387);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == HybridSystemParser::T__22) {
            setState(383);
            match(HybridSystemParser::T__22);
            setState(384);
            stringToken();
            setState(389);
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

//----------------- TypeDefsContext ------------------------------------------------------------------

HybridSystemParser::TypeDefsContext::TypeDefsContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::IdentifierContext *> HybridSystemParser::TypeDefsContext::identifier() {
    return getRuleContexts<HybridSystemParser::IdentifierContext>();
}

HybridSystemParser::IdentifierContext *HybridSystemParser::TypeDefsContext::identifier(size_t i) {
    return getRuleContext<HybridSystemParser::IdentifierContext>(i);
}

std::vector<HybridSystemParser::TypeContext *> HybridSystemParser::TypeDefsContext::type() {
    return getRuleContexts<HybridSystemParser::TypeContext>();
}

HybridSystemParser::TypeContext *HybridSystemParser::TypeDefsContext::type(size_t i) {
    return getRuleContext<HybridSystemParser::TypeContext>(i);
}


size_t HybridSystemParser::TypeDefsContext::getRuleIndex() const {
    return HybridSystemParser::RuleTypeDefs;
}

antlrcpp::Any HybridSystemParser::TypeDefsContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitTypeDefs(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::TypeDefsContext *HybridSystemParser::typeDefs() {
    TypeDefsContext *_localctx = _tracker.createInstance<TypeDefsContext>(_ctx, getState());
    enterRule(_localctx, 18, HybridSystemParser::RuleTypeDefs);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(390);
        identifier();
        setState(391);
        match(HybridSystemParser::T__23);
        setState(392);
        type();
        setState(400);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == HybridSystemParser::T__22) {
            setState(393);
            match(HybridSystemParser::T__22);
            setState(394);
            identifier();
            setState(395);
            match(HybridSystemParser::T__23);
            setState(396);
            type();
            setState(402);
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

//----------------- EnumDefsContext ------------------------------------------------------------------

HybridSystemParser::EnumDefsContext::EnumDefsContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::IdentifierContext *> HybridSystemParser::EnumDefsContext::identifier() {
    return getRuleContexts<HybridSystemParser::IdentifierContext>();
}

HybridSystemParser::IdentifierContext *HybridSystemParser::EnumDefsContext::identifier(size_t i) {
    return getRuleContext<HybridSystemParser::IdentifierContext>(i);
}


size_t HybridSystemParser::EnumDefsContext::getRuleIndex() const {
    return HybridSystemParser::RuleEnumDefs;
}

antlrcpp::Any HybridSystemParser::EnumDefsContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitEnumDefs(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::EnumDefsContext *HybridSystemParser::enumDefs() {
    EnumDefsContext *_localctx = _tracker.createInstance<EnumDefsContext>(_ctx, getState());
    enterRule(_localctx, 20, HybridSystemParser::RuleEnumDefs);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(403);
        identifier();
        setState(404);
        match(HybridSystemParser::T__23);
        setState(405);
        match(HybridSystemParser::T__24);
        setState(406);
        identifier();
        setState(407);
        match(HybridSystemParser::T__25);
        setState(417);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == HybridSystemParser::T__22) {
            setState(408);
            match(HybridSystemParser::T__22);
            setState(409);
            identifier();
            setState(410);
            match(HybridSystemParser::T__23);
            setState(411);
            match(HybridSystemParser::T__24);
            setState(412);
            identifier();
            setState(413);
            match(HybridSystemParser::T__25);
            setState(419);
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

//----------------- ConstantDefsContext ------------------------------------------------------------------

HybridSystemParser::ConstantDefsContext::ConstantDefsContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::IdentifierContext *> HybridSystemParser::ConstantDefsContext::identifier() {
    return getRuleContexts<HybridSystemParser::IdentifierContext>();
}

HybridSystemParser::IdentifierContext *HybridSystemParser::ConstantDefsContext::identifier(size_t i) {
    return getRuleContext<HybridSystemParser::IdentifierContext>(i);
}

std::vector<HybridSystemParser::ExpressionContext *> HybridSystemParser::ConstantDefsContext::expression() {
    return getRuleContexts<HybridSystemParser::ExpressionContext>();
}

HybridSystemParser::ExpressionContext *HybridSystemParser::ConstantDefsContext::expression(size_t i) {
    return getRuleContext<HybridSystemParser::ExpressionContext>(i);
}


size_t HybridSystemParser::ConstantDefsContext::getRuleIndex() const {
    return HybridSystemParser::RuleConstantDefs;
}

antlrcpp::Any HybridSystemParser::ConstantDefsContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitConstantDefs(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::ConstantDefsContext *HybridSystemParser::constantDefs() {
    ConstantDefsContext *_localctx = _tracker.createInstance<ConstantDefsContext>(_ctx, getState());
    enterRule(_localctx, 22, HybridSystemParser::RuleConstantDefs);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(420);
        identifier();
        setState(421);
        match(HybridSystemParser::T__23);
        setState(422);
        expression();
        setState(430);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == HybridSystemParser::T__22) {
            setState(423);
            match(HybridSystemParser::T__22);
            setState(424);
            identifier();
            setState(425);
            match(HybridSystemParser::T__23);
            setState(426);
            expression();
            setState(432);
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

//----------------- AlgVarsDefsContext ------------------------------------------------------------------

HybridSystemParser::AlgVarsDefsContext::AlgVarsDefsContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::IdentifierContext *> HybridSystemParser::AlgVarsDefsContext::identifier() {
    return getRuleContexts<HybridSystemParser::IdentifierContext>();
}

HybridSystemParser::IdentifierContext *HybridSystemParser::AlgVarsDefsContext::identifier(size_t i) {
    return getRuleContext<HybridSystemParser::IdentifierContext>(i);
}

std::vector<HybridSystemParser::ExpressionContext *> HybridSystemParser::AlgVarsDefsContext::expression() {
    return getRuleContexts<HybridSystemParser::ExpressionContext>();
}

HybridSystemParser::ExpressionContext *HybridSystemParser::AlgVarsDefsContext::expression(size_t i) {
    return getRuleContext<HybridSystemParser::ExpressionContext>(i);
}


size_t HybridSystemParser::AlgVarsDefsContext::getRuleIndex() const {
    return HybridSystemParser::RuleAlgVarsDefs;
}

antlrcpp::Any HybridSystemParser::AlgVarsDefsContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitAlgVarsDefs(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::AlgVarsDefsContext *HybridSystemParser::algVarsDefs() {
    AlgVarsDefsContext *_localctx = _tracker.createInstance<AlgVarsDefsContext>(_ctx, getState());
    enterRule(_localctx, 24, HybridSystemParser::RuleAlgVarsDefs);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(438);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
            case 1: {
                setState(433);
                identifier();
                break;
            }

            case 2: {
                setState(434);
                identifier();
                setState(435);
                match(HybridSystemParser::T__23);
                setState(436);
                expression();
                break;
            }

        }
        setState(450);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == HybridSystemParser::T__22) {
            setState(440);
            match(HybridSystemParser::T__22);
            setState(446);
            _errHandler->sync(this);
            switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
                case 1: {
                    setState(441);
                    identifier();
                    break;
                }

                case 2: {
                    setState(442);
                    identifier();
                    setState(443);
                    match(HybridSystemParser::T__23);
                    setState(444);
                    expression();
                    break;
                }

            }
            setState(452);
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

//----------------- FuncParamsContext ------------------------------------------------------------------

HybridSystemParser::FuncParamsContext::FuncParamsContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::FuncParamDeclsContext *HybridSystemParser::FuncParamsContext::funcParamDecls() {
    return getRuleContext<HybridSystemParser::FuncParamDeclsContext>(0);
}


size_t HybridSystemParser::FuncParamsContext::getRuleIndex() const {
    return HybridSystemParser::RuleFuncParams;
}

antlrcpp::Any HybridSystemParser::FuncParamsContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitFuncParams(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::FuncParamsContext *HybridSystemParser::funcParams() {
    FuncParamsContext *_localctx = _tracker.createInstance<FuncParamsContext>(_ctx, getState());
    enterRule(_localctx, 26, HybridSystemParser::RuleFuncParams);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        setState(459);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
            case 1: {
                enterOuterAlt(_localctx, 1);
                setState(453);
                match(HybridSystemParser::T__26);
                setState(454);
                match(HybridSystemParser::T__27);
                break;
            }

            case 2: {
                enterOuterAlt(_localctx, 2);
                setState(455);
                match(HybridSystemParser::T__26);
                setState(456);
                funcParamDecls();
                setState(457);
                match(HybridSystemParser::T__27);
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

//----------------- FuncParamDeclsContext ------------------------------------------------------------------

HybridSystemParser::FuncParamDeclsContext::FuncParamDeclsContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::TypeContext *> HybridSystemParser::FuncParamDeclsContext::type() {
    return getRuleContexts<HybridSystemParser::TypeContext>();
}

HybridSystemParser::TypeContext *HybridSystemParser::FuncParamDeclsContext::type(size_t i) {
    return getRuleContext<HybridSystemParser::TypeContext>(i);
}

std::vector<HybridSystemParser::IdentifierContext *> HybridSystemParser::FuncParamDeclsContext::identifier() {
    return getRuleContexts<HybridSystemParser::IdentifierContext>();
}

HybridSystemParser::IdentifierContext *HybridSystemParser::FuncParamDeclsContext::identifier(size_t i) {
    return getRuleContext<HybridSystemParser::IdentifierContext>(i);
}


size_t HybridSystemParser::FuncParamDeclsContext::getRuleIndex() const {
    return HybridSystemParser::RuleFuncParamDecls;
}

antlrcpp::Any HybridSystemParser::FuncParamDeclsContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitFuncParamDecls(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::FuncParamDeclsContext *HybridSystemParser::funcParamDecls() {
    FuncParamDeclsContext *_localctx = _tracker.createInstance<FuncParamDeclsContext>(_ctx, getState());
    enterRule(_localctx, 28, HybridSystemParser::RuleFuncParamDecls);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(461);
        type();
        setState(462);
        identifier();
        setState(469);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == HybridSystemParser::T__1) {
            setState(463);
            match(HybridSystemParser::T__1);
            setState(464);
            type();
            setState(465);
            identifier();
            setState(471);
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

//----------------- FuncBodyContext ------------------------------------------------------------------

HybridSystemParser::FuncBodyContext::FuncBodyContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::FuncVarDeclsContext *HybridSystemParser::FuncBodyContext::funcVarDecls() {
    return getRuleContext<HybridSystemParser::FuncVarDeclsContext>(0);
}

HybridSystemParser::FuncStatementsContext *HybridSystemParser::FuncBodyContext::funcStatements() {
    return getRuleContext<HybridSystemParser::FuncStatementsContext>(0);
}

HybridSystemParser::StringTokenContext *HybridSystemParser::FuncBodyContext::stringToken() {
    return getRuleContext<HybridSystemParser::StringTokenContext>(0);
}


size_t HybridSystemParser::FuncBodyContext::getRuleIndex() const {
    return HybridSystemParser::RuleFuncBody;
}

antlrcpp::Any HybridSystemParser::FuncBodyContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitFuncBody(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::FuncBodyContext *HybridSystemParser::funcBody() {
    FuncBodyContext *_localctx = _tracker.createInstance<FuncBodyContext>(_ctx, getState());
    enterRule(_localctx, 30, HybridSystemParser::RuleFuncBody);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        setState(479);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
            case HybridSystemParser::T__3:
            case HybridSystemParser::T__26:
            case HybridSystemParser::T__29:
            case HybridSystemParser::T__30:
            case HybridSystemParser::T__31:
            case HybridSystemParser::T__32:
            case HybridSystemParser::T__33:
            case HybridSystemParser::T__63:
            case HybridSystemParser::T__64:
            case HybridSystemParser::T__66:
            case HybridSystemParser::T__67:
            case HybridSystemParser::T__68:
            case HybridSystemParser::T__69:
            case HybridSystemParser::T__70:
            case HybridSystemParser::T__71:
            case HybridSystemParser::T__72:
            case HybridSystemParser::IDENTIFIER:
            case HybridSystemParser::RELATIVENAME:
            case HybridSystemParser::ABSOLUTENAME:
            case HybridSystemParser::ROOTNAME: {
                enterOuterAlt(_localctx, 1);
                setState(472);
                funcVarDecls();
                setState(473);
                funcStatements();
                setState(474);
                match(HybridSystemParser::T__7);
                break;
            }

            case HybridSystemParser::STRING: {
                enterOuterAlt(_localctx, 2);
                setState(476);
                stringToken();
                setState(477);
                match(HybridSystemParser::T__1);
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

//----------------- FuncVarDeclsContext ------------------------------------------------------------------

HybridSystemParser::FuncVarDeclsContext::FuncVarDeclsContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::TypeContext *> HybridSystemParser::FuncVarDeclsContext::type() {
    return getRuleContexts<HybridSystemParser::TypeContext>();
}

HybridSystemParser::TypeContext *HybridSystemParser::FuncVarDeclsContext::type(size_t i) {
    return getRuleContext<HybridSystemParser::TypeContext>(i);
}

std::vector<HybridSystemParser::FuncVarDeclContext *> HybridSystemParser::FuncVarDeclsContext::funcVarDecl() {
    return getRuleContexts<HybridSystemParser::FuncVarDeclContext>();
}

HybridSystemParser::FuncVarDeclContext *HybridSystemParser::FuncVarDeclsContext::funcVarDecl(size_t i) {
    return getRuleContext<HybridSystemParser::FuncVarDeclContext>(i);
}


size_t HybridSystemParser::FuncVarDeclsContext::getRuleIndex() const {
    return HybridSystemParser::RuleFuncVarDecls;
}

antlrcpp::Any HybridSystemParser::FuncVarDeclsContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitFuncVarDecls(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::FuncVarDeclsContext *HybridSystemParser::funcVarDecls() {
    FuncVarDeclsContext *_localctx = _tracker.createInstance<FuncVarDeclsContext>(_ctx, getState());
    enterRule(_localctx, 32, HybridSystemParser::RuleFuncVarDecls);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        size_t alt;
        enterOuterAlt(_localctx, 1);
        setState(487);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
            if (alt == 1) {
                setState(481);
                type();
                setState(482);
                funcVarDecl();
                setState(483);
                match(HybridSystemParser::T__1);
            }
            setState(489);
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx);
        }

    }
    catch (RecognitionException &e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- FuncVarDeclContext ------------------------------------------------------------------

HybridSystemParser::FuncVarDeclContext::FuncVarDeclContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::IdentifierContext *> HybridSystemParser::FuncVarDeclContext::identifier() {
    return getRuleContexts<HybridSystemParser::IdentifierContext>();
}

HybridSystemParser::IdentifierContext *HybridSystemParser::FuncVarDeclContext::identifier(size_t i) {
    return getRuleContext<HybridSystemParser::IdentifierContext>(i);
}

std::vector<HybridSystemParser::ExpressionContext *> HybridSystemParser::FuncVarDeclContext::expression() {
    return getRuleContexts<HybridSystemParser::ExpressionContext>();
}

HybridSystemParser::ExpressionContext *HybridSystemParser::FuncVarDeclContext::expression(size_t i) {
    return getRuleContext<HybridSystemParser::ExpressionContext>(i);
}


size_t HybridSystemParser::FuncVarDeclContext::getRuleIndex() const {
    return HybridSystemParser::RuleFuncVarDecl;
}

antlrcpp::Any HybridSystemParser::FuncVarDeclContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitFuncVarDecl(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::FuncVarDeclContext *HybridSystemParser::funcVarDecl() {
    FuncVarDeclContext *_localctx = _tracker.createInstance<FuncVarDeclContext>(_ctx, getState());
    enterRule(_localctx, 34, HybridSystemParser::RuleFuncVarDecl);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(495);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
            case 1: {
                setState(490);
                identifier();
                break;
            }

            case 2: {
                setState(491);
                identifier();
                setState(492);
                match(HybridSystemParser::T__23);
                setState(493);
                expression();
                break;
            }

        }
        setState(507);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == HybridSystemParser::T__22) {
            setState(497);
            match(HybridSystemParser::T__22);
            setState(503);
            _errHandler->sync(this);
            switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx)) {
                case 1: {
                    setState(498);
                    identifier();
                    break;
                }

                case 2: {
                    setState(499);
                    identifier();
                    setState(500);
                    match(HybridSystemParser::T__23);
                    setState(501);
                    expression();
                    break;
                }

            }
            setState(509);
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

//----------------- FuncStatementsContext ------------------------------------------------------------------

HybridSystemParser::FuncStatementsContext::FuncStatementsContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::FuncStatementContext *> HybridSystemParser::FuncStatementsContext::funcStatement() {
    return getRuleContexts<HybridSystemParser::FuncStatementContext>();
}

HybridSystemParser::FuncStatementContext *HybridSystemParser::FuncStatementsContext::funcStatement(size_t i) {
    return getRuleContext<HybridSystemParser::FuncStatementContext>(i);
}


size_t HybridSystemParser::FuncStatementsContext::getRuleIndex() const {
    return HybridSystemParser::RuleFuncStatements;
}

antlrcpp::Any HybridSystemParser::FuncStatementsContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitFuncStatements(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::FuncStatementsContext *HybridSystemParser::funcStatements() {
    FuncStatementsContext *_localctx = _tracker.createInstance<FuncStatementsContext>(_ctx, getState());
    enterRule(_localctx, 36, HybridSystemParser::RuleFuncStatements);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(511);
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
            setState(510);
            funcStatement();
            setState(513);
            _errHandler->sync(this);
            _la = _input->LA(1);
        } while ((((_la & ~0x3fULL) == 0) &&
                  ((1ULL << _la) & ((1ULL << HybridSystemParser::T__26)
                                    | (1ULL << HybridSystemParser::T__29)
                                    | (1ULL << HybridSystemParser::T__30)
                                    | (1ULL << HybridSystemParser::T__31)
                                    | (1ULL << HybridSystemParser::T__32)
                                    | (1ULL << HybridSystemParser::T__33))) != 0) ||
                 _la == HybridSystemParser::IDENTIFIER);

    }
    catch (RecognitionException &e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- FuncStatementContext ------------------------------------------------------------------

HybridSystemParser::FuncStatementContext::FuncStatementContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::AdressablesContext *HybridSystemParser::FuncStatementContext::adressables() {
    return getRuleContext<HybridSystemParser::AdressablesContext>(0);
}

HybridSystemParser::ExpressionsContext *HybridSystemParser::FuncStatementContext::expressions() {
    return getRuleContext<HybridSystemParser::ExpressionsContext>(0);
}

HybridSystemParser::FuncStatementsContext *HybridSystemParser::FuncStatementContext::funcStatements() {
    return getRuleContext<HybridSystemParser::FuncStatementsContext>(0);
}

HybridSystemParser::OptElifFuncStatsContext *HybridSystemParser::FuncStatementContext::optElifFuncStats() {
    return getRuleContext<HybridSystemParser::OptElifFuncStatsContext>(0);
}

HybridSystemParser::OptElseFuncStatContext *HybridSystemParser::FuncStatementContext::optElseFuncStat() {
    return getRuleContext<HybridSystemParser::OptElseFuncStatContext>(0);
}


size_t HybridSystemParser::FuncStatementContext::getRuleIndex() const {
    return HybridSystemParser::RuleFuncStatement;
}

antlrcpp::Any HybridSystemParser::FuncStatementContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitFuncStatement(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::FuncStatementContext *HybridSystemParser::funcStatement() {
    FuncStatementContext *_localctx = _tracker.createInstance<FuncStatementContext>(_ctx, getState());
    enterRule(_localctx, 38, HybridSystemParser::RuleFuncStatement);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        setState(542);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
            case HybridSystemParser::T__26:
            case HybridSystemParser::IDENTIFIER: {
                enterOuterAlt(_localctx, 1);
                setState(515);
                adressables();
                setState(516);
                match(HybridSystemParser::T__28);
                setState(517);
                expressions();
                setState(518);
                match(HybridSystemParser::T__1);
                break;
            }

            case HybridSystemParser::T__29: {
                enterOuterAlt(_localctx, 2);
                setState(520);
                match(HybridSystemParser::T__29);
                setState(521);
                expressions();
                setState(522);
                match(HybridSystemParser::T__4);
                setState(523);
                funcStatements();
                setState(524);
                optElifFuncStats();
                setState(525);
                optElseFuncStat();
                setState(526);
                match(HybridSystemParser::T__7);
                break;
            }

            case HybridSystemParser::T__30: {
                enterOuterAlt(_localctx, 3);
                setState(528);
                match(HybridSystemParser::T__30);
                setState(529);
                expressions();
                setState(530);
                match(HybridSystemParser::T__4);
                setState(531);
                funcStatements();
                setState(532);
                match(HybridSystemParser::T__7);
                break;
            }

            case HybridSystemParser::T__31: {
                enterOuterAlt(_localctx, 4);
                setState(534);
                match(HybridSystemParser::T__31);
                setState(535);
                match(HybridSystemParser::T__1);
                break;
            }

            case HybridSystemParser::T__32: {
                enterOuterAlt(_localctx, 5);
                setState(536);
                match(HybridSystemParser::T__32);
                setState(537);
                match(HybridSystemParser::T__1);
                break;
            }

            case HybridSystemParser::T__33: {
                enterOuterAlt(_localctx, 6);
                setState(538);
                match(HybridSystemParser::T__33);
                setState(539);
                expressions();
                setState(540);
                match(HybridSystemParser::T__1);
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

//----------------- OptElifFuncStatsContext ------------------------------------------------------------------

HybridSystemParser::OptElifFuncStatsContext::OptElifFuncStatsContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::ExpressionContext *> HybridSystemParser::OptElifFuncStatsContext::expression() {
    return getRuleContexts<HybridSystemParser::ExpressionContext>();
}

HybridSystemParser::ExpressionContext *HybridSystemParser::OptElifFuncStatsContext::expression(size_t i) {
    return getRuleContext<HybridSystemParser::ExpressionContext>(i);
}

std::vector<HybridSystemParser::FuncStatementsContext *> HybridSystemParser::OptElifFuncStatsContext::funcStatements() {
    return getRuleContexts<HybridSystemParser::FuncStatementsContext>();
}

HybridSystemParser::FuncStatementsContext *HybridSystemParser::OptElifFuncStatsContext::funcStatements(size_t i) {
    return getRuleContext<HybridSystemParser::FuncStatementsContext>(i);
}


size_t HybridSystemParser::OptElifFuncStatsContext::getRuleIndex() const {
    return HybridSystemParser::RuleOptElifFuncStats;
}

antlrcpp::Any HybridSystemParser::OptElifFuncStatsContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitOptElifFuncStats(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::OptElifFuncStatsContext *HybridSystemParser::optElifFuncStats() {
    OptElifFuncStatsContext *_localctx = _tracker.createInstance<OptElifFuncStatsContext>(_ctx, getState());
    enterRule(_localctx, 40, HybridSystemParser::RuleOptElifFuncStats);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(551);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == HybridSystemParser::T__34) {
            setState(544);
            match(HybridSystemParser::T__34);
            setState(545);
            expression();
            setState(546);
            match(HybridSystemParser::T__4);
            setState(547);
            funcStatements();
            setState(553);
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

//----------------- OptElseFuncStatContext ------------------------------------------------------------------

HybridSystemParser::OptElseFuncStatContext::OptElseFuncStatContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::FuncStatementsContext *HybridSystemParser::OptElseFuncStatContext::funcStatements() {
    return getRuleContext<HybridSystemParser::FuncStatementsContext>(0);
}


size_t HybridSystemParser::OptElseFuncStatContext::getRuleIndex() const {
    return HybridSystemParser::RuleOptElseFuncStat;
}

antlrcpp::Any HybridSystemParser::OptElseFuncStatContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitOptElseFuncStat(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::OptElseFuncStatContext *HybridSystemParser::optElseFuncStat() {
    OptElseFuncStatContext *_localctx = _tracker.createInstance<OptElseFuncStatContext>(_ctx, getState());
    enterRule(_localctx, 42, HybridSystemParser::RuleOptElseFuncStat);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(554);
        match(HybridSystemParser::T__35);
        setState(555);
        funcStatements();

    }
    catch (RecognitionException &e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- EventsContext ------------------------------------------------------------------

HybridSystemParser::EventsContext::EventsContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::NameContext *> HybridSystemParser::EventsContext::name() {
    return getRuleContexts<HybridSystemParser::NameContext>();
}

HybridSystemParser::NameContext *HybridSystemParser::EventsContext::name(size_t i) {
    return getRuleContext<HybridSystemParser::NameContext>(i);
}


size_t HybridSystemParser::EventsContext::getRuleIndex() const {
    return HybridSystemParser::RuleEvents;
}

antlrcpp::Any HybridSystemParser::EventsContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitEvents(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::EventsContext *HybridSystemParser::events() {
    EventsContext *_localctx = _tracker.createInstance<EventsContext>(_ctx, getState());
    enterRule(_localctx, 44, HybridSystemParser::RuleEvents);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(557);
        name();
        setState(562);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == HybridSystemParser::T__22) {
            setState(558);
            match(HybridSystemParser::T__22);
            setState(559);
            name();
            setState(564);
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

//----------------- ActualParmsContext ------------------------------------------------------------------

HybridSystemParser::ActualParmsContext::ActualParmsContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::ExpressionsContext *HybridSystemParser::ActualParmsContext::expressions() {
    return getRuleContext<HybridSystemParser::ExpressionsContext>(0);
}


size_t HybridSystemParser::ActualParmsContext::getRuleIndex() const {
    return HybridSystemParser::RuleActualParms;
}

antlrcpp::Any HybridSystemParser::ActualParmsContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitActualParms(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::ActualParmsContext *HybridSystemParser::actualParms() {
    ActualParmsContext *_localctx = _tracker.createInstance<ActualParmsContext>(_ctx, getState());
    enterRule(_localctx, 46, HybridSystemParser::RuleActualParms);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        setState(571);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
            case 1: {
                enterOuterAlt(_localctx, 1);
                setState(565);
                match(HybridSystemParser::T__26);
                setState(566);
                match(HybridSystemParser::T__27);
                break;
            }

            case 2: {
                enterOuterAlt(_localctx, 2);
                setState(567);
                match(HybridSystemParser::T__26);
                setState(568);
                expressions();
                setState(569);
                match(HybridSystemParser::T__27);
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

//----------------- FormalParmsContext ------------------------------------------------------------------

HybridSystemParser::FormalParmsContext::FormalParmsContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::FormalDeclsContext *HybridSystemParser::FormalParmsContext::formalDecls() {
    return getRuleContext<HybridSystemParser::FormalDeclsContext>(0);
}


size_t HybridSystemParser::FormalParmsContext::getRuleIndex() const {
    return HybridSystemParser::RuleFormalParms;
}

antlrcpp::Any HybridSystemParser::FormalParmsContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitFormalParms(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::FormalParmsContext *HybridSystemParser::formalParms() {
    FormalParmsContext *_localctx = _tracker.createInstance<FormalParmsContext>(_ctx, getState());
    enterRule(_localctx, 48, HybridSystemParser::RuleFormalParms);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        setState(579);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
            case 1: {
                enterOuterAlt(_localctx, 1);
                setState(573);
                match(HybridSystemParser::T__26);
                setState(574);
                match(HybridSystemParser::T__27);
                break;
            }

            case 2: {
                enterOuterAlt(_localctx, 2);
                setState(575);
                match(HybridSystemParser::T__26);
                setState(576);
                formalDecls();
                setState(577);
                match(HybridSystemParser::T__27);
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

//----------------- FormalDeclsContext ------------------------------------------------------------------

HybridSystemParser::FormalDeclsContext::FormalDeclsContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::FormalDeclarationContext *>
HybridSystemParser::FormalDeclsContext::formalDeclaration() {
    return getRuleContexts<HybridSystemParser::FormalDeclarationContext>();
}

HybridSystemParser::FormalDeclarationContext *HybridSystemParser::FormalDeclsContext::formalDeclaration(size_t i) {
    return getRuleContext<HybridSystemParser::FormalDeclarationContext>(i);
}


size_t HybridSystemParser::FormalDeclsContext::getRuleIndex() const {
    return HybridSystemParser::RuleFormalDecls;
}

antlrcpp::Any HybridSystemParser::FormalDeclsContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitFormalDecls(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::FormalDeclsContext *HybridSystemParser::formalDecls() {
    FormalDeclsContext *_localctx = _tracker.createInstance<FormalDeclsContext>(_ctx, getState());
    enterRule(_localctx, 50, HybridSystemParser::RuleFormalDecls);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(581);
        formalDeclaration();
        setState(586);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == HybridSystemParser::T__1) {
            setState(582);
            match(HybridSystemParser::T__1);
            setState(583);
            formalDeclaration();
            setState(588);
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

//----------------- FormalDeclarationContext ------------------------------------------------------------------

HybridSystemParser::FormalDeclarationContext::FormalDeclarationContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::OptControllabilityContext *HybridSystemParser::FormalDeclarationContext::optControllability() {
    return getRuleContext<HybridSystemParser::OptControllabilityContext>(0);
}

HybridSystemParser::IdentifierContext *HybridSystemParser::FormalDeclarationContext::identifier() {
    return getRuleContext<HybridSystemParser::IdentifierContext>(0);
}

HybridSystemParser::EventTypeContext *HybridSystemParser::FormalDeclarationContext::eventType() {
    return getRuleContext<HybridSystemParser::EventTypeContext>(0);
}

HybridSystemParser::ControllabilityContext *HybridSystemParser::FormalDeclarationContext::controllability() {
    return getRuleContext<HybridSystemParser::ControllabilityContext>(0);
}

HybridSystemParser::NameContext *HybridSystemParser::FormalDeclarationContext::name() {
    return getRuleContext<HybridSystemParser::NameContext>(0);
}

HybridSystemParser::TypeContext *HybridSystemParser::FormalDeclarationContext::type() {
    return getRuleContext<HybridSystemParser::TypeContext>(0);
}


size_t HybridSystemParser::FormalDeclarationContext::getRuleIndex() const {
    return HybridSystemParser::RuleFormalDeclaration;
}

antlrcpp::Any HybridSystemParser::FormalDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitFormalDeclaration(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::FormalDeclarationContext *HybridSystemParser::formalDeclaration() {
    FormalDeclarationContext *_localctx = _tracker.createInstance<FormalDeclarationContext>(_ctx, getState());
    enterRule(_localctx, 52, HybridSystemParser::RuleFormalDeclaration);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        setState(614);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
            case 1: {
                enterOuterAlt(_localctx, 1);
                setState(589);
                optControllability();
                setState(590);
                match(HybridSystemParser::T__14);
                setState(591);
                identifier();
                break;
            }

            case 2: {
                enterOuterAlt(_localctx, 2);
                setState(593);
                optControllability();
                setState(594);
                match(HybridSystemParser::T__14);
                setState(595);
                eventType();
                setState(596);
                identifier();
                break;
            }

            case 3: {
                enterOuterAlt(_localctx, 3);
                setState(598);
                controllability();
                setState(599);
                identifier();
                break;
            }

            case 4: {
                enterOuterAlt(_localctx, 4);
                setState(601);
                controllability();
                setState(602);
                eventType();
                setState(603);
                identifier();
                break;
            }

            case 5: {
                enterOuterAlt(_localctx, 5);
                setState(605);
                name();
                setState(606);
                identifier();
                break;
            }

            case 6: {
                enterOuterAlt(_localctx, 6);
                setState(608);
                match(HybridSystemParser::T__36);
                setState(609);
                identifier();
                break;
            }

            case 7: {
                enterOuterAlt(_localctx, 7);
                setState(610);
                match(HybridSystemParser::T__16);
                setState(611);
                type();
                setState(612);
                identifier();
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

//----------------- DiscDeclsContext ------------------------------------------------------------------

HybridSystemParser::DiscDeclsContext::DiscDeclsContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::DiscDeclContext *> HybridSystemParser::DiscDeclsContext::discDecl() {
    return getRuleContexts<HybridSystemParser::DiscDeclContext>();
}

HybridSystemParser::DiscDeclContext *HybridSystemParser::DiscDeclsContext::discDecl(size_t i) {
    return getRuleContext<HybridSystemParser::DiscDeclContext>(i);
}


size_t HybridSystemParser::DiscDeclsContext::getRuleIndex() const {
    return HybridSystemParser::RuleDiscDecls;
}

antlrcpp::Any HybridSystemParser::DiscDeclsContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitDiscDecls(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::DiscDeclsContext *HybridSystemParser::discDecls() {
    DiscDeclsContext *_localctx = _tracker.createInstance<DiscDeclsContext>(_ctx, getState());
    enterRule(_localctx, 54, HybridSystemParser::RuleDiscDecls);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(616);
        discDecl();
        setState(621);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == HybridSystemParser::T__22) {
            setState(617);
            match(HybridSystemParser::T__22);
            setState(618);
            discDecl();
            setState(623);
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

//----------------- DiscDeclContext ------------------------------------------------------------------

HybridSystemParser::DiscDeclContext::DiscDeclContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::IdentifierContext *HybridSystemParser::DiscDeclContext::identifier() {
    return getRuleContext<HybridSystemParser::IdentifierContext>(0);
}

HybridSystemParser::ExpressionContext *HybridSystemParser::DiscDeclContext::expression() {
    return getRuleContext<HybridSystemParser::ExpressionContext>(0);
}

HybridSystemParser::ExpressionsContext *HybridSystemParser::DiscDeclContext::expressions() {
    return getRuleContext<HybridSystemParser::ExpressionsContext>(0);
}


size_t HybridSystemParser::DiscDeclContext::getRuleIndex() const {
    return HybridSystemParser::RuleDiscDecl;
}

antlrcpp::Any HybridSystemParser::DiscDeclContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitDiscDecl(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::DiscDeclContext *HybridSystemParser::discDecl() {
    DiscDeclContext *_localctx = _tracker.createInstance<DiscDeclContext>(_ctx, getState());
    enterRule(_localctx, 56, HybridSystemParser::RuleDiscDecl);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        setState(639);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx)) {
            case 1: {
                enterOuterAlt(_localctx, 1);
                setState(624);
                identifier();
                break;
            }

            case 2: {
                enterOuterAlt(_localctx, 2);
                setState(625);
                identifier();
                setState(626);
                match(HybridSystemParser::T__37);
                setState(627);
                match(HybridSystemParser::T__38);
                break;
            }

            case 3: {
                enterOuterAlt(_localctx, 3);
                setState(629);
                identifier();
                setState(630);
                match(HybridSystemParser::T__23);
                setState(631);
                expression();
                break;
            }

            case 4: {
                enterOuterAlt(_localctx, 4);
                setState(633);
                identifier();
                setState(634);
                match(HybridSystemParser::T__37);
                setState(635);
                match(HybridSystemParser::T__24);
                setState(636);
                expressions();
                setState(637);
                match(HybridSystemParser::T__25);
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

//----------------- ContDeclsContext ------------------------------------------------------------------

HybridSystemParser::ContDeclsContext::ContDeclsContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::ContDeclContext *> HybridSystemParser::ContDeclsContext::contDecl() {
    return getRuleContexts<HybridSystemParser::ContDeclContext>();
}

HybridSystemParser::ContDeclContext *HybridSystemParser::ContDeclsContext::contDecl(size_t i) {
    return getRuleContext<HybridSystemParser::ContDeclContext>(i);
}


size_t HybridSystemParser::ContDeclsContext::getRuleIndex() const {
    return HybridSystemParser::RuleContDecls;
}

antlrcpp::Any HybridSystemParser::ContDeclsContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitContDecls(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::ContDeclsContext *HybridSystemParser::contDecls() {
    ContDeclsContext *_localctx = _tracker.createInstance<ContDeclsContext>(_ctx, getState());
    enterRule(_localctx, 58, HybridSystemParser::RuleContDecls);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(641);
        contDecl();
        setState(646);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == HybridSystemParser::T__22) {
            setState(642);
            match(HybridSystemParser::T__22);
            setState(643);
            contDecl();
            setState(648);
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

//----------------- ContDeclContext ------------------------------------------------------------------

HybridSystemParser::ContDeclContext::ContDeclContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::IdentifierContext *HybridSystemParser::ContDeclContext::identifier() {
    return getRuleContext<HybridSystemParser::IdentifierContext>(0);
}

HybridSystemParser::OptDerivateContext *HybridSystemParser::ContDeclContext::optDerivate() {
    return getRuleContext<HybridSystemParser::OptDerivateContext>(0);
}

HybridSystemParser::ExpressionContext *HybridSystemParser::ContDeclContext::expression() {
    return getRuleContext<HybridSystemParser::ExpressionContext>(0);
}


size_t HybridSystemParser::ContDeclContext::getRuleIndex() const {
    return HybridSystemParser::RuleContDecl;
}

antlrcpp::Any HybridSystemParser::ContDeclContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitContDecl(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::ContDeclContext *HybridSystemParser::contDecl() {
    ContDeclContext *_localctx = _tracker.createInstance<ContDeclContext>(_ctx, getState());
    enterRule(_localctx, 60, HybridSystemParser::RuleContDecl);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        setState(657);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx)) {
            case 1: {
                enterOuterAlt(_localctx, 1);
                setState(649);
                identifier();
                setState(650);
                optDerivate();
                break;
            }

            case 2: {
                enterOuterAlt(_localctx, 2);
                setState(652);
                identifier();
                setState(653);
                match(HybridSystemParser::T__23);
                setState(654);
                expression();
                setState(655);
                optDerivate();
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

//----------------- OptDerivateContext ------------------------------------------------------------------

HybridSystemParser::OptDerivateContext::OptDerivateContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::ExpressionContext *HybridSystemParser::OptDerivateContext::expression() {
    return getRuleContext<HybridSystemParser::ExpressionContext>(0);
}


size_t HybridSystemParser::OptDerivateContext::getRuleIndex() const {
    return HybridSystemParser::RuleOptDerivate;
}

antlrcpp::Any HybridSystemParser::OptDerivateContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitOptDerivate(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::OptDerivateContext *HybridSystemParser::optDerivate() {
    OptDerivateContext *_localctx = _tracker.createInstance<OptDerivateContext>(_ctx, getState());
    enterRule(_localctx, 62, HybridSystemParser::RuleOptDerivate);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(661);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == HybridSystemParser::T__39) {
            setState(659);
            match(HybridSystemParser::T__39);
            setState(660);
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

//----------------- OptControllabilityContext ------------------------------------------------------------------

HybridSystemParser::OptControllabilityContext::OptControllabilityContext(ParserRuleContext *parent,
                                                                         size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::ControllabilityContext *HybridSystemParser::OptControllabilityContext::controllability() {
    return getRuleContext<HybridSystemParser::ControllabilityContext>(0);
}


size_t HybridSystemParser::OptControllabilityContext::getRuleIndex() const {
    return HybridSystemParser::RuleOptControllability;
}

antlrcpp::Any HybridSystemParser::OptControllabilityContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitOptControllability(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::OptControllabilityContext *HybridSystemParser::optControllability() {
    OptControllabilityContext *_localctx = _tracker.createInstance<OptControllabilityContext>(_ctx, getState());
    enterRule(_localctx, 64, HybridSystemParser::RuleOptControllability);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(664);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == HybridSystemParser::T__40

            || _la == HybridSystemParser::T__41) {
            setState(663);
            controllability();
        }

    }
    catch (RecognitionException &e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- ControllabilityContext ------------------------------------------------------------------

HybridSystemParser::ControllabilityContext::ControllabilityContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}


size_t HybridSystemParser::ControllabilityContext::getRuleIndex() const {
    return HybridSystemParser::RuleControllability;
}

antlrcpp::Any HybridSystemParser::ControllabilityContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitControllability(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::ControllabilityContext *HybridSystemParser::controllability() {
    ControllabilityContext *_localctx = _tracker.createInstance<ControllabilityContext>(_ctx, getState());
    enterRule(_localctx, 66, HybridSystemParser::RuleControllability);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(666);
        _la = _input->LA(1);
        if (!(_la == HybridSystemParser::T__40

              || _la == HybridSystemParser::T__41)) {
            _errHandler->recoverInline(this);
        } else {
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

//----------------- EventTypeContext ------------------------------------------------------------------

HybridSystemParser::EventTypeContext::EventTypeContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::TypeContext *HybridSystemParser::EventTypeContext::type() {
    return getRuleContext<HybridSystemParser::TypeContext>(0);
}


size_t HybridSystemParser::EventTypeContext::getRuleIndex() const {
    return HybridSystemParser::RuleEventType;
}

antlrcpp::Any HybridSystemParser::EventTypeContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitEventType(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::EventTypeContext *HybridSystemParser::eventType() {
    EventTypeContext *_localctx = _tracker.createInstance<EventTypeContext>(_ctx, getState());
    enterRule(_localctx, 68, HybridSystemParser::RuleEventType);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        setState(670);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
            case HybridSystemParser::T__42: {
                enterOuterAlt(_localctx, 1);
                setState(668);
                match(HybridSystemParser::T__42);
                break;
            }

            case HybridSystemParser::T__3:
            case HybridSystemParser::T__63:
            case HybridSystemParser::T__64:
            case HybridSystemParser::T__66:
            case HybridSystemParser::T__67:
            case HybridSystemParser::T__68:
            case HybridSystemParser::T__69:
            case HybridSystemParser::T__70:
            case HybridSystemParser::T__71:
            case HybridSystemParser::T__72:
            case HybridSystemParser::IDENTIFIER:
            case HybridSystemParser::RELATIVENAME:
            case HybridSystemParser::ABSOLUTENAME:
            case HybridSystemParser::ROOTNAME: {
                enterOuterAlt(_localctx, 2);
                setState(669);
                type();
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

//----------------- ExpressionsContext ------------------------------------------------------------------

HybridSystemParser::ExpressionsContext::ExpressionsContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::ExpressionContext *> HybridSystemParser::ExpressionsContext::expression() {
    return getRuleContexts<HybridSystemParser::ExpressionContext>();
}

HybridSystemParser::ExpressionContext *HybridSystemParser::ExpressionsContext::expression(size_t i) {
    return getRuleContext<HybridSystemParser::ExpressionContext>(i);
}


size_t HybridSystemParser::ExpressionsContext::getRuleIndex() const {
    return HybridSystemParser::RuleExpressions;
}

antlrcpp::Any HybridSystemParser::ExpressionsContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitExpressions(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::ExpressionsContext *HybridSystemParser::expressions() {
    ExpressionsContext *_localctx = _tracker.createInstance<ExpressionsContext>(_ctx, getState());
    enterRule(_localctx, 70, HybridSystemParser::RuleExpressions);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(672);
        expression();
        setState(677);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == HybridSystemParser::T__22) {
            setState(673);
            match(HybridSystemParser::T__22);
            setState(674);
            expression();
            setState(679);
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

HybridSystemParser::OptExpressionContext::OptExpressionContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::ExpressionContext *HybridSystemParser::OptExpressionContext::expression() {
    return getRuleContext<HybridSystemParser::ExpressionContext>(0);
}


size_t HybridSystemParser::OptExpressionContext::getRuleIndex() const {
    return HybridSystemParser::RuleOptExpression;
}

antlrcpp::Any HybridSystemParser::OptExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitOptExpression(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::OptExpressionContext *HybridSystemParser::optExpression() {
    OptExpressionContext *_localctx = _tracker.createInstance<OptExpressionContext>(_ctx, getState());
    enterRule(_localctx, 72, HybridSystemParser::RuleOptExpression);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(681);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (((((_la - 25) & ~0x3fULL) == 0) &&
             ((1ULL << (_la - 25)) & ((1ULL << (HybridSystemParser::T__24 - 25))
                                      | (1ULL << (HybridSystemParser::T__26 - 25))
                                      | (1ULL << (HybridSystemParser::T__29 - 25))
                                      | (1ULL << (HybridSystemParser::T__48 - 25))
                                      | (1ULL << (HybridSystemParser::T__49 - 25))
                                      | (1ULL << (HybridSystemParser::T__50 - 25))
                                      | (1ULL << (HybridSystemParser::T__51 - 25))
                                      | (1ULL << (HybridSystemParser::T__52 - 25))
                                      | (1ULL << (HybridSystemParser::T__54 - 25))
                                      | (1ULL << (HybridSystemParser::T__55 - 25))
                                      | (1ULL << (HybridSystemParser::T__56 - 25))
                                      | (1ULL << (HybridSystemParser::T__57 - 25))
                                      | (1ULL << (HybridSystemParser::T__59 - 25))
                                      | (1ULL << (HybridSystemParser::T__60 - 25))
                                      | (1ULL << (HybridSystemParser::T__61 - 25))
                                      | (1ULL << (HybridSystemParser::T__76 - 25))
                                      | (1ULL << (HybridSystemParser::T__77 - 25))
                                      | (1ULL << (HybridSystemParser::T__78 - 25))
                                      | (1ULL << (HybridSystemParser::T__79 - 25))
                                      | (1ULL << (HybridSystemParser::T__80 - 25))
                                      | (1ULL << (HybridSystemParser::T__81 - 25))
                                      | (1ULL << (HybridSystemParser::T__82 - 25))
                                      | (1ULL << (HybridSystemParser::T__83 - 25))
                                      | (1ULL << (HybridSystemParser::T__84 - 25))
                                      | (1ULL << (HybridSystemParser::T__85 - 25))
                                      | (1ULL << (HybridSystemParser::T__86 - 25))
                                      | (1ULL << (HybridSystemParser::T__87 - 25)))) != 0) ||
            ((((_la - 89) & ~0x3fULL) == 0) &&
             ((1ULL << (_la - 89)) & ((1ULL << (HybridSystemParser::T__88 - 89))
                                      | (1ULL << (HybridSystemParser::T__89 - 89))
                                      | (1ULL << (HybridSystemParser::T__90 - 89))
                                      | (1ULL << (HybridSystemParser::T__91 - 89))
                                      | (1ULL << (HybridSystemParser::T__92 - 89))
                                      | (1ULL << (HybridSystemParser::T__93 - 89))
                                      | (1ULL << (HybridSystemParser::T__94 - 89))
                                      | (1ULL << (HybridSystemParser::T__95 - 89))
                                      | (1ULL << (HybridSystemParser::T__96 - 89))
                                      | (1ULL << (HybridSystemParser::T__97 - 89))
                                      | (1ULL << (HybridSystemParser::T__98 - 89))
                                      | (1ULL << (HybridSystemParser::T__99 - 89))
                                      | (1ULL << (HybridSystemParser::T__100 - 89))
                                      | (1ULL << (HybridSystemParser::T__101 - 89))
                                      | (1ULL << (HybridSystemParser::T__102 - 89))
                                      | (1ULL << (HybridSystemParser::T__103 - 89))
                                      | (1ULL << (HybridSystemParser::T__104 - 89))
                                      | (1ULL << (HybridSystemParser::T__105 - 89))
                                      | (1ULL << (HybridSystemParser::T__106 - 89))
                                      | (1ULL << (HybridSystemParser::T__107 - 89))
                                      | (1ULL << (HybridSystemParser::NUMBER - 89))
                                      | (1ULL << (HybridSystemParser::REALNUMBER - 89))
                                      | (1ULL << (HybridSystemParser::STRING - 89))
                                      | (1ULL << (HybridSystemParser::IDENTIFIER - 89))
                                      | (1ULL << (HybridSystemParser::RELATIVENAME - 89))
                                      | (1ULL << (HybridSystemParser::ABSOLUTENAME - 89))
                                      | (1ULL << (HybridSystemParser::ROOTNAME - 89)))) != 0)) {
            setState(680);
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

HybridSystemParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::OrExpressionContext *> HybridSystemParser::ExpressionContext::orExpression() {
    return getRuleContexts<HybridSystemParser::OrExpressionContext>();
}

HybridSystemParser::OrExpressionContext *HybridSystemParser::ExpressionContext::orExpression(size_t i) {
    return getRuleContext<HybridSystemParser::OrExpressionContext>(i);
}


size_t HybridSystemParser::ExpressionContext::getRuleIndex() const {
    return HybridSystemParser::RuleExpression;
}

antlrcpp::Any HybridSystemParser::ExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitExpression(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::ExpressionContext *HybridSystemParser::expression() {
    ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
    enterRule(_localctx, 74, HybridSystemParser::RuleExpression);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        setState(692);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx)) {
            case 1: {
                enterOuterAlt(_localctx, 1);
                setState(683);
                orExpression();
                break;
            }

            case 2: {
                enterOuterAlt(_localctx, 2);
                setState(684);
                orExpression();
                setState(685);
                match(HybridSystemParser::T__43);
                setState(686);
                orExpression();
                break;
            }

            case 3: {
                enterOuterAlt(_localctx, 3);
                setState(688);
                orExpression();
                setState(689);
                match(HybridSystemParser::T__44);
                setState(690);
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

HybridSystemParser::EquationsContext::EquationsContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::EquationContext *> HybridSystemParser::EquationsContext::equation() {
    return getRuleContexts<HybridSystemParser::EquationContext>();
}

HybridSystemParser::EquationContext *HybridSystemParser::EquationsContext::equation(size_t i) {
    return getRuleContext<HybridSystemParser::EquationContext>(i);
}


size_t HybridSystemParser::EquationsContext::getRuleIndex() const {
    return HybridSystemParser::RuleEquations;
}

antlrcpp::Any HybridSystemParser::EquationsContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitEquations(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::EquationsContext *HybridSystemParser::equations() {
    EquationsContext *_localctx = _tracker.createInstance<EquationsContext>(_ctx, getState());
    enterRule(_localctx, 76, HybridSystemParser::RuleEquations);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(694);
        equation();
        setState(699);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == HybridSystemParser::T__22) {
            setState(695);
            match(HybridSystemParser::T__22);
            setState(696);
            equation();
            setState(701);
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

HybridSystemParser::EquationContext::EquationContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}


size_t HybridSystemParser::EquationContext::getRuleIndex() const {
    return HybridSystemParser::RuleEquation;
}

void HybridSystemParser::EquationContext::copyFrom(EquationContext *ctx) {
    ParserRuleContext::copyFrom(ctx);
}

//----------------- EquationDerivateContext ------------------------------------------------------------------

HybridSystemParser::IdentifierContext *HybridSystemParser::EquationDerivateContext::identifier() {
    return getRuleContext<HybridSystemParser::IdentifierContext>(0);
}

HybridSystemParser::ExpressionContext *HybridSystemParser::EquationDerivateContext::expression() {
    return getRuleContext<HybridSystemParser::ExpressionContext>(0);
}

HybridSystemParser::EquationDerivateContext::EquationDerivateContext(EquationContext *ctx) { copyFrom(ctx); }

antlrcpp::Any HybridSystemParser::EquationDerivateContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitEquationDerivate(this);
    else
        return visitor->visitChildren(this);
}
//----------------- EquationNonDerivateContext ------------------------------------------------------------------

HybridSystemParser::IdentifierContext *HybridSystemParser::EquationNonDerivateContext::identifier() {
    return getRuleContext<HybridSystemParser::IdentifierContext>(0);
}

HybridSystemParser::ExpressionContext *HybridSystemParser::EquationNonDerivateContext::expression() {
    return getRuleContext<HybridSystemParser::ExpressionContext>(0);
}

HybridSystemParser::EquationNonDerivateContext::EquationNonDerivateContext(EquationContext *ctx) { copyFrom(ctx); }

antlrcpp::Any HybridSystemParser::EquationNonDerivateContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitEquationNonDerivate(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::EquationContext *HybridSystemParser::equation() {
    EquationContext *_localctx = _tracker.createInstance<EquationContext>(_ctx, getState());
    enterRule(_localctx, 78, HybridSystemParser::RuleEquation);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        setState(711);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx)) {
            case 1: {
                _localctx = dynamic_cast<EquationContext *>(_tracker.createInstance<HybridSystemParser::EquationDerivateContext>(
                        _localctx));
                enterOuterAlt(_localctx, 1);
                setState(702);
                identifier();
                setState(703);
                match(HybridSystemParser::T__45);
                setState(704);
                match(HybridSystemParser::T__23);
                setState(705);
                expression();
                break;
            }

            case 2: {
                _localctx = dynamic_cast<EquationContext *>(_tracker.createInstance<HybridSystemParser::EquationNonDerivateContext>(
                        _localctx));
                enterOuterAlt(_localctx, 2);
                setState(707);
                identifier();
                setState(708);
                match(HybridSystemParser::T__23);
                setState(709);
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

HybridSystemParser::OrExpressionContext::OrExpressionContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::AndExpressionContext *> HybridSystemParser::OrExpressionContext::andExpression() {
    return getRuleContexts<HybridSystemParser::AndExpressionContext>();
}

HybridSystemParser::AndExpressionContext *HybridSystemParser::OrExpressionContext::andExpression(size_t i) {
    return getRuleContext<HybridSystemParser::AndExpressionContext>(i);
}


size_t HybridSystemParser::OrExpressionContext::getRuleIndex() const {
    return HybridSystemParser::RuleOrExpression;
}

antlrcpp::Any HybridSystemParser::OrExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitOrExpression(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::OrExpressionContext *HybridSystemParser::orExpression() {
    OrExpressionContext *_localctx = _tracker.createInstance<OrExpressionContext>(_ctx, getState());
    enterRule(_localctx, 80, HybridSystemParser::RuleOrExpression);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(713);
        andExpression();
        setState(718);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == HybridSystemParser::T__46) {
            setState(714);
            match(HybridSystemParser::T__46);
            setState(715);
            andExpression();
            setState(720);
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

HybridSystemParser::AndExpressionContext::AndExpressionContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::CompareExpressionContext *>
HybridSystemParser::AndExpressionContext::compareExpression() {
    return getRuleContexts<HybridSystemParser::CompareExpressionContext>();
}

HybridSystemParser::CompareExpressionContext *HybridSystemParser::AndExpressionContext::compareExpression(size_t i) {
    return getRuleContext<HybridSystemParser::CompareExpressionContext>(i);
}


size_t HybridSystemParser::AndExpressionContext::getRuleIndex() const {
    return HybridSystemParser::RuleAndExpression;
}

antlrcpp::Any HybridSystemParser::AndExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitAndExpression(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::AndExpressionContext *HybridSystemParser::andExpression() {
    AndExpressionContext *_localctx = _tracker.createInstance<AndExpressionContext>(_ctx, getState());
    enterRule(_localctx, 82, HybridSystemParser::RuleAndExpression);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(721);
        compareExpression();
        setState(726);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == HybridSystemParser::T__47) {
            setState(722);
            match(HybridSystemParser::T__47);
            setState(723);
            compareExpression();
            setState(728);
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

HybridSystemParser::CompareExpressionContext::CompareExpressionContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::AddExpressionContext *> HybridSystemParser::CompareExpressionContext::addExpression() {
    return getRuleContexts<HybridSystemParser::AddExpressionContext>();
}

HybridSystemParser::AddExpressionContext *HybridSystemParser::CompareExpressionContext::addExpression(size_t i) {
    return getRuleContext<HybridSystemParser::AddExpressionContext>(i);
}

std::vector<tree::TerminalNode *> HybridSystemParser::CompareExpressionContext::COMPOP() {
    return getTokens(HybridSystemParser::COMPOP);
}

tree::TerminalNode *HybridSystemParser::CompareExpressionContext::COMPOP(size_t i) {
    return getToken(HybridSystemParser::COMPOP, i);
}


size_t HybridSystemParser::CompareExpressionContext::getRuleIndex() const {
    return HybridSystemParser::RuleCompareExpression;
}

antlrcpp::Any HybridSystemParser::CompareExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitCompareExpression(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::CompareExpressionContext *HybridSystemParser::compareExpression() {
    CompareExpressionContext *_localctx = _tracker.createInstance<CompareExpressionContext>(_ctx, getState());
    enterRule(_localctx, 84, HybridSystemParser::RuleCompareExpression);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(729);
        addExpression();
        setState(734);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == HybridSystemParser::COMPOP) {
            setState(730);
            match(HybridSystemParser::COMPOP);
            setState(731);
            addExpression();
            setState(736);
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

HybridSystemParser::AddExpressionContext::AddExpressionContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::MulExpressionContext *> HybridSystemParser::AddExpressionContext::mulExpression() {
    return getRuleContexts<HybridSystemParser::MulExpressionContext>();
}

HybridSystemParser::MulExpressionContext *HybridSystemParser::AddExpressionContext::mulExpression(size_t i) {
    return getRuleContext<HybridSystemParser::MulExpressionContext>(i);
}

std::vector<tree::TerminalNode *> HybridSystemParser::AddExpressionContext::ADDOP() {
    return getTokens(HybridSystemParser::ADDOP);
}

tree::TerminalNode *HybridSystemParser::AddExpressionContext::ADDOP(size_t i) {
    return getToken(HybridSystemParser::ADDOP, i);
}


size_t HybridSystemParser::AddExpressionContext::getRuleIndex() const {
    return HybridSystemParser::RuleAddExpression;
}

antlrcpp::Any HybridSystemParser::AddExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitAddExpression(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::AddExpressionContext *HybridSystemParser::addExpression() {
    AddExpressionContext *_localctx = _tracker.createInstance<AddExpressionContext>(_ctx, getState());
    enterRule(_localctx, 86, HybridSystemParser::RuleAddExpression);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(737);
        mulExpression();
        setState(742);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == HybridSystemParser::ADDOP) {
            setState(738);
            match(HybridSystemParser::ADDOP);
            setState(739);
            mulExpression();
            setState(744);
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

HybridSystemParser::MulExpressionContext::MulExpressionContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::UnaryExpressionContext *> HybridSystemParser::MulExpressionContext::unaryExpression() {
    return getRuleContexts<HybridSystemParser::UnaryExpressionContext>();
}

HybridSystemParser::UnaryExpressionContext *HybridSystemParser::MulExpressionContext::unaryExpression(size_t i) {
    return getRuleContext<HybridSystemParser::UnaryExpressionContext>(i);
}

std::vector<tree::TerminalNode *> HybridSystemParser::MulExpressionContext::MULOP() {
    return getTokens(HybridSystemParser::MULOP);
}

tree::TerminalNode *HybridSystemParser::MulExpressionContext::MULOP(size_t i) {
    return getToken(HybridSystemParser::MULOP, i);
}


size_t HybridSystemParser::MulExpressionContext::getRuleIndex() const {
    return HybridSystemParser::RuleMulExpression;
}

antlrcpp::Any HybridSystemParser::MulExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitMulExpression(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::MulExpressionContext *HybridSystemParser::mulExpression() {
    MulExpressionContext *_localctx = _tracker.createInstance<MulExpressionContext>(_ctx, getState());
    enterRule(_localctx, 88, HybridSystemParser::RuleMulExpression);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(745);
        unaryExpression();
        setState(750);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == HybridSystemParser::MULOP) {
            setState(746);
            match(HybridSystemParser::MULOP);
            setState(747);
            unaryExpression();
            setState(752);
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

HybridSystemParser::UnaryExpressionContext::UnaryExpressionContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}


size_t HybridSystemParser::UnaryExpressionContext::getRuleIndex() const {
    return HybridSystemParser::RuleUnaryExpression;
}

void HybridSystemParser::UnaryExpressionContext::copyFrom(UnaryExpressionContext *ctx) {
    ParserRuleContext::copyFrom(ctx);
}

//----------------- UnaryExprContext ------------------------------------------------------------------

HybridSystemParser::UnaryExpressionContext *HybridSystemParser::UnaryExprContext::unaryExpression() {
    return getRuleContext<HybridSystemParser::UnaryExpressionContext>(0);
}

HybridSystemParser::UnaryExprContext::UnaryExprContext(UnaryExpressionContext *ctx) { copyFrom(ctx); }

antlrcpp::Any HybridSystemParser::UnaryExprContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitUnaryExpr(this);
    else
        return visitor->visitChildren(this);
}
//----------------- UnaryExprFuncContext ------------------------------------------------------------------

HybridSystemParser::FuncExpressionContext *HybridSystemParser::UnaryExprFuncContext::funcExpression() {
    return getRuleContext<HybridSystemParser::FuncExpressionContext>(0);
}

HybridSystemParser::UnaryExprFuncContext::UnaryExprFuncContext(UnaryExpressionContext *ctx) { copyFrom(ctx); }

antlrcpp::Any HybridSystemParser::UnaryExprFuncContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitUnaryExprFunc(this);
    else
        return visitor->visitChildren(this);
}
//----------------- UnaryExprMinusContext ------------------------------------------------------------------

HybridSystemParser::UnaryExpressionContext *HybridSystemParser::UnaryExprMinusContext::unaryExpression() {
    return getRuleContext<HybridSystemParser::UnaryExpressionContext>(0);
}

HybridSystemParser::UnaryExprMinusContext::UnaryExprMinusContext(UnaryExpressionContext *ctx) { copyFrom(ctx); }

antlrcpp::Any HybridSystemParser::UnaryExprMinusContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitUnaryExprMinus(this);
    else
        return visitor->visitChildren(this);
}
//----------------- UnaryExprPlusContext ------------------------------------------------------------------

HybridSystemParser::UnaryExpressionContext *HybridSystemParser::UnaryExprPlusContext::unaryExpression() {
    return getRuleContext<HybridSystemParser::UnaryExpressionContext>(0);
}

HybridSystemParser::UnaryExprPlusContext::UnaryExprPlusContext(UnaryExpressionContext *ctx) { copyFrom(ctx); }

antlrcpp::Any HybridSystemParser::UnaryExprPlusContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitUnaryExprPlus(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::UnaryExpressionContext *HybridSystemParser::unaryExpression() {
    UnaryExpressionContext *_localctx = _tracker.createInstance<UnaryExpressionContext>(_ctx, getState());
    enterRule(_localctx, 90, HybridSystemParser::RuleUnaryExpression);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        setState(762);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
            case HybridSystemParser::T__24:
            case HybridSystemParser::T__26:
            case HybridSystemParser::T__29:
            case HybridSystemParser::T__52:
            case HybridSystemParser::T__54:
            case HybridSystemParser::T__55:
            case HybridSystemParser::T__56:
            case HybridSystemParser::T__57:
            case HybridSystemParser::T__59:
            case HybridSystemParser::T__60:
            case HybridSystemParser::T__61:
            case HybridSystemParser::T__76:
            case HybridSystemParser::T__77:
            case HybridSystemParser::T__78:
            case HybridSystemParser::T__79:
            case HybridSystemParser::T__80:
            case HybridSystemParser::T__81:
            case HybridSystemParser::T__82:
            case HybridSystemParser::T__83:
            case HybridSystemParser::T__84:
            case HybridSystemParser::T__85:
            case HybridSystemParser::T__86:
            case HybridSystemParser::T__87:
            case HybridSystemParser::T__88:
            case HybridSystemParser::T__89:
            case HybridSystemParser::T__90:
            case HybridSystemParser::T__91:
            case HybridSystemParser::T__92:
            case HybridSystemParser::T__93:
            case HybridSystemParser::T__94:
            case HybridSystemParser::T__95:
            case HybridSystemParser::T__96:
            case HybridSystemParser::T__97:
            case HybridSystemParser::T__98:
            case HybridSystemParser::T__99:
            case HybridSystemParser::T__100:
            case HybridSystemParser::T__101:
            case HybridSystemParser::T__102:
            case HybridSystemParser::T__103:
            case HybridSystemParser::T__104:
            case HybridSystemParser::T__105:
            case HybridSystemParser::T__106:
            case HybridSystemParser::T__107:
            case HybridSystemParser::NUMBER:
            case HybridSystemParser::REALNUMBER:
            case HybridSystemParser::STRING:
            case HybridSystemParser::IDENTIFIER:
            case HybridSystemParser::RELATIVENAME:
            case HybridSystemParser::ABSOLUTENAME:
            case HybridSystemParser::ROOTNAME: {
                _localctx = dynamic_cast<UnaryExpressionContext *>(_tracker.createInstance<HybridSystemParser::UnaryExprFuncContext>(
                        _localctx));
                enterOuterAlt(_localctx, 1);
                setState(753);
                funcExpression();
                break;
            }

            case HybridSystemParser::T__48: {
                _localctx = dynamic_cast<UnaryExpressionContext *>(_tracker.createInstance<HybridSystemParser::UnaryExprMinusContext>(
                        _localctx));
                enterOuterAlt(_localctx, 2);
                setState(754);
                match(HybridSystemParser::T__48);
                setState(755);
                unaryExpression();
                break;
            }

            case HybridSystemParser::T__49: {
                _localctx = dynamic_cast<UnaryExpressionContext *>(_tracker.createInstance<HybridSystemParser::UnaryExprPlusContext>(
                        _localctx));
                enterOuterAlt(_localctx, 3);
                setState(756);
                match(HybridSystemParser::T__49);
                setState(757);
                unaryExpression();
                break;
            }

            case HybridSystemParser::T__50: {
                _localctx = dynamic_cast<UnaryExpressionContext *>(_tracker.createInstance<HybridSystemParser::UnaryExprContext>(
                        _localctx));
                enterOuterAlt(_localctx, 4);
                setState(758);
                match(HybridSystemParser::T__50);
                setState(759);
                unaryExpression();
                break;
            }

            case HybridSystemParser::T__51: {
                _localctx = dynamic_cast<UnaryExpressionContext *>(_tracker.createInstance<HybridSystemParser::UnaryExprContext>(
                        _localctx));
                enterOuterAlt(_localctx, 5);
                setState(760);
                match(HybridSystemParser::T__51);
                setState(761);
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

HybridSystemParser::FuncExpressionContext::FuncExpressionContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::ExpressionFactorContext *HybridSystemParser::FuncExpressionContext::expressionFactor() {
    return getRuleContext<HybridSystemParser::ExpressionFactorContext>(0);
}

HybridSystemParser::StdLibFunctionContext *HybridSystemParser::FuncExpressionContext::stdLibFunction() {
    return getRuleContext<HybridSystemParser::StdLibFunctionContext>(0);
}

std::vector<HybridSystemParser::ExpressionsContext *> HybridSystemParser::FuncExpressionContext::expressions() {
    return getRuleContexts<HybridSystemParser::ExpressionsContext>();
}

HybridSystemParser::ExpressionsContext *HybridSystemParser::FuncExpressionContext::expressions(size_t i) {
    return getRuleContext<HybridSystemParser::ExpressionsContext>(i);
}

std::vector<HybridSystemParser::OptExpressionContext *> HybridSystemParser::FuncExpressionContext::optExpression() {
    return getRuleContexts<HybridSystemParser::OptExpressionContext>();
}

HybridSystemParser::OptExpressionContext *HybridSystemParser::FuncExpressionContext::optExpression(size_t i) {
    return getRuleContext<HybridSystemParser::OptExpressionContext>(i);
}


size_t HybridSystemParser::FuncExpressionContext::getRuleIndex() const {
    return HybridSystemParser::RuleFuncExpression;
}

antlrcpp::Any HybridSystemParser::FuncExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitFuncExpression(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::FuncExpressionContext *HybridSystemParser::funcExpression() {
    FuncExpressionContext *_localctx = _tracker.createInstance<FuncExpressionContext>(_ctx, getState());
    enterRule(_localctx, 92, HybridSystemParser::RuleFuncExpression);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        size_t alt;
        enterOuterAlt(_localctx, 1);
        setState(774);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx)) {
            case 1: {
                setState(764);
                expressionFactor();
                break;
            }

            case 2: {
                setState(765);
                stdLibFunction();
                setState(766);
                match(HybridSystemParser::T__26);
                setState(767);
                match(HybridSystemParser::T__27);
                break;
            }

            case 3: {
                setState(769);
                stdLibFunction();
                setState(770);
                match(HybridSystemParser::T__26);
                setState(771);
                expressions();
                setState(772);
                match(HybridSystemParser::T__27);
                break;
            }

        }
        setState(794);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
            if (alt == 1) {
                setState(792);
                _errHandler->sync(this);
                switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 46, _ctx)) {
                    case 1: {
                        setState(776);
                        match(HybridSystemParser::T__52);
                        setState(777);
                        expressions();
                        setState(778);
                        match(HybridSystemParser::T__53);
                        break;
                    }

                    case 2: {
                        setState(780);
                        match(HybridSystemParser::T__52);
                        setState(781);
                        optExpression();
                        setState(782);
                        match(HybridSystemParser::T__4);
                        setState(783);
                        optExpression();
                        setState(784);
                        match(HybridSystemParser::T__53);
                        break;
                    }

                    case 3: {
                        setState(786);
                        match(HybridSystemParser::T__26);
                        setState(787);
                        match(HybridSystemParser::T__27);
                        break;
                    }

                    case 4: {
                        setState(788);
                        match(HybridSystemParser::T__26);
                        setState(789);
                        expressions();
                        setState(790);
                        match(HybridSystemParser::T__27);
                        break;
                    }

                }
            }
            setState(796);
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx);
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

HybridSystemParser::ExpressionFactorContext::ExpressionFactorContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}


size_t HybridSystemParser::ExpressionFactorContext::getRuleIndex() const {
    return HybridSystemParser::RuleExpressionFactor;
}

void HybridSystemParser::ExpressionFactorContext::copyFrom(ExpressionFactorContext *ctx) {
    ParserRuleContext::copyFrom(ctx);
}

//----------------- ExprFactNumberContext ------------------------------------------------------------------

tree::TerminalNode *HybridSystemParser::ExprFactNumberContext::NUMBER() {
    return getToken(HybridSystemParser::NUMBER, 0);
}

HybridSystemParser::ExprFactNumberContext::ExprFactNumberContext(ExpressionFactorContext *ctx) { copyFrom(ctx); }

antlrcpp::Any HybridSystemParser::ExprFactNumberContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitExprFactNumber(this);
    else
        return visitor->visitChildren(this);
}
//----------------- ExprFactContext ------------------------------------------------------------------

HybridSystemParser::StringTokenContext *HybridSystemParser::ExprFactContext::stringToken() {
    return getRuleContext<HybridSystemParser::StringTokenContext>(0);
}

HybridSystemParser::ExpressionsContext *HybridSystemParser::ExprFactContext::expressions() {
    return getRuleContext<HybridSystemParser::ExpressionsContext>(0);
}

HybridSystemParser::NonEmptySetExpressionContext *HybridSystemParser::ExprFactContext::nonEmptySetExpression() {
    return getRuleContext<HybridSystemParser::NonEmptySetExpressionContext>(0);
}

HybridSystemParser::DictPairsContext *HybridSystemParser::ExprFactContext::dictPairs() {
    return getRuleContext<HybridSystemParser::DictPairsContext>(0);
}

std::vector<HybridSystemParser::ExpressionContext *> HybridSystemParser::ExprFactContext::expression() {
    return getRuleContexts<HybridSystemParser::ExpressionContext>();
}

HybridSystemParser::ExpressionContext *HybridSystemParser::ExprFactContext::expression(size_t i) {
    return getRuleContext<HybridSystemParser::ExpressionContext>(i);
}

HybridSystemParser::TypeContext *HybridSystemParser::ExprFactContext::type() {
    return getRuleContext<HybridSystemParser::TypeContext>(0);
}

HybridSystemParser::ExpressionFactorContext *HybridSystemParser::ExprFactContext::expressionFactor() {
    return getRuleContext<HybridSystemParser::ExpressionFactorContext>(0);
}

HybridSystemParser::OptElifExprsContext *HybridSystemParser::ExprFactContext::optElifExprs() {
    return getRuleContext<HybridSystemParser::OptElifExprsContext>(0);
}

HybridSystemParser::SwitchBodyContext *HybridSystemParser::ExprFactContext::switchBody() {
    return getRuleContext<HybridSystemParser::SwitchBodyContext>(0);
}

HybridSystemParser::NameContext *HybridSystemParser::ExprFactContext::name() {
    return getRuleContext<HybridSystemParser::NameContext>(0);
}

HybridSystemParser::ExprFactContext::ExprFactContext(ExpressionFactorContext *ctx) { copyFrom(ctx); }

antlrcpp::Any HybridSystemParser::ExprFactContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitExprFact(this);
    else
        return visitor->visitChildren(this);
}
//----------------- ExprFactRealNumberContext ------------------------------------------------------------------

tree::TerminalNode *HybridSystemParser::ExprFactRealNumberContext::REALNUMBER() {
    return getToken(HybridSystemParser::REALNUMBER, 0);
}

HybridSystemParser::ExprFactRealNumberContext::ExprFactRealNumberContext(ExpressionFactorContext *ctx) {
    copyFrom(ctx);
}

antlrcpp::Any HybridSystemParser::ExprFactRealNumberContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitExprFactRealNumber(this);
    else
        return visitor->visitChildren(this);
}
//----------------- ExprFactNameContext ------------------------------------------------------------------

HybridSystemParser::NameContext *HybridSystemParser::ExprFactNameContext::name() {
    return getRuleContext<HybridSystemParser::NameContext>(0);
}

HybridSystemParser::ExprFactNameContext::ExprFactNameContext(ExpressionFactorContext *ctx) { copyFrom(ctx); }

antlrcpp::Any HybridSystemParser::ExprFactNameContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitExprFactName(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::ExpressionFactorContext *HybridSystemParser::expressionFactor() {
    ExpressionFactorContext *_localctx = _tracker.createInstance<ExpressionFactorContext>(_ctx, getState());
    enterRule(_localctx, 94, HybridSystemParser::RuleExpressionFactor);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        setState(852);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 48, _ctx)) {
            case 1: {
                _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<HybridSystemParser::ExprFactContext>(
                        _localctx));
                enterOuterAlt(_localctx, 1);
                setState(797);
                match(HybridSystemParser::T__54);
                break;
            }

            case 2: {
                _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<HybridSystemParser::ExprFactContext>(
                        _localctx));
                enterOuterAlt(_localctx, 2);
                setState(798);
                match(HybridSystemParser::T__55);
                break;
            }

            case 3: {
                _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<HybridSystemParser::ExprFactNumberContext>(
                        _localctx));
                enterOuterAlt(_localctx, 3);
                setState(799);
                match(HybridSystemParser::NUMBER);
                break;
            }

            case 4: {
                _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<HybridSystemParser::ExprFactRealNumberContext>(
                        _localctx));
                enterOuterAlt(_localctx, 4);
                setState(800);
                match(HybridSystemParser::REALNUMBER);
                break;
            }

            case 5: {
                _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<HybridSystemParser::ExprFactNameContext>(
                        _localctx));
                enterOuterAlt(_localctx, 5);
                setState(801);
                name();
                break;
            }

            case 6: {
                _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<HybridSystemParser::ExprFactContext>(
                        _localctx));
                enterOuterAlt(_localctx, 6);
                setState(802);
                stringToken();
                break;
            }

            case 7: {
                _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<HybridSystemParser::ExprFactContext>(
                        _localctx));
                enterOuterAlt(_localctx, 7);
                setState(803);
                match(HybridSystemParser::T__56);
                break;
            }

            case 8: {
                _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<HybridSystemParser::ExprFactContext>(
                        _localctx));
                enterOuterAlt(_localctx, 8);
                setState(804);
                match(HybridSystemParser::T__52);
                setState(805);
                match(HybridSystemParser::T__53);
                break;
            }

            case 9: {
                _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<HybridSystemParser::ExprFactContext>(
                        _localctx));
                enterOuterAlt(_localctx, 9);
                setState(806);
                match(HybridSystemParser::T__52);
                setState(807);
                expressions();
                setState(808);
                match(HybridSystemParser::T__53);
                break;
            }

            case 10: {
                _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<HybridSystemParser::ExprFactContext>(
                        _localctx));
                enterOuterAlt(_localctx, 10);
                setState(810);
                match(HybridSystemParser::T__24);
                setState(811);
                match(HybridSystemParser::T__25);
                break;
            }

            case 11: {
                _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<HybridSystemParser::ExprFactContext>(
                        _localctx));
                enterOuterAlt(_localctx, 11);
                setState(812);
                nonEmptySetExpression();
                break;
            }

            case 12: {
                _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<HybridSystemParser::ExprFactContext>(
                        _localctx));
                enterOuterAlt(_localctx, 12);
                setState(813);
                match(HybridSystemParser::T__24);
                setState(814);
                dictPairs();
                setState(815);
                match(HybridSystemParser::T__25);
                break;
            }

            case 13: {
                _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<HybridSystemParser::ExprFactContext>(
                        _localctx));
                enterOuterAlt(_localctx, 13);
                setState(817);
                match(HybridSystemParser::T__26);
                setState(818);
                expression();
                setState(819);
                match(HybridSystemParser::T__22);
                setState(820);
                expression();
                setState(821);
                match(HybridSystemParser::T__27);
                break;
            }

            case 14: {
                _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<HybridSystemParser::ExprFactContext>(
                        _localctx));
                enterOuterAlt(_localctx, 14);
                setState(823);
                match(HybridSystemParser::T__57);
                setState(824);
                type();
                setState(825);
                match(HybridSystemParser::T__58);
                setState(826);
                expressionFactor();
                break;
            }

            case 15: {
                _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<HybridSystemParser::ExprFactContext>(
                        _localctx));
                enterOuterAlt(_localctx, 15);
                setState(828);
                match(HybridSystemParser::T__29);
                setState(829);
                expressions();
                setState(830);
                match(HybridSystemParser::T__4);
                setState(831);
                expression();
                setState(832);
                optElifExprs();
                setState(833);
                match(HybridSystemParser::T__35);
                setState(834);
                expression();
                setState(835);
                match(HybridSystemParser::T__7);
                break;
            }

            case 16: {
                _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<HybridSystemParser::ExprFactContext>(
                        _localctx));
                enterOuterAlt(_localctx, 16);
                setState(837);
                match(HybridSystemParser::T__59);
                setState(838);
                expression();
                setState(839);
                match(HybridSystemParser::T__4);
                setState(840);
                switchBody();
                setState(841);
                match(HybridSystemParser::T__7);
                break;
            }

            case 17: {
                _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<HybridSystemParser::ExprFactContext>(
                        _localctx));
                enterOuterAlt(_localctx, 17);
                setState(843);
                match(HybridSystemParser::T__26);
                setState(844);
                expression();
                setState(845);
                match(HybridSystemParser::T__27);
                break;
            }

            case 18: {
                _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<HybridSystemParser::ExprFactContext>(
                        _localctx));
                enterOuterAlt(_localctx, 18);
                setState(847);
                name();
                setState(848);
                match(HybridSystemParser::T__45);
                break;
            }

            case 19: {
                _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<HybridSystemParser::ExprFactContext>(
                        _localctx));
                enterOuterAlt(_localctx, 19);
                setState(850);
                match(HybridSystemParser::T__60);
                break;
            }

            case 20: {
                _localctx = dynamic_cast<ExpressionFactorContext *>(_tracker.createInstance<HybridSystemParser::ExprFactContext>(
                        _localctx));
                enterOuterAlt(_localctx, 20);
                setState(851);
                match(HybridSystemParser::T__61);
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

HybridSystemParser::NonEmptySetExpressionContext::NonEmptySetExpressionContext(ParserRuleContext *parent,
                                                                               size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::ExpressionsContext *HybridSystemParser::NonEmptySetExpressionContext::expressions() {
    return getRuleContext<HybridSystemParser::ExpressionsContext>(0);
}


size_t HybridSystemParser::NonEmptySetExpressionContext::getRuleIndex() const {
    return HybridSystemParser::RuleNonEmptySetExpression;
}

antlrcpp::Any HybridSystemParser::NonEmptySetExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitNonEmptySetExpression(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::NonEmptySetExpressionContext *HybridSystemParser::nonEmptySetExpression() {
    NonEmptySetExpressionContext *_localctx = _tracker.createInstance<NonEmptySetExpressionContext>(_ctx, getState());
    enterRule(_localctx, 96, HybridSystemParser::RuleNonEmptySetExpression);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(854);
        match(HybridSystemParser::T__24);
        setState(855);
        expressions();
        setState(856);
        match(HybridSystemParser::T__25);

    }
    catch (RecognitionException &e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- DictPairsContext ------------------------------------------------------------------

HybridSystemParser::DictPairsContext::DictPairsContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::ExpressionContext *> HybridSystemParser::DictPairsContext::expression() {
    return getRuleContexts<HybridSystemParser::ExpressionContext>();
}

HybridSystemParser::ExpressionContext *HybridSystemParser::DictPairsContext::expression(size_t i) {
    return getRuleContext<HybridSystemParser::ExpressionContext>(i);
}


size_t HybridSystemParser::DictPairsContext::getRuleIndex() const {
    return HybridSystemParser::RuleDictPairs;
}

antlrcpp::Any HybridSystemParser::DictPairsContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitDictPairs(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::DictPairsContext *HybridSystemParser::dictPairs() {
    DictPairsContext *_localctx = _tracker.createInstance<DictPairsContext>(_ctx, getState());
    enterRule(_localctx, 98, HybridSystemParser::RuleDictPairs);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(858);
        expression();
        setState(859);
        match(HybridSystemParser::T__4);
        setState(860);
        expression();

        setState(861);
        match(HybridSystemParser::T__22);
        setState(862);
        expression();
        setState(863);
        match(HybridSystemParser::T__4);
        setState(864);
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

HybridSystemParser::OptElifExprsContext::OptElifExprsContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::ExpressionContext *> HybridSystemParser::OptElifExprsContext::expression() {
    return getRuleContexts<HybridSystemParser::ExpressionContext>();
}

HybridSystemParser::ExpressionContext *HybridSystemParser::OptElifExprsContext::expression(size_t i) {
    return getRuleContext<HybridSystemParser::ExpressionContext>(i);
}


size_t HybridSystemParser::OptElifExprsContext::getRuleIndex() const {
    return HybridSystemParser::RuleOptElifExprs;
}

antlrcpp::Any HybridSystemParser::OptElifExprsContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitOptElifExprs(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::OptElifExprsContext *HybridSystemParser::optElifExprs() {
    OptElifExprsContext *_localctx = _tracker.createInstance<OptElifExprsContext>(_ctx, getState());
    enterRule(_localctx, 100, HybridSystemParser::RuleOptElifExprs);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(873);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (((((_la - 25) & ~0x3fULL) == 0) &&
                ((1ULL << (_la - 25)) & ((1ULL << (HybridSystemParser::T__24 - 25))
                                         | (1ULL << (HybridSystemParser::T__26 - 25))
                                         | (1ULL << (HybridSystemParser::T__29 - 25))
                                         | (1ULL << (HybridSystemParser::T__48 - 25))
                                         | (1ULL << (HybridSystemParser::T__49 - 25))
                                         | (1ULL << (HybridSystemParser::T__50 - 25))
                                         | (1ULL << (HybridSystemParser::T__51 - 25))
                                         | (1ULL << (HybridSystemParser::T__52 - 25))
                                         | (1ULL << (HybridSystemParser::T__54 - 25))
                                         | (1ULL << (HybridSystemParser::T__55 - 25))
                                         | (1ULL << (HybridSystemParser::T__56 - 25))
                                         | (1ULL << (HybridSystemParser::T__57 - 25))
                                         | (1ULL << (HybridSystemParser::T__59 - 25))
                                         | (1ULL << (HybridSystemParser::T__60 - 25))
                                         | (1ULL << (HybridSystemParser::T__61 - 25))
                                         | (1ULL << (HybridSystemParser::T__76 - 25))
                                         | (1ULL << (HybridSystemParser::T__77 - 25))
                                         | (1ULL << (HybridSystemParser::T__78 - 25))
                                         | (1ULL << (HybridSystemParser::T__79 - 25))
                                         | (1ULL << (HybridSystemParser::T__80 - 25))
                                         | (1ULL << (HybridSystemParser::T__81 - 25))
                                         | (1ULL << (HybridSystemParser::T__82 - 25))
                                         | (1ULL << (HybridSystemParser::T__83 - 25))
                                         | (1ULL << (HybridSystemParser::T__84 - 25))
                                         | (1ULL << (HybridSystemParser::T__85 - 25))
                                         | (1ULL << (HybridSystemParser::T__86 - 25))
                                         | (1ULL << (HybridSystemParser::T__87 - 25)))) != 0) ||
               ((((_la - 89) & ~0x3fULL) == 0) &&
                ((1ULL << (_la - 89)) & ((1ULL << (HybridSystemParser::T__88 - 89))
                                         | (1ULL << (HybridSystemParser::T__89 - 89))
                                         | (1ULL << (HybridSystemParser::T__90 - 89))
                                         | (1ULL << (HybridSystemParser::T__91 - 89))
                                         | (1ULL << (HybridSystemParser::T__92 - 89))
                                         | (1ULL << (HybridSystemParser::T__93 - 89))
                                         | (1ULL << (HybridSystemParser::T__94 - 89))
                                         | (1ULL << (HybridSystemParser::T__95 - 89))
                                         | (1ULL << (HybridSystemParser::T__96 - 89))
                                         | (1ULL << (HybridSystemParser::T__97 - 89))
                                         | (1ULL << (HybridSystemParser::T__98 - 89))
                                         | (1ULL << (HybridSystemParser::T__99 - 89))
                                         | (1ULL << (HybridSystemParser::T__100 - 89))
                                         | (1ULL << (HybridSystemParser::T__101 - 89))
                                         | (1ULL << (HybridSystemParser::T__102 - 89))
                                         | (1ULL << (HybridSystemParser::T__103 - 89))
                                         | (1ULL << (HybridSystemParser::T__104 - 89))
                                         | (1ULL << (HybridSystemParser::T__105 - 89))
                                         | (1ULL << (HybridSystemParser::T__106 - 89))
                                         | (1ULL << (HybridSystemParser::T__107 - 89))
                                         | (1ULL << (HybridSystemParser::NUMBER - 89))
                                         | (1ULL << (HybridSystemParser::REALNUMBER - 89))
                                         | (1ULL << (HybridSystemParser::STRING - 89))
                                         | (1ULL << (HybridSystemParser::IDENTIFIER - 89))
                                         | (1ULL << (HybridSystemParser::RELATIVENAME - 89))
                                         | (1ULL << (HybridSystemParser::ABSOLUTENAME - 89))
                                         | (1ULL << (HybridSystemParser::ROOTNAME - 89)))) != 0)) {
            setState(866);
            expression();
            setState(867);
            match(HybridSystemParser::T__4);
            setState(868);
            expression();
            setState(869);
            match(HybridSystemParser::T__34);
            setState(875);
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

HybridSystemParser::SwitchBodyContext::SwitchBodyContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::SwitchCasesContext *HybridSystemParser::SwitchBodyContext::switchCases() {
    return getRuleContext<HybridSystemParser::SwitchCasesContext>(0);
}

HybridSystemParser::ExpressionContext *HybridSystemParser::SwitchBodyContext::expression() {
    return getRuleContext<HybridSystemParser::ExpressionContext>(0);
}


size_t HybridSystemParser::SwitchBodyContext::getRuleIndex() const {
    return HybridSystemParser::RuleSwitchBody;
}

antlrcpp::Any HybridSystemParser::SwitchBodyContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitSwitchBody(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::SwitchBodyContext *HybridSystemParser::switchBody() {
    SwitchBodyContext *_localctx = _tracker.createInstance<SwitchBodyContext>(_ctx, getState());
    enterRule(_localctx, 102, HybridSystemParser::RuleSwitchBody);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        setState(883);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx)) {
            case 1: {
                enterOuterAlt(_localctx, 1);
                setState(876);
                switchCases();
                break;
            }

            case 2: {
                enterOuterAlt(_localctx, 2);
                setState(877);
                switchCases();
                setState(878);
                match(HybridSystemParser::T__35);
                setState(879);
                expression();
                break;
            }

            case 3: {
                enterOuterAlt(_localctx, 3);
                setState(881);
                match(HybridSystemParser::T__35);
                setState(882);
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

HybridSystemParser::SwitchCasesContext::SwitchCasesContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::ExpressionContext *> HybridSystemParser::SwitchCasesContext::expression() {
    return getRuleContexts<HybridSystemParser::ExpressionContext>();
}

HybridSystemParser::ExpressionContext *HybridSystemParser::SwitchCasesContext::expression(size_t i) {
    return getRuleContext<HybridSystemParser::ExpressionContext>(i);
}


size_t HybridSystemParser::SwitchCasesContext::getRuleIndex() const {
    return HybridSystemParser::RuleSwitchCases;
}

antlrcpp::Any HybridSystemParser::SwitchCasesContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitSwitchCases(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::SwitchCasesContext *HybridSystemParser::switchCases() {
    SwitchCasesContext *_localctx = _tracker.createInstance<SwitchCasesContext>(_ctx, getState());
    enterRule(_localctx, 104, HybridSystemParser::RuleSwitchCases);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(890);
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
            setState(885);
            match(HybridSystemParser::T__62);
            setState(886);
            expression();
            setState(887);
            match(HybridSystemParser::T__4);
            setState(888);
            expression();
            setState(892);
            _errHandler->sync(this);
            _la = _input->LA(1);
        } while (_la == HybridSystemParser::T__62);

    }
    catch (RecognitionException &e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- TypesContext ------------------------------------------------------------------

HybridSystemParser::TypesContext::TypesContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::TypeContext *> HybridSystemParser::TypesContext::type() {
    return getRuleContexts<HybridSystemParser::TypeContext>();
}

HybridSystemParser::TypeContext *HybridSystemParser::TypesContext::type(size_t i) {
    return getRuleContext<HybridSystemParser::TypeContext>(i);
}


size_t HybridSystemParser::TypesContext::getRuleIndex() const {
    return HybridSystemParser::RuleTypes;
}

antlrcpp::Any HybridSystemParser::TypesContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitTypes(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::TypesContext *HybridSystemParser::types() {
    TypesContext *_localctx = _tracker.createInstance<TypesContext>(_ctx, getState());
    enterRule(_localctx, 106, HybridSystemParser::RuleTypes);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(894);
        type();
        setState(899);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == HybridSystemParser::T__22) {
            setState(895);
            match(HybridSystemParser::T__22);
            setState(896);
            type();
            setState(901);
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

HybridSystemParser::TypeContext::TypeContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::ExpressionContext *> HybridSystemParser::TypeContext::expression() {
    return getRuleContexts<HybridSystemParser::ExpressionContext>();
}

HybridSystemParser::ExpressionContext *HybridSystemParser::TypeContext::expression(size_t i) {
    return getRuleContext<HybridSystemParser::ExpressionContext>(i);
}

std::vector<HybridSystemParser::TypeContext *> HybridSystemParser::TypeContext::type() {
    return getRuleContexts<HybridSystemParser::TypeContext>();
}

HybridSystemParser::TypeContext *HybridSystemParser::TypeContext::type(size_t i) {
    return getRuleContext<HybridSystemParser::TypeContext>(i);
}

HybridSystemParser::FieldsContext *HybridSystemParser::TypeContext::fields() {
    return getRuleContext<HybridSystemParser::FieldsContext>(0);
}

HybridSystemParser::TypesContext *HybridSystemParser::TypeContext::types() {
    return getRuleContext<HybridSystemParser::TypesContext>(0);
}

HybridSystemParser::NameContext *HybridSystemParser::TypeContext::name() {
    return getRuleContext<HybridSystemParser::NameContext>(0);
}


size_t HybridSystemParser::TypeContext::getRuleIndex() const {
    return HybridSystemParser::RuleType;
}

antlrcpp::Any HybridSystemParser::TypeContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitType(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::TypeContext *HybridSystemParser::type() {
    TypeContext *_localctx = _tracker.createInstance<TypeContext>(_ctx, getState());
    enterRule(_localctx, 108, HybridSystemParser::RuleType);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        setState(957);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 53, _ctx)) {
            case 1: {
                enterOuterAlt(_localctx, 1);
                setState(902);
                match(HybridSystemParser::T__63);
                break;
            }

            case 2: {
                enterOuterAlt(_localctx, 2);
                setState(903);
                match(HybridSystemParser::T__64);
                break;
            }

            case 3: {
                enterOuterAlt(_localctx, 3);
                setState(904);
                match(HybridSystemParser::T__64);
                setState(905);
                match(HybridSystemParser::T__52);
                setState(906);
                expression();
                setState(907);
                match(HybridSystemParser::T__65);
                setState(908);
                expression();
                setState(909);
                match(HybridSystemParser::T__53);
                break;
            }

            case 4: {
                enterOuterAlt(_localctx, 4);
                setState(911);
                match(HybridSystemParser::T__66);
                break;
            }

            case 5: {
                enterOuterAlt(_localctx, 5);
                setState(912);
                match(HybridSystemParser::T__67);
                break;
            }

            case 6: {
                enterOuterAlt(_localctx, 6);
                setState(913);
                match(HybridSystemParser::T__68);
                setState(914);
                type();
                break;
            }

            case 7: {
                enterOuterAlt(_localctx, 7);
                setState(915);
                match(HybridSystemParser::T__68);
                setState(916);
                match(HybridSystemParser::T__52);
                setState(917);
                expression();
                setState(918);
                match(HybridSystemParser::T__53);
                setState(919);
                type();
                break;
            }

            case 8: {
                enterOuterAlt(_localctx, 8);
                setState(921);
                match(HybridSystemParser::T__68);
                setState(922);
                match(HybridSystemParser::T__52);
                setState(923);
                expression();
                setState(924);
                match(HybridSystemParser::T__65);
                setState(925);
                expression();
                setState(926);
                match(HybridSystemParser::T__53);
                setState(927);
                type();
                break;
            }

            case 9: {
                enterOuterAlt(_localctx, 9);
                setState(929);
                match(HybridSystemParser::T__69);
                setState(930);
                type();
                break;
            }

            case 10: {
                enterOuterAlt(_localctx, 10);
                setState(931);
                match(HybridSystemParser::T__70);
                setState(932);
                match(HybridSystemParser::T__26);
                setState(933);
                type();
                setState(934);
                match(HybridSystemParser::T__4);
                setState(935);
                type();
                setState(936);
                match(HybridSystemParser::T__27);
                break;
            }

            case 11: {
                enterOuterAlt(_localctx, 11);
                setState(938);
                match(HybridSystemParser::T__71);
                setState(939);
                match(HybridSystemParser::T__26);
                setState(940);
                fields();
                setState(941);
                match(HybridSystemParser::T__27);
                break;
            }

            case 12: {
                enterOuterAlt(_localctx, 12);
                setState(943);
                match(HybridSystemParser::T__3);
                setState(944);
                type();
                setState(945);
                match(HybridSystemParser::T__26);
                setState(946);
                match(HybridSystemParser::T__27);
                break;
            }

            case 13: {
                enterOuterAlt(_localctx, 13);
                setState(948);
                match(HybridSystemParser::T__3);
                setState(949);
                type();
                setState(950);
                match(HybridSystemParser::T__26);
                setState(951);
                types();
                setState(952);
                match(HybridSystemParser::T__27);
                break;
            }

            case 14: {
                enterOuterAlt(_localctx, 14);
                setState(954);
                match(HybridSystemParser::T__72);
                setState(955);
                type();
                break;
            }

            case 15: {
                enterOuterAlt(_localctx, 15);
                setState(956);
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

HybridSystemParser::FieldsContext::FieldsContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::FieldContext *> HybridSystemParser::FieldsContext::field() {
    return getRuleContexts<HybridSystemParser::FieldContext>();
}

HybridSystemParser::FieldContext *HybridSystemParser::FieldsContext::field(size_t i) {
    return getRuleContext<HybridSystemParser::FieldContext>(i);
}


size_t HybridSystemParser::FieldsContext::getRuleIndex() const {
    return HybridSystemParser::RuleFields;
}

antlrcpp::Any HybridSystemParser::FieldsContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitFields(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::FieldsContext *HybridSystemParser::fields() {
    FieldsContext *_localctx = _tracker.createInstance<FieldsContext>(_ctx, getState());
    enterRule(_localctx, 110, HybridSystemParser::RuleFields);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(959);
        field();
        setState(964);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == HybridSystemParser::T__22) {
            setState(960);
            match(HybridSystemParser::T__22);
            setState(961);
            field();
            setState(966);
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

HybridSystemParser::FieldContext::FieldContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::TypeContext *HybridSystemParser::FieldContext::type() {
    return getRuleContext<HybridSystemParser::TypeContext>(0);
}

HybridSystemParser::IdentifierContext *HybridSystemParser::FieldContext::identifier() {
    return getRuleContext<HybridSystemParser::IdentifierContext>(0);
}


size_t HybridSystemParser::FieldContext::getRuleIndex() const {
    return HybridSystemParser::RuleField;
}

antlrcpp::Any HybridSystemParser::FieldContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitField(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::FieldContext *HybridSystemParser::field() {
    FieldContext *_localctx = _tracker.createInstance<FieldContext>(_ctx, getState());
    enterRule(_localctx, 112, HybridSystemParser::RuleField);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(967);
        type();
        setState(968);
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

HybridSystemParser::NameSetContext::NameSetContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::NamesContext *HybridSystemParser::NameSetContext::names() {
    return getRuleContext<HybridSystemParser::NamesContext>(0);
}


size_t HybridSystemParser::NameSetContext::getRuleIndex() const {
    return HybridSystemParser::RuleNameSet;
}

antlrcpp::Any HybridSystemParser::NameSetContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitNameSet(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::NameSetContext *HybridSystemParser::nameSet() {
    NameSetContext *_localctx = _tracker.createInstance<NameSetContext>(_ctx, getState());
    enterRule(_localctx, 114, HybridSystemParser::RuleNameSet);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(970);
        match(HybridSystemParser::T__24);
        setState(971);
        names();
        setState(972);
        match(HybridSystemParser::T__25);

    }
    catch (RecognitionException &e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- NamesContext ------------------------------------------------------------------

HybridSystemParser::NamesContext::NamesContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::NameContext *> HybridSystemParser::NamesContext::name() {
    return getRuleContexts<HybridSystemParser::NameContext>();
}

HybridSystemParser::NameContext *HybridSystemParser::NamesContext::name(size_t i) {
    return getRuleContext<HybridSystemParser::NameContext>(i);
}


size_t HybridSystemParser::NamesContext::getRuleIndex() const {
    return HybridSystemParser::RuleNames;
}

antlrcpp::Any HybridSystemParser::NamesContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitNames(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::NamesContext *HybridSystemParser::names() {
    NamesContext *_localctx = _tracker.createInstance<NamesContext>(_ctx, getState());
    enterRule(_localctx, 116, HybridSystemParser::RuleNames);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(974);
        name();
        setState(979);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == HybridSystemParser::T__22) {
            setState(975);
            match(HybridSystemParser::T__22);
            setState(976);
            name();
            setState(981);
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

HybridSystemParser::NameContext::NameContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::IdentifierContext *HybridSystemParser::NameContext::identifier() {
    return getRuleContext<HybridSystemParser::IdentifierContext>(0);
}

tree::TerminalNode *HybridSystemParser::NameContext::RELATIVENAME() {
    return getToken(HybridSystemParser::RELATIVENAME, 0);
}

tree::TerminalNode *HybridSystemParser::NameContext::ABSOLUTENAME() {
    return getToken(HybridSystemParser::ABSOLUTENAME, 0);
}

tree::TerminalNode *HybridSystemParser::NameContext::ROOTNAME() {
    return getToken(HybridSystemParser::ROOTNAME, 0);
}


size_t HybridSystemParser::NameContext::getRuleIndex() const {
    return HybridSystemParser::RuleName;
}

antlrcpp::Any HybridSystemParser::NameContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitName(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::NameContext *HybridSystemParser::name() {
    NameContext *_localctx = _tracker.createInstance<NameContext>(_ctx, getState());
    enterRule(_localctx, 118, HybridSystemParser::RuleName);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        setState(986);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
            case HybridSystemParser::IDENTIFIER: {
                enterOuterAlt(_localctx, 1);
                setState(982);
                identifier();
                break;
            }

            case HybridSystemParser::RELATIVENAME: {
                enterOuterAlt(_localctx, 2);
                setState(983);
                match(HybridSystemParser::RELATIVENAME);
                break;
            }

            case HybridSystemParser::ABSOLUTENAME: {
                enterOuterAlt(_localctx, 3);
                setState(984);
                match(HybridSystemParser::ABSOLUTENAME);
                break;
            }

            case HybridSystemParser::ROOTNAME: {
                enterOuterAlt(_localctx, 4);
                setState(985);
                match(HybridSystemParser::ROOTNAME);
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

HybridSystemParser::OptSupKindContext::OptSupKindContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::SupKindContext *HybridSystemParser::OptSupKindContext::supKind() {
    return getRuleContext<HybridSystemParser::SupKindContext>(0);
}


size_t HybridSystemParser::OptSupKindContext::getRuleIndex() const {
    return HybridSystemParser::RuleOptSupKind;
}

antlrcpp::Any HybridSystemParser::OptSupKindContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitOptSupKind(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::OptSupKindContext *HybridSystemParser::optSupKind() {
    OptSupKindContext *_localctx = _tracker.createInstance<OptSupKindContext>(_ctx, getState());
    enterRule(_localctx, 120, HybridSystemParser::RuleOptSupKind);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(989);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (((((_la - 74) & ~0x3fULL) == 0) &&
             ((1ULL << (_la - 74)) & ((1ULL << (HybridSystemParser::T__73 - 74))
                                      | (1ULL << (HybridSystemParser::T__74 - 74))
                                      | (1ULL << (HybridSystemParser::T__75 - 74)))) != 0)) {
            setState(988);
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

HybridSystemParser::SupKindContext::SupKindContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}


size_t HybridSystemParser::SupKindContext::getRuleIndex() const {
    return HybridSystemParser::RuleSupKind;
}

antlrcpp::Any HybridSystemParser::SupKindContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitSupKind(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::SupKindContext *HybridSystemParser::supKind() {
    SupKindContext *_localctx = _tracker.createInstance<SupKindContext>(_ctx, getState());
    enterRule(_localctx, 122, HybridSystemParser::RuleSupKind);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(991);
        _la = _input->LA(1);
        if (!(((((_la - 74) & ~0x3fULL) == 0) &&
               ((1ULL << (_la - 74)) & ((1ULL << (HybridSystemParser::T__73 - 74))
                                        | (1ULL << (HybridSystemParser::T__74 - 74))
                                        | (1ULL << (HybridSystemParser::T__75 - 74)))) != 0))) {
            _errHandler->recoverInline(this);
        } else {
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

HybridSystemParser::IdentifierContext::IdentifierContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode *HybridSystemParser::IdentifierContext::IDENTIFIER() {
    return getToken(HybridSystemParser::IDENTIFIER, 0);
}


size_t HybridSystemParser::IdentifierContext::getRuleIndex() const {
    return HybridSystemParser::RuleIdentifier;
}

antlrcpp::Any HybridSystemParser::IdentifierContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitIdentifier(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::IdentifierContext *HybridSystemParser::identifier() {
    IdentifierContext *_localctx = _tracker.createInstance<IdentifierContext>(_ctx, getState());
    enterRule(_localctx, 124, HybridSystemParser::RuleIdentifier);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(993);
        match(HybridSystemParser::IDENTIFIER);

    }
    catch (RecognitionException &e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- StringTokenContext ------------------------------------------------------------------

HybridSystemParser::StringTokenContext::StringTokenContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode *HybridSystemParser::StringTokenContext::STRING() {
    return getToken(HybridSystemParser::STRING, 0);
}


size_t HybridSystemParser::StringTokenContext::getRuleIndex() const {
    return HybridSystemParser::RuleStringToken;
}

antlrcpp::Any HybridSystemParser::StringTokenContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitStringToken(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::StringTokenContext *HybridSystemParser::stringToken() {
    StringTokenContext *_localctx = _tracker.createInstance<StringTokenContext>(_ctx, getState());
    enterRule(_localctx, 126, HybridSystemParser::RuleStringToken);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(995);
        match(HybridSystemParser::STRING);

    }
    catch (RecognitionException &e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- StdLibFunctionContext ------------------------------------------------------------------

HybridSystemParser::StdLibFunctionContext::StdLibFunctionContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}


size_t HybridSystemParser::StdLibFunctionContext::getRuleIndex() const {
    return HybridSystemParser::RuleStdLibFunction;
}

antlrcpp::Any HybridSystemParser::StdLibFunctionContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitStdLibFunction(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::StdLibFunctionContext *HybridSystemParser::stdLibFunction() {
    StdLibFunctionContext *_localctx = _tracker.createInstance<StdLibFunctionContext>(_ctx, getState());
    enterRule(_localctx, 128, HybridSystemParser::RuleStdLibFunction);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(997);
        _la = _input->LA(1);
        if (!(((((_la - 77) & ~0x3fULL) == 0) &&
               ((1ULL << (_la - 77)) & ((1ULL << (HybridSystemParser::T__76 - 77))
                                        | (1ULL << (HybridSystemParser::T__77 - 77))
                                        | (1ULL << (HybridSystemParser::T__78 - 77))
                                        | (1ULL << (HybridSystemParser::T__79 - 77))
                                        | (1ULL << (HybridSystemParser::T__80 - 77))
                                        | (1ULL << (HybridSystemParser::T__81 - 77))
                                        | (1ULL << (HybridSystemParser::T__82 - 77))
                                        | (1ULL << (HybridSystemParser::T__83 - 77))
                                        | (1ULL << (HybridSystemParser::T__84 - 77))
                                        | (1ULL << (HybridSystemParser::T__85 - 77))
                                        | (1ULL << (HybridSystemParser::T__86 - 77))
                                        | (1ULL << (HybridSystemParser::T__87 - 77))
                                        | (1ULL << (HybridSystemParser::T__88 - 77))
                                        | (1ULL << (HybridSystemParser::T__89 - 77))
                                        | (1ULL << (HybridSystemParser::T__90 - 77))
                                        | (1ULL << (HybridSystemParser::T__91 - 77))
                                        | (1ULL << (HybridSystemParser::T__92 - 77))
                                        | (1ULL << (HybridSystemParser::T__93 - 77))
                                        | (1ULL << (HybridSystemParser::T__94 - 77))
                                        | (1ULL << (HybridSystemParser::T__95 - 77))
                                        | (1ULL << (HybridSystemParser::T__96 - 77))
                                        | (1ULL << (HybridSystemParser::T__97 - 77))
                                        | (1ULL << (HybridSystemParser::T__98 - 77))
                                        | (1ULL << (HybridSystemParser::T__99 - 77))
                                        | (1ULL << (HybridSystemParser::T__100 - 77))
                                        | (1ULL << (HybridSystemParser::T__101 - 77))
                                        | (1ULL << (HybridSystemParser::T__102 - 77))
                                        | (1ULL << (HybridSystemParser::T__103 - 77))
                                        | (1ULL << (HybridSystemParser::T__104 - 77))
                                        | (1ULL << (HybridSystemParser::T__105 - 77))
                                        | (1ULL << (HybridSystemParser::T__106 - 77))
                                        | (1ULL << (HybridSystemParser::T__107 - 77)))) != 0))) {
            _errHandler->recoverInline(this);
        } else {
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

//----------------- LocationsContext ------------------------------------------------------------------

HybridSystemParser::LocationsContext::LocationsContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::LocationContext *> HybridSystemParser::LocationsContext::location() {
    return getRuleContexts<HybridSystemParser::LocationContext>();
}

HybridSystemParser::LocationContext *HybridSystemParser::LocationsContext::location(size_t i) {
    return getRuleContext<HybridSystemParser::LocationContext>(i);
}


size_t HybridSystemParser::LocationsContext::getRuleIndex() const {
    return HybridSystemParser::RuleLocations;
}

antlrcpp::Any HybridSystemParser::LocationsContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitLocations(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::LocationsContext *HybridSystemParser::locations() {
    LocationsContext *_localctx = _tracker.createInstance<LocationsContext>(_ctx, getState());
    enterRule(_localctx, 130, HybridSystemParser::RuleLocations);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(1000);
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
            setState(999);
            location();
            setState(1002);
            _errHandler->sync(this);
            _la = _input->LA(1);
        } while (_la == HybridSystemParser::T__36);

    }
    catch (RecognitionException &e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- LocationContext ------------------------------------------------------------------

HybridSystemParser::LocationContext::LocationContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}


size_t HybridSystemParser::LocationContext::getRuleIndex() const {
    return HybridSystemParser::RuleLocation;
}

void HybridSystemParser::LocationContext::copyFrom(LocationContext *ctx) {
    ParserRuleContext::copyFrom(ctx);
}

//----------------- LocElemContext ------------------------------------------------------------------

HybridSystemParser::LocationElementsContext *HybridSystemParser::LocElemContext::locationElements() {
    return getRuleContext<HybridSystemParser::LocationElementsContext>(0);
}

HybridSystemParser::LocElemContext::LocElemContext(LocationContext *ctx) { copyFrom(ctx); }

antlrcpp::Any HybridSystemParser::LocElemContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitLocElem(this);
    else
        return visitor->visitChildren(this);
}
//----------------- LocContext ------------------------------------------------------------------

HybridSystemParser::LocContext::LocContext(LocationContext *ctx) { copyFrom(ctx); }

antlrcpp::Any HybridSystemParser::LocContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitLoc(this);
    else
        return visitor->visitChildren(this);
}
//----------------- LocIdElemContext ------------------------------------------------------------------

HybridSystemParser::IdentifierContext *HybridSystemParser::LocIdElemContext::identifier() {
    return getRuleContext<HybridSystemParser::IdentifierContext>(0);
}

HybridSystemParser::LocationElementsContext *HybridSystemParser::LocIdElemContext::locationElements() {
    return getRuleContext<HybridSystemParser::LocationElementsContext>(0);
}

HybridSystemParser::LocIdElemContext::LocIdElemContext(LocationContext *ctx) { copyFrom(ctx); }

antlrcpp::Any HybridSystemParser::LocIdElemContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitLocIdElem(this);
    else
        return visitor->visitChildren(this);
}
//----------------- LocIdContext ------------------------------------------------------------------

HybridSystemParser::IdentifierContext *HybridSystemParser::LocIdContext::identifier() {
    return getRuleContext<HybridSystemParser::IdentifierContext>(0);
}

HybridSystemParser::LocIdContext::LocIdContext(LocationContext *ctx) { copyFrom(ctx); }

antlrcpp::Any HybridSystemParser::LocIdContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitLocId(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::LocationContext *HybridSystemParser::location() {
    LocationContext *_localctx = _tracker.createInstance<LocationContext>(_ctx, getState());
    enterRule(_localctx, 132, HybridSystemParser::RuleLocation);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        setState(1018);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 59, _ctx)) {
            case 1: {
                _localctx = dynamic_cast<LocationContext *>(_tracker.createInstance<HybridSystemParser::LocContext>(
                        _localctx));
                enterOuterAlt(_localctx, 1);
                setState(1004);
                match(HybridSystemParser::T__36);
                setState(1005);
                match(HybridSystemParser::T__1);
                break;
            }

            case 2: {
                _localctx = dynamic_cast<LocationContext *>(_tracker.createInstance<HybridSystemParser::LocIdContext>(
                        _localctx));
                enterOuterAlt(_localctx, 2);
                setState(1006);
                match(HybridSystemParser::T__36);
                setState(1007);
                identifier();
                setState(1008);
                match(HybridSystemParser::T__1);
                break;
            }

            case 3: {
                _localctx = dynamic_cast<LocationContext *>(_tracker.createInstance<HybridSystemParser::LocElemContext>(
                        _localctx));
                enterOuterAlt(_localctx, 3);
                setState(1010);
                match(HybridSystemParser::T__36);
                setState(1011);
                match(HybridSystemParser::T__4);
                setState(1012);
                locationElements();
                break;
            }

            case 4: {
                _localctx = dynamic_cast<LocationContext *>(_tracker.createInstance<HybridSystemParser::LocIdElemContext>(
                        _localctx));
                enterOuterAlt(_localctx, 4);
                setState(1013);
                match(HybridSystemParser::T__36);
                setState(1014);
                identifier();
                setState(1015);
                match(HybridSystemParser::T__4);
                setState(1016);
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

HybridSystemParser::LocationElementsContext::LocationElementsContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::LocationElementContext *>
HybridSystemParser::LocationElementsContext::locationElement() {
    return getRuleContexts<HybridSystemParser::LocationElementContext>();
}

HybridSystemParser::LocationElementContext *HybridSystemParser::LocationElementsContext::locationElement(size_t i) {
    return getRuleContext<HybridSystemParser::LocationElementContext>(i);
}


size_t HybridSystemParser::LocationElementsContext::getRuleIndex() const {
    return HybridSystemParser::RuleLocationElements;
}

antlrcpp::Any HybridSystemParser::LocationElementsContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitLocationElements(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::LocationElementsContext *HybridSystemParser::locationElements() {
    LocationElementsContext *_localctx = _tracker.createInstance<LocationElementsContext>(_ctx, getState());
    enterRule(_localctx, 134, HybridSystemParser::RuleLocationElements);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(1021);
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
            setState(1020);
            locationElement();
            setState(1023);
            _errHandler->sync(this);
            _la = _input->LA(1);
        } while ((((_la & ~0x3fULL) == 0) &&
                  ((1ULL << _la) & ((1ULL << HybridSystemParser::T__19)
                                    | (1ULL << HybridSystemParser::T__20)
                                    | (1ULL << HybridSystemParser::T__21))) != 0) || ((((_la - 74) & ~0x3fULL) == 0) &&
                                                                                      ((1ULL << (_la - 74)) & ((1ULL
                                                                                              << (HybridSystemParser::T__73 -
                                                                                                  74))
                                                                                                               | (1ULL
                                                                                              << (HybridSystemParser::T__74 -
                                                                                                  74))
                                                                                                               | (1ULL
                                                                                              << (HybridSystemParser::T__75 -
                                                                                                  74))
                                                                                                               | (1ULL
                                                                                              << (HybridSystemParser::T__108 -
                                                                                                  74))
                                                                                                               | (1ULL
                                                                                              << (HybridSystemParser::T__109 -
                                                                                                  74))
                                                                                                               | (1ULL
                                                                                              << (HybridSystemParser::T__116 -
                                                                                                  74)))) != 0));

    }
    catch (RecognitionException &e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- LocationElementContext ------------------------------------------------------------------

HybridSystemParser::LocationElementContext::LocationElementContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}


size_t HybridSystemParser::LocationElementContext::getRuleIndex() const {
    return HybridSystemParser::RuleLocationElement;
}

void HybridSystemParser::LocationElementContext::copyFrom(LocationElementContext *ctx) {
    ParserRuleContext::copyFrom(ctx);
}

//----------------- LocElemEdgeToContext ------------------------------------------------------------------

HybridSystemParser::CoreEdgeContext *HybridSystemParser::LocElemEdgeToContext::coreEdge() {
    return getRuleContext<HybridSystemParser::CoreEdgeContext>(0);
}

HybridSystemParser::IdentifierContext *HybridSystemParser::LocElemEdgeToContext::identifier() {
    return getRuleContext<HybridSystemParser::IdentifierContext>(0);
}

HybridSystemParser::LocElemEdgeToContext::LocElemEdgeToContext(LocationElementContext *ctx) { copyFrom(ctx); }

antlrcpp::Any HybridSystemParser::LocElemEdgeToContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitLocElemEdgeTo(this);
    else
        return visitor->visitChildren(this);
}
//----------------- LocElemMarkedContext ------------------------------------------------------------------

HybridSystemParser::LocElemMarkedContext::LocElemMarkedContext(LocationElementContext *ctx) { copyFrom(ctx); }

antlrcpp::Any HybridSystemParser::LocElemMarkedContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitLocElemMarked(this);
    else
        return visitor->visitChildren(this);
}
//----------------- LocElemInvContext ------------------------------------------------------------------

HybridSystemParser::InvariantDeclsContext *HybridSystemParser::LocElemInvContext::invariantDecls() {
    return getRuleContext<HybridSystemParser::InvariantDeclsContext>(0);
}

HybridSystemParser::LocElemInvContext::LocElemInvContext(LocationElementContext *ctx) { copyFrom(ctx); }

antlrcpp::Any HybridSystemParser::LocElemInvContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitLocElemInv(this);
    else
        return visitor->visitChildren(this);
}
//----------------- LocElemMarkedExprContext ------------------------------------------------------------------

HybridSystemParser::ExpressionsContext *HybridSystemParser::LocElemMarkedExprContext::expressions() {
    return getRuleContext<HybridSystemParser::ExpressionsContext>(0);
}

HybridSystemParser::LocElemMarkedExprContext::LocElemMarkedExprContext(LocationElementContext *ctx) { copyFrom(ctx); }

antlrcpp::Any HybridSystemParser::LocElemMarkedExprContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitLocElemMarkedExpr(this);
    else
        return visitor->visitChildren(this);
}
//----------------- LocElemUrgentContext ------------------------------------------------------------------

HybridSystemParser::LocElemUrgentContext::LocElemUrgentContext(LocationElementContext *ctx) { copyFrom(ctx); }

antlrcpp::Any HybridSystemParser::LocElemUrgentContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitLocElemUrgent(this);
    else
        return visitor->visitChildren(this);
}
//----------------- LocElemLoopContext ------------------------------------------------------------------

HybridSystemParser::CoreEdgeContext *HybridSystemParser::LocElemLoopContext::coreEdge() {
    return getRuleContext<HybridSystemParser::CoreEdgeContext>(0);
}

HybridSystemParser::LocElemLoopContext::LocElemLoopContext(LocationElementContext *ctx) { copyFrom(ctx); }

antlrcpp::Any HybridSystemParser::LocElemLoopContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitLocElemLoop(this);
    else
        return visitor->visitChildren(this);
}
//----------------- LocElemInitialFlagContext ------------------------------------------------------------------

HybridSystemParser::LocElemInitialFlagContext::LocElemInitialFlagContext(LocationElementContext *ctx) { copyFrom(ctx); }

antlrcpp::Any HybridSystemParser::LocElemInitialFlagContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitLocElemInitialFlag(this);
    else
        return visitor->visitChildren(this);
}
//----------------- LocElemInitialFlagExprContext ------------------------------------------------------------------

HybridSystemParser::ExpressionsContext *HybridSystemParser::LocElemInitialFlagExprContext::expressions() {
    return getRuleContext<HybridSystemParser::ExpressionsContext>(0);
}

HybridSystemParser::LocElemInitialFlagExprContext::LocElemInitialFlagExprContext(
        LocationElementContext *ctx) { copyFrom(ctx); }

antlrcpp::Any HybridSystemParser::LocElemInitialFlagExprContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitLocElemInitialFlagExpr(this);
    else
        return visitor->visitChildren(this);
}
//----------------- LocElemEqsContext ------------------------------------------------------------------

HybridSystemParser::EquationsContext *HybridSystemParser::LocElemEqsContext::equations() {
    return getRuleContext<HybridSystemParser::EquationsContext>(0);
}

HybridSystemParser::LocElemEqsContext::LocElemEqsContext(LocationElementContext *ctx) { copyFrom(ctx); }

antlrcpp::Any HybridSystemParser::LocElemEqsContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitLocElemEqs(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::LocationElementContext *HybridSystemParser::locationElement() {
    LocationElementContext *_localctx = _tracker.createInstance<LocationElementContext>(_ctx, getState());
    enterRule(_localctx, 136, HybridSystemParser::RuleLocationElement);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        setState(1054);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 61, _ctx)) {
            case 1: {
                _localctx = dynamic_cast<LocationElementContext *>(_tracker.createInstance<HybridSystemParser::LocElemInitialFlagContext>(
                        _localctx));
                enterOuterAlt(_localctx, 1);
                setState(1025);
                match(HybridSystemParser::T__20);
                setState(1026);
                match(HybridSystemParser::T__1);
                break;
            }

            case 2: {
                _localctx = dynamic_cast<LocationElementContext *>(_tracker.createInstance<HybridSystemParser::LocElemInitialFlagExprContext>(
                        _localctx));
                enterOuterAlt(_localctx, 2);
                setState(1027);
                match(HybridSystemParser::T__20);
                setState(1028);
                expressions();
                setState(1029);
                match(HybridSystemParser::T__1);
                break;
            }

            case 3: {
                _localctx = dynamic_cast<LocationElementContext *>(_tracker.createInstance<HybridSystemParser::LocElemInvContext>(
                        _localctx));
                enterOuterAlt(_localctx, 3);
                setState(1031);
                invariantDecls();
                break;
            }

            case 4: {
                _localctx = dynamic_cast<LocationElementContext *>(_tracker.createInstance<HybridSystemParser::LocElemEqsContext>(
                        _localctx));
                enterOuterAlt(_localctx, 4);
                setState(1032);
                match(HybridSystemParser::T__19);
                setState(1033);
                equations();
                setState(1034);
                match(HybridSystemParser::T__1);
                break;
            }

            case 5: {
                _localctx = dynamic_cast<LocationElementContext *>(_tracker.createInstance<HybridSystemParser::LocElemMarkedContext>(
                        _localctx));
                enterOuterAlt(_localctx, 5);
                setState(1036);
                match(HybridSystemParser::T__21);
                setState(1037);
                match(HybridSystemParser::T__1);
                break;
            }

            case 6: {
                _localctx = dynamic_cast<LocationElementContext *>(_tracker.createInstance<HybridSystemParser::LocElemMarkedExprContext>(
                        _localctx));
                enterOuterAlt(_localctx, 6);
                setState(1038);
                match(HybridSystemParser::T__21);
                setState(1039);
                expressions();
                setState(1040);
                match(HybridSystemParser::T__1);
                break;
            }

            case 7: {
                _localctx = dynamic_cast<LocationElementContext *>(_tracker.createInstance<HybridSystemParser::LocElemUrgentContext>(
                        _localctx));
                enterOuterAlt(_localctx, 7);
                setState(1042);
                match(HybridSystemParser::T__108);
                setState(1043);
                match(HybridSystemParser::T__1);
                break;
            }

            case 8: {
                _localctx = dynamic_cast<LocationElementContext *>(_tracker.createInstance<HybridSystemParser::LocElemEdgeToContext>(
                        _localctx));
                enterOuterAlt(_localctx, 8);
                setState(1044);
                match(HybridSystemParser::T__109);
                setState(1045);
                coreEdge();
                setState(1046);
                match(HybridSystemParser::T__110);
                setState(1047);
                identifier();
                setState(1048);
                match(HybridSystemParser::T__1);
                break;
            }

            case 9: {
                _localctx = dynamic_cast<LocationElementContext *>(_tracker.createInstance<HybridSystemParser::LocElemLoopContext>(
                        _localctx));
                enterOuterAlt(_localctx, 9);
                setState(1050);
                match(HybridSystemParser::T__109);
                setState(1051);
                coreEdge();
                setState(1052);
                match(HybridSystemParser::T__1);
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

HybridSystemParser::CoreEdgeContext::CoreEdgeContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::EdgeEventsContext *HybridSystemParser::CoreEdgeContext::edgeEvents() {
    return getRuleContext<HybridSystemParser::EdgeEventsContext>(0);
}

HybridSystemParser::OptEdgeGuardContext *HybridSystemParser::CoreEdgeContext::optEdgeGuard() {
    return getRuleContext<HybridSystemParser::OptEdgeGuardContext>(0);
}

HybridSystemParser::OptEdgeUrgentContext *HybridSystemParser::CoreEdgeContext::optEdgeUrgent() {
    return getRuleContext<HybridSystemParser::OptEdgeUrgentContext>(0);
}

HybridSystemParser::OptEdgeUpdateContext *HybridSystemParser::CoreEdgeContext::optEdgeUpdate() {
    return getRuleContext<HybridSystemParser::OptEdgeUpdateContext>(0);
}

HybridSystemParser::ExpressionsContext *HybridSystemParser::CoreEdgeContext::expressions() {
    return getRuleContext<HybridSystemParser::ExpressionsContext>(0);
}

HybridSystemParser::UpdatesContext *HybridSystemParser::CoreEdgeContext::updates() {
    return getRuleContext<HybridSystemParser::UpdatesContext>(0);
}


size_t HybridSystemParser::CoreEdgeContext::getRuleIndex() const {
    return HybridSystemParser::RuleCoreEdge;
}

antlrcpp::Any HybridSystemParser::CoreEdgeContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitCoreEdge(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::CoreEdgeContext *HybridSystemParser::coreEdge() {
    CoreEdgeContext *_localctx = _tracker.createInstance<CoreEdgeContext>(_ctx, getState());
    enterRule(_localctx, 138, HybridSystemParser::RuleCoreEdge);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        setState(1070);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
            case HybridSystemParser::T__114:
            case HybridSystemParser::IDENTIFIER:
            case HybridSystemParser::RELATIVENAME:
            case HybridSystemParser::ABSOLUTENAME:
            case HybridSystemParser::ROOTNAME: {
                enterOuterAlt(_localctx, 1);
                setState(1056);
                edgeEvents();
                setState(1057);
                optEdgeGuard();
                setState(1058);
                optEdgeUrgent();
                setState(1059);
                optEdgeUpdate();
                break;
            }

            case HybridSystemParser::T__111: {
                enterOuterAlt(_localctx, 2);
                setState(1061);
                match(HybridSystemParser::T__111);
                setState(1062);
                expressions();
                setState(1063);
                optEdgeUrgent();
                setState(1064);
                optEdgeUpdate();
                break;
            }

            case HybridSystemParser::T__112: {
                enterOuterAlt(_localctx, 3);
                setState(1066);
                match(HybridSystemParser::T__112);
                setState(1067);
                optEdgeUpdate();
                break;
            }

            case HybridSystemParser::T__113: {
                enterOuterAlt(_localctx, 4);
                setState(1068);
                match(HybridSystemParser::T__113);
                setState(1069);
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

HybridSystemParser::OptEdgeGuardContext::OptEdgeGuardContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::ExpressionsContext *HybridSystemParser::OptEdgeGuardContext::expressions() {
    return getRuleContext<HybridSystemParser::ExpressionsContext>(0);
}


size_t HybridSystemParser::OptEdgeGuardContext::getRuleIndex() const {
    return HybridSystemParser::RuleOptEdgeGuard;
}

antlrcpp::Any HybridSystemParser::OptEdgeGuardContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitOptEdgeGuard(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::OptEdgeGuardContext *HybridSystemParser::optEdgeGuard() {
    OptEdgeGuardContext *_localctx = _tracker.createInstance<OptEdgeGuardContext>(_ctx, getState());
    enterRule(_localctx, 140, HybridSystemParser::RuleOptEdgeGuard);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(1074);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == HybridSystemParser::T__111) {
            setState(1072);
            match(HybridSystemParser::T__111);
            setState(1073);
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

HybridSystemParser::OptEdgeUrgentContext::OptEdgeUrgentContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}


size_t HybridSystemParser::OptEdgeUrgentContext::getRuleIndex() const {
    return HybridSystemParser::RuleOptEdgeUrgent;
}

antlrcpp::Any HybridSystemParser::OptEdgeUrgentContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitOptEdgeUrgent(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::OptEdgeUrgentContext *HybridSystemParser::optEdgeUrgent() {
    OptEdgeUrgentContext *_localctx = _tracker.createInstance<OptEdgeUrgentContext>(_ctx, getState());
    enterRule(_localctx, 142, HybridSystemParser::RuleOptEdgeUrgent);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(1077);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == HybridSystemParser::T__112) {
            setState(1076);
            match(HybridSystemParser::T__112);
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

HybridSystemParser::OptEdgeUpdateContext::OptEdgeUpdateContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::UpdatesContext *HybridSystemParser::OptEdgeUpdateContext::updates() {
    return getRuleContext<HybridSystemParser::UpdatesContext>(0);
}


size_t HybridSystemParser::OptEdgeUpdateContext::getRuleIndex() const {
    return HybridSystemParser::RuleOptEdgeUpdate;
}

antlrcpp::Any HybridSystemParser::OptEdgeUpdateContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitOptEdgeUpdate(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::OptEdgeUpdateContext *HybridSystemParser::optEdgeUpdate() {
    OptEdgeUpdateContext *_localctx = _tracker.createInstance<OptEdgeUpdateContext>(_ctx, getState());
    enterRule(_localctx, 144, HybridSystemParser::RuleOptEdgeUpdate);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(1081);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == HybridSystemParser::T__113) {
            setState(1079);
            match(HybridSystemParser::T__113);
            setState(1080);
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

HybridSystemParser::EdgeEventsContext::EdgeEventsContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::EdgeEventContext *> HybridSystemParser::EdgeEventsContext::edgeEvent() {
    return getRuleContexts<HybridSystemParser::EdgeEventContext>();
}

HybridSystemParser::EdgeEventContext *HybridSystemParser::EdgeEventsContext::edgeEvent(size_t i) {
    return getRuleContext<HybridSystemParser::EdgeEventContext>(i);
}


size_t HybridSystemParser::EdgeEventsContext::getRuleIndex() const {
    return HybridSystemParser::RuleEdgeEvents;
}

antlrcpp::Any HybridSystemParser::EdgeEventsContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitEdgeEvents(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::EdgeEventsContext *HybridSystemParser::edgeEvents() {
    EdgeEventsContext *_localctx = _tracker.createInstance<EdgeEventsContext>(_ctx, getState());
    enterRule(_localctx, 146, HybridSystemParser::RuleEdgeEvents);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(1083);
        edgeEvent();
        setState(1088);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == HybridSystemParser::T__22) {
            setState(1084);
            match(HybridSystemParser::T__22);
            setState(1085);
            edgeEvent();
            setState(1090);
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

HybridSystemParser::EdgeEventContext::EdgeEventContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::NameContext *HybridSystemParser::EdgeEventContext::name() {
    return getRuleContext<HybridSystemParser::NameContext>(0);
}

HybridSystemParser::ExpressionContext *HybridSystemParser::EdgeEventContext::expression() {
    return getRuleContext<HybridSystemParser::ExpressionContext>(0);
}


size_t HybridSystemParser::EdgeEventContext::getRuleIndex() const {
    return HybridSystemParser::RuleEdgeEvent;
}

antlrcpp::Any HybridSystemParser::EdgeEventContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitEdgeEvent(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::EdgeEventContext *HybridSystemParser::edgeEvent() {
    EdgeEventContext *_localctx = _tracker.createInstance<EdgeEventContext>(_ctx, getState());
    enterRule(_localctx, 148, HybridSystemParser::RuleEdgeEvent);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        setState(1103);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 67, _ctx)) {
            case 1: {
                enterOuterAlt(_localctx, 1);
                setState(1091);
                match(HybridSystemParser::T__114);
                break;
            }

            case 2: {
                enterOuterAlt(_localctx, 2);
                setState(1092);
                name();
                break;
            }

            case 3: {
                enterOuterAlt(_localctx, 3);
                setState(1093);
                name();
                setState(1094);
                match(HybridSystemParser::T__115);
                break;
            }

            case 4: {
                enterOuterAlt(_localctx, 4);
                setState(1096);
                name();
                setState(1097);
                match(HybridSystemParser::T__115);
                setState(1098);
                expression();
                break;
            }

            case 5: {
                enterOuterAlt(_localctx, 5);
                setState(1100);
                name();
                setState(1101);
                match(HybridSystemParser::T__60);
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

HybridSystemParser::InvariantDeclsContext::InvariantDeclsContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::OptSupKindContext *HybridSystemParser::InvariantDeclsContext::optSupKind() {
    return getRuleContext<HybridSystemParser::OptSupKindContext>(0);
}

HybridSystemParser::InvariantsContext *HybridSystemParser::InvariantDeclsContext::invariants() {
    return getRuleContext<HybridSystemParser::InvariantsContext>(0);
}

HybridSystemParser::SupKindContext *HybridSystemParser::InvariantDeclsContext::supKind() {
    return getRuleContext<HybridSystemParser::SupKindContext>(0);
}


size_t HybridSystemParser::InvariantDeclsContext::getRuleIndex() const {
    return HybridSystemParser::RuleInvariantDecls;
}

antlrcpp::Any HybridSystemParser::InvariantDeclsContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitInvariantDecls(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::InvariantDeclsContext *HybridSystemParser::invariantDecls() {
    InvariantDeclsContext *_localctx = _tracker.createInstance<InvariantDeclsContext>(_ctx, getState());
    enterRule(_localctx, 150, HybridSystemParser::RuleInvariantDecls);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        setState(1114);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 68, _ctx)) {
            case 1: {
                enterOuterAlt(_localctx, 1);
                setState(1105);
                optSupKind();
                setState(1106);
                match(HybridSystemParser::T__116);
                setState(1107);
                invariants();
                setState(1108);
                match(HybridSystemParser::T__1);
                break;
            }

            case 2: {
                enterOuterAlt(_localctx, 2);
                setState(1110);
                supKind();
                setState(1111);
                invariants();
                setState(1112);
                match(HybridSystemParser::T__1);
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

HybridSystemParser::InvariantsContext::InvariantsContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::InvariantContext *> HybridSystemParser::InvariantsContext::invariant() {
    return getRuleContexts<HybridSystemParser::InvariantContext>();
}

HybridSystemParser::InvariantContext *HybridSystemParser::InvariantsContext::invariant(size_t i) {
    return getRuleContext<HybridSystemParser::InvariantContext>(i);
}


size_t HybridSystemParser::InvariantsContext::getRuleIndex() const {
    return HybridSystemParser::RuleInvariants;
}

antlrcpp::Any HybridSystemParser::InvariantsContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitInvariants(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::InvariantsContext *HybridSystemParser::invariants() {
    InvariantsContext *_localctx = _tracker.createInstance<InvariantsContext>(_ctx, getState());
    enterRule(_localctx, 152, HybridSystemParser::RuleInvariants);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(1116);
        invariant();
        setState(1121);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == HybridSystemParser::T__22) {
            setState(1117);
            match(HybridSystemParser::T__22);
            setState(1118);
            invariant();
            setState(1123);
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

HybridSystemParser::InvariantContext::InvariantContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}


size_t HybridSystemParser::InvariantContext::getRuleIndex() const {
    return HybridSystemParser::RuleInvariant;
}

void HybridSystemParser::InvariantContext::copyFrom(InvariantContext *ctx) {
    ParserRuleContext::copyFrom(ctx);
}

//----------------- InvNeedsContext ------------------------------------------------------------------

HybridSystemParser::NameContext *HybridSystemParser::InvNeedsContext::name() {
    return getRuleContext<HybridSystemParser::NameContext>(0);
}

HybridSystemParser::ExpressionContext *HybridSystemParser::InvNeedsContext::expression() {
    return getRuleContext<HybridSystemParser::ExpressionContext>(0);
}

HybridSystemParser::InvNeedsContext::InvNeedsContext(InvariantContext *ctx) { copyFrom(ctx); }

antlrcpp::Any HybridSystemParser::InvNeedsContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitInvNeeds(this);
    else
        return visitor->visitChildren(this);
}
//----------------- InvExprContext ------------------------------------------------------------------

HybridSystemParser::ExpressionContext *HybridSystemParser::InvExprContext::expression() {
    return getRuleContext<HybridSystemParser::ExpressionContext>(0);
}

HybridSystemParser::InvExprContext::InvExprContext(InvariantContext *ctx) { copyFrom(ctx); }

antlrcpp::Any HybridSystemParser::InvExprContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitInvExpr(this);
    else
        return visitor->visitChildren(this);
}
//----------------- InvDisablesContext ------------------------------------------------------------------

HybridSystemParser::ExpressionContext *HybridSystemParser::InvDisablesContext::expression() {
    return getRuleContext<HybridSystemParser::ExpressionContext>(0);
}

HybridSystemParser::NameContext *HybridSystemParser::InvDisablesContext::name() {
    return getRuleContext<HybridSystemParser::NameContext>(0);
}

HybridSystemParser::InvDisablesContext::InvDisablesContext(InvariantContext *ctx) { copyFrom(ctx); }

antlrcpp::Any HybridSystemParser::InvDisablesContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitInvDisables(this);
    else
        return visitor->visitChildren(this);
}
//----------------- InvNeedsSetContext ------------------------------------------------------------------

HybridSystemParser::NonEmptySetExpressionContext *HybridSystemParser::InvNeedsSetContext::nonEmptySetExpression() {
    return getRuleContext<HybridSystemParser::NonEmptySetExpressionContext>(0);
}

HybridSystemParser::ExpressionContext *HybridSystemParser::InvNeedsSetContext::expression() {
    return getRuleContext<HybridSystemParser::ExpressionContext>(0);
}

HybridSystemParser::InvNeedsSetContext::InvNeedsSetContext(InvariantContext *ctx) { copyFrom(ctx); }

antlrcpp::Any HybridSystemParser::InvNeedsSetContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitInvNeedsSet(this);
    else
        return visitor->visitChildren(this);
}
//----------------- InvDisablesSetContext ------------------------------------------------------------------

HybridSystemParser::ExpressionContext *HybridSystemParser::InvDisablesSetContext::expression() {
    return getRuleContext<HybridSystemParser::ExpressionContext>(0);
}

HybridSystemParser::NameSetContext *HybridSystemParser::InvDisablesSetContext::nameSet() {
    return getRuleContext<HybridSystemParser::NameSetContext>(0);
}

HybridSystemParser::InvDisablesSetContext::InvDisablesSetContext(InvariantContext *ctx) { copyFrom(ctx); }

antlrcpp::Any HybridSystemParser::InvDisablesSetContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitInvDisablesSet(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::InvariantContext *HybridSystemParser::invariant() {
    InvariantContext *_localctx = _tracker.createInstance<InvariantContext>(_ctx, getState());
    enterRule(_localctx, 154, HybridSystemParser::RuleInvariant);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        setState(1141);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 70, _ctx)) {
            case 1: {
                _localctx = dynamic_cast<InvariantContext *>(_tracker.createInstance<HybridSystemParser::InvExprContext>(
                        _localctx));
                enterOuterAlt(_localctx, 1);
                setState(1124);
                expression();
                break;
            }

            case 2: {
                _localctx = dynamic_cast<InvariantContext *>(_tracker.createInstance<HybridSystemParser::InvNeedsContext>(
                        _localctx));
                enterOuterAlt(_localctx, 2);
                setState(1125);
                name();
                setState(1126);
                match(HybridSystemParser::T__117);
                setState(1127);
                expression();
                break;
            }

            case 3: {
                _localctx = dynamic_cast<InvariantContext *>(_tracker.createInstance<HybridSystemParser::InvNeedsSetContext>(
                        _localctx));
                enterOuterAlt(_localctx, 3);
                setState(1129);
                nonEmptySetExpression();
                setState(1130);
                match(HybridSystemParser::T__117);
                setState(1131);
                expression();
                break;
            }

            case 4: {
                _localctx = dynamic_cast<InvariantContext *>(_tracker.createInstance<HybridSystemParser::InvDisablesContext>(
                        _localctx));
                enterOuterAlt(_localctx, 4);
                setState(1133);
                expression();
                setState(1134);
                match(HybridSystemParser::T__118);
                setState(1135);
                name();
                break;
            }

            case 5: {
                _localctx = dynamic_cast<InvariantContext *>(_tracker.createInstance<HybridSystemParser::InvDisablesSetContext>(
                        _localctx));
                enterOuterAlt(_localctx, 5);
                setState(1137);
                expression();
                setState(1138);
                match(HybridSystemParser::T__118);
                setState(1139);
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

HybridSystemParser::UpdatesContext::UpdatesContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::UpdateContext *> HybridSystemParser::UpdatesContext::update() {
    return getRuleContexts<HybridSystemParser::UpdateContext>();
}

HybridSystemParser::UpdateContext *HybridSystemParser::UpdatesContext::update(size_t i) {
    return getRuleContext<HybridSystemParser::UpdateContext>(i);
}


size_t HybridSystemParser::UpdatesContext::getRuleIndex() const {
    return HybridSystemParser::RuleUpdates;
}

antlrcpp::Any HybridSystemParser::UpdatesContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitUpdates(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::UpdatesContext *HybridSystemParser::updates() {
    UpdatesContext *_localctx = _tracker.createInstance<UpdatesContext>(_ctx, getState());
    enterRule(_localctx, 156, HybridSystemParser::RuleUpdates);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(1143);
        update();
        setState(1148);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == HybridSystemParser::T__22) {
            setState(1144);
            match(HybridSystemParser::T__22);
            setState(1145);
            update();
            setState(1150);
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

HybridSystemParser::UpdateContext::UpdateContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}


size_t HybridSystemParser::UpdateContext::getRuleIndex() const {
    return HybridSystemParser::RuleUpdate;
}

void HybridSystemParser::UpdateContext::copyFrom(UpdateContext *ctx) {
    ParserRuleContext::copyFrom(ctx);
}

//----------------- UpdateNonIfContext ------------------------------------------------------------------

HybridSystemParser::AdressableContext *HybridSystemParser::UpdateNonIfContext::adressable() {
    return getRuleContext<HybridSystemParser::AdressableContext>(0);
}

HybridSystemParser::ExpressionContext *HybridSystemParser::UpdateNonIfContext::expression() {
    return getRuleContext<HybridSystemParser::ExpressionContext>(0);
}

HybridSystemParser::UpdateNonIfContext::UpdateNonIfContext(UpdateContext *ctx) { copyFrom(ctx); }

antlrcpp::Any HybridSystemParser::UpdateNonIfContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitUpdateNonIf(this);
    else
        return visitor->visitChildren(this);
}
//----------------- UpdateIfContext ------------------------------------------------------------------

HybridSystemParser::ExpressionsContext *HybridSystemParser::UpdateIfContext::expressions() {
    return getRuleContext<HybridSystemParser::ExpressionsContext>(0);
}

HybridSystemParser::UpdatesContext *HybridSystemParser::UpdateIfContext::updates() {
    return getRuleContext<HybridSystemParser::UpdatesContext>(0);
}

HybridSystemParser::OptElifUpdatesContext *HybridSystemParser::UpdateIfContext::optElifUpdates() {
    return getRuleContext<HybridSystemParser::OptElifUpdatesContext>(0);
}

HybridSystemParser::OptElseUpdateContext *HybridSystemParser::UpdateIfContext::optElseUpdate() {
    return getRuleContext<HybridSystemParser::OptElseUpdateContext>(0);
}

HybridSystemParser::UpdateIfContext::UpdateIfContext(UpdateContext *ctx) { copyFrom(ctx); }

antlrcpp::Any HybridSystemParser::UpdateIfContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitUpdateIf(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::UpdateContext *HybridSystemParser::update() {
    UpdateContext *_localctx = _tracker.createInstance<UpdateContext>(_ctx, getState());
    enterRule(_localctx, 158, HybridSystemParser::RuleUpdate);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        setState(1163);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
            case HybridSystemParser::T__26:
            case HybridSystemParser::IDENTIFIER: {
                _localctx = dynamic_cast<UpdateContext *>(_tracker.createInstance<HybridSystemParser::UpdateNonIfContext>(
                        _localctx));
                enterOuterAlt(_localctx, 1);
                setState(1151);
                adressable();
                setState(1152);
                match(HybridSystemParser::T__28);
                setState(1153);
                expression();
                break;
            }

            case HybridSystemParser::T__29: {
                _localctx = dynamic_cast<UpdateContext *>(_tracker.createInstance<HybridSystemParser::UpdateIfContext>(
                        _localctx));
                enterOuterAlt(_localctx, 2);
                setState(1155);
                match(HybridSystemParser::T__29);
                setState(1156);
                expressions();
                setState(1157);
                match(HybridSystemParser::T__4);
                setState(1158);
                updates();
                setState(1159);
                optElifUpdates();
                setState(1160);
                optElseUpdate();
                setState(1161);
                match(HybridSystemParser::T__7);
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

HybridSystemParser::OptElifUpdatesContext::OptElifUpdatesContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::ExpressionsContext *> HybridSystemParser::OptElifUpdatesContext::expressions() {
    return getRuleContexts<HybridSystemParser::ExpressionsContext>();
}

HybridSystemParser::ExpressionsContext *HybridSystemParser::OptElifUpdatesContext::expressions(size_t i) {
    return getRuleContext<HybridSystemParser::ExpressionsContext>(i);
}

std::vector<HybridSystemParser::UpdatesContext *> HybridSystemParser::OptElifUpdatesContext::updates() {
    return getRuleContexts<HybridSystemParser::UpdatesContext>();
}

HybridSystemParser::UpdatesContext *HybridSystemParser::OptElifUpdatesContext::updates(size_t i) {
    return getRuleContext<HybridSystemParser::UpdatesContext>(i);
}


size_t HybridSystemParser::OptElifUpdatesContext::getRuleIndex() const {
    return HybridSystemParser::RuleOptElifUpdates;
}

antlrcpp::Any HybridSystemParser::OptElifUpdatesContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitOptElifUpdates(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::OptElifUpdatesContext *HybridSystemParser::optElifUpdates() {
    OptElifUpdatesContext *_localctx = _tracker.createInstance<OptElifUpdatesContext>(_ctx, getState());
    enterRule(_localctx, 160, HybridSystemParser::RuleOptElifUpdates);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(1172);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == HybridSystemParser::T__34) {
            setState(1165);
            match(HybridSystemParser::T__34);
            setState(1166);
            expressions();
            setState(1167);
            match(HybridSystemParser::T__4);
            setState(1168);
            updates();
            setState(1174);
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

HybridSystemParser::OptElseUpdateContext::OptElseUpdateContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::UpdateContext *HybridSystemParser::OptElseUpdateContext::update() {
    return getRuleContext<HybridSystemParser::UpdateContext>(0);
}


size_t HybridSystemParser::OptElseUpdateContext::getRuleIndex() const {
    return HybridSystemParser::RuleOptElseUpdate;
}

antlrcpp::Any HybridSystemParser::OptElseUpdateContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitOptElseUpdate(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::OptElseUpdateContext *HybridSystemParser::optElseUpdate() {
    OptElseUpdateContext *_localctx = _tracker.createInstance<OptElseUpdateContext>(_ctx, getState());
    enterRule(_localctx, 162, HybridSystemParser::RuleOptElseUpdate);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(1177);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == HybridSystemParser::T__35) {
            setState(1175);
            match(HybridSystemParser::T__35);
            setState(1176);
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

HybridSystemParser::AdressablesContext::AdressablesContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::AdressableContext *> HybridSystemParser::AdressablesContext::adressable() {
    return getRuleContexts<HybridSystemParser::AdressableContext>();
}

HybridSystemParser::AdressableContext *HybridSystemParser::AdressablesContext::adressable(size_t i) {
    return getRuleContext<HybridSystemParser::AdressableContext>(i);
}


size_t HybridSystemParser::AdressablesContext::getRuleIndex() const {
    return HybridSystemParser::RuleAdressables;
}

antlrcpp::Any HybridSystemParser::AdressablesContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitAdressables(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::AdressablesContext *HybridSystemParser::adressables() {
    AdressablesContext *_localctx = _tracker.createInstance<AdressablesContext>(_ctx, getState());
    enterRule(_localctx, 164, HybridSystemParser::RuleAdressables);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(1179);
        adressable();
        setState(1184);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == HybridSystemParser::T__22) {
            setState(1180);
            match(HybridSystemParser::T__22);
            setState(1181);
            adressable();
            setState(1186);
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

HybridSystemParser::AdressableContext::AdressableContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}


size_t HybridSystemParser::AdressableContext::getRuleIndex() const {
    return HybridSystemParser::RuleAdressable;
}

void HybridSystemParser::AdressableContext::copyFrom(AdressableContext *ctx) {
    ParserRuleContext::copyFrom(ctx);
}

//----------------- AdressableIdContext ------------------------------------------------------------------

HybridSystemParser::IdentifierContext *HybridSystemParser::AdressableIdContext::identifier() {
    return getRuleContext<HybridSystemParser::IdentifierContext>(0);
}

HybridSystemParser::AdressableIdContext::AdressableIdContext(AdressableContext *ctx) { copyFrom(ctx); }

antlrcpp::Any HybridSystemParser::AdressableIdContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitAdressableId(this);
    else
        return visitor->visitChildren(this);
}
//----------------- AdressableProjContext ------------------------------------------------------------------

HybridSystemParser::IdentifierContext *HybridSystemParser::AdressableProjContext::identifier() {
    return getRuleContext<HybridSystemParser::IdentifierContext>(0);
}

HybridSystemParser::ProjectionsContext *HybridSystemParser::AdressableProjContext::projections() {
    return getRuleContext<HybridSystemParser::ProjectionsContext>(0);
}

HybridSystemParser::AdressableProjContext::AdressableProjContext(AdressableContext *ctx) { copyFrom(ctx); }

antlrcpp::Any HybridSystemParser::AdressableProjContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitAdressableProj(this);
    else
        return visitor->visitChildren(this);
}
//----------------- AdressablePairContext ------------------------------------------------------------------

std::vector<HybridSystemParser::AdressableContext *> HybridSystemParser::AdressablePairContext::adressable() {
    return getRuleContexts<HybridSystemParser::AdressableContext>();
}

HybridSystemParser::AdressableContext *HybridSystemParser::AdressablePairContext::adressable(size_t i) {
    return getRuleContext<HybridSystemParser::AdressableContext>(i);
}

HybridSystemParser::AdressablePairContext::AdressablePairContext(AdressableContext *ctx) { copyFrom(ctx); }

antlrcpp::Any HybridSystemParser::AdressablePairContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitAdressablePair(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::AdressableContext *HybridSystemParser::adressable() {
    AdressableContext *_localctx = _tracker.createInstance<AdressableContext>(_ctx, getState());
    enterRule(_localctx, 166, HybridSystemParser::RuleAdressable);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        setState(1197);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 76, _ctx)) {
            case 1: {
                _localctx = dynamic_cast<AdressableContext *>(_tracker.createInstance<HybridSystemParser::AdressableIdContext>(
                        _localctx));
                enterOuterAlt(_localctx, 1);
                setState(1187);
                identifier();
                break;
            }

            case 2: {
                _localctx = dynamic_cast<AdressableContext *>(_tracker.createInstance<HybridSystemParser::AdressableProjContext>(
                        _localctx));
                enterOuterAlt(_localctx, 2);
                setState(1188);
                identifier();
                setState(1189);
                projections();
                break;
            }

            case 3: {
                _localctx = dynamic_cast<AdressableContext *>(_tracker.createInstance<HybridSystemParser::AdressablePairContext>(
                        _localctx));
                enterOuterAlt(_localctx, 3);
                setState(1191);
                match(HybridSystemParser::T__26);
                setState(1192);
                adressable();
                setState(1193);
                match(HybridSystemParser::T__22);
                setState(1194);
                adressable();
                setState(1195);
                match(HybridSystemParser::T__27);
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

HybridSystemParser::ProjectionsContext::ProjectionsContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::ProjectionContext *> HybridSystemParser::ProjectionsContext::projection() {
    return getRuleContexts<HybridSystemParser::ProjectionContext>();
}

HybridSystemParser::ProjectionContext *HybridSystemParser::ProjectionsContext::projection(size_t i) {
    return getRuleContext<HybridSystemParser::ProjectionContext>(i);
}


size_t HybridSystemParser::ProjectionsContext::getRuleIndex() const {
    return HybridSystemParser::RuleProjections;
}

antlrcpp::Any HybridSystemParser::ProjectionsContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitProjections(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::ProjectionsContext *HybridSystemParser::projections() {
    ProjectionsContext *_localctx = _tracker.createInstance<ProjectionsContext>(_ctx, getState());
    enterRule(_localctx, 168, HybridSystemParser::RuleProjections);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(1202);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == HybridSystemParser::T__52) {
            setState(1199);
            projection();
            setState(1204);
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

HybridSystemParser::ProjectionContext::ProjectionContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::ExpressionContext *HybridSystemParser::ProjectionContext::expression() {
    return getRuleContext<HybridSystemParser::ExpressionContext>(0);
}


size_t HybridSystemParser::ProjectionContext::getRuleIndex() const {
    return HybridSystemParser::RuleProjection;
}

antlrcpp::Any HybridSystemParser::ProjectionContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitProjection(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::ProjectionContext *HybridSystemParser::projection() {
    ProjectionContext *_localctx = _tracker.createInstance<ProjectionContext>(_ctx, getState());
    enterRule(_localctx, 170, HybridSystemParser::RuleProjection);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(1205);
        match(HybridSystemParser::T__52);
        setState(1206);
        expression();
        setState(1207);
        match(HybridSystemParser::T__53);

    }
    catch (RecognitionException &e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- OptIoDeclsContext ------------------------------------------------------------------

HybridSystemParser::OptIoDeclsContext::OptIoDeclsContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::IoDeclsContext *> HybridSystemParser::OptIoDeclsContext::ioDecls() {
    return getRuleContexts<HybridSystemParser::IoDeclsContext>();
}

HybridSystemParser::IoDeclsContext *HybridSystemParser::OptIoDeclsContext::ioDecls(size_t i) {
    return getRuleContext<HybridSystemParser::IoDeclsContext>(i);
}


size_t HybridSystemParser::OptIoDeclsContext::getRuleIndex() const {
    return HybridSystemParser::RuleOptIoDecls;
}

antlrcpp::Any HybridSystemParser::OptIoDeclsContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitOptIoDecls(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::OptIoDeclsContext *HybridSystemParser::optIoDecls() {
    OptIoDeclsContext *_localctx = _tracker.createInstance<OptIoDeclsContext>(_ctx, getState());
    enterRule(_localctx, 172, HybridSystemParser::RuleOptIoDecls);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(1212);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (((((_la - 120) & ~0x3fULL) == 0) &&
                ((1ULL << (_la - 120)) & ((1ULL << (HybridSystemParser::T__119 - 120))
                                          | (1ULL << (HybridSystemParser::T__121 - 120))
                                          | (1ULL << (HybridSystemParser::T__125 - 120))
                                          | (1ULL << (HybridSystemParser::T__127 - 120))
                                          | (1ULL << (HybridSystemParser::T__131 - 120))
                                          | (1ULL << (HybridSystemParser::T__132 - 120))
                                          | (1ULL << (HybridSystemParser::T__133 - 120)))) != 0)) {
            setState(1209);
            ioDecls();
            setState(1214);
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

//----------------- IoDeclsContext ------------------------------------------------------------------

HybridSystemParser::IoDeclsContext::IoDeclsContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::SvgFileContext *HybridSystemParser::IoDeclsContext::svgFile() {
    return getRuleContext<HybridSystemParser::SvgFileContext>(0);
}

HybridSystemParser::SvgCopyContext *HybridSystemParser::IoDeclsContext::svgCopy() {
    return getRuleContext<HybridSystemParser::SvgCopyContext>(0);
}

HybridSystemParser::SvgMoveContext *HybridSystemParser::IoDeclsContext::svgMove() {
    return getRuleContext<HybridSystemParser::SvgMoveContext>(0);
}

HybridSystemParser::SvgOutContext *HybridSystemParser::IoDeclsContext::svgOut() {
    return getRuleContext<HybridSystemParser::SvgOutContext>(0);
}

HybridSystemParser::SvgInContext *HybridSystemParser::IoDeclsContext::svgIn() {
    return getRuleContext<HybridSystemParser::SvgInContext>(0);
}

HybridSystemParser::PrintFileContext *HybridSystemParser::IoDeclsContext::printFile() {
    return getRuleContext<HybridSystemParser::PrintFileContext>(0);
}

HybridSystemParser::PrintContext *HybridSystemParser::IoDeclsContext::print() {
    return getRuleContext<HybridSystemParser::PrintContext>(0);
}


size_t HybridSystemParser::IoDeclsContext::getRuleIndex() const {
    return HybridSystemParser::RuleIoDecls;
}

antlrcpp::Any HybridSystemParser::IoDeclsContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitIoDecls(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::IoDeclsContext *HybridSystemParser::ioDecls() {
    IoDeclsContext *_localctx = _tracker.createInstance<IoDeclsContext>(_ctx, getState());
    enterRule(_localctx, 174, HybridSystemParser::RuleIoDecls);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        setState(1222);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
            case HybridSystemParser::T__119: {
                enterOuterAlt(_localctx, 1);
                setState(1215);
                svgFile();
                break;
            }

            case HybridSystemParser::T__121: {
                enterOuterAlt(_localctx, 2);
                setState(1216);
                svgCopy();
                break;
            }

            case HybridSystemParser::T__125: {
                enterOuterAlt(_localctx, 3);
                setState(1217);
                svgMove();
                break;
            }

            case HybridSystemParser::T__127: {
                enterOuterAlt(_localctx, 4);
                setState(1218);
                svgOut();
                break;
            }

            case HybridSystemParser::T__131: {
                enterOuterAlt(_localctx, 5);
                setState(1219);
                svgIn();
                break;
            }

            case HybridSystemParser::T__132: {
                enterOuterAlt(_localctx, 6);
                setState(1220);
                printFile();
                break;
            }

            case HybridSystemParser::T__133: {
                enterOuterAlt(_localctx, 7);
                setState(1221);
                print();
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

//----------------- SvgFileContext ------------------------------------------------------------------

HybridSystemParser::SvgFileContext::SvgFileContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::StringTokenContext *HybridSystemParser::SvgFileContext::stringToken() {
    return getRuleContext<HybridSystemParser::StringTokenContext>(0);
}


size_t HybridSystemParser::SvgFileContext::getRuleIndex() const {
    return HybridSystemParser::RuleSvgFile;
}

antlrcpp::Any HybridSystemParser::SvgFileContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitSvgFile(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::SvgFileContext *HybridSystemParser::svgFile() {
    SvgFileContext *_localctx = _tracker.createInstance<SvgFileContext>(_ctx, getState());
    enterRule(_localctx, 176, HybridSystemParser::RuleSvgFile);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(1224);
        match(HybridSystemParser::T__119);
        setState(1225);
        stringToken();
        setState(1226);
        match(HybridSystemParser::T__1);

    }
    catch (RecognitionException &e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- OptSvgFileContext ------------------------------------------------------------------

HybridSystemParser::OptSvgFileContext::OptSvgFileContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::StringTokenContext *HybridSystemParser::OptSvgFileContext::stringToken() {
    return getRuleContext<HybridSystemParser::StringTokenContext>(0);
}


size_t HybridSystemParser::OptSvgFileContext::getRuleIndex() const {
    return HybridSystemParser::RuleOptSvgFile;
}

antlrcpp::Any HybridSystemParser::OptSvgFileContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitOptSvgFile(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::OptSvgFileContext *HybridSystemParser::optSvgFile() {
    OptSvgFileContext *_localctx = _tracker.createInstance<OptSvgFileContext>(_ctx, getState());
    enterRule(_localctx, 178, HybridSystemParser::RuleOptSvgFile);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(1230);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == HybridSystemParser::T__120) {
            setState(1228);
            match(HybridSystemParser::T__120);
            setState(1229);
            stringToken();
        }

    }
    catch (RecognitionException &e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- SvgCopyContext ------------------------------------------------------------------

HybridSystemParser::SvgCopyContext::SvgCopyContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::ExpressionContext *HybridSystemParser::SvgCopyContext::expression() {
    return getRuleContext<HybridSystemParser::ExpressionContext>(0);
}

HybridSystemParser::OptSvgCopyPreContext *HybridSystemParser::SvgCopyContext::optSvgCopyPre() {
    return getRuleContext<HybridSystemParser::OptSvgCopyPreContext>(0);
}

HybridSystemParser::OptSvgCopyPostContext *HybridSystemParser::SvgCopyContext::optSvgCopyPost() {
    return getRuleContext<HybridSystemParser::OptSvgCopyPostContext>(0);
}

HybridSystemParser::OptSvgFileContext *HybridSystemParser::SvgCopyContext::optSvgFile() {
    return getRuleContext<HybridSystemParser::OptSvgFileContext>(0);
}


size_t HybridSystemParser::SvgCopyContext::getRuleIndex() const {
    return HybridSystemParser::RuleSvgCopy;
}

antlrcpp::Any HybridSystemParser::SvgCopyContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitSvgCopy(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::SvgCopyContext *HybridSystemParser::svgCopy() {
    SvgCopyContext *_localctx = _tracker.createInstance<SvgCopyContext>(_ctx, getState());
    enterRule(_localctx, 180, HybridSystemParser::RuleSvgCopy);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(1232);
        match(HybridSystemParser::T__121);
        setState(1233);
        match(HybridSystemParser::T__122);
        setState(1234);
        expression();
        setState(1235);
        optSvgCopyPre();
        setState(1236);
        optSvgCopyPost();
        setState(1237);
        optSvgFile();
        setState(1238);
        match(HybridSystemParser::T__1);

    }
    catch (RecognitionException &e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- OptSvgCopyPreContext ------------------------------------------------------------------

HybridSystemParser::OptSvgCopyPreContext::OptSvgCopyPreContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::ExpressionContext *HybridSystemParser::OptSvgCopyPreContext::expression() {
    return getRuleContext<HybridSystemParser::ExpressionContext>(0);
}


size_t HybridSystemParser::OptSvgCopyPreContext::getRuleIndex() const {
    return HybridSystemParser::RuleOptSvgCopyPre;
}

antlrcpp::Any HybridSystemParser::OptSvgCopyPreContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitOptSvgCopyPre(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::OptSvgCopyPreContext *HybridSystemParser::optSvgCopyPre() {
    OptSvgCopyPreContext *_localctx = _tracker.createInstance<OptSvgCopyPreContext>(_ctx, getState());
    enterRule(_localctx, 182, HybridSystemParser::RuleOptSvgCopyPre);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(1242);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == HybridSystemParser::T__123) {
            setState(1240);
            match(HybridSystemParser::T__123);
            setState(1241);
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

//----------------- OptSvgCopyPostContext ------------------------------------------------------------------

HybridSystemParser::OptSvgCopyPostContext::OptSvgCopyPostContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::ExpressionContext *HybridSystemParser::OptSvgCopyPostContext::expression() {
    return getRuleContext<HybridSystemParser::ExpressionContext>(0);
}


size_t HybridSystemParser::OptSvgCopyPostContext::getRuleIndex() const {
    return HybridSystemParser::RuleOptSvgCopyPost;
}

antlrcpp::Any HybridSystemParser::OptSvgCopyPostContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitOptSvgCopyPost(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::OptSvgCopyPostContext *HybridSystemParser::optSvgCopyPost() {
    OptSvgCopyPostContext *_localctx = _tracker.createInstance<OptSvgCopyPostContext>(_ctx, getState());
    enterRule(_localctx, 184, HybridSystemParser::RuleOptSvgCopyPost);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(1246);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == HybridSystemParser::T__124) {
            setState(1244);
            match(HybridSystemParser::T__124);
            setState(1245);
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

//----------------- SvgMoveContext ------------------------------------------------------------------

HybridSystemParser::SvgMoveContext::SvgMoveContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::ExpressionContext *> HybridSystemParser::SvgMoveContext::expression() {
    return getRuleContexts<HybridSystemParser::ExpressionContext>();
}

HybridSystemParser::ExpressionContext *HybridSystemParser::SvgMoveContext::expression(size_t i) {
    return getRuleContext<HybridSystemParser::ExpressionContext>(i);
}

HybridSystemParser::SvgFileContext *HybridSystemParser::SvgMoveContext::svgFile() {
    return getRuleContext<HybridSystemParser::SvgFileContext>(0);
}


size_t HybridSystemParser::SvgMoveContext::getRuleIndex() const {
    return HybridSystemParser::RuleSvgMove;
}

antlrcpp::Any HybridSystemParser::SvgMoveContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitSvgMove(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::SvgMoveContext *HybridSystemParser::svgMove() {
    SvgMoveContext *_localctx = _tracker.createInstance<SvgMoveContext>(_ctx, getState());
    enterRule(_localctx, 186, HybridSystemParser::RuleSvgMove);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        setState(1268);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 83, _ctx)) {
            case 1: {
                enterOuterAlt(_localctx, 1);
                setState(1248);
                match(HybridSystemParser::T__125);
                setState(1249);
                match(HybridSystemParser::T__122);
                setState(1250);
                expression();
                setState(1251);
                match(HybridSystemParser::T__126);
                setState(1252);
                expression();
                setState(1253);
                match(HybridSystemParser::T__22);
                setState(1254);
                expression();
                setState(1255);
                match(HybridSystemParser::T__1);
                break;
            }

            case 2: {
                enterOuterAlt(_localctx, 2);
                setState(1257);
                match(HybridSystemParser::T__125);
                setState(1258);
                match(HybridSystemParser::T__122);
                setState(1259);
                expression();
                setState(1260);
                match(HybridSystemParser::T__126);
                setState(1261);
                expression();
                setState(1262);
                match(HybridSystemParser::T__22);
                setState(1263);
                expression();
                setState(1264);
                match(HybridSystemParser::T__4);
                setState(1265);
                svgFile();
                setState(1266);
                match(HybridSystemParser::T__7);
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

//----------------- SvgOutContext ------------------------------------------------------------------

HybridSystemParser::SvgOutContext::SvgOutContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::ExpressionContext *> HybridSystemParser::SvgOutContext::expression() {
    return getRuleContexts<HybridSystemParser::ExpressionContext>();
}

HybridSystemParser::ExpressionContext *HybridSystemParser::SvgOutContext::expression(size_t i) {
    return getRuleContext<HybridSystemParser::ExpressionContext>(i);
}

HybridSystemParser::SvgAttrContext *HybridSystemParser::SvgOutContext::svgAttr() {
    return getRuleContext<HybridSystemParser::SvgAttrContext>(0);
}

HybridSystemParser::OptSvgFileContext *HybridSystemParser::SvgOutContext::optSvgFile() {
    return getRuleContext<HybridSystemParser::OptSvgFileContext>(0);
}


size_t HybridSystemParser::SvgOutContext::getRuleIndex() const {
    return HybridSystemParser::RuleSvgOut;
}

antlrcpp::Any HybridSystemParser::SvgOutContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitSvgOut(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::SvgOutContext *HybridSystemParser::svgOut() {
    SvgOutContext *_localctx = _tracker.createInstance<SvgOutContext>(_ctx, getState());
    enterRule(_localctx, 188, HybridSystemParser::RuleSvgOut);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(1270);
        match(HybridSystemParser::T__127);
        setState(1271);
        match(HybridSystemParser::T__122);
        setState(1272);
        expression();
        setState(1273);
        svgAttr();
        setState(1274);
        match(HybridSystemParser::T__128);
        setState(1275);
        expression();
        setState(1276);
        optSvgFile();
        setState(1277);
        match(HybridSystemParser::T__1);

    }
    catch (RecognitionException &e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- SvgAttrContext ------------------------------------------------------------------

HybridSystemParser::SvgAttrContext::SvgAttrContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::StringTokenContext *HybridSystemParser::SvgAttrContext::stringToken() {
    return getRuleContext<HybridSystemParser::StringTokenContext>(0);
}


size_t HybridSystemParser::SvgAttrContext::getRuleIndex() const {
    return HybridSystemParser::RuleSvgAttr;
}

antlrcpp::Any HybridSystemParser::SvgAttrContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitSvgAttr(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::SvgAttrContext *HybridSystemParser::svgAttr() {
    SvgAttrContext *_localctx = _tracker.createInstance<SvgAttrContext>(_ctx, getState());
    enterRule(_localctx, 190, HybridSystemParser::RuleSvgAttr);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        setState(1282);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
            case HybridSystemParser::T__129: {
                enterOuterAlt(_localctx, 1);
                setState(1279);
                match(HybridSystemParser::T__129);
                setState(1280);
                stringToken();
                break;
            }

            case HybridSystemParser::T__130: {
                enterOuterAlt(_localctx, 2);
                setState(1281);
                match(HybridSystemParser::T__130);
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

//----------------- SvgInContext ------------------------------------------------------------------

HybridSystemParser::SvgInContext::SvgInContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::ExpressionContext *HybridSystemParser::SvgInContext::expression() {
    return getRuleContext<HybridSystemParser::ExpressionContext>(0);
}

HybridSystemParser::SvgInEventContext *HybridSystemParser::SvgInContext::svgInEvent() {
    return getRuleContext<HybridSystemParser::SvgInEventContext>(0);
}

HybridSystemParser::OptSvgFileContext *HybridSystemParser::SvgInContext::optSvgFile() {
    return getRuleContext<HybridSystemParser::OptSvgFileContext>(0);
}


size_t HybridSystemParser::SvgInContext::getRuleIndex() const {
    return HybridSystemParser::RuleSvgIn;
}

antlrcpp::Any HybridSystemParser::SvgInContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitSvgIn(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::SvgInContext *HybridSystemParser::svgIn() {
    SvgInContext *_localctx = _tracker.createInstance<SvgInContext>(_ctx, getState());
    enterRule(_localctx, 192, HybridSystemParser::RuleSvgIn);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(1284);
        match(HybridSystemParser::T__131);
        setState(1285);
        match(HybridSystemParser::T__122);
        setState(1286);
        expression();
        setState(1287);
        match(HybridSystemParser::T__14);
        setState(1288);
        svgInEvent();
        setState(1289);
        optSvgFile();
        setState(1290);
        match(HybridSystemParser::T__1);

    }
    catch (RecognitionException &e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- SvgInEventContext ------------------------------------------------------------------

HybridSystemParser::SvgInEventContext::SvgInEventContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::NameContext *> HybridSystemParser::SvgInEventContext::name() {
    return getRuleContexts<HybridSystemParser::NameContext>();
}

HybridSystemParser::NameContext *HybridSystemParser::SvgInEventContext::name(size_t i) {
    return getRuleContext<HybridSystemParser::NameContext>(i);
}

HybridSystemParser::ExpressionContext *HybridSystemParser::SvgInEventContext::expression() {
    return getRuleContext<HybridSystemParser::ExpressionContext>(0);
}

HybridSystemParser::OptSvgInEventElifsContext *HybridSystemParser::SvgInEventContext::optSvgInEventElifs() {
    return getRuleContext<HybridSystemParser::OptSvgInEventElifsContext>(0);
}

HybridSystemParser::SvgInEventElifsContext *HybridSystemParser::SvgInEventContext::svgInEventElifs() {
    return getRuleContext<HybridSystemParser::SvgInEventElifsContext>(0);
}


size_t HybridSystemParser::SvgInEventContext::getRuleIndex() const {
    return HybridSystemParser::RuleSvgInEvent;
}

antlrcpp::Any HybridSystemParser::SvgInEventContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitSvgInEvent(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::SvgInEventContext *HybridSystemParser::svgInEvent() {
    SvgInEventContext *_localctx = _tracker.createInstance<SvgInEventContext>(_ctx, getState());
    enterRule(_localctx, 194, HybridSystemParser::RuleSvgInEvent);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        setState(1309);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 85, _ctx)) {
            case 1: {
                enterOuterAlt(_localctx, 1);
                setState(1292);
                name();
                break;
            }

            case 2: {
                enterOuterAlt(_localctx, 2);
                setState(1293);
                match(HybridSystemParser::T__29);
                setState(1294);
                expression();
                setState(1295);
                match(HybridSystemParser::T__4);
                setState(1296);
                name();
                setState(1297);
                optSvgInEventElifs();
                setState(1298);
                match(HybridSystemParser::T__35);
                setState(1299);
                name();
                setState(1300);
                match(HybridSystemParser::T__7);
                break;
            }

            case 3: {
                enterOuterAlt(_localctx, 3);
                setState(1302);
                match(HybridSystemParser::T__29);
                setState(1303);
                expression();
                setState(1304);
                match(HybridSystemParser::T__4);
                setState(1305);
                name();
                setState(1306);
                svgInEventElifs();
                setState(1307);
                match(HybridSystemParser::T__7);
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

//----------------- OptSvgInEventElifsContext ------------------------------------------------------------------

HybridSystemParser::OptSvgInEventElifsContext::OptSvgInEventElifsContext(ParserRuleContext *parent,
                                                                         size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::SvgInEventElifsContext *HybridSystemParser::OptSvgInEventElifsContext::svgInEventElifs() {
    return getRuleContext<HybridSystemParser::SvgInEventElifsContext>(0);
}


size_t HybridSystemParser::OptSvgInEventElifsContext::getRuleIndex() const {
    return HybridSystemParser::RuleOptSvgInEventElifs;
}

antlrcpp::Any HybridSystemParser::OptSvgInEventElifsContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitOptSvgInEventElifs(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::OptSvgInEventElifsContext *HybridSystemParser::optSvgInEventElifs() {
    OptSvgInEventElifsContext *_localctx = _tracker.createInstance<OptSvgInEventElifsContext>(_ctx, getState());
    enterRule(_localctx, 196, HybridSystemParser::RuleOptSvgInEventElifs);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(1312);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == HybridSystemParser::T__34) {
            setState(1311);
            svgInEventElifs();
        }

    }
    catch (RecognitionException &e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- SvgInEventElifsContext ------------------------------------------------------------------

HybridSystemParser::SvgInEventElifsContext::SvgInEventElifsContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::ExpressionContext *> HybridSystemParser::SvgInEventElifsContext::expression() {
    return getRuleContexts<HybridSystemParser::ExpressionContext>();
}

HybridSystemParser::ExpressionContext *HybridSystemParser::SvgInEventElifsContext::expression(size_t i) {
    return getRuleContext<HybridSystemParser::ExpressionContext>(i);
}

std::vector<HybridSystemParser::NameContext *> HybridSystemParser::SvgInEventElifsContext::name() {
    return getRuleContexts<HybridSystemParser::NameContext>();
}

HybridSystemParser::NameContext *HybridSystemParser::SvgInEventElifsContext::name(size_t i) {
    return getRuleContext<HybridSystemParser::NameContext>(i);
}


size_t HybridSystemParser::SvgInEventElifsContext::getRuleIndex() const {
    return HybridSystemParser::RuleSvgInEventElifs;
}

antlrcpp::Any HybridSystemParser::SvgInEventElifsContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitSvgInEventElifs(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::SvgInEventElifsContext *HybridSystemParser::svgInEventElifs() {
    SvgInEventElifsContext *_localctx = _tracker.createInstance<SvgInEventElifsContext>(_ctx, getState());
    enterRule(_localctx, 198, HybridSystemParser::RuleSvgInEventElifs);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(1319);
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
            setState(1314);
            match(HybridSystemParser::T__34);
            setState(1315);
            expression();
            setState(1316);
            match(HybridSystemParser::T__4);
            setState(1317);
            name();
            setState(1321);
            _errHandler->sync(this);
            _la = _input->LA(1);
        } while (_la == HybridSystemParser::T__34);

    }
    catch (RecognitionException &e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- PrintFileContext ------------------------------------------------------------------

HybridSystemParser::PrintFileContext::PrintFileContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::StringTokenContext *HybridSystemParser::PrintFileContext::stringToken() {
    return getRuleContext<HybridSystemParser::StringTokenContext>(0);
}


size_t HybridSystemParser::PrintFileContext::getRuleIndex() const {
    return HybridSystemParser::RulePrintFile;
}

antlrcpp::Any HybridSystemParser::PrintFileContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitPrintFile(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::PrintFileContext *HybridSystemParser::printFile() {
    PrintFileContext *_localctx = _tracker.createInstance<PrintFileContext>(_ctx, getState());
    enterRule(_localctx, 200, HybridSystemParser::RulePrintFile);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(1323);
        match(HybridSystemParser::T__132);
        setState(1324);
        stringToken();
        setState(1325);
        match(HybridSystemParser::T__1);

    }
    catch (RecognitionException &e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- PrintContext ------------------------------------------------------------------

HybridSystemParser::PrintContext::PrintContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::PrintTxtContext *HybridSystemParser::PrintContext::printTxt() {
    return getRuleContext<HybridSystemParser::PrintTxtContext>(0);
}

HybridSystemParser::OptPrintForsContext *HybridSystemParser::PrintContext::optPrintFors() {
    return getRuleContext<HybridSystemParser::OptPrintForsContext>(0);
}

HybridSystemParser::OptPrintWhenContext *HybridSystemParser::PrintContext::optPrintWhen() {
    return getRuleContext<HybridSystemParser::OptPrintWhenContext>(0);
}

HybridSystemParser::OptPrintFileContext *HybridSystemParser::PrintContext::optPrintFile() {
    return getRuleContext<HybridSystemParser::OptPrintFileContext>(0);
}


size_t HybridSystemParser::PrintContext::getRuleIndex() const {
    return HybridSystemParser::RulePrint;
}

antlrcpp::Any HybridSystemParser::PrintContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitPrint(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::PrintContext *HybridSystemParser::print() {
    PrintContext *_localctx = _tracker.createInstance<PrintContext>(_ctx, getState());
    enterRule(_localctx, 202, HybridSystemParser::RulePrint);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(1327);
        match(HybridSystemParser::T__133);
        setState(1328);
        printTxt();
        setState(1329);
        optPrintFors();
        setState(1330);
        optPrintWhen();
        setState(1331);
        optPrintFile();
        setState(1332);
        match(HybridSystemParser::T__1);

    }
    catch (RecognitionException &e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- PrintTxtContext ------------------------------------------------------------------

HybridSystemParser::PrintTxtContext::PrintTxtContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::ExpressionContext *> HybridSystemParser::PrintTxtContext::expression() {
    return getRuleContexts<HybridSystemParser::ExpressionContext>();
}

HybridSystemParser::ExpressionContext *HybridSystemParser::PrintTxtContext::expression(size_t i) {
    return getRuleContext<HybridSystemParser::ExpressionContext>(i);
}


size_t HybridSystemParser::PrintTxtContext::getRuleIndex() const {
    return HybridSystemParser::RulePrintTxt;
}

antlrcpp::Any HybridSystemParser::PrintTxtContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitPrintTxt(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::PrintTxtContext *HybridSystemParser::printTxt() {
    PrintTxtContext *_localctx = _tracker.createInstance<PrintTxtContext>(_ctx, getState());
    enterRule(_localctx, 204, HybridSystemParser::RulePrintTxt);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        setState(1344);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 88, _ctx)) {
            case 1: {
                enterOuterAlt(_localctx, 1);
                setState(1334);
                expression();
                break;
            }

            case 2: {
                enterOuterAlt(_localctx, 2);
                setState(1335);
                match(HybridSystemParser::T__123);
                setState(1336);
                expression();
                break;
            }

            case 3: {
                enterOuterAlt(_localctx, 3);
                setState(1337);
                match(HybridSystemParser::T__124);
                setState(1338);
                expression();
                break;
            }

            case 4: {
                enterOuterAlt(_localctx, 4);
                setState(1339);
                match(HybridSystemParser::T__123);
                setState(1340);
                expression();
                setState(1341);
                match(HybridSystemParser::T__124);
                setState(1342);
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

//----------------- OptPrintForsContext ------------------------------------------------------------------

HybridSystemParser::OptPrintForsContext::OptPrintForsContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::PrintForsContext *HybridSystemParser::OptPrintForsContext::printFors() {
    return getRuleContext<HybridSystemParser::PrintForsContext>(0);
}


size_t HybridSystemParser::OptPrintForsContext::getRuleIndex() const {
    return HybridSystemParser::RuleOptPrintFors;
}

antlrcpp::Any HybridSystemParser::OptPrintForsContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitOptPrintFors(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::OptPrintForsContext *HybridSystemParser::optPrintFors() {
    OptPrintForsContext *_localctx = _tracker.createInstance<OptPrintForsContext>(_ctx, getState());
    enterRule(_localctx, 206, HybridSystemParser::RuleOptPrintFors);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(1348);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == HybridSystemParser::T__134) {
            setState(1346);
            match(HybridSystemParser::T__134);
            setState(1347);
            printFors();
        }

    }
    catch (RecognitionException &e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- PrintForsContext ------------------------------------------------------------------

HybridSystemParser::PrintForsContext::PrintForsContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::PrintForContext *> HybridSystemParser::PrintForsContext::printFor() {
    return getRuleContexts<HybridSystemParser::PrintForContext>();
}

HybridSystemParser::PrintForContext *HybridSystemParser::PrintForsContext::printFor(size_t i) {
    return getRuleContext<HybridSystemParser::PrintForContext>(i);
}


size_t HybridSystemParser::PrintForsContext::getRuleIndex() const {
    return HybridSystemParser::RulePrintFors;
}

antlrcpp::Any HybridSystemParser::PrintForsContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitPrintFors(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::PrintForsContext *HybridSystemParser::printFors() {
    PrintForsContext *_localctx = _tracker.createInstance<PrintForsContext>(_ctx, getState());
    enterRule(_localctx, 208, HybridSystemParser::RulePrintFors);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(1350);
        printFor();
        setState(1355);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == HybridSystemParser::T__22) {
            setState(1351);
            match(HybridSystemParser::T__22);
            setState(1352);
            printFor();
            setState(1357);
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

//----------------- PrintForContext ------------------------------------------------------------------

HybridSystemParser::PrintForContext::PrintForContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::NameContext *HybridSystemParser::PrintForContext::name() {
    return getRuleContext<HybridSystemParser::NameContext>(0);
}


size_t HybridSystemParser::PrintForContext::getRuleIndex() const {
    return HybridSystemParser::RulePrintFor;
}

antlrcpp::Any HybridSystemParser::PrintForContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitPrintFor(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::PrintForContext *HybridSystemParser::printFor() {
    PrintForContext *_localctx = _tracker.createInstance<PrintForContext>(_ctx, getState());
    enterRule(_localctx, 210, HybridSystemParser::RulePrintFor);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        setState(1363);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
            case HybridSystemParser::T__14: {
                enterOuterAlt(_localctx, 1);
                setState(1358);
                match(HybridSystemParser::T__14);
                break;
            }

            case HybridSystemParser::T__56: {
                enterOuterAlt(_localctx, 2);
                setState(1359);
                match(HybridSystemParser::T__56);
                break;
            }

            case HybridSystemParser::IDENTIFIER:
            case HybridSystemParser::RELATIVENAME:
            case HybridSystemParser::ABSOLUTENAME:
            case HybridSystemParser::ROOTNAME: {
                enterOuterAlt(_localctx, 3);
                setState(1360);
                name();
                break;
            }

            case HybridSystemParser::T__20: {
                enterOuterAlt(_localctx, 4);
                setState(1361);
                match(HybridSystemParser::T__20);
                break;
            }

            case HybridSystemParser::T__135: {
                enterOuterAlt(_localctx, 5);
                setState(1362);
                match(HybridSystemParser::T__135);
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

//----------------- OptPrintWhenContext ------------------------------------------------------------------

HybridSystemParser::OptPrintWhenContext::OptPrintWhenContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

std::vector<HybridSystemParser::ExpressionContext *> HybridSystemParser::OptPrintWhenContext::expression() {
    return getRuleContexts<HybridSystemParser::ExpressionContext>();
}

HybridSystemParser::ExpressionContext *HybridSystemParser::OptPrintWhenContext::expression(size_t i) {
    return getRuleContext<HybridSystemParser::ExpressionContext>(i);
}


size_t HybridSystemParser::OptPrintWhenContext::getRuleIndex() const {
    return HybridSystemParser::RuleOptPrintWhen;
}

antlrcpp::Any HybridSystemParser::OptPrintWhenContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitOptPrintWhen(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::OptPrintWhenContext *HybridSystemParser::optPrintWhen() {
    OptPrintWhenContext *_localctx = _tracker.createInstance<OptPrintWhenContext>(_ctx, getState());
    enterRule(_localctx, 212, HybridSystemParser::RuleOptPrintWhen);

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(1379);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 92, _ctx)) {
            case 1: {
                setState(1365);
                match(HybridSystemParser::T__111);
                setState(1366);
                expression();
                break;
            }

            case 2: {
                setState(1367);
                match(HybridSystemParser::T__111);
                setState(1368);
                match(HybridSystemParser::T__123);
                setState(1369);
                expression();
                break;
            }

            case 3: {
                setState(1370);
                match(HybridSystemParser::T__111);
                setState(1371);
                match(HybridSystemParser::T__124);
                setState(1372);
                expression();
                break;
            }

            case 4: {
                setState(1373);
                match(HybridSystemParser::T__111);
                setState(1374);
                match(HybridSystemParser::T__123);
                setState(1375);
                expression();
                setState(1376);
                match(HybridSystemParser::T__124);
                setState(1377);
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

//----------------- OptPrintFileContext ------------------------------------------------------------------

HybridSystemParser::OptPrintFileContext::OptPrintFileContext(ParserRuleContext *parent, size_t invokingState)
        : ParserRuleContext(parent, invokingState) {
}

HybridSystemParser::StringTokenContext *HybridSystemParser::OptPrintFileContext::stringToken() {
    return getRuleContext<HybridSystemParser::StringTokenContext>(0);
}


size_t HybridSystemParser::OptPrintFileContext::getRuleIndex() const {
    return HybridSystemParser::RuleOptPrintFile;
}

antlrcpp::Any HybridSystemParser::OptPrintFileContext::accept(tree::ParseTreeVisitor *visitor) {
    if (auto parserVisitor = dynamic_cast<HybridSystemVisitor *>(visitor))
        return parserVisitor->visitOptPrintFile(this);
    else
        return visitor->visitChildren(this);
}

HybridSystemParser::OptPrintFileContext *HybridSystemParser::optPrintFile() {
    OptPrintFileContext *_localctx = _tracker.createInstance<OptPrintFileContext>(_ctx, getState());
    enterRule(_localctx, 214, HybridSystemParser::RuleOptPrintFile);
    size_t _la = 0;

    auto onExit = finally([=] {
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(1383);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == HybridSystemParser::T__120) {
            setState(1381);
            match(HybridSystemParser::T__120);
            setState(1382);
            stringToken();
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
std::vector <dfa::DFA> HybridSystemParser::_decisionToDFA;
atn::PredictionContextCache HybridSystemParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN HybridSystemParser::_atn;
std::vector <uint16_t> HybridSystemParser::_serializedATN;

std::vector <std::string> HybridSystemParser::_ruleNames = {
        "specification", "groupBody", "automatonBody", "optGroupDecls", "groupDecl",
        "optAutDecls", "autDecl", "decl", "imports", "typeDefs", "enumDefs", "constantDefs",
        "algVarsDefs", "funcParams", "funcParamDecls", "funcBody", "funcVarDecls",
        "funcVarDecl", "funcStatements", "funcStatement", "optElifFuncStats",
        "optElseFuncStat", "events", "actualParms", "formalParms", "formalDecls",
        "formalDeclaration", "discDecls", "discDecl", "contDecls", "contDecl",
        "optDerivate", "optControllability", "controllability", "eventType", "expressions",
        "optExpression", "expression", "equations", "equation", "orExpression",
        "andExpression", "compareExpression", "addExpression", "mulExpression",
        "unaryExpression", "funcExpression", "expressionFactor", "nonEmptySetExpression",
        "dictPairs", "optElifExprs", "switchBody", "switchCases", "types", "type",
        "fields", "field", "nameSet", "names", "name", "optSupKind", "supKind",
        "identifier", "stringToken", "stdLibFunction", "locations", "location",
        "locationElements", "locationElement", "coreEdge", "optEdgeGuard", "optEdgeUrgent",
        "optEdgeUpdate", "edgeEvents", "edgeEvent", "invariantDecls", "invariants",
        "invariant", "updates", "update", "optElifUpdates", "optElseUpdate", "adressables",
        "adressable", "projections", "projection", "optIoDecls", "ioDecls", "svgFile",
        "optSvgFile", "svgCopy", "optSvgCopyPre", "optSvgCopyPost", "svgMove",
        "svgOut", "svgAttr", "svgIn", "svgInEvent", "optSvgInEventElifs", "svgInEventElifs",
        "printFile", "print", "printTxt", "optPrintFors", "printFors", "printFor",
        "optPrintWhen", "optPrintFile"
};

std::vector <std::string> HybridSystemParser::_literalNames = {
        "", "'import'", "';'", "'namespace'", "'func'", "':'", "'group'", "'def'",
        "'end'", "'automaton'", "'alphabet'", "'monitor'", "'disc'", "'type'",
        "'enum'", "'event'", "'const'", "'alg'", "'input'", "'cont'", "'equation'",
        "'initial'", "'marked'", "','", "'='", "'{'", "'}'", "'('", "')'", "':='",
        "'if'", "'while'", "'break'", "'continue'", "'return'", "'elif'", "'else'",
        "'location'", "'in'", "'any'", "'der'", "'controllable'", "'uncontrollable'",
        "'void'", "'=>'", "'<=>'", "'''", "'or'", "'and'", "'-'", "'+'", "'not'",
        "'sample'", "'['", "']'", "'true'", "'false'", "'time'", "'<'", "'>'",
        "'switch'", "'?'", "'self'", "'case'", "'bool'", "'int'", "'..'", "'real'",
        "'string'", "'list'", "'set'", "'dict'", "'tuple'", "'dist'", "'plant'",
        "'requirement'", "'supervisor'", "'acosh'", "'acos'", "'asinh'", "'asin'",
        "'atanh'", "'cosh'", "'cos'", "'sinh'", "'sin'", "'tanh'", "'tan'", "'abs'",
        "'cbrt'", "'ceil'", "'del'", "'empty'", "'exp'", "'floor'", "'fmt'", "'ln'",
        "'log'", "'max'", "'min'", "'pop'", "'pow'", "'round'", "'scale'", "'sign'",
        "'size'", "'sqrt'", "'bernoulli'", "'beta'", "'urgent'", "'edge'", "'goto'",
        "'when'", "'now'", "'do'", "'tau'", "'!'", "'invariant'", "'needs'", "'disables'",
        "'svgFile'", "'file'", "'svgCopy'", "'id'", "'pre'", "'post'", "'svgmove'",
        "'to'", "'svgout'", "'value'", "'attr'", "'text'", "'svgin'", "'printFile'",
        "'print'", "'for'", "'final'"
};

std::vector <std::string> HybridSystemParser::_symbolicNames = {
        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "", "", "MULOP", "ADDOP", "COMPOP",
        "NUMBER", "REALNUMBER", "STRING", "IDENTIFIER", "RELATIVENAME", "ABSOLUTENAME",
        "ROOTNAME", "WS"
};

dfa::Vocabulary HybridSystemParser::_vocabulary(_literalNames, _symbolicNames);

std::vector <std::string> HybridSystemParser::_tokenNames;

HybridSystemParser::Initializer::Initializer() {
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
            0x3, 0x95, 0x56c, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4,
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
            0x32, 0x4, 0x33, 0x9, 0x33, 0x4, 0x34, 0x9, 0x34, 0x4, 0x35, 0x9, 0x35,
            0x4, 0x36, 0x9, 0x36, 0x4, 0x37, 0x9, 0x37, 0x4, 0x38, 0x9, 0x38, 0x4,
            0x39, 0x9, 0x39, 0x4, 0x3a, 0x9, 0x3a, 0x4, 0x3b, 0x9, 0x3b, 0x4, 0x3c,
            0x9, 0x3c, 0x4, 0x3d, 0x9, 0x3d, 0x4, 0x3e, 0x9, 0x3e, 0x4, 0x3f, 0x9,
            0x3f, 0x4, 0x40, 0x9, 0x40, 0x4, 0x41, 0x9, 0x41, 0x4, 0x42, 0x9, 0x42,
            0x4, 0x43, 0x9, 0x43, 0x4, 0x44, 0x9, 0x44, 0x4, 0x45, 0x9, 0x45, 0x4,
            0x46, 0x9, 0x46, 0x4, 0x47, 0x9, 0x47, 0x4, 0x48, 0x9, 0x48, 0x4, 0x49,
            0x9, 0x49, 0x4, 0x4a, 0x9, 0x4a, 0x4, 0x4b, 0x9, 0x4b, 0x4, 0x4c, 0x9,
            0x4c, 0x4, 0x4d, 0x9, 0x4d, 0x4, 0x4e, 0x9, 0x4e, 0x4, 0x4f, 0x9, 0x4f,
            0x4, 0x50, 0x9, 0x50, 0x4, 0x51, 0x9, 0x51, 0x4, 0x52, 0x9, 0x52, 0x4,
            0x53, 0x9, 0x53, 0x4, 0x54, 0x9, 0x54, 0x4, 0x55, 0x9, 0x55, 0x4, 0x56,
            0x9, 0x56, 0x4, 0x57, 0x9, 0x57, 0x4, 0x58, 0x9, 0x58, 0x4, 0x59, 0x9,
            0x59, 0x4, 0x5a, 0x9, 0x5a, 0x4, 0x5b, 0x9, 0x5b, 0x4, 0x5c, 0x9, 0x5c,
            0x4, 0x5d, 0x9, 0x5d, 0x4, 0x5e, 0x9, 0x5e, 0x4, 0x5f, 0x9, 0x5f, 0x4,
            0x60, 0x9, 0x60, 0x4, 0x61, 0x9, 0x61, 0x4, 0x62, 0x9, 0x62, 0x4, 0x63,
            0x9, 0x63, 0x4, 0x64, 0x9, 0x64, 0x4, 0x65, 0x9, 0x65, 0x4, 0x66, 0x9,
            0x66, 0x4, 0x67, 0x9, 0x67, 0x4, 0x68, 0x9, 0x68, 0x4, 0x69, 0x9, 0x69,
            0x4, 0x6a, 0x9, 0x6a, 0x4, 0x6b, 0x9, 0x6b, 0x4, 0x6c, 0x9, 0x6c, 0x4,
            0x6d, 0x9, 0x6d, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x4, 0x3,
            0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x5, 0x7, 0x5, 0xe4, 0xa, 0x5, 0xc, 0x5,
            0xe, 0x5, 0xe7, 0xb, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3,
            0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3,
            0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3,
            0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3,
            0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3,
            0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3,
            0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3,
            0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3,
            0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3,
            0x6, 0x5, 0x6, 0x126, 0xa, 0x6, 0x3, 0x7, 0x7, 0x7, 0x129, 0xa, 0x7,
            0xc, 0x7, 0xe, 0x7, 0x12c, 0xb, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3,
            0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3,
            0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3,
            0x8, 0x5, 0x8, 0x140, 0xa, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9,
            0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9,
            0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9,
            0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9,
            0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9,
            0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9,
            0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9,
            0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9,
            0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9,
            0x3, 0x9, 0x5, 0x9, 0x17f, 0xa, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x7,
            0xa, 0x184, 0xa, 0xa, 0xc, 0xa, 0xe, 0xa, 0x187, 0xb, 0xa, 0x3, 0xb,
            0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb,
            0x7, 0xb, 0x191, 0xa, 0xb, 0xc, 0xb, 0xe, 0xb, 0x194, 0xb, 0xb, 0x3,
            0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3,
            0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x7, 0xc, 0x1a2, 0xa, 0xc,
            0xc, 0xc, 0xe, 0xc, 0x1a5, 0xb, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3,
            0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x7, 0xd, 0x1af, 0xa, 0xd,
            0xc, 0xd, 0xe, 0xd, 0x1b2, 0xb, 0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3,
            0xe, 0x3, 0xe, 0x5, 0xe, 0x1b9, 0xa, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe,
            0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x5, 0xe, 0x1c1, 0xa, 0xe, 0x7, 0xe, 0x1c3,
            0xa, 0xe, 0xc, 0xe, 0xe, 0xe, 0x1c6, 0xb, 0xe, 0x3, 0xf, 0x3, 0xf, 0x3,
            0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x5, 0xf, 0x1ce, 0xa, 0xf, 0x3, 0x10,
            0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x7, 0x10, 0x1d6,
            0xa, 0x10, 0xc, 0x10, 0xe, 0x10, 0x1d9, 0xb, 0x10, 0x3, 0x11, 0x3, 0x11,
            0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x5, 0x11, 0x1e2,
            0xa, 0x11, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x7, 0x12, 0x1e8,
            0xa, 0x12, 0xc, 0x12, 0xe, 0x12, 0x1eb, 0xb, 0x12, 0x3, 0x13, 0x3, 0x13,
            0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x5, 0x13, 0x1f2, 0xa, 0x13, 0x3, 0x13,
            0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x5, 0x13, 0x1fa,
            0xa, 0x13, 0x7, 0x13, 0x1fc, 0xa, 0x13, 0xc, 0x13, 0xe, 0x13, 0x1ff,
            0xb, 0x13, 0x3, 0x14, 0x6, 0x14, 0x202, 0xa, 0x14, 0xd, 0x14, 0xe, 0x14,
            0x203, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15,
            0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3,
            0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15,
            0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3,
            0x15, 0x3, 0x15, 0x5, 0x15, 0x221, 0xa, 0x15, 0x3, 0x16, 0x3, 0x16,
            0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x7, 0x16, 0x228, 0xa, 0x16, 0xc, 0x16,
            0xe, 0x16, 0x22b, 0xb, 0x16, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x18,
            0x3, 0x18, 0x3, 0x18, 0x7, 0x18, 0x233, 0xa, 0x18, 0xc, 0x18, 0xe, 0x18,
            0x236, 0xb, 0x18, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19,
            0x3, 0x19, 0x5, 0x19, 0x23e, 0xa, 0x19, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a,
            0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x5, 0x1a, 0x246, 0xa, 0x1a, 0x3, 0x1b,
            0x3, 0x1b, 0x3, 0x1b, 0x7, 0x1b, 0x24b, 0xa, 0x1b, 0xc, 0x1b, 0xe, 0x1b,
            0x24e, 0xb, 0x1b, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c,
            0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3,
            0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c,
            0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3,
            0x1c, 0x5, 0x1c, 0x269, 0xa, 0x1c, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d,
            0x7, 0x1d, 0x26e, 0xa, 0x1d, 0xc, 0x1d, 0xe, 0x1d, 0x271, 0xb, 0x1d,
            0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3,
            0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e,
            0x3, 0x1e, 0x3, 0x1e, 0x5, 0x1e, 0x282, 0xa, 0x1e, 0x3, 0x1f, 0x3, 0x1f,
            0x3, 0x1f, 0x7, 0x1f, 0x287, 0xa, 0x1f, 0xc, 0x1f, 0xe, 0x1f, 0x28a,
            0xb, 0x1f, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3,
            0x20, 0x3, 0x20, 0x3, 0x20, 0x5, 0x20, 0x294, 0xa, 0x20, 0x3, 0x21,
            0x3, 0x21, 0x5, 0x21, 0x298, 0xa, 0x21, 0x3, 0x22, 0x5, 0x22, 0x29b,
            0xa, 0x22, 0x3, 0x23, 0x3, 0x23, 0x3, 0x24, 0x3, 0x24, 0x5, 0x24, 0x2a1,
            0xa, 0x24, 0x3, 0x25, 0x3, 0x25, 0x3, 0x25, 0x7, 0x25, 0x2a6, 0xa, 0x25,
            0xc, 0x25, 0xe, 0x25, 0x2a9, 0xb, 0x25, 0x3, 0x26, 0x5, 0x26, 0x2ac,
            0xa, 0x26, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3,
            0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x5, 0x27, 0x2b7, 0xa, 0x27,
            0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 0x7, 0x28, 0x2bc, 0xa, 0x28, 0xc, 0x28,
            0xe, 0x28, 0x2bf, 0xb, 0x28, 0x3, 0x29, 0x3, 0x29, 0x3, 0x29, 0x3, 0x29,
            0x3, 0x29, 0x3, 0x29, 0x3, 0x29, 0x3, 0x29, 0x3, 0x29, 0x5, 0x29, 0x2ca,
            0xa, 0x29, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x7, 0x2a, 0x2cf, 0xa, 0x2a,
            0xc, 0x2a, 0xe, 0x2a, 0x2d2, 0xb, 0x2a, 0x3, 0x2b, 0x3, 0x2b, 0x3, 0x2b,
            0x7, 0x2b, 0x2d7, 0xa, 0x2b, 0xc, 0x2b, 0xe, 0x2b, 0x2da, 0xb, 0x2b,
            0x3, 0x2c, 0x3, 0x2c, 0x3, 0x2c, 0x7, 0x2c, 0x2df, 0xa, 0x2c, 0xc, 0x2c,
            0xe, 0x2c, 0x2e2, 0xb, 0x2c, 0x3, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x7, 0x2d,
            0x2e7, 0xa, 0x2d, 0xc, 0x2d, 0xe, 0x2d, 0x2ea, 0xb, 0x2d, 0x3, 0x2e,
            0x3, 0x2e, 0x3, 0x2e, 0x7, 0x2e, 0x2ef, 0xa, 0x2e, 0xc, 0x2e, 0xe, 0x2e,
            0x2f2, 0xb, 0x2e, 0x3, 0x2f, 0x3, 0x2f, 0x3, 0x2f, 0x3, 0x2f, 0x3, 0x2f,
            0x3, 0x2f, 0x3, 0x2f, 0x3, 0x2f, 0x3, 0x2f, 0x5, 0x2f, 0x2fd, 0xa, 0x2f,
            0x3, 0x30, 0x3, 0x30, 0x3, 0x30, 0x3, 0x30, 0x3, 0x30, 0x3, 0x30, 0x3,
            0x30, 0x3, 0x30, 0x3, 0x30, 0x3, 0x30, 0x5, 0x30, 0x309, 0xa, 0x30,
            0x3, 0x30, 0x3, 0x30, 0x3, 0x30, 0x3, 0x30, 0x3, 0x30, 0x3, 0x30, 0x3,
            0x30, 0x3, 0x30, 0x3, 0x30, 0x3, 0x30, 0x3, 0x30, 0x3, 0x30, 0x3, 0x30,
            0x3, 0x30, 0x3, 0x30, 0x3, 0x30, 0x7, 0x30, 0x31b, 0xa, 0x30, 0xc, 0x30,
            0xe, 0x30, 0x31e, 0xb, 0x30, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31,
            0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3,
            0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31,
            0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3,
            0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31,
            0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3,
            0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31,
            0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3,
            0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x5, 0x31,
            0x357, 0xa, 0x31, 0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 0x3, 0x33,
            0x3, 0x33, 0x3, 0x33, 0x3, 0x33, 0x3, 0x33, 0x3, 0x33, 0x3, 0x33, 0x3,
            0x33, 0x3, 0x34, 0x3, 0x34, 0x3, 0x34, 0x3, 0x34, 0x3, 0x34, 0x7, 0x34,
            0x36a, 0xa, 0x34, 0xc, 0x34, 0xe, 0x34, 0x36d, 0xb, 0x34, 0x3, 0x35,
            0x3, 0x35, 0x3, 0x35, 0x3, 0x35, 0x3, 0x35, 0x3, 0x35, 0x3, 0x35, 0x5,
            0x35, 0x376, 0xa, 0x35, 0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 0x3, 0x36,
            0x3, 0x36, 0x6, 0x36, 0x37d, 0xa, 0x36, 0xd, 0x36, 0xe, 0x36, 0x37e,
            0x3, 0x37, 0x3, 0x37, 0x3, 0x37, 0x7, 0x37, 0x384, 0xa, 0x37, 0xc, 0x37,
            0xe, 0x37, 0x387, 0xb, 0x37, 0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 0x3, 0x38,
            0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 0x3,
            0x38, 0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 0x3, 0x38,
            0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 0x3,
            0x38, 0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 0x3, 0x38,
            0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 0x3,
            0x38, 0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 0x3, 0x38,
            0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 0x3,
            0x38, 0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 0x5, 0x38,
            0x3c0, 0xa, 0x38, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x7, 0x39, 0x3c5,
            0xa, 0x39, 0xc, 0x39, 0xe, 0x39, 0x3c8, 0xb, 0x39, 0x3, 0x3a, 0x3, 0x3a,
            0x3, 0x3a, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3c, 0x3,
            0x3c, 0x3, 0x3c, 0x7, 0x3c, 0x3d4, 0xa, 0x3c, 0xc, 0x3c, 0xe, 0x3c,
            0x3d7, 0xb, 0x3c, 0x3, 0x3d, 0x3, 0x3d, 0x3, 0x3d, 0x3, 0x3d, 0x5, 0x3d,
            0x3dd, 0xa, 0x3d, 0x3, 0x3e, 0x5, 0x3e, 0x3e0, 0xa, 0x3e, 0x3, 0x3f,
            0x3, 0x3f, 0x3, 0x40, 0x3, 0x40, 0x3, 0x41, 0x3, 0x41, 0x3, 0x42, 0x3,
            0x42, 0x3, 0x43, 0x6, 0x43, 0x3eb, 0xa, 0x43, 0xd, 0x43, 0xe, 0x43,
            0x3ec, 0x3, 0x44, 0x3, 0x44, 0x3, 0x44, 0x3, 0x44, 0x3, 0x44, 0x3, 0x44,
            0x3, 0x44, 0x3, 0x44, 0x3, 0x44, 0x3, 0x44, 0x3, 0x44, 0x3, 0x44, 0x3,
            0x44, 0x3, 0x44, 0x5, 0x44, 0x3fd, 0xa, 0x44, 0x3, 0x45, 0x6, 0x45,
            0x400, 0xa, 0x45, 0xd, 0x45, 0xe, 0x45, 0x401, 0x3, 0x46, 0x3, 0x46,
            0x3, 0x46, 0x3, 0x46, 0x3, 0x46, 0x3, 0x46, 0x3, 0x46, 0x3, 0x46, 0x3,
            0x46, 0x3, 0x46, 0x3, 0x46, 0x3, 0x46, 0x3, 0x46, 0x3, 0x46, 0x3, 0x46,
            0x3, 0x46, 0x3, 0x46, 0x3, 0x46, 0x3, 0x46, 0x3, 0x46, 0x3, 0x46, 0x3,
            0x46, 0x3, 0x46, 0x3, 0x46, 0x3, 0x46, 0x3, 0x46, 0x3, 0x46, 0x3, 0x46,
            0x3, 0x46, 0x5, 0x46, 0x421, 0xa, 0x46, 0x3, 0x47, 0x3, 0x47, 0x3, 0x47,
            0x3, 0x47, 0x3, 0x47, 0x3, 0x47, 0x3, 0x47, 0x3, 0x47, 0x3, 0x47, 0x3,
            0x47, 0x3, 0x47, 0x3, 0x47, 0x3, 0x47, 0x3, 0x47, 0x5, 0x47, 0x431,
            0xa, 0x47, 0x3, 0x48, 0x3, 0x48, 0x5, 0x48, 0x435, 0xa, 0x48, 0x3, 0x49,
            0x5, 0x49, 0x438, 0xa, 0x49, 0x3, 0x4a, 0x3, 0x4a, 0x5, 0x4a, 0x43c,
            0xa, 0x4a, 0x3, 0x4b, 0x3, 0x4b, 0x3, 0x4b, 0x7, 0x4b, 0x441, 0xa, 0x4b,
            0xc, 0x4b, 0xe, 0x4b, 0x444, 0xb, 0x4b, 0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c,
            0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 0x3,
            0x4c, 0x3, 0x4c, 0x3, 0x4c, 0x5, 0x4c, 0x452, 0xa, 0x4c, 0x3, 0x4d,
            0x3, 0x4d, 0x3, 0x4d, 0x3, 0x4d, 0x3, 0x4d, 0x3, 0x4d, 0x3, 0x4d, 0x3,
            0x4d, 0x3, 0x4d, 0x5, 0x4d, 0x45d, 0xa, 0x4d, 0x3, 0x4e, 0x3, 0x4e,
            0x3, 0x4e, 0x7, 0x4e, 0x462, 0xa, 0x4e, 0xc, 0x4e, 0xe, 0x4e, 0x465,
            0xb, 0x4e, 0x3, 0x4f, 0x3, 0x4f, 0x3, 0x4f, 0x3, 0x4f, 0x3, 0x4f, 0x3,
            0x4f, 0x3, 0x4f, 0x3, 0x4f, 0x3, 0x4f, 0x3, 0x4f, 0x3, 0x4f, 0x3, 0x4f,
            0x3, 0x4f, 0x3, 0x4f, 0x3, 0x4f, 0x3, 0x4f, 0x3, 0x4f, 0x5, 0x4f, 0x478,
            0xa, 0x4f, 0x3, 0x50, 0x3, 0x50, 0x3, 0x50, 0x7, 0x50, 0x47d, 0xa, 0x50,
            0xc, 0x50, 0xe, 0x50, 0x480, 0xb, 0x50, 0x3, 0x51, 0x3, 0x51, 0x3, 0x51,
            0x3, 0x51, 0x3, 0x51, 0x3, 0x51, 0x3, 0x51, 0x3, 0x51, 0x3, 0x51, 0x3,
            0x51, 0x3, 0x51, 0x3, 0x51, 0x5, 0x51, 0x48e, 0xa, 0x51, 0x3, 0x52,
            0x3, 0x52, 0x3, 0x52, 0x3, 0x52, 0x3, 0x52, 0x7, 0x52, 0x495, 0xa, 0x52,
            0xc, 0x52, 0xe, 0x52, 0x498, 0xb, 0x52, 0x3, 0x53, 0x3, 0x53, 0x5, 0x53,
            0x49c, 0xa, 0x53, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x7, 0x54, 0x4a1,
            0xa, 0x54, 0xc, 0x54, 0xe, 0x54, 0x4a4, 0xb, 0x54, 0x3, 0x55, 0x3, 0x55,
            0x3, 0x55, 0x3, 0x55, 0x3, 0x55, 0x3, 0x55, 0x3, 0x55, 0x3, 0x55, 0x3,
            0x55, 0x3, 0x55, 0x5, 0x55, 0x4b0, 0xa, 0x55, 0x3, 0x56, 0x7, 0x56,
            0x4b3, 0xa, 0x56, 0xc, 0x56, 0xe, 0x56, 0x4b6, 0xb, 0x56, 0x3, 0x57,
            0x3, 0x57, 0x3, 0x57, 0x3, 0x57, 0x3, 0x58, 0x7, 0x58, 0x4bd, 0xa, 0x58,
            0xc, 0x58, 0xe, 0x58, 0x4c0, 0xb, 0x58, 0x3, 0x59, 0x3, 0x59, 0x3, 0x59,
            0x3, 0x59, 0x3, 0x59, 0x3, 0x59, 0x3, 0x59, 0x5, 0x59, 0x4c9, 0xa, 0x59,
            0x3, 0x5a, 0x3, 0x5a, 0x3, 0x5a, 0x3, 0x5a, 0x3, 0x5b, 0x3, 0x5b, 0x5,
            0x5b, 0x4d1, 0xa, 0x5b, 0x3, 0x5c, 0x3, 0x5c, 0x3, 0x5c, 0x3, 0x5c,
            0x3, 0x5c, 0x3, 0x5c, 0x3, 0x5c, 0x3, 0x5c, 0x3, 0x5d, 0x3, 0x5d, 0x5,
            0x5d, 0x4dd, 0xa, 0x5d, 0x3, 0x5e, 0x3, 0x5e, 0x5, 0x5e, 0x4e1, 0xa,
            0x5e, 0x3, 0x5f, 0x3, 0x5f, 0x3, 0x5f, 0x3, 0x5f, 0x3, 0x5f, 0x3, 0x5f,
            0x3, 0x5f, 0x3, 0x5f, 0x3, 0x5f, 0x3, 0x5f, 0x3, 0x5f, 0x3, 0x5f, 0x3,
            0x5f, 0x3, 0x5f, 0x3, 0x5f, 0x3, 0x5f, 0x3, 0x5f, 0x3, 0x5f, 0x3, 0x5f,
            0x3, 0x5f, 0x5, 0x5f, 0x4f7, 0xa, 0x5f, 0x3, 0x60, 0x3, 0x60, 0x3, 0x60,
            0x3, 0x60, 0x3, 0x60, 0x3, 0x60, 0x3, 0x60, 0x3, 0x60, 0x3, 0x60, 0x3,
            0x61, 0x3, 0x61, 0x3, 0x61, 0x5, 0x61, 0x505, 0xa, 0x61, 0x3, 0x62,
            0x3, 0x62, 0x3, 0x62, 0x3, 0x62, 0x3, 0x62, 0x3, 0x62, 0x3, 0x62, 0x3,
            0x62, 0x3, 0x63, 0x3, 0x63, 0x3, 0x63, 0x3, 0x63, 0x3, 0x63, 0x3, 0x63,
            0x3, 0x63, 0x3, 0x63, 0x3, 0x63, 0x3, 0x63, 0x3, 0x63, 0x3, 0x63, 0x3,
            0x63, 0x3, 0x63, 0x3, 0x63, 0x3, 0x63, 0x3, 0x63, 0x5, 0x63, 0x520,
            0xa, 0x63, 0x3, 0x64, 0x5, 0x64, 0x523, 0xa, 0x64, 0x3, 0x65, 0x3, 0x65,
            0x3, 0x65, 0x3, 0x65, 0x3, 0x65, 0x6, 0x65, 0x52a, 0xa, 0x65, 0xd, 0x65,
            0xe, 0x65, 0x52b, 0x3, 0x66, 0x3, 0x66, 0x3, 0x66, 0x3, 0x66, 0x3, 0x67,
            0x3, 0x67, 0x3, 0x67, 0x3, 0x67, 0x3, 0x67, 0x3, 0x67, 0x3, 0x67, 0x3,
            0x68, 0x3, 0x68, 0x3, 0x68, 0x3, 0x68, 0x3, 0x68, 0x3, 0x68, 0x3, 0x68,
            0x3, 0x68, 0x3, 0x68, 0x3, 0x68, 0x5, 0x68, 0x543, 0xa, 0x68, 0x3, 0x69,
            0x3, 0x69, 0x5, 0x69, 0x547, 0xa, 0x69, 0x3, 0x6a, 0x3, 0x6a, 0x3, 0x6a,
            0x7, 0x6a, 0x54c, 0xa, 0x6a, 0xc, 0x6a, 0xe, 0x6a, 0x54f, 0xb, 0x6a,
            0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x5, 0x6b, 0x556,
            0xa, 0x6b, 0x3, 0x6c, 0x3, 0x6c, 0x3, 0x6c, 0x3, 0x6c, 0x3, 0x6c, 0x3,
            0x6c, 0x3, 0x6c, 0x3, 0x6c, 0x3, 0x6c, 0x3, 0x6c, 0x3, 0x6c, 0x3, 0x6c,
            0x3, 0x6c, 0x3, 0x6c, 0x5, 0x6c, 0x566, 0xa, 0x6c, 0x3, 0x6d, 0x3, 0x6d,
            0x5, 0x6d, 0x56a, 0xa, 0x6d, 0x3, 0x6d, 0x2, 0x2, 0x6e, 0x2, 0x4, 0x6,
            0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e,
            0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e, 0x30, 0x32, 0x34, 0x36,
            0x38, 0x3a, 0x3c, 0x3e, 0x40, 0x42, 0x44, 0x46, 0x48, 0x4a, 0x4c, 0x4e,
            0x50, 0x52, 0x54, 0x56, 0x58, 0x5a, 0x5c, 0x5e, 0x60, 0x62, 0x64, 0x66,
            0x68, 0x6a, 0x6c, 0x6e, 0x70, 0x72, 0x74, 0x76, 0x78, 0x7a, 0x7c, 0x7e,
            0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c, 0x8e, 0x90, 0x92, 0x94, 0x96,
            0x98, 0x9a, 0x9c, 0x9e, 0xa0, 0xa2, 0xa4, 0xa6, 0xa8, 0xaa, 0xac, 0xae,
            0xb0, 0xb2, 0xb4, 0xb6, 0xb8, 0xba, 0xbc, 0xbe, 0xc0, 0xc2, 0xc4, 0xc6,
            0xc8, 0xca, 0xcc, 0xce, 0xd0, 0xd2, 0xd4, 0xd6, 0xd8, 0x2, 0x5, 0x3,
            0x2, 0x2b, 0x2c, 0x3, 0x2, 0x4c, 0x4e, 0x3, 0x2, 0x4f, 0x6e, 0x2, 0x5cb,
            0x2, 0xda, 0x3, 0x2, 0x2, 0x2, 0x4, 0xdc, 0x3, 0x2, 0x2, 0x2, 0x6, 0xde,
            0x3, 0x2, 0x2, 0x2, 0x8, 0xe5, 0x3, 0x2, 0x2, 0x2, 0xa, 0x125, 0x3,
            0x2, 0x2, 0x2, 0xc, 0x12a, 0x3, 0x2, 0x2, 0x2, 0xe, 0x13f, 0x3, 0x2,
            0x2, 0x2, 0x10, 0x17e, 0x3, 0x2, 0x2, 0x2, 0x12, 0x180, 0x3, 0x2, 0x2,
            0x2, 0x14, 0x188, 0x3, 0x2, 0x2, 0x2, 0x16, 0x195, 0x3, 0x2, 0x2, 0x2,
            0x18, 0x1a6, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x1b8, 0x3, 0x2, 0x2, 0x2, 0x1c,
            0x1cd, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x1cf, 0x3, 0x2, 0x2, 0x2, 0x20, 0x1e1,
            0x3, 0x2, 0x2, 0x2, 0x22, 0x1e9, 0x3, 0x2, 0x2, 0x2, 0x24, 0x1f1, 0x3,
            0x2, 0x2, 0x2, 0x26, 0x201, 0x3, 0x2, 0x2, 0x2, 0x28, 0x220, 0x3, 0x2,
            0x2, 0x2, 0x2a, 0x229, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x22c, 0x3, 0x2, 0x2,
            0x2, 0x2e, 0x22f, 0x3, 0x2, 0x2, 0x2, 0x30, 0x23d, 0x3, 0x2, 0x2, 0x2,
            0x32, 0x245, 0x3, 0x2, 0x2, 0x2, 0x34, 0x247, 0x3, 0x2, 0x2, 0x2, 0x36,
            0x268, 0x3, 0x2, 0x2, 0x2, 0x38, 0x26a, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x281,
            0x3, 0x2, 0x2, 0x2, 0x3c, 0x283, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x293, 0x3,
            0x2, 0x2, 0x2, 0x40, 0x297, 0x3, 0x2, 0x2, 0x2, 0x42, 0x29a, 0x3, 0x2,
            0x2, 0x2, 0x44, 0x29c, 0x3, 0x2, 0x2, 0x2, 0x46, 0x2a0, 0x3, 0x2, 0x2,
            0x2, 0x48, 0x2a2, 0x3, 0x2, 0x2, 0x2, 0x4a, 0x2ab, 0x3, 0x2, 0x2, 0x2,
            0x4c, 0x2b6, 0x3, 0x2, 0x2, 0x2, 0x4e, 0x2b8, 0x3, 0x2, 0x2, 0x2, 0x50,
            0x2c9, 0x3, 0x2, 0x2, 0x2, 0x52, 0x2cb, 0x3, 0x2, 0x2, 0x2, 0x54, 0x2d3,
            0x3, 0x2, 0x2, 0x2, 0x56, 0x2db, 0x3, 0x2, 0x2, 0x2, 0x58, 0x2e3, 0x3,
            0x2, 0x2, 0x2, 0x5a, 0x2eb, 0x3, 0x2, 0x2, 0x2, 0x5c, 0x2fc, 0x3, 0x2,
            0x2, 0x2, 0x5e, 0x308, 0x3, 0x2, 0x2, 0x2, 0x60, 0x356, 0x3, 0x2, 0x2,
            0x2, 0x62, 0x358, 0x3, 0x2, 0x2, 0x2, 0x64, 0x35c, 0x3, 0x2, 0x2, 0x2,
            0x66, 0x36b, 0x3, 0x2, 0x2, 0x2, 0x68, 0x375, 0x3, 0x2, 0x2, 0x2, 0x6a,
            0x37c, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x380, 0x3, 0x2, 0x2, 0x2, 0x6e, 0x3bf,
            0x3, 0x2, 0x2, 0x2, 0x70, 0x3c1, 0x3, 0x2, 0x2, 0x2, 0x72, 0x3c9, 0x3,
            0x2, 0x2, 0x2, 0x74, 0x3cc, 0x3, 0x2, 0x2, 0x2, 0x76, 0x3d0, 0x3, 0x2,
            0x2, 0x2, 0x78, 0x3dc, 0x3, 0x2, 0x2, 0x2, 0x7a, 0x3df, 0x3, 0x2, 0x2,
            0x2, 0x7c, 0x3e1, 0x3, 0x2, 0x2, 0x2, 0x7e, 0x3e3, 0x3, 0x2, 0x2, 0x2,
            0x80, 0x3e5, 0x3, 0x2, 0x2, 0x2, 0x82, 0x3e7, 0x3, 0x2, 0x2, 0x2, 0x84,
            0x3ea, 0x3, 0x2, 0x2, 0x2, 0x86, 0x3fc, 0x3, 0x2, 0x2, 0x2, 0x88, 0x3ff,
            0x3, 0x2, 0x2, 0x2, 0x8a, 0x420, 0x3, 0x2, 0x2, 0x2, 0x8c, 0x430, 0x3,
            0x2, 0x2, 0x2, 0x8e, 0x434, 0x3, 0x2, 0x2, 0x2, 0x90, 0x437, 0x3, 0x2,
            0x2, 0x2, 0x92, 0x43b, 0x3, 0x2, 0x2, 0x2, 0x94, 0x43d, 0x3, 0x2, 0x2,
            0x2, 0x96, 0x451, 0x3, 0x2, 0x2, 0x2, 0x98, 0x45c, 0x3, 0x2, 0x2, 0x2,
            0x9a, 0x45e, 0x3, 0x2, 0x2, 0x2, 0x9c, 0x477, 0x3, 0x2, 0x2, 0x2, 0x9e,
            0x479, 0x3, 0x2, 0x2, 0x2, 0xa0, 0x48d, 0x3, 0x2, 0x2, 0x2, 0xa2, 0x496,
            0x3, 0x2, 0x2, 0x2, 0xa4, 0x49b, 0x3, 0x2, 0x2, 0x2, 0xa6, 0x49d, 0x3,
            0x2, 0x2, 0x2, 0xa8, 0x4af, 0x3, 0x2, 0x2, 0x2, 0xaa, 0x4b4, 0x3, 0x2,
            0x2, 0x2, 0xac, 0x4b7, 0x3, 0x2, 0x2, 0x2, 0xae, 0x4be, 0x3, 0x2, 0x2,
            0x2, 0xb0, 0x4c8, 0x3, 0x2, 0x2, 0x2, 0xb2, 0x4ca, 0x3, 0x2, 0x2, 0x2,
            0xb4, 0x4d0, 0x3, 0x2, 0x2, 0x2, 0xb6, 0x4d2, 0x3, 0x2, 0x2, 0x2, 0xb8,
            0x4dc, 0x3, 0x2, 0x2, 0x2, 0xba, 0x4e0, 0x3, 0x2, 0x2, 0x2, 0xbc, 0x4f6,
            0x3, 0x2, 0x2, 0x2, 0xbe, 0x4f8, 0x3, 0x2, 0x2, 0x2, 0xc0, 0x504, 0x3,
            0x2, 0x2, 0x2, 0xc2, 0x506, 0x3, 0x2, 0x2, 0x2, 0xc4, 0x51f, 0x3, 0x2,
            0x2, 0x2, 0xc6, 0x522, 0x3, 0x2, 0x2, 0x2, 0xc8, 0x529, 0x3, 0x2, 0x2,
            0x2, 0xca, 0x52d, 0x3, 0x2, 0x2, 0x2, 0xcc, 0x531, 0x3, 0x2, 0x2, 0x2,
            0xce, 0x542, 0x3, 0x2, 0x2, 0x2, 0xd0, 0x546, 0x3, 0x2, 0x2, 0x2, 0xd2,
            0x548, 0x3, 0x2, 0x2, 0x2, 0xd4, 0x555, 0x3, 0x2, 0x2, 0x2, 0xd6, 0x565,
            0x3, 0x2, 0x2, 0x2, 0xd8, 0x569, 0x3, 0x2, 0x2, 0x2, 0xda, 0xdb, 0x5,
            0x4, 0x3, 0x2, 0xdb, 0x3, 0x3, 0x2, 0x2, 0x2, 0xdc, 0xdd, 0x5, 0x8,
            0x5, 0x2, 0xdd, 0x5, 0x3, 0x2, 0x2, 0x2, 0xde, 0xdf, 0x5, 0xc, 0x7,
            0x2, 0xdf, 0xe0, 0x5, 0x84, 0x43, 0x2, 0xe0, 0xe1, 0x5, 0xae, 0x58,
            0x2, 0xe1, 0x7, 0x3, 0x2, 0x2, 0x2, 0xe2, 0xe4, 0x5, 0xa, 0x6, 0x2,
            0xe3, 0xe2, 0x3, 0x2, 0x2, 0x2, 0xe4, 0xe7, 0x3, 0x2, 0x2, 0x2, 0xe5,
            0xe3, 0x3, 0x2, 0x2, 0x2, 0xe5, 0xe6, 0x3, 0x2, 0x2, 0x2, 0xe6, 0x9,
            0x3, 0x2, 0x2, 0x2, 0xe7, 0xe5, 0x3, 0x2, 0x2, 0x2, 0xe8, 0x126, 0x5,
            0x10, 0x9, 0x2, 0xe9, 0xea, 0x7, 0x3, 0x2, 0x2, 0xea, 0xeb, 0x5, 0x12,
            0xa, 0x2, 0xeb, 0xec, 0x7, 0x4, 0x2, 0x2, 0xec, 0x126, 0x3, 0x2, 0x2,
            0x2, 0xed, 0xee, 0x7, 0x5, 0x2, 0x2, 0xee, 0xef, 0x7, 0x91, 0x2, 0x2,
            0xef, 0x126, 0x7, 0x4, 0x2, 0x2, 0xf0, 0xf1, 0x7, 0x5, 0x2, 0x2, 0xf1,
            0xf2, 0x7, 0x92, 0x2, 0x2, 0xf2, 0x126, 0x7, 0x4, 0x2, 0x2, 0xf3, 0xf4,
            0x7, 0x6, 0x2, 0x2, 0xf4, 0xf5, 0x5, 0x6c, 0x37, 0x2, 0xf5, 0xf6, 0x5,
            0x7e, 0x40, 0x2, 0xf6, 0xf7, 0x5, 0x1c, 0xf, 0x2, 0xf7, 0xf8, 0x7, 0x7,
            0x2, 0x2, 0xf8, 0xf9, 0x5, 0x20, 0x11, 0x2, 0xf9, 0x126, 0x3, 0x2, 0x2,
            0x2, 0xfa, 0xfb, 0x5, 0x7e, 0x40, 0x2, 0xfb, 0xfc, 0x7, 0x7, 0x2, 0x2,
            0xfc, 0xfd, 0x5, 0x78, 0x3d, 0x2, 0xfd, 0xfe, 0x5, 0x30, 0x19, 0x2,
            0xfe, 0xff, 0x7, 0x4, 0x2, 0x2, 0xff, 0x126, 0x3, 0x2, 0x2, 0x2, 0x100,
            0x101, 0x7, 0x8, 0x2, 0x2, 0x101, 0x102, 0x7, 0x9, 0x2, 0x2, 0x102,
            0x103, 0x5, 0x7e, 0x40, 0x2, 0x103, 0x104, 0x5, 0x32, 0x1a, 0x2, 0x104,
            0x105, 0x7, 0x7, 0x2, 0x2, 0x105, 0x106, 0x5, 0x4, 0x3, 0x2, 0x106,
            0x107, 0x7, 0xa, 0x2, 0x2, 0x107, 0x126, 0x3, 0x2, 0x2, 0x2, 0x108,
            0x109, 0x5, 0x7a, 0x3e, 0x2, 0x109, 0x10a, 0x7, 0xb, 0x2, 0x2, 0x10a,
            0x10b, 0x7, 0x9, 0x2, 0x2, 0x10b, 0x10c, 0x5, 0x7e, 0x40, 0x2, 0x10c,
            0x10d, 0x5, 0x32, 0x1a, 0x2, 0x10d, 0x10e, 0x7, 0x7, 0x2, 0x2, 0x10e,
            0x10f, 0x5, 0x6, 0x4, 0x2, 0x10f, 0x110, 0x7, 0xa, 0x2, 0x2, 0x110,
            0x126, 0x3, 0x2, 0x2, 0x2, 0x111, 0x112, 0x5, 0x7c, 0x3f, 0x2, 0x112,
            0x113, 0x7, 0x9, 0x2, 0x2, 0x113, 0x114, 0x5, 0x7e, 0x40, 0x2, 0x114,
            0x115, 0x7, 0x7, 0x2, 0x2, 0x115, 0x116, 0x5, 0x4, 0x3, 0x2, 0x116,
            0x117, 0x7, 0xa, 0x2, 0x2, 0x117, 0x126, 0x3, 0x2, 0x2, 0x2, 0x118,
            0x119, 0x5, 0x7a, 0x3e, 0x2, 0x119, 0x11a, 0x7, 0xb, 0x2, 0x2, 0x11a,
            0x11b, 0x5, 0x7e, 0x40, 0x2, 0x11b, 0x11c, 0x7, 0x7, 0x2, 0x2, 0x11c,
            0x11d, 0x5, 0x6, 0x4, 0x2, 0x11d, 0x11e, 0x7, 0xa, 0x2, 0x2, 0x11e,
            0x126, 0x3, 0x2, 0x2, 0x2, 0x11f, 0x120, 0x5, 0x7c, 0x3f, 0x2, 0x120,
            0x121, 0x5, 0x7e, 0x40, 0x2, 0x121, 0x122, 0x7, 0x7, 0x2, 0x2, 0x122,
            0x123, 0x5, 0x6, 0x4, 0x2, 0x123, 0x124, 0x7, 0xa, 0x2, 0x2, 0x124,
            0x126, 0x3, 0x2, 0x2, 0x2, 0x125, 0xe8, 0x3, 0x2, 0x2, 0x2, 0x125, 0xe9,
            0x3, 0x2, 0x2, 0x2, 0x125, 0xed, 0x3, 0x2, 0x2, 0x2, 0x125, 0xf0, 0x3,
            0x2, 0x2, 0x2, 0x125, 0xf3, 0x3, 0x2, 0x2, 0x2, 0x125, 0xfa, 0x3, 0x2,
            0x2, 0x2, 0x125, 0x100, 0x3, 0x2, 0x2, 0x2, 0x125, 0x108, 0x3, 0x2,
            0x2, 0x2, 0x125, 0x111, 0x3, 0x2, 0x2, 0x2, 0x125, 0x118, 0x3, 0x2,
            0x2, 0x2, 0x125, 0x11f, 0x3, 0x2, 0x2, 0x2, 0x126, 0xb, 0x3, 0x2, 0x2,
            0x2, 0x127, 0x129, 0x5, 0xe, 0x8, 0x2, 0x128, 0x127, 0x3, 0x2, 0x2,
            0x2, 0x129, 0x12c, 0x3, 0x2, 0x2, 0x2, 0x12a, 0x128, 0x3, 0x2, 0x2,
            0x2, 0x12a, 0x12b, 0x3, 0x2, 0x2, 0x2, 0x12b, 0xd, 0x3, 0x2, 0x2, 0x2,
            0x12c, 0x12a, 0x3, 0x2, 0x2, 0x2, 0x12d, 0x140, 0x5, 0x10, 0x9, 0x2,
            0x12e, 0x12f, 0x7, 0xc, 0x2, 0x2, 0x12f, 0x130, 0x5, 0x2e, 0x18, 0x2,
            0x130, 0x131, 0x7, 0x4, 0x2, 0x2, 0x131, 0x140, 0x3, 0x2, 0x2, 0x2,
            0x132, 0x133, 0x7, 0xc, 0x2, 0x2, 0x133, 0x140, 0x7, 0x4, 0x2, 0x2,
            0x134, 0x135, 0x7, 0xd, 0x2, 0x2, 0x135, 0x136, 0x5, 0x2e, 0x18, 0x2,
            0x136, 0x137, 0x7, 0x4, 0x2, 0x2, 0x137, 0x140, 0x3, 0x2, 0x2, 0x2,
            0x138, 0x139, 0x7, 0xd, 0x2, 0x2, 0x139, 0x140, 0x7, 0x4, 0x2, 0x2,
            0x13a, 0x13b, 0x7, 0xe, 0x2, 0x2, 0x13b, 0x13c, 0x5, 0x6e, 0x38, 0x2,
            0x13c, 0x13d, 0x5, 0x38, 0x1d, 0x2, 0x13d, 0x13e, 0x7, 0x4, 0x2, 0x2,
            0x13e, 0x140, 0x3, 0x2, 0x2, 0x2, 0x13f, 0x12d, 0x3, 0x2, 0x2, 0x2,
            0x13f, 0x12e, 0x3, 0x2, 0x2, 0x2, 0x13f, 0x132, 0x3, 0x2, 0x2, 0x2,
            0x13f, 0x134, 0x3, 0x2, 0x2, 0x2, 0x13f, 0x138, 0x3, 0x2, 0x2, 0x2,
            0x13f, 0x13a, 0x3, 0x2, 0x2, 0x2, 0x140, 0xf, 0x3, 0x2, 0x2, 0x2, 0x141,
            0x142, 0x7, 0xf, 0x2, 0x2, 0x142, 0x143, 0x5, 0x14, 0xb, 0x2, 0x143,
            0x144, 0x7, 0x4, 0x2, 0x2, 0x144, 0x17f, 0x3, 0x2, 0x2, 0x2, 0x145,
            0x146, 0x7, 0x10, 0x2, 0x2, 0x146, 0x147, 0x5, 0x16, 0xc, 0x2, 0x147,
            0x148, 0x7, 0x4, 0x2, 0x2, 0x148, 0x17f, 0x3, 0x2, 0x2, 0x2, 0x149,
            0x14a, 0x5, 0x42, 0x22, 0x2, 0x14a, 0x14b, 0x7, 0x11, 0x2, 0x2, 0x14b,
            0x14c, 0x5, 0x7e, 0x40, 0x2, 0x14c, 0x14d, 0x7, 0x4, 0x2, 0x2, 0x14d,
            0x17f, 0x3, 0x2, 0x2, 0x2, 0x14e, 0x14f, 0x5, 0x42, 0x22, 0x2, 0x14f,
            0x150, 0x7, 0x11, 0x2, 0x2, 0x150, 0x151, 0x5, 0x46, 0x24, 0x2, 0x151,
            0x152, 0x5, 0x7e, 0x40, 0x2, 0x152, 0x153, 0x7, 0x4, 0x2, 0x2, 0x153,
            0x17f, 0x3, 0x2, 0x2, 0x2, 0x154, 0x155, 0x5, 0x44, 0x23, 0x2, 0x155,
            0x156, 0x5, 0x7e, 0x40, 0x2, 0x156, 0x157, 0x7, 0x4, 0x2, 0x2, 0x157,
            0x17f, 0x3, 0x2, 0x2, 0x2, 0x158, 0x159, 0x5, 0x44, 0x23, 0x2, 0x159,
            0x15a, 0x5, 0x46, 0x24, 0x2, 0x15a, 0x15b, 0x5, 0x7e, 0x40, 0x2, 0x15b,
            0x15c, 0x7, 0x4, 0x2, 0x2, 0x15c, 0x17f, 0x3, 0x2, 0x2, 0x2, 0x15d,
            0x15e, 0x7, 0x12, 0x2, 0x2, 0x15e, 0x15f, 0x5, 0x6e, 0x38, 0x2, 0x15f,
            0x160, 0x5, 0x18, 0xd, 0x2, 0x160, 0x161, 0x7, 0x4, 0x2, 0x2, 0x161,
            0x17f, 0x3, 0x2, 0x2, 0x2, 0x162, 0x163, 0x7, 0x13, 0x2, 0x2, 0x163,
            0x164, 0x5, 0x6e, 0x38, 0x2, 0x164, 0x165, 0x5, 0x1a, 0xe, 0x2, 0x165,
            0x166, 0x7, 0x4, 0x2, 0x2, 0x166, 0x17f, 0x3, 0x2, 0x2, 0x2, 0x167,
            0x168, 0x7, 0x14, 0x2, 0x2, 0x168, 0x169, 0x5, 0x6e, 0x38, 0x2, 0x169,
            0x16a, 0x5, 0x7e, 0x40, 0x2, 0x16a, 0x16b, 0x7, 0x4, 0x2, 0x2, 0x16b,
            0x17f, 0x3, 0x2, 0x2, 0x2, 0x16c, 0x16d, 0x7, 0x15, 0x2, 0x2, 0x16d,
            0x16e, 0x5, 0x3c, 0x1f, 0x2, 0x16e, 0x16f, 0x7, 0x4, 0x2, 0x2, 0x16f,
            0x17f, 0x3, 0x2, 0x2, 0x2, 0x170, 0x171, 0x7, 0x16, 0x2, 0x2, 0x171,
            0x172, 0x5, 0x4e, 0x28, 0x2, 0x172, 0x173, 0x7, 0x4, 0x2, 0x2, 0x173,
            0x17f, 0x3, 0x2, 0x2, 0x2, 0x174, 0x175, 0x7, 0x17, 0x2, 0x2, 0x175,
            0x176, 0x5, 0x48, 0x25, 0x2, 0x176, 0x177, 0x7, 0x4, 0x2, 0x2, 0x177,
            0x17f, 0x3, 0x2, 0x2, 0x2, 0x178, 0x17f, 0x5, 0x98, 0x4d, 0x2, 0x179,
            0x17a, 0x7, 0x18, 0x2, 0x2, 0x17a, 0x17b, 0x5, 0x48, 0x25, 0x2, 0x17b,
            0x17c, 0x7, 0x4, 0x2, 0x2, 0x17c, 0x17f, 0x3, 0x2, 0x2, 0x2, 0x17d,
            0x17f, 0x5, 0xb0, 0x59, 0x2, 0x17e, 0x141, 0x3, 0x2, 0x2, 0x2, 0x17e,
            0x145, 0x3, 0x2, 0x2, 0x2, 0x17e, 0x149, 0x3, 0x2, 0x2, 0x2, 0x17e,
            0x14e, 0x3, 0x2, 0x2, 0x2, 0x17e, 0x154, 0x3, 0x2, 0x2, 0x2, 0x17e,
            0x158, 0x3, 0x2, 0x2, 0x2, 0x17e, 0x15d, 0x3, 0x2, 0x2, 0x2, 0x17e,
            0x162, 0x3, 0x2, 0x2, 0x2, 0x17e, 0x167, 0x3, 0x2, 0x2, 0x2, 0x17e,
            0x16c, 0x3, 0x2, 0x2, 0x2, 0x17e, 0x170, 0x3, 0x2, 0x2, 0x2, 0x17e,
            0x174, 0x3, 0x2, 0x2, 0x2, 0x17e, 0x178, 0x3, 0x2, 0x2, 0x2, 0x17e,
            0x179, 0x3, 0x2, 0x2, 0x2, 0x17e, 0x17d, 0x3, 0x2, 0x2, 0x2, 0x17f,
            0x11, 0x3, 0x2, 0x2, 0x2, 0x180, 0x185, 0x5, 0x80, 0x41, 0x2, 0x181,
            0x182, 0x7, 0x19, 0x2, 0x2, 0x182, 0x184, 0x5, 0x80, 0x41, 0x2, 0x183,
            0x181, 0x3, 0x2, 0x2, 0x2, 0x184, 0x187, 0x3, 0x2, 0x2, 0x2, 0x185,
            0x183, 0x3, 0x2, 0x2, 0x2, 0x185, 0x186, 0x3, 0x2, 0x2, 0x2, 0x186,
            0x13, 0x3, 0x2, 0x2, 0x2, 0x187, 0x185, 0x3, 0x2, 0x2, 0x2, 0x188, 0x189,
            0x5, 0x7e, 0x40, 0x2, 0x189, 0x18a, 0x7, 0x1a, 0x2, 0x2, 0x18a, 0x192,
            0x5, 0x6e, 0x38, 0x2, 0x18b, 0x18c, 0x7, 0x19, 0x2, 0x2, 0x18c, 0x18d,
            0x5, 0x7e, 0x40, 0x2, 0x18d, 0x18e, 0x7, 0x1a, 0x2, 0x2, 0x18e, 0x18f,
            0x5, 0x6e, 0x38, 0x2, 0x18f, 0x191, 0x3, 0x2, 0x2, 0x2, 0x190, 0x18b,
            0x3, 0x2, 0x2, 0x2, 0x191, 0x194, 0x3, 0x2, 0x2, 0x2, 0x192, 0x190,
            0x3, 0x2, 0x2, 0x2, 0x192, 0x193, 0x3, 0x2, 0x2, 0x2, 0x193, 0x15, 0x3,
            0x2, 0x2, 0x2, 0x194, 0x192, 0x3, 0x2, 0x2, 0x2, 0x195, 0x196, 0x5,
            0x7e, 0x40, 0x2, 0x196, 0x197, 0x7, 0x1a, 0x2, 0x2, 0x197, 0x198, 0x7,
            0x1b, 0x2, 0x2, 0x198, 0x199, 0x5, 0x7e, 0x40, 0x2, 0x199, 0x1a3, 0x7,
            0x1c, 0x2, 0x2, 0x19a, 0x19b, 0x7, 0x19, 0x2, 0x2, 0x19b, 0x19c, 0x5,
            0x7e, 0x40, 0x2, 0x19c, 0x19d, 0x7, 0x1a, 0x2, 0x2, 0x19d, 0x19e, 0x7,
            0x1b, 0x2, 0x2, 0x19e, 0x19f, 0x5, 0x7e, 0x40, 0x2, 0x19f, 0x1a0, 0x7,
            0x1c, 0x2, 0x2, 0x1a0, 0x1a2, 0x3, 0x2, 0x2, 0x2, 0x1a1, 0x19a, 0x3,
            0x2, 0x2, 0x2, 0x1a2, 0x1a5, 0x3, 0x2, 0x2, 0x2, 0x1a3, 0x1a1, 0x3,
            0x2, 0x2, 0x2, 0x1a3, 0x1a4, 0x3, 0x2, 0x2, 0x2, 0x1a4, 0x17, 0x3, 0x2,
            0x2, 0x2, 0x1a5, 0x1a3, 0x3, 0x2, 0x2, 0x2, 0x1a6, 0x1a7, 0x5, 0x7e,
            0x40, 0x2, 0x1a7, 0x1a8, 0x7, 0x1a, 0x2, 0x2, 0x1a8, 0x1b0, 0x5, 0x4c,
            0x27, 0x2, 0x1a9, 0x1aa, 0x7, 0x19, 0x2, 0x2, 0x1aa, 0x1ab, 0x5, 0x7e,
            0x40, 0x2, 0x1ab, 0x1ac, 0x7, 0x1a, 0x2, 0x2, 0x1ac, 0x1ad, 0x5, 0x4c,
            0x27, 0x2, 0x1ad, 0x1af, 0x3, 0x2, 0x2, 0x2, 0x1ae, 0x1a9, 0x3, 0x2,
            0x2, 0x2, 0x1af, 0x1b2, 0x3, 0x2, 0x2, 0x2, 0x1b0, 0x1ae, 0x3, 0x2,
            0x2, 0x2, 0x1b0, 0x1b1, 0x3, 0x2, 0x2, 0x2, 0x1b1, 0x19, 0x3, 0x2, 0x2,
            0x2, 0x1b2, 0x1b0, 0x3, 0x2, 0x2, 0x2, 0x1b3, 0x1b9, 0x5, 0x7e, 0x40,
            0x2, 0x1b4, 0x1b5, 0x5, 0x7e, 0x40, 0x2, 0x1b5, 0x1b6, 0x7, 0x1a, 0x2,
            0x2, 0x1b6, 0x1b7, 0x5, 0x4c, 0x27, 0x2, 0x1b7, 0x1b9, 0x3, 0x2, 0x2,
            0x2, 0x1b8, 0x1b3, 0x3, 0x2, 0x2, 0x2, 0x1b8, 0x1b4, 0x3, 0x2, 0x2,
            0x2, 0x1b9, 0x1c4, 0x3, 0x2, 0x2, 0x2, 0x1ba, 0x1c0, 0x7, 0x19, 0x2,
            0x2, 0x1bb, 0x1c1, 0x5, 0x7e, 0x40, 0x2, 0x1bc, 0x1bd, 0x5, 0x7e, 0x40,
            0x2, 0x1bd, 0x1be, 0x7, 0x1a, 0x2, 0x2, 0x1be, 0x1bf, 0x5, 0x4c, 0x27,
            0x2, 0x1bf, 0x1c1, 0x3, 0x2, 0x2, 0x2, 0x1c0, 0x1bb, 0x3, 0x2, 0x2,
            0x2, 0x1c0, 0x1bc, 0x3, 0x2, 0x2, 0x2, 0x1c1, 0x1c3, 0x3, 0x2, 0x2,
            0x2, 0x1c2, 0x1ba, 0x3, 0x2, 0x2, 0x2, 0x1c3, 0x1c6, 0x3, 0x2, 0x2,
            0x2, 0x1c4, 0x1c2, 0x3, 0x2, 0x2, 0x2, 0x1c4, 0x1c5, 0x3, 0x2, 0x2,
            0x2, 0x1c5, 0x1b, 0x3, 0x2, 0x2, 0x2, 0x1c6, 0x1c4, 0x3, 0x2, 0x2, 0x2,
            0x1c7, 0x1c8, 0x7, 0x1d, 0x2, 0x2, 0x1c8, 0x1ce, 0x7, 0x1e, 0x2, 0x2,
            0x1c9, 0x1ca, 0x7, 0x1d, 0x2, 0x2, 0x1ca, 0x1cb, 0x5, 0x1e, 0x10, 0x2,
            0x1cb, 0x1cc, 0x7, 0x1e, 0x2, 0x2, 0x1cc, 0x1ce, 0x3, 0x2, 0x2, 0x2,
            0x1cd, 0x1c7, 0x3, 0x2, 0x2, 0x2, 0x1cd, 0x1c9, 0x3, 0x2, 0x2, 0x2,
            0x1ce, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x1cf, 0x1d0, 0x5, 0x6e, 0x38, 0x2,
            0x1d0, 0x1d7, 0x5, 0x7e, 0x40, 0x2, 0x1d1, 0x1d2, 0x7, 0x4, 0x2, 0x2,
            0x1d2, 0x1d3, 0x5, 0x6e, 0x38, 0x2, 0x1d3, 0x1d4, 0x5, 0x7e, 0x40, 0x2,
            0x1d4, 0x1d6, 0x3, 0x2, 0x2, 0x2, 0x1d5, 0x1d1, 0x3, 0x2, 0x2, 0x2,
            0x1d6, 0x1d9, 0x3, 0x2, 0x2, 0x2, 0x1d7, 0x1d5, 0x3, 0x2, 0x2, 0x2,
            0x1d7, 0x1d8, 0x3, 0x2, 0x2, 0x2, 0x1d8, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x1d9,
            0x1d7, 0x3, 0x2, 0x2, 0x2, 0x1da, 0x1db, 0x5, 0x22, 0x12, 0x2, 0x1db,
            0x1dc, 0x5, 0x26, 0x14, 0x2, 0x1dc, 0x1dd, 0x7, 0xa, 0x2, 0x2, 0x1dd,
            0x1e2, 0x3, 0x2, 0x2, 0x2, 0x1de, 0x1df, 0x5, 0x80, 0x41, 0x2, 0x1df,
            0x1e0, 0x7, 0x4, 0x2, 0x2, 0x1e0, 0x1e2, 0x3, 0x2, 0x2, 0x2, 0x1e1,
            0x1da, 0x3, 0x2, 0x2, 0x2, 0x1e1, 0x1de, 0x3, 0x2, 0x2, 0x2, 0x1e2,
            0x21, 0x3, 0x2, 0x2, 0x2, 0x1e3, 0x1e4, 0x5, 0x6e, 0x38, 0x2, 0x1e4,
            0x1e5, 0x5, 0x24, 0x13, 0x2, 0x1e5, 0x1e6, 0x7, 0x4, 0x2, 0x2, 0x1e6,
            0x1e8, 0x3, 0x2, 0x2, 0x2, 0x1e7, 0x1e3, 0x3, 0x2, 0x2, 0x2, 0x1e8,
            0x1eb, 0x3, 0x2, 0x2, 0x2, 0x1e9, 0x1e7, 0x3, 0x2, 0x2, 0x2, 0x1e9,
            0x1ea, 0x3, 0x2, 0x2, 0x2, 0x1ea, 0x23, 0x3, 0x2, 0x2, 0x2, 0x1eb, 0x1e9,
            0x3, 0x2, 0x2, 0x2, 0x1ec, 0x1f2, 0x5, 0x7e, 0x40, 0x2, 0x1ed, 0x1ee,
            0x5, 0x7e, 0x40, 0x2, 0x1ee, 0x1ef, 0x7, 0x1a, 0x2, 0x2, 0x1ef, 0x1f0,
            0x5, 0x4c, 0x27, 0x2, 0x1f0, 0x1f2, 0x3, 0x2, 0x2, 0x2, 0x1f1, 0x1ec,
            0x3, 0x2, 0x2, 0x2, 0x1f1, 0x1ed, 0x3, 0x2, 0x2, 0x2, 0x1f2, 0x1fd,
            0x3, 0x2, 0x2, 0x2, 0x1f3, 0x1f9, 0x7, 0x19, 0x2, 0x2, 0x1f4, 0x1fa,
            0x5, 0x7e, 0x40, 0x2, 0x1f5, 0x1f6, 0x5, 0x7e, 0x40, 0x2, 0x1f6, 0x1f7,
            0x7, 0x1a, 0x2, 0x2, 0x1f7, 0x1f8, 0x5, 0x4c, 0x27, 0x2, 0x1f8, 0x1fa,
            0x3, 0x2, 0x2, 0x2, 0x1f9, 0x1f4, 0x3, 0x2, 0x2, 0x2, 0x1f9, 0x1f5,
            0x3, 0x2, 0x2, 0x2, 0x1fa, 0x1fc, 0x3, 0x2, 0x2, 0x2, 0x1fb, 0x1f3,
            0x3, 0x2, 0x2, 0x2, 0x1fc, 0x1ff, 0x3, 0x2, 0x2, 0x2, 0x1fd, 0x1fb,
            0x3, 0x2, 0x2, 0x2, 0x1fd, 0x1fe, 0x3, 0x2, 0x2, 0x2, 0x1fe, 0x25, 0x3,
            0x2, 0x2, 0x2, 0x1ff, 0x1fd, 0x3, 0x2, 0x2, 0x2, 0x200, 0x202, 0x5,
            0x28, 0x15, 0x2, 0x201, 0x200, 0x3, 0x2, 0x2, 0x2, 0x202, 0x203, 0x3,
            0x2, 0x2, 0x2, 0x203, 0x201, 0x3, 0x2, 0x2, 0x2, 0x203, 0x204, 0x3,
            0x2, 0x2, 0x2, 0x204, 0x27, 0x3, 0x2, 0x2, 0x2, 0x205, 0x206, 0x5, 0xa6,
            0x54, 0x2, 0x206, 0x207, 0x7, 0x1f, 0x2, 0x2, 0x207, 0x208, 0x5, 0x48,
            0x25, 0x2, 0x208, 0x209, 0x7, 0x4, 0x2, 0x2, 0x209, 0x221, 0x3, 0x2,
            0x2, 0x2, 0x20a, 0x20b, 0x7, 0x20, 0x2, 0x2, 0x20b, 0x20c, 0x5, 0x48,
            0x25, 0x2, 0x20c, 0x20d, 0x7, 0x7, 0x2, 0x2, 0x20d, 0x20e, 0x5, 0x26,
            0x14, 0x2, 0x20e, 0x20f, 0x5, 0x2a, 0x16, 0x2, 0x20f, 0x210, 0x5, 0x2c,
            0x17, 0x2, 0x210, 0x211, 0x7, 0xa, 0x2, 0x2, 0x211, 0x221, 0x3, 0x2,
            0x2, 0x2, 0x212, 0x213, 0x7, 0x21, 0x2, 0x2, 0x213, 0x214, 0x5, 0x48,
            0x25, 0x2, 0x214, 0x215, 0x7, 0x7, 0x2, 0x2, 0x215, 0x216, 0x5, 0x26,
            0x14, 0x2, 0x216, 0x217, 0x7, 0xa, 0x2, 0x2, 0x217, 0x221, 0x3, 0x2,
            0x2, 0x2, 0x218, 0x219, 0x7, 0x22, 0x2, 0x2, 0x219, 0x221, 0x7, 0x4,
            0x2, 0x2, 0x21a, 0x21b, 0x7, 0x23, 0x2, 0x2, 0x21b, 0x221, 0x7, 0x4,
            0x2, 0x2, 0x21c, 0x21d, 0x7, 0x24, 0x2, 0x2, 0x21d, 0x21e, 0x5, 0x48,
            0x25, 0x2, 0x21e, 0x21f, 0x7, 0x4, 0x2, 0x2, 0x21f, 0x221, 0x3, 0x2,
            0x2, 0x2, 0x220, 0x205, 0x3, 0x2, 0x2, 0x2, 0x220, 0x20a, 0x3, 0x2,
            0x2, 0x2, 0x220, 0x212, 0x3, 0x2, 0x2, 0x2, 0x220, 0x218, 0x3, 0x2,
            0x2, 0x2, 0x220, 0x21a, 0x3, 0x2, 0x2, 0x2, 0x220, 0x21c, 0x3, 0x2,
            0x2, 0x2, 0x221, 0x29, 0x3, 0x2, 0x2, 0x2, 0x222, 0x223, 0x7, 0x25,
            0x2, 0x2, 0x223, 0x224, 0x5, 0x4c, 0x27, 0x2, 0x224, 0x225, 0x7, 0x7,
            0x2, 0x2, 0x225, 0x226, 0x5, 0x26, 0x14, 0x2, 0x226, 0x228, 0x3, 0x2,
            0x2, 0x2, 0x227, 0x222, 0x3, 0x2, 0x2, 0x2, 0x228, 0x22b, 0x3, 0x2,
            0x2, 0x2, 0x229, 0x227, 0x3, 0x2, 0x2, 0x2, 0x229, 0x22a, 0x3, 0x2,
            0x2, 0x2, 0x22a, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x22b, 0x229, 0x3, 0x2, 0x2,
            0x2, 0x22c, 0x22d, 0x7, 0x26, 0x2, 0x2, 0x22d, 0x22e, 0x5, 0x26, 0x14,
            0x2, 0x22e, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x22f, 0x234, 0x5, 0x78, 0x3d,
            0x2, 0x230, 0x231, 0x7, 0x19, 0x2, 0x2, 0x231, 0x233, 0x5, 0x78, 0x3d,
            0x2, 0x232, 0x230, 0x3, 0x2, 0x2, 0x2, 0x233, 0x236, 0x3, 0x2, 0x2,
            0x2, 0x234, 0x232, 0x3, 0x2, 0x2, 0x2, 0x234, 0x235, 0x3, 0x2, 0x2,
            0x2, 0x235, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x236, 0x234, 0x3, 0x2, 0x2, 0x2,
            0x237, 0x238, 0x7, 0x1d, 0x2, 0x2, 0x238, 0x23e, 0x7, 0x1e, 0x2, 0x2,
            0x239, 0x23a, 0x7, 0x1d, 0x2, 0x2, 0x23a, 0x23b, 0x5, 0x48, 0x25, 0x2,
            0x23b, 0x23c, 0x7, 0x1e, 0x2, 0x2, 0x23c, 0x23e, 0x3, 0x2, 0x2, 0x2,
            0x23d, 0x237, 0x3, 0x2, 0x2, 0x2, 0x23d, 0x239, 0x3, 0x2, 0x2, 0x2,
            0x23e, 0x31, 0x3, 0x2, 0x2, 0x2, 0x23f, 0x240, 0x7, 0x1d, 0x2, 0x2,
            0x240, 0x246, 0x7, 0x1e, 0x2, 0x2, 0x241, 0x242, 0x7, 0x1d, 0x2, 0x2,
            0x242, 0x243, 0x5, 0x34, 0x1b, 0x2, 0x243, 0x244, 0x7, 0x1e, 0x2, 0x2,
            0x244, 0x246, 0x3, 0x2, 0x2, 0x2, 0x245, 0x23f, 0x3, 0x2, 0x2, 0x2,
            0x245, 0x241, 0x3, 0x2, 0x2, 0x2, 0x246, 0x33, 0x3, 0x2, 0x2, 0x2, 0x247,
            0x24c, 0x5, 0x36, 0x1c, 0x2, 0x248, 0x249, 0x7, 0x4, 0x2, 0x2, 0x249,
            0x24b, 0x5, 0x36, 0x1c, 0x2, 0x24a, 0x248, 0x3, 0x2, 0x2, 0x2, 0x24b,
            0x24e, 0x3, 0x2, 0x2, 0x2, 0x24c, 0x24a, 0x3, 0x2, 0x2, 0x2, 0x24c,
            0x24d, 0x3, 0x2, 0x2, 0x2, 0x24d, 0x35, 0x3, 0x2, 0x2, 0x2, 0x24e, 0x24c,
            0x3, 0x2, 0x2, 0x2, 0x24f, 0x250, 0x5, 0x42, 0x22, 0x2, 0x250, 0x251,
            0x7, 0x11, 0x2, 0x2, 0x251, 0x252, 0x5, 0x7e, 0x40, 0x2, 0x252, 0x269,
            0x3, 0x2, 0x2, 0x2, 0x253, 0x254, 0x5, 0x42, 0x22, 0x2, 0x254, 0x255,
            0x7, 0x11, 0x2, 0x2, 0x255, 0x256, 0x5, 0x46, 0x24, 0x2, 0x256, 0x257,
            0x5, 0x7e, 0x40, 0x2, 0x257, 0x269, 0x3, 0x2, 0x2, 0x2, 0x258, 0x259,
            0x5, 0x44, 0x23, 0x2, 0x259, 0x25a, 0x5, 0x7e, 0x40, 0x2, 0x25a, 0x269,
            0x3, 0x2, 0x2, 0x2, 0x25b, 0x25c, 0x5, 0x44, 0x23, 0x2, 0x25c, 0x25d,
            0x5, 0x46, 0x24, 0x2, 0x25d, 0x25e, 0x5, 0x7e, 0x40, 0x2, 0x25e, 0x269,
            0x3, 0x2, 0x2, 0x2, 0x25f, 0x260, 0x5, 0x78, 0x3d, 0x2, 0x260, 0x261,
            0x5, 0x7e, 0x40, 0x2, 0x261, 0x269, 0x3, 0x2, 0x2, 0x2, 0x262, 0x263,
            0x7, 0x27, 0x2, 0x2, 0x263, 0x269, 0x5, 0x7e, 0x40, 0x2, 0x264, 0x265,
            0x7, 0x13, 0x2, 0x2, 0x265, 0x266, 0x5, 0x6e, 0x38, 0x2, 0x266, 0x267,
            0x5, 0x7e, 0x40, 0x2, 0x267, 0x269, 0x3, 0x2, 0x2, 0x2, 0x268, 0x24f,
            0x3, 0x2, 0x2, 0x2, 0x268, 0x253, 0x3, 0x2, 0x2, 0x2, 0x268, 0x258,
            0x3, 0x2, 0x2, 0x2, 0x268, 0x25b, 0x3, 0x2, 0x2, 0x2, 0x268, 0x25f,
            0x3, 0x2, 0x2, 0x2, 0x268, 0x262, 0x3, 0x2, 0x2, 0x2, 0x268, 0x264,
            0x3, 0x2, 0x2, 0x2, 0x269, 0x37, 0x3, 0x2, 0x2, 0x2, 0x26a, 0x26f, 0x5,
            0x3a, 0x1e, 0x2, 0x26b, 0x26c, 0x7, 0x19, 0x2, 0x2, 0x26c, 0x26e, 0x5,
            0x3a, 0x1e, 0x2, 0x26d, 0x26b, 0x3, 0x2, 0x2, 0x2, 0x26e, 0x271, 0x3,
            0x2, 0x2, 0x2, 0x26f, 0x26d, 0x3, 0x2, 0x2, 0x2, 0x26f, 0x270, 0x3,
            0x2, 0x2, 0x2, 0x270, 0x39, 0x3, 0x2, 0x2, 0x2, 0x271, 0x26f, 0x3, 0x2,
            0x2, 0x2, 0x272, 0x282, 0x5, 0x7e, 0x40, 0x2, 0x273, 0x274, 0x5, 0x7e,
            0x40, 0x2, 0x274, 0x275, 0x7, 0x28, 0x2, 0x2, 0x275, 0x276, 0x7, 0x29,
            0x2, 0x2, 0x276, 0x282, 0x3, 0x2, 0x2, 0x2, 0x277, 0x278, 0x5, 0x7e,
            0x40, 0x2, 0x278, 0x279, 0x7, 0x1a, 0x2, 0x2, 0x279, 0x27a, 0x5, 0x4c,
            0x27, 0x2, 0x27a, 0x282, 0x3, 0x2, 0x2, 0x2, 0x27b, 0x27c, 0x5, 0x7e,
            0x40, 0x2, 0x27c, 0x27d, 0x7, 0x28, 0x2, 0x2, 0x27d, 0x27e, 0x7, 0x1b,
            0x2, 0x2, 0x27e, 0x27f, 0x5, 0x48, 0x25, 0x2, 0x27f, 0x280, 0x7, 0x1c,
            0x2, 0x2, 0x280, 0x282, 0x3, 0x2, 0x2, 0x2, 0x281, 0x272, 0x3, 0x2,
            0x2, 0x2, 0x281, 0x273, 0x3, 0x2, 0x2, 0x2, 0x281, 0x277, 0x3, 0x2,
            0x2, 0x2, 0x281, 0x27b, 0x3, 0x2, 0x2, 0x2, 0x282, 0x3b, 0x3, 0x2, 0x2,
            0x2, 0x283, 0x288, 0x5, 0x3e, 0x20, 0x2, 0x284, 0x285, 0x7, 0x19, 0x2,
            0x2, 0x285, 0x287, 0x5, 0x3e, 0x20, 0x2, 0x286, 0x284, 0x3, 0x2, 0x2,
            0x2, 0x287, 0x28a, 0x3, 0x2, 0x2, 0x2, 0x288, 0x286, 0x3, 0x2, 0x2,
            0x2, 0x288, 0x289, 0x3, 0x2, 0x2, 0x2, 0x289, 0x3d, 0x3, 0x2, 0x2, 0x2,
            0x28a, 0x288, 0x3, 0x2, 0x2, 0x2, 0x28b, 0x28c, 0x5, 0x7e, 0x40, 0x2,
            0x28c, 0x28d, 0x5, 0x40, 0x21, 0x2, 0x28d, 0x294, 0x3, 0x2, 0x2, 0x2,
            0x28e, 0x28f, 0x5, 0x7e, 0x40, 0x2, 0x28f, 0x290, 0x7, 0x1a, 0x2, 0x2,
            0x290, 0x291, 0x5, 0x4c, 0x27, 0x2, 0x291, 0x292, 0x5, 0x40, 0x21, 0x2,
            0x292, 0x294, 0x3, 0x2, 0x2, 0x2, 0x293, 0x28b, 0x3, 0x2, 0x2, 0x2,
            0x293, 0x28e, 0x3, 0x2, 0x2, 0x2, 0x294, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x295,
            0x296, 0x7, 0x2a, 0x2, 0x2, 0x296, 0x298, 0x5, 0x4c, 0x27, 0x2, 0x297,
            0x295, 0x3, 0x2, 0x2, 0x2, 0x297, 0x298, 0x3, 0x2, 0x2, 0x2, 0x298,
            0x41, 0x3, 0x2, 0x2, 0x2, 0x299, 0x29b, 0x5, 0x44, 0x23, 0x2, 0x29a,
            0x299, 0x3, 0x2, 0x2, 0x2, 0x29a, 0x29b, 0x3, 0x2, 0x2, 0x2, 0x29b,
            0x43, 0x3, 0x2, 0x2, 0x2, 0x29c, 0x29d, 0x9, 0x2, 0x2, 0x2, 0x29d, 0x45,
            0x3, 0x2, 0x2, 0x2, 0x29e, 0x2a1, 0x7, 0x2d, 0x2, 0x2, 0x29f, 0x2a1,
            0x5, 0x6e, 0x38, 0x2, 0x2a0, 0x29e, 0x3, 0x2, 0x2, 0x2, 0x2a0, 0x29f,
            0x3, 0x2, 0x2, 0x2, 0x2a1, 0x47, 0x3, 0x2, 0x2, 0x2, 0x2a2, 0x2a7, 0x5,
            0x4c, 0x27, 0x2, 0x2a3, 0x2a4, 0x7, 0x19, 0x2, 0x2, 0x2a4, 0x2a6, 0x5,
            0x4c, 0x27, 0x2, 0x2a5, 0x2a3, 0x3, 0x2, 0x2, 0x2, 0x2a6, 0x2a9, 0x3,
            0x2, 0x2, 0x2, 0x2a7, 0x2a5, 0x3, 0x2, 0x2, 0x2, 0x2a7, 0x2a8, 0x3,
            0x2, 0x2, 0x2, 0x2a8, 0x49, 0x3, 0x2, 0x2, 0x2, 0x2a9, 0x2a7, 0x3, 0x2,
            0x2, 0x2, 0x2aa, 0x2ac, 0x5, 0x4c, 0x27, 0x2, 0x2ab, 0x2aa, 0x3, 0x2,
            0x2, 0x2, 0x2ab, 0x2ac, 0x3, 0x2, 0x2, 0x2, 0x2ac, 0x4b, 0x3, 0x2, 0x2,
            0x2, 0x2ad, 0x2b7, 0x5, 0x52, 0x2a, 0x2, 0x2ae, 0x2af, 0x5, 0x52, 0x2a,
            0x2, 0x2af, 0x2b0, 0x7, 0x2e, 0x2, 0x2, 0x2b0, 0x2b1, 0x5, 0x52, 0x2a,
            0x2, 0x2b1, 0x2b7, 0x3, 0x2, 0x2, 0x2, 0x2b2, 0x2b3, 0x5, 0x52, 0x2a,
            0x2, 0x2b3, 0x2b4, 0x7, 0x2f, 0x2, 0x2, 0x2b4, 0x2b5, 0x5, 0x52, 0x2a,
            0x2, 0x2b5, 0x2b7, 0x3, 0x2, 0x2, 0x2, 0x2b6, 0x2ad, 0x3, 0x2, 0x2,
            0x2, 0x2b6, 0x2ae, 0x3, 0x2, 0x2, 0x2, 0x2b6, 0x2b2, 0x3, 0x2, 0x2,
            0x2, 0x2b7, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x2b8, 0x2bd, 0x5, 0x50, 0x29,
            0x2, 0x2b9, 0x2ba, 0x7, 0x19, 0x2, 0x2, 0x2ba, 0x2bc, 0x5, 0x50, 0x29,
            0x2, 0x2bb, 0x2b9, 0x3, 0x2, 0x2, 0x2, 0x2bc, 0x2bf, 0x3, 0x2, 0x2,
            0x2, 0x2bd, 0x2bb, 0x3, 0x2, 0x2, 0x2, 0x2bd, 0x2be, 0x3, 0x2, 0x2,
            0x2, 0x2be, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x2bf, 0x2bd, 0x3, 0x2, 0x2, 0x2,
            0x2c0, 0x2c1, 0x5, 0x7e, 0x40, 0x2, 0x2c1, 0x2c2, 0x7, 0x30, 0x2, 0x2,
            0x2c2, 0x2c3, 0x7, 0x1a, 0x2, 0x2, 0x2c3, 0x2c4, 0x5, 0x4c, 0x27, 0x2,
            0x2c4, 0x2ca, 0x3, 0x2, 0x2, 0x2, 0x2c5, 0x2c6, 0x5, 0x7e, 0x40, 0x2,
            0x2c6, 0x2c7, 0x7, 0x1a, 0x2, 0x2, 0x2c7, 0x2c8, 0x5, 0x4c, 0x27, 0x2,
            0x2c8, 0x2ca, 0x3, 0x2, 0x2, 0x2, 0x2c9, 0x2c0, 0x3, 0x2, 0x2, 0x2,
            0x2c9, 0x2c5, 0x3, 0x2, 0x2, 0x2, 0x2ca, 0x51, 0x3, 0x2, 0x2, 0x2, 0x2cb,
            0x2d0, 0x5, 0x54, 0x2b, 0x2, 0x2cc, 0x2cd, 0x7, 0x31, 0x2, 0x2, 0x2cd,
            0x2cf, 0x5, 0x54, 0x2b, 0x2, 0x2ce, 0x2cc, 0x3, 0x2, 0x2, 0x2, 0x2cf,
            0x2d2, 0x3, 0x2, 0x2, 0x2, 0x2d0, 0x2ce, 0x3, 0x2, 0x2, 0x2, 0x2d0,
            0x2d1, 0x3, 0x2, 0x2, 0x2, 0x2d1, 0x53, 0x3, 0x2, 0x2, 0x2, 0x2d2, 0x2d0,
            0x3, 0x2, 0x2, 0x2, 0x2d3, 0x2d8, 0x5, 0x56, 0x2c, 0x2, 0x2d4, 0x2d5,
            0x7, 0x32, 0x2, 0x2, 0x2d5, 0x2d7, 0x5, 0x56, 0x2c, 0x2, 0x2d6, 0x2d4,
            0x3, 0x2, 0x2, 0x2, 0x2d7, 0x2da, 0x3, 0x2, 0x2, 0x2, 0x2d8, 0x2d6,
            0x3, 0x2, 0x2, 0x2, 0x2d8, 0x2d9, 0x3, 0x2, 0x2, 0x2, 0x2d9, 0x55, 0x3,
            0x2, 0x2, 0x2, 0x2da, 0x2d8, 0x3, 0x2, 0x2, 0x2, 0x2db, 0x2e0, 0x5,
            0x58, 0x2d, 0x2, 0x2dc, 0x2dd, 0x7, 0x8d, 0x2, 0x2, 0x2dd, 0x2df, 0x5,
            0x58, 0x2d, 0x2, 0x2de, 0x2dc, 0x3, 0x2, 0x2, 0x2, 0x2df, 0x2e2, 0x3,
            0x2, 0x2, 0x2, 0x2e0, 0x2de, 0x3, 0x2, 0x2, 0x2, 0x2e0, 0x2e1, 0x3,
            0x2, 0x2, 0x2, 0x2e1, 0x57, 0x3, 0x2, 0x2, 0x2, 0x2e2, 0x2e0, 0x3, 0x2,
            0x2, 0x2, 0x2e3, 0x2e8, 0x5, 0x5a, 0x2e, 0x2, 0x2e4, 0x2e5, 0x7, 0x8c,
            0x2, 0x2, 0x2e5, 0x2e7, 0x5, 0x5a, 0x2e, 0x2, 0x2e6, 0x2e4, 0x3, 0x2,
            0x2, 0x2, 0x2e7, 0x2ea, 0x3, 0x2, 0x2, 0x2, 0x2e8, 0x2e6, 0x3, 0x2,
            0x2, 0x2, 0x2e8, 0x2e9, 0x3, 0x2, 0x2, 0x2, 0x2e9, 0x59, 0x3, 0x2, 0x2,
            0x2, 0x2ea, 0x2e8, 0x3, 0x2, 0x2, 0x2, 0x2eb, 0x2f0, 0x5, 0x5c, 0x2f,
            0x2, 0x2ec, 0x2ed, 0x7, 0x8b, 0x2, 0x2, 0x2ed, 0x2ef, 0x5, 0x5c, 0x2f,
            0x2, 0x2ee, 0x2ec, 0x3, 0x2, 0x2, 0x2, 0x2ef, 0x2f2, 0x3, 0x2, 0x2,
            0x2, 0x2f0, 0x2ee, 0x3, 0x2, 0x2, 0x2, 0x2f0, 0x2f1, 0x3, 0x2, 0x2,
            0x2, 0x2f1, 0x5b, 0x3, 0x2, 0x2, 0x2, 0x2f2, 0x2f0, 0x3, 0x2, 0x2, 0x2,
            0x2f3, 0x2fd, 0x5, 0x5e, 0x30, 0x2, 0x2f4, 0x2f5, 0x7, 0x33, 0x2, 0x2,
            0x2f5, 0x2fd, 0x5, 0x5c, 0x2f, 0x2, 0x2f6, 0x2f7, 0x7, 0x34, 0x2, 0x2,
            0x2f7, 0x2fd, 0x5, 0x5c, 0x2f, 0x2, 0x2f8, 0x2f9, 0x7, 0x35, 0x2, 0x2,
            0x2f9, 0x2fd, 0x5, 0x5c, 0x2f, 0x2, 0x2fa, 0x2fb, 0x7, 0x36, 0x2, 0x2,
            0x2fb, 0x2fd, 0x5, 0x5c, 0x2f, 0x2, 0x2fc, 0x2f3, 0x3, 0x2, 0x2, 0x2,
            0x2fc, 0x2f4, 0x3, 0x2, 0x2, 0x2, 0x2fc, 0x2f6, 0x3, 0x2, 0x2, 0x2,
            0x2fc, 0x2f8, 0x3, 0x2, 0x2, 0x2, 0x2fc, 0x2fa, 0x3, 0x2, 0x2, 0x2,
            0x2fd, 0x5d, 0x3, 0x2, 0x2, 0x2, 0x2fe, 0x309, 0x5, 0x60, 0x31, 0x2,
            0x2ff, 0x300, 0x5, 0x82, 0x42, 0x2, 0x300, 0x301, 0x7, 0x1d, 0x2, 0x2,
            0x301, 0x302, 0x7, 0x1e, 0x2, 0x2, 0x302, 0x309, 0x3, 0x2, 0x2, 0x2,
            0x303, 0x304, 0x5, 0x82, 0x42, 0x2, 0x304, 0x305, 0x7, 0x1d, 0x2, 0x2,
            0x305, 0x306, 0x5, 0x48, 0x25, 0x2, 0x306, 0x307, 0x7, 0x1e, 0x2, 0x2,
            0x307, 0x309, 0x3, 0x2, 0x2, 0x2, 0x308, 0x2fe, 0x3, 0x2, 0x2, 0x2,
            0x308, 0x2ff, 0x3, 0x2, 0x2, 0x2, 0x308, 0x303, 0x3, 0x2, 0x2, 0x2,
            0x309, 0x31c, 0x3, 0x2, 0x2, 0x2, 0x30a, 0x30b, 0x7, 0x37, 0x2, 0x2,
            0x30b, 0x30c, 0x5, 0x48, 0x25, 0x2, 0x30c, 0x30d, 0x7, 0x38, 0x2, 0x2,
            0x30d, 0x31b, 0x3, 0x2, 0x2, 0x2, 0x30e, 0x30f, 0x7, 0x37, 0x2, 0x2,
            0x30f, 0x310, 0x5, 0x4a, 0x26, 0x2, 0x310, 0x311, 0x7, 0x7, 0x2, 0x2,
            0x311, 0x312, 0x5, 0x4a, 0x26, 0x2, 0x312, 0x313, 0x7, 0x38, 0x2, 0x2,
            0x313, 0x31b, 0x3, 0x2, 0x2, 0x2, 0x314, 0x315, 0x7, 0x1d, 0x2, 0x2,
            0x315, 0x31b, 0x7, 0x1e, 0x2, 0x2, 0x316, 0x317, 0x7, 0x1d, 0x2, 0x2,
            0x317, 0x318, 0x5, 0x48, 0x25, 0x2, 0x318, 0x319, 0x7, 0x1e, 0x2, 0x2,
            0x319, 0x31b, 0x3, 0x2, 0x2, 0x2, 0x31a, 0x30a, 0x3, 0x2, 0x2, 0x2,
            0x31a, 0x30e, 0x3, 0x2, 0x2, 0x2, 0x31a, 0x314, 0x3, 0x2, 0x2, 0x2,
            0x31a, 0x316, 0x3, 0x2, 0x2, 0x2, 0x31b, 0x31e, 0x3, 0x2, 0x2, 0x2,
            0x31c, 0x31a, 0x3, 0x2, 0x2, 0x2, 0x31c, 0x31d, 0x3, 0x2, 0x2, 0x2,
            0x31d, 0x5f, 0x3, 0x2, 0x2, 0x2, 0x31e, 0x31c, 0x3, 0x2, 0x2, 0x2, 0x31f,
            0x357, 0x7, 0x39, 0x2, 0x2, 0x320, 0x357, 0x7, 0x3a, 0x2, 0x2, 0x321,
            0x357, 0x7, 0x8e, 0x2, 0x2, 0x322, 0x357, 0x7, 0x8f, 0x2, 0x2, 0x323,
            0x357, 0x5, 0x78, 0x3d, 0x2, 0x324, 0x357, 0x5, 0x80, 0x41, 0x2, 0x325,
            0x357, 0x7, 0x3b, 0x2, 0x2, 0x326, 0x327, 0x7, 0x37, 0x2, 0x2, 0x327,
            0x357, 0x7, 0x38, 0x2, 0x2, 0x328, 0x329, 0x7, 0x37, 0x2, 0x2, 0x329,
            0x32a, 0x5, 0x48, 0x25, 0x2, 0x32a, 0x32b, 0x7, 0x38, 0x2, 0x2, 0x32b,
            0x357, 0x3, 0x2, 0x2, 0x2, 0x32c, 0x32d, 0x7, 0x1b, 0x2, 0x2, 0x32d,
            0x357, 0x7, 0x1c, 0x2, 0x2, 0x32e, 0x357, 0x5, 0x62, 0x32, 0x2, 0x32f,
            0x330, 0x7, 0x1b, 0x2, 0x2, 0x330, 0x331, 0x5, 0x64, 0x33, 0x2, 0x331,
            0x332, 0x7, 0x1c, 0x2, 0x2, 0x332, 0x357, 0x3, 0x2, 0x2, 0x2, 0x333,
            0x334, 0x7, 0x1d, 0x2, 0x2, 0x334, 0x335, 0x5, 0x4c, 0x27, 0x2, 0x335,
            0x336, 0x7, 0x19, 0x2, 0x2, 0x336, 0x337, 0x5, 0x4c, 0x27, 0x2, 0x337,
            0x338, 0x7, 0x1e, 0x2, 0x2, 0x338, 0x357, 0x3, 0x2, 0x2, 0x2, 0x339,
            0x33a, 0x7, 0x3c, 0x2, 0x2, 0x33a, 0x33b, 0x5, 0x6e, 0x38, 0x2, 0x33b,
            0x33c, 0x7, 0x3d, 0x2, 0x2, 0x33c, 0x33d, 0x5, 0x60, 0x31, 0x2, 0x33d,
            0x357, 0x3, 0x2, 0x2, 0x2, 0x33e, 0x33f, 0x7, 0x20, 0x2, 0x2, 0x33f,
            0x340, 0x5, 0x48, 0x25, 0x2, 0x340, 0x341, 0x7, 0x7, 0x2, 0x2, 0x341,
            0x342, 0x5, 0x4c, 0x27, 0x2, 0x342, 0x343, 0x5, 0x66, 0x34, 0x2, 0x343,
            0x344, 0x7, 0x26, 0x2, 0x2, 0x344, 0x345, 0x5, 0x4c, 0x27, 0x2, 0x345,
            0x346, 0x7, 0xa, 0x2, 0x2, 0x346, 0x357, 0x3, 0x2, 0x2, 0x2, 0x347,
            0x348, 0x7, 0x3e, 0x2, 0x2, 0x348, 0x349, 0x5, 0x4c, 0x27, 0x2, 0x349,
            0x34a, 0x7, 0x7, 0x2, 0x2, 0x34a, 0x34b, 0x5, 0x68, 0x35, 0x2, 0x34b,
            0x34c, 0x7, 0xa, 0x2, 0x2, 0x34c, 0x357, 0x3, 0x2, 0x2, 0x2, 0x34d,
            0x34e, 0x7, 0x1d, 0x2, 0x2, 0x34e, 0x34f, 0x5, 0x4c, 0x27, 0x2, 0x34f,
            0x350, 0x7, 0x1e, 0x2, 0x2, 0x350, 0x357, 0x3, 0x2, 0x2, 0x2, 0x351,
            0x352, 0x5, 0x78, 0x3d, 0x2, 0x352, 0x353, 0x7, 0x30, 0x2, 0x2, 0x353,
            0x357, 0x3, 0x2, 0x2, 0x2, 0x354, 0x357, 0x7, 0x3f, 0x2, 0x2, 0x355,
            0x357, 0x7, 0x40, 0x2, 0x2, 0x356, 0x31f, 0x3, 0x2, 0x2, 0x2, 0x356,
            0x320, 0x3, 0x2, 0x2, 0x2, 0x356, 0x321, 0x3, 0x2, 0x2, 0x2, 0x356,
            0x322, 0x3, 0x2, 0x2, 0x2, 0x356, 0x323, 0x3, 0x2, 0x2, 0x2, 0x356,
            0x324, 0x3, 0x2, 0x2, 0x2, 0x356, 0x325, 0x3, 0x2, 0x2, 0x2, 0x356,
            0x326, 0x3, 0x2, 0x2, 0x2, 0x356, 0x328, 0x3, 0x2, 0x2, 0x2, 0x356,
            0x32c, 0x3, 0x2, 0x2, 0x2, 0x356, 0x32e, 0x3, 0x2, 0x2, 0x2, 0x356,
            0x32f, 0x3, 0x2, 0x2, 0x2, 0x356, 0x333, 0x3, 0x2, 0x2, 0x2, 0x356,
            0x339, 0x3, 0x2, 0x2, 0x2, 0x356, 0x33e, 0x3, 0x2, 0x2, 0x2, 0x356,
            0x347, 0x3, 0x2, 0x2, 0x2, 0x356, 0x34d, 0x3, 0x2, 0x2, 0x2, 0x356,
            0x351, 0x3, 0x2, 0x2, 0x2, 0x356, 0x354, 0x3, 0x2, 0x2, 0x2, 0x356,
            0x355, 0x3, 0x2, 0x2, 0x2, 0x357, 0x61, 0x3, 0x2, 0x2, 0x2, 0x358, 0x359,
            0x7, 0x1b, 0x2, 0x2, 0x359, 0x35a, 0x5, 0x48, 0x25, 0x2, 0x35a, 0x35b,
            0x7, 0x1c, 0x2, 0x2, 0x35b, 0x63, 0x3, 0x2, 0x2, 0x2, 0x35c, 0x35d,
            0x5, 0x4c, 0x27, 0x2, 0x35d, 0x35e, 0x7, 0x7, 0x2, 0x2, 0x35e, 0x35f,
            0x5, 0x4c, 0x27, 0x2, 0x35f, 0x360, 0x7, 0x19, 0x2, 0x2, 0x360, 0x361,
            0x5, 0x4c, 0x27, 0x2, 0x361, 0x362, 0x7, 0x7, 0x2, 0x2, 0x362, 0x363,
            0x5, 0x4c, 0x27, 0x2, 0x363, 0x65, 0x3, 0x2, 0x2, 0x2, 0x364, 0x365,
            0x5, 0x4c, 0x27, 0x2, 0x365, 0x366, 0x7, 0x7, 0x2, 0x2, 0x366, 0x367,
            0x5, 0x4c, 0x27, 0x2, 0x367, 0x368, 0x7, 0x25, 0x2, 0x2, 0x368, 0x36a,
            0x3, 0x2, 0x2, 0x2, 0x369, 0x364, 0x3, 0x2, 0x2, 0x2, 0x36a, 0x36d,
            0x3, 0x2, 0x2, 0x2, 0x36b, 0x369, 0x3, 0x2, 0x2, 0x2, 0x36b, 0x36c,
            0x3, 0x2, 0x2, 0x2, 0x36c, 0x67, 0x3, 0x2, 0x2, 0x2, 0x36d, 0x36b, 0x3,
            0x2, 0x2, 0x2, 0x36e, 0x376, 0x5, 0x6a, 0x36, 0x2, 0x36f, 0x370, 0x5,
            0x6a, 0x36, 0x2, 0x370, 0x371, 0x7, 0x26, 0x2, 0x2, 0x371, 0x372, 0x5,
            0x4c, 0x27, 0x2, 0x372, 0x376, 0x3, 0x2, 0x2, 0x2, 0x373, 0x374, 0x7,
            0x26, 0x2, 0x2, 0x374, 0x376, 0x5, 0x4c, 0x27, 0x2, 0x375, 0x36e, 0x3,
            0x2, 0x2, 0x2, 0x375, 0x36f, 0x3, 0x2, 0x2, 0x2, 0x375, 0x373, 0x3,
            0x2, 0x2, 0x2, 0x376, 0x69, 0x3, 0x2, 0x2, 0x2, 0x377, 0x378, 0x7, 0x41,
            0x2, 0x2, 0x378, 0x379, 0x5, 0x4c, 0x27, 0x2, 0x379, 0x37a, 0x7, 0x7,
            0x2, 0x2, 0x37a, 0x37b, 0x5, 0x4c, 0x27, 0x2, 0x37b, 0x37d, 0x3, 0x2,
            0x2, 0x2, 0x37c, 0x377, 0x3, 0x2, 0x2, 0x2, 0x37d, 0x37e, 0x3, 0x2,
            0x2, 0x2, 0x37e, 0x37c, 0x3, 0x2, 0x2, 0x2, 0x37e, 0x37f, 0x3, 0x2,
            0x2, 0x2, 0x37f, 0x6b, 0x3, 0x2, 0x2, 0x2, 0x380, 0x385, 0x5, 0x6e,
            0x38, 0x2, 0x381, 0x382, 0x7, 0x19, 0x2, 0x2, 0x382, 0x384, 0x5, 0x6e,
            0x38, 0x2, 0x383, 0x381, 0x3, 0x2, 0x2, 0x2, 0x384, 0x387, 0x3, 0x2,
            0x2, 0x2, 0x385, 0x383, 0x3, 0x2, 0x2, 0x2, 0x385, 0x386, 0x3, 0x2,
            0x2, 0x2, 0x386, 0x6d, 0x3, 0x2, 0x2, 0x2, 0x387, 0x385, 0x3, 0x2, 0x2,
            0x2, 0x388, 0x3c0, 0x7, 0x42, 0x2, 0x2, 0x389, 0x3c0, 0x7, 0x43, 0x2,
            0x2, 0x38a, 0x38b, 0x7, 0x43, 0x2, 0x2, 0x38b, 0x38c, 0x7, 0x37, 0x2,
            0x2, 0x38c, 0x38d, 0x5, 0x4c, 0x27, 0x2, 0x38d, 0x38e, 0x7, 0x44, 0x2,
            0x2, 0x38e, 0x38f, 0x5, 0x4c, 0x27, 0x2, 0x38f, 0x390, 0x7, 0x38, 0x2,
            0x2, 0x390, 0x3c0, 0x3, 0x2, 0x2, 0x2, 0x391, 0x3c0, 0x7, 0x45, 0x2,
            0x2, 0x392, 0x3c0, 0x7, 0x46, 0x2, 0x2, 0x393, 0x394, 0x7, 0x47, 0x2,
            0x2, 0x394, 0x3c0, 0x5, 0x6e, 0x38, 0x2, 0x395, 0x396, 0x7, 0x47, 0x2,
            0x2, 0x396, 0x397, 0x7, 0x37, 0x2, 0x2, 0x397, 0x398, 0x5, 0x4c, 0x27,
            0x2, 0x398, 0x399, 0x7, 0x38, 0x2, 0x2, 0x399, 0x39a, 0x5, 0x6e, 0x38,
            0x2, 0x39a, 0x3c0, 0x3, 0x2, 0x2, 0x2, 0x39b, 0x39c, 0x7, 0x47, 0x2,
            0x2, 0x39c, 0x39d, 0x7, 0x37, 0x2, 0x2, 0x39d, 0x39e, 0x5, 0x4c, 0x27,
            0x2, 0x39e, 0x39f, 0x7, 0x44, 0x2, 0x2, 0x39f, 0x3a0, 0x5, 0x4c, 0x27,
            0x2, 0x3a0, 0x3a1, 0x7, 0x38, 0x2, 0x2, 0x3a1, 0x3a2, 0x5, 0x6e, 0x38,
            0x2, 0x3a2, 0x3c0, 0x3, 0x2, 0x2, 0x2, 0x3a3, 0x3a4, 0x7, 0x48, 0x2,
            0x2, 0x3a4, 0x3c0, 0x5, 0x6e, 0x38, 0x2, 0x3a5, 0x3a6, 0x7, 0x49, 0x2,
            0x2, 0x3a6, 0x3a7, 0x7, 0x1d, 0x2, 0x2, 0x3a7, 0x3a8, 0x5, 0x6e, 0x38,
            0x2, 0x3a8, 0x3a9, 0x7, 0x7, 0x2, 0x2, 0x3a9, 0x3aa, 0x5, 0x6e, 0x38,
            0x2, 0x3aa, 0x3ab, 0x7, 0x1e, 0x2, 0x2, 0x3ab, 0x3c0, 0x3, 0x2, 0x2,
            0x2, 0x3ac, 0x3ad, 0x7, 0x4a, 0x2, 0x2, 0x3ad, 0x3ae, 0x7, 0x1d, 0x2,
            0x2, 0x3ae, 0x3af, 0x5, 0x70, 0x39, 0x2, 0x3af, 0x3b0, 0x7, 0x1e, 0x2,
            0x2, 0x3b0, 0x3c0, 0x3, 0x2, 0x2, 0x2, 0x3b1, 0x3b2, 0x7, 0x6, 0x2,
            0x2, 0x3b2, 0x3b3, 0x5, 0x6e, 0x38, 0x2, 0x3b3, 0x3b4, 0x7, 0x1d, 0x2,
            0x2, 0x3b4, 0x3b5, 0x7, 0x1e, 0x2, 0x2, 0x3b5, 0x3c0, 0x3, 0x2, 0x2,
            0x2, 0x3b6, 0x3b7, 0x7, 0x6, 0x2, 0x2, 0x3b7, 0x3b8, 0x5, 0x6e, 0x38,
            0x2, 0x3b8, 0x3b9, 0x7, 0x1d, 0x2, 0x2, 0x3b9, 0x3ba, 0x5, 0x6c, 0x37,
            0x2, 0x3ba, 0x3bb, 0x7, 0x1e, 0x2, 0x2, 0x3bb, 0x3c0, 0x3, 0x2, 0x2,
            0x2, 0x3bc, 0x3bd, 0x7, 0x4b, 0x2, 0x2, 0x3bd, 0x3c0, 0x5, 0x6e, 0x38,
            0x2, 0x3be, 0x3c0, 0x5, 0x78, 0x3d, 0x2, 0x3bf, 0x388, 0x3, 0x2, 0x2,
            0x2, 0x3bf, 0x389, 0x3, 0x2, 0x2, 0x2, 0x3bf, 0x38a, 0x3, 0x2, 0x2,
            0x2, 0x3bf, 0x391, 0x3, 0x2, 0x2, 0x2, 0x3bf, 0x392, 0x3, 0x2, 0x2,
            0x2, 0x3bf, 0x393, 0x3, 0x2, 0x2, 0x2, 0x3bf, 0x395, 0x3, 0x2, 0x2,
            0x2, 0x3bf, 0x39b, 0x3, 0x2, 0x2, 0x2, 0x3bf, 0x3a3, 0x3, 0x2, 0x2,
            0x2, 0x3bf, 0x3a5, 0x3, 0x2, 0x2, 0x2, 0x3bf, 0x3ac, 0x3, 0x2, 0x2,
            0x2, 0x3bf, 0x3b1, 0x3, 0x2, 0x2, 0x2, 0x3bf, 0x3b6, 0x3, 0x2, 0x2,
            0x2, 0x3bf, 0x3bc, 0x3, 0x2, 0x2, 0x2, 0x3bf, 0x3be, 0x3, 0x2, 0x2,
            0x2, 0x3c0, 0x6f, 0x3, 0x2, 0x2, 0x2, 0x3c1, 0x3c6, 0x5, 0x72, 0x3a,
            0x2, 0x3c2, 0x3c3, 0x7, 0x19, 0x2, 0x2, 0x3c3, 0x3c5, 0x5, 0x72, 0x3a,
            0x2, 0x3c4, 0x3c2, 0x3, 0x2, 0x2, 0x2, 0x3c5, 0x3c8, 0x3, 0x2, 0x2,
            0x2, 0x3c6, 0x3c4, 0x3, 0x2, 0x2, 0x2, 0x3c6, 0x3c7, 0x3, 0x2, 0x2,
            0x2, 0x3c7, 0x71, 0x3, 0x2, 0x2, 0x2, 0x3c8, 0x3c6, 0x3, 0x2, 0x2, 0x2,
            0x3c9, 0x3ca, 0x5, 0x6e, 0x38, 0x2, 0x3ca, 0x3cb, 0x5, 0x7e, 0x40, 0x2,
            0x3cb, 0x73, 0x3, 0x2, 0x2, 0x2, 0x3cc, 0x3cd, 0x7, 0x1b, 0x2, 0x2,
            0x3cd, 0x3ce, 0x5, 0x76, 0x3c, 0x2, 0x3ce, 0x3cf, 0x7, 0x1c, 0x2, 0x2,
            0x3cf, 0x75, 0x3, 0x2, 0x2, 0x2, 0x3d0, 0x3d5, 0x5, 0x78, 0x3d, 0x2,
            0x3d1, 0x3d2, 0x7, 0x19, 0x2, 0x2, 0x3d2, 0x3d4, 0x5, 0x78, 0x3d, 0x2,
            0x3d3, 0x3d1, 0x3, 0x2, 0x2, 0x2, 0x3d4, 0x3d7, 0x3, 0x2, 0x2, 0x2,
            0x3d5, 0x3d3, 0x3, 0x2, 0x2, 0x2, 0x3d5, 0x3d6, 0x3, 0x2, 0x2, 0x2,
            0x3d6, 0x77, 0x3, 0x2, 0x2, 0x2, 0x3d7, 0x3d5, 0x3, 0x2, 0x2, 0x2, 0x3d8,
            0x3dd, 0x5, 0x7e, 0x40, 0x2, 0x3d9, 0x3dd, 0x7, 0x92, 0x2, 0x2, 0x3da,
            0x3dd, 0x7, 0x93, 0x2, 0x2, 0x3db, 0x3dd, 0x7, 0x94, 0x2, 0x2, 0x3dc,
            0x3d8, 0x3, 0x2, 0x2, 0x2, 0x3dc, 0x3d9, 0x3, 0x2, 0x2, 0x2, 0x3dc,
            0x3da, 0x3, 0x2, 0x2, 0x2, 0x3dc, 0x3db, 0x3, 0x2, 0x2, 0x2, 0x3dd,
            0x79, 0x3, 0x2, 0x2, 0x2, 0x3de, 0x3e0, 0x5, 0x7c, 0x3f, 0x2, 0x3df,
            0x3de, 0x3, 0x2, 0x2, 0x2, 0x3df, 0x3e0, 0x3, 0x2, 0x2, 0x2, 0x3e0,
            0x7b, 0x3, 0x2, 0x2, 0x2, 0x3e1, 0x3e2, 0x9, 0x3, 0x2, 0x2, 0x3e2, 0x7d,
            0x3, 0x2, 0x2, 0x2, 0x3e3, 0x3e4, 0x7, 0x91, 0x2, 0x2, 0x3e4, 0x7f,
            0x3, 0x2, 0x2, 0x2, 0x3e5, 0x3e6, 0x7, 0x90, 0x2, 0x2, 0x3e6, 0x81,
            0x3, 0x2, 0x2, 0x2, 0x3e7, 0x3e8, 0x9, 0x4, 0x2, 0x2, 0x3e8, 0x83, 0x3,
            0x2, 0x2, 0x2, 0x3e9, 0x3eb, 0x5, 0x86, 0x44, 0x2, 0x3ea, 0x3e9, 0x3,
            0x2, 0x2, 0x2, 0x3eb, 0x3ec, 0x3, 0x2, 0x2, 0x2, 0x3ec, 0x3ea, 0x3,
            0x2, 0x2, 0x2, 0x3ec, 0x3ed, 0x3, 0x2, 0x2, 0x2, 0x3ed, 0x85, 0x3, 0x2,
            0x2, 0x2, 0x3ee, 0x3ef, 0x7, 0x27, 0x2, 0x2, 0x3ef, 0x3fd, 0x7, 0x4,
            0x2, 0x2, 0x3f0, 0x3f1, 0x7, 0x27, 0x2, 0x2, 0x3f1, 0x3f2, 0x5, 0x7e,
            0x40, 0x2, 0x3f2, 0x3f3, 0x7, 0x4, 0x2, 0x2, 0x3f3, 0x3fd, 0x3, 0x2,
            0x2, 0x2, 0x3f4, 0x3f5, 0x7, 0x27, 0x2, 0x2, 0x3f5, 0x3f6, 0x7, 0x7,
            0x2, 0x2, 0x3f6, 0x3fd, 0x5, 0x88, 0x45, 0x2, 0x3f7, 0x3f8, 0x7, 0x27,
            0x2, 0x2, 0x3f8, 0x3f9, 0x5, 0x7e, 0x40, 0x2, 0x3f9, 0x3fa, 0x7, 0x7,
            0x2, 0x2, 0x3fa, 0x3fb, 0x5, 0x88, 0x45, 0x2, 0x3fb, 0x3fd, 0x3, 0x2,
            0x2, 0x2, 0x3fc, 0x3ee, 0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3f0, 0x3, 0x2,
            0x2, 0x2, 0x3fc, 0x3f4, 0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3f7, 0x3, 0x2,
            0x2, 0x2, 0x3fd, 0x87, 0x3, 0x2, 0x2, 0x2, 0x3fe, 0x400, 0x5, 0x8a,
            0x46, 0x2, 0x3ff, 0x3fe, 0x3, 0x2, 0x2, 0x2, 0x400, 0x401, 0x3, 0x2,
            0x2, 0x2, 0x401, 0x3ff, 0x3, 0x2, 0x2, 0x2, 0x401, 0x402, 0x3, 0x2,
            0x2, 0x2, 0x402, 0x89, 0x3, 0x2, 0x2, 0x2, 0x403, 0x404, 0x7, 0x17,
            0x2, 0x2, 0x404, 0x421, 0x7, 0x4, 0x2, 0x2, 0x405, 0x406, 0x7, 0x17,
            0x2, 0x2, 0x406, 0x407, 0x5, 0x48, 0x25, 0x2, 0x407, 0x408, 0x7, 0x4,
            0x2, 0x2, 0x408, 0x421, 0x3, 0x2, 0x2, 0x2, 0x409, 0x421, 0x5, 0x98,
            0x4d, 0x2, 0x40a, 0x40b, 0x7, 0x16, 0x2, 0x2, 0x40b, 0x40c, 0x5, 0x4e,
            0x28, 0x2, 0x40c, 0x40d, 0x7, 0x4, 0x2, 0x2, 0x40d, 0x421, 0x3, 0x2,
            0x2, 0x2, 0x40e, 0x40f, 0x7, 0x18, 0x2, 0x2, 0x40f, 0x421, 0x7, 0x4,
            0x2, 0x2, 0x410, 0x411, 0x7, 0x18, 0x2, 0x2, 0x411, 0x412, 0x5, 0x48,
            0x25, 0x2, 0x412, 0x413, 0x7, 0x4, 0x2, 0x2, 0x413, 0x421, 0x3, 0x2,
            0x2, 0x2, 0x414, 0x415, 0x7, 0x6f, 0x2, 0x2, 0x415, 0x421, 0x7, 0x4,
            0x2, 0x2, 0x416, 0x417, 0x7, 0x70, 0x2, 0x2, 0x417, 0x418, 0x5, 0x8c,
            0x47, 0x2, 0x418, 0x419, 0x7, 0x71, 0x2, 0x2, 0x419, 0x41a, 0x5, 0x7e,
            0x40, 0x2, 0x41a, 0x41b, 0x7, 0x4, 0x2, 0x2, 0x41b, 0x421, 0x3, 0x2,
            0x2, 0x2, 0x41c, 0x41d, 0x7, 0x70, 0x2, 0x2, 0x41d, 0x41e, 0x5, 0x8c,
            0x47, 0x2, 0x41e, 0x41f, 0x7, 0x4, 0x2, 0x2, 0x41f, 0x421, 0x3, 0x2,
            0x2, 0x2, 0x420, 0x403, 0x3, 0x2, 0x2, 0x2, 0x420, 0x405, 0x3, 0x2,
            0x2, 0x2, 0x420, 0x409, 0x3, 0x2, 0x2, 0x2, 0x420, 0x40a, 0x3, 0x2,
            0x2, 0x2, 0x420, 0x40e, 0x3, 0x2, 0x2, 0x2, 0x420, 0x410, 0x3, 0x2,
            0x2, 0x2, 0x420, 0x414, 0x3, 0x2, 0x2, 0x2, 0x420, 0x416, 0x3, 0x2,
            0x2, 0x2, 0x420, 0x41c, 0x3, 0x2, 0x2, 0x2, 0x421, 0x8b, 0x3, 0x2, 0x2,
            0x2, 0x422, 0x423, 0x5, 0x94, 0x4b, 0x2, 0x423, 0x424, 0x5, 0x8e, 0x48,
            0x2, 0x424, 0x425, 0x5, 0x90, 0x49, 0x2, 0x425, 0x426, 0x5, 0x92, 0x4a,
            0x2, 0x426, 0x431, 0x3, 0x2, 0x2, 0x2, 0x427, 0x428, 0x7, 0x72, 0x2,
            0x2, 0x428, 0x429, 0x5, 0x48, 0x25, 0x2, 0x429, 0x42a, 0x5, 0x90, 0x49,
            0x2, 0x42a, 0x42b, 0x5, 0x92, 0x4a, 0x2, 0x42b, 0x431, 0x3, 0x2, 0x2,
            0x2, 0x42c, 0x42d, 0x7, 0x73, 0x2, 0x2, 0x42d, 0x431, 0x5, 0x92, 0x4a,
            0x2, 0x42e, 0x42f, 0x7, 0x74, 0x2, 0x2, 0x42f, 0x431, 0x5, 0x9e, 0x50,
            0x2, 0x430, 0x422, 0x3, 0x2, 0x2, 0x2, 0x430, 0x427, 0x3, 0x2, 0x2,
            0x2, 0x430, 0x42c, 0x3, 0x2, 0x2, 0x2, 0x430, 0x42e, 0x3, 0x2, 0x2,
            0x2, 0x431, 0x8d, 0x3, 0x2, 0x2, 0x2, 0x432, 0x433, 0x7, 0x72, 0x2,
            0x2, 0x433, 0x435, 0x5, 0x48, 0x25, 0x2, 0x434, 0x432, 0x3, 0x2, 0x2,
            0x2, 0x434, 0x435, 0x3, 0x2, 0x2, 0x2, 0x435, 0x8f, 0x3, 0x2, 0x2, 0x2,
            0x436, 0x438, 0x7, 0x73, 0x2, 0x2, 0x437, 0x436, 0x3, 0x2, 0x2, 0x2,
            0x437, 0x438, 0x3, 0x2, 0x2, 0x2, 0x438, 0x91, 0x3, 0x2, 0x2, 0x2, 0x439,
            0x43a, 0x7, 0x74, 0x2, 0x2, 0x43a, 0x43c, 0x5, 0x9e, 0x50, 0x2, 0x43b,
            0x439, 0x3, 0x2, 0x2, 0x2, 0x43b, 0x43c, 0x3, 0x2, 0x2, 0x2, 0x43c,
            0x93, 0x3, 0x2, 0x2, 0x2, 0x43d, 0x442, 0x5, 0x96, 0x4c, 0x2, 0x43e,
            0x43f, 0x7, 0x19, 0x2, 0x2, 0x43f, 0x441, 0x5, 0x96, 0x4c, 0x2, 0x440,
            0x43e, 0x3, 0x2, 0x2, 0x2, 0x441, 0x444, 0x3, 0x2, 0x2, 0x2, 0x442,
            0x440, 0x3, 0x2, 0x2, 0x2, 0x442, 0x443, 0x3, 0x2, 0x2, 0x2, 0x443,
            0x95, 0x3, 0x2, 0x2, 0x2, 0x444, 0x442, 0x3, 0x2, 0x2, 0x2, 0x445, 0x452,
            0x7, 0x75, 0x2, 0x2, 0x446, 0x452, 0x5, 0x78, 0x3d, 0x2, 0x447, 0x448,
            0x5, 0x78, 0x3d, 0x2, 0x448, 0x449, 0x7, 0x76, 0x2, 0x2, 0x449, 0x452,
            0x3, 0x2, 0x2, 0x2, 0x44a, 0x44b, 0x5, 0x78, 0x3d, 0x2, 0x44b, 0x44c,
            0x7, 0x76, 0x2, 0x2, 0x44c, 0x44d, 0x5, 0x4c, 0x27, 0x2, 0x44d, 0x452,
            0x3, 0x2, 0x2, 0x2, 0x44e, 0x44f, 0x5, 0x78, 0x3d, 0x2, 0x44f, 0x450,
            0x7, 0x3f, 0x2, 0x2, 0x450, 0x452, 0x3, 0x2, 0x2, 0x2, 0x451, 0x445,
            0x3, 0x2, 0x2, 0x2, 0x451, 0x446, 0x3, 0x2, 0x2, 0x2, 0x451, 0x447,
            0x3, 0x2, 0x2, 0x2, 0x451, 0x44a, 0x3, 0x2, 0x2, 0x2, 0x451, 0x44e,
            0x3, 0x2, 0x2, 0x2, 0x452, 0x97, 0x3, 0x2, 0x2, 0x2, 0x453, 0x454, 0x5,
            0x7a, 0x3e, 0x2, 0x454, 0x455, 0x7, 0x77, 0x2, 0x2, 0x455, 0x456, 0x5,
            0x9a, 0x4e, 0x2, 0x456, 0x457, 0x7, 0x4, 0x2, 0x2, 0x457, 0x45d, 0x3,
            0x2, 0x2, 0x2, 0x458, 0x459, 0x5, 0x7c, 0x3f, 0x2, 0x459, 0x45a, 0x5,
            0x9a, 0x4e, 0x2, 0x45a, 0x45b, 0x7, 0x4, 0x2, 0x2, 0x45b, 0x45d, 0x3,
            0x2, 0x2, 0x2, 0x45c, 0x453, 0x3, 0x2, 0x2, 0x2, 0x45c, 0x458, 0x3,
            0x2, 0x2, 0x2, 0x45d, 0x99, 0x3, 0x2, 0x2, 0x2, 0x45e, 0x463, 0x5, 0x9c,
            0x4f, 0x2, 0x45f, 0x460, 0x7, 0x19, 0x2, 0x2, 0x460, 0x462, 0x5, 0x9c,
            0x4f, 0x2, 0x461, 0x45f, 0x3, 0x2, 0x2, 0x2, 0x462, 0x465, 0x3, 0x2,
            0x2, 0x2, 0x463, 0x461, 0x3, 0x2, 0x2, 0x2, 0x463, 0x464, 0x3, 0x2,
            0x2, 0x2, 0x464, 0x9b, 0x3, 0x2, 0x2, 0x2, 0x465, 0x463, 0x3, 0x2, 0x2,
            0x2, 0x466, 0x478, 0x5, 0x4c, 0x27, 0x2, 0x467, 0x468, 0x5, 0x78, 0x3d,
            0x2, 0x468, 0x469, 0x7, 0x78, 0x2, 0x2, 0x469, 0x46a, 0x5, 0x4c, 0x27,
            0x2, 0x46a, 0x478, 0x3, 0x2, 0x2, 0x2, 0x46b, 0x46c, 0x5, 0x62, 0x32,
            0x2, 0x46c, 0x46d, 0x7, 0x78, 0x2, 0x2, 0x46d, 0x46e, 0x5, 0x4c, 0x27,
            0x2, 0x46e, 0x478, 0x3, 0x2, 0x2, 0x2, 0x46f, 0x470, 0x5, 0x4c, 0x27,
            0x2, 0x470, 0x471, 0x7, 0x79, 0x2, 0x2, 0x471, 0x472, 0x5, 0x78, 0x3d,
            0x2, 0x472, 0x478, 0x3, 0x2, 0x2, 0x2, 0x473, 0x474, 0x5, 0x4c, 0x27,
            0x2, 0x474, 0x475, 0x7, 0x79, 0x2, 0x2, 0x475, 0x476, 0x5, 0x74, 0x3b,
            0x2, 0x476, 0x478, 0x3, 0x2, 0x2, 0x2, 0x477, 0x466, 0x3, 0x2, 0x2,
            0x2, 0x477, 0x467, 0x3, 0x2, 0x2, 0x2, 0x477, 0x46b, 0x3, 0x2, 0x2,
            0x2, 0x477, 0x46f, 0x3, 0x2, 0x2, 0x2, 0x477, 0x473, 0x3, 0x2, 0x2,
            0x2, 0x478, 0x9d, 0x3, 0x2, 0x2, 0x2, 0x479, 0x47e, 0x5, 0xa0, 0x51,
            0x2, 0x47a, 0x47b, 0x7, 0x19, 0x2, 0x2, 0x47b, 0x47d, 0x5, 0xa0, 0x51,
            0x2, 0x47c, 0x47a, 0x3, 0x2, 0x2, 0x2, 0x47d, 0x480, 0x3, 0x2, 0x2,
            0x2, 0x47e, 0x47c, 0x3, 0x2, 0x2, 0x2, 0x47e, 0x47f, 0x3, 0x2, 0x2,
            0x2, 0x47f, 0x9f, 0x3, 0x2, 0x2, 0x2, 0x480, 0x47e, 0x3, 0x2, 0x2, 0x2,
            0x481, 0x482, 0x5, 0xa8, 0x55, 0x2, 0x482, 0x483, 0x7, 0x1f, 0x2, 0x2,
            0x483, 0x484, 0x5, 0x4c, 0x27, 0x2, 0x484, 0x48e, 0x3, 0x2, 0x2, 0x2,
            0x485, 0x486, 0x7, 0x20, 0x2, 0x2, 0x486, 0x487, 0x5, 0x48, 0x25, 0x2,
            0x487, 0x488, 0x7, 0x7, 0x2, 0x2, 0x488, 0x489, 0x5, 0x9e, 0x50, 0x2,
            0x489, 0x48a, 0x5, 0xa2, 0x52, 0x2, 0x48a, 0x48b, 0x5, 0xa4, 0x53, 0x2,
            0x48b, 0x48c, 0x7, 0xa, 0x2, 0x2, 0x48c, 0x48e, 0x3, 0x2, 0x2, 0x2,
            0x48d, 0x481, 0x3, 0x2, 0x2, 0x2, 0x48d, 0x485, 0x3, 0x2, 0x2, 0x2,
            0x48e, 0xa1, 0x3, 0x2, 0x2, 0x2, 0x48f, 0x490, 0x7, 0x25, 0x2, 0x2,
            0x490, 0x491, 0x5, 0x48, 0x25, 0x2, 0x491, 0x492, 0x7, 0x7, 0x2, 0x2,
            0x492, 0x493, 0x5, 0x9e, 0x50, 0x2, 0x493, 0x495, 0x3, 0x2, 0x2, 0x2,
            0x494, 0x48f, 0x3, 0x2, 0x2, 0x2, 0x495, 0x498, 0x3, 0x2, 0x2, 0x2,
            0x496, 0x494, 0x3, 0x2, 0x2, 0x2, 0x496, 0x497, 0x3, 0x2, 0x2, 0x2,
            0x497, 0xa3, 0x3, 0x2, 0x2, 0x2, 0x498, 0x496, 0x3, 0x2, 0x2, 0x2, 0x499,
            0x49a, 0x7, 0x26, 0x2, 0x2, 0x49a, 0x49c, 0x5, 0xa0, 0x51, 0x2, 0x49b,
            0x499, 0x3, 0x2, 0x2, 0x2, 0x49b, 0x49c, 0x3, 0x2, 0x2, 0x2, 0x49c,
            0xa5, 0x3, 0x2, 0x2, 0x2, 0x49d, 0x4a2, 0x5, 0xa8, 0x55, 0x2, 0x49e,
            0x49f, 0x7, 0x19, 0x2, 0x2, 0x49f, 0x4a1, 0x5, 0xa8, 0x55, 0x2, 0x4a0,
            0x49e, 0x3, 0x2, 0x2, 0x2, 0x4a1, 0x4a4, 0x3, 0x2, 0x2, 0x2, 0x4a2,
            0x4a0, 0x3, 0x2, 0x2, 0x2, 0x4a2, 0x4a3, 0x3, 0x2, 0x2, 0x2, 0x4a3,
            0xa7, 0x3, 0x2, 0x2, 0x2, 0x4a4, 0x4a2, 0x3, 0x2, 0x2, 0x2, 0x4a5, 0x4b0,
            0x5, 0x7e, 0x40, 0x2, 0x4a6, 0x4a7, 0x5, 0x7e, 0x40, 0x2, 0x4a7, 0x4a8,
            0x5, 0xaa, 0x56, 0x2, 0x4a8, 0x4b0, 0x3, 0x2, 0x2, 0x2, 0x4a9, 0x4aa,
            0x7, 0x1d, 0x2, 0x2, 0x4aa, 0x4ab, 0x5, 0xa8, 0x55, 0x2, 0x4ab, 0x4ac,
            0x7, 0x19, 0x2, 0x2, 0x4ac, 0x4ad, 0x5, 0xa8, 0x55, 0x2, 0x4ad, 0x4ae,
            0x7, 0x1e, 0x2, 0x2, 0x4ae, 0x4b0, 0x3, 0x2, 0x2, 0x2, 0x4af, 0x4a5,
            0x3, 0x2, 0x2, 0x2, 0x4af, 0x4a6, 0x3, 0x2, 0x2, 0x2, 0x4af, 0x4a9,
            0x3, 0x2, 0x2, 0x2, 0x4b0, 0xa9, 0x3, 0x2, 0x2, 0x2, 0x4b1, 0x4b3, 0x5,
            0xac, 0x57, 0x2, 0x4b2, 0x4b1, 0x3, 0x2, 0x2, 0x2, 0x4b3, 0x4b6, 0x3,
            0x2, 0x2, 0x2, 0x4b4, 0x4b2, 0x3, 0x2, 0x2, 0x2, 0x4b4, 0x4b5, 0x3,
            0x2, 0x2, 0x2, 0x4b5, 0xab, 0x3, 0x2, 0x2, 0x2, 0x4b6, 0x4b4, 0x3, 0x2,
            0x2, 0x2, 0x4b7, 0x4b8, 0x7, 0x37, 0x2, 0x2, 0x4b8, 0x4b9, 0x5, 0x4c,
            0x27, 0x2, 0x4b9, 0x4ba, 0x7, 0x38, 0x2, 0x2, 0x4ba, 0xad, 0x3, 0x2,
            0x2, 0x2, 0x4bb, 0x4bd, 0x5, 0xb0, 0x59, 0x2, 0x4bc, 0x4bb, 0x3, 0x2,
            0x2, 0x2, 0x4bd, 0x4c0, 0x3, 0x2, 0x2, 0x2, 0x4be, 0x4bc, 0x3, 0x2,
            0x2, 0x2, 0x4be, 0x4bf, 0x3, 0x2, 0x2, 0x2, 0x4bf, 0xaf, 0x3, 0x2, 0x2,
            0x2, 0x4c0, 0x4be, 0x3, 0x2, 0x2, 0x2, 0x4c1, 0x4c9, 0x5, 0xb2, 0x5a,
            0x2, 0x4c2, 0x4c9, 0x5, 0xb6, 0x5c, 0x2, 0x4c3, 0x4c9, 0x5, 0xbc, 0x5f,
            0x2, 0x4c4, 0x4c9, 0x5, 0xbe, 0x60, 0x2, 0x4c5, 0x4c9, 0x5, 0xc2, 0x62,
            0x2, 0x4c6, 0x4c9, 0x5, 0xca, 0x66, 0x2, 0x4c7, 0x4c9, 0x5, 0xcc, 0x67,
            0x2, 0x4c8, 0x4c1, 0x3, 0x2, 0x2, 0x2, 0x4c8, 0x4c2, 0x3, 0x2, 0x2,
            0x2, 0x4c8, 0x4c3, 0x3, 0x2, 0x2, 0x2, 0x4c8, 0x4c4, 0x3, 0x2, 0x2,
            0x2, 0x4c8, 0x4c5, 0x3, 0x2, 0x2, 0x2, 0x4c8, 0x4c6, 0x3, 0x2, 0x2,
            0x2, 0x4c8, 0x4c7, 0x3, 0x2, 0x2, 0x2, 0x4c9, 0xb1, 0x3, 0x2, 0x2, 0x2,
            0x4ca, 0x4cb, 0x7, 0x7a, 0x2, 0x2, 0x4cb, 0x4cc, 0x5, 0x80, 0x41, 0x2,
            0x4cc, 0x4cd, 0x7, 0x4, 0x2, 0x2, 0x4cd, 0xb3, 0x3, 0x2, 0x2, 0x2, 0x4ce,
            0x4cf, 0x7, 0x7b, 0x2, 0x2, 0x4cf, 0x4d1, 0x5, 0x80, 0x41, 0x2, 0x4d0,
            0x4ce, 0x3, 0x2, 0x2, 0x2, 0x4d0, 0x4d1, 0x3, 0x2, 0x2, 0x2, 0x4d1,
            0xb5, 0x3, 0x2, 0x2, 0x2, 0x4d2, 0x4d3, 0x7, 0x7c, 0x2, 0x2, 0x4d3,
            0x4d4, 0x7, 0x7d, 0x2, 0x2, 0x4d4, 0x4d5, 0x5, 0x4c, 0x27, 0x2, 0x4d5,
            0x4d6, 0x5, 0xb8, 0x5d, 0x2, 0x4d6, 0x4d7, 0x5, 0xba, 0x5e, 0x2, 0x4d7,
            0x4d8, 0x5, 0xb4, 0x5b, 0x2, 0x4d8, 0x4d9, 0x7, 0x4, 0x2, 0x2, 0x4d9,
            0xb7, 0x3, 0x2, 0x2, 0x2, 0x4da, 0x4db, 0x7, 0x7e, 0x2, 0x2, 0x4db,
            0x4dd, 0x5, 0x4c, 0x27, 0x2, 0x4dc, 0x4da, 0x3, 0x2, 0x2, 0x2, 0x4dc,
            0x4dd, 0x3, 0x2, 0x2, 0x2, 0x4dd, 0xb9, 0x3, 0x2, 0x2, 0x2, 0x4de, 0x4df,
            0x7, 0x7f, 0x2, 0x2, 0x4df, 0x4e1, 0x5, 0x4c, 0x27, 0x2, 0x4e0, 0x4de,
            0x3, 0x2, 0x2, 0x2, 0x4e0, 0x4e1, 0x3, 0x2, 0x2, 0x2, 0x4e1, 0xbb, 0x3,
            0x2, 0x2, 0x2, 0x4e2, 0x4e3, 0x7, 0x80, 0x2, 0x2, 0x4e3, 0x4e4, 0x7,
            0x7d, 0x2, 0x2, 0x4e4, 0x4e5, 0x5, 0x4c, 0x27, 0x2, 0x4e5, 0x4e6, 0x7,
            0x81, 0x2, 0x2, 0x4e6, 0x4e7, 0x5, 0x4c, 0x27, 0x2, 0x4e7, 0x4e8, 0x7,
            0x19, 0x2, 0x2, 0x4e8, 0x4e9, 0x5, 0x4c, 0x27, 0x2, 0x4e9, 0x4ea, 0x7,
            0x4, 0x2, 0x2, 0x4ea, 0x4f7, 0x3, 0x2, 0x2, 0x2, 0x4eb, 0x4ec, 0x7,
            0x80, 0x2, 0x2, 0x4ec, 0x4ed, 0x7, 0x7d, 0x2, 0x2, 0x4ed, 0x4ee, 0x5,
            0x4c, 0x27, 0x2, 0x4ee, 0x4ef, 0x7, 0x81, 0x2, 0x2, 0x4ef, 0x4f0, 0x5,
            0x4c, 0x27, 0x2, 0x4f0, 0x4f1, 0x7, 0x19, 0x2, 0x2, 0x4f1, 0x4f2, 0x5,
            0x4c, 0x27, 0x2, 0x4f2, 0x4f3, 0x7, 0x7, 0x2, 0x2, 0x4f3, 0x4f4, 0x5,
            0xb2, 0x5a, 0x2, 0x4f4, 0x4f5, 0x7, 0xa, 0x2, 0x2, 0x4f5, 0x4f7, 0x3,
            0x2, 0x2, 0x2, 0x4f6, 0x4e2, 0x3, 0x2, 0x2, 0x2, 0x4f6, 0x4eb, 0x3,
            0x2, 0x2, 0x2, 0x4f7, 0xbd, 0x3, 0x2, 0x2, 0x2, 0x4f8, 0x4f9, 0x7, 0x82,
            0x2, 0x2, 0x4f9, 0x4fa, 0x7, 0x7d, 0x2, 0x2, 0x4fa, 0x4fb, 0x5, 0x4c,
            0x27, 0x2, 0x4fb, 0x4fc, 0x5, 0xc0, 0x61, 0x2, 0x4fc, 0x4fd, 0x7, 0x83,
            0x2, 0x2, 0x4fd, 0x4fe, 0x5, 0x4c, 0x27, 0x2, 0x4fe, 0x4ff, 0x5, 0xb4,
            0x5b, 0x2, 0x4ff, 0x500, 0x7, 0x4, 0x2, 0x2, 0x500, 0xbf, 0x3, 0x2,
            0x2, 0x2, 0x501, 0x502, 0x7, 0x84, 0x2, 0x2, 0x502, 0x505, 0x5, 0x80,
            0x41, 0x2, 0x503, 0x505, 0x7, 0x85, 0x2, 0x2, 0x504, 0x501, 0x3, 0x2,
            0x2, 0x2, 0x504, 0x503, 0x3, 0x2, 0x2, 0x2, 0x505, 0xc1, 0x3, 0x2, 0x2,
            0x2, 0x506, 0x507, 0x7, 0x86, 0x2, 0x2, 0x507, 0x508, 0x7, 0x7d, 0x2,
            0x2, 0x508, 0x509, 0x5, 0x4c, 0x27, 0x2, 0x509, 0x50a, 0x7, 0x11, 0x2,
            0x2, 0x50a, 0x50b, 0x5, 0xc4, 0x63, 0x2, 0x50b, 0x50c, 0x5, 0xb4, 0x5b,
            0x2, 0x50c, 0x50d, 0x7, 0x4, 0x2, 0x2, 0x50d, 0xc3, 0x3, 0x2, 0x2, 0x2,
            0x50e, 0x520, 0x5, 0x78, 0x3d, 0x2, 0x50f, 0x510, 0x7, 0x20, 0x2, 0x2,
            0x510, 0x511, 0x5, 0x4c, 0x27, 0x2, 0x511, 0x512, 0x7, 0x7, 0x2, 0x2,
            0x512, 0x513, 0x5, 0x78, 0x3d, 0x2, 0x513, 0x514, 0x5, 0xc6, 0x64, 0x2,
            0x514, 0x515, 0x7, 0x26, 0x2, 0x2, 0x515, 0x516, 0x5, 0x78, 0x3d, 0x2,
            0x516, 0x517, 0x7, 0xa, 0x2, 0x2, 0x517, 0x520, 0x3, 0x2, 0x2, 0x2,
            0x518, 0x519, 0x7, 0x20, 0x2, 0x2, 0x519, 0x51a, 0x5, 0x4c, 0x27, 0x2,
            0x51a, 0x51b, 0x7, 0x7, 0x2, 0x2, 0x51b, 0x51c, 0x5, 0x78, 0x3d, 0x2,
            0x51c, 0x51d, 0x5, 0xc8, 0x65, 0x2, 0x51d, 0x51e, 0x7, 0xa, 0x2, 0x2,
            0x51e, 0x520, 0x3, 0x2, 0x2, 0x2, 0x51f, 0x50e, 0x3, 0x2, 0x2, 0x2,
            0x51f, 0x50f, 0x3, 0x2, 0x2, 0x2, 0x51f, 0x518, 0x3, 0x2, 0x2, 0x2,
            0x520, 0xc5, 0x3, 0x2, 0x2, 0x2, 0x521, 0x523, 0x5, 0xc8, 0x65, 0x2,
            0x522, 0x521, 0x3, 0x2, 0x2, 0x2, 0x522, 0x523, 0x3, 0x2, 0x2, 0x2,
            0x523, 0xc7, 0x3, 0x2, 0x2, 0x2, 0x524, 0x525, 0x7, 0x25, 0x2, 0x2,
            0x525, 0x526, 0x5, 0x4c, 0x27, 0x2, 0x526, 0x527, 0x7, 0x7, 0x2, 0x2,
            0x527, 0x528, 0x5, 0x78, 0x3d, 0x2, 0x528, 0x52a, 0x3, 0x2, 0x2, 0x2,
            0x529, 0x524, 0x3, 0x2, 0x2, 0x2, 0x52a, 0x52b, 0x3, 0x2, 0x2, 0x2,
            0x52b, 0x529, 0x3, 0x2, 0x2, 0x2, 0x52b, 0x52c, 0x3, 0x2, 0x2, 0x2,
            0x52c, 0xc9, 0x3, 0x2, 0x2, 0x2, 0x52d, 0x52e, 0x7, 0x87, 0x2, 0x2,
            0x52e, 0x52f, 0x5, 0x80, 0x41, 0x2, 0x52f, 0x530, 0x7, 0x4, 0x2, 0x2,
            0x530, 0xcb, 0x3, 0x2, 0x2, 0x2, 0x531, 0x532, 0x7, 0x88, 0x2, 0x2,
            0x532, 0x533, 0x5, 0xce, 0x68, 0x2, 0x533, 0x534, 0x5, 0xd0, 0x69, 0x2,
            0x534, 0x535, 0x5, 0xd6, 0x6c, 0x2, 0x535, 0x536, 0x5, 0xd8, 0x6d, 0x2,
            0x536, 0x537, 0x7, 0x4, 0x2, 0x2, 0x537, 0xcd, 0x3, 0x2, 0x2, 0x2, 0x538,
            0x543, 0x5, 0x4c, 0x27, 0x2, 0x539, 0x53a, 0x7, 0x7e, 0x2, 0x2, 0x53a,
            0x543, 0x5, 0x4c, 0x27, 0x2, 0x53b, 0x53c, 0x7, 0x7f, 0x2, 0x2, 0x53c,
            0x543, 0x5, 0x4c, 0x27, 0x2, 0x53d, 0x53e, 0x7, 0x7e, 0x2, 0x2, 0x53e,
            0x53f, 0x5, 0x4c, 0x27, 0x2, 0x53f, 0x540, 0x7, 0x7f, 0x2, 0x2, 0x540,
            0x541, 0x5, 0x4c, 0x27, 0x2, 0x541, 0x543, 0x3, 0x2, 0x2, 0x2, 0x542,
            0x538, 0x3, 0x2, 0x2, 0x2, 0x542, 0x539, 0x3, 0x2, 0x2, 0x2, 0x542,
            0x53b, 0x3, 0x2, 0x2, 0x2, 0x542, 0x53d, 0x3, 0x2, 0x2, 0x2, 0x543,
            0xcf, 0x3, 0x2, 0x2, 0x2, 0x544, 0x545, 0x7, 0x89, 0x2, 0x2, 0x545,
            0x547, 0x5, 0xd2, 0x6a, 0x2, 0x546, 0x544, 0x3, 0x2, 0x2, 0x2, 0x546,
            0x547, 0x3, 0x2, 0x2, 0x2, 0x547, 0xd1, 0x3, 0x2, 0x2, 0x2, 0x548, 0x54d,
            0x5, 0xd4, 0x6b, 0x2, 0x549, 0x54a, 0x7, 0x19, 0x2, 0x2, 0x54a, 0x54c,
            0x5, 0xd4, 0x6b, 0x2, 0x54b, 0x549, 0x3, 0x2, 0x2, 0x2, 0x54c, 0x54f,
            0x3, 0x2, 0x2, 0x2, 0x54d, 0x54b, 0x3, 0x2, 0x2, 0x2, 0x54d, 0x54e,
            0x3, 0x2, 0x2, 0x2, 0x54e, 0xd3, 0x3, 0x2, 0x2, 0x2, 0x54f, 0x54d, 0x3,
            0x2, 0x2, 0x2, 0x550, 0x556, 0x7, 0x11, 0x2, 0x2, 0x551, 0x556, 0x7,
            0x3b, 0x2, 0x2, 0x552, 0x556, 0x5, 0x78, 0x3d, 0x2, 0x553, 0x556, 0x7,
            0x17, 0x2, 0x2, 0x554, 0x556, 0x7, 0x8a, 0x2, 0x2, 0x555, 0x550, 0x3,
            0x2, 0x2, 0x2, 0x555, 0x551, 0x3, 0x2, 0x2, 0x2, 0x555, 0x552, 0x3,
            0x2, 0x2, 0x2, 0x555, 0x553, 0x3, 0x2, 0x2, 0x2, 0x555, 0x554, 0x3,
            0x2, 0x2, 0x2, 0x556, 0xd5, 0x3, 0x2, 0x2, 0x2, 0x557, 0x558, 0x7, 0x72,
            0x2, 0x2, 0x558, 0x566, 0x5, 0x4c, 0x27, 0x2, 0x559, 0x55a, 0x7, 0x72,
            0x2, 0x2, 0x55a, 0x55b, 0x7, 0x7e, 0x2, 0x2, 0x55b, 0x566, 0x5, 0x4c,
            0x27, 0x2, 0x55c, 0x55d, 0x7, 0x72, 0x2, 0x2, 0x55d, 0x55e, 0x7, 0x7f,
            0x2, 0x2, 0x55e, 0x566, 0x5, 0x4c, 0x27, 0x2, 0x55f, 0x560, 0x7, 0x72,
            0x2, 0x2, 0x560, 0x561, 0x7, 0x7e, 0x2, 0x2, 0x561, 0x562, 0x5, 0x4c,
            0x27, 0x2, 0x562, 0x563, 0x7, 0x7f, 0x2, 0x2, 0x563, 0x564, 0x5, 0x4c,
            0x27, 0x2, 0x564, 0x566, 0x3, 0x2, 0x2, 0x2, 0x565, 0x557, 0x3, 0x2,
            0x2, 0x2, 0x565, 0x559, 0x3, 0x2, 0x2, 0x2, 0x565, 0x55c, 0x3, 0x2,
            0x2, 0x2, 0x565, 0x55f, 0x3, 0x2, 0x2, 0x2, 0x565, 0x566, 0x3, 0x2,
            0x2, 0x2, 0x566, 0xd7, 0x3, 0x2, 0x2, 0x2, 0x567, 0x568, 0x7, 0x7b,
            0x2, 0x2, 0x568, 0x56a, 0x5, 0x80, 0x41, 0x2, 0x569, 0x567, 0x3, 0x2,
            0x2, 0x2, 0x569, 0x56a, 0x3, 0x2, 0x2, 0x2, 0x56a, 0xd9, 0x3, 0x2, 0x2,
            0x2, 0x60, 0xe5, 0x125, 0x12a, 0x13f, 0x17e, 0x185, 0x192, 0x1a3, 0x1b0,
            0x1b8, 0x1c0, 0x1c4, 0x1cd, 0x1d7, 0x1e1, 0x1e9, 0x1f1, 0x1f9, 0x1fd,
            0x203, 0x220, 0x229, 0x234, 0x23d, 0x245, 0x24c, 0x268, 0x26f, 0x281,
            0x288, 0x293, 0x297, 0x29a, 0x2a0, 0x2a7, 0x2ab, 0x2b6, 0x2bd, 0x2c9,
            0x2d0, 0x2d8, 0x2e0, 0x2e8, 0x2f0, 0x2fc, 0x308, 0x31a, 0x31c, 0x356,
            0x36b, 0x375, 0x37e, 0x385, 0x3bf, 0x3c6, 0x3d5, 0x3dc, 0x3df, 0x3ec,
            0x3fc, 0x401, 0x420, 0x430, 0x434, 0x437, 0x43b, 0x442, 0x451, 0x45c,
            0x463, 0x477, 0x47e, 0x48d, 0x496, 0x49b, 0x4a2, 0x4af, 0x4b4, 0x4be,
            0x4c8, 0x4d0, 0x4dc, 0x4e0, 0x4f6, 0x504, 0x51f, 0x522, 0x52b, 0x542,
            0x546, 0x54d, 0x555, 0x565, 0x569,
    };

    atn::ATNDeserializer deserializer;
    _atn = deserializer.deserialize(_serializedATN);

    size_t count = _atn.getNumberOfDecisions();
    _decisionToDFA.reserve(count);
    for (size_t i = 0; i < count; i++) {
        _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
    }
}

HybridSystemParser::Initializer HybridSystemParser::_init;
