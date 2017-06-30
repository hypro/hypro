#include "HyproHAListener.h"

namespace hypro {

	template<typename Number>
	HyproHAListener<Number>::HyproHAListener(){
		locSet = std::set<Location<Number>*>();
		//loc = Location<Number>(0);
		vars = std::vector<std::string>();
		locNames = std::vector<std::string>();
		flowMatrix = matrix_t<Number>(1,1);
	}

	template<typename Number>
	HyproHAListener<Number>::~HyproHAListener(){ }

	template<typename Number>
	Number HyproHAListener<Number>::stringToNumber(std::string string){
		float numInFloat = std::stof(string);
		Number numInNumber = Number(numInFloat);
		return numInNumber;
	}

	template<typename Number>
	void HyproHAListener<Number>::enterVardeclaration(HybridAutomatonParser::VardeclarationContext* ctx) { 
		for(tree::TerminalNode* variable : ctx->VARIABLE()){
			this->vars.push_back(variable->getText());
			//NOTE: the respective position in the vars vector is the assigned id to the variable!
			this->flowMatrix = matrix_t<Number>(this->vars.size(), this->vars.size());
		}
	}

	template<typename Number>
	void HyproHAListener<Number>::enterLocation(HybridAutomatonParser::LocationContext* ctx){
		//Check if no location name occurs a second time
		for(auto& name : this->locNames){
			if(name == ctx->VARIABLE()->getText()){
				std::cerr << "Location " << name << " has already been parsed." << std::endl;
			}
		}
	}

	template<typename Number>
	void HyproHAListener<Number>::enterActivities(HybridAutomatonParser::ActivitiesContext* ctx){
		//Check if there are enough equations
		if(this->vars.size() != ctx->equation().size()){
			std::cerr << "Wrong amount of activites for " << this->locNames.back() << std::endl;
		}
	}
	
	template<typename Number>
	void HyproHAListener<Number>::enterEquation(HybridAutomatonParser::EquationContext* ctx){
		
		//Syntax check
		bool found = false;
		for(auto& variable : this->vars){
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

		//Update which row in the matrix we are in
		if(currentRow < this->vars.size()){
			currentRow++;
			std::cout << "currentRow after inc is: " << currentRow << std::endl;
		}
	}

	template<typename Number>
	void HyproHAListener<Number>::enterTerm(HybridAutomatonParser::TermContext* ctx){
		//Syntax check maybe: if only defined variables occur
	}

	template<typename Number>
	void HyproHAListener<Number>::enterMult(HybridAutomatonParser::MultContext* ctx){
		
		//Turn 2*3*4*5*x ... into 120*x
		Number multed = 1;
		if(ctx->NUMBER().size() > 1){
			for(auto ctxNum : ctx->NUMBER()){
				std::string num = ctxNum->getText();
				Number numInNumber = this->stringToNumber(num);
				multed = multed * numInNumber;
			}	
		} else if(ctx->NUMBER().size() == 1){
			std::string num = ctx->NUMBER()[0]->getText();
			multed = this->stringToNumber(num);
		}
		
		if(ctx->VARIABLE().size() == 0){
			//No variables at all: Just put multed into matrix
			flowMatrix(currentRow, flowMatrix.cols()) = multed;
		} else if(ctx->VARIABLE().size() == 1){
			//Exactly one variable: 
			for(unsigned int i=0; i < this->vars.size(); i++){
				if(vars[i] == ctx->VARIABLE()[0]->getText()){
					flowMatrix(currentRow, i) = multed;	
				}
			}
		} else {
			//TODO: Multiple variables in one mult, i.e. x = axy
			//IDEA: Turn x = axy = (a/2)*xy + (a/2)*xy and save for x in matrix (a/2)y and for y in matrix (a/2)x
			std::cout << "blub" << std::endl;
		}
	}

	template<typename Number>
	void HyproHAListener<Number>::exitTerm(HybridAutomatonParser::TermContext* ctx){

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