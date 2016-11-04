/**
 * @file    Grid.tpp
 * @author 	Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @author  Benedikt Seidl
 *
 * @since   2014-04-14
 * @version 2015-08-26
 */

#include "Grid.h"

namespace hypro {

/*
*	Constructors
*/

template <typename Number>
Grid<Number>::Grid() {
}

template <typename Number>
Grid<Number>::Grid( const vSet<Number> &vertices )
	: mVertices() {
	induceGrid( vertices );
}

template <typename Number>
Grid<Number>::Grid( const std::vector<Vertex<Number>> &_vertices )
	: mVertices() {
	induceGrid( vSet<Number>( _vertices.begin(), _vertices.end() ) );
}

template <typename Number>
Grid<Number>::Grid( const Grid<Number> &copy )
	: mVertices( copy.mVertices ), mGridMap( copy.mGridMap ), mInducedGridPoints( copy.mInducedGridPoints ) {
}

/*
*	Getter & Setter
*/

template <typename Number>
unsigned Grid<Number>::size() const {
	return mVertices.size();
}

template <typename Number>
unsigned Grid<Number>::dimension() const {
	return mInducedGridPoints.size();
}

template <typename Number>
std::vector<carl::Variable> Grid<Number>::variables() const {
	std::vector<carl::Variable> res;
	if ( mGridMap.empty() ) return res;

	res = mGridMap.begin()->first.variables();
	return ( res );
}

template <typename Number>
std::vector<Vertex<Number>> Grid<Number>::vertices() const {
	std::vector<Vertex<Number>> res;
	for ( const auto &point : mVertices ) {
		// std::cout << "Calculated vertex " << calculateOriginal(point.point()) <<
		// " from " << point.point() <<
		// std::endl;
		if ( point.point() != Point<unsigned>::Zero( point.point().dimension() ) ) {  // do not add origin
			res.emplace_back( calculateOriginal( point.point() ), point.color() );
		}
	}
	return ( res );
}

template <typename Number>
std::vector<Number> Grid<Number>::inducedDimensionAt( unsigned dimension ) const {
	assert( dimension < mInducedGridPoints.size() );
	return mInducedGridPoints.at( dimension );
}

template <typename Number>
bool Grid<Number>::empty() const {
	return mGridMap.empty();
}

template <typename Number>
bool Grid<Number>::colorAt( const Point<Number> &point ) const {
	Point<unsigned> inducedPoint = calculateInduced( point ).first;
	// the point is not a vertex (vertices are inserted at the beginning) and not
	// yet calculated.
	if ( mGridMap.find( inducedPoint ) != mGridMap.end() ) {
		// std::cout << "known: " << point << "(" << inducedPoint << ") " <<
		// mGridMap.at(inducedPoint) << std::endl;
		return mGridMap.at( inducedPoint );
	}

	return colorAtInduced( inducedPoint );
}

template <typename Number>
bool Grid<Number>::colorAtInduced( const Point<unsigned> &inducedPoint ) const {
	// std::cout << __func__ << " " << inducedPoint << std::endl;
	// the point is not a vertex (vertices are inserted at the beginning) and not
	// yet calculated.
	if ( mGridMap.find( inducedPoint ) != mGridMap.end() ) {
		// std::cout << "known: " << mGridMap.at(inducedPoint) << std::endl;
		return mGridMap.at( inducedPoint );
	}

	// if one coordinate is zero just go along the axes towards origin and count
	// vertices (origin is always white)
	bool containsZero = false;
	std::vector<unsigned> nonZero;
	for ( unsigned d = 0; d < inducedPoint.dimension(); ++d ) {
		if ( inducedPoint.at( d ) == 0 ) {
			// std::cout << "Zero at dimension " << d << std::endl;
			containsZero = true;
		} else {
			nonZero.push_back( d );
		}
	}
	if ( containsZero ) {  // move along axes to origin, collect predecessors
		Point<unsigned> predecessor( iPredecessorInduced( inducedPoint, nonZero.back() ) );
		std::vector<Point<unsigned>> predecessors;
		while ( !nonZero.empty() ) {
			unsigned dir = nonZero.back();
			// std::cout << "Chosen predecessor direction: " << dir << std::endl;
			while ( mGridMap.find( predecessor ) == mGridMap.end() &&
					( iPredecessorInduced( predecessor, dir ) != predecessor ) ) {
				// std::cout << "Added predecessor " << predecessor << std::endl;
				predecessors.push_back( predecessor );
				predecessor = iPredecessorInduced( predecessor, dir );
			}
			nonZero.pop_back();
		}
		// std::cout << "Found vertex: " << predecessor << ", set color to " <<
		// mGridMap.at(predecessor) <<  std::endl;
		bool color = mGridMap.at( predecessor );
		mGridMap[inducedPoint] = color;
		while ( !predecessors.empty() ) {
			mGridMap[predecessors.back()] = color;
			predecessors.pop_back();
		}
		// std::cout << "Color " << inducedPoint << ": " << color << std::endl;
		return color;
	}

	/* calculate color recursively:
	 * - go through all directions j: There exists j such that for all
	 * j-neighbors(x) (except x itself) it holds:
	 * 		color(j-pred(jneigh)) == color(j-neigh)
	 * 		-> color(x) = color(j-pred(j-neigh))
	 */

	unsigned dim = dimension();
	bool setColor = true;  // remarks if we found the correct direction
	bool color = false;
	for ( unsigned j = 0; j < dim; ++j ) {
		// std::cout << "Evaluate "<< inducedPoint <<" in direction " << j <<
		// std::endl;
		setColor = true;
		std::vector<Point<unsigned>> jneighs = iNeighborhoodInduced( inducedPoint, j );
		// for(const auto& p : jneighs) {
		//	std::cout << j << "-Neighbor: " << p << std::endl;
		//}
		for ( const auto &x : jneighs ) {
			if ( x != inducedPoint ) {
				// std::cout << "Get color at " << x << std::endl;
				color = colorAtInduced( x );

				if ( color == colorAtInduced( iPredecessorInduced( x, j ) ) ) {
					color = colorAtInduced( iPredecessorInduced( inducedPoint, j ) );
					break;
				} else {
					setColor = false;
					break;
				}
			}
		}
		if ( setColor ) {
			mGridMap[inducedPoint] = color;
			break;
		}
	}
	// std::cout << "Color " << inducedPoint << ": " << color << std::endl;
	return color;
}

template <typename Number>
std::vector<Point<Number>> Grid<Number>::allBlack() const {
	colorAll();
	std::vector<Point<Number>> res;
	for ( const auto &pPair : mGridMap ) {
		if ( pPair.second ) res.emplace_back( calculateOriginal( pPair.first ) );
	}
	return ( res );
}

template <typename Number>
void Grid<Number>::colorAll() const {
	std::vector<std::vector<unsigned>> points;
	for ( const auto &vecPair : mInducedGridPoints ) {
		std::vector<unsigned> positions;
		for ( unsigned i = 0; i < vecPair.second.size(); ++i ) positions.emplace_back( i );
		points.emplace_back( positions );
	}

	pointIt<unsigned> iter( points );
	while ( !iter.end ) {
		colorAtInduced( ++iter );
	}
}

template <typename Number>
std::vector<Point<unsigned>> Grid<Number>::iNeighborhoodInduced( const Point<unsigned> &_inducedPoint,
																 unsigned _dimension ) const {
	// std::cout << __func__ << " " << _inducedPoint << " " << _dimension <<
	// std::endl;
	assert( _dimension < mInducedGridPoints.size() );
	std::vector<Point<unsigned>> result;

	unsigned d = this->dimension();
	Point<unsigned> directPredecessor( _inducedPoint );
	for ( unsigned dim = 0; dim < d; ++dim ) {
		if ( _inducedPoint.at( dim ) > 0 ) directPredecessor[dim] = ( _inducedPoint.at( dim ) ) - 1;
	}

	std::vector<std::vector<unsigned>> possibleCoords;
	for ( unsigned j = 0; j < d; ++j ) {
		if ( _dimension != j ) {
			std::vector<unsigned> tmp( {directPredecessor.at( j ), _inducedPoint.at( j )} );
			possibleCoords.emplace_back( std::move( tmp ) );
		} else {
			std::vector<unsigned> tmp( {_inducedPoint.at( j )} );
			possibleCoords.emplace_back( tmp );
		}
	}
	pointIt<unsigned> pIt( possibleCoords );

	while ( !pIt.end ) {
		result.emplace_back( ++pIt  );
	}
	return ( result );
}

template <typename Number>
Point<unsigned> Grid<Number>::iPredecessorInduced( const Point<unsigned> &_point, unsigned _dimension ) const {
	Point<unsigned> res( _point );
	res[_dimension] = res[_dimension] > 0 ? res[_dimension] - 1 : 0;
	return ( res );
}

template <typename Number>
Point<Number> Grid<Number>::iPredecessor( const Point<Number> &_point, unsigned _dimension ) const {
	return calculateOriginal( iPredecessorInduced( calculateInduced( _point ).first, _dimension ) );
}

template <typename Number>
Point<unsigned> Grid<Number>::iSuccessorInduced( const Point<unsigned> &_point, unsigned _dimension ) const {
	Point<unsigned> res( _point );
	res[_dimension] = res[_dimension] < mInducedGridPoints[_dimension].size() ? res[_dimension] + 1 : res[_dimension];
	return ( res );
}

template <typename Number>
Point<Number> Grid<Number>::iSuccessor( const Point<Number> &_point, unsigned _dimension ) const {
	return calculateOriginal( iSuccessorInduced( calculateInduced( _point ).first, _dimension ) );
}

template <typename Number>
Point<unsigned> Grid<Number>::directPredecessorInduced( const Point<unsigned> &_point ) const {
	Point<unsigned> directPredecessor( _point );
	for ( unsigned dim = 0; dim < this->dimension(); ++dim ) {
		directPredecessor[dim] = _point.at( dim ) > 0 ? _point.at( dim ) - 1 : 0;
	}
	return ( directPredecessor );
}

template <typename Number>
Point<Number> Grid<Number>::directPredecessor( const Point<Number> &_point ) const {
	return calculateOriginal( directPredecessorInduced( calculateInduced( _point ).first ) );
}

template <typename Number>
Point<unsigned> Grid<Number>::directSuccessorInduced( const Point<unsigned> &_point ) const {
	Point<unsigned> directSuccessor( _point );
	for ( unsigned dim = 0; dim < this->dimension(); ++dim ) {
		directSuccessor[dim] =
			  _point.at( dim ) < mInducedGridPoints[dim].size() ? _point.at( dim ) + 1 : _point.at( dim );
	}
	return ( directSuccessor );
}

template <typename Number>
Point<Number> Grid<Number>::directSuccessor( const Point<Number> &_point ) const {
	return calculateOriginal( directSuccessorInduced( calculateInduced( _point ).first ) );
}

template <typename Number>
std::vector<Point<unsigned>> Grid<Number>::iSliceInduced( unsigned i ) const {
	std::vector<Point<unsigned>> result;

	std::vector<std::vector<unsigned>> tmp;
	for ( unsigned j = 0; j < mInducedGridPoints.size(); ++j ) {
		if ( i != j ) {
			tmp.emplace_back( std::vector<unsigned>( {i} ) );
		} else {
			std::vector<unsigned> positions;
			positions.resize( mInducedGridPoints.at( j ).size() );
			for ( unsigned k = 0; k < mInducedGridPoints.at( j ).size(); ++k ) positions.emplace_back( k );

			tmp.emplace_back( std::move( positions ) );
		}
	}
	pointIt<unsigned> pIt( tmp );

	while ( !pIt.end ) {
		result.emplace_back( ++pIt );
	}
	return ( result );
}

template <typename Number>
std::vector<Point<Number>> Grid<Number>::iSlice( unsigned i, Number pos ) const {
	unsigned inducedPos = 0;
	while ( mInducedGridPoints.at( i )[inducedPos] < pos ) ++inducedPos;

	if ( inducedPos > 0 ) --inducedPos;

	std::vector<Point<unsigned>> tmp = iSliceInduced( i );
	std::vector<Point<Number>> res;
	for ( const auto &p : tmp ) res.emplace_back( calculateOriginal( p ) );

	return ( res );
}

template <typename Number>
std::vector<Point<Number>> Grid<Number>::iNeighborhood( const Point<Number> &_point, unsigned _dimension ) const {
	std::vector<Point<unsigned>> neighborhood = iNeighborhoodInduced( calculateInduced( _point ).first, _dimension );
	std::vector<Point<Number>> res;
	for ( const auto &n : neighborhood ) res.emplace_back( calculateOriginal( n ) );

	return ( res );
}

template <typename Number>
std::vector<Point<unsigned>> Grid<Number>::neighborhoodInduced( const Point<unsigned> &_inducedPoint ) const {
	std::vector<Point<unsigned>> result;
	unsigned d = this->dimension();

	// calculate direct predecessor point in all dimensions
	Point<unsigned> directPredecessor( _inducedPoint );
	for ( unsigned dim = 0; dim < d; ++dim ) {
		directPredecessor[dim] = _inducedPoint.at( dim ) > 0 ? _inducedPoint.at( dim ) - 1 : 0;
	}

	// get all 2^d i-neighbors by combination of the point and its direct
	// predecessor
	for ( unsigned i = 0; i < std::pow( 2, d ); ++i ) {
		std::bitset<MAX_DIMENSION_LIMIT> map( i );
		unsigned pos = 0;
		Point<unsigned> neighbor( directPredecessor );
		while ( pos < d ) {
			if ( map.test( pos ) ) neighbor[pos] = _inducedPoint.at( pos );
			++pos;
		}
		result.emplace_back( std::move( neighbor ) );
	}

	return ( result );
}

template <typename Number>
std::vector<Point<Number>> Grid<Number>::neighborhood( const Point<Number> &_point ) const {
	std::vector<Point<unsigned>> tmp = neighborhoodInduced( calculateInduced( _point ).first );
	std::vector<Point<Number>> res;
	for ( const auto &p : tmp ) res.emplace_back( calculateOriginal( p ) );

	return ( res );
}

template <typename Number>
bool Grid<Number>::isVertex( const Point<Number> &_point ) const {
	// if the point is not on the grid, it can never be a vertex
	if ( !calculateInduced( _point ).second ) return false;

	for ( unsigned dim = 0; dim < this->dimension(); ++dim ) {
		if ( !isOnIFacet( _point, dim ) ) return false;
	}

	return true;
}

template <typename Number>
bool Grid<Number>::isOnIFacet( const Point<Number> &_point, unsigned i ) const {
	// either the point is a vertex or there is a color change in its
	// i-neighborhood
	// if the point is not part of the induced grid, it cannot be on a facet.
	// Otherwise all points larger than the
	// largest coordinate are on a facet.
	if ( isOutside( _point ) ) return false;

	unsigned pos = 0;
	while ( pos < mInducedGridPoints.at( i ).size() && mInducedGridPoints.at( i )[pos] < _point.at( i ) ) ++pos;
	if ( mInducedGridPoints.at( i )[pos] != _point.at( i ) ) {
		// std::cout << "Point is not on grid coordinate for dim " << i <<
		// std::endl;
		return false;
	}

	Point<unsigned> inducedPoint = calculateInduced( _point ).first;

	// std::cout << "Is on " << i << "-facet " << _point << " (" << inducedPoint
	// << ") : ";

	// special case: origin is never on a facet
	if ( inducedPoint == Point<unsigned>::Zero( inducedPoint.dimension() ) ) {
		// std::cout << "false" << std::endl;
		return false;
	}

	// special case: if the points coordinate in dimension i is zero and it is
	// black, it is always on an i-facet.
	// also if its induced version is a real vertex, it is on an i-facet.
	if ( inducedPoint.at( i ) == 0 &&
		 ( colorAtInduced( inducedPoint ) || ( mVertices.find( inducedPoint ) != mVertices.end() ) ) ) {
		// std::cout << "true" << std::endl;
		return true;
	}

	// check color change
	std::vector<Point<unsigned>> iNeighborhood = iNeighborhoodInduced( inducedPoint, i );
	for ( const auto &x : iNeighborhood ) {
		if ( colorAtInduced( x ) != colorAtInduced( iPredecessorInduced( x, i ) ) ) {
			// std::cout << "true" << std::endl;
			return true;
		}
	}
	// std::cout << "false" << std::endl;
	return false;
}

template <typename Number>
bool Grid<Number>::isOnFacet( const Point<Number> &_point ) const {
	if ( isOutside( _point ) ) return false;

	for ( unsigned d = 0; d < dimension(); ++d ) {
		if ( isOnIFacet( _point, d ) ) return true;
	}
	return false;
}

template <typename Number>
bool Grid<Number>::isOutside( const Point<Number> &_point ) const {
	for ( unsigned d = 0; d < mInducedGridPoints.size(); ++d ) {
		if ( _point.at( d ) > mInducedGridPoints.at( d ).back() ) return true;
	}
	return false;
}

template <typename Number>
void Grid<Number>::insert( const Point<Number> &point, bool color ) {
	mGridMap.insert( std::make_pair( calculateInduced( point ).first, color ) );
	mVertices.emplace( calculateInduced( point ).first, color );
}

template <typename Number>
void Grid<Number>::insertInduced( const Point<unsigned> &inducedPoint, bool color ) {
	mGridMap[inducedPoint] = color;
	mVertices.emplace( inducedPoint, color );
}

template <typename Number>
void Grid<Number>::addCoordinate( Number value, unsigned dimension ) {
	if ( mInducedGridPoints.find( dimension ) == mInducedGridPoints.end() ) {
		mInducedGridPoints[dimension] = std::vector<Number>();
		mInducedGridPoints[dimension].push_back( Number( 0 ) );
	}
	assert(mInducedGridPoints.find( dimension ) != mInducedGridPoints.end());
	assert(!mInducedGridPoints[dimension].empty());

	typename std::vector<Number>::iterator pos = mInducedGridPoints[dimension].begin();

	while ( pos != mInducedGridPoints[dimension].end() && *pos < value  ) {
		++pos;
	}

	if ( ( pos == mInducedGridPoints[dimension].end() ) || ( *pos > value ) )  // if equal, do nothing
		mInducedGridPoints[dimension].insert( pos, value );
}

template <typename Number>
Grid<Number> Grid<Number>::combine( const Grid<Number> &a, const Grid<Number> &b ) {
	assert( a.dimension() == b.dimension() );
	Grid<Number> res;
	for ( unsigned d = 0; d < a.dimension(); ++d ) {
		std::vector<Number> aValues = a.inducedDimensionAt( d );
		std::vector<Number> bValues = b.inducedDimensionAt( d );

		while ( !aValues.empty() ) {
			res.addCoordinate( aValues.back(), d );
			aValues.pop_back();
		}
		while ( !bValues.empty() ) {
			res.addCoordinate( bValues.back(), d );
			bValues.pop_back();
		}
	}

	// insert origin
	res.insertInduced( Point<unsigned>::Zero( a.dimension() ), false );

	return ( res );
}

template <typename Number>
void Grid<Number>::clear() {
	mGridMap.clear();
	mVertices.clear();
	mInducedGridPoints.clear();
}

template <typename Number>
typename Grid<Number>::gridMap::const_iterator Grid<Number>::find( const Point<Number> &point ) const {
	return mGridMap.find( calculateInduced( point ).first );
}

template <typename Number>
typename Grid<Number>::gridMap::const_iterator Grid<Number>::findInduced( const Point<unsigned> &inducedPoint ) const {
	return mGridMap.find( inducedPoint );
}

template <typename Number>
typename Grid<Number>::gridMap::const_iterator Grid<Number>::end() const {
	return mGridMap.end();
}

template <typename Number>
void Grid<Number>::induceGrid( const vSet<Number> &vertices ) {
	clear();

	std::vector<Number> v;
	v.resize( vertices.size() + 1 );  // we add the origin
	for ( unsigned i = 0; i != vertices.begin()->dimension(); ++i ) {
		// insert origin as vertex
		v = std::vector<Number>( {Number( 0 )} );

		// Projection of all points to the axes.
		for ( auto &vertex : vertices ) {
			v.push_back( vertex.coordinate( i ) );
		}

		// Sort every dimension, erase duplicate entries.
		std::sort( v.begin(), v.end() );
		auto itr = std::unique( v.begin(), v.end() );
		v.resize( itr - v.begin() );

		mInducedGridPoints[i] = v;
	}

	// set color of origin manually (always white)
	// this->insertInduced(Point<unsigned>::Zero(mInducedGridPoints.size()),
	// false);
	mGridMap.insert( std::make_pair( Point<unsigned>::Zero( mInducedGridPoints.size() ),
									 false ) );  // insert only in gridmap to not affect the size

	// set up datastructures for colors of vertices and vertices
	for ( auto it : vertices ) {
		this->insert( it.rPoint(), it.color() );
		mVertices.insert( Vertex<unsigned>( calculateInduced( it.point() ).first, it.color() ) );
		// std::cout << "Added induced Vertex " <<
		// Vertex<unsigned>(calculateInduced(it.point()),it.color()) <<
		// std::endl;
	}
}

template <typename Number>
std::pair<Point<unsigned>, bool> Grid<Number>::calculateInduced( const Point<Number> &point ) const {
	vector_t<unsigned> coordinates( mInducedGridPoints.size() );
	bool precise = true;
	// std::cout << *this << std::endl;
	for ( unsigned dim = 0; dim < mInducedGridPoints.size(); ++dim ) {
		std::vector<Number> inducedGridPoints = mInducedGridPoints.at( dim );

		// get the position of the first element greater than the coordinate + 1
		unsigned pos = 0;
		while ( pos < inducedGridPoints.size() - 1 && inducedGridPoints[pos] < point.at( dim ) ) ++pos;

		// insert the index of the element one before the element found above
		if ( inducedGridPoints[pos] <= point.at( dim ) ) {  // here the points coordinate is either equal or we reached
															// the last element and it is larger
			coordinates[dim] = pos;
		} else {
			// std::cout << "dim: " <<  dim << ", " << inducedGridPoints[pos] << " > "
			// <<  point.at(dim) << std::endl;
			coordinates[dim] = pos - 1;
			precise = false;
		}
	}
	return std::make_pair( Point<unsigned>( coordinates ), precise );  // return induced point
}

template <typename Number>
Point<Number> Grid<Number>::calculateOriginal( const Point<unsigned> &inducedPoint ) const {
	vector_t<Number> coordinates( mInducedGridPoints.size() );
	for ( auto inducedGridPointsIt : mInducedGridPoints ) {
		unsigned fixed = inducedGridPointsIt.first;
		std::vector<Number> inducedGridPoints = inducedGridPointsIt.second;

		// get the value of the element at the specified position
		int induced = inducedPoint.at( fixed );

		coordinates[fixed] = inducedGridPoints.at( induced );
	}

	return Point<Number>( coordinates );  // return original point
}

template <typename Number>
vSet<unsigned> Grid<Number>::translateToInduced( const vSet<Number> &vertices ) const {
	vSet<unsigned> induced;
	for ( auto it : vertices ) {
		Vertex<unsigned> v = calculateInduced( it.point() ).first;
		v.setColor( it.color() );
		induced.insert( v );
	}
	return induced;
}

template <typename Number>
vSet<Number> Grid<Number>::translateToOriginal( const vSet<unsigned> &inducedVertices ) const {
	vSet<Number> original;
	for ( auto it : inducedVertices ) {
		Vertex<Number> v = calculateOriginal( it.point() );
		v.setColor( it.color() );
		original.insert( v );
	}
	return original;
}
}
