#include "HyproHAListener.h"

namespace hypro {

	template<typename Number>
	HyproHAListener<Number>::HyproHAListener(){
		locSet = std::set<Location<Number>*>();
		loc = Location<Number>(0);
		vars = std::vector<std::string>();
	}

	template<typename Number>
	HyproHAListener<Number>::~HyproHAListener(){ }

	template<typename Number>
	void HyproHAListener<Number>::enterVardeclaration(HybridAutomatonParser::VardeclarationContext* ctx) { 
		for(tree::TerminalNode* variable : ctx->VARIABLE()){
			this.vars.push_back(variable->getText());
		}
	}

	template<typename Number>
	void HyproHAListener<Number>::enterLocation(HybridAutomatonParser::LocationContext* ctx){
		//Check if no location name occurs a second time
		for(std::string name : this.locNames){
			if(name == ctx->VARIABLE()->getText()){
				std::cerr << "Location " << name << " has already been parsed." << std::endl;
			}
		}
	}

	template<typename Number>
	void HyproHAListener<Number>::enterActivities(HybridAutomatonParser::ActivitiesContext* ctx){
		//Check if there are enough equations
		if(this.vars.size() != ctx->equation().size()){
			std::cerr << "Wrong amount of activites for " << this.locNames.last() << std::endl;
		}
	}
	
	template<typename Number>
	void HyproHAListener<Number>::enterEquation(HybridAutomatonParser::EquationContext* ctx){
		
		//Syntax check
		bool found = false;
		for(auto variable : this.vars){
			if((variable + "'") == ctx->VARIABLE()->getText()){
				found = true;
			}
		}
		if(!found){
			//auto actualEquationInNodes = ctx->ParserRuleContext::getRuleContexts();
			//std::string actualEquation;			
			//for(auto part : actualEquationInNodes){
			//	actualEquation.append(part->getText());
			//}
			//std::cerr << "Left side of " << actualEquation << " has no respective variable." << std::endl;
			std::cerr << "An equation has a not defined variable." << std::endl;
		}

	}

	template<typename Number>
	void HyproHAListener<Number>::enterTerm(HybridAutomatonParser::TermContext* ctx){

		//Syntax check
		bool found = false;
		for(auto var : this.vars){
			for(auto ctxVar : ctx->VARIABLE()){
				if(var == ctxVar->getText()){
					found = true;
				}
			}
			if(!found){
				std::cerr << "In a term a variable occurred that was not defined before." << std::endl;
			}	
		}

	}

	template<typename Number>
	void HyproHAListener<Number>::exitEquation(HybridAutomatonParser::EquationContext* ctx){
		
	}

	template<typename Number>
	void HyproHAListener<Number>::enterInvariants(HybridAutomatonParser::InvariantsContext* ctx){
		
	}

	template<typename Number>
	void HyproHAListener<Number>::exitInvariants(HybridAutomatonParser::InvariantsContext* ctx){
		
	}

	template<typename Number>
	void HyproHAListener<Number>::enterBoolexpr(HybridAutomatonParser::BoolexprContext* ctx){
		
	}

	template<typename Number>
 	void HyproHAListener<Number>::exitBoolexpr(HybridAutomatonParser::BoolexprContext* ctx){
 		
 	}

 	template<typename Number>
  	void HyproHAListener<Number>::enterIntervalexpr(HybridAutomatonParser::IntervalexprContext* ctx){
  		
  	}

  	template<typename Number>
  	void HyproHAListener<Number>::exitIntervalexpr(HybridAutomatonParser::IntervalexprContext* ctx){
  		
  	}

  	template<typename Number>
  	void HyproHAListener<Number>::exitLocation(HybridAutomatonParser::LocationContext* ctx){
  		
  	}
	
	template<typename Number>
	void HyproHAListener<Number>::exitStart(HybridAutomatonParser::StartContext* ctx){
		
	} 



}