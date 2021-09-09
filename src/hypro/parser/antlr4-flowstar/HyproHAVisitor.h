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
#include "HybridAutomatonLexer.h"
#include "HybridAutomatonParser.h"
#include "HybridAutomatonBaseVisitor.h"
#include "HyproLocationVisitor.h"
#include "HyproTransitionVisitor.h"
#include "HyproInitialSetVisitor.h"
#include "HyproSettingVisitor.h"
#include "HyproBadStatesVisitor.h"
#include "hypro/datastructures/HybridAutomaton/HybridAutomaton.h"
#include "hypro/datastructures/HybridAutomaton/StochasticHybridAutomaton.h"
#include "hypro/datastructures/reachability/Settings.h"
#include "hypro/util/logging/Logger.h"
#include "hypro/util/VariablePool.h"

using namespace antlr4;

namespace hypro {

template<typename Number>
class HyproHAVisitor : public HybridAutomatonBaseVisitor {

	private:

		//A vector of all variables that are defined.
		//This must be passed onto all the underlying visitors as they need to have
		//access to the variable names stated in the variable declaration
		std::vector<std::string> vars;

		//Stores the parsed reachability settings
		ReachabilitySettings reachSettings;

		//Inherited from HybridAutomatonBaseVisitor which is generated from AnTLR
		antlrcpp::Any visitVardeclaration(HybridAutomatonParser::VardeclarationContext *ctx) override;

	public:

		//Is first defined in HybridAutomaton.h
		//using locationStateMap = std::multimap<const Location<Number>*, State<Number,ConstraintSet<Number>>, locPtrComp<Number>>;
		//using locationConditionMap = std::map<const Location<Number>*, Condition<Number>, locPtrComp<Number>>; /// Map from location pointers to conditions.

		//Constructor and Destructor
		HyproHAVisitor();
		~HyproHAVisitor();

		//Inherited from HybridAutomatonBaseVisitor which is generated from AnTLR
		//As this is the starting rule, it must stay public.
		antlrcpp::Any visitStart(HybridAutomatonParser::StartContext *ctx) override;

		//Getter for settings
		inline ReachabilitySettings getSettings() { return reachSettings; }
};

} //namespace hypro

#include "HyproHAVisitor.tpp"
