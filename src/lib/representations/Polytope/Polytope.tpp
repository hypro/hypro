/* 
 * File:   Polytope.tpp
 * Author: Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * 
 * @since       2014-03-20
 * @version     2014-04-04
 */

#include "Polytope.h"
#include "VariablePool.h"

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
        std::cout << "Dimension." << std::endl;
        Generator_System gs = mPolyhedron.generators();
        std::set<Parma_Polyhedra_Library::Variable, Parma_Polyhedra_Library::Variable::Compare> variables;
        for(auto& generator : gs)
        {
            Generator::expr_type l = generator.expression();
            for(auto& variableIt : polytope::VariablePool::getInstance().pplVariables())
            {
                if(l.get(variableIt) != 0)
                {
                    variables.insert(variableIt);
                }
            }
//            for(auto linearIt = l.begin(); linearIt != l.end(); ++linearIt)
//            {
//                std::cout << (*linearIt) << std::endl;
//                Parma_Polyhedra_Library::Expression_Adapter::dinner_type tmp = (*linarIt).inner();
//                std::cout << "Inner: " << tmp << std::endl;
//                
//                //variables.insert(polytope::VariablePool::variable((*linearIt).variable()));
//            }
        }
        return variables.size();
    }
    
    template<typename Number>
    bool Polytope<Number>::linearTransformation(Polytope<Number>& result, const matrix& A, const vector& b)
    {
        using namespace Parma_Polyhedra_Library;
        
        std::cout << "Input: " << std::endl;
        this->print();
        //std::cout << "Matrix A: " << A << std::endl;
        //std::cout << "Vector b: " << b << std::endl;
        result = *this;
        
        std::vector<Parma_Polyhedra_Library::Variable> variables;
        for(unsigned i = 0; i < A.rows(); ++i)
            variables.push_back(polytope::VariablePool::getInstance().pplVarByIndex(i));
        
        const Generator_System generators = this->mPolyhedron.generators();
        
        // Create Eigen::Matrix from Polytope
        Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, Eigen::Dynamic> polytopeMatrix;
        unsigned gCount = 0;
        for(Generator_System::const_iterator generatorIt = generators.begin(); generatorIt != generators.end(); ++generatorIt)
        {
            std::cout << "Generator: ";
            generatorIt->print();
            std::cout << std::endl;
            
            unsigned vCount = 0;
            for(auto& var : variables)
            {
                polytopeMatrix(vCount, gCount) = carl::FLOAT_T<Number>(generatorIt->coefficient(variables.at(vCount)));
                ++vCount;
            }
            ++gCount;
        }
        
        for(int i = 0; i < A.rows(); ++i)
        {
            Eigen::Matrix<carl::FLOAT_T<Number>, 1, Eigen::Dynamic> rowE = A.row(i);
            //std::cout << "Row: " << rowE << std::endl;
            Parma_Polyhedra_Library::Linear_Expression rowP;
            for(int j = 0; j < rowE.cols(); ++j)
            {
                std::cout << "Try to set coefficient: " << polytope::VariablePool::getInstance().pplVarByIndex(j) << " -> " << rowE(j).value() << std::endl;
                rowP.set_coefficient(polytope::VariablePool::getInstance().pplVarByIndex(j), rowE(j).value()); // TODO: value() is temporary atm
            }
            std::cout << "PPL Linear_Expression: " << rowP << std::endl;
            if(b(i).value() != 0)
            {
                result.mPolyhedron.affine_image(polytope::VariablePool::getInstance().pplVarByIndex(i), rowP, b(i).value());
            }
            else
            {
                result.mPolyhedron.affine_image(polytope::VariablePool::getInstance().pplVarByIndex(i), rowP);
            }
            
            result.print();
        }
        return true;
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
        //@author Chris: just to get rid of the warning
        return true;
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
