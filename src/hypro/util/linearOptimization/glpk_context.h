#pragma once
#include "../logging/Logger.h"

#include <glpk.h>

namespace hypro {
struct glpk_context {
	glp_prob* lp = nullptr;
	glp_smcp parm;
	int* ia = nullptr;
	int* ja = nullptr;
	double* ar = nullptr;
	bool arraysCreated = false;			   // true if array variables have been created.
	mutable bool mInitialized = false;	 // true if lp instance has been created.
	mutable bool mConstraintsSet = false;  // true if lp instance exists, arrays have been set and the lp instance is set up with the current constraints.

	glpk_context()
		: lp( nullptr )
		, parm()
		, ia( nullptr )
		, ja( nullptr )
		, ar( nullptr )
		, arraysCreated( false )
		, mInitialized( false )
		, mConstraintsSet( false ) {
		TRACE( "hypro.optimizer", "Create glpk_context " << this );
	}

	glpk_context( const glpk_context& orig ) {
		if ( orig.mInitialized ) {
			glp_copy_prob( lp, orig.lp, GLP_ON );
			parm = orig.parm;
			glp_init_smcp( &parm );
			parm.msg_lev = GLP_MSG_OFF;
			glp_set_obj_dir( lp, GLP_MAX );
		}
		mInitialized = orig.mInitialized;
		// We do not attempt to copy the arrays
		arraysCreated = false;
		mConstraintsSet = false;
	}

	glpk_context( glpk_context&& orig ) = delete;

	glpk_context& operator=( const glpk_context& orig ) {
		// compare problem instances to avoid self-assignment
		if(lp == orig.lp) {
			return *this;
		}
		deleteLPInstance();
		deleteArrays();
		if ( orig.mInitialized ) {
			glp_copy_prob( lp, orig.lp, GLP_ON );
			parm = orig.parm;
			glp_init_smcp( &parm );
			parm.msg_lev = GLP_MSG_OFF;
			glp_set_obj_dir( lp, GLP_MAX );
		}
		mInitialized = orig.mInitialized;
		// We do not attempt to copy the arrays
		arraysCreated = false;
		mConstraintsSet = false;
		return *this;
	}

	glpk_context& operator=( glpk_context&& orig ) = delete;

	void createArrays( unsigned size ) {
		TRACE( "hypro.optimizer", "" );
		if ( arraysCreated ) {
			deleteArrays();
		}
		ia = new int[size + 1];
		ja = new int[size + 1];
		ar = new double[size + 1];
		arraysCreated = true;
	}

	void deleteArrays() {
		TRACE( "hypro.optimizer", "" );
		if ( arraysCreated ) {
			delete[] ia;
			delete[] ja;
			delete[] ar;
			ia = nullptr;
			ja = nullptr;
			ar = nullptr;
			arraysCreated = false;
		}
	}

	void createLPInstance() {
		if ( !mInitialized ) {
			lp = glp_create_prob();
			glp_init_smcp( &parm );
			parm.msg_lev = GLP_MSG_OFF;
			glp_set_obj_dir( lp, GLP_MAX );
			glp_term_out( GLP_OFF );
			TRACE( "hypro.optimizer", "Thread " << std::this_thread::get_id() << " creates its glp instance. (@" << this << ")" );
			mInitialized = true;
			mConstraintsSet = false;
		}
	}

	void deleteLPInstance() {
		TRACE( "hypro.optimizer", "Start."
										<< " instance @" << this );
		if ( mInitialized ) {
			assert( lp != nullptr );
			glp_delete_prob( lp );
			mInitialized = false;
			mConstraintsSet = false;
			lp = nullptr;
		}
		TRACE( "hypro.optimizer", "Done."
										<< " instance @" << this );
	}

	~glpk_context() {
		TRACE( "hypro.optimizer", "Arrays created: " << arraysCreated << " instance @" << this );
		// deleteLPInstance();
		// assume that all fields are set at once so just check one.
		deleteArrays();
	}
};
}  // namespace hypro
