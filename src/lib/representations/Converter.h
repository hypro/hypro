/**
 * Class that provides a converter for representations. The template parameter specifies the target representation, the
 *source representation is
 * included as an overloading.
 * @file Converter.h
 *
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @author Simon Froitzheim
 *
 * @since 	2015-05-08
 * @version	2015-12-17
 */

#pragma once

#include "../util/VariablePool.h"
#include "../config.h"

//enum for differentiating between exact conversion and over-/underapproximation.
enum CONV_MODE {EXACT, OVER, UNDER};
// include representations for conversion
#include "Box/Box.h"
#include "Polytope/Polytope.h"
#include "Polytopes/VPolytope/VPolytope.h"
#include "Polytopes/HPolytope/HPolytope.h"
#include "SupportFunction/SupportFunction.h"
#include "Zonotope/Zonotope.h"

#include "Box/converterToBox.h"
#include "SupportFunction/converterToSupportFunction.h"
#include "Polytopes/HPolytope/converterToHPolytope.h"
#include "Polytopes/VPolytope/converterToVPolytope.h"
#include "Zonotope/converterToZonotope.h"

