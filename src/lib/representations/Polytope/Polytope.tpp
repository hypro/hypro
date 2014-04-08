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
    Polytope<Number>::Polytope(unsigned dimension) : mPolyhedron(dimension, Parma_Polyhedra_Library::EMPTY)
    {}
    
    template<typename Number>
    Polytope<Number>::Polytope(const carl::Variable& _var, double _val)
    {

    }

    template<typename Number>
    Polytope<Number>::Polytope(const Point<Number>& _point) :
        mPolyhedron(C_Polyhedron(polytope::pplDimension(_point)+1, Parma_Polyhedra_Library::EMPTY))
    {
        mPolyhedron.add_generator(polytope::pointToGenerator(_point));
    }
    
    template<typename Number>
    Polytope<Number>::Polytope(const typename Point<Number>::pointSet& points)
    {
        //mPolyhedron.initialize();
        mPolyhedron = Parma_Polyhedra_Library::C_Polyhedron(polytope::pplDimension(points)+1, Parma_Polyhedra_Library::EMPTY);
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
    void Polytope<Number>::print() const
    {
        std::cout << "[";
        for(auto& generator : mPolyhedron.generators())
        {
            generator.print();
        }
        std::cout << "]" << std::endl;
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
        result = *this;
        result.mPolyhedron.positive_time_elapse_assign(rhs.mPolyhedron);
        return true;
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
        Generator_System gs = mPolyhedron.minimized_generators();
        result = Polytope<Number>(C_Polyhedron(gs));
    }
    
    template<typename Number>
    bool Polytope<Number>::contains(const Point<Number>& point)
    {
        return mPolyhedron.contains(Polytope<Number>(point).rawPolyhedron());
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
    
    template<typename Number>
    bool operator== (const Polytope<Number>& rhs, const Polytope<Number>& lhs) 
    { 
        return (rhs.rawPolyhedron() == lhs.rawPolyhedron());
    }
    template<typename Number>
    bool operator!= (const Polytope<Number>& rhs, const Polytope<Number>& lhs) 
    { 
        return (rhs.rawPolyhedron() != lhs.rawPolyhedron());
    }
}
