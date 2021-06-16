/**
 * File holding utility functions to keep the main files clean.
 */

#pragma once
#include "HPolytope.h"

namespace hypro {

/*
   * Compute all neighbors of a facet by calculating the participation at the vertices of the facet
   * @input unsigned facet
   * @return std::vector<Number> res contains all indices of neighbors, sorted
   */
template <typename Number, typename Converter, class Setting>
std::vector<std::vector<unsigned>> HPolytopeT<Number, Converter, Setting>::getMembersOfVertices( std::vector<Point<Number>> vertices ) const {
	HPolytopeT<Number, Converter, Setting> hpolytope = *this;
	std::vector<std::vector<unsigned>> res;

	for ( Point<Number> vertex : vertices ) {
		vector_t<Number> vertexVector = vector_t<Number>( vertex.rawCoordinates() );
		std::vector<unsigned> subRes;

		for ( unsigned i = 0; i < hpolytope.size(); i++ ) {
			if ( vertexVector.dot( hpolytope.constraints().at( i ).normal() ) == hpolytope.constraints().at( i ).offset() &&
				 std::find( subRes.begin(), subRes.end(), i ) == subRes.end() ) {
				subRes.push_back( i );
			}
		}
		std::sort( subRes.begin(), subRes.end() );
		if ( !subRes.empty() ) res.push_back( subRes );
	}

	return res;
}

/*
   * Compute all neighbors of a facet by calculating the participation at the vertices of the facet
   * @input unsigned facet, membersOfvertices
   * @return std::vector<unsigned> res contains all indices of neighbors, sorted
   */
template <typename Number, typename Converter, class Setting>
std::vector<unsigned> HPolytopeT<Number, Converter, Setting>::getNeighborsOfIndex( unsigned facet, std::vector<std::vector<unsigned>> membersOfvertices ) const {
	std::vector<unsigned> res;

	for ( std::vector<unsigned> membersOfvertex : membersOfvertices ) {
		if ( std::find( membersOfvertex.begin(), membersOfvertex.end(), facet ) != membersOfvertex.end() ) {
			for ( unsigned member : membersOfvertex ) {
				if ( member != facet && std::find( res.begin(), res.end(), member ) == res.end() ) {
					res.push_back( member );
				}
			}
		}
	}
	std::sort( res.begin(), res.end() );
	return res;
}

/*
   * Get all vertices which have one facet as member
   * @input unsigned facet a, vertices, membersOfvertices
   * @return std::vector<Point<Number>> res contains all vertices which have a as member
   */
template <typename Number, typename Converter, class Setting>
std::vector<Point<Number>> HPolytopeT<Number, Converter, Setting>::getVerticesOfIndex( unsigned a, std::vector<Point<Number>> vertices, std::vector<std::vector<unsigned>> membersOfvertices ) const {
	std::vector<Point<Number>> res;

	for ( unsigned i = 0; i < vertices.size(); i++ ) {
		if ( std::find( membersOfvertices.at( i ).begin(), membersOfvertices.at( i ).end(), a ) != membersOfvertices.at( i ).end() ) {
			res.push_back( vertices.at( i ) );
		}
	}

	return res;
}

/*
   * Get all vertices which have two facets as members
   * @input unsigned facet a, b, vertices, membersOfvertices
   * @return std::vector<Point<Number>> res contains all vertices which have a, b as members
   */
template <typename Number, typename Converter, class Setting>
std::vector<Point<Number>> HPolytopeT<Number, Converter, Setting>::getVerticesOf2Indices( unsigned a, unsigned b, std::vector<Point<Number>> vertices, std::vector<std::vector<unsigned>> membersOfvertices ) const {
	std::vector<Point<Number>> res;

	for ( unsigned i = 0; i < vertices.size(); i++ ) {
		if ( std::find( membersOfvertices.at( i ).begin(), membersOfvertices.at( i ).end(), a ) != membersOfvertices.at( i ).end() && std::find( membersOfvertices.at( i ).begin(), membersOfvertices.at( i ).end(), b ) != membersOfvertices.at( i ).end() ) {
			res.push_back( vertices.at( i ) );
		}
	}

	return res;
}

/*
   * Get all vertices which have onyl one of two facets as members
   * @input unsigned facet a, b, vertices, membersOfvertices
   * @return std::vector<Point<Number>> res contains all vertices which have only one of a, b as members
   */
template <typename Number, typename Converter, class Setting>
std::vector<Point<Number>> HPolytopeT<Number, Converter, Setting>::getVerticesOf2IndicesAround( unsigned a, unsigned b, std::vector<Point<Number>> vertices, std::vector<std::vector<unsigned>> membersOfvertices ) const {
	std::vector<Point<Number>> res;

	for ( unsigned i = 0; i < vertices.size(); i++ ) {
		if ( ( ( std::find( membersOfvertices.at( i ).begin(), membersOfvertices.at( i ).end(), a ) != membersOfvertices.at( i ).end() ) && ( std::find( membersOfvertices.at( i ).begin(), membersOfvertices.at( i ).end(), b ) == membersOfvertices.at( i ).end() ) ) ||
			 ( ( std::find( membersOfvertices.at( i ).begin(), membersOfvertices.at( i ).end(), b ) != membersOfvertices.at( i ).end() ) && ( std::find( membersOfvertices.at( i ).begin(), membersOfvertices.at( i ).end(), a ) == membersOfvertices.at( i ).end() ) ) ) {
			res.push_back( vertices.at( i ) );
		}
	}

	return res;
}

/*
   * Get all permutations for the ridge of the facet
   * @input unsigned facet a, b, vertices
   * @return std::vector<std::vector<Point<Number>>> permutations
   */
template <typename Number, typename Converter, class Setting>
std::vector<std::vector<vector_t<Number>>> HPolytopeT<Number, Converter, Setting>::getVerticesPermutationForFacet( unsigned a, unsigned b, std::vector<Point<Number>> vertices ) const {
	HPolytopeT<Number, Converter, Setting> hpolytope = *this;
	std::vector<std::vector<vector_t<Number>>> res;
	std::vector<Point<Number>> cutPointsAround_a_b = getVerticesOf2IndicesAround( a, b, vertices, getMembersOfVertices( vertices ) );

	if ( cutPointsAround_a_b.size() == cutPointsAround_a_b.at( 0 ).dimension() ) {
		std::vector<vector_t<Number>> setOfPoints;
		for ( Point<Number> point : cutPointsAround_a_b ) {
			setOfPoints.push_back( vector_t<Number>( point.rawCoordinates() ) );
		}

		res.push_back( setOfPoints );
	} else {
		Permutator permutator( cutPointsAround_a_b.size(), cutPointsAround_a_b.at( 0 ).dimension() );
		std::vector<std::size_t> permutation;
		while ( !permutator.end() ) {
			permutation = permutator();
			std::vector<vector_t<Number>> setOfPoints;
			for ( unsigned index : permutation ) {
				setOfPoints.push_back( vector_t<Number>( cutPointsAround_a_b.at( index ).rawCoordinates() ) );
			}
			res.push_back( setOfPoints );
		}
	}
	return res;
}

/*
   * Prepare computeNormal with a set of vertices - compute the base vectors
   * @input vertices, test vector a, test vector b
   * @return vector_t<Number> normal vector
   */
template <typename Number, typename Converter, class Setting>
vector_t<Number> HPolytopeT<Number, Converter, Setting>::computeNormal( std::vector<vector_t<Number>> vertices, vector_t<Number> check ) const {
	unsigned dimension = vertices.at( 0 ).size();
	std::vector<vector_t<Number>> baseVectors;
	for ( unsigned i = 1; i < vertices.size(); i++ ) {
		baseVectors.push_back( vertices.at( i ) - vertices.at( 0 ) );
	}

	if ( vertices.size() != dimension ) {  // check if we have the exact number of vertices for the calculation
		std::cout << __func__ << " : " << __LINE__ << "\n   Error - the number of vertices does not fit for the calculation.\nActual Number: " << vertices.size() << "\nNeeded Number: " << dimension - 1 << std::endl;
		return check;
	}

	vector_t<Number> res = vector_t<Number>::Zero( dimension );

	for ( unsigned i = 0; i < dimension; i++ ) {  // iterate through each coordinate of the normal vector
		// create the matrix and get determinant for each matrix
		matrix_t<Number> m( dimension - 1, dimension - 1 );
		for ( unsigned r = 0; r < dimension; r++ ) {
			if ( r != i ) {
				unsigned rCorrect = r;
				if ( r > i ) rCorrect--;
				for ( unsigned v = 0; v < baseVectors.size(); v++ ) {
					m( rCorrect, v ) = baseVectors[v][r];
				}
			}
		}
		Number determinant = Number( m.determinant() );
		if ( ( i % 2 ) == 0 ) {
			res[i] = determinant;
		} else {
			res[i] = ( -1 ) * determinant;
		}
	}

	if ( check.dot( res ) <= 0 ) {  // check direction ...should not be 0?
		return ( -1 ) * res;
	}

	return res;
}

/*
   * Find the outmost vertex of vertices regarding the passed direction.
   * @input vertices, vector
   * @return Point<Number> vertex for the vector
   */
template <typename Number, typename Converter, class Setting>
Point<Number> HPolytopeT<Number, Converter, Setting>::getVertexForVector( const vector_t<Number>& vector, const std::vector<Point<Number>>& vertices ) const {
	assert( !vertices.empty() );
	if ( vertices.size() == 1 )
		return *vertices.begin();

	Point<Number>& res = *vertices.begin();
	Number largestOffset = vector.dot( res.rawCoordinates() );
	for ( const Point<Number>& vertex : vertices ) {
		// calculate offset
		Number currentOffset = vector.dot( vertex.rawCoordinates() );
		if ( currentOffset > largestOffset ) {
			largestOffset = currentOffset;
			res = vertex;
		}
	}

	return res;
}

/*
   * check if the drop of one facet yields to an unbounded poyltope
   * @input unsigned facet to be droped
   * @return bool isBounded or not
   */
template <typename Number, typename Converter, class Setting>
bool HPolytopeT<Number, Converter, Setting>::isBounded( std::vector<vector_t<Number>> evaluations ) const {
	HPolytopeT<Number, Converter, Setting> hpolytope = *this;

	for ( vector_t<Number> evaluation : evaluations ) {
		EvaluationResult<Number> evaluation_result = hpolytope.evaluate( evaluation );
		if ( evaluation_result.errorCode == SOLUTION::INFTY ) {
			return false;
		}
	}
	return true;
}

/*
	* Heuristic for reduction strategies
	* @Input a H-polytope
	* @return the reduced polytope or if the result would be unbounded the inital polytope
	*/
template <typename Number, typename Converter, class Setting>
HPolytopeT<Number, Converter, Setting> HPolytopeT<Number, Converter, Setting>::heuristic() const {
	// 2D
	std::vector<Point<Number>> vertices = this->vertices();
	std::vector<std::vector<unsigned>> membersOfVertices = getMembersOfVertices( vertices );
	std::map<unsigned, std::vector<unsigned>> membersOfFacets;

	// init membersOfFacets
	for ( unsigned i = 0; i < membersOfVertices.size(); ++i ) {
		for ( auto memberOfVertex : membersOfVertices.at( i ) ) {
			//std::cout << "vertex " << i << " belongs to facet " << memberOfVertex << std::endl;
			if ( membersOfFacets.find( memberOfVertex ) != membersOfFacets.end() ) {
				membersOfFacets[memberOfVertex].push_back( i );
			} else {
				// create
				std::vector<unsigned> verticesForFacet;
				verticesForFacet.push_back( i );
				membersOfFacets.insert( std::make_pair( memberOfVertex, verticesForFacet ) );
			}
		}
	}

	//std::cout << "print membersOfFacets: " << std::endl << membersOfFacets << std::endl;

	// facets-size - with same indices as mHPlanes -
	std::vector<double> sizesOfFacets;
	for ( unsigned i = 0; i < membersOfFacets.size(); ++i ) {
		if ( membersOfFacets.find( i ) != membersOfFacets.end() ) {  // memberOfFacets are all vertices which are members to a facet

			double size = 0;
			if ( this->dimension() == 2 ) {
				if ( membersOfFacets[i].size() == 2 ) {
					vector_t<Number> diff = vertices.at( membersOfFacets[i].at( 0 ) ).rawCoordinates() - vertices.at( membersOfFacets[i].at( 1 ) ).rawCoordinates();  // TODO for higher dimension
					size = sqrt( (double)diff.dot( diff ) );
				} else {
					size = 1;
				}
			} else {
				unsigned permutation_count = 0;
				//std::cout << "Start permutation with " << membersOfFacets[i].size() << "/"<< vertices.size() << " (size) and " <<this->dimension() << std::endl;
				Permutator permutator( membersOfFacets[i].size(), this->dimension() );
				std::vector<std::size_t> permutation;
				while ( !permutator.end() ) {
					permutation = permutator();
					//std::cout << "Permutation for size: " << permutation << std::endl;

					std::vector<vector_t<Number>> verticesForCross;
					for ( unsigned p : permutation ) {
						verticesForCross.push_back( vertices.at( membersOfFacets[i].at( p ) ).rawCoordinates() );
					}

					vector_t<Number> cross = computeNormal( verticesForCross, this->constraints().at( i ).normal() );
					size += sqrt( (double)cross.dot( cross ) );
					permutation_count++;
				}
				size = size / (double)permutation_count;
			}
			sizesOfFacets.push_back( size );
			//std::cout << "Size of "<< i << " is " << size << std::endl;
		}
	}

	// neighbors-scalarproduct - map from (facet,facet) to double
	std::map<std::pair<unsigned, unsigned>, double> scalarproductOfFacets;
	for ( auto memberOfVertex : membersOfVertices ) {
		if ( memberOfVertex.size() > 1 ) {
			Permutator permutator( memberOfVertex.size(), 2 );
			std::vector<std::size_t> permutation;
			while ( !permutator.end() ) {
				permutation = permutator();
				//std::cout << permutation << std::endl;
				vector_t<Number> normal0 = this->constraints().at( memberOfVertex.at( permutation.at( 0 ) ) ).normal();
				vector_t<Number> normal1 = this->constraints().at( memberOfVertex.at( permutation.at( 1 ) ) ).normal();
				normal0.normalize();
				normal1.normalize();

				double scalarpoduct = normal0.dot( normal1 );
				scalarproductOfFacets.insert( std::make_pair( std::make_pair( memberOfVertex.at( permutation.at( 0 ) ), memberOfVertex.at( permutation.at( 1 ) ) ), scalarpoduct ) );
				//std::cout << "scalarpoduct of " << memberOfVertex.at(permutation.at(0)) << " and " << memberOfVertex.at(permutation.at(1)) << " is " << scalarpoduct << std::endl;
			}
		}
	}

	//std::cout << "print scalarproductOfFacets: " << std::endl << scalarproductOfFacets << std::endl;

	// find values for single strats

	// drop
	double bestDropValue = -1;
	unsigned bestDropIndex = 0;

	for ( unsigned i = 0; i < sizesOfFacets.size(); i++ ) {
		double scalarproducts = 1;
		for ( auto scalarproductOfFacet : scalarproductOfFacets ) {
			if ( scalarproductOfFacet.first.first == i || scalarproductOfFacet.first.second == i ) {
				//std::cout << "Facet " << i << " found with "<< scalarproductOfFacet.second << std::endl;
				scalarproducts *= ( 1 + scalarproductOfFacet.second );
			}
		}
		double dropValue = ( scalarproducts / sizesOfFacets.at( i ) );
		if ( dropValue > bestDropValue ) {
			bestDropIndex = i;
			bestDropValue = dropValue;
		}
		//std::cout << "dropValue with" << dropValue << std::endl;
	}

	//std::cout << "Drop finished!" << std::endl;

	// drop_smooth
	double bestDropSmoothValue = -1;
	unsigned bestDropSmoothIndex = 0;

	for ( unsigned i = 0; i < sizesOfFacets.size(); ++i ) {
		std::vector<unsigned> neighborsOf_i = getNeighborsOfIndex( i, membersOfVertices );  // get neighbors

		double scalarproducts = 1;
		for ( auto scalarproductOfFacet : scalarproductOfFacets ) {
			if ( scalarproductOfFacet.first.first == i || scalarproductOfFacet.first.second == i ) {
				//std::cout << "Facet " << i << " found with "<< scalarproductOfFacet.second << std::endl;
				scalarproducts *= ( 1 + scalarproductOfFacet.second );
			}
		}

		double sizes = 1;
		for ( unsigned neighborOf_i : neighborsOf_i ) {
			if ( neighborOf_i < sizesOfFacets.size() ) sizes *= sizesOfFacets.at( neighborOf_i );
		}

		double dropSmoothValue = ( ( sizesOfFacets.at( i ) * scalarproducts ) / sizes );
		if ( dropSmoothValue > bestDropSmoothValue ) {
			bestDropSmoothIndex = i;
			bestDropSmoothValue = dropSmoothValue;
		}
		//std::cout << "dropSmoothValue with " << dropSmoothValue << std::endl;
	}
	//std::cout << "DropSmooth finished!" << std::endl;

	//bestDropSmoothValue+=1; // add offset

	// unite
	double bestUniteValue = -1;
	std::pair<unsigned, unsigned> bestUniteIndex = std::make_pair( 0, 0 );
	REDUCTION_STRATEGY bestUniteStrat = REDUCTION_STRATEGY::UNITE;

	for ( unsigned a = 0; a < sizesOfFacets.size(); ++a ) {
		for ( unsigned b = a + 1; b < sizesOfFacets.size(); ++b ) {
			std::vector<unsigned> neighborsOf_a = getNeighborsOfIndex( a, membersOfVertices );  // get neighbors
			std::vector<unsigned> neighborsOf_b = getNeighborsOfIndex( b, membersOfVertices );  // get neighbors

			// neighbor
			if ( std::find( neighborsOf_a.begin(), neighborsOf_a.end(), b ) != neighborsOf_a.end() ) {
				double scalarproducts = 1, scalarproduct_a_b = 1;
				for ( auto scalarproductOfFacet : scalarproductOfFacets ) {
					//std::cout << "Search for " << a << ", " << b << " in " << scalarproductOfFacet.first << std::endl;
					if ( scalarproductOfFacet.first.first == a || scalarproductOfFacet.first.first == b || scalarproductOfFacet.first.second == a || scalarproductOfFacet.first.second == b ) {
						//std::cout << "Facets " << a << ", " << b << " found with "<< scalarproductOfFacet.second << std::endl;
						if ( ( scalarproductOfFacet.first.first == a && scalarproductOfFacet.first.second == b ) || ( scalarproductOfFacet.first.first == b || scalarproductOfFacet.first.second == a ) ) {
							scalarproduct_a_b *= ( 1 + scalarproductOfFacet.second );  // TODO more weight?
						} else {
							scalarproducts *= ( 1 + scalarproductOfFacet.second );
						}
					}
				}
				//std::cout << std::endl;
				double uniteValue = ( 2 * scalarproduct_a_b + scalarproducts );
				if ( uniteValue > bestUniteValue ) {
					bestUniteIndex = std::make_pair( a, b );
					bestUniteValue = uniteValue;
					//if(std::min(sizesOfFacets.at(a),sizesOfFacets.at(b))<=0.8*std::max(sizesOfFacets.at(a),sizesOfFacets.at(b))){
					//unite_standard
					bestUniteStrat = REDUCTION_STRATEGY::UNITE;
					//} else {
					//unite_vertices
					//bestUniteStrat= REDUCTION_STRATEGY::UNITE;
					//}
				}
			}
		}
	}

	//std::cout << "Unite finished!" << std::endl;

	// determine strat and facet/s
	REDUCTION_STRATEGY strat = REDUCTION_STRATEGY::DROP;
	unsigned facet1 = 0, facet2 = 0;

	if ( bestUniteValue > bestDropValue && bestUniteValue > bestDropSmoothValue ) {
		//unite is best strat
		facet1 = std::max( bestUniteIndex.first, bestUniteIndex.second );
		facet2 = std::min( bestUniteIndex.first, bestUniteIndex.second );
		strat = bestUniteStrat;
	} else if ( bestDropValue > bestUniteValue && bestDropValue > bestDropSmoothValue ) {
		//drop is best strat
		facet1 = bestDropIndex;
	} else if ( bestDropSmoothValue > bestUniteValue && bestDropSmoothValue > bestDropValue ) {
		//drop is best strat
		facet1 = bestDropSmoothIndex;
		strat = REDUCTION_STRATEGY::DROP_SMOOTH;
	}

	std::cout << std::endl;
	std::cout << "[Drop]       Chose facet " << bestDropIndex << " with " << bestDropValue << std::endl;
	std::cout << "[DropSmooth] Chose facet " << bestDropSmoothIndex << " with " << bestDropSmoothValue << std::endl;
	std::cout << "[Unite]      Chose facets " << bestUniteIndex << " with " << bestUniteValue << " and strat " << bestUniteStrat << std::endl;
	std::cout << "   Reduce with " << strat << " and facet1 " << facet1 << ", facet2 " << facet2 << std::endl;
	std::cout << std::endl;

	// do reduction
	return reduce( facet1, facet2, strat );
}

/*
   * Reduction-Function
   * @Input unsigned strat for the strategy, unsigned a for the facet (Drop, drop_smooth) and first facet for (unite, unite_...), unsigned b for the seconde facet
   * @return the reduced polytope or if the result would be unbounded the inital polytope
   */
template <typename Number, typename Converter, class Setting>
HPolytopeT<Number, Converter, Setting> HPolytopeT<Number, Converter, Setting>::reduce( unsigned a, unsigned b, REDUCTION_STRATEGY strat ) const {  // REDUCTION_STRATEGY

	// init
	HPolytopeT<Number, Converter, Setting> res = *this;

	std::vector<vector_t<Number>> evaluations;
	std::vector<Point<Number>> vertices;
	std::vector<std::vector<unsigned>> membersOfVertices;
	std::vector<unsigned> neighborsOf_a, neighborsOf_b;

	if ( strat > 0 ) {
		vertices = res.vertices();
		membersOfVertices = getMembersOfVertices( vertices );

		neighborsOf_a = getNeighborsOfIndex( a, membersOfVertices );
		neighborsOf_b = getNeighborsOfIndex( b, membersOfVertices );
	}

	// neighbor test for unite
	if ( strat > 1 && strat < 6 && std::find( neighborsOf_a.begin(), neighborsOf_a.end(), b ) == neighborsOf_a.end() ) {
		std::cout << "Error - second facet is no neighbor of first facet" << std::endl;
		return res;
	}

	// (try to) reduce
	switch ( strat ) {
		case REDUCTION_STRATEGY::DROP: {
			evaluations.push_back( res.constraints().at( a ).normal() );
			res.erase( a );  // delete facet
			break;
		}

		case REDUCTION_STRATEGY::DROP_SMOOTH: {
			std::vector<vector_t<Number>> smoothVectors;
			std::vector<Number> smoothVectors_offset;
			std::vector<unsigned> smoothVectors_oldIndices;

			for ( unsigned neighbor : neighborsOf_a ) {
				smoothVectors.push_back( res.constraints().at( neighbor ).normal() + res.constraints().at( a ).normal() );
				smoothVectors_offset.push_back( res.constraints().at( neighbor ).offset() + res.constraints().at( a ).offset() );
				smoothVectors_oldIndices.push_back( neighbor );
			}

			neighborsOf_a.push_back( a );
			std::sort( neighborsOf_a.begin(), neighborsOf_a.end() );
			std::reverse( neighborsOf_a.begin(), neighborsOf_a.end() );

			for ( unsigned i = 0; i < smoothVectors.size(); i++ ) {
				res.insert( Halfspace<Number>( smoothVectors[i], smoothVectors_offset[i] ) );  // update neighbor facets
			}

			for ( unsigned neighbor : neighborsOf_a ) {
				evaluations.push_back( res.constraints().at( neighbor ).normal() );
				res.erase( neighbor );  // delete not smoothed facet
			}

			break;
		}

		case REDUCTION_STRATEGY::UNITE: {
			vector_t<Number> uniteVector = ( res.constraints().at( a ).normal() + res.constraints().at( b ).normal() );
			Number uniteVector_offset = res.constraints().at( a ).offset() + res.constraints().at( b ).offset();

			evaluations.push_back( res.constraints().at( a ).normal() );
			evaluations.push_back( res.constraints().at( b ).normal() );

			res.insert( Halfspace<Number>( uniteVector, uniteVector_offset ) );  // insert united facet
			res.erase( a );
			res.erase( b );

			break;
		}

		case REDUCTION_STRATEGY::UNITE_SMOOTH: {
			vector_t<Number> uniteVector = vector_t<Number>::Zero( vertices.at( 0 ).dimension() );  // init smooth united facet
			Number uniteVector_offset;

			evaluations.push_back( res.constraints().at( a ).normal() );
			evaluations.push_back( res.constraints().at( b ).normal() );

			// smooth united facet is the sum of all (normalized and smoothed) neighbor facets of a and b
			// uniteVector
			for ( unsigned neighbor : neighborsOf_a ) {
				//if(neighbor!=b){
				vector_t<Number> vector_normalized = res.constraints().at( a ).normal() + res.constraints().at( neighbor ).normal();
				vector_normalized.normalize();
				uniteVector += vector_normalized;
				//}
			}
			for ( unsigned neighbor : neighborsOf_b ) {
				//if(neighbor!=a){
				vector_t<Number> vector_normalized = res.constraints().at( b ).normal() + res.constraints().at( neighbor ).normal();
				vector_normalized.normalize();
				uniteVector += vector_normalized;
				//}
			}

			// uniteVector_offset
			Point<Number> point_a_b = getVertexForVector( uniteVector, getVerticesOf2Indices( a, b, vertices, membersOfVertices ) );

			// smooth united facet offset is computed with the united facet and cutPoint of facet a and b
			uniteVector_offset = uniteVector.dot( point_a_b.rawCoordinates() );

			res.insert( Halfspace<Number>( uniteVector, uniteVector_offset ) );  // insert united facet
			res.erase( a );
			res.erase( b );

			break;
		}

		case REDUCTION_STRATEGY::UNITE_CUT: {
			vector_t<Number> uniteVector = vector_t<Number>::Zero( vertices.at( 0 ).dimension() );  // init cut united facet
			Number uniteVector_offset;

			evaluations.push_back( res.constraints().at( a ).normal() );
			evaluations.push_back( res.constraints().at( b ).normal() );

			// cut united facet is the sum of all possible normals
			for ( std::vector<vector_t<Number>> setOfPoints : getVerticesPermutationForFacet( a, b, vertices ) ) {  // get all set of points which could determine the new facet
				vector_t<Number> normal = computeNormal( setOfPoints, res.constraints().at( a ).normal() );
				if ( normal != vector_t<Number>::Zero( vertices.at( 0 ).dimension() ) ) normal.normalize();
				uniteVector += normal;  // add all these candidates
			}

			if ( uniteVector != vector_t<Number>::Zero( vertices.at( 0 ).dimension() ) ) uniteVector.normalize();
			//std::cout << "uniteVector Vertices: " << uniteVector << std::endl << std::endl;

			// uniteVector_offset
			Point<Number> point_a_b = getVertexForVector( uniteVector, getVerticesOf2Indices( a, b, vertices, membersOfVertices ) );

			// cut united facet offset is computed with the united facet and cutPoint of facet a and b
			uniteVector_offset = uniteVector.dot( point_a_b.rawCoordinates() );

			res.insert( Halfspace<Number>( uniteVector, uniteVector_offset ) );  // insert united facet
			res.erase( a );
			res.erase( b );

			break;
		}

		case REDUCTION_STRATEGY::UNITE_NORM: {
			double size_a = 0, size_b = 0;
			std::vector<Point<Number>> vertices_a = getVerticesOfIndex( a, vertices, membersOfVertices );
			std::vector<Point<Number>> vertices_b = getVerticesOfIndex( b, vertices, membersOfVertices );

			if ( this->dimension() == 2 ) {  // 2D
				if ( vertices_a.size() == 2 && vertices_b.size() == 2 ) {
					vector_t<Number> diff_a = vertices_a.at( 0 ).rawCoordinates() - vertices_a.at( 1 ).rawCoordinates();
					vector_t<Number> diff_b = vertices_b.at( 0 ).rawCoordinates() - vertices_b.at( 1 ).rawCoordinates();

					//std::cout << "Diff_a:\n" << diff_a << std::endl << std::endl;
					//std::cout << "Diff_b:\n" << diff_b << std::endl << std::endl;

					size_a = sqrt( (double)diff_a.dot( diff_a ) );
					size_b = sqrt( (double)diff_b.dot( diff_b ) );
				} else {
					size_a = 1;
					size_b = 1;
				}
			} else if ( this->dimension() > 2 ) {  // 3D ... nD
				unsigned permutation_count = 0;

				// compute weight a
				Permutator permutator_a( vertices_a.size(), this->dimension() );
				std::vector<std::size_t> permutation;
				while ( !permutator_a.end() ) {
					permutation = permutator_a();
					//std::cout << "Permutation_a for size: " << permutation << std::endl;

					std::vector<vector_t<Number>> verticesForCross;
					for ( unsigned p : permutation ) {
						verticesForCross.push_back( vertices_a.at( p ).rawCoordinates() );
					}

					vector_t<Number> cross = computeNormal( verticesForCross, this->constraints().at( a ).normal() );
					size_a += sqrt( (double)cross.dot( cross ) );
					permutation_count++;
				}
				size_a = size_a / (double)permutation_count;

				// compute weight b
				permutation_count = 0;
				Permutator permutator_b( vertices_b.size(), this->dimension() );
				while ( !permutator_b.end() ) {
					permutation = permutator_b();
					//std::cout << "Permutation_b for size: " << permutation << std::endl;

					std::vector<vector_t<Number>> verticesForCross;
					for ( unsigned p : permutation ) {
						verticesForCross.push_back( vertices_b.at( p ).rawCoordinates() );
					}

					vector_t<Number> cross = computeNormal( verticesForCross, this->constraints().at( b ).normal() );
					size_b += sqrt( (double)cross.dot( cross ) );
					permutation_count++;
				}
				size_b = size_b / (double)permutation_count;
			}

			std::pair<double, double> weights = std::pair<double, double>( size_a, size_b );
			//std::cout << "Weights computed and stored: " << weights << std::endl;

			// norm united facet works as unite_normal, but with weights for each component
			vector_t<Number> vector_a = res.constraints().at( a ).normal();
			vector_t<Number> vector_b = res.constraints().at( b ).normal();

			vector_a.normalize();
			vector_b.normalize();

			vector_t<Number> uniteVector = vector_a * weights.first + vector_b * weights.second;
			//std::cout << "uniteVector Weight: " << uniteVector << std::endl << std::endl;

			Number uniteVector_offset;

			evaluations.push_back( res.constraints().at( a ).normal() );
			evaluations.push_back( res.constraints().at( b ).normal() );

			// uniteVector_offset
			Point<Number> point_a_b = getVertexForVector( uniteVector, getVerticesOf2Indices( a, b, vertices, membersOfVertices ) );

			// norm united facet offset is computed with the united facet and (TODO furthest) cutPoint of facet a and b
			uniteVector_offset = uniteVector.dot( point_a_b.rawCoordinates() );

			res.insert( Halfspace<Number>( uniteVector, uniteVector_offset ) );  // insert united facet
			res.erase( a );
			res.erase( b );

			break;
		}
		default:
			break;
	}

	if ( res.isBounded( evaluations ) ) {
		//check if all vertices are inside the new polytope - optional
		//for(Point<Number> vertex: vertices){
		//  if(!res.contains(vertex)){
		//    //std::cout << "Vertex " << vertex << " is missing inside res -> use this" <<std::endl;
		//    return *this;
		//  }
		//}

		return res;
	}

	return *this;
}

/*
   * Reduction-Function with a special strategy
   * @Input vector_t<Number> directed is the vector in which direction we would like to reduce
   * @return the reduced polytope or if the result would be unbounded the inital polytope
   */
template <typename Number, typename Converter, class Setting>
HPolytopeT<Number, Converter, Setting> HPolytopeT<Number, Converter, Setting>::reduce_directed( std::vector<vector_t<Number>> directions, REDUCTION_STRATEGY strat ) const {
	// init
	HPolytopeT<Number, Converter, Setting> res = *this;

	// break if the amount of directions is greater than the actual size of the polytope TODO decide if used or not?
	//if(res.size()<directions.size()){
	//	//std::cout << "Warning - Output would be bigger than reduce_from, so use old polytope" << std::endl;
	//	return res;
	//}

	std::vector<Point<Number>> vertices = res.vertices();
	assert( !vertices.empty() );
	std::vector<std::vector<unsigned>> membersOfVertices = getMembersOfVertices( vertices );

	std::vector<unsigned> facets_erase;
	std::vector<Halfspace<Number>> facets_insert;

	/*
	 * idea to prevent adding of redundant planes:
	 *
	 * save for each vertex of vertices if they belong to dimension-directions the cone.
	 * test for each new direction which is added to a vertex if it is outside/inside the cone
	 * (if it already exists, else create the cone if there are enough facets, else save the direction).
	 *
	 * Needed: map for a vertex->cone TODO create 'test'
	 */
	std::map<Point<Number>, std::vector<vector_t<Number>>> mapVertices;

	// erase all facets if strat is directed_template
	if ( strat == REDUCTION_STRATEGY::DIRECTED_TEMPLATE ) {
		for ( unsigned i = 0; i < res.size(); i++ ) {
			facets_erase.push_back( i );
		}
	}

	// loop through each direction
	for ( const vector_t<Number>& directed : directions ) {
		Point<Number> point_directed;
		std::vector<std::pair<unsigned, Number>> scalarproducts;
		Number directed_offset = 0;
		//vector_t<Number> directed_normalized = directed;
		//directed_normalized.normalize();

		// collect vertex
		point_directed = getVertexForVector( directed, vertices );

		// update the vertex->cone, vertex->directions
		if ( mapVertices.find( point_directed ) != mapVertices.end() ) {
			// test consists of
			//   create cone if possible TODO create cone
			//   does cone contains directed
			//    -> true, break
			//    -> false, update and remove redundant directions TODO find redundant directions, only one?
			bool test = true;

			// update
			if ( test )
				mapVertices[point_directed].push_back( directed );
			else
				break;

			//std::cout << " Entry in mapVertices updated" << std::endl;
		} else {
			// create
			std::vector<vector_t<Number>> directionsForVertex;
			directionsForVertex.push_back( directed );
			mapVertices.insert( std::make_pair( point_directed, directionsForVertex ) );
			//std::cout << " Entry in mapVertices created" << std::endl;
		}

		// determine offset of directed
		directed_offset = directed.dot( point_directed.rawCoordinates() );

		// collect facets to erase
		switch ( strat ) {
			case REDUCTION_STRATEGY::DIRECTED_SMALL: {
				for ( unsigned v = 0; v < vertices.size(); v++ ) {
					if ( vertices[v] == point_directed ) {
						for ( unsigned memberOfVertex : membersOfVertices[v] ) {
							vector_t<Number> dummy = res.constraints().at( memberOfVertex ).normal();
							//dummy.normalize();
							//Number scalarproduct= dummy.dot(directed_normalized);

							if ( std::find( facets_erase.begin(), facets_erase.end(), memberOfVertex ) == facets_erase.end() ) {  //} && !carl::AlmostEqual2sComplement(scalarproduct+1, Number(1.0)) && scalarproduct>0){
								facets_erase.push_back( memberOfVertex );
							}
						}
					}
				}
				break;
			}
			case REDUCTION_STRATEGY::DIRECTED_BIG: {
				for ( unsigned i = 0; i < res.size(); i++ ) {
					vector_t<Number> dummy = res.constraints().at( i ).normal();
					//dummy.normalize();
					//Number scalarproduct= dummy.dot(directed_normalized);
					Number scalarproduct = dummy.dot( directed );

					if ( std::find( facets_erase.begin(), facets_erase.end(), i ) == facets_erase.end() && scalarproduct > 0 ) {
						facets_erase.push_back( i );
					}
				}
				break;
			}
			default:
				break;
		}

		// TODO if test with cone works insert Halfspace after the directions-loop
		facets_insert.push_back( Halfspace<Number>( directed, directed_offset ) );
	}

	// insert
	for ( Halfspace<Number> facet_insert : facets_insert ) {
		res.insert( facet_insert );
	}

	// erase
	std::sort( facets_erase.begin(), facets_erase.end(), []( const unsigned left, const unsigned right ) { return left > right; } );

	std::vector<vector_t<Number>> evaluations;
	for ( unsigned facet_erase : facets_erase ) {
		evaluations.push_back( res.constraints().at( facet_erase ).normal() );
		res.erase( facet_erase );
	}

	if ( strat == REDUCTION_STRATEGY::DIRECTED_TEMPLATE ) {
		return res;
	}

	if ( res.isBounded( evaluations ) ) {
		for ( Point<Number> vertex : vertices ) {
			if ( !res.contains( vertex ) ) {
				//std::cout << "Vertex " << vertex << " is missing inside res -> use this" <<std::endl << std::endl;
				return *this;
			}
		}

		//res.removeRedundantPlanes(); // remove redundant planes here or in the overall algorithm

		return res;
	}

	return *this;
}

}  // namespace hypro
