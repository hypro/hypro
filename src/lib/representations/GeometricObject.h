/**
 * Abstract representation of a geometric object.
 * All representations of geometric objects should implement this abstract class.
 * @author Benedikt Seidl
 * @version 2013-09-01
 */

#pragma once
#include "../datastructures/Point.h"
#include "../config.h"
#include "conversion/Converter.h"

namespace hypro {

enum representation_name { cpair, box, zonotope, polytope_h, polytope_v, support_function, taylor_model };

} // namespace hypro
