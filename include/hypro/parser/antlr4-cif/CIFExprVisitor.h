/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once


#include "../../datastructures/HybridAutomaton/Location.h"
#include "../../datastructures/HybridAutomaton/LocationManager.h"
#include "../../datastructures/HybridAutomaton/Transition.h"
#include "../../types.h"
#include "HybridSystemBaseVisitor.h"
#include "HybridSystemVisitor.h"
#include "antlr4-runtime.h"


using namespace antlr4;

namespace hypro {

    template<typename Number>
    class CIFExprVisitor : public HybridSystemBaseVisitor {


    private:

        std::vector<std::string> vars;
        std::map<string, int> varToInt;

        antlrcpp::Any visitEquationDerivate(HybridSystemParser::EquationDerivateContext *ctx) override;


        antlrcpp::Any visitOrExpression(HybridSystemParser::OrExpressionContext *ctx) override;

        antlrcpp::Any visitAndExpression(HybridSystemParser::AndExpressionContext *ctx) override;

        antlrcpp::Any visitCompareExpression(HybridSystemParser::CompareExpressionContext *ctx) override;

        antlrcpp::Any visitMulExpression(HybridSystemParser::MulExpressionContext *ctx) override;

        antlrcpp::Any visitAddExpression(HybridSystemParser::AddExpressionContext *ctx) override;

        antlrcpp::Any visitUnaryExprMinus(HybridSystemParser::UnaryExprMinusContext *ctx) override;


        antlrcpp::Any visitExprFactName(HybridSystemParser::ExprFactNameContext *ctx) override;

        antlrcpp::Any visitExprFactNumber(HybridSystemParser::ExprFactNumberContext *ctx) override;

        antlrcpp::Any visitExprFactRealNumber(HybridSystemParser::ExprFactRealNumberContext *ctx) override;

        antlrcpp::Any visitName(HybridSystemParser::NameContext *ctx) override;


        //helper functions
        void initalize();

        Number stringToNumber(const std::string &string) const;


        //things we can't handle
        antlrcpp::Any visitStdLibFunction(HybridSystemParser::StdLibFunctionContext *ctx) override;

        antlrcpp::Any visitUnaryExpr(HybridSystemParser::UnaryExprContext *ctx) override;

        antlrcpp::Any visitEquationNonDerivate(HybridSystemParser::EquationNonDerivateContext *ctx) override;


    public:

        CIFExprVisitor(std::vector<std::string> varVec);

        ~CIFExprVisitor();

        antlrcpp::Any visitExpressions(HybridSystemParser::ExpressionsContext *ctx) override;

        antlrcpp::Any visitExpression(HybridSystemParser::ExpressionContext *ctx) override;

        antlrcpp::Any visitEquations(HybridSystemParser::EquationsContext *ctx) override;


    };


} //namespace hypro

#include "CIFExprVisitor.tpp"
