#include "HPolytope.h"
namespace hypro {
template <typename Number>
HPolytope<Number>::HPolytope()
	: mHPlanes(), mFanSet( false ), mFan(), mDimension( 0 ), mInitialized( false ) {
}

template <typename Number>
HPolytope<Number>::HPolytope( const HPolytope &orig )
	: mHPlanes(), mFanSet( orig.mFanSet ), mFan( orig.mFan ), mDimension( orig.mDimension ), mInitialized( false ) {
	for ( const auto &plane : orig.constraints() ) {
		mHPlanes.push_back( plane );
	}
}

template <typename Number>
HPolytope<Number>::HPolytope( const HyperplaneVector &planes )
	: mHPlanes(), mFanSet( false ), mFan(), mDimension( 0 ), mInitialized( false ) {
	if ( !planes.empty() ) {
		mDimension = planes.begin()->dimension();
		for ( const auto &plane : planes ) {
			mHPlanes.push_back( plane );
		}
	}
}

template <typename Number>
HPolytope<Number>::HPolytope( const matrix_t<Number> &A, const vector_t<Number> &b )
	: mHPlanes(), mFanSet( false ), mFan(), mDimension( A.cols() ), mInitialized( false ) {
	assert( A.rows() == b.rows() );
	for ( unsigned i = 0; i < A.rows(); ++i ) {
		mHPlanes.push_back( Hyperplane<Number>( A.row( i ), b( i ) ) );
	}
}

template <typename Number>
HPolytope<Number>::HPolytope( const matrix_t<Number> &A )
	: mHPlanes(), mFanSet( false ), mFan(), mDimension( A.cols() ), mInitialized( false ) {
	for ( unsigned i = 0; i < A.rows(); ++i ) {
		mHPlanes.push_back( Hyperplane<Number>( A.row( i ), Number( 0 ) ) );
	}
}

template <typename Number>
HPolytope<Number>::HPolytope( const VPolytope<Number> &alien )
	: mHPlanes(), mFanSet( false ), mFan(), mDimension( 0 ), mInitialized( false ) {
	if ( !alien.empty() ) {
		// degenerate cases
		unsigned size = alien.size();
		mDimension = alien.dimension();
		if ( size == 1 ) {
			// Return Box constraints.
		} else if ( size < mDimension ) {
			std::vector<Point<Number>> vertices = alien.vertices();

			// ATTENTION: Assumption here: alien is reduced, such that the d points in alien span a d-1 dimensional object.

			// find all hyperplanar descriptions by reducing to d dimensions (get the plane)
			std::size_t dim = vertices.size();
			polytope::dPermutator permutator(mDimension, dim);

			std::vector<unsigned> permutation;
			while(!permutator.end()) {
				permutation = permutator();

				// project to chosen dimensions
				std::vector<Point<Number>> reducedVertices;
				reducedVertices.reserve(dim);
				for(const auto& vertex : vertices) {
					vector_t<Number> reductor = vector_t<Number>(dim);
					for(unsigned d = 0; d < dim; ++d)
						reductor(d) = vertex.at(d);

					reducedVertices.push_back(Point<Number>(std::move(reductor)));
				}

				std::vector<std::shared_ptr<Facet<Number>>> facets = convexHull( reducedVertices ).first;
				//std::cout << "Conv Hull end" << std::endl;
				for ( auto &facet : facets ) {
					mHPlanes.push_back( facet->hyperplane() );
				}

			}

			assert( false );
		} else {
			//std::cout << "Conv Hull" << std::endl;
			// TODO: Chose suitable convex hull algorithm
			typename std::vector<Point<Number>> points = alien.vertices();
			std::vector<std::shared_ptr<Facet<Number>>> facets = convexHull( points ).first;
			//std::cout << "Conv Hull end" << std::endl;
			for ( auto &facet : facets ) {
				mHPlanes.push_back( facet->hyperplane() );
			}
			facets.clear();
		}
	}
}

template <typename Number>
HPolytope<Number>::~HPolytope() {
	if ( mInitialized ) glp_delete_prob(lp);
}

/*
 * Getters and setters
 */

template <typename Number>
bool HPolytope<Number>::empty() const {
	if(mHPlanes.empty())
		return false;

	#ifdef USE_SMTRAT
	smtrat::SimplexSolver simplex;
	smtrat::FormulaT constr = createFormula(this->matrix(), this->vector());
	simplex.inform(constr);
	simplex.add(constr);

	std::cout << constr << std::endl;

	return (simplex.check() == smtrat::Answer::False);
	#else
	if(!mInitialized) {
		initialize();
	}
	glp_term_out(GLP_OFF);
	for ( unsigned i = 0; i < mDimension; i++ ) {
		glp_set_col_bnds( lp, i + 1, GLP_FR, 0.0, 0.0 );
		glp_set_obj_coef( lp, i + 1, 1.0 ); // not needed?
	}
	glp_exact( lp, NULL );
	//if(glp_get_status(lp) == GLP_NOFEAS)
		//std::cout << "Empty!" << std::endl;

	return (glp_get_status(lp) == GLP_NOFEAS);
	#endif
}

template <typename Number>
HPolytope<Number> HPolytope<Number>::Empty(){
	Hyperplane<Number> a({1},-1);
	Hyperplane<Number> b({-1},-1);
	HyperplaneVector v;
	v.emplace_back(a);
	v.emplace_back(b);
	HPolytope<Number> res(v);
	return res;
}

template <typename Number>
std::size_t HPolytope<Number>::dimension() const {
	if(mHPlanes.empty()) return 0;
	return mDimension;
}

template <typename Number>
std::size_t HPolytope<Number>::size() const {
	return mHPlanes.size();
}

template <typename Number>
matrix_t<Number> HPolytope<Number>::matrix() const {
	matrix_t<Number> res( mHPlanes.size(), dimension() );
	for ( unsigned planeIndex = 0; planeIndex < mHPlanes.size(); ++planeIndex ) {
		res.row( planeIndex ) = mHPlanes.at( planeIndex ).normal().transpose();
	}
	return res;
}

template <typename Number>
vector_t<Number> HPolytope<Number>::vector() const {
	vector_t<Number> res( mHPlanes.size() );
	for ( unsigned planeIndex = 0; planeIndex < mHPlanes.size(); ++planeIndex ) {
		res( planeIndex ) = mHPlanes.at( planeIndex ).offset();
	}
	return res;
}

template <typename Number>
std::pair<matrix_t<Number>, vector_t<Number>> HPolytope<Number>::inequalities() const {
	matrix_t<Number> A( mHPlanes.size(), dimension() );
	vector_t<Number> b( mHPlanes.size() );
	for ( unsigned planeIndex = 0; planeIndex < mHPlanes.size(); ++planeIndex ) {
		A.row( planeIndex ) = mHPlanes.at( planeIndex ).normal().transpose();
		b( planeIndex ) = mHPlanes.at( planeIndex ).offset();
	}
	return std::make_pair( A, b );
}

template <typename Number>
const typename polytope::Fan<Number> &HPolytope<Number>::fan() const {
	if ( !mFanSet ) {
		calculateFan();
	}
	return mFan;
}

template <typename Number>
typename std::vector<Point<Number>> HPolytope<Number>::vertices() const {
	//std::cout << "Compute vertices of " << *this << std::endl;
	typename std::vector<Point<Number>> vertices;
	if(!mHPlanes.empty()) {
		unsigned dim = this->dimension();

		polytope::dPermutator permutator(mHPlanes.size(), dim);
		std::vector<unsigned> permutation;
		while(!permutator.end()) {
			permutation = permutator();
			//std::cout << "Use planes ";
			//for(const auto item : permutation)
			//	std::cout << item << ", ";
			//std::cout << std::endl;

			matrix_t<Number> A( dim, dim );
			vector_t<Number> b( dim );
			unsigned pos = 0;
			for(auto planeIt = permutation.begin(); planeIt != permutation.end(); ++planeIt) {
				A.row(pos) = mHPlanes.at(*planeIt).normal().transpose();
				// std::cout << A.row(pos) << std::endl;
				b(pos) = mHPlanes.at(*planeIt).offset();
				// std::cout << b(pos) << std::endl;
				++pos;
			}

			//std::cout << "Created first matrix" << std::endl;

			Eigen::FullPivLU<matrix_t<Number>> lu_decomp( A );
			if ( lu_decomp.rank() < A.rows() ) {
				continue;
			}

			vector_t<Number> res = lu_decomp.solve( b );

			// check for infinity
			bool infty = false;
			for ( unsigned i = 0; i < res.rows(); ++i ) {
				if ( std::numeric_limits<Number>::infinity() == ( Number( res( i ) ) ) ) {
					//std::cout << ( Number( res( i ) ) ) << " is infty." << std::endl;
					infty = true;
					break;
				}
			}

			if(!infty) {
				//std::cout << "Solved to " << res.transpose() << std::endl;
				// check if point lies above all planes -> if not, ensure by enlarging the polytope (very expensive)
				bool below = false;
				for(auto planeIt = permutation.begin(); planeIt != permutation.end(); ++planeIt) {
					Number dist = mHPlanes.at(*planeIt).offset() - mHPlanes.at(*planeIt).normal().dot(res);
					if(dist > 0) {
						below = true;
						break;
					}
				}
				Number eps = std::numeric_limits<Number>::epsilon();
				while (below) {
					//std::cout << "Is below, iterate " << std::endl;
					// enlarge as long as point lies below one of the planes.
					below = false;
					eps = eps * 10;

					pos = 0;
					for(auto planeIt = permutation.begin(); planeIt != permutation.end(); ++planeIt) {
						A.row(pos) = mHPlanes.at(*planeIt).normal().transpose();
						b(pos) = mHPlanes.at(*planeIt).offset() + eps;
						++pos;
					}
					vector_t<Number> tmp = Eigen::FullPivLU<matrix_t<Number>>(A).solve( b );

					for(auto planeIt = permutation.begin(); planeIt != permutation.end(); ++planeIt){
						Number dist = mHPlanes.at(*planeIt).offset() - mHPlanes.at(*planeIt).normal().dot(tmp);
						if(dist > 0) {
							//std::cout << "Dist: " << dist << std::endl;
							below = true;
							break;
						}
					}
					if(!below)
						res = tmp;
				}
////////////////TODO: change to almostEqual() function
                ///// if it's not almost equal, then
				// Check containment
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
						if( mHPlanes.at(planePos).offset() - mHPlanes.at(planePos).normal().dot(res) < 0 ) {
							//std::cout << "Drop vertex: " << res.transpose() << " because of plane " << planePos << std::endl;
							outside = true;
							break;
						}
					}
				}
				if(!outside) {
					Point<Number> point = Point<Number>(res);
					vertices.push_back(point);
					//std::cout << "Final vertex: " << res.transpose() << std::endl;
				}
			}
			//std::cout << "PING" << std::endl;
		}
	}
	return vertices;
}

