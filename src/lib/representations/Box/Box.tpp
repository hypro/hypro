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

template <typename Number>
Box<Number>::Box( const std::set<Point<Number>> &_points ) {
	if ( _points.size() > 0 ) {
		std::size_t dim = _points.begin()->dimension();
		for ( std::size_t d = 0; d < dim; ++d ) {
			mBoundaries.push_back( carl::Interval<Number>( _points.begin()->at( d ) ) );
		}
		if ( _points.size() > 1 ) {
			auto pointIt = _points.begin();
			++pointIt;
			for ( ; pointIt != _points.end(); ++pointIt ) {
				for ( std::size_t d = 0; d < pointIt->dimension(); ++d ) {
					if ( mBoundaries[d].lower() > pointIt->at( d ) ) mBoundaries[d].setLower( pointIt->at( d ) );

					if ( mBoundaries[d].upper() < pointIt->at( d ) ) mBoundaries[d].setUpper( pointIt->at( d ) );
				}
			}
		}
	}
}

template <typename Number>
Box<Number>::Box( const std::vector<Point<Number>> &_points ) {
	if ( _points.size() > 0 ) {
		std::size_t dim = _points.begin()->dimension();
		for ( std::size_t d = 0; d < dim; ++d ) {
			mBoundaries.push_back( carl::Interval<Number>( _points.begin()->at( d ) ) );
		}
		if ( _points.size() > 1 ) {
			auto pointIt = _points.begin();
			++pointIt;
			for ( ; pointIt != _points.end(); ++pointIt ) {
				for ( std::size_t d = 0; d < pointIt->dimension(); ++d ) {
					if ( mBoundaries[d].lower() > pointIt->at( d ) ) mBoundaries[d].setLower( pointIt->at( d ) );

					if ( mBoundaries[d].upper() < pointIt->at( d ) ) mBoundaries[d].setUpper( pointIt->at( d ) );
				}
			}
		}
	}
}

template <typename Number>
Box<Number>::Box( const std::set<Vertex<Number>> &_vertices ) {
	if ( _vertices.size() > 0 ) {
		std::size_t dim = _vertices.begin()->dimension();
		for ( std::size_t d = 0; d < dim; ++d ) {
			mBoundaries.push_back( carl::Interval<Number>( _vertices.begin()->at( d ) ) );
		}
		if ( _vertices.size() > 1 ) {
			auto pointIt = _vertices.begin();
			++pointIt;
			for ( ; pointIt != _vertices.end(); ++pointIt ) {
				for ( std::size_t d = 0; d < pointIt->dimension(); ++d ) {
					if ( mBoundaries[d].lower() > pointIt->at( d ) ) mBoundaries[d].setLower( pointIt->at( d ) );

					if ( mBoundaries[d].upper() < pointIt->at( d ) ) mBoundaries[d].setUpper( pointIt->at( d ) );
				}
			}
		}
	}
}

template <typename Number>
Box<Number>::Box( const std::vector<Vertex<Number>> &_vertices ) {
	if ( _vertices.size() > 0 ) {
		std::size_t dim = _vertices.begin()->dimension();
		for ( std::size_t d = 0; d < dim; ++d ) {
			mBoundaries.push_back( carl::Interval<Number>( _vertices.begin()->at( d ) ) );
		}
		if ( _vertices.size() > 1 ) {
			auto pointIt = _vertices.begin();
			++pointIt;
			for ( ; pointIt != _vertices.end(); ++pointIt ) {
				for ( std::size_t d = 0; d < pointIt->dimension(); ++d ) {
					if ( mBoundaries[d].lower() > pointIt->at( d ) ) mBoundaries[d].setLower( pointIt->at( d ) );

					if ( mBoundaries[d].upper() < pointIt->at( d ) ) mBoundaries[d].setUpper( pointIt->at( d ) );
				}
			}
		}
	}
}

template<typename Number>
std::vector<Hyperplane<Number>> Box<Number>::constraints() const {
	std::vector<Hyperplane<Number>> res;
	if(!mBoundaries.empty()) {
		std::size_t dim = this->dimension();
		res.reserve(2*dim);
		for( std::size_t d = 0; d < dim; ++d) {
			vector_t<Number> low = vector_t<Number>::Zero(dim);
			low(d) = -1;
			vector_t<Number> up = vector_t<Number>::Zero(dim);
			up(d) = 1;
			Number lOff = -mBoundaries.at(d).lower();
			Number uOff = mBoundaries.at(d).upper();
			res.emplace_back(low, lOff);
			res.emplace_back(up, uOff);
		}
	}
	return res;
}

