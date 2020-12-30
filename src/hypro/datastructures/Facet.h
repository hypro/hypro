/**
 * @file Facet.h
 */

#pragma once

#include "../types.h"
#include "Halfspace.h"

namespace hypro {

/**
 * @brief      Class for a facet of a polytope.
 *
 * @tparam     Number  The used number type.
 */
template <class Number>
class Facet {
  public:
	/**
	 * Typedefs
	 */
	using pointVector = std::vector<Point<Number>>;
	using neighborsSet = std::vector<std::shared_ptr<Facet<Number>>>;

	/**
	 * Members
	 */
  private:
	pointVector mVertices;
	neighborsSet mNeighbors;
	Halfspace<Number> mHalfspace;
	pointVector mOutsideSet;
	vector_t<Number> mNormal;
	Number mScalar;

	/**
	 * Constructors & Destructor
	 */
  public:
	Facet() {}

	Facet( const Facet<Number>& f )
		: mVertices( f.vertices() )
		, mNeighbors( f.neighbors() )
		, mHalfspace( f.halfspace() )
		, mOutsideSet( f.getOutsideSet() )
		, mNormal( f.getNormal() )
		, mScalar( f.getScalar() ) {}

	Facet( const std::shared_ptr<Facet<Number>>& f )
		: mVertices( f->vertices() )
		, mNeighbors( f->neighbors() )
		, mHalfspace( f->halfspace() )
		, mOutsideSet( f->getOutsideSet() )
		, mNormal( f->getNormal() )
		, mScalar( f->getScalar() ) {}

	Facet( std::vector<Point<Number>> r, const Point<Number>& p, const Point<Number>& insidePoint ) {
		r.push_back( p );
		setPoints( std::move( r ), insidePoint );
		mHalfspace = Halfspace<Number>( mNormal, mScalar );
	}

	Facet( std::vector<Point<Number>> r, const Point<Number>& p, const std::vector<Point<Number>>& outsidePoints,
		   const std::vector<Point<Number>>& currentOutside, const Point<Number>& insidePoint ) {
		r.push_back( p );
		setPoints( std::move( r ), outsidePoints, currentOutside, insidePoint );
		mHalfspace = Halfspace<Number>( mNormal, mScalar );
	}

	Facet( std::vector<Point<Number>> r, const Point<Number>& p, const std::vector<Point<Number>>& insidePoints ) {
		r.push_back( p );
		setPoints( std::move( r ), insidePoints );
		mHalfspace = Halfspace<Number>( mNormal, mScalar );
	}

	Facet( std::vector<Point<Number>> r, const Point<Number>& p, const Point<Number>& insidePoint1, const Point<Number>& insidePoint2 ) {
		r.push_back( p );
		setPoints( std::move( r ), insidePoint1, insidePoint2 );
		mHalfspace = Halfspace<Number>( mNormal, mScalar );
	}

	Facet( const std::set<vector_t<Number>>& _vertices )
		: mNeighbors() {
		if ( !_vertices.empty() ) {
			mVertices.insert( _vertices.begin(), _vertices.end() );
			unsigned dimension = _vertices.begin()->rows();
			if ( _vertices.size() < dimension ) {
				mHalfspace = Halfspace<Number>();
			} else if ( _vertices.size() > dimension ) {
				// TODO: Introduce check for degeneracy -> if not degenerate, reduce and initialize plane
				mHalfspace = Halfspace<Number>();  // TODO: temporary!
			} else {
				// proper amount of vertices for initialization of Halfspace
				std::vector<vector_t<Number>> edges;
				for ( unsigned i = 0; i < _vertices.size() - 1; ++i ) {
					for ( unsigned j = i + 1; j < _vertices.size(); ++j ) {
						edges.insert( vector_t<Number>( _vertices( j ) - _vertices( i ) ) );
					}
				}

				assert( edges.size() == dimension - 1 );
				mHalfspace = Halfspace<Number>( *( _vertices.begin() ), edges );
			}
		}
	}

	Facet& operator=( const Facet& other ) = default;

	~Facet() {}

	/**
	 * Getters and Setters
	 */

	bool empty() const { return ( mVertices.size() == 0 ); }

