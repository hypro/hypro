#include "HyproHAVisitor.h"

namespace hypro {

	template<typename Number>
	HyproHAVisitor<Number>::HyproHAVisitor() :
		vars()
	{ }

	template<typename Number>
	HyproHAVisitor<Number>::~HyproHAVisitor(){ }

	template<typename Number>
	antlrcpp::Any HyproHAVisitor<Number>::visitStart(HybridAutomatonParser::StartContext *ctx){
		std::cout << "-- Bin bei visitStart!" << std::endl;

		//1.Calls visit(ctx->vardeclaration()) to get vars vector 
		vars = visit(ctx->vardeclaration()).antlrcpp::Any::as<std::vector<std::string>>();
		std::cout << "---- vars is now: " << vars << std::endl;
		std::vector<std::string>& varVec = vars;

		//2.Calls visit(ctx->setting()) to get reachability settings
		//.antlrcpp::Any::as<ReachabilitySettings<Number>>();
		HyproSettingVisitor<Number> settingVisitor = HyproSettingVisitor<Number>(varVec);
		ReachabilitySettings<Number> rSettings = settingVisitor.visit(ctx->setting());
		std::cout << "---- rSettings is now: " << rSettings << std::endl;

		//3.Calls visit(ctx->modes()) to get locSet 
		HyproLocationVisitor<Number> locVisitor = HyproLocationVisitor<Number>(varVec);
		std::set<Location<Number>*> locSet = locVisitor.visit(ctx->modes()).antlrcpp::Any::as<std::set<Location<Number>*>>();
		std::cout << "-- locVisitor visited!" << std::endl;
		std::set<Location<Number>*>& rLocSet = locSet;
		//std::cout << "---- locSet is now: " << locSet << std::endl;		

		//4.Later calls visit to get transitions
		HyproTransitionVisitor<Number> transVisitor = HyproTransitionVisitor<Number>(varVec, rLocSet);
		std::set<Transition<Number>*> transSet = transVisitor.visit(ctx->jumps()).antlrcpp::Any::as<std::set<Transition<Number>*>>();
		std::cout << "-- transVisitor visited!" << std::endl;

		//5.Later calls visit to get initial states
		HyproInitialSetVisitor<Number> initVisitor = HyproInitialSetVisitor<Number>(varVec, rLocSet);
		locationStateMap initSet = initVisitor.visit(ctx->init()).antlrcpp::Any::as<locationStateMap>();
		std::cout << "-- initVisitor visited!" << std::endl;

		//6.Build HybridAutomaton, return it
		HybridAutomaton<Number> ha;
		ha.setLocations(locSet);
		ha.setTransitions(transSet);
		ha.setInitialStates(initSet);
		return std::move(ha);			//Move the ownership of ha to whoever uses ha then, i.e. the test suite
	}

	template<typename Number>
	antlrcpp::Any HyproHAVisitor<Number>::visitVardeclaration(HybridAutomatonParser::VardeclarationContext *ctx){
		std::cout << "-- Bin bei visitVardeclaration!" << std::endl;

		//Get variable names and push them into vars vector
		std::vector<std::string> varVec;
		for(tree::TerminalNode* variable : ctx->VARIABLE()){
			//NOTE: the respective position in the vars vector is the assigned id to the variable!
			varVec.push_back(variable->getText());
			//matrix_t<Number>tmpMatrix = matrix_t<Number>::Zero(vars.size()+1, vars.size()+1);
		}
		if(varVec.size() == 0){
			std::cout << "ERROR: No variables were defined" << std::endl;
		}
		return varVec;
	}

}