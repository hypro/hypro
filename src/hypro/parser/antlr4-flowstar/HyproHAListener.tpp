#include "HyproHAListener.h"

namespace hypro {

	template<typename Number>
	HyproHAListener<Number>::HyproHAListener()
		: locSet(),
		vars(),
		loc(LocationManager<Number>::create()),
		tmpMatrix(matrix_t<Number>::Zero(1,1)),
		tmpVector(vector_t<Number>::Zero(1))
	{
		std::cout << "Ich wurde gebaut!" << std::endl;
	}

	template<typename Number>
	HyproHAListener<Number>::~HyproHAListener(){ }

	template<typename Number>
	Number HyproHAListener<Number>::stringToNumber(std::string& string){
		double numInFloat = std::stod(string);
		Number numInNumber = Number(numInFloat);
		return numInNumber;
	}

	template<typename Number>
	void HyproHAListener<Number>::enterVardeclaration(HybridAutomatonParser::VardeclarationContext* ctx) {
		std::cout << "Bin bei enterVardeclaration!" << std::endl;
		for(tree::TerminalNode* variable : ctx->VARIABLE()){
			vars.push_back(variable->getText());
			//NOTE: the respective position in the vars vector is the assigned id to the variable!
			tmpMatrix = matrix_t<Number>::Zero(vars.size()+1, vars.size()+1);
		}
	}

	template<typename Number>
	void HyproHAListener<Number>::enterLocation(HybridAutomatonParser::LocationContext* ctx){
		std::cout << "Bin bei enterLocation!" << std::endl;

		//Check if no location name occurs a second time
		for(auto& location : locSet){
			if(location->getName() == ctx->VARIABLE()->getText()){
				std::cerr << "Location " << location->getName() << " has already been parsed." << std::endl;
			}
		}

		//Create an temporary location with given name
		loc = LocationManager<Number>::create(VARIABLE()->getText());
	}

	template<typename Number>
	void HyproHAListener<Number>::enterActivities(HybridAutomatonParser::ActivitiesContext* ctx){
		std::cout << "Bin bei enterActivities!" << std::endl;

		//Check if there are enough equations
		if(vars.size() != ctx->equation().size()){
			std::cerr << "Wrong amount of activites for " << loc->getName() << std::endl;
		}
	}

	template<typename Number>
	void HyproHAListener<Number>::exitActivities(HybridAutomatonParser::ActivitiesContext* ctx){
		std::cout << "Bin bei exitActivities!" << std::endl;

		//Check if last row consists of 0's entirely
		if(tmpMatrix.row(tmpMatrix.rows()-1) != vector_t<Number>::Zero(tmpMatrix.rows()-1)){
			std::cout << "Last row of tmpMatrix is:\n " << tmpMatrix.row(tmpMatrix.rows()-1) << std::endl;
			std::cerr << "Last row of tmpMatrix was not completely zero!" << std::endl;
		}	

		//Assign tmpMatrix as our flowMatrix in loc
		loc->setFlow(tmpMatrix);
	}

