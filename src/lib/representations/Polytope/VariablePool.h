/* 
 * The class handles the conversion from carl::Variable to Parma_Polyhedra_Library::Variable
 * and backwards. It keeps track of the created and used variables.
 * @file   VariablePool.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since       2014-04-02
 * @version     2014-04-03
 */

#pragma once

#include <ppl.hh>
#include <carl/util/Singleton.h>
#include <carl/core/Variable.h>
#include <carl/core/VariablePool.h>
#include <map>
#include <cassert>

using namespace Parma_Polyhedra_Library::IO_Operators;

namespace hypro
{
namespace polytope
{
    class VariablePool : public carl::Singleton<hypro::polytope::VariablePool>
    {
        friend carl::Singleton<hypro::polytope::VariablePool>;
    private:
        /**
         * Typedefs
         */
        typedef std::map<carl::Variable, Parma_Polyhedra_Library::Variable> carlPplMap;
        typedef std::map<Parma_Polyhedra_Library::Variable, carl::Variable, Parma_Polyhedra_Library::Variable::Compare > pplCarlMap;
        
        /**
         * Members
         */
        carlPplMap              mCarlToPpl;
        pplCarlMap              mPplToCarl;
        unsigned                mPplId;
        carl::VariablePool&     mPool;
        
    protected:
        /**
         * Default constructor and destructor
         */
        VariablePool() : 
                mPplId(0),
                mPool(carl::VariablePool::getInstance())
        {}
    public:
        
        ~VariablePool()
        {
            mCarlToPpl.erase(mCarlToPpl.begin(), mCarlToPpl.end());
            mPplToCarl.erase(mPplToCarl.begin(), mPplToCarl.end());
        }
        
        /*
         * Access
         */
        carl::Variable& variable(const Parma_Polyhedra_Library::Variable& _var)
        {
            assert(mCarlToPpl.size() == mPplToCarl.size());
            pplCarlMap::iterator target = mPplToCarl.find(_var);
            if(target == mPplToCarl.end())
            {
                Parma_Polyhedra_Library::Variable newPplVar = Parma_Polyhedra_Library::Variable(mPplId++);
                carl::Variable newCarlVar = mPool.getFreshVariable();
                target = mPplToCarl.insert(std::make_pair(newPplVar, newCarlVar)).first;
                mCarlToPpl.insert(std::make_pair(newCarlVar, newPplVar));
                assert(mCarlToPpl.size() == mPplToCarl.size());
            }
            return (*target).second;
        }
        
        Parma_Polyhedra_Library::Variable& variable(const carl::Variable& _var)
        {
            assert(mCarlToPpl.size() == mPplToCarl.size());
            carlPplMap::iterator target = mCarlToPpl.find(_var);
            if(target == mCarlToPpl.end())
            {
                Parma_Polyhedra_Library::Variable newPplVar = Parma_Polyhedra_Library::Variable(mPplId++);
                mPplToCarl.insert(std::make_pair(newPplVar, _var));
                target = mCarlToPpl.insert(std::make_pair(_var, newPplVar)).first;
                assert(mCarlToPpl.size() == mPplToCarl.size());
            }
            return (*target).second;
        }
        
        unsigned inline dimension(const Parma_Polyhedra_Library::Variable& _var) const
        {
            assert(mCarlToPpl.size() == mPplToCarl.size());
            assert(mPplToCarl.find(_var) != mPplToCarl.end());
            return (_var.space_dimension());
        }
        
        unsigned size() const
        {
            assert(mCarlToPpl.size() == mPplToCarl.size());
            return mCarlToPpl.size();
        }
        
        void clear()
        {
            mCarlToPpl.erase(mCarlToPpl.begin(), mCarlToPpl.end());
            mPplToCarl.erase(mPplToCarl.begin(), mPplToCarl.end());
            mPplId = 0;
        }
        
        void print() const
        {
            assert(mCarlToPpl.size() == mPplToCarl.size());
            for(auto& var : mCarlToPpl)
            {
                std::cout << var.first << " -> " << var.second << std::endl;
            }
        }
    };
}
}