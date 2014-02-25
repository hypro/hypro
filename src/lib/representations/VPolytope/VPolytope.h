/* 
 * The class implementing the vertex representation of a convex polytope.
 * @file   VPolytope.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since   2014-02-25
 * @version 2014-02-25
 */
#pragma once

#include "../../datastructures/Point.h"
#include "../GeometricObject.h"
#include <carl/core/Variable.h>

namespace hypro
{

template<typename Number>
class VPolytope hypro::GeometricObject<Number>
{
    public: 
        
        /***************************************************************************
	 * Members
	 **************************************************************************/
    protected:
	
    public:
	/***************************************************************************
	 * Constructors
	 **************************************************************************/

        VPolytope(){}

        VPolytope(const VPolytope& orig)
        {

        }

        ~VPolytope()
        {}

};

}//namespace