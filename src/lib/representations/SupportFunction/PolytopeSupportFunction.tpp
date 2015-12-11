/*
 * This file contains the basic implementation of support functions of polyhedra
 *(template polyhedra) and their
 *evaluation.
 * @file PolytopeSupportFunction.tpp
 *
 * @author Norman Hansen
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @author Simon Froitzheim
 *
 * @version	2015-02-27
 */

#include "PolytopeSupportFunction.h"

namespace hypro {

#ifdef USE_SMTRAT
#else
template <typename Number>
void PolytopeSupportFunction<Number>::createArrays( unsigned size ) {
	ia = new int[size + 1];
	ja = new int[size + 1];
	ar = new double[size + 1];
}

template <typename Number>
void PolytopeSupportFunction<Number>::deleteArrays() {
	delete[] ia;
	delete[] ja;
	delete[] ar;
}


template <typename Number>
void PolytopeSupportFunction<Number>::initialize( matrix_t<Number> constraints, vector_t<Number> constraintConstants ) {
	assert( constraints.rows() == constraintConstants.rows() );
	mDimension = constraints.cols();

#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
	std::cout << __func__ << " copied constraint pointers" << std::endl;
#endif

	/* create glpk problem */
	lp = glp_create_prob();
	glp_set_prob_name( lp, "SupportFunctionContent" );
	glp_set_obj_dir( lp, GLP_MAX );

#ifndef PPOLYTOPESUPPORTFUNCTION_VERBOSE
	glp_term_out( GLP_OFF );
#endif

	int numberOfConstraints = constraints.rows();

	// convert constraint constants
	glp_add_rows( lp, numberOfConstraints );

#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
	std::cout << __func__ << " Constructed GLPK problem" << std::endl << "mDimension: " << mDimension << std::endl;
#endif

	for ( int i = 0; i < numberOfConstraints; i++ ) {
		glp_set_row_bnds( lp, i + 1, GLP_UP, 0.0, double( constraintConstants( i ) ) );
	}

	// add cols here
	glp_add_cols( lp, mDimension );

#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
	std::cout << __func__ << " added constraints (values)" << std::endl;
#endif

	createArrays( constraints.size() );

	// convert constraint matrix
	for ( int i = 0; i < constraints.size(); i++ ) {
		ia[i + 1] = ( (int)( i / mDimension ) ) + 1;
		ja[i + 1] = ( (int)( i % mDimension ) ) + 1;
		ar[i + 1] = double( constraints( (int)( i / mDimension ), (int)( i % mDimension ) ) );

#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
		std::cout << __func__ << " set: ar[" << i + 1 << "]=" << ar[i + 1] << ", ja[" << i + 1 << "]=" << ja[i + 1]
				  << ", ia[" << i + 1 << "]=" << ia[i + 1] << std::endl;
#endif
	}

#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
	std::cout << __func__ << " terminated matrix construction" << std::endl;
	std::cout << __func__ << " number of matrix elements: " << constraints.size() << std::endl;
	std::cout << "ia: " << ia << std::endl;
	std::cout << "ja: " << ja << std::endl;
	std::cout << "ar: " << ar << std::endl;
#endif

	glp_load_matrix( lp, constraints.size(), ia, ja, ar );

#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
	std::cout << __func__ << " added constraints (matrix)" << std::endl;
#endif
}

#endif

template <typename Number>
PolytopeSupportFunction<Number>::PolytopeSupportFunction( matrix_t<Number> constraints,
														  vector_t<Number> constraintConstants )
	: mConstraints( constraints ), mConstraintConstants( constraintConstants ), mDimension(mConstraints.cols()) {
	#ifndef USE_SMTRAT
	initialize( mConstraints, mConstraintConstants );
	#endif
}

template <typename Number>
PolytopeSupportFunction<Number>::PolytopeSupportFunction( const std::vector<Hyperplane<Number>> &_planes ) {
	assert( !_planes.empty() );
	mConstraints = matrix_t<Number>( _planes.size(), _planes[0].dimension() );
	mConstraintConstants = vector_t<Number>( _planes.size() );
	mDimension = _planes[0].dimension();

	unsigned pos = 0;
	for ( const auto &plane : _planes ) {
		mConstraints.row( pos ) = plane.normal().transpose();
		mConstraintConstants( pos ) = plane.offset();
		++pos;
	}
	#ifndef USE_SMTRAT
	initialize( mConstraints, mConstraintConstants );
	#endif
}

template <typename Number>
PolytopeSupportFunction<Number>::PolytopeSupportFunction( const PolytopeSupportFunction<Number> &_origin )
	: mConstraints( _origin.constraints() ), mConstraintConstants( _origin.constants()), mDimension(mConstraints.cols() ) {
	#ifndef USE_SMTRAT
	initialize( mConstraints, mConstraintConstants );
	#endif
}

template <typename Number>
PolytopeSupportFunction<Number>::~PolytopeSupportFunction() {
	#ifdef USE_SMTRAT
	#else
#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
	std::cout << "PolytopeSupportFunction: destructor" << std::endl;
#endif

	//deleteArrays();

	// free glpk resources
	glp_delete_prob( lp );

#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
	std::cout << "PolytopeSupportFunction: destructor - complete" << std::endl;
#endif
	#endif
}

template <typename Number>
unsigned PolytopeSupportFunction<Number>::dimension() const {
	return mDimension;
}

template <typename Number>
SF_TYPE PolytopeSupportFunction<Number>::type() const {
	return SF_TYPE::POLY;
}

template <typename Number>
matrix_t<Number> PolytopeSupportFunction<Number>::constraints() const {
	return mConstraints;
}

template <typename Number>
vector_t<Number> PolytopeSupportFunction<Number>::constants() const {
	return mConstraintConstants;
}

template <typename Number>
evaluationResult<Number> PolytopeSupportFunction<Number>::evaluate( const vector_t<Number> &l ) const {
	evaluationResult<Number> result;
	#ifdef USE_SMTRAT
		smtrat::SimplexSolver simplex;
		std::pair<smtrat::FormulaT, Poly> constrPair = createFormula(mConstraints, mConstraintConstants, l);
		simplex.inform(constrPair.first);
		simplex.add(constrPair.first);
		Poly objective = constrPair.second;
		simplex.addObjective(objective, false);

		std::cout << "Checking: " << std::endl << ((smtrat::FormulaT)simplex.formula()).toString( false, 1, "", true, false, true, true ) << std::endl;
		std::cout << "with objective function " << std::endl << objective << std::endl;

		smtrat::Answer res = simplex.check();

		switch(res) {
			case smtrat::Answer::SAT:{
				smtrat::ModelValue valuation = simplex.optimum(objective);
				assert(!valuation.isBool());
				assert(!valuation.isSqrtEx());
				assert(!valuation.isRAN());
				assert(!valuation.isBVValue());
				assert(!valuation.isSortValue());
				assert(!valuation.isUFModel());
				if(valuation.isMinusInfinity() || valuation.isPlusInfinity() ){
					//std::cout << __func__ << ": INFINITY" << std::endl;
					result.supportValue = 0;
					result.errorCode = GLP_UNBND;
				} else {
					assert(valuation.isRational());
					//std::cout << __func__ << ": " << valuation.asRational() << std::endl;
					result.supportValue = carl::convert<Rational,Number>(valuation.asRational());
					result.errorCode = GLP_FEAS;
				}
				break;
			}
			default:
				result.supportValue = 0;
				result.errorCode = GLP_INFEAS;
		}
	#else

#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
	std::cout << "PolytopeSupportFunction: evaluate in " << l << std::endl;
#endif

	assert( l.rows() == mDimension );

	for ( unsigned i = 0; i < mDimension; i++ ) {
		glp_set_col_bnds( lp, i + 1, GLP_FR, 0.0, 0.0 );
		glp_set_obj_coef( lp, i + 1, double( l( i, 0 ) ) );
	}

	/* solve problem */
	glp_simplex( lp, NULL );

	/* recover and display results */
	result.supportValue = glp_get_obj_val( lp );

	// std::cout << " Obj coeff: " << glp_get_obj_coef(lp,0) << " and " <<
	// glp_get_obj_coef(lp,1) << std::endl;

	vector_t<Number> x = vector_t<Number>( mDimension );
	for ( unsigned i = 0; i < mDimension; i++ ) {
		x( i ) = Number( glp_get_col_prim( lp, i + 1 ) );
	}
	result.optimumValue = x;
	result.errorCode = glp_get_status( lp );

	// display potential problems
	switch ( result.errorCode ) {
		case GLP_OPT:
		case GLP_FEAS:
			break;
		case GLP_UNBND:
			result.supportValue = INFINITY;
			break;
		default:
			std::cout << "Unable to find a suitable solution for the support function "
						 "(linear program). ErrorCode: " << result.errorCode << std::endl;
	}
/*
#ifdef PPOLYTOPESUPPORTFUNCTION_VERIFY
	if(result.errorCode == GLP_OPT || result.errorCode != GLP_FEAS) {
		// check value against all hyperplanes
		vector_t<Number> optPoint = l*result.supportValue;
		Number tmpSupportValue = result.supportValue;

		std::cout << "START Shifting." << std::endl;
		std::vector<std::pair<matrix_t<Number>, Number>> invalidPlanes;
		for(int rowIndex = 0; rowIndex < mConstraints.rows(); ++rowIndex) {
			if(mConstraints.row(rowIndex).dot(l) > 0 && mConstraints.row(rowIndex).dot(optPoint) < mConstraintConstants(rowIndex)) {
				while(mConstraints.row(rowIndex).dot(optPoint) < mConstraintConstants(rowIndex)){
					std::cout << "shift by " << (mConstraintConstants(rowIndex)-mConstraints.row(rowIndex).dot(optPoint)) << std::endl;
					tmpSupportValue = tmpSupportValue+(mConstraintConstants(rowIndex)-mConstraints.row(rowIndex).dot(optPoint));
					optPoint = l*tmpSupportValue;
				}
				rowIndex = -1;
			}
		}
		std::cout << "END Shifting." << std::endl;
		result.supportValue = tmpSupportValue;
	}
#endif
*/

#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
	printf( "fx = %g; x = ", double( result.supportValue ) );
	std::cout << x;
	std::cout << std::endl << "size x: " << x.size() << std::endl;
#endif
	#endif
	return result;
}

template <typename Number>
vector_t<Number> PolytopeSupportFunction<Number>::multiEvaluate( const matrix_t<Number> &_A ) const {
	std::cout << "A.cols: " << _A.cols() << " and dimension: " << mDimension << std::endl;
	assert( _A.cols() == mDimension );
	vector_t<Number> res( _A.rows() );

	for ( unsigned index = 0; index < _A.rows(); ++index ) {
		res( index ) = evaluate( _A.row( index ).transpose() ).supportValue;
	}

	return res;
}

template <typename Number>
bool PolytopeSupportFunction<Number>::contains( const Point<Number> &_point ) const {
	return this->contains( _point.rawCoordinates() );
}

template <typename Number>
bool PolytopeSupportFunction<Number>::contains( const vector_t<Number> &_point ) const {
	assert(mConstraints.rows() == mConstraintConstants.rows());
	for ( unsigned rowIt = 0; rowIt < mConstraints.rows(); ++rowIt ) {
		if( mConstraints.row(rowIt).dot(_point) > mConstraintConstants(rowIt) )
			return false;
	}
	return true;
}

template <typename Number>
bool PolytopeSupportFunction<Number>::empty() const {
	#ifdef USE_SMTRAT
	smtrat::SimplexSolver simplex;
	smtrat::FormulaT constr = createFormula(mConstraints, mConstraintConstants);
	simplex.inform(constr);
	simplex.add(constr);

	smtrat::Answer res = simplex.check();

	return (res == smtrat::Answer::UNSAT);
	#else
	for ( int i = 0; i < mDimension; i++ ) {
		glp_set_col_bnds( lp, i + 1, GLP_FR, 0.0, 0.0 );  // unbounded
		glp_set_obj_coef( lp, i + 1, 1.0 );
	}

	glp_simplex( lp, NULL );

	int errorCode = glp_get_status( lp );

	if ( errorCode == GLP_INFEAS || errorCode == GLP_NOFEAS ) return false;

	return true;
	#endif
}

template <typename Number>
void PolytopeSupportFunction<Number>::print() const{
    std::cout << mConstraints << std::endl;
    std::cout << mConstraintConstants << std::endl;
}
}  // namespace
