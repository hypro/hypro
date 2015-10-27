/*
 * File:   util.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since   2014-08-11
 * @version 2014-08-22
 */

#pragma once

#include <cassert>
#include <glpk.h>

#include "../../datastructures/Point.h"
#include "../../datastructures/Hyperplane.h"
#include <carl/formula/Constraint.h>
#include "Cone.h"

namespace hypro {
namespace polytope {

class dPermutator {
private:
	std::vector<unsigned> mCurrent;
	unsigned max;
	bool mEnd;

public:

	dPermutator(std::size_t totalSize, std::size_t d) : mCurrent(d,0), max(totalSize), mEnd(false) {
		assert(d < totalSize);
		if(d < totalSize) {
			for(unsigned i = 0; i < d; ++i)
				mCurrent[i] = d-i-1;
		}
	}

	std::vector<unsigned> operator()() {
		if(mEnd) {
			return mCurrent;
		}

		std::vector<unsigned> tmp = mCurrent;

		// find pos to iterate
		std::size_t pos = 0;
		while(pos < mCurrent.size() && mCurrent.at(pos) == max-pos-1) {
			++pos;
		}

		if(pos == mCurrent.size()) {
			mEnd = true;
			return tmp;
		}

		mCurrent[pos] += 1;
		while(pos > 0) {
			--pos;
			mCurrent[pos] = mCurrent[pos+1]+1;
		}

		return tmp;
	}

	bool end() const {
		return mEnd;
	}
};

template <typename Number>
class Fan {
  public:
	typedef std::vector<const Cone<Number>*> cones;

  private:
	cones mCones;
	unsigned mDimension;

  public:
	Fan() : mCones(), mDimension() {}

	~Fan() { mCones.clear(); }

	Fan( const Fan& _orig ) : mCones( _orig.get() ), mDimension( _orig.dimension() ) {}

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
		// set up glpk
		glp_prob* cones;
		cones = glp_create_prob();
		glp_set_obj_dir( cones, GLP_MAX );

		typename polytope::Cone<Number>::vectors vectors;
		for ( auto& cone : mCones ) {
			vectors.insert( vectors.end(), cone.begin(), cone.end() );
		}
		unsigned numPlanes = vectors.size();
		unsigned elements = this->mDimension * numPlanes;

		glp_add_cols( cones, numPlanes );
		glp_add_rows( cones, this->mDimension );

		int ia[elements];
		int ja[elements];
		double ar[elements];
		unsigned pos = 1;

		for ( unsigned i = 1; i <= this->mDimension; ++i ) {
			for ( unsigned j = 1; j <= numPlanes; ++j ) {
				ia[pos] = i;
				ja[pos] = j;
				ar[pos] = vectors.at( j ).at( i );
				++pos;
			}
		}
		assert( pos <= elements );

		glp_load_matrix( cones, elements, ia, ja, ar );
		glp_simplex( cones, NULL );

		// TODO output & result interpretation

		glp_delete_prob( cones );
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

}  // namespace polytope
}  // namespace hypro
