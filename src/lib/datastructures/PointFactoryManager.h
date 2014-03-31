/* 
 * The factoryManager holds all PointFactories and creates them. It is designed to
 * keep track of the different factories for points with different dimensions.
 *
 * @file   PointFactoryManager.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since       2014-03-27
 * @version     2014-03-27
 */

#pragma once

#include "PointFactory.h"
#include "../config.h"

namespace hypro
{
    class PointFactoryManager
    {
        private:
            PointFactoryManager();
            ~PointFactoryManager();
            
            /**
             * Member
             */
            static PointFactoryManager mManager;
            unsigned mId;
            std::map<unsigned, PointFactory<number_t>*> mFactories;
            
        public:
            
            static PointFactoryManager& instance()
            {
                return mManager;
            }
            
            PointFactory<number_t>* factory(unsigned _id);
            PointFactory<number_t>* factory(const variableSet& _variables);
            PointFactory<number_t>* factory(const typename std::map<carl::Variable, carl::FLOAT_T<number_t>>& _variables);
    };
}