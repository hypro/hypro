#include "HyproLocationVisitor.h"

namespace hypro {

	///////////////// Constructor & Destructor
	
	template<typename Number>
	HyproLocationVisitor<Number>::HyproLocationVisitor(std::vector<std::string> varVec) :
		vars(varVec)
	{ }

	template<typename Number>
	HyproLocationVisitor<Number>::~HyproLocationVisitor() { }

	//////////////// Inherited Functions

	template<typename Number>
	antlrcpp::Any HyproLocationVisitor<Number>::visitModes(HybridAutomatonParser::ModesContext *ctx){
		std::cout << "-- Bin bei visitModes!" << std::endl;

		//Calls visit(ctx->location()) to get location, put into locSet, return locSet
		unsigned i = 0;
		std::set<Location<Number>*> locSet;
		while(i < ctx->location().size()){

			//0.Syntax check - Location name already parsed? 
			for(auto& loc : locSet){
				if(loc->getName() == ctx->location().at(i)->VARIABLE()->getText()){
					std::cerr << "Location " << loc->getName() << " has already been parsed." << std::endl;
				}
			}

			Location<Number>* loc = visit(ctx->location().at(i));
			std::cout << "---- Visitied location " << i << std::endl;
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
		////////////////NOTE: Vorerst nur leere location
		LocationManager<Number>& manager = LocationManager<Number>::getInstance();
		return manager.create();
	}

	template<typename Number>
	antlrcpp::Any HyproLocationVisitor<Number>::visitActivities(HybridAutomatonParser::ActivitiesContext *ctx){
		std::cout << "-- Bin bei visitActivities!" << std::endl;

		//0.Syntax check - Are there vars.size() equations?
		if(vars.size() != ctx->equation().size()){
			std::cerr << "Wrong amount of activites for current location!" << std::endl;
		}

		//1.Calls iteratively visit(ctx->equation()) to get vector, store them
		matrix_t<Number> tmpMatrix = matrix_t<Number>::Zero(vars.size()+1, vars.size()+1);
		HyproFormulaVisitor<Number> visitor(vars);
		for(unsigned i=0; i < ctx->equation().size(); i++){
			vector_t<Number> tmpRow = visitor.visit(ctx->equation()[i]);
			std::cout << "---- From equation " << i << " we got tmpRow:\n" << tmpRow << std::endl;
			tmpMatrix.row(i) = tmpRow;
			std::cout << "---- After insertion tmpMatrix is now:\n" << tmpMatrix << std::endl;
		}

		//3.Syntax check - Last row completely 0's?
		if(tmpMatrix.row(tmpMatrix.rows()-1) == vector_t<Number>::Zero(tmpMatrix.rows()-1)){
			//std::cout << "Last row of tmpMatrix is:\n " << tmpMatrix.row(tmpMatrix.rows()-1) << std::endl;
			std::cerr << "Last row of tmpMatrix was not completely zero!" << std::endl;
		}

		//4.Returns a matrix
		return tmpMatrix;
	}

	template<typename Number>
	antlrcpp::Any HyproLocationVisitor<Number>::visitInvariants(HybridAutomatonParser::InvariantsContext *ctx){
		std::cout << "-- Bin bei visitInvariants!" << std::endl;

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
}