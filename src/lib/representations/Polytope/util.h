/* 
 * Contains utilities to wrap the ppl polyhedra to our datastructure.
 * @file   util.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since       2014-04-01
 * @version     2014-04-03
 */

#pragma once

#include <ppl.hh>
#include <carl/core/Variable.h>
#include "../../config.h"
#include "../../util/eigenTypetraits.h"
#include "../../util/VariablePool.h"

#include "../../datastructures/Point.h"

namespace hypro
{
namespace polytope
{
    static inline std::set<Parma_Polyhedra_Library::Variable, Parma_Polyhedra_Library::Variable::Compare> variables(const Parma_Polyhedra_Library::C_Polyhedron& poly)
    {
        Parma_Polyhedra_Library::Generator_System gs = poly.generators();
        std::set<Parma_Polyhedra_Library::Variable, Parma_Polyhedra_Library::Variable::Compare> variables;
        for(auto& generator : gs)
        {
            Parma_Polyhedra_Library::Generator::expr_type l = generator.expression();
            for(auto& variableIt : VariablePool::getInstance().pplVariables())
            {
                if(l.get(variableIt) != 0)
                {
                    variables.insert(variableIt);
                }
            }
        }
        return variables;
    }
    
    static inline const unsigned gsSize(const Parma_Polyhedra_Library::Generator_System& gs)
    {
        using namespace Parma_Polyhedra_Library;
        unsigned i = 0;
        for(auto& g : gs)
            ++i;
                    
        return i;
    }
    
    static inline const unsigned csSize(const Parma_Polyhedra_Library::Constraint_System& cs)
    {
        using namespace Parma_Polyhedra_Library;
        unsigned i = 0;
        for(auto& c : cs)
            ++i;
                    
        return i;
    }
    
    template<typename Number>
    static inline Parma_Polyhedra_Library::Generator pointToGenerator(const Point<Number>& point)
    {
        using namespace Parma_Polyhedra_Library;
        Linear_Expression ls;
        for(auto pointIt = point.begin(); pointIt != point.end(); ++pointIt)
        {
            Linear_Expression tmp = (*pointIt).second.toDouble() * VariablePool::getInstance().variable((*pointIt).first);
            ls += tmp;
        }
        Generator result = Generator::point(ls);
        return result;
    }
    
    /**
     * Creates a generator from a point, which is a colum-vector (mx1)
     */
    template<typename Number>
    static inline Parma_Polyhedra_Library::Generator pointToGenerator(const Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, Eigen::Dynamic>& point)
    {
        using namespace Parma_Polyhedra_Library;
        Linear_Expression ls;
        for(unsigned i = 0; i < point.rows(); ++i)
        {
            Linear_Expression tmp = point.row(i) * VariablePool::getInstance().pplVarByIndex(i);
            ls += tmp;
            ++i;
        }
        Generator result = Generator::point(ls);
        return result;
    }
    
    template<typename Number>
    static inline Point<Number> generatorToPoint(const Parma_Polyhedra_Library::Generator& gen, const std::set<Parma_Polyhedra_Library::Variable, Parma_Polyhedra_Library::Variable::Compare>& variables)
    {
        Point<Number> result;
        for(auto varIt = variables.begin(); varIt != variables.end(); ++varIt)
        {
            result.setCoordinate(hypro::VariablePool::getInstance().variable(*varIt), (int)Parma_Polyhedra_Library::raw_value(gen.coefficient(*varIt)).get_si());
        }
        return result;
    }
    
    static inline unsigned pplDimension(const Parma_Polyhedra_Library::C_Polyhedron& poly)
    {
        Parma_Polyhedra_Library::Generator_System gs = poly.generators();
        std::set<Parma_Polyhedra_Library::Variable, Parma_Polyhedra_Library::Variable::Compare> variables;
        for(auto& generator : gs)
        {
            Parma_Polyhedra_Library::Generator::expr_type l = generator.expression();
            for(auto& variableIt : VariablePool::getInstance().pplVariables())
            {
                if(l.get(variableIt) != 0)
                {
                    variables.insert(variableIt);
                }
            }
        }
        return variables.size();
    }
    
    template<typename Number>
    static inline unsigned pplDimension(const Point<Number>& point)
    {
        unsigned result = 0;
        for(auto& coordinate : point)
        {
            result = result > VariablePool::getInstance().variable(coordinate.first).id() ? result : VariablePool::getInstance().variable(coordinate.first).id();
        }
        return result;
    }
    
    template<typename Number>
    static inline unsigned pplDimension(const typename std::set<Point<Number> >& points)
    {
        unsigned result = 0;
        for(auto& point : points)
        {
            unsigned tmp = pplDimension(point);
            result = result > tmp ? result : tmp;
        }
        return result;
    }
    
    template<typename Number>
    static inline unsigned pplDimension(const typename std::set<Eigen::Matrix<Number, Eigen::Dynamic, 1>>& points)
    {
        unsigned result = 0;
        for(auto& point : points)
        {
            result = result < point.rows() ? point.rows() : result;
        }
        return result;
    }
    
    template<typename Number>
    static inline Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, Eigen::Dynamic> polytopeToMatrix(const Parma_Polyhedra_Library::C_Polyhedron& poly)
    {
        // TODO: What about the constant factor?
        unsigned rowCount = 0;
        unsigned columCount = 0;
        poly.print();
        Parma_Polyhedra_Library::Constraint_System cs = poly.constraints();
        std::set<Parma_Polyhedra_Library::Variable, Parma_Polyhedra_Library::Variable::Compare> vars = variables(poly);
        Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, Eigen::Dynamic> result = Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, Eigen::Dynamic>(hypro::polytope::csSize(cs), pplDimension(poly));
        //std::cout << "CSSize: " << hypro::polytope::csSize(cs) << ", Dimension: " << pplDimension(poly) << std::endl;
        for(auto constraintIt = cs.begin(); constraintIt != cs.end(); ++constraintIt)
        {
            columCount = 0;
            Parma_Polyhedra_Library::Constraint::expr_type t = (*constraintIt).expression();
            for(auto variableIt = vars.begin(); variableIt != vars.end(); ++variableIt)
            {
                carl::FLOAT_T<Number> val = (int)Parma_Polyhedra_Library::raw_value(t.get(*variableIt)).get_si();
                //std::cout << "Insert " << val << " at (" << rowCount << ", " << columCount << ")" << std::endl; 
                result(rowCount, columCount) = val;
                ++columCount;
            }
            ++rowCount;
        }
        return result;
    }
}
}