template <typename Number>
Number HPolytope<Number>::supremum() const {
	Number max = 0;
	for ( auto &point : this->vertices() ) {
		Number inftyNorm = hypro::Point<Number>::inftyNorm( point );
		max = max > inftyNorm ? max : inftyNorm;
	}
	return max;
}

template <typename Number>
void HPolytope<Number>::calculateFan() const {
	std::vector<std::shared_ptr<Facet<Number>>> facets = convexHull( vertices() ).first;
	std::set<Point<Number>> preresult;
	for ( unsigned i = 0; i < facets.size(); i++ ) {
		for ( unsigned j = 0; j < facets[i].vertices().size(); j++ ) {
			preresult.insert( facets[i]->vertices().at( j ) );
		}
	}
	polytope::Fan<Number> fan;
	for ( auto &point : preresult ) {
		polytope::Cone<Number> *cone = new polytope::Cone<Number>();
		for ( unsigned i = 0; i < facets.size(); i++ ) {
			for ( unsigned j = 0; j < facets[i]->vertices().size(); j++ ) {
				if ( point == facets[i]->vertices().at( j ) ) {
					std::vector<Ridge<Number>> ridges = getRidges( *facets[i] );
					for ( unsigned m = 0; m < ridges.size(); m++ ) {
						if ( checkInsideRidge( ridges[m], point ) ) {
							std::vector<Facet<Number>> conefacets = shareRidge( facets, ridges[m] );

							matrix_t<Number> matrix = matrix_t<Number>( conefacets.size(), point.size() );
							for ( unsigned k = 1; k < conefacets.size(); k++ ) {
								for ( unsigned l = 0; l < conefacets[k].getNormal().size(); l++ ) {
									matrix( k, l ) = conefacets[k].getNormal()( l );
								}
							}

							for ( unsigned j = 0; j < point.size(); j++ ) {
								matrix( 0, j ) = 1;

								if ( matrix.fullPivLu().rank() == point.size() ) {
									break;
								} else {
									matrix( 0, j ) = 0;
								}
							}
							vector_t<Number> b = vector_t<Number>::Zero( conefacets.size() );
							b( 0 ) = 1;
							vector_t<Number> result = matrix.fullPivHouseholderQr().solve( b );

							cone->add( std::shared_ptr<Hyperplane<Number>>(
								  new Hyperplane<Number>( result, result.dot( point.rawCoordinates() ) ) ) );
							// cone->add(std::make_shared<Hyperplane<Number>>(Hyperplane<Number>(result,
							// result.dot(point.rawCoordinates()))));
						}
					}
				}
			}
		}
		fan.add( cone );
	}
	mFanSet = true;
	mFan = fan;
}

