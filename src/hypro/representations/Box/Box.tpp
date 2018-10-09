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

	template<typename Number, typename Converter, class Setting>
	BoxT<Number,Converter,Setting>::BoxT( const std::vector<carl::Interval<Number>>& _intervals )
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

	template<typename Number, typename Converter, class Setting>
	BoxT<Number,Converter,Setting>::BoxT( const matrix_t<Number>& _constraints, const vector_t<Number>& _constants )
	{
		TRACE("hypro.representations","matrix: " << _constraints << ", vector: " << _constants);
		if(Setting::HYPRO_BOX_AVOID_LINEAR_OPTIMIZATION == true){
			// calculate all possible Halfspace intersections -> TODO: dPermutation can
			// be improved.
			assert(_constraints.rows() == _constants.rows());
			if(_constraints.rows() == 0) {
				assert(this->empty());
				assert(this->dimension() == 0);
				return;
			}
			Permutator permutator = Permutator( _constraints.rows(), _constraints.cols() );
			matrix_t<Number> intersection = matrix_t<Number>( _constraints.cols(), _constraints.cols() );
			vector_t<Number> intersectionConstants = vector_t<Number>( _constraints.cols() );
			std::set<vector_t<Number>> possibleVertices;
			std::vector<std::size_t> permutation;
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
				if(!deleted) {
					++vertex;
				}
			}
			// std::cout<<__func__ << " : " <<__LINE__ <<std::endl;
			// finish initialization
			if(possibleVertices.empty()) {
				assert(false);
				*this = BoxT<Number,Converter,Setting>::Empty();
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
			}

		} else {

			// convert box to a set of constraints, add other halfspaces and evaluate in box main directions to get new intervals.
			std::vector<vector_t<Number>> tpl = computeTemplate<Number>(_constraints.cols(), 4);
			matrix_t<Number> boxDirections = matrix_t<Number>::Zero(tpl.size(), _constraints.cols());
			vector_t<Number> boxDistances = vector_t<Number>::Zero(boxDirections.rows());

			// set up matrix.
			// Todo: Can be combined with next loop.
			Eigen::Index i = 0;
			for(const auto& row : tpl) {
				boxDirections.row(i) = row;
				++i;
			}

			// the template has one non-Zero index per row
			/*
			for(Eigen::Index rowIndex = 0; rowIndex < boxDirections.rows(); ++rowIndex) {
				for(Eigen::Index colIndex = 0; colIndex < boxDirections.cols(); ++colIndex) {
					if(boxDirections(rowIndex,colIndex) > 0) {
						boxDistances(rowIndex) = mLimits.second.at(colIndex);
						break;
					} else if (boxDirections(rowIndex,colIndex) < 0) {
						boxDistances(rowIndex) = -mLimits.first.at(colIndex);
						break;
					}
				}
			}
			*/

			// evaluate in box directions.
			Optimizer<Number> opt(_constraints,_constants);
			std::vector<EvaluationResult<Number>> results;
			for(Eigen::Index rowIndex = 0; rowIndex < boxDirections.rows(); ++rowIndex) {
				results.emplace_back(opt.evaluate(boxDirections.row(rowIndex), false));
			}
			opt.cleanGLPInstance();
			assert(Eigen::Index(results.size()) == boxDirections.rows());

			// re-construct box from results.
			mLimits = std::make_pair(Point<Number>(vector_t<Number>::Zero(_constraints.cols())), Point<Number>(vector_t<Number>::Zero(_constraints.cols())));
			for(Eigen::Index rowIndex = 0; rowIndex < boxDirections.rows(); ++rowIndex) {
				for(Eigen::Index colIndex = 0; colIndex < boxDirections.cols(); ++colIndex) {
					if(boxDirections(rowIndex,colIndex) > 0) {
						mLimits.second[colIndex] = results[rowIndex].supportValue;
					} else if (boxDirections(rowIndex,colIndex) < 0) {
						mLimits.first[colIndex] = -results[rowIndex].supportValue;
				}
			}
		}

		reduceNumberRepresentation();
	}
}

template<typename Number, typename Converter, class Setting>
BoxT<Number,Converter,Setting>::BoxT( const std::set<Point<Number>> &_points ) {
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
	reduceNumberRepresentation();
}

