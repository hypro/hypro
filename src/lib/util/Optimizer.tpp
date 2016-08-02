#include "Optimizer.h"
#include "VariablePool.h"

namespace hypro {

	template<typename Number>
	const matrix_t<Number>& Optimizer<Number>::matrix() const {
		return mConstraintMatrix;
	}

	template<typename Number>
	const vector_t<Number>& Optimizer<Number>::vector() const {
		return mConstraintVector;
	}

	template<typename Number>
	void Optimizer<Number>::setMatrix(const matrix_t<Number>& _matrix) {
		if(mConstraintMatrix != _matrix){
			mConstraintsSet = false;
			mConsistencyChecked = false;
			mConstraintMatrix = _matrix;
		}
	}

	template<typename Number>
	void Optimizer<Number>::setVector(const vector_t<Number>& _vector) {
		if(mConstraintVector != _vector){
			mConstraintsSet = false;
			mConsistencyChecked = false;
			mConstraintVector = _vector;
		}
	}

	template<typename Number>
	void Optimizer<Number>::clear() {
		mConstraintMatrix = matrix_t<Number>::Zero(1,1);
		mConstraintVector = vector_t<Number>::Zero(1);
		#ifdef HYPRO_USE_SMTRAT
		if(lp != nullptr)
			mSmtratSolver.clear();
		#endif
		deleteArrays();
		mConsistencyChecked = false;
		mConstraintsSet = false;
		mInitialized = false;
	}

