/*
 * This file contains typdefs, includes and some general stuff used by HyReach
 * Author: Norman Hansen
 */

#pragma once

#define BL '\n'

// model includes
#include "util.h"
#include "../../datastructures/hybridAutomata/util.h"
#include "../../datastructures/hybridAutomata/HybridAutomaton.h"  // used for datastructures (matrix_t<...> etc.)

// standard includes
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <map>
#include <list>
#include <iterator>

// GLPK includes
#include <stdio.h>  /* C input/output                       */
#include <stdlib.h> /* C standard library                   */
#include <glpk.h>   /* GNU GLPK linear/mixed integer solver */

// some Macros
#define MIN( a, b ) ( a < b ? a : b )
#define MAX( a, b ) ( a > b ? a : b )

namespace hypro {
// typedefs for types returned by the hybrid automata model
typedef Location<double> location;
typedef Transition<double> transition;

/*
* Computes the exponential matrix of the parameter
*/
matrix_t<double> exponentialmatrix( matrix_t<double> matrix ) {
	// adapted/used code from C.Kugler (forwardReachability.h & util.h)
	matrix_t<double> resultMatrix( matrix.rows(), matrix.cols() );
	Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> doubleMatrix( matrix.rows(), matrix.cols() );
	Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> expMatrix( matrix.rows(), matrix.cols() );
	doubleMatrix = convertMatToDouble<double>( matrix );
	expMatrix = doubleMatrix.exp();
	resultMatrix = convertMatToFloatT<double>( expMatrix );

	return resultMatrix;
}
}

#include "FlowpipeSegment.h"

namespace hypro {
/*
   * This structure describes a set of consecutive sets in the flowpipe by the start and end indexis relatively to a
 * specific flowpipeSegment
   * The main purpose of this structure is to be used as elements of a list inside the possibleTransition structure
   */
struct convexSetOfFlowpipeSetIndexis {
	unsigned int start;
	unsigned int end;
};

/*
* Structure describing a possible transition and a list of all associated sets of the currently considered flowpipe
*/
struct possibleTransition {
	transition* transition_pt;		   // transition
	FlowpipeSegment* flowpipeSegment;  // flowpipe the set indexis relate to
	std::vector<convexSetOfFlowpipeSetIndexis>
		  sets;  // list of successive sets having an intersection with the guard (and I* etc.) of the transition
};
}

#include "helperMethods.h"	// make helper methods available (print/convert)
#include "vectorgenerator.h"  // make vectorgenerator functionalities globally available

// Supportfunctions
#include "SupportFunction.h"
#include "PolytopeSupportfunction.h"
#include "NonLinearOmega0Supportfunction.h"

#include "matlabConversions.h"  // transformation of objects to matlab input for debugging purpose
