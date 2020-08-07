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

		//4.2.Make a set of unique ptrs to Locations
		std::vector<std::unique_ptr<Location<Number>>> uniquePtrLocSet;
		for(auto& l : locSet){
			uniquePtrLocSet.emplace_back(std::unique_ptr<Location<Number>>(std::move(l)));
		}
		locSet.clear();
		for(auto& l : uniquePtrLocSet){
			locSet.emplace(l.get());
		}

		//4.Calls visit to get transitions
		//NOTE: the transVisitor will modify locSet as every location has its own set of transitions that must be added here.
		HyproTransitionVisitor<Number> transVisitor = HyproTransitionVisitor<Number>(varVec, locSet);
		std::set<Transition<Number>*> tSet = transVisitor.visit(ctx->jumps()).template as<std::set<Transition<Number>*>>();

		//4.1.Make a set of unique ptrs to transitions
		for(auto t : tSet){
			assert(t != nullptr);
			//std::cout << "Transition from " << t->getSource() << "("<< t->getSource()->getName() << ")" << " to " << t->getTarget() << "(" << t->getTarget()->getName() << ")"<< std::endl;
			//std::cout << "Reset is " << t->getReset() << std::endl;
			for(auto& l : uniquePtrLocSet){
				//std::cout << "Location raw: " << l.get() <<  "(" << l->getName() << ")" << std::endl;
				assert(t != nullptr);
				if(t->getSource() == l.get()) {
					l->addTransition(std::move(std::make_unique<Transition<Number>>(*t)));
					//std::cout << "Added." << std::endl;
					break;
				}
			}
		}

		//5.Calls visit to get all initial states
		typename HybridAutomaton<Number>::locationConditionMap initSet;
		//HyproInitialSetVisitor<Number> initVisitor = HyproInitialSetVisitor<Number>(varVec, rLocSet);
		HyproInitialSetVisitor<Number> initVisitor = HyproInitialSetVisitor<Number>(varVec, locSet);
		for(auto& initState : ctx->init()){
			typename HybridAutomaton<Number>::locationConditionMap oneInitialState = initVisitor.visit(initState).template as<typename HybridAutomaton<Number>::locationConditionMap>();
			//initSet.insert(oneInitialState.begin(), oneInitialState.end());
			for(auto& is : oneInitialState){
				initSet.emplace(is);
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

#ifdef HYPRO_LOGGING
		COUT("================================\n");
		COUT("From the parser\n");
		COUT("================================\n");
		COUT("Parsed variables: " << vars << std::endl);
		COUT("Reachability settings:\n" << reachSettings);
		COUT("All locations:\n");COUT("Size:"); COUT(locSet.size());
		for(auto it = locSet.begin(); it != locSet.end(); ++it){
			COUT(**it);
		}
		//COUT("All Transitions:\n");
		//for(auto it = transSet.begin(); it != transSet.end(); ++it){
		//	COUT(**it);
		//}
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
			VariablePool::getInstance().carlVarByIndex(varVec.size() - 1);
		}
		if(varVec.size() == 0){
			std::cerr << "ERROR: No variables were defined" << std::endl;
			exit(0);
		}
		return varVec;
	}

}
