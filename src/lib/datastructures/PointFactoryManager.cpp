
#include "PointFactoryManager.h"

namespace hypro
{
    PointFactoryManager::PointFactoryManager() : 
    mId(0)
    {}

    PointFactoryManager::~PointFactoryManager()
    {
        for(auto factory : mFactories)
        {
            PointFactory<number_t>* tmp = factory.second;
            mFactories.erase(factory.first);
            delete tmp;
        }
    }

    PointFactory<number_t>* PointFactoryManager::factory(unsigned _id)
    {
        return mFactories.at(_id);
    }

    PointFactory<number_t>* PointFactoryManager::factory(const variableSet& _variables)
    {
        for(auto factory : mFactories)
        {
            if( factory.second->hasVariables(_variables) )
            {
                return factory.second;
            }
        }
        PointFactory<number_t>* tmp = new PointFactory<number_t>(_variables, mId++);
        mFactories.insert(std::make_pair(mId, tmp));
        return tmp;
    }

    PointFactory<number_t>* PointFactoryManager::factory(const typename std::map<carl::Variable, carl::FLOAT_T<number_t>>& _variables)
    {
        for(auto factory : mFactories)
        {
            if( factory.second->hasVariables(_variables) )
            {
                return factory.second;
            }
        }
        PointFactory<number_t>* tmp = new PointFactory<number_t>(_variables, mId++);
        mFactories.insert(std::make_pair(mId, tmp));
        return tmp;
    }
}