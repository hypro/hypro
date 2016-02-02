#include "Optimizer.h"

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
	void Optimizer<Number>::setMatrix(const matrix_t<Number> _matrix) {
		if(mConstraintMatrix != _matrix){
			mConstraintsSet = false;
			mConsistencyChecked = false;
			mConstraintMatrix = _matrix;
		}
	}

	template<typename Number>
	void Optimizer<Number>::setVector(const vector_t<Number> _vector) {
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
	std::pair<Number, SOLUTION> Optimizer<Number>::evaluate(const vector_t<Number>& _direction, bool overapproximate) const {
		if(!mConstraintsSet)
			updateConstraints();

		assert( _direction.rows() == mConstraintMatrix.cols() );
		std::pair<Number,SOLUTION> res;

		// std::cout << "Set target: ";
		for ( unsigned i = 0; i < mConstraintMatrix.cols(); i++ ) {
			glp_set_col_bnds( lp, i + 1, GLP_FR, 0.0, 0.0 );
			glp_set_obj_coef( lp, i + 1, carl::toDouble( _direction( i ) ) );
		}

		/* solve problem */
		glp_simplex( lp, NULL );

		res.first = carl::rationalize<Number>(glp_get_obj_val( lp ));

		// display potential problems
		switch ( glp_get_status( lp ) ) {
			case GLP_OPT:
			case GLP_FEAS: {
				res.second = FEAS;
				break;
			}
			case GLP_UNBND: {
				res = std::make_pair( 1, INFTY );
				break;
			}
			default:
				res = std::make_pair( 0, INFEAS );
		}

		#ifdef USE_SMTRAT
		#ifdef RECREATE_SOLVER
		smtrat::SimplexSolver simplex;
		smtrat::FormulaT currentSystem = createFormula(mConstraintMatrix, mConstraintVector);
		simplex.inform(currentSystem);
		simplex.add(currentSystem);

		Poly objective = createObjective(_direction);

		#ifdef USE_PRESOLUTION
		// Get glpk model to initialize assignments for SMT-RAT.
		vector_t<double> glpkModel(mConstraintMatrix.cols());
		for(unsigned i=1; i <= mConstraintMatrix.cols(); ++i) {
			glpkModel(i-1) = glp_get_col_prim(lp, i);
		}

		// Add a constraint forcing SMT-RAT to improve the solution calculated by glpk (increase precision).
		if(res.second == FEAS) {
			// add assignment from glpk
			VariablePool& varPool = VariablePool::getInstance();
			for(unsigned i=0; i < mConstraintMatrix.cols(); ++i) {
				if(_direction(i) != 0) {
					Poly bound = varPool.carlVarByIndex(i) - carl::convert<double, smtrat::Rational>(glpkModel(i));
					smtrat::FormulaT boundConstraint;
					if(_direction(i) > 0 ) {
						boundConstraint = smtrat::FormulaT(bound, carl::Relation::GEQ);
					} else {
						boundConstraint = smtrat::FormulaT(bound, carl::Relation::LEQ);
					}
					simplex.inform(boundConstraint);
					simplex.add(boundConstraint);
				}
			}

			// add constraint for improvement of glpk solution.
			Poly tmpSolution = objective - carl::convert<Number, smtrat::Rational>(res.first);
			smtrat::FormulaT tmpSolutionConstraint(tmpSolution, carl::Relation::GEQ);
			simplex.inform(tmpSolutionConstraint);
			simplex.add(tmpSolutionConstraint);
		} else if( res.second == INFEAS) {
			if(simplex.check() == smtrat::Answer::UNSAT)
				return std::move(res);
		} else { // if glpk detected unboundedness we return. TODO: Is this correct?
			return std::move(res);
		}
		#endif
		simplex.addObjective(objective, false);

		//std::cout << "(push)" << std::endl;
		//std::cout << ((smtrat::FormulaT)simplex.formula()).toString( false, 1, "", true, false, true, true ) << std::endl;
		//std::cout << "(maximize " << objective.toString(false,true) << ")" << std::endl << "(check-sat)" << std::endl << "(pop)" << std::endl;

		smtrat::Answer smtratCheck = simplex.check();

		switch(smtratCheck) {
			case smtrat::Answer::SAT:{
				smtrat::ModelValue valuation = simplex.optimum(objective);
				assert(!valuation.isBool());
				assert(!valuation.isSqrtEx());
				assert(!valuation.isRAN());
				assert(!valuation.isBVValue());
				assert(!valuation.isSortValue());
				assert(!valuation.isUFModel());
				if(valuation.isMinusInfinity() || valuation.isPlusInfinity() ){
					res = std::make_pair( 1, INFTY );
				} else {
					assert(valuation.isRational());
					res = std::make_pair( carl::convert<Rational,Number>(valuation.asRational()), FEAS );
				}
				break;
			}
			default:{
			}
		}

		#else
		mSmtratSolver.push();

		// create objective function from _direction.
		Poly objective = createObjective(_direction);

		#ifdef USE_PRESOLUTION
		// Get glpk model to initialize assignments for SMT-RAT.
		vector_t<double> glpkModel(mConstraintMatrix.cols());
		for(unsigned i=1; i <= mConstraintMatrix.cols(); ++i) {
			glpkModel(i-1) = glp_get_col_prim(lp, i);
		}

		// Add a constraint forcing SMT-RAT to improve the solution calculated by glpk (increase precision).
		if(res.second == FEAS) {
			// add assignment from glpk
			VariablePool& varPool = VariablePool::getInstance();
			for(unsigned i=0; i < mConstraintMatrix.cols(); ++i) {
				if(_direction(i) != 0) {
					Poly bound = varPool.carlVarByIndex(i) - carl::convert<double, smtrat::Rational>(glpkModel(i));
					smtrat::FormulaT boundConstraint;
					if(_direction(i) > 0 ) {
						boundConstraint = smtrat::FormulaT(bound, carl::Relation::GEQ);
					} else {
						boundConstraint = smtrat::FormulaT(bound, carl::Relation::LEQ);
					}
					mSmtratSolver.inform(boundConstraint);
					mSmtratSolver.add(boundConstraint);
				}
			}

			// add constraint for improvement of glpk solution.
			Poly tmpSolution = objective - carl::convert<Number, smtrat::Rational>(res.first);
			smtrat::FormulaT tmpSolutionConstraint(tmpSolution, carl::Relation::GEQ);
			mSmtratSolver.inform(tmpSolutionConstraint);
			mSmtratSolver.add(tmpSolutionConstraint);
		} else if( res.second == INFEAS) {
			if(mSmtratSolver.check() == smtrat::Answer::UNSAT)
				return std::move(res);
		} else { // if glpk detected unboundedness we return. TODO: Is this correct?
			return std::move(res);
		}
		#endif

		mSmtratSolver.addObjective(objective, false);

		//std::cout << "(push)" << std::endl;
		//std::cout << ((smtrat::FormulaT)mSmtratSolver.formula()).toString( false, 1, "", true, false, true, true ) << std::endl;
		//std::cout << "(maximize " << objective.toString(false,true) << ")" << std::endl << "(check-sat)" << std::endl << "(pop)" << std::endl;

		smtrat::Answer smtratCheck = mSmtratSolver.check();

		switch(smtratCheck) {
			case smtrat::Answer::SAT:{
				smtrat::ModelValue valuation = mSmtratSolver.optimum(objective);
				assert(!valuation.isBool());
				assert(!valuation.isSqrtEx());
				assert(!valuation.isRAN());
				assert(!valuation.isBVValue());
				assert(!valuation.isSortValue());
				assert(!valuation.isUFModel());
				if(valuation.isMinusInfinity() || valuation.isPlusInfinity() ){
					res = std::make_pair( 1, INFTY );
				} else {
					assert(valuation.isRational());
					res = std::make_pair( carl::convert<Rational,Number>(valuation.asRational()), FEAS );
				}
				break;
			}
			default:{
			}
		}
		// cleanup: Remove optimization function and glpk pre-results, if added
		mSmtratSolver.pop();
		#endif
		#endif

		return std::move(res);
	}

	template<typename Number>
	bool Optimizer<Number>::checkConsistency() const {
		if(!mConstraintsSet)
			updateConstraints();

		#ifdef USE_SMTRAT
		#ifdef RECREATE_SOLVER
		smtrat::SimplexSolver simplex;
		smtrat::FormulaT currentSystem = createFormula(mConstraintMatrix, mConstraintVector);
		simplex.inform(currentSystem);
		simplex.add(currentSystem);
		smtrat::Answer sol = simplex.check();
		return (sol == smtrat::Answer::SAT);

		#else
		if(!mConsistencyChecked) { // If this setup has already been checked, avoid call.
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
		return (mLastConsistencyAnswer == SOLUTION::FEAS);
		#endif
		#else

		// TODO: Avoid re-call here too!
		glp_exact( lp, NULL );
		return (glp_get_status(lp) != GLP_NOFEAS);
		#endif
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
		if(!mInitialized)
			initialize();

		if(!mConstraintsSet){
			//std::cout << "!mConstraintsSet" << std::endl;

			if(alreadyInitialized) { // clean up old setup.
				//std::cout << "alreadyInitialized" << std::endl;
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
					std::cout << ((smtrat::FormulaT)mSmtratSolver.formula()).toString( false, 1, "", true, false, true, true ) << std::endl;
					mSmtratSolver.clear();
				}
				assert(mSmtratSolver.formula().empty());
				mSmtratSolver.push();
				#endif
				#endif
			}

			unsigned numberOfConstraints = mConstraintMatrix.rows();
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
				ia[i + 1] = ( (int)( i / mConstraintMatrix.cols() ) ) + 1;
				// std::cout << __func__ << " set ia[" << i+1 << "]= " << ia[i+1];
				ja[i + 1] = ( (int)( i % mConstraintMatrix.cols() ) ) + 1;
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
			smtrat::FormulaT currentSystem = createFormula(mConstraintMatrix, mConstraintVector);

			mSmtratSolver.inform(currentSystem);
			mSmtratSolver.add(currentSystem);
			#endif
			#endif

			mConstraintsSet = true;
		}
	}

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
} // namespace