	template<typename Number>
	EvaluationResult<Number> Optimizer<Number>::evaluate(const vector_t<Number>& _direction, bool ) const {
		if(!mConstraintsSet) {
			updateConstraints();
		}
		assert( _direction.rows() == mConstraintMatrix.cols() );

#ifdef DEBUG_MSG
		std::cout << __func__ << ": in direction " << _direction << std::endl;
#endif

		if( mConstraintMatrix.rows() == 0 ) {
			// std::cout << "INFTY" << std::endl;
			return EvaluationResult<Number>(0,vector_t<Number>::Zero(1), SOLUTION::INFTY);
		}

#if defined(HYPRO_USE_SMTRAT) || defined(HYPRO_USE_Z3)
		EvaluationResult<Number> res;
#endif

		// setup glpk
		for ( unsigned i = 0; i < mConstraintMatrix.cols(); i++ ) {
			glp_set_col_bnds( lp, i + 1, GLP_FR, 0.0, 0.0 );
			glp_set_obj_coef( lp, i + 1, carl::toDouble( _direction( i ) ) );
		}
		/* solve problem */
		glp_simplex( lp, NULL );

		// display potential problems
		switch ( glp_get_status( lp ) ) {
			case GLP_OPT:
			case GLP_FEAS: {
				vector_t<Number> glpkModel(mConstraintMatrix.cols());
				for(unsigned i=1; i <= mConstraintMatrix.cols(); ++i) {
					glpkModel(i-1) = carl::rationalize<Number>(glp_get_col_prim(lp, i));
				}
#if defined(HYPRO_USE_SMTRAT) || defined(HYPRO_USE_Z3)
				res.supportValue = carl::rationalize<Number>(glp_get_obj_val( lp ));
				res.errorCode = FEAS;
				res.optimumValue = glpkModel;
#else
				return EvaluationResult<Number>(carl::rationalize<Number>(glp_get_obj_val( lp )), glpkModel, SOLUTION::FEAS);
#endif
				break;
			}
			case GLP_UNBND: {
				vector_t<Number> glpkModel(mConstraintMatrix.cols());
				for(unsigned i=1; i <= mConstraintMatrix.cols(); ++i) {
					glpkModel(i-1) = carl::rationalize<Number>(glp_get_col_prim(lp, i));
				}
#if defined(HYPRO_USE_SMTRAT) || defined(HYPRO_USE_Z3)
				res = EvaluationResult<Number>( 1, SOLUTION::INFTY );
				res.optimumValue = glpkModel;
#else
				return EvaluationResult<Number>(1, glpkModel, SOLUTION::INFTY);
#endif
				// std::cout << "glpk INFTY " << std::endl;
				break;
			}
			default:
#if defined(HYPRO_USE_SMTRAT) || defined(HYPRO_USE_Z3)
				res = EvaluationResult<Number>( 0, SOLUTION::INFEAS );
#else
				return EvaluationResult<Number>(0, vector_t<Number>::Zero(1), SOLUTION::INFEAS);
#endif
				// std::cout << "glpk INFEAS " << std::endl;
		}

#ifdef DEBUG_MSG
		std::cout << "glpk optimumValue: " << res.optimumValue << ", glpk errorcode: " << res.errorCode << std::endl;
#endif
		#ifdef HYPRO_USE_Z3

		z3Context c;
		z3::optimize z3Optimizer(c);
		std::vector<z3::expr> variables;

		// create formula and objective
		std::pair<z3::expr, z3::expr> formulaObjectivePair = createFormula<Number>(mConstraintMatrix, mConstraintVector, _direction, c, variables);

		// inform and add constraints
		z3Optimizer.add(formulaObjectivePair.first);

		// optimize with objective function
		z3::optimize::handle result = z3Optimizer.maximize(formulaObjectivePair.second);

		std::cout << "Optimizer String: " << z3Optimizer << std::endl;

		// verify and set result
		if(z3::sat == z3Optimizer.check()) {
			z3::expr z3res = z3Optimizer.upper(result);
			assert(z3res.is_arith());

			// check for infinity
			if(Z3_get_numeral_string(c,z3res) == nullptr) {
				std::cout << "INFTY !!!" << std::endl;
			}

			// TODO: Fixme!
			//std::cout << "Result without string conversion: " << z3res << std::endl;
			//std::cout << "Result without decimal: " << Z3_get_numeral_string(c,z3res) << std::endl;
			//std::cout << "Result: " << Z3_get_numeral_decimal_string(c,z3res,1000) << std::endl;

			z3::model m = z3Optimizer.get_model();
			//std::cout << "Model: " << m << std::endl;
			assert(m.num_consts() == mConstraintMatrix.cols());
			assert(variables.size() == m.num_consts());
			vector_t<Number> pointCoordinates = vector_t<Number>(mConstraintMatrix.cols());
			for( unsigned i = 0; i < variables.size(); ++i ){
				z3::func_decl tmp = variables.at(i).decl();
				//std::cout << Z3_get_numeral_decimal_string(c, m.get_const_interp(m.get_const_decl(i)), 100) << std::endl;
				assert(Z3_model_get_const_interp(c,m,tmp) != nullptr);
				pointCoordinates(i) = Number(Z3_get_numeral_string(c,m.get_const_interp(tmp)));
			}
			res.errorCode = SOLUTION::FEAS;
			std::cout << z3res << std::endl;
			std::cout << "Point satisfying res: " << pointCoordinates << std::endl;
			std::cout << "Result numeral string: " << Z3_get_numeral_string(c,z3res) << std::endl;
			res.supportValue = Number(Z3_get_numeral_string(c,z3res));
			res.optimumValue = pointCoordinates;
		}

		#elif defined(HYPRO_USE_SMTRAT) // else if HYPRO_USE_SMTRAT
		smtrat::Poly objective = createObjective(_direction);
		#ifdef RECREATE_SOLVER
		smtrat::SimplexSolver simplex;
		simplex.push();
		std::unordered_map<smtrat::FormulaT, std::size_t> formulaMapping = createFormula(mConstraintMatrix, mConstraintVector);
		for(const auto& constraintPair : formulaMapping) {
			simplex.inform(constraintPair.first);
			simplex.add(constraintPair.first, false);
		}
		// std::cout << "Informed basic constraints defining the object." << std::endl;

		#ifdef USE_PRESOLUTION
		simplex.push();
		// Add a constraint forcing SMT-RAT to improve the solution calculated by glpk (increase precision).
		if(res.errorCode == FEAS) {
			addPresolution(simplex,res,_direction,objective);
		} else if( res.errorCode == INFEAS) {
			if(simplex.check() == smtrat::Answer::UNSAT){
				return res; // glpk correctly detected infeasibility.
			} // if glpk falsely detected infeasibility, we cope with this case below.
		} else { // if glpk already detected unboundedness we return its result.
			return res;
		}
		#endif // USE_PRESOLUTION
		simplex.addObjective(objective, false);

		#ifdef DEBUG_MSG
		std::cout << "(push)" << std::endl;
		std::cout << ((smtrat::FormulaT)simplex.formula()).toString( false, 1, "", true, false, true, true ) << std::endl;
		std::cout << "(maximize " << objective.toString(false,true) << ")" << std::endl;
		#endif

		smtrat::Answer smtratCheck = simplex.check();

		#ifdef DEBUG_MSG
		std::cout << "Done checking." << std::endl;
		#endif

		switch(smtratCheck) {
			case smtrat::Answer::SAT:{
				// std::cout << "smtrat: SAT" << std::endl;
				res = extractSolution(simplex,objective);
				assert(checkPoint(Point<Number>(res.optimumValue)));
				break;
			}
			default:{
				#ifdef USE_PRESOLUTION
				// in this case the constraints introduced by the presolution made the problem infeasible
				simplex.pop();
				simplex.addObjective(objective, false);
				// std::cout << "Cleared formula: " << std::endl;
				// std::cout << ((smtrat::FormulaT)simplex.formula()).toString( false, 1, "", true, false, true, true ) << std::endl;
				// std::cout << "(maximize " << objective.toString(false,true) << ")" << std::endl;
				smtratCheck = simplex.check();
				assert(smtratCheck != smtrat::Answer::UNKNOWN);
				if(smtratCheck == smtrat::Answer::SAT) {
					res = extractSolution(simplex,objective);
					assert(checkPoint(Point<Number>(res.optimumValue)));
				} else {
					assert(smtratCheck == smtrat::Answer::UNSAT);
					return EvaluationResult<Number>( 0, SOLUTION::INFEAS );
				}
				#else // USE_PRESOLUTION
				// the original constraint system is UNSAT. (LRA Module cannot return UNKNOWN, except for inequality constraints (!=)
				assert(smtratCheck == smtrat::Answer::UNSAT);
				return EvaluationResult<Number>( 0, SOLUTION::INFEAS );
				#endif // USE_PRESOLUTION
				break;
			}
		}

		#else // RECREATE_SOVER
		mSmtratSolver.push();
		#ifdef USE_PRESOLUTION

		// Add a constraint forcing SMT-RAT to improve the solution calculated by glpk (increase precision).
		if(res.errorCode == FEAS) {
			addPresolution(mSmtratSolver,res,_direction,objective);
		} else if( res.errorCode == INFEAS) {
			if(mSmtratSolver.check() == smtrat::Answer::UNSAT) {
				return res;
			}
		} else { // if glpk detected unboundedness we return.
			return res;
		}
		#endif // USE_PRESOLUTION
		mSmtratSolver.addObjective(objective, false);
		//std::cout << "(push)" << std::endl;
		//std::cout << ((smtrat::FormulaT)mSmtratSolver.formula()).toString( false, 1, "", true, false, true, true ) << std::endl;
		//std::cout << "(maximize " << objective.toString(false,true) << ")" << std::endl;

		smtrat::Answer smtratCheck = mSmtratSolver.check();
		switch(smtratCheck) {
			case smtrat::Answer::SAT:{
				res = extractSolution(mSmtratSolver,objective);
				assert(checkPoint(Point<Number>(res.optimumValue)));
				break;
			}
			default:{
				#ifdef USE_PRESOLUTION
				// GLPK Solution was missleading, restart without it
				mSmtratSolver.pop();
				mSmtratSolver.addObjective(objective, false);
				//std::cout << "Cleared formula: " << std::endl;
				//std::cout << ((smtrat::FormulaT)mSmtratSolver.formula()).toString( false, 1, "", true, false, true, true ) << std::endl;
				//std::cout << "(maximize " << objective.toString(false,true) << ")" << std::endl;

				smtratCheck = mSmtratSolver.check();
				assert(smtratCheck != smtrat::Answer::UNKNOWN);
				if(smtratCheck == smtrat::Answer::SAT) {
					res = extractSolution(mSmtratSolver,objective);
					assert(checkPoint(Point<Number>(res.optimumValue)));
				} else {
					assert(smtratCheck == smtrat::Answer::UNSAT);
					return EvaluationResult<Number>( 0, SOLUTION::INFEAS );
				}
				#endif // USE_PRESOLUTION
				// the original constraint system is UNSAT. (LRA Module cannot return UNKNOWN, except for inequality constraints (!=)
				assert(smtratCheck == smtrat::Answer::UNSAT);
				return EvaluationResult<Number>( 0, SOLUTION::INFEAS );
				break;
			}
		}
		// cleanup: Remove optimization function and glpk pre-results, if added
		mSmtratSolver.pop();
		#endif // RECREATE_SOLVER
		#endif // HYPRO_USE_SMTRAT

#if defined(HYPRO_USE_SMTRAT) || defined(HYPRO_USE_Z3)
		// if there is a valid solution (FEAS), it implies the optimumValue is set.
		assert(res.errorCode  != FEAS || (res.optimumValue.rows() > 1 || (res.optimumValue != vector_t<Number>::Zero(0) && res.supportValue > 0 )));
		//std::cout << "Point: " << res.optimumValue << " contained: " << checkPoint(Point<Number>(res.optimumValue)) << ", Solution is feasible: " << (res.errorCode==SOLUTION::FEAS) << std::endl;
		assert(res.errorCode  != FEAS || checkPoint(Point<Number>(res.optimumValue)));
		return res;
#endif
	}

