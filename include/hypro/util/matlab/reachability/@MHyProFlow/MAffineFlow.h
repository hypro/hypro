/*
 *   Wrapper class for affine flow.
 */

#pragma once

#include "../../../../types.h"
#include "../../handles/ClassHandle.h"
#include "../../handles/ObjectHandle.h"
#include "MFlow.h"
#include "matrix.h"
#include "mex.h"

class MAffineFlow : public MFlow<hypro::affineFlow<double>> {
  public:
	static void process( int, mxArray**, int, const mxArray** );

  private:
	static void new_mat_vec( int, mxArray**, int, const mxArray** );
	static void setTranslation( int, mxArray**, int, const mxArray** );
	static void getTranslation( int, mxArray**, int, const mxArray** );
	static void hasTranslation( int, mxArray**, int, const mxArray** );
	static void outstream( int, mxArray**, int, const mxArray** );
};

#include "MAffineFlow.tpp"