
#include "Polytope.h"

namespace hypro {
template <typename Number, typename Converter, class Setting>
PolytopeT<Number, Converter, Setting>::PolytopeT()
	: mPolyhedron( 0, Parma_Polyhedra_Library::EMPTY )
	, mPoints()
	, mPointsUpToDate( false ) {
}

template <typename Number, typename Converter, class Setting>
PolytopeT<Number, Converter, Setting>::PolytopeT( const PolytopeT<Number, Converter, Setting>& orig )
	: mPolyhedron( orig.mPolyhedron )
	, mPoints( orig.mPoints )
	, mPointsUpToDate( orig.mPointsUpToDate ) {
}

template <typename Number, typename Converter, class Setting>
PolytopeT<Number, Converter, Setting>::~PolytopeT() {
}

template <typename Number, typename Converter, class Setting>
PolytopeT<Number, Converter, Setting>::PolytopeT( unsigned dimension )
	: mPolyhedron( dimension, Parma_Polyhedra_Library::EMPTY )
	, mPoints()
	, mPointsUpToDate( true ) {
}

template <typename Number, typename Converter, class Setting>
PolytopeT<Number, Converter, Setting>::PolytopeT( const Point<Number>& _point )
	: mPolyhedron( Parma_Polyhedra_Library::C_Polyhedron( _point.dimension(), Parma_Polyhedra_Library::EMPTY ) ) {
	// std::cout << "Try Ppint: " << _point << std::endl;
	mPolyhedron.add_generator( polytope::pointToGenerator( _point ) );
	mPoints.push_back( _point );
	mPointsUpToDate = true;
}

template <typename Number, typename Converter, class Setting>
PolytopeT<Number, Converter, Setting>::PolytopeT( const typename std::vector<Point<Number>>& points ) {
	// mPolyhedron.initialize();
	// std::cout << "Try Points" << std::endl;
	mPolyhedron =
		  Parma_Polyhedra_Library::C_Polyhedron( points.begin()->dimension(), Parma_Polyhedra_Library::EMPTY );
	for ( auto& point : points ) {
		mPolyhedron.add_generator( polytope::pointToGenerator( point ) );
		mPoints.push_back( point );
	}
	mPointsUpToDate = true;
}

template <typename Number, typename Converter, class Setting>
PolytopeT<Number, Converter, Setting>::PolytopeT( const typename std::vector<vector_t<Number>>& points ) {
	mPolyhedron = Parma_Polyhedra_Library::C_Polyhedron( points.begin()->rows(), Parma_Polyhedra_Library::EMPTY );
	for ( auto pointIt = points.begin(); pointIt != points.end(); ++pointIt ) {
		Parma_Polyhedra_Library::Generator tmp = polytope::pointToGenerator( *pointIt );
		mPolyhedron.add_generator( tmp );
		Point<Number> tmpPoint = Point<Number>( *pointIt );
		mPoints.push_back( tmpPoint );
	}
	mPointsUpToDate = true;
}

template <typename Number, typename Converter, class Setting>
PolytopeT<Number, Converter, Setting>::PolytopeT( const matrix_t<Number>& A, const vector_t<Number>& b ) {
	assert( A.rows() == b.rows() );
	mPolyhedron = Parma_Polyhedra_Library::C_Polyhedron( A.cols(), Parma_Polyhedra_Library::UNIVERSE );
	for ( unsigned rowIndex = 0; rowIndex < A.rows(); ++rowIndex ) {
		// std::cout << "Process row " << rowIndex << std::endl;
		Parma_Polyhedra_Library::Constraint constraint = polytope::createConstraint( vector_t<Number>( A.row( rowIndex ) ), b( rowIndex ) );

		mPolyhedron.add_constraint( constraint );
	}
	mPointsUpToDate = false;
}

template <typename Number, typename Converter, class Setting>
PolytopeT<Number, Converter, Setting>::PolytopeT( const matrix_t<Number>& A ) {
	mPolyhedron = Parma_Polyhedra_Library::C_Polyhedron( A.rows(), Parma_Polyhedra_Library::UNIVERSE );
	for ( unsigned rowIndex = 0; rowIndex < A.rows(); ++rowIndex ) {
		Parma_Polyhedra_Library::Constraint constraint = polytope::createConstraint( vector_t<Number>( A.row( rowIndex ) ), Number( 0 ) );

		mPolyhedron.add_constraint( constraint );
		// mPolyhedron.add_generator(gen);
	}
	mPointsUpToDate = false;
}

template <typename Number, typename Converter, class Setting>
PolytopeT<Number, Converter, Setting>::PolytopeT( const Parma_Polyhedra_Library::C_Polyhedron& _rawPoly )
	: mPolyhedron( _rawPoly )
	, mPoints()
	, mPointsUpToDate( false ) {
}

template <typename Number, typename Converter, class Setting>
bool PolytopeT<Number, Converter, Setting>::empty() const {
	return mPolyhedron.is_empty();
}

template <typename Number, typename Converter, class Setting>
void PolytopeT<Number, Converter, Setting>::addPoint( const Point<Number>& point ) {
	Parma_Polyhedra_Library::Generator tmp = polytope::pointToGenerator( point );
	if ( mPolyhedron.space_dimension() != tmp.space_dimension() ) {
		mPolyhedron.add_space_dimensions_and_embed( tmp.space_dimension() );
	}
	mPolyhedron.add_generator( tmp );
	mPoints.push_back( point );
}

template <typename Number, typename Converter, class Setting>
void PolytopeT<Number, Converter, Setting>::updatePoints() const {
	// using Parma_Polyhedra_Library::IO_Operators::operator<<;
	if ( !mPointsUpToDate ) {
		// std::cout << __func__ << ": " << *this << std::endl;
		mPoints.clear();
		for ( auto& generator : mPolyhedron.minimized_generators() ) {
			Point<Number> tmp = polytope::generatorToPoint<Number>( generator );
			mPoints.push_back( tmp );
		}
		mPointsUpToDate = true;
	}
}

template <typename Number, typename Converter, class Setting>
std::vector<Point<Number>> PolytopeT<Number, Converter, Setting>::vertices( const matrix_t<Number>& ) const {
	if ( !mPointsUpToDate ) {
		updatePoints();
	}
	return mPoints;
}

// returns the fan of the Polytope
template <typename Number, typename Converter, class Setting>
const Fan<Number>& PolytopeT<Number, Converter, Setting>::fan() {
	return mFan;
}

template <typename Number, typename Converter, class Setting>
Fan<Number>& PolytopeT<Number, Converter, Setting>::rFan() {
	return mFan;
}

// sets the fan of the Polytope
template <typename Number, typename Converter, class Setting>
void PolytopeT<Number, Converter, Setting>::setFan( const Fan<Number>& _fan ) {
	mFan = _fan;
}

template <typename Number, typename Converter, class Setting>
void PolytopeT<Number, Converter, Setting>::calculateFan() {
	std::vector<Facet<Number>> facets = convexHull( mPoints );
	std::set<Point<Number>> preresult;
	for ( unsigned i = 0; i < facets.size(); i++ ) {
		for ( unsigned j = 0; j < facets[i].vertices().size(); j++ ) {
			preresult.insert( facets[i].vertices().at( j ) );
		}
	}
	Fan<Number> fan;
	for ( auto& point : preresult ) {
		Cone<Number>* cone = new Cone<Number>();
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

							cone->add( std::shared_ptr<Halfspace<Number>>(
								  new Halfspace<Number>( result, result.dot( point.rawCoordinates() ) ) ) );
							// cone->add(std::make_shared<Halfspace<Number>>(Halfspace<Number>(result,
							// result.dot(point.rawCoordinates()))));
						}
					}
				}
			}
		}
		fan.add( cone );
	}
	mFan = fan;
}

