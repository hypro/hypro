/*
 * HyproBadStatesVisitor.h
 *
 * A visitor that builds the local and global bad states and returns it to the HyproHAVisitor.h.
 *
 * @author Phillip Tse
 * @date 14.9.2017
 */

#pragma once

#include "HybridAutomatonBaseVisitor.h"
#include "hypro/datastructures/HybridAutomaton/Location.h" 	//For locPtrComp
#include "hypro/datastructures/HybridAutomaton/Condition.h" //For Condition class

namespace hypro {

template<typename Number>
class HyproHAVisitor;

template<typename Number>
class HyproBadStatesVisitor : public HybridAutomatonBaseVisitor {

	friend class HyproHAVisitor<Number>;

	private:

		//Vector of declared state variables
		std::vector<std::string>& vars;

		//Set of parsed locations
		std::set<Location<Number>*>& locSet;

		//Auxiliary variable since this visitor returns local and global badstates
		std::vector<Condition<Number>> gBadStates;

		//Constructor
		HyproBadStatesVisitor(std::vector<std::string>& varVec, std::set<Location<Number>*>& lSet);
		~HyproBadStatesVisitor();

	public:

		//Getter for global badstates
		std::vector<Condition<Number>> getGlobalBadStates(){ return gBadStates; }

		//Inherited from HybridAutomatonBaseVisitor
		antlrcpp::Any visitUnsafeset(HybridAutomatonParser::UnsafesetContext *ctx) override;
		antlrcpp::Any visitLbadstate(HybridAutomatonParser::LbadstateContext *ctx) override;
		antlrcpp::Any visitGbadstate(HybridAutomatonParser::GbadstateContext *ctx) override;

};

} //namespace hypro

#include "HyproBadStatesVisitor.tpp"
