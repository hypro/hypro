/* 
 * The class which represents a polytope.
 *
 * @file   Polytope.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * 
 * @since       2014-03-20
 * @version     2015-01-21
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
#include "../../datastructures/Facet.h"
#include "../../datastructures/Ridge.h"
#include "../../datastructures/Hyperplane.h"
#include "../../util/convexHull.h"


using namespace Parma_Polyhedra_Library;

namespace hypro
{
	using carl::operator <<;

    template<typename Number>
    class Polytope : hypro::GeometricObject<Number>
    {
    private:
        C_Polyhedron mPolyhedron;
        mutable std::vector<Point<Number>> mPoints;
        mutable bool mPointsUpToDate;
        polytope::Fan<Number> mFan;

    public:
        Polytope();
        Polytope(const Polytope& orig);
        Polytope(unsigned dimension);
        Polytope(const Point<Number>& point);
        Polytope(const typename std::vector<Point<Number>>& points);
        Polytope(const typename std::vector<vector_t<Number>>& points);
        Polytope(const matrix_t<Number>& A, const vector_t<Number>& b);
        Polytope(const matrix_t<Number>& A);
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
        
        
        void updatePoints() const;
        void setPointsUpToDate(bool _val = true){
        	mPointsUpToDate = _val;
        }

        /**initConvexHull
         * Returns the set of points which form the polytope.
         * @return Pointset.
         */
        const std::vector<Point<Number>>& vertices() const;
        
        /*
         *
         */
        std::vector<Point<Number>>& rVertices();

        /*
         * returns the fan of the Polytope
         */
        const polytope::Fan<Number>& fan();

        /*
         * returns a reference to the fan of the Polytope
         */
        polytope::Fan<Number>& rFan();

        /*
         * sets the fan of the Polytope
         */
        void setFan(const polytope::Fan<Number>& _fan);

        void calculateFan();

        /**
         * Prints the polytopes' generators obtained from the PPL to stdout.
         */
        void print() const;
        
        /**
         * Writes the polytope to a file in a matlab format.
         * @param _filename The filename of the output file.
         */
        void writeToFile(std::string _filename) const;
        
        /*
         *
         */
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
        Polytope<Number> linearTransformation(const matrix_t<Number>& A, const vector_t<Number>& b = vector_t<Number>());
        
        Polytope<Number> minkowskiSum(const Polytope<Number>& rhs);
        // implemented according to Komei Fukuda 2004
        Polytope<Number> altMinkowskiSum(Polytope<Number>& rhs);
        Polytope<Number> intersect(const Polytope<Number>& rhs);
        Polytope<Number> hull();
        bool contains(const Point<Number>& point);
        bool contains(const Polytope<Number>& poly);
        Polytope<Number> unite(const Polytope<Number>& rhs);
      //  static std::vector<Facet<Number>> convexHull(const std::vector<Point<Number>> points);

        
        /**
         * Polytope related
         */
        Number hausdorffError(const Number& delta, const matrix_t<Number>& matrix);
        
        
        //Polytope<Number>& operator= (const Polytope<Number>& rhs);

        /**
         * Auxiliary functions
         */
        int computeMaxVDegree();
        Point<Number> computeMaxPoint();
        Point<Number> computeInitVertex(Polytope<Number> _secondPoly);
        Point<Number> localSearch(Point<Number>& _vertex,  Point<Number>& _sinkMaximizerTarget);

    };
} // namespace

#include "Polytope.tpp"
