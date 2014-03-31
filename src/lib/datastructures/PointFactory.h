/* 
 *  The factory for points, which keeps a mapping of the dimensions to variables
 * @file   PointFactory.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de
 *
 * @since       2014-03-27
 * @version     2014-03-27
 */

#pragma once
#include "../config.h"

namespace hypro
{   
    template<typename Number>
    class Point;
    
    template<typename Number>
    class PointFactory
    {
        public:
            /**
             * Static Members
             */
            static unsigned mCurrentFactoryId;
            
            /**
             * Typedefs
             */
            
        private:
            unsigned mId;
            varIdMap mMapping;
            
        public:
            PointFactory() : 
                mId(++mCurrentFactoryId),
                mMapping()
            {}
                
            PointFactory(const typename std::map<carl::Variable, carl::FLOAT_T<Number> > _values, unsigned _id) :
                mId(_id)
            {
                unsigned i = 0;
                for(auto variable : _values)
                {                    
                    mMapping.insert(std::make_pair(variable.first, Number(i++)));
                }
            }
            
            PointFactory(const variableSet& _variables, unsigned _id) :
            mId(_id)
            {
                unsigned i = 0;
                for(auto variable : _variables)
                {                    
                    mMapping.insert(std::make_pair(variable, Number(i++)));
                }
            }
                
            PointFactory(const PointFactory& _pf) :
                mId(_pf.id()),
                mMapping(_pf.mapping())
            {}
            
            ~PointFactory()
            {}
            
            Point<Number> point();
            Point<Number> point(unsigned _dimension);
            Point<Number> point(const varIdMap& _values);
            Point<Number> point(const typename std::map<carl::Variable, carl::FLOAT_T<Number>>& _values);
            
            Point<Number> origin();
            
            bool hasVariables(const variableSet& _variables);
            bool hasVariables(const typename std::map<carl::Variable, carl::FLOAT_T<Number>>& _variables);
            
            unsigned variableIndex(const carl::Variable& _var)
            {
                return mMapping.at(_var);
            }
            
            unsigned size() const
            {
                return mMapping.size();
            }
            
            unsigned varValue() const;
    };
    
    template<typename Number>
    inline bool operator<(const PointFactory<Number>& lhs, const PointFactory<Number>& rhs)
    {
        return (lhs.varValue() < rhs.varValue());
    }
}
#include "PointFactory.tpp"