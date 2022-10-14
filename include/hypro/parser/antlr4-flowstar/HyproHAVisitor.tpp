/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "HyproHAVisitor.h"

namespace hypro {

	template<typename Number>
	HyproHAVisitor<Number>::HyproHAVisitor() :
		vars(),
		reachSettings()
	{ }

	template<typename Number>
	HyproHAVisitor<Number>::~HyproHAVisitor(){ }

	template<typename Number>
	antlrcpp::Any HyproHAVisitor<Number>::visitStart(HybridAutomatonParser::StartContext *ctx){

		//1.Calls visit(ctx->vardeclaration()) to get vars vector
		vars = visit(ctx->vardeclaration()).template as<std::vector<std::string>>();
		std::vector<std::string>& varVec = vars;

		//2.Calls visit(ctx->setting()) to get reachability settings
		HyproSettingVisitor<Number> settingVisitor = HyproSettingVisitor<Number>(varVec);
		reachSettings = settingVisitor.visit(ctx->setting()).template as<hypro::ReachabilitySettings>();

		//3.Calls visit(ctx->modes()) to get locSet
		HyproLocationVisitor<Number> locVisitor = HyproLocationVisitor<Number>(varVec);
		std::set<Location<Number>*> locSet = locVisitor.visit(ctx->modes()).template as<std::set<Location<Number>*>>();

		//4.2.Make a set of unique ptrs to Locations
		std::vector<std::unique_ptr<Location<Number>>> uniquePtrLocSet;
		bool stochasticlocation = false;
		for(auto& l : locSet){
			StochasticLocation<Number>* stoLoc = dynamic_cast<StochasticLocation<Number>*>( l );
			if ( !stoLoc ){
				uniquePtrLocSet.emplace_back(std::unique_ptr<Location<Number>>(std::move(l)));
			} else {
				uniquePtrLocSet.emplace_back(std::unique_ptr<Location<Number>>(std::move(stoLoc)));
				stochasticlocation = true;
			}
		}
		locSet.clear();
		for(auto& l : uniquePtrLocSet){
			locSet.emplace(l.get());
		}

		//4.Calls visit to get transitions
		//NOTE: the transVisitor will modify locSet as every location has its own set of transitions that must be added here.
		HyproTransitionVisitor<Number> transVisitor = HyproTransitionVisitor<Number>(varVec, locSet);
		std::set<Transition<Location<Number>>*> tSet = transVisitor.visit(ctx->jumps()).template as<std::set<Transition<Location<Number>>*>>();

		//4.1.Make a set of unique ptrs to transitions
		for(auto t : tSet){
			assert(t != nullptr);
			for(auto& l : uniquePtrLocSet){
				assert(t != nullptr);
				if(t->getSource() == l.get()) {
					StochasticTransition<Location<Number>>* stoTrans = dynamic_cast<StochasticTransition<Location<Number>>*>( t );
					if ( !stoTrans ) {
						l->addTransition(std::move
(std::unique_ptr<Transition<Location<Number>>>(t)));
					} else {
						l->addTransition(std::move
(std::unique_ptr<StochasticTransition<Location<Number>>>( stoTrans )));
					}
					break;
				}
			}
		}

		//5.Calls visit to get all initial states
		typename HybridAutomaton<Number>::locationConditionMap initSet;
		if (!stochasticlocation ){
			//HyproInitialSetVisitor<Number> initVisitor = HyproInitialSetVisitor<Number>(varVec, rLocSet);
			HyproInitialSetVisitor<Number> initVisitor = HyproInitialSetVisitor<Number>(varVec, locSet);
			for(auto& initState : ctx->init()){
				typename HybridAutomaton<Number>::locationConditionMap oneInitialState = initVisitor.visit(initState).template as<typename HybridAutomaton<Number>::locationConditionMap>();
				//initSet.insert(oneInitialState.begin(), oneInitialState.end());
				for(auto& is : oneInitialState){
					initSet.emplace(is);
				}
			}
		} else {
			// typename StochasticHybridAutomaton<Number>::stochasticInitialMap initSet;
			//HyproInitialSetVisitor<Number> initVisitor = HyproInitialSetVisitor<Number>(varVec, rLocSet);
			HyproInitialSetVisitor<Number> initVisitor = HyproInitialSetVisitor<Number>(varVec, locSet);
			for(auto& initState : ctx->init()){
				typename StochasticHybridAutomaton<Number>::stochasticInitialMap oneInitialState = initVisitor.visit(initState).template as<typename StochasticHybridAutomaton<Number>::stochasticInitialMap>();
				//initSet.insert(oneInitialState.begin(), oneInitialState.end());
				for(auto& is : oneInitialState){
					initSet.emplace(std::make_pair(is.first,is.second.first));
				}
			}
		}

		//6.Calls visit(ctx->unsafeset()) to get local and global badStates
		typename HybridAutomaton<Number>::locationConditionMap lBadStates;
		std::vector<Condition<Number>> gBadStates;
		if(ctx->unsafeset() != NULL && (ctx->unsafeset()->lbadstate().size() > 0 || ctx->unsafeset()->gbadstate().size() > 0)){
			HyproBadStatesVisitor<Number> bStateVisitor = HyproBadStatesVisitor<Number>(varVec, locSet);
			lBadStates = bStateVisitor.visit(ctx->unsafeset()).template as<typename HybridAutomaton<Number>::locationConditionMap>();
			gBadStates = bStateVisitor.getGlobalBadStates();
		}

		//7.Build HybridAutomaton, return it
		HybridAutomaton<Number> ha;
		ha.setLocations(std::move(uniquePtrLocSet));
		//ha.setTransitions(std::move(transSet));
		ha.setInitialStates(initSet);
		ha.setLocalBadStates(lBadStates);
		ha.setGlobalBadStates(gBadStates);
                ha.setVariables(varVec);

		return ha;			//Move the ownership of ha to whoever uses ha then, i.e. the test suite
	}

	template<typename Number>
	antlrcpp::Any HyproHAVisitor<Number>::visitVardeclaration(HybridAutomatonParser::VardeclarationContext *ctx){

		//Get variable names and push them into vars vector
		std::vector<std::string> varVec;
		for(tree::TerminalNode* variable : ctx->VARIABLE()){
			//NOTE: the respective position in the vars vector is the assigned id to the variable!
			varVec.push_back(variable->getText());
			// add variable entry to variable pool
			VariablePool::getInstance().newCarlVariable(variable->getText(), varVec.size() - 1);
		}
		if(varVec.size() == 0){
			std::cerr << "ERROR: No variables were defined" << std::endl;
			exit(0);
		}
		return varVec;
	}

}
