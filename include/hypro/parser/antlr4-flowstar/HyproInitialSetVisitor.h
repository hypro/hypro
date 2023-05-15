/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * HyproInitialSetVisitor.h
 *
 * Collects information to build a Transition set which can be
 * given to the HAVisitor in order to build a HybridAutomaton.
 *
 * @author Phillip Tse
 * @date 26.7.2017
 */

#pragma once

#include "../../types.h"
#include "HybridAutomatonLexer.h"
#include "HybridAutomatonParser.h"
#include "HybridAutomatonBaseVisitor.h"
#include "HyproFormulaVisitor.h"
#include "../../datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../../datastructures/HybridAutomaton/StochasticHybridAutomaton.h"
#include <map>

using namespace antlr4;

namespace hypro {

    template<typename Number>
    class HyproHAVisitor;

    template<typename Number>
    class HyproInitialSetVisitor : HybridAutomatonBaseVisitor {

        friend class HyproHAVisitor<Number>;

    private:

        //A vector of all variables that are defined
        std::vector<std::string> &vars;

        //The set of possible locations
        std::set<Location<Number> *> &locSet;

        //Inherited
        antlrcpp::Any visitInitstate(HybridAutomatonParser::InitstateContext *ctx) override;

        antlrcpp::Any visitProbinitstate(HybridAutomatonParser::ProbinitstateContext *ctx) override;

    public:

        //using locationStateMap = std::multimap<const Location<Number>*, State<Number,ConstraintSet<Number>>, locPtrComp<Number>>;

        //Constructor & Destructor
        HyproInitialSetVisitor(std::vector<std::string> &varVec, std::set<Location<Number> *> &lSet);

        ~HyproInitialSetVisitor();

        //Inherited - stays public for testing/debugging
        antlrcpp::Any visitInit(HybridAutomatonParser::InitContext *ctx) override;


    };

} //namespace hypro

#include "HyproInitialSetVisitor.tpp"
