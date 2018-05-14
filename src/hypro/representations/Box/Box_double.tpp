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

	template<typename Converter, class Setting>
	BoxT<double,Converter,Setting>::BoxT( const std::vector<carl::Interval<double>>& _intervals )
	{
		if(!_intervals.empty()) {
			vector_t<double> lower = vector_t<double>(_intervals.size());
			vector_t<double> upper = vector_t<double>(_intervals.size());
			for (std::size_t dim = 0; dim < _intervals.size(); ++dim) {
				lower(Eigen::Index(dim)) = _intervals.at(dim).lower();
				upper(Eigen::Index(dim)) = _intervals.at(dim).upper();
			}
			mLimits = std::make_pair(Point<double>(lower), Point<double>(upper));
		}
	}

	template<typename Converter, class Setting>
	BoxT<double,Converter,Setting>::BoxT( const matrix_t<double>& _constraints, const vector_t<double>& _constants )
	{
		assert(_constraints.rows() == _constants.rows());
		if(_constraints.rows() == 0) {
			assert(this->empty());
			assert(this->dimension() == 0);
			return;
		}

		Optimizer<double> opt(_constraints, _constants);

		vector_t<double> posDir = vector_t<double>::Ones(_constraints.cols());

		EvaluationResult<double> posPoint = opt.evaluate(posDir, false);
		EvaluationResult<double> negPoint = opt.evaluate(-posDir, false);

		opt.cleanGLPInstance();

		if(posPoint.errorCode == SOLUTION::INFEAS) {
			*this = Empty(_constraints.cols());
		}

		mLimits.first = negPoint.optimumValue;
		mLimits.second = posPoint.optimumValue;

		/*
		//std::cout << __func__ << ": matrix: " << _constraints << ", vector: " << _constants << std::endl;
		// calculate all possible Halfspace intersections -> TODO: dPermutation can
		// be improved.
		assert(_constraints.rows() == _constants.rows());
		Permutator permutator = Permutator( _constraints.rows(), _constraints.cols() );
		matrix_t<double> intersection = matrix_t<double>( _constraints.cols(), _constraints.cols() );
		vector_t<double> intersectionConstants = vector_t<double>( _constraints.cols() );
		std::set<vector_t<double>> possibleVertices;
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
			Eigen::FullPivLU<matrix_t<double>> luDecomposition = intersection.fullPivLu();
			if ( luDecomposition.rank() == intersection.cols() ) {
				vector_t<double> vertex = luDecomposition.solve( intersectionConstants );
				assert(vertex.rows() == _constraints.cols());
				possibleVertices.emplace( std::move(vertex) );
				//std::cout<< "Vertex computed: " << convert<double,double>(vertex).transpose() << std::endl;
			}
		}
		assert(!possibleVertices.empty());

		// check if vertices are true vertices (i.e. they fulfill all constraints)
		for ( auto vertex = possibleVertices.begin(); vertex != possibleVertices.end(); ) {
			//std::cout  << "Refinement: Consider vertex : " << convert<double,double>(*vertex).transpose() << std::endl;
			// possibleVertices.size() << std::endl;
			bool deleted = false;
			for ( unsigned rowIndex = 0; rowIndex < _constraints.rows(); ++rowIndex ) {
				double res = vertex->dot( _constraints.row( rowIndex ) );
				if ( !carl::AlmostEqual2sComplement(res, _constants( rowIndex ), 128) && res > _constants( rowIndex ) ) {
					vertex = possibleVertices.erase( vertex );
					deleted = true;
					//std::cout << "Deleted because of row " << convert<double,double>(vector_t<double>(_constraints.row(rowIndex))) << std::endl;
					//std::cout << "Res was " << res << " and the constant is " << _constants(rowIndex) << std::endl;
					break;
				}
			}
			if(!deleted) {
				++vertex;
			}
		}
		//std::cout<<__func__ << " : " <<__LINE__ <<std::endl;
		// finish initialization
		if(possibleVertices.empty()) {
			assert(false);
			*this = BoxT<double,Converter,Setting>::Empty();
		} else {
			vector_t<double> min = *possibleVertices.begin();
			vector_t<double> max = *possibleVertices.begin();
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
			mLimits = std::make_pair(Point<double>(min), Point<double>(max));
		}
		*/
	}

