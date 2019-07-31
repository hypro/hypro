#include "Point.h"

namespace hypro {

template <typename Number>
Point<Number>::Point()
	: mCoordinates( vector_t<Number>::Zero( 0 ) ),
	mHash(0),
	// mNeighbors(),
	mComposedOf() {
	assert(this->dimension() == 0);
}

template <typename Number>
Point<Number>::Point( const Number &_value )
	:  // mNeighbors(),
	mHash(0),
	mComposedOf() {
	mCoordinates = vector_t<Number>( 1 );
	mCoordinates( 0 ) = _value;
	assert(this->dimension() >= 0);
}

template <typename Number>
Point<Number>::Point( std::initializer_list<Number> _coordinates )
	:  // mNeighbors(),
	mHash(0),
	mComposedOf()
	{
	unsigned count = 0;
	mCoordinates = vector_t<Number>( _coordinates.size() );
	for ( auto &coordinate : _coordinates ) {
		mCoordinates( count ) = Number( coordinate );
		++count;
	}
	assert(this->dimension() >= 0);
}

template <typename Number>
Point<Number>::Point( std::vector<Number> _coordinates )
	:  // mNeighbors(),
	mHash(0),
	mComposedOf() {
	unsigned count = 0;
	mCoordinates = vector_t<Number>( _coordinates.size() );
	for ( unsigned j = 0; j < _coordinates.size(); ++j ) {
		mCoordinates( count ) = _coordinates.at( count );
		++count;
	}
	assert(this->dimension() >= 0);
}

template <typename Number>
Point<Number>::Point( const vector_t<Number> &_vector )
	: mCoordinates( _vector ),
	mHash(0),
	// mNeighbors(),
	mComposedOf() {
	assert(this->dimension() >= 0);
}


template <typename Number>
Point<Number>::Point( vector_t<Number>&& _vector )
	: mCoordinates( _vector ),
	mHash(0),
	mComposedOf() {
	assert(this->dimension() >= 0);
}


template <typename Number>
Point<Number>::Point( const Point<Number> &_p )
	: mCoordinates( _p.rawCoordinates() ),
	mHash(0),
	// mNeighbors(_p.neighbors()),
	mComposedOf( _p.composedOf() ) {
	// std::cout << "This coordinates " << mCoordinates << " vs. " << _p.rawCoordinates() << std::endl;
  	// std::cout << "This hash " << this->hash() << " vs. " << std::endl;
  	// std::cout << _p.hash() << std::endl;
  	assert(mCoordinates == _p.rawCoordinates());
  	//assert(_p.hash() == this->hash());
  	assert(this->dimension() >= 0);
}

/*
template <typename Number>
Point<Number>::Point( Point<Number> &&_p )
	: mCoordinates( _p.rawCoordinates() ),
	mHash(0),
	// mNeighbors(std::move(_p.neighbors())),
	mComposedOf( std::move( _p.composedOf() ) ) {
	assert(this->dimension() >= 0);
}
*/

/*
template<typename Number>
std::vector<Point<Number>> Point<Number>::neighbors() const {
		return mNeighbors;
}

template<typename Number>
void Point<Number>::setNeighbors(const std::vector<Point<Number> >& _neighbors)
{
		mNeighbors = _neighbors;
}

template<typename Number>
void Point<Number>::joinNeighbors(const std::vector<Point<Number> >& _neighbors)
{
		for(unsigned i = 0; i<_neighbors.size(); i++){
				if(!isNeighbor(_neighbors.at(i))){
						addNeighbor(_neighbors.at(i));
				}
		}
}

template<typename Number>
void Point<Number>::addNeighbor(const Point<Number>& _neighbor) {
		bool alreadyNeighbor = false;
		for(unsigned i = 0; i< mNeighbors.size(); i++) {
				if(mNeighbors.at(i) == _neighbor){
						alreadyNeighbor = true;
				}
		}
		if(!alreadyNeighbor) {
				mNeighbors.push_back(_neighbor);
		}
}

template<typename Number>
bool Point<Number>::isNeighbor(const Point<Number>& _neighbor) {
		for(unsigned i = 0; i< mNeighbors.size(); i++) {
				if(mNeighbors.at(i) == _neighbor){
						return true;
				}
		}
		return false;
}

template<typename Number>
void Point<Number>::removeNeighbor(const Point<Number>& _neighbor) {
		for(unsigned i = 0; i < mNeighbors.size(); i++){
				if((mNeighbors.at(i)) == (_neighbor)) {
						mNeighbors.erase(mNeighbors.begin() + i);
						break;
				}
		}
}
*/

template <typename Number>
std::vector<Point<Number>> Point<Number>::composedOf() const {
	return mComposedOf;
}

template <typename Number>
void Point<Number>::setComposition( const std::vector<Point<Number>> &_elements ) {
	mComposedOf = _elements;
	mHash = 0;
}

template <typename Number>
void Point<Number>::addToComposition( const Point<Number> &_element ) {
	mComposedOf.push_back( _element );
	mHash = 0;
}

template <typename Number>
Point<Number> Point<Number>::origin() const {
	vector_t<Number> coordinates = vector_t<Number>::Zero( this->dimension() );
	Point<Number> result = Point<Number>( coordinates );
	return result;
}

template <typename Number>
Number Point<Number>::coordinate( const carl::Variable &_var ) const {
	return mCoordinates( hypro::VariablePool::getInstance().id( _var ) );
}

template <typename Number>
Number Point<Number>::coordinate( std::size_t _dimension ) const {
	assert( std::size_t(mCoordinates.size()) > _dimension );
	return mCoordinates( _dimension );
}

template <typename Number>
typename Point<Number>::coordinateMap Point<Number>::coordinates() const {
	coordinateMap res;
	for ( unsigned i = 0; i < mCoordinates.rows(); ++i ) {
		res.insert( std::make_pair( hypro::VariablePool::getInstance().carlVarByIndex( i ), mCoordinates( i ) ) );
	}
	return res;
}

template <typename Number>
const vector_t<Number> &Point<Number>::rawCoordinates() const {
	return mCoordinates;
}

template <typename Number>
void Point<Number>::setCoordinate( const carl::Variable &_dim, const Number &_value ) {
	unsigned dim = hypro::VariablePool::getInstance().id( _dim );
	assert( dim >= 0 );
	if ( dim >= mCoordinates.rows() ) {
		vector_t<Number> old = mCoordinates;
		mCoordinates.resize( dim + 1 );
		mCoordinates.topLeftCorner( old.rows(), 1 ) = old;
	}
	mCoordinates( dim ) = _value;
	mHash = 0;
}

template <typename Number>
void Point<Number>::setCoordinate( std::size_t dimension, const Number& _value ) {
	assert( dimension >= 0 );
	if ( Eigen::Index(dimension) >= mCoordinates.rows() ) {
		vector_t<Number> old = mCoordinates;
		mCoordinates.resize( dimension + 1 );
		mCoordinates.topLeftCorner( old.rows(), 1 ) = old;
	}
	mCoordinates( dimension ) = _value;
	mHash = 0;
}

template <typename Number>
void Point<Number>::swap( Point<Number> &_rhs ) {
	auto tmp = this->mCoordinates;
	this->mCoordinates = _rhs.mCoordinates;
	_rhs.mCoordinates = tmp;
	// std::swap(this->mNeighbors, _rhs.mNeighbors);

	std::swap( this->mComposedOf, _rhs.mComposedOf );
	_rhs.mHash = 0;
	mHash = 0;
}

template <typename Number>
void Point<Number>::setCoordinates( const vector_t<Number> &vector ) {
	mCoordinates = vector;
	mHash = 0;
}

template <typename Number>
unsigned Point<Number>::dimension() const {
	assert(mCoordinates.rows() >= 0);
	return unsigned(mCoordinates.rows());
}

template <typename Number>
void Point<Number>::reduceDimension( unsigned _dimension ) {
	if ( _dimension < mCoordinates.rows() ) {
		vector_t<Number> newCoordinates = vector_t<Number>( _dimension );
		for ( unsigned pos = 0; pos < _dimension; ++pos ) {
			newCoordinates( pos ) = mCoordinates( pos );
		}
		mCoordinates = newCoordinates;
	}
	assert( mCoordinates.rows() <= _dimension );
	mHash = 0;
}

template <typename Number>
Point<Number> Point<Number>::reduceToDimensions( std::vector<unsigned> _dimensions ) const {
	TRACE("hypro.datastructures.point","*this: " << *this);
	if(_dimensions.size() == 0) {
		return Point<Number>();
	}
	vector_t<Number> newCoordinates = vector_t<Number>( _dimensions.size() );
	unsigned tPos = 0;
	for ( const auto sPos : _dimensions ) {
		TRACE("hypro.datastructures.point","consider dimension " << sPos);
		assert(sPos < mCoordinates.rows());
		assert(sPos >= 0);
		newCoordinates( tPos ) = mCoordinates( sPos );
		++tPos;
	}
	return Point<Number>(newCoordinates);
}

template <typename Number>
std::vector<carl::Variable> Point<Number>::variables() const {
	std::vector<carl::Variable> variables;
	for ( unsigned i = 0; i != mCoordinates.rows(); ++i ) {
		variables.push_back( hypro::VariablePool::getInstance().carlVarByIndex( i ) );
	}
	return variables;
}

template <typename Number>
Point<Number> Point<Number>::extAdd( const Point<Number> &_rhs ) const {
	assert( mCoordinates.rows() == _rhs.rawCoordinates().rows() );

	Point<Number> result = Point<Number>( mCoordinates + _rhs.rawCoordinates() );
	return result;
}

template <typename Number>
Number Point<Number>::distance( const Point<Number> &_rhs ) const {
	return ( norm( vector_t<Number>(mCoordinates - _rhs.rawCoordinates()) ) );
}

template <typename Number>
std::vector<Number> Point<Number>::polarCoordinates( const Point<Number> &_origin, bool _radians ) const {
	Point<Number> base = *this - _origin;
	vector_t<double> transformedCoordinates = vector_t<double>(base.dimension());
	for( unsigned d = 0; d < base.dimension(); ++d) {
		transformedCoordinates(d) = carl::convert<Number, double>(base.at(d));
	}

	std::vector<Number> result;

	// 1st component of the result is the radial part, the following components
	// are the angles.
	double radialCoordinate = 0;
	for ( unsigned i = 0; i < base.dimension(); ++i ) {
		double square;
		square = carl::pow( transformedCoordinates( i ), 2 );
		radialCoordinate += square;
	}
	radialCoordinate = carl::sqrt( radialCoordinate );
	result.insert( result.begin(), carl::convert<double, Number>(radialCoordinate) );

	// compute polar angles
	for ( unsigned dimension = 0; dimension < base.dimension() - 1; ++dimension ) {
		double angle( 0 );
		for ( auto dimension2 = dimension; dimension2 < base.dimension(); ++dimension2 ) {
			angle += carl::pow( transformedCoordinates( dimension2 ), 2 );
		}
		angle = carl::sqrt( angle );
		angle = ( transformedCoordinates( dimension ) / angle );
		angle = std::acos( angle );

		if ( !_radians ) {
			angle /= 2 * PI_DN;
			angle *= 360;
		}
		result.emplace_back( std::move( carl::convert<double,Number>(angle) ) );
	}
	if ( ( base.mCoordinates( base.dimension() - 1 ) ) < Number( 0 ) ) {
		Number tmp = result.back();
		result.pop_back();
		if ( !_radians ) {
			tmp = Number( 360 ) - tmp;
		} else {
			tmp = -tmp;
		}
		result.push_back( tmp );
	}
	assert( result.size() == this->dimension() );
	return result;
}

template <typename Number>
Point<Number> Point<Number>::newEmpty() const {
	vector_t<Number> origin = vector_t<Number>::Zero( this->dimension() );
	return Point<Number>( origin );
}

template<typename Number>
Point<Number> Point<Number>::project( const std::vector<std::size_t>& dimensions ) const {
	if(dimensions.empty()) {
		return Point<Number>();
	}

	vector_t<Number> projectedCoordinates = vector_t<Number>::Zero(dimensions.size());

	for(unsigned i = 0; i < dimensions.size(); ++i) {
		if(dimensions.at(i) < this->dimension() && dimensions.at(i) >= 0) {
			projectedCoordinates(i) = mCoordinates(dimensions.at(i));
		}
	}
	return Point<Number>(projectedCoordinates);
}

template <typename Number>
Point<Number> Point<Number>::linearTransformation( const matrix_t<Number> &A ) const {
	//std::cout << "Linear trafo of " << mCoordinates << " with " << A << " and " << b << std::endl;
	assert(A.cols() == mCoordinates.rows());
	return Point<Number>( A * mCoordinates );
}

template <typename Number>
Point<Number> Point<Number>::affineTransformation( const matrix_t<Number> &A, const vector_t<Number> &b ) const {
	//std::cout << "Linear trafo of " << mCoordinates << " with " << A << " and " << b << std::endl;
	assert(A.cols() == mCoordinates.rows());
	assert(b.rows() == mCoordinates.rows());
	return Point<Number>( A * mCoordinates + b );
}

template <typename Number>
Number Point<Number>::sum() const {
	Number sum = mCoordinates.dot( vector_t<Number>::Ones( mCoordinates.rows() ) );
	return sum;
}

template <typename Number>
void Point<Number>::incrementInFixedDim( const carl::Variable &_d ) {
	mCoordinates( hypro::VariablePool::getInstance().id( _d ) ) += 1;
	mHash = 0;
}

template <typename Number>
void Point<Number>::incrementInFixedDim( unsigned _d ) {
	mCoordinates( _d ) += Number(1);
	mHash = 0;
}

template <typename Number>
void Point<Number>::incrementInAllDim( const Number &_val ) {
	vector_t<Number> one = vector_t<Number>::Ones( mCoordinates.rows() );
	one *= _val;
	mCoordinates += one;
	mHash = 0;
}

template <typename Number>
void Point<Number>::decrementInFixedDim( const carl::Variable &_d ) {
	mCoordinates( hypro::VariablePool::getInstance().id( _d ) ) -= 1;
	mHash = 0;
}

template <typename Number>
void Point<Number>::decrementInFixedDim( unsigned _d ) {
	mCoordinates( _d ) -= Number(1);
	mHash = 0;
}

template <typename Number>
Point<Number> Point<Number>::getPredecessorInDimension( const carl::Variable &_d ) const {
	Point<Number> pred = Point<Number>( *this );
	pred.decrementInFixedDim( _d );
	return pred;
}

template <typename Number>
Point<Number> Point<Number>::getPredecessorInDimension( unsigned _d ) const {
	Point<Number> pred = Point<Number>( *this );
	pred.decrementInFixedDim( _d );
	return pred;
}

template <typename Number>
bool Point<Number>::isInBoundary( const Point<Number> &_boundary ) const {
	return ( mCoordinates < _boundary.rawCoordinates() );
}

template <typename Number>
bool Point<Number>::hasDimension( const carl::Variable &_i ) const {
	return ( mCoordinates.rows() > Eigen::Index(hypro::VariablePool::getInstance().id( _i )) );
}

template <typename Number>
bool Point<Number>::hasDimensions( const std::vector<carl::Variable> &_variables ) const {
	for ( auto it : _variables ) {
		if ( !hasDimension( it ) ) {
			return false;
		}
	}
	return true;
}

template <typename Number>
std::vector<bool> Point<Number>::lesserDimensionPattern( const Point<Number> &_p1, const Point<Number> &_p2 ) {
	assert( _p1.dimension() == _p2.dimension() );
	std::vector<bool> res;
	res.resize( _p1.dimension() );
	for ( unsigned pos = 0; pos < res.size(); ++pos ) {
		res[pos] = _p1.at( pos ) < _p2.at( pos ) ? true : false;
	}
	return res;
}

template <typename Number>
bool Point<Number>::haveEqualCoordinate( const Point<Number> &_p2 ) const {
	if ( dimension() == _p2.dimension() ) {
		for ( unsigned i = 0; i < mCoordinates.rows(); ++i ) {
			if ( mCoordinates( i ) == _p2.rawCoordinates()( i ) ) {
				return true;
			}
		}
	}
	return false;
}

template <typename Number>
bool Point<Number>::haveSameDimensions( const Point<Number> &_p ) const {
	return ( dimension() == _p.dimension() );
}

template <typename Number>
Point<Number> &Point<Number>::operator+=( const Point<Number> &_rhs ) {
	assert( this->dimension() == _rhs.dimension() );
	for ( unsigned i = 0; i < mCoordinates.rows(); ++i ) {
		mCoordinates( i ) += _rhs.at( i );
	}
	mHash = 0;
	return *this;
}

template <typename Number>
Point<Number> &Point<Number>::operator+=( const vector_t<Number> &_rhs ) {
	assert( this->dimension() == _rhs.rows() );
	for ( unsigned i = 0; i < mCoordinates.rows(); ++i ) {
		mCoordinates( i ) += _rhs( i );
	}
	mHash = 0;
	return *this;
}

template <typename Number>
Point<Number> &Point<Number>::operator-=( const Point<Number> &_rhs ) {
	assert( this->dimension() == _rhs.dimension() );
	for ( unsigned i = 0; i < mCoordinates.rows(); ++i ) {
		mCoordinates( i ) -= _rhs.at( i );
	}
	mHash = 0;
	return *this;
}

template <typename Number>
Point<Number> &Point<Number>::operator-=( const vector_t<Number> &_rhs ) {
	assert( this->dimension() == _rhs.rows() );
	for ( unsigned i = 0; i < mCoordinates.rows(); ++i ) {
		mCoordinates( i ) -= _rhs( i );
	}
	mHash = 0;
	return *this;
}

template<typename Number>
Point<Number> Point<Number>::operator-() const {
    return Point<Number>(-mCoordinates);
}

template <typename Number>
Point<Number> &Point<Number>::operator/=( unsigned _quotient ) {
	for ( unsigned i = 0; i < mCoordinates.rows(); ++i ) {
		mCoordinates( i ) = mCoordinates( i ) / _quotient;
	}
	mHash = 0;
	return *this;
}

template <typename Number>
Point<Number> &Point<Number>::operator*=( const Number _factor ) {
	for ( unsigned i = 0; i < mCoordinates.rows(); ++i ) {
		mCoordinates( i ) = mCoordinates( i ) * _factor;
	}
	mHash = 0;
	return *this;
}

/*
template <typename Number>
Point<Number> &Point<Number>::operator=( const Point<Number> &_in ) {
	mCoordinates = _in.rawCoordinates();
	// this->mNeighbors = _in.neighbors();
	mComposedOf = _in.composedOf();
	mHash = 0;
	return *this;
}

template <typename Number>
Point<Number> &Point<Number>::operator=( Point<Number> &&_in ) {
	mCoordinates = _in.rawCoordinates();
	// this->mNeighbors = _in.neighbors();
	mComposedOf = _in.composedOf();
	mHash = 0;
	return *this;
}
*/

template <typename Number>
Point<Number>& Point<Number>::operator=( const vector_t<Number>& _in ) {
	mCoordinates = _in;
	mHash = 0;
	return *this;
}

template <typename Number>
Point<Number>& Point<Number>::operator=( vector_t<Number>&& _in ) {
	mCoordinates = std::move(_in);
	mHash = 0;
	return *this;
}


template <typename Number>
Number &Point<Number>::operator[]( const carl::Variable &_i ) {
	unsigned dim = hypro::VariablePool::getInstance().id( _i );
	return mCoordinates( dim );
}

template <typename Number>
Number &Point<Number>::operator[]( std::size_t _i ) {
	return mCoordinates( _i );
}

template <typename Number>
const Number &Point<Number>::operator[]( const carl::Variable &_i ) const {
	unsigned dim = hypro::VariablePool::getInstance().id( _i );
	return mCoordinates( dim );
}

template <typename Number>
const Number &Point<Number>::operator[]( std::size_t _i ) const {
	return mCoordinates( _i );
}

template <typename Number>
Number& Point<Number>::at( const carl::Variable &_i ) {
	if(hypro::VariablePool::getInstance().id( _i ) >= mCoordinates.rows()) {
		throw std::out_of_range("Variable dimension larger than state space of vector");
	}
	return mCoordinates( hypro::VariablePool::getInstance().id( _i ) );
}

template <typename Number>
Number& Point<Number>::at( std::size_t _index ) {
	if(Eigen::Index(_index) >= mCoordinates.rows()) {
		throw std::out_of_range("Index larger than state space of vector");
	}
	return mCoordinates( _index );
}

template <typename Number>
const Number& Point<Number>::at( const carl::Variable &_i ) const {
	if(hypro::VariablePool::getInstance().id( _i ) >= mCoordinates.rows()) {
		throw std::out_of_range("Variable dimension larger than state space of vector");
	}
	return mCoordinates( hypro::VariablePool::getInstance().id( _i ) );
}

template <typename Number>
const Number& Point<Number>::at( std::size_t _index ) const {
	if(Eigen::Index(_index) >= mCoordinates.rows()) {
		throw std::out_of_range("Index larger than state space of vector");
	}
	return mCoordinates( _index );
}
}  // namespace hypro