	template<typename Number>
	bool Optimizer<Number>::checkConsistency() const {
		if(!mConstraintsSet) {
			updateConstraints();
		}

		if(mConstraintMatrix.rows() == 0) {
			mLastConsistencyAnswer = SOLUTION::FEAS;
			return true;
		}

		#ifdef HYPRO_USE_SMTRAT
		#ifdef RECREATE_SOLVER
        //std::cout << mConstraintMatrix << std::endl << mConstraintVector << std::endl;
		smtrat::SimplexSolver simplex;
		std::unordered_map<smtrat::FormulaT, std::size_t> formulaMapping = createFormula(mConstraintMatrix, mConstraintVector);
		for(const auto& constraintPair : formulaMapping) {
			simplex.inform(constraintPair.first);
			simplex.add(constraintPair.first, false);
			//std::cout << constraintPair.first << std::endl;
		}
		smtrat::Answer sol = simplex.check();
		//std::cout << "smtrat says " << sol << std::endl;
		return (sol == smtrat::Answer::SAT);

		#else // RECREATE_SOLVER
		if(!mConsistencyChecked) { // If this setup has already been checked, avoid call.
			//std::cout << "Check: " << std::endl;
			//std::cout << ((smtrat::FormulaT)mSmtratSolver.formula()).toString( false, 1, "", true, false, true, true ) << std::endl;

			smtrat::Answer tmp = mSmtratSolver.check();
			switch (tmp) {
				case smtrat::Answer::UNSAT: {
					mLastConsistencyAnswer = SOLUTION::INFEAS;
					break;
				}
				case smtrat::Answer::SAT: {
					mLastConsistencyAnswer = SOLUTION::FEAS;
					break;
				}
				default:
					mLastConsistencyAnswer = SOLUTION::UNKNOWN;
			}
			mConsistencyChecked = true;
		}
		#endif // RECREATE_SOLVER
        #elif defined(USE_Z3)
		z3::context c;
		z3::optimize z3Optimizer(c);

		// create formula and objective
		z3::expr_vector constraintsExpression = createFormula<Number>(mConstraintMatrix, mConstraintVector, c);
		//std::cout << "constraints " << constraintsExpression << std::endl;
		//std::cout << mConstraintMatrix << std::endl << mConstraintVector << std::endl;
		for (unsigned i = 0; i < constraintsExpression.size(); i++) {
			z3Optimizer.add(constraintsExpression[i]);
			//std::cout << "constraint " << constraintsExpression[i] << std::endl;
		}
		z3::check_result res = z3Optimizer.check();
		//std::cout << "result: " << res << std::endl;
		return (z3::sat == res);

		#else // HYPRO_USE_SMTRAT
		if(!mConsistencyChecked){
			glp_exact( lp, NULL );
			mLastConsistencyAnswer = glp_get_status(lp) == GLP_NOFEAS ? SOLUTION::INFEAS : SOLUTION::FEAS;
			mConsistencyChecked = true;
		}
		#endif
		return (mLastConsistencyAnswer == SOLUTION::FEAS);
	}