template <typename Number>
carl::Interval<Number> Box<Number>::interval( std::size_t d ) const {
	if ( d > mBoundaries.size() ) return carl::Interval<Number>::emptyInterval();

	return mBoundaries.at( d );
}

template <typename Number>
carl::Interval<Number> &Box<Number>::rInterval( std::size_t d ) {
	if ( d > mBoundaries.size() ) return carl::Interval<Number>::emptyInterval();

	return mBoundaries.at( d );
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
	std::size_t limit = pow( 2, mBoundaries.size() );

	for ( std::size_t bitCount = 0; bitCount < limit; ++bitCount ) {
		vector_t<Number> coord = vector_t<Number>( dimension() );
		for ( std::size_t dimension = 0; dimension < this->dimension(); ++dimension ) {
			std::size_t pos = ( 1 << dimension );
			if ( bitCount & pos )
				coord( dimension ) = mBoundaries[dimension].upper();
			else
				coord( dimension ) = mBoundaries[dimension].lower();
		}
		result.push_back( Point<Number>( coord ) );
	}
	return result;
}

template <typename Number>
Box<Number> Box<Number>::linearTransformation( const matrix_t<Number> &A, const vector_t<Number> &b ) const {
	std::vector<Point<Number>> corners = this->vertices();
	std::set<Point<Number>> transformedCorners;
	for ( auto &point : corners ) {
		transformedCorners.insert( Point<Number>( A * point.rawCoordinates() + b ) );
	}

	return Box<Number>( transformedCorners );
}

template <typename Number>
Box<Number> Box<Number>::minkowskiSum( const Box<Number> &rhs ) const {
	assert( dimension() == rhs.dimension() );
	Box<Number> result;
	for ( std::size_t i = 0; i < dimension(); ++i ) {
		result.insert( mBoundaries[i].add( rhs[i] ) );
	}
	return result;
}

template <typename Number>
Box<Number> Box<Number>::intersect( const Box<Number> &rhs ) const {
	Box<Number> result;
	std::size_t dim = rhs.dimension() < this->dimension() ? rhs.dimension() : this->dimension();
	for ( std::size_t i = 0; i < dim; ++i ) {
		carl::Interval<Number> res = mBoundaries[i].intersect( rhs[i] );
		result.insert( res );
	}
	return result;
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

	for ( std::size_t i = 0; i < dimension(); ++i ) {
		if ( !mBoundaries[i].contains( point.at( i ) ) ) return false;
	}
	return true;
}

template <typename Number>
bool Box<Number>::contains( const Box<Number> &box ) const {
	if ( this->dimension() != box.dimension() ) return false;

	for ( std::size_t pos = 0; pos < mBoundaries.size(); ++pos ) {
		std::cout << "TEst Contains: " << mBoundaries.at( pos ) << " contains " << box.at( pos ) << ": "
				  << mBoundaries.at( pos ).contains( box.at( pos ) ) << std::endl;
		if ( !mBoundaries.at( pos ).contains( box.at( pos ) ) ) return false;
	}
	return true;
}

template <typename Number>
Box<Number> Box<Number>::unite( const Box<Number> &rhs ) const {
	assert( dimension() == rhs.dimension() );
	Box<Number> result;
	for ( std::size_t i = 0; i < this->dimension(); ++i ) {
		Number lowerMin = mBoundaries[i].lower() < rhs.at( i ).lower() ? mBoundaries[i].lower() : rhs.at( i ).lower();
		Number upperMax = mBoundaries[i].upper() > rhs.at( i ).upper() ? mBoundaries[i].upper() : rhs.at( i ).upper();
		carl::BoundType lowerType =
			  carl::getWeakestBoundType( mBoundaries[i].lowerBoundType(), rhs.at( i ).lowerBoundType() );
		carl::BoundType upperType =
			  carl::getWeakestBoundType( mBoundaries[i].upperBoundType(), rhs.at( i ).upperBoundType() );
		result.insert( carl::Interval<Number>( lowerMin, lowerType, upperMax, upperType ) );
	}
	return result;
}

template <typename Number>
void Box<Number>::clear() {
	mBoundaries.erase( mBoundaries.begin(), mBoundaries.end() );
}

template <typename Number>
void Box<Number>::print() const {
	std::cout << *this << std::endl;
}

}  // namespace
