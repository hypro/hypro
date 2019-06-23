/*
 * Wrapper class for boxes.
 */

#pragma once

#include "../../handles/ClassHandle.h"
#include "../../handles/ObjectHandle.h"
#include "../@MHyProGeometricObject/MGeometricObject.h"
#include "matrix.hpp"
#include "mex.hpp"
#include <iostream>
#include <string>

class MBoxAdvanced {
  public:
	static void process( matlab::mex::ArgumentList);

  private:
	static void newEmpty( matlab::mex::ArgumentList);

};

#include "MBoxAdvanced.tpp"