template <typename Number>
void HPolytope<Number>::insert( const Hyperplane<Number> &plane ) {
	assert( mDimension == 0 || mDimension == plane.dimension() );
	if ( mDimension == 0 ) {
		mDimension = plane.dimension();
	}
	mHPlanes.push_back( plane );
	mInitialized = false;
}

template <typename Number>
void HPolytope<Number>::insert( const typename HyperplaneVector::iterator begin,
								const typename HyperplaneVector::iterator end ) {
	assert( mDimension == 0 || mDimension == begin->dimension() );
	if ( mDimension == 0 ) {
		mDimension = begin->dimension();
	}
	auto it = begin;
	while ( it != end ) {
		mHPlanes.push_back( *it );
		++it;
	}
	mInitialized = false;
}

template <typename Number>
void HPolytope<Number>::erase( const unsigned index ) {
	mHPlanes.erase(mHPlanes.begin()+index);
}

template <typename Number>
const typename HPolytope<Number>::HyperplaneVector &HPolytope<Number>::constraints() const {
	return mHPlanes;
}

template <typename Number>
bool HPolytope<Number>::hasConstraint( const Hyperplane<Number> &hplane ) const {
	for ( const auto &plane : mHPlanes ) {
		if ( hplane == plane ) return true;
	}
	return false;
}

