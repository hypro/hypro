/*
 * ProjectOp.h
 *
 * A RootGrowNode that represents a projection operation in the tree of operations representing a SupportFunction.
 * Every ProjectOp knows the dimensions that should be kept.
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

// A data struct for ProjectOp, containing all needed info to construct a ProjectOp from it. No child info is saved.
struct ProjectData : public RGNData {
	std::vector<std::size_t> dimensions;
	ProjectData( const std::vector<std::size_t>& dims )
		: dimensions( dims ) {}
};

template <typename Number, typename Converter, typename Setting>
class ProjectOp : public RootGrowNode<Number, Converter, Setting> {
  private:
	////// Usings

	using PointerVec = typename RootGrowNode<Number, Converter, Setting>::PointerVec;

	////// General Interface

	SFNEW_TYPE type = SFNEW_TYPE::PROJECTOP;
	unsigned originCount;
	PointerVec mChildren;
	std::size_t mDimension;

	////// Members for this class

	std::vector<std::size_t> dimensions;  // Vector of all indices that should not be projected to 0

  public:
	////// Constructors & Destructors

	ProjectOp() = delete;

	ProjectOp( const SupportFunctionNewT<Number, Converter, Setting>& origin, const std::vector<std::size_t>& dims )
		: originCount( 1 )
		, mChildren( PointerVec( 1, nullptr ) )
		, mDimension( origin.dimension() )
		, dimensions( dims ) {
		origin.addOperation( this );
	}

	ProjectOp( const ProjectData& d )
		: originCount( 1 )
		, mChildren( PointerVec( { 1, nullptr } ) )
		//, mDimension(d.origin->getDimension())
		, dimensions( d.dimensions ) {}

	~ProjectOp() {}

	////// Getters & Setters

	SFNEW_TYPE getType() const override { return type; }
	unsigned getOriginCount() const override { return originCount; }
	std::size_t getDimension() const override { return mDimension; }
	std::vector<std::size_t> getDimensions() const { return dimensions; }
	RGNData* getData() const override { return new ProjectData( dimensions ); }
	void setDimension( const std::size_t d ) override { mDimension = d; }

	////// RootGrowNode Interface

	// Unwantend dimensions are set to 0, keep all other entries in param
	matrix_t<Number> transform( const matrix_t<Number>& param ) const override {
		matrix_t<Number> projectedParameters = matrix_t<Number>::Zero( param.rows(), param.cols() );
		Eigen::Index entryIndex = 0;
		for ( const auto& entry : dimensions ) {
			TRACE( "hypro.representations.supportFunction", "Entry: " << entry )
			if ( int( entry ) < param.cols() ) {
				projectedParameters.col( entry ) = param.col( entry );
				++entryIndex;
			}
		}
		assert( std::size_t( entryIndex ) == dimensions.size() );
		return projectedParameters;
	}

	// should not be reachable
	std::vector<EvaluationResult<Number>> compute( const matrix_t<Number>&, bool ) const override {
		assert( false && "ProjectOp::compute should not be called" );
		return std::vector<EvaluationResult<Number>>();
	}

	// Given the results, return vector of evaluation results (here only first place needed, since unary op)
	std::vector<EvaluationResult<Number>> aggregate( std::vector<std::vector<EvaluationResult<Number>>>& resultStackBack, const matrix_t<Number>& ) const override {
		assert( resultStackBack.size() == 1 );
		return resultStackBack.front();
	}

	// Checks emptiness
	bool empty( const std::vector<bool>& childrenEmpty ) const override {
		assert( childrenEmpty.size() == 1 );
		if ( dimensions.empty() || childrenEmpty.front() ) return true;
		return false;
	}

	// Set all unwanted dimensions to zero
	Point<Number> supremumPoint( std::vector<Point<Number>>& points ) const override {
		assert( points.size() == 1 );
		vector_t<Number> tmp = vector_t<Number>::Zero( points.front().dimension() );
		for ( const auto& entry : dimensions ) {
			if ( entry < points.front().dimension() ) {
				tmp( entry ) = points.front().at( entry );
			}
		}
		return Point<Number>( tmp );
	}

	// TODO: if wildcard values in vectors avaiable, then implement smth correct here
	vector_t<Number> reverseOp( const vector_t<Number>& point ) const override {
		return point;
	}

	// If child contains p, then projected version will contain it too
	bool contains( const std::vector<bool>& v, const vector_t<Number>& /*point*/ ) const override {
		assert( v.size() == 1 );
		if ( v.front() ) return true;
		return false;
	}

	// Return all dimensions that are in "dims" and also in "dimensions"
	std::vector<std::size_t> intersectDims( const std::vector<std::vector<std::size_t>>& dims ) const override {
		assert( dims.size() == 1 );
		std::vector<std::size_t> res;
		for ( auto& d : dims.front() ) {
			for ( auto& dimToKeep : dimensions ) {
				if ( d == dimToKeep ) {
					res.push_back( d );
				}
			}
		}
		return res;
	}
};

}  // namespace hypro
