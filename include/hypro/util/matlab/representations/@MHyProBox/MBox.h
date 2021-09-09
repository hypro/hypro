/*
 * Wrapper class for boxes.
 */

#pragma once

#include "../../handles/ClassHandle.h"
#include "../../handles/ObjectHandle.h"
#include "../@MHyProGeometricObject/MGeometricObject.h"
#include "matrix.h"
#include "mex.h"

#include <iostream>
#include <string>

class MBox : public MGeometricObject<hypro::Box<double>> {
  public:
	static void process( int, mxArray**, int, const mxArray** );

  private:
	static void boxFromSingleInterval( int, mxArray**, int, const mxArray** );
	static void boxFromIntervals( int, mxArray**, int, const mxArray** );
	static void boxFromPoints( int, mxArray**, int, const mxArray** );
	static void empty( int, mxArray**, int, const mxArray** );
	static void intervals( int, mxArray**, int, const mxArray** );
	static void insert( int, mxArray**, int, const mxArray** );
	static void limits( int, mxArray**, int, const mxArray** );
	static void constraints( int, mxArray**, int, const mxArray** );
	static void interval( int, mxArray**, int, const mxArray** );
	static void at( int, mxArray**, int, const mxArray** );
	static void is_symmetric( int, mxArray**, int, const mxArray** );
	static void max( int, mxArray**, int, const mxArray** );
	static void min( int, mxArray**, int, const mxArray** );
	static void type( int, mxArray**, int, const mxArray** );
	static void makeSymmetric( int, mxArray**, int, const mxArray** );
	static void minkowskiDecomposition( int, mxArray**, int, const mxArray** );
};

#include "MBox.tpp"