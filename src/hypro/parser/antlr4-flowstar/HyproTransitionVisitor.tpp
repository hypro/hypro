#include "HyproTransitionVisitor.h"

namespace hypro {

	//////////// Constructor and Destructor

	template<typename Number>
	HyproTransitionVisitor<Number>::HyproTransitionVisitor(std::vector<std::string>& varVec, std::set<Location<Number>*>& lSet) :
		vars(varVec),
		locSet(lSet)
	{ }

	template<typename Number>
	HyproTransitionVisitor<Number>::~HyproTransitionVisitor() { }

	/////////// Inherited from HybridAutomatonBaseVisitor

	template<typename Number>
	antlrcpp::Any HyproTransitionVisitor<Number>::visitJumps(HybridAutomatonParser::JumpsContext *ctx){

		if(ctx->transition().size() > 0){
			std::set<Transition<Number>*> trSet;
			for(auto tr : ctx->transition()){
				//trSet.insert(visit(tr).antlrcpp::Any::as<Transition<Number>*>());
				Transition<Number>* t = visit(tr).template as<Transition<Number>*>();
				trSet.insert(t);
				(t->getSource())->addTransition(t);
			}
			return trSet;
		} else {
			return std::set<Transition<Number>*>();
		}

	}

	template<typename Number>
	antlrcpp::Any HyproTransitionVisitor<Number>::visitTransition(HybridAutomatonParser::TransitionContext *ctx){

		Transition<Number>* t = new Transition<Number>();

		//1.Collect start/destination location from visitFromTo
		std::pair<Location<Number>*,Location<Number>*> fromTo = visit(ctx->fromto());
		t->setSource(fromTo.first);
		t->setTarget(fromTo.second);

		//2. Collect Urgency
		if(ctx->urgent().size() > 1){
			std::cout << "WARNING: Please refrain from entering 'urgent' multiple times. One time is sufficient. Urgency has not been parsed." << std::endl;
		} else if(ctx->urgent().size() == 1){
			t->setUrgent(true);
		} else {
			t->setUrgent(false);
		}

		//3.Collect Guards
		if(ctx->guard().size() > 1){
			std::cout << "WARNING: Please refrain from entering multiple guard constraints via several guard spaces.\n";
			std::cout << "Typing one guard space of the form 'guard { constraint1 constraint2 ... }' is sufficient.\n";
			std::cout << "The guards have not been parsed.\n";
		}
		if(ctx->guard().size() == 1){
			Condition<Number> inv = visit(ctx->guard()[0]);
			t->setGuard(inv);
		}

		//4.Collect Resets
		if(ctx->resetfct().size() > 1){
			std::cout << "WARNING: Please refrain from entering multiple reset allocations via several reset spaces.\n";
			std::cout << "Typing one reset space of the form 'reset { allocation1 allocation2 ... }' is sufficient.\n";
			std::cout << "The resets have not been parsed.\n";
		}
		if(ctx->resetfct().size() == 1){
			Reset<Number> reset = visit(ctx->resetfct()[0]);
			t->setReset(reset);
		}

		//5.Collect Aggregation
		if(ctx->aggregation().size() > 1){
			std::cerr << "ERROR: Multiple aggregation types specified for one transition." << std::endl;
			exit(0);
		}
		if(ctx->aggregation().size() == 1){
			Aggregation agg = visit(ctx->aggregation()[0]);
			t->setAggregation(agg);
		}

		//6. Collect Labels
		if(ctx->labels().size() >= 1) {
			std::set<Label> ls;
			for(const auto& ctxlabel: ctx->labels()) {
				Label l = visit(ctxlabel);
				ls.insert(l);
			}
			t->setLabels(ls);
		}

		return t;
	}

	template<typename Number>
	antlrcpp::Any HyproTransitionVisitor<Number>::visitFromto(HybridAutomatonParser::FromtoContext *ctx){

		//0.Syntax check - are both given names really location names?
		//1.While doing syntax check, also fill fromTo (defined below) so we can return it.
		bool foundLeft = false;
		bool foundRight = false;
		std::pair<Location<Number>*,Location<Number>*> fromTo;
		for(auto& loc : locSet){
			//std::cout << "---- Name of loc: " << loc->getName() << " name of variable 0: " << ctx->VARIABLE()[0]->getText() << " name of variable 1: " << ctx->VARIABLE()[1]->getText() << std::endl;
			if(loc->getName() == ctx->VARIABLE()[0]->getText()){
				foundLeft = true;
				fromTo.first = loc;
			}
			if(loc->getName() == ctx->VARIABLE()[1]->getText()){
				foundRight = true;
				fromTo.second = loc;
			}
		}
		if(!foundLeft || !foundRight){
			std::cerr << "ERROR: Location names in a jump do not exist." << std::endl;
			exit(0);
		}

		//1.Return pair of location pointers to both given location names
		return fromTo;
	}

