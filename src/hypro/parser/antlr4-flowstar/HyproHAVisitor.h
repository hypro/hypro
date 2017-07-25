/*
 * HyproHAVisitor.h
 *
 * The actual class that will build a hybrid automaton from
 * the generated parser.
 *
 *
 *
 * @author Phillip Tse
 * @date 17.7.2017
 */

#pragma once

#include <string>
#include <memory>
#include <antlr4-runtime.h>
#include "HybridAutomatonLexer.h"
#include "HybridAutomatonParser.h"
#include "HybridAutomatonBaseVisitor.h"
#include "../../types.h"
#include "../../datastructures/HybridAutomaton/Location.h"
#include "../../datastructures/HybridAutomaton/LocationManager.h"
//#include "../../datastructures/HybridAutomaton/HybridAutomaton.h"

using namespace antlr4;

namespace hypro {

template<typename Number>
class HyproHAVisitor : public HybridAutomatonBaseVisitor {

	private:
		//Set of locations a hybrid automaton needs
		std::set<Location<Number>*> locSet;

		//A vector of all variables that are defined
		std::vector<std::string> vars;

		//Helping functions
		Number stringToNumber(std::string string);
		Number multTogether(HybridAutomatonParser::TermContext* ctx);
		vector_t<Number> getPolynomCoeff(HybridAutomatonParser::PolynomContext* ctx);


	public:

		HyproHAVisitor();
		~HyproHAVisitor();

		antlrcpp::Any visitStart(HybridAutomatonParser::StartContext *ctx) override;

		antlrcpp::Any visitVardeclaration(HybridAutomatonParser::VardeclarationContext *ctx) override;

		antlrcpp::Any visitModes(HybridAutomatonParser::ModesContext *ctx) override;

		antlrcpp::Any visitLocation(HybridAutomatonParser::LocationContext *ctx) override;

		antlrcpp::Any visitActivities(HybridAutomatonParser::ActivitiesContext *ctx) override;

		antlrcpp::Any visitInvariants(HybridAutomatonParser::InvariantsContext *ctx) override;

		antlrcpp::Any visitPolynom(HybridAutomatonParser::PolynomContext *ctx) override;

		antlrcpp::Any visitEquation(HybridAutomatonParser::EquationContext *ctx) override;

		antlrcpp::Any visitConstraint(HybridAutomatonParser::ConstraintContext *ctx) override;

		antlrcpp::Any visitIntervalexpr(HybridAutomatonParser::IntervalexprContext *ctx) override;

};

template<typename Number>
std::ostream& operator<<(std::ostream& ostr, HyproHAVisitor<Number> visitor){
	ostr << "Location Names: " << std::endl;
/*	for(auto loc : visitor.getLocSet()){
		ostr << loc << std::endl;
	}
*/
	ostr << "Variable Names: " << std::endl;
/*
	for(auto var : visitor.getVarNames()){
		ostr << var << std::endl;
	}
*/
	//ostr << "flowMatrix is:\n " << visitor.getFlow() << std::endl;
	//ostr << "invMatrix is:\n " << visitor.getInvMat() << std::endl;
	return ostr;
}

} //namespace hypro

#include "HyproHAVisitor.tpp"
