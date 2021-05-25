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

template <typename Number, typename Converter, class Setting>
BoxT<Number, Converter, Setting>::BoxT( const matrix_t<Number>& _constraints, const vector_t<Number>& _constants ) {
	TRACE( "hypro.representations", "matrix: " << _constraints << ", vector: " << _constants );

	assert( _constraints.rows() == _constants.rows() );
	if ( _constraints.rows() == 0 ) {
		mEmptyState = SETSTATE::EMPTY;
		assert( this->empty() );
		assert( this->dimension() == 0 );
		return;
	}

	// if possible and allowed by settings, detect whether the constraints represent a box.
	bool boxDefined = false;
	if ( !boxDefined && Setting::DETECT_BOX ) {
		auto boolIntervalsTuple = isBox( _constraints, _constants );
		TRACE( "hypro.representations", "Is box, use interval constructor." );
		if ( std::get<0>( boolIntervalsTuple ) ) {
			*this = BoxT<Number, Converter, Setting>( std::get<1>( boolIntervalsTuple ) );
			boxDefined = true;
		}
	}

	if ( !boxDefined ) {
		if ( Setting::HYPRO_BOX_AVOID_LINEAR_OPTIMIZATION == true ) {
			// calculate all possible Halfspace intersections -> TODO: dPermutation can
			// be improved.
			Permutator permutator = Permutator( _constraints.rows(), _constraints.cols() );
			matrix_t<Number> intersection = matrix_t<Number>( _constraints.cols(), _constraints.cols() );
			vector_t<Number> intersectionConstants = vector_t<Number>( _constraints.cols() );
			std::set<vector_t<Number>> possibleVertices;
			std::vector<std::size_t> permutation;
			while ( !permutator.end() ) {
				permutation = permutator();
				unsigned rowCount = 0;
				// std::cout << "Intersect :" << std::endl;
				for ( const auto& rowIndex : permutation ) {
					// std::cout << _constraints.row(rowIndex) << " <= " <<
					// _constants(rowIndex) << std::endl;
					assert( rowCount < _constraints.cols() );
					intersection.row( rowCount ) = _constraints.row( rowIndex );
					intersectionConstants( rowCount ) = _constants( rowIndex );
					++rowCount;
				}
				// check if rank is full
				Eigen::FullPivLU<matrix_t<Number>> luDecomposition = intersection.fullPivLu();
				if ( luDecomposition.rank() == intersection.cols() ) {
					vector_t<Number> vertex = luDecomposition.solve( intersectionConstants );
					assert( vertex.rows() == _constraints.cols() );
					possibleVertices.emplace( std::move( vertex ) );
					//std::cout<< "Vertex computed: " << convert<Number,double>(vertex).transpose() << std::endl;
				}
			}
			assert( !possibleVertices.empty() );

			// check if vertices are true vertices (i.e. they fulfill all constraints)
			for ( auto vertex = possibleVertices.begin(); vertex != possibleVertices.end(); ) {
				// std::cout  << "Refinement: Consider vertex : " << convert<Number,double>(*vertex).transpose() << std::endl;
				// possibleVertices.size() << std::endl;
				bool deleted = false;
				for ( unsigned rowIndex = 0; rowIndex < _constraints.rows(); ++rowIndex ) {
					Number res = vertex->dot( _constraints.row( rowIndex ) );
					if ( res > _constants( rowIndex ) ) {
						vertex = possibleVertices.erase( vertex );
						deleted = true;
						// std::cout << "Deleted because of row " << convert<Number,double>(vector_t<Number>(_constraints.row(rowIndex))) << std::endl;
						// std::cout << "Res was " << res << " and the constant is " << _constants(rowIndex) << std::endl;
						break;
					}
				}
				if ( !deleted ) {
					++vertex;
				}
			}
			// std::cout<<__func__ << " : " <<__LINE__ <<std::endl;
			// finish initialization
			if ( possibleVertices.empty() ) {
				*this = BoxT<Number, Converter, Setting>::Empty();
				return;
			} else {
				vector_t<Number> min = *possibleVertices.begin();
				vector_t<Number> max = *possibleVertices.begin();
				for ( const auto& point : possibleVertices ) {
					for ( unsigned d = 0; d < point.rows(); ++d ) {
						if ( min( d ) > point( d ) ) {
							min( d ) = point( d );
						}
						if ( max( d ) < point( d ) ) {
							max( d ) = point( d );
						}
					}
				}
				*this = BoxT<Number, Converter, Setting>( std::make_pair( Point<Number>( min ), Point<Number>( max ) ) );
				boxDefined = true;
			}
		} else {
			TRACE( "hypro.representations", "Use linear optimizer." );
			// convert box to a set of constraints, add other halfspaces and evaluate in box main directions to get new intervals.
			std::vector<vector_t<Number>> tpl = computeTemplate<Number>( _constraints.cols(), 4 );

			// evaluate in box directions.
			Optimizer<Number> opt( _constraints, _constants );
			std::vector<EvaluationResult<Number>> results;
			for(vector_t<Number> const& direction : tpl ) {
				results.emplace_back(opt.evaluate(direction, false));
				if ( results.back().errorCode == SOLUTION::INFEAS ) {
					opt.cleanContexts();
					*this = BoxT<Number, Converter, Setting>::Empty();
					return;
				}
			}

			opt.cleanContexts();
			assert( Eigen::Index( results.size() ) == Eigen::Index( tpl.size() ) );

			// re-construct box from results.
			mLimits = std::vector<carl::Interval<Number>>( _constraints.cols(), carl::Interval<Number>( 0 ) );
			std::vector<std::pair<bool, bool>> boundsSet = std::vector<std::pair<bool, bool>>( _constraints.cols(), std::make_pair( false, false ) );
			for ( Eigen::Index rowIndex = 0; rowIndex < Eigen::Index( tpl.size() ); ++rowIndex ) {
				for ( Eigen::Index colIndex = 0; colIndex < _constraints.cols(); ++colIndex ) {
					if ( tpl[rowIndex]( colIndex ) > 0 ) {
						// each bound only gets set once due to the template.
						assert( !boundsSet[colIndex].second );
						TRACE( "hypro.representations", "Add upper bound " << results[rowIndex].supportValue );
						if ( boundsSet[colIndex].first ) {
							mLimits[colIndex].setUpper( results[rowIndex].supportValue );
						} else {
							// set to point value, if lower bound has not been set yet.
							mLimits[colIndex].set( results[rowIndex].supportValue, results[rowIndex].supportValue );
						}
						boundsSet[colIndex].second = true;
						TRACE( "hypro.representations", "Result: " << mLimits[colIndex] );
					} else if ( tpl[rowIndex]( colIndex ) < 0 ) {
						// each bound only gets set once due to the template.
						assert( !boundsSet[colIndex].first );
						TRACE( "hypro.representations", "Add lower bound " << -results[rowIndex].supportValue );
						if ( boundsSet[colIndex].second ) {
							mLimits[colIndex].setLower( -results[rowIndex].supportValue );
						} else {
							// set to point value, if upper bound has not been set yet.
							mLimits[colIndex].set( -results[rowIndex].supportValue, -results[rowIndex].supportValue );
						}
						boundsSet[colIndex].first = true;
						TRACE( "hypro.representations", "Result: " << mLimits[colIndex] );
					}
				}
				mEmptyState = SETSTATE::NONEMPTY;
				boxDefined = true;
			}
		}

		assert( boxDefined );
		reduceNumberRepresentation();
	}
}

