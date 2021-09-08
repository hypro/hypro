/*
 * IntersectHalfspaceOp.h
 *
 * A RootGrowNode that represents a scaling operation in the tree of operations representing a SupportFunction.
 * Every IntersectHalfspaceOp knows its scaling factor
 *
 * @author Stefan Schupp
 * @author Phillip Tse
 */

#pragma once

#include "../../config.h"
#include "RootGrowNode.h"

namespace hypro {

// Forward Declaration
template <typename Number, typename Converter, typename Setting>
class SupportFunctionNewT;

template <typename Number, typename Converter, typename Setting>
class RootGrowNode;

// A data struct for IntersectHalfspaceOp, containing all needed info to construct a IntersectHalfspaceOp from it. No child info is saved.
template <typename Number>
struct IntersectHalfspaceData : public RGNData {
	Halfspace<Number> hspace;
	IntersectHalfspaceData( const Halfspace<Number>& h )
		: hspace( h ) {}
};

template <typename Number, typename Converter, typename Setting>
class IntersectHalfspaceOp : public RootGrowNode<Number, Converter, Setting> {
  private:
	////// Usings

	using PointerVec = typename RootGrowNode<Number, Converter, Setting>::PointerVec;

	////// General Interface

	SFNEW_TYPE type = SFNEW_TYPE::INTERSECTHSPACEOP;
	unsigned originCount;
	PointerVec mChildren;
	std::size_t mDimension;

	////// Members for this class

	Halfspace<Number> hspace;

  public:
	////// Constructors & Destructors

	IntersectHalfspaceOp() = delete;

	IntersectHalfspaceOp( const SupportFunctionNewT<Number, Converter, Setting>& origin, const Halfspace<Number>& h )
		: originCount( 1 )
		, mChildren( PointerVec( 1, nullptr ) )
		, mDimension( origin.dimension() )
		, hspace( h ) {
		origin.addOperation( this );
	}

	IntersectHalfspaceOp( const IntersectHalfspaceData<Number>& d )
		: originCount( 1 )
		, mChildren( PointerVec( { 1, nullptr } ) )
		//, mDimension(d.origin->getDimension())
		, hspace( d.hspace ) {}

	~IntersectHalfspaceOp() {}

	////// Getters & Setters

	SFNEW_TYPE getType() const { return type; }
	unsigned getOriginCount() const { return originCount; }
	std::size_t getDimension() const { return mDimension; }
	Halfspace<Number> getHalfspace() const { return hspace; }
	RGNData* getData() const { return new IntersectHalfspaceData<Number>( hspace ); }
	void setDimension( const std::size_t d ) { mDimension = d; }

	////// RootGrowNode Interface

	// does nothing
	matrix_t<Number> transform( const matrix_t<Number>& param ) const {
		return param;
	}

	// should not be reachable
	std::vector<EvaluationResult<Number>> compute( const matrix_t<Number>&, bool ) const {
		assert( false && "IntersectHalfspaceOp::compute should not be called" );
		return std::vector<EvaluationResult<Number>>();
	}

	// Method described in LeGuernic's and Girard's paper about support functions, but extended to halfspaces and not only hyperplanes
	std::vector<EvaluationResult<Number>> aggregate( std::vector<std::vector<EvaluationResult<Number>>>& resultStackBack, const matrix_t<Number>& directions ) const {
		COUNT( "IntersectHalfspaceOp::aggregate" );
		TRACE( "hypro.representations.supportFunction", ": INTERSECT HSPACE, accumulate results." );
		assert( resultStackBack.size() == 1 );
		std::vector<EvaluationResult<Number>> accumulatedRes;
		for ( int i = 0; i < directions.rows(); ++i ) {
			// If direction not similar to halfspace normal, then use halfspace evaluate
			if ( hspace.normal().dot( directions.row( i ) ) < 0 ) {
				accumulatedRes.push_back( resolveEvaluationResults( resultStackBack.front().at( i ), directions.row( i ) ) );
			} else {
				accumulatedRes.push_back( leGuernicFast( vector_t<Number>( directions.row( i ).transpose() ) ) );
			}
		}
		return accumulatedRes;
	}

