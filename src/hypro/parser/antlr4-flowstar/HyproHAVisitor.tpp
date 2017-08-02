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

		//2.Calls visit(ctx->modes()) to get locSet 
		HyproLocationVisitor<Number> locVisitor = HyproLocationVisitor<Number>(vars);
		//std::set<Location<Number>*> locSet = locVisitor.visit(ctx->modes()).antlrcpp::Any::as<std::set<Location<Number>*>>();
		std::set<Location<Number>*> locSet = locVisitor.visit(ctx->modes());
		std::cout << "-- locVisitor visited!" << std::endl;
		//std::cout << "---- locSet is now: " << locSet << std::endl;		

		//3.Later calls visit to get transitions
		HyproTransitionVisitor<Number> transVisitor = HyproTransitionVisitor<Number>(vars, locSet);
		std::set<Transition<Number>*> transSet = transVisitor.visit(ctx->jumps());
		std::cout << "-- transVisitor visited!" << std::endl;

		//4.Later calls visit to get initial states
		HyproInitialSetVisitor<Number> initVisitor = HyproInitialSetVisitor<Number>(vars, locSet);
		locationStateMap initSet = initVisitor.visit(ctx->init());
		std::cout << "-- initVisitor visited!" << std::endl;

		//Vorerst: Gib leeren HA zurück, später mit inhalt
		//return HybridAutomaton<Number>();
		return true;
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