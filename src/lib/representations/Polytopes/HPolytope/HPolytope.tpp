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
HPolytope<Number>::HPolytope( const Hyperplane<Number> &plane )
	: mHPlanes( {plane} ), mFanSet( false ), mFan(), mDimension( plane.dimension() ), mInitialized( false ) {
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
		if ( size < mDimension ) {
			// TODO
			assert( false );
		} else if ( size == mDimension ) {
			typename std::vector<Point<Number>> points = alien.vertices();
			std::vector<vector_t<Number>> rawPoints;
			for ( const auto point : points ) rawPoints.push_back( point.rawCoordinates() );

			vector_t<Number> root = rawPoints.back();
			rawPoints.pop_back();
			mHPlanes.push_back( Hyperplane<Number>( root, rawPoints ) );

		} else {
			typename std::vector<Point<Number>> points = alien.vertices();
			std::vector<std::shared_ptr<Facet<Number>>> facets = convexHull( points ).first;
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
			std::cout << "Use planes ";
			for(const auto item : permutation)
				std::cout << item << ", ";
			std::cout << std::endl;

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
					std::cout << ( Number( res( i ) ) ) << " is infty." << std::endl;
					infty = true;
					break;
				}
			}

			if(!infty) {
				std::cout << "Solved to " << res.transpose() << std::endl;
				// check if point lies above all planes -> if not, ensure by enlarging the polytope (very expensive)
				bool below = false;
				for(auto planeIt = permutation.begin(); planeIt != permutation.end(); ++planeIt) {
					Number dist = mHPlanes.at(*planeIt).offset() - mHPlanes.at(*planeIt).normal().dot(res);
					if(dist > 0) {
						below = true;
						break;
					}
				}
				Number eps = 0;
				while (below) {
					std::cout << "Is below, iterate " << std::endl;
					// enlarge as long as point lies below one of the planes.
					below = false;
					eps += std::numeric_limits<Number>::epsilon();

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
							below = true;
							break;
						}
					}
					if(!below)
						res = tmp;
				}

				// Check containment
				bool outside = false;
				for(unsigned planePos = 0; planePos < mHPlanes.size(); ++planePos) {
					bool skip = false;
					for(unsigned permPos = 0; permPos < permutation.size(); ++permPos) {
						if(planePos == permutation.at(permPos)) {
							std::cout << "Skip plane " << planePos << std::endl;
							skip = true;
							break;
						}
					}

					if(!skip) {
						if( mHPlanes.at(planePos).offset() - mHPlanes.at(planePos).normal().dot(res) < 0 ) {
							std::cout << "Drop vertex: " << res.transpose() << " because of plane " << planePos << std::endl;
							outside = true;
							break;
						}
					}
				}
				if(!outside) {
					vertices.push_back(Point<Number>(res));
					std::cout << "Final vertex: " << res.transpose() << std::endl;
				}
			}
			std::cout << "PING" << std::endl;
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
HPolytope<Number> HPolytope<Number>::reduce_nd() const { // REDUCTION_STRATEGY
	HPolytope<Number> res = *this;

	/*
	// STRAT: Drop_normal
	unsigned i = 4;
	res.mHPlanes.erase(res.mHPlanes.begin()+i);
	*/

	///*
	// STRAT: Drop_smooth

	vector_t<Number> bVector_smooth = res.mHPlanes[1].normal()+res.mHPlanes[4].normal(); // special case: 3 neighboors and we know where TODO find neighboors
	Number bVector_smooth_offset = res.mHPlanes[1].offset()+res.mHPlanes[4].offset();
	vector_t<Number> cVector_smooth = res.mHPlanes[2].normal()+res.mHPlanes[4].normal();
	Number cVector_smooth_offset = res.mHPlanes[2].offset()+res.mHPlanes[4].offset();
	vector_t<Number> dVector_smooth = res.mHPlanes[3].normal()+res.mHPlanes[4].normal();
	Number dVector_smooth_offset = res.mHPlanes[3].offset()+res.mHPlanes[4].offset();

	res.mHPlanes.erase(res.mHPlanes.begin()+1); // b <- neighboor
	res.mHPlanes.erase(res.mHPlanes.begin()+1); // c <- neighboor
	res.mHPlanes.erase(res.mHPlanes.begin()+1); // d <- neighboor
	res.mHPlanes.erase(res.mHPlanes.begin()+1); // e <- target

	res.insert(Hyperplane<Number>(bVector_smooth,bVector_smooth_offset)); // b_smooth
	res.insert(Hyperplane<Number>(cVector_smooth,cVector_smooth_offset)); // c_smooth
	res.insert(Hyperplane<Number>(dVector_smooth,dVector_smooth_offset)); // d_smooth
	//*/

	/*
	// STRAT: Unite_normal
	vector_t<Number> uniteVector = res.mHPlanes[2].normal()+res.mHPlanes[4].normal(); // special case: 3 neighboors and we know where TODO find neighboors
	Number uniteVector_offset = res.mHPlanes[2].offset()+res.mHPlanes[4].offset();

	res.mHPlanes.erase(res.mHPlanes.begin()+4); // e
	res.mHPlanes.erase(res.mHPlanes.begin()+2); // c

	res.insert(Hyperplane<Number>(uniteVector,uniteVector_offset)); // uniteVector
	*/

	/*
	// STRAT: Unite_smooth
	vector_t<Number> e_bVector_normalized = res.mHPlanes[4].normal()+res.mHPlanes[1].normal(); // eVector Part: add e+neighboor(except "partner") and normalize TODO find neighboors
	e_bVector_normalized.normalize();
	vector_t<Number> e_dVector_normalized = res.mHPlanes[4].normal()+res.mHPlanes[3].normal();
	e_dVector_normalized.normalize();

	vector_t<Number> c_aVector_normalized = res.mHPlanes[2].normal()+res.mHPlanes[0].normal(); // cVector Part: add c+neighboor(except "partner") and normalize
	c_aVector_normalized.normalize();
	vector_t<Number> c_bVector_normalized = res.mHPlanes[2].normal()+res.mHPlanes[1].normal();
	c_bVector_normalized.normalize();
	vector_t<Number> c_dVector_normalized = res.mHPlanes[2].normal()+res.mHPlanes[3].normal();
	c_dVector_normalized.normalize();

	vector_t<Number> uniteVector = e_bVector_normalized + e_dVector_normalized + c_aVector_normalized + c_bVector_normalized + c_dVector_normalized;
	Number uniteVector_offset = uniteVector[0]*(-5.6) + uniteVector[1]*2.8 + uniteVector[2]*2; //uniteVector[0]*2.8 + uniteVector[1]*(-5.6) + uniteVector[2]*2; // is the same TODO calculate the cutPoint

	res.mHPlanes.erase(res.mHPlanes.begin()+4); // e
	res.mHPlanes.erase(res.mHPlanes.begin()+2); // c

	res.insert(Hyperplane<Number>(uniteVector,uniteVector_offset)); // uniteVector
	*/

	/*
	// STRAT: Unite_cut
	// TODO check if calculate facet for uniteVector is correct
	// TODO calculate the facet
	Number uniteVector_offset = (-18)*(-5.6) + (-18)*2.8 + (77.4)*2; // TODO calculate cutPoint

	res.mHPlanes.erase(res.mHPlanes.begin()+4); // e
	res.mHPlanes.erase(res.mHPlanes.begin()+2); // c

	res.insert(Hyperplane<Number>({-18,-18,77.4},uniteVector_offset)); // uniteVector
	*/

	/*
	// STRAT: Unite_norm
	// TODO compute weights
	vector_t<Number> uniteVector = res.mHPlanes[2].normal()*(2)+res.mHPlanes[4].normal()*(5.9); // weights are calculated by hand
	Number uniteVector_offset = uniteVector[0]*(-5.6) + uniteVector[1]*2.8 + uniteVector[2]*2;

	res.mHPlanes.erase(res.mHPlanes.begin()+4); // e
	res.mHPlanes.erase(res.mHPlanes.begin()+2); // c

	res.insert(Hyperplane<Number>(uniteVector,uniteVector_offset)); // uniteVector
	*/

	return res;
}

