/*
 * Wrapper class for constraint set.
 */

#pragma once

#include "../../handles/ClassHandle.h"
#include "../../handles/ObjectHandle.h"
#include "../@MHyProGeometricObject/MGeometricObject.h"
#include "matrix.h"
#include "mex.h"

class MConstraintSet : public MGeometricObject<hypro::ConstraintSet<double>> {
  public:
	static void process( int, mxArray**, int, const mxArray** );

  private:
	static void isAxisAligned( int, mxArray**, int, const mxArray** );
	static void addConstraint( int, mxArray**, int, const mxArray** );
	static void type( int, mxArray**, int, const mxArray** );
	static void reduceNumberRepresentation( int, mxArray**, int, const mxArray** );
};

#include "MConstraintSet.tpp"