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
		reduceNumberRepresentation();
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
			Eigen::FullPivLU<matrix_t<Number>> luDecomposition = intersection.fullPivLu();
			if ( luDecomposition.rank() == intersection.cols() ) {
				vector_t<Number> vertex = luDecomposition.solve( intersectionConstants );
				assert(vertex.rows() == _constraints.cols());
				possibleVertices.emplace( std::move(vertex) );
				//std::cout<< "Vertex computed: " << convert<Number,double>(vertex).transpose() << std::endl;
			}
		}
		assert(!possibleVertices.empty());

		// check if vertices are true vertices (i.e. they fulfill all constraints)
		for ( auto vertex = possibleVertices.begin(); vertex != possibleVertices.end(); ) {
			//std::cout  << "Refinement: Consider vertex : " << convert<Number,double>(*vertex).transpose() << std::endl;
			// possibleVertices.size() << std::endl;
			bool deleted = false;
			for ( unsigned rowIndex = 0; rowIndex < _constraints.rows(); ++rowIndex ) {
				Number res = vertex->dot( _constraints.row( rowIndex ) );
				if ( res > _constants( rowIndex ) ) {
					vertex = possibleVertices.erase( vertex );
					deleted = true;
					//std::cout << "Deleted because of row " << convert<Number,double>(vector_t<Number>(_constraints.row(rowIndex))) << std::endl;
					//std::cout << "Res was " << res << " and the constant is " << _constants(rowIndex) << std::endl;
					break;
				}
			}
			if(!deleted) {
				++vertex;
			}
		}
		// std::cout<<__func__ << " : " <<__LINE__ <<std::endl;
		// finish initialization
		if(possibleVertices.empty()) {
			assert(false);
			*this = BoxT<Number,Converter>::Empty();
		} else {
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
			reduceNumberRepresentation();
		}
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
		reduceNumberRepresentation();
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
		reduceNumberRepresentation();
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
matrix_t<Number> BoxT<Number, Converter>::matrix() const {
	matrix_t<Number> res = matrix_t<Number>::Zero(2*mLimits.first.dimension(), mLimits.first.dimension());
	for(unsigned i = 0; i < mLimits.first.dimension(); ++i) {
		res(2*i,i) = 1;
		res(2*i+1,i) = -1;
	}
	return res;
}

template<typename Number, typename Converter>
vector_t<Number> BoxT<Number, Converter>::vector() const {
	vector_t<Number> res = vector_t<Number>::Zero(2*mLimits.first.dimension());
	for(unsigned i = 0; i < mLimits.first.dimension(); ++i) {
		res(2*i) = mLimits.second.at(i);
		res(2*i+1) = -mLimits.first.at(i);
	}
	return res;
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
		Number inftyNorm = Point<Number>::inftyNorm( point );
		max = max > inftyNorm ? max : inftyNorm;
	}
	return max;
}