template<typename Number, typename Converter, class Setting>
BoxT<Number,Converter,Setting>::BoxT( const std::vector<Point<Number>> &_points ) {
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
	reduceNumberRepresentation();
}

/*
template<typename Number, typename Converter, class Setting>
BoxT<Number,Converter,Setting>::BoxT( const std::set<Vertex<Number>> &_vertices ) {
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
template<typename Number, typename Converter, class Setting>
BoxT<Number,Converter,Setting>::BoxT( const std::vector<Vertex<Number>> &_vertices ) {
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

template<typename Number, typename Converter, class Setting>
std::vector<carl::Interval<Number>> BoxT<Number,Converter,Setting>::boundaries() const {
	std::vector<carl::Interval<Number>> result;
	result.reserve(this->dimension());

	for(std::size_t d = 0; d < this->dimension(); ++d) {
		result.push_back(carl::Interval<Number>(mLimits.first.at(d), mLimits.second.at(d)));
	}

	return result;
}

template<typename Number, typename Converter, class Setting>
matrix_t<Number> BoxT<Number,Converter,Setting>::matrix() const {
	matrix_t<Number> res = matrix_t<Number>::Zero(2*mLimits.first.dimension(), mLimits.first.dimension());
	for(unsigned i = 0; i < mLimits.first.dimension(); ++i) {
		res(2*i,i) = 1;
		res(2*i+1,i) = -1;
	}
	return res;
}

template<typename Number, typename Converter, class Setting>
vector_t<Number> BoxT<Number,Converter,Setting>::vector() const {
	vector_t<Number> res = vector_t<Number>::Zero(2*mLimits.first.dimension());
	for(unsigned i = 0; i < mLimits.first.dimension(); ++i) {
		res(2*i) = mLimits.second.at(i);
		res(2*i+1) = -mLimits.first.at(i);
	}
	return res;
}

template<typename Number, typename Converter, class Setting>
std::vector<Halfspace<Number>> BoxT<Number,Converter,Setting>::constraints() const {
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

template<typename Number, typename Converter, class Setting>
carl::Interval<Number> BoxT<Number,Converter,Setting>::interval( std::size_t d ) const {
	if ( d >= mLimits.first.dimension() ) {
		return carl::Interval<Number>::emptyInterval();
	}
	return carl::Interval<Number>(mLimits.first.at(d), mLimits.second.at(d));
}

template<typename Number, typename Converter, class Setting>
Number BoxT<Number,Converter,Setting>::supremum() const {
	Number max = 0;
	for ( auto &point : this->vertices() ) {
		Number inftyNorm = Point<Number>::inftyNorm( point );
		max = max > inftyNorm ? max : inftyNorm;
	}
	return max;
}

template<typename Number, typename Converter, class Setting>
std::vector<Point<Number>> BoxT<Number,Converter,Setting>::vertices( const matrix_t<Number>& ) const {
	std::vector<Point<Number>> result;
	std::size_t limit = std::size_t(pow( 2, mLimits.first.dimension() ));

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

template<typename Number, typename Converter, class Setting>
EvaluationResult<Number> BoxT<Number,Converter,Setting>::evaluate( const vector_t<Number>& _direction, bool ) const {
	assert(_direction.rows() == Eigen::Index(this->dimension()));
	if(this->empty()){
		return EvaluationResult<Number>(); // defaults to infeasible, i.e. empty.
	}

	// find the point, which represents the maximum towards the direction - compare signs.
	vector_t<Number> furthestPoint = vector_t<Number>(this->dimension());
	for(Eigen::Index i = 0; i < furthestPoint.rows(); ++i) {
		furthestPoint(i) = _direction(i) >= 0 ? mLimits.second.at(i) : mLimits.first.at(i);
	}
	return EvaluationResult<Number>(furthestPoint.dot(_direction),furthestPoint,SOLUTION::FEAS);
}

template<typename Number, typename Converter, class Setting>
std::vector<EvaluationResult<Number>> BoxT<Number,Converter,Setting>::multiEvaluate( const matrix_t<Number>& _directions, bool useExact ) const {
	std::vector<EvaluationResult<Number>> res;
	for(Eigen::Index i = 0; i < _directions.rows(); ++i) {
		res.emplace_back(this->evaluate(vector_t<Number>(_directions.row(i)), useExact));
	}
	return res;
}

template<typename Number, typename Converter, class Setting>
std::size_t BoxT<Number,Converter,Setting>::size() const {
	if(this->empty()) {
		return 0;
	}
	// TODO: What is this supposed to do???
	return 2;
}

template<typename Number, typename Converter, class Setting>
const BoxT<Number,Converter,Setting>& BoxT<Number,Converter,Setting>::reduceNumberRepresentation(unsigned limit) {
	Number limit2 = Number(limit)*Number(limit);
	for(unsigned d = 0; d < this->dimension(); ++d) {
		//std::cout << "(Upper Bound) Number: " << mLimits.second.at(d) << std::endl;
		if(mLimits.second.at(d) != 0) {
			Number numerator = carl::getNum(mLimits.second.at(d));
			Number denominator = carl::getDenom(mLimits.second.at(d));
			Number largest = carl::abs(numerator) > carl::abs(denominator) ? carl::abs(numerator) : carl::abs(denominator);
			if(largest > limit2){
				Number dividend = largest / Number(limit);
				assert(largest/dividend == limit);
				Number val = Number(carl::ceil(numerator/dividend));
				Number newDenom;
				if(mLimits.second.at(d) > 0) {
					newDenom = Number(carl::floor(denominator/dividend));
				} else {
					newDenom = Number(carl::ceil(denominator/dividend));
				}
				if(newDenom != 0) {
					val = val / newDenom;
					assert(val >= mLimits.second.at(d));
					mLimits.second[d] = val;
				}
				//std::cout << "Assert: " << val << " >= " << mLimits.second.at(d) << std::endl;
				//std::cout << "(Upper bound) Rounding Error: " << carl::convert<Number,double>(val - mLimits.second.at(d)) << std::endl;
			}
		}

		//std::cout << "(Lower Bound) Number: " << mLimits.first.at(d) << std::endl;
		if(mLimits.first.at(d) != 0) {
			Number numerator = carl::getNum(mLimits.first.at(d));
			Number denominator = carl::getDenom(mLimits.first.at(d));
			Number largest = carl::abs(numerator) > carl::abs(denominator) ? carl::abs(numerator) : carl::abs(denominator);
			if(largest > limit2){
				Number dividend = largest / Number(limit);
				assert(largest/dividend == limit);
				Number val = Number(carl::floor(numerator/dividend));
				Number newDenom;
				if( mLimits.first.at(d) > 0) {
					newDenom = Number(carl::ceil(denominator/dividend));
				} else {
					newDenom = Number(carl::floor(denominator/dividend));
				}
				if(newDenom != 0) {
					val = val / newDenom;
					assert(val <= mLimits.first.at(d));
					mLimits.first[d] = val;
				}
				//std::cout << "Assert: " << val << " <= " << mLimits.first.at(d) << std::endl;
				//std::cout << "(Lower bound) Rounding Error: " << carl::convert<Number,double>(val - mLimits.first.at(d)) << std::endl;
			}
		}
	}
	return *this;
}

template<typename Number, typename Converter, class Setting>
BoxT<Number,Converter,Setting> BoxT<Number,Converter,Setting>::makeSymmetric() const {
	Point<Number> limit = mLimits.first;
	for(unsigned d = 0; d < mLimits.first.dimension(); ++d) {
		limit[d] = carl::abs(mLimits.first.at(d)) >= carl::abs(mLimits.second.at(d)) ? carl::abs(mLimits.first.at(d)) : carl::abs(mLimits.second.at(d));
	}
	return BoxT<Number,Converter,Setting>(std::make_pair(-limit, limit));
}

template<typename Number, typename Converter, class Setting>
std::pair<CONTAINMENT, BoxT<Number,Converter,Setting>> BoxT<Number,Converter,Setting>::satisfiesHalfspace( const Halfspace<Number>& rhs ) const {
	std::vector<Point<Number>> vertices = this->vertices();
	bool allVerticesContained = true;
	unsigned outsideVertexCnt = 0;
	for(const auto& vertex : vertices) {

		if(vertex.rawCoordinates().dot(rhs.normal()) > rhs.offset()){
			allVerticesContained = false;
			outsideVertexCnt++;
		}
	}
	if(allVerticesContained) {
		return std::make_pair(CONTAINMENT::FULL, *this);
	}

	if(outsideVertexCnt == vertices.size()) {
		return std::make_pair(CONTAINMENT::NO, Empty());
	}

	return std::make_pair(CONTAINMENT::PARTIAL, this->intersectHalfspace(rhs));
}

template<typename Number, typename Converter, class Setting>
std::pair<CONTAINMENT, BoxT<Number,Converter,Setting>> BoxT<Number,Converter,Setting>::satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {
	if(_mat.rows() == 0) {
		return std::make_pair(CONTAINMENT::FULL, *this);
	}
	//std::cout << __func__ << " This: " << convert<Number,double>(*this) << std::endl;
	//std::cout << __func__ << ": input matrix: " << convert<Number,double>(_mat) << std::endl << "input vector: " << convert<Number,double>(_vec) << std::endl;
	// std::cout << __func__ << ": This->dimension() = " << this->dimension() << std::endl;
	assert(this->dimension() == unsigned(_mat.cols()));
	std::vector<unsigned> limitingPlanes;

	for(unsigned rowIndex = 0; rowIndex < _mat.rows(); ++rowIndex) {
		carl::Interval<Number> evaluatedBox = carl::Interval<Number>(0);
		for(unsigned d = 0; d < _mat.cols(); ++d){
			evaluatedBox += carl::Interval<Number>(mLimits.first.at(d), mLimits.second.at(d)) * Number(_mat(rowIndex,d));
		}

		//std::cout << __func__ << " Row: " << convert<Number,double>(_mat.row(rowIndex)) << std::endl;
		//std::cout << __func__ << " Evaluated box: " << evaluatedBox << std::endl;
		//std::cout << __func__ << " Distance: " << carl::convert<Number,double>(_vec(rowIndex)) << std::endl;

		if(evaluatedBox.lower() > _vec(rowIndex)){
			return std::make_pair(CONTAINMENT::NO,Empty());
		}

		if(evaluatedBox.upper() > _vec(rowIndex)){
			limitingPlanes.push_back(rowIndex);
		}
	}

	// at this point the box cannot be empty.
	if(limitingPlanes.empty()){
		return std::make_pair(CONTAINMENT::FULL, *this);
	}

	// at this point the box will be limited but not empty.
	matrix_t<Number> newPlanes = matrix_t<Number>(limitingPlanes.size(), _mat.cols());
	vector_t<Number> newDistances = vector_t<Number>(limitingPlanes.size());
	Eigen::Index rowPos = newPlanes.rows()-1;
	while(!limitingPlanes.empty()){
		assert(rowPos >= 0);
		newPlanes.row(rowPos) = _mat.row(limitingPlanes.back());
		newDistances(rowPos) = _vec(limitingPlanes.back());
		--rowPos;
		limitingPlanes.pop_back();
	}
	assert(newPlanes.rows() == newDistances.rows());
	return std::make_pair(CONTAINMENT::PARTIAL, this->intersectHalfspaces(newPlanes,newDistances));
}

template<typename Number, typename Converter, class Setting>
BoxT<Number,Converter,Setting> BoxT<Number,Converter,Setting>::project(const std::vector<std::size_t>& dimensions) const {
	if(dimensions.empty()) {
		return Empty();
	}
	return BoxT<Number,Converter,Setting>(std::make_pair(mLimits.first.project(dimensions), mLimits.second.project(dimensions)));
}

template<typename Number, typename Converter, class Setting>
BoxT<Number,Converter,Setting> BoxT<Number,Converter,Setting>::linearTransformation( const matrix_t<Number> &A ) const {
	#ifndef NDEBUG
	bool empty = this->empty();
	#endif
	// create both limit matrices
	// std::cout << __func__ << ": This: " << *this << std::endl;
	// std::cout << __func__ << ": Matrix" <<  std::endl << A << std::endl << "Vector" << std::endl << b << std::endl;
	//matrix_t<Number> ax(A);
	//matrix_t<Number> bx(A);
	Point<Number> min(vector_t<Number>::Zero(this->dimension()));
	Point<Number> max(vector_t<Number>::Zero(this->dimension()));

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
	//std::cout << __func__ << ": Min: " << min << ", Max: " << max << std::endl;
	#ifndef NDEBUG
	assert( (BoxT<Number,Converter,Setting>(std::make_pair(min, max)).empty() == empty) );
	#endif
	BoxT<Number,Converter,Setting> res(std::make_pair(min, max));
	res.reduceNumberRepresentation();
	assert(res.contains(Point<Number>(A*mLimits.first.rawCoordinates())));
	assert(res.contains(Point<Number>(A*mLimits.second.rawCoordinates())));
	#ifndef NDEBUG
	std::vector<Point<Number>> vertices = this->vertices();
	Point<Number> manualMin = Point<Number>(A*(vertices.begin()->rawCoordinates()));
	Point<Number> manualMax = Point<Number>(A*(vertices.begin()->rawCoordinates()));
	for(const auto& v : vertices) {
		Point<Number> t = Point<Number>(A*v.rawCoordinates());
		assert(res.contains(t));
		for(std::size_t d = 0; d < this->dimension(); ++d) {
			if(manualMin.at(d) > t.at(d)) {
				manualMin[d] = t[d];
			}
			if(manualMax.at(d) < t.at(d)) {
				manualMax[d] = t[d];
			}
		}
	}
	//assert(manualMin == res.min());
	//assert(manualMax == res.max());
	#endif
	return res;
}

template<typename Number, typename Converter, class Setting>
BoxT<Number,Converter,Setting> BoxT<Number,Converter,Setting>::affineTransformation( const matrix_t<Number> &A, const vector_t<Number> &b ) const {
	if(this->empty()){
		return *this;
	}
	TRACE("hypro.representations.box","This: " << *this << ", A: " << A << "b: " << b);
	BoxT<Number,Converter,Setting> res = this->linearTransformation(A);
	TRACE("hypro.representations.box","Result of linear trafo: " << res);
	return BoxT<Number,Converter,Setting>( std::make_pair(res.min()+b, res.max()+b) );
}

template<typename Number, typename Converter, class Setting>
BoxT<Number,Converter,Setting> BoxT<Number,Converter,Setting>::minkowskiSum( const BoxT<Number,Converter,Setting> &rhs ) const {
	assert( dimension() == rhs.dimension() );
	return BoxT<Number,Converter,Setting>(std::make_pair(mLimits.first + rhs.min(), mLimits.second + rhs.max()));
}

template<typename Number, typename Converter, class Setting>
BoxT<Number,Converter,Setting> BoxT<Number,Converter,Setting>::minkowskiDecomposition( const BoxT<Number,Converter,Setting>& rhs ) const {
	if(rhs.empty()) {
		return *this;
	}
	TRACE("hypro.representations.box","This: " << *this << ", Rhs: " << rhs);
	assert( dimension() == rhs.dimension() );
	// assert( std::mismatch(this->boundaries().begin(), this->boundaries.end(), rhs.boundaries().begin(), rhs.boundaries.end(), [&](a,b) -> bool {return a.diameter() >= b.diameter()}  ) ); // TODO: wait for c++14 support
	// assert( (BoxT<Number,Converter,Setting>(std::make_pair(mLimits.first - rhs.min(), mLimits.second - rhs.max())).minkowskiSum(rhs) == *this) );
	return BoxT<Number,Converter,Setting>(std::make_pair(mLimits.first - rhs.min(), mLimits.second - rhs.max()));
}

template<typename Number, typename Converter, class Setting>
BoxT<Number,Converter,Setting> BoxT<Number,Converter,Setting>::intersect( const BoxT<Number,Converter,Setting> &rhs ) const {
	std::size_t dim = rhs.dimension() < this->dimension() ? rhs.dimension() : this->dimension();
	std::pair<Point<Number>, Point<Number>> limits(std::make_pair(Point<Number>(vector_t<Number>::Zero(dim)), Point<Number>(vector_t<Number>::Zero(dim))));
	std::pair<Point<Number>, Point<Number>> rhsLimits = rhs.limits();
	for ( std::size_t i = 0; i < dim; ++i ) {
		limits.first[i] = mLimits.first.at(i) > rhsLimits.first.at(i) ? mLimits.first.at(i) : rhsLimits.first.at(i);
		limits.second[i] = mLimits.second.at(i) < rhsLimits.second.at(i) ? mLimits.second.at(i) : rhsLimits.second.at(i);
	}
	return BoxT<Number,Converter,Setting>(limits);
}

template<typename Number, typename Converter, class Setting>
BoxT<Number,Converter,Setting> BoxT<Number,Converter,Setting>::intersectHalfspace( const Halfspace<Number>& hspace ) const {
	//std::cout << __func__ << " of " << *this << " and " << hspace << std::endl;
	if(!this->empty()) {
		if(Setting::USE_INTERVAL_ARITHMETIC) {
			std::vector<carl::Interval<Number>> intervals = this->boundaries();
			bool empty = icpIntersectHalfspace(intervals,hspace);
			if(empty) {
				return Empty(this->dimension());
			}
			return BoxT<Number,Converter,Setting>(intervals);
		} else { // Do not use interval arithmetic.
			BoxT<Number,Converter,Setting> boxcopy(*this);
			// Preprocessing: If any two points opposite to each other are contained, the box stays the same - test limit points
			bool holdsMin = hspace.contains(boxcopy.limits().first.rawCoordinates());
			bool holdsMax = hspace.contains(boxcopy.limits().second.rawCoordinates());
			if(holdsMin && holdsMax){
				//std::cout << __func__ << " Min and Max are below the halfspace." << std::endl;
				return *this;
			}

			// another special case: if the hspace normal is axis-aligned, i.e. it has only one non-zero entry, we simply can use interval-
			// style intersection.
			if(hspace.normal().nonZeros() == 1) {
				// from previous checks we know that either the lowest or the highest point is not contained. If both are not
				// contained and the normal is axis-aligned, the set is empty.
				if(!holdsMin && !holdsMax) {
					return Empty(this->dimension());
				}

				// find the one, non-zero component
				unsigned nonZeroDim = 0;
				while(hspace.normal()(nonZeroDim) == 0 ) ++nonZeroDim;

				if(hspace.normal()(nonZeroDim) > 0) {
					boxcopy.rLimits().second[nonZeroDim] = hspace.offset() / hspace.normal()(nonZeroDim);
				} else {
					boxcopy.rLimits().first[nonZeroDim] = hspace.offset() / hspace.normal()(nonZeroDim);
				}
				return boxcopy;
			}

			//std::cout << __func__ << " Min below: " << holdsMin << ", Max below: " << holdsMax << std::endl;
			std::size_t dim = this->dimension();

			// Phase 1: Find starting point (point outside) for phase 2 by depth-first search or use limit points, if applicable
			Point<Number> farestPointOutside = boxcopy.limits().first;
			Point<Number> farestPointInside = boxcopy.limits().first;
			std::size_t usedDimension = 0;
			// determine walk direction by using plane normal and variable order
			for(; usedDimension < dim; ++usedDimension){
				if(hspace.normal()(usedDimension) > 0){
					if(farestPointOutside.at(usedDimension) != boxcopy.limits().second.at(usedDimension)) {
						farestPointOutside[usedDimension] = boxcopy.limits().second.at(usedDimension);
					}
					if(farestPointInside.at(usedDimension) != boxcopy.limits().first.at(usedDimension)) {
						farestPointInside[usedDimension] = boxcopy.limits().first.at(usedDimension);
					}
				} else if( hspace.normal()(usedDimension) < 0){
					if( farestPointOutside.at(usedDimension) != boxcopy.limits().first.at(usedDimension) ) {
						farestPointOutside[usedDimension] = boxcopy.limits().first.at(usedDimension);
					}
					if(farestPointInside.at(usedDimension) != boxcopy.limits().second.at(usedDimension)) {
						farestPointInside[usedDimension] = boxcopy.limits().second.at(usedDimension);
					}
				}
			}
			// farestPointOutside is the point farest point in direction of the plane normal - if it is contained in the halfspace, there is no intersection.
			if(hspace.contains(farestPointOutside.rawCoordinates())) {
				//std::cout << __func__ << " Farest point outside is contained - return full box." << std::endl;
				return *this;
			}
			if(!hspace.contains(farestPointInside.rawCoordinates())) {
				//std::cout << __func__ << " Farest point inside is  NOT contained - return EMPTY box." << std::endl;
				return BoxT<Number,Converter,Setting>::Empty();
			}

			//std::cout << __func__ << " Farest point outside: " << convert<Number,double>(farestPointOutside.rawCoordinates()).transpose() << std::endl;

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
				//std::cout << "Current Point: " << convert<Number,double>(current.rawCoordinates()).transpose() << std::endl;
				// create and test neighbors
				for(unsigned d = 0; d < dim; ++d ) {
					Point<Number> tmp = current;
					if( hspace.normal()(d) < 0 && current.at(d) == boxcopy.limits().first.at(d) ){
						tmp[d] = boxcopy.limits().second.at(d);
					} else if ( hspace.normal()(d) > 0 && current.at(d) == boxcopy.limits().second.at(d) ) {
						tmp[d] = boxcopy.limits().first.at(d);
					} else if ( hspace.normal()(d) == 0 ) {
						tmp[d] = tmp.at(d) == boxcopy.limits().first.at(d) ? boxcopy.limits().second.at(d) : boxcopy.limits().first.at(d);
					} else {
						// UNSINN!?
						//std::cout << "Could create point " << tmp << ", but is the same as " << current << std::endl;
						assert(tmp == current);
						continue;
					}

					//std::cout << "Created search-point: " << convert<Number,double>(tmp.rawCoordinates()).transpose() << std::endl;
					// if neighbor is new, test is, otherwise skip.
					if(std::find(discoveredPoints.begin(), discoveredPoints.end(), tmp) == discoveredPoints.end()){
						if(!hspace.contains(tmp.rawCoordinates())){
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
							//std::cout << "is inside, intersection point is " << convert<Number,double>(intersectionPoint.rawCoordinates()).transpose() << std::endl;
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
				return BoxT<Number,Converter,Setting>(intersectionPoints);
			} else {
				if(holdsMin){
					intersectionPoints.push_back(boxcopy.limits().first);
				} else {
					intersectionPoints.push_back(boxcopy.limits().second);
				}
				return BoxT<Number,Converter,Setting>(intersectionPoints);
			}
		}
	}
	return Empty(this->dimension());
}

template<typename Number, typename Converter, class Setting>
BoxT<Number,Converter,Setting> BoxT<Number,Converter,Setting>::intersectHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {
	assert(_mat.rows() == _vec.rows());
	assert(_mat.cols() == Eigen::Index(this->dimension()));
	if(_mat.rows() == 0) {
			return *this;
	}
	if(this->empty()) {
		return Empty(this->dimension());
	}

	if(Setting::USE_INTERVAL_ARITHMETIC) {
		std::vector<carl::Interval<Number>> intervals = this->boundaries();
		// Todo: This is a first draft using the function for single halfspaces - maybe we can check more than one plane at the same time.
		for(unsigned planeIndex = 0; planeIndex < _mat.rows(); ++planeIndex) {
			bool empty = icpIntersectHalfspace(intervals,Halfspace<Number>(_mat.row(planeIndex), _vec(planeIndex)));
			if(empty){
				return Empty(this->dimension());
			}
		}
		return BoxT<Number,Converter,Setting>(intervals);
	} else {

		// convert box to a set of constraints, add other halfspaces and evaluate in box main directions to get new intervals.
		std::vector<vector_t<Number>> tpl = computeTemplate<Number>(this->dimension(), 4);
		matrix_t<Number> boxDirections = matrix_t<Number>::Zero(tpl.size(), this->dimension());
		vector_t<Number> boxDistances = vector_t<Number>::Zero(boxDirections.rows());

		// set up matrix.
		// Todo: Can be combined with next loop.
		Eigen::Index i = 0;
		for(const auto& row : tpl) {
			boxDirections.row(i) = row;
			++i;
		}

		// the template has one non-Zero index per row
		for(Eigen::Index rowIndex = 0; rowIndex < boxDirections.rows(); ++rowIndex) {
			for(Eigen::Index colIndex = 0; colIndex < boxDirections.cols(); ++colIndex) {
				if(boxDirections(rowIndex,colIndex) > 0) {
					boxDistances(rowIndex) = mLimits.second.at(colIndex);
					break;
				} else if (boxDirections(rowIndex,colIndex) < 0) {
					boxDistances(rowIndex) = -mLimits.first.at(colIndex);
					break;
				}
			}
		}

		// At this point the constraints for the box are created as a matrix-vector pair.
		// Now add the halfspace constraints in a fresh matrix (we re-use the box template later).
		matrix_t<Number> constraints = matrix_t<Number>(boxDirections.rows() + _mat.rows(), _mat.cols());
		vector_t<Number> constants = vector_t<Number>(boxDistances.rows() + _mat.rows());
		constraints.block(0,0,boxDirections.rows(), boxDirections.cols()) = boxDirections;
		constraints.block(boxDirections.rows(), 0, _mat.rows(), _mat.cols()) = _mat;
		constants.block(0,0,boxDirections.rows(),1) = boxDistances;
		constants.block(boxDirections.rows(),0,_vec.rows(),1) = _vec;

		// evaluate in box directions.
		Optimizer<Number> opt(constraints,constants);
		std::vector<EvaluationResult<Number>> results;
		for(Eigen::Index rowIndex = 0; rowIndex < boxDirections.rows(); ++rowIndex) {
			results.emplace_back(opt.evaluate(boxDirections.row(rowIndex), false));
		}
		opt.cleanGLPInstance();
		assert(Eigen::Index(results.size()) == boxDirections.rows());

		// re-construct box from results.
		std::pair<Point<Number>,Point<Number>> newLimits = std::make_pair(Point<Number>(vector_t<Number>::Zero(this->dimension())), Point<Number>(vector_t<Number>::Zero(this->dimension())));
		for(Eigen::Index rowIndex = 0; rowIndex < boxDirections.rows(); ++rowIndex) {
			for(Eigen::Index colIndex = 0; colIndex < boxDirections.cols(); ++colIndex) {
				if(boxDirections(rowIndex,colIndex) > 0) {
					newLimits.second[colIndex] = results[rowIndex].supportValue;
				} else if (boxDirections(rowIndex,colIndex) < 0) {
					newLimits.first[colIndex] = -results[rowIndex].supportValue;
				}
			}
		}
		BoxT<Number,Converter,Setting> res(newLimits);
		res.reduceNumberRepresentation();
		return res;
	}
}

template<typename Number, typename Converter, class Setting>
bool BoxT<Number,Converter,Setting>::contains( const Point<Number> &point ) const {
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

template<typename Number, typename Converter, class Setting>
bool BoxT<Number,Converter,Setting>::contains( const BoxT<Number,Converter,Setting> &box ) const {
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

template<typename Number, typename Converter, class Setting>
BoxT<Number,Converter,Setting> BoxT<Number,Converter,Setting>::unite( const BoxT<Number,Converter,Setting> &rhs ) const {
	assert( dimension() == rhs.dimension() );
	std::size_t dim = this->dimension();

	std::pair<Point<Number>, Point<Number>> limits(std::make_pair(Point<Number>(vector_t<Number>::Zero(dim)), Point<Number>(vector_t<Number>::Zero(dim))));
	std::pair<Point<Number>, Point<Number>> rhsLimits = rhs.limits();
	for ( std::size_t i = 0; i < dim; ++i ) {
		limits.first[i] = mLimits.first.at(i) < rhsLimits.first.at(i) ? mLimits.first.at(i) : rhsLimits.first.at(i);
		limits.second[i] = mLimits.second.at(i) > rhsLimits.second.at(i) ? mLimits.second.at(i) : rhsLimits.second.at(i);
	}
	return BoxT<Number,Converter,Setting>(limits);
}

template<typename Number, typename Converter, class Setting>
BoxT<Number,Converter,Setting> BoxT<Number,Converter,Setting>::unite( const std::vector<BoxT<Number,Converter,Setting>>& boxes ) {
	if(boxes.empty()) {
		return BoxT<Number,Converter,Setting>::Empty();
	}

	std::pair<Point<Number>, Point<Number>> newLimits = boxes.begin()->limits();
	for(const auto& box : boxes) {
		newLimits.first = coeffWiseMin(newLimits.first, box.limits().first);
		newLimits.second = coeffWiseMax(newLimits.first, box.limits().second);
	}
	return BoxT<Number,Converter,Setting>(newLimits);
}

template<typename Number, typename Converter, class Setting>
void BoxT<Number,Converter,Setting>::clear() {
	*this = BoxT<Number,Converter,Setting>::Empty(0);
}

template<typename Number, typename Converter, class Setting>
void BoxT<Number,Converter,Setting>::print() const {
	//std::cout << *this << std::endl;
}

}  // namespace hypro