template <typename Number, typename Converter, class Setting>
void PolytopeT<Number, Converter, Setting>::print() const {
	std::cout << *this << std::endl;
}

template <typename Number, typename Converter, class Setting>
const Parma_Polyhedra_Library::C_Polyhedron& PolytopeT<Number, Converter, Setting>::rawPolyhedron() const {
	return mPolyhedron;
}

template <typename Number, typename Converter, class Setting>
std::size_t PolytopeT<Number, Converter, Setting>::dimension() const {
	return mPolyhedron.space_dimension();
}

template <typename Number, typename Converter, class Setting>
PolytopeT<Number, Converter, Setting> PolytopeT<Number, Converter, Setting>::linearTransformation( const matrix_t<Number>& A ) const {
	using Parma_Polyhedra_Library::IO_Operators::operator<<;

	PolytopeT<Number, Converter, Setting> result;

	const Parma_Polyhedra_Library::Generator_System generators = this->mPolyhedron.generators();

	// Create Eigen::Matrix from Polytope representing the vertices
	matrix_t<Number> polytopeMatrix = matrix_t<Number>::Zero( this->dimension(), polytope::gsSize( generators ) );
	unsigned gCount = 0;

	mpz_class coefficient;
	mpz_class divisor;
	Number value;

	for ( auto generatorIt = generators.begin(); generatorIt != generators.end();
		  ++generatorIt ) {
		// Assuming the divisor stays the same in one generator
		divisor = generatorIt->divisor();
		for ( unsigned varIndex = 0; varIndex < this->dimension(); ++varIndex ) {
			coefficient = generatorIt->coefficient( VariablePool::getInstance().pplVarByIndex( varIndex ) );
			mpq_class tmpValue( coefficient, divisor );
			value = carl::convert<mpq_class, Number>( tmpValue );
			polytopeMatrix( varIndex, gCount ) = value;
		}
		++gCount;
	}

	// apply lineartransformation
	matrix_t<Number> res( this->dimension(), polytope::gsSize( generators ) );

	res = ( A * polytopeMatrix );

	// clear actual generators and add new ones
	std::vector<vector_t<Number>> ps;
	for ( unsigned i = 0; i < res.cols(); ++i ) {
		vector_t<Number> t = vector_t<Number>( res.rows() );
		for ( unsigned j = 0; j < res.rows(); ++j ) t( j ) = res.col( i )( j );
		ps.push_back( t );
	}
	Parma_Polyhedra_Library::C_Polyhedron tmp = Parma_Polyhedra_Library::C_Polyhedron( res.rows(), Parma_Polyhedra_Library::EMPTY );

	for ( auto& pointSetIt : ps ) {
		tmp.add_generator( polytope::pointToGenerator( pointSetIt ) );
	}

	result.mPolyhedron = tmp;
	return result;
}