template<typename Converter, class Setting>
BoxT<double,Converter,Setting>::BoxT( const std::set<Point<double>> &_points ) {
	if ( !_points.empty() ) {
		vector_t<double> lower = _points.begin()->rawCoordinates();
		vector_t<double> upper = _points.begin()->rawCoordinates();
		for(const auto& point : _points) {
			for(std::size_t d = 0; d < point.dimension(); ++d){
				if(point.at(d) < lower(Eigen::Index(d))) {
					lower(Eigen::Index(d)) = point.at(d);
				}

				if(point.at(d) > upper(Eigen::Index(d))) {
					upper(Eigen::Index(d)) = point.at(d);
				}
			}
		}
		mLimits = std::make_pair(Point<double>(lower), Point<double>(upper));
	}
}

template<typename Converter, class Setting>
BoxT<double,Converter,Setting>::BoxT( const std::vector<Point<double>> &_points ) {
	if ( !_points.empty() ) {
		vector_t<double> lower = _points.begin()->rawCoordinates();
		vector_t<double> upper = _points.begin()->rawCoordinates();
		for(const auto& point : _points) {
			for(std::size_t d = 0; d < point.dimension(); ++d){
				if(point.at(d) < lower(Eigen::Index(d))) {
					lower(Eigen::Index(d)) = point.at(d);
				}

				if(point.at(d) > upper(Eigen::Index(d))) {
					upper(Eigen::Index(d)) = point.at(d);
				}
			}
		}
		mLimits = std::make_pair(Point<double>(lower), Point<double>(upper));
	}
}

template<typename Converter, class Setting>
std::vector<carl::Interval<double>> BoxT<double,Converter,Setting>::boundaries() const {
	std::vector<carl::Interval<double>> result;
	result.reserve(this->dimension());

	for(std::size_t d = 0; d < this->dimension(); ++d) {
		result.push_back(carl::Interval<double>(mLimits.first.at(d), mLimits.second.at(d)));
	}

	return result;
}

template<typename Converter, class Setting>
matrix_t<double> BoxT<double,Converter,Setting>::matrix() const {
	matrix_t<double> res = matrix_t<double>::Zero(2*mLimits.first.dimension(), mLimits.first.dimension());
	for(unsigned i = 0; i < mLimits.first.dimension(); ++i) {
		res(2*i,i) = 1;
		res(2*i+1,i) = -1;
	}
	return res;
}

template<typename Converter, class Setting>
vector_t<double> BoxT<double,Converter,Setting>::vector() const {
	vector_t<double> res = vector_t<double>::Zero(2*mLimits.first.dimension());
	for(unsigned i = 0; i < mLimits.first.dimension(); ++i) {
		res(2*i) = mLimits.second.at(i);
		res(2*i+1) = -mLimits.first.at(i);
	}
	return res;
}

template<typename Converter, class Setting>
std::vector<Halfspace<double>> BoxT<double,Converter,Setting>::constraints() const {
	std::vector<Halfspace<double>> res;
	if(this->dimension() != 0) {
		std::size_t dim = this->dimension();
		res.reserve(2*dim);
		for( std::size_t d = 0; d < dim; ++d) {
			vector_t<double> low = vector_t<double>::Zero(Eigen::Index(dim));
			low(Eigen::Index(d)) = -1;
			vector_t<double> up = vector_t<double>::Zero(Eigen::Index(dim));
			up(Eigen::Index(d)) = 1;
			double lOff = -mLimits.first.at(d);
			double uOff = mLimits.second.at(d);
			res.emplace_back(low, lOff);
			res.emplace_back(up, uOff);
		}
	}
	return res;
}

