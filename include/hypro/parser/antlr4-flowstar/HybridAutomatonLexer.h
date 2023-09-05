
/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

// Generated from HybridAutomaton.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"


namespace hypro {


    class HybridAutomatonLexer : public antlr4::Lexer {
    public:
        enum {
            T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7,
            T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14,
            T__14 = 15, T__15 = 16, T__16 = 17, T__17 = 18, T__18 = 19, T__19 = 20,
            T__20 = 21, T__21 = 22, T__22 = 23, T__23 = 24, POLY = 25, LINEAR = 26,
            NONLINEAR = 27, NONPOLY = 28, LTI = 29, ODE = 30, URGENT = 31, IN = 32,
            TRUE = 33, FALSE = 34, PAR = 35, JUMPS = 36, GUARD = 37, RESET = 38,
            PARALLELOTOPE = 39, BOX = 40, JUMP = 41, DEFINE = 42, COMMENT = 43,
            EQUALS = 44, BOOLRELATION = 45, PLUS = 46, MINUS = 47, TIMES = 48, DIVIDE = 49,
            SBOPEN = 50, SBCLOSE = 51, CBOPEN = 52, CBCLOSE = 53, RBOPEN = 54, RBCLOSE = 55,
            COMMA = 56, NUMBER = 57, CONSTANT = 58, VARIABLE = 59, WS = 60, INTERVALAGG = 61,
            EXPONENTIAL = 62
        };

        HybridAutomatonLexer(antlr4::CharStream *input);

        ~HybridAutomatonLexer();


        bool parsingConstants = false;

        virtual std::string getGrammarFileName() const override;

        virtual const std::vector<std::string> &getRuleNames() const override;

        virtual const std::vector<std::string> &getChannelNames() const override;

        virtual const std::vector<std::string> &getModeNames() const override;

        virtual const std::vector<std::string> &getTokenNames() const override; // deprecated, use vocabulary instead
        virtual antlr4::dfa::Vocabulary &getVocabulary() const override;

        virtual const std::vector<uint16_t> getSerializedATN() const override;

        virtual const antlr4::atn::ATN &getATN() const override;

        virtual void action(antlr4::RuleContext *context, size_t ruleIndex, size_t actionIndex) override;

    private:
        static std::vector<antlr4::dfa::DFA> _decisionToDFA;
        static antlr4::atn::PredictionContextCache _sharedContextCache;
        static std::vector<std::string> _ruleNames;
        static std::vector<std::string> _tokenNames;
        static std::vector<std::string> _channelNames;
        static std::vector<std::string> _modeNames;

        static std::vector<std::string> _literalNames;
        static std::vector<std::string> _symbolicNames;
        static antlr4::dfa::Vocabulary _vocabulary;
        static antlr4::atn::ATN _atn;
        static std::vector<uint16_t> _serializedATN;


        // Individual action functions triggered by action() above.
        void PARAction(antlr4::RuleContext *context, size_t actionIndex);

        void CBCLOSEAction(antlr4::RuleContext *context, size_t actionIndex);

        void CONSTANTAction(antlr4::RuleContext *context, size_t actionIndex);

        void VARIABLEAction(antlr4::RuleContext *context, size_t actionIndex);

        // Individual semantic predicate functions triggered by sempred() above.

        struct Initializer {
            Initializer();
        };

        static Initializer _init;
    };

}  // namespace hypro
