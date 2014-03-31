/* 
 * File:   Polytope.h
 * Author: Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * 
 * @since 2014-03-20
 * @version 2014-03-20
 */

#pragma once

#include <gmp.h>
#include <ppl.hh>
#include <carl/core/Variable.h>

#include "../GeometricObject.h"
#include "../../datastructures/Point.h"


using namespace Parma_Polyhedra_Library;

namespace hypro
{
    class Polytope
    {
    private:
        C_Polyhedron mPolyhedron;

    public:
        Polytope();
        Polytope(const Polytope& orig);
        
        Polytope(const Variable& _var, double _val);
        
        
        virtual ~Polytope();
        
        /**
         * Getters and Setters
         */
        
        const C_Polyhedron& rawPolyhedron() const
        {
            return mPolyhedron;
        }
        
        C_Polyhedron& rRawPolyhedron()
        {
            return mPolyhedron;
        }
        
        unsigned dimension() const
        {
            return unsigned(mPolyhedron.space_dimension());
        }
        
    };
} // namespace