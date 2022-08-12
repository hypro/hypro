/*
 * Super class for all wrapped representations implementing
 * common functions.
 */

#pragma once

#include "../../handles/ClassHandle.h"
#include "../../handles/ObjectHandle.h"
#include "matrix.h"
#include "mex.h"

#include <cassert>
#include <iostream>
#include <map>

template <class T>
class MGeometricObject {
  public:
	static void new_empty( int, mxArray**, int, const mxArray** );
	static void new_matrix( int, mxArray**, int, const mxArray** );
	static void new_vector( int, mxArray**, int, const mxArray** );
	static void copyObj( int, mxArray**, int, const mxArray** );
	static void new_mat_vec( int, mxArray**, int, const mxArray** );
	static void deleteObject( int, mxArray**, int, const mxArray** );
	static void matrix( int, mxArray**, int, const mxArray** );
	static void scale( int, mxArray**, int, const mxArray** );
	static void vector( int, mxArray**, int, const mxArray** );
	static void is_empty( int, mxArray**, int, const mxArray** );
	static void vertices( int, mxArray**, int, const mxArray** );
	static void equal( int, mxArray**, int, const mxArray** );
	static void unequal( int, mxArray**, int, const mxArray** );
	static void dimension( int, mxArray**, int, const mxArray** );
	static void removeRedundancy( int, mxArray**, int, const mxArray** );
	static void size( int, mxArray**, int, const mxArray** );
	static void reduceNumberRepresentation( int, mxArray**, int, const mxArray** );
	static void satisfiesHalfspace( int, mxArray**, int, const mxArray** );
	static void satisfiesHalfspaces( int, mxArray**, int, const mxArray** );
	static void projectOn( int, mxArray**, int, const mxArray** );
	static void linearTransformation( int, mxArray**, int, const mxArray** );
	static void affineTransformation( int, mxArray**, int, const mxArray** );
	static void minkowskiSum( int, mxArray**, int, const mxArray** );
	static void intersect( int, mxArray**, int, const mxArray** );
	static void intersectHalfspace( int, mxArray**, int, const mxArray** );
	static void intersectHalfspaces( int, mxArray**, int, const mxArray** );
	static void contains_point( int, mxArray**, int, const mxArray** );
	static void contains_object( int, mxArray**, int, const mxArray** );
	static void unite_single( int, mxArray**, int, const mxArray** );
	static void unite_vec( int, mxArray**, int, const mxArray** );
	static void reduceRepresentation( int, mxArray**, int, const mxArray** );
	static void clear( int, mxArray**, int, const mxArray** );
	static void ostream( int, mxArray**, int, const mxArray** );
	static void supremum( int, mxArray**, int, const mxArray** );
};

#include "MGeometricObject.tpp"