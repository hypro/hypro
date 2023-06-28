/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * HyproHAVisitor.h
 *
 * The actual class that will build a hybrid automaton from
 * the generated parser.
 *
 * @author Phillip Tse
 * @date 17.7.2017
 */

#pragma once

#include <string>
#include <memory>
#include "HybridAutomatonLexer.h"
#include "HybridAutomatonParser.h"
#include "HybridAutomatonBaseVisitor.h"
#include "HyproLocationVisitor.h"
#include "HyproTransitionVisitor.h"
#include "HyproInitialSetVisitor.h"
#include "HyproSettingVisitor.h"
#include "HyproBadStatesVisitor.h"
#include "../../datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../../datastructures/HybridAutomaton/StochasticHybridAutomaton.h"
#include "../../datastructures/reachability/Settings.h"
#include "../../util/logging/Logger.h"
#include "../../util/VariablePool.h"

using namespace antlr4;

namespace hypro {

    template<typename Number>
    class HyproHAVisitor : public HybridAutomatonBaseVisitor {

    private:

        //A vector of all variables that are defined.
        //This must be passed onto all the underlying visitors as they need to have
        //access to the variable names stated in the variable declaration
        std::vector<std::string> vars;

        //Stores the parsed reachability settings
        ReachabilitySettings reachSettings;

        //Inherited from HybridAutomatonBaseVisitor which is generated from AnTLR
        antlrcpp::Any visitVardeclaration(HybridAutomatonParser::VardeclarationContext *ctx) override;

    public:

        //Is first defined in HybridAutomaton.h
        //using locationStateMap = std::multimap<const Location<Number>*, State<Number,ConstraintSet<Number>>, locPtrComp<Number>>;
        //using locationConditionMap = std::map<const Location<Number>*, Condition<Number>, locPtrComp<Number>>; /// Map from location pointers to conditions.

        //Constructor and Destructor
        HyproHAVisitor();

        ~HyproHAVisitor();

        //Inherited from HybridAutomatonBaseVisitor which is generated from AnTLR
        //As this is the starting rule, it must stay public.
        antlrcpp::Any visitStart(HybridAutomatonParser::StartContext *ctx) override;

        //Getter for settings
        inline ReachabilitySettings getSettings() { return reachSettings; }
    };

} //namespace hypro

#include "HyproHAVisitor.tpp"