template<typename Converter, class Setting>
carl::Interval<double> BoxT<double,Converter,Setting>::interval( std::size_t d ) const {
	if ( d >= mLimits.first.dimension() ) {
		return carl::Interval<double>::emptyInterval();
	}
	return carl::Interval<double>(mLimits.first.at(d), mLimits.second.at(d));
}

template<typename Converter, class Setting>
double BoxT<double,Converter,Setting>::supremum() const {
	double max = 0;
	for ( auto &point : this->vertices() ) {
		double inftyNorm = Point<double>::inftyNorm( point );
		max = max > inftyNorm ? max : inftyNorm;
	}
	return max;
}

template<typename Converter, class Setting>
std::vector<Point<double>> BoxT<double,Converter,Setting>::vertices( const matrix_t<double>& ) const {
	std::vector<Point<double>> result;
	std::size_t limit = std::size_t(pow( 2, mLimits.first.dimension() ));

	for ( std::size_t bitCount = 0; bitCount < limit; ++bitCount ) {
		vector_t<double> coord = vector_t<double>( dimension() );
		for ( std::size_t dimension = 0; dimension < this->dimension(); ++dimension ) {
			std::size_t pos = ( 1 << dimension );
			if ( bitCount & pos ) {
				coord( dimension ) = mLimits.second.at(dimension);
			} else {
				coord( dimension ) = mLimits.first.at(dimension);
			}
		}
		result.push_back( Point<double>( coord ) );
	}
	return result;
}

template<typename Converter, class Setting>
std::size_t BoxT<double,Converter,Setting>::size() const {
	if(this->empty()) {
		return 0;
	}
	// TODO: What is this supposed to do???
	return 2;
}

template<typename Converter, class Setting>
BoxT<double,Converter,Setting> BoxT<double,Converter,Setting>::makeSymmetric() const {
	Point<double> limit = mLimits.first;
	for(unsigned d = 0; d < mLimits.first.dimension(); ++d) {
		limit[d] = carl::abs(mLimits.first.at(d)) >= carl::abs(mLimits.second.at(d)) ? carl::abs(mLimits.first.at(d)) : carl::abs(mLimits.second.at(d));
	}
	return BoxT<double,Converter,Setting>(std::make_pair(-limit, limit));
}

