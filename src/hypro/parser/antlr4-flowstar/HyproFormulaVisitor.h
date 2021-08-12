/*
 * HyproFormulaVisitor.h
 *
 * For equations, this visitor will create a vector of coefficients and will return them.
 * For invariants, this visitor will create a vector of pairs of coefficient vectors and constants.
 *
 * @author Phillip Tse
 * @date 25.7.2017
 */

#pragma once

#include "hypro/types.h"
#include "HybridAutomatonBaseVisitor.h"
#include "HybridAutomatonLexer.h"
#include "HybridAutomatonParser.h"
#include "boost/lexical_cast.hpp"
#include <carl/interval/Interval.h>
#include <memory>
#include <string>

using namespace antlr4;

namespace hypro {

template<typename Number>
class HyproLocationVisitor;

template<typename Number>
class HyproTransitionVisitor;

template<typename Number>
class HyproInitialSetVisitor;

template<typename Number>
class HyproSettingVisitor;

template<typename Number>
class HyproBadStatesVisitor;

template<typename Number>
class HyproFormulaVisitor : public HybridAutomatonBaseVisitor {

	friend class HyproLocationVisitor<Number>;
	friend class HyproTransitionVisitor<Number>;
	friend class HyproInitialSetVisitor<Number>;
	friend class HyproSettingVisitor<Number>;
	friend class HyproBadStatesVisitor<Number>;

	private:

		//The vector of defined variables
		std::vector<std::string>& vars;

		//Helping functions
		Number stringToNumber(const std::string& string);
		Number multTogether(HybridAutomatonParser::TermContext* ctx);
		vector_t<Number> getPolynomCoeff(HybridAutomatonParser::PolynomContext* ctx);

		template<typename L, typename R>
		bool isBefore(L* lhs, R* rhs);
		template<typename L, typename R>
		bool isAfter(L* lhs, R* rhs);
		template<typename C, typename L, typename R>
		bool isBetween(C* c, L* lhs, R* rhs);

		//Constructor and Destructor
		HyproFormulaVisitor(std::vector<std::string>& varVec);
		~HyproFormulaVisitor();

		//Functions inherited by HybridAutomatonBaseVisitor
		antlrcpp::Any visitExpression(HybridAutomatonParser::ExpressionContext *ctx) override;
		antlrcpp::Any visitPolynom(HybridAutomatonParser::PolynomContext *ctx) override;
		antlrcpp::Any visitEquation(HybridAutomatonParser::EquationContext *ctx) override;
		antlrcpp::Any visitConstraint(HybridAutomatonParser::ConstraintContext *ctx) override;
		antlrcpp::Any visitInterval(HybridAutomatonParser::IntervalContext *ctx) override;
		antlrcpp::Any visitIntervalexpr(HybridAutomatonParser::IntervalexprContext *ctx) override;
		antlrcpp::Any visitConstrset(HybridAutomatonParser::ConstrsetContext *ctx) override;
		antlrcpp::Any visitBracketExpression(HybridAutomatonParser::BracketExpressionContext *ctx) override;

};

} //namespace hypro

#include "HyproFormulaVisitor.tpp"