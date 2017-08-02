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
#include <antlr4-runtime.h>
#include "../../types.h"
#include "HybridAutomatonLexer.h"
#include "HybridAutomatonParser.h"
#include "HybridAutomatonBaseVisitor.h"
#include "HyproLocationVisitor.h"
#include "HyproTransitionVisitor.h"
#include "HyproInitialSetVisitor.h"
#include "../../datastructures/HybridAutomaton/HybridAutomaton.h"

using namespace antlr4;

namespace hypro {

template<typename Number>
class HyproHAVisitor : public HybridAutomatonBaseVisitor {

	private:

		//A vector of all variables that are defined
		std::vector<std::string> vars;

	public:

		using locationStateMap = std::multimap<const Location<Number>*, State<Number,ConstraintSet<Number>>, locPtrComp<Number>>;

		HyproHAVisitor();
		~HyproHAVisitor();

		//Inherited from HybridAutomatonBaseVisitor which is generated from AnTLR
		antlrcpp::Any visitStart(HybridAutomatonParser::StartContext *ctx) override;
		antlrcpp::Any visitVardeclaration(HybridAutomatonParser::VardeclarationContext *ctx) override;

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
