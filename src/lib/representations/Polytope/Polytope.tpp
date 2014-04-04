/* 
 * File:   Polytope.tpp
 * Author: Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * 
 * @since       2014-03-20
 * @version     2014-04-04
 */

#include "Polytope.h"

namespace hypro
{
    template<typename Number>
    Polytope<Number>::Polytope() {
    }

    template<typename Number>
    Polytope<Number>::Polytope(const Polytope& orig) : mPolyhedron(orig.mPolyhedron){
    }

    template<typename Number>
    Polytope<Number>::~Polytope() {
    }

    template<typename Number>
    Polytope<Number>::Polytope(unsigned dimension) : mPolyhedron(dimension)
    {}
    
    template<typename Number>
    Polytope<Number>::Polytope(const carl::Variable& _var, double _val)
    {

    }

    template<typename Number>
    Polytope<Number>::Polytope(const Point<Number>& _point) : 
        mPolyhedron(C_Polyhedron(polytope::pplDimension(_point)+1))
    {
        mPolyhedron.add_generator(polytope::pointToGenerator(_point));
    }
    
    template<typename Number>
    Polytope<Number>::Polytope(const typename Point<Number>::pointSet& points)
    {
        //mPolyhedron.initialize();
        mPolyhedron = Parma_Polyhedra_Library::C_Polyhedron(polytope::pplDimension(points)+1);
        for(auto& pointSetIt : points)
        {
            mPolyhedron.add_generator(polytope::pointToGenerator(pointSetIt));
        }
    }
    
    template<typename Number>
    Polytope<Number>::Polytope(const C_Polyhedron& _rawPoly) : mPolyhedron(_rawPoly)
    {}
    
    template<typename Number>
    bool Polytope<Number>::isEmpty() const
    {
        return mPolyhedron.is_empty();
    }
    
    template<typename Number>
    void Polytope<Number>::addPoint(const Point<Number>& point)
    {
        mPolyhedron.add_generator(polytope::pointToGenerator(point));
    }
    
    template<typename Number>
    const C_Polyhedron& Polytope<Number>::rawPolyhedron() const
    {
        return mPolyhedron;
    }

    template<typename Number>
    C_Polyhedron& Polytope<Number>::rRawPolyhedron()
    {
        return mPolyhedron;
    }

    template<typename Number>
    unsigned int Polytope<Number>::dimension() const
    {
        return unsigned(mPolyhedron.space_dimension());
    }
    
    template<typename Number>
    bool Polytope<Number>::linearTransformation(Polytope<Number>& result /*, ... */)
    {
        
    }
    
    template<typename Number>
    bool Polytope<Number>::minkowskiSum(Polytope<Number>& result, const Polytope<Number>& rhs)
    {
        
    }
    
    template<typename Number>
    bool Polytope<Number>::intersect(Polytope<Number>& result, const Polytope<Number>& rhs)
    {
        C_Polyhedron res = mPolyhedron;
        res.intersection_assign(rhs.rawPolyhedron());
        result = Polytope<Number>(res);
        return true;
    }
    
    template<typename Number>
    bool Polytope<Number>::hull(Polytope<Number>& result)
    {
        // Todo: correct?
        result = *this;
    }
    
    template<typename Number>
    bool Polytope<Number>::contains(const Point<Number>& point)
    {
        
    }
    
    template<typename Number>
    bool Polytope<Number>::unite(Polytope<Number>& result, const Polytope<Number>& rhs)
    {
        C_Polyhedron res = mPolyhedron;
        res.poly_hull_assign(rhs.rawPolyhedron());
        result = Polytope<Number>(res);
        return true;
    }
    
    template<typename Number>
    Polytope<Number>& Polytope<Number>::operator= (const Polytope<Number>& rhs) 
    { 
      if (this != &rhs)
      { 
        C_Polyhedron tmp(rhs.rawPolyhedron());
        mPolyhedron.m_swap(tmp); 
      } 
      return *this;
    }
}
