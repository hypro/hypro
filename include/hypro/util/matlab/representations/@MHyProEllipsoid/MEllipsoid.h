/*
 * Wrapper class for ellipsoids.
 */

#pragma once

#include "../../handles/ClassHandle.h"
#include "../../handles/ObjectHandle.h"
#include "../@MHyProGeometricObject/MGeometricObject.h"
#include "matrix.h"
#include "mex.h"

#include <cassert>
#include <iostream>
#include <map>

class MEllipsoid : public MGeometricObject<hypro::Ellipsoid<double>> {
  public:
	static void process( int, mxArray**, int, const mxArray** );

  private:
	static void ellipsoid_rad( int, mxArray**, int, const mxArray** );
	static void ellipsoid_mat( int, mxArray**, int, const mxArray** );
	static void approxEllipsoidTMatrix( int, mxArray**, int, const mxArray** );
	static void ostream( int, mxArray**, int, const mxArray** );
	static void type( int, mxArray**, int, const mxArray** );
};

#include "MEllipsoid.tpp"