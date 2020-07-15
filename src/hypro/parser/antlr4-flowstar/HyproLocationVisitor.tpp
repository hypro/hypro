#include "HyproLocationVisitor.h"

namespace hypro {

	///////////////// Constructor & Destructor

	template<typename Number>
	HyproLocationVisitor<Number>::HyproLocationVisitor(std::vector<std::string>& varVec) :
		vars(varVec)
	{ }

	template<typename Number>
	HyproLocationVisitor<Number>::~HyproLocationVisitor() { }

	//////////////// Inherited Functions

	template<typename Number>
	antlrcpp::Any HyproLocationVisitor<Number>::visitModes(HybridAutomatonParser::ModesContext *ctx){

		//Calls visit(ctx->location()) to get location, name it, put into locSet, return locSet
		unsigned i = 0;
		std::set<Location<Number>*> locSet;
		while(i < ctx->location().size()){

			//0.Syntax check - Location name already parsed?
			for(auto& loc : locSet){
				if(loc->getName() == ctx->location().at(i)->VARIABLE()->getText()){
					std::cerr << "ERROR: Location " << loc->getName() << " has already been parsed." << std::endl;
					exit(0);
				}
			}

			Location<Number>* loc = visit(ctx->location().at(i));
			assert(loc != nullptr);
			//locSet.insert(loc);
			locSet.emplace(loc);
			i++;
		}
		//return set of raw ptrs to locations
		return locSet;
	}

	template<typename Number>
	antlrcpp::Any HyproLocationVisitor<Number>::visitLocation(HybridAutomatonParser::LocationContext *ctx){

		//1.Calls visit(ctx->activities()) to get flow (as a variant) and externalInputBox
		std::tuple<linearFlow<Number>, rectangularFlow<Number>,std::vector<carl::Interval<Number>>> flowAndExtInput = visit(ctx->activities());
		//std::cout << "---- Flow matrix is:\n" << flowAndExtInput.first << std::endl;
		//std::cout << "---- externalInputBox is:\n" << flowAndExtInput.second << std::endl;

		//2.Iteratively Calls visit(ctx->invariant()) to get all conditions and collect them in one big condition
		//By default, if no invariant is given, return a 0xn matrix because we have zero contraints over n variables
		Condition<Number> inv{ConstraintSetT<Number>{matrix_t<Number>::Zero(0,vars.size()), vector_t<Number>::Zero(0)}};

		bool firstTime = true;
		for(auto& currInvCtx : ctx->invariants()){
			Condition<Number> currInv = visit(currInvCtx);
			if(currInv != Condition<Number>()){
				if(firstTime){
					inv = currInv;
					firstTime = false;
					continue;
				}

				//Extend inv.matrix with currInv.matrix
				matrix_t<Number> newMat = inv.getMatrix();
				matrix_t<Number> currInvMat = currInv.getMatrix();
				assert(newMat.cols() == currInvMat.cols());
				std::size_t newMatRowsBefore = newMat.rows();
				newMat.conservativeResize(newMat.rows()+currInvMat.rows(),newMat.cols());
				for(int i = newMat.rows()-currInvMat.rows(); i < newMat.rows(); i++){
					newMat.row(i) = currInvMat.row(i-newMatRowsBefore);
				}

				//Extend inv.vector with currInv.vector
				vector_t<Number> newVec = inv.getVector();
				vector_t<Number> currInvVec = currInv.getVector();
				newVec.conservativeResize(newVec.rows()+currInvVec.rows());
				for(int i = newVec.rows()-currInvVec.rows(); i < newVec.rows(); i++){
					newVec(i) = currInvVec(i-newMatRowsBefore);
				}

				inv = Condition<Number>(newMat, newVec);
			}
		}

		//3.Returns a ptr to location
		Location<Number>* loc = new Location<Number>();
		loc->setName(ctx->VARIABLE()->getText());
		if(std::get<0>(flowAndExtInput).size() > 0) {
			loc->setLinearFlow(std::get<0>(flowAndExtInput));
		}
		if(!std::get<1>(flowAndExtInput).empty()) {
			loc->setRectangularFlow(std::get<1>(flowAndExtInput));
		}

		loc->setInvariant(inv);

		// only set external input, if it is different from zero
		if(!std::get<2>(flowAndExtInput).empty()) {
			//std::cout << "Set external input to " << flowAndExtInput.second << " which is not equal to " << Box<Number>(std::make_pair(Point<Number>(vector_t<Number>::Zero(flowAndExtInput.first.cols()-1)), Point<Number>(vector_t<Number>::Zero(flowAndExtInput.first.cols()-1)))) << std::endl;
			loc->setExtInput(std::get<2>(flowAndExtInput));
		}
		return loc;
	}

