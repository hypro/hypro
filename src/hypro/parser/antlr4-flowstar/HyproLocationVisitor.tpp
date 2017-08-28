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
		std::cout << "-- Bin bei visitModes!" << std::endl;

		//Calls visit(ctx->location()) to get location, name it, put into locSet, return locSet
		unsigned i = 0;
		std::set<Location<Number>*> locSet;
		while(i < ctx->location().size()){

			//0.Syntax check - Location name already parsed?
			for(auto& loc : locSet){
				if(loc->getName() == ctx->location().at(i)->VARIABLE()->getText()){
					std::cerr << "ERROR: Location " << loc->getName() << " has already been parsed." << std::endl;
				}
			}

			Location<Number>* loc = visit(ctx->location().at(i));
			loc->setName(ctx->location().at(i)->VARIABLE()->getText());
			std::cout << "---- Visited location " << loc->getName() << std::endl;
			locSet.insert(loc);
			i++;
		}
		return locSet;
	}

	template<typename Number>
	antlrcpp::Any HyproLocationVisitor<Number>::visitLocation(HybridAutomatonParser::LocationContext *ctx){
		std::cout << "-- Bin bei visitLocation!" << std::endl;


		//1.Calls visit(ctx->activities()) to get matrix
		matrix_t<Number> tmpMatrix = visit(ctx->activities());
		std::cout << "---- Flow matrix is:\n" << tmpMatrix << std::endl;

		//2.Calls visit(ctx->invariant()) to get Condition
		Condition<Number> inv = visit(ctx->invariants());
		std::cout << "---- inv is:\n" << inv.getMatrix() << "and\n" << inv.getVector() << std::endl;

		//3.Returns a location
		LocationManager<Number>& manager = LocationManager<Number>::getInstance();
		Location<Number>* loc = manager.create();
		loc->setFlow(tmpMatrix);
		loc->setInvariant(inv);
		return loc;
	}

	template<typename Number>
	antlrcpp::Any HyproLocationVisitor<Number>::visitActivities(HybridAutomatonParser::ActivitiesContext *ctx){
		std::cout << "-- Bin bei visitActivities!" << std::endl;

		//0.Syntax check - Are there vars.size() equations?
		if(vars.size() != ctx->equation().size()){
			std::cerr << "ERROR: Wrong amount of activites for current location!" << std::endl;
		}

		//1.Calls iteratively visit(ctx->equation()) to get vector, store them
		matrix_t<Number> tmpMatrix = matrix_t<Number>::Zero(vars.size()+1, vars.size()+1);
		HyproFormulaVisitor<Number> visitor(vars);
		for(unsigned i=0; i < ctx->equation().size(); i++){
			vector_t<Number> tmpRow = visitor.visit(ctx->equation()[i]);
			//std::cout << "---- From equation " << i << " we got tmpRow:\n" << tmpRow << std::endl;
			tmpMatrix.row(i) = tmpRow;
			//std::cout << "---- After insertion tmpMatrix is now:\n" << tmpMatrix << std::endl;
		}

		//3.Syntax check - Last row completely 0's?
		if(vector_t<Number>(tmpMatrix.row(tmpMatrix.rows()-1)) != vector_t<Number>::Zero(tmpMatrix.cols())){
			//std::cout << "Last row of tmpMatrix is:\n " << tmpMatrix.row(tmpMatrix.rows()-1) << std::endl;
			std::cerr << "ERROR: Last row of tmpMatrix was not completely zero!" << std::endl;
		}

		//4.Returns a matrix
		return tmpMatrix;
	}

	template<typename Number>
	antlrcpp::Any HyproLocationVisitor<Number>::visitInvariants(HybridAutomatonParser::InvariantsContext *ctx){
		std::cout << "-- Bin bei visitInvariants!" << std::endl;

		//2.Call HyproFormulaVisitor and get pair of matrix and vector
		HyproFormulaVisitor<Number> visitor(vars);
		std::pair<matrix_t<Number>,vector_t<Number>> result = visitor.visit(ctx->constrset());

		//3.Build condition out of them
		Condition<Number> inv;
		inv.setMatrix(result.first);
		inv.setVector(result.second);

		//4.Return condition
		return inv;
	}
}