template<typename Converter, class Setting>
std::pair<CONTAINMENT, BoxT<double,Converter,Setting>> BoxT<double,Converter,Setting>::satisfiesHalfspace( const Halfspace<double>& rhs ) const {
	std::vector<Point<double>> vertices = this->vertices();
	bool allVerticesContained = true;
	unsigned outsideVertexCnt = 0;
	for(const auto& vertex : vertices) {
		if(!carl::AlmostEqual2sComplement(vertex.rawCoordinates().dot(rhs.normal()), rhs.offset(), 128) && vertex.rawCoordinates().dot(rhs.normal()) > rhs.offset()){
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

template<typename Converter, class Setting>
std::pair<CONTAINMENT, BoxT<double,Converter,Setting>> BoxT<double,Converter,Setting>::satisfiesHalfspaces( const matrix_t<double>& _mat, const vector_t<double>& _vec ) const {
	if(_mat.rows() == 0) {
		return std::make_pair(CONTAINMENT::FULL, *this);
	}

	if(this->empty()) {
		return std::make_pair(CONTAINMENT::NO, *this);
	}

	//std::cout << __func__ << " This: " << convert<double,double>(*this) << std::endl;
	//std::cout << __func__ << ": input matrix: " << convert<double,double>(_mat) << std::endl << "input vector: " << convert<double,double>(_vec) << std::endl;
	//std::cout << __func__ << ": This->dimension() = " << this->dimension() << std::endl;
	assert(this->dimension() == unsigned(_mat.cols()));
	std::vector<unsigned> limitingPlanes;

	// For a rough estimate, insert box intervals into normal and check, whether the box is fully, partially or not contained.
	for(unsigned rowIndex = 0; rowIndex < _mat.rows(); ++rowIndex) {
		carl::Interval<double> evaluatedBox = carl::Interval<double>(0);
		for(unsigned d = 0; d < _mat.cols(); ++d){
			evaluatedBox += carl::Interval<double>(mLimits.first.at(d), mLimits.second.at(d)) * double(_mat(rowIndex,d));
		}

		//std::cout << __func__ << " Row: " << convert<double,double>(_mat.row(rowIndex)) << std::endl;
		//std::cout << __func__ << " Evaluated box: " << evaluatedBox << std::endl;
		//std::cout << __func__ << " Distance: " << carl::convert<double,double>(_vec(rowIndex)) << std::endl;

		//if( !carl::AlmostEqual2sComplement(evaluatedBox.lower(), _vec(rowIndex), 128) && evaluatedBox.lower() > _vec(rowIndex)){
		if( evaluatedBox.lower() > _vec(rowIndex)){
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
	matrix_t<double> newPlanes = matrix_t<double>(limitingPlanes.size(), _mat.cols());
	vector_t<double> newDistances = vector_t<double>(limitingPlanes.size());
	Eigen::Index rowPos = newPlanes.rows()-1;
	while(!limitingPlanes.empty()){
		assert(rowPos >= 0);
		newPlanes.row(rowPos) = _mat.row(limitingPlanes.back());
		newDistances(rowPos) = _vec(limitingPlanes.back());
		--rowPos;
		limitingPlanes.pop_back();
	}
	assert(newPlanes.rows() == newDistances.rows());
	BoxT<double,Converter,Setting> tmpBox = this->intersectHalfspaces(newPlanes,newDistances);
	// Todo-check: For rational numbers this assertion holds, what about native doubles?
	//assert(!tmpBox.empty());
	//std::cout << __func__ << " TRUE, " << convert<double,double>(tmpBox) << std::endl;
	return std::make_pair(CONTAINMENT::PARTIAL, tmpBox);
}

template<typename Converter, class Setting>
BoxT<double,Converter,Setting> BoxT<double,Converter,Setting>::project(const std::vector<std::size_t>& dimensions) const {
	if(dimensions.empty()) {
		return Empty();
	}
	return BoxT<double,Converter,Setting>(std::make_pair(mLimits.first.project(dimensions), mLimits.second.project(dimensions)));
}

template<typename Converter, class Setting>
BoxT<double,Converter,Setting> BoxT<double,Converter,Setting>::linearTransformation( const matrix_t<double> &A ) const {
	if(this->empty()) {
		return *this;
	}
	// create both limit matrices
	// std::cout << __func__ << ": This: " << *this << std::endl;
	// std::cout << __func__ << ": Matrix" <<  std::endl << A << std::endl << "Vector" << std::endl << b << std::endl;
	//matrix_t<double> ax(A);
	//matrix_t<double> bx(A);
	Point<double> min;
	Point<double> max;

	for (std::size_t k = 0; k < std::size_t(A.rows()); ++k) {
		for (std::size_t j = 0; j < std::size_t(A.cols()); ++j) {
			double a = mLimits.first.at(j)*A(Eigen::Index(k),Eigen::Index(j));
			double b = mLimits.second.at(j)*A(Eigen::Index(k),Eigen::Index(j));
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
	BoxT<double,Converter,Setting> res = BoxT<double,Converter,Setting>( std::make_pair(min, max) );
	//assert(res.contains(Point<double>(A*mLimits.first.rawCoordinates())));
	//assert(res.contains(Point<double>(A*mLimits.second.rawCoordinates())));
	return res;
}

template<typename Converter, class Setting>
BoxT<double,Converter,Setting> BoxT<double,Converter,Setting>::affineTransformation( const matrix_t<double> &A, const vector_t<double> &b ) const {
	if(!this->empty()){
		TRACE("hypro.representations.box","This: " << *this << ", A: " << A << "b: " << b);
		BoxT<double,Converter,Setting> res = this->linearTransformation(A);
		TRACE("hypro.representations.box","Result of linear trafo: " << res);
		return BoxT<double,Converter,Setting>( std::make_pair(res.min()+b, res.max()+b) );
	}
	return *this;
}

template<typename Converter, class Setting>
BoxT<double,Converter,Setting> BoxT<double,Converter,Setting>::minkowskiSum( const BoxT<double,Converter,Setting> &rhs ) const {
	assert( dimension() == rhs.dimension() );
	return BoxT<double,Converter,Setting>(std::make_pair(mLimits.first + rhs.min(), mLimits.second + rhs.max()));
}

template<typename Converter, class Setting>
BoxT<double,Converter,Setting> BoxT<double,Converter,Setting>::minkowskiDecomposition( const BoxT<double,Converter,Setting>& rhs ) const {
	if(rhs.empty()) {
		return *this;
	}
	TRACE("hypro.representations.box","This: " << *this << ", Rhs: " << rhs);
	assert( dimension() == rhs.dimension() );
	// assert( std::mismatch(this->boundaries().begin(), this->boundaries.end(), rhs.boundaries().begin(), rhs.boundaries.end(), [&](a,b) -> bool {return a.diameter() >= b.diameter()}  ) ); // TODO: wait for c++14 support
	// assert( (BoxT<double,Converter,Setting>(std::make_pair(mLimits.first - rhs.min(), mLimits.second - rhs.max())).minkowskiSum(rhs) == *this) );
	return BoxT<double,Converter,Setting>(std::make_pair(mLimits.first - rhs.min(), mLimits.second - rhs.max()));
}

template<typename Converter, class Setting>
BoxT<double,Converter,Setting> BoxT<double,Converter,Setting>::intersect( const BoxT<double,Converter,Setting> &rhs ) const {
	std::size_t dim = rhs.dimension() < this->dimension() ? rhs.dimension() : this->dimension();
	std::pair<Point<double>, Point<double>> limits(std::make_pair(Point<double>(vector_t<double>::Zero(Eigen::Index(dim))), Point<double>(vector_t<double>::Zero(Eigen::Index(dim)))));
	std::pair<Point<double>, Point<double>> rhsLimits = rhs.limits();
	for ( std::size_t i = 0; i < dim; ++i ) {
		limits.first[i] = mLimits.first.at(i) > rhsLimits.first.at(i) ? mLimits.first.at(i) : rhsLimits.first.at(i);
		limits.second[i] = mLimits.second.at(i) < rhsLimits.second.at(i) ? mLimits.second.at(i) : rhsLimits.second.at(i);
	}
	return BoxT<double,Converter,Setting>(limits);
}

template<typename Converter, class Setting>
BoxT<double,Converter,Setting> BoxT<double,Converter,Setting>::intersectHalfspace( const Halfspace<double>& hspace ) const {
	//std::cout << __func__ << " of " << *this << " and " << hspace << std::endl;
	if(!this->empty()) {
		if(Setting::USE_INTERVAL_ARITHMETIC) {
			std::vector<carl::Interval<double>> intervals = this->boundaries();
			bool empty = icpIntersectHalfspace(intervals,hspace);
			if(empty) {
				return Empty(this->dimension());
			}
			return BoxT<double,Converter,Setting>(intervals);
		} else {
			BoxT<double,Converter,Setting> copyBox(*this);
			// Preprocessing: If any two points opposite to each other are contained, the box stays the same - test limit points
			bool holdsMin = hspace.contains(mLimits.first.rawCoordinates());
			bool holdsMax = hspace.contains(mLimits.second.rawCoordinates());
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
					copyBox.rLimits().second[nonZeroDim] = hspace.offset() / hspace.normal()(nonZeroDim);
				} else {
					copyBox.rLimits().first[nonZeroDim] = hspace.offset() / hspace.normal()(nonZeroDim);
				}
				return copyBox;
			}

			//std::cout << __func__ << " Min below: " << holdsMin << ", Max below: " << holdsMax << std::endl;
			std::size_t dim = this->dimension();

			// Phase 1: Find starting point (point outside) for phase 2 by depth-first search or use limit points, if applicable
			Point<double> farestPointOutside = copyBox.limits().first;
			Point<double> farestPointInside = copyBox.limits().first;
			std::size_t usedDimension = 0;
			// determine walk direction by using plane normal and variable order
			for(; usedDimension < dim; ++usedDimension){
				if(hspace.normal()(Eigen::Index(usedDimension)) > 0){
					if(farestPointOutside.at(usedDimension) != copyBox.limits().second.at(usedDimension)) {
						farestPointOutside[usedDimension] = copyBox.limits().second.at(usedDimension);
					}
					if(farestPointInside.at(usedDimension) != copyBox.limits().first.at(usedDimension)) {
						farestPointInside[usedDimension] = copyBox.limits().first.at(usedDimension);
					}
				} else if( hspace.normal()(Eigen::Index(usedDimension)) < 0){
					if( farestPointOutside.at(usedDimension) != copyBox.limits().first.at(usedDimension) ) {
						farestPointOutside[usedDimension] = copyBox.limits().first.at(usedDimension);
					}
					if(farestPointInside.at(usedDimension) != copyBox.limits().second.at(usedDimension)) {
						farestPointInside[usedDimension] = copyBox.limits().second.at(usedDimension);
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
				return BoxT<double,Converter,Setting>::Empty();
			}

			//std::cout << __func__ << " Farest point outside: " << convert<double,double>(farestPointOutside.rawCoordinates()).transpose() << std::endl;

			// at this point farestPointOutside is outside and farestPointInside is inside - the plane intersects the box somehow.
			std::vector<Point<double>> discoveredPoints;
			std::vector<Point<double>> intersectionPoints;
			std::queue<Point<double>> workingQueue;
			workingQueue.push(farestPointOutside);

			// BFS search of points outside and intersection points.
			//std::cout << __func__ << " Start BFS search." << std::endl;
			while(!workingQueue.empty()){
				//std::cout << "Queue size: " << workingQueue.size() << std::endl;
				Point<double> current = workingQueue.front();
				workingQueue.pop();
				//std::cout << "Current Point: " << convert<double,double>(current.rawCoordinates()).transpose() << std::endl;
				// create and test neighbors
				for(unsigned d = 0; d < dim; ++d ) {
					Point<double> tmp = current;
					if( hspace.normal()(d) < 0 && current.at(d) == copyBox.limits().first.at(d) ){
						tmp[d] = copyBox.limits().second.at(d);
					} else if ( hspace.normal()(d) > 0 && current.at(d) == copyBox.limits().second.at(d) ) {
						tmp[d] = copyBox.limits().first.at(d);
					} else if ( hspace.normal()(d) == 0 ) {
						tmp[d] = tmp.at(d) == copyBox.limits().first.at(d) ? copyBox.limits().second.at(d) : copyBox.limits().first.at(d);
					} else {
						// UNSINN!?
						//std::cout << "Could create point " << tmp << ", but is the same as " << current << std::endl;
						assert(tmp == current);
						continue;
					}

					//std::cout << "Created search-point: " << convert<double,double>(tmp.rawCoordinates()).transpose() << std::endl;
					// if neighbor is new, test is, otherwise skip.
					if(std::find(discoveredPoints.begin(), discoveredPoints.end(), tmp) == discoveredPoints.end()){
						if(!hspace.contains(tmp.rawCoordinates())){
							//std::cout << "is also outside, enqueue." << std::endl;
							workingQueue.push(tmp);
						} else {
							double dCoord = 0;
							for(unsigned i = 0; i < dim; ++i){
								if( i != d ) {
									dCoord += hspace.normal()(i) * current.at(i);
								}
							}
							dCoord -= hspace.offset();
							dCoord /= -hspace.normal()(d);
							Point<double> intersectionPoint = tmp;
							intersectionPoint[d] = dCoord;
							//std::cout << "is inside, intersection point is " << convert<double,double>(intersectionPoint.rawCoordinates()).transpose() << std::endl;
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
				return BoxT<double,Converter,Setting>(intersectionPoints);
			} else {
				if(holdsMin){
					intersectionPoints.push_back(copyBox.limits().first);
				} else {
					intersectionPoints.push_back(copyBox.limits().second);
				}
				//std::cout << __func__ << " Intersection points:" << std::endl;
				//for(const auto& point : intersectionPoints) {
				//	std::cout << convert<double,double>(point.rawCoordinates()).transpose() << std::endl;
				//}
				return BoxT<double,Converter,Setting>(intersectionPoints);
			}
		}
	}
	return Empty(this->dimension());
}

template<typename Converter, class Setting>
BoxT<double,Converter,Setting> BoxT<double,Converter,Setting>::intersectHalfspaces( const matrix_t<double>& _mat, const vector_t<double>& _vec ) const {
	TRACE("hypro.representations", "Halfspaces: " << _mat << " and vector: " << _vec );
	assert(_mat.rows() == _vec.rows());
	assert(_mat.cols() == Eigen::Index(this->dimension()));
	if(Setting::USE_INTERVAL_ARITHMETIC) {
		std::vector<carl::Interval<double>> intervals = this->boundaries();
		// Todo: This is a first draft using the function for single halfspaces - maybe we can check more than one plane at the same time.
		for(unsigned planeIndex = 0; planeIndex < _mat.rows(); ++planeIndex) {
			bool empty = icpIntersectHalfspace(intervals,Halfspace<double>(_mat.row(planeIndex), _vec(planeIndex)));
			if(empty){
				return Empty(this->dimension());
			}
		}
		return BoxT<double,Converter,Setting>(intervals);
	} else if(Setting::HYPRO_BOX_AVOID_LINEAR_OPTIMIZATION){
		if(_mat.rows() == 0) {
			return *this;
		}
		if(!this->empty()) {
			BoxT<double,Converter,Setting> result = *this;
			// Todo: This is a first draft using the function for single halfspaces - maybe we can check more than one plane at the same time.
			for(unsigned planeIndex = 0; planeIndex < _mat.rows(); ++planeIndex) {
				result = result.intersectHalfspace(Halfspace<double>(_mat.row(planeIndex), _vec(planeIndex)));
				if(result.empty()){
					break;
				}
			}
			return result;
		}
		return Empty(this->dimension());
	} else {

		// convert box to a set of constraints, add other halfspaces and evaluate in box main directions to get new intervals.
		std::vector<vector_t<double>> tpl = computeTemplate<double>(this->dimension(), 4);
		matrix_t<double> boxDirections = matrix_t<double>::Zero(tpl.size(), this->dimension());
		vector_t<double> boxDistances = vector_t<double>::Zero(boxDirections.rows());

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
		matrix_t<double> constraints = matrix_t<double>(boxDirections.rows() + _mat.rows(), _mat.cols());
		vector_t<double> constants = vector_t<double>(boxDistances.rows() + _mat.rows());
		constraints.block(0,0,boxDirections.rows(), boxDirections.cols()) = boxDirections;
		constraints.block(boxDirections.rows(), 0, _mat.rows(), _mat.cols()) = _mat;
		constants.block(0,0,boxDirections.rows(),1) = boxDistances;
		constants.block(boxDirections.rows(),0,_vec.rows(),1) = _vec;

		// evaluate in box directions.
		Optimizer<double> opt(constraints,constants);
		std::vector<EvaluationResult<double>> results;
		TRACE("hypro.representations.box","Multiple calls to evaluate.");
		for(Eigen::Index rowIndex = 0; rowIndex < boxDirections.rows(); ++rowIndex) {
			results.emplace_back(opt.evaluate(boxDirections.row(rowIndex), false));
		}
		TRACE("hypro.representations.box","Multiple calls to evaluate - Done.");
		assert(Eigen::Index(results.size()) == boxDirections.rows());
		TRACE("hypro.representations.box","Call to clean opt.");
		opt.cleanGLPInstance();

		// re-construct box from results.
		std::pair<Point<double>,Point<double>> newLimits = std::make_pair(Point<double>(vector_t<double>::Zero(this->dimension())), Point<double>(vector_t<double>::Zero(this->dimension())));
		for(Eigen::Index rowIndex = 0; rowIndex < boxDirections.rows(); ++rowIndex) {
			//assert(boxDirections.row(rowIndex).nonZeros() == Eigen::Index(1));
			for(Eigen::Index colIndex = 0; colIndex < boxDirections.cols(); ++colIndex) {
				if(boxDirections(rowIndex,colIndex) > 0) {
					newLimits.second[colIndex] = results[rowIndex].supportValue;
				} else if (boxDirections(rowIndex,colIndex) < 0) {
					newLimits.first[colIndex] = -results[rowIndex].supportValue;
				}
			}
		}
		return BoxT<double,Converter,Setting>(newLimits);
	}
}

template<typename Converter, class Setting>
bool BoxT<double,Converter,Setting>::contains( const Point<double> &point ) const {
	if ( this->dimension() > point.dimension() ) {
		return false;
	}

	for(unsigned d = 0; d < this->dimension(); ++d) {
		if( !carl::AlmostEqual2sComplement(mLimits.first.at(d),point.at(d), 128) && mLimits.first.at(d) > point.at(d))
			return false;
		if( !carl::AlmostEqual2sComplement(mLimits.first.at(d),point.at(d), 128) && mLimits.second.at(d) < point.at(d))
			return false;
	}
	return true;
}

template<typename Converter, class Setting>
bool BoxT<double,Converter,Setting>::contains( const BoxT<double,Converter,Setting> &box ) const {
	if ( this->dimension() != box.dimension() ) {
		return false;
	}

	for(unsigned d = 0; d < this->dimension(); ++d) {
		if(!carl::AlmostEqual2sComplement(mLimits.first.at(d),box.min().at(d), 128) && mLimits.first.at(d) > box.min().at(d))
			return false;
		if(!carl::AlmostEqual2sComplement(mLimits.first.at(d),box.max().at(d), 128) && mLimits.second.at(d) < box.max().at(d))
			return false;
	}
	return true;
}

template<typename Converter, class Setting>
BoxT<double,Converter,Setting> BoxT<double,Converter,Setting>::unite( const BoxT<double,Converter,Setting> &rhs ) const {
	assert( dimension() == rhs.dimension() );
	std::size_t dim = this->dimension();

	std::pair<Point<double>, Point<double>> limits(std::make_pair(Point<double>(vector_t<double>::Zero(Eigen::Index(dim))), Point<double>(vector_t<double>::Zero(Eigen::Index(dim)))));
	std::pair<Point<double>, Point<double>> rhsLimits = rhs.limits();
	for ( std::size_t i = 0; i < dim; ++i ) {
		limits.first[i] = mLimits.first.at(i) < rhsLimits.first.at(i) ? mLimits.first.at(i) : rhsLimits.first.at(i);
		limits.second[i] = mLimits.second.at(i) > rhsLimits.second.at(i) ? mLimits.second.at(i) : rhsLimits.second.at(i);
	}
	return BoxT<double,Converter,Setting>(limits);
}

template<typename Converter, class Setting>
BoxT<double,Converter,Setting> BoxT<double,Converter,Setting>::unite( const std::vector<BoxT<double,Converter,Setting>>& boxes ) {
	if(boxes.empty()) {
		return BoxT<double,Converter,Setting>::Empty();
	}

	std::pair<Point<double>, Point<double>> newLimits = boxes.begin()->limits();
	for(const auto& box : boxes) {
		newLimits.first = coeffWiseMin(newLimits.first, box.limits().first);
		newLimits.second = coeffWiseMax(newLimits.first, box.limits().second);
	}
	return BoxT<double,Converter,Setting>(newLimits);
}

template<typename Converter, class Setting>
void BoxT<double,Converter,Setting>::clear() {
	*this = BoxT<double,Converter,Setting>::Empty(0);
}

template<typename Converter, class Setting>
void BoxT<double,Converter,Setting>::print() const {
	std::cout << *this << std::endl;
}

}  // namespace hypro
