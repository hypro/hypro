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

		//4.Calls visit to get transitions
		//NOTE: the transVisitor will modify locSet as every location has its own set of transitions that must be added here.
		HyproTransitionVisitor<Number> transVisitor = HyproTransitionVisitor<Number>(varVec, rLocSet);
		std::set<Transition<Number>*> transSet = transVisitor.visit(ctx->jumps()).template as<std::set<Transition<Number>*>>();

		//5.Calls visit to get all initial states
		typename hypro::HybridAutomaton<Number>::locationStateMap initSet;
		HyproInitialSetVisitor<Number> initVisitor = HyproInitialSetVisitor<Number>(varVec, rLocSet);
		for(auto& initState : ctx->init()){
			typename hypro::HybridAutomaton<Number>::locationStateMap oneInitialState = initVisitor.visit(initState).template as<typename hypro::HybridAutomaton<Number>::locationStateMap>();
			initSet.insert(oneInitialState.begin(), oneInitialState.end());
		}

		//6.Calls visit(ctx->unsafeset()) to get local badStates
		typename hypro::HybridAutomaton<Number>::locationConditionMap lBadStates;
		std::vector<Condition<Number>> gBadStates;
		if(ctx->unsafeset() != NULL && (ctx->unsafeset()->lbadstate().size() > 0 || ctx->unsafeset()->gbadstate().size() > 0)){
			//std::cout << "-- size of badstates: " << ctx->unsafeset()->badstate().size() << std::endl;
			HyproBadStatesVisitor<Number> bStateVisitor = HyproBadStatesVisitor<Number>(varVec, rLocSet);
			lBadStates = bStateVisitor.visit(ctx->unsafeset()).template as<typename hypro::HybridAutomaton<Number>::locationConditionMap>();
			gBadStates = bStateVisitor.getGlobalBadStates();
		}

#ifdef HYPRO_LOGGING
		COUT("================================\n");
		COUT("From the parser\n");	
		COUT("================================\n");	
		COUT("Parsed variables: " << vars << std::endl);
		COUT("Reachability settings:\n" << reachSettings);
		COUT("All locations:\n");
		for(auto it = rLocSet.begin(); it != rLocSet.end(); ++it){
			COUT(**it);
		}
		COUT("All Transitions:\n");
		for(auto it = transSet.begin(); it != transSet.end(); ++it){
			COUT(**it);
		}
		COUT("Initial state:\n");
		for(auto it = initSet.begin(); it != initSet.end(); ++it){
			COUT("Initial Location: " << it->first->getName() << " and initial state: " << it->second);
		}
		COUT("Local Bad states:\n");
		for(auto it = lBadStates.begin(); it != lBadStates.end(); ++it){
			COUT("Bad Location: " << it->first->getName() << " and bad state: " << it->second);
		}
		COUT("Global Bad states:\n");
		for(const auto& g : gBadStates){
			COUT("Global Bad condition: " << g);
		}
		
#endif
		//7.Build HybridAutomaton, return it
		HybridAutomaton<Number> ha;
		ha.setLocations(locSet);
		ha.setTransitions(transSet);
		ha.setInitialStates(initSet);
		ha.setLocalBadStates(lBadStates);
		ha.setGlobalBadStates(gBadStates);

		return std::move(ha);			//Move the ownership of ha to whoever uses ha then, i.e. the test suite
	}

	template<typename Number>
	antlrcpp::Any HyproHAVisitor<Number>::visitVardeclaration(HybridAutomatonParser::VardeclarationContext *ctx){

		//Get variable names and push them into vars vector
		std::vector<std::string> varVec;
		for(tree::TerminalNode* variable : ctx->VARIABLE()){
			//NOTE: the respective position in the vars vector is the assigned id to the variable!
			varVec.push_back(variable->getText());
		}
		if(varVec.size() == 0){
			std::cerr << "ERROR: No variables were defined" << std::endl;
			exit(0);
		}
		return varVec;
	}

}