	pointVector& rVertices() { return mVertices; }

	const pointVector& vertices() const { return mVertices; }

	neighborsSet& rNeighbors() { return mNeighbors; }

	const neighborsSet& neighbors() const { return mNeighbors; }

	void addNeighbor( const std::shared_ptr<Facet<Number>>& facet ) {
		//std::cout << "Adding " << *facet << " to " << *this << std::endl;
		if ( !isNeighbor( facet ) ) {
			mNeighbors.push_back( facet );
			assert( isNeighbor( facet ) );
			//facet->addNeighbor( std::make_shared<Facet<Number>>( *this ) );
		}
	}

	const vector_t<Number>& getNormal() const { return mNormal; }

	Number getScalar() const { return mScalar; }

	/*
	 * removes a given facet from the neighborset if it is inside the list
	 */
	bool removeNeighbor( const std::shared_ptr<Facet<Number>>& facet ) {
		for ( unsigned i = 0; i < mNeighbors.size(); i++ ) {
			if ( *facet == *mNeighbors[i] ) {
				mNeighbors.erase( mNeighbors.begin() + i );
				return true;  // check for multiple entries?
			}
		}
		return false;
	}

	void setPoints( std::vector<Point<Number>>&& points, const Point<Number>& _insidePoint ) {
		if ( mVertices.empty() ) {
			std::move( points.begin(), points.end(), std::back_inserter( mVertices ) );

			mNormal = getNormalVector();
			mScalar = getScalarVector();

			if ( mNormal.dot( _insidePoint.rawCoordinates() ) > mScalar ) {
				mNormal *= -1;
				mScalar *= (Number)-1;
			}
			mHalfspace = Halfspace<Number>( mNormal, mScalar );
		}
	}

	void setPoints( std::vector<Point<Number>>&& points, Point<Number> insidePoint1, Point<Number> insidePoint2 ) {
		if ( mVertices.empty() ) {
			std::move( points.begin(), points.end(), std::back_inserter( mVertices ) );

			mNormal = getNormalVector();
			mScalar = getScalarVector();

			bool changed = false;
			if ( mNormal.dot( insidePoint1.rawCoordinates() ) > mScalar ) {
				mNormal *= -1;
				mScalar *= (Number)-1;
				changed = true;
			}

			if ( ( mNormal.dot( insidePoint2.rawCoordinates() ) > mScalar ) && ( !changed ) ) {
				mNormal *= -1;
				mScalar *= (Number)-1;
			}

			mHalfspace = Halfspace<Number>( mNormal, mScalar );
		}
	}

	void setPoints( std::vector<Point<Number>>&& points, const std::vector<Point<Number>>& insidePoints ) {
		if ( mVertices.empty() ) {
			std::move( points.begin(), points.end(), std::back_inserter( mVertices ) );

			mNormal = getNormalVector();
			mScalar = getScalarVector();

			//std::cout << __func__ << " : " << __LINE__ << std::endl;
			//std::cout << mNormal << std::endl;
			//std::cout << insidePoints << "  " << mScalar << std::endl;
			bool changed = false;
			for ( unsigned i = 0; i < insidePoints.size(); i++ ) {
				if ( isAbove( insidePoints.at( i ) ) ) {
					mNormal *= -1;
					mScalar = getScalarVector();
					if ( changed ) {
						std::cout << "Error: facet has points below and above it." << std::endl;
					}
					changed = true;
				}
			}
			mHalfspace = Halfspace<Number>( mNormal, mScalar );
		}
	}

