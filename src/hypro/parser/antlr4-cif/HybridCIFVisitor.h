/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once


#include "antlr4-runtime.h"
#include "HybridSystemVisitor.h"
#include "HybridSystemBaseVisitor.h"
#include "CIFLocVisitor.h"
#include "../../types.h"
#include "../../datastructures/HybridAutomaton/Location.h"
#include "../../datastructures/HybridAutomaton/LocationManager.h"
/*#include "../../datastructures/HybridAutomaton/HybridAutomaton.h"

#include "../../datastructures/HybridAutomaton/Condition.h"*/

using namespace antlr4;

namespace hypro {

    template<typename Number>
    class HybridCIFVisitor : public HybridSystemBaseVisitor {

    private:

        //A vector of all variables which are defined
        std::vector<std::string> vars;
        int numberOfLocationsWithoutAName = 0;
        std::vector<Location<Number> *> locSet;
        std::vector<Transition<Number> *> transitionVector;

        antlrcpp::Any visitDiscDecl(HybridSystemParser::DiscDeclContext *ctx) override;

        antlrcpp::Any visitAutomatonBody(HybridSystemParser::AutomatonBodyContext *ctx) override;

        antlrcpp::Any visitStdLibFunction(HybridSystemParser::StdLibFunctionContext *ctx) override;

        antlrcpp::Any visitControllability(HybridSystemParser::ControllabilityContext *ctx) override;

        antlrcpp::Any visitOptControllability(HybridSystemParser::OptControllabilityContext *ctx) override;

        antlrcpp::Any visitEvents(HybridSystemParser::EventsContext *ctx) override;

        antlrcpp::Any visitEdgeEvent(HybridSystemParser::EdgeEventContext *ctx) override;

        antlrcpp::Any visitIoDecls(HybridSystemParser::IoDeclsContext *ctx) override;

    public:

        HybridCIFVisitor();

        ~HybridCIFVisitor();

        antlrcpp::Any visitSpecification(HybridSystemParser::SpecificationContext *ctx) override;


    };


} //namespace hypro

#include "HybridCIFVisitor.tpp"
