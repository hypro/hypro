/*
 * @file   util.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since	February 24, 2015
 * @version	February 24, 2015
 */

#pragma once
#include "../../config.h"

namespace hypro {
// This enum represents the support function type and is used to identify support function without instanceof operations
enum SF_TYPE { SUM, INTERSECT, LINTRAFO, SCALE, UNION, POLY, INFTY_BALL, TWO_BALL, ELLIPSOID, BOX, ZONOTOPE, NONE };
}
