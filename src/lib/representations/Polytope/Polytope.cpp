/* 
 * File:   Polytope.cpp
 * Author: Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * 
 * @since 2014-03-20
 * @version 2014-03-20
 */

#include "Polytope.h"

using namespace hypro;

Polytope::Polytope() : mPolyhedron() {
}

Polytope::Polytope(const Polytope& orig) : mPolyhedron(orig.mPolyhedron){
}

Polytope::~Polytope() {
}

Polytope::Polytope(const Variable& _var, double _val)
{
    
}