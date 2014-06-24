/* 
 * File:   Polytope.tpp
 * Author: Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * 
 * @since       2014-03-20
 * @version     2014-04-04
 */

#include "Polytope.h"
#include "util.h"

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
    Polytope<Number>::Polytope(const matrix& A, const vector& b)
    {
        assert(A.rows() == b.rows());
        mPolyhedron = Parma_Polyhedra_Library::C_Polyhedron(A.rows(), Parma_Polyhedra_Library::UNIVERSE);
        for(unsigned rowIndex = 0; rowIndex < A.rows(); ++rowIndex)
        {
            Parma_Polyhedra_Library::Linear_Expression polynom;
            polynom.set_space_dimension(A.cols());
            for(unsigned columIndex = 0; columIndex < A.cols(); ++columIndex)
            {
                std::cout << hypro::VariablePool::getInstance().pplVarByIndex(columIndex) << " = " << A(rowIndex,columIndex).toDouble() << std::endl;
                polynom.set_coefficient(hypro::VariablePool::getInstance().pplVarByIndex(columIndex), A(rowIndex,columIndex).toDouble());
            }
            polynom.set_inhomogeneous_term(-b(rowIndex,0).toDouble());
            Parma_Polyhedra_Library::Constraint constraint;
            constraint = polynom <= 0;
            
            mPolyhedron.add_constraint(constraint);
            //mPolyhedron.add_generator(gen);
        }
    }
    
    template<typename Number>
    Polytope<Number>::Polytope(const matrix& A)
    {
        mPolyhedron = Parma_Polyhedra_Library::C_Polyhedron(A.rows(), Parma_Polyhedra_Library::UNIVERSE);
        for(unsigned rowIndex = 0; rowIndex < A.rows(); ++rowIndex)
        {
            Parma_Polyhedra_Library::Linear_Expression polynom;
            polynom.set_space_dimension(A.cols());
            for(unsigned columIndex = 0; columIndex < A.cols(); ++columIndex)
            {
                std::cout << hypro::VariablePool::getInstance().pplVarByIndex(columIndex) << " = " << A(rowIndex,columIndex).toDouble() << std::endl;
                polynom.set_coefficient(hypro::VariablePool::getInstance().pplVarByIndex(columIndex), A(rowIndex,columIndex).toDouble());
            }
            Parma_Polyhedra_Library::Constraint constraint;
            constraint = polynom <= 0;
            
            mPolyhedron.add_constraint(constraint);
            //mPolyhedron.add_generator(gen);
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
    typename Point<Number>::pointSet Polytope<Number>::points() const
    {
        typename Point<Number>::pointSet result;
        std::set<Parma_Polyhedra_Library::Variable, Parma_Polyhedra_Library::Variable::Compare> variables = hypro::polytope::variables(mPolyhedron);
        for(auto& generator : mPolyhedron.generators())
        {
            Point<Number> tmp = polytope::generatorToPoint<Number>(generator, variables);
            result.insert(tmp);
        }
        return result;
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
        return hypro::polytope::pplDimension(mPolyhedron);
    }
    
    template<typename Number>
    bool Polytope<Number>::linearTransformation(Polytope<Number>& result, const matrix& A) const
    {
        using namespace Parma_Polyhedra_Library;
        
        std::cout << "Input: " << std::endl;
        this->print();
        //std::cout << "Matrix A: " << A << std::endl;
        //std::cout << "Vector b: " << b << std::endl;
        result = *this;
        
        std::vector<Parma_Polyhedra_Library::Variable> variables;
        for(unsigned i = 0; i < A.rows(); ++i)
            variables.push_back(VariablePool::getInstance().pplVarByIndex(i));
        
        const Generator_System generators = this->mPolyhedron.generators();
        
        // Create Eigen::Matrix from Polytope
        Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, Eigen::Dynamic> polytopeMatrix(variables.size(), polytope::gsSize(generators));
        unsigned gCount = 0;
        for(Generator_System::const_iterator generatorIt = generators.begin(); generatorIt != generators.end(); ++generatorIt)
        {
            std::cout << "Generator: ";
            generatorIt->print();
            std::cout << std::endl;
            
            unsigned vCount = 0;
            for(auto& var : variables)
            {
                std::cout << "Try: " << var << ", coeff: " << carl::FLOAT_T<Number>((int)raw_value(generatorIt->coefficient(var)).get_si()) << std::endl;
                polytopeMatrix(vCount, gCount) =carl::FLOAT_T<Number>( (int)raw_value(generatorIt->coefficient(var)).get_si() );
                ++vCount;
            }
            ++gCount;
            std::cout << "ping." << std::endl;
        }
        
        // apply lineartransformation
        Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, Eigen::Dynamic> res(variables.size(), polytope::gsSize(generators));
        res = A*polytopeMatrix;
        
        std::cout << "colums: " << res.cols() << ", rows: " << res.rows() << std::endl;
        
        // clear actual generators and add new ones
        typename Point<Number>::pointSet ps;
        for(unsigned i = 0; i < res.cols(); ++i)
        {
            std::cout << res.col(i) << std::endl;
            Point<Number> t;
            for(unsigned j = 0; j < res.rows(); ++j)
                t.setCoordinate(VariablePool::getInstance().carlVarByIndex(j), res.col(i)(j));
            ps.insert(t);
            std::cout << "point: " << t << std::endl;
        }
        C_Polyhedron tmp = Parma_Polyhedra_Library::C_Polyhedron(polytope::pplDimension(ps)+1, Parma_Polyhedra_Library::EMPTY);
        for(auto& pointSetIt : ps)
        {
            tmp.add_generator(polytope::pointToGenerator(pointSetIt));
        }
        result.mPolyhedron = tmp;
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
    bool Polytope<Number>::contains(const Polytope<Number>& poly)
    {
        return mPolyhedron.contains(poly.rawPolyhedron());
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
    Number Polytope<Number>::hausdorffError(const Number& delta) const
    {
        using namespace Eigen;
        // TODO: Can we omit conversion to carl::FLOAT_T<Number> and use Number instead?
        carl::FLOAT_T<Number> result;
        carl::FLOAT_T<Number> d = carl::FLOAT_T<Number>(delta);
        //TODO: What about the constant factor?
        Eigen::Matrix<carl::FLOAT_T<Number>, Dynamic, Dynamic> matrix = Eigen::Matrix<carl::FLOAT_T<Number>, Dynamic, Dynamic>(polytope::csSize(mPolyhedron.constraints()), polytope::pplDimension(mPolyhedron));
        matrix = hypro::polytope::polytopeToMatrix<Number>(mPolyhedron);
        
        // TODO: Matrix lpNorm function of Eigen does not work ...
        //carl::FLOAT_T<Number> t = matrix.lpNorm<Infinity>();
        
        // calculate matrix infinity norm by hand
        carl::FLOAT_T<Number> norm = 0;
        for(unsigned rowCnt = 0; rowCnt < matrix.rows(); ++rowCnt)
        {
            for(unsigned colCnt = 0; colCnt < matrix.cols(); ++colCnt)
            {
                carl::FLOAT_T<Number> value = matrix(rowCnt, colCnt);
                value.abs_assign();
                norm = norm < value ? value : norm;
            }
        }
        
        //carl::FLOAT_T<Number> tmp = d * t;
        carl::FLOAT_T<Number> tmp = d * norm;
        tmp.exp(result);
        result = result - 1 - tmp;
        
        // compute RX_0
        Number max = 0;
        for(auto& point : points())
        {
            Number inftyNorm = hypro::Point<Number>::inftyNorm(point);
            max = max > inftyNorm ? max : inftyNorm;
        }
        result *= carl::FLOAT_T<Number>(max);
        
        return result.value();
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
