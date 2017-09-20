#include "HyproBadStatesVisitor.h"

namespace hypro {

	//Constructor & Destructor
	template<typename Number>
	HyproBadStatesVisitor<Number>::HyproBadStatesVisitor(std::vector<std::string>& varVec, std::set<Location<Number>*>& lSet) :
		vars(varVec),
		locSet(lSet)
	{ }
	
	template<typename Number>
	HyproBadStatesVisitor<Number>::~HyproBadStatesVisitor() { }

	//Inherited from HybridAutomatonBaseVisitor	
	template<typename Number>
	antlrcpp::Any HyproBadStatesVisitor<Number>::visitUnsafeset(HybridAutomatonParser::UnsafesetContext *ctx){

		std::cout << "-- Bin bei visitUnsafeset!" << std::endl;

		//1.Collect badState information. NOTE: There can be multiple denoted badstates for one location.
		locationConditionMap lcMap;
		if(ctx->badstate().size() > 0){
			for(auto& bState : ctx->badstate()){	
				if(bState->constrset() != NULL && bState->constrset()->getText() != ""){
					std::pair<Location<Number>*,Condition<Number>> badStateInfo = visit(bState).template as<std::pair<Location<Number>*,Condition<Number>>>();
					lcMap.insert(badStateInfo);
					//std::cout << "-- bad state location:\n" << *(badStateInfo.first) << "and condition matrix:\n" << badStateInfo.second.getMatrix() << "and vector:\n" << badStateInfo.second.getVector() << std::endl;
				//} else {
					//std::cout << "---- constrset does not exist!" << std::endl;	
				}
			}	
		}
		return lcMap;
	}
	
	template<typename Number>
	antlrcpp::Any HyproBadStatesVisitor<Number>::visitBadstate(HybridAutomatonParser::BadstateContext *ctx){

		std::cout << "-- Bin bei visitBadstate!" << std::endl;

		//0.Check if given loc name exists and get meant location where bad states can occur
		bool found = false;
		Location<Number>* badLoc;
		for(const auto& loc : locSet){
			if(ctx->VARIABLE()->getText() == loc->getName()){
				found = true;
				badLoc = loc;
				break;
			}
		}
		if(!found){
			std::cerr << "ERROR: Given location name in unsafe set does not exist." << std::endl;
			exit(0);
		}

		//1.Get the conditions under which we enter a bad state.
		HyproFormulaVisitor<Number> visitor(vars);
		std::pair<matrix_t<Number>,vector_t<Number>> badStatePair = visitor.visit(ctx->constrset()).template as<std::pair<matrix_t<Number>,vector_t<Number>>>();
		Condition<Number> badStateConditions(badStatePair.first, badStatePair.second);	
		return std::make_pair(badLoc, badStateConditions);
		
	}

} //namespace hypro