template <typename Number, typename Converter, class Setting>
BoxT<Number, Converter, Setting>::BoxT( const std::set<Point<Number>>& _points ) {
	if ( !_points.empty() ) {
		for ( std::size_t d = 0; d < _points.begin()->dimension(); ++d ) {
			Number min = _points.begin()->rawCoordinates()( d );
			Number max = _points.begin()->rawCoordinates()( d );
			for ( const auto& point : _points ) {
				if ( point[d] < min ) {
					min = point[d];
				}
				if ( point[d] > max ) {
					max = point[d];
				}
			}
			mLimits.emplace_back( min, max );
		}
		mEmptyState = SETSTATE::NONEMPTY;
	} else {
		mEmptyState = SETSTATE::EMPTY;
	}
	reduceNumberRepresentation();
}

template <typename Number, typename Converter, class Setting>
BoxT<Number, Converter, Setting>::BoxT( const std::vector<Point<Number>>& _points ) {
	if ( !_points.empty() ) {
		for ( std::size_t d = 0; d < _points.begin()->dimension(); ++d ) {
			Number min = _points.begin()->rawCoordinates()( d );
			Number max = _points.begin()->rawCoordinates()( d );
			for ( const auto& point : _points ) {
				if ( point[d] < min ) {
					min = point[d];
				}
				if ( point[d] > max ) {
					max = point[d];
				}
			}
			mLimits.emplace_back( min, max );
		}
		mEmptyState = SETSTATE::NONEMPTY;
	} else {
		mEmptyState = SETSTATE::EMPTY;
	}
	reduceNumberRepresentation();
}

template <typename Number, typename Converter, class Setting>
matrix_t<Number> BoxT<Number, Converter, Setting>::matrix() const {
	matrix_t<Number> res = matrix_t<Number>::Zero( 2 * this->dimension(), this->dimension() );
	for ( unsigned i = 0; i < this->dimension(); ++i ) {
		res( 2 * i, i ) = 1;
		res( 2 * i + 1, i ) = -1;
	}
	return res;
}

template <typename Number, typename Converter, class Setting>
vector_t<Number> BoxT<Number, Converter, Setting>::vector() const {
	vector_t<Number> res = vector_t<Number>::Zero( 2 * this->dimension() );
	for ( unsigned i = 0; i < this->dimension(); ++i ) {
		res( 2 * i ) = mLimits[i].upper();
		res( 2 * i + 1 ) = -mLimits[i].lower();
	}
	return res;
}