	template<typename Number>
	antlrcpp::Any HyproLocationVisitor<Number>::visitActivities(HybridAutomatonParser::ActivitiesContext *ctx){
		auto& vpool = VariablePool::getInstance();
		//0.Syntax check - Are there vars.size() equations?
		//if(vars.size() != ctx->equation().size()){
		//	std::cerr << "ERROR: Wrong amount of activites for current location!" << std::endl;
		//	exit(0);
		//}

		//1.Calls iteratively visit(ctx->equation()) to get vector, store them
		// maps used to deduce subspaces
		std::map<std::size_t, vector_t<Number>> linearFlows;
		std::map<carl::Variable, carl::Interval<Number>> rectangularFlows;

		std::vector<carl::Interval<Number>> extInputVec(vars.size(), carl::Interval<Number>());
		//std::cout << "extInputVec has been made!\n";
		HyproFormulaVisitor<Number> equationVisitor(vars);
		for(unsigned i=0; i < ctx->equation().size(); i++){
			//std::cout << "Try to parse linear flow." << std::endl;
			//insert into row according to state var order
			vector_t<Number> tmpRow = equationVisitor.visit(ctx->equation(i)).template as<vector_t<Number>>();
			for(unsigned j=0; j < vars.size(); j++){
				if(ctx->equation()[i]->VARIABLE()->getText() == (vars[j] + "'")){
					//std::cout << "Linear flow for variable " << j << ", row: " << tmpRow << std::endl;
					linearFlows[j] = tmpRow;
					if(ctx->equation(i)->interval() != NULL){
						carl::Interval<Number> intervalValues = equationVisitor.visit(ctx->equation(i)->interval());
						extInputVec[j] = intervalValues;
						//std::cout << "internalValues are: " << intervalValues << std::endl;
					}
					//std::cout << "extInputVec is at pos " << j << "is now:\n" << extInputVec[j] << std::endl;
					break;
				}
			}
		}
		// check if rectangular-dynamics exists and create flow
		HyproFormulaVisitor<Number> intervalVisitor(vars);
		for(unsigned i=0; i < ctx->intervalexpr().size(); i++){
			//std::cout << "Try to parse rectangular flow." << std::endl;
			// parse interval
			carl::Interval<Number> tmpintv = intervalVisitor.visit(ctx->intervalexpr(i)->interval());
			// find according variable and store in mapping
			for(unsigned j=0; j < vars.size(); j++){
				if(ctx->intervalexpr()[i]->VARIABLE()->getText() == (vars[j])){
					//std::cout << "Rectangular flow for variable " << j <<  ", interval: " << tmpintv << std::endl;
					rectangularFlows[vpool.carlVarByIndex(j)] = tmpintv;
					break;
				}
			}
		}

		// 2. assemble linear Flow
		matrix_t<Number> flowMatrix = matrix_t<Number>::Zero(vars.size()+1,vars.size()+1);
		for(const auto f : linearFlows) {
			flowMatrix.row(f.first) = f.second;
		}

		//4.Returns a tuple of flows and a externalInputBox
		rectangularFlow<Number> rFlow;
		rFlow.setFlowIntervals(rectangularFlows);
		linearFlow<Number> lFlow;
		lFlow.setFlowMatrix(flowMatrix);
		std::tuple<linearFlow<Number>, rectangularFlow<Number>,std::vector<carl::Interval<Number>>> res{lFlow,rFlow,extInputVec};
		return res;
	}

	template<typename Number>
	antlrcpp::Any HyproLocationVisitor<Number>::visitInvariants(HybridAutomatonParser::InvariantsContext *ctx){

		if(ctx->constrset() != NULL){

			//1.Call HyproFormulaVisitor and get pair of matrix and vector
			HyproFormulaVisitor<Number> visitor(vars);
			std::pair<matrix_t<Number>,vector_t<Number>> result = visitor.visit(ctx->constrset());

			//2.Build condition out of them
			Condition<Number> inv;
			inv.setMatrix(result.first);
			inv.setVector(result.second);

			//3.Return condition
			return inv;

		}

		return Condition<Number>();

	}
}
