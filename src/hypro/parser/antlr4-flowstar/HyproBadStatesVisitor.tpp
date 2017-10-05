#include "HyproBadStatesVisitor.h"

namespace hypro {

	//////////////// Constructor & Destructor

	template<typename Number>
	HyproBadStatesVisitor<Number>::HyproBadStatesVisitor(std::vector<std::string>& varVec, std::set<Location<Number>*>& lSet) :
		vars(varVec),
		locSet(lSet)
	{ }
	
	template<typename Number>
	HyproBadStatesVisitor<Number>::~HyproBadStatesVisitor() { }

	/////////////// Inherited from HybridAutomatonBaseVisitor	

	template<typename Number>
	antlrcpp::Any HyproBadStatesVisitor<Number>::visitUnsafeset(HybridAutomatonParser::UnsafesetContext *ctx){

		//1.Collect badState information. NOTE: There can be multiple denoted badstates for one location.
		locationConditionMap lcMap;
		if(ctx->badstate().size() > 0){
			for(auto bState : ctx->badstate()){	
				if(bState->constrset() != NULL && bState->constrset()->getText() != ""){
					std::pair<Location<Number>*,Condition<Number>> badStateInfo = visit(bState).template as<std::pair<Location<Number>*,Condition<Number>>>();
					std::size_t lcMapSize = lcMap.size();
					lcMap.insert(badStateInfo);
					//Case that nothing has been inserted as location already existed in map: 
					//Extend condition matrix and vector of condition that is already in map
					if(lcMapSize == lcMap.size()){

						auto it = lcMap.find(badStateInfo.first);
						assert(it != lcMap.end());
						
						//Extend inMapCondition.matrix with badStateInfo.matrix
						matrix_t<Number> newMat = it->second.getMatrix();
						std::size_t newMatRowsBefore = newMat.rows();
						matrix_t<Number> currbStateMat = badStateInfo.second.getMatrix();
						assert(newMat.cols() == currbStateMat.cols());
						newMat.conservativeResize((newMat.rows()+currbStateMat.rows()),newMat.cols());
						for(int i = newMat.rows()-currbStateMat.rows(); i < newMat.rows(); i++){
							newMat.row(i) = currbStateMat.row((i-newMatRowsBefore));
						}

						//Extend inMapCondition.vector with badStateInfo.vector
						vector_t<Number> newVec = it->second.getVector();
						vector_t<Number> currbStateVec = badStateInfo.second.getVector();
						newVec.conservativeResize(newVec.rows()+currbStateVec.rows());
						for(int i = newVec.rows()-currbStateVec.rows(); i < newVec.rows(); i++){
							newVec(i) = currbStateVec(i-newMatRowsBefore);
						}

						it->second.setMatrix(newMat);
						it->second.setVector(newVec);

					}
				}
			}	
		}
		return lcMap;
	}
	
	template<typename Number>
	antlrcpp::Any HyproBadStatesVisitor<Number>::visitBadstate(HybridAutomatonParser::BadstateContext *ctx){

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