template <typename Number, typename Converter, class Setting>
PolytopeT<Number, Converter, Setting> PolytopeT<Number, Converter, Setting>::affineTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const {
	// using Parma_Polyhedra_Library::IO_Operators::operator<<;

	PolytopeT<Number, Converter, Setting> result;

	const Parma_Polyhedra_Library::Generator_System generators = this->mPolyhedron.generators();

	// Create Eigen::Matrix from Polytope representing the vertices
	matrix_t<Number> polytopeMatrix = matrix_t<Number>::Zero( this->dimension(), polytope::gsSize( generators ) );
	unsigned gCount = 0;

	mpz_class coefficient;
	mpz_class divisor;
	Number value;

	for ( auto generatorIt = generators.begin(); generatorIt != generators.end();
		  ++generatorIt ) {
		// Assuming the divisor stays the same in one generator
		divisor = generatorIt->divisor();
		for ( unsigned varIndex = 0; varIndex < this->dimension(); ++varIndex ) {
			coefficient = generatorIt->coefficient( VariablePool::getInstance().pplVarByIndex( varIndex ) );
			mpq_class tmpValue( coefficient, divisor );
			value = carl::convert<mpq_class, Number>( tmpValue );
			polytopeMatrix( varIndex, gCount ) = value;
		}
		++gCount;
	}

	// apply lineartransformation
	matrix_t<Number> res( this->dimension(), polytope::gsSize( generators ) );

	res = ( A * polytopeMatrix );
	matrix_t<Number> constantPart( res.rows(), res.cols() );
	for ( unsigned m = 0; m < constantPart.rows(); ++m )
		for ( unsigned n = 0; n < constantPart.cols(); ++n ) {
			constantPart( m, n ) = b( m );
		}
	res += constantPart;

	// clear actual generators and add new ones
	std::vector<vector_t<Number>> ps;
	for ( unsigned i = 0; i < res.cols(); ++i ) {
		vector_t<Number> t = vector_t<Number>( res.rows() );
		for ( unsigned j = 0; j < res.rows(); ++j ) t( j ) = res.col( i )( j );
		ps.push_back( t );
	}
	Parma_Polyhedra_Library::C_Polyhedron tmp = Parma_Polyhedra_Library::C_Polyhedron( res.rows(), Parma_Polyhedra_Library::EMPTY );

	for ( auto& pointSetIt : ps ) {
		tmp.add_generator( polytope::pointToGenerator( pointSetIt ) );
	}

	result.mPolyhedron = tmp;
	result.updatePoints();

	// update neighbor relations
	/*
	for(unsigned pointIndex = 0; pointIndex < mPoints.size(); ++pointIndex)
	{
			//std::cout << "Create neighbor for original node: " <<
	mPoints.at(pointIndex) << " , which is the new: " <<
	newPoints.at(pointIndex) << std::endl;
			std::vector<Point<Number> > tmpNeighbors =
	mPoints.at(pointIndex).neighbors();
			for(unsigned neighborIndex = 0 ; neighborIndex <  tmpNeighbors.size();
	++neighborIndex)
			{
					for(unsigned refPoint = 0; refPoint < mPoints.size();
	++refPoint)
					{
							if( mPoints.at(refPoint) ==
	tmpNeighbors.at(neighborIndex))
							{
									//std::cout << "Add neighbor: " <<
	tmpNeighbors.at(neighborIndex) << ", which is new " <<
	*tmpPoints.at(refPoint) << std::endl;
									newPoints.at(pointIndex).addNeighbor(tmpPoints.at(refPoint));
							}
					}
			}
	}
	*/
	return result;
}

template <typename Number, typename Converter, class Setting>
PolytopeT<Number, Converter, Setting> PolytopeT<Number, Converter, Setting>::projectOn( const std::vector<std::size_t>& dimensions ) const {
	// create inverse of dimensions to get the variables to unconstrain
	Parma_Polyhedra_Library::Variables_Set vars;
	for ( unsigned i = 0; i < this->dimension(); ++i ) {
		if ( std::find( dimensions.begin(), dimensions.end(), i ) == dimensions.end() ) {
			vars.insert( VariablePool::getInstance().pplVarByIndex( i ) );
		}
	}
	Parma_Polyhedra_Library::C_Polyhedron tmp = mPolyhedron;
	tmp.remove_space_dimensions( vars );
	return PolytopeT( tmp );
}