template <typename Number, typename Converter, class Setting>
std::vector<Halfspace<Number>> BoxT<Number, Converter, Setting>::constraints() const {
	std::vector<Halfspace<Number>> res;
	std::size_t dim = this->dimension();
	if ( !this->empty() && dim != 0 ) {
		matrix_t<Number> m = this->matrix();
		vector_t<Number> v = this->vector();
		res.reserve( 2 * dim );
		for ( std::size_t d = 0; d < dim; ++d ) {
			res.emplace_back( m.row( 2 * d ), v( 2 * d ) );
			res.emplace_back( m.row( 2 * d + 1 ), v( 2 * d + 1 ) );
		}
	}
	return res;
}

template <typename Number, typename Converter, class Setting>
Number BoxT<Number, Converter, Setting>::supremum() const {
	Number max = 0;
	for ( auto& point : this->vertices() ) {
		Number inftyNorm = Point<Number>::inftyNorm( point );
		max = max > inftyNorm ? max : inftyNorm;
	}
	return max;
}

template <typename Number, typename Converter, class Setting>
std::vector<Point<Number>> BoxT<Number, Converter, Setting>::vertices( const matrix_t<Number>& ) const {
	std::vector<Point<Number>> result;
	if ( this->empty() ) {
		return result;
	}
	std::size_t d = this->dimension();

	// compute 2^d: loop is faster than std::pow for integer-types
	// background: we need 2^d bits, i is the currently available number of bits
	std::size_t limit = 2;
	for ( std::size_t i = 1; i < d; ++i ) {
		limit = 2 * limit;
	}
	result.reserve( limit );

	for ( std::size_t bitCount = 0; bitCount < limit; ++bitCount ) {
		vector_t<Number> coord = vector_t<Number>( d );
		for ( std::size_t dimension = 0; dimension < d; ++dimension ) {
			std::size_t pos = ( 1 << dimension );
			if ( bitCount & pos ) {
				coord( dimension ) = mLimits[dimension].upper();
			} else {
				coord( dimension ) = mLimits[dimension].lower();
			}
		}
		result.emplace_back( coord );
	}
	return result;
}

template <typename Number, typename Converter, class Setting>
EvaluationResult<Number> BoxT<Number, Converter, Setting>::evaluate( const vector_t<Number>& _direction, bool ) const {
	DEBUG( "hypro.representations.box", "In evaluate. direction: " << std::endl
																   << _direction );
	assert( _direction.rows() == Eigen::Index( this->dimension() ) || this->empty() );
	if ( this->empty() ) {
		return EvaluationResult<Number>();	// defaults to infeasible, i.e. empty.
	}
	// find the point, which represents the maximum towards the direction - compare signs.
	vector_t<Number> furthestPoint = vector_t<Number>::Zero( this->dimension() );
	for ( Eigen::Index i = 0; i < furthestPoint.rows(); ++i ) {
		if ( _direction( i ) >= 0 ) {
			//Unboundedness check
			if ( mLimits[i].upperBoundType() == carl::BoundType::INFTY ) {
				return EvaluationResult<Number>( 0, furthestPoint, SOLUTION::INFTY );
			}
			furthestPoint( i ) = mLimits[i].upper();
		} else {
			//Unboundedness check
			if ( mLimits[i].lowerBoundType() == carl::BoundType::INFTY ) {
				return EvaluationResult<Number>( 0, furthestPoint, SOLUTION::INFTY );
			}
			furthestPoint( i ) = mLimits[i].lower();
		}
	}
	return EvaluationResult<Number>( furthestPoint.dot( _direction ), furthestPoint, SOLUTION::FEAS );
}

template <typename Number, typename Converter, class Setting>
std::vector<EvaluationResult<Number>> BoxT<Number, Converter, Setting>::multiEvaluate( const matrix_t<Number>& _directions, bool useExact ) const {
	DEBUG( "hypro.representations.box", "In Box::multiEvaluate. directions: " << std::endl
																			  << _directions );
	std::vector<EvaluationResult<Number>> res;
	for ( Eigen::Index i = 0; i < _directions.rows(); ++i ) {
		res.emplace_back( this->evaluate( vector_t<Number>( _directions.row( i ).transpose() ), useExact ) );
	}
	return res;
}

template <typename Number, typename Converter, class Setting>
std::size_t BoxT<Number, Converter, Setting>::size() const {
	if ( this->empty() ) {
		return 0;
	}
	// TODO: What is this supposed to do???
	return 2;
}

template <typename Number, typename Converter, class Setting>
const BoxT<Number, Converter, Setting>& BoxT<Number, Converter, Setting>::reduceNumberRepresentation( unsigned limit ) {
	reduceIntervalsNumberRepresentation( mLimits, limit );

	return *this;
}

template <typename Number, typename Converter, typename Setting>
BoxT<Number, Converter, Setting> BoxT<Number, Converter, Setting>::makeSymmetric() const {
	if ( this->empty() ) {
		return *this;
	}
	std::vector<carl::Interval<Number>> newIntervals;
	for ( const auto& i : mLimits ) {
		// find the maximal bound (absolute value) to make box symmetric to the origin.
		Number lbabs = carl::abs( i.lower() );
		Number ubabs = carl::abs( i.upper() );
		Number bound = lbabs < ubabs ? ubabs : lbabs;
		// create symmetric interval
		newIntervals.emplace_back( -bound, bound );
	}
	return BoxT<Number, Converter, Setting>( newIntervals );
}

