/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * HyproSettingVisitor.h
 *
 * Collects information from given settings
 * in order to build a HybridAutomaton.
 *
 * @author Phillip Tse
 * @date 17.8.2017
 */

#pragma once

#include "../../types.h"
#include "HybridAutomatonLexer.h"
#include "HybridAutomatonParser.h"
#include "HybridAutomatonBaseVisitor.h"
#include "HyproFormulaVisitor.h"
#include "../../datastructures/reachability/Settings.h"
#include <math.h>

using namespace antlr4;

namespace hypro {

    template<typename Number>
    class HyproHAVisitor;

    template<typename Number>
    class HyproSettingVisitor : HybridAutomatonBaseVisitor {

        friend class HyproHAVisitor<Number>;

    private:

        //A vector of all variables that are defined
        std::vector<std::string> &vars;

        //Inherited
        antlrcpp::Any visitFixedsteps(HybridAutomatonParser::FixedstepsContext *ctx) override;

        antlrcpp::Any visitTime(HybridAutomatonParser::TimeContext *ctx) override;

        antlrcpp::Any visitPlotsetting(HybridAutomatonParser::PlotsettingContext *ctx) override;

        antlrcpp::Any visitFilename(HybridAutomatonParser::FilenameContext *ctx) override;

        antlrcpp::Any visitMaxjumps(HybridAutomatonParser::MaxjumpsContext *ctx) override;
/*          
        antlrcpp::Any visitPrint(HybridAutomatonParser::PrintContext *ctx) override;
        antlrcpp::Any visitRemainder(HybridAutomatonParser::RemainderContext *ctx) override;
        antlrcpp::Any visitIdentity(HybridAutomatonParser::IdentityContext *ctx) override;
        antlrcpp::Any visitFixedorders(HybridAutomatonParser::FixedordersContext *ctx) override;
        antlrcpp::Any visitCutoff(HybridAutomatonParser::CutoffContext *ctx) override;
        antlrcpp::Any visitPrecision(HybridAutomatonParser::PrecisionContext *ctx) override;
*/

    public:

        //Constructor & Destructor
        HyproSettingVisitor(std::vector<std::string> &varVec);

        ~HyproSettingVisitor();

        //Inherited - stays public so we can access it for testing/debugging
        antlrcpp::Any visitSetting(HybridAutomatonParser::SettingContext *ctx) override;

    };

} //namespace hypro

#include "HyproSettingVisitor.tpp"