template <typename Number>
void HPolytope<Number>::removeRedundantPlanes() {
	if(this->empty()) {
		*this = HPolytope<Number>::Empty();
	} else {
		//std::cout << __func__ << ": " << *this << std::endl;
		for ( auto planeIt = mHPlanes.begin(); planeIt != mHPlanes.end(); ) {
			// std::cout << "Current plane: " << *planeIt << std::endl;
			std::pair<Number, SOLUTION> evalRes = this->evaluate( planeIt->normal() );
			if ( evalRes.second == INFEAS ) {
				// return empty polytope
				this->clear();
				break;
			} else if ( evalRes.second == FEAS ) {
				if ( evalRes.first < planeIt->offset() &&
					 !carl::AlmostEqual2sComplement( evalRes.first, planeIt->offset() ) ) {
					// std::cout << "erase " << *planeIt << " which is really redundant." <<
					// std::endl;
					planeIt = mHPlanes.erase( planeIt );
					mInitialized = false;
				} else {
					Hyperplane<Number> tmp = Hyperplane<Number>( *planeIt );
					auto pos = mHPlanes.erase( planeIt );
					mInitialized = false;
					std::pair<Number, SOLUTION> tmpRes = this->evaluate( tmp.normal() );
					// std::cout << "Eval with: " << evalRes.first << ", without: " <<
					// tmpRes.first << ", solution type: "
					// << tmpRes.second << std::endl;
					if ( tmpRes.second == INFTY ||
						 ( tmpRes.first > tmp.offset() && !carl::AlmostEqual2sComplement( tmpRes.first, tmp.offset() ) ) ) {
						planeIt = mHPlanes.insert( pos, tmp );
						mInitialized = false;
						++planeIt;
						// std::cout << "keep "  << tmp << std::endl;
					} else {
						// std::cout << "erase " << tmp << " which is equal to something." <<
						// std::endl;
						planeIt = pos;
					}
				}
			}  // FEAS
		}	  // loop
	   // std::cout << __func__ << ": Result: " << *this << std::endl;
	}
}

template <typename Number>
bool HPolytope<Number>::isExtremePoint( vector_t<Number> point ) const {
	unsigned cnt = 0;
	for ( const auto &plane : mHPlanes ) {
		Number val = plane.evaluate( point );
		// std::cout << "Eval: " << plane.normal() << " in direction " << point << "
		// = " << val << ", offset is " <<
		// plane.offset() << ", with tolerance: " << abs(plane.offset() - val) <<
		// std::endl;
		if ( carl::AlmostEqual2sComplement( plane.offset(), val ) ) {
			// std::cout << "Increase cnt " << std::endl;
			++cnt;
		} else if ( plane.offset() - val < 0 ) {
			// std::cout << "######" << val << " != " << plane.offset() << std::endl;
			return false;
		}
	}
	// std::cout << "CNT: " << cnt << std::endl;
	return cnt >= mDimension;
}