template <typename Number, typename Converter, class Setting>
PolytopeT<Number, Converter, Setting> PolytopeT<Number, Converter, Setting>::minkowskiSum( const PolytopeT<Number, Converter, Setting>& rhs ) const {
	PolytopeT<Number, Converter, Setting> result;

	result = Parma_Polyhedra_Library::C_Polyhedron( 0, Parma_Polyhedra_Library::EMPTY );

	assert( this->dimension() == rhs.dimension() );

	for ( auto& genA : mPolyhedron.generators() ) {
		Point<Number> tmpA = polytope::generatorToPoint<Number>( genA );
		for ( auto& genB : rhs.rawPolyhedron().generators() ) {
			Point<Number> tmpB = polytope::generatorToPoint<Number>( genB );

			Point<Number> res = tmpA.extAdd( tmpB );
			result.addPoint( res );
		}
	}

	mPointsUpToDate = false;
	return result;
}

/**
 * @author: Chris K.
 * Minkowski Sum computation based on Fukuda
 */
template <typename Number, typename Converter, class Setting>
PolytopeT<Number, Converter, Setting> PolytopeT<Number, Converter, Setting>::altMinkowskiSum( PolytopeT<Number, Converter, Setting>& rhs ) {
	PolytopeT<Number, Converter, Setting> result;
	// TODO compute adjacency for this & rhs vertices (currently manually defined
	// within the tests)
	result = Parma_Polyhedra_Library::C_Polyhedron( 0, Parma_Polyhedra_Library::EMPTY );
	std::vector<Point<Number>> alreadyExploredVertices;

	/**
	 * Preprocessing
	 */

	// delta = max vertex degree
	int delta_1 = this->computeMaxVDegree();
	int delta_2 = rhs.computeMaxVDegree();

	// initVertex = initial extreme point & root of spanning tree
	Point<Number> initVertex = this->computeInitVertex( rhs );
	result.addPoint( initVertex );
	alreadyExploredVertices.push_back( initVertex );

	if ( Setting::fukuda_DEBUG ) {
		std::cout << "---------------" << std::endl;
		std::cout << "following Vertex is part of result: " << initVertex << std::endl;
		std::cout << "---------------" << std::endl;
	}

	// compute the maximizer vector (& its target) for the initial extreme point
	// -> necessary for localSearch()
	Point<Number> sinkMaximizerTarget;
	vector_t<Number> sinkMaximizerVector = polytope::computeMaximizerVector( sinkMaximizerTarget, initVertex );

	// compute the normal cone of the initial extreme point
	Cone<Number>* cone = polytope::computeCone( initVertex, sinkMaximizerVector );
	// add this normal cone to the fan of the polytope
	result.rFan().add( cone );

	// set currentVertex to initVertex
	Point<Number> currentVertex = initVertex;

	// counter initially (1,0)
	std::pair<int, int> counter;
	counter.first = 1;
	counter.second = 0;

	/**
	 * Reverse Search Algorithm
	 */
	if ( Setting::fukuda_DEBUG ) {
		std::cout << "-------------------------" << std::endl;
		std::cout << "-------------------------" << std::endl;
		std::cout << "The Preprocessing Ends here - Start of Algorithm" << std::endl;
		std::cout << "-------------------------" << std::endl;
		std::cout << "-------------------------" << std::endl;
	}

	Point<Number> nextVertex;
	std::vector<std::pair<int, int>> counterMemory;
	bool alreadyExplored;
	std::map<Point<Number>, Point<Number>> parentMap;

	do {
		while ( counter.first < 2 || ( counter.first == 2 && counter.second < delta_2 ) ) {
			if ( Setting::fukuda_DEBUG ) {
				std::cout << "Max. Vertex Degree in Poly 1: " << delta_1 << std::endl;
				std::cout << "Max. Vertex Degree in Poly 2: " << delta_2 << std::endl;
			}

			alreadyExplored = false;

			// increment counter by 1
			if ( counter.second == delta_1 ) {
				counter.first = 2;
				counter.second = 1;
			} else {
				counter.second += 1;
			}

			if ( Setting::fukuda_DEBUG ) {
				std::cout << "Counter tuple: (" << counter.first << "," << counter.second << ")" << std::endl;
			}

			// choose next Vertex, only continue if one exists
			if ( polytope::adjOracle( nextVertex, currentVertex, counter ) ) {
				// set neighbors of the vertices accordingly - the adjacency oracle
				// confirmed neighborship
				// TODO problem: addNeighbor requires a pointer
				// currentVertex.addNeighbor(&nextVertex);
				// nextVertex.addNeighbor(&currentVertex);

				for ( unsigned i = 0; i < alreadyExploredVertices.size(); ++i ) {
					if ( nextVertex == alreadyExploredVertices.at( i ) ) {
						alreadyExplored = true;
						if ( Setting::fukuda_DEBUG ) {
							std::cout << "Vertex has already been explored: " << nextVertex << std::endl;
						}
					}
				}
				if ( alreadyExplored ) {
					if ( Setting::fukuda_DEBUG ) {
						std::cout << "continue with next loop iteration" << std::endl;
						std::cout << "-------------------------" << std::endl;
					}
					// dont traverse back and forth between two vertices
					continue;
				}
				Point<Number> localSearchVertex = result.localSearch( nextVertex, sinkMaximizerTarget );
				parentMap.insert( std::make_pair( nextVertex, localSearchVertex ) );
				if ( localSearchVertex == currentVertex ) {
					// reverse traverse
					currentVertex = nextVertex;

					// add to result Poly
					result.addPoint( currentVertex );
					if ( Setting::fukuda_DEBUG ) {
						std::cout << "---------------" << std::endl;
						std::cout << "following Vertex is part of result: " << currentVertex << std::endl;
						std::cout << "---------------" << std::endl;
					}

					alreadyExploredVertices.push_back( currentVertex );
					// store the current counter value - needed if DFS comes back this
					// vertex
					counterMemory.push_back( counter );
					if ( Setting::fukuda_DEBUG ) {
						std::cout << "---------------" << std::endl;
						std::cout << "Counter Memory Stack - add Counter: (" << counter.first << "," << counter.second
								  << ")" << std::endl;
						std::cout << "Already explored Vertices: " << alreadyExploredVertices << std::endl;
						std::cout << "---------------" << std::endl;
					}

					counter.first = 1;
					counter.second = 0;
				}
			}
		}
		if ( Setting::fukuda_DEBUG ) {
			std::cout << "---------------" << std::endl;
			std::cout << "While Loop left" << std::endl;
			std::cout << "---------------" << std::endl;
		}
		if ( currentVertex != initVertex ) {
			// forward traverse
			// currentVertex = result.localSearch(currentVertex, sinkMaximizerTarget);
			// instead of computing the local Search result again, retrieve the parent
			// from the parentMap
			currentVertex = parentMap.at( currentVertex );

			if ( Setting::fukuda_DEBUG ) {
				std::cout << "Local Search finished" << std::endl;
				std::cout << "counterMemory size: " << counterMemory.size() << std::endl;
			}

			// restore counter such that adjOracle(currentVertex,counter) = temp
			// use the "stack" counterMemory for that
			counter = counterMemory.at( counterMemory.size() - 1 );
			counterMemory.pop_back();

			if ( Setting::fukuda_DEBUG ) {
				std::cout << "---------------" << std::endl;
				std::cout << "Counter restored to: (" << counter.first << "," << counter.second << ")" << std::endl;
				std::cout << "While Loop Condition: "
						  << ( ( currentVertex != initVertex ) || ( counter.first != 2 && counter.second != delta_2 ) )
						  << std::endl;
				std::cout << "CurrrentVertex != initVertex: " << ( currentVertex != initVertex ) << std::endl;
				std::cout << "Counter != (2,2): " << ( counter.first != 2 || counter.second != delta_2 ) << std::endl;
				std::cout << "---------------" << std::endl;
			}
		}

	} while ( ( currentVertex != initVertex ) || ( counter.first != 2 || counter.second != delta_2 ) );

	mPointsUpToDate = false;

	return result;
}

