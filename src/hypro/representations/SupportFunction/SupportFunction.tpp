/**
 * Wrapper class for SupportFunctionContent for easier use.
 * @file   SupportFunction.tpp
 *
 * @since      2015-11-23
 * @version    2015-12-16
 */

#include "SupportFunction.h"

namespace hypro {

//CONSTRUCTORS

//-------PRIVATE---------
template <typename Number, typename Converter, typename Setting>
SupportFunctionT<Number, Converter, Setting>::SupportFunctionT( const std::shared_ptr<SupportFunctionContent<Number, Setting>> _source )
	: content( _source ) {
	//handled by initializer list
}

//-------PUBLIC---------
template <typename Number, typename Converter, typename Setting>
SupportFunctionT<Number, Converter, Setting>::SupportFunctionT() {
	//handled by initializer list
}

//copy constructor
template <typename Number, typename Converter, typename Setting>
SupportFunctionT<Number, Converter, Setting>::SupportFunctionT( const SupportFunctionT<Number, Converter, Setting>& _orig )
	: GeometricObjectBase( _orig )
	, content( _orig.content ) {
	//handled by initializer list
}

//move constructor
template <typename Number, typename Converter, typename Setting>
SupportFunctionT<Number, Converter, Setting>::SupportFunctionT( SupportFunctionT<Number, Converter, Setting>&& other )
	: SupportFunctionT<Number, Converter, Setting>() {
	swap( *this, other );
}

template <typename Number, typename Converter, typename Setting>
SupportFunctionT<Number, Converter, Setting>::SupportFunctionT( SF_TYPE _type, Number _radius, unsigned dimension )
	: content( SupportFunctionContent<Number, Setting>::create( _type, _radius, dimension ) ) {
	//handled by initializer list
}

template <typename Number, typename Converter, typename Setting>
SupportFunctionT<Number, Converter, Setting>::SupportFunctionT( const std::vector<Point<Number>>& _vertices )
	: content( SupportFunctionContent<Number, Setting>::create( SF_TYPE::POLY, _vertices ) ) {
	//handled by initializer list
}

template <typename Number, typename Converter, typename Setting>
SupportFunctionT<Number, Converter, Setting>::SupportFunctionT( const matrix_t<Number>& _directions, const vector_t<Number>& _distances, bool overrideReduction )
	: content( SupportFunctionContent<Number, Setting>::create( SF_TYPE::POLY, _directions, _distances, overrideReduction ) ) {
	//handled by initializer list
}

template <typename Number, typename Converter, typename Setting>
SupportFunctionT<Number, Converter, Setting>::SupportFunctionT( const std::vector<Halfspace<Number>>& _planes )
	: content( SupportFunctionContent<Number, Setting>::create( SF_TYPE::POLY, _planes ) ) {
	//handled by initializer list
}

template <typename Number, typename Converter, typename Setting>
SupportFunctionT<Number, Converter, Setting>::SupportFunctionT( const matrix_t<Number>& _shapeMatrix )
	: content( SupportFunctionContent<Number, Setting>::create( SF_TYPE::ELLIPSOID, _shapeMatrix ) ) {
	//handled by initializer list
}

template <typename Number, typename Converter, typename Setting>
SupportFunctionT<Number, Converter, Setting>::SupportFunctionT( const std::vector<carl::Interval<Number>>& inBox )
	: content( SupportFunctionContent<Number, Setting>::create( SF_TYPE::BOX, inBox ) ) {
	//handled by initializer list
}

//destructor
template <typename Number, typename Converter, typename Setting>
SupportFunctionT<Number, Converter, Setting>::~SupportFunctionT() {
}

// OPERATOR OVERLOADING

template <typename Number, typename Converter, typename Setting>
SupportFunctionT<Number, Converter, Setting>& SupportFunctionT<Number, Converter, Setting>::operator=( SupportFunctionT<Number, Converter, Setting> _orig ) {
	if ( this != &_orig ) {
		swap( *this, _orig );
	}
	return *this;
}

// FUNCTIONS

template <typename Number, typename Converter, typename Setting>
EvaluationResult<Number> SupportFunctionT<Number, Converter, Setting>::evaluate( const vector_t<Number>& _direction, bool useExact ) const {
	matrix_t<Number> tmpMatrix = _direction.transpose();
	return content->multiEvaluate( tmpMatrix, useExact ).at( 0 );
}

template <typename Number, typename Converter, typename Setting>
std::vector<EvaluationResult<Number>> SupportFunctionT<Number, Converter, Setting>::multiEvaluate( const matrix_t<Number>& _directions, bool useExact ) const {
	TRACE( "hypro.representations.supportFunction", "Directions: " << _directions );
	std::vector<EvaluationResult<Number>> res = content->multiEvaluate( _directions, useExact );
	assert( res.size() == std::size_t( _directions.rows() ) );
	return res;
}

template <typename Number, typename Converter, typename Setting>
std::size_t SupportFunctionT<Number, Converter, Setting>::dimension() const {
	return content->dimension();
}

template <typename Number, typename Converter, typename Setting>
SF_TYPE SupportFunctionT<Number, Converter, Setting>::sfType() const {
	return content->type();
}

template <typename Number, typename Converter, typename Setting>
unsigned SupportFunctionT<Number, Converter, Setting>::depth() const {
	return content->depth();
}

template <typename Number, typename Converter, typename Setting>
unsigned SupportFunctionT<Number, Converter, Setting>::multiplicationsPerEvaluation() const {
	return content->multiplicationsPerEvaluation();
}

template <typename Number, typename Converter, typename Setting>
void SupportFunctionT<Number, Converter, Setting>::cleanUp() const {
	content->cleanUp();
}

template <typename Number, typename Converter, typename Setting>
std::string SupportFunctionT<Number, Converter, Setting>::getDotRepresentation() const {
	std::string nodes = "digraph structs \n { node [shape=record];\n";
	std::string transitions = "";

	content->getDotRepresentation( 0, nodes, transitions );

	return nodes + transitions + "}\n";
}

template <typename Number, typename Converter, typename Setting>
unsigned SupportFunctionT<Number, Converter, Setting>::operationCount() const {
	return content->operationCount();
}

template <typename Number, typename Converter, typename Setting>
sumContent<Number, Setting>* SupportFunctionT<Number, Converter, Setting>::summands() const {
	return content->summands();
}

template <typename Number, typename Converter, typename Setting>
trafoContent<Number, Setting>* SupportFunctionT<Number, Converter, Setting>::linearTrafoParameters() const {
	return content->linearTrafoParameters();
}

template <typename Number, typename Converter, typename Setting>
scaleContent<Number, Setting>* SupportFunctionT<Number, Converter, Setting>::scaleParameters() const {
	return content->scaleParameters();
}

template <typename Number, typename Converter, typename Setting>
unionContent<Number, Setting>* SupportFunctionT<Number, Converter, Setting>::unionParameters() const {
	return content->unionParameters();
}

template <typename Number, typename Converter, typename Setting>
intersectionContent<Number, Setting>* SupportFunctionT<Number, Converter, Setting>::intersectionParameters() const {
	return content->intersectionParameters();
}

template <typename Number, typename Converter, typename Setting>
PolytopeSupportFunction<Number, Setting>* SupportFunctionT<Number, Converter, Setting>::polytope() const {
	return content->polytope();
}

template <typename Number, typename Converter, typename Setting>
BallSupportFunction<Number>* SupportFunctionT<Number, Converter, Setting>::ball() const {
	return content->ball();
}

template <typename Number, typename Converter, typename Setting>
BoxSupportFunction<Number, Setting>* SupportFunctionT<Number, Converter, Setting>::box() const {
	return content->box();
}

template <typename Number, typename Converter, typename Setting>
EllipsoidSupportFunction<Number>* SupportFunctionT<Number, Converter, Setting>::ellipsoid() const {
	return content->ellipsoid();
}

template <typename Number, typename Converter, typename Setting>
matrix_t<Number> SupportFunctionT<Number, Converter, Setting>::matrix() const {
	if ( !mTemplateSet ) {
		evaluateTemplate();
	}
	return mMatrix;
}

template <typename Number, typename Converter, typename Setting>
vector_t<Number> SupportFunctionT<Number, Converter, Setting>::vector() const {
	if ( !mTemplateSet ) {
		evaluateTemplate();
	}
	return mVector;
}

template <typename Number, typename Converter, typename Setting>
void SupportFunctionT<Number, Converter, Setting>::removeRedundancy() const {
	// Support functions are already non-redundant (Polytope support functions are made non-redundant upon construction)
}

template <typename Number, typename Converter, typename Setting>
std::vector<Point<Number>> SupportFunctionT<Number, Converter, Setting>::vertices( const matrix_t<Number>& additionalDirections ) const {
	std::vector<vector_t<Number>> additionalDirectionVector;
	for ( unsigned rowIndex = 0; rowIndex < additionalDirections.rows(); ++rowIndex ) {
		additionalDirectionVector.push_back( vector_t<Number>( additionalDirections.row( rowIndex ) ) );
	}

	auto tmp = Converter::toHPolytope( *this, additionalDirectionVector );
	return tmp.vertices();
}

template <typename Number, typename Converter, typename Setting>
std::vector<Point<Number>> SupportFunctionT<Number, Converter, Setting>::vertices( const std::vector<vector_t<Number>>& additionalDirections ) const {
	auto tmp = Converter::toHPolytope( *this, additionalDirections );
	return tmp.vertices();
}

template <typename Number, typename Converter, typename Setting>
Number SupportFunctionT<Number, Converter, Setting>::supremum() const {
	Point<Number> supPoint = content->supremumPoint();
	return Point<Number>::inftyNorm( supPoint );
}

template <typename Number, typename Converter, typename Setting>
SupportFunctionT<Number, Converter, Setting> SupportFunctionT<Number, Converter, Setting>::projectOn( const std::vector<std::size_t>& dimensions ) const {
	// check for full projection
	bool fullProjection = true;
	if ( dimensions.size() == this->dimension() ) {
		for ( unsigned i = 0; i < this->dimension(); ++i ) {
			if ( dimensions.at( i ) != i ) {
				fullProjection = false;
				break;
			}
		}
	} else {
		fullProjection = false;
	}

	if ( !fullProjection ) {
		DEBUG( "hypro.represetations.supportFunction", "No full projection, create." );
		SupportFunctionT<Number, Converter, Setting> res = SupportFunctionT<Number, Converter, Setting>( content->projectOn( dimensions ) );
		return res;
	}
	DEBUG( "hypro.represetations.supportFunction", "Full projection, copy." );
	return *this;
}

template <typename Number, typename Converter, typename Setting>
SupportFunctionT<Number, Converter, Setting> SupportFunctionT<Number, Converter, Setting>::linearTransformation( const matrix_t<Number>& A ) const {
	SupportFunctionT<Number, Converter, Setting> res = SupportFunctionT<Number, Converter, Setting>( content->affineTransformation( A, vector_t<Number>::Zero( A.rows() ) ) );
	return res;
}

template <typename Number, typename Converter, typename Setting>
SupportFunctionT<Number, Converter, Setting> SupportFunctionT<Number, Converter, Setting>::affineTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const {
	SupportFunctionT<Number, Converter, Setting> res = SupportFunctionT<Number, Converter, Setting>( content->affineTransformation( A, b ) );
	return res;
}

template <typename Number, typename Converter, typename Setting>
SupportFunctionT<Number, Converter, Setting> SupportFunctionT<Number, Converter, Setting>::minkowskiSum( const SupportFunctionT<Number, Converter, Setting>& _rhs ) const {
	SupportFunctionT<Number, Converter, Setting> res = SupportFunctionT<Number, Converter, Setting>( content->minkowskiSum( _rhs.content ) );
	return res;
}

template <typename Number, typename Converter, typename Setting>
SupportFunctionT<Number, Converter, Setting> SupportFunctionT<Number, Converter, Setting>::intersect( const SupportFunctionT<Number, Converter, Setting>& _rhs ) const {
	SupportFunctionT<Number, Converter, Setting> res = SupportFunctionT<Number, Converter, Setting>( content->intersect( _rhs.content ) );
	return res;
}

template <typename Number, typename Converter, typename Setting>
SupportFunctionT<Number, Converter, Setting> SupportFunctionT<Number, Converter, Setting>::intersectHalfspace( const Halfspace<Number>& hs ) const {
	matrix_t<Number> mat = matrix_t<Number>( 1, hs.normal().rows() );
	for ( unsigned i = 0; i < hs.normal().rows(); ++i ) {
		mat( 0, i ) = hs.normal()( i );
	}
	vector_t<Number> vec = vector_t<Number>( 1 );
	vec( 0 ) = hs.offset();
	SupportFunctionT<Number, Converter, Setting> res = SupportFunctionT<Number, Converter, Setting>( content->intersect( SupportFunctionT<Number, Converter, Setting>( mat, vec ).content ) );
	return res;
}

template <typename Number, typename Converter, typename Setting>
SupportFunctionT<Number, Converter, Setting> SupportFunctionT<Number, Converter, Setting>::intersectHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {
	SupportFunctionT<Number, Converter, Setting> res = SupportFunctionT<Number, Converter, Setting>( content->intersect( SupportFunctionT<Number, Converter, Setting>( _mat, _vec ).content ) );
	return res;
}

template <typename Number, typename Converter, typename Setting>
bool SupportFunctionT<Number, Converter, Setting>::contains( const Point<Number>& _point ) const {
	return content->contains( _point );
}

template <typename Number, typename Converter, typename Setting>
bool SupportFunctionT<Number, Converter, Setting>::contains( const vector_t<Number>& _point ) const {
	return content->contains( _point );
}

template <typename Number, typename Converter, typename Setting>
bool SupportFunctionT<Number, Converter, Setting>::contains( const SupportFunctionT<Number, Converter, Setting>& rhs, std::size_t directions ) const {
	std::vector<vector_t<Number>> templateDirections = computeTemplate<Number>( this->dimension(), directions );
	for ( const auto& direction : templateDirections ) {
		if ( this->evaluate( direction ).supportValue < rhs.evaluate( direction ).supportValue ) {
			return false;
		}
	}
	return true;
}

template <typename Number, typename Converter, typename Setting>
bool SupportFunctionT<Number, Converter, Setting>::contains( const SupportFunctionT<Number, Converter, Setting>& rhs ) const {
	std::vector<vector_t<Number>> templateDirections = computeTemplate<Number>( this->dimension(), 8 );
	for ( const auto& direction : templateDirections ) {
		if ( this->evaluate( direction ).supportValue < rhs.evaluate( direction ).supportValue ) {
			return false;
		}
	}
	return true;
}

template <typename Number, typename Converter, typename Setting>
SupportFunctionT<Number, Converter, Setting> SupportFunctionT<Number, Converter, Setting>::unite( const SupportFunctionT<Number, Converter, Setting>& _rhs ) const {
	return SupportFunctionT<Number, Converter, Setting>( content->unite( _rhs.content ) );
}

template <typename Number, typename Converter, typename Setting>
SupportFunctionT<Number, Converter, Setting> unite( const std::vector<SupportFunctionT<Number, Converter, Setting>>& _rhs ) {
	std::vector<SupportFunctionContent<Number, Setting>> converted;
	for ( const auto& set : _rhs ) {
		converted.push_back( set->content );
	}
	return SupportFunctionT<Number, Converter, Setting>( SupportFunctionContent<Number, Setting>::unite( converted ) );
}

template <typename Number, typename Converter, typename Setting>
SupportFunctionT<Number, Converter, Setting> SupportFunctionT<Number, Converter, Setting>::scale( const Number& _factor ) const {
	return SupportFunctionT<Number, Converter, Setting>( content->scale( _factor ) );
}

template <typename Number, typename Converter, typename Setting>
std::pair<CONTAINMENT, SupportFunctionT<Number, Converter, Setting>> SupportFunctionT<Number, Converter, Setting>::satisfiesHalfspace( const Halfspace<Number>& rhs ) const {
	// catch zero-constraints separately
	if ( rhs.normal() == vector_t<Number>::Zero( rhs.normal().rows() ) ) {
		return rhs.offset() <= 0 ? std::make_pair( CONTAINMENT::FULL, *this ) : std::make_pair( CONTAINMENT::NO, *this );
	}

	bool limiting = false;
	EvaluationResult<Number> planeEvalRes = content->evaluate( rhs.normal(), false );
	if ( planeEvalRes.errorCode == SOLUTION::INFEAS ) {
		assert( Converter::toHPolytope( *this ).empty() );
		return std::make_pair( CONTAINMENT::NO, *this );
	} else if ( planeEvalRes.supportValue > rhs.offset() ) {
		// the actual object will be limited by the new plane
		limiting = true;
		if ( content->evaluate( -( rhs.normal() ), false ).supportValue < -( rhs.offset() ) ) {
			// the object lies fully outside one of the planes -> return false
			return std::make_pair( CONTAINMENT::NO, this->intersectHalfspace( rhs ) );
		}
	}

	if ( limiting ) {
		auto tmp = this->intersectHalfspace( rhs );
		assert( !tmp.empty() );
		return std::make_pair( CONTAINMENT::PARTIAL, tmp );
	} else {
		return std::make_pair( CONTAINMENT::FULL, *this );
	}
}

template <typename Number, typename Converter, typename Setting>
std::pair<CONTAINMENT, SupportFunctionT<Number, Converter, Setting>> SupportFunctionT<Number, Converter, Setting>::satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {
	DEBUG( "hypro.representations.supportFunction", "Matrix: " << _mat << std::endl
															   << " <= " << _vec );
	if ( _mat.rows() == 0 ) {
		return std::make_pair( CONTAINMENT::FULL, *this );
	}
	assert( _mat.rows() == _vec.rows() );

	// maintain potential result
	std::optional<SupportFunctionT<Number, Converter, Setting>> res;
	std::vector<Eigen::Index> intersectingHalfspaces;
	for ( Eigen::Index rowI = 0; rowI < _mat.rows(); ++rowI ) {
		// catch zero-constraints separately
		if ( _mat.row( rowI ).isZero() ) {
			if ( _vec( rowI ) > 0 ) {
				DEBUG( "hypro.representations.supportFunction", "Row " << rowI << " failed." );
				return std::make_pair( CONTAINMENT::NO, *this );
			}
			continue;
		}
#ifdef HYPRO_LOGGING
		if ( std::find( intersectingHalfspaces.begin(), intersectingHalfspaces.end(), rowI ) != intersectingHalfspaces.end() ) {
			TRACE( "hypro.representations.supportFunction", "Re-evaluation against plane " << rowI );
		} else {
			TRACE( "hypro.representations.supportFunction", "First-time evaluation against plane " << rowI );
		}

#endif

		EvaluationResult<Number> planeEvalRes;
		if ( res ) {
			planeEvalRes = res.value().evaluate( _mat.row( rowI ), false );
		} else {
			planeEvalRes = content->evaluate( _mat.row( rowI ), false );
		}

		if ( planeEvalRes.errorCode == SOLUTION::INFEAS ) {
			DEBUG( "hypro.representations.supportFunction", "Row " << rowI << " failed." );
			return std::make_pair( CONTAINMENT::NO, *this );
		} else if ( !carl::AlmostEqual2sComplement( planeEvalRes.supportValue, _vec( rowI ) ) && planeEvalRes.supportValue > _vec( rowI ) ) {
			// Case where the object will be limited, i.e., the support from the set is larger than the constant part of the constraint in the chosen direction.

			TRACE( "hypro.representations.supportFunction", "Object will be limited, as " << planeEvalRes.supportValue << " > " << _vec( rowI ) );

			// to check for emptiness, compute support in opposite direction.
			Number invDirVal;
			if ( res ) {
				invDirVal = res.value().evaluate( -( _mat.row( rowI ) ), false ).supportValue;
			} else {
				invDirVal = content->evaluate( -( _mat.row( rowI ) ), false ).supportValue;
			}

			TRACE( "hypro.representations.supportFunction", "Potentially fully empty, if " << invDirVal << " < " << -( _vec( rowI ) ) );

			// case where the result is empty, i.e., when the supporting hyperplane in the opposite direction lies outside the current half-space.
			if ( invDirVal < -( _vec( rowI ) ) ) {
				// exact verification in case the values are close to each other
				if ( carl::AlmostEqual2sComplement( Number( -invDirVal ), planeEvalRes.supportValue, 16 ) ) {
					EvaluationResult<Number> secndPosEval;
					if ( res ) {
						secndPosEval = res.value().evaluate( _mat.row( rowI ), true );
					} else {
						secndPosEval = content->evaluate( _mat.row( rowI ), true );
					}
					if ( secndPosEval.supportValue > _vec( rowI ) ) {
						EvaluationResult<Number> secndNegEval;
						if ( res ) {
							secndNegEval = res.value().evaluate( -( _mat.row( rowI ) ), true );
						} else {
							secndNegEval = content->evaluate( -( _mat.row( rowI ) ), true );
						}
						if ( secndNegEval.supportValue < -( _vec( rowI ) ) ) {
							TRACE( "hypro.representations.supportFunction", "fullyOutside" );
							// the object lies fully outside one of the planes -> return false
							DEBUG( "hypro.representations.supportFunction", "Row " << rowI << " failed -- fully outside." );
							return std::make_pair( CONTAINMENT::NO, this->intersectHalfspaces( _mat, _vec ) );
						}
					}
				} else {
					// the values are far enough away from each other to make this result a false negative.
					TRACE( "hypro.representations.supportFunction", "fullyOutside, as " << invDirVal << " >= " << -( _vec( rowI ) ) );
					// the object lies fully outside one of the planes -> return false
					DEBUG( "hypro.representations.supportFunction", "Row " << rowI << " failed." );
					return std::make_pair( CONTAINMENT::NO, this->intersectHalfspaces( _mat, _vec ) );
				}
			} else {
				// as we do multiple checks, only add if not already contained.
				if ( std::find( intersectingHalfspaces.begin(), intersectingHalfspaces.end(), rowI ) == intersectingHalfspaces.end() ) {
					// update cache
					intersectingHalfspaces.push_back( rowI );
					// object is not empty. Create intersection object, and use this to add all limiting planes.
					if ( res ) {
						// the result, whose right-hand-side are the added planes
						intersectionContent<Number, Setting>* intersection = res.value().rGetContent()->rIntersectionParameters();
						// add constraint to right-hand-side
						appendRow( intersection->rhs->rPolytope()->rMatrix(), vector_t<Number>( _mat.row( rowI ) ) );
						appendRow( intersection->rhs->rPolytope()->rVector(), _vec( rowI ) );

						TRACE( "hypro.representations.supportFunction", "Add plane at index " << rowI << " to intersection object." );
					} else {
						TRACE( "hypro.representations.supportFunction", "Initialize intersection object with plane at index " << rowI );
						// use override reduction to enforce, that the resulting support function is of type polytope to be able to add halfspaces, this is currently not supported for boxes.
						matrix_t<Number> constraint = _mat.row( rowI );
						vector_t<Number> constant = _vec.row( rowI );
						res = SupportFunctionT<Number, Converter, Setting>( content->intersect( SupportFunctionT<Number, Converter, Setting>( constraint, constant, true ).content ) );
					}

					// finally, reset rowI to zero (to re-check all other constraints), as the limitation might have rendered the object emtpy in combination with other constraints.
					rowI = 0;
				}
			}
		}
	}

	// case: object is fully contained
	if ( !res.has_value() ) {
		return std::make_pair( CONTAINMENT::FULL, *this );
	} else {
#ifdef HYPRO_LOGGING
		intersectionContent<Number, Setting>* intersection = res.value().rGetContent()->rIntersectionParameters();
		TRACE( "hypro.representations.supportFunction", "Final intersection constraints " << intersection->rhs->rPolytope()->constraints() );
		TRACE( "hypro.representations.supportFunction", "Final intersection constants " << intersection->rhs->rPolytope()->constants() );
#endif
		CONTAINMENT containmentState = res.value().empty() ? CONTAINMENT::NO : CONTAINMENT::PARTIAL;
		return std::make_pair( containmentState, res.value() );
	}
}

template <typename Number, typename Converter, typename Setting>
void SupportFunctionT<Number, Converter, Setting>::reduceRepresentation() {
	// create polyhedral approximation using a template
	if ( Setting::REDUCE_TO_BOX ) {
		// force sampling - not necessary if stored template was using 4 directions.
		this->evaluateTemplate( 4, true );
		content = std::move( SupportFunctionContent<Number, Setting>::create( SF_TYPE::BOX, mMatrix, mVector ) );
	} else {
		this->evaluateTemplate();
		content = std::move( SupportFunctionContent<Number, Setting>::create( SF_TYPE::POLY, mMatrix, mVector ) );
	}
}

template <typename Number, typename Converter, typename Setting>
bool SupportFunctionT<Number, Converter, Setting>::empty() const {
	if ( mEmptyState == SETSTATE::UNKNOWN ) {
		mEmptyState = content->empty() ? SETSTATE::EMPTY : SETSTATE::NONEMPTY;
	}
	assert( mEmptyState != SETSTATE::UNIVERSAL );
	return mEmptyState == SETSTATE::EMPTY;
}

template <typename Number, typename Converter, typename Setting>
void SupportFunctionT<Number, Converter, Setting>::print() const {
	return content->print();
}

template <typename Number, typename Converter, typename Setting>
void SupportFunctionT<Number, Converter, Setting>::swap( SupportFunctionT<Number, Converter, Setting>& first, SupportFunctionT<Number, Converter, Setting>& second ) {
	first.content.swap( second.content );
}

template <typename Number, typename Converter, typename Setting>
void SupportFunctionT<Number, Converter, Setting>::forceLinTransReduction() {
	content->forceLinTransReduction();
}

template <typename Number, typename Converter, typename Setting>
std::vector<std::size_t> SupportFunctionT<Number, Converter, Setting>::collectProjections() const {
	assert( content->checkTreeValidity() );
	return content->collectProjections();
}

template <typename Number, typename Converter, typename Setting>
const SupportFunctionT<Number, Converter, Setting>& SupportFunctionT<Number, Converter, Setting>::evaluateTemplate( std::size_t directionCount, bool force ) const {
	if ( !mTemplateSet || force ) {
		std::vector<vector_t<Number>> templateDirections = computeTemplate<Number>( this->dimension(), directionCount );

		matrix_t<Number> templateDirectionMatrix = combineRows( templateDirections );

		//lets the support function evaluate the offset of the halfspaces for each direction
		std::vector<EvaluationResult<Number>> offsets = this->multiEvaluate( templateDirectionMatrix );

		std::vector<std::size_t> boundedConstraints;
		for ( unsigned offsetIndex = 0; offsetIndex < offsets.size(); ++offsetIndex ) {
			if ( offsets[offsetIndex].errorCode != SOLUTION::INFTY ) {
				boundedConstraints.push_back( offsetIndex );
			}
		}
		matrix_t<Number> constraints = matrix_t<Number>( boundedConstraints.size(), this->dimension() );
		vector_t<Number> constants = vector_t<Number>( boundedConstraints.size() );
		Eigen::Index pos = Eigen::Index( boundedConstraints.size() ) - 1;
		while ( !boundedConstraints.empty() ) {
			constraints.row( pos ) = templateDirectionMatrix.row( boundedConstraints.back() );
			constants( pos ) = offsets[boundedConstraints.back()].supportValue;
			boundedConstraints.pop_back();
			--pos;
		}

		mMatrix = constraints;
		mVector = constants;
		mTemplateSet = true;
	}
	return *this;
}

}  // namespace hypro
