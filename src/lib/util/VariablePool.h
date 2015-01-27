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

#include <carl/util/Singleton.h>
#include <carl/core/Variable.h>
#include <carl/core/VariablePool.h>
#include <ppl.hh>
#include <map>
#include <cassert>

using namespace Parma_Polyhedra_Library::IO_Operators;

namespace hypro
{
    class VariablePool : public carl::Singleton<hypro::VariablePool>
    {
        friend carl::Singleton<hypro::VariablePool>;
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
        {
			mPool.clear();
		}
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
            }
			assert(mCarlToPpl.size() == mPplToCarl.size());
            return (*target).second;
        }
        
        Parma_Polyhedra_Library::Variable& variable(const carl::Variable& _var)
        {
            //std::cout << "PC: " << mPplToCarl.size() << ", CP: " << mCarlToPpl.size() << std::endl;
            //std::cout << "Variable: " << _var << std::endl;
            //this->print();
            assert(mCarlToPpl.size() == mPplToCarl.size());
            carlPplMap::iterator target = mCarlToPpl.find(_var);
            if(target == mCarlToPpl.end())
            {
                Parma_Polyhedra_Library::Variable newPplVar = Parma_Polyhedra_Library::Variable(mPplId++);
                //std::cout << "PC: " << mPplToCarl.size() << ", CP: " << mCarlToPpl.size() << std::endl;
                //bool test = (mPplToCarl.find(newPplVar) != mPplToCarl.end());
                mPplToCarl.insert(std::make_pair(newPplVar, _var));
                /*
                if (test)
                    std::cout << "In" << std::endl;
                else
                    std::cout << "Not In" << std::endl;
                std::cout << "before:" << std::endl;
                for(auto& pair : mPplToCarl)
                    std::cout << pair.first << " -> " << pair.second << std::endl;*/
                target = mCarlToPpl.insert(std::make_pair(_var, newPplVar)).first;
                /*std::cout << "after" << std::endl;
                for(auto& pair : mPplToCarl)
                    std::cout << pair.first << " -> " << pair.second << std::endl;
                std::cout << "PC: " << mPplToCarl.size() << ", CP: " << mCarlToPpl.size() << std::endl;*/
                assert(mCarlToPpl.size() == mPplToCarl.size());
            }
            return (*target).second;
        }
        
        const Parma_Polyhedra_Library::Variable& pplVarByIndex(unsigned _index)
        {
            //std::cout << "BEFORE: " << _index << "CurId: "<< mPplId << std::endl;
            assert(mCarlToPpl.size() == mPplToCarl.size());
            pplCarlMap::const_iterator varIt = mPplToCarl.begin();
            for(;varIt != mPplToCarl.end(); ++varIt)
            {
                if(varIt->first.id() == _index)
                    break;
            }
            if(varIt != mPplToCarl.end())
                return varIt->first;
            else
            {
				std::cout << __func__ << " _index: " << _index << " mPplId: " << mPplId << std::endl;
                assert(_index == mPplId);
                Parma_Polyhedra_Library::Variable newPplVar = Parma_Polyhedra_Library::Variable(mPplId++);
                carl::Variable newCarlVar = mPool.getFreshVariable();
                pplCarlMap::iterator target = mPplToCarl.insert(std::make_pair(newPplVar, newCarlVar)).first;
                mCarlToPpl.insert(std::make_pair(newCarlVar, newPplVar));
                assert(mCarlToPpl.size() == mPplToCarl.size());
                return (*target).first;
            }
        }
        
        const carl::Variable& carlVarByIndex(unsigned _index)
        {
			//std::cout << __func__ << " search variable with Id: " << _index << std::endl;
            assert(mCarlToPpl.size() == mPplToCarl.size());
            pplCarlMap::const_iterator varIt = mPplToCarl.begin();
            for(;varIt != mPplToCarl.end(); ++varIt)
            {
                if(varIt->first.id() == _index)
                    break;
            }
            if(varIt != mPplToCarl.end())
               return varIt->second;
            else
            {
				//std::cout << __func__ << " create variable with Id: " << _index << std::endl;
                Parma_Polyhedra_Library::Variable newPplVar = Parma_Polyhedra_Library::Variable(_index);
                carl::Variable newCarlVar = mPool.getFreshVariable();
                pplCarlMap::iterator target = mPplToCarl.insert(std::make_pair(newPplVar, newCarlVar)).first;
                mCarlToPpl.insert(std::make_pair(newCarlVar, newPplVar));
                assert(mCarlToPpl.size() == mPplToCarl.size());
                return (*target).second;
            }
        }
        
        unsigned inline dimension(const Parma_Polyhedra_Library::Variable& _var) const
        {
            assert(mCarlToPpl.size() == mPplToCarl.size());
            assert(mPplToCarl.find(_var) != mPplToCarl.end());
            return (_var.space_dimension());
        }
        
        std::set<carl::Variable> carlVariables() const
        {
            assert(mCarlToPpl.size() == mPplToCarl.size());
            std::set<carl::Variable> variables;
            for(auto variableIt = mCarlToPpl.begin(); variableIt != mCarlToPpl.end(); ++variableIt)
            {
                variables.insert((*variableIt).first);
            }
            return variables;
        }
        
        std::set<Parma_Polyhedra_Library::Variable, Parma_Polyhedra_Library::Variable::Compare> pplVariables() const
        {
            assert(mCarlToPpl.size() == mPplToCarl.size());
            std::set<Parma_Polyhedra_Library::Variable, Parma_Polyhedra_Library::Variable::Compare> variables;
            for(auto variableIt = mPplToCarl.begin(); variableIt != mPplToCarl.end(); ++variableIt)
            {
                variables.insert((*variableIt).first);
            }
            return variables;
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