	template<typename Number>
	bool Optimizer<Number>::checkPoint(const Point<Number>& _point) const {
		if(!mConstraintsSet) {
			updateConstraints();
		}
		if(mConstraintMatrix.rows() == 0) {
			mLastConsistencyAnswer = SOLUTION::FEAS;
			return true;
		}

		#ifdef HYPRO_USE_Z3

		z3Context c;
		z3::solver z3Solver(c);

		// create formula and objective
		z3::expr formula = createFormula<Number>(_point,  mConstraintMatrix, mConstraintVector, c);

		// inform and add constraints
		z3Solver.add(formula);

		// verify and set result
		if(z3::sat == z3Solver.check()) {

			return true;
		}
		return false;

		#elif defined(HYPRO_USE_SMTRAT) // else if HYPRO_USE_SMTRAT
		#ifdef RECREATE_SOLVER
		smtrat::SimplexSolver simplex;
		std::unordered_map<smtrat::FormulaT, std::size_t> formulaMapping = createFormula(mConstraintMatrix, mConstraintVector);
		for(const auto& constraintPair : formulaMapping) {
			simplex.inform(constraintPair.first);
			simplex.add(constraintPair.first, false);
		}
		std::unordered_map<smtrat::FormulaT, std::size_t> pointMapping = createFormula(_point);
		for(const auto& constraintPair : pointMapping) {
			simplex.inform(constraintPair.first);
			simplex.add(constraintPair.first, false);
		}
		//std::cout << "Check: " << std::endl;
		//std::cout << ((smtrat::FormulaT)simplex.formula()).toString( false, 1, "", true, false, true, true ) << std::endl;
		smtrat::Answer sol = simplex.check();
		assert(sol != smtrat::Answer::UNKNOWN);
		return (sol == smtrat::Answer::SAT);
		#else // RECREATE_SOLVER
		mSmtratSolver.push();
		std::unordered_map<smtrat::FormulaT, std::size_t> pointMapping = createFormula(_point);
		for(const auto& constraintPair : pointMapping) {
			mSmtratSolver.inform(constraintPair.first);
			mSmtratSolver.add(constraintPair.first, false);
		}
		//std::cout << "Check: " << std::endl;
		//std::cout << ((smtrat::FormulaT)mSmtratSolver.formula()).toString( false, 1, "", true, false, true, true ) << std::endl;
		smtrat::Answer tmp = mSmtratSolver.check();
		mSmtratSolver.pop();
		return (tmp == smtrat::Answer::SAT);
		#endif // RECREATE_SOLVER
		#else // HYPRO_USE_SMTRAT

		// set point
		assert(mConstraintMatrix.cols() == _point.rawCoordinates().rows());
		for ( unsigned i = 0; i < mConstraintMatrix.cols(); ++i ) {
			glp_set_col_bnds( lp, i + 1, GLP_FX, carl::toDouble(_point.rawCoordinates()(i)), 0.0 );
			glp_set_obj_coef( lp, i + 1, 1.0 ); // not needed?
		}

		glp_exact( lp, NULL );
		return (glp_get_status(lp) != GLP_NOFEAS);
		#endif
	}

