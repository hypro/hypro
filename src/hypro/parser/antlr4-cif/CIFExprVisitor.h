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
		std::map<string,int> varToInt;

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
		Number stringToNumber(const std::string& string) const;


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