template <typename Number>
HPolytope<Number> HPolytope<Number>::reduce(  int strat, unsigned _steps ) const { // REDUCTION_STRATEGY
	HPolytope<Number> res = *this;
	unsigned size=res.mHPlanes.size()-1;

	// TODO check strat on facet drop_normal, drop_smooth, unite_normal, unite_norm - unite_smooth, unite_cut?

	std::pair<unsigned, unsigned> recommended = chooseStrat();

	if(strat>=0){
		recommended.first = strat; // fix strategy
		recommended.second = _steps; // fix facet TODO normally not _steps!
	} else {
		//recommended = chooseStrat();
	}

	// Switch strategy, implement each strategy.
	switch (recommended.first) { // (strat) {

		// DROP
		case REDUCTION_STRATEGY::DROP:
		{
			unsigned a=recommended.second;
			unsigned next_a=a+1,  prev_a=a-1;

			// select prev_a and next_a propely
			if(next_a>size){
				next_a=0;
			}
			else if(a==0){
				prev_a=size;
			}

			// compute scalarproduct
			vector_t<Number> aVector = res.mHPlanes[a].normal();
			aVector.normalize();
			vector_t<Number> prev_aVector = res.mHPlanes[prev_a].normal();
			prev_aVector.normalize();
			vector_t<Number> next_aVector = res.mHPlanes[next_a].normal();
			next_aVector.normalize();
			double scalarproductPrev = aVector.dot(prev_aVector);
			double scalarproductNext = aVector.dot(next_aVector);

			if(scalarproductPrev+scalarproductNext>0){ // check possibility
				res.mHPlanes.erase(res.mHPlanes.begin()+a);
			} else {
				std::cout << " Drop impossible! " << std::endl;
			}
			break;
		}

		// DROP_SMOOTH
		case REDUCTION_STRATEGY::DROP_SMOOTH:
		{
			unsigned a=recommended.second, next_a=a+1, next2_a=a+2,  prev_a=a-1, prev2_a=a-2;

			// select prev_a and next_a propely
			if(next_a>size){
				next_a=0;
				next2_a=1;
			}
			else if(next2_a>size){
				next2_a=0;
			}
			else if(a==0){
				prev_a=size;
				prev2_a=size-1;
			}
			else if(prev_a==0){
				prev2_a=size;
			}

			// compute scalarproduct
			vector_t<Number> prev_aVector = res.mHPlanes[prev_a].normal();
			prev_aVector.normalize();
			vector_t<Number> prev2_aVector = res.mHPlanes[prev2_a].normal();
			prev2_aVector.normalize();
			vector_t<Number> next_aVector = res.mHPlanes[next_a].normal();
			next_aVector.normalize();
			vector_t<Number> next2_aVector = res.mHPlanes[next2_a].normal();
			next2_aVector.normalize();

			vector_t<Number> next_a_aVector = res.mHPlanes[a].normal() + res.mHPlanes[next_a].normal();
			vector_t<Number> nextVector = next_a_aVector;
			nextVector.normalize();
			Number next_a_aOffset = res.mHPlanes[a].offset() + res.mHPlanes[next_a].offset();
			vector_t<Number> prev_a_aVector = res.mHPlanes[a].normal() + res.mHPlanes[prev_a].normal();
			vector_t<Number> prevVector = prev_a_aVector;
			prevVector.normalize();
			Number prev_a_aOffset = res.mHPlanes[a].offset() + res.mHPlanes[prev_a].offset();

			double scalarproductPrev = prevVector.dot(prev_aVector);
			//std::cout << "SPPrev: " << scalarproductPrev << std::endl;
			double scalarproductPrev2 = prev_aVector.dot(prev2_aVector);
			//std::cout << "SPPrev2: " << scalarproductPrev2 << std::endl;
			double scalarproductNext = nextVector.dot(next_aVector);
			//std::cout << "SPNext: " << scalarproductNext << std::endl;
			double scalarproductNext2 = next_aVector.dot(next2_aVector);
			//std::cout << "SPNext2: " << scalarproductNext2 << std::endl;

			if(scalarproductPrev+scalarproductPrev2>0 && scalarproductNext+scalarproductNext2>0 ) {
				res.mHPlanes.erase(res.mHPlanes.begin()+a); // erase a
				if(next_a==0){ // erase next_a propely
					res.mHPlanes.erase(res.mHPlanes.begin()+prev_a); // erase prev_a
					res.mHPlanes.erase(res.mHPlanes.begin()); // erase next_a
				} else if(a==0){ // erase prev_a propely
					res.mHPlanes.erase(res.mHPlanes.begin()); // erase next_a
					res.mHPlanes.erase(res.mHPlanes.begin()+size); // erase prev_a
				} else {
					res.mHPlanes.erase(res.mHPlanes.begin()+prev_a); // erase prev_a
					res.mHPlanes.erase(res.mHPlanes.begin()+prev_a); // erase next_a
				}

				res.insert(Hyperplane<Number>(next_a_aVector,next_a_aOffset));
				res.insert(Hyperplane<Number>(prev_a_aVector,prev_a_aOffset));
			} else {
				std::cout << " Drop_smooth impossible! " << std::endl;
			}
			break;
		}

		// UNITE
		case REDUCTION_STRATEGY::UNITE:
		{
			unsigned a=recommended.second, b=a+1, prev_a=a-1,  next_b=b+1;

			// select b, prev_a and next_b propely
			if(b>size){
				b=0;
				next_b=1;
			}
			else if(next_b>size){
				next_b=0;
			}
			else if(a==0){
				prev_a=size;
			}

			vector_t<Number> uniteVector = res.mHPlanes[a].normal() + res.mHPlanes[b].normal(); // calculate the uniteVector (i+j)
			Number uniteOffset = res.mHPlanes[a].offset() + res.mHPlanes[b].offset(); // calculate the uniteOffset (i+j)

			vector_t<Number> bVector = res.mHPlanes[b].normal();
			bVector.normalize();
			vector_t<Number> next_bVector = res.mHPlanes[next_b].normal();
			next_bVector.normalize();
			vector_t<Number> aVector = res.mHPlanes[a].normal();
			aVector.normalize();
			vector_t<Number> prev_aVector = res.mHPlanes[prev_a].normal();
			prev_aVector.normalize();
			vector_t<Number> uniteVectorNormalized = uniteVector;
			uniteVectorNormalized.normalize();
			double scalarproductPrev = uniteVectorNormalized.dot(aVector);
			//std::cout << "SPPrev: " << scalarproductPrev << " of (c) " << uniteVectorNormalized << " and (p) " << aVector <<  std::endl;
			double scalarproductPrev2 = aVector.dot(prev_aVector);
			//std::cout << "SPPrev: " << scalarproductPrev2 << " of (p) " << aVector << " and (p2) " << prev_aVector <<  std::endl;
			double scalarproductNext = uniteVectorNormalized.dot(bVector);
			//std::cout << "SPNext: " << scalarproductNext << " of (c) " << uniteVectorNormalized << " and (n) " << bVector <<std::endl;
			double scalarproductNext2 = bVector.dot(next_bVector);
			//std::cout << "SPNext: " << scalarproductNext << " of (n) " << bVector << " and (n2) " << next_bVector <<std::endl;

			if(scalarproductPrev+scalarproductPrev2>0 && scalarproductNext+scalarproductNext2>0){ // check possibility
				res.mHPlanes.erase(res.mHPlanes.begin()+a);
				if(b==0){ // erase b propely
					res.mHPlanes.erase(res.mHPlanes.begin());
				} else {
					res.mHPlanes.erase(res.mHPlanes.begin()+a);
				}
				res.insert(Hyperplane<Number>(uniteVector,uniteOffset));
			} else {
				std::cout << " Unite_normal impossible! " << std::endl;
			}
			break;
		}

		// UNITE_SMOOTH
		case REDUCTION_STRATEGY::UNITE_SMOOTH:
		{
			unsigned a=recommended.second, b=a+1, prev_a=a-1,  next_b=b+1;

			// select b, prev_a and next_b propely
			if(b>size){
				b=0;
				next_b=1;
			}
			else if(next_b>size){
				next_b=0;
			}
			else if(a==0){
				prev_a=size;
			}

			// calculate next_b+b and prev_a+a -- normalized to keep the proportion
			vector_t<Number> prev_a_aVector = res.mHPlanes[a].normal() + res.mHPlanes[prev_a].normal();
			prev_a_aVector.normalize();
			vector_t<Number> next_b_bVector = res.mHPlanes[b].normal() + res.mHPlanes[next_b].normal();
			next_b_bVector.normalize();

			// Helpvalues to calculate the correct uniteOffset
			std::pair<Number, Number> center = cut(res.mHPlanes[a], res.mHPlanes[b]);

			vector_t<Number> uniteVector = next_b_bVector + prev_a_aVector; // calculate uniteVector (next_b+b + prev_a+a)
			Number uniteOffset = uniteVector[0]*center.first + uniteVector[1]*center.second; // calculate the actual uniteOffset

			vector_t<Number> bVector = res.mHPlanes[b].normal();
			bVector.normalize();
			vector_t<Number> next_bVector = res.mHPlanes[next_b].normal();
			next_bVector.normalize();
			vector_t<Number> aVector = res.mHPlanes[a].normal();
			aVector.normalize();
			vector_t<Number> prev_aVector = res.mHPlanes[prev_a].normal();
			prev_aVector.normalize();
			vector_t<Number> uniteVectorNormalized = uniteVector;
			uniteVectorNormalized.normalize();
			double scalarproductPrev = uniteVectorNormalized.dot(aVector);
			//std::cout << "SPPrev: " << scalarproductPrev << " of (c) " << uniteVectorNormalized << " and (p) " << aVector <<  std::endl;
			double scalarproductPrev2 = aVector.dot(prev_aVector);
			//std::cout << "SPPrev: " << scalarproductPrev2 << " of (p) " << aVector << " and (p2) " << prev_aVector <<  std::endl;
			double scalarproductNext = uniteVectorNormalized.dot(bVector);
			//std::cout << "SPNext: " << scalarproductNext << " of (c) " << uniteVectorNormalized << " and (n) " << bVector <<std::endl;
			double scalarproductNext2 = bVector.dot(next_bVector);
			//std::cout << "SPNext: " << scalarproductNext << " of (n) " << bVector << " and (n2) " << next_bVector <<std::endl;

			if(scalarproductPrev+scalarproductPrev2>0 && scalarproductNext+scalarproductNext2>0){ // check possibility
				res.mHPlanes.erase(res.mHPlanes.begin()+a);
				if(b==0){ // erase b propely
					res.mHPlanes.erase(res.mHPlanes.begin());
				} else {
					res.mHPlanes.erase(res.mHPlanes.begin()+a);
				}
				res.insert(Hyperplane<Number>(uniteVector,uniteOffset));
			} else {
					std::cout << " Unite_smooth impossible! " << std::endl;
			}
			break;
		}

		// UNITE_CUT
		case REDUCTION_STRATEGY::UNITE_CUT:
		{
			unsigned a=recommended.second, b=a+1, prev_a=a-1, next_b=b+1;

			// select b, prev_a and next_b propely
			if(b>size){
				b=0;
				next_b=1;
			}
			else if(next_b>size){
				next_b=0;
			}
			else if(a==0){
				prev_a=size;
			}

			// Helpvalues to calculate the correct uniteVector and uniteOffset - prev_Cut, next_Cut and Cut
			std::pair<Number, Number> prev = cut(res.mHPlanes[prev_a], res.mHPlanes[a]);
			std::pair<Number, Number> next = cut(res.mHPlanes[b], res.mHPlanes[next_b]);
			std::pair<Number, Number> center = cut(res.mHPlanes[a], res.mHPlanes[b]);

			res.mHPlanes.erase(res.mHPlanes.begin()+a);
			if(b==0){ // erase b propely
				res.mHPlanes.erase(res.mHPlanes.begin());
			} else {
				res.mHPlanes.erase(res.mHPlanes.begin()+a);
			}
			res.insert(Hyperplane<Number>(	{prev.second-next.second,next.first-prev.first}, // UniteVector
																			(prev.second-next.second)*center.first + (next.first-prev.first)*center.second)); // UniteOffset
			break;
		}

		// UNITE_NORM
		case REDUCTION_STRATEGY::UNITE_NORM:
		{
			unsigned a=recommended.second, b=a+1, prev_a=a-1, next_b=b+1;

			// select b, prev_a and next_b propely
			if(b>size){
				b=0;
				next_b=1;
			}
			else if(next_b>size){
				next_b=0;
			}
			else if(a==0){
				prev_a=size;
			}

			// Helpvalues to calculate the correct uniteVector and uniteOffset - prev_Cut, next_Cut and Cut
			std::pair<Number, Number> prev = cut(res.mHPlanes[prev_a], res.mHPlanes[a]);
			std::pair<Number, Number> next = cut(res.mHPlanes[b], res.mHPlanes[next_b]);
			std::pair<Number, Number> center = cut(res.mHPlanes[a], res.mHPlanes[b]);

			double prev_center = sqrt(pow(center.first-prev.first,2) + pow(center.second-prev.second,2));
			double center_next = sqrt(pow(next.first-center.first,2) + pow(next.second-center.second,2));

			vector_t<Number> uniteVector = prev_center*res.mHPlanes[a].normal() + center_next*res.mHPlanes[b].normal(); // calculate uniteVector (next_b+b + prev_a+a)
			Number uniteOffset = uniteVector[0]*center.first + uniteVector[1]*center.second; // calculate the actual uniteOffset

			vector_t<Number> bVector = res.mHPlanes[b].normal();
			bVector.normalize();
			vector_t<Number> next_bVector = res.mHPlanes[next_b].normal();
			next_bVector.normalize();
			vector_t<Number> aVector = res.mHPlanes[a].normal();
			aVector.normalize();
			vector_t<Number> prev_aVector = res.mHPlanes[prev_a].normal();
			prev_aVector.normalize();
			vector_t<Number> uniteVectorNormalized = uniteVector;
			uniteVectorNormalized.normalize();
			double scalarproductPrev = uniteVectorNormalized.dot(aVector);
			//std::cout << "SPPrev: " << scalarproductPrev << " of (c) " << uniteVectorNormalized << " and (p) " << aVector <<  std::endl;
			double scalarproductPrev2 = aVector.dot(prev_aVector);
			//std::cout << "SPPrev: " << scalarproductPrev2 << " of (p) " << aVector << " and (p2) " << prev_aVector <<  std::endl;
			double scalarproductNext = uniteVectorNormalized.dot(bVector);
			//std::cout << "SPNext: " << scalarproductNext << " of (c) " << uniteVectorNormalized << " and (n) " << bVector <<std::endl;
			double scalarproductNext2 = bVector.dot(next_bVector);
			//std::cout << "SPNext: " << scalarproductNext << " of (n) " << bVector << " and (n2) " << next_bVector <<std::endl;

			if(scalarproductPrev+scalarproductPrev2>0 && scalarproductNext+scalarproductNext2>0){ // check possibility
				res.mHPlanes.erase(res.mHPlanes.begin()+a);
				if(b==0){ // erase b propely
					res.mHPlanes.erase(res.mHPlanes.begin());
				} else {
					res.mHPlanes.erase(res.mHPlanes.begin()+a);
				}
				res.insert(Hyperplane<Number>(uniteVector, uniteOffset));
			} else {
				std::cout << " Unite_norm impossible! " << std::endl;
			}
			break;
		}

		default:
			break;
	}

	return res;
}

