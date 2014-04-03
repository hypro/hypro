/* 
 * File:   Polytope.h
 * Author: Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * 
 * @since       2014-03-20
 * @version     2014-04-03
 */

#pragma once

#include <map>
#include <cassert>
#include <gmp.h>
#include <ppl.hh>
#include <carl/core/Variable.h>

#include "util.h"
#include "../GeometricObject.h"
#include "../../datastructures/Point.h"


using namespace Parma_Polyhedra_Library;

namespace hypro
{
    template<typename Number>
    class Polytope : hypro::GeometricObject<Number>
    {
    private:
        C_Polyhedron mPolyhedron;

    public:
        Polytope();
        Polytope(const Polytope& orig);
        Polytope(unsigned dimension);
        Polytope(const carl::Variable& _var, double _val);
        Polytope(const Point<Number>& point);
        Polytope(const typename Point<Number>::pointSet& points);
        
        virtual ~Polytope();
        
        /**
         * Getters and Setters
         */
        
        bool isEmpty() const;
        
        void addPoint(const Point<Number>& point);
        
        // PPL related
        const C_Polyhedron& rawPolyhedron() const;
        C_Polyhedron& rRawPolyhedron();
        
        /**
         * Geometric Object interface
         */
        unsigned int dimension() const;
        bool linearTransformation(Polytope<Number>& result /*, ... */);
        bool minkowskiSum(Polytope<Number>& result, const Polytope<Number>& rhs);
        bool intersect(Polytope<Number>& result, const Polytope<Number>& rhs);
        bool hull(Polytope<Number>& result);
        bool contains(const Point<Number>& point);
        bool unite(Polytope<Number>& result, const Polytope<Number>& rhs);
    };
} // namespace

#include "Polytope.tpp"