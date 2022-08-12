/*
 *   Wrapper class for reset.
 */

#pragma once

#include "../../../../types.h"
#include "../../handles/ClassHandle.h"
#include "../../handles/ObjectHandle.h"
#include "matrix.h"
#include "mex.h"

#include <map>

class MReset {
  public:
	static void process( int, mxArray**, int, const mxArray** );

  private:
	static void new_empty( int, mxArray**, int, const mxArray** );
	static void copy( int, mxArray**, int, const mxArray** );
	static void new_mat_vec( int, mxArray**, int, const mxArray** );
	static void new_intervals( int, mxArray**, int, const mxArray** );
	static void delete_reset( int, mxArray**, int, const mxArray** );
	static void empty( int, mxArray**, int, const mxArray** );
	static void size( int, mxArray**, int, const mxArray** );
	static void getVector( int, mxArray**, int, const mxArray** );
	static void getMatrix( int, mxArray**, int, const mxArray** );
	static void getIntervals( int, mxArray**, int, const mxArray** );
	static void getAffineReset_at( int, mxArray**, int, const mxArray** );
	static void getAffineResets( int, mxArray**, int, const mxArray** );
	static void getIntervalReset_at( int, mxArray**, int, const mxArray** );
	static void getIntervalResets( int, mxArray**, int, const mxArray** );
	static void setVector( int, mxArray**, int, const mxArray** );
	static void setMatrix( int, mxArray**, int, const mxArray** );
	static void setIntervals( int, mxArray**, int, const mxArray** );
	static void isIdentity( int, mxArray**, int, const mxArray** );
	static void hash( int, mxArray**, int, const mxArray** );
	static void decompose( int, mxArray**, int, const mxArray** );
	static void combine( int, mxArray**, int, const mxArray** );
};

#include "MReset.tpp"