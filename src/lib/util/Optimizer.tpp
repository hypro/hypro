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
		#ifdef USE_SMTRAT
		if(lp != nullptr)
			mSmtratSolver.clear();
		#endif
		deleteArrays();
		mConsistencyChecked = false;
		mConstraintsSet = false;
		mInitialized = false;
	}

	template<typename Number>
	EvaluationResult<Number> Optimizer<Number>::evaluate(const vector_t<Number>& _direction, bool overapproximate) const {
		if(!mConstraintsSet) {
			updateConstraints();
		}
		assert( _direction.rows() == mConstraintMatrix.cols() );
		EvaluationResult<Number> res;

		if( mConstraintMatrix.rows() == 0 ) {
			res.supportValue = 0;
			res.errorCode = SOLUTION::INFTY;
			res.optimumValue = vector_t<Number>::Zero(1);
			// std::cout << "INFTY" << std::endl;
			return res;
		}

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
				res.supportValue = carl::rationalize<Number>(glp_get_obj_val( lp ));
				res.errorCode = FEAS;
				vector_t<Number> glpkModel(mConstraintMatrix.cols());
				for(unsigned i=1; i <= mConstraintMatrix.cols(); ++i) {
					glpkModel(i-1) = carl::rationalize<Number>(glp_get_col_prim(lp, i));
				}
				res.optimumValue = glpkModel;
				break;
			}
			case GLP_UNBND: {
				res = EvaluationResult<Number>( 1, SOLUTION::INFTY );
				vector_t<Number> glpkModel(mConstraintMatrix.cols());
				for(unsigned i=1; i <= mConstraintMatrix.cols(); ++i) {
					glpkModel(i-1) = carl::rationalize<Number>(glp_get_col_prim(lp, i));
				}
				res.optimumValue = glpkModel;
				// std::cout << "glpk INFTY " << std::endl;
				break;
			}
			default:
				res = EvaluationResult<Number>( 0, SOLUTION::INFEAS );
				// std::cout << "glpk INFEAS " << std::endl;
		}

		// std::cout << "glpk optimumValue: " << res.optimumValue << ", glpk errorcode: " << res.errorCode << std::endl;

		#ifdef USE_SMTRAT
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

		// std::cout << "(push)" << std::endl;
		// std::cout << ((smtrat::FormulaT)simplex.formula()).toString( false, 1, "", true, false, true, true ) << std::endl;
		// std::cout << "(maximize " << objective.toString(false,true) << ")" << std::endl;

		smtrat::Answer smtratCheck = simplex.check();

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
		#endif // USE_SMTRAT

		// if there is a valid solution (FEAS), it implies the optimumValue is set.
		assert(res.errorCode  != FEAS || (res.optimumValue.rows() > 1 || (res.optimumValue != vector_t<Number>::Zero(0) && res.supportValue > 0 )));
		assert(res.errorCode  != FEAS || checkPoint(Point<Number>(res.optimumValue)));
		return res;
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

		#ifdef USE_SMTRAT
		#ifdef RECREATE_SOLVER
		smtrat::SimplexSolver simplex;
		std::unordered_map<smtrat::FormulaT, std::size_t> formulaMapping = createFormula(mConstraintMatrix, mConstraintVector);
		for(const auto& constraintPair : formulaMapping) {
			simplex.inform(constraintPair.first);
			simplex.add(constraintPair.first, false);
		}
		smtrat::Answer sol = simplex.check();
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
		#else // USE_SMTRAT
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

		#ifdef USE_SMTRAT
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
		#else // USE_SMTRAT

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

		#ifdef USE_SMTRAT
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

		#ifdef USE_SMTRAT
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
		//std::cout << "Original Formula: " << std::endl;
		//simplex.printAssertions();

		std::size_t formulaSize = simplex.formula().size();
		for(auto formulaIt = simplex.formulaBegin(); count < formulaSize; ++count) {
			smtrat::FormulaT originalConstraint = (*formulaIt).formula();
			smtrat::FormulaT negatedConstraint = smtrat::FormulaT( (*formulaIt).formula().constraint().lhs(), carl::invertRelation( (*formulaIt).formula().constraint().relation() ) );
			formulaIt = simplex.remove(formulaIt);
			simplex.inform(negatedConstraint);
			simplex.add(negatedConstraint, false);

			//std::cout << "Modified Formula: " << negatedConstraint << std::endl;

			smtrat::Answer isRedundant = simplex.check();
			assert(isRedundant != smtrat::Answer::UNKNOWN);
			if(isRedundant == smtrat::Answer::UNSAT){
				assert(formulaMapping.find(originalConstraint) != formulaMapping.end());
				assert(unsigned(formulaMapping.at(originalConstraint)) < mConstraintMatrix.rows());
				res.push_back(formulaMapping.at(originalConstraint));
			}

			assert(*(--(simplex.formula().end())) == negatedConstraint);
			simplex.remove(--(simplex.formulaEnd()));
			simplex.deinform(negatedConstraint);
			simplex.add(originalConstraint, false);
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
		#endif // USE_SMTRAT

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
			glp_set_prob_name( lp, "hpoly" );
			glp_set_obj_dir( lp, GLP_MAX );
			glp_term_out( GLP_OFF );
			#ifdef USE_SMTRAT
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
				glp_delete_prob(lp);
				deleteArrays();

				// TODO: can we directly reset stuff?
				lp = glp_create_prob();
				glp_set_prob_name( lp, "hpoly" );
				glp_set_obj_dir( lp, GLP_MAX );
				glp_term_out( GLP_OFF );

				#ifdef USE_SMTRAT
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
				createArrays( numberOfConstraints * mConstraintMatrix.cols() );

				// convert constraint matrix
				ia[0] = 0;
				ja[0] = 0;
				ar[0] = 0;
				for ( unsigned i = 0; i < numberOfConstraints * mConstraintMatrix.cols(); ++i ) {
					ia[i + 1] = ( int( i / mConstraintMatrix.cols() ) ) + 1;
					// std::cout << __func__ << " set ia[" << i+1 << "]= " << ia[i+1];
					ja[i + 1] = ( int( i % mConstraintMatrix.cols() ) ) + 1;
					// std::cout << ", ja[" << i+1 << "]= " << ja[i+1];
					ar[i + 1] = carl::toDouble( mConstraintMatrix.row(ia[i + 1] - 1)( ja[i + 1] - 1 ) );
					//ar[i + 1] = double( mHPlanes[ia[i + 1] - 1].normal()( ja[i + 1] - 1 ) );
					// std::cout << ", ar[" << i+1 << "]=" << ar[i+1] << std::endl;
				}

				glp_load_matrix( lp, numberOfConstraints * mConstraintMatrix.cols(), ia, ja, ar );
				glp_term_out(GLP_OFF);
				for ( unsigned i = 0; i < mConstraintMatrix.cols(); ++i ) {
					glp_set_col_bnds( lp, i + 1, GLP_FR, 0.0, 0.0 );
					glp_set_obj_coef( lp, i + 1, 1.0 ); // not needed?
				}

				#ifdef USE_SMTRAT
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

#ifdef USE_SMTRAT
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
	EvaluationResult<Number> Optimizer<Number>::extractSolution(const smtrat::SimplexSolver& solver, const smtrat::Poly& objective) const {
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
		}
		return res;
	}
#endif

	template <typename Number>
	void Optimizer<Number>::createArrays( unsigned size ) const {
		ia = new int[size + 1];
		ja = new int[size + 1];
		ar = new double[size + 1];
	}

	template <typename Number>
	void Optimizer<Number>::deleteArrays() const {
		delete[] ia;
		delete[] ja;
		delete[] ar;
	}
} // namespace hypro
