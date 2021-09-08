/*
 * HyproLocationVisitor.h
 *
 * A visitor that builds a location.
 *
 * @author Phillip Tse
 * @date 25.7.2017
 */

#pragma once

#include "hypro/datastructures/HybridAutomaton/Condition.h"
#include "hypro/datastructures/HybridAutomaton/Location.h"
#include "hypro/datastructures/HybridAutomaton/StochasticLocation.h"
#include "hypro/types.h"
#include "hypro/util/VariablePool.h"
#include "HybridAutomatonLexer.h"
#include "HybridAutomatonParser.h"
#include "HyproFormulaVisitor.h"
#include <antlr4-runtime.h>

using namespace antlr4;

namespace hypro {

template<typename Number>
class HyproHAVisitor;

template<typename Number>
class HyproLocationVisitor : public HybridAutomatonBaseVisitor {

	friend class HyproHAVisitor<Number>;

	private:

		//The vector of defined variables
		std::vector<std::string>& vars;

		//Inherited Functions
		antlrcpp::Any visitLocation(HybridAutomatonParser::LocationContext *ctx) override;
		antlrcpp::Any visitActivities(HybridAutomatonParser::ActivitiesContext *ctx) override;
		antlrcpp::Any visitInvariants(HybridAutomatonParser::InvariantsContext *ctx) override;
		antlrcpp::Any visitStochasticlocation(HybridAutomatonParser::StochasticlocationContext *ctx) override;
  		antlrcpp::Any visitProbdistribution(HybridAutomatonParser::ProbdistributionContext *ctx) override;
		antlrcpp::Any visitLoc_labels(HybridAutomatonParser::Loc_labelsContext *ctx) override;

		struct LocationLabels{
			bool isUrgent = false;
		};

	public:

		//Constuctor and Destructor
		HyproLocationVisitor(std::vector<std::string>& varVec);
		~HyproLocationVisitor();

		//Inherited Functions - stays public so we can access it for testing/debugging
		antlrcpp::Any visitModes(HybridAutomatonParser::ModesContext *ctx) override;
};

} //namespace hypro

#include "HyproLocationVisitor.tpp"
