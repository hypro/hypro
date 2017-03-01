#include "HPolytope.h"

namespace hypro {
template <typename Number, typename Converter>
HPolytopeT<Number, Converter>::HPolytopeT()
	: mHPlanes(), mDimension( 0 ), mEmpty(TRIBOOL::NSET), mNonRedundant(true) {
}

template <typename Number, typename Converter>
HPolytopeT<Number, Converter>::HPolytopeT( const HalfspaceVector &planes )
	: mHPlanes(), mDimension( 0 ), mEmpty(TRIBOOL::NSET), mNonRedundant(false) {
	//std::cout << __func__ << ": construct from planes." << std::endl;
	if ( !planes.empty() ) {
		mDimension = planes.begin()->dimension();
		for ( const auto &plane : planes ) {
			mHPlanes.push_back( plane );
		}
		#ifndef NDEBUG
		bool empty = this->empty();
		#endif
		reduceNumberRepresentation();
		assert( empty == this->empty() );
	}
}

template <typename Number, typename Converter>
HPolytopeT<Number, Converter>::HPolytopeT( const matrix_t<Number> &A, const vector_t<Number> &b )
	: mHPlanes(), mDimension( A.cols() ), mEmpty(TRIBOOL::NSET), mNonRedundant(false) {
	TRACE("hypro.hPolytope","construct from Ax <= b," << std::endl  << "A: " << A << "b: " <<b);
	assert( A.rows() == b.rows() );
	for ( unsigned i = 0; i < A.rows(); ++i ) {
		mHPlanes.emplace_back( A.row( i ), b( i ) );
	}
	#ifndef NDEBUG
	bool empty = this->empty();
	#endif
	reduceNumberRepresentation();
	assert( empty == this->empty() );
}

template <typename Number, typename Converter>
HPolytopeT<Number, Converter>::HPolytopeT( const matrix_t<Number> &A )
	: mHPlanes(), mDimension( A.cols() ), mEmpty(TRIBOOL::NSET), mNonRedundant(false) {
	for ( unsigned i = 0; i < A.rows(); ++i ) {
		mHPlanes.push_back( Halfspace<Number>( A.row( i ), Number( 0 ) ) );
	}
}

template <typename Number, typename Converter>
HPolytopeT<Number, Converter>::HPolytopeT( const std::vector<Point<Number>>& points )
	: mHPlanes(), mDimension( 0 ), mEmpty(TRIBOOL::NSET), mNonRedundant(true) {
	TRACE("hypro.hPolytope","Construct from vertices: ");
	for(const auto& vertex : points) {
		TRACE("hypro.hPolytope", vertex);
	}
	/*
	if ( !points.empty() ) {
		mDimension = points.begin()->dimension();
		ConvexHull<Number> ch(points);
		ch.convexHullVertices();
		mHPlanes = ch.getHsv();
		//std::cout << "After CH there are " << mHPlanes.size() << " new hplanes." << std::endl;
		assert(ch.getCone().empty());
		assert(ch.getLinealtySpace().empty());

		//std::cout << "Object constructed from vertices: " << *this << std::endl;
		//std::cout << "Vertices: " << std::endl;
		//for(const auto& vertex : points) {
		//	std::cout << vertex << std::endl;
		//}
	}
	*/

	if ( !points.empty() ) {
		mDimension = points.begin()->dimension();
		// check affine independence - verify object dimension.
		std::vector<vector_t<Number>> coordinates;
		for(const auto& vertex : points){
			coordinates.emplace_back(vertex.rawCoordinates());
		}
		int effectiveDim = effectiveDimension(coordinates);
		assert(effectiveDim >= 0);

		// For debugging
		//std::cout << "effectiveDimension: " << effectiveDim << std::endl;
		//if(effectiveDim < mDimension){
		//	std::vector<Halfspace<Number>> boxConstraints = computeOrientedBox(points);
		//	HPolytopeT<Number,Converter> tmp(boxConstraints);
		//	std::cout << "Theoretical oriented Box: " << tmp << std::endl;
		//}

		// End for debugging

		mEmpty = TRIBOOL::FALSE;
		//if ( points.size() <= mDimension ) {
		if ( unsigned(effectiveDim) < mDimension ) {
			PrincipalComponentAnalysis<Number> pca(points);
			std::vector<Halfspace<Number>> boxConstraints = pca.box();
			for(const auto& constraint : boxConstraints){
				mHPlanes.emplace_back(constraint);
			}

			// Alternative version
			// We need a copy of the set of points since auxiliary points will be added
			//std::vector<Point<Number>> auxiliaryPoints(points);
			//mHPlanes = computeConstraintsForDegeneratedPolytope(auxiliaryPoints, mDimension - effectiveDim);


		} else {
			/*
			ConvexHull<Number> ch(points);
			ch.convexHullVertices();
			mHPlanes = ch.getHsv();
			*/

			std::vector<std::shared_ptr<Facet<Number>>> facets = convexHull( points ).first;
			for ( auto &facet : facets ) {
				assert(facet->halfspace().contains(points));
				mHPlanes.push_back( facet->halfspace() );
			}
			facets.clear();

		}
	}

}

template <typename Number, typename Converter>
HPolytopeT<Number, Converter>::~HPolytopeT() {
}

/*
 * Getters and setters
 */

template <typename Number, typename Converter>
bool HPolytopeT<Number, Converter>::empty() const {
	TRACE("hypro.hPolytope",__func__);
	if(mEmpty == TRIBOOL::TRUE){
		TRACE("hypro.hPolytope","Already set to true.");
		return true;
	}
	if(mEmpty == TRIBOOL::FALSE){
		TRACE("hypro.hPolytope","Already set to false.");
		return false;
	}

	if(mHPlanes.empty()){
		TRACE("hypro.hPolytope","Polytope is universe.");
		mEmpty = TRIBOOL::FALSE;
		return false;
	}

	TRACE("hypro.hPolytope","Call to Optimizer.");

	Optimizer<Number> opt;
	opt.setMatrix(this->matrix());
	opt.setVector(this->vector());

	bool res = !opt.checkConsistency();
	mEmpty = (res == true ? TRIBOOL::TRUE : TRIBOOL::FALSE);
	TRACE("hypro.hPolytope","Optimizer result: " << res);
	return res;
}

template <typename Number, typename Converter>
HPolytopeT<Number, Converter> HPolytopeT<Number, Converter>::Empty(){
	Halfspace<Number> a({Number(1)},Number(-1));
	Halfspace<Number> b({Number(-1)},Number(-1));
	HalfspaceVector v;
	v.emplace_back(a);
	v.emplace_back(b);
	HPolytopeT<Number, Converter> res(v);
	res.mEmpty=TRIBOOL::TRUE;
	res.mNonRedundant=true;
	return res;
}

template <typename Number, typename Converter>
std::size_t HPolytopeT<Number, Converter>::dimension() const {
	if(mHPlanes.empty()) return 0;
	return mDimension;
}

template <typename Number, typename Converter>
std::size_t HPolytopeT<Number, Converter>::size() const {
	return mHPlanes.size();
}

template <typename Number, typename Converter>
matrix_t<Number> HPolytopeT<Number, Converter>::matrix() const {
	matrix_t<Number> res( mHPlanes.size(), dimension() );
	for ( unsigned planeIndex = 0; planeIndex < mHPlanes.size(); ++planeIndex ) {
		//std::cout << "Add HPlane " << mHPlanes.at( planeIndex ) << " to matrix ( " << res.rows() << " x " << res.cols() << " )" << std::endl;
		res.row( planeIndex ) = mHPlanes.at( planeIndex ).normal();
	}
	return res;
}

template <typename Number, typename Converter>
vector_t<Number> HPolytopeT<Number, Converter>::vector() const {
	vector_t<Number> res( mHPlanes.size() );
	for ( unsigned planeIndex = 0; planeIndex < mHPlanes.size(); ++planeIndex ) {
		res( planeIndex ) = mHPlanes.at( planeIndex ).offset();
	}
	return res;
}

template <typename Number, typename Converter>
std::pair<matrix_t<Number>, vector_t<Number>> HPolytopeT<Number, Converter>::inequalities() const {
	matrix_t<Number> A( mHPlanes.size(), dimension() );
	vector_t<Number> b( mHPlanes.size() );
	for ( unsigned planeIndex = 0; planeIndex < mHPlanes.size(); ++planeIndex ) {
		A.row( planeIndex ) = mHPlanes.at( planeIndex ).normal().transpose();
		b( planeIndex ) = mHPlanes.at( planeIndex ).offset();
	}
	return std::make_pair( A, b );
}

template <typename Number, typename Converter>
typename std::vector<Point<Number>> HPolytopeT<Number, Converter>::vertices( const Location<Number>* ) const {
	typename std::vector<Point<Number>> vertices;
	if(!mHPlanes.empty() && mHPlanes.size() >= this->dimension() && !this->empty()) {
		unsigned dim = this->dimension();

		Permutator permutator(mHPlanes.size(), dim);
		std::vector<unsigned> permutation;
		while(!permutator.end()) {
			permutation = permutator();

			matrix_t<Number> A( dim, dim );
			vector_t<Number> b( dim );
			unsigned pos = 0;
			//std::cout << "Permute planes ";
			for(auto planeIt = permutation.begin(); planeIt != permutation.end(); ++planeIt) {
				//std::cout << *planeIt << ", ";
				A.row(pos) = mHPlanes.at(*planeIt).normal().transpose();
				// std::cout << A.row(pos) << std::endl;
				b(pos) = mHPlanes.at(*planeIt).offset();
				// std::cout << b(pos) << std::endl;
				++pos;
			}
			//std::cout << std::endl;

			//std::cout << "Created first matrix" << std::endl;

			Eigen::FullPivLU<matrix_t<Number>> lu_decomp( A );
			if ( lu_decomp.rank() < A.rows() ) {
				continue;
			}
			#ifdef HPOLY_DEBUG_MSG
			std::cout << convert<Number,double>(A) << std::endl;
			std::cout << convert<Number,double>(b) << std::endl;
			#endif

			vector_t<Number> res = lu_decomp.solve( b );

			TRACE("hypro.hPolytope","Computed Vertex: " << (convert<Number,double>(res).transpose()));

			// Check if the computed vertex is a real vertex
			bool outside = false;
			for(unsigned planePos = 0; planePos < mHPlanes.size(); ++planePos) {
				bool skip = false;
				for(unsigned permPos = 0; permPos < permutation.size(); ++permPos) {
					if(planePos == permutation.at(permPos)) {
						//std::cout << "Skip plane " << planePos << std::endl;
						skip = true;
						break;
					}
				}

				if(!skip) {
					if( !carl::AlmostEqual2sComplement(mHPlanes.at(planePos).offset(), mHPlanes.at(planePos).normal().dot(res), default_double_comparison_ulps) && mHPlanes.at(planePos).offset() - mHPlanes.at(planePos).normal().dot(res) < 0 ) {
						TRACE("hypro.hPolytope","Drop vertex: " << (convert<Number,double>(res).transpose()) << " because of plane " << planePos );
						outside = true;
						break;
					}
				}
			}
			if(!outside) {
				// insert, if no duplicate
				Point<Number> tmp(res);
				if(std::find(vertices.begin(), vertices.end(), tmp) == vertices.end()) {
					vertices.push_back(tmp);
				}
				TRACE("hypro.hPolytope","Final vertex: " << (convert<Number,double>(res).transpose()));
			}
		}
	}
	return vertices;
/*
	VertexEnumeration<Number> ev = VertexEnumeration<Number>(mHPlanes);
	ev.enumerateVertices();
	std::cout << "Enumerate vertices of " << std::endl << *this << std::endl;
	assert(ev.getLinealtySpace().empty());

	if(!ev.getCones().empty()) {
		std::cout << "Computed cone: " << std::endl;
		for(const auto& cone : ev.getCones() ) {
			std::cout << convert<Number,double>(cone).transpose() << std::endl;
		}
	}

	assert(ev.getCones().empty());
	for (const auto& point : ev.getPoints() ) {
		bool found = false;
		for (const auto& vert : vertices ) {
			found=found||(point==vert);
		}
		assert(found);
	}
	for ( const auto &point : vertices ) {
		bool found = false;
		for ( const auto &vert : ev.getPoints() ) {
			found=found||(point==vert);
		}
		assert(found);
	}
	return ev.getPoints();
*/
}

template <typename Number, typename Converter>
Number HPolytopeT<Number, Converter>::supremum() const {
	Number max = 0;
	assert(!this->empty());
	assert(!this->vertices().empty());
	for ( const auto &point : this->vertices() ) {
		Number inftyNorm = Point<Number>::inftyNorm( point );
		max = max > inftyNorm ? max : inftyNorm;
	}
	return max;
}

//template <typename Number, typename Converter>
//void HPolytopeT<Number, Converter>::calculateFan() const {
//	std::vector<std::shared_ptr<Facet<Number>>> facets = convexHull( vertices() ).first;
//	std::set<Point<Number>> preresult;
//	for ( unsigned i = 0; i < facets.size(); i++ ) {
//		for ( unsigned j = 0; j < facets[i].vertices().size(); j++ ) {
//			preresult.insert( facets[i]->vertices().at( j ) );
//		}
//	}
//	polytope::Fan<Number> fan;
//	for ( auto &point : preresult ) {
//		polytope::Cone<Number> *cone = new polytope::Cone<Number>();
//		for ( unsigned i = 0; i < facets.size(); i++ ) {
//			for ( unsigned j = 0; j < facets[i]->vertices().size(); j++ ) {
//				if ( point == facets[i]->vertices().at( j ) ) {
//					std::vector<Ridge<Number>> ridges = getRidges( *facets[i] );
//					for ( unsigned m = 0; m < ridges.size(); m++ ) {
//						if ( checkInsideRidge( ridges[m], point ) ) {
//							std::vector<Facet<Number>> conefacets = shareRidge( facets, ridges[m] );
//
//							matrix_t<Number> matrix = matrix_t<Number>( conefacets.size(), point.size() );
//							for ( unsigned k = 1; k < conefacets.size(); k++ ) {
//								for ( unsigned l = 0; l < conefacets[k].getNormal().size(); l++ ) {
//									matrix( k, l ) = conefacets[k].getNormal()( l );
//								}
//							}
//
//							for ( unsigned j = 0; j < point.size(); j++ ) {
//								matrix( 0, j ) = 1;
//
//								if ( matrix.fullPivLu().rank() == point.size() ) {
//									break;
//								} else {
//									matrix( 0, j ) = 0;
//								}
//							}
//							vector_t<Number> b = vector_t<Number>::Zero( conefacets.size() );
//							b( 0 ) = 1;
//							vector_t<Number> result = matrix.fullPivHouseholderQr().solve( b );
//
//							cone->add( std::shared_ptr<Halfspace<Number>>(
//								  new Halfspace<Number>( result, result.dot( point.rawCoordinates() ) ) ) );
//							// cone->add(std::make_shared<Halfspace<Number>>(Halfspace<Number>(result,
//							// result.dot(point.rawCoordinates()))));
//						}
//					}
//				}
//			}
//		}
//		fan.add( cone );
//	}
//	mFanSet = true;
//	mFan = fan;
//}

template <typename Number, typename Converter>
void HPolytopeT<Number, Converter>::insert( const Halfspace<Number> &plane ) {
	assert( mDimension == 0 || mDimension == plane.dimension() );
	if ( mDimension == 0 ) {
		mDimension = plane.dimension();
		mHPlanes.push_back( plane );
		mEmpty = TRIBOOL::FALSE;
		mNonRedundant = true;
	} else {
		bool found = false;
		for(auto planeIt = mHPlanes.begin(); planeIt != mHPlanes.end(); ++planeIt) {
			if(*planeIt == plane){
				found = true;
				break;
			}
		}
		if(!found){
			mHPlanes.push_back( plane );
			mEmpty = TRIBOOL::NSET;
			mNonRedundant = false;
		}
	}
}

template <typename Number, typename Converter>
void HPolytopeT<Number, Converter>::insert( const typename HalfspaceVector::iterator begin,
								const typename HalfspaceVector::iterator end ) {
	auto it = begin;
	while ( it != end ) {
		this->insert( *it );
		++it;
	}
}

template <typename Number, typename Converter>
void HPolytopeT<Number, Converter>::erase( const unsigned index ) {
	assert(index < mHPlanes.size());
	mHPlanes.erase(mHPlanes.begin()+index);
	if(mEmpty == TRIBOOL::TRUE) {
		mEmpty = TRIBOOL::NSET;
	}
}

template <typename Number, typename Converter>
const typename HPolytopeT<Number, Converter>::HalfspaceVector &HPolytopeT<Number, Converter>::constraints() const {
	return mHPlanes;
}

template <typename Number, typename Converter>
bool HPolytopeT<Number, Converter>::hasConstraint( const Halfspace<Number> &hplane ) const {
	for ( const auto &plane : mHPlanes ) {
		if ( hplane == plane ) return true;
	}
	return false;
}

template <typename Number, typename Converter>
const HPolytopeT<Number,Converter>& HPolytopeT<Number, Converter>::removeRedundancy() {
	//std::cout << __func__ << std::endl;
	if(!mNonRedundant && mHPlanes.size() > 1){
		//std::cout << "Not already reduced." << std::endl;
		Optimizer<Number> opt;
		opt.setMatrix(this->matrix());
		opt.setVector(this->vector());

		std::vector<std::size_t> redundant = opt.redundantConstraints();
		//std::cout << __func__ << ": found " << redundant.size() << " redundant constraints." << std::endl;
		//std::cout << __func__ << ": Redundant constraints: " << redundant << std::endl;

		if(!redundant.empty()){
			std::size_t cnt = mHPlanes.size()-1;
			for ( auto rIt = mHPlanes.rbegin(); rIt != mHPlanes.rend(); ++rIt ) {
				if(redundant.empty())
					break;

				if(redundant.back() == cnt){
					mHPlanes.erase( --(rIt.base()) );
					redundant.pop_back();
					//std::cout << "Erase plane " << cnt << std::endl;
				}
				--cnt;
			}
		}

		assert(redundant.empty());
	}
	mNonRedundant=true;
	return *this;
}

template <typename Number, typename Converter>
bool HPolytopeT<Number, Converter>::isExtremePoint( const vector_t<Number>& point ) const {
	unsigned cnt = 0;
	for ( const auto &plane : mHPlanes ) {
		Number val = plane.evaluate( point );
		if ( plane.offset() == val  ) {
			++cnt;
		} else if ( plane.offset() - val < 0 ) {
			return false;
		}
	}
	return (cnt >= mDimension);
}

template <typename Number, typename Converter>
bool HPolytopeT<Number, Converter>::isExtremePoint( const Point<Number> &point ) const {
	return isExtremePoint( point.rawCoordinates() );
}

template <typename Number, typename Converter>
EvaluationResult<Number> HPolytopeT<Number, Converter>::evaluate( const vector_t<Number> &_direction ) const {
	if(mHPlanes.empty()) {
		return EvaluationResult<Number>( Number(1), INFTY );
	}

	//reduceNumberRepresentation();

	Optimizer<Number> opt;
	opt.setMatrix(this->matrix());
	opt.setVector(this->vector());

	return opt.evaluate(_direction, true);
}

/*
 * General interface
 */

template<typename Number, typename Converter>
std::pair<bool, HPolytopeT<Number, Converter>> HPolytopeT<Number, Converter>::satisfiesHalfspace( const Halfspace<Number>& rhs ) const {
	TRACE("hypro.hPolytope","(P AND ex <= d) == emptyset?, e: " << rhs.normal() << "d: " << rhs.offset());
	if(this->empty()) {
		return std::make_pair(false, *this);
	}
	HPolytopeT<Number,Converter> tmp = this->intersectHalfspace(rhs);
	return std::make_pair(!(tmp).empty(), tmp);
}

template<typename Number, typename Converter>
std::pair<bool, HPolytopeT<Number, Converter>> HPolytopeT<Number, Converter>::satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {
	TRACE("hypro.hPolytope","(P AND Ax <= b) == emptyset?, A: " << _mat << "b: " << _vec);
	assert(_mat.rows() == _vec.rows());
	if(this->empty()) {
		return std::make_pair(false, *this);
	}

	if(_mat.rows() == 0) {
		return std::make_pair(true, *this);
	}
	HPolytopeT<Number,Converter> tmp = this->intersectHalfspaces(_mat, _vec);
	return std::make_pair(!(tmp).empty(),tmp);
}

template <typename Number, typename Converter>
HPolytopeT<Number, Converter> HPolytopeT<Number, Converter>::project(const std::vector<unsigned>& dimensions) const {
	TRACE("hypro.hPolytope","on dimensions " << dimensions);
	if(dimensions.empty()) {
		return Empty();
	}

	auto box = Converter::toBox(*this);
	box = box.project(dimensions);

	return Converter::toHPolytope(box);
}

template <typename Number, typename Converter>
HPolytopeT<Number, Converter> HPolytopeT<Number, Converter>::linearTransformation( const matrix_t<Number> &A ) const {
	TRACE("hypro.hPolytope","P' = A*P, A:" << std::endl << A);
	if(A.nonZeros() == 0) {
		return HPolytopeT<Number,Converter>::Empty();
	}
	if(!this->empty() && !mHPlanes.empty()) {
		Eigen::FullPivLU<matrix_t<Number>> lu(A);
		// if A has full rank, we can simply re-transform, otherwise use v-representation.
		if(lu.rank() == A.rows()) {
			TRACE("hypro.hPolytope","A has full rank - do not use v-conversion.");
			std::pair<matrix_t<Number>, vector_t<Number>> inequalities = this->inequalities();
			assert( (HPolytopeT<Number, Converter>(inequalities.first*A.inverse(), inequalities.second).size() == this->size()) );
			return HPolytopeT<Number, Converter>(inequalities.first*A.inverse(), inequalities.second);
		} else {
			TRACE("hypro.hPolytope","Use V-Conversion for linear transformation.");
			auto intermediate = Converter::toVPolytope( *this );
			intermediate = intermediate.linearTransformation( A );
			auto res = Converter::toHPolytope(intermediate);
			//assert(res.size() <= this->size());
			res.setReduced();
			return res;
		}
	} else {
		return *this;
	}
}

template <typename Number, typename Converter>
HPolytopeT<Number, Converter> HPolytopeT<Number, Converter>::affineTransformation( const matrix_t<Number> &A,
														   const vector_t<Number> &b ) const {
	TRACE("hypro.hPolytope","P' = A*P + b, A: " << std::endl << A << "b: " << std::endl << b);
	if(A.nonZeros() == 0) {
		std::vector<Point<Number>> points;
		points.emplace_back(b);
		return HPolytopeT<Number,Converter>(points);
	}
	if(!this->empty() && !mHPlanes.empty()) {
		Eigen::FullPivLU<matrix_t<Number>> lu(A);
		// if A has full rank, we can simply re-transform, otherwise use v-representation.
		if(lu.rank() == A.rows()) {
			TRACE("hypro.hPolytope","A has full rank - do not use v-conversion.");
			std::pair<matrix_t<Number>, vector_t<Number>> inequalities = this->inequalities();
			assert( (HPolytopeT<Number, Converter>(inequalities.first*A.inverse(), inequalities.first*A.inverse()*b + inequalities.second).size() == this->size()) );
			assert( !(HPolytopeT<Number, Converter>(inequalities.first*A.inverse(), inequalities.first*A.inverse()*b + inequalities.second).empty()) );
			return HPolytopeT<Number, Converter>(inequalities.first*A.inverse(), inequalities.first*A.inverse()*b + inequalities.second);
		} else {
			TRACE("hypro.hPolytope","Use V-Conversion for linear transformation.");
			auto intermediate = Converter::toVPolytope( *this );
			intermediate = intermediate.affineTransformation( A, b );
			auto res = Converter::toHPolytope(intermediate);
			//assert(res.size() <= this->size());
			res.setReduced();
			return res;
		}
	} else {
		return *this;
	}
}

template <typename Number, typename Converter>
HPolytopeT<Number, Converter> HPolytopeT<Number, Converter>::minkowskiSum( const HPolytopeT &rhs ) const {
	TRACE("hypro.hPolytope","P' = P + " << rhs << std::endl);
	HPolytopeT<Number, Converter> res;
	Number result;

	// evaluation of rhs in directions of lhs
	for ( unsigned i = 0; i < mHPlanes.size(); ++i ) {
		EvaluationResult<Number> evalRes = rhs.evaluate( mHPlanes.at( i ).normal() );
		if ( evalRes.errorCode == INFTY ) {
			// Do nothing - omit inserting plane.
		} else if ( evalRes.errorCode == INFEAS ) {
			return Empty();
		} else {
			result = mHPlanes.at( i ).offset() + evalRes.supportValue;
			res.insert( Halfspace<Number>( mHPlanes.at( i ).normal(), result ) );
		}
	}

	//if(!oneWay) { // Todo: push to settings.
		// evaluation of lhs in directions of rhs
		for ( unsigned i = 0; i < rhs.constraints().size(); ++i ) {
			EvaluationResult<Number> evalRes = this->evaluate( rhs.constraints().at( i ).normal() );
			if ( evalRes.errorCode == INFTY ) {
				// Do nothing - omit inserting plane.
			} else if ( evalRes.errorCode == INFEAS ) {
				return Empty();
			} else {
				result = rhs.constraints().at( i ).offset() + evalRes.supportValue;
				res.insert( Halfspace<Number>( rhs.constraints().at( i ).normal(), result ) );
			}
		}
	//}
	return res;
}

template <typename Number, typename Converter>
HPolytopeT<Number, Converter> HPolytopeT<Number, Converter>::intersect( const HPolytopeT &rhs ) const {
	TRACE("hypro.hPolytope","with " << rhs << std::endl);
	if ( rhs.empty() || this->empty() ) {
		return HPolytopeT<Number, Converter>::Empty();
	} else {
		HPolytopeT<Number, Converter> res;
		for ( const auto &plane : mHPlanes ) {
			res.insert( plane );
		}
		for ( const auto &plane : rhs.constraints() ) {
			res.insert( plane );
		}

		return res;
	}
}

template <typename Number, typename Converter>
HPolytopeT<Number, Converter> HPolytopeT<Number, Converter>::intersectHalfspace( const Halfspace<Number> &rhs ) const {
	TRACE("hypro.hPolytope","with " << rhs << std::endl);
	HPolytopeT<Number, Converter> res( *this );
	// only insert the new Halfspace, if it is not already redundant.
	if(res.evaluate(rhs.normal()).supportValue > rhs.offset())
		res.insert( Halfspace<Number>( rhs ) );

	return res;
}

template <typename Number, typename Converter>
HPolytopeT<Number, Converter> HPolytopeT<Number, Converter>::intersectHalfspaces( const matrix_t<Number> &_mat,
														   const vector_t<Number> &_vec ) const {
	TRACE("hypro.hPolytope","P' = P AND Ax <= b,  A: " << std::endl << _mat << std::endl << "b: " << _vec);
	assert( _mat.rows() == _vec.rows() );
	HPolytopeT<Number, Converter> res( *this );
	for ( unsigned i = 0; i < _mat.rows(); ++i ) {
		res.insert( Halfspace<Number>( _mat.row(i), _vec( i ) ) );
	}
	res.removeRedundancy();
	return res;
}

template <typename Number, typename Converter>
bool HPolytopeT<Number, Converter>::contains( const Point<Number> &point ) const {
	TRACE("hypro.hPolytope",point);
	return this->contains( point.rawCoordinates() );
}

template <typename Number, typename Converter>
bool HPolytopeT<Number, Converter>::contains( const vector_t<Number> &vec ) const {
	for ( const auto &plane : mHPlanes ) {
		// The 2's complement check for equality is required to ensure double compatibility.
		if (!carl::AlmostEqual2sComplement(plane.normal().dot( vec ), plane.offset(), 128) && plane.normal().dot( vec ) > plane.offset()) {
			return false;
		}
	}
	return true;
}

template <typename Number, typename Converter>
bool HPolytopeT<Number, Converter>::contains( const HPolytopeT<Number, Converter> &rhs ) const {
	if(this->empty()){
		return false;
	}
	if(rhs.empty()) {
		return true;
	}

	for ( const auto &plane : rhs.constraints() ) {
		EvaluationResult<Number> evalRes = this->evaluate( plane.normal() );
		if ( evalRes.errorCode == INFEAS ) {
			return false;  // empty!
		} else if ( evalRes.errorCode == INFTY ) {
			continue;
		} else if ( evalRes.supportValue < plane.offset() ) {
			assert(evalRes.errorCode == FEAS);
			return false;
		}
	}
	return true;
}

template <typename Number, typename Converter>
HPolytopeT<Number, Converter> HPolytopeT<Number, Converter>::unite( const HPolytopeT &_rhs ) const {
	TRACE("hypro.hPolytope","with " << _rhs << std::endl);
	if( this->empty() ) {
		// if this is empty, the result is _rhs, even if _rhs is empty, too.
		return _rhs;
	}
	// at this point *this is not empty.
	if ( _rhs.empty() ) {
		return *this;
	}
	// at this point, none is empty.
	#ifdef AVOID_CONVERSION
	unsigned numberOfDirections = 8;
	TRACE("hypro.hPolytope","Unite using templated evaluation using " << numberOfDirections << " directions.");
	assert(this->dimension() == _rhs.dimension());
	std::vector<vector_t<Number>> templateDirections = computeTemplate<Number>(this->dimension(), numberOfDirections);
	// as the template directions are ordered, we assume the same order for the results.
	HalfspaceVector newHalfspaces;
	for(const auto& direction : templateDirections) {
		EvaluationResult<Number> thisResult = this->evaluate(direction);
		EvaluationResult<Number> rhsResult = _rhs.evaluate(direction);
		assert(thisResult.errorCode != SOLUTION::INFEAS);
		assert(rhsResult.errorCode != SOLUTION::INFEAS);
		// if one of the polytopes is unbounded, do not add this halfspace -> keep the unboundedness.
		if(thisResult.errorCode == SOLUTION::FEAS && rhsResult.errorCode == SOLUTION::FEAS) {
			if(thisResult.supportValue > rhsResult.supportValue) {
				newHalfspaces.emplace_back(direction, thisResult.supportValue);
			} else {
				newHalfspaces.emplace_back(direction, rhsResult.supportValue);
			}
		}
	}
	assert(newHalfspaces.size() <= templateDirections.size());
	return HPolytopeT<Number,Converter>(newHalfspaces);
	#else
	TRACE("hypro.hPolytope","Unite using V-polytope representation.");
	std::vector<Point<Number>> vertices = this->vertices();
	std::vector<Point<Number>> rhsVertices = _rhs.vertices();
	vertices.insert(vertices.end(), rhsVertices.begin(), rhsVertices.end());
	HPolytopeT<Number,Converter> result(vertices);

	/*
	auto lhs = Converter::toVPolytope( *this );
	std::cout << "this as vpoly: " << lhs << std::endl;
	auto tmpRes = lhs.unite( Converter::toVPolytope( _rhs ) );
	std::cout << "rhs as vpoly : " << Converter::toVPolytope( _rhs ) << std::endl;
	HPolytopeT<Number,Converter> result = Converter::toHPolytope( tmpRes );
	*/

	//std::cout << "size after union: " << result.size() << std::endl;

	//assert(result.contains(*this));
	//assert(result.contains(_rhs));
	//std::cout << __func__ << " : tmpres " << tmpRes << std::endl;

	/*
	std::cout << __func__ << " BEGIN." << std::endl;
	std::vector<Point<Number>> unitedVertices(this->vertices());
	for(const auto& vertex : _rhs.vertices()) {
		unitedVertices.emplace_back(vertex);
	}


	for(const auto vertex : unitedVertices) {
		std::cout << "Vertex to unite: " << vertex << std::endl;
	}


	ConvexHull<Number> ch = ConvexHull<Number>(unitedVertices);
	ch.convexHullVertices();
	HPolytopeT<Number,Converter> result = HPolytopeT<Number,Converter>(ch.getHsv());
	assert(ch.getCone().empty());
	assert(ch.getLinealtySpace().empty());
	*/
	/*
	for(const auto& vertex : owenTmpRes.vertices()) {
		std::cout << "Result vertex " << convert<Number,double>(vertex.rawCoordinates()).transpose() << std::endl;
		//assert(std::find(unitedVertices.begin(), unitedVertices.end(), vertex) != unitedVertices.end());
	}
	std::cout << __func__ << " END." << std::endl;
	*/
	return result;
	#endif
}

template<typename Number, typename Converter>
HPolytopeT<Number,Converter> HPolytopeT<Number,Converter>::unite( const std::vector<HPolytopeT>& rhs ) const {
	// Todo: Implement alternative avoiding conversion.
	std::vector<Point<Number>> vertices = this->vertices();
	for(const auto& poly : rhs) {
		vertices.insert(vertices.end(), poly.vertices().begin(), poly.vertices().end());
	}
	return HPolytopeT(vertices);
}

template <typename Number, typename Converter>
void HPolytopeT<Number, Converter>::clear() {
	mHPlanes.clear();
	mDimension = 0;
	mEmpty = FALSE;
	mNonRedundant = true;
}

template <typename Number, typename Converter>
void HPolytopeT<Number, Converter>::print() const {
	//std::cout << *this << std::endl;
}

/*
 * Auxiliary functions
 */


template <typename Number, typename Converter>
typename HPolytopeT<Number, Converter>::HalfspaceVector HPolytopeT<Number, Converter>::computeConstraintsForDegeneratedPolytope(std::vector<Point<Number>>& points, unsigned degeneratedDimensions) const {
	if(degeneratedDimensions == 0) {
		return std::move(HPolytopeT<Number, Converter>(points).mHPlanes);
	}
	assert(!points.empty());
	Halfspace<Number> h; // TODO set h to some hyperplane holding all points, i.e., a*p=b for all points p
	points.emplace_back(points.begin()->rawCoordinates() + h.normal());
	// The effective dimension of the convex hull of points is now increased by one, i.e.,
	// the number of degenerated dimensions is decreased by one.
	// Furthermore, one of the faces of the convex hull of points is the polytope we are looking for.
	// This is exactly the face we get when we intersect the convex hull with the halfspace h
	HalfspaceVector result = commputeConstraintsForDegeneratedPolytope(points, degeneratedDimensions - 1);
	result.push_back(std::move(h)); // decreases the effective dimension again
	return result;
}

}  // namespace hypro
