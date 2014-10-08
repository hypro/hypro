/*
 * This file contains typdefs, includes and some general stuff used by HyReach
 * Author: Norman Hansen
 */

#pragma once

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

// Supportfunction
#include "SupportFunction.h"
#include "PolytopeSupportfunction.h"
//#include "NonLinearOmega0Supportfunction.h"


#include "matlabConversions.h"   // transformation of objects to matlab input for debugging purpose

// some globally used methods
namespace hypro
{	
#include "helperMethods.h"      // make helper methods available
#include "vectorgenerator.h"    // make vectorgenerator functionalities globally available
}