template <typename Number, typename Converter, class Setting>
std::pair<CONTAINMENT, BoxT<Number, Converter, Setting>> BoxT<Number, Converter, Setting>::satisfiesHalfspace( const Halfspace<Number>& rhs ) const {
	matrix_t<Number> constraints = matrix_t<Number>( 1, this->dimension() );
	constraints.row( 0 ) = rhs.normal();
	vector_t<Number> constants = vector_t<Number>( 1 );
	constants << rhs.offset();
	return this->satisfiesHalfspaces( constraints, constants );
}

template <typename Number, typename Converter, class Setting>
std::pair<CONTAINMENT, BoxT<Number, Converter, Setting>> BoxT<Number, Converter, Setting>::satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {
	if ( _mat.rows() == 0 ) {
		return std::make_pair( CONTAINMENT::FULL, *this );
	}

	if ( this->empty() ) {
		return std::make_pair( CONTAINMENT::NO, *this );
	}

	// std::cout << __func__ << " This: " << convert<Number,double>(*this) << std::endl;
	// std::cout << __func__ << ": input matrix: " << convert<Number,double>(_mat) << std::endl << "input vector: " << convert<Number,double>(_vec) << std::endl;
	// std::cout << __func__ << ": This->dimension() = " << this->dimension() << std::endl;
	assert( this->dimension() == unsigned( _mat.cols() ) );
	std::vector<unsigned> limitingPlanes;

	for ( unsigned rowIndex = 0; rowIndex < _mat.rows(); ++rowIndex ) {
		carl::Interval<Number> evaluatedBox = carl::Interval<Number>( 0 );
		for ( unsigned d = 0; d < _mat.cols(); ++d ) {
			evaluatedBox += mLimits[d] * Number( _mat( rowIndex, d ) );
		}

		//std::cout << __func__ << " Row: " << convert<Number,double>(_mat.row(rowIndex)) << std::endl;
		//std::cout << __func__ << " Evaluated box: " << evaluatedBox << std::endl;
		//std::cout << __func__ << " Distance: " << carl::convert<Number,double>(_vec(rowIndex)) << std::endl;

		if ( evaluatedBox.lower() > _vec( rowIndex ) ) {
			return std::make_pair( CONTAINMENT::NO, Empty() );
		}

		if ( evaluatedBox.upper() > _vec( rowIndex ) ) {
			limitingPlanes.push_back( rowIndex );
		}
	}

	// at this point the box cannot be empty.
	if ( limitingPlanes.empty() ) {
		return std::make_pair( CONTAINMENT::FULL, *this );
	}

	// at this point the box will be limited but not empty.
	matrix_t<Number> newPlanes = matrix_t<Number>( limitingPlanes.size(), _mat.cols() );
	vector_t<Number> newDistances = vector_t<Number>( limitingPlanes.size() );
	Eigen::Index rowPos = newPlanes.rows() - 1;
	while ( !limitingPlanes.empty() ) {
		assert( rowPos >= 0 );
		newPlanes.row( rowPos ) = _mat.row( limitingPlanes.back() );
		newDistances( rowPos ) = _vec( limitingPlanes.back() );
		--rowPos;
		limitingPlanes.pop_back();
	}
	assert( newPlanes.rows() == newDistances.rows() );
	auto tmp = this->intersectHalfspaces( newPlanes, newDistances );
	bool empty = tmp.empty();
	if ( empty ) {
		return std::make_pair( CONTAINMENT::NO, tmp );
	} else {
		return std::make_pair( CONTAINMENT::PARTIAL, tmp );
	}
}

template <typename Number, typename Converter, class Setting>
BoxT<Number, Converter, Setting> BoxT<Number, Converter, Setting>::projectOn( const std::vector<std::size_t>& dimensions ) const {
	if ( dimensions.empty() ) {
		return Empty();
	}
	std::vector<carl::Interval<Number>> newIntervals;
	for ( const auto d : dimensions ) {
		assert( d < this->dimension() );
		newIntervals.push_back( mLimits[d] );
	}
	return BoxT<Number, Converter, Setting>( newIntervals );
}

template <typename Number, typename Converter, class Setting>
BoxT<Number, Converter, Setting> BoxT<Number, Converter, Setting>::assignIntervals( const std::map<std::size_t, carl::Interval<Number>>& assignments ) const {
	std::vector<carl::Interval<Number>> newIntervals{ mLimits };
	for ( const auto& dimensionIntervalPair : assignments ) {
		assert( dimensionIntervalPair.first < newIntervals.size() );
		newIntervals[dimensionIntervalPair.first] = dimensionIntervalPair.second;
	}
	return BoxT<Number, Converter, Settings>{ newIntervals };
}

