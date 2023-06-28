/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "CIFExprVisitor.h"

namespace hypro {


    template<typename Number>
    CIFExprVisitor<Number>::CIFExprVisitor(std::vector<std::string> varVec) :
            vars(varVec) {}

    template<typename Number>
    CIFExprVisitor<Number>::~CIFExprVisitor() {}


    template<typename Number>
    antlrcpp::Any CIFExprVisitor<Number>::visitExpressions(HybridSystemParser::ExpressionsContext *ctx) {

        return visitChildren(ctx); //for not generating a warning
    }

    template<typename Number>
    antlrcpp::Any CIFExprVisitor<Number>::visitExpression(HybridSystemParser::ExpressionContext *ctx) {

        return visitChildren(ctx); //for not generating a warning
    }

    template<typename Number>
    antlrcpp::Any CIFExprVisitor<Number>::visitEquations(HybridSystemParser::EquationsContext *ctx) {

        matrix_t<Number> result = matrix_t<Number>::Zero(vars.size() + 1, vars.size() + 1);


        //TODO check, if every var has an equation and none more than one
        size_t n = ctx->children.size();
        for (size_t i = 0; i < n - 1; i++) {
            std::pair<string, vector_t<Number>> tmp = visit(ctx->children[i]);
            result.row(varToInt[tmp.first]) = tmp.second;
        }

        return result;
    }

    template<typename Number>
    antlrcpp::Any CIFExprVisitor<Number>::visitEquationDerivate(HybridSystemParser::EquationDerivateContext *ctx) {

        std::pair<string, vector_t<Number>> result;

        result.first = ctx->identifier()->getText();
        std::vector<std::pair<vector_t<Number>, Number>> tmp = visit(ctx->expression());
        result.second = tmp[0].first;

        return result;
    }


    template<typename Number>
    antlrcpp::Any CIFExprVisitor<Number>::visitOrExpression(HybridSystemParser::OrExpressionContext *ctx) {
        if (ctx->children.size() != 1) {
            std::cerr << "Could not handle OR yet." << std::endl;
            exit(1);
        }
        return visitChildren(ctx);
    }

    template<typename Number>
    antlrcpp::Any CIFExprVisitor<Number>::visitAndExpression(HybridSystemParser::AndExpressionContext *ctx) {

        std::vector<std::pair<vector_t<Number>, Number>> result;

        size_t n = ctx->children.size();
        for (size_t i = 0; i < n; i++) {
            std::vector<std::pair<vector_t<Number>, Number>> tmp = visit(ctx->children[i]);
            for (unsigned int j = 0; j < tmp.size(); j++) {
                result.push_back(tmp[j]);
            }
        }
        return result;
    }


    template<typename Number>
    antlrcpp::Any CIFExprVisitor<Number>::visitCompareExpression(HybridSystemParser::CompareExpressionContext *ctx) {

        vector_t<Number> leftVector = visit(ctx->children[0]);
        int vectorsize = leftVector.size();

        Number leftNumber = leftVector[vectorsize - 1];
        vector_t<Number> rightVector;
        Number rightNumber;

        std::vector<std::pair<vector_t<Number>, Number>> result;

        //only one expression => no comparison
        if (ctx->children.size() == 1) {
            auto res = std::make_pair(leftVector, leftNumber);
            result.push_back(res);
            return result;
        }

        //more than one child => comparison
        leftVector.conservativeResize(vectorsize - 1);

        size_t n = ctx->children.size();
        for (size_t i = 0; i < n - 1; i++) {

            //init this step
            rightVector = visit(ctx->children[i + 1]);
            rightNumber = rightVector[vectorsize - 1];
            rightVector.conservativeResize(vectorsize - 1);

            string actOperator = (ctx->COMPOP()[i])->getText();

            //not allowed operators
            if (actOperator == "<" || actOperator == ">" || actOperator == "!=" || actOperator == "in" ||
                actOperator == "sub") {
                std::cerr << "Could not handle comparison operator " << actOperator << "  yet." << std::endl;
                exit(1);
            }

            //allowed operators
            if (actOperator == "<") {
                std::pair<vector_t<Number>, Number> res = std::make_pair(leftVector - rightVector,
                                                                         rightNumber - leftNumber);
                result.push_back(res);
            }
            if (actOperator == ">") {
                std::pair<vector_t<Number>, Number> res = std::make_pair(rightVector - leftVector,
                                                                         leftNumber - rightNumber);
                result.push_back(res);
            }
            if (actOperator == "=") {
                std::pair<vector_t<Number>, Number> res = std::make_pair(leftVector - rightVector,
                                                                         rightNumber - leftNumber);
                result.push_back(res);
                res = std::make_pair(rightVector - leftVector, leftNumber - rightNumber);
                result.push_back(res);
            }

            //init for next step
            leftNumber = rightNumber;
            leftVector = rightVector;

        }


        return result;
    }

