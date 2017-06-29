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

		//A temporary reusable location that is needed to build a location
		Location<Number> loc;

		//A vector of all variables that are defined 
		std::vector<std::string> vars;

		//A vector of all location names 
		std::vector<std::string> locNames;

	public:
		
		HyproHAListener();
		~HyproHAListener();

		void enterVardeclaration(HybridAutomatonParser::VardeclarationContext* ctx) override;
		void enterLocation(HybridAutomatonParser::LocationContext* ctx) override;
		void enterActivities(HybridAutomatonParser::ActivitiesContext* ctx) override;
		void enterEquation(HybridAutomatonParser::EquationContext* ctx) override;
		void enterTerm(HybridAutomatonParser::TermContext* ctx) override;

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

} //namespace hypro