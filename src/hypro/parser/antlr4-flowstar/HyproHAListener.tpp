#include "HyproHAListener.h"

namespace hypro {

	template<typename Number>
	HyproHAListener<Number>::HyproHAListener(){
		locSet = std::set<Location<Number>*>();
		//loc = Location<Number>(0);
		vars = std::vector<std::string>();
		locNames = std::vector<std::string>();
		flowMatrix = matrix_t<Number>::Zero(1,1);
		//invMatrix = matrix_t<Number>::Zero(1,1);
		inv.vec = vector_t<Number>::Zero(1);
		inv.mat = matrix_t<Number>::Zero(1,1);
		fillingTarget = std::make_shared<matrix_t<Number>>(flowMatrix);
		std::cout << "Ich wurde gebaut!" << std::endl;
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
		std::cout << "Bin bei enterVardeclaration!" << std::endl;
		for(tree::TerminalNode* variable : ctx->VARIABLE()){
			this->vars.push_back(variable->getText());
			//NOTE: the respective position in the vars vector is the assigned id to the variable!
			this->flowMatrix = matrix_t<Number>::Zero(this->vars.size()+1, this->vars.size()+1);
		}
	}

	template<typename Number>
	void HyproHAListener<Number>::enterLocation(HybridAutomatonParser::LocationContext* ctx){
		std::cout << "Bin bei enterLocation!" << std::endl;
		//Check if no location name occurs a second time
		for(auto& name : this->locNames){
			if(name == ctx->VARIABLE()->getText()){
				std::cerr << "Location " << name << " has already been parsed." << std::endl;
			}
		}
	}

	template<typename Number>
	void HyproHAListener<Number>::enterActivities(HybridAutomatonParser::ActivitiesContext* ctx){
		std::cout << "Bin bei enterActivities!" << std::endl;
		//Check if there are enough equations
		if(this->vars.size() != ctx->equation().size()){
			std::cerr << "Wrong amount of activites for " << this->locNames.back() << std::endl;
		}
		//Since we are in activities, we will only fill the flow matrix. Set the filling target accordingly
		this->setFillingTarget(this->flowMatrix);
	}
	
	template<typename Number>
	void HyproHAListener<Number>::enterEquation(HybridAutomatonParser::EquationContext* ctx){
		std::cout << "Bin bei enterEquation!" << std::endl;
		//Syntax check
		bool found = false;
		for(auto& variable : this->vars){
			if((variable + "'") == ctx->VARIABLE()->getText()){
				found = true;
			}
		}
		if(!found){
			std::cerr << "An equation has a not defined variable." << std::endl;
		}
	}

	template<typename Number>
	void HyproHAListener<Number>::exitEquation(HybridAutomatonParser::EquationContext* ctx){
		//Update which row in the matrix we are in
		if(this->currentRow < this->vars.size()){
			this->currentRow++;
			std::cout << "currentRow after inc is: " << currentRow << std::endl;
		} else {
			std::cout << "currentRow with " << this->currentRow << " is bigger or equal than var size with " << this->vars.size() << std::endl;
		}	
	}

	template<typename Number>
	void HyproHAListener<Number>::enterTerm(HybridAutomatonParser::TermContext* ctx){
		//Syntax check : if only defined variables occur
		//adding terms will be checked implicitly as every add contains a term
		std::cout << "Bin bei enterTerm!" << std::endl;
		bool allVarsFound = true;
		std::string undefinedVars;
		for(auto maybeVar : ctx->mult()->VARIABLE()){
			bool found = false;
			for(auto var : this->vars){
				if(maybeVar->getText() == var){
					found = true;
				}
			}
			if(!found){
				undefinedVars = maybeVar->getText() + ", " + undefinedVars; 
				allVarsFound = false;
			}
		}
		if(!allVarsFound){
			// TODO: FIND OUT HOW TO GET COMPLETE CONTEXT
			//auto ctxContexts = ctx->getRuleContexts();
			//std::string ctxString;
			//for(auto token : *ctxContexts){
			//	ctxString = ctxString + token->getText();
			//}
			std::cerr << "Following variables were undefined in a term " << ": " << undefinedVars << std::endl;
		}
	}

	template<typename Number>
	void HyproHAListener<Number>::enterMult(HybridAutomatonParser::MultContext* ctx){
		std::cout << "Bin bei enterMult!" << std::endl;
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
		std::cout << "Multiplied constants to " << multed << std::endl;
		
		if(ctx->VARIABLE().size() == 0){
			//No variables at all: Just put multed into matrix
			std::cout << "currentRow is " << currentRow << " and flowMatrix.cols() is " << flowMatrix.cols() << std::endl;
			this->getFillingTarget(this->currentRow, flowMatrix.cols()-1) = multed;
			std::cout << "flowMatrix is now:\n" << flowMatrix << std::endl;
		} else if(ctx->VARIABLE().size() == 1){
			//Exactly one variable: 
			for(unsigned int i=0; i < this->vars.size(); i++){
				std::cout << "vars[i] is: " << vars[i] << " and ctx variable 0 is: " << ctx->VARIABLE()[0]->getText() << std::endl;
				if(vars[i] == ctx->VARIABLE()[0]->getText()){
					this->getFillingTarget(this->currentRow, i) = multed;	
					std::cout << "flowMatrix is now:\n" << flowMatrix << std::endl;
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
	void HyproHAListener<Number>::enterInvariants(HybridAutomatonParser::InvariantsContext* ctx){
		std::cout << "Bin bei enterInvariants!" << std::endl;	
		this->setFillingTarget(this->inv.getMatrix());
	}

	template<typename Number>
	void HyproHAListener<Number>::exitInvariants(HybridAutomatonParser::InvariantsContext* ctx){
		std::cout << "Bin bei exitInvariants!" << std::endl;		
	}

	template<typename Number>
	void HyproHAListener<Number>::enterBoolexpr(HybridAutomatonParser::BoolexprContext* ctx){
		std::cout << "Bin bei enterBoolexpr!" << std::endl;

		//Syntax check: Block all invariants where "<" and ">" occur
		if(ctx->BOOLRELATION()->getText() == "<" || ctx->BOOLRELATION()->getText() == ">"){
			std::cerr << "Strict relations are not allowed in current build!"
		}
		//Else: Convert equation to a form such that its relation is always "<=" and then put into matrix
		if(ctx->BOOLRELATION()->getText() == "<="){
			
		}


	}

	template<typename Number>
 	void HyproHAListener<Number>::exitBoolexpr(HybridAutomatonParser::BoolexprContext* ctx){
 		std::cout << "Bin bei exitBoolexpr!" << std::endl;	
 	}

 	template<typename Number>
  	void HyproHAListener<Number>::enterIntervalexpr(HybridAutomatonParser::IntervalexprContext* ctx){
  		
  	}

  	template<typename Number>
  	void HyproHAListener<Number>::exitIntervalexpr(HybridAutomatonParser::IntervalexprContext* ctx){
  		
  	}

  	template<typename Number>
  	void HyproHAListener<Number>::exitLocation(HybridAutomatonParser::LocationContext* ctx){
  		std::cout << "Bin bei exitLocation!" << std::endl;
  	}
	
	template<typename Number>
	void HyproHAListener<Number>::exitStart(HybridAutomatonParser::StartContext* ctx){
		std::cout << "Bin bei exitStart!" << std::endl;
	} 



}