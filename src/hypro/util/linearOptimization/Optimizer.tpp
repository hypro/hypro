#include "Optimizer.h"

namespace hypro {

template <typename Number>
void Optimizer<Number>::cleanContexts() {
	assert( isSane() );
	TRACE( "hypro.optimizer", "Thread " << std::this_thread::get_id() << " attempts to erase its context. (@" << this << ")" );

	std::lock_guard<std::mutex> lock( mContextLock );
#ifdef HYPRO_USE_GLPK
	auto ctxtItGlpk = mGlpkContexts.find( std::this_thread::get_id() );
	if ( ctxtItGlpk != mGlpkContexts.end() ) {
		TRACE( "hypro.optimizer", "Thread " << std::this_thread::get_id() << " glp instances left (before erase): " << mGlpkContexts.size() );
		TRACE( "hypro.optimizer", "Thread " << std::this_thread::get_id() << " erases its context. (@" << this << ")" );
		ctxtItGlpk->second.deleteLPInstance();
		TRACE( "hypro.optimizer", "Deleted lp instance." );
		mGlpkContexts.erase( ctxtItGlpk );
		TRACE( "hypro.optimizer", "Thread " << std::this_thread::get_id() << " glp instances left (after erase): " << mGlpkContexts.size() );
	}
#endif
#ifdef HYPRO_USE_CLP
	auto ctxtItClp = mClpContexts.find( std::this_thread::get_id() );
	if ( ctxtItClp != mClpContexts.end() ) {
		TRACE( "hypro.optimizer", "Thread " << std::this_thread::get_id() << " glp instances left (before erase): " << mClpContexts.size() );
		TRACE( "hypro.optimizer", "Thread " << std::this_thread::get_id() << " erases its context. (@" << this << ")" );
		ctxtItClp->second.deleteLPInstance();
		TRACE( "hypro.optimizer", "Deleted lp instance." );
		mClpContexts.erase( ctxtItClp );
		TRACE( "hypro.optimizer", "Thread " << std::this_thread::get_id() << " glp instances left (after erase): " << mClpContexts.size() );
	}
#endif
	assert( isSane() );
}  // namespace hypro

template <typename Number>
const matrix_t<Number>& Optimizer<Number>::matrix() const {
	assert( isSane() );
	return mConstraintMatrix;
}

template <typename Number>
const vector_t<Number>& Optimizer<Number>::vector() const {
	assert( isSane() );
	return mConstraintVector;
}

//Move ctor via Copy-and-Swap idiom
template <typename Number>
Optimizer<Number>::Optimizer( Optimizer<Number>&& orig )
	: Optimizer() {
	swap( *this, orig );
}

//Copy ctor via Copy-and-Swap idiom
template <typename Number>
Optimizer<Number>::Optimizer( const Optimizer<Number>& orig )
	: mConstraintMatrix( orig.matrix() )
	, mConstraintVector( orig.vector() )
	, mConsistencyChecked( false )
	, maximize( orig.maximize )
	, mRelationSymbols( orig.mRelationSymbols ) {
	TRACE( "hypro.optimizer", "" );
	assert( isSane() );
	//mConstraintMatrix = orig.matrix();
	//mConstraintVector = orig.vector();
	//mConsistencyChecked = false;
	////TODO: Instead of cleaning the glp context every time we copy,
	////clarify how copying the contexts works in glpk and fix that in glpk_context.h
	////mLastConsistencyAnswer = orig.getLastConsistencyAnswer();
	//cleanGLPInstance();
	//mGlpkContext = std::map<std::thread::id, glpk_context>();
	cleanContexts();
	assert( isSane() );
	assert( !mConsistencyChecked );
}

//Copy assignment via Copy-and-Swap idiom
template <typename Number>
Optimizer<Number>& Optimizer<Number>::operator=( const Optimizer<Number>& orig ) {
	Optimizer<Number> tmp( orig );
	swap( *this, tmp );
	return *this;
}

template <typename Number>
void Optimizer<Number>::setMatrix( const matrix_t<Number>& _matrix ) {
	assert( isSane() );
	if ( mConstraintMatrix != _matrix ) {
		clearCache();
		mConstraintMatrix = _matrix;
		mRelationSymbols = std::vector<carl::Relation>( mConstraintMatrix.rows(), carl::Relation::LEQ );
	}
}

template <typename Number>
void Optimizer<Number>::setVector( const vector_t<Number>& _vector ) {
	assert( isSane() );
	if ( mConstraintVector != _vector ) {
		clearCache();
		mConstraintVector = _vector;
	}
}

template <typename Number>
void Optimizer<Number>::setRelations( const std::vector<carl::Relation>& rels ) {
	assert( isSane() );
	mRelationSymbols = rels;
	clearCache();
}

template <typename Number>
void Optimizer<Number>::setMaximize( bool max ) {
	assert( isSane() );
	if ( max != maximize ) {
		maximize = max;
		clearCache();
	}
}

template <typename Number>
void Optimizer<Number>::addConstraint( const vector_t<Number>& constraint, Number constantPart, carl::Relation rel ) {
	assert( isSane() );
	mConstraintMatrix.conservativeResize( mConstraintMatrix.rows() + 1, mConstraintMatrix.cols() );
	mConstraintVector.conservativeResize( mConstraintVector.rows() + 1 );
	mConstraintMatrix.row( mConstraintMatrix.rows() - 1 ) = constraint;
	mConstraintVector( mConstraintVector.size() - 1 ) = constantPart;
	// save that the constraint is an equality constraint.
	mRelationSymbols.push_back( rel );
	// reset caches
	clearCache();
}

template <typename Number>
void Optimizer<Number>::setRelation( carl::Relation rel, std::size_t pos ) {
	assert( isSane() );
	assert( pos < mRelationSymbols.size() );
	// save that the constraint is an equality constraint.
	mRelationSymbols[pos] = rel;
	// reset caches
	clearCache();
}

template <typename Number>
void Optimizer<Number>::clear() {
	assert( isSane() );
	mConstraintMatrix = matrix_t<Number>::Zero( 1, 1 );
	mConstraintVector = vector_t<Number>::Zero( 1 );
	mRelationSymbols.clear();
	//#ifdef HYPRO_USE_SMTRAT
	//if(lp != nullptr)
	//	mSmtratSolver.clear();
	//#endif
	assert( false );
#ifdef HYPRO_USE_GLPK
	while ( !mGlpkContexts.empty() ) {
		mGlpkContexts.erase( mGlpkContexts.begin() );
	}
#endif
#ifdef HYPRO_USE_CLP
	while ( !mClpContexts.empty() ) {
		mClpContexts.erase( mClpContexts.begin() );
	}
#endif
	mConsistencyChecked = false;
}

template <typename Number>
EvaluationResult<Number> Optimizer<Number>::evaluate( const vector_t<Number>& _direction, bool useExactGlpk ) const {
	assert( isSane() );
	updateConstraints();
	assert( _direction.rows() == mConstraintMatrix.cols() );

	if ( mConstraintMatrix.rows() == 0 ) {
		return EvaluationResult<Number>( Number( 0 ), vector_t<Number>::Zero( 1 ), SOLUTION::INFTY );
	}

	// there is no non-zero cost function -> check for emptiness.
	if ( _direction.rows() == 0 || _direction.nonZeros() == 0 ) {
		if ( this->checkConsistency() ) {
			return EvaluationResult<Number>( Number( 0 ), vector_t<Number>::Zero( 1 ), SOLUTION::FEAS );  // origin, feasible
		}
		return EvaluationResult<Number>();	// defaults to infeasible.
	}

	// return value
	EvaluationResult<Number> res;

	// call to first solver
#if HYPRO_PRIMARY_SOLVER == SOLVER_GLPK
	res = glpkOptimizeLinear( mGlpkContexts[std::this_thread::get_id()], _direction, mConstraintMatrix, mConstraintVector, useExactGlpk );
#elif HYPRO_PRIMARY_SOLVER == SOLVER_CLP
	res = clpOptimizeLinear( mClpContexts[std::this_thread::get_id()], _direction, mConstraintMatrix, mConstraintVector, useExactGlpk );
#elif HYPRO_PRIMARY_SOLVER == SOLVER_SOPLEX
	res = soplexOptimizeLinear( _direction, mConstraintMatrix, mConstraintVector, mRelationSymbols, maximize );
#elif HYPRO_PRIMARY_SOLVER == SOLVER_SMTRAT
	res = smtratOptimizeLinear( _direction, mConstraintMatrix, mConstraintVector, mRelationSymbols, maximize );
#elif HYPRO_PRIMARY_SOLVER == SOLVER_ZTHREE
	res = z3OptimizeLinear( maximize, _direction, mConstraintMatrix, mConstraintVector, mRelationSymbols );
#endif

#if !defined( HYPRO_SECONDARY_SOLVER )
	return res;
#else
	// At this point we can check, whether the primary result is already exact and optimal.
	// We do this by inserting the solution into the constraints. The solution is exact,
	// whenever it lies at least on one hyperplane (the respective constraint is saturated). Moreover
	// the solution should always satisfy all constraints and if the direction is linear independent from
	// all normals, at least d (d is the dimension) constraints are saturated.
	unsigned saturatedPositiveConstraints = 0;
	int closestLinearDependentConstraint = -1;
	vector_t<Number> closestPointOnLinearDependentPlane;
	bool invalidResult = false;
	for ( unsigned constraintIndex = 0; constraintIndex < mConstraintMatrix.rows(); ++constraintIndex ) {
		Number optVal = mConstraintMatrix.row( constraintIndex ).dot( res.optimumValue );
		if ( optVal > mConstraintVector( constraintIndex ) ) {
			invalidResult = true;
			break;
		}
		// check for saturation. Only when not linear dependent and the normal points in the same direction.
		if ( closestLinearDependentConstraint >= 0 &&
			 mConstraintMatrix.row( constraintIndex ).dot( _direction ) > 0 &&
			 optVal == mConstraintVector( constraintIndex ) ) {
			++saturatedPositiveConstraints;
		}
		if ( linearDependent( vector_t<Number>( mConstraintMatrix.row( constraintIndex ) ), _direction ).first ) {
			// obtain point on the plane: scale the normal with the factor of the difference of the
			// length of the normal and the target distance.
			Number factor = mConstraintVector( constraintIndex ) / ( mConstraintMatrix.row( constraintIndex ).dot( mConstraintMatrix.row( constraintIndex ) ) );
			vector_t<Number> pointOnPlane = mConstraintMatrix.row( constraintIndex ) * factor;
			// update closest point if required (compare first nonZero component).
			unsigned nonZeroPos = 0;
			while ( _direction( nonZeroPos ) == Number( 0 ) ) {
				++nonZeroPos;
			}
			// positive pointing direction - take the point with the smallest component in this dimension.
			if ( _direction( nonZeroPos ) > 0 ) {
				if ( closestLinearDependentConstraint == -1 || closestPointOnLinearDependentPlane( nonZeroPos ) > pointOnPlane( nonZeroPos ) ) {
					closestPointOnLinearDependentPlane = pointOnPlane;
					closestLinearDependentConstraint = constraintIndex;
				}
			} else {
				if ( closestLinearDependentConstraint == -1 || closestPointOnLinearDependentPlane( nonZeroPos ) < pointOnPlane( nonZeroPos ) ) {
					closestPointOnLinearDependentPlane = pointOnPlane;
					closestLinearDependentConstraint = constraintIndex;
				}
			}
		}
	}

	// re-solve when: Either the result invalidates one constraint, or the direction is linear independent from all
	// constraint-normals and there are not at least d constraints saturated or if the direction is linear
	// dependent and the closest linear dependent constraint is not satisfied.
	if ( invalidResult ||
		 ( closestLinearDependentConstraint == -1 && saturatedPositiveConstraints < mConstraintMatrix.cols() ) ||
		 ( mConstraintMatrix.row( closestLinearDependentConstraint ).dot( res.optimumValue ) != mConstraintVector( closestLinearDependentConstraint ) ) ) {
		// TODO: just for statistics, delete in productive code!
		if ( invalidResult ) {
			COUNT( "invalid result" )
		};

		if ( ( closestLinearDependentConstraint == -1 && saturatedPositiveConstraints < mConstraintMatrix.cols() ) ) {
			COUNT( "saturation failure" )
		};

		if ( ( closestLinearDependentConstraint != -1 && mConstraintMatrix.row( closestLinearDependentConstraint ).dot( res.optimumValue ) != mConstraintVector( closestLinearDependentConstraint ) ) ) {
			COUNT( "linear dependence failure" )
		};

#if HYPRO_SECONDARY_SOLVER == SOLVER_GLPK
		res = glpkOptimizeLinearPostSolve( mGlpkContexts[std::this_thread::get_id()], _direction, mConstraintMatrix, mConstraintVector, useExactGlpk, res );
#elif HYPRO_SECONDARY_SOLVER == SOLVER_CLP
		res = clpOptimizeLinearPostSolve( mClpContexts[std::this_thread::get_id()], _direction, mConstraintMatrix, mConstraintVector, useExactGlpk, res );
#elif HYPRO_SECONDARY_SOLVER == SOLVER_SOPLEX
		res = soplexOptimizeLinearPostSolve( _direction, mConstraintMatrix, mConstraintVector, mRelationSymbols, maximize, res );
#elif HYPRO_SECONDARY_SOLVER == SOLVER_SMTRAT
		res = smtratOptimizeLinearPostSolve( _direction, mConstraintMatrix, mConstraintVector, mRelationSymbols, maximize, res );
#elif HYPRO_SECONDARY_SOLVER == SOLVER_ZTHREE
		res = z3OptimizeLinearPostSolve( maximize, _direction, mConstraintMatrix, mConstraintVector, mRelationSymbols, res );
#endif
	}
	return res;
#endif
}

template <typename Number>
bool Optimizer<Number>::checkConsistency() const {
	//assert((mConsistencyChecked && mLastConsistencyAnswer != SOLUTION::UNKNOWN) || (!mConsistencyChecked && mLastConsistencyAnswer == SOLUTION::UNKNOWN));
	assert( isSane() );
	updateConstraints();

	if ( mConstraintMatrix.rows() == 0 ) {
		mLastConsistencyAnswer = SOLUTION::FEAS;
		return true;
	}

#ifdef HYPRO_USE_SMTRAT
	//TRACE("hypro.optimizer","Use smtrat for consistency check.");
	mLastConsistencyAnswer = smtratCheckConsistency( mConstraintMatrix, mConstraintVector, mRelationSymbols ) == true ? SOLUTION::FEAS : SOLUTION::INFEAS;
	mConsistencyChecked = true;
#elif defined( HYPRO_USE_Z3 )
	mLastConsistencyAnswer = z3CheckConsistency( mConstraintMatrix, mConstraintVector, mRelationSymbols ) == true ? SOLUTION::FEAS : SOLUTION::INFEAS;
	mConsistencyChecked = true;
#elif defined( HYPRO_USE_SOPLEX )
	mLastConsistencyAnswer = soplexCheckConsistency( mConstraintMatrix, mConstraintVector, mRelationSymbols ) == true ? SOLUTION::FEAS : SOLUTION::INFEAS;
	mConsistencyChecked = true;
#endif

	if ( !mConsistencyChecked ) {
#if HYPRO_PRIMARY_SOLVER == SOLVER_GLPK
		glp_simplex( mGlpkContexts[std::this_thread::get_id()].lp, &mGlpkContexts[std::this_thread::get_id()].parm );
		glp_exact( mGlpkContexts[std::this_thread::get_id()].lp, &mGlpkContexts[std::this_thread::get_id()].parm );
		mLastConsistencyAnswer = glp_get_status( mGlpkContexts[std::this_thread::get_id()].lp ) == GLP_NOFEAS ? SOLUTION::INFEAS : SOLUTION::FEAS;
		mConsistencyChecked = true;
#elif HYPRO_PRIMARY_SOLVER == SOLVER_CLP
		mLastConsistencyAnswer = clpCheckConsistency( mClpContexts[std::this_thread::get_id()] );
		mConsistencyChecked = true;
#endif
	}
	return ( mLastConsistencyAnswer == SOLUTION::FEAS );
}

template <typename Number>
bool Optimizer<Number>::checkPoint( const Point<Number>& _point ) const {
	assert( isSane() );
	updateConstraints();

	if ( mConstraintMatrix.rows() == 0 ) {
		mLastConsistencyAnswer = SOLUTION::FEAS;
		return true;
	}

#ifdef HYPRO_USE_Z3
	return z3CheckPoint( mConstraintMatrix, mConstraintVector, mRelationSymbols, _point );
#elif defined( HYPRO_USE_SMTRAT )
	return smtratCheckPoint( mConstraintMatrix, mConstraintVector, mRelationSymbols, _point );
#elif defined( HYPRO_USE_SOPLEX )
	return soplexCheckPoint( mConstraintMatrix, mConstraintVector, mRelationSymbols, _point );
#elif HYPRO_PRIMARY_SOLVER == SOLVER_GLPK
	return glpkCheckPoint( mGlpkContexts[std::this_thread::get_id()], mConstraintMatrix, mConstraintVector, _point );
#elif HYPRO_PRIMARY_SOLVER == SOLVER_CLP
	return clpCheckPoint( mClpContexts[std::this_thread::get_id()], mConstraintMatrix, mConstraintVector, _point );
#endif
}

template <typename Number>
EvaluationResult<Number> Optimizer<Number>::getInternalPoint() const {
	assert( isSane() );
	updateConstraints();

	if ( mConstraintMatrix.rows() == 0 ) {
		mLastConsistencyAnswer = SOLUTION::FEAS;
		mConsistencyChecked = true;
		return EvaluationResult<Number>( vector_t<Number>::Zero( 1 ), SOLUTION::FEAS );
	}

	EvaluationResult<Number> res;

#if defined( HYPRO_USE_SMTRAT )
	res = smtratGetInternalPoint( mConstraintMatrix, mConstraintVector, mRelationSymbols );
	mConsistencyChecked = true;
	mLastConsistencyAnswer = res.errorCode;
#elif defined( HYPRO_USE_SOPLEX )
	res = soplexGetInternalPoint<Number>( mConstraintMatrix, mConstraintVector, mRelationSymbols );
	mConsistencyChecked = true;
	mLastConsistencyAnswer = res.errorCode;
#elif HYPRO_PRIMARY_SOLVER == SOLVER_GLPK
	res = glpkGetInternalPoint<Number>( mGlpkContexts[std::this_thread::get_id()], mConstraintMatrix.cols(), false );
	mConsistencyChecked = true;
	mLastConsistencyAnswer = res.errorCode;
#elif HYPRO_PRIMARY_SOLVER == SOLVER_CLP
	res = clpGetInternalPoint<Number>( mClpContexts[std::this_thread::get_id()] );
	mConsistencyChecked = true;
	mLastConsistencyAnswer = res.errorCode;
#elif HYPRO_PRIMARY_SOLVER == SOLVER_ZTHREE
	res = z3GetInternalPoint<Number>( mConstraintMatrix, mConstraintVector, mRelationSymbols );
	mConsistencyChecked = true;
	mLastConsistencyAnswer = res.errorCode;
#endif
	return res;
}

template <typename Number>
std::vector<std::size_t> Optimizer<Number>::redundantConstraints() const {
	assert( isSane() );
	std::vector<std::size_t> res;
	updateConstraints();

	if ( mConstraintMatrix.rows() <= 1 ) {
		return res;
	}

#ifdef HYPRO_USE_Z3
	res = z3RedundantConstraints( mConstraintMatrix, mConstraintVector, mRelationSymbols );
#elif defined( HYPRO_USE_SMTRAT )  // elif HYPRO_USE_SMTRAT
	res = smtratRedundantConstraints( mConstraintMatrix, mConstraintVector, mRelationSymbols );
#elif defined( HYPRO_USE_SOPLEX )
	res = soplexRedundantConstraints( mConstraintMatrix, mConstraintVector, mRelationSymbols );
#elif HYPRO_PRIMARY_SOLVER == SOLVER_GLPK
	res = glpkRedundantConstraints( mGlpkContexts[std::this_thread::get_id()], mConstraintMatrix, mConstraintVector, mRelationSymbols );
#elif HYPRO_PRIMARY_SOLVER == SOLVER_CLP
	res = clpRedundantConstraints( mClpContexts[std::this_thread::get_id()], mConstraintMatrix, mConstraintVector, mRelationSymbols );
#endif

	std::sort( res.begin(), res.end() );

	return res;
}

template <typename Number>
bool Optimizer<Number>::isSane() const {
#ifndef NDEBUG
	TRACE( "hypro.optimizer", "Have " << mGlpkContexts.size() << " instances to check." );
	for ( const auto& glpPair : mGlpkContexts ) {
		if ( glpPair.second.mConstraintsSet && ( !glpPair.second.mInitialized || !glpPair.second.arraysCreated ) )
			return false;
		if ( glpPair.second.arraysCreated && ( glpPair.second.ia == nullptr || glpPair.second.ja == nullptr || glpPair.second.ar == nullptr ) )
			return false;
		TRACE( "hypro.optimizer", "Instance " << &glpPair.second << " for thread " << glpPair.first << " is sane." );
	}
#endif
	return true;
}

template <typename Number>
void Optimizer<Number>::initialize() const {
	assert( isSane() );
	mGlpkContexts[std::this_thread::get_id()].createLPInstance();
	assert( mGlpkContexts[std::this_thread::get_id()].mInitialized == true );

#if defined( HYPRO_USE_GLPK )
	if ( mGlpkContexts.find( std::this_thread::get_id() ) == mGlpkContexts.end() ) {
		std::lock_guard<std::mutex> lock( mContextLock );
		TRACE( "hypro.optimizer", "Actual creation." );
#ifdef HYPRO_STATISTICS
		contextConstructions++;
#endif
		mGlpkContexts.emplace( std::this_thread::get_id(), glpk_context() );
	}
#endif
#if defined( HYPRO_USE_CLP )
	if ( mClpContexts.find( std::this_thread::get_id() ) == mClpContexts.end() ) {
		std::lock_guard<std::mutex> lock( mContextLock );
		TRACE( "hypro.optimizer", "Actual creation." );
		mClpContexts.emplace( std::this_thread::get_id(), clp_context() );
	}
#endif

	TRACE( "hypro.optimizer", "Done." );
}

template <typename Number>
void Optimizer<Number>::updateConstraints() const {
	TRACE( "hypro.optimizer", "" );
	assert( isSane() );
	initialize();

#if defined( HYPRO_USE_GLPK )
	mGlpkContexts[std::this_thread::get_id()].updateConstraints( mConstraintMatrix, mConstraintVector, mRelationSymbols, maximize );
#endif
#if defined( HYPRO_USE_CLP )
	mClpContexts[std::this_thread::get_id()].updateConstraints( mConstraintMatrix, mConstraintVector, mRelationSymbols, maximize );
#endif

#ifdef HYPRO_USE_SMTRAT
#ifndef RECREATE_SOLVER
	mSmtratSolver.pop();
	if ( !mSmtratSolver.formula().empty() ) {
		//std::cout << "THIS SHOULD NOT HAPPEN -> INCORRECT TRACKING OF BT-POINTS." << std::endl;
		//std::cout << ((smtrat::FormulaT)mSmtratSolver.formula()).toString( false, 1, "", true, false, true, true ) << std::endl;
		mSmtratSolver.clear();
	}
	assert( mSmtratSolver.formula().empty() );

	for ( const auto& constraintPair : mFormulaMapping ) {
		mSmtratSolver.deinform( constraintPair.first );
	}

	mSmtratSolver.push();
	//std::cout << "Cleanup - done." << std::endl;

	mFormulaMapping = createFormula( mConstraintMatrix, mConstraintVector );

	//std::cout << "Set new constraints." << std::endl;

	for ( const auto& constraintPair : mFormulaMapping ) {
		mSmtratSolver.inform( constraintPair.first );
		mSmtratSolver.add( constraintPair.first, false );
	}

	//std::cout << "Set new constraints - done." << std::endl;

	mCurrentFormula = smtrat::FormulaT( mSmtratSolver.formula() );
#endif
#endif
	TRACE( "hypro.optimizer", "Done." );
}

template <typename Number>
void Optimizer<Number>::clearCache() const {
#ifdef HYPRO_USE_GLPK
	for ( auto& idContextPair : mGlpkContexts ) {
		idContextPair.second.mConstraintsSet = false;
	}
#endif
#ifdef HYPRO_USE_CLP
	for ( auto& idContextPair : mClpContexts ) {
		idContextPair.second.mConstraintsSet = false;
	}
#endif
	mConsistencyChecked = false;
}

}  // namespace hypro
