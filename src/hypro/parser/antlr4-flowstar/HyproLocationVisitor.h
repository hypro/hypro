/*
 * HyproLocationVisitor.h
 *
 * A visitor that builds a location.
 *
 * @author Phillip Tse
 * @date 25.7.2017
 */

#pragma once

#include <antlr4-runtime.h>
#include "HybridAutomatonLexer.h"
#include "HybridAutomatonParser.h"
#include "HyproFormulaVisitor.h"
#include "../../types.h"
#include "../../datastructures/HybridAutomaton/LocationManager.h"
#include "../../datastructures/HybridAutomaton/Condition.h"


using namespace antlr4;

namespace hypro {

template<typename Number>
class HyproHAVisitor;

template<typename Number>
class HyproLocationVisitor : public HybridAutomatonBaseVisitor {

	friend class HyproHAVisitor<Number>;	

	private:

		//The vector of defined variables
		std::vector<std::string> vars;

		//Constuctor and Destructor
		HyproLocationVisitor(std::vector<std::string> varVec);
		~HyproLocationVisitor();

	public:
		
		//Inherited Functions
		antlrcpp::Any visitModes(HybridAutomatonParser::ModesContext *ctx) override;
		antlrcpp::Any visitLocation(HybridAutomatonParser::LocationContext *ctx) override;
		antlrcpp::Any visitActivities(HybridAutomatonParser::ActivitiesContext *ctx) override;
		antlrcpp::Any visitInvariants(HybridAutomatonParser::InvariantsContext *ctx) override;
		

};

} //namespace hypro

#include "HyproLocationVisitor.tpp"