template <typename Number, typename Converter, class Setting>
PolytopeT<Number, Converter, Setting> PolytopeT<Number, Converter, Setting>::intersect( const PolytopeT<Number, Converter, Setting>& rhs ) const {
	// std::cout << __func__ << ": " << *this << " and " << rhs << std::endl;
	if ( rhs.dimension() == 0 ) {
		return PolytopeT<Number, Converter, Setting>();
	} else {
		Parma_Polyhedra_Library::C_Polyhedron res = mPolyhedron;
		res.intersection_assign( rhs.rawPolyhedron() );
		PolytopeT<Number, Converter, Setting> result = PolytopeT<Number, Converter, Setting>( res );

		return result;
	}
}

template <typename Number, typename Converter, class Setting>
PolytopeT<Number, Converter, Setting> PolytopeT<Number, Converter, Setting>::intersectHalfspace( const Halfspace<Number>& rhs ) const {
	if ( rhs.dimension() == 0 ) {
		return PolytopeT<Number, Converter, Setting>();
	} else {
		Parma_Polyhedra_Library::C_Polyhedron res = mPolyhedron;
		Parma_Polyhedra_Library::Constraint constraint = polytope::createConstraint( rhs.normal(), rhs.offset() );

		res.add_constraint( constraint );
		PolytopeT<Number, Converter, Setting> result = PolytopeT<Number, Converter, Setting>( res );

		return result;
	}
}

