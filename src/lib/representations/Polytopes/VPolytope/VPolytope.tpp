/*
 * @file   VPolytope.tpp
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since   2014-02-25
 * @version 2014-02-25
 */

#include "VPolytope.h"

namespace hypro {
template <typename Number>
VPolytope<Number>::VPolytope()
	: mVertices(), mFan(), mFanSet( false ), mReduced( true ), mNeighbors(), mInitialized( false ) {
}

template <typename Number>
VPolytope<Number>::VPolytope( const Point<Number> &point ) {
	mVertices.push_back( point );
	mFan = polytope::Fan<Number>();
	mFanSet = false;
	mReduced = true;
	mInitialized = false;
	mNeighbors.push_back( std::set<unsigned>() );
}

template <typename Number>
VPolytope<Number>::VPolytope( const pointVector &points ) {
	for ( const auto point : points ) {
		mVertices.push_back( point );
		mNeighbors.push_back( std::set<unsigned>() );
	}
	mFan = polytope::Fan<Number>();
	mFanSet = false;
	mReduced = false;
	mInitialized = false;
}

template <typename Number>
VPolytope<Number>::VPolytope( const matrix_t<Number> &_constraints, const vector_t<Number> _constants ) {
	// calculate all possible hyperplane intersections -> TODO: dPermutation can
	// be improved.
	std::vector<std::vector<unsigned>> permutationIndices =
		  polytope::dPermutation( _constraints.rows(), _constraints.cols() );
	matrix_t<Number> intersection = matrix_t<Number>( _constraints.cols(), _constraints.cols() );
	vector_t<Number> intersectionConstants = vector_t<Number>( _constraints.cols() );
	std::vector<vector_t<Number>> possibleVertices;
	for ( const auto &permutation : permutationIndices ) {
		unsigned rowCount = 0;
		// std::cout << "Intersect :" << std::endl;
		for ( const auto &rowIndex : permutation ) {
			// std::cout << _constraints.row(rowIndex) << " <= " <<
			// _constants(rowIndex) << std::endl;
			intersection.row( rowCount ) = _constraints.row( rowIndex );
			intersectionConstants( rowCount ) = _constants( rowIndex );
			++rowCount;
		}
		// check if rank is full
		if ( intersection.fullPivHouseholderQr().rank() == intersection.cols() ) {
			vector_t<Number> vertex = intersection.fullPivHouseholderQr().solve( intersectionConstants );
			possibleVertices.push_back( vertex );
			// std::cout<< "Vertex computed: " << vertex.transpose() << std::endl;
		}
	}

	// check if vertices are true vertices (i.e. they fulfill all constraints)
	for ( auto vertex = possibleVertices.begin(); vertex != possibleVertices.end(); ++vertex ) {
		// std::cout<<__func__ << " : " <<__LINE__ << " current position : " << i <<
		// std::endl;
		// std::cout<<__func__ << " : " <<__LINE__ << "number of vertices : " <<
		// possibleVertices.size() << std::endl;
		for ( unsigned rowIndex = 0; rowIndex < _constraints.rows(); ++rowIndex ) {
			Number res = vertex->dot( _constraints.row( rowIndex ) );
			if ( res > _constants( rowIndex ) ) vertex = possibleVertices.erase( vertex ) - 1;
		}
	}
	// std::cout<<__func__ << " : " <<__LINE__ <<std::endl;
	// finish initialization
	for ( const auto &point : possibleVertices ) {
		mVertices.push_back( Point<Number>( point ) );
		mNeighbors.push_back( std::set<unsigned>() );
		// std::cout << "Real vertex " << point.transpose() << std::endl;
	}
	// std::cout<<__func__ << " : " <<__LINE__ <<std::endl;
	mFan = polytope::Fan<Number>();
	mFanSet = false;
	mReduced = false;
	mInitialized = false;
}

template <typename Number>
VPolytope<Number>::VPolytope( const VPolytope &orig ) {
	mVertices.insert( mVertices.end(), orig.begin(), orig.end() );
	mFan = polytope::Fan<Number>();
	mFanSet = false;			// TODO: Include getter fpr this
	mReduced = orig.reduced();  // TODO: Include getter fpr this
	mInitialized = false;
	mCone = orig.cone();
	mNeighbors = orig.mNeighbors;
}

template <typename Number>
VPolytope<Number> VPolytope<Number>::linearTransformation( const matrix_t<Number> &A,
														   const vector_t<Number> &b ) const {
	// std::cout << __func__ << " A: " << A << ", b: " << b << std::endl;
	VPolytope<Number> result;
	for ( const auto &vertex : mVertices ) {
		result.insert( vertex.linearTransformation( A, b ) );
	}
	result.setCone( mCone.linearTransformation( A, b ) );
	result.unsafeSetNeighbors( mNeighbors );
	return result;
}

template <typename Number>
VPolytope<Number> VPolytope<Number>::minkowskiSum( const VPolytope<Number> &rhs ) const {
	VPolytope<Number> result;
	// add each rhs-vertex to each vertex of this polytope.
	for ( auto lhsVertex : mVertices ) {
		for ( auto rhsVertex : rhs.mVertices ) {
			result.insert( lhsVertex + rhsVertex );
		}
	}
	result.setCone( mCone.minkowskiSum( rhs.cone() ) );
	return result;
}

template <typename Number>
VPolytope<Number> VPolytope<Number>::intersect( const VPolytope<Number> &rhs ) const {
	// create a set of possible points via combination of all coordinates
	if ( rhs.size() == 0 ) {
		return VPolytope<Number>();
	} else {
		pointVector possibleVertices;
		for ( const auto &lhsVertex : mVertices ) {
			possibleVertices.push_back( lhsVertex );
			for ( unsigned coordIndex = 0; coordIndex < lhsVertex.rawCoordinates().rows(); ++coordIndex ) {
				for ( const auto &rhsVertex : rhs.mVertices ) {
					vector_t<Number> newVertex = rhsVertex.rawCoordinates();
					newVertex( coordIndex ) = lhsVertex.at( coordIndex );
					possibleVertices.push_back( vector_t<Number>( newVertex ) );
					possibleVertices.push_back( vector_t<Number>( rhsVertex ) );
				}
			}
		}
		// remove all vertices, which are only contained in one of the polytopes
		for ( auto vertexIt = possibleVertices.begin(); vertexIt != possibleVertices.end(); ) {
			if ( !( this->contains( *vertexIt ) && rhs.contains( *vertexIt ) ) ) {
				vertexIt = possibleVertices.erase( vertexIt );
			} else {
				++vertexIt;
			}
		}
		return VPolytope<Number>( possibleVertices );
	}
}

template <typename Number>
bool VPolytope<Number>::contains( const Point<Number> &point ) const {
	return this->contains( point.rawCoordinates() );
}

template <typename Number>
bool VPolytope<Number>::contains( const vector_t<Number> &vec ) const {
	// initialize tableau if necessary
	if ( !mInitialized ) initGLPK();

	glp_set_obj_dir( mLp, GLP_MAX );
	for ( unsigned i = 1; i <= vec.rows(); ++i )
		glp_set_row_bnds( mLp, i, GLP_FX, double( vec( i - 1 ) ),
						  0 );  // as the variable is fixed, the last parameter (upper
								// row bound) is ignored

	glp_set_row_bnds( mLp, vec.rows() + 1, GLP_FX, 1.0, 0 );  // the sum of the vectors equals exactly one.

	for ( unsigned i = 1; i <= mVertices.size(); ++i ) {
		glp_set_col_bnds( mLp, i, GLP_DB, 0.0, 1.0 );
		glp_set_obj_coef( mLp, i, 1.0 );  // the objective function is max: v1 + v2 + v3 + ... + vn
	}

	// solve
	glp_simplex( mLp, &mOptions );
	bool interiorPoint = ( glp_get_prim_stat( mLp ) == GLP_FEAS );

	return interiorPoint;
}

template <typename Number>
bool VPolytope<Number>::contains( const VPolytope<Number> &_other ) const {
	// std::cout << *this<< " " << __func__ << " " << _other << std::endl;
	for ( const auto &vertex : _other.vertices() ) {
		// std::cout << __func__ << " check vertex " << vertex << std::endl;
		if ( !this->contains( vertex ) ) {
			// std::cout << "false" << std::endl;
			return false;
		}
	}
	return true;
}

template <typename Number>
VPolytope<Number> VPolytope<Number>::unite( const VPolytope<Number> &rhs ) const {
	if ( rhs.dimension() == 0 ) {
		return VPolytope<Number>( mVertices );
	} else {
		VPolytope<Number>::pointVector points;
		points.insert( points.end(), this->mVertices.begin(), this->mVertices.end() );
		points.insert( points.end(), rhs.mVertices.begin(), rhs.mVertices.end() );

		std::vector<std::shared_ptr<Facet<Number>>> facets = convexHull( points ).first;
		std::set<Point<Number>> preresult;
		for ( unsigned i = 0; i < facets.size(); i++ ) {
			for ( unsigned j = 0; j < facets[i]->vertices().size(); j++ ) {
				preresult.insert( facets[i]->vertices().at( j ) );
			}
		}

		VPolytope<Number>::pointVector res;
		for ( const auto &point : preresult ) res.push_back( point );

		return VPolytope<Number>( res );

		/*
		std::cout << "Compute convex hull of " << std::endl;
		for(const auto& vertex : points)
				std::cout << vertex << std::endl;



		std::map<Point<Number>, std::set<Point<Number>>> neighbors =
		convexHull(points).second;
		VPolytope<Number> result;
		for(const auto& pointNeighborsPair : neighbors) {
				std::cout << "Union result insert " << pointNeighborsPair.first <<
		std::endl;
				result.insert(pointNeighborsPair.first);
		}
		// we can only set neighbors after all points have been inserted.
		for(const auto& pointNeighborsPair : neighbors) {
				result.setNeighbors(pointNeighborsPair.first,
		pointNeighborsPair.second);
		}
		return result;
		*/
	}
}

template <typename Number>
void VPolytope<Number>::clear() {
	mVertices.clear();
}

template <typename Number>
Number VPolytope<Number>::supremum() const {
	Number max = 0;
	for ( auto &point : mVertices ) {
		Number inftyNorm = hypro::Point<Number>::inftyNorm( point );
		max = max > inftyNorm ? max : inftyNorm;
	}
	return max;
}

template <typename Number>
void VPolytope<Number>::removeRedundancy() {
	if ( !mReduced ) {
		std::set<Point<Number>> toDelete;
		smtrat::SimplexSolver simplex;
		simplex.push();

		// create mapping of variables (lambdas') to vertices.
		std::map<Point<Number>, carl::Variable> lambdas;
		for(const auto& vertex : mVertices) {
			carl::Variable lambda = carl::freshRealVariable();
			lambdas.insert(std::make_pair(vertex, lambda));
			//std::cout << "Assigned " << lambdas.find(vertex)->second << " to " << lambdas.find(vertex)->first << std::endl;
		}


		for(auto currVertex = mVertices.begin(); currVertex != mVertices.end(); ){
			//std::cout << currVertex << ": " << std::endl;
			// create constraint for Sum(lambdas) == 1
			Poly sumBound;
			for(const auto& vertex : mVertices) {
				if(vertex != *currVertex) {
					carl::Variable lambda = lambdas.find(vertex)->second;
					sumBound += lambda;
					smtrat::FormulaT constr = smtrat::FormulaT(Poly(lambda), carl::Relation::GEQ);
					simplex.inform(constr);
					simplex.add(constr);
				}
			}
			sumBound -= Rational(1);
			smtrat::FormulaT constr = smtrat::FormulaT(sumBound, carl::Relation::EQ);
			simplex.inform(constr);
			simplex.add(constr);

			for(unsigned dim = 0; dim < this->dimension(); ++dim) {
				Poly row;
				for(const auto& vertex : mVertices ) {
					if(*currVertex != vertex) {
						carl::Variable tmp = lambdas.find(vertex)->second;
						row += tmp*Rational(vertex.at(dim));
					} else {
						row -= Rational(vertex.at(dim));
					}
				}
				smtrat::FormulaT constr = smtrat::FormulaT(row, carl::Relation::EQ);
				//std::cout << constr << std::endl;
				simplex.inform(constr);
				simplex.add(constr);
			}

			std::cout << "Checking: " << std::endl << simplex.formula().toString() << std::endl;

			smtrat::Answer res = simplex.check();

			if(res == smtrat::Answer::True) {
				currVertex = mVertices.erase(currVertex);
			} else {
				++currVertex;
			}

			//std::cout << "Is extreme point: " << (res == smtrat::Answer::False) << std::endl << std::endl << std::endl << std::endl;
			simplex.pop();
			simplex.push();
		}

		mReduced = true;
	}
}

template <typename Number>
void VPolytope<Number>::updateNeighbors() {
	std::map<Point<Number>, std::set<Point<Number>>> neighbors = convexHull( mVertices ).second;
	mVertices.clear();
	for ( const auto &pointNeighborsPair : neighbors ) {
		mVertices.push_back( pointNeighborsPair.first );
	}
	// we can only set neighbors after all points have been inserted.
	for ( const auto &pointNeighborsPair : neighbors ) {
		this->setNeighbors( pointNeighborsPair.first, pointNeighborsPair.second );
	}
	mReduced = true;
}

/***************************************************************************
 * Auxiliary functions
 **************************************************************************/

template <typename Number>
void VPolytope<Number>::initGLPK() const {
	if ( !mInitialized ) {
		// create lp problem (basic options etc.) of size dimension+1 x #Points
		mLp = glp_create_prob();
		glp_init_smcp( &mOptions );
		mOptions.msg_lev = GLP_MSG_OFF;
		glp_add_rows( mLp, this->dimension() + 1 );
		glp_add_cols( mLp, mVertices.size() );

		// prepare matrix
		unsigned size =
			  mVertices.size() * ( this->dimension() + 1 );  // add one row to hold the constraint that all add up to one.
		mIa = new int[size + 1];
		mJa = new int[size + 1];
		mAr = new double[size + 1];
		unsigned pos = 1;
		typename pointVector::const_iterator vertex = mVertices.begin();
		for ( unsigned i = 1; i <= this->dimension() + 1; ++i ) {
			for ( unsigned j = 1; j <= mVertices.size(); ++j ) {
				mIa[pos] = i;
				mJa[pos] = j;
				if ( i == this->dimension() + 1 ) {
					mAr[pos] = 1.0;
					// std::cout << "Setting: mIa[" << pos << "]=" << i << ", mJa[" << pos
					// << "]=" << j << ", mAr[" <<
					// pos << "]= 1.0" << std::endl;
				} else {
					mAr[pos] = double( ( *vertex ).at( i - 1 ) );
					// std::cout << "Setting: mIa[" << pos << "]=" << i << ", mJa[" << pos
					// << "]=" << j << ", mAr[" <<
					// pos << "]=" << double((*vertex).at(i-1)) << std::endl;
				}
				++pos;
				++vertex;
			}
			vertex = mVertices.begin();
		}
		glp_load_matrix( mLp, size, mIa, mJa, mAr );
		mInitialized = true;
	}
}

template <typename Number>
const typename VPolytope<Number>::Fan &VPolytope<Number>::calculateFan() const {
	if ( !mFanSet ) {
		std::vector<Facet<Number>> facets = convexHull( mVertices ).first;
		std::set<Point<Number>> preresult;
		for ( unsigned i = 0; i < facets.size(); i++ ) {
			for ( unsigned j = 0; j < facets[i].vertices().size(); j++ ) {
				preresult.insert( facets[i].vertices().at( j ) );
			}
		}
		polytope::Fan<Number> fan;
		for ( auto &point : preresult ) {
			polytope::Cone<Number> *cone = new polytope::Cone<Number>();
			for ( unsigned i = 0; i < facets.size(); i++ ) {
				for ( unsigned j = 0; j < facets[i].vertices().size(); j++ ) {
					if ( point == facets[i].vertices().at( j ) ) {
						std::vector<Ridge<Number>> ridges = getRidges( facets[i] );
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
}

template <typename Number>
const typename VPolytope<Number>::Cone &VPolytope<Number>::calculateCone( const Point<Number> &vertex ) {
	// set up glpk
	glp_prob *cone;
	cone = glp_create_prob();
	glp_set_obj_dir( cone, GLP_MIN );

	typename polytope::Cone<Number>::vectors vectors;
	for ( auto &cone : mFan.get() ) {
		vectors.insert( vectors.end(), cone.begin(), cone.end() );
	}
	unsigned numVectors = vectors.size();
	unsigned elements = this->dimension() * numVectors;

	glp_add_cols( cone, numVectors );
	glp_add_rows( cone, this->dimension() );

	int ia[elements];
	int ja[elements];
	double ar[elements];
	unsigned pos = 1;

	for ( unsigned i = 1; i <= this->dimension(); ++i ) {
		for ( unsigned j = 1; j <= numVectors; ++j ) {
			ia[pos] = i;
			ja[pos] = j;
			ar[pos] = vectors.at( j ).at( i );
			++pos;
		}
	}
	assert( pos <= elements );

	glp_load_matrix( cone, elements, ia, ja, ar );
	glp_simplex( cone, NULL );

	// TODO output & result interpretation

	// glp_delete_prob(cone);
}

template <typename Number>
VPolytope<Number> &VPolytope<Number>::operator=( const VPolytope<Number> &rhs ) {
	if ( this != &rhs ) {
		VPolytope<Number> tmp( rhs );
		std::swap( *this, tmp );
	}
	return *this;
}

template <typename Number>
bool VPolytope<Number>::operator==( const VPolytope<Number> &rhs ) const {
	if ( this->dimension() != rhs.dimension() ) return false;

	// TODO: Highly inefficient!!!
	for ( auto &lPoint : this->vertices() ) {
		if ( !rhs.hasVertex( lPoint ) ) return false;
	}
	for ( auto &rPoint : rhs.vertices() ) {
		if ( !this->hasVertex( rPoint ) ) return false;
	}
	return true;
}

}  // namespace
