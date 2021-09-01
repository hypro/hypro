/*
 *   Wrapper class for linear flow.
 */

#pragma once

#include "../../../../types.h"
#include "../../handles/ClassHandle.h"
#include "../../handles/ObjectHandle.h"
#include "MFlow.h"
#include "matrix.h"
#include "mex.h"

class MLinearFlow : public MFlow<hypro::linearFlow<double>> {
  public:
	static void process( int, mxArray**, int, const mxArray** );

  private:
	static void new_mat( int, mxArray**, int, const mxArray** );
	static void setFlowMatrix( int, mxArray**, int, const mxArray** );
	static void addRow( int, mxArray**, int, const mxArray** );
	static void getFlowMatrix( int, mxArray**, int, const mxArray** );
	static void isIdentity( int, mxArray**, int, const mxArray** );
	static void hasNoFlow( int, mxArray**, int, const mxArray** );
	static void outstream( int, mxArray**, int, const mxArray** );
};

#include "MLinearFlow.tpp"