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

template <typename Number>
PolytopeSupportFunction<Number>::PolytopeSupportFunction( matrix_t<Number> constraints,
														  vector_t<Number> constraintConstants )
	: mConstraints( constraints ), mConstraintConstants( constraintConstants ), mDimension(mConstraints.cols()) {
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
}

template <typename Number>
PolytopeSupportFunction<Number>::PolytopeSupportFunction( const PolytopeSupportFunction<Number> &_origin )
	: mConstraints( _origin.constraints() ), mConstraintConstants( _origin.constants()), mDimension(mConstraints.cols() ) {
}

template <typename Number>
PolytopeSupportFunction<Number>::~PolytopeSupportFunction() {
}

template <typename Number>
PolytopeSupportFunction<Number>& PolytopeSupportFunction<Number>::operator=(const PolytopeSupportFunction<Number>& _orig){
    this->mConstraints = _orig.mConstraints;
    this->mConstraintConstants = _orig.mConstraintConstants;
    this->mDimension = _orig.mDimension;
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

	Optimizer<Number>& opt = Optimizer<Number>::getInstance();
	opt.setMatrix(mConstraints);
	opt.setVector(mConstraintConstants);

	std::pair<Number,SOLUTION> res = opt.evaluate(l);

#ifdef PPOLYTOPESUPPORTFUNCTION_VERBOSE
	std::cout << "PolytopeSupportFunction: evaluate in " << l << std::endl;
#endif

	assert( l.rows() == mDimension );

	result.supportValue = res.first;
	result.errorCode = res.second;

	return result;
}

template <typename Number>
std::vector<evaluationResult<Number>> PolytopeSupportFunction<Number>::multiEvaluate( const matrix_t<Number> &_A ) const {
	assert( _A.cols() == mDimension );
	std::vector<evaluationResult<Number>> res;

	for ( unsigned index = 0; index < _A.rows(); ++index ) {
		res.push_back(evaluate( _A.row( index ) ));
	}
	assert(res.size() == _A.rows());

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
	Optimizer<Number>& opt = Optimizer<Number>::getInstance();
	opt.setMatrix(mConstraints);
	opt.setVector(mConstraintConstants);
	return !opt.checkConsistency();
}

template <typename Number>
void PolytopeSupportFunction<Number>::print() const{
    std::cout << mConstraints << std::endl;
    std::cout << mConstraintConstants << std::endl;
}
}  // namespace
