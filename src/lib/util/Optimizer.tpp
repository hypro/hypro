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
		mInitialized = false;
		mConstraintMatrix = _matrix;
	}

	template<typename Number>
	void Optimizer<Number>::setVector(const vector_t<Number> _vector) {
		mInitialized = false;
		mConstraintVector = _vector;
	}

	template<typename Number>
	void Optimizer<Number>::clear() {
		mConstraintMatrix = matrix_t<Number>::Zero(1,1);
		mConstraintVector = vector_t<Number>::Zero(1);
		#ifdef USE_SMTRAT
		#elif defined USE_Z3
		#endif
		deleteArrays();
		mInitialized = false;
	}

	template<typename Number>
	std::pair<Number, SOLUTION> Optimizer<Number>::evaluate(const vector_t<Number>& _direction, bool overapproximate) const {
		if(!mInitialized)
			initialize();

		assert( _direction.rows() == mConstraintMatrix.cols() );

		std::pair<Number,SOLUTION> res;

		// std::cout << "Set target: ";
		for ( unsigned i = 0; i < mConstraintMatrix.cols(); i++ ) {
			glp_set_col_bnds( lp, i + 1, GLP_FR, 0.0, 0.0 );
			glp_set_obj_coef( lp, i + 1, double( _direction( i ) ) );
		}

		/* solve problem */
		glp_simplex( lp, NULL );

		res.first = glp_get_obj_val( lp );

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
		Poly objective = createObjective(_direction);

		// add presolution
		bool addedTmpSolution = false;
		if(res.second == FEAS) {
			Poly tmpSolution = objective - carl::convert<Number, smtrat::Rational>(res.first.value());
			smtrat::FormulaT tmpSolutionConstraint(tmpSolution, carl::Relation::GEQ);
			mSmtratSolver.inform(tmpSolutionConstraint);
			mSmtratSolver.add(tmpSolutionConstraint);
			addedTmpSolution = true;
		} else if( res.second == INFEAS) {
			if(mSmtratSolver.check() == smtrat::Answer::UNSAT)
				return res;
		} else { // if glpk detected unboundedness we return. TODO: Is this correct?
			return res;
		}


		mSmtratSolver.addObjective(objective, false);

		//std::cout << "(push)" << std::endl;
		//std::cout << ((smtrat::FormulaT)mSmtratSolver.formula()).toString( false, 1, "", true, false, true, true ) << std::endl;
		//std::cout << "(maximize " << objective.toString(false,true) << ")" << std::endl << "(check-sat)" << std::endl << "(pop)" << std::endl;

		smtrat::Answer smtratCheck = mSmtratSolver.check();

		switch(smtratCheck) {
			case smtrat::Answer::SAT:{
				smtrat::ModelValue valuation = mSmtratSolver.optimum(objective);
				mSmtratSolver.removeObjective(objective);
				if(addedTmpSolution)
					mSmtratSolver.pop();
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
			}
			default:{
				mSmtratSolver.removeObjective(objective);
				if(addedTmpSolution)
					mSmtratSolver.pop();
			}
		}
		#elif defined USE_Z3

		// create optimization function
		z3::expr direction(c);
		for(unsigned i = 0; i < mConstraintMatrix.cols(); ++i){
			const char* coefficient(_direction(i).toString().c_str());
			z3::expr coeff(c);

			std::cout << "coefficient " << coefficient;

			if (_direction(i) < 0){
				std::string tmp = _direction(i).toString();

				// cover potential brackets
				if(tmp.find("(") == std::string::npos){
					tmp = tmp.substr(1,tmp.length()-1);
				} else {
					tmp = tmp.substr(2,tmp.length()-3);
				}
				//tmp.erase(std::remove_if(tmp.begin(), tmp.end(), [](char c) { return !isalpha(c); }), tmp.end());

				//tmp = "(- " + tmp + ")";

				std::cout << " tmp " << tmp;

				coefficient = tmp.data();
				coeff = c.real_val(coefficient);
				coeff = -coeff;
			} else {
				string tmp = _direction(i).toString();
				//tmp.erase(std::remove_if(tmp.begin(), tmp.end(), [](char c) { return !isalpha(c); }), tmp.end());

				coefficient = tmp.data();
				coeff = c.real_val(coefficient);
			}

			std::cout << " vs coeff " << coeff << std::endl;

			z3::expr term(c);
			term=variables[i]*coeff;

			if(i==0)
				direction = term;
			else
				direction = direction + term;
		}

		z3::optimize::handle h1 = opt.maximize(direction);

	    std::cout << "Evaluate in direction " << direction << std::endl;

	    if (z3::sat == opt.check()) {
			assert(opt.upper(h1).is_arith());
			//assert(opt.upper(h1).is_const());
			std::cout << __func__ << " " <<  opt.upper(h1) << ", " << opt.lower(h1) << std::endl;
			std::cout << "Satisfied typetraits: " << std::endl;
			std::cout << "opt.upper(h1).is_real(): " << opt.upper(h1).is_real() << std::endl;
			std::cout << "opt.upper(h1).is_int(): " << opt.upper(h1).is_int() << std::endl;
			std::cout << "opt.upper(h1).is_arith(): " << opt.upper(h1).is_arith() << std::endl;
			std::cout << "opt.upper(h1).is_numeral(): " << opt.upper(h1).is_numeral() << std::endl;
			std::cout << "opt.upper(h1).is_const(): " << opt.upper(h1).is_const() << std::endl;
			if(opt.upper(h1).is_numeral() ) {
				long long num;
	    		long long den;
	    		if (Z3_get_numeral_rational_int64(opt.upper(h1).ctx(), opt.upper(h1), &num, &den)) {
	    			// TODO: TEMPORARY!!!
	    			long tmpNum = (long)num;
	    			long tmpDen = (long)den;

	            	res = std::make_pair(Number(tmpNum)/Number(tmpDen), FEAS);
	            } else {
	            	std::cout << "Expression is not convertible exactly." << std::endl;
	            	std::cout << Z3_get_numeral_string(opt.upper(h1).ctx(), opt.upper(h1)) << std::endl;

	            	std::string stringRep = Z3_get_numeral_string(opt.upper(h1).ctx(), opt.upper(h1));
	            	std::size_t delimiterPos = stringRep.find("/");
	            	std::string numerator = stringRep.substr(0,delimiterPos);
	            	std::string denominator = stringRep.substr(delimiterPos+1, stringRep.length()-delimiterPos);

	            	std::cout << numerator << "/" << denominator << std::endl;

	            	Number numer(numerator);
	            	Number denom(denominator);

	            	std::cout << numer << "/" << denom << std::endl;

	            	res = std::make_pair(numer/denom, FEAS);
	            }
			} else {
				res = std::make_pair( 1, INFTY );
			}
	    }
	    else {
	    	res = std::make_pair( 0, INFEAS );
	    }
		#endif

		return std::move(res);
	}

	template<typename Number>
	bool Optimizer<Number>::checkConsistency() const {
		if(!mInitialized)
			initialize();

		#ifdef USE_SMTRAT
		std::cout << __func__ << ": " << (mSmtratSolver.check()) << std::endl;

		return (mSmtratSolver.check() != smtrat::Answer::UNSAT);

		#elif defined USE_Z3
	    if (z3::sat == z3solver.check())
	    	return true;
	    else
	    	return false;

		#else
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

			unsigned numberOfConstraints = mConstraintMatrix.rows();

			// convert constraint constants
			glp_add_rows( lp, numberOfConstraints );
			for ( unsigned i = 0; i < numberOfConstraints; i++ ) {
				glp_set_row_bnds( lp, i + 1, GLP_UP, 0.0, double( mConstraintVector(i) ) );
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
				ar[i + 1] = double( mConstraintMatrix.row(ia[i + 1] - 1)( ja[i + 1] - 1 ) );
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
			smtrat::FormulaT currentSystem = createFormula(mConstraintMatrix, mConstraintVector);
			mSmtratSolver.pop();
			mSmtratSolver.push();
			mSmtratSolver.inform(currentSystem);
			mSmtratSolver.add(currentSystem);
			mSmtratSolver.push();

			#elif defined USE_Z3
			z3::expr_vector constraints(c);
			z3::expr_vector variables(c);
			for(unsigned i = 0; i < mConstraintMatrix.cols(); ++i){
				z3::expr var(c);
				const char* varName = ("x_" + std::to_string(i)).c_str();
				var=c.real_const(varName);
				variables.push_back(var);
			}

			for(unsigned i = 0; i < mConstraintMatrix.rows(); ++i){
				z3::expr polynomial(c);
				for(unsigned j = 0; j < mConstraintMatrix.cols(); ++j){
					z3::expr coeff(c);

					std::cout << "String: " << mConstraintMatrix(i,j).toString() << std::endl;
					std::string stringRep = mConstraintMatrix(i,j).toString();
					// cover potential brackets
					if(stringRep.find("(") == std::string::npos){
						stringRep = stringRep.substr(1,stringRep.length()-1);
					} else {
						stringRep = stringRep.substr(2,stringRep.length()-3);
					}
					stringRep.erase(std::remove_if(stringRep.begin(), stringRep.end(), [](char c) { return !isalpha(c); }), stringRep.end());

					std::size_t delimiterPos = stringRep.find("/");

					if(delimiterPos == std::string::npos) {
						coeff = c.real_val(stringRep.data());
					} else {
						std::string numerator = stringRep.substr(0,delimiterPos);
			            std::string denominator = stringRep.substr(delimiterPos+1, stringRep.length()-delimiterPos);

			            z3::expr nom = c.real_val(numerator.data());
						z3::expr den = c.real_val(denominator.data());

						coeff = nom / den;
					}

					if (mConstraintMatrix(i,j) < 0){
						coeff = -coeff;
					}

					z3::expr term(c);

					std::cout << "Variable: " << variables[j] << std::endl;
					std::cout << "J: " << j << ", coeff: " << coeff << std::endl;

					term=variables[j]*coeff;
					if(j == 0)
						polynomial = term;
					else
						polynomial = polynomial + term ;
				}
				const char* constantPart;
				z3::expr constant(c);
				if (mConstraintVector(i) < 0){
					std::string tmp = mConstraintVector(i).toString();

					// cover potential brackets
					if(tmp.find("(") == std::string::npos){
						tmp = tmp.substr(1,tmp.length()-1);
					} else {
						tmp = tmp.substr(2,tmp.length()-3);
					}
					tmp.erase(std::remove_if(tmp.begin(), tmp.end(), [](char c) { return !isalpha(c); }), tmp.end());

					constantPart = tmp.c_str();
					constant = c.real_val(constantPart);
					constant = -constant;
				} else {
					constantPart = mConstraintVector(i).toString().c_str();
					constant = c.real_val(constantPart);
				}

				z3::expr constraint(polynomial <= constant);
				constraints.push_back(constraint);
			}

		    for(unsigned i = 0; i < constraints.size(); ++i) {
		    	//std::cout << constraints[i] << std::endl;
		    	z3solver.add(constraints[i]);
		    }

			#endif

			mInitialized = true;
		}
	}

	template <typename Number>
	void Optimizer<Number>::createArrays( unsigned size ) const {
		ia = new int[size + 1];
		ja = new int[size + 1];
		ar = new double[size + 1];
	}

	template <typename Number>
	void Optimizer<Number>::deleteArrays() {
		delete[] ia;
		delete[] ja;
		delete[] ar;
	}
} // namespace