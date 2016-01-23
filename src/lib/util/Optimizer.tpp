
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
		mConstraintVector = _vector
	}


	template<typename Number>
	Number Optimizer<Number>::evaluate() const {
		#ifdef USE_SMTRAT
		if(!mInitialized)
			initialize();

		Poly objective = createObjective(_direction);
		mSmtratSolver.addObjective(objective, false);

		//std::cout << "(push)" << std::endl;
		//std::cout << ((smtrat::FormulaT)mSmtratSolver.formula()).toString( false, 1, "", true, false, true, true ) << std::endl;
		//std::cout << "(maximize " << objective.toString(false,true) << ")" << std::endl << "(check-sat)" << std::endl << "(pop)" << std::endl;

		smtrat::Answer res = mSmtratSolver.check();

		switch(res) {
			case smtrat::Answer::SAT:{
				smtrat::ModelValue valuation = mSmtratSolver.optimum(objective);
				mSmtratSolver.removeObjective(objective);
				assert(!valuation.isBool());
				assert(!valuation.isSqrtEx());
				assert(!valuation.isRAN());
				assert(!valuation.isBVValue());
				assert(!valuation.isSortValue());
				assert(!valuation.isUFModel());
				if(valuation.isMinusInfinity() || valuation.isPlusInfinity() ){
					return std::make_pair( 1, INFTY );
				} else {
					assert(valuation.isRational());
					return std::make_pair( carl::convert<Rational,Number>(valuation.asRational()), FEAS );
				}
			}
			default:{
				mSmtratSolver.removeObjective(objective);
				return std::make_pair( 0, INFEAS );
			}
		}
		#endif
	}

	template<typename Number>
	bool Optimizer<Number>::checkConsistency() const {
		#ifdef USE_SMTRAT
		if(!mInitialized)
			initialize();

		return (simplex.check() == smtrat::Answer::UNSAT);
		#endif
	}


	template<typename Number>
	void Optimizer<Number>::initialize() const {
		if(!mInitialized) {
			#ifdef USE_SMTRAT
			smtrat::FormulaT currentSystem = createFormula(mConstraintMatrix, mConstraintVector);
			mSmtratSolver.push();
			mSmtratSolver.inform(currentSystem);
			mSmtratSolver.add(currentSystem);
			mSmtratSolver.push();
			mInitialized = true;
			#endif
		}
	}


} // namespace