    template<typename Number>
    antlrcpp::Any CIFExprVisitor<Number>::visitAddExpression(HybridSystemParser::AddExpressionContext *ctx) {

        vector_t<Number> actualValue = visit(ctx->children[0]);

        size_t n = ctx->children.size();
        for (size_t i = 0; i < n - 1; i++) {

            vector_t<Number> expr = visit(ctx->children[i + 1]);
            string actOperator = (ctx->ADDOP()[i])->getText();

            //addition
            if (actOperator == "+") {
                actualValue = actualValue + expr;
            }

            //subtraction
            if (actOperator == "-") {
                actualValue = actualValue - expr;
            }
        }

        return actualValue;
    }


    template<typename Number>
    antlrcpp::Any CIFExprVisitor<Number>::visitMulExpression(HybridSystemParser::MulExpressionContext *ctx) {

        vector_t<Number> result;
        vector_t<Number> actualValue = visit(ctx->children[0]);
        bool actValHasVariable = false;
        bool nextExprHasVariable = false;

        for (int j = 0; j < actualValue.size() - 1; j++) {
            if (actualValue[j] != 0) {
                actValHasVariable = true;
            }
        }

        size_t n = ctx->children.size();
        for (size_t i = 0; i < n - 1; i++) {

            vector_t<Number> expr = visit(ctx->children[i + 1]);
            string actOperator = (ctx->MULOP()[i])->getText();
            if (actOperator == "div" || actOperator == "mod") {
                std::cerr << "Could not interpret div/mod in expressions yet." << std::endl;
                exit(1);
            }
            //test for linearity problems
            for (unsigned int j = 0; j < expr.size() - 1; j++) {
                if (expr[j] != 0) {
                    if (actValHasVariable) {
                        std::cerr << "Could not interpret non linear expressions yet." << std::endl;
                        exit(1);
                    } else {
                        nextExprHasVariable = true;
                    }
                }

            }

            //check for problems special to the '/' operator
            if (actOperator == "/") {
                if (nextExprHasVariable) {
                    std::cerr << "Could not interpret non linear expressions yet." << std::endl;
                    exit(1);
                }
                if (expr[expr.size() - 1] == 0) {
                    std::cerr << "Division by 0" << std::endl;
                    exit(1);
                }
            }

            //everything with linearity is fine, lets multiply / divide


            //multiplication
            if (actOperator == "*") {
                if (actValHasVariable && !nextExprHasVariable) {
                    actualValue = actualValue * expr[expr.size() - 1];
                }

                if (!actValHasVariable && nextExprHasVariable) {
                    actualValue = expr * actualValue[expr.size() - 1];
                }

                if (!actValHasVariable && !nextExprHasVariable) {
                    actualValue[actualValue.size() - 1] = actualValue[actualValue.size() - 1] * expr[expr.size() - 1];
                }
            }

            //division
            if (actOperator == "/") {
                if (actValHasVariable && !nextExprHasVariable) {
                    actualValue = actualValue * (1 / expr[expr.size() - 1]);
                }

                if (!actValHasVariable && nextExprHasVariable) {
                    actualValue = expr * (1 / actualValue[expr.size() - 1]);
                }

                if (!actValHasVariable && !nextExprHasVariable) {
                    actualValue[actualValue.size() - 1] = actualValue[actualValue.size() - 1] / expr[expr.size() - 1];
                }
            }

            //set actValHasVariable for the next step
            if (!actValHasVariable) {
                actValHasVariable = nextExprHasVariable;
            }

        }


        return actualValue; //for not generating a warning
    }


