/**
 * Implementation of the box.
 *
 * @file Box.tpp
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since   2014-01-16
 * @version 2015-02-27
 */

#include "Box.h"

namespace hypro {

	template<typename Number, typename Converter>
	BoxT<Number,Converter>::BoxT( const std::vector<carl::Interval<Number>>& _intervals )
	{
		if(!_intervals.empty()) {
			vector_t<Number> lower = vector_t<Number>(_intervals.size());
			vector_t<Number> upper = vector_t<Number>(_intervals.size());
			for (std::size_t dim = 0; dim < _intervals.size(); ++dim) {
				lower(dim) = _intervals.at(dim).lower();
				upper(dim) = _intervals.at(dim).upper();
			}
			mLimits = std::make_pair(Point<Number>(lower), Point<Number>(upper));
		}
	}

	template<typename Number, typename Converter>
	BoxT<Number,Converter>::BoxT( const matrix_t<Number>& _constraints, const vector_t<Number>& _constants )
	{
		// calculate all possible Halfspace intersections -> TODO: dPermutation can
		// be improved.
		assert(_constraints.rows() == _constants.rows());
		Permutator permutator = Permutator( _constraints.rows(), _constraints.cols() );
		matrix_t<Number> intersection = matrix_t<Number>( _constraints.cols(), _constraints.cols() );
		vector_t<Number> intersectionConstants = vector_t<Number>( _constraints.cols() );
		std::set<vector_t<Number>> possibleVertices;
		std::vector<unsigned> permutation;
		while ( !permutator.end()  ) {
			permutation = permutator();
			unsigned rowCount = 0;
			// std::cout << "Intersect :" << std::endl;
			for ( const auto &rowIndex : permutation ) {
				// std::cout << _constraints.row(rowIndex) << " <= " <<
				// _constants(rowIndex) << std::endl;
				assert(rowCount < _constraints.cols());
				intersection.row( rowCount ) = _constraints.row( rowIndex );
				intersectionConstants( rowCount ) = _constants( rowIndex );
				++rowCount;
			}
			// check if rank is full
			if ( intersection.fullPivLu().rank() == intersection.cols() ) {
				vector_t<Number> vertex = intersection.fullPivLu().solve( intersectionConstants );
				assert(vertex.rows() == _constraints.cols());
				possibleVertices.emplace( std::move(vertex) );
				// std::cout<< "Vertex computed: " << vertex.transpose() << std::endl;
			}
		}

		// check if vertices are true vertices (i.e. they fulfill all constraints)
		for ( auto vertex = possibleVertices.begin(); vertex != possibleVertices.end(); ) {
			// std::cout<<__func__ << " : " <<__LINE__ << " current position : " << i <<
			// std::endl;
			// std::cout<<__func__ << " : " <<__LINE__ << "number of vertices : " <<
			// possibleVertices.size() << std::endl;
			bool deleted = false;
			for ( unsigned rowIndex = 0; rowIndex < _constraints.rows(); ++rowIndex ) {
				Number res = vertex->dot( _constraints.row( rowIndex ) );
				if ( res > _constants( rowIndex ) ) {
					vertex = possibleVertices.erase( vertex );
					deleted = true;
					break;
				}
			}
			if(!deleted) {
				++vertex;
			}
		}
		// std::cout<<__func__ << " : " <<__LINE__ <<std::endl;
		// finish initialization
		assert(!possibleVertices.empty());
		vector_t<Number> min = *possibleVertices.begin();
		vector_t<Number> max = *possibleVertices.begin();
		for ( const auto &point : possibleVertices ) {
			for( unsigned d = 0; d < point.rows(); ++d){
				if( min(d) > point(d)) {
					min(d) = point(d);
				}
				if( max(d) < point(d)) {
					max(d) = point(d);
				}
			}
		}
		mLimits = std::make_pair(Point<Number>(min), Point<Number>(max));
	}

template<typename Number, typename Converter>
BoxT<Number,Converter>::BoxT( const std::set<Point<Number>> &_points ) {
	if ( !_points.empty() ) {
		vector_t<Number> lower = _points.begin()->rawCoordinates();
		vector_t<Number> upper = _points.begin()->rawCoordinates();
		for(const auto& point : _points) {
			for(std::size_t d = 0; d < point.dimension(); ++d){
				if(point.at(d) < lower(d)) {
					lower(d) = point.at(d);
				}

				if(point.at(d) > upper(d)) {
					upper(d) = point.at(d);
				}
			}
		}
		mLimits = std::make_pair(Point<Number>(lower), Point<Number>(upper));
	}
}

template<typename Number, typename Converter>
BoxT<Number,Converter>::BoxT( const std::vector<Point<Number>> &_points ) {
	if ( !_points.empty() ) {
		vector_t<Number> lower = _points.begin()->rawCoordinates();
		vector_t<Number> upper = _points.begin()->rawCoordinates();
		for(const auto& point : _points) {
			for(std::size_t d = 0; d < point.dimension(); ++d){
				if(point.at(d) < lower(d)) {
					lower(d) = point.at(d);
				}

				if(point.at(d) > upper(d)) {
					upper(d) = point.at(d);
				}
			}
		}
		mLimits = std::make_pair(Point<Number>(lower), Point<Number>(upper));
	}
}

/*
template<typename Number, typename Converter>
BoxT<Number,Converter>::BoxT( const std::set<Vertex<Number>> &_vertices ) {
	if ( !_vertices.empty() ) {
		vector_t<Number> lower = _vertices.begin()->rawCoordinates();
		vector_t<Number> upper = _vertices.begin()->rawCoordinates();
		for(const auto& point : _vertices) {
			for(std::size_t d = 0; d < point.dimension(); ++d){
				if(point.at(d) < lower(d))
					lower(d) = point.at(d);

				if(point.at(d) > upper(d))
					upper(d) = point.at(d);
			}
		}
		mLimits = std::make_pair(Point<Number>(lower), Point<Number>(upper));
	}
}
*/

/*
template<typename Number, typename Converter>
BoxT<Number,Converter>::BoxT( const std::vector<Vertex<Number>> &_vertices ) {
	if ( !_vertices.empty() ) {
		vector_t<Number> lower = _vertices.begin()->rawCoordinates();
		vector_t<Number> upper = _vertices.begin()->rawCoordinates();
		for(const auto& point : _vertices) {
			for(std::size_t d = 0; d < point.dimension(); ++d){
				if(point.at(d) < lower(d))
					lower(d) = point.at(d);

				if(point.at(d) > upper(d))
					upper(d) = point.at(d);
			}
		}
		mLimits = std::make_pair(Point<Number>(lower), Point<Number>(upper));
	}
	std::cout << "Constructed box " << *this << std::endl;
}
*/

template<typename Number, typename Converter>
std::vector<carl::Interval<Number>> BoxT<Number,Converter>::boundaries() const {
	std::vector<carl::Interval<Number>> result;
	result.reserve(this->dimension());

	for(std::size_t d = 0; d < this->dimension(); ++d) {
		result.push_back(carl::Interval<Number>(mLimits.first.at(d), mLimits.second.at(d)));
	}

	return result;
}

template<typename Number, typename Converter>
std::vector<Halfspace<Number>> BoxT<Number,Converter>::constraints() const {
	std::vector<Halfspace<Number>> res;
	if(this->dimension() != 0) {
		std::size_t dim = this->dimension();
		res.reserve(2*dim);
		for( std::size_t d = 0; d < dim; ++d) {
			vector_t<Number> low = vector_t<Number>::Zero(dim);
			low(d) = -1;
			vector_t<Number> up = vector_t<Number>::Zero(dim);
			up(d) = 1;
			Number lOff = -mLimits.first.at(d);
			Number uOff = mLimits.second.at(d);
			res.emplace_back(low, lOff);
			res.emplace_back(up, uOff);
		}
	}
	return res;
}

/*
template<typename Number, typename Converter>
void BoxT<Number,Converter>::insert( const std::vector<carl::Interval<Number>>& boundaries ) {
	for(const auto& interval : boundaries) {
		mLimits.first.extend(interval.lower());
		mLimits.second.extend(interval.upper());
	}
}
*/
template<typename Number, typename Converter>
carl::Interval<Number> BoxT<Number,Converter>::interval( std::size_t d ) const {
	if ( d > mLimits.first.dimension() ) {
		return carl::Interval<Number>::emptyInterval();
	}
	return carl::Interval<Number>(mLimits.first.at(d), mLimits.second.at(d));
}

template<typename Number, typename Converter>
Number BoxT<Number,Converter>::supremum() const {
	Number max = 0;
	for ( auto &point : this->vertices() ) {
		Number inftyNorm = hypro::Point<Number>::inftyNorm( point );
		max = max > inftyNorm ? max : inftyNorm;
	}
	return max;
}

template<typename Number, typename Converter>
std::vector<Point<Number>> BoxT<Number,Converter>::vertices() const {
	std::vector<Point<Number>> result;
	std::size_t limit = pow( 2, mLimits.first.dimension() );

	for ( std::size_t bitCount = 0; bitCount < limit; ++bitCount ) {
		vector_t<Number> coord = vector_t<Number>( dimension() );
		for ( std::size_t dimension = 0; dimension < this->dimension(); ++dimension ) {
			std::size_t pos = ( 1 << dimension );
			if ( bitCount & pos ) {
				coord( dimension ) = mLimits.second.at(dimension);
			} else {
				coord( dimension ) = mLimits.first.at(dimension);
			}
		}
		result.push_back( Point<Number>( coord ) );
	}
	return result;
}

template<typename Number, typename Converter>
std::size_t BoxT<Number,Converter>::size() const {
	if(this->empty()) {
		return 0;
	}
	// TODO: What is this supposed to do???
	return 2;
}

template<typename Number, typename Converter>
BoxT<Number,Converter> BoxT<Number,Converter>::makeSymmetric() const {
	Point<Number> limit = mLimits.first;
	for(unsigned d = 0; d < mLimits.first.dimension(); ++d) {
		limit[d] = carl::abs(mLimits.first.at(d)) >= carl::abs(mLimits.second.at(d)) ? carl::abs(mLimits.first.at(d)) : carl::abs(mLimits.second.at(d));
	}
	return BoxT<Number,Converter>(std::make_pair(-limit, limit));
}

template<typename Number, typename Converter>
std::pair<bool, BoxT<Number,Converter>> BoxT<Number,Converter>::satisfiesHalfspace( const vector_t<Number>& normal, const Number& offset ) const {
	std::vector<Point<Number>> vertices = this->vertices();
	bool allVerticesContained = true;
	unsigned outsideVertexCnt = 0;
	for(const auto& vertex : vertices) {
		if(vertex.rawCoordinates().dot(normal) > offset){
			allVerticesContained = false;
			outsideVertexCnt++;
		}
	}
	if(allVerticesContained) {
		return std::make_pair(true, *this);
	}

	if(outsideVertexCnt == vertices.size_()) {
		return std::make_pair(false, Empty());
	}

	return std::make_pair(true, this->intersectHalfspace(Halfspace<Number>(normal,offset)));
}

template<typename Number, typename Converter>
std::pair<bool, BoxT<Number,Converter>> BoxT<Number,Converter>::satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {
	if(_mat.rows() == 0) {
		return std::make_pair(true, *this);
	}
	assert(this->dimension() == unsigned(_mat.cols()));
	matrix_t<Number> constraints = matrix_t<Number>::Zero(2*this->dimension()+_mat.rows(), this->dimension());
	vector_t<Number> constants = vector_t<Number>::Zero(2*this->dimension()+_vec.rows());
	for(unsigned d = 0; d < this->dimension(); ++d) {
		constraints(2*d, d) = 1;
		constraints(2*d+1, d) = -1;
		constants(2*d) = mLimits.second.at(d);
		constants(2*d+1) = -mLimits.first.at(d);
	}
	//std::cout << "So far box constraints:" << std::endl << constraints << std::endl << constants << std::endl << "MAT: " << std::endl << _mat << std::endl << "VEC: " << std::endl << _vec << std::endl;

	//std::cout << "Block start at " << 2*this->dimension() << ", 0" << " \t size " << _mat.rows() << "," << _mat.cols() << std::endl;
	//std::cout << "Block start at " << 2*this->dimension() << ", 0" << " \t size " << _vec.rows() << ",1" << std::endl;
	constraints.block(2*this->dimension(),0,_mat.rows(), _mat.cols()) = _mat;
	constants.block(2*this->dimension(),0, _vec.rows(),1) = _vec;
	Optimizer<Number> opt;
	opt.setMatrix(constraints);
	opt.setVector(constants);

	if(!opt.checkConsistency()){
		return std::make_pair(false, Empty());
	}

	std::vector<Point<Number>> vertices = this->vertices();
	bool allVerticesContained = true;
	unsigned outsideVertexCnt = 0;
	for(const auto& vertex : vertices) {
		if(!opt.checkPoint(vertex)) {
			allVerticesContained = false;
			outsideVertexCnt++;
		}
	}

	//std::cout << __func__ << ": #vertices outside: " << outsideVertexCnt << "/" << vertices.size() << std::endl;

	if(allVerticesContained) {
		return std::make_pair(true, *this);
	}

	// cannot be empty, otherwise all points would have violated the planes.
	assert(!this->intersectHalfspaces(_mat,_vec).empty());
	return std::make_pair(true, this->intersectHalfspaces(_mat, _vec));
}

template<typename Number, typename Converter>
BoxT<Number,Converter> BoxT<Number,Converter>::linearTransformation( const matrix_t<Number> &A, const vector_t<Number> &b ) const {
	// create both limit matrices
	// std::cout << __func__ << ": Matrix" <<  std::endl << A << std::endl << "Vector" << std::endl << b << std::endl;
	matrix_t<Number> ax(A);
	matrix_t<Number> bx(A);
	Point<Number> min;
	Point<Number> max;

	for (int k = 0; k < A.rows(); ++k) {
		for (int j = 0; j < A.cols(); ++j) {
			Number a = mLimits.first.at(j)*A(k,j);
			Number b = mLimits.second.at(j)*A(k,j);
			//std::cout << "Obtained values " << a << " and " << b << " for dimension " << k << " and colum " << j << std::endl;
				if(a > b){
					max[k] += a;
					min[k] += b;
				} else {
					max[k] += b;
					min[k] += a;
				}

			//std::cout << "After addition max["<<k<<"] = " << max.at(k) << " and min["<<k<<"] = " << min.at(k) << std::endl;
		}
	}
	min += b;
	max += b;

	return BoxT<Number,Converter>( std::make_pair(min, max) );
}

template<typename Number, typename Converter>
BoxT<Number,Converter> BoxT<Number,Converter>::minkowskiSum( const BoxT<Number,Converter> &rhs ) const {
	assert( dimension() == rhs.dimension() );
	return BoxT<Number,Converter>(std::make_pair(mLimits.first + rhs.min(), mLimits.second + rhs.max()));
}

template<typename Number, typename Converter>
BoxT<Number,Converter> BoxT<Number,Converter>::minkowskiDecomposition( const BoxT<Number,Converter>& rhs ) const {
	assert( dimension() == rhs.dimension() );
	// assert( std::mismatch(this->boundaries().begin(), this->boundaries.end(), rhs.boundaries().begin(), rhs.boundaries.end(), [&](a,b) -> bool {return a.diameter() >= b.diameter()}  ) ); // TODO: wait for c++14 support
	// assert( (BoxT<Number,Converter>(std::make_pair(mLimits.first - rhs.min(), mLimits.second - rhs.max())).minkowskiSum(rhs) == *this) );
	return BoxT<Number,Converter>(std::make_pair(mLimits.first - rhs.min(), mLimits.second - rhs.max()));
}

template<typename Number, typename Converter>
BoxT<Number,Converter> BoxT<Number,Converter>::intersect( const BoxT<Number,Converter> &rhs ) const {
	std::size_t dim = rhs.dimension() < this->dimension() ? rhs.dimension() : this->dimension();
	std::pair<Point<Number>, Point<Number>> limits(std::make_pair(Point<Number>(vector_t<Number>::Zero(dim)), Point<Number>(vector_t<Number>::Zero(dim))));
	std::pair<Point<Number>, Point<Number>> rhsLimits = rhs.limits();
	for ( std::size_t i = 0; i < dim; ++i ) {
		limits.first[i] = mLimits.first.at(i) > rhsLimits.first.at(i) ? mLimits.first.at(i) : rhsLimits.first.at(i);
		limits.second[i] = mLimits.second.at(i) < rhsLimits.second.at(i) ? mLimits.second.at(i) : rhsLimits.second.at(i);
	}
	return BoxT<Number,Converter>(limits);
}

template<typename Number, typename Converter>
BoxT<Number,Converter> BoxT<Number,Converter>::intersectHalfspace( const Halfspace<Number>& rhs ) const {
	if(!this->empty()) {
		auto intermediate = Converter::toHPolytope(*this);
		intermediate.insert(rhs);
		return Converter::toBox(intermediate);
	}
	return Empty(this->dimension());
}

template<typename Number, typename Converter>
BoxT<Number,Converter> BoxT<Number,Converter>::intersectHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {
	if(!this->empty()) {
		auto intermediate = Converter::toHPolytope(*this);
		intermediate = intermediate.intersectHalfspaces(_mat, _vec);
		//std::cout << "Intermediate: " << intermediate << std::endl;
		return Converter::toBox(intermediate);
	}
	return Empty(this->dimension());
}

template<typename Number, typename Converter>
bool BoxT<Number,Converter>::contains( const Point<Number> &point ) const {
	if ( this->dimension() > point.dimension() ) {
		return false;
	}

	return (point >= mLimits.first && point <= mLimits.second );
}

template<typename Number, typename Converter>
bool BoxT<Number,Converter>::contains( const BoxT<Number,Converter> &box ) const {
	if ( this->dimension() != box.dimension() ) {
		return false;
	}

	return (box.min() >= mLimits.first && box.max() <= mLimits.second );
}

template<typename Number, typename Converter>
BoxT<Number,Converter> BoxT<Number,Converter>::unite( const BoxT<Number,Converter> &rhs ) const {
	assert( dimension() == rhs.dimension() );
	std::size_t dim = this->dimension();

	std::pair<Point<Number>, Point<Number>> limits(std::make_pair(Point<Number>(vector_t<Number>::Zero(dim)), Point<Number>(vector_t<Number>::Zero(dim))));
	std::pair<Point<Number>, Point<Number>> rhsLimits = rhs.limits();
	for ( std::size_t i = 0; i < dim; ++i ) {
		limits.first[i] = mLimits.first.at(i) < rhsLimits.first.at(i) ? mLimits.first.at(i) : rhsLimits.first.at(i);
		limits.second[i] = mLimits.second.at(i) > rhsLimits.second.at(i) ? mLimits.second.at(i) : rhsLimits.second.at(i);
	}
	return BoxT<Number,Converter>(limits);
}

template<typename Number, typename Converter>
void BoxT<Number,Converter>::clear() {
	*this = BoxT<Number,Converter>::Empty(0);
}

template<typename Number, typename Converter>
void BoxT<Number,Converter>::print() const {
	std::cout << *this << std::endl;
}

}  // namespace hypro
