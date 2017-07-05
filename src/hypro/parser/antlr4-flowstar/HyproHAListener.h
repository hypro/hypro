/*
 * HyproHAListener.h
 *
 * The actual class that will build a hybrid automaton from 
 * the generated parser.
 *
 * On entering each rule of the parser, we will make a syntax check.
 * On exiting each rule we will extract the actual information.
 *
 * @author Phillip Tse
 * @date 27.6.2017
 */

#pragma once

#include <string>
#include <memory>
#include <antlr4-runtime.h>
#include "HybridAutomatonLexer.h"
#include "HybridAutomatonParser.h"
#include "HybridAutomatonBaseListener.h"
#include "../../types.h"
#include "../../datastructures/hybridAutomata/Location.h"

//using namespace org::antlr::v4::runtime;
using namespace antlr4;

namespace hypro {

template<typename Number>
class HyproHAListener : public HybridAutomatonBaseListener {

	private: 
		//Set of locations a hybrid automaton needs
		std::set<Location<Number>*> locSet; 

		//A vector of all variables that are defined 
		std::vector<std::string> vars;

		//A vector of all location names 
		std::vector<std::string> locNames;

		//A temporary reusable location that is needed to build a location
		//Location<Number> loc;

		//A temporary flow matrix and needed positioning variable
		matrix_t<Number> flowMatrix;
		matrix_t<Number> invMatrix;
		std::shared_ptr<matrix_t<Number>> fillingTarget;
		unsigned int currentRow = 0;

	public:
		
		HyproHAListener();
		~HyproHAListener();

		Number stringToNumber(std::string string);

		inline std::vector<std::string> getLocNames(){ return locNames; }
		inline std::vector<std::string> getVarNames(){ return vars; }
		inline matrix_t<Number> getFlow(){ return flowMatrix; }
		inline matrix_t<Number> getInv(){ return invMatrix; }
		inline matrix_t<Number> getFillingTarget(){ return *fillingTarget; }
		inline void setFillingTarget(matrix_t<Number> newTarget){ fillingTarget = std::make_shared<matrix_t<Number>>(newTarget); }

		void enterVardeclaration(HybridAutomatonParser::VardeclarationContext* ctx) override;
		void enterLocation(HybridAutomatonParser::LocationContext* ctx) override;
		void enterActivities(HybridAutomatonParser::ActivitiesContext* ctx) override;
		void enterEquation(HybridAutomatonParser::EquationContext* ctx) override;
		void enterMult(HybridAutomatonParser::MultContext* ctx) override;
		
		void enterTerm(HybridAutomatonParser::TermContext* ctx) override;
		void exitTerm(HybridAutomatonParser::TermContext* ctx) override;

		void exitEquation(HybridAutomatonParser::EquationContext* ctx) override;

		void enterInvariants(HybridAutomatonParser::InvariantsContext* ctx) override;
	    void exitInvariants(HybridAutomatonParser::InvariantsContext* ctx) override;

		void enterBoolexpr(HybridAutomatonParser::BoolexprContext* ctx) override;
 		void exitBoolexpr(HybridAutomatonParser::BoolexprContext* ctx) override;

  		void enterIntervalexpr(HybridAutomatonParser::IntervalexprContext* ctx) override;
  		void exitIntervalexpr(HybridAutomatonParser::IntervalexprContext* ctx) override;

  		void exitLocation(HybridAutomatonParser::LocationContext* ctx) override;
	
		void exitStart(HybridAutomatonParser::StartContext* ctx) override; 

};

template<typename Number>
std::ostream& operator<<(std::ostream& ostr, HyproHAListener<Number> listener){
	ostr << "Location Names: " << std::endl;
	for(auto loc : listener.getLocNames()){
		ostr << loc << std::endl;
	}
	ostr << "Variable Names: " << std::endl;
	for(auto var : listener.getVarNames()){
		ostr << var << std::endl; 
	}
	ostr << "flowMatrix is:\n " << listener.getFlow() << std::endl;
	return ostr;
}

} //namespace hypro

#include "HyproHAListener.tpp"