	template<typename Number>
	EvaluationResult<Number> Optimizer<Number>::getInternalPoint() const {
		if(!mConstraintsSet) {
			updateConstraints();
		}

		if(mConstraintMatrix.rows() == 0) {
			mLastConsistencyAnswer = SOLUTION::FEAS;
			mConsistencyChecked = true;
			return EvaluationResult<Number>(vector_t<Number>::Zero(1), SOLUTION::FEAS);
		}

		EvaluationResult<Number> res;

		#ifdef HYPRO_USE_SMTRAT
		#ifdef RECREATE_SOLVER
		smtrat::SimplexSolver simplex;
		std::unordered_map<smtrat::FormulaT, std::size_t> formulaMapping = createFormula(mConstraintMatrix, mConstraintVector);
		for(const auto& constraintPair : formulaMapping) {
			simplex.inform(constraintPair.first);
			simplex.add(constraintPair.first, false);
		}
		smtrat::Answer sol = simplex.check();
		if(sol == smtrat::Answer::UNSAT){
			res.errorCode = SOLUTION::INFEAS;
			mLastConsistencyAnswer = SOLUTION::INFEAS;
			return res;
		} else {
			mLastConsistencyAnswer = SOLUTION::FEAS;
		}
		mConsistencyChecked = true;
		smtrat::Model assignment = mSmtratSolver.model();
		vector_t<Number> point;
		for(unsigned d = 0; d < mConstraintMatrix.cols(); ++d){
			// if the variable did not occur in the current call, set to 0.
			if(assignment.find(hypro::VariablePool::getInstance().carlVarByIndex(d)) == assignment.end()){
				point(d) = 0;
			} else {
				assert(assignment.find(hypro::VariablePool::getInstance().carlVarByIndex(d)) != assignment.end());
				assert(assignment.find(hypro::VariablePool::getInstance().carlVarByIndex(d))->second.isRational());
				point(d) = carl::convert<smtrat::Rational, Number>(assignment.find(hypro::VariablePool::getInstance().carlVarByIndex(d))->second.asRational());
			}
		}
		assert(checkPoint(point));
		return EvaluationResult<Number>(point, mLastConsistencyAnswer);

		#else

		smtrat::Answer tmp = mSmtratSolver.check();
		switch (tmp) {
			case smtrat::Answer::UNSAT: {
				mLastConsistencyAnswer = SOLUTION::INFEAS;
				mConsistencyChecked = true;
				res.errorCode = SOLUTION::INFEAS;
				return res;
			}
			case smtrat::Answer::SAT: {
				mLastConsistencyAnswer = SOLUTION::FEAS;
				mConsistencyChecked = true;
				smtrat::Model assignment = mSmtratSolver.model();
				vector_t<Number> point;
				for(unsigned d = 0; d < mConstraintMatrix.cols(); ++d){
					// if the variable did not occur in the current call, set to 0.
					if(assignment.find(hypro::VariablePool::getInstance().carlVarByIndex(d)) == assignment.end()){
						point(d) = 0;
					} else {
						assert(assignment.find(hypro::VariablePool::getInstance().carlVarByIndex(d)) != assignment.end());
						assert(assignment.find(hypro::VariablePool::getInstance().carlVarByIndex(d))->second.isRational());
						point(d) = carl::convert<smtrat::Rational, Number>(assignment.find(hypro::VariablePool::getInstance().carlVarByIndex(d))->second.asRational());
					}
				}
				res.optimumValue = point;
				res.errorCode = mLastConsistencyAnswer;
				assert(checkPoint(Point<Number>(res.optimumValue)));
				break;
			}
			default:
				mLastConsistencyAnswer = SOLUTION::UNKNOWN;
		}
		return res;

		#endif
		#else

		// TODO: Avoid re-call here too!
		glp_exact( lp, NULL );
		//return (glp_get_status(lp) != GLP_NOFEAS);

		//TODO: Undone!
		return res;
		#endif
	}

