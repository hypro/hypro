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

#include <vector>
#include <string>
#include <memory>
#include <antlr4-runtime.h>
#include "HybridAutomatonLexer.h"
#include "HybridAutomatonParser.h"
#include "HybridAutomatonBaseVisitor.h"
#include "../../types.h"

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
class HyproFormulaVisitor : public HybridAutomatonBaseVisitor {

	friend class HyproLocationVisitor<Number>;
	friend class HyproTransitionVisitor<Number>;
	friend class HyproInitialSetVisitor<Number>;

	private:

		//The vector of defined variables
		std::vector<std::string> vars;

		//Helping functions
		Number stringToNumber(std::string string);
		Number multTogether(HybridAutomatonParser::TermContext* ctx);
		vector_t<Number> getPolynomCoeff(HybridAutomatonParser::PolynomContext* ctx);

		//Constructor and Destructor
		HyproFormulaVisitor(std::vector<std::string> varVec);
		~HyproFormulaVisitor();

	public:

		//Functions inherited by FormulaBaseVisitor
		antlrcpp::Any visitPolynom(HybridAutomatonParser::PolynomContext *ctx) override;
		antlrcpp::Any visitEquation(HybridAutomatonParser::EquationContext *ctx) override;
		antlrcpp::Any visitConstraint(HybridAutomatonParser::ConstraintContext *ctx) override;
		antlrcpp::Any visitIntervalexpr(HybridAutomatonParser::IntervalexprContext *ctx) override;
		antlrcpp::Any visitConstrset(HybridAutomatonParser::ConstrsetContext *ctx) override;

};

} //namespace hypro

#include "HyproFormulaVisitor.tpp"