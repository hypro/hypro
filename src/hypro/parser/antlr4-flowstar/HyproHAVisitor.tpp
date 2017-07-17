#include "HyproHAVisitor.h"

namespace hypro {

	template<typename Number>
	HyproHAVisitor<Number>::HyproHAVisitor(){ }

	template<typename Number>
	HyproHAVisitor<Number>::~HyproHAVisitor(){ }

	template<typename Number>
	Number HyproHAVisitor<Number>::stringToNumber(std::string& string){
		double numInFloat = std::stod(string);
		Number numInNumber = Number(numInFloat);
		return numInNumber;
	}

	template<typename Number>
	Number HyproHAVisitor<Number>::multTogether(HybridAutomatonParser::TermContext* ctx){
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

	//For a given polynom context, return the vector of coefficients in the order of variables pushed into vars
	//The last coefficient is a constant, so the one without a respective variable
	template<typename Number>
	vector_t<Number> HyproHAVisitor<Number>::getPolynomCoeff(HybridAutomatonParser::PolynomContext* ctx){
/*		std::cout << "Bin bei getPolynomCoeff!" << std::endl;		
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
*/		vector_t<Number> coeffVec;
		return coeffVec;
	}

	template<typename Number>
	antlrcpp::Any HyproHAVisitor<Number>::visitStart(HybridAutomatonParser::StartContext *ctx){
		std::cout << "-- Bin bei visitStart!" << std::endl;
		//return visitChildren(ctx);
		return visit(ctx->vardeclaration());

		//1.Calls visit(ctx->vardeclaration()) to get vars vector 
		//2.Calls visit(ctx->modes()) to get locSet 
		//3.Later calls visit to get transitions
		//4.Later calls visit to get initial states
		//returns HybridAutomaton
	}

	template<typename Number>
	antlrcpp::Any HyproHAVisitor<Number>::visitVardeclaration(HybridAutomatonParser::VardeclarationContext *ctx){
		std::cout << "-- Bin bei visitVardeclaration!" << std::endl;

		//Get variable names and push them into vars
		for(tree::TerminalNode* variable : ctx->VARIABLE()){
			//vars.push_back(variable->getText());
			//NOTE: the respective position in the vars vector is the assigned id to the variable!
			//matrix_t<Number>tmpMatrix = matrix_t<Number>::Zero(vars.size()+1, vars.size()+1);
		}
		return true;

		//1.Makes a vars vector and puts all variable names in it
		//2.Returns vars
	}

	template<typename Number>
	antlrcpp::Any HyproHAVisitor<Number>::visitModes(HybridAutomatonParser::ModesContext *ctx){
		std::cout << "-- Bin bei visitModes!" << std::endl;

		//1.Calls visit(ctx->location()) to get location
		//2.Puts location into locSet
		//3.Returns locSet

	}

	template<typename Number>
	antlrcpp::Any HyproHAVisitor<Number>::visitLocation(HybridAutomatonParser::LocationContext *ctx){
		//0.Syntax check - Location name already parsed? 
		//1.Calls visit(ctx->activities()) to get matrix
		//2.Calls visit(ctx->invariant()) to get Condition
		//3.Returns a location
	}

	template<typename Number>
	antlrcpp::Any HyproHAVisitor<Number>::visitActivities(HybridAutomatonParser::ActivitiesContext *ctx){
		//0.Syntax check - Are there vars.size() equations?
		//1.Calls iteratively visit(ctx->equation()) to get vector, store them
		//2.Put all vectors together to a matrix
		//3.Syntax check - Last row completely 0's?
		//4.Returns a matrix
	}

	template<typename Number>
	antlrcpp::Any HyproHAVisitor<Number>::visitEquation(HybridAutomatonParser::EquationContext *ctx){
		//0.Syntax Check - Left side of equation legal?
		//1.Call visit(ctx->polynom()) to get vector
		//2.Return vector
	}

	template<typename Number>
	antlrcpp::Any HyproHAVisitor<Number>::visitPolynom(HybridAutomatonParser::PolynomContext *ctx){
		//0.Syntax Check - Only legal variables in polynom?
		//1.1: If equation called then call visit Term to fill vector of length vars.size()+1
		//1.2: If constraint called then call visit Term / getPolynomCoeff to fill vector of length vars.size()
		//2.Return Vector
	}

	template<typename Number>
	antlrcpp::Any HyproHAVisitor<Number>::visitTerm(HybridAutomatonParser::TermContext *ctx){
		//1.Mult numbers into one number
		//2.Put number into the corresponding place in vector
		//3.Return vector
	}

	template<typename Number>
	antlrcpp::Any HyproHAVisitor<Number>::visitInvariants(HybridAutomatonParser::InvariantsContext *ctx){
		//0.Syntax Check - < or > not allowed
		//1.Iteratively call visit(ctx->constraint()) to get vector of constraint vectors
		//2.Iteratively call visit(ctx->intervalexpr()) to get vector of constraint vectors
		//3.Build condition out of them
		//4.Return condition
	}

	template<typename Number>
	antlrcpp::Any HyproHAVisitor<Number>::visitConstraint(HybridAutomatonParser::ConstraintContext *ctx){
		//1.Call visit(ctx->polynom()) for both sides to get 2 vectors
		//2.Use them to calculate constraint vector
		//3.Return a vector of constraint vectors!
	}

	template<typename Number>
	antlrcpp::Any HyproHAVisitor<Number>::visitIntervalexpr(HybridAutomatonParser::IntervalexprContext *ctx){
		//0.Syntax Check - Check if interval is legal
		//1.Make constraint vectors
		//2.Return vector of constraint vectors!
	}

}