	template<typename Number>
	std::vector<std::size_t> Optimizer<Number>::redundantConstraints() const {
		std::vector<std::size_t> res;
		if(!mConstraintsSet) {
			updateConstraints();
		}
		if(mConstraintMatrix.rows() == 0) {
			return res;
		}

#ifdef HYPRO_USE_Z3
		z3Context c;
		z3::solver z3Solver(c);
		z3Solver.push();

		// TODO: ATTENTION: This relies upon that Z3 maintains the order of the constraints!
		z3::expr_vector formulas = createFormula(mConstraintMatrix, mConstraintVector, c );

		if(formulas.size() == 1){

			return res;
		}

		assert(unsigned(formulas.size() + res.size()) == mConstraintMatrix.rows());
		for(unsigned i = 0; i < formulas.size(); ++i) {
			z3Solver.add(formulas[i]);
		}

		// first call to check satisfiability
		z3::check_result firstCheck = z3Solver.check();
		#ifdef DEBUG_MSG
		std::cout << __func__ << " Original problem solution: " << firstCheck << std::endl;
		#endif
		switch (firstCheck) {
				case z3::check_result::unsat: {
		
					return res;
					break;
				}
				case z3::check_result::sat: {
					break;
				}
				default: {
					assert(false);
					break;
				}
		}

		z3Solver.pop();

		for(unsigned constraintIndex = 0; constraintIndex < formulas.size(); ++constraintIndex) {
			z3::expr originalConstraint = formulas[constraintIndex];
			#ifdef DEBUG_MSG
			std::cout << __func__ << " Original constraint: " << originalConstraint << std::endl;
			#endif
			z3::expr negatedConstraint = !originalConstraint;

			z3Solver.push();
			for(unsigned i = 0; i < formulas.size(); ++i){
				if(i == constraintIndex) {
					z3Solver.add(negatedConstraint);
				} else {
					z3Solver.add(formulas[i]);
				}
			}

			z3::check_result isRedundant = z3Solver.check();
			assert(isRedundant != z3::check_result::unknown);
			if(isRedundant == z3::check_result::unsat){
				#ifdef DEBUG_MSG
				std::cout << __func__ << " is redundant." << std::endl;
				#endif
				res.push_back(constraintIndex);
			}

			z3Solver.pop();
		}

		#elif defined(HYPRO_USE_SMTRAT) // else if HYPRO_USE_SMTRAT
		#ifdef RECREATE_SOLVER
		smtrat::SimplexSolver simplex;
		const std::unordered_map<smtrat::FormulaT, std::size_t> formulaMapping = createFormula(mConstraintMatrix, mConstraintVector);

		if(formulaMapping.size() == 1){
			return res;
		}

		if(unsigned(formulaMapping.size()) != mConstraintMatrix.rows()) {
			for(unsigned cnt = 0; cnt < mConstraintMatrix.rows(); ++cnt) {
				bool found = false;
				for(const auto& constraintPair : formulaMapping) {
					if(constraintPair.second == cnt){
						found = true;
						break;
					}
				}
				if(!found) {
					res.push_back(cnt);
				}
				if(res.size() == (mConstraintMatrix.rows() - formulaMapping.size()) )
					break;
			}
		}

		assert(unsigned(formulaMapping.size() + res.size()) == mConstraintMatrix.rows());
		for(const auto& constraintPair : formulaMapping) {
			simplex.inform(constraintPair.first);
			simplex.add(constraintPair.first, false);
		}

		// first call to check satisfiability
		smtrat::Answer firstCheck = simplex.check();
		#ifdef DEBUG_MSG
		std::cout << __func__ << " Original problem solution: " << firstCheck << std::endl;
		#endif
		switch (firstCheck) {
				case smtrat::Answer::UNSAT: {
					return res;
					break;
				}
				case smtrat::Answer::SAT: {
					break;
				}
				default: {
					assert(false);
					break;
				}
		}

		std::size_t count = 0;
		#ifdef DEBUG_MSG
		std::cout << __func__ << " Original Formula: " << std::endl;
		simplex.printAssertions();
		#endif

		std::size_t formulaSize = simplex.formula().size();
		for(auto formulaIt = simplex.formulaBegin(); count < formulaSize; ++count) {
			smtrat::FormulaT originalConstraint = (*formulaIt).formula();
			#ifdef DEBUG_MSG
			std::cout << __func__ << " Original constraint: " << originalConstraint << std::endl;
			#endif
			smtrat::FormulaT negatedConstraint = smtrat::FormulaT( (*formulaIt).formula().constraint().lhs(), carl::turnAroundRelation( (*formulaIt).formula().constraint().relation() ) );
			unsigned currentFormulaSize = simplex.formula().size();
			simplex.inform(negatedConstraint);
			simplex.add(negatedConstraint, false);

			if(simplex.formula().size() > currentFormulaSize) {
				formulaIt = simplex.remove(formulaIt);
				#ifdef DEBUG_MSG
				std::cout << __func__ << " Negated Constraint: " << negatedConstraint << std::endl;
				#endif

				smtrat::Answer isRedundant = simplex.check();
				assert(isRedundant != smtrat::Answer::UNKNOWN);
				if(isRedundant == smtrat::Answer::UNSAT){
					#ifdef DEBUG_MSG
					std::cout << __func__ << " is redundant." << std::endl;
					#endif
					assert(formulaMapping.find(originalConstraint) != formulaMapping.end());
					assert(unsigned(formulaMapping.at(originalConstraint)) < mConstraintMatrix.rows());
					res.push_back(formulaMapping.at(originalConstraint));
				}

				assert(*(--(simplex.formula().end())) == negatedConstraint);
				simplex.remove(--(simplex.formulaEnd()));
				simplex.deinform(negatedConstraint);
				simplex.add(originalConstraint, false);
			}else{
				formulaIt++;
			}

		}

		#else // RECREATE_SOLVER

		if(mCurrentFormula.getType() == carl::FormulaType::CONSTRAINT ){ // if there is only one constraint
			return res;
		}

		// first call to check satisfiability
		smtrat::Answer firstCheck;
		if(!mConsistencyChecked) { // If this setup has already been checked, avoid call.
			//std::cout << "Making first check." << std::endl;
			//std::cout << ((smtrat::FormulaT)mSmtratSolver.formula()).toString( false, 1, "", true, false, true, true ) << std::endl;
			firstCheck = mSmtratSolver.check();
			switch (firstCheck) {
				case smtrat::Answer::UNSAT: {
					mLastConsistencyAnswer = SOLUTION::INFEAS;
					// TODO: Return complement of infeasible subset indices.
					return res;
					break;
				}
				case smtrat::Answer::SAT: {
					mLastConsistencyAnswer = SOLUTION::FEAS;
					break;
				}
				default: {
					assert(false);
					break;
				}
			}
			mConsistencyChecked = true;
		}

		if(mLastConsistencyAnswer == SOLUTION::INFEAS){
			return res;
		}

		std::size_t count = 0;
		//std::cout << "Original Formula: " << std::endl;
		//mSmtratSolver.printAssertions();
		std::size_t formulaSize = mSmtratSolver.formula().size();
		for(auto formulaIt = mSmtratSolver.formulaBegin(); count < formulaSize; ) {
			smtrat::FormulaT originalConstraint = (*formulaIt).formula();
			smtrat::FormulaT negatedConstraint = smtrat::FormulaT( (*formulaIt).formula().constraint().lhs(), carl::invertRelation( (*formulaIt).formula().constraint().relation() ) );
			formulaIt = mSmtratSolver.remove(formulaIt);
			mSmtratSolver.inform(negatedConstraint);
			mSmtratSolver.add(negatedConstraint, false);

			//std::cout << "Modified Formula: " << negatedConstraint << std::endl;

			smtrat::Answer isRedundant = mSmtratSolver.check();
			assert(isRedundant != smtrat::Answer::UNKNOWN);
			if(isRedundant == smtrat::Answer::UNSAT)
				res.push_back(mFormulaMapping.at(originalConstraint));

			assert(*(--(mSmtratSolver.formula().end())) == negatedConstraint);
			mSmtratSolver.remove(--(mSmtratSolver.formulaEnd()));
			mSmtratSolver.deinform(negatedConstraint);
			mSmtratSolver.add(originalConstraint, false);
			++count;
		}
		#endif // RECREATE_SOLVER
		#endif // HYPRO_USE_SMTRAT

		//TODO: Currently this test only works while using SMTRAT

		std::sort(res.begin(), res.end());

		return res;
	}