template <typename Number>
bool HPolytope<Number>::isExtremePoint( const Point<Number> &point ) const {
	return isExtremePoint( point.rawCoordinates() );
}

template <typename Number>
std::pair<Number, SOLUTION> HPolytope<Number>::evaluate( const vector_t<Number> &_direction ) const {
	if ( !mInitialized ) {
		initialize();
	}

	// std::cout << __func__ << ": " << _direction.transpose() << std::endl;

	assert( _direction.rows() == mDimension );

	// std::cout << "Set target: ";
	for ( unsigned i = 0; i < mDimension; i++ ) {
		glp_set_col_bnds( lp, i + 1, GLP_FR, 0.0, 0.0 );
		glp_set_obj_coef( lp, i + 1, double( _direction( i ) ) );
		// std::cout << double(_direction(i)) << ", ";
	}
	// std::cout << std::endl;

	/* solve problem */
	glp_simplex( lp, NULL );

	Number result = glp_get_obj_val( lp );

	// display potential problems
	switch ( glp_get_status( lp ) ) {
		case GLP_OPT:
		case GLP_FEAS: {
			break;
		}
		case GLP_UNBND: {
			return std::make_pair( 1, INFTY );
			break;
		}
		default:
			// std::cout << __func__ << ": " << *this << " in direction " << _direction
			// << std::endl;
			// std::cout << "Unable to find a suitable solution for the support function
			// (linear program). ErrorCode: "
			// << glp_get_status(lp) << std::endl;
			return std::make_pair( 0, INFEAS );
	}
	// std::cout << "Result: " << result << std::endl;

	return std::make_pair( result, FEAS );
}

template <typename Number>
typename HPolytope<Number>::HyperplaneVector::iterator HPolytope<Number>::begin() {
	return mHPlanes.begin();
}

template <typename Number>
typename HPolytope<Number>::HyperplaneVector::const_iterator HPolytope<Number>::begin() const {
	return mHPlanes.begin();
}

template <typename Number>
typename HPolytope<Number>::HyperplaneVector::iterator HPolytope<Number>::end() {
	return mHPlanes.end();
}

template <typename Number>
typename HPolytope<Number>::HyperplaneVector::const_iterator HPolytope<Number>::end() const {
	return mHPlanes.end();
}

/*
 * General interface
 */

template <typename Number>
HPolytope<Number> HPolytope<Number>::linearTransformation( const matrix_t<Number> &A,
														   const vector_t<Number> &b ) const {
	if(!this->empty() && !mHPlanes.empty()) {
		Eigen::FullPivLU<matrix_t<Number>> lu(A);
		// if A has full rank, we can simply retransform, otherwise use double description method.
		if(lu.rank() == A.rows()) {
			//std::cout << "Full rank, retransform!" << std::endl;
			std::pair<matrix_t<Number>, vector_t<Number>> inequalities = this->inequalities();
			return HPolytope<Number>(inequalities.first*A.inverse(), inequalities.first*A.inverse()*b + inequalities.second);
		} else {
			//std::cout << __func__ << " this: " << *this << std::endl;
		//std::cout << __func__ << " vertices: " << std::endl;
		for ( const auto &vertex : this->vertices() ) std::cout << vertex << std::endl;

			//std::cout << "Create intermediate. " << std::endl;

			VPolytope<Number> intermediate( this->vertices() );

			//std::cout << "Intermediate : " << intermediate << std::endl;

			intermediate = intermediate.linearTransformation( A, b );

			//std::cout << "Intermediate : " << intermediate << std::endl;

			HPolytope<Number> res( intermediate );
			return res;
		}
	} else {
		return *this;
	}
}