	void setPoints( std::vector<Point<Number>>&& points, const std::vector<Point<Number>>& outsidePoints,
					const std::vector<Point<Number>>& currentOutside, Point<Number> _insidePoint ) {
		if ( mVertices.empty() ) {
			std::move( points.begin(), points.end(), std::back_inserter( mVertices ) );

			mNormal = getNormalVector();
			mScalar = getScalarVector();

			// std::cout << __func__ << " : " << __LINE__ << std::endl;
			// std::cout << mNormal << std::endl;
			// std::cout << _insidePoint << "  " << mScalar << std::endl;
			bool inside = false;
			bool outside = false;
			bool change = true;
			for ( unsigned i = 0; i < outsidePoints.size(); i++ ) {
				change = true;
				Number temp = Number( mNormal.dot( outsidePoints.at( i ).rawCoordinates() ) );
				if ( temp - mScalar > 0 ) {
					outside = true;
					for ( unsigned j = 0; j < currentOutside.size(); j++ ) {
						if ( outsidePoints.at( i ) == currentOutside.at( j ) ) {
							change = false;
						}
					}
					if ( change ) {
						mNormal *= -1;
						mScalar = getScalarVector();
						outside = inside;
						inside = true;
						break;
					}
				} else {
					if ( temp - mScalar < 0 ) {
						inside = true;
					}
				}
			}

			if ( !change && ( !inside || !outside ) ) {
				if ( isAbove( _insidePoint ) ) {
					mNormal *= -1;
					mScalar = getScalarVector();
				}
			}

			mHalfspace = Halfspace<Number>( mNormal, mScalar );
		}
	}

	void addPoint( Point<Number> p ) {
		mVertices.push_back( p );
		/*
		std::vector<Point<Number>> neighbors1 = p.neighbors();
		for(unsigned i = 0; i<neighbors1.size(); i++) {
			std::vector<Point<Number>> neighbors2 = neighbors1.at(i).neighbors();
			for(unsigned j = 0; j<neighbors2.size(); j++) {
				if(neighbors2.at(j) != p){
					neighbors1.at(i).removeNeighbor(neighbors2.at(j));
					//neighbors2.at(j).removeNeighbor(neighbors1.at(i));
				}
			}
		}
		*/
	}

	vector_t<Number> getNormalVector() const {
		std::vector<vector_t<Number>> vectors;
		// std::cout << mVertices[0].rawCoordinates() << std::endl;
		// vectors.push_back(vector_t<Number>::Zero(mVertices[0].rawCoordinates().rows()));
		vectors.push_back( mVertices[0].rawCoordinates() );
		for ( unsigned i = 1; i < mVertices.size(); i++ ) {
			vectors.push_back( mVertices[i].rawCoordinates() - vectors[0] );
		}

		matrix_t<Number> matrix = matrix_t<Number>::Zero( vectors.size(), mVertices[0].rawCoordinates().size() );
		for ( unsigned i = 1; i < vectors.size(); i++ ) {
			for ( unsigned j = 0; j < vectors[i].size(); j++ ) {
				matrix( i, j ) = vectors[i]( j );
			}
		}

		//std::cout << matrix << std::endl;

		// matrix(0,vectors[0].size()-1) = 1;
		for ( unsigned j = 0; j < vectors[0].size(); j++ ) {
			matrix( 0, j ) = 1;

			if ( matrix.fullPivLu().rank() == vectors[0].size() ) {
				break;
			} else {
				matrix( 0, j ) = 0;
			}
		}

		vector_t<Number> b = vector_t<Number>::Zero( vectors.size() );
		b( 0 ) = 1;

		//std::cout << __func__ << ": A " << std::endl << matrix << std::endl << ",b " << std::endl << b << std::endl;

		matrix_t<Number> copyMatrix = matrix_t<Number>( matrix.rows(), matrix.cols() + 1 );
		for ( unsigned colIt = 0; colIt < copyMatrix.cols() - 1; ++colIt ) {
			copyMatrix.col( colIt ) = matrix.col( colIt );
		}
		copyMatrix.col( copyMatrix.cols() - 1 ) = b;
		vector_t<Number> result = matrix.fullPivLu().solve( b );
		return result;
	}

	Number getScalarVector() const { return Number( mNormal.dot( mVertices[0].rawCoordinates() ) ); }

	Halfspace<Number> halfspace() const { return mHalfspace; }

	/*
	 * Iterators
	 */

	typename pointVector::iterator begin() { return mVertices.begin(); }

	typename pointVector::const_iterator begin() const { return mVertices.begin(); }

	typename pointVector::iterator end() { return mVertices.end(); }

	typename pointVector::const_iterator end() const { return mVertices.end(); }

	/*
	 * Functions
	 */

