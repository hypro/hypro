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
		if ( size == 1 ) {
			// Return Box constraints.
		} else if ( size < mDimension + 1 ) {
			std::vector<Point<Number>> vertices = alien.vertices();

			// Recursive projection:
			// find planes which define the largest dimension -> solve for d

			// project to one dimension less (reduce to d-1)
			// define lambda function reducing a given point by one dimension (the last)
			//auto reduce = [=](Point<Number> orig){ return Point<Number>(orig.rawCoordinates().conservativeResize(orig.rawCoordinates().rows()-1, Eigen::NoChange_t)); };

			//std::vector<Point<Number>> reducedVertices;
			//for(const auto& vertex : vertices){
			//	reducedVertices.push_back(reduce(vertex));
			//}

			// if proper definition possible, return this
			// else start over (we can use the constructor)

			assert( false );
		} else {
			std::cout << "Conv Hull" << std::endl;
			// TODO: Chose suitable convex hull algorithm
			typename std::vector<Point<Number>> points = alien.vertices();
			std::vector<std::shared_ptr<Facet<Number>>> facets = convexHull( points ).first;
			std::cout << "Conv Hull end" << std::endl;
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
				Number eps = 0;
				while (below) {
					//std::cout << "Is below, iterate " << std::endl;
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

/*
 * Compute all neighbors of a facet by calculating the participation at the vertices of the facet
 * @input unsigned facet
 * @return std::vector<Number> res contains all indices of neighbors, sorted
 */
template <typename Number>
std::vector<std::vector<unsigned>> HPolytope<Number>::getMembersOfVertices(std::vector<Point<Number>> vertices) const {
	std::vector<std::vector<unsigned>> res;
	HPolytope<Number> hpolytope = *this;

	for(Point<Number> vertex: vertices) {
		vector_t<Number> vertexVector = vector_t<Number>(vertex.rawCoordinates());
		std::vector<unsigned> subRes;

		for(unsigned i=0; i<hpolytope.size(); i++){
			if(carl::AlmostEqual2sComplement(vertexVector.dot(hpolytope.mHPlanes[i].normal()), hpolytope.mHPlanes[i].offset())){
				if(std::find(subRes.begin(), subRes.end(), i)==subRes.end()) {
					subRes.push_back(i);
				}
			}
		}
		std::sort(subRes.begin(), subRes.end());
		if(!subRes.empty()) res.push_back(subRes);
	}

	return res;
}

/*
 * Compute all neighbors of a facet by calculating the participation at the vertices of the facet
 * @input unsigned facet, membersOfvertices
 * @return std::vector<unsigned> res contains all indices of neighbors, sorted
 */
template <typename Number>
std::vector<unsigned> HPolytope<Number>::getNeighborsOfIndex(unsigned facet, std::vector<std::vector<unsigned>> membersOfvertices) const {
	std::vector<unsigned> res;

	for(std::vector<unsigned> membersOfvertex: membersOfvertices) {
		if(std::find(membersOfvertex.begin(), membersOfvertex.end(), facet)!=membersOfvertex.end()){
			for(unsigned member: membersOfvertex){
				if(member!=facet && std::find(res.begin(), res.end(), member)==res.end()){
					res.push_back(member);
				}
			}
		}
	}
	std::sort(res.begin(), res.end());
	return res;
}

/*
 * Get all vertices which have one facet as member
 * @input unsigned facet a, vertices, membersOfvertices
 * @return std::vector<Point<Number>> res contains all vertices which have a as member
 */
template <typename Number>
std::vector<Point<Number>> HPolytope<Number>::getVerticesOfIndex(unsigned a, std::vector<Point<Number>> vertices, std::vector<std::vector<unsigned>> membersOfvertices) const {
	std::vector<Point<Number>> res;

	for(unsigned i=0; i<vertices.size(); i++) {
		if(std::find(membersOfvertices[i].begin(), membersOfvertices[i].end(), a)!= membersOfvertices[i].end()) {
			res.push_back(vertices[i]);
		}
	}

	return res;
}

/*
 * Get all vertices which have two facets as members
 * @input unsigned facet a, b, vertices, membersOfvertices
 * @return std::vector<Point<Number>> res contains all vertices which have a, b as members
 */
template <typename Number>
std::vector<Point<Number>> HPolytope<Number>::getVerticesOf2Indices(unsigned a, unsigned b, std::vector<Point<Number>> vertices, std::vector<std::vector<unsigned>> membersOfvertices) const {
	std::vector<Point<Number>> res;

	for(unsigned i=0; i<vertices.size(); i++) {
		if(std::find(membersOfvertices[i].begin(), membersOfvertices[i].end(), a)!= membersOfvertices[i].end()
		&& std::find(membersOfvertices[i].begin(), membersOfvertices[i].end(), b)!= membersOfvertices[i].end()) {
			res.push_back(vertices[i]);
		}
	}

	return res;
}

/*
 * Get all vertices which have onyl one of two facets as members
 * @input unsigned facet a, b, vertices, membersOfvertices
 * @return std::vector<Point<Number>> res contains all vertices which have only one of a, b as members
 */
template <typename Number>
std::vector<Point<Number>> HPolytope<Number>::getVerticesOf2IndicesAround(unsigned a, unsigned b, std::vector<Point<Number>> vertices, std::vector<std::vector<unsigned>> membersOfvertices) const {
	std::vector<Point<Number>> res;

	for(unsigned i=0; i<vertices.size(); i++) {
		if(((std::find(membersOfvertices[i].begin(), membersOfvertices[i].end(), a)!=membersOfvertices[i].end()) && (std::find(membersOfvertices[i].begin(), membersOfvertices[i].end(), b)==membersOfvertices[i].end()))
		||
			((std::find(membersOfvertices[i].begin(), membersOfvertices[i].end(), b)!=membersOfvertices[i].end()) && (std::find(membersOfvertices[i].begin(), membersOfvertices[i].end(), a)==membersOfvertices[i].end()))) {
			res.push_back(vertices[i]);
		}
	}

	return res;
}

/*
 * Get all permutations for the ridge of the facet
 * @input unsigned facet a, b, vertices
 * @return std::vector<std::vector<Point<Number>>> permutations
 */
template <typename Number>
std::vector<std::vector<vector_t<Number>>> HPolytope<Number>::getVerticesPermutationForFacet(unsigned a, unsigned b, std::vector<Point<Number>> vertices) const {
	std::vector<std::vector<vector_t<Number>>> res;
	std::vector<Point<Number>> cutPointsAround_a_b = getVerticesOf2IndicesAround(a, b, vertices, getMembersOfVertices(vertices));

	if(cutPointsAround_a_b.size()==cutPointsAround_a_b[0].dimension()){
		std::vector<vector_t<Number>> setOfPoints;
		for(Point<Number> point: cutPointsAround_a_b){
			setOfPoints.push_back(vector_t<Number>(point.rawCoordinates()));
		}

		res.push_back(setOfPoints);
	} else {
		polytope::dPermutator permutator(cutPointsAround_a_b.size(), cutPointsAround_a_b[0].dimension());
		std::vector<unsigned> permutation;
		while(!permutator.end()) {
			permutation = permutator();
			std::vector<vector_t<Number>> setOfPoints;
			for(unsigned index: permutation) {
				setOfPoints.push_back(vector_t<Number>(cutPointsAround_a_b[index].rawCoordinates()));
			}
			res.push_back(setOfPoints);
		}
	}
	return res;
}

/*
 * Prepare computeNormal with a set of vertices - compute the base vectors
 * @input vertices, test vector a, test vector b
 * @return vector_t<Number> normal vector
 */
template <typename Number>
vector_t<Number> HPolytope<Number>::computeNormal(std::vector<vector_t<Number>> vertices, vector_t<Number> check) const{
	unsigned dimension = vertices[0].size();
	std::vector<vector_t<Number>> baseVectors;
	for(unsigned i=1; i<vertices.size(); i++){
		baseVectors.push_back(vertices[i]-vertices[0]);
	}

	if(vertices.size()!=dimension){ // check if we have the exact number of vertices for the calculation
		std::cout << __func__ << " : " << __LINE__ << "\n   Error - the number of vertices does not fit for the calculation.\nActual Number: " << vertices.size() << "\nNeeded Number: " << dimension-1<< std::endl;
		return check;
	}

	vector_t<Number> res = vector_t<Number>::Zero(dimension);

	for(unsigned i=0; i<dimension; i++){ // iterate through each coordinate of the normal vector
		// create the matrix and get determinant for each matrix
		Eigen::MatrixXd m(dimension-1, dimension-1);
		for(unsigned r=0; r<dimension; r++) {
			if(r!=i){
				unsigned rCorrect = r;
				if(r>i) rCorrect--;
				for(unsigned v=0; v<baseVectors.size(); v++){
					m(rCorrect,v) = baseVectors[v][r];
				}
			}
		}
		double determinant = m.determinant();
		if ((i % 2) == 0) {
			res[i] = determinant;
		}
		else {
			res[i] = (-1)*determinant;
		}
	}

	if(check.dot(res)<=0){// check direction ...should not be 0?
		return (-1)*res;
	}

	return res;
}

/*
 * Get the closest vertex for a given vector
 * @input vertices, vector
 * @return Point<Number> vertex for the vector
 */
template <typename Number>
Point<Number> HPolytope<Number>::getVertexForVector(vector_t<Number> vector, std::vector<Point<Number>> vertices) const{
	Point<Number> result = vertices[0]; // init for the case that all SP are 0... if
	vector.normalize();
	vector_t<Number> tempVertex = vector_t<Number>(vertices[0].rawCoordinates());
	tempVertex.normalize();
	double bestSP= vector.dot(tempVertex);

	for(Point<Number> vertex: vertices){
		tempVertex = vector_t<Number>(vertex.rawCoordinates());
		tempVertex.normalize();
		double newSP = vector.dot(tempVertex);
		if(newSP>bestSP){
			bestSP = newSP;
			result = vertex;
		}
	}

	return result;
}

/*
 * check if the drop of one facet yields to an unbounded poyltope
 * @input unsigned facet to be droped
 * @return bool isBounded or not
 */
template <typename Number>
bool HPolytope<Number>::isBounded(std::vector<vector_t<Number>> evaluations) const{

	HPolytope<Number> res = *this;

	// test bounded
	for(vector_t<Number> evaluation: evaluations){
		std::pair<Number, SOLUTION> evaluation_result = res.evaluate(evaluation);
		if(evaluation_result.second==INFTY){
			return false;
		}
	}
	return true;
}

/*
 * Reduction-Function
 * @Input unsigned strat for the strategy, unsigned a for the facet (Drop, drop_smooth) and first facet for (unite, unite_...), unsigned b for the seconde facet
 * @return the reduced facet or if the result would be unbounded the inital polytope
 */
template <typename Number>
HPolytope<Number> HPolytope<Number>::reduce_nd(unsigned a, unsigned b, REDUCTION_STRATEGY strat) const { // REDUCTION_STRATEGY

	// init
	HPolytope<Number> res = *this;
	std::vector<Point<Number>> vertices = res.vertices();
	std::vector<std::vector<unsigned>> membersOfVertices = getMembersOfVertices(vertices);
	std::vector<vector_t<Number>> evaluations;

	std::vector<unsigned> neighborsOf_a = getNeighborsOfIndex(a, membersOfVertices); // get neighbors
	std::vector<unsigned> neighborsOf_b = getNeighborsOfIndex(b, membersOfVertices); // get neighbors

	// neighbor test for unite
	if(strat>1 && strat<6 && std::find(neighborsOf_a.begin(), neighborsOf_a.end(), b)==neighborsOf_a.end()){
		std::cout << "Error - second facet is no neighbor of first facet" << std::endl;
		return res;
	}


	// (try to) reduce
	switch(strat){
		case REDUCTION_STRATEGY::DROP:
			{
				evaluations.push_back(res.mHPlanes[a].normal());
				res.mHPlanes.erase(res.mHPlanes.begin()+a); // delete facet
				break;
			}

		case REDUCTION_STRATEGY::DROP_SMOOTH:
			{
				std::vector<vector_t<Number>> smoothVectors;
				std::vector<Number> smoothVectors_offset;
				std::vector<unsigned> smoothVectors_oldIndices;


				for(unsigned neighbor: neighborsOf_a){
					smoothVectors.push_back(res.mHPlanes[neighbor].normal()+res.mHPlanes[a].normal());
					smoothVectors_offset.push_back(res.mHPlanes[neighbor].offset()+res.mHPlanes[a].offset());
					smoothVectors_oldIndices.push_back(neighbor);
				}

				neighborsOf_a.push_back(a);
				std::sort(neighborsOf_a.begin(), neighborsOf_a.end());
				std::reverse(neighborsOf_a.begin(), neighborsOf_a.end());

				for(unsigned i=0; i<smoothVectors.size(); i++){
					res.insert(Hyperplane<Number>(smoothVectors[i], smoothVectors_offset[i])); // update neighbor facets
				}

				for(unsigned neighbor: neighborsOf_a){
					evaluations.push_back(res.mHPlanes[neighbor].normal());
					res.mHPlanes.erase(res.mHPlanes.begin()+neighbor); // delete not smoothed facet
				}

				break;
			}


		case REDUCTION_STRATEGY::UNITE:
			{
				vector_t<Number> uniteVector = (res.mHPlanes[a].normal()+res.mHPlanes[b].normal());
				Number uniteVector_offset = res.mHPlanes[a].offset()+res.mHPlanes[b].offset();

				evaluations.push_back(res.mHPlanes[a].normal());
				evaluations.push_back(res.mHPlanes[b].normal());

				res.insert(Hyperplane<Number>(uniteVector, uniteVector_offset)); // insert united facet
				res.mHPlanes.erase(res.mHPlanes.begin()+a);
				res.mHPlanes.erase(res.mHPlanes.begin()+b);

				break;
			}

		case REDUCTION_STRATEGY::UNITE_SMOOTH:
			{
				vector_t<Number> uniteVector = vector_t<Number>::Zero(vertices[0].dimension()); // init smooth united facet
				Number uniteVector_offset;

				evaluations.push_back(res.mHPlanes[a].normal());
				evaluations.push_back(res.mHPlanes[b].normal());

				// smooth united facet is the sum of all (normalized and smoothed) neighbor facets of a and b
				// uniteVector
				for(unsigned neighbor: neighborsOf_a){
					if(neighbor!=b){
						vector_t<Number> vector_normalized = res.mHPlanes[a].normal()+res.mHPlanes[neighbor].normal();
						vector_normalized.normalize();
						uniteVector+=vector_normalized;
					}
				}
				for(unsigned neighbor: neighborsOf_b){
					if(neighbor!=a){
						vector_t<Number> vector_normalized = res.mHPlanes[b].normal()+res.mHPlanes[neighbor].normal();
						vector_normalized.normalize();
						uniteVector+=vector_normalized;
					}
				}

				// uniteVector_offset
				Point<Number> point_a_b = getVertexForVector(uniteVector, getVerticesOf2Indices(a, b, vertices, membersOfVertices));

				// smooth united facet offset is computed with the united facet and cutPoint of facet a and b
				for(unsigned i=0; i<uniteVector.size(); i++){
					uniteVector_offset+=uniteVector[i]*point_a_b.coordinate(i);
				}

				res.insert(Hyperplane<Number>(uniteVector, uniteVector_offset)); // insert united facet
				res.mHPlanes.erase(res.mHPlanes.begin()+a);
				res.mHPlanes.erase(res.mHPlanes.begin()+b);

				break;
			}

		case REDUCTION_STRATEGY::UNITE_CUT: // TODO fix the '-'Problem
			{
				vector_t<Number> uniteVector = vector_t<Number>::Zero(vertices[0].dimension()); // init cut united facet
				Number uniteVector_offset;

				evaluations.push_back(res.mHPlanes[a].normal());
				evaluations.push_back(res.mHPlanes[b].normal());

				// cut united facet is the sum of all possible normals
				for(std::vector<vector_t<Number>> setOfPoints: getVerticesPermutationForFacet(a, b, vertices)) { // get all set of points which could determine the new facet
					//Hyperplane<Number> normal = Hyperplane<Number>(res.mHPlanes[a].normal(), setOfPoints);
					//std::cout << "normal of Hyperplane:\n" << normal.normal() << std::endl;
					vector_t<Number> normal = computeNormal(setOfPoints, res.mHPlanes[a].normal()); // TODO use a simple hyperplane for this task
					//std::cout << "normal of Me:\n" << normal << std::endl;
					if(normal!=vector_t<Number>::Zero(vertices[0].dimension())) normal.normalize();
					uniteVector += normal;//normal.normal(); // add all these candidates
					if(uniteVector!=vector_t<Number>::Zero(vertices[0].dimension())) uniteVector.normalize();
				}
				//std::cout << "uniteVector of Me:\n" << uniteVector << std::endl;


				// uniteVector_offset
				Point<Number> point_a_b = getVertexForVector(uniteVector, getVerticesOf2Indices(a, b, vertices, membersOfVertices));

				// cut united facet offset is computed with the united facet and cutPoint of facet a and b
				for(unsigned i=0; i<uniteVector.size(); i++){
					uniteVector_offset+=uniteVector[i]*point_a_b.coordinate(i);
				}

				res.insert(Hyperplane<Number>(uniteVector, uniteVector_offset)); // insert united facet
				res.mHPlanes.erase(res.mHPlanes.begin()+a);
				res.mHPlanes.erase(res.mHPlanes.begin()+b);

				break;
			}

		case REDUCTION_STRATEGY::UNITE_NORM:
			{
				// TODO compute weights
				std::pair<double, double> weights = std::pair<double, double>(5.9, 2);

				// norm united facet works as unite_normal, but with weights for each component
				vector_t<Number> uniteVector = res.mHPlanes[a].normal()*weights.first + res.mHPlanes[b].normal()*weights.second; // weights are calculated by hand
				Number uniteVector_offset;

				// uniteVector_offset
				Point<Number> point_a_b = getVertexForVector(uniteVector, getVerticesOf2Indices(a, b, vertices, membersOfVertices));

				// norm united facet offset is computed with the united facet and (TODO furthest) cutPoint of facet a and b
				for(unsigned i=0; i<uniteVector.size(); i++){
					uniteVector_offset+=uniteVector[i]*point_a_b.coordinate(i);
				}

				break;
			}
			default:
				break;
	}

	if(res.isBounded(evaluations)) return res;

	return *this;
}

/*
 * Reduction-Function with a special strategy
 * @Input vector_t<Number> directed is the vector in which direction we would like to reduce
 * @return the reduced facet or if the result would be unbounded the inital polytope
 */
template <typename Number>
HPolytope<Number> HPolytope<Number>::reduce_directed(std::vector<vector_t<Number>> directions, REDUCTION_STRATEGY strat) const {

	// init
	HPolytope<Number> res = *this;

	std::vector<Point<Number>> vertices = res.vertices();
	std::vector<std::vector<unsigned>> membersOfVertices = getMembersOfVertices(vertices);

	std::vector<unsigned> facets_erase;
	std::vector<Hyperplane<Number>> facets_insert;

	// loop through each direction
	for(vector_t<Number> directed: directions){
		Point<Number> point_directed;
		std::vector<std::pair<unsigned, double>> scalarproducts;
		double directed_offset=0;
		bool skip=false;

		// compute scalarproducts
		vector_t<Number> directed_normalized = directed;
		directed_normalized.normalize();

		for(unsigned i=0; i<res.size(); i++){
			vector_t<Number> temp = res.mHPlanes[i].normal();
			temp.normalize();
			double scalarproduct = directed_normalized.dot(temp);

			if(carl::AlmostEqual2sComplement(scalarproduct, 1.0)){
				std::cout << "Error - wanted direction does already exist" << std::endl;
				skip=true;
			}

			scalarproducts.push_back(std::pair<unsigned, double>(i, scalarproduct));
		}

		if(!skip){
			// sort scalarproducts TODO only max?
			std::sort(scalarproducts.begin(), scalarproducts.end(), [](const std::pair<unsigned,double> &left, const std::pair<unsigned,double> &right) {	return left.second > right.second;	});

			// collect vertex
			point_directed = getVertexForVector(directed, getVerticesOfIndex(scalarproducts[0].first, vertices, membersOfVertices));

			// determine offset of directed
			for(unsigned i=0; i<directed.size(); i++){
				directed_offset+=directed[i]*point_directed.coordinate(i);
			}

			// collect facets to erase
			switch(strat){
				case REDUCTION_STRATEGY::DIRECTED_SMALL:
					{
						for(unsigned v=0; v<vertices.size(); v++){
							if(vertices[v] == point_directed){

								for(unsigned memberOfVertex: membersOfVertices[v]){
									vector_t<Number> dummy = res.mHPlanes[memberOfVertex].normal();
									dummy.normalize();
									double scalarproduct= dummy.dot(directed_normalized);

									if(std::find(facets_erase.begin(), facets_erase.end(), memberOfVertex)==facets_erase.end() && !carl::AlmostEqual2sComplement(scalarproduct+1, 1.0) && scalarproduct>0){
										facets_erase.push_back(memberOfVertex);
									}
								}
							}
						}
						break;
					}
				case REDUCTION_STRATEGY::DIRECTED_BIG:
					{
						for(unsigned i=0; i<res.size(); i++){
							vector_t<Number> dummy = res.mHPlanes[i].normal();
							dummy.normalize();
							double scalarproduct= dummy.dot(directed_normalized);

							if(std::find(facets_erase.begin(), facets_erase.end(), i)==facets_erase.end() && !carl::AlmostEqual2sComplement(scalarproduct+1, 1.0) && scalarproduct>0){
								facets_erase.push_back(i);
							}
						}
						break;
						default:
							break;
					}
			}

			std::sort(facets_erase.begin(), facets_erase.end(), [](const unsigned left, const unsigned right) {	return left > right;	});

			facets_insert.push_back(Hyperplane<Number>(directed, directed_offset));
		}
	}

	for(Hyperplane<Number> facet_insert: facets_insert){
		res.insert(facet_insert);
	}

	std::vector<vector_t<Number>> evaluations;
	for(unsigned facet_erase: facets_erase){
		evaluations.push_back(res.mHPlanes[facet_erase].normal());
		res.mHPlanes.erase(res.mHPlanes.begin()+facet_erase);
	}

	if(res.isBounded(evaluations)) return res;

	return *this;
}




template <typename Number>
void HPolytope<Number>::reduceAssign(unsigned _steps, REDUCTION_STRATEGY strat) {

	// TODO.

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