	// Take the smaller evaluation result between the one from child and the hspace
	EvaluationResult<Number> resolveEvaluationResults( const EvaluationResult<Number>& other, const vector_t<Number>& dir ) const {
		COUNT( "IntersectHalfspaceOp::resolveEvaluationResults" );
		auto hspaceEval = hspace.evaluate( dir, true );
		if ( other.errorCode == SOLUTION::FEAS ) {
			// Since the first result we compare with can still be infty
			if ( hspaceEval.errorCode == SOLUTION::INFTY ) {
				hspaceEval.errorCode = SOLUTION::FEAS;
				hspaceEval.supportValue = other.supportValue;
				hspaceEval.optimumValue = other.optimumValue;
			} else {
				hspaceEval.errorCode = SOLUTION::FEAS;
				hspaceEval.supportValue = other.supportValue < hspaceEval.supportValue ? other.supportValue : hspaceEval.supportValue;
				hspaceEval.optimumValue = other.optimumValue < hspaceEval.optimumValue ? other.optimumValue : hspaceEval.optimumValue;
			}
		}
		return hspaceEval;
	}

	// Computes the support value of the intersection between our child and the member halfspace in direction "direction"
	EvaluationResult<Number> leGuernic( const vector_t<Number>& direction ) const {
		COUNT( "IntersectHalfspaceOp::leGuernic" );

		// Projection matrix - normalize columns then put them into matrix
		// NOTE: This is the already transposed matrix M^T
		matrix_t<Number> projMat = matrix_t<Number>::Zero( direction.rows(), 2 );
		projMat.col( 0 ) = hspace.normal().transpose();
		projMat.col( 1 ) = direction.transpose();

		// Wiggle vector and wiggle angle
		Number wiggleAngle = 0.0;
		vector_t<Number> wiggleVec = vector_t<Number>::Zero( 2 );
		wiggleVec( 0 ) = Number( std::cos( carl::toDouble( wiggleAngle ) ) );
		wiggleVec( 1 ) = Number( std::sin( carl::toDouble( wiggleAngle ) ) );

		// Golden section search for the value f
		Number maximumAngle = PI_UP;
		Number tolerance = 0.001;
		Number goldenRatio = ( std::sqrt( 5 ) + 1 ) / 2;
		Number upper = maximumAngle - ( ( maximumAngle - wiggleAngle ) / goldenRatio );
		Number lower = wiggleAngle + ( ( maximumAngle - wiggleAngle ) / goldenRatio );
		EvaluationResult<Number> evalInProjectedWiggleDir;
		SupportFunctionNewT<Number, Converter, Setting> childSF( this->getChildren().at( 0 ) );

		// Get absolute value of difference
		Number absDiff = upper - lower;
		if ( absDiff <= 0 ) {
			absDiff *= Number( -1 );
		}

		while ( absDiff > tolerance ) {
			COUNT( "IntersectHalfspaceOp::wobbleIterations" );

			// Compute evaluation value for upper bound
			wiggleVec( 0 ) = Number( std::cos( carl::toDouble( upper ) ) );
			wiggleVec( 1 ) = Number( std::sin( carl::toDouble( upper ) ) );
			evalInProjectedWiggleDir = childSF.evaluate( projMat * wiggleVec, true );
			COUNT( "IntersectHalfspaceOp::leGuernic::evaluate" );
			Number heightOfUpper = ( evalInProjectedWiggleDir.supportValue - hspace.offset() * Number( std::cos( carl::toDouble( upper ) ) ) ) / Number( std::sin( carl::toDouble( upper ) ) );

			// Compute evaluation value for lower bound
			wiggleVec( 0 ) = Number( std::cos( carl::toDouble( lower ) ) );
			wiggleVec( 1 ) = Number( std::sin( carl::toDouble( lower ) ) );
			evalInProjectedWiggleDir = childSF.evaluate( projMat * wiggleVec, true );
			COUNT( "IntersectHalfspaceOp::leGuernic::evaluate" );
			Number heightOfLower = ( evalInProjectedWiggleDir.supportValue - hspace.offset() * Number( std::cos( carl::toDouble( lower ) ) ) ) / Number( std::sin( carl::toDouble( lower ) ) );

			// Reduce search space to where minimum of evaluation values seems to be
			if ( heightOfLower < heightOfUpper ) {
				wiggleAngle = upper;
			} else {
				maximumAngle = lower;
			}

			// Update upper and lower bound
			upper = maximumAngle - ( ( maximumAngle - wiggleAngle ) / goldenRatio );
			lower = wiggleAngle + ( ( maximumAngle - wiggleAngle ) / goldenRatio );
			absDiff = upper - lower;
			if ( absDiff <= 0 ) {
				absDiff *= Number( -1 );
			}
		}
		// Resulting angle is the average of maximumAngle and wiggleAngle
		Number resultAngle = ( maximumAngle + wiggleAngle ) / 2;
		assert( 0 <= resultAngle && resultAngle <= PI_UP );
		wiggleVec( 0 ) = Number( std::cos( carl::toDouble( resultAngle ) ) );
		wiggleVec( 1 ) = Number( std::sin( carl::toDouble( resultAngle ) ) );
		evalInProjectedWiggleDir = childSF.evaluate( projMat * wiggleVec, true );
		COUNT( "IntersectHalfspaceOp::leGuernic::evaluate" );
		Number heightOfResult = ( evalInProjectedWiggleDir.supportValue - hspace.offset() * Number( std::cos( carl::toDouble( resultAngle ) ) ) ) / Number( std::sin( carl::toDouble( resultAngle ) ) );
		// NOTE: This evaluation result does not return an optimal value
		return EvaluationResult<Number>( heightOfResult, SOLUTION::FEAS );
	}

