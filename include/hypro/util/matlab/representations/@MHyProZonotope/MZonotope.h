/*
 * Wrapper class for zonotopes.
 */

#pragma once

#include "../../../../representations/Zonotope/Zonotope.h"
#include "../../handles/ClassHandle.h"
#include "../../handles/ObjectHandle.h"
#include "../@MHyProGeometricObject/MGeometricObject.h"
#include "matrix.h"
#include "mex.h"

#include <iostream>
#include <string>

class MZonotope : public MGeometricObject<hypro::Zonotope<double>> {
  public:
	static void process( int, mxArray**, int, const mxArray** );

  private:
	static void newZonotopeDimension( int, mxArray**, int, const mxArray** );
	static void newZonotopeCG( int, mxArray**, int, const mxArray** );
	static void copyDimensions( int, mxArray**, int, const mxArray** );
	static void emptyAt( int, mxArray**, int, const mxArray** );
	static void setCenter( int, mxArray**, int, const mxArray** );
	static void setGenerators( int, mxArray**, int, const mxArray** );
	static void addGenerators( int, mxArray**, int, const mxArray** );
	static void center( int, mxArray**, int, const mxArray** );
	static void generators( int, mxArray**, int, const mxArray** );
	static void order( int, mxArray**, int, const mxArray** );
	static void removeEmptyGenerators( int, mxArray**, int, const mxArray** );
	static void uniteEqualVectors( int, mxArray**, int, const mxArray** );
	static void changeDimension( int, mxArray**, int, const mxArray** );
	static void print( int, mxArray**, int, const mxArray** );
	static void reduceOrder( int, mxArray**, int, const mxArray** );
	static void computeZonotopeBoundary( int, mxArray**, int, const mxArray** );
	static void intersectHalfspacesMethod( int, mxArray**, int, const mxArray** );
	static void intersectHalfspaceMethod( int, mxArray**, int, const mxArray** );
	static void intersectMinMax( int, mxArray**, int, const mxArray** );
	static void intervalHull( int, mxArray**, int, const mxArray** );
	static void supremum( int, mxArray**, int, const mxArray** );
	static void type( int, mxArray**, int, const mxArray** );
	static void reduceNumberRepresentation( int, mxArray**, int, const mxArray** );
};

#include "MZonotope.tpp"