template <typename Number, typename Converter, class Setting>
BoxT<Number, Converter, Setting> BoxT<Number, Converter, Setting>::linearTransformation( const matrix_t<Number>& A ) const {
	if ( this->empty() ) {
		return *this;
	}

	//std::vector<carl::Interval<Number>> newIntervals = std::vector<carl::Interval<Number>>(this->dimension(), carl::Interval<Number>(Number(0)));
	//for(std::size_t i = 0; i < this->dimension(); ++i) {
	//	for(std::size_t j = 0; j < this->dimension(); ++j){
	//		newIntervals[i] =  newIntervals[i] + this->intervals()[i]*A(i,j);
	//	}
	//}
	//BoxT<Number,Converter,Setting> res(newIntervals);

	std::vector<carl::Interval<Number>> newIntervals = std::vector<carl::Interval<Number>>( this->dimension(), carl::Interval<Number>( Number( 0 ) ) );
	for ( int k = 0; k < A.rows(); ++k ) {
		for ( int j = 0; j < A.cols(); ++j ) {
			Number a = mLimits[j].lower() * A( k, j );
			Number b = mLimits[j].upper() * A( k, j );
			// std::cout << "Obtained values " << a << " and " << b << " for dimension " << k << " and colum " << j << std::endl;
			if ( a > b ) {
				newIntervals[k] = newIntervals[k] + carl::Interval<Number>( b, a );
			} else {
				newIntervals[k] = newIntervals[k] + carl::Interval<Number>( a, b );
			}
		}
	}

	BoxT<Number, Converter, Setting> res( newIntervals );
	res.reduceNumberRepresentation();

	//std::cout << "Res: " << res << std::endl;
	//std::cout << "min transformed: " << Point<Number>(A*this->min().rawCoordinates()) << std::endl;
	//std::cout << "max transformed: " << Point<Number>(A*this->max().rawCoordinates()) << std::endl;
	assert( res.contains( Point<Number>( A * this->min().rawCoordinates() ) ) );
	assert( res.contains( Point<Number>( A * this->max().rawCoordinates() ) ) );
#ifndef NDEBUG
	// only validate, if the dimension is small enough - computing all vertices in higher dimensions is not possible.
	if ( this->dimension() < 10 ) {
		std::vector<Point<Number>> vertices = this->vertices();
		Point<Number> manualMin = Point<Number>( A * ( vertices.begin()->rawCoordinates() ) );
		Point<Number> manualMax = Point<Number>( A * ( vertices.begin()->rawCoordinates() ) );
		for ( const auto& v : vertices ) {
			Point<Number> t = Point<Number>( A * v.rawCoordinates() );
			assert( res.contains( t ) );
			for ( std::size_t d = 0; d < this->dimension(); ++d ) {
				if ( manualMin.at( d ) > t.at( d ) ) {
					manualMin[d] = t[d];
				}
				if ( manualMax.at( d ) < t.at( d ) ) {
					manualMax[d] = t[d];
				}
			}
		}
	}

	//assert(manualMin == res.min());
	//assert(manualMax == res.max());
#endif
	return res;
}

template <typename Number, typename Converter, class Setting>
BoxT<Number, Converter, Setting> BoxT<Number, Converter, Setting>::affineTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const {
	if ( this->empty() ) {
		return *this;
	}
	//TRACE("hypro.representations.box","This: " << *this << ", A: " << A << "b: " << b);
	//std::cout << "Linear trafo ";
	std::vector<carl::Interval<Number>> newIntervals = std::vector<carl::Interval<Number>>( this->dimension() );
	for ( std::size_t i = 0; i < this->dimension(); ++i ) {
		newIntervals[i] = carl::Interval<Number>{ b( i ) };
		for ( std::size_t j = 0; j < this->dimension(); ++j ) {
			newIntervals[i] = newIntervals[i] + A( i, j ) * this->intervals()[j];
		}
	}
	return BoxT<Number, Converter, Setting>{ newIntervals };
}

template <typename Number, typename Converter, class Setting>
BoxT<Number, Converter, Setting> BoxT<Number, Converter, Setting>::minkowskiSum( const BoxT<Number, Converter, Setting>& rhs ) const {
	assert( dimension() == rhs.dimension() );
	std::vector<carl::Interval<Number>> newIntervals;
	for ( std::size_t d = 0; d < this->dimension(); ++d ) {
		newIntervals.emplace_back( mLimits[d] + rhs.interval( d ) );
	}
	return BoxT<Number, Converter, Setting>( newIntervals );
}

template <typename Number, typename Converter, class Setting>
BoxT<Number, Converter, Setting> BoxT<Number, Converter, Setting>::minkowskiDecomposition( const BoxT<Number, Converter, Setting>& rhs ) const {
	if ( rhs.empty() ) {
		return *this;
	}
	TRACE( "hypro.representations.box", "This: " << *this << ", Rhs: " << rhs );
	assert( dimension() == rhs.dimension() );
	std::vector<carl::Interval<Number>> newIntervals;
	for ( std::size_t d = 0; d < this->dimension(); ++d ) {
		newIntervals.emplace_back( mLimits[d].lower() - rhs.interval( d ).lower(), mLimits[d].upper() - rhs.interval( d ).upper() );
	}
	return BoxT<Number, Converter, Setting>( newIntervals );
}

