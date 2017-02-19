#include "Optimizer.h"

namespace hypro {

	template<typename Number>
	Optimizer<Number>& Optimizer<Number>::operator=(const Optimizer<Number>& orig) {
		mConstraintMatrix = orig.matrix();
		mConstraintVector = orig.vector();
		mConsistencyChecked = false;
		mConstraintsSet = false;
		mInitialized = false;
		return *this;
	}

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
		//#ifdef HYPRO_USE_SMTRAT
		//if(lp != nullptr)
		//	mSmtratSolver.clear();
		//#endif
		glp_delete_prob(lp);
		deleteArrays();
		mConsistencyChecked = false;
		mConstraintsSet = false;
		mInitialized = false;
	}

	template<typename Number>
	EvaluationResult<Number> Optimizer<Number>::evaluate(const vector_t<Number>& _direction, bool useExactGlpk) const {
		if(!mConstraintsSet) {
			updateConstraints();
		}
		TRACE("hypro.optimizer","Direction: " << _direction << ", constraintMatrix: " << std::endl << mConstraintMatrix << ", and vector:" << std::endl << mConstraintVector);
		assert( _direction.rows() == mConstraintMatrix.cols() );

		if( mConstraintMatrix.rows() == 0 ) {
			TRACE("hypro.optimizer", "System is unbounded.");
			return EvaluationResult<Number>( Number(0),vector_t<Number>::Zero(1), SOLUTION::INFTY);
		}

		// there is no non-zero cost function -> check for emptiness.
		if(_direction.rows() == 0 || _direction.nonZeros() == 0){
			if( this->checkConsistency() ) {
				return EvaluationResult<Number>( Number(0),vector_t<Number>::Zero(1), SOLUTION::FEAS); // origin, feasible
			}
			return EvaluationResult<Number>(); // defaults to infeasible.
		}

		#if defined(HYPRO_USE_SMTRAT) || defined(HYPRO_USE_Z3) || defined(HYPRO_USE_SOPLEX)
		EvaluationResult<Number> res;
		#endif

		COUNT("glpk");
		#if defined(HYPRO_USE_SMTRAT) || defined(HYPRO_USE_Z3) || defined(HYPRO_USE_SOPLEX)
		res = glpkOptimizeLinear(lp,_direction,mConstraintMatrix,mConstraintVector,useExactGlpk);
		#else
		return glpkOptimizeLinear(lp,_direction,mConstraintMatrix,mConstraintVector,useExactGlpk);
		#endif

		#if defined(HYPRO_USE_SMTRAT) || defined(HYPRO_USE_Z3) || defined(HYPRO_USE_SOPLEX)
		#ifdef DEBUG_MSG
		std::cout << "glpk optimumValue: " << res.optimumValue << ", glpk errorcode: " << res.errorCode << std::endl;
		#endif

		// At this point we can check, whether the glpk result is already exact and optimal.
		// We do this by inserting the solution into the constraints. The solution is exact,
		// whenever it lies at least on one hyperplane (the respective constraint is saturated). Moreover
		// the solution should always satisfy all constraints and if the direction is linear independent from
		// all normals, at least d (d is the dimension) constraints are saturated.
 		unsigned saturatedPositiveConstraints = 0;
 		int closestLinearDependentConstraint = -1;
 		vector_t<Number> closestPointOnLinearDependentPlane;
 		bool invalidResult = false;
		for(unsigned constraintIndex = 0; constraintIndex < mConstraintMatrix.rows(); ++constraintIndex) {
			Number optVal = mConstraintMatrix.row(constraintIndex).dot(res.optimumValue);
			if(optVal > mConstraintVector(constraintIndex)) {
				invalidResult = true;
				break;
			}
			// check for saturation. Only when not linear dependent and the normal points in the same direction.
			if( closestLinearDependentConstraint >= 0 &&
				mConstraintMatrix.row(constraintIndex).dot(_direction) > 0 &&
			 	optVal == mConstraintVector(constraintIndex) )
			{
				++saturatedPositiveConstraints;
			}
			if( linearDependent(vector_t<Number>(mConstraintMatrix.row(constraintIndex)), _direction).first ) {
				// obtain point on the plane: scale the normal with the factor of the difference of the
				// length of the normal and the target distance.
				Number factor = mConstraintVector(constraintIndex)/(mConstraintMatrix.row(constraintIndex).dot(mConstraintMatrix.row(constraintIndex)));
				vector_t<Number> pointOnPlane = mConstraintMatrix.row(constraintIndex) * factor;
				// update closest point if required (compare first nonZero component).
				unsigned nonZeroPos = 0;
				while(_direction(nonZeroPos) == Number(0)) {++nonZeroPos;}
				// positive pointing direction - take the point with the smallest component in this dimension.
				if(_direction(nonZeroPos) > 0) {
					if(closestLinearDependentConstraint==-1 || closestPointOnLinearDependentPlane(nonZeroPos) > pointOnPlane(nonZeroPos)) {
						closestPointOnLinearDependentPlane = pointOnPlane;
						closestLinearDependentConstraint = constraintIndex;
					}
				} else {
					if(closestLinearDependentConstraint==-1 || closestPointOnLinearDependentPlane(nonZeroPos) < pointOnPlane(nonZeroPos)) {
						closestPointOnLinearDependentPlane = pointOnPlane;
						closestLinearDependentConstraint = constraintIndex;
					}
				}
			}
		}

		// re-solve when: Either the result invalidates one constraint, or the direction is linear independent from all
		// constraint-normals and there are not at least d constraints saturated or if the direction is linear
		// dependent and the closest linear dependent constraint is not satisfied.
		if( invalidResult ||
			( closestLinearDependentConstraint == -1 && saturatedPositiveConstraints < mConstraintMatrix.cols() ) ||
			( mConstraintMatrix.row(closestLinearDependentConstraint).dot(res.optimumValue) != mConstraintVector(closestLinearDependentConstraint) )) {

			// TODO: just for statistics, delete in productive code!
			if(invalidResult) {COUNT("invalid result")};

			if(( closestLinearDependentConstraint == -1 && saturatedPositiveConstraints < mConstraintMatrix.cols())) {COUNT("saturation failure")};

			if(( closestLinearDependentConstraint != -1 && mConstraintMatrix.row(closestLinearDependentConstraint).dot(res.optimumValue) != mConstraintVector(closestLinearDependentConstraint) )) {COUNT("linear dependence failure")};

			#ifdef HYPRO_USE_Z3
			COUNT("z3");
			res = z3OptimizeLinear(_direction,mConstraintMatrix,mConstraintVector,res);
			#elif defined(HYPRO_USE_SMTRAT) // else if HYPRO_USE_SMTRAT
			COUNT("smtrat");
			res = smtratOptimizeLinear(_direction,mConstraintMatrix,mConstraintVector,res);
			#elif defined(HYPRO_USE_SOPLEX)
			COUNT("soplex");
			res = soplexOptimizeLinear(_direction,mConstraintMatrix,mConstraintVector,res);
			#endif
		}

		// if there is a valid solution (FEAS), it implies the optimumValue is set.
		assert(res.errorCode  != FEAS || (res.optimumValue.rows() > 1 || (res.optimumValue != vector_t<Number>::Zero(0) && res.supportValue > 0 )));
		//std::cout << "Point: " << res.optimumValue << " contained: " << checkPoint(Point<Number>(res.optimumValue)) << ", Solution is feasible: " << (res.errorCode==SOLUTION::FEAS) << std::endl;
		//assert(res.errorCode  != FEAS || checkPoint(Point<Number>(res.optimumValue)));
		#ifdef DEBUG_MSG
		std::cout << "Final solution distance: " << res.supportValue << std::endl;
		#endif
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

		//std::cout << __func__ << ": matrix: " << mConstraintMatrix << std::endl << "Vector: " << mConstraintVector << std::endl;

		#ifdef HYPRO_USE_SMTRAT
		TRACE("hypro.optimizer","Use smtrat for consistency check.");
		mLastConsistencyAnswer = smtratCheckConsistency(mConstraintMatrix,mConstraintVector) == true ? SOLUTION::FEAS : SOLUTION::INFEAS;
		mConsistencyChecked = true;
        #elif defined(HYPRO_USE_Z3)
		mLastConsistencyAnswer = z3CheckConsistency(mConstraintMatrix,mConstraintVector) == true ? SOLUTION::FEAS : SOLUTION::INFEAS;
		mConsistencyChecked = true;
		#elif defined(HYPRO_USE_SOPLEX)
		mLastConsistencyAnswer = soplexCheckConsistency(mConstraintMatrix,mConstraintVector) == true ? SOLUTION::FEAS : SOLUTION::INFEAS;
		mConsistencyChecked = true;
		#else // use glpk
		if(!mConsistencyChecked){
			TRACE("hypro.optimizer","Use glpk for consistency check.");
			glp_simplex( lp, NULL);
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
		return z3CheckPoint(mConstraintMatrix,mConstraintVector,_point);
		#elif defined(HYPRO_USE_SMTRAT)
		return smtratCheckPoint(mConstraintMatrix, mConstraintVector, _point);
		#elif defined(HYPRO_USE_SOPLEX)
		return soplexCheckPoint(mConstraintMatrix, mConstraintVector, _point);
		#else
		return glpkCheckPoint(lp, mConstraintMatrix, mConstraintVector, _point);
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
		res = smtratGetInternalPoint(mConstraintMatrix, mConstraintVector);
		mConsistencyChecked = true;
		mLastConsistencyAnswer = res.errorCode;
		#else

		// TODO: Avoid re-call here too!
		glp_simplex( lp, NULL);
		glp_exact( lp, NULL );
		//return (glp_get_status(lp) != GLP_NOFEAS);

		//TODO: Undone!
		#endif
		return res;
	}

	template<typename Number>
	std::vector<std::size_t> Optimizer<Number>::redundantConstraints() const {
		std::vector<std::size_t> res;
		if(!mConstraintsSet) {
			updateConstraints();
		}
		if(mConstraintMatrix.rows() <= 1) {
			return res;
		}

		#ifdef HYPRO_USE_Z3
		res = z3RedundantConstraints(mConstraintMatrix, mConstraintVector);
		#elif defined(HYPRO_USE_SMTRAT) // else if HYPRO_USE_SMTRAT
		res = smtratRedundantConstraints(mConstraintMatrix, mConstraintVector);
		#else
		res = glpkRedundantConstraints(lp, mConstraintMatrix, mConstraintVector);
		#endif

		std::sort(res.begin(), res.end());

		return res;
	}

	template<typename Number>
	void Optimizer<Number>::initialize() const {
		if(!mInitialized) {
			/* create glpk problem */
			lp = glp_create_prob();
			glp_set_obj_dir( lp, GLP_MAX );
			glp_term_out( GLP_OFF );
			//#ifdef HYPRO_USE_SMTRAT
			//#ifndef RECREATE_SOLVER
			//mSmtratSolver.push();
			//#endif
			//#endif
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

				glp_delete_prob(lp);
				lp = glp_create_prob();

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
					//assert(*(mConstraintMatrix.data()+(ja[i+1]*numberOfConstraints) - ia[i+1]) ==  mConstraintMatrix.row(ia[i + 1] - 1)( ja[i + 1] - 1 ));
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