template<typename Number, typename Converter>
std::vector<Point<Number>> BoxT<Number,Converter>::vertices( const Location<Number>* ) const {
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
void BoxT<Number,Converter>::reduceNumberRepresentation(unsigned limit) const {
	Number limit2 = Number(limit)*Number(limit);
	for(unsigned d = 0; d < this->dimension(); ++d) {
		//std::cout << "(Upper Bound) Number: " << mLimits.second.at(d) << std::endl;
		if(mLimits.second.at(d) != 0) {
			Number numerator = carl::getNum(mLimits.second.at(d));
			Number denominator = carl::getDenom(mLimits.second.at(d));
			Number largest = carl::abs(numerator) > carl::abs(denominator) ? carl::abs(numerator) : carl::abs(denominator);
			Number dividend = largest / Number(limit);
			assert(largest/dividend == limit);
			if(largest > limit2){
				Number val = mLimits.second.at(d) > 0 ? Number(carl::ceil(numerator/dividend)) / Number(carl::floor(denominator/dividend)) : Number(carl::ceil(numerator/dividend)) / Number(carl::ceil(denominator/dividend));
				//std::cout << "Assert: " << val << " >= " << mLimits.second.at(d) << std::endl;
				assert(val >= mLimits.second.at(d));
				//std::cout << "(Upper bound) Rounding Error: " << carl::convert<Number,double>(val - mLimits.second.at(d)) << std::endl;
				mLimits.second[d] = val;
			}
		}

		//std::cout << "(Lower Bound) Number: " << mLimits.first.at(d) << std::endl;
		if(mLimits.first.at(d) != 0) {
			Number numerator = carl::getNum(mLimits.first.at(d));
			Number denominator = carl::getDenom(mLimits.first.at(d));
			Number largest = carl::abs(numerator) > carl::abs(denominator) ? carl::abs(numerator) : carl::abs(denominator);
			Number dividend = largest / Number(limit);
			assert(largest/dividend == limit);
			if(largest > limit2){
				Number val =  mLimits.first.at(d) > 0 ?  Number(carl::floor(numerator/dividend)) / Number(carl::ceil(denominator/dividend)) : Number(carl::floor(numerator/dividend)) / Number(carl::floor(denominator/dividend));
				//std::cout << "Assert: " << val << " <= " << mLimits.first.at(d) << std::endl;
				assert(val <= mLimits.first.at(d));
				//std::cout << "(Lower bound) Rounding Error: " << carl::convert<Number,double>(val - mLimits.first.at(d)) << std::endl;
				mLimits.first[d] = val;
			}
		}
	}
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
	// std::cout << __func__ << ": input matrix: " << _mat << std::endl << "input vector: " << _vec << std::endl;
	// std::cout << __func__ << ": This->dimension() = " << this->dimension() << std::endl;
	assert(this->dimension() == unsigned(_mat.cols()));
	std::vector<unsigned> limitingPlanes;

	for(unsigned rowIndex = 0; rowIndex < _mat.rows(); ++rowIndex) {
		carl::Interval<Number> evaluatedBox = carl::Interval<Number>(0);
		for(unsigned d = 0; d < _mat.cols(); ++d){
			evaluatedBox += carl::Interval<Number>(mLimits.first.at(d), mLimits.second.at(d)) * Number(_mat(rowIndex,d));
		}

		if(evaluatedBox.lower() > _vec(rowIndex)){
			return std::make_pair(false,*this);
		}

		if(evaluatedBox.upper() > _vec(rowIndex)){
			limitingPlanes.push_back(rowIndex);
		}
	}

	// at this point the box cannot be empty.
	if(limitingPlanes.empty()){
		return std::make_pair(true, *this);
	}

	// at this point the box will be limited but not empty.
	matrix_t<Number> newPlanes = matrix_t<Number>(limitingPlanes.size(), _mat.cols());
	vector_t<Number> newDistances = vector_t<Number>(limitingPlanes.size());
	int rowPos = newPlanes.rows()-1;
	while(!limitingPlanes.empty()){
		assert(rowPos >= 0);
		newPlanes.row(rowPos) = _mat.row(limitingPlanes.back());
		newDistances(rowPos) = _vec(limitingPlanes.back());
		--rowPos;
		limitingPlanes.pop_back();
	}
	assert(newPlanes.rows() == newDistances.rows());
	return std::make_pair(true, this->intersectHalfspaces(newPlanes,newDistances));
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

	//std::cout << __func__ << ": Min: " << min << ", Max: " << max << std::endl;

	return BoxT<Number,Converter>( std::make_pair(min, max) );
}

template<typename Number, typename Converter>
BoxT<Number,Converter> BoxT<Number,Converter>::minkowskiSum( const BoxT<Number,Converter> &rhs ) const {
	assert( dimension() == rhs.dimension() );
	return BoxT<Number,Converter>(std::make_pair(mLimits.first + rhs.min(), mLimits.second + rhs.max()));
}

template<typename Number, typename Converter>
BoxT<Number,Converter> BoxT<Number,Converter>::minkowskiDecomposition( const BoxT<Number,Converter>& rhs ) const {
	if(rhs.empty()) {
		return *this;
	}
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
BoxT<Number,Converter> BoxT<Number,Converter>::intersectHalfspace( const Halfspace<Number>& hspace ) const {
	//std::cout << __func__ << " of " << *this << " and " << hspace << std::endl;
	if(!this->empty()) {
		// Preprocessing: If any two points opposite to each other are contained, the box stays the same - test limit points
		bool holdsMin = hspace.holds(mLimits.first.rawCoordinates());
		bool holdsMax = hspace.holds(mLimits.second.rawCoordinates());
		if(holdsMin && holdsMax){
			return *this;
		}
		unsigned dim = this->dimension();

		// Phase 1: Find starting point (point outside) for phase 2 by depth-first search or use limit points, if applicable
		Point<Number> farestPointOutside = mLimits.first;
		Point<Number> farestPointInside = mLimits.first;
		unsigned usedDimension = 0;
		// determine walk direction by using plane normal and variable order
		for(; usedDimension < dim; ++usedDimension){
			if(hspace.normal()(usedDimension) > 0){
				if(farestPointOutside.at(usedDimension) != mLimits.second.at(usedDimension)) {
					farestPointOutside[usedDimension] = mLimits.second.at(usedDimension);
				}
				if(farestPointInside.at(usedDimension) != mLimits.first.at(usedDimension)) {
					farestPointInside[usedDimension] = mLimits.first.at(usedDimension);
				}
			} else if( hspace.normal()(usedDimension) < 0){
				if( farestPointOutside.at(usedDimension) != mLimits.first.at(usedDimension) ) {
					farestPointOutside[usedDimension] = mLimits.first.at(usedDimension);
				}
				if(farestPointInside.at(usedDimension) != mLimits.second.at(usedDimension)) {
					farestPointInside[usedDimension] = mLimits.second.at(usedDimension);
				}
			}
		}
		// farestPointOutside is the point farest point in direction of the plane normal - if it is contained in the halfspace, there is no intersection.
		if(hspace.holds(farestPointOutside.rawCoordinates())) {
			return *this;
		}
		if(!hspace.holds(farestPointInside.rawCoordinates())) {
			return BoxT<Number,Converter>::Empty();
		}

		//std::cout << __func__ << " Point farest outside: " << farestPointOutside << std::endl;

		// at this point farestPointOutside is outside and farestPointInside is inside - the plane intersects the box somehow.
		std::vector<Point<Number>> discoveredPoints;
		std::vector<Point<Number>> intersectionPoints;
		std::queue<Point<Number>> workingQueue;
		workingQueue.push(farestPointOutside);

		// BFS search of points outside and intersection points.
		//std::cout << __func__ << " Start BFS search." << std::endl;
		while(!workingQueue.empty()){
			//std::cout << "Queue size: " << workingQueue.size() << std::endl;
			Point<Number> current = workingQueue.front();
			workingQueue.pop();
			//std::cout << "Current Point: " << current << std::endl;
			// create and test neighbors
			for(unsigned d = 0; d < dim; ++d ) {
				Point<Number> tmp = current;
				if( hspace.normal()(d) < 0 && current.at(d) == mLimits.first.at(d) ){
					tmp[d] = mLimits.second.at(d);
				} else if ( hspace.normal()(d) > 0 && current.at(d) == mLimits.second.at(d) ) {
					tmp[d] = mLimits.first.at(d);
				} else if ( hspace.normal()(d) == 0 ) {
					tmp[d] = tmp.at(d) == mLimits.first.at(d) ? mLimits.second.at(d) : mLimits.first.at(d);
				} else {
					//std::cout << "Could create point " << tmp << ", but is the same as " << current << std::endl;
					assert(tmp == current);
					continue;
				}

				//std::cout << "Created search-point: " << tmp << std::endl;
				// if neighbor is new, test is, otherwise skip.
				if(std::find(discoveredPoints.begin(), discoveredPoints.end(), tmp) == discoveredPoints.end()){
					if(!hspace.holds(tmp.rawCoordinates())){
						//std::cout << "is also outside, enqueue." << std::endl;
						workingQueue.push(tmp);
					} else {
						Number dCoord = 0;
						for(unsigned i = 0; i < dim; ++i){
							if( i != d ) {
								dCoord += hspace.normal()(i) * current.at(i);
							}
						}
						dCoord -= hspace.offset();
						dCoord /= -hspace.normal()(d);
						Point<Number> intersectionPoint = tmp;
						intersectionPoint[d] = dCoord;
						//std::cout << "is inside, intersection point is " << intersectionPoint << std::endl;
						intersectionPoints.push_back(intersectionPoint);
					}
				} else {
					//std::cout << "Already discovered - skip." << std::endl;
				}
			}
			discoveredPoints.push_back(current);
		}
		//std::cout << __func__ << " BFS search finished." << std::endl;

		// at this point we know that either min or max or both are outside but not both inside.
		if(!holdsMin && !holdsMax) {
			return BoxT<Number,Converter>(intersectionPoints);
		} else {
			if(holdsMin){
				intersectionPoints.push_back(mLimits.first);
			} else {
				intersectionPoints.push_back(mLimits.second);
			}
			return BoxT<Number,Converter>(intersectionPoints);
		}
	}
	return Empty(this->dimension());
}

template<typename Number, typename Converter>
BoxT<Number,Converter> BoxT<Number,Converter>::intersectHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {
	//std::cout << __func__ << ": " << _mat << ", " << _vec << std::endl;
	assert(_mat.rows() == _vec.rows());
	if(_mat.rows() == 0) {
		return *this;
	}
	if(!this->empty()) {
		BoxT<Number,Converter> result = *this;
		// Todo: This is a first draft using the function for single halfspaces - maybe we can check more than one plane at the same time.
		for(unsigned planeIndex = 0; planeIndex < _mat.rows(); ++planeIndex) {
			result = result.intersectHalfspace(Halfspace<Number>(_mat.row(planeIndex), _vec(planeIndex)));
			if(result.empty()){
				break;
			}
		}
		return result;
	}
	return Empty(this->dimension());
}

template<typename Number, typename Converter>
bool BoxT<Number,Converter>::contains( const Point<Number> &point ) const {
	if ( this->dimension() > point.dimension() ) {
		return false;
	}

	for(unsigned d = 0; d < this->dimension(); ++d) {
		if(mLimits.first.at(d) > point.at(d))
			return false;
		if(mLimits.second.at(d) < point.at(d))
			return false;
	}
	return true;
}

template<typename Number, typename Converter>
bool BoxT<Number,Converter>::contains( const BoxT<Number,Converter> &box ) const {
	if ( this->dimension() != box.dimension() ) {
		return false;
	}

	for(unsigned d = 0; d < this->dimension(); ++d) {
		if(mLimits.first.at(d) > box.min().at(d))
			return false;
		if(mLimits.second.at(d) < box.max().at(d))
			return false;
	}
	return true;
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
BoxT<Number,Converter> BoxT<Number,Converter>::unite( const std::vector<BoxT<Number,Converter>>& boxes ) const {
	std::pair<Point<Number>, Point<Number>> newLimits = this->mLimits;
	for(const auto& box : boxes) {
		newLimits.first = coeffWiseMin(newLimits.first, box.limits().first);
		newLimits.second = coeffWiseMax(newLimits.first, box.limits().second);
	}
	return BoxT<Number,Converter>(newLimits);
}

template<typename Number, typename Converter>
void BoxT<Number,Converter>::clear() {
	*this = BoxT<Number,Converter>::Empty(0);
}

template<typename Number, typename Converter>
void BoxT<Number,Converter>::print() const {
	//std::cout << *this << std::endl;
}

}  // namespace hypro
