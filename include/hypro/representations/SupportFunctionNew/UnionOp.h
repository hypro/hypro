/*
 * UnionOp.h
 *
 * A RootGrowNode that represents a Union operation in the tree of operations representing a SupportFunction.
 *
 * @author Stefan Schupp
 * @author Phillip Tse
 */

#pragma once

#include "RootGrowNode.h"

namespace hypro {

// Forward Declaration
template <typename Number, typename Converter, typename Setting>
class SupportFunctionNewT;

template <typename Number, typename Converter, typename Setting>
class RootGrowNode;

// Specialized subclass for sums as example of a binary operator
template <typename Number, typename Converter, typename Setting>
class UnionOp : public RootGrowNode<Number, Converter, Setting> {
  private:
	////// General Interface

	SFNEW_TYPE type = SFNEW_TYPE::UNIONOP;
	unsigned originCount = 2;
	std::size_t mDimension;
	std::vector<std::shared_ptr<RootGrowNode<Number, Converter, Setting>>> mChildren;

	////// Special members of this class

  public:
	////// Constructors & Destructors

	UnionOp() = delete;

	UnionOp( const SupportFunctionNewT<Number, Converter, Setting>& lhs, const SupportFunctionNewT<Number, Converter, Setting>& rhs )
		: mDimension( lhs.dimension() ) {
		assert( lhs.dimension() == rhs.dimension() || lhs.empty() || rhs.empty() );
		lhs.addOperation( this, std::vector<SupportFunctionNewT<Number, Converter, Setting>>{ rhs } );
		// update and set empty-cache
		if ( lhs.empty() && rhs.empty() ) {
			RootGrowNode<Number, Converter, Setting>::mEmptyState = SETSTATE::EMPTY;
		}
	}

	UnionOp( const SupportFunctionNewT<Number, Converter, Setting>& lhs, const std::vector<SupportFunctionNewT<Number, Converter, Setting>>& rhs )
		: mDimension( lhs.dimension() ) {
#ifndef NDEBUG
		for ( const auto& sf : rhs ) {
			assert( lhs.dimension() == sf.dimension() || lhs.empty() || sf.empty() );
		}
#endif
		lhs.addOperation( this, rhs );
		// check for rhs is too expensive at the moment -> update usage of cache everywhere, then this is fine.
	}

	UnionOp( const RGNData& ) {}

	~UnionOp() {}

	////// Getters and Setters

	SFNEW_TYPE getType() const override { return type; }
	unsigned getOriginCount() const override { return originCount; }
	std::size_t getDimension() const override { return mDimension; }
	RGNData* getData() const override { return new RGNData(); }
	void setDimension( const std::size_t d ) override { mDimension = d; }

	////// RootGrowNode Interface

	// Does nothing
	matrix_t<Number> transform( const matrix_t<Number>& param ) const override {
		return param;
	}

	// Should not be reached
	std::vector<EvaluationResult<Number>> compute( const matrix_t<Number>&, bool ) const override {
		std::cout << "USED COMPUTE FROM UnionOp SUBCLASS.\n";
		assert( false );
		return std::vector<EvaluationResult<Number>>();
	}

	// Given two or more result vecs, get maximum
	std::vector<EvaluationResult<Number>> aggregate( std::vector<std::vector<EvaluationResult<Number>>>& resultStackBack, const matrix_t<Number>& ) const override {
		TRACE( "hypro.representations.supportFunction", ": UNITE, accumulate results." )
		assert( resultStackBack.size() >= 2 );
		std::vector<EvaluationResult<Number>> accumulatedResult = resultStackBack.front();
		for ( auto resIt = resultStackBack.begin(); resIt != resultStackBack.end(); ++resIt ) {
			for ( unsigned resultId = 0; resultId < accumulatedResult.size(); ++resultId ) {
				if ( ( *resIt )[resultId].errorCode == SOLUTION::INFEAS ) {
					accumulatedResult[resultId] = ( *resIt )[resultId];
					break;
				} else if ( ( *resIt )[resultId].errorCode == SOLUTION::INFTY ) {
					( *resIt )[resultId].supportValue = 1;
					accumulatedResult[resultId] = ( *resIt )[resultId];
					// std::cout << "UnionOp::aggregate, entry was infty" << std::endl;
				} else {
					assert( ( *resIt )[resultId].errorCode == SOLUTION::FEAS );
					accumulatedResult[resultId] = ( *resIt )[resultId] > accumulatedResult[resultId] ? ( *resIt )[resultId] : accumulatedResult[resultId];
					// std::cout << "UnionOp::aggregate, after choosing mas between " << accumulatedResult[resultId] << " and  " << ( *resIt )[resultId] << " r is:" << accumulatedResult[resultId] << std::endl;
				}
			}
		}
		return accumulatedResult;
	}

	// Only empty, if all children are empty since union of nonempty smth with empty set equals smth
	bool empty( const std::vector<bool>& childrenEmpty ) const override {
		for ( const auto childEmpty : childrenEmpty ) {
			if ( !childEmpty ) return false;
		}
		return true;
	}

	// Transform the supremum
	Point<Number> supremumPoint( std::vector<Point<Number>>& points ) const override {
		assert( points.size() > 0 );
		Point<Number> biggestInftyNorm = points.front();
		for ( const auto& p : points ) {
			if ( p.dimension() == 0 ) return p;
			biggestInftyNorm = Point<Number>::inftyNorm( biggestInftyNorm ) > Point<Number>::inftyNorm( p ) ? biggestInftyNorm : p;
		}
		return biggestInftyNorm;
	}

	// Only return true if at least one child contained the point before
	bool contains( const std::vector<bool>& v, const vector_t<Number>& /*point*/ ) const override {
		for ( const auto& containedInChild : v ) {
			if ( containedInChild ) return true;
		}
		return false;
	}

	// Erases all dimensions from a copy of dimensions that are denoted in dims
	std::vector<std::size_t> intersectDims( const std::vector<std::vector<std::size_t>>& dims ) const override {
		// we create the intersection of all results. Therefore we iterate over the first vector and check the other
		// result vectors, if the respective element is contained. Iterating over the first is sufficient, as elements
		// not in the first vector will not be in the intersection anyways.
		std::vector<std::size_t> accumulatedResult;
		for ( unsigned pos = 0; pos < dims.begin()->size(); ++pos ) {
			std::size_t element = dims.begin()->at( pos );
			bool elementInAllVectors = true;
			for ( unsigned resIndex = 1; resIndex < dims.size(); ++resIndex ) {
				if ( std::find( dims.at( resIndex ).begin(), dims.at( resIndex ).end(), element ) == dims.at( resIndex ).end() ) {
					elementInAllVectors = false;
					break;
				}
			}
			if ( elementInAllVectors ) {
				// if this is a projection, we need to remove non-projected dimensions -> we could not have been in a projection since
				// since this part of the function was only executed if a node had more than 2 children
				accumulatedResult.emplace_back( element );
			}
		}
		return accumulatedResult;
	}
};

}  // namespace hypro
