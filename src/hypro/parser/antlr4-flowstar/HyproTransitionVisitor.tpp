#include "HyproTransitionVisitor.h"

namespace hypro {

	//////////// Constructor and Destructor

	template<typename Number>
	HyproTransitionVisitor<Number>::HyproTransitionVisitor(std::vector<std::string> varVec, std::set<Location<Number>*> lSet) :
		vars(varVec),
		locSet(lSet)
	{ }

	template<typename Number>
	HyproTransitionVisitor<Number>::~HyproTransitionVisitor() { }

	/////////// Inherited from HybridAutomatonBaseVisitor

	template<typename Number>
	antlrcpp::Any HyproTransitionVisitor<Number>::visitJumps(HybridAutomatonParser::JumpsContext *ctx){

		std::cout << "-- Bin bei visitJumps!" << std::endl;

		if(ctx->transition().size() > 0){
			std::set<Transition<Number>*> trSet;
			for(auto tr : ctx->transition()){
				trSet.insert(visit(tr).antlrcpp::Any::as<Transition<Number>*>());
				//auto blub = visit(tr).antlrcpp::Any::as<Transition<Number>*>();
				//std::cout << *blub << std::endl;
				//trSet.insert(blub);
			}
			return trSet;
		} else {
			std::cout << "-- No jumps found! Returning empty transition set." << std::endl;
			return std::set<Transition<Number>*>();
		}
		
	}

	template<typename Number>
	antlrcpp::Any HyproTransitionVisitor<Number>::visitTransition(HybridAutomatonParser::TransitionContext *ctx){

		std::cout << "-- Bin bei visitTransition!" << std::endl;

		Transition<Number>* t = new Transition<Number>();

		//1.Collect start/destination location from visitFromTo
		std::pair<Location<Number>*,Location<Number>*> fromTo = visit(ctx->fromto());
		std::cout << "---- Checked source/target location!" << std::endl;
		t->setSource(fromTo.first);
		std::cout << "---- Set source!" << std::endl;
		t->setTarget(fromTo.second);
			
		//2. Collect Urgency
		if(ctx->urgent().size() > 1){
			std::cout << "WARNING: Please refrain from entering 'urgent' multiple times. One time is sufficient->" << std::endl;
		} else if(ctx->urgent().size() == 1){
			t->setUrgent(true);
		} else {
			t->setUrgent(false);
		}
		std::cout << "---- Checked urgency!" << std::endl;

		//3.Collect Guards
		if(ctx->guard().size() > 1){
			std::cout << "WARNING: Please refrain from entering multiple guard constraints via several guard spaces. Typing one guard space of the form 'guard { constraint1 constraint2 ... }' is sufficient->" << std::endl;
		} 
		if(ctx->guard().size() == 1){
			Condition<Number> inv = visit(ctx->guard()[0]);
			t->setGuard(inv);
		} 
		std::cout << "---- Checked guards!" << std::endl;

		//4.Collect Resets
		if(ctx->resetfct().size() > 1){
			std::cout << "WARNING: Please refrain from entering multiple reset allocations via several reset spaces. Typing one reset space of the form 'reset { allocation1 allocation2 ... }' is sufficient->" << std::endl;
		}
		if(ctx->resetfct().size() == 1){
			Reset<Number> reset = visit(ctx->resetfct()[0]);
			t->setReset(reset);
		}
		std::cout << "---- Checked resets!" << std::endl;

		//5.Collect Aggregation
		if(ctx->aggregation().size() > 1){
			std::cerr << "ERROR: Multiple aggregation types specified for one transition." << std::endl;
		}
		if(ctx->aggregation().size() == 1){
			Aggregation agg = visit(ctx->aggregation()[0]);
			t->setAggregation(agg);
		}
		std::cout << "---- Checked aggregation!" << std::endl;		

		return t;
	}

	template<typename Number>
	antlrcpp::Any HyproTransitionVisitor<Number>::visitFromto(HybridAutomatonParser::FromtoContext *ctx){

		std::cout << "-- Bin bei visitFromto!" << std::endl;

		//0.Syntax check - are both given names really location names?
		//1.While doing syntax check, also fill fromTo (defined below) so we can return it.
		bool foundLeft = false;
		bool foundRight = false;
		std::pair<Location<Number>*,Location<Number>*> fromTo;
		for(auto& loc : locSet){
			std::cout << "---- Name of loc: " << loc->getName() << " name of variable 0: " << ctx->VARIABLE()[0]->getText() << " name of variable 1: " << ctx->VARIABLE()[1]->getText() << std::endl;
			if(loc->getName() == ctx->VARIABLE()[0]->getText()){
				foundLeft = true;
				fromTo.first = loc;
				std::cout << "------ Found a match with variable " << ctx->VARIABLE()[0]->getText() << std::endl;
			}
			if(loc->getName() == ctx->VARIABLE()[1]->getText()){
				foundRight = true;
				fromTo.second = loc;
				std::cout << "------ Found a match with variable " << ctx->VARIABLE()[1]->getText() << std::endl;
			}
		}
		if(!foundLeft || !foundRight){
			std::cerr << "ERROR: Location names in a jump do not exist." << std::endl;
		}

		//1.Return pair of location pointers to both given location names
		return fromTo;
	}

