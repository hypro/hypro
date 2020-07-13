#pragma once
#ifdef HYPRO_USE_CLP
#include "../../logging/Logger.h"
#include "helperFunctions.h"

#include <ClpSimplex.hpp>
#include <CoinPackedMatrix.hpp>
#include <carl/core/Relation.h>

namespace hypro {

struct clp_context {
	ClpSimplex lp;
	CoinPackedMatrix matrix;
	double* mUpperBounds = nullptr;
	double* mLowerBounds = nullptr;
	double* mColumnLowerBounds = nullptr;
	double* mColumnUpperBounds = nullptr;
	bool arraysCreated = false;			   // true if array variables have been created.
	mutable bool mInitialized = false;	 // true if lp instance has been created, not needed for clp
	mutable bool mConstraintsSet = false;  // true if lp instance exists, arrays have been set and the lp instance is set up with the current constraints.

	bool operator==( const clp_context& rhs ) {
		return this == &rhs;
	}

	void createArrays( unsigned rows, unsigned columns ) {
		if ( arraysCreated ) {
			deleteArrays();
		}
		mUpperBounds = new double[rows];
		mLowerBounds = new double[rows];
		mColumnLowerBounds = new double[columns];
		mColumnUpperBounds = new double[columns];
		arraysCreated = true;
	}

	void deleteArrays() {
		if ( arraysCreated ) {
			delete[] mUpperBounds;
			delete[] mLowerBounds;
			delete[] mColumnUpperBounds;
			delete[] mColumnLowerBounds;
			mUpperBounds = nullptr;
			mLowerBounds = nullptr;
			mColumnUpperBounds = nullptr;
			mColumnLowerBounds = nullptr;
			arraysCreated = false;
		}
	}

	void createLPInstance() {
	}

	void deleteLPInstance() {
	}

	~clp_context() {
		deleteArrays();
		mConstraintsSet = false;
	}

	template <typename Number>
	void setMatrix( const matrix_t<Number>& constraints, const vector_t<Number>& constants, const std::vector<carl::Relation>& relations ) {
		if ( !mConstraintsSet ){
			matrix = detail::createMatrix( constraints );
			createArrays( constraints.rows(), constraints.cols() );
			for ( int i = 0; i < constants.rows(); ++i ) {
				switch ( relations[i] ) {
					case carl::Relation::LEQ:
						mUpperBounds[i] = carl::toDouble( constants( i ) );
						mLowerBounds[i] = -COIN_DBL_MAX;
						break;
					case carl::Relation::GEQ:
						mUpperBounds[i] = COIN_DBL_MAX;
						mLowerBounds[i] = carl::toDouble( constants( i ) );
						break;
					case carl::Relation::EQ:
						mUpperBounds[i] = carl::toDouble( constants( i ) );
						mLowerBounds[i] = mUpperBounds[i];
						break;
					default:
						// clp cannot handle strict inequalities.
						assert( false );
						std::cout << "This should not happen." << std::endl;
				}
			}
			for ( int i = 0; i < constraints.cols(); ++i ) {
				mColumnLowerBounds[i] = -COIN_DBL_MAX;
				mColumnUpperBounds[i] = COIN_DBL_MAX;
			}
			mConstraintsSet = true;
		}
	}

	template <typename Number>
	void updateConstraints( const matrix_t<Number>& constraints, const vector_t<Number>& constants, const std::vector<carl::Relation>& relations, bool maximize ) {
		if ( maximize ){
			lp.setOptimizationDirection( -1 );
		} else {
			lp.setOptimizationDirection( 1 );
		}
		// turn off clp output
		lp.setLogLevel( 0 );

		// initialize problem + bounds
		setMatrix( constraints, constants, relations );
	}
};
}  // namespace hypro
#endif