template <typename Number>
HPolytope<Number> HPolytope<Number>::minkowskiSum( const HPolytope &rhs ) const {
	HPolytope<Number> res;
	Number result;

	// evaluation of rhs in directions of lhs
	for ( unsigned i = 0; i < mHPlanes.size(); ++i ) {
		std::pair<Number, SOLUTION> evalRes = rhs.evaluate( mHPlanes.at( i ).normal() );
		if ( evalRes.second == INFTY ) {
			// Do nothing - omit inserting plane.
		} else if ( evalRes.second == INFEAS ) {
			// TODO: Return empty polytope.
		} else {
			result = mHPlanes.at( i ).offset() + evalRes.first;
			res.insert( Hyperplane<Number>( mHPlanes.at( i ).normal(), result ) );
			// std::cout << __func__ << " Evaluated against " <<
			// mHPlanes.at(i).normal() << std::endl;
		}
	}

	// evaluation of lhs in directions of rhs
	for ( unsigned i = 0; i < rhs.constraints().size(); ++i ) {
		std::pair<Number, SOLUTION> evalRes = this->evaluate( rhs.constraints().at( i ).normal() );
		if ( evalRes.second == INFTY ) {
			// Do nothing - omit inserting plane.
		} else if ( evalRes.second == INFEAS ) {
			// TODO: Return empty polytope.
		} else {
			result = rhs.constraints().at( i ).offset() + evalRes.first;
			res.insert( Hyperplane<Number>( rhs.constraints().at( i ).normal(), result ) );
			// std::cout << __func__ << " Evaluated against " <<
			// mHPlanes.at(i).normal() << std::endl;
		}
	}
	// res.removeRedundantPlanes();
	return res;
}

template <typename Number>
HPolytope<Number> HPolytope<Number>::intersect( const HPolytope &rhs ) const {
	if ( rhs.empty() || this->empty() ) {
		std::cout << "this->empty(): " << this->empty() << ", rhs.empty(): " << rhs.empty() << std::endl;
		return HPolytope<Number>::Empty();
	} else {
		HPolytope<Number> res;
		for ( const auto &plane : mHPlanes ) {
			res.insert( plane );
		}
		for ( const auto &plane : rhs.constraints() ) {
			res.insert( plane );
		}
		if(!res.constraints().empty()) {
			res.removeRedundantPlanes();
		}

		return res;
	}
}

template <typename Number>
HPolytope<Number> HPolytope<Number>::intersectHyperplane( const Hyperplane<Number> &rhs ) const {
}

template <typename Number>
HPolytope<Number> HPolytope<Number>::intersectHyperplanes( const matrix_t<Number> &_mat,
														   const vector_t<Number> &_vec ) const {
	assert( _mat.rows() == _vec.rows() );
	//std::cout << __func__ << std::endl;

	HPolytope<Number> res( *this );

	//std::cout << "intersection Vertices before intersection: " << std::endl;
	//for(const auto& vertex : this->vertices()) {
	//	std::cout << vertex.rawCoordinates().transpose() << std::endl;
	//}

	for ( unsigned i = 0; i < _mat.rows(); ++i ) {
		res.insert( Hyperplane<Number>( _mat.row( i ), _vec( i ) ) );
	}

	//std::cout << "intersection Result before reduction: " << std::endl;
	//std::cout << res << std::endl;
	if(!res.empty()) {
		res.removeRedundantPlanes();
	} else {
		res = HPolytope<Number>::Empty();
	}

	//std::cout << "intersection Result AFTER reduction: " << std::endl;
	//std::cout << res << std::endl;

	return res;
}

template <typename Number>
bool HPolytope<Number>::contains( const Point<Number> &point ) const {
	return this->contains( point.rawCoordinates() );
}

template <typename Number>
bool HPolytope<Number>::contains( const vector_t<Number> &vec ) const {
	// std::cout << __func__ << "  " << vec << ": ";
	for ( const auto &plane : mHPlanes ) {
		// std::cout << plane << ": " << plane.normal().dot(vec) << ", -> " <<
		// (!carl::AlmostEqual2sComplement(plane.normal().dot(vec),
		// plane.offset(),TOLLERANCE_ULPS) &&
		// plane.normal().dot(vec) > plane.offset()) << std::endl;
		// carl::AlmostEqual2sComplement(plane.normal().dot(vec), plane.offset());
		if ( !carl::AlmostEqual2sComplement( plane.normal().dot( vec ), plane.offset(), TOLLERANCE_ULPS ) &&
			 plane.normal().dot( vec ) > plane.offset() ) {
			//std::cout << vec.transpose() << " not contained in " << plane.normal().transpose()
			//		  << " <= " << plane.offset() << "(is: " << plane.normal().dot( vec ) << ")" << std::endl;
			return false;
		}
	}
	return true;
}