template <typename Number>
void HPolytope<Number>::reduceAssign( REDUCTION_STRATEGY strat, unsigned _steps ) {

	// TODO.

}

template <typename Number>
std::pair<unsigned, unsigned> HPolytope<Number>::chooseStrat() const{
	unsigned maxIndex=0, strat=0;
	double maxScalarproduct=-1;
	HPolytope<Number> hpolytope = *this;

	// normalize vectors
	for(unsigned index=0; index<hpolytope.mHPlanes.size(); index++){
		hpolytope.mHPlanes[index].rNormal().normalize();
	}

	// compare scalarproduct of neighboors of index (Drop)/ neighboors (Unite)
	// *** If we focus only on the SP unite will always be closer as drop! ***
	// *** TODO focus on distance also ***
	// *** TODO decide for which Unite_...  or which Drop_... ***

	for(unsigned index=0; index<hpolytope.mHPlanes.size(); index++){
		double scalarproduct_drop=1, scalarproduct_unite=1;
		if(index==hpolytope.mHPlanes.size()-2){
			scalarproduct_drop = hpolytope.mHPlanes[index].normal().dot(hpolytope.mHPlanes[0].normal()); // Drop
			scalarproduct_unite = hpolytope.mHPlanes[index].normal().dot(hpolytope.mHPlanes[index+1].normal()); // Unite
		}
		else if(index==hpolytope.mHPlanes.size()-1){
			scalarproduct_drop = hpolytope.mHPlanes[index].normal().dot(hpolytope.mHPlanes[1].normal()); // Drop
			scalarproduct_unite = hpolytope.mHPlanes[index].normal().dot(hpolytope.mHPlanes[0].normal()); // Unite
		}
		else {
			scalarproduct_drop = hpolytope.mHPlanes[index].normal().dot(hpolytope.mHPlanes[index+2].normal()); // Drop
			scalarproduct_unite = hpolytope.mHPlanes[index].normal().dot(hpolytope.mHPlanes[index+1].normal()); // Unite
		}

		if(scalarproduct_drop<scalarproduct_unite && maxScalarproduct<scalarproduct_unite){ // decide for Unite
			strat=4;
			maxScalarproduct=scalarproduct_unite;
			maxIndex=index;
		}
		else if(maxScalarproduct<scalarproduct_drop){ // decide for Drop
			strat=1;
			maxScalarproduct=scalarproduct_drop;
			maxIndex=index+1;
			if(maxIndex>=hpolytope.mHPlanes.size()) maxIndex=0;
		}

		//std::cout << "[Drop] SP between " << index << " and " << index+2 << " is " << scalarproduct_drop << std::endl;
		//std::cout << "[Unite] SP between " << index << " and " << index+1 << " is " << scalarproduct_unite << std::endl;
	}

	return std::pair<unsigned, unsigned>(strat, maxIndex);
}