	template<typename Number>
	antlrcpp::Any HyproTransitionVisitor<Number>::visitGuard(HybridAutomatonParser::GuardContext *ctx){

		std::cout << "-- Bin bei visitGuard!" << std::endl;

		//NOTE: This code is copypasted from HyproLocationVisitor::visitInvariants()

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
				std::cout << "---- Have chosen the " << i << "-th constraint vector!" << std::endl;
			} else {
				unsigned posInIntervalExpr = i - ctx->constraint().size();
				std::cout << "---- Have chosen the " << posInIntervalExpr << "-th intervalexpr vector!" << std::endl;
				//std::cout << "---- intervalexpr size: " << ctx->intervalexpr().size() << std::endl;
				if(posInIntervalExpr < ctx->intervalexpr().size()){
					values = visitor.visit(ctx->intervalexpr().at(posInIntervalExpr)).antlrcpp::Any::as<std::vector<std::pair<vector_t<Number>,Number>>>();					
					//std::cout << "---- intervalexpr existed!" << std::endl;					
				} else {
					std::cerr << "ERROR: There is no " << posInIntervalExpr << "-th constraint parsed!" << std::endl;
				}
			}

			//Print stuff
			std::cout << "---- Received following constraint Vec:" << std::endl;
			for(auto v : values){
				std::cout << v.first << "and \n" << v.second << "\n" << std::endl;
			}

			//Resize tmpMatrix and tmpVector and initialise them with 0, then write values inside
			tmpMatrix.conservativeResize(tmpMatrix.rows()+values.size()-1, Eigen::NoChange_t::NoChange);
			tmpVector.conservativeResize(tmpVector.rows()+values.size()-1, Eigen::NoChange_t::NoChange);
			for(int k=rowToFill; k < tmpMatrix.rows(); k++){
				tmpMatrix.row(k) = vector_t<Number>::Zero(tmpMatrix.cols());
				tmpVector(k) = Number(0);
			}
			std::cout << "---- Resized tmpMatrix to:\n" << tmpMatrix << std::endl;
			std::cout << "---- Resized tmpVector to:\n" << tmpVector << std::endl;
			for(unsigned k=0; k < values.size(); k++){
				tmpMatrix.row(rowToFill+k) = values[k].first;
				tmpVector(rowToFill+k) = values[k].second;
			}

			//Increment i by our added size
			std::cout << "---- After insertion tmpMatrix is:\n" << tmpMatrix << " and tmpVector is:\n" << tmpVector << std::endl;
			rowToFill += values.size();
			i++;
			std::cout << "---- AFTER UPDATE size: " << size << " rowToFill: " << rowToFill << " i: " << i << std::endl;
		}

		//3.Build condition out of them
		Condition<Number> inv;
		inv.setMatrix(tmpMatrix);
		inv.setVector(tmpVector);

		//4.Return condition
		return inv;
	}

	template<typename Number>
	antlrcpp::Any HyproTransitionVisitor<Number>::visitAllocation(HybridAutomatonParser::AllocationContext *ctx){
		
		std::cout << "-- Bin bei visitAllocation!" << std::endl;

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

		std::cout << "-- Bin bei visitResetfct!" << std::endl;

		//0.Check if there are not too much resets
		if(ctx->allocation().size() > vars.size()){
			std::cerr << "ERROR: Too many resets for this amount of variables. Only one reset per transition per variable allowed." << std::endl;
		}

		//1.Iteratively call visit(allocation) to get a values for the row of resetMatrix and a value for resetVector
		matrix_t<Number> resetMatrix = matrix_t<Number>::Identity(vars.size(), vars.size());
		vector_t<Number> resetVector = vector_t<Number>::Zero(vars.size());
		for(unsigned i=0; i < ctx->allocation().size(); i++){
			std::pair<vector_t<Number>,unsigned> valuesNPos = visit(ctx->allocation()[i]);
			if(valuesNPos.first.rows() != vars.size()+1){
				std::cerr << "ERROR: Visiting Allocation brought forth vec of size: " << valuesNPos.first.rows() << " but we need: " << vars.size() << std::endl;
			}
			//1.2.Find out into which row according to vars we have to place the row
			resetMatrix.row(valuesNPos.second) = valuesNPos.first.head(vars.size());
			resetVector(valuesNPos.second) = valuesNPos.first(valuesNPos.first.rows()-1);
		}
		if(resetMatrix == matrix_t<Number>::Zero(vars.size(), vars.size())){
			resetMatrix = matrix_t<Number>::Identity(vars.size(), vars.size());
		}
		std::cout << "---- resetMatrix:\n" << resetMatrix << "\n and resetVector:\n" << resetVector << std::endl;

		//2.return a Reset - 0 in the setter arguments is for the position within the vector of ConstraintSets
		Reset<Number> r;
		r.setMatrix(resetMatrix, 0);
		r.setVector(resetVector, 0);
		return r;
	}

	template<typename Number>
	antlrcpp::Any HyproTransitionVisitor<Number>::visitAggregation(HybridAutomatonParser::AggregationContext *ctx){

		std::cout << "-- Bin bei visitAggregation!" << std::endl;

		if(ctx->PARALLELOTOPE() != NULL){
			std::cout << "---- Aggregation is parallelotope" << std::endl;
			return Aggregation::parallelotopeAgg;
		} else if(ctx->BOX() != NULL){
			std::cout << "---- Aggregation is box" << std::endl;
			return Aggregation::boxAgg;
		} else {
			std::cout << "---- Aggregation is none" << std::endl;
			return Aggregation::none;
		}
	}

}
	
	