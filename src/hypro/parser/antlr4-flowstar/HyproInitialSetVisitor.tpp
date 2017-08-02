#include "HyproInitialSetVisitor.h"

namespace hypro {
	
	//Constructor & Destructor
	template<typename Number>
	HyproInitialSetVisitor<Number>::HyproInitialSetVisitor(std::vector<std::string> varVec, std::set<Location<Number>*> lSet) : 
		vars(varVec),
		locSet(lSet)
	{ }

	template<typename Number>
	HyproInitialSetVisitor<Number>::~HyproInitialSetVisitor() { }

	//Inherited
	template<typename Number>
	antlrcpp::Any HyproInitialSetVisitor<Number>::visitInit(HybridAutomatonParser::InitContext *ctx){

		std::cout << "-- Bin bei visitInitial!" << std::endl;

		//0.Syntax Check - given variable name really a location name?
		//If it is, save the location pointer for the localStateMap
		bool found = false;
		Location<Number>* initialLoc;
		for(const auto& loc : locSet){
			if(ctx->initstate()->VARIABLE()->getText() == loc->getName()){
				found = true;
				initialLoc = loc;
			}
		}
		if(!found){
			std::cerr << "ERROR: Given location name in init does not exist." << std::endl;
		}

		//1.Get ConstraintSet, build State and return localStateMap
		ConstraintSet<Number> conSet = visit(ctx->initstate());
		std::cout << "---- Hab ein ConstraintSet mitgebracht!" << std::endl;
		State<Number,ConstraintSet<Number>> state;
		std::cout << "---- state deklariert" << std::endl;
		state.setLocation(initialLoc);
		std::cout << "---- location gesettet" << std::endl;
		state.setSet(conSet, 0);	//HIEEEEEEER EIN PROBLEM
		std::cout << "---- State gebaut!" << std::endl;
		locationStateMap initialState;
		initialState.insert(std::make_pair(initialLoc, state));
		return initialState;
	}

	template<typename Number>
  	antlrcpp::Any HyproInitialSetVisitor<Number>::visitInitstate(HybridAutomatonParser::InitstateContext *ctx){

  		std::cout << "-- Bin bei visitInitstate!" << std::endl;

  		//0.Check if there is a constraint for every stated variable
  		//Up to now, the idea is to count how often the variables occur in all constraints.
  		//If a variable occurs 0 times, it is missing
  		//TODO: Maybe find cheaper solution
  		std::vector<unsigned> varCount;
  		for(unsigned i=0; i < vars.size(); i++){
  			varCount.push_back(0);
  		}
  		for(auto& intexpr : ctx->intervalexpr()){
  			for(unsigned i=0; i < vars.size(); i++){
  				if(intexpr->VARIABLE()->getText() == vars[i]){
  					varCount[i]++;
  				}
  			}
  		}
  		for(auto& con : ctx->constraint()){
  			for(auto& poly : con->polynom()){
  				for(auto& t : poly->term()){
  					//if(t->VARIABLE() != NULL){
  						for(auto& v : t->VARIABLE()){
  							for(unsigned i=0; i < vars.size(); i++){
  								if(v->getText() == vars[i]){
  									varCount[i]++;
  								}
  							}
  						}	
  					//}
  				}
  			}
  		}
  		for(unsigned i=0; i < varCount.size(); i++){
  			if(varCount[i] == 0){
  				std::cerr << "ERROR: For variable " << vars[i] << " no initial constraint has been set." << std::endl;
  			}
  		}

  		//1.Iteratively call visit(ctx->constraint()) to get vector of pairs of constraint vectors and constant Numbers
		unsigned size = ctx->constraint().size() + ctx->intervalexpr().size();
		matrix_t<Number> tmpMatrix = matrix_t<Number>::Zero(size, vars.size());
		vector_t<Number> tmpVector = vector_t<Number>::Zero(size);
		unsigned i = 0;
		int rowToFill = 0;
		std::vector<std::pair<vector_t<Number>,Number>> values;
		HyproFormulaVisitor<Number> visitor(vars);
		while(i < size){

			//Choose constraints until there are no more, then choose intervalexprs
			if(i < ctx->constraint().size()){
				values = visitor.visit(ctx->constraint().at(i)).antlrcpp::Any::as<std::vector<std::pair<vector_t<Number>,Number>>>();
				//std::cout << "---- Have chosen the " << i << "-th constraint vector!" << std::endl;
			} else {
				unsigned posInIntervalExpr = i - ctx->constraint().size();
				//std::cout << "---- Have chosen the " << posInIntervalExpr << "-th intervalexpr vector!" << std::endl;
				//std::cout << "---- intervalexpr size: " << ctx->intervalexpr().size() << std::endl;
				if(posInIntervalExpr < ctx->intervalexpr().size()){
					values = visitor.visit(ctx->intervalexpr().at(posInIntervalExpr)).antlrcpp::Any::as<std::vector<std::pair<vector_t<Number>,Number>>>();					
					//std::cout << "---- intervalexpr existed!" << std::endl;					
				} else {
					std::cerr << "ERROR: There is no " << posInIntervalExpr << "-th constraint parsed!" << std::endl;
				}
			}

			//Print stuff
			//std::cout << "---- Received following constraint Vec:" << std::endl;
			//for(auto v : values){
			//	std::cout << v.first << "and \n" << v.second << "\n" << std::endl;
			//}

			//Resize tmpMatrix and tmpVector and initialise them with 0, then write values inside
			tmpMatrix.conservativeResize(tmpMatrix.rows()+values.size()-1, Eigen::NoChange_t::NoChange);
			tmpVector.conservativeResize(tmpVector.rows()+values.size()-1, Eigen::NoChange_t::NoChange);
			for(int k=rowToFill; k < tmpMatrix.rows(); k++){
				tmpMatrix.row(k) = vector_t<Number>::Zero(tmpMatrix.cols());
				tmpVector(k) = Number(0);
			}
			//std::cout << "---- Resized tmpMatrix to:\n" << tmpMatrix << std::endl;
			//std::cout << "---- Resized tmpVector to:\n" << tmpVector << std::endl;
			for(unsigned k=0; k < values.size(); k++){
				tmpMatrix.row(rowToFill+k) = values[k].first;
				tmpVector(rowToFill+k) = values[k].second;
			}

			//Increment rowToFill by our added size
			//std::cout << "---- After insertion tmpMatrix is:\n" << tmpMatrix << " and tmpVector is:\n" << tmpVector << std::endl;
			rowToFill += values.size();
			i++;
			//std::cout << "---- AFTER UPDATE size: " << size << " rowToFill: " << rowToFill << " i: " << i << std::endl;
		}

		//3.Build State and return it
		return ConstraintSet<Number>(tmpMatrix, tmpVector);
		//State<Number,ConstraintSet<Number>> state;
		//state.setSets(conSet, 0)
		//return state;

  	}
}