	template<typename Number>
	void Optimizer<Number>::initialize() const {
		#ifdef LOGGING
		if (!carl::logging::logger().has("smtrat")) {
			carl::logging::logger().configure("smtrat", "smtrat.log");
		}
		if (!carl::logging::logger().has("stdout")) {
			carl::logging::logger().configure("stdout", std::cout);
		}
		carl::logging::logger().formatter("stdout")->printInformation = false;
		carl::logging::logger().filter("smtrat")
			("smtrat", carl::logging::LogLevel::LVL_INFO)
			("smtrat.cad", carl::logging::LogLevel::LVL_DEBUG)
			("smtrat.preprocessing", carl::logging::LogLevel::LVL_DEBUG)
		;
		carl::logging::logger().filter("stdout")
			("smtrat", carl::logging::LogLevel::LVL_DEBUG)
			("smtrat.module", carl::logging::LogLevel::LVL_INFO)
			("smtrat.parser", carl::logging::LogLevel::LVL_INFO)
			("smtrat.cad", carl::logging::LogLevel::LVL_DEBUG)
			("smtrat.preprocessing", carl::logging::LogLevel::LVL_DEBUG)
			("smtrat.strategygraph", carl::logging::LogLevel::LVL_DEBUG)
		;
		#endif

		if(!mInitialized) {
			/* create glpk problem */
			lp = glp_create_prob();
			glp_set_obj_dir( lp, GLP_MAX );
			glp_term_out( GLP_OFF );
			#ifdef HYPRO_USE_SMTRAT
			#ifndef RECREATE_SOLVER
			mSmtratSolver.push();
			#endif
			#endif
			mInitialized = true;
		}
	}

	template<typename Number>
	void Optimizer<Number>::updateConstraints() const {
		assert(!mConsistencyChecked || mConstraintsSet);
		bool alreadyInitialized = mInitialized;
		if(!mInitialized){
			initialize();
		}

		if(!mConstraintsSet){
			//std::cout << "!mConstraintsSet" << std::endl;

			if(alreadyInitialized) { // clean up old setup.
				//std::cout << "alreadyInitialized - Cleanup" << std::endl;
				deleteArrays();

				// TODO: can we directly reset stuff?
				glp_erase_prob(lp);
				glp_set_obj_dir( lp, GLP_MAX );
				glp_term_out( GLP_OFF );

				#ifdef HYPRO_USE_SMTRAT
				#ifndef RECREATE_SOLVER
				mSmtratSolver.pop();
				if(!mSmtratSolver.formula().empty()){
					//std::cout << "THIS SHOULD NOT HAPPEN -> INCORRECT TRACKING OF BT-POINTS." << std::endl;
					//std::cout << ((smtrat::FormulaT)mSmtratSolver.formula()).toString( false, 1, "", true, false, true, true ) << std::endl;
					mSmtratSolver.clear();
				}
				assert(mSmtratSolver.formula().empty());

				for(const auto& constraintPair : mFormulaMapping){
					mSmtratSolver.deinform(constraintPair.first);
				}

				mSmtratSolver.push();
				//std::cout << "Cleanup - done." << std::endl;
				#endif
				#endif
			}

			unsigned numberOfConstraints = mConstraintMatrix.rows();
			if(numberOfConstraints > 0) {
				// convert constraint constants
				glp_add_rows( lp, numberOfConstraints );
				for ( unsigned i = 0; i < numberOfConstraints; i++ ) {
					glp_set_row_bnds( lp, i + 1, GLP_UP, 0.0, carl::toDouble( mConstraintVector(i) ) );
				}
				// add cols here
				glp_add_cols( lp, mConstraintMatrix.cols() );
				unsigned cols = mConstraintMatrix.cols();
				createArrays( numberOfConstraints * cols );

				// convert constraint matrix
				ia[0] = 0;
				ja[0] = 0;
				ar[0] = 0;
				assert(mConstraintMatrix.size() == numberOfConstraints * cols);
				for ( unsigned i = 0; i < numberOfConstraints * cols; ++i ) {
					ia[i + 1] = ( int( i / cols ) ) + 1;
					// std::cout << __func__ << " set ia[" << i+1 << "]= " << ia[i+1];
					ja[i + 1] = ( int( i % cols ) ) + 1;
					// std::cout << ", ja[" << i+1 << "]= " << ja[i+1];
					ar[i + 1] = carl::toDouble( mConstraintMatrix.row(ia[i + 1] - 1)( ja[i + 1] - 1 ) );
					// TODO:: Assuming ColMajor storage alignment.
					assert(*(mConstraintMatrix.data()+(ja[i+1]*numberOfConstraints) - ia[i+1]) ==  mConstraintMatrix.row(ia[i + 1] - 1)( ja[i + 1] - 1 ));
					//std::cout << ", ar[" << i+1 << "]=" << ar[i+1] << std::endl;
					//std::cout << "Came from: " << mConstraintMatrix.row(ia[i + 1] - 1)( ja[i + 1] - 1 ) << std::endl;
				}

				glp_load_matrix( lp, numberOfConstraints * cols, ia, ja, ar );
				glp_term_out(GLP_OFF);
				for ( unsigned i = 0; i < cols; ++i ) {
					glp_set_col_bnds( lp, i + 1, GLP_FR, 0.0, 0.0 );
					glp_set_obj_coef( lp, i + 1, 1.0 ); // not needed?
				}

				#ifdef HYPRO_USE_SMTRAT
				#ifndef RECREATE_SOLVER
				mFormulaMapping = createFormula(mConstraintMatrix, mConstraintVector);

				//std::cout << "Set new constraints." << std::endl;

				for(const auto& constraintPair : mFormulaMapping) {
					mSmtratSolver.inform(constraintPair.first);
					mSmtratSolver.add(constraintPair.first, false);
				}

				//std::cout << "Set new constraints - done." << std::endl;

				mCurrentFormula = smtrat::FormulaT(mSmtratSolver.formula());
				#endif
				#endif
			}

			mConstraintsSet = true;
		}
	}

#ifdef HYPRO_USE_SMTRAT
	template<typename Number>
	void Optimizer<Number>::addPresolution(smtrat::SimplexSolver& solver, const EvaluationResult<Number>& glpkResult, const vector_t<Number>& direction, const smtrat::Poly& objective) const {
		// add assignment from glpk
		VariablePool& varPool = VariablePool::getInstance();
		for(unsigned i=0; i < mConstraintMatrix.cols(); ++i) {
			if(direction(i) != 0) {
				smtrat::Poly bound = varPool.carlVarByIndex(i) - carl::convert<Number,smtrat::Rational>(glpkResult.optimumValue(i));
				smtrat::FormulaT boundConstraint;
				if(direction(i) > 0 ) {
					boundConstraint = smtrat::FormulaT(bound, carl::Relation::GEQ);
				} else {
					boundConstraint = smtrat::FormulaT(bound, carl::Relation::LEQ);
				}
				//std::cout << "Inform and add bound constraint " << boundConstraint << std::endl;
				solver.inform(boundConstraint);
				solver.add(boundConstraint);
			}
		}

		// add constraint for improvement of glpk solution.
		smtrat::Poly preSolution = objective - carl::convert<Number, smtrat::Rational>(glpkResult.supportValue);
		smtrat::FormulaT preSolutionConstraint(preSolution, carl::Relation::GEQ);

		//std::cout << "Inform and add improvement constraint " << preSolutionConstraint << std::endl;

		solver.inform(preSolutionConstraint);
		solver.add(preSolutionConstraint);
	}

