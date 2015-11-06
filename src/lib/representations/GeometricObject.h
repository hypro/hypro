/**
 * Abstract representation of a geometric object.
 * All representations of geometric objects should implement this abstract class.
 * @author Benedikt Seidl
 * @version 2013-09-01
 */

#pragma once
#include "../datastructures/Point.h"
#include "../config.h"

namespace hypro {
template <class Number>
class GeometricObject {
  public:
	typedef Number type;
};
}