template <typename Number>
bool HPolytope<Number>::contains( const HPolytope<Number> &rhs ) const {
	for ( const auto &plane : rhs ) {
		std::pair<Number, SOLUTION> evalRes = this->evaluate( plane.normal() );
		if ( evalRes.second == INFEAS ) {
			return false;  // empty!
		} else if ( evalRes.second == INFTY ) {
			continue;
		} else if ( evalRes.first < plane.offset() &&
					!carl::AlmostEqual2sComplement( evalRes.first, plane.offset() ) ) {
			return false;
		}
	}
	return true;
}

template <typename Number>
HPolytope<Number> HPolytope<Number>::unite( const HPolytope &_rhs ) const {
	if ( _rhs.empty() ) {
		return HPolytope<Number>( *this );
	} else {
		VPolytope<Number> lhs( this->vertices() );
		VPolytope<Number> tmpRes = lhs.unite( VPolytope<Number>( _rhs.vertices() ) );

		return HPolytope<Number>( tmpRes );
	}
}

template <typename Number>
void HPolytope<Number>::clear() {
	mHPlanes.clear();
	mFanSet = false;
	mDimension = 0;
	deleteArrays();
	mInitialized = false;
}

template <typename Number>
void HPolytope<Number>::print() const {
	std::cout << *this << std::endl;
}

/*
 * Operators
 */

template <typename Number>
const Hyperplane<Number>& HPolytope<Number>::operator[]( size_t i ) const {
	return mHPlanes.at( i );
}

template <typename Number>
Hyperplane<Number>& HPolytope<Number>::operator[]( size_t i ) {
	return mHPlanes.at( i );
}

template <typename Number>
HPolytope<Number> &HPolytope<Number>::operator=( const HPolytope<Number> &rhs ) {
	if ( this != &rhs ) {
		HPolytope<Number> tmp( rhs );
		swap( *this, tmp );
	}
	return *this;
}

/*
 * Auxiliary functions
 */

template <typename Number>
void HPolytope<Number>::createArrays( unsigned size ) const {
	ia = new int[size + 1];
	ja = new int[size + 1];
	ar = new double[size + 1];
}

template <typename Number>
void HPolytope<Number>::deleteArrays() {
	delete[] ia;
	delete[] ja;
	delete[] ar;
}

template <typename Number>
void HPolytope<Number>::printArrays() {
	if ( !mInitialized ) {
		initialize();
	}
	unsigned size = mHPlanes.size() * mDimension;
	std::cout << "IA: ";
	for ( unsigned pos = 0; pos < size; ++pos ) {
		std::cout << ia[pos] << ", ";
	}
	std::cout << std::endl;
}

template <typename Number>
void HPolytope<Number>::initialize() const {
	if ( !mInitialized ) {
		/* create glpk problem */
		lp = glp_create_prob();
		glp_set_prob_name( lp, "hpoly" );
		glp_set_obj_dir( lp, GLP_MAX );
		glp_term_out( GLP_OFF );

		unsigned numberOfConstraints = mHPlanes.size();

		// convert constraint constants
		glp_add_rows( lp, numberOfConstraints );
		for ( unsigned i = 0; i < numberOfConstraints; i++ ) {
			glp_set_row_bnds( lp, i + 1, GLP_UP, 0.0, double( mHPlanes[i].offset() ) );
		}

		// add cols here
		glp_add_cols( lp, mDimension );
		createArrays( numberOfConstraints * mDimension );

		// convert constraint matrix
		ia[0] = 0;
		ja[0] = 0;
		ar[0] = 0;
		for ( unsigned i = 0; i < numberOfConstraints * mDimension; ++i ) {
			ia[i + 1] = ( (int)( i / mDimension ) ) + 1;
			// std::cout << __func__ << " set ia[" << i+1 << "]= " << ia[i+1];
			ja[i + 1] = ( (int)( i % mDimension ) ) + 1;
			// std::cout << ", ja[" << i+1 << "]= " << ja[i+1];
			ar[i + 1] = double( mHPlanes[ia[i + 1] - 1].normal()( ja[i + 1] - 1 ) );
			// std::cout << ", ar[" << i+1 << "]=" << ar[i+1] << std::endl;
		}

		glp_load_matrix( lp, numberOfConstraints * mDimension, ia, ja, ar );
		mInitialized = true;
	}
}

}  // namespace hypro
