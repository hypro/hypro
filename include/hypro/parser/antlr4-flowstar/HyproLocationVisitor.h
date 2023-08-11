/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * HyproLocationVisitor.h
 *
 * A visitor that builds a location.
 *
 * @author Phillip Tse
 * @date 25.7.2017
 */

#pragma once

#include "../../datastructures/HybridAutomaton/Condition.h"
#include "../../datastructures/HybridAutomaton/Location.h"
#include "../../datastructures/HybridAutomaton/StochasticLocation.h"
#include "../../types.h"
#include "../../util/VariablePool.h"
#include "HybridAutomatonLexer.h"
#include "HybridAutomatonParser.h"
#include "HyproFormulaVisitor.h"
#include <antlr4-runtime.h>

using namespace antlr4;

namespace hypro {

    template<typename Number>
    class HyproHAVisitor;

    template<typename Number>
    class HyproLocationVisitor : public HybridAutomatonBaseVisitor {

        friend class HyproHAVisitor<Number>;

    private:

        //The vector of defined variables
        std::vector<std::string> &vars;

        //Inherited Functions
        antlrcpp::Any visitLocation(HybridAutomatonParser::LocationContext *ctx) override;

        antlrcpp::Any visitActivities(HybridAutomatonParser::ActivitiesContext *ctx) override;

        antlrcpp::Any visitInvariants(HybridAutomatonParser::InvariantsContext *ctx) override;

        antlrcpp::Any visitStochasticlocation(HybridAutomatonParser::StochasticlocationContext *ctx) override;

        antlrcpp::Any visitProbdistribution(HybridAutomatonParser::ProbdistributionContext *ctx) override;

        antlrcpp::Any visitLoc_labels(HybridAutomatonParser::Loc_labelsContext *ctx) override;

        struct LocationLabels {
            bool isUrgent = false;
        };

    public:

        //Constuctor and Destructor
        HyproLocationVisitor(std::vector<std::string> &varVec);

        ~HyproLocationVisitor();

        //Inherited Functions - stays public so we can access it for testing/debugging
        antlrcpp::Any visitModes(HybridAutomatonParser::ModesContext *ctx) override;
    };

} //namespace hypro

#include "HyproLocationVisitor.tpp"