template <typename Number, typename Converter, class Setting>
BoxT<Number, Converter, Setting> BoxT<Number, Converter, Setting>::intersect( const BoxT<Number, Converter, Setting>& rhs ) const {
	if ( this->empty() || rhs.empty() ) {
		return Empty();
	}
	std::vector<carl::Interval<Number>> newIntervals;
	std::size_t dim = this->dimension();
	std::size_t rdim = rhs.dimension();
	newIntervals.reserve( std::max( dim, rdim ) );
	for ( std::size_t d = 0; d < this->dimension(); ++d ) {
		// intersection if both agree on the dimension
		if ( d < rdim )
			newIntervals.emplace_back( set_intersection( mLimits[d], rhs.interval( d ) ) );
		else  // if this->dimension() > rdim use projection
			newIntervals.emplace_back( mLimits[d] );
	}
	// if the other box has a larger dimension use projection as well.
	if ( rdim > dim ) {
		for ( std::size_t d = dim; d < rdim; ++d ) {
			newIntervals.emplace_back( rhs.interval( d ) );
		}
	}
	return BoxT<Number, Converter, Setting>( newIntervals );
}

template <typename Number, typename Converter, class Setting>
BoxT<Number, Converter, Setting> BoxT<Number, Converter, Setting>::intersectHalfspace( const Halfspace<Number>& hspace ) const {
	//std::cout << __func__ << " of " << *this << " and " << hspace << std::endl;
	if ( !this->empty() ) {
		if ( Setting::USE_INTERVAL_ARITHMETIC ) {
			std::vector<carl::Interval<Number>> intervals = this->intervals();
			bool empty = icpIntersectHalfspace( intervals, hspace );
			if ( empty ) {
				return Empty();
			}
			return BoxT<Number, Converter, Setting>( intervals );
		} else {  // Do not use interval arithmetic.
			BoxT<Number, Converter, Setting> boxcopy( *this );
			// Preprocessing: If any two points opposite to each other are contained, the box stays the same - test limit points
			bool holdsMin = hspace.contains( boxcopy.min() );
			bool holdsMax = hspace.contains( boxcopy.max() );
			if ( holdsMin && holdsMax ) {
				//std::cout << __func__ << " Min and Max are below the halfspace." << std::endl;
				return *this;
			}

			// another special case: if the hspace normal is axis-aligned, i.e. it has only one non-zero entry, we simply can use interval-
			// style intersection.
			if ( hspace.normal().nonZeros() == 1 ) {
				// from previous checks we know that either the lowest or the highest point is not contained. If both are not
				// contained and the normal is axis-aligned, the set is empty.
				if ( !holdsMin && !holdsMax ) {
					return Empty();
				}

				// find the one, non-zero component
				unsigned nonZeroDim = 0;
				while ( hspace.normal()( nonZeroDim ) == 0 ) ++nonZeroDim;

				if ( hspace.normal()( nonZeroDim ) > 0 ) {
					boxcopy.rInterval( nonZeroDim ).setUpper( hspace.offset() / hspace.normal()( nonZeroDim ) );
				} else {
					boxcopy.rInterval( nonZeroDim ).setLower( hspace.offset() / hspace.normal()( nonZeroDim ) );
				}
				return boxcopy;
			}

			//std::cout << __func__ << " Min below: " << holdsMin << ", Max below: " << holdsMax << std::endl;
			std::size_t dim = this->dimension();

			// Phase 1: Find starting point (point outside) for phase 2 by depth-first search or use limit points, if applicable
			Point<Number> farestPointOutside = boxcopy.min();
			Point<Number> farestPointInside = boxcopy.min();
			std::size_t usedDimension = 0;
			// determine walk direction by using plane normal and variable order
			for ( ; usedDimension < dim; ++usedDimension ) {
				if ( hspace.normal()( usedDimension ) > 0 ) {
					if ( farestPointOutside.at( usedDimension ) != boxcopy.intervals()[usedDimension].upper() ) {
						farestPointOutside[usedDimension] = boxcopy.intervals()[usedDimension].upper();
					}
					if ( farestPointInside.at( usedDimension ) != boxcopy.intervals()[usedDimension].lower() ) {
						farestPointInside[usedDimension] = boxcopy.intervals()[usedDimension].lower();
					}
				} else if ( hspace.normal()( usedDimension ) < 0 ) {
					if ( farestPointOutside.at( usedDimension ) != boxcopy.intervals()[usedDimension].lower() ) {
						farestPointOutside[usedDimension] = boxcopy.intervals()[usedDimension].lower();
					}
					if ( farestPointInside.at( usedDimension ) != boxcopy.intervals()[usedDimension].upper() ) {
						farestPointInside[usedDimension] = boxcopy.intervals()[usedDimension].upper();
					}
				}
			}
			// farestPointOutside is the point farest point in direction of the plane normal - if it is contained in the halfspace, there is no intersection.
			if ( hspace.contains( farestPointOutside.rawCoordinates() ) ) {
				//std::cout << __func__ << " Farest point outside is contained - return full box." << std::endl;
				return *this;
			}
			if ( !hspace.contains( farestPointInside.rawCoordinates() ) ) {
				//std::cout << __func__ << " Farest point inside is  NOT contained - return EMPTY box." << std::endl;
				return BoxT<Number, Converter, Setting>::Empty();
			}

			//std::cout << __func__ << " Farest point outside: " << convert<Number,double>(farestPointOutside.rawCoordinates()).transpose() << std::endl;

			// at this point farestPointOutside is outside and farestPointInside is inside - the plane intersects the box somehow.
			std::vector<Point<Number>> discoveredPoints;
			std::vector<Point<Number>> intersectionPoints;
			std::queue<Point<Number>> workingQueue;
			workingQueue.push( farestPointOutside );

			// BFS search of points outside and intersection points.
			//std::cout << __func__ << " Start BFS search." << std::endl;
			while ( !workingQueue.empty() ) {
				//std::cout << "Queue size: " << workingQueue.size() << std::endl;
				Point<Number> current = workingQueue.front();
				workingQueue.pop();
				//std::cout << "Current Point: " << convert<Number,double>(current.rawCoordinates()).transpose() << std::endl;
				// create and test neighbors
				for ( unsigned d = 0; d < dim; ++d ) {
					Point<Number> tmp = current;
					if ( hspace.normal()( d ) < 0 && current.at( d ) == boxcopy.intervals()[d].lower() ) {
						tmp[d] = boxcopy.intervals()[d].upper();
					} else if ( hspace.normal()( d ) > 0 && current.at( d ) == boxcopy.intervals()[d].upper() ) {
						tmp[d] = boxcopy.intervals()[d].lower();
					} else if ( hspace.normal()( d ) == 0 ) {
						tmp[d] = tmp.at( d ) == boxcopy.intervals()[d].lower() ? boxcopy.intervals()[d].upper() : boxcopy.intervals()[d].lower();
					} else {
						// UNSINN!?
						//std::cout << "Could create point " << tmp << ", but is the same as " << current << std::endl;
						assert( tmp == current );
						continue;
					}

					//std::cout << "Created search-point: " << convert<Number,double>(tmp.rawCoordinates()).transpose() << std::endl;
					// if neighbor is new, test is, otherwise skip.
					if ( std::find( discoveredPoints.begin(), discoveredPoints.end(), tmp ) == discoveredPoints.end() ) {
						if ( !hspace.contains( tmp.rawCoordinates() ) ) {
							//std::cout << "is also outside, enqueue." << std::endl;
							workingQueue.push( tmp );
						} else {
							Number dCoord = 0;
							for ( unsigned i = 0; i < dim; ++i ) {
								if ( i != d ) {
									dCoord += hspace.normal()( i ) * current.at( i );
								}
							}
							dCoord -= hspace.offset();
							dCoord /= -hspace.normal()( d );
							Point<Number> intersectionPoint = tmp;
							intersectionPoint[d] = dCoord;
							//std::cout << "is inside, intersection point is " << convert<Number,double>(intersectionPoint.rawCoordinates()).transpose() << std::endl;
							intersectionPoints.push_back( intersectionPoint );
						}
					} else {
						//std::cout << "Already discovered - skip." << std::endl;
					}
				}
				discoveredPoints.push_back( current );
			}
			//std::cout << __func__ << " BFS search finished." << std::endl;

			// at this point we know that either min or max or both are outside but not both inside.
			if ( !holdsMin && !holdsMax ) {
				return BoxT<Number, Converter, Setting>( intersectionPoints );
			} else {
				if ( holdsMin ) {
					intersectionPoints.push_back( boxcopy.min() );
				} else {
					intersectionPoints.push_back( boxcopy.max() );
				}
				return BoxT<Number, Converter, Setting>( intersectionPoints );
			}
		}
	}
	return Empty();
}