template <typename Number, typename Converter, class Setting>
PolytopeT<Number, Converter, Setting> PolytopeT<Number, Converter, Setting>::intersectHalfspaces( const matrix_t<Number>& _mat,
																								  const vector_t<Number>& _vec ) const {
	// using Parma_Polyhedra_Library::IO_Operators::operator<<;
	assert( _mat.rows() == _vec.rows() );
	Parma_Polyhedra_Library::C_Polyhedron res = this->mPolyhedron;
	for ( unsigned rowIndex = 0; rowIndex < _mat.rows(); ++rowIndex ) {
		Parma_Polyhedra_Library::Constraint constraint = polytope::createConstraint( vector_t<Number>( _mat.row( rowIndex ) ), _vec( rowIndex ) );
		res.refine_with_constraint( constraint );
	}
	return PolytopeT( res );
}

template <typename Number, typename Converter, class Setting>
std::pair<CONTAINMENT, PolytopeT<Number, Converter, Setting>> PolytopeT<Number, Converter, Setting>::satisfiesHalfspace( const Halfspace<Number>& rhs ) const {
	TRACE( "hypro.pplPolytope", *this << " and halfspace " << rhs );
	PolytopeT<Number, Converter, Setting> res = this->intersectHalfspace( rhs );
	if ( !res.empty() ) {
		for ( auto point : this->vertices() ) {
			if ( !res.contains( point ) ) {
				return std::make_pair( CONTAINMENT::PARTIAL, res );
			}
		}
		return std::make_pair( CONTAINMENT::FULL, res );
		// return std::make_pair(CONTAINMENT::YES, res);
	} else {
		return std::make_pair( CONTAINMENT::NO, res );
	}
}

template <typename Number, typename Converter, class Setting>
std::pair<CONTAINMENT, PolytopeT<Number, Converter, Setting>> PolytopeT<Number, Converter, Setting>::satisfiesHalfspaces( const matrix_t<Number>& _mat,
																														  const vector_t<Number>& _vec ) const {
	TRACE( "hypro.pplPolytope", *this << " and halfspaces " << _mat << " <= " << _vec );
	PolytopeT<Number, Converter, Setting> res = this->intersectHalfspaces( _mat, _vec );
	if ( !res.empty() ) {
		for ( auto point : this->vertices() ) {
			if ( !res.contains( point ) ) {
				return std::make_pair( CONTAINMENT::PARTIAL, res );
			}
		}
		return std::make_pair( CONTAINMENT::FULL, res );
		// return std::make_pair(CONTAINMENT::YES, res);
	} else {
		return std::make_pair( CONTAINMENT::NO, res );
	}
}

template <typename Number, typename Converter, class Setting>
PolytopeT<Number, Converter, Setting> PolytopeT<Number, Converter, Setting>::hull() const {
	// Parma_Polyhedra_Library::Generator_System gs = mPolyhedron.minimized_generators();
	// PolytopeT<Number,Converter,Setting> result = PolytopeT<Number,Converter,Setting>(C_Polyhedron(gs));

	if ( !mPointsUpToDate ) {
		// std::cout<<__func__ << " : " <<__LINE__ <<std::endl;
		updatePoints();
	}
	// std::cout<<__func__ << " : " <<__LINE__ <<std::endl;
	std::vector<std::shared_ptr<Facet<Number>>> hull = convexHull( mPoints ).first;
	// std::cout<<__func__ << " : " <<__LINE__ <<std::endl;
	std::set<Point<Number>> preresult;

	for ( unsigned i = 0; i < hull.size(); i++ ) {
		for ( unsigned j = 0; j < hull[i]->rVertices().size(); j++ ) {
			// std::cout << "Unite created point: " <<
			// hull[i]->vertices().at(j).rawCoordinates().transpose() <<
			// std::endl;

			preresult.insert( hull[i]->rVertices().at( j ) );

			// it->joinNeighbors(hull[i]->rVertices().at(j).neighbors());

			// std::cout<<((Point<Number>)*(preresult.find(hull[i]->rVertices().at(j)))).neighbors().size()<<std::endl;

			/*
					std::cout << "Set after insert: ";
					for(const auto& point : preresult) {
					std::cout << point.rawCoordinates().transpose() << ", ";
					}
					std::cout << std::endl;
			*/
		}
	}
	// std::cout<<__func__ << " : " <<__LINE__ <<std::endl;
	std::vector<Point<Number>> points;
	// std::cout<<__func__ << " : " <<__LINE__ <<std::endl;
	for ( auto& point : preresult ) {
		points.push_back( point );
	}
	// std::cout<<__func__ << " : " <<__LINE__ <<std::endl;
	PolytopeT<Number, Converter, Setting> result = PolytopeT<Number, Converter, Setting>( points );
	// std::cout<<__func__ << " : " <<__LINE__ <<std::endl;
	mPointsUpToDate = false;

	return result;
}

