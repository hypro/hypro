#include "HPolytope.h"

namespace hypro {
template <typename Number, typename Converter, class Setting>
HPolytopeT<Number, Converter, Setting>::HPolytopeT()
	: mHPlanes()
	, mDimension( 0 )
	, mNonRedundant( true ) {
	if ( Setting::OPTIMIZER_CACHING ) {
		setOptimizer();
	}
}

//copy constructor
template <typename Number, typename Converter, class Setting>
HPolytopeT<Number, Converter, Setting>::HPolytopeT( const HPolytopeT& orig )
	: GeometricObjectBase( orig )
	, mHPlanes( orig.constraints() )
	, mDimension( orig.dimension() )
	, mNonRedundant( orig.isNonRedundant() ) {
	if ( Setting::OPTIMIZER_CACHING && orig.getOptimizer().has_value() ) {
		setOptimizer( orig.matrix(), orig.vector() );
	}
}

template <typename Number, typename Converter, class Setting>
HPolytopeT<Number, Converter, Setting>::HPolytopeT( const HalfspaceVector& planes )
	: mHPlanes()
	, mDimension( 0 )
	, mNonRedundant( false ) {
	if ( !planes.empty() ) {
		mDimension = planes.begin()->dimension();
		for ( const auto& plane : planes ) {
			mHPlanes.push_back( plane );
		}
#ifndef NDEBUG
		bool empty = this->empty();
#endif
		reduceNumberRepresentation();
		assert( empty == this->empty() );
		if ( Setting::OPTIMIZER_CACHING ) {
			setOptimizer( this->matrix(), this->vector() );
		}
	} else {
		if ( Setting::OPTIMIZER_CACHING ) {
			setOptimizer();
		}
	}
}

template <typename Number, typename Converter, class Setting>
HPolytopeT<Number, Converter, Setting>::HPolytopeT( const matrix_t<Number>& A, const vector_t<Number>& b )
	: mHPlanes()
	, mDimension( A.cols() )
	, mNonRedundant( false ) {
	TRACE( "hypro.representations.HPolytope", "construct from Ax <= b," << std::endl
																		<< "A: " << A << "b: " << b );
	assert( A.rows() == b.rows() );
	for ( unsigned i = 0; i < A.rows(); ++i ) {
		mHPlanes.emplace_back( A.row( i ), b( i ) );
	}
#ifndef NDEBUG
	bool empty = this->empty();
#endif
	reduceNumberRepresentation();
	assert( empty == this->empty() );
	if ( Setting::OPTIMIZER_CACHING ) {
		setOptimizer( A, b );
	}
}

template <typename Number, typename Converter, class Setting>
HPolytopeT<Number, Converter, Setting>::HPolytopeT( const matrix_t<Number>& A )
	: mHPlanes()
	, mDimension( A.cols() )
	, mNonRedundant( false ) {
	for ( unsigned i = 0; i < A.rows(); ++i ) {
		mHPlanes.push_back( Halfspace<Number>( A.row( i ), Number( 0 ) ) );
	}
	if ( Setting::OPTIMIZER_CACHING ) {
		setOptimizer( A );
	}
}

template <typename Number, typename Converter, class Setting>
HPolytopeT<Number, Converter, Setting>::HPolytopeT( const Point<Number>& point )
	: mDimension( point.dimension() ) {
	assert( mDimension > 0 );
	for ( unsigned d = 0; d < mDimension; ++d ) {
		vector_t<Number> normal = vector_t<Number>::Zero( mDimension );
		normal( d ) = 1;
		mHPlanes.insert( mHPlanes.end(), Halfspace<Number>( normal, point.at( d ) ) );
		mHPlanes.insert( mHPlanes.end(), Halfspace<Number>( -normal, -( point.at( d ) ) ) );
	}
	if ( Setting::OPTIMIZER_CACHING ) {
		setOptimizer( this->matrix(), this->vector() );
	}
}

template <typename Number, typename Converter, class Setting>
HPolytopeT<Number, Converter, Setting>::HPolytopeT( const std::vector<Point<Number>>& points )
	: mHPlanes()
	, mDimension( 0 )
	, mNonRedundant( true ) {
	mEmptyState = points.empty() ? SETSTATE::EMPTY : SETSTATE::NONEMPTY;
	//START_BENCHMARK_OPERATION( "HPoly_vertices_constructor" )
	// skip
	if ( points.empty() ) {
		//EVALUATE_BENCHMARK_RESULT( "HPoly_vertices_constructor" )
		return;
	}

	// special case: 1 point - we can directly use box constraints.
	if ( points.size() == 1 ) {
		*this = { *points.begin() };
		return;
	}

	if constexpr ( is_exact<Number> ) {
		mDimension = points.front().dimension();

		//Get raw data for quickhull
		std::vector<vector_t<Number>> inputPoints;

		for ( auto const& point : points ) {
			inputPoints.push_back( point.rawCoordinates() );
		}

		//Initialize and run quickhull
		Quickhull<Number> qh{ inputPoints, mDimension };
		qh.compute();

		//Convert resulting facets into halfspaces
		for ( auto const& facet : qh.getFacets() ) {
			mHPlanes.emplace_back( facet.mNormal, facet.mOffset );
		}

		//Assert containment
		assert( std::all_of( mHPlanes.begin(), mHPlanes.end(), [&]( auto const& hplane ) {
			return std::all_of( points.begin(), points.end(), [&]( auto const& point ) {
				return hplane.contains( point );
			} );
		} ) );
	} else {
		auto pointsCopy = points;

		// remove duplicates
		/*
		unordered_set<Point<Number>> s;
		for ( int i : points )
			s.insert( i );
		points.assign( s.begin(), s.end() );
		*/

		for ( auto pointsIt = pointsCopy.begin(); pointsIt != pointsCopy.end(); ++pointsIt ) {
			for ( auto compIt = std::next( pointsIt ); compIt != pointsCopy.end(); ) {
				if ( *pointsIt == *compIt ) {
					compIt = pointsCopy.erase( compIt );
				} else {
					++compIt;
				}
			}
		}

		if ( pointsCopy.size() == 1 ) {
			*this = { *pointsCopy.begin() };
			return;
		}

#ifdef HYPRO_LOGGING
		TRACE( "hypro.representations.HPolytope", "Construct from vertices (duplicates removed): " );
		for ( auto vertex : pointsCopy ) {
			Point<double> tmp = convert<Number, double>( vertex );
			TRACE( "hypro.representations.HPolytope", tmp );
		}
#endif

		if ( !pointsCopy.empty() ) {
			mDimension = pointsCopy.begin()->dimension();
			// check affine independence - verify object dimension.
			std::vector<vector_t<Number>> coordinates;
			for ( const auto& vertex : pointsCopy ) {
				coordinates.push_back( vertex.rawCoordinates() );
			}
			int effectiveDim = effectiveDimension( coordinates );
			assert( effectiveDim >= 0 );

			//if ( pointsCopy.size() <= mDimension ) {
			if ( unsigned( effectiveDim ) < mDimension ) {
				TRACE( "hypro.representations.HPolytope", "Points size: " << pointsCopy.size() );
				TRACE( "hypro.representations.HPolytope", "Affine dimension: " << effectiveDim );
				// get common plane
				std::vector<vector_t<Number>> vectorsInPlane;
				//std::cout << "first point: " << *pointsCopy.begin() << std::endl;
				for ( unsigned i = 1; i < pointsCopy.size(); ++i ) {
					vectorsInPlane.emplace_back( pointsCopy[i].rawCoordinates() - pointsCopy[0].rawCoordinates() );
				}
				vector_t<Number> planeNormal = Halfspace<Number>::computePlaneNormal( vectorsInPlane );
				Number planeOffset = Halfspace<Number>::computePlaneOffset( planeNormal, pointsCopy[0] );

				TRACE( "hypro.representations.HPolytope", "Shared plane normal: " << planeNormal << ", plane offset: " << planeOffset );

				// project on lower dimension.
				// Use dimensions with largest coordinate range for improved stability.
				// So to say: Drop dimensions with minimal coordinate range
				Point<Number> maxP = pointsCopy[0];
				Point<Number> minP = pointsCopy[0];
				for ( const auto& point : pointsCopy ) {
					maxP = Point<Number>::coeffWiseMax( maxP, point );
					minP = Point<Number>::coeffWiseMin( minP, point );
				}
				//Make all range values positive
				Point<Number> dimRange = maxP - minP;
				for ( unsigned i = 0; i < dimRange.dimension(); i++ ) {
					dimRange[i] = dimRange.at( i ) < 0 ? Number( -1 ) * dimRange.at( i ) : dimRange.at( i );
				}
				//Get dimension with smallest range
				std::size_t smallest = 0;
				for ( std::size_t d = 0; d < dimRange.dimension(); d++ ) {
					if ( dimRange.at( d ) < dimRange.at( smallest ) ) {
						smallest = d;
					}
				}
				//projDimensions are those who are bigger than smallest.
				std::vector<std::size_t> projectionDimensions;
				std::vector<std::size_t> droppedDimensions;
				TRACE( "hypro.representations.HPolytope", "Project on dimensions: " );
				for ( std::size_t d = 0; d < dimRange.dimension(); d++ ) {
					if ( d != smallest ) {
						TRACE( "hypro.representations.HPolytope", d );
						projectionDimensions.push_back( d );
					} else {
						droppedDimensions.push_back( d );
					}
				}

				/*
					std::vector<std::size_t> projectionDimensions;
					std::vector<std::size_t> droppedDimensions;
					for(std::size_t d = 0; d < mDimension; ++d){
						if(d < unsigned(effectiveDim)){
							projectionDimensions.push_back(d);
						} else {
							droppedDimensions.push_back(d);
						}
					}
					*/
				std::vector<Point<Number>> projectedPoints;
				for ( const auto& point : pointsCopy ) {
					TRACE( "hypro.representations.HPolytope", "Projected point " << point.projectOn( projectionDimensions ) );
					projectedPoints.emplace_back( point.projectOn( projectionDimensions ) );
				}

				HPolytopeT<Number, Converter, Setting> projectedPoly( projectedPoints );
				//std::cout << "Projected polytope: " << projectedPoly << std::endl;
				projectedPoly.insertEmptyDimensions( projectionDimensions, droppedDimensions );

				TRACE( "hypro.representations.HPolytope", "After lifting " << projectedPoly );

				//std::cout << "After inserting empty dimensions: " << projectedPoly << std::endl;
				//std::cout << "Poly dimension: " << projectedPoly.dimension() << " and plane dimension : " << planeNormal.rows() << std::endl;
				projectedPoly.insert( Halfspace<Number>( planeNormal, planeOffset ) );
				projectedPoly.insert( Halfspace<Number>( -planeNormal, -planeOffset ) );

				TRACE( "hypro.representations.HPolytope", "After adding constraints " << projectedPoly );

				*this = projectedPoly;

				if ( Setting::OPTIMIZER_CACHING ) {
					setOptimizer( this->matrix(), this->vector() );
				}

				// Alternative version
				// We need a copy of the set of pointsCopy since auxiliary points will be added
				//std::vector<Point<Number>> auxiliaryPoints(points);
				//mHPlanes = computeConstraintsForDegeneratedPolytope(auxiliaryPoints, mDimension - effectiveDim);

			} else {
				/*
					ConvexHull<Number> ch(points);
					ch.convexHullVertices();
					mHPlanes = ch.getHsv();
					*/

				std::vector<std::shared_ptr<Facet<Number>>> facets = convexHull( pointsCopy ).first;
				for ( auto& facet : facets ) {
#ifndef NDEBUG
					std::for_each( pointsCopy.begin(), pointsCopy.end(), [&facet]( const auto& p ) { if(!facet->halfspace().contains(p)) {
						std::cout << "Facet " << *facet << " does not contain point " << p << ", distance: " << facet->getDist(p) <<  std::endl;
					} } );
#endif
					assert( facet->halfspace().contains( pointsCopy ) );
					mHPlanes.push_back( facet->halfspace() );
				}
				facets.clear();

				if ( Setting::OPTIMIZER_CACHING ) {
					setOptimizer( this->matrix(), this->vector() );
				}
			}
		}
	}
	//EVALUATE_BENCHMARK_RESULT( "HPoly_vertices_constructor" )
}

//conversion ctor - just like copy ctor
template <typename Number, typename Converter, class Setting>
template <typename SettingRhs, carl::DisableIf<std::is_same<Setting, SettingRhs>>>
HPolytopeT<Number, Converter, Setting>::HPolytopeT( const HPolytopeT<Number, Converter, SettingRhs>& orig )
	: mHPlanes( orig.constraints() )
	, mDimension( orig.dimension() )
	, mNonRedundant( orig.isNonRedundant() ) {
	if ( Setting::OPTIMIZER_CACHING && orig.getOptimizer().has_value() ) {
		setOptimizer( orig.matrix(), orig.vector() );
	}
}

template <typename Number, typename Converter, class Setting>
HPolytopeT<Number, Converter, Setting>::~HPolytopeT() {
}

/*
 * Getters and setters
 */

template <typename Number, typename Converter, class Setting>
bool HPolytopeT<Number, Converter, Setting>::empty() const {
	TRACE( "hypro.representations.HPolytope", __func__ );
	if ( mEmptyState == SETSTATE::EMPTY ) {
		TRACE( "hypro.representations.HPolytope", "Already set to true." );
		return true;
	}
	if ( mEmptyState == SETSTATE::NONEMPTY || mEmptyState == SETSTATE::UNIVERSAL ) {
		TRACE( "hypro.representations.HPolytope", "Already set to false." );
		return false;
	}

	if ( mHPlanes.empty() ) {
		TRACE( "hypro.representations.HPolytope", "Polytope is universe." );
		mEmptyState = SETSTATE::UNIVERSAL;
		return false;
	}

	TRACE( "hypro.representations.HPolytope", "Call to Optimizer." );

	bool res = false;
	if ( Setting::OPTIMIZER_CACHING ) {
		if ( !mUpdated ) {
			this->setOptimizer( this->matrix(), this->vector() );
		}
		res = !mOptimizer->checkConsistency();
	} else {
		Optimizer<Number> opt{ this->matrix(), this->vector() };
		res = !opt.checkConsistency();
	}

	mEmptyState = ( res == true ? SETSTATE::EMPTY : SETSTATE::NONEMPTY );
	TRACE( "hypro.representations.HPolytope", "Optimizer result: " << res );
	return res;
}

template <typename Number, typename Converter, class Setting>
HPolytopeT<Number, Converter, Setting> HPolytopeT<Number, Converter, Setting>::Empty() {
	HPolytopeT res{};
	res.setEmptyState( SETSTATE::EMPTY );
	res.mNonRedundant = true;
	return res;
}

template <typename Number, typename Converter, class Setting>
std::size_t HPolytopeT<Number, Converter, Setting>::dimension() const {
	if ( mHPlanes.empty() ) return 0;
	return mDimension;
}

template <typename Number, typename Converter, class Setting>
std::size_t HPolytopeT<Number, Converter, Setting>::size() const {
	return mHPlanes.size();
}

template <typename Number, typename Converter, class Setting>
matrix_t<Number> HPolytopeT<Number, Converter, Setting>::matrix() const {
	matrix_t<Number> res( mHPlanes.size(), dimension() );
	for ( unsigned planeIndex = 0; planeIndex < mHPlanes.size(); ++planeIndex ) {
		assert( mHPlanes.at( planeIndex ).normal().rows() == int( dimension() ) );
		res.row( planeIndex ) = mHPlanes.at( planeIndex ).normal();
	}
	return res;
}

template <typename Number, typename Converter, class Setting>
vector_t<Number> HPolytopeT<Number, Converter, Setting>::vector() const {
	vector_t<Number> res( mHPlanes.size() );
	for ( unsigned planeIndex = 0; planeIndex < mHPlanes.size(); ++planeIndex ) {
		res( planeIndex ) = mHPlanes.at( planeIndex ).offset();
	}
	return res;
}

template <typename Number, typename Converter, class Setting>
std::pair<matrix_t<Number>, vector_t<Number>> HPolytopeT<Number, Converter, Setting>::inequalities() const {
	return std::make_pair( this->matrix(), this->vector() );
}

template <typename Number, typename Converter, class Setting>
typename std::vector<Point<Number>> HPolytopeT<Number, Converter, Setting>::vertices( const matrix_t<Number>& ) const {
	typename std::vector<Point<Number>> vertices;
	// empty polytope
	if ( mHPlanes.empty() || this->empty() ) {
		return vertices;
	}

	if ( Setting::NAIVE_ALGORITHMS ) {
		if ( !mHPlanes.empty() && mHPlanes.size() >= this->dimension() && !this->empty() ) {
			std::size_t dim = this->dimension();

			Permutator permutator( mHPlanes.size(), dim );
			std::vector<std::size_t> permutation;
			while ( !permutator.end() ) {
				permutation = permutator();

				matrix_t<Number> A( dim, dim );
				vector_t<Number> b( dim );
				unsigned pos = 0;
				//std::cout << "Permute planes ";
				for ( auto planeIt = permutation.begin(); planeIt != permutation.end(); ++planeIt ) {
					//std::cout << *planeIt << ", ";
					A.row( pos ) = mHPlanes.at( *planeIt ).normal().transpose();
					// std::cout << A.row(pos) << std::endl;
					b( pos ) = mHPlanes.at( *planeIt ).offset();
					// std::cout << b(pos) << std::endl;
					++pos;
				}
				//std::cout << std::endl;

				//std::cout << "Created first matrix" << std::endl;

				Eigen::FullPivLU<matrix_t<Number>> lu_decomp( A );
				if ( lu_decomp.rank() < A.rows() ) {
					continue;
				}

				vector_t<Number> res = lu_decomp.solve( b );

				TRACE( "hypro.representations.HPolytope", "Computed Vertex: " << ( convert<Number, double>( res ).transpose() ) );

				// Check if the computed vertex is a real vertex
				bool outside = false;
				for ( unsigned planePos = 0; planePos < mHPlanes.size(); ++planePos ) {
					bool skip = false;
					for ( unsigned permPos = 0; permPos < permutation.size(); ++permPos ) {
						if ( planePos == permutation.at( permPos ) ) {
							//std::cout << "Skip plane " << planePos << std::endl;
							skip = true;
							break;
						}
					}

					if ( !skip && !carl::AlmostEqual2sComplement( mHPlanes.at( planePos ).offset(), mHPlanes.at( planePos ).normal().dot( res ), default_double_comparison_ulps ) && mHPlanes.at( planePos ).offset() - mHPlanes.at( planePos ).normal().dot( res ) < 0 ) {
						TRACE( "hypro.representations.HPolytope", "Drop vertex: " << ( convert<Number, double>( res ).transpose() ) << " because of plane " << planePos );
						outside = true;
						break;
					}
				}
				if ( !outside ) {
					// insert, if no duplicate
					Point<Number> tmp( res );
					if ( std::find( vertices.begin(), vertices.end(), tmp ) == vertices.end() ) {
						vertices.push_back( tmp );
					}
					TRACE( "hypro.representations.HPolytope", "Final vertex: " << ( convert<Number, double>( res ).transpose() ) );
				}
			}
		}
		return vertices;
	} else {  // Use quickhull (exact arithmetic) for vertex-enumeration

		// conversion to mpq_class
		std::vector<vector_t<mpq_class>> halfspaces;
		for ( std::size_t i = 0; i < mHPlanes.size(); ++i ) {
			halfspaces.emplace_back( this->dimension() + 1 );
			halfspaces.back().head( this->dimension() ) = convert<Number, mpq_class>( mHPlanes[i].normal() );
			halfspaces.back()[this->dimension()] = carl::convert<Number, mpq_class>( mHPlanes[i].offset() );
		}
		// compute vertices (dual)
		QuickIntersection<mpq_class> facetEnumerator{ halfspaces, this->dimension() };
		facetEnumerator.compute();

		// re-transform and convert
		for ( auto facet : facetEnumerator.getFacets() ) {
			vertices.emplace_back( this->dimension() );
			//The resulting points can't be points at infinity
			if ( facet.mOffset == 0 ) {
				std::cout << "Polytope is unbounded." << std::endl;
			} else {
				facet.mNormal /= facet.mOffset;
				vertices.back() = convert<mpq_class, Number>( facet.mNormal );
			}
		}
		return vertices;
	}

	// verify against reverse-search algorithm.
	/*
#ifndef NDEBUG
	VertexEnumeration<Number> ev = VertexEnumeration<Number>(mHPlanes);
	ev.enumerateVertices();
	//std::cout << "Enumerate vertices of " << std::endl << *this << std::endl;
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
			found= found || (point==vert);
		}
		assert(found);
	}
	return ev.getPoints();
#endif
	*/

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

template <typename Number, typename Converter, class Setting>
Number HPolytopeT<Number, Converter, Setting>::supremum() const {
	Number max = 0;
	assert( !this->empty() );
	assert( !this->vertices().empty() );
	for ( const auto& point : this->vertices() ) {
		Number inftyNorm = Point<Number>::inftyNorm( point );
		max = max > inftyNorm ? max : inftyNorm;
	}
	return max;
}

//template <typename Number, typename Converter, class Setting>
//void HPolytopeT<Number, Converter, Setting>::calculateFan() const {
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

template <typename Number, typename Converter, class Setting>
void HPolytopeT<Number, Converter, Setting>::insert( const Halfspace<Number>& plane ) {
	assert( mDimension == 0 || mDimension == plane.dimension() );
	if ( mDimension == 0 ) {
		mDimension = plane.dimension();
		mHPlanes.push_back( plane );
		mEmptyState = SETSTATE::NONEMPTY;
		mNonRedundant = true;
	} else {
		bool found = false;
		for ( auto planeIt = mHPlanes.begin(); planeIt != mHPlanes.end(); ++planeIt ) {
			if ( *planeIt == plane ) {
				found = true;
				break;
			}
		}
		if ( !found ) {
			mHPlanes.push_back( plane );
			mEmptyState = SETSTATE::UNKNOWN;
			mNonRedundant = false;
			mUpdated = false;
		}
	}
	invalidateCache();
}

template <typename Number, typename Converter, class Setting>
void HPolytopeT<Number, Converter, Setting>::insert( const typename HalfspaceVector::iterator begin, const typename HalfspaceVector::iterator end ) {
	auto it = begin;
	while ( it != end ) {
		this->insert( *it );
		++it;
	}
}

template <typename Number, typename Converter, class Setting>
void HPolytopeT<Number, Converter, Setting>::erase( const unsigned index ) {
	assert( index < mHPlanes.size() );
	mHPlanes.erase( mHPlanes.begin() + index );
	if ( mEmptyState == SETSTATE::EMPTY ) {
		setEmptyState( SETSTATE::UNKNOWN );
	}
	mUpdated = false;
	invalidateCache();
}

template <typename Number, typename Converter, class Setting>
const typename HPolytopeT<Number, Converter, Setting>::HalfspaceVector& HPolytopeT<Number, Converter, Setting>::constraints() const {
	return mHPlanes;
}

template <typename Number, typename Converter, class Setting>
bool HPolytopeT<Number, Converter, Setting>::hasConstraint( const Halfspace<Number>& hplane ) const {
	for ( const auto& plane : mHPlanes ) {
		if ( hplane == plane ) return true;
	}
	return false;
}

template <typename Number, typename Converter, class Setting>
const HPolytopeT<Number, Converter, Setting>& HPolytopeT<Number, Converter, Setting>::removeRedundancy() {
	//std::cout << __func__ << std::endl;
	if ( !mNonRedundant && mHPlanes.size() > 1 ) {
		std::vector<std::size_t> redundant;
		if ( Setting::OPTIMIZER_CACHING ) {
			if ( !mUpdated ) {
				setOptimizer( this->matrix(), this->vector() );
			}
			redundant = mOptimizer->redundantConstraints();
		} else {
			Optimizer<Number> opt;
			opt.setMatrix( this->matrix() );
			opt.setVector( this->vector() );
			redundant = opt.redundantConstraints();
		}

		//std::vector<std::size_t> redundant = opt.redundantConstraints();

		if ( !redundant.empty() ) {
			std::size_t cnt = mHPlanes.size() - 1;
			for ( auto rIt = mHPlanes.rbegin(); rIt != mHPlanes.rend(); ++rIt ) {
				if ( redundant.empty() )
					break;

				if ( redundant.back() == cnt ) {
					mHPlanes.erase( --( rIt.base() ) );
					redundant.pop_back();
					//std::cout << "Erase plane " << cnt << std::endl;
				}
				--cnt;
			}
		}

		assert( redundant.empty() );
	}
	mNonRedundant = true;
	return *this;
}

template <typename Number, typename Converter, class Setting>
bool HPolytopeT<Number, Converter, Setting>::isExtremePoint( const vector_t<Number>& point ) const {
	unsigned cnt = 0;
	for ( const auto& plane : mHPlanes ) {
		Number val = plane.evaluate( point );
		if ( plane.offset() == val ) {
			++cnt;
		} else if ( plane.offset() - val < 0 ) {
			return false;
		}
	}
	return ( cnt >= mDimension );
}

template <typename Number, typename Converter, class Setting>
bool HPolytopeT<Number, Converter, Setting>::isExtremePoint( const Point<Number>& point ) const {
	return isExtremePoint( point.rawCoordinates() );
}

template <typename Number, typename Converter, class Setting>
EvaluationResult<Number> HPolytopeT<Number, Converter, Setting>::evaluate( const vector_t<Number>& _direction ) const {
	if ( mHPlanes.empty() ) {
		//return EvaluationResult<Number>( Number(1), SOLUTION::INFTY );
		return EvaluationResult<Number>();
	}
	//reduceNumberRepresentation();
	if ( Setting::OPTIMIZER_CACHING ) {
		assert( mOptimizer.has_value() );
		if ( !mUpdated ) {
			setOptimizer( this->matrix(), this->vector() );
		}
		return mOptimizer->evaluate( _direction, true );
	} else {
		Optimizer<Number> opt;
		opt.setMatrix( this->matrix() );
		opt.setVector( this->vector() );
		return opt.evaluate( _direction, true );
	}
}

template <typename Number, typename Converter, class Setting>
std::vector<EvaluationResult<Number>> HPolytopeT<Number, Converter, Setting>::multiEvaluate( const matrix_t<Number>& _directions, bool useExact ) const {
	assert( _directions.cols() == Eigen::Index( dimension() ) );
	if ( mHPlanes.empty() ) {
		return std::vector<EvaluationResult<Number>>();
	}
	std::vector<EvaluationResult<Number>> res;
	if ( Setting::OPTIMIZER_CACHING ) {
		assert( mOptimizer.has_value() );
		if ( !mUpdated ) {
			setOptimizer( this->matrix(), this->vector() );
		}
		for ( int i = 0; i < _directions.rows(); ++i ) {
			res.emplace_back( mOptimizer->evaluate( _directions.row( i ), useExact ) );
		}
	} else {
		Optimizer<Number> opt;
		opt.setMatrix( this->matrix() );
		opt.setVector( this->vector() );
		for ( int i = 0; i < _directions.rows(); ++i ) {
			res.emplace_back( opt.evaluate( _directions.row( i ), useExact ) );
		}
	}
	return res;
}

template <typename Number, typename Converter, class Setting>
std::vector<EvaluationResult<Number>> HPolytopeT<Number, Converter, Setting>::multiEvaluate( const matrix_t<Number>& _directions ) const {
	std::vector<EvaluationResult<Number>> res;
	for ( int i = 0; i < _directions.rows(); ++i ) {
		res.push_back( evaluate( _directions.row( i ) ) );
	}
	return res;
}

/*
 * General interface
 */

template <typename Number, typename Converter, class Setting>
std::pair<CONTAINMENT, HPolytopeT<Number, Converter, Setting>> HPolytopeT<Number, Converter, Setting>::satisfiesHalfspace( const Halfspace<Number>& rhs ) const {
	TRACE( "hypro.representations.HPolytope", "(P AND ex <= d) == emptyset?, e: " << rhs.normal() << "d: " << rhs.offset() );
	if ( this->empty() ) {
		return std::make_pair( CONTAINMENT::NO, *this );
	}
	HPolytopeT<Number, Converter, Setting> tmp = this->intersectHalfspace( rhs );
	if ( tmp.hasConstraint( rhs ) ) {
		if ( tmp.empty() ) {
			return std::make_pair( CONTAINMENT::NO, std::move( tmp ) );
		} else {
			return std::make_pair( CONTAINMENT::PARTIAL, std::move( tmp ) );
		}
	}
	assert( !tmp.empty() );
	return std::make_pair( CONTAINMENT::FULL, std::move( tmp ) );
}

template <typename Number, typename Converter, class Setting>
std::pair<CONTAINMENT, HPolytopeT<Number, Converter, Setting>> HPolytopeT<Number, Converter, Setting>::satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {
	TRACE( "hypro.representations.HPolytope", "(P AND Ax <= b) == emptyset?, A: " << _mat << "b: " << _vec );
	assert( _mat.rows() == _vec.rows() );
	if ( this->empty() ) {
		return std::make_pair( CONTAINMENT::NO, *this );
	}

	if ( _mat.rows() == 0 ) {
		return std::make_pair( CONTAINMENT::FULL, *this );
	}
	HPolytopeT<Number, Converter, Setting> tmp = this->intersectHalfspaces( _mat, _vec );
	if ( tmp.empty() ) {
		return std::make_pair( CONTAINMENT::NO, std::move( tmp ) );
	}

	for ( Eigen::Index rowI = 0; rowI < _mat.rows(); ++rowI ) {
		if ( tmp.hasConstraint( Halfspace<Number>( _mat.row( rowI ), _vec( rowI ) ) ) ) {
			return std::make_pair( CONTAINMENT::PARTIAL, std::move( tmp ) );
		}
	}
	assert( !tmp.empty() );
	return std::make_pair( CONTAINMENT::FULL, tmp );
}

template <typename Number, typename Converter, class Setting>
HPolytopeT<Number, Converter, Setting> HPolytopeT<Number, Converter, Setting>::projectOut( const std::vector<std::size_t>& dimensions, bool viaLinearTransformation ) const {
	TRACE( "hypro.representations.HPolytope", "out dimensions " << dimensions );
	if ( dimensions.empty() ) {
		return *this;
	}

	if ( viaLinearTransformation ) {
		// projection by means of a linear transformation
		matrix_t<Number> projectionMatrix = matrix_t<Number>::Identity( this->dimension(), this->dimension() );
		for ( auto i : dimensions ) {
			projectionMatrix( i, i ) = 0;
		}
		// TODO remove empty cols which were projected out
		return this->linearTransformation( projectionMatrix );
	} else {
		auto [newConstraints, newConstants] = eliminateCols( this->matrix(), this->vector(), dimensions, false );
		return { newConstraints, newConstants };
	}
}

template <typename Number, typename Converter, class Setting>
HPolytopeT<Number, Converter, Setting> HPolytopeT<Number, Converter, Setting>::projectOutConservative( const std::vector<std::size_t>& dimensions, bool viaLinearTransformation ) const {
	TRACE( "hypro.representations.HPolytope", "out dimensions " << dimensions );
	if ( dimensions.empty() ) {
		return *this;
	}

	if ( viaLinearTransformation ) {
		// projection by means of a linear transformation
		matrix_t<Number> projectionMatrix = matrix_t<Number>::Identity( this->dimension(), this->dimension() );
		for ( auto i : dimensions ) {
			projectionMatrix( i, i ) = 0;
		}

		return this->linearTransformation( projectionMatrix );
	} else {
		auto [newConstraints, newConstants] = eliminateCols( this->matrix(), this->vector(), dimensions, true );
		return { newConstraints, newConstants };
	}
}

template <typename Number, typename Converter, class Setting>
HPolytopeT<Number, Converter, Setting> HPolytopeT<Number, Converter, Setting>::projectOn( const std::vector<std::size_t>& dimensions ) const {
	TRACE( "hypro.representations.HPolytope", "out dimensions " << dimensions );
	if ( dimensions.empty() ) {
		return Empty();
	}

	// projection by means of a linear transformation
	matrix_t<Number> projectionMatrix = matrix_t<Number>::Zero( this->dimension(), this->dimension() );
	for ( auto i : dimensions ) {
		projectionMatrix( i, i ) = 1;
	}

	return this->linearTransformation( projectionMatrix );
}

template <typename Number, typename Converter, class Setting>
HPolytopeT<Number, Converter, Setting> HPolytopeT<Number, Converter, Setting>::linearTransformation( const matrix_t<Number>& A ) const {
	TRACE( "hypro.representations.HPolytope", "P' = A*P, A:" << std::endl
															 << A );
	if ( A.nonZeros() == 0 ) {
		return HPolytopeT<Number, Converter, Setting>::Empty();
	}
	if ( !this->empty() && !mHPlanes.empty() ) {
		Eigen::FullPivLU<matrix_t<Number>> lu( A );
		// if A has full rank, we can simply re-transform, otherwise use v-representation.
		if ( lu.rank() == A.rows() ) {
			TRACE( "hypro.representations.HPolytope", "A has full rank - do not use v-conversion." );
			std::pair<matrix_t<Number>, vector_t<Number>> inequalities = this->inequalities();
			assert( ( HPolytopeT<Number, Converter, Setting>( inequalities.first * A.inverse(), inequalities.second ).size() == this->size() ) );
			return HPolytopeT<Number, Converter, Setting>( inequalities.first * A.inverse(), inequalities.second );
		} else {
			TRACE( "hypro.representations.HPolytope", "Use V-Conversion for linear transformation." );
			auto intermediate = Converter::toVPolytope( *this );
			intermediate = intermediate.linearTransformation( A );
			auto res = Converter::toHPolytope( intermediate );
			res.setReduced();
			return res;
		}
	} else {
		return *this;
	}
}

template <typename Number, typename Converter, class Setting>
HPolytopeT<Number, Converter, Setting> HPolytopeT<Number, Converter, Setting>::affineTransformation( const matrix_t<Number>& A,
																									 const vector_t<Number>& b ) const {
	TRACE( "hypro.representations.HPolytope", "P' = A*P + b, A: " << std::endl
																  << A << "b: " << std::endl
																  << b );
	if ( A.nonZeros() == 0 ) {
		std::vector<Point<Number>> points;
		points.emplace_back( b );
		return HPolytopeT<Number, Converter, Setting>( points );
	}
	if ( !this->empty() && !mHPlanes.empty() ) {
		Eigen::FullPivLU<matrix_t<Number>> lu( A );
		// if A has full rank, we can simply re-transform, otherwise use v-representation.
		if ( lu.rank() == A.rows() ) {
			TRACE( "hypro.representations.HPolytope", "A has full rank - do not use v-conversion." );
			std::pair<matrix_t<Number>, vector_t<Number>> inequalities = this->inequalities();
			assert( ( HPolytopeT<Number, Converter, Setting>( inequalities.first * A.inverse(), inequalities.first * A.inverse() * b + inequalities.second ).size() == this->size() ) );
			assert( !( HPolytopeT<Number, Converter, Setting>( inequalities.first * A.inverse(), inequalities.first * A.inverse() * b + inequalities.second ).empty() ) );
			return HPolytopeT<Number, Converter, Setting>( inequalities.first * A.inverse(), inequalities.first * A.inverse() * b + inequalities.second );
		} else {
			TRACE( "hypro.representations.HPolytope", "Use V-Conversion for linear transformation." );
			auto intermediate = Converter::toVPolytope( *this );
			intermediate = intermediate.affineTransformation( A, b );
			auto res = Converter::toHPolytope( intermediate );
			//assert(res.size() <= this->size());
			res.setReduced();
			return res;
		}
	} else {
		return *this;
	}
}

template <typename Number, typename Converter, class Setting>
HPolytopeT<Number, Converter, Setting> HPolytopeT<Number, Converter, Setting>::minkowskiSum( const HPolytopeT& rhs ) const {
	TRACE( "hypro.representations.HPolytope", "P' = P + " << rhs << std::endl );
	HPolytopeT<Number, Converter, Setting> res;
	Number result;

	// evaluation of rhs in directions of lhs
	for ( unsigned i = 0; i < mHPlanes.size(); ++i ) {
		EvaluationResult<Number> evalRes = rhs.evaluate( mHPlanes.at( i ).normal() );
		if ( evalRes.errorCode == SOLUTION::INFTY ) {
			// Do nothing - omit inserting plane.
		} else if ( evalRes.errorCode == SOLUTION::INFEAS ) {
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
		if ( evalRes.errorCode == SOLUTION::INFTY ) {
			// Do nothing - omit inserting plane.
		} else if ( evalRes.errorCode == SOLUTION::INFEAS ) {
			return Empty();
		} else {
			result = rhs.constraints().at( i ).offset() + evalRes.supportValue;
			res.insert( Halfspace<Number>( rhs.constraints().at( i ).normal(), result ) );
		}
	}
	//}
	return res;
}

template <typename Number, typename Converter, class Setting>
HPolytopeT<Number, Converter, Setting> HPolytopeT<Number, Converter, Setting>::intersect( const HPolytopeT& rhs ) const {
	TRACE( "hypro.representations.HPolytope", "with " << rhs << std::endl );
	if ( rhs.empty() || this->empty() ) {
		return HPolytopeT<Number, Converter, Setting>::Empty();
	} else {
		HPolytopeT<Number, Converter, Setting> res;
		for ( const auto& plane : mHPlanes ) {
			res.insert( plane );
		}
		for ( const auto& plane : rhs.constraints() ) {
			res.insert( plane );
		}

		return res;
	}
}

template <typename Number, typename Converter, class Setting>
HPolytopeT<Number, Converter, Setting> HPolytopeT<Number, Converter, Setting>::intersectHalfspace( const Halfspace<Number>& rhs ) const {
#ifdef HYPRO_LOGGING
	TRACE( "hypro.representations.HPolytope", "with " << rhs << std::endl );
#endif
	HPolytopeT<Number, Converter, Setting> res{ *this };
	// only insert the new Halfspace, if it is not already redundant.
	if ( res.evaluate( rhs.normal() ).supportValue > rhs.offset() )
		res.insert( Halfspace<Number>( rhs ) );

	return res;
}

template <typename Number, typename Converter, class Setting>
HPolytopeT<Number, Converter, Setting> HPolytopeT<Number, Converter, Setting>::intersectHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {
	TRACE( "hypro.representations.HPolytope", "P' = P AND Ax <= b,  A: " << std::endl
																		 << _mat << std::endl
																		 << "b: " << _vec );
	assert( _mat.rows() == _vec.rows() );
	HPolytopeT<Number, Converter, Setting> res( *this );
	for ( unsigned i = 0; i < _mat.rows(); ++i ) {
		res.insert( Halfspace<Number>( _mat.row( i ), _vec( i ) ) );
	}
	res.removeRedundancy();
	return res;
}

template <typename Number, typename Converter, class Setting>
bool HPolytopeT<Number, Converter, Setting>::contains( const Point<Number>& point ) const {
#ifdef HYPRO_LOGGING
	TRACE( "hypro.representations.HPolytope", point );
#endif
	return this->contains( point.rawCoordinates() );
}

template <typename Number, typename Converter, class Setting>
bool HPolytopeT<Number, Converter, Setting>::contains( const vector_t<Number>& vec ) const {
	if ( Setting::CACHE_BOUNDING_BOX ) {
		if ( !mBox ) {
			// update cache
			updateBoundingBox();
		}
		assert( vec.rows() == Eigen::Index( mBox->size() ) );
		// check containment in bounding box
		for ( std::size_t i = 0; i < mBox->size(); ++i ) {
			if ( !( *mBox )[i].contains( vec( i ) ) ) {
				return false;
			}
		}
	}
	// The 2's complement check for equality is required to ensure double compatibility, for exact numbers it will fallback to checking exact equality.
	return std::all_of( mHPlanes.begin(), mHPlanes.end(), [&vec]( const auto& plane ) { return carl::AlmostEqual2sComplement( plane.normal().dot( vec ), plane.offset() ) || plane.normal().dot( vec ) <= plane.offset(); } );

	/*
	for ( const auto &plane : mHPlanes ) {
		// The 2's complement check for equality is required to ensure double compatibility, for exact numbers it will fallback to checking exact equality.
		if ( !carl::AlmostEqual2sComplement( plane.normal().dot( vec ), plane.offset() ) && plane.normal().dot( vec ) > plane.offset() ) {
			return false;
		}
	}
	return true;
	*/
}

template <typename Number, typename Converter, class Setting>
bool HPolytopeT<Number, Converter, Setting>::contains( const HPolytopeT<Number, Converter, Setting>& rhs ) const {
	if ( this->empty() ) {
		return false;
	}
	if ( rhs.empty() ) {
		return true;
	}

	for ( const auto& plane : rhs.constraints() ) {
		EvaluationResult<Number> evalRes = this->evaluate( plane.normal() );
		if ( evalRes.errorCode == SOLUTION::INFEAS ) {
			return false;  // empty!
		} else if ( evalRes.errorCode == SOLUTION::INFTY ) {
			continue;
		} else if ( evalRes.supportValue < plane.offset() ) {
			assert( evalRes.errorCode == SOLUTION::FEAS );
			return false;
		}
	}
	return true;
}

template <typename Number, typename Converter, class Setting>
HPolytopeT<Number, Converter, Setting> HPolytopeT<Number, Converter, Setting>::unite( const HPolytopeT& _rhs ) const {
	TRACE( "hypro.representations.HPolytope", "with " << _rhs << std::endl );
	if ( this->empty() ) {
		// if this is empty, the result is _rhs, even if _rhs is empty, too.
		return _rhs;
	}
	// at this point *this is not empty.
	if ( _rhs.empty() ) {
		return *this;
	}
	// at this point, none is empty.
	if ( Setting::AVOID_CONVERSION == true ) {
		std::size_t numberOfDirections = 8;
		TRACE( "hypro.representations.HPolytope", "Unite using templated evaluation using " << numberOfDirections << " directions." );
		assert( this->dimension() == _rhs.dimension() );
		std::vector<vector_t<Number>> templateDirections = computeTemplate<Number>( this->dimension(), numberOfDirections );
		// as the template directions are ordered, we assume the same order for the results.
		HalfspaceVector newHalfspaces;
		for ( const auto& direction : templateDirections ) {
			EvaluationResult<Number> thisResult = this->evaluate( direction );
			EvaluationResult<Number> rhsResult = _rhs.evaluate( direction );
			assert( thisResult.errorCode != SOLUTION::INFEAS );
			assert( rhsResult.errorCode != SOLUTION::INFEAS );
			// if one of the polytopes is unbounded, do not add this halfspace -> keep the unboundedness.
			if ( thisResult.errorCode == SOLUTION::FEAS && rhsResult.errorCode == SOLUTION::FEAS ) {
				if ( thisResult.supportValue > rhsResult.supportValue ) {
					newHalfspaces.emplace_back( direction, thisResult.supportValue );
				} else {
					newHalfspaces.emplace_back( direction, rhsResult.supportValue );
				}
			}
		}
		assert( newHalfspaces.size() <= templateDirections.size() );
		return HPolytopeT<Number, Converter, Setting>( newHalfspaces );
	} else {
		TRACE( "hypro.representations.HPolytope", "Unite using V-polytope representation." );
		std::vector<Point<Number>> vertices = this->vertices();
		std::vector<Point<Number>> rhsVertices = _rhs.vertices();
		vertices.insert( vertices.end(), rhsVertices.begin(), rhsVertices.end() );
		HPolytopeT<Number, Converter, Setting> result( vertices );

		/*
		auto lhs = Converter::toVPolytope( *this );
		std::cout << "this as vpoly: " << lhs << std::endl;
		auto tmpRes = lhs.unite( Converter::toVPolytope( _rhs ) );
		std::cout << "rhs as vpoly : " << Converter::toVPolytope( _rhs ) << std::endl;
		HPolytopeT<Number,Converter,Setting> result = Converter::toHPolytope( tmpRes );
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
		HPolytopeT<Number,Converter,Setting> result = HPolytopeT<Number,Converter,Setting>(ch.getHsv());
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
	}
}

template <typename Number, typename Converter, class Setting>
HPolytopeT<Number, Converter, Setting> HPolytopeT<Number, Converter, Setting>::unite( const std::vector<HPolytopeT>& rhs ) {
	// Todo: Implement alternative avoiding conversion.
	// Idea: Use templated evaluation.
	std::vector<Point<Number>> vertices;
	for ( const auto& poly : rhs ) {
		vertices.insert( vertices.end(), poly.vertices().begin(), poly.vertices().end() );
	}
	return HPolytopeT( vertices );
}

template <typename Number, typename Converter, class Setting>
void HPolytopeT<Number, Converter, Setting>::clear() {
	mHPlanes.clear();
	mDimension = 0;
	mEmptyState = SETSTATE::UNIVERSAL;
	mNonRedundant = true;
	mUpdated = false;
	if ( Setting::OPTIMIZER_CACHING ) {
		mOptimizer->cleanContexts();
	}
	invalidateCache();
}

template <typename Number, typename Converter, class Setting>
void HPolytopeT<Number, Converter, Setting>::print() const {
	//std::cout << *this << std::endl;
}

/*
 * Auxiliary functions
 */

template <typename Number, typename Converter, class Setting>
typename HPolytopeT<Number, Converter, Setting>::HalfspaceVector HPolytopeT<Number, Converter, Setting>::computeConstraintsForDegeneratedPolytope( std::vector<Point<Number>>& points, unsigned degeneratedDimensions ) const {
	if ( degeneratedDimensions == 0 ) {
		return HPolytopeT<Number, Converter, Setting>( points ).mHPlanes;
	}
	assert( !points.empty() );
	Halfspace<Number> h;  // TODO set h to some hyperplane holding all points, i.e., a*p=b for all points p
	points.emplace_back( points.begin()->rawCoordinates() + h.normal() );
	// The effective dimension of the convex hull of points is now increased by one, i.e.,
	// the number of degenerated dimensions is decreased by one.
	// Furthermore, one of the faces of the convex hull of points is the polytope we are looking for.
	// This is exactly the face we get when we intersect the convex hull with the halfspace h
	HalfspaceVector result = commputeConstraintsForDegeneratedPolytope( points, degeneratedDimensions - 1 );
	result.emplace_back( std::move( h ) );	// decreases the effective dimension again
	return result;
}

template <typename Number, typename Converter, class Setting>
void HPolytopeT<Number, Converter, Setting>::insertEmptyDimensions( const std::vector<std::size_t>& existingDimensions, const std::vector<std::size_t>& newDimensions ) {
	assert( mDimension == existingDimensions.size() );

	//std::cout << __func__ << "Existing dimensions: " << existingDimensions << " and new dimensions: " << newDimensions << std::endl;

	for ( auto& halfspace : mHPlanes ) {
		vector_t<Number> newNormal = vector_t<Number>::Zero( existingDimensions.size() + newDimensions.size() );
		//std::cout << "New normal: " << newNormal << std::endl;
		unsigned currentPos = 0;
		for ( unsigned d = 0; d < existingDimensions.size() + newDimensions.size(); ++d ) {
			//std::cout << "Check dimension " << d << std::endl;
			if ( std::find( existingDimensions.begin(), existingDimensions.end(), d ) != existingDimensions.end() ) {
				//std::cout << "Found in existing dimensions." << std::endl;
				assert( std::find( newDimensions.begin(), newDimensions.end(), d ) == newDimensions.end() );
				newNormal( d ) = halfspace.normal()( currentPos );
				//std::cout << "updated normal: " << newNormal << std::endl;
				++currentPos;
			}
		}
		halfspace.setNormal( newNormal );
		//std::cout << "Updated halfspace: " << halfspace << std::endl;
	}
	mDimension = existingDimensions.size() + newDimensions.size();
	mUpdated = false;
}

template <typename Number, typename Converter, class Setting>
void HPolytopeT<Number, Converter, Setting>::updateBoundingBox() const {
	if ( Settings::CACHE_BOUNDING_BOX ) {
		std::size_t dim = this->dimension();
		mBox = decltype( mBox )( dim );
		for ( std::size_t i = 0; i < dim; ++i ) {
			vector_t<Number> direction = vector_t<Number>::Zero( dim );
			direction( i ) = Number( 1 );
			auto evalResUpper = this->evaluate( direction );
			carl::BoundType upperBound = carl::BoundType::WEAK;
			//if no bound is found in that direction (infinity) set interval end point to infinity
			if ( evalResUpper.errorCode == SOLUTION::INFTY ) {
				upperBound = carl::BoundType::INFTY;
			}

			direction( i ) = Number( -1 );
			auto evalResLower = this->evaluate( direction );
			carl::BoundType lowerBound = carl::BoundType::WEAK;
			//if no bound is found in that direction (infinity) set interval end point to infinity
			if ( evalResLower.errorCode == SOLUTION::INFTY ) {
				lowerBound = carl::BoundType::INFTY;
			}
			( *mBox )[i] = carl::Interval<Number>( -evalResLower.supportValue, lowerBound, evalResUpper.supportValue, upperBound );
		}
	}
}

template <typename Number, typename Converter, class Setting>
void HPolytopeT<Number, Converter, Setting>::updateCache() const {
	updateBoundingBox();
}

template <typename Number, typename Converter, class Setting>
void HPolytopeT<Number, Converter, Setting>::invalidateCache() const {
	if ( Settings::CACHE_BOUNDING_BOX ) {
		mBox = std::nullopt;
	}
}

template <typename Number, typename Converter, class Setting>
void HPolytopeT<Number, Converter, Setting>::setOptimizer( const matrix_t<Number>& mat, const vector_t<Number>& vec ) const {
	if ( mOptimizer.has_value() ) {
		mOptimizer->setMatrix( mat );
		mOptimizer->setVector( vec );
		mUpdated = true;
	} else {
		std::optional<Optimizer<Number>> tmp( std::in_place, mat, vec );
		mOptimizer.swap( tmp );
		assert( mOptimizer.has_value() );
		mUpdated = true;
	}
}

}  // namespace hypro
