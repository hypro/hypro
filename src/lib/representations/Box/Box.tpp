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

	template<typename Number>
	Box<Number>::Box( const std::vector<carl::Interval<Number>>& _intervals )
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

	template<typename Number>
	Box<Number>::Box( const matrix_t<Number>& _matrix, const vector_t<Number>& _constants )
			: Box( VPolytope<Number>( _matrix, _constants ).vertices() )
	{}

template <typename Number>
Box<Number>::Box( const std::set<Point<Number>> &_points ) {
	if ( !_points.empty() ) {
		vector_t<Number> lower = _points.begin()->rawCoordinates();
		vector_t<Number> upper = _points.begin()->rawCoordinates();
		for(const auto& point : _points) {
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

template <typename Number>
Box<Number>::Box( const std::vector<Point<Number>> &_points ) {
	if ( !_points.empty() ) {
		vector_t<Number> lower = _points.begin()->rawCoordinates();
		vector_t<Number> upper = _points.begin()->rawCoordinates();
		for(const auto& point : _points) {
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

template <typename Number>
Box<Number>::Box( const std::set<Vertex<Number>> &_vertices ) {
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

template <typename Number>
Box<Number>::Box( const std::vector<Vertex<Number>> &_vertices ) {
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

template<typename Number>
std::vector<carl::Interval<Number>> Box<Number>::boundaries() const {
	std::vector<carl::Interval<Number>> result;
	result.reserve(this->dimension());

	for(std::size_t d = 0; d < this->dimension(); ++d) {
		result.push_back(carl::Interval<Number>(mLimits.first.at(d), mLimits.second.at(d)));
	}

	return result;
}

template<typename Number>
std::vector<Hyperplane<Number>> Box<Number>::constraints() const {
	std::vector<Hyperplane<Number>> res;
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

template<typename Number>
void Box<Number>::insert( const std::vector<carl::Interval<Number>>& boundaries ) {
	for(const auto& interval : boundaries) {
		mLimits.first.extend(interval.lower());
		mLimits.second.extend(interval.upper());
	}
}

template <typename Number>
carl::Interval<Number> Box<Number>::interval( std::size_t d ) const {
	if ( d > mLimits.first.dimension() ) return carl::Interval<Number>::emptyInterval();
	return carl::Interval<Number>(mLimits.first.at(d), mLimits.second.at(d));
}

template <typename Number>
Number Box<Number>::supremum() const {
	Number max = 0;
	for ( auto &point : this->vertices() ) {
		Number inftyNorm = hypro::Point<Number>::inftyNorm( point );
		max = max > inftyNorm ? max : inftyNorm;
	}
	return max;
}

template <typename Number>
std::vector<Point<Number>> Box<Number>::vertices() const {
	std::vector<Point<Number>> result;
	std::size_t limit = pow( 2, mLimits.first.dimension() );

	for ( std::size_t bitCount = 0; bitCount < limit; ++bitCount ) {
		vector_t<Number> coord = vector_t<Number>( dimension() );
		for ( std::size_t dimension = 0; dimension < this->dimension(); ++dimension ) {
			std::size_t pos = ( 1 << dimension );
			if ( bitCount & pos )
				coord( dimension ) = mLimits.second.at(dimension);
			else
				coord( dimension ) = mLimits.first.at(dimension);
		}
		result.push_back( Point<Number>( coord ) );
	}
	return result;
}

template <typename Number>
Box<Number> Box<Number>::linearTransformation( const matrix_t<Number> &A, const vector_t<Number> &b ) const {
	// create both limit matrices
	matrix_t<Number> ax(A);
	matrix_t<Number> bx(A);
	Point<Number> min;
	Point<Number> max;

	std::cout << "Matrix: " << A << std::endl;

	for (int k = 0; k < A.rows(); ++k) {
		for (int j = 0; j < A.cols(); ++j) {
			Number a = mLimits.first.at(k)*A(k,j);
			Number b = mLimits.second.at(k)*A(k,j);
			std::cout << "Obtained values " << a << " and " << b << " for dimension " << k << " and colum " << j << std::endl;

				if(a > b){
					max[k] += a;
					min[k] += b;
				} else {
					max[k] += b;
					min[k] += a;
				}

			std::cout << "After addition max["<<k<<"] = " << max.at(k) << " and min["<<k<<"] = " << min.at(k) << std::endl;
		}
	}

	return Box<Number>( std::make_pair(min, max) );
}

template <typename Number>
Box<Number> Box<Number>::minkowskiSum( const Box<Number> &rhs ) const {
	assert( dimension() == rhs.dimension() );

	return Box<Number>(std::make_pair(mLimits.first + rhs.min(), mLimits.second + rhs.max()));
}

template <typename Number>
Box<Number> Box<Number>::intersect( const Box<Number> &rhs ) const {
	std::size_t dim = rhs.dimension() < this->dimension() ? rhs.dimension() : this->dimension();
	std::pair<Point<Number>, Point<Number>> limits(std::make_pair(Point<Number>(vector_t<Number>::Zero(dim)), Point<Number>(vector_t<Number>::Zero(dim))));
	std::pair<Point<Number>, Point<Number>> rhsLimits = rhs.limits();
	for ( std::size_t i = 0; i < dim; ++i ) {
		limits.first[i] = mLimits.first.at(i) > rhsLimits.first.at(i) ? mLimits.first.at(i) : rhsLimits.first.at(i);
		limits.second[i] = mLimits.second.at(i) < rhsLimits.second.at(i) ? mLimits.second.at(i) : rhsLimits.second.at(i);
	}
	return Box<Number>(limits);
}

template <typename Number>
Box<Number> Box<Number>::intersectHyperplane( const Hyperplane<Number>& rhs ) const {
	if(!this->empty()) {
		HPolytope<Number> intermediate(this->constraints());
		intermediate.insert(rhs);
		return Box<Number>(intermediate.vertices());
	}
	return Empty(this->dimension());
}

template <typename Number>
bool Box<Number>::contains( const Point<Number> &point ) const {
	if ( this->dimension() > point.dimension() ) return false;

	return (point >= mLimits.first && point <= mLimits.second );
}

template <typename Number>
bool Box<Number>::contains( const Box<Number> &box ) const {
	if ( this->dimension() != box.dimension() ) return false;

	return (box.min() >= mLimits.first && box.max() <= mLimits.second );
}

template <typename Number>
Box<Number> Box<Number>::unite( const Box<Number> &rhs ) const {
	assert( dimension() == rhs.dimension() );
	std::size_t dim = this->dimension();

	std::pair<Point<Number>, Point<Number>> limits(std::make_pair(Point<Number>(vector_t<Number>::Zero(dim)), Point<Number>(vector_t<Number>::Zero(dim))));
	std::pair<Point<Number>, Point<Number>> rhsLimits = rhs.limits();
	for ( std::size_t i = 0; i < dim; ++i ) {
		limits.first[i] = mLimits.first.at(i) < rhsLimits.first.at(i) ? mLimits.first.at(i) : rhsLimits.first.at(i);
		limits.second[i] = mLimits.second.at(i) > rhsLimits.second.at(i) ? mLimits.second.at(i) : rhsLimits.second.at(i);
	}
	return Box<Number>(limits);
}

template<typename Number>
void Box<Number>::clear() {
	*this = Box<Number>::Empty(0);
}

template <typename Number>
void Box<Number>::print() const {
	std::cout << *this << std::endl;
}

}  // namespace
