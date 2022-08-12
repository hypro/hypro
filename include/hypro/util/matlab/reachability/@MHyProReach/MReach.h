/*
 *   Wrapper class for reach.
 */

#pragma once

#include "../../../../algorithms/reachability/Reach.h"
#include "../../handles/ClassHandle.h"
#include "../../handles/ObjectHandle.h"
#include "matrix.h"
#include "mex.h"

class MReach {
  public:
	using Reacher = hypro::reachability::Reach<double, hypro::reachability::ReachSettings, hypro::State_t<double>>;
	using flowpipe = std::vector<hypro::State_t<double>>;

	static void del_reach( int lhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] );
	static void new_reach( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] );
	static void computeForwardReachability( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] );
	static void setSettings( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] );
	static void setRepresentationType( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] );
	static void settings( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] );
	static void process( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] );
	static void reachedBadStates( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] );
};