template <typename Number, typename Converter, class Setting>
BoxT<Number, Converter, Setting> BoxT<Number, Converter, Setting>::intersectHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {
	assert( _mat.rows() == _vec.rows() );
	assert( _mat.cols() == Eigen::Index( this->dimension() ) );
	if ( _mat.rows() == 0 ) {
		return *this;
	}
	if ( this->empty() ) {
		return Empty();
	}

	if ( Setting::USE_INTERVAL_ARITHMETIC ) {
		std::vector<carl::Interval<Number>> intervals = this->intervals();
		// Todo: This is a first draft using the function for single halfspaces - maybe we can check more than one plane at the same time.
		for ( unsigned planeIndex = 0; planeIndex < _mat.rows(); ++planeIndex ) {
			bool empty = icpIntersectHalfspace( intervals, Halfspace<Number>( _mat.row( planeIndex ), _vec( planeIndex ) ) );
			if ( empty ) {
				return Empty();
			}
		}
		return BoxT<Number, Converter, Setting>( intervals );
	} else if ( Setting::HYPRO_BOX_AVOID_LINEAR_OPTIMIZATION ) {
		if ( _mat.rows() == 0 ) {
			return *this;
		}
		if ( !this->empty() ) {
			BoxT<Number, Converter, Setting> result = *this;
			// Todo: This is a first draft using the function for single halfspaces - maybe we can check more than one plane at the same time.
			for ( unsigned planeIndex = 0; planeIndex < _mat.rows(); ++planeIndex ) {
				result = result.intersectHalfspace( Halfspace<Number>( _mat.row( planeIndex ), _vec( planeIndex ) ) );
				if ( result.empty() ) {
					break;
				}
			}
			return result;
		}
		return Empty();
	} else {
		// convert box to a set of constraints, add other halfspaces and evaluate in box main directions to get new intervals.
		std::vector<vector_t<Number>> tpl = computeTemplate<Number>( this->dimension(), 4 );
		matrix_t<Number> boxDirections = this->matrix();
		vector_t<Number> boxDistances = this->vector();

		// At this point the constraints for the box are created as a matrix-vector pair.
		// Now add the halfspace constraints in a fresh matrix (we re-use the box template later).
		matrix_t<Number> constraints = matrix_t<Number>( boxDirections.rows() + _mat.rows(), _mat.cols() );
		vector_t<Number> constants = vector_t<Number>( boxDistances.rows() + _mat.rows() );
		constraints.block( 0, 0, boxDirections.rows(), boxDirections.cols() ) = boxDirections;
		constraints.block( boxDirections.rows(), 0, _mat.rows(), _mat.cols() ) = _mat;
		constants.block( 0, 0, boxDirections.rows(), 1 ) = boxDistances;
		constants.block( boxDirections.rows(), 0, _vec.rows(), 1 ) = _vec;

		// evaluate in box directions.
		Optimizer<Number> opt( constraints, constants );
		std::vector<EvaluationResult<Number>> results;
		for ( Eigen::Index rowIndex = 0; rowIndex < boxDirections.rows(); ++rowIndex ) {
			results.emplace_back( opt.evaluate( boxDirections.row( rowIndex ), false ) );
		}
		opt.cleanContexts();
		assert( Eigen::Index( results.size() ) == boxDirections.rows() );

		// re-construct box from results.
		std::pair<Point<Number>, Point<Number>> newLimits = std::make_pair( Point<Number>( vector_t<Number>::Zero( this->dimension() ) ), Point<Number>( vector_t<Number>::Zero( this->dimension() ) ) );
		for ( Eigen::Index rowIndex = 0; rowIndex < boxDirections.rows(); ++rowIndex ) {
			for ( Eigen::Index colIndex = 0; colIndex < boxDirections.cols(); ++colIndex ) {
				if ( boxDirections( rowIndex, colIndex ) > 0 ) {
					newLimits.second[colIndex] = results[rowIndex].supportValue;
				} else if ( boxDirections( rowIndex, colIndex ) < 0 ) {
					newLimits.first[colIndex] = -results[rowIndex].supportValue;
				}
			}
		}
		BoxT<Number, Converter, Setting> res( newLimits );
		res.reduceNumberRepresentation();
		return res;
	}
}

