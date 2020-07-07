#include "HyproFormulaVisitor.h"

namespace hypro {

	////////////// Constructor and Destructor

	template<typename Number>
	HyproFormulaVisitor<Number>::HyproFormulaVisitor(std::vector<std::string>& varVec) :
		vars(varVec)
	{ }

	template<typename Number>
	HyproFormulaVisitor<Number>::~HyproFormulaVisitor() { }

	///////////// Helping functions

	template<typename Number>
	Number HyproFormulaVisitor<Number>::stringToNumber(const std::string& string) const {
		double numInFloat = boost::lexical_cast<double>(string);
		//double numInFloat = std::stod(string);
		//std::cerr << "String: " << string << " converted with lexical_cast(string) to double numInFloat: " << numInFloat << std::endl;
		Number numInNumber = Number(numInFloat);
		return numInNumber;
	}

	template<typename Number>
	Number HyproFormulaVisitor<Number>::multTogether(HybridAutomatonParser::TermContext* ctx) const {

		//Turn -2*3*4*-5*x ... into 120*x
		Number multed = 1;
		if(ctx->NUMBER().size() > 1){
			for(const auto& ctxNum : ctx->NUMBER()){
				std::string num = ctxNum->getText();
				Number numInNumber = stringToNumber(num);
				multed = multed * numInNumber;
			}
		} else if(ctx->NUMBER().size() == 1){
			std::string num = ctx->NUMBER()[0]->getText();
			multed = stringToNumber(num);
		}

		if(ctx->connector().size() > 0){
			//Take minus count into account
			unsigned minusCount = 0;
			std::size_t startIndex = ctx->start->getStartIndex();
			std::size_t endIndex = ctx->stop->getStopIndex();
			for(const auto& ctxCon : ctx->connector()){
				std::size_t conIndex = ctxCon->start->getStartIndex();
				if(startIndex <= conIndex && conIndex <= endIndex && ctxCon->getText() == "-"){
					minusCount++;
				}
			}

			//make multed negative/posivite depending on its minusCount
			if(minusCount % 2 == 1){
				multed = Number(-1)*multed;
			}
		}

		//If term has a minus in front, inverse the result
		if(ctx->MINUS() != nullptr){
			multed = Number(-1)*multed;
		}

		return multed;
	}

	//For a given polynom context, return the vector of coefficients in the order of variables pushed into vars
	//The last coefficient is a constant, so the one without a respective variable
	template<typename Number>
	vector_t<Number> HyproFormulaVisitor<Number>::getPolynomCoeff(HybridAutomatonParser::PolynomContext* ctx) const {

		vector_t<Number> coeffVec = vector_t<Number>::Zero(vars.size()+1);
		std::size_t lastTermEndIndex = 0;

		for(const auto& mTerm : ctx->term()){

			//Multiply numbers and handle connectors within term
			Number multed = multTogether(mTerm);

			//Count the amount of '-'-connectors that are before the term.
			std::size_t mTermStartIndex = mTerm->start->getStartIndex();
			unsigned minusCount = 0;
			for(const auto& mConnector : ctx->connector()){
				std::size_t connectorStartIndex = mConnector->start->getStartIndex();
				if(lastTermEndIndex < connectorStartIndex && connectorStartIndex < mTermStartIndex && mConnector->getText() == "-"){
					minusCount++;
				}
			}

			//put into place according to place of variable in vars
			unsigned dest = 0;
			if(mTerm->VARIABLE().size() == 0){
				dest = coeffVec.rows()-1;
			} else if(mTerm->VARIABLE().size() == 1){
				auto tmpVar = mTerm->VARIABLE()[0]->getText();
				for(unsigned i=0; i < vars.size(); i++){
					if(vars[i] == tmpVar){
						dest = i;
						break;
					}
				}
			} else {
				std::cout << "ERROR: multiplication of several variables not allowed!" << std::endl;
				exit(0);
			}
			coeffVec(dest) += (minusCount % 2 == 1) ? Number(-1)*multed : multed;

			lastTermEndIndex = mTerm->stop->getStopIndex();

		}
		return coeffVec;
	}

	///////////// Functions inherited by FormulaBaseVisitor