	// Golden section search where the amount of evaluations made is halved
	// NOTE: algorithm idea is from wikipedia "Golden section search", the variable names in the comments are mappings to the variable names in the article
	EvaluationResult<Number> leGuernicFast( const vector_t<Number>& direction ) const {
		COUNT( "IntersectHalfspaceOp::leGuernic" );

		// Projection matrix - normalize columns then put them into matrix
		// NOTE: This is the already transposed matrix M^T
		matrix_t<Number> projMat( direction.rows(), 2 );
		projMat.col( 0 ) = hspace.normal().transpose();
		projMat.col( 1 ) = direction.transpose();

		// Wiggle vector and wiggle angle
		Number wiggleAngle = 0.0;
		vector_t<Number> wiggleVec( 2 );

		// Golden section search for the value f
		Number maximumAngle = PI_UP;
		const Number tolerance = 0.001;
		const Number goldenRatioInv = ( std::sqrt( 5 ) - 1 ) / 2;
		const Number goldenRatioInv2 = ( 3 - std::sqrt( 5 ) ) / 2;
		assert( wiggleAngle < maximumAngle );
		carl::Interval<Number> resInterval( wiggleAngle, maximumAngle );  // upper = b, lower = a

		// Determine difference
		Number h = PI_UP;

		// Compute steps needed to acquire tolerance
		unsigned steps = static_cast<unsigned>( carl::ceil( std::log( carl::toDouble( tolerance ) / carl::toDouble( h ) ) / std::log( carl::toDouble( goldenRatioInv ) ) ) );

		// Compute upper (c) and lower bound (d)
		Number upper = resInterval.lower() + goldenRatioInv2 * h;
		Number lower = resInterval.lower() + goldenRatioInv * h;

		// Compute upper height yc
		EvaluationResult<Number> evalInProjectedWiggleDir;
		SupportFunctionNewT<Number, Converter, Setting> childSF( this->getChildren().at( 0 ) );
		wiggleVec( 0 ) = Number( std::cos( carl::toDouble( upper ) ) );
		wiggleVec( 1 ) = Number( std::sin( carl::toDouble( upper ) ) );
		evalInProjectedWiggleDir = childSF.evaluate( projMat * wiggleVec, true );
		COUNT( "IntersectHalfspaceOp::leGuernic::evaluate" );
		Number heightOfUpper = ( evalInProjectedWiggleDir.supportValue - hspace.offset() * Number( std::cos( carl::toDouble( upper ) ) ) ) / Number( std::sin( carl::toDouble( upper ) ) );

		// Compute lower height yd
		wiggleVec( 0 ) = Number( std::cos( carl::toDouble( lower ) ) );
		wiggleVec( 1 ) = Number( std::sin( carl::toDouble( lower ) ) );
		evalInProjectedWiggleDir = childSF.evaluate( projMat * wiggleVec, true );
		COUNT( "IntersectHalfspaceOp::leGuernic::evaluate" );
		Number heightOfLower = ( evalInProjectedWiggleDir.supportValue - hspace.offset() * Number( std::cos( carl::toDouble( lower ) ) ) ) / Number( std::sin( carl::toDouble( lower ) ) );

		// Update interval
		for ( unsigned i = 0; i < steps; ++i ) {
			COUNT( "IntersectHalfspaceOp::wobbleIterations" );
			if ( heightOfUpper < heightOfLower ) {
				resInterval.setUpper( lower );
				lower = upper;
				heightOfLower = heightOfUpper;
				h = goldenRatioInv * h;
				upper = resInterval.lower() + goldenRatioInv2 * h;
				wiggleVec( 0 ) = Number( std::cos( carl::toDouble( upper ) ) );
				wiggleVec( 1 ) = Number( std::sin( carl::toDouble( upper ) ) );
				evalInProjectedWiggleDir = childSF.evaluate( projMat * wiggleVec, true );
				COUNT( "IntersectHalfspaceOp::leGuernic::evaluate" );
				heightOfUpper = ( evalInProjectedWiggleDir.supportValue - hspace.offset() * Number( std::cos( carl::toDouble( upper ) ) ) ) / Number( std::sin( carl::toDouble( upper ) ) );
			} else {
				resInterval.setLower( upper );
				upper = lower;
				heightOfUpper = heightOfLower;
				h = goldenRatioInv * h;
				lower = resInterval.lower() + goldenRatioInv * h;
				wiggleVec( 0 ) = Number( std::cos( carl::toDouble( lower ) ) );
				wiggleVec( 1 ) = Number( std::sin( carl::toDouble( lower ) ) );
				evalInProjectedWiggleDir = childSF.evaluate( projMat * wiggleVec, true );
				COUNT( "IntersectHalfspaceOp::leGuernic::evaluate" );
				heightOfLower = ( evalInProjectedWiggleDir.supportValue - hspace.offset() * Number( std::cos( carl::toDouble( lower ) ) ) ) / Number( std::sin( carl::toDouble( lower ) ) );
			}
		}

		return EvaluationResult<Number>( ( ( heightOfLower + heightOfUpper ) / 2 ), vector_t<Number>::Zero( getDimension() ), SOLUTION::FEAS );
	}

