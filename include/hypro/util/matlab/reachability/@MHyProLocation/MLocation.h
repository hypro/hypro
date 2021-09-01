/*
 *   Wrapper class for location.
 */

#pragma once

#include "../../handles/ClassHandle.h"
#include "../../handles/ObjectHandle.h"
#include "matrix.h"

#include <mex.h>

class MLocation {
  public:
	static void process( int, mxArray**, int, const mxArray** );

  private:
	static void new_empty( int, mxArray**, int, const mxArray** );
	static void new_matrix( int, mxArray**, int, const mxArray** );
	static void new_mat_tran_inv( int, mxArray**, int, const mxArray** );
	static void copy( int, mxArray**, int, const mxArray** );
	static void delete_loc( int, mxArray**, int, const mxArray** );
	static void getNumberFlow( int, mxArray**, int, const mxArray** );
	static void getLinearFlow( int, mxArray**, int, const mxArray** );
	static void getLinearFlows( int, mxArray**, int, const mxArray** );
	static void getInvariant( int, mxArray**, int, const mxArray** );
	static void getTransitions( int, mxArray**, int, const mxArray** );
	static void getExternalInput( int, mxArray**, int, const mxArray** );
	static void hasExternalInput( int, mxArray**, int, const mxArray** );
	static void hash( int, mxArray**, int, const mxArray** );
	static void getName( int, mxArray**, int, const mxArray** );
	static void dimension( int, mxArray**, int, const mxArray** );
	static void dimension_at( int, mxArray**, int, const mxArray** );
	static void setName( int, mxArray**, int, const mxArray** );
	static void setFlow( int, mxArray**, int, const mxArray** );
	static void setLinearFlow( int, mxArray**, int, const mxArray** );
	static void setLinearFlow_vec( int, mxArray**, int, const mxArray** );
	static void setInvariant( int, mxArray**, int, const mxArray** );
	// static void setTransition(int, mxArray**, int , const mxArray**);
	static void addTransition( int, mxArray**, int, const mxArray** );
	static void setExtInput( int, mxArray**, int, const mxArray** );
	static void isComposedOf( int, mxArray**, int, const mxArray** );
	// static void getDotRepresentation(int, mxArray**, int , const mxArray**);
	static void decompose( int, mxArray**, int, const mxArray** );
	static void less( int, mxArray**, int, const mxArray** );
	static void equals( int, mxArray**, int, const mxArray** );
	static void unequals( int, mxArray**, int, const mxArray** );
	static void outstream( int, mxArray**, int, const mxArray** );
};
#include "MLocation.tpp"