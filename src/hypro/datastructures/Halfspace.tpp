/**
 *  Class that holds the implementation of a Halfspace.
 *  @file Halfspace.tpp
 *
 *  @author Stefan Schupp 	<stefan.schupp@cs.rwth-aachen.de>
 *
 *  @since 	2015-03-16
 *  @version 	2015-03-16
 */

#include "Halfspace.h"

namespace hypro {
template <typename Number>
Halfspace<Number>::Halfspace()
	: mNormal( vector_t<Number>::Zero( 1 ) ), mScalar( Number( 0 ) ), mIsInteger( true ) {
}

template <typename Number>
Halfspace<Number>::Halfspace( const Halfspace<Number> &_orig )
	: mNormal( _orig.mNormal ), mScalar( _orig.mScalar ), mIsInteger( _orig.isInteger() ) {
}

template <typename Number>
Halfspace<Number>::Halfspace( const Point<Number> &_vector, const Number &_off )
	: mNormal( _vector.rawCoordinates() ), mScalar( _off ), mIsInteger( false ) {
}

template <typename Number>
Halfspace<Number>::Halfspace( std::initializer_list<Number> _coordinates, const Number &_off ) {
	mNormal = vector_t<Number>( _coordinates.size() );
	unsigned pos = 0;
	for ( auto &coordinate : _coordinates ) {
		mNormal( pos ) = coordinate;
		++pos;
	}
	mScalar = _off;
	mIsInteger = false;
}

template <typename Number>
Halfspace<Number>::Halfspace( const vector_t<Number> &_vector, const Number &_off )
	: mNormal( _vector ), mScalar( _off ), mIsInteger( false ) {
}

template <typename Number>
Halfspace<Number>::Halfspace( const vector_t<Number> &_vec, const std::vector<vector_t<Number>> &_vectorSet ) {
	// here: Halfspace given in parameterform is converted to normalform
	// the normal vector of the Halfspace is computed by solving a system of
	// equations
	mNormal = computePlaneNormal( _vectorSet );
#ifdef fukuda_DEBUG
	std::cout << "computed Plane Normal: " << mNormal << std::endl;
#endif

	// the scalar is just the scalar product of the normal vector & a point in the
	// Halfspace
	mScalar = mNormal.dot( _vec );
#ifdef fukuda_DEBUG
	std::cout << "computed Offset: " << mScalar << std::endl;
#endif
	mIsInteger = false;
}

template <typename Number>
Halfspace<Number>::~Halfspace() {
}

template <typename Number>
unsigned Halfspace<Number>::dimension() const {
	return mNormal.nonZeros();
}

template<typename Number>
void Halfspace<Number>::projectOnDimensions( std::vector<unsigned> _dimensions ) {
	// TODO
	this->mHash = 0;
}

template <typename Number>
const vector_t<Number> &Halfspace<Number>::normal() const {
	return mNormal;
}

template <typename Number>
void Halfspace<Number>::setNormal( const vector_t<Number> &_normal ) {
	mNormal = _normal;
	this->mHash = 0;
	mIsInteger = false;
}

template<typename Number>
Halfspace<Number>& Halfspace<Number>::invert() {
	mNormal = -mNormal;
	mScalar = -mScalar;
	return *this;
}

template <typename Number>
Number Halfspace<Number>::offset() const {
	return mScalar;
}

template <typename Number>
void Halfspace<Number>::setOffset( Number _offset ) {
	mScalar = _offset;
	this->mHash = 0;
	mIsInteger = mIsInteger && carl::isInteger(_offset);
}

template <typename Number>
Number Halfspace<Number>::signedDistance( const vector_t<Number> &_point ) const {
	return ( _point.dot( mNormal ) - mScalar );
}

template <typename Number>
Number Halfspace<Number>::evaluate( const vector_t<Number> &_direction ) const {
	return ( _direction.dot( mNormal ) );
}

template <typename Number>
Point<Number> Halfspace<Number>::projectPointOnPlane( const Point<Number> point ) const {
	return Point<Number>( point.rawCoordinates() + ( (mScalar- point.rawCoordinates().dot(mNormal))/mNormal.dot(mNormal) ) * mNormal );
}

template <typename Number>
bool Halfspace<Number>::intersection( Number &_result, const vector_t<Number> &_vector ) const {
	bool intersect = false;
	Number factor = 0;
#ifdef fukuda_DEBUG
	std::cout << "mNormal: " << mNormal << std::endl;
#endif
	Number dotProduct = ( mNormal.dot( _vector ) );
#ifdef fukuda_DEBUG
	std::cout << "dotProduct: " << dotProduct << std::endl;
#endif
	if ( dotProduct != 0 ) {
		intersect = true;
		factor = mScalar / dotProduct;
	}
	_result = factor;
	// note: to get the intersection point -> _vector *= factor;
	return intersect;
}

template <typename Number>
bool Halfspace<Number>::intersection( Number &_result, const Point<Number> &_vector ) const {
	return intersection( _result, _vector.rawCoordinates() );
}

template<typename Number>
Halfspace<Number> Halfspace<Number>::project( const std::vector<unsigned>& dimensions ) const {
	if(dimensions.empty()) {
		return Halfspace<Number>();
	}

	vector_t<Number> projectedNormal = hypro::project(mNormal, dimensions);
	return Halfspace<Number>(projectedNormal, mScalar);
}

template <typename Number>
Halfspace<Number> Halfspace<Number>::linearTransformation( const matrix_t<Number> &A ) const {
	Eigen::FullPivLU<matrix_t<Number>> lu(A);
	// if A has full rank, we can simply retransform
	if(lu.rank() == A.rows()) {
		// Todo: Verify this.
		return Halfspace<Number>(mNormal.transpose()*A.inverse(), mScalar);
	} else {
		// we cannot invert A - chose points on the plane surface and create new plane
		assert(false);
		//TODO
		return Halfspace<Number>();
	}
}

template <typename Number>
Halfspace<Number> Halfspace<Number>::affineTransformation( const matrix_t<Number> &A,
															 const vector_t<Number> &b ) const {
	Eigen::FullPivLU<matrix_t<Number>> lu(A);
	// if A has full rank, we can simply retransform
	if(lu.rank() == A.rows()) {
		Number newOffset = mNormal.transpose()*A.inverse()*b;
		return Halfspace<Number>(mNormal.transpose()*A.inverse(), newOffset + mScalar);
	} else {
		// we cannot invert A - chose points on the plane surface and create new plane
		assert(false);
		//TODO
		return Halfspace<Number>();
	}
}

template <typename Number>
vector_t<Number> Halfspace<Number>::intersectionVector( const Halfspace<Number> &_rhs ) const {
	matrix_t<Number> A = matrix_t<Number>( 3, mNormal.rows() );
	A.row( 0 ) = mNormal.transpose();
	A.row( 1 ) = _rhs.normal().transpose();
	A.row( 2 ) = vector_t<Number>::Ones( A.cols() ).transpose();

	vector_t<Number> b = vector_t<Number>( 3 );
	b << mScalar, _rhs.offset(), Number( 1 );

	vector_t<Number> result = A.fullPivLu().solve( b );
	//vector_t<Number> result = gauss( A, b );

	return result;
}

template <typename Number>
vector_t<Number> Halfspace<Number>::fastIntersect( const std::vector<Halfspace<Number>>& _planes ) {
	assert(_planes.size() == _planes.begin()->dimension()); // TODO: Make function more general to cope with arbitrary input.

	matrix_t<Number> A( _planes.size(), _planes.begin()->dimension() );
	vector_t<Number> b( _planes.size() );
	std::size_t pos = 0;
	for(auto planeIt = _planes.begin(); planeIt != _planes.end(); ++planeIt){
		A.row(pos) = planeIt->normal().transpose();
		// std::cout << A.row(pos) << std::endl;
		b(pos) = planeIt->offset();
		// std::cout << b(pos) << std::endl;
		++pos;
	}

	//std::cout << "Created first matrix" << std::endl;

	Eigen::FullPivLU<matrix_t<Number>> lu_decomp( A );
	if ( lu_decomp.rank() < A.rows() ) {
		// TODO: Cope with intersection plane.
	}

	vector_t<Number> res = lu_decomp.solve( b );

	/*
	// check for infinity
	bool infty = false;
	for ( unsigned i = 0; i < res.rows(); ++i ) {
		if ( std::numeric_limits<Number>::infinity() == ( Number( res( i ) ) ) ) {
			//std::cout << ( Number( res( i ) ) ) << " is infty." << std::endl;
			infty = true;
			break;
		}
	}
	*/
	return res;
}

template <typename Number>
vector_t<Number> Halfspace<Number>::saveIntersect( const std::vector<Halfspace<Number>>& _planes, Number threshold ) {
	assert(_planes.size() == _planes.begin()->dimension()); // TODO: Make function more general to cope with arbitrary input.

	matrix_t<Number> A( _planes.size(), _planes.begin()->dimension() );
	vector_t<Number> b( _planes.size() );
	std::size_t pos = 0;
	for(auto planeIt = _planes.begin(); planeIt != _planes.end(); ++planeIt){
		A.row(pos) = planeIt->normal().transpose();
		// std::cout << A.row(pos) << std::endl;
		b(pos) = planeIt->offset();
		// std::cout << b(pos) << std::endl;
		++pos;
	}

	//std::cout << "Created first matrix" << std::endl;

	Eigen::FullPivLU<matrix_t<Number>> lu_decomp( A );
	if ( lu_decomp.rank() < A.rows() ) {
		// TODO: Cope with intersection plane.
	}

	vector_t<Number> res = lu_decomp.solve( b );

	std::vector<std::size_t> belowIndices;
	for(std::size_t index = 0; index < _planes.size(); ++index){
		Number dist = _planes.at(index).offset() - _planes.at(index).normal().dot(res);
		if(dist > 0) {
			belowIndices.push_back(index);
		}
	}
	Number eps = std::numeric_limits<Number>::epsilon();
	std::size_t iterationCount = 0;
	while (!belowIndices.empty()){
		//std::cout << "\r" << iterationCount << " Is below, ";
		// enlarge as long as point lies below one of the planes.
		if(eps < threshold) {
			eps = eps*2;
		} else {
			eps += std::numeric_limits<Number>::epsilon();
		}

		for(std::size_t index = 0; index < _planes.size(); ++index){
			A.row(index) = _planes.at(index).normal().transpose();
			//if(belowIndices.front() == index) {
				//std::cout << "Shift plane  + " << eps << ", dist: ";
				b(index) = _planes.at(index).offset() + eps;
			//	belowIndices.erase(belowIndices.begin());
			//} else {
			//	b(index) = _planes.at(index).offset();
			//}
		}
		belowIndices.clear();
		assert(belowIndices.empty());
		vector_t<Number> tmp = Eigen::FullPivLU<matrix_t<Number>>(A).solve( b );

		for(std::size_t i = 0; i < _planes.size(); ++i){
			Number dist = _planes.at(i).offset() - _planes.at(i).normal().dot(tmp);
			if(dist > 0) {
				//std::cout << dist << " ";
				belowIndices.push_back(i);
			}
		}
		//std::cout << std::flush;
		++iterationCount;
		if(belowIndices.empty()) {
			res = tmp;
		}
	}
	return res;
}


template <typename Number>
bool Halfspace<Number>::contains( const vector_t<Number> _vector ) const {
	return ( _vector.dot( mNormal ) <= mScalar );
}

template <typename Number>
bool Halfspace<Number>::contains( const Point<Number> _vector ) const {
	return this->contains(_vector.rawCoordinates());
}

template<typename Number>
bool Halfspace<Number>::contains( const std::vector<Point<Number>>& _points) const {
	for(const auto& point : _points){
		if(!carl::AlmostEqual2sComplement(point.rawCoordinates().dot(mNormal), mScalar, 128) && point.rawCoordinates().dot(mNormal) > mScalar){
			return false;
		}
	}
	return true;
}

template <typename Number>
bool Halfspace<Number>::holds( const vector_t<Number> _vector ) const {
	return ( _vector.dot( mNormal ) == mScalar );
}

/**
 * @author: Chris K
 * Method to compute the normal of a plane based on two direction vectors
 * simply computing the cross product does not work since the dimension is not
 * necessarily 3
 */
template <typename Number>
vector_t<Number> Halfspace<Number>::computePlaneNormal( const std::vector<vector_t<Number>> &_edgeSet ) {
	assert(_edgeSet.size() > 0);
	assert(_edgeSet.size() >= (unsigned)_edgeSet.begin()->rows() - 1);
	if(_edgeSet.size() == unsigned(_edgeSet.begin()->rows()) - 1 ) {
		// method avoiding glpk and using Eigen instead (higher precision)
		matrix_t<Number> constraints(_edgeSet.size(), _edgeSet.begin()->rows());
		for(unsigned pos = 0; pos < _edgeSet.size(); ++pos) {
			constraints.row(pos) = _edgeSet.at(pos).transpose();
		}
		vector_t<Number> normal = constraints.fullPivLu().kernel();

		return normal;
	} else {
		/*
		 * Setup LP with GLPK
		 */
		glp_prob *normal;
		normal = glp_create_prob();
		glp_set_obj_dir( normal, GLP_MAX );

		// we have one row for each edge in our set
		glp_add_rows( normal, _edgeSet.size() );

		// constraints of auxiliary variables (bounds for rows)
		for ( unsigned i = 1; i <= _edgeSet.size(); ++i ) {
			glp_set_row_bnds( normal, i, GLP_FX, 0.0, 0.0 );
		}

		// each column corresponds to one dimension of a vector in our edgeSet
		// TODO consider p1 & p2 of different dimensions? (-> two edge sets)
		glp_add_cols( normal, _edgeSet.at( 0 ).rows() );

		// coefficients of objective function:
		for ( unsigned i = 1; i <= _edgeSet.at( 0 ).rows(); ++i ) {
			glp_set_obj_coef( normal, i, 1.0 );
		}

		// constraints for structural variables
		for ( unsigned i = 1; i <= _edgeSet.at( 0 ).rows(); ++i ) {
			glp_set_col_bnds( normal, i, GLP_DB, -1.0, 1.0 );
		}

		// setup matrix coefficients
		unsigned elements = ( _edgeSet.size() ) * ( _edgeSet.at( 0 ).rows() );
		int* ia = new int[1 + elements];
		int* ja = new int[1 + elements];
		double* ar = new double[1 + elements];
		unsigned pos = 1;

		// to prevent bugs
		ia[0] = 0;
		ja[0] = 0;
		ar[0] = 0;

		for ( unsigned i = 1; i <= _edgeSet.size(); ++i ) {
			for ( unsigned j = 1; j <= _edgeSet.at( 0 ).rows(); ++j ) {
				ia[pos] = i;
				ja[pos] = j;
				vector_t<Number> tmpVec = _edgeSet.at( i - 1 );
				ar[pos] = carl::toDouble( tmpVec( j - 1 ) );
	#ifdef fukuda_DEBUG
				std::cout << "Coeff. at (" << i << "," << j << "): " << ar[pos] << std::endl;
	#endif
				++pos;
			}
		}
		assert( pos - 1 <= elements );

		glp_load_matrix( normal, elements, ia, ja, ar );
		glp_simplex( normal, NULL );
		glp_exact(normal, NULL);

		vector_t<Number> result = vector_t<Number>( _edgeSet.at( 0 ).rows(), 1 );

		// fill the result vector based on the optimal solution returned by the LP
		for ( unsigned i = 1; i <= _edgeSet.at( 0 ).rows(); ++i ) {
			result( i - 1 ) = carl::rationalize<Number>(glp_get_col_prim( normal, i ));
		}

		glp_delete_prob( normal );
		delete[] ja;
		delete[] ia;
		delete[] ar;

		return result;
	}
}

template<typename Number>
Number Halfspace<Number>::computePlaneOffset( const vector_t<Number>& normal, const Point<Number>& pointOnPlane) {
	return normal.dot(-pointOnPlane.rawCoordinates());
}

} // namespace hypro
