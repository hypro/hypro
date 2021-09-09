#pragma once

#include "../../datastructures/Point.h"
#include "../../util/linearOptimization/Optimizer.h"
#include "Cone.h"

#include <carl/formula/Constraint.h>
#include <cassert>

namespace hypro {

/**
 * @brief      Class for a polytopal fan.
 *
 * @tparam     Number  The used number type.
 */
template <typename Number>
class Fan {
  public:
	using cones = std::vector<const Cone<Number>*>;

  private:
	cones mCones;
	unsigned mDimension;

  public:
	Fan()
		: mCones()
		, mDimension() {}

	~Fan() { mCones.clear(); }

	Fan( const Fan& _orig )
		: mCones( _orig.get() )
		, mDimension( _orig.dimension() ) {}

	/*
	 * Getters & setters
	 */

	const cones& get() const { return mCones; }

	const Cone<Number>* get( unsigned _index ) const {
		assert( _index < mCones.size() );
		return mCones.at( _index );
	}

	unsigned dimension() const { return mDimension; }

	unsigned size() const { return mCones.size(); }

	void add( const Cone<Number>* _cone ) {
		mCones.push_back( _cone );
		mDimension = mDimension < _cone->dimension() ? _cone->dimension() : mDimension;
	}

	const Cone<Number>* containingCone( const Point<Number>& _vector ) const {
		Optimizer<Number> opt{};

		// set up glpk
		glp_prob* cones;
		cones = glp_create_prob();
		glp_set_obj_dir( cones, GLP_MAX );

		typename Cone<Number>::vectors vectors;
		for ( auto& cone : mCones ) {
			vectors.insert( vectors.end(), cone.begin(), cone.end() );
		}
		unsigned numPlanes = vectors.size();
		// unsigned elements = this->mDimension * numPlanes;

		matrix_t<Number> constraints = matrix_t<Number>::Zero( this->mDimension, numPlanes );

		for ( unsigned i = 1; i <= this->mDimension; ++i ) {
			for ( unsigned j = 1; j <= numPlanes; ++j ) {
				constraints( i, j ) = vectors.at( j ).at( i );
			}
		}

		opt.checkConsistency();
		// TODO: output and stuff.
	}

	Fan<Number> operator=( const Fan<Number>& _rhs ) {
		/* if( this != &rhs )
		 {
			 Fan<Number> tmp(rhs);
			 std::swap(*this,tmp);
		 }
		 return *this;
		 */
		this->mCones = _rhs.get();
		this->mDimension = _rhs.dimension();
		return *this;
	}
};

}  // namespace hypro
