/* 
 *  The factory for points, which keeps a mapping of the dimensions to variables
 * @file   PointFactory.cpp
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de
 *
 * @since       2014-03-27
 * @version     2014-03-27
 */
#include "PointFactory.h"
#include "Point.h"

namespace hypro
{
    template<typename Number>
    Point<Number> PointFactory<Number>::point()
    {
        if(mMapping.size() == 0)
        {
            
        }
    }
    
    template<typename Number>
    Point<Number> PointFactory<Number>::point(unsigned _dimension)
    {
        
    }
    
    template<typename Number>
    Point<Number> PointFactory<Number>::point(const varIdMap& _values)
    {
        
    }
    
    template<typename Number>
    unsigned PointFactory<Number>::varValue() const
    {
        unsigned value = 0;
        for(auto variableIt : mMapping)
        {
            value += variableIt.second;
        }
        return value;
    }
    
    template<typename Number>
    bool PointFactory<Number>::hasVariables(const variableSet& _variables)
    {
        if(_variables.size() == mMapping.size())
        {
            for(auto varIt : _variables)
            {
                if(mMapping.find(varIt) == mMapping.end())
                    return false;
            }
            return true;
        }
        return false;
    }

    template<typename Number>
    bool PointFactory<Number>::hasVariables(const typename std::map<carl::Variable, carl::FLOAT_T<Number>>& _variables)
    {
        if(_variables.size() == mMapping.size())
        {
            for(auto varIt : _variables)
            {
                if(mMapping.find(varIt.first) == mMapping.end())
                    return false;
            }
            return true;
        }
        return false;
    }
}