	template<typename Number>
	antlrcpp::Any HyproTransitionVisitor<Number>::visitGuard(HybridAutomatonParser::GuardContext *ctx){

		//1.Call HyproFormulaVisitor and get pair of matrix and vector if constrset exists
		if(ctx->constrset() != NULL){
			HyproFormulaVisitor<Number> visitor(vars);
			std::pair<matrix_t<Number>,vector_t<Number>> result = visitor.visit(ctx->constrset());
			Condition<Number> inv;
			inv.setMatrix(result.first);
			inv.setVector(result.second);
			return inv;
		}
		//Return empty condition if no guard given
		return Condition<Number>();
	}

	template<typename Number>
	antlrcpp::Any HyproTransitionVisitor<Number>::visitAllocation(HybridAutomatonParser::AllocationContext *ctx){

		//0.Syntax Check - Check if left side is a var with '
		bool found = false;
		unsigned placeInto = 0;
		for(unsigned i=0; i < vars.size(); i++){
			if((vars[i] + "'") == ctx->VARIABLE()->getText()){
				found = true;
				placeInto = i;
			}
		}
		if(!found){
			std::cerr << "An allocation in the reset part has a not defined variable." << std::endl;
			exit(0);
		}

		//1.Call HyproFormulaVisitor::visitPolynom()
		vector_t<Number> tmpVector = vector_t<Number>::Zero(vars.size());
		if(ctx->polynom() != NULL){
			HyproFormulaVisitor<Number> visitor(vars);
			tmpVector = visitor.visit(ctx->polynom());
		}
		//NOTE: Intervals are parsed but not handled yet
		if(ctx->interval() != NULL){
			std::cout << "We do not support resets to intervals in this current build." << std::endl;
		}

		//3.Return Vector of coefficents and place in matrix
		return std::make_pair(tmpVector,placeInto);
	}

	template<typename Number>
	antlrcpp::Any HyproTransitionVisitor<Number>::visitResetfct(HybridAutomatonParser::ResetfctContext *ctx){

		//0.Check if there are not too much resets
		if(ctx->allocation().size() > vars.size()){
			std::cerr << "ERROR: Too many resets for this amount of variables. Only one reset per transition per variable allowed." << std::endl;
			exit(0);
		}

		//1.Iteratively call visit(allocation) to get a values for the row of resetMatrix and a value for resetVector
		matrix_t<Number> resetMatrix = matrix_t<Number>::Identity(vars.size(), vars.size());
		vector_t<Number> resetVector = vector_t<Number>::Zero(vars.size());
		for(unsigned i=0; i < ctx->allocation().size(); i++){
			std::pair<vector_t<Number>,unsigned> valuesNPos = visit(ctx->allocation()[i]);
			if(static_cast<unsigned>(valuesNPos.first.rows()) != vars.size()+1){
				std::cerr << "ERROR: Visiting Allocation brought forth vec of size: " << valuesNPos.first.rows() << " but we need: " << vars.size() << std::endl;
				exit(0);
			}
			//1.2.Find out into which row according to vars we have to place the row
			resetMatrix.row(valuesNPos.second) = valuesNPos.first.head(vars.size());
			resetVector(valuesNPos.second) = valuesNPos.first(valuesNPos.first.rows()-1);
		}
		//if(resetMatrix == matrix_t<Number>::Zero(vars.size(), vars.size())){
		//	resetMatrix = matrix_t<Number>::Identity(vars.size(), vars.size());
		//}
		//std::cout << "---- resetMatrix:\n" << resetMatrix << "\n and resetVector:\n" << resetVector << std::endl;

		//2.return a Reset - 0 in the setter arguments is for the position within the vector of ConstraintSets
		Reset<Number> r;
		r.setMatrix(resetMatrix, 0);
		r.setVector(resetVector, 0);
		return r;
	}

	template<typename Number>
	antlrcpp::Any HyproTransitionVisitor<Number>::visitAggregation(HybridAutomatonParser::AggregationContext *ctx){

		if(ctx->PARALLELOTOPE() != NULL){
			//std::cout << "---- Aggregation is parallelotope" << std::endl;
			return Aggregation::parallelotopeAgg;
		} else if(ctx->BOX() != NULL){
			//std::cout << "---- Aggregation is box" << std::endl;
			return Aggregation::boxAgg;
		} else {
			//std::cout << "---- Aggregation is none" << std::endl;
			return Aggregation::none;
		}
	}

	template<typename Number>
	antlrcpp::Any HyproTransitionVisitor<Number>::visitLabels(HybridAutomatonParser::LabelsContext * ctx){
		Label l;
		l.setName(ctx->getText());
		return l;
	}

}