	template<typename Number>
	EvaluationResult<Number> Optimizer<Number>::extractSolution(smtrat::SimplexSolver& solver, const smtrat::Poly& objective) const {
		smtrat::ModelValue valuation = solver.optimum(objective);
		EvaluationResult<Number> res;
		assert(!valuation.isBool());
		assert(!valuation.isSqrtEx());
		assert(!valuation.isRAN());
		assert(!valuation.isBVValue());
		assert(!valuation.isSortValue());
		assert(!valuation.isUFModel());
		if(valuation.isMinusInfinity() || valuation.isPlusInfinity() ){
			// std::cout << __func__ << ": INFTY" << std::endl;
			res = EvaluationResult<Number>( 1, INFTY );
		} else {
			assert(valuation.isRational());
			res = EvaluationResult<Number>( carl::convert<smtrat::Rational, Number>(valuation.asRational()), FEAS );
			smtrat::Model assignment = solver.model();
			vector_t<Number> point = vector_t<Number>(mConstraintMatrix.cols());
			for(unsigned d = 0; d < mConstraintMatrix.cols(); ++d){
				// if the variable did not occur in the current call, set to 0.
				if(assignment.find(hypro::VariablePool::getInstance().carlVarByIndex(d)) == assignment.end()){
					point(d) = 0;
				} else {
					assert(assignment.find(hypro::VariablePool::getInstance().carlVarByIndex(d)) != assignment.end());
					assert(assignment.find(hypro::VariablePool::getInstance().carlVarByIndex(d))->second.isRational());
					point(d) = carl::convert<smtrat::Rational, Number>(assignment.find(hypro::VariablePool::getInstance().carlVarByIndex(d))->second.asRational());
				}
			}
			res.optimumValue = point;
			#ifdef VERIFY_RESULT
			solver.push();
			smtrat::FormulaT inversedObjective(objective-valuation.asRational(), carl::Relation::GREATER);
			solver.inform(inversedObjective);
			solver.add(inversedObjective);
			if(solver.check() != smtrat::Answer::UNSAT) {
				outputToSmtlibFormat(solver,fileCounter++, objective, filenamePrefix);
			}
			solver.pop();
			#endif
		}
		return res;
	}
#endif

	template <typename Number>
	void Optimizer<Number>::createArrays( unsigned size ) const {
		if(arraysCreated) {
			deleteArrays();
		}
		ia = new int[size + 1];
		ja = new int[size + 1];
		ar = new double[size + 1];
		arraysCreated = true;
	}

	template <typename Number>
	void Optimizer<Number>::deleteArrays() const {
		if(arraysCreated) {
			delete[] ia;
			delete[] ja;
			delete[] ar;
		}
		arraysCreated = false;
	}
} // namespace hypro