    //UnaryExpression
    //for funcExpr and plus the generated function is sufficient
    template<typename Number>
    antlrcpp::Any CIFExprVisitor<Number>::visitUnaryExprMinus(HybridSystemParser::UnaryExprMinusContext *ctx) {

        vector_t<Number> result = vector_t<Number>::Zero(vars.size() + 1);
        vector_t<Number> tmp = visit(ctx->unaryExpression());

        for (unsigned int i = 0; i < vars.size(); i++) {
            result[i] = tmp[i] * (-1);
        }

        return result;
    }


    //ExpressionFactors
    template<typename Number>
    antlrcpp::Any CIFExprVisitor<Number>::visitExprFactName(HybridSystemParser::ExprFactNameContext *ctx) {

        vector_t<Number> result = vector_t<Number>::Zero(vars.size() + 1);

        string name = visit(ctx->name());
        result[varToInt[name]] = 1;

        return result;

    }

    template<typename Number>
    antlrcpp::Any CIFExprVisitor<Number>::visitExprFactNumber(HybridSystemParser::ExprFactNumberContext *ctx) {

        vector_t<Number> result = vector_t<Number>::Zero(vars.size() + 1);

        result[vars.size()] = stringToNumber(ctx->NUMBER()->getText());

        return result;

    }

    template<typename Number>
    antlrcpp::Any CIFExprVisitor<Number>::visitExprFactRealNumber(HybridSystemParser::ExprFactRealNumberContext *ctx) {

        vector_t<Number> result = vector_t<Number>::Zero(vars.size() + 1);

        result[vars.size()] = stringToNumber(ctx->REALNUMBER()->getText());

        return result;

    }

    template<typename Number>
    antlrcpp::Any CIFExprVisitor<Number>::visitName(HybridSystemParser::NameContext *ctx) {
        return ctx->getText();
    }

    //helper functions
    template<typename Number>
    void CIFExprVisitor<Number>::initalize() {
        for (unsigned i = 0; i < vars.size(); i++) {
            varToInt.insert(std::pair<string, int>(vars[i], i));
        }
    }


    template<typename Number>
    Number CIFExprVisitor<Number>::stringToNumber(const std::string &string) const {
        double numInFloat = std::stod(string);
        Number numInNumber = Number(numInFloat);
        return numInNumber;
    }


    //things we can't handle
    template<typename Number>
    antlrcpp::Any CIFExprVisitor<Number>::visitStdLibFunction(HybridSystemParser::StdLibFunctionContext *ctx) {
        std::cerr << "Could not interpret std::lib functions yet." << std::endl;
        exit(1);
        return visitChildren(ctx); //for not generating a warning
    }

    template<typename Number>
    antlrcpp::Any CIFExprVisitor<Number>::visitUnaryExpr(HybridSystemParser::UnaryExprContext *ctx) {
        std::cerr << "Could not interpret 'sample' yet." << std::endl;
        exit(1);
        return visitChildren(ctx); //for not generating a warning
    }

    template<typename Number>
    antlrcpp::Any
    CIFExprVisitor<Number>::visitEquationNonDerivate(HybridSystemParser::EquationNonDerivateContext *ctx) {
        std::cerr << "Could not interpret non derivate equation for the flow yet." << std::endl;
        exit(1);
        return visitChildren(ctx); //for not generating a warning
    }

/*
	template<typename Number>
	antlrcpp::Any CIFExprVisitor<Number>::visit***(HybridSystemParser::***Context *ctx){
		std::cerr << "Could not interpret /handle *** yet." << std::endl;
		exit( 1 );
		return visitChildren(ctx); //for not generating a warning
	}
*/
}
