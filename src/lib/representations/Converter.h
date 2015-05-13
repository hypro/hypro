/**
 * Class that provides a converter for representations. The template parameter specifies the target representation, the source representation is
 * included as an overloading.
 * @file Converter.h
 * 
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * 
 * @since 	2015-05-08
 * @version	2015-05-08
 */
 
#pragma once

#include "../util/VariablePool.h"
#include "../config.h"

// include representations for conversion
#include "Box/Box.h"
#include "Polytope/Polytope.h"
#include "Polytopes/VPolytope/VPolytope.h"
#include "Polytopes/HPolytope/HPolytope.h"
#include "SupportFunction/SupportFunction.h"
#include "Zonotope/Zonotope.h"

#include "Box/converter.h"
#include "SupportFunction/converter.h"