	template<typename Number>
	antlrcpp::Any HyproFormulaVisitor<Number>::visitPolynom(HybridAutomatonParser::PolynomContext *ctx){

		//0.Syntax Check - Only legal variables in polynom?
		bool allVarsFound = true;
		std::string undefinedVars;
		for(const auto& currTerm : ctx->term()){
			for(const auto& maybeVar : currTerm->VARIABLE()){
				bool found = false;
				for(const auto& var : vars){
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
			std::cerr << "ERROR: Following variables were undefined in a term " << ": " << undefinedVars << std::endl;
			exit(0);
		}

		//1.Call getPolynomCoeff to fill vector of length vars.size()+1
		vector_t<Number> tmpVec = getPolynomCoeff(ctx);

		//2.Return Vector
		return tmpVec;
	}

	template<typename Number>
	antlrcpp::Any HyproFormulaVisitor<Number>::visitEquation(HybridAutomatonParser::EquationContext *ctx){

		//0.Syntax Check - Left side of equation legal?
		bool found = false;
		for(auto& variable : vars){
			if((variable + "'") == ctx->VARIABLE()->getText()){
				found = true;
			}
		}
		if(!found){
			std::cerr << "ERROR: An equation contains a non-defined variable." << std::endl;
			exit(0);
		}

		//1.Call visit(ctx->expression()) to get vector and return it
		return visit(ctx->expression()).template as<vector_t<Number>>();
	}

	template<typename Number>
	antlrcpp::Any HyproFormulaVisitor<Number>::visitExpression(HybridAutomatonParser::ExpressionContext *ctx) {
		
		DEBUG("hypro.parser", "current expression: " << ctx->getText());

		//If expression is only a polynom, return the coeff vector of the polynom
		if(ctx->polynom() != nullptr){
			vector_t<Number> result = visit(ctx->polynom()).template as<vector_t<Number>>();
			return result;
		}

		//Assert that terms do not have variable names inside (do not allow multiplication of multiple variables)
		//if(ctx->term().size() > 0 && ctx->term(0)->VARIABLE().size() > 0 || ctx->term(1)->VARIABLE().size() > 0){
		//	std::cerr << "ERROR: Multiplication of multiple variables not allowed" << std::endl;
		//}

		//Get factor left and right outside the expressions
		assert(0 <= ctx->term().size() && ctx->term().size() <= 2);
		Number leftFactor = 1;
		Number rightFactor = 1;
		if(ctx->term().size() != 0){
			if(ctx->term(0)->start->getStartIndex() > ctx->expression().back()->stop->getStopIndex()){
				//There was no left term, so the first term is the right-hand side term
				rightFactor = multTogether(ctx->term(0));
			} else {
				//The first term is the left term
				leftFactor = multTogether(ctx->term(0));
				rightFactor = ctx->term().size() == 2 ? multTogether(ctx->term(1)) : 1;
			}
		}

		//Get the vectors of each subexpression and aggregate them according to the connector in front
		assert(ctx->expression().size() >= 1);
		assert(ctx->expression().size() == ctx->connector().size() + 1);
		vector_t<Number> aggregateResult = visit(ctx->expression(0)).template as<vector_t<Number>>();
		for(std::size_t i = 1; i < ctx->expression().size(); ++i){
			if(ctx->connector()[i-1]->getText() == "+"){
				aggregateResult += visit(ctx->expression()[i]).template as<vector_t<Number>>();
			} else if(ctx->connector()[i-1]->getText() == "-"){
				aggregateResult -= visit(ctx->expression()[i]).template as<vector_t<Number>>();
			} else {
				std::cerr << "ERROR: Unknown operation found during expression aggregation." << std::endl;
			}
		}

		//Multiply/Divide by the left and right factors with the result and return it
		if(ctx->DIVIDE() != nullptr){
			return vector_t<Number>((leftFactor / rightFactor) * aggregateResult);
		} else {
			return vector_t<Number>((leftFactor * rightFactor) * aggregateResult);
		}
	}

	template<typename Number>
	antlrcpp::Any HyproFormulaVisitor<Number>::visitConstraint(HybridAutomatonParser::ConstraintContext *ctx){

		//0.Syntax Check - < or > not allowed
		if(ctx->BOOLRELATION() != NULL){
			if(ctx->BOOLRELATION()->getText() == "<" || ctx->BOOLRELATION()->getText() == ">"){
				std::cerr << "ERROR: Strict relations are not allowed in current build!";
				exit(0);
			}
		}

		//1.Call visit(ctx->expression()) for both sides to get 2 vectors
		vector_t<Number> poly1 = visit(ctx->expression()[0]);
		vector_t<Number> poly2 = visit(ctx->expression()[1]);

		//2.Shorten both vectors by one, save last coeff and save everything in pair
		Number poly1Back = poly1(poly1.size()-1);
		poly1.conservativeResize(poly1.size()-1, Eigen::NoChange_t::NoChange);
		//std::cout << "---- After shortening poly1 is:\n" << poly1 << " and poly1Back is: " << poly1Back << std::endl;
		Number poly2Back = poly2(poly2.size()-1);
		poly2.conservativeResize(poly2.size()-1, Eigen::NoChange_t::NoChange);
		//std::cout << "---- After shortening poly2 is:\n" << poly2 << " and poly2Back is: " << poly2Back << std::endl;

		//2.Use them to calculate constraint vector
		std::vector<std::pair<vector_t<Number>,Number>> constraintVec;
		if(ctx->BOOLRELATION() != NULL){
			if(ctx->BOOLRELATION()->getText() == "<="){

				auto res = std::make_pair(poly1 - poly2, poly2Back - poly1Back);
				constraintVec.push_back(res);

			} else if(ctx->BOOLRELATION()->getText() == ">="){

				auto res = std::make_pair(poly2 - poly1, poly1Back - poly2Back);
				constraintVec.push_back(res);

			}
		}
		if(ctx->EQUALS() != NULL){
			auto res1 = std::make_pair(poly1 - poly2, poly2Back - poly1Back);
			auto res2 = std::make_pair(poly2 - poly1, poly1Back - poly2Back);
			constraintVec.push_back(res1);
			constraintVec.push_back(res2);
		}

		//3.Return a vector of pairs of constraint vectors and constant Numbers
		return constraintVec;
	}

	template<typename Number>
	antlrcpp::Any HyproFormulaVisitor<Number>::visitInterval(HybridAutomatonParser::IntervalContext *ctx){

		//1.Attach the possible minuses to the numbers
		std::string leftString;
		std::string rightString;
		if(ctx->MINUS().size() > 0){
			std::size_t leftIndex = ctx->NUMBER(0)->getSymbol()->getStartIndex();
			for(const auto& m : ctx->MINUS()){
				std::size_t minusIndex = m->getSymbol()->getStartIndex();
				if(minusIndex < leftIndex){
					leftString = ctx->MINUS(0)->getText();
				} else {
					rightString = ctx->MINUS(1)->getText();
				}
			}
		}
		leftString += ctx->NUMBER()[0]->getText();
		rightString += ctx->NUMBER()[1]->getText();
		Number left = stringToNumber(leftString);
		Number right = stringToNumber(rightString);

		//2.Syntax Check - Check if interval is legal
		if(left > right){
			std::cerr << "ERROR: Interval left side with " << left << " is bigger than right side with " << right << "!" << std::endl;
			exit(0);
		}

		return carl::Interval<Number>(left,right);
	}

	template<typename Number>
	antlrcpp::Any HyproFormulaVisitor<Number>::visitIntervalexpr(HybridAutomatonParser::IntervalexprContext *ctx){

		//0.Syntax Check
		bool found = false;
		for(const auto& var : vars){
			if(ctx->VARIABLE()->getText() == var){
				found = true;
			}
		}
		if(!found){
			std::cerr << "ERROR: Variable in interval expression has not been defined!" << std::endl;
			exit(0);
		}

		//1.Get inverval
		carl::Interval<Number> intervalValues = visit(ctx->interval());

		//2.Make constraint vectors
		std::vector<std::pair<vector_t<Number>,Number>> constraintVec;
		vector_t<Number> firstConstraint = vector_t<Number>::Zero(vars.size());
		vector_t<Number> secondConstraint = vector_t<Number>::Zero(vars.size());
		unsigned dest = 0;
		for(unsigned i=0; i < vars.size(); i++){
			if(vars[i] == ctx->VARIABLE()->getText()){
				dest = i;
				break;
			}
		}
		firstConstraint(dest) = Number(-1);
		secondConstraint(dest) = Number(1);
		Number firstConstant = Number(-1) * intervalValues.lower();
		Number secondConstant = intervalValues.upper();
		auto firstPair = std::make_pair(firstConstraint, firstConstant);
		auto secondPair = std::make_pair(secondConstraint, secondConstant);
		constraintVec.push_back(firstPair);
		constraintVec.push_back(secondPair);

		//3.Return vector of pairs of constraint vectors and constant Numbers!
		return constraintVec;
	}

	template<typename Number>
	antlrcpp::Any HyproFormulaVisitor<Number>::visitConstrset(HybridAutomatonParser::ConstrsetContext *ctx){

		//0. Check if our constraint set contains TRUE or FALSE and return a fitting pair of matrix and vector in that case.
		if(ctx->TRUE() != NULL && ctx->FALSE() == NULL){

			matrix_t<Number> tmpMatrix = matrix_t<Number>::Zero(1,vars.size());
			vector_t<Number> tmpVector = vector_t<Number>::Zero(1);
			return std::make_pair(tmpMatrix, tmpVector);

		} else if (ctx->TRUE() == NULL && ctx->FALSE() != NULL) {

			matrix_t<Number> tmpMatrix = matrix_t<Number>::Zero(1,vars.size());
			vector_t<Number> minusOne = vector_t<Number>(1);
			minusOne(0) = Number(-1);
			return std::make_pair(tmpMatrix, minusOne);

		} else if (ctx->TRUE() != NULL && ctx->FALSE() != NULL) {

			std::cerr << "ERROR: It should not be possible to have true and false in a constraint set." << std::endl;
			exit(0);

		} else {

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
					values = (visitor.visit(ctx->constraint().at(i))).template as<std::vector<std::pair<vector_t<Number>,Number>>>();
				} else {
					unsigned posInIntervalExpr = i - ctx->constraint().size();
					if(posInIntervalExpr < ctx->intervalexpr().size()){
						values = visitor.visit(ctx->intervalexpr().at(posInIntervalExpr)).template as<std::vector<std::pair<vector_t<Number>,Number>>>();
					} else {
						std::cerr << "ERROR: There is no " << posInIntervalExpr << "-th constraint parsed!" << std::endl;
						exit(0);
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
				for(unsigned k=0; k < values.size(); k++){
					tmpMatrix.row(rowToFill+k) = values[k].first;
					tmpVector(rowToFill+k) = values[k].second;
				}

				//Increment rowToFill by our added size
				rowToFill += values.size();
				i++;
			}

			return std::make_pair(tmpMatrix, tmpVector);
		}
	}
}
