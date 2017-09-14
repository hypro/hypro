/*
 * HyproBadStatesVisitor.h
 *
 * A visitor that builds the bad states and returns it to the HyproHAVisitor.h
 *
 * @author Phillip Tse
 * @date 14.9.2017
 */

#pragma once

#include "BadStatesLexer.h"
#include "BadStatesParser.h"
#include "HybridAutomatonBaseVisitor.h"
#include "datastructures/HybridAutomaton/Location.h" 	//For locPtrComp
#include "datastructures/HybridAutomaton/Condition.h" 	//For Condition class

namespace hypro {

template<typename Number>
class HyproHAVisitor;

template<typename Number>
class HyproBadStatesVisitor : public HybridAutomatonBaseVisitor {

	friend class HyproHAVisitor<Number>;

	//From HybridAutomaton.h, for local bad states
	using locationConditionMap = std::map<const Location<Number>*, Condition<Number>, locPtrComp<Number>>; /// Map from location pointers to conditions.

	//TODO: Maybe implement global bad states

	private:

		//Vector of declared state variables
		std::vector<std::string>& vars;

		//Set of parsed locations
		std::set<Location<Number>*>& locSet;

		//Constructor
		HyproBadStatesVisitor(std::vector<std::string>& varVec, std::set<Location<Number>*>& lSet);
		~HyproBadStatesVisitor();

	public:

		//Inherited from HybridAutomatonBaseVisitor
		antlrcpp::Any visitUnsafeset(HybridAutomatonParser::UnsafesetContext *ctx) override;
		antlrcpp::Any visitBadstate(HybridAutomatonParser::BadstateContext *ctx) override; 

};

} //namespace hypro

#include "HyproBadStatesVisitor.tpp"