	// Checks emptiness
	bool empty( const std::vector<bool>& childrenEmpty ) const {
		assert( childrenEmpty.size() == 1 );
		if ( RootGrowNode<Number, Converter, Setting>::mEmptyState != SETSTATE::UNKNOWN ) {
			return ( RootGrowNode<Number, Converter, Setting>::mEmptyState == SETSTATE::EMPTY );
		}
		if ( childrenEmpty.front() ) {
			RootGrowNode<Number, Converter, Setting>::mEmptyState = SETSTATE::EMPTY;
			return true;
		}
		SupportFunctionNewT<Number, Converter, Setting> child( this->getChildren().at( 0 ) );
		auto posNormalEval = child.evaluate( hspace.normal(), true );
		auto negNormalEval = child.evaluate( -hspace.normal(), true );
		if ( -negNormalEval.supportValue <= hspace.offset() && hspace.offset() <= posNormalEval.supportValue ) {
			RootGrowNode<Number, Converter, Setting>::mEmptyState = SETSTATE::NONEMPTY;
			return false;
		}
		RootGrowNode<Number, Converter, Setting>::mEmptyState = SETSTATE::EMPTY;
		return true;
	}

	// TODO: Needs to be fixed. How to compute supremum point if it was cut off?
	// NOTE: Doesn't matter, function seems to be obsolete
	Point<Number> supremumPoint( std::vector<Point<Number>>& points ) const {
		assert( points.size() == 1 );
		if ( hspace.contains( points.front() ) ) {
			return points.front();
		}
		SupportFunctionNewT<Number, Converter, Setting> child( this->getChildren().at( 0 ) );
		auto childEval = child.evaluate( hspace.normal(), true );
		auto hspaceEval = resolveEvaluationResults( childEval, hspace.normal() );
		if ( hspaceEval.errorCode == SOLUTION::FEAS ) {
			// Gets an optimal one, but not a supremum
			return Point<Number>( hspaceEval.optimumValue );
		}
		return Point<Number>::Zero( points.front().dimension() );
	}

	vector_t<Number> reverseOp( const vector_t<Number>& point ) const {
		return point;
	}

	bool contains( const std::vector<bool>& v, const vector_t<Number>& point ) const {
		assert( v.size() == 1 );
		if ( v.front() && hspace.contains( point ) )
			return true;
		return false;
	}
};

}  // namespace hypro
