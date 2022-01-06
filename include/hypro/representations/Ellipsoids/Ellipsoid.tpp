/*
 * @file EllipsoidT.tpp
 *
 * @author Phillip Florian
 *
 * @since	2016-05-04
 * @version	2016-05-04
 */

#include "Ellipsoid.h"

namespace hypro {

template <typename Number, typename Converter>
EllipsoidT<Number, Converter>::EllipsoidT( Number _radius, std::size_t _dimension ) {
	mShapeMatrix = matrix_t<Number>::Zero( _dimension, _dimension );
	for ( std::size_t i = 0; i < _dimension; i++ ) {
		mShapeMatrix( i, i ) = _radius;
	}
	mDimension = _dimension;
	mIsEmpty = empty();
}

template <typename Number, typename Converter>
EllipsoidT<Number, Converter>::EllipsoidT( matrix_t<Number> _matrix )
	: mDimension( _matrix.rows() )
	, mShapeMatrix( _matrix ) {
	assert( _matrix.transpose() == _matrix );  // symmetric
											   // Todo: _matrix is positive definite? x * Qx >= 0
	mIsEmpty = empty();
}

template <typename Number, typename Converter>
EllipsoidT<Number, Converter>::EllipsoidT( const EllipsoidT<Number, Converter>& _orig )
	: mDimension( _orig.dimension() )
	, mShapeMatrix( _orig.matrix() ) {
	mIsEmpty = empty();
}

template <typename Number, typename Converter>
EllipsoidT<Number, Converter>::~EllipsoidT() {
}

template <typename Number, typename Converter>
matrix_t<Number> EllipsoidT<Number, Converter>::matrix() const {
	return mShapeMatrix;
}

template <typename Number, typename Converter>
std::size_t EllipsoidT<Number, Converter>::dimension() const {
	return mDimension;
}

template <typename Number, typename Converter>
bool EllipsoidT<Number, Converter>::empty() const {
	for ( unsigned i = 0; i < mShapeMatrix.rows(); i++ ) {
		for ( unsigned j = 0; j < mShapeMatrix.cols(); j++ ) {
			if ( mShapeMatrix( i, j ) != 0 )
				return false;
		}
	}
	return true;
}

template <typename Number, typename Converter>
EllipsoidT<Number, Converter> EllipsoidT<Number, Converter>::linearTransformation( const matrix_t<Number>& _A ) const {
	return EllipsoidT<Number, Converter>( _A * mShapeMatrix * _A.transpose() );
}

template <typename Number, typename Converter>
EllipsoidT<Number, Converter> EllipsoidT<Number, Converter>::affineTransformation( const matrix_t<Number>& _A, const vector_t<Number>& _b ) const {
	vector_t<Number> b = _b;  // TODO remove this. just wanted to get rid of the warning
	return EllipsoidT<Number, Converter>( _A * mShapeMatrix * _A.transpose() );
}

template <typename Number, typename Converter>
EllipsoidT<Number, Converter> EllipsoidT<Number, Converter>::minkowskiSum( const EllipsoidT<Number, Converter>& _rhs, bool _approx ) const {
	// TODO l needs to be normalized in order for this to work!!
	vector_t<Number> l;
	l.setZero( this->mDimension );
	l( 0 ) = 1;
	if ( mIsEmpty ) {
		return EllipsoidT<Number, Converter>( _rhs );
	}
	Number lhsScalar, rhsScalar;
	Number lhsFactor, rhsFactor;
	lhsScalar = carl::sqrt( l.dot( this->mShapeMatrix * l ) );
	rhsScalar = carl::sqrt( l.dot( _rhs.mShapeMatrix * l ) );
	lhsFactor = ( lhsScalar + rhsScalar ) / lhsScalar;
	rhsFactor = ( lhsScalar + rhsScalar ) / rhsScalar;
	matrix_t<Number> matrix = lhsFactor * this->mShapeMatrix + rhsFactor * _rhs.mShapeMatrix;
	if ( _approx ) {
		return EllipsoidT<Number, Converter>( approxEllipsoidTMatrix( matrix ) );
	} else {
		return EllipsoidT<Number, Converter>( matrix );
	}
}

template <typename Number, typename Converter>
matrix_t<Number> EllipsoidT<Number, Converter>::approxEllipsoidTMatrix( const matrix_t<Number> _matrix ) const {
	matrix_t<Number> roundetMatrix( _matrix.rows(), _matrix.cols() );
	Number remains = 0;
	Number roundedValue;
	std::size_t dim = _matrix.rows();
	for ( std::size_t j = 0; j < dim - 1; j++ ) {
		for ( std::size_t k = j + 1; k < dim; k++ ) {
			if ( _matrix( j, k ) > 0 ) {
				roundedValue = carl::floor( _matrix( j, k ) * (Number)fReach_DENOMINATOR ) / (Number)fReach_DENOMINATOR;
				remains += 2 * ( _matrix( j, k ) - roundedValue );
				roundetMatrix( j, k ) = roundedValue;
				roundetMatrix( k, j ) = roundedValue;
			} else if ( _matrix( j, k ) < 0 ) {
				roundedValue = carl::ceil( _matrix( j, k ) * (Number)fReach_DENOMINATOR ) / (Number)fReach_DENOMINATOR;
				remains -= 2 * ( _matrix( j, k ) - roundedValue );
				roundetMatrix( j, k ) = roundedValue;
				roundetMatrix( k, j ) = roundedValue;
			}
		}
	}
	Number newEntry = 0;
	for ( std::size_t i = 0; i < dim; i++ ) {
		newEntry = _matrix( i, i ) + remains;
		if ( newEntry >= 0 ) {
			roundetMatrix( i, i ) = carl::ceil( newEntry * (Number)fReach_DENOMINATOR ) / (Number)fReach_DENOMINATOR;

		} else {
			roundetMatrix( i, i ) = carl::floor( newEntry * (Number)fReach_DENOMINATOR ) / (Number)fReach_DENOMINATOR;
			assert( false );  // TODO -fix me
		}
	}
	return roundetMatrix;
}

template <typename Number, typename Converter>
vector_t<Number> EllipsoidT<Number, Converter>::evaluate( vector_t<Number> const _l ) const {
	return _l * ( carl::sqrt( _l.dot( mShapeMatrix * _l ) ) );
}

}  // namespace hypro