	template<typename Number>
	void HyproHAListener<Number>::enterEquation(HybridAutomatonParser::EquationContext* ctx){
		std::cout << "Bin bei enterEquation!" << std::endl;

		//Syntax check for the left side of an equation
		bool found = false;
		for(auto& variable : vars){
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
		if(currentRow < vars.size()){
			currentRow++;
			std::cout << "currentRow after inc is: " << currentRow << std::endl;
		} else {
			std::cout << "currentRow with " << currentRow << " is bigger or equal than var size with " << this->vars.size() << std::endl;
		}
	}

	template<typename Number>
	void HyproHAListener<Number>::enterPolynom(HybridAutomatonParser::PolynomContext* ctx){
		std::cout << "Bin bei enterTerm!" << std::endl;

		//Syntax check : if only defined variables occur
		bool allVarsFound = true;
		std::string undefinedVars;
		for(auto currTerm : ctx->term()){
			for(auto maybeVar : currTerm->VARIABLE()){
				bool found = false;
				for(auto var : vars){
					if(maybeVar->getText() == var){
						found = true;
					}
				}
				if(!found){
					undefinedVars = maybeVar->getText() + ", " + undefinedVars;
					allVarsFound = false;
				}
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
	void HyproHAListener<Number>::exitPolynom(HybridAutomatonParser::PolynomContext* ctx){

	}

	template<typename Number>
	Number HyproHAListener<Number>::multTogether(HybridAutomatonParser::TermContext* ctx){
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
		return multed;
	}

	template<typename Number>
	void HyproHAListener<Number>::enterTerm(HybridAutomatonParser::TermContext* ctx){
		std::cout << "Bin bei enterTerm!" << std::endl;
		
		//Turn 2*3*4*5*x ... into 120*x
		Number multed = multTogether(ctx);

		//No variables at all: Just put multed into matrix
		if(ctx->VARIABLE().size() == 0){
			std::cout << "currentRow is " << currentRow << " and tmpMatrix.cols() is " << tmpMatrix.cols() << std::endl;
			//(*this->rGetFillingTarget())(this->currentRow, flowMatrix.cols()-1) = multed;
			tmpMatrix(currentRow, tmpMatrix.cols()-1) = multed;
			std::cout << "tmpMatrix is now:\n" << tmpMatrix << std::endl;

		//Exactly one variable:
		} else if(ctx->VARIABLE().size() == 1){
			for(unsigned int i=0; i < this->vars.size(); i++){
				std::cout << "vars[i] is: " << vars[i] << " and ctx variable 0 is: " << ctx->VARIABLE()[0]->getText() << std::endl;
				if(vars[i] == ctx->VARIABLE()[0]->getText()){
					//(*this->rGetFillingTarget())(this->currentRow, i) = multed;
					tmpMatrix(currentRow, i) = multed;
					std::cout << "tmpMatrix is now:\n" << tmpMatrix << std::endl;
				}
			}
		} else {
			//TODO: Multiple variables in one mult, i.e. x = axy
			//IDEA: Turn x = axy = (a/2)*xy + (a/2)*xy and save for x in matrix (a/2)y and for y in matrix (a/2)x
			std::cout << "Hypro does not support multiplication of several variables in the current build." << std::endl;
		}
	}

	template<typename Number>
	void HyproHAListener<Number>::exitTerm(HybridAutomatonParser::TermContext* ctx){

	}

	template<typename Number>
	void HyproHAListener<Number>::enterInvariants(HybridAutomatonParser::InvariantsContext* ctx){
		std::cout << "Bin bei enterInvariants!" << std::endl;

		//Set tmpMatrix back to 0
		tmpMatrix = matrix_t<Number>::Zero(vars.size(), vars.size());
		tmpVector = vector_t<Number>::Zero(vars.size());

		//Set currentRow back to 0
		currentRow = 0;
	}

	template<typename Number>
	void HyproHAListener<Number>::exitInvariants(HybridAutomatonParser::InvariantsContext* ctx){
		std::cout << "Bin bei exitInvariants!" << std::endl;

		//Set tmpMatrix and tmpVector as invariant matrix 
		Condition<Number> tmpCond(tmpMatrix,tmpVector);
		loc->setInvariant(tmpCond);
	}

	//For a given polynom context, return the vector of coefficients in the order of variables pushed into vars
	//The last coefficient is a constant, so the one without a respective variable
	template<typename Number>
	vector_t<Number> HyproHAListener<Number>::getPolynomCoeff(HybridAutomatonParser::PolynomContext* ctx){
		std::cout << "Bin bei getPolynomCoeff!" << std::endl;		
		vector_t<Number> coeffVec = vector_t<Number>::Zero(vars.size()+1);
		for(auto mTerm : ctx->term()){
			Number multed = multTogether(mTerm);
			if(mTerm->VARIABLE().size() == 0){
				//put into last place of coeffVec
				coeffVec(coeffVec.rows()) = multed;
			} else if(mTerm->VARIABLE().size() == 1) {
				//put into place according to place of variable in vars	
				unsigned dest = 0;
				auto tmpVar = mTerm->VARIABLE()[0]->getText();
				for(unsigned i=0; i < vars.size(); i++){
					if(vars[i] == tmpVar){
						dest = i;
						break;
					}
				}
				coeffVec(dest) = multed;
			} else {
				std::cout << "ERROR: multiplication of several variables not allowed!" << std::endl;
			}
		}
		return coeffVec;
	}	

	template<typename Number>
	void HyproHAListener<Number>::enterConstraint(HybridAutomatonParser::ConstraintContext* ctx){
		std::cout << "Bin bei enterConstraint!" << std::endl;

		//Syntax check: Block all invariants where "<" and ">" occur
		if(ctx->BOOLRELATION()->getText() == "<" || ctx->BOOLRELATION()->getText() == ">"){
			std::cerr << "ERROR: Strict relations are not allowed in current build!";
		} 

		//Next: Form all constraints of form "polynom {<=,>=,=} polynom" to "polynom {<=,>=,=} value"
		//NOTE: value can be 0, but needn't be.
		else {
			vector_t<Number> coeffLeft = getPolynomCoeff(ctx->polynom(0));
			vector_t<Number> coeffRight = getPolynomCoeff(ctx->polynom(1));

		}

		


	}

	template<typename Number>
 	void HyproHAListener<Number>::exitConstraint(HybridAutomatonParser::ConstraintContext* ctx){
 		std::cout << "Bin bei exitConstraint!" << std::endl;

 		//Fill the tmpVector with its respective value for this row

 		//If =, copy values of that row, emplace negated version in matrix/vector and lengthen it with 0's
 		//Don't forget to increase currentRow by 2 as we added a new constraint
 		if(ctx->BOOLRELATION()->getText() == "="){
 			std::cout << "Detected =-symbol! tmpMatrix before:\n" << tmpMatrix << "tmpVector before: " << tmpVector << std::endl;
 			tmpMatrix.conservativeResize(tmpMatrix.rows()+1, Eigen::NoChange_t::NoChange);
 			tmpMatrix.row(currentRow+1) = tmpMatrix.row(currentRow) * (-1);
 			tmpVector.conservativeResize(tmpVector.rows()+1);
 			tmpVector.row(currentRow+1) = tmpVector.row(currentRow) * (-1);
 			if(currentRow+1 < tmpMatrix.rows()){
 				tmpMatrix.row(tmpMatrix.rows()) = vector_t<Number>::Zero(vars.size());
 				tmpVector.row(tmpVector.rows()) = Number(0);	
 			}
 			currentRow += 2;
 			std::cout << "tmpMatrix after: \n" << tmpMatrix << "tmpVector after:\n" << tmpVector << std::endl;
 		}

		//In exitConstraint: If >= negate the row when exitConstraint
		else if(ctx->BOOLRELATION()->getText() == ">="){
			std::cout << "Detected >=-symbol! tmpMatrix before:\n" << tmpMatrix << "tmpVector before: " << tmpVector << std::endl;
			tmpMatrix.row(currentRow) = tmpMatrix.row(currentRow) * (-1);
			tmpVector.row(currentRow) = tmpVector.row(currentRow) * (-1);
			currentRow++;
			std::cout << "tmpMatrix after: \n" << tmpMatrix << "tmpVector after:\n" << tmpVector << std::endl;
		}

		//Since <= does not change entries, this case is only if > or < were detected
		else {
			std::cout << "Detected <=, < or >" << std::endl;
			currentRow++;
			//std::cerr << "Strict relations are still not allowed in current build!";	
		}

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

  		//Add loc to locSet
  		locSet.insert(loc);

  	}

	template<typename Number>
	void HyproHAListener<Number>::exitStart(HybridAutomatonParser::StartContext* ctx){
		std::cout << "Bin bei exitStart!" << std::endl;
	}



}