template <typename Number>
unsigned HPolytope<Number>::getIndexForDrop() const{

	unsigned maxIndex=0;
	double maxScalarproduct=-1;
	HPolytope<Number> hpolytope = *this;

	// normalize vectors
	for(unsigned index=0; index<hpolytope.mHPlanes.size(); index++){
		hpolytope.mHPlanes[index].rNormal().normalize();
	}

	// compare scalarproduct of neighboors of index
	for(unsigned index=0; index<hpolytope.mHPlanes.size(); index++){
		double scalarproduct=1;
		if(index==hpolytope.mHPlanes.size()-2){
			scalarproduct = hpolytope.mHPlanes[index].normal().dot(hpolytope.mHPlanes[0].normal());
		} else if(index==hpolytope.mHPlanes.size()-1){
			scalarproduct = hpolytope.mHPlanes[index].normal().dot(hpolytope.mHPlanes[1].normal());
		} else {
			scalarproduct = hpolytope.mHPlanes[index].normal().dot(hpolytope.mHPlanes[index+2].normal());
		}
		if(scalarproduct>maxScalarproduct){
			maxScalarproduct=scalarproduct;
			maxIndex=index+1;
			if(maxIndex>=hpolytope.mHPlanes.size()){
				maxIndex=0;
			}
		}
	}
	return maxIndex;
}

