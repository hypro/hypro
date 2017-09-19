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
		reachSettings = settingVisitor.visit(ctx->setting());
		
		//3.Calls visit(ctx->modes()) to get locSet
		HyproLocationVisitor<Number> locVisitor = HyproLocationVisitor<Number>(varVec);
		std::set<Location<Number>*> locSet = locVisitor.visit(ctx->modes()).template as<std::set<Location<Number>*>>();
		std::set<Location<Number>*>& rLocSet = locSet;

		//4.Later calls visit to get transitions
		//NOTE: the transVisitor will modify locSet as every location has its own set of transitions that must be added here.
		HyproTransitionVisitor<Number> transVisitor = HyproTransitionVisitor<Number>(varVec, rLocSet);
		std::set<Transition<Number>*> transSet = transVisitor.visit(ctx->jumps()).template as<std::set<Transition<Number>*>>();

		//5.Later calls visit to get initial states
		HyproInitialSetVisitor<Number> initVisitor = HyproInitialSetVisitor<Number>(varVec, rLocSet);
		locationStateMap initSet = initVisitor.visit(ctx->init()).template as<locationStateMap>();

		//6.Calls visit(ctx->unsafeset()) to get local badStates
		locationConditionMap badStates;
		if(ctx->unsafeset() != NULL && ctx->unsafeset()->badstate().size() > 1){
			std::cout << "---- badstate size: " << ctx->unsafeset()->badstate().size() << std::endl;
			std::cout << "---- badstate content: " << ctx->unsafeset()->badstate()[0]->getText() << std::endl;
			HyproBadStatesVisitor<Number> bStateVisitor = HyproBadStatesVisitor<Number>(varVec, rLocSet);
			badStates = bStateVisitor.visit(ctx->unsafeset()).template as<locationConditionMap>();	
		}

#ifdef HYPRO_LOGGING
		TRACE("hypro.parser","Parsed variables: " << vars);
		TRACE("hypro.parser","Reachability settings: " << reachSettings)
		//TODO: Print all the other parsed stuff
#endif

		//7.Build HybridAutomaton, return it
		HybridAutomaton<Number> ha;
		ha.setLocations(locSet);
		ha.setTransitions(transSet);
		ha.setInitialStates(initSet);
		if(ctx->unsafeset() != NULL && ctx->unsafeset()->badstate().size() > 1){
			ha.setLocalBadStates(badStates);
		}
		return std::move(ha);			//Move the ownership of ha to whoever uses ha then, i.e. the test suite
	}

	template<typename Number>
	antlrcpp::Any HyproHAVisitor<Number>::visitVardeclaration(HybridAutomatonParser::VardeclarationContext *ctx){

		//Get variable names and push them into vars vector
		std::vector<std::string> varVec;
		for(tree::TerminalNode* variable : ctx->VARIABLE()){
			//NOTE: the respective position in the vars vector is the assigned id to the variable!
			varVec.push_back(variable->getText());
			//matrix_t<Number>tmpMatrix = matrix_t<Number>::Zero(vars.size()+1, vars.size()+1);
		}
		if(varVec.size() == 0){
			std::cout << "ERROR: No variables were defined" << std::endl;
			exit(0);
		}
		return varVec;
	}

}
