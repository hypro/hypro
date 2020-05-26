/*
 * HyproTransitionVisitor.h
 *
 * Collects information to build a Transition set which can be
 * given to the HAVisitor in order to build a HybridAutomaton.
 *
 * @author Phillip Tse
 * @date 26.7.2017
 */

#pragma once

#include "../../datastructures/HybridAutomaton/Location.h"
#include "../../datastructures/HybridAutomaton/Transition.h"
#include "../../types.h"
#include "HybridAutomatonBaseVisitor.h"
#include "HyproFormulaVisitor.h"

using namespace antlr4;

namespace hypro {

template<typename Number>
class HyproHAVisitor;

template<typename Number>
class HyproTransitionVisitor : public HybridAutomatonBaseVisitor{

	friend class HyproHAVisitor<Number>;

	private:

		//A vector of all variables that are defined
		std::vector<std::string>& vars;

		//The set of possible locations
		const std::set<Location<Number>*>& locSet;

		//Inherited
		antlrcpp::Any visitTransition(HybridAutomatonParser::TransitionContext *ctx) override;
		antlrcpp::Any visitFromto(HybridAutomatonParser::FromtoContext *ctx) override;
		antlrcpp::Any visitGuard(HybridAutomatonParser::GuardContext *ctx) override;
		antlrcpp::Any visitLabels(HybridAutomatonParser::LabelsContext *ctx) override;
		antlrcpp::Any visitAllocation(HybridAutomatonParser::AllocationContext *ctx) override;
		antlrcpp::Any visitResetfct(HybridAutomatonParser::ResetfctContext *ctx) override;
		antlrcpp::Any visitAggregation(HybridAutomatonParser::AggregationContext *ctx) override;

	public:

		//Constructor and Destructor
		HyproTransitionVisitor(std::vector<std::string>& varVec, const std::set<Location<Number>*>& lSet);
		~HyproTransitionVisitor();

		//Inherited from HybridAutomatonBaseVisitor - stays public for testing/debugging
		antlrcpp::Any visitJumps(HybridAutomatonParser::JumpsContext *ctx) override;

};


} //namespace hypro

#include "HyproTransitionVisitor.tpp"