template <typename Number>
unsigned HPolytope<Number>::getIndexForUnite() const{
	unsigned maxIndex=0;
	double maxScalarproduct=-1;
	HPolytope<Number> hpolytope = *this;

	// normalize vectors
	for(unsigned index=0; index<hpolytope.mHPlanes.size(); index++){
		hpolytope.mHPlanes[index].rNormal().normalize();
	}

	// compare scalarproduct of neighboors
	for(unsigned index=0; index<hpolytope.mHPlanes.size(); index++){
		double scalarproduct=1;
		if(index==hpolytope.mHPlanes.size()-1){
			scalarproduct = hpolytope.mHPlanes[index].normal().dot(hpolytope.mHPlanes[0].normal());
		} else {
			scalarproduct = hpolytope.mHPlanes[index].normal().dot(hpolytope.mHPlanes[index+1].normal());
		}
		if(scalarproduct>maxScalarproduct){
			maxScalarproduct=scalarproduct;
			maxIndex=index;
		}
	}

	return maxIndex;
}

template <typename Number>
std::pair<Number, Number> HPolytope<Number>::cut(Hyperplane<Number> a, Hyperplane<Number> b) const{
	// save aVector and bVector
	vector_t<Number> aVector = a.normal();
	vector_t<Number> bVector = b.normal();
	Number aOffset = a.offset();
	Number bOffset = b.offset();

	double helpx2_top, helpx2_down, x1, x2;
	if(aVector[0]!=0){
		helpx2_top = bOffset - (bVector[0]*aOffset/aVector[0]);
		helpx2_down = bVector[1] - (bVector[0]*aVector[1]/aVector[0]);
		x2 = helpx2_top/helpx2_down;
		x1 = (aOffset - aVector[1]*x2)/aVector[0];
	} else {
		helpx2_top = aOffset - (aVector[0]*bOffset/bVector[0]);
		helpx2_down = aVector[1] - (aVector[0]*bVector[1]/bVector[0]);
		x2 = helpx2_top/helpx2_down;
		x1 = (bOffset - bVector[1]*x2)/bVector[0];
	}

	return std::pair<Number, Number>(x1, x2);
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

/*
template<typename Number>
Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, Eigen::Dynamic>
HPolytope<Number>::getOptimalDictionary(
		const Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic,
Eigen::Dynamic> A,
		unsigned dimension,
		std::vector<unsigned>& B,
		std::vector<unsigned>& N) const
{
		typedef Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic,
Eigen::Dynamic> matrix_t;
		typedef Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, 1>
vector_t;
		typedef Eigen::Matrix<carl::FLOAT_T<Number>, 1, Eigen::Dynamic> row_t;
		// create matrix from HPlanes
		const unsigned numRows = mHPlanes.size() -
mHPlanes.begin()->dimension();
		const unsigned numCols = mHPlanes.begin()->dimension() + 1;
		matrix_t dictionary = matrix_t(numRows, numCols);

		// Assumption: The last d equations of A are linear independent
		auto bottom = A.bottomRows(dimension);
		auto top = A.topRows(A.rows()-dimension);
		auto varBlock = bottom.rightCols(dimension);
		auto constPart = bottom.leftCols(1);

		matrix_t tmp = matrix_t(varBlock);
		vector_t b = vector_t(constPart);

		matrix_t a(tmp.rows(), 2*dimension+1);
		a << tmp, -b, matrix_t::Identity(dimension,dimension);

		//normalize rows for each variable and forward insertion
		for(unsigned rowIndex = 0; rowIndex < a.rows()-1; ++rowIndex)
		{
				a.row(rowIndex) = a.row(rowIndex)/a(rowIndex,rowIndex);
				a.row(rowIndex+1) = a.row(rowIndex+1) -
(a.row(rowIndex)*a(rowIndex+1, rowIndex));
		}

		// backward insertion
		for(unsigned rowIndex = a.rows()-1; rowIndex > 0; --rowIndex)
		{
				if(a(rowIndex,rowIndex) != 1)
				{
						a.row(rowIndex) = a.row(rowIndex) /
a(rowIndex,rowIndex);
				}
				a.row(rowIndex-1) = a.row(rowIndex-1) -
(a.row(rowIndex)*a(rowIndex-1, rowIndex));
		}

		auto substitutionBlock = a.rightCols(dimension+1);

		for(unsigned rI = 0; rI < top.rows(); ++rI)
		{
				dictionary(rI,0) = top(rI,0);

				for(unsigned dI = 1; dI < top.cols(); ++dI)
				{
						dictionary.row(rI) = dictionary.row(rI) + (top(rI,dI) *
substitutionBlock.row(dI-1));
				}
		}

		// Augment dictionary by a row of -1s
		dictionary.conservativeResize(numRows+1,Eigen::NoChange_t());

		row_t allOnes = matrix_t::Constant(1,numCols,
carl::FLOAT_T<Number>(-1));
		allOnes(0) = carl::FLOAT_T<Number>(0);
		dictionary.row(numRows) = allOnes;

		//std::cout << "Optimal dictionary: " << dictionary << std::endl;
		for(unsigned index = 0; index < mHPlanes.size() - dimension; ++index)
				B.push_back(index);
		//B.push_back(mHPlanes.size()+1);

		for(unsigned index = 1 ; index < dictionary.cols() ; ++index)
				N.push_back(index);

		return dictionary;
}

template<typename Number>
std::vector<Point<Number> > HPolytope<Number>::vertexEnumeration() const
{
		std::vector<Point<Number> > solution;

		// create Matrix from hPlanes TODO: Recheck with page 299 of the paper
		const unsigned rows = mHPlanes.size();
		const unsigned colums = this->dimension()+1;
		Eigen::Matrix<carl::FLOAT_T<Number>,Eigen::Dynamic, Eigen::Dynamic> poly
= Eigen::Matrix<carl::FLOAT_T<Number>,
Eigen::Dynamic, Eigen::Dynamic>(rows,colums);
		unsigned rowCount = 0;
		unsigned columCount = 0;

		for(auto& hplane : mHPlanes)
		{
				columCount = 0;
				poly(rowCount, columCount) =
carl::FLOAT_T<double>(hplane.offset());
				vector_t<Number> normal = hplane.normal();
				for(unsigned index = 0; index < normal.rows(); ++index)
				{
						++columCount;
						poly(rowCount, columCount) = -normal(index);
				}
				++rowCount;
		}

		// get unique optimal first Dictionary
		std::vector<unsigned> basis;
		std::vector<unsigned> coBasis;
		Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, Eigen::Dynamic>
dictionary =
getOptimalDictionary(poly,this->dimension(), basis, coBasis);

		//std::cout << "Optimal dictionary:" << std::endl << dictionary <<
std::endl;

		// Note: f and g mark the indices, not the enumeration as stored in B
and N
		//unsigned f = dictionary.rows();
		//unsigned g = 0;

		//unsigned m = mHPlanes.size() - dimension() +1;
		//unsigned n = mHPlanes.size() +2;

		hpolytope::search(basis, coBasis, dictionary);

		return solution;
}
*/

}  // namespace
