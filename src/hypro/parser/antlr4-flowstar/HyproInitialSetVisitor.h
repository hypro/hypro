/*
 * HyproInitialSetVisitor.h
 *
 * Collects information to build a Transition set which can be
 * given to the HAVisitor in order to build a HybridAutomaton.
 *
 * @author Phillip Tse
 * @date 26.7.2017
 */

#pragma once

#include "../../types.h"
#include "HybridAutomatonLexer.h"
#include "HybridAutomatonParser.h"
#include "HybridAutomatonBaseVisitor.h"
#include "HyproFormulaVisitor.h"
#include "../../datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../../datastructures/HybridAutomaton/StochasticHybridAutomaton.h"
#include <map>

using namespace antlr4;

namespace hypro {

template<typename Number>
class HyproHAVisitor;

template<typename Number>
class HyproInitialSetVisitor : HybridAutomatonBaseVisitor {

	friend class HyproHAVisitor<Number>;

	private:

		//A vector of all variables that are defined
		std::vector<std::string>& vars;

		//The set of possible locations
		std::set<Location<Number>*>& locSet;

		//Inherited
		antlrcpp::Any visitInitstate(HybridAutomatonParser::InitstateContext *ctx) override;
		antlrcpp::Any visitProbinitstate(HybridAutomatonParser::ProbinitstateContext *ctx) override;

	public:

		//using locationStateMap = std::multimap<const Location<Number>*, State<Number,ConstraintSet<Number>>, locPtrComp<Number>>;

		//Constructor & Destructor
		HyproInitialSetVisitor(std::vector<std::string>& varVec, std::set<Location<Number>*>& lSet);
		~HyproInitialSetVisitor();

		//Inherited - stays public for testing/debugging
		antlrcpp::Any visitInit(HybridAutomatonParser::InitContext *ctx) override;


};

} //namespace hypro

#include "HyproInitialSetVisitor.tpp"