template <typename Number, typename Converter, class Setting>
bool PolytopeT<Number, Converter, Setting>::contains( const Point<Number>& point ) const {
	return mPolyhedron.contains( PolytopeT<Number, Converter, Setting>( point ).rawPolyhedron() );
}

template <typename Number, typename Converter, class Setting>
bool PolytopeT<Number, Converter, Setting>::contains( const PolytopeT<Number, Converter, Setting>& poly ) const {
	return mPolyhedron.contains( poly.rawPolyhedron() );
}

template <typename Number, typename Converter, class Setting>
PolytopeT<Number, Converter, Setting> PolytopeT<Number, Converter, Setting>::unite( const PolytopeT<Number, Converter, Setting>& rhs ) const {
	if ( rhs.empty() ) {
		return *this;
	}

	updatePoints();

	Parma_Polyhedra_Library::C_Polyhedron res = mPolyhedron;
	res.poly_hull_assign( rhs.rawPolyhedron() );
	PolytopeT<Number, Converter, Setting> result = PolytopeT<Number, Converter, Setting>( res );
	return result;
}
/*
template <typename Number, typename Converter, class Setting>
PolytopeT<Number,Converter,Setting> PolytopeT<Number,Converter,Setting>::unite(const PolytopeT<Number,Converter,Setting>& polytopes) {
	if(polytopes.empty()) {
		return PolytopeT<Number,Converter,Setting>::Empty();
	}

	C_Polyhedron res;
	for(const auto& poly : polytopes) {
		poly.updatePoints();
		res.poly_hull_assign(poly.rawPolyhedron());
	}

	PolytopeT<Number,Converter,Setting> result = PolytopeT<Number,Converter,Setting>(res);
	return result;
}
*/
template <typename Number, typename Converter, class Setting>
Number PolytopeT<Number, Converter, Setting>::supremum() const {
	Number max = 0;
	for ( auto& point : this->vertices() ) {
		Number inftyNorm = hypro::Point<Number>::inftyNorm( point );
		max = max > inftyNorm ? max : inftyNorm;
	}
	return max;
}

/*
template<typename Number>
PolytopeT<Number,Converter,Setting>& PolytopeT<Number,Converter,Setting>::operator= (const PolytopeT<Number,Converter,Setting>& rhs)
{
  if (this != &rhs)
  {
		PolytopeT<Number,Converter,Setting> tmp(rhs);
		std::swap(*this, tmp);
  }
  return *this;
}
*/

template <typename Number, typename Converter, class Setting>
bool operator==( const PolytopeT<Number, Converter, Setting>& rhs, const PolytopeT<Number, Converter, Setting>& lhs ) {
	return ( rhs.rawPolyhedron() == lhs.rawPolyhedron() );
}
template <typename Number, typename Converter, class Setting>
bool operator!=( const PolytopeT<Number, Converter, Setting>& rhs, const PolytopeT<Number, Converter, Setting>& lhs ) {
	return ( rhs.rawPolyhedron() != lhs.rawPolyhedron() );
}

/**
 * @author: Chris K.
 * in the following: Utility functions for altMinkowskiSum()
 */

/**
 * returns the maximum vertex degree in a polytope
 */
template <typename Number, typename Converter, class Setting>
int PolytopeT<Number, Converter, Setting>::computeMaxVDegree() {
	std::vector<Point<Number>> points = this->points();
	int max = 0;

	for ( typename std::vector<Point<Number>>::iterator it = points.begin(); it != points.end(); ++it ) {
		if ( max < it->neighbors().size() ) {
			max = it->neighbors().size();
		}
	}

	return max;
}

/**
 * returns the vertex with maximum x-value for a given polytope
 */
template <typename Number, typename Converter, class Setting>
Point<Number> PolytopeT<Number, Converter, Setting>::computeMaxPoint() {
	Point<Number> result;

	if ( !mPoints.empty() ) {
		result = *( mPoints.begin() );
		for ( typename std::vector<Point<Number>>::iterator it = mPoints.begin(); it != mPoints.end(); ++it ) {
			assert( it->dimension() == result.dimension() );
			assert( it->hasDimension( result.coordinates().begin()->first ) );
			Number coeff = it->coordinate( result.coordinates().begin()->first );
			if ( result.coordinates().begin()->second < coeff ) {
				result = *it;
			}
		}
	}
	return result;
}

/**
 * returns one vertex of the sum polytope P = P1+P2
 */
template <typename Number, typename Converter, class Setting>
Point<Number> PolytopeT<Number, Converter, Setting>::computeInitVertex( PolytopeT<Number, Converter, Setting> _secondPoly ) {
	Point<Number> p1 = this->computeMaxPoint();
	Point<Number> p2 = _secondPoly.computeMaxPoint();

	Point<Number> res = p1.extAdd( p2 );

	// remember how the resulting point is composed (v= v1+v2)
	res.addToComposition( p1 );
	res.addToComposition( p2 );
	return res;
}