	/*
	 * Checks if a point is above, i.e. a positive distance to the Halfspace.
	 * @return true, if the point is above.vertices()
	 */
	bool isBelow( const Point<Number>& p ) const {
		// return (mHalfspace.signedDistance(p) > 0);
		Number temp = Number( mNormal.dot( p.rawCoordinates() ) );
		// std::cout << __func__ << " : " << __LINE__ << std::endl;
		/*	if(carl::AlmostEqual2sComplement(temp, mScalar, 4)){
				return false;
			} */
		// std::cout << __func__ << " : " << __LINE__ << " value " <<temp-mScalar << std::endl;

		return ( temp - mScalar <= 0 );
	}

	bool isAbove( const Point<Number>& p ) const {
		Number temp = Number( mNormal.dot( p.rawCoordinates() ) );
		return ( temp - mScalar > 0 );
	}

	Number getDist( const Point<Number>& p ) const {
		Number temp = Number( mNormal.dot( p.rawCoordinates() ) );
		return Number( temp - mScalar );
	}

	void addPointToOutsideSet( Point<Number> point ) {
		mOutsideSet.push_back( point );	 // check double entries?
	}

	std::vector<Point<Number>> getOutsideSet() const {
		// std::cout << __func__ << " : " << __LINE__ << mOutsideSet << std::endl;
		return mOutsideSet;
	}

	void removePointFromOutsideSet( const Point<Number>& _point ) {
		for ( auto pointIt = mOutsideSet.begin(); pointIt != mOutsideSet.end(); ) {
			if ( *pointIt == _point ) {
				pointIt = mOutsideSet.erase( pointIt );
			} else {
				++pointIt;
			}
		}
	}

	/*
	 * Determines the point furthest away from the Halfspace. The points to be considered are saved in hashlist.
	 * @return The Point which has the highest distance to the Halfspace.
	 */
	Point<Number> furthest_Point() const {
		if ( mOutsideSet.empty() ) {
			return Point<Number>();
		} else {
			Point<Number> result = mOutsideSet[0];
			Number max = Number( mNormal.dot( mOutsideSet[0].rawCoordinates() ) );	// mHalfspace.signedDistance(result);
			for ( unsigned i = 1; i < mOutsideSet.size(); i++ ) {
				Number temp = Number( mNormal.dot( mOutsideSet[i].rawCoordinates() ) );
				if ( temp > max ) {
					max = temp;
					result = mOutsideSet[i];
				}
			}
			return result;
		}
	}

	bool isNeighbor( const std::shared_ptr<Facet<Number>>& facet ) const {
		for ( unsigned i = 0; i < mNeighbors.size(); i++ ) {
			// std::cout << "Compare " << *mNeighbors[i] << " and " << *facet << ": " << (*mNeighbors[i] == *facet) <<
			// std::endl;
			if ( *mNeighbors[i] == *facet ) {
				return true;
			}
		}
		return false;
	}

	friend bool operator==( const Facet<Number>& _f1, const Facet<Number>& _f2 ) {
		// std::cout << "compare " << _f1 << "and" << _f2 << ":" ;
		for ( unsigned i = 0; i < _f1.vertices().size(); i++ ) {
			bool found = false;
			for ( unsigned j = 0; j < _f2.vertices().size(); j++ ) {
				// std::cout << "\t Point compare: " << _f1.vertices().at(i) << " and " << _f2.vertices().at(j) << ": "
				// << (_f1.vertices().at(i) == _f2.vertices().at(j)) << std::endl;
				if ( _f1.vertices().at( i ) == _f2.vertices().at( j ) ) {
					found = true;
				}
			}
			if ( !found ) {
				//	std::cout << "0"<< std::endl;
				return false;
			}
		}
		// std::cout << "1" << std::endl;
		return true;
		// return (_f1.vertices() == _f2.vertices());
	}

	friend bool operator!=( const Facet<Number>& _f1, const Facet<Number>& _f2 ) { return !( _f1 == _f2 ); }
};

template <typename Number>
std::ostream& operator<<( std::ostream& _ostr, const Facet<Number>& _f ) {
	_ostr << "Facet : \n";
	for ( const auto& vertex : _f.vertices() ) {
		_ostr << vertex << "\n ";
	}
	return _ostr;
}
}  // namespace hypro
