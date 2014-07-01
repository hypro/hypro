/* 
 * File:   Polytope.h
 * Author: Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * 
 * @since       2014-03-20
 * @version     2014-04-04
 */

#pragma once

#include <map>
#include <cassert>
#include <string>
#include <sstream>
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
        Polytope(const typename std::set<Eigen::Matrix<carl::FLOAT_T<Number>,Eigen::Dynamic,1>>& points);
        Polytope(const matrix& A, const vector& b);
        Polytope(const matrix& A);
        Polytope(const C_Polyhedron& _rawPoly);
        
        virtual ~Polytope();
        
        /**
         * Getters and Setters
         */
        
        /**
         * Returns true, if the generatorset is empty.
         * @return 
         */
        bool isEmpty() const;
        
        /**
         * Adds a point to the polytope. Note that if the point lies inside the
         * current polytope, this has no effect.
         * @param point
         */
        void addPoint(const Point<Number>& point);
        
        /**
         * Returns the set of points which form the polytope.
         * @return Pointset.
         */
        typename Point<Number>::pointSet points() const;
        
        /**
         * Prints the polytopes' generators obtained from the PPL to stdout.
         */
        void print() const;
        
        /**
         * Writes the polytope to a file in a matlab format.
         * @param _filename The filename of the output file.
         */
        void writeToFile(std::string _filename) const;
        
        friend std::ostream& operator<<(std::ostream& lhs, const Polytope<Number>& rhs)
        {
            using namespace Parma_Polyhedra_Library::IO_Operators;
            lhs << "[";
            for(auto& generator : rhs.rawPolyhedron().generators())
            {
                lhs << generator;
            }
            lhs << "]" << std::endl;
            return lhs;
        }
        
        /**
         * PPL related functions
         */
        const C_Polyhedron& rawPolyhedron() const;
        C_Polyhedron& rRawPolyhedron();
        
        /**
         * Geometric Object interface
         */
        unsigned int dimension() const;
        bool linearTransformation(Polytope<Number>& result, const matrix& A, const vector& b = vector::Zero(1)) const;
        bool minkowskiSum(Polytope<Number>& result, const Polytope<Number>& rhs);
        bool intersect(Polytope<Number>& result, const Polytope<Number>& rhs);
        bool hull(Polytope<Number>& result);
        bool contains(const Point<Number>& point);
        bool contains(const Polytope<Number>& poly);
        bool unite(Polytope<Number>& result, const Polytope<Number>& rhs);
        
        /**
         * Polytope related
         */
        Number hausdorffError(const Number& delta) const;
        
        
        Polytope<Number>& operator= (const Polytope<Number>& rhs);
    };
} // namespace

#include "Polytope.tpp"