template <typename Number, typename Converter, class Setting>
bool BoxT<Number, Converter, Setting>::contains( const Point<Number>& point ) const {
	if ( this->dimension() > point.dimension() ) {
		return false;
	}

	for ( unsigned d = 0; d < this->dimension(); ++d ) {
		if ( !mLimits[d].contains( point.at( d ) ) ) {
			return false;
		}
	}
	return true;
}

template <typename Number, typename Converter, class Setting>
bool BoxT<Number, Converter, Setting>::contains( const BoxT<Number, Converter, Setting>& box ) const {
	if ( this->dimension() != box.dimension() ) {
		return false;
	}

	for ( unsigned d = 0; d < this->dimension(); ++d ) {
		if ( !mLimits[d].contains( box.interval( d ) ) ) {
			return false;
		}
	}
	return true;
}

template <typename Number, typename Converter, class Setting>
BoxT<Number, Converter, Setting> BoxT<Number, Converter, Setting>::unite( const BoxT<Number, Converter, Setting>& rhs ) const {
	if ( this->empty() ) {
		return rhs;
	}
	if ( rhs.empty() ) {
		return *this;
	}
	assert( dimension() == rhs.dimension() );

	std::vector<carl::Interval<Number>> newIntervals;
	for ( std::size_t i = 0; i < this->dimension(); ++i ) {
		newIntervals.emplace_back( mLimits[i].convexHull( rhs.interval( i ) ) );
	}
	return BoxT<Number, Converter, Setting>( newIntervals );
}

template <typename Number, typename Converter, class Setting>
BoxT<Number, Converter, Setting> BoxT<Number, Converter, Setting>::unite( const std::vector<BoxT<Number, Converter, Setting>>& boxes ) {
	if ( boxes.empty() ) {
		return BoxT<Number, Converter, Setting>::Empty();
	}

	auto res = boxes[0];
	for ( std::size_t i = 0; i < boxes.size(); ++i ) {
		res = res.unite( boxes[i] );
	}
	return res;
}

template <typename Number, typename Converter, class Setting>
void BoxT<Number, Converter, Setting>::clear() {
	*this = BoxT<Number, Converter, Setting>::Empty();
}

template <typename Number, typename Converter, class Setting>
void BoxT<Number, Converter, Setting>::print() const {
	//std::cout << *this << std::endl;
}

}  // namespace hypro