/**
 * the Local Search as per Fukuda's paper
 * computes the parent of a given vertex w.r.t the sink of the spanning tree
 */
template <typename Number, typename Converter, class Setting>
Point<Number> PolytopeT<Number, Converter, Setting>::localSearch( Point<Number>& _vertex, Point<Number>& _sinkMaximizerTarget ) {
	if ( Setting::fukuda_DEBUG ) {
		std::cout << "-------------------------" << std::endl;
		std::cout << "in the following: Local Search for Vertex " << _vertex << std::endl;
		std::cout << "-------------------------" << std::endl;
	}

	// compute the maximizer vector of the currently considered vertex
	Point<Number> maximizerTarget;
	vector_t<Number> maximizerVector = polytope::computeMaximizerVector( maximizerTarget, _vertex );

	// compute the ray direction (a vector)
	vector_t<Number> ray = polytope::computeEdge( maximizerTarget, _sinkMaximizerTarget );

	if ( Setting::fukuda_DEBUG ) {
		std::cout << "Starting Point of Ray: " << maximizerTarget << std::endl;
		std::cout << "End Point of Ray: " << _sinkMaximizerTarget << std::endl;
	}

	// compute the normal cone of _vertex
	Cone<Number>* cone = polytope::computeCone( _vertex, maximizerVector );

	// iterate through all planes and check which one intersects with the ray
	Number factor;
	Point<Number> origin = cone->origin();
	Halfspace<Number> intersectedPlane;

	std::vector<Halfspace<Number>*> planes = cone->get();

	if ( Setting::fukuda_DEBUG ) {
		std::cout << "-----------------" << std::endl;
		std::cout << "Ray: " << ray << std::endl;
	}

	for ( typename std::vector<Halfspace<Number>*>::iterator it = planes.begin(); it != planes.end(); ++it ) {
		if ( ( *it )->intersection( factor, ray ) ) {
			if ( Setting::fukuda_DEBUG ) {
				std::cout << "Intersection found " << std::endl;
			}
			intersectedPlane = *( *it );
			break;
		}
	}

	Point<Number> secondOrigin;

	if ( Setting::fukuda_DEBUG ) {
		std::cout << "-----------------" << std::endl;
		std::cout << "Normal of Intersection Plane: " << intersectedPlane.normal() << std::endl;
		std::cout << "Offset of Intersection Plane: " << intersectedPlane.offset() << std::endl;
		std::cout << "-----------------" << std::endl;
	}

	std::vector<vector_t<Number>> decompositionEdges = polytope::computeEdgeSet( _vertex );

	for ( unsigned i = 0; i < decompositionEdges.size(); i++ ) {
		Number dotProduct = intersectedPlane.normal().dot( decompositionEdges.at( i ) );
		Number normFactor = intersectedPlane.normal().norm() * decompositionEdges.at( i ).norm();

		// has to be done...
		dotProduct = std::round( dotProduct.toDouble() * 1000000 );
		normFactor = std::round( normFactor.toDouble() * 1000000 );

		if ( Setting::fukuda_DEBUG ) {
			std::cout << "Dot Product: " << dotProduct << std::endl;
			std::cout << "Norm Factor: " << normFactor << std::endl;
			std::cout << "Parallelism Factor: " << dotProduct / normFactor << std::endl;
			std::cout << "Value of the if condition: " << ( dotProduct / normFactor == 1 ) << std::endl;
		}

		if ( ( dotProduct / normFactor == 1 + EPSILON ) || ( dotProduct / normFactor == 1 - EPSILON ) ||
			 ( dotProduct / normFactor == -1 + EPSILON ) || ( dotProduct / normFactor == -1 - EPSILON ) ||
			 ( dotProduct / normFactor == -1 ) || ( dotProduct / normFactor == 1 ) ) {
			if ( Setting::fukuda_DEBUG ) {
				std::cout << "Parallel Edge found" << std::endl;
				std::cout << "-----------------" << std::endl;
			}

			// we have to find out from which decomposition our edge came from
			// and accordingly initialize a counter that describes the direction
			unsigned half = decompositionEdges.size() / 2;

			std::pair<int, int> counter;
			if ( i + 1 <= half ) {
				counter.first = 1;
				counter.second = i + 1;
			} else {
				counter.first = 2;
				counter.second = i + 1 - half;
			}

			// now we have to retrieve the new vertex in this edge direction, using
			// the adjacency oracle
			// the result is stored in secondOrigin
			bool res = polytope::adjOracle( secondOrigin, _vertex, counter );
			if ( res ) {
				break;
			}
		}
	}

	// add this normal cone to fan of polytope
	this->mFan.add( cone );

	if ( Setting::fukuda_DEBUG ) {
		std::cout << "-------------------------" << std::endl;
		std::cout << "Local Search result: " << secondOrigin << std::endl;
		std::cout << "-------------------------" << std::endl;
	}

	return secondOrigin;
}
}  // namespace hypro
