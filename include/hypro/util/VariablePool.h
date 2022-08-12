/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

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

#include <algorithm>
#include <carl/core/Variable.h>
#include <carl/core/VariablePool.h>
#include <carl/util/Singleton.h>
#include <cassert>
#include <hypro/flags.h>
#include <map>
#include <vector>
#ifdef HYPRO_USE_PPL
#include <ppl.hh>
#endif

namespace hypro {

class VariablePool : public carl::Singleton<VariablePool> {
	friend carl::Singleton<VariablePool>;
	/**
	 * Typedefs
	 */
#ifdef HYPRO_USE_PPL
	using carlPplMap = std::map<carl::Variable, Parma_Polyhedra_Library::Variable>;
	using pplCarlMap = std::map<Parma_Polyhedra_Library::Variable, carl::Variable, Parma_Polyhedra_Library::Variable::Compare>;
#endif

	/**
	 * Members
	 */
	std::vector<carl::Variable> mCarlVariables;
#ifdef HYPRO_USE_PPL
	std::vector<Parma_Polyhedra_Library::Variable> mPplVariables;
	carlPplMap mCarlToPpl;
	pplCarlMap mPplToCarl;
#endif
	std::size_t mPplId;
	carl::VariablePool& mPool;

  protected:
	/**
	 * Default constructor and destructor
	 */
	VariablePool()
		: mPplId( 0 )
		, mPool( carl::VariablePool::getInstance() ) { mPool.clear(); }

  public:
	~VariablePool() {}

/*
 * Access
 */
#ifdef HYPRO_USE_PPL
	const carl::Variable& variable( const Parma_Polyhedra_Library::Variable& _var ) const {
		assert( mCarlVariables.size() == mPplId );
		assert( mPplVariables.size() == mPplId );
		for ( std::size_t pos = 0; pos < mPplVariables.size(); ++pos ) {
			if ( _var.id() == mPplVariables[pos].id() ) return mCarlVariables[pos];
		}
		assert( false );
		return carl::Variable::NO_VARIABLE;
	}

	const Parma_Polyhedra_Library::Variable& variable( const carl::Variable& _var ) const {
		assert( mCarlVariables.size() == mPplId );
		assert( mPplVariables.size() == mPplId );
		for ( std::size_t pos = 0; pos < mCarlVariables.size(); ++pos ) {
			if ( _var == mCarlVariables[pos] ) return mPplVariables[pos];
		}
		assert( false );
		return mPplVariables.back();
	}

	const Parma_Polyhedra_Library::Variable& pplVarByIndex( std::size_t _index ) {
		assert( mCarlVariables.size() == mPplId );
		assert( mPplVariables.size() == mPplId );
		if ( _index >= mPplId ) {
			for ( std::size_t curr = mPplId; curr <= _index; ++curr ) {
				carl::Variable cVar = carl::freshRealVariable();
				Parma_Polyhedra_Library::Variable pVar = Parma_Polyhedra_Library::Variable( mPplId++ );
				mCarlVariables.push_back( cVar );
				mPplVariables.push_back( pVar );
			}
		}
		assert( mCarlVariables.size() == mPplId );
		assert( mPplVariables.size() == mPplId );
		return mPplVariables.at( _index );
	}
#endif

	carl::Variable& carlVarByIndex( std::size_t _index, std::string prefix = "x" ) {
		assert( mCarlVariables.size() == mPplId );
#ifdef HYPRO_USE_PPL
		assert( mPplVariables.size() == mPplId );
#endif
		if ( _index >= mPplId ) {
			for ( std::size_t curr = mPplId; curr <= _index; ++curr ) {
				carl::Variable cVar = carl::freshRealVariable( prefix + "_" + std::to_string( curr ) );
				mCarlVariables.push_back( cVar );
#ifdef HYPRO_USE_PPL
				Parma_Polyhedra_Library::Variable pVar = Parma_Polyhedra_Library::Variable( mPplId++ );
				mPplVariables.push_back( pVar );
#else
				++mPplId;
#endif
			}
		}
		assert( mCarlVariables.size() == mPplId );
#ifdef HYPRO_USE_PPL
		assert( mPplVariables.size() == mPplId );
#endif
		return mCarlVariables.at( _index );
	}

	const carl::Variable& newCarlVariable( std::string _name = "", std::optional<std::size_t> index = std::nullopt ) {
		assert( mCarlVariables.size() == mPplId );
#ifdef HYPRO_USE_PPL
		assert( mPplVariables.size() == mPplId );
#endif
		if ( index ) {
			// fill with new, unused variables, if the index is larger than the pool
			while ( index.value() >= mCarlVariables.size() ) {
				newCarlVariable();
			}
			// set / update variable with the correct name at the correct position
			mCarlVariables[index.value()] = carl::freshRealVariable( _name );
			return mCarlVariables[index.value()];
		}

		carl::Variable cVar = carl::VariablePool::getInstance().findVariableWithName( _name );
		if ( cVar == carl::Variable::NO_VARIABLE ) {
			cVar = carl::freshRealVariable( _name );
		}
		mCarlVariables.push_back( cVar );
#ifdef HYPRO_USE_PPL
		Parma_Polyhedra_Library::Variable pVar = Parma_Polyhedra_Library::Variable( mPplId++ );
		mPplVariables.push_back( pVar );
#else
		++mPplId;
#endif
		assert( mCarlVariables.size() == mPplId );
#ifdef HYPRO_USE_PPL
		assert( mPplVariables.size() == mPplId );
#endif
		return mCarlVariables.back();
	}

	std::size_t addCarlVariable( carl::Variable var ) {
		if ( std::find( mCarlVariables.begin(), mCarlVariables.end(), var ) == mCarlVariables.end() ) {
			mCarlVariables.push_back( var );
#ifdef HYPRO_USE_PPL
			Parma_Polyhedra_Library::Variable pVar = Parma_Polyhedra_Library::Variable( mPplId++ );
			mPplVariables.push_back( pVar );
#else
			++mPplId;
#endif
		}
		assert( mCarlVariables.size() == mPplId );
#ifdef HYPRO_USE_PPL
		assert( mPplVariables.size() == mPplId );
#endif
		// return id - decrease by one as we start counting from zero.
		return mCarlVariables.size() - 1;
	}

#ifdef HYPRO_USE_PPL
	const Parma_Polyhedra_Library::Variable& newPplVariable() {
		assert( mCarlVariables.size() == mPplId );
#ifdef HYPRO_USE_PPL
		assert( mPplVariables.size() == mPplId );
#endif
		carl::Variable cVar = carl::freshRealVariable();
		Parma_Polyhedra_Library::Variable pVar = Parma_Polyhedra_Library::Variable( mPplId++ );
		mCarlVariables.push_back( cVar );
		mPplVariables.push_back( pVar );
		assert( mCarlVariables.size() == mPplId );
#ifdef HYPRO_USE_PPL
		assert( mPplVariables.size() == mPplId );
#endif
		return mPplVariables.back();
	}
#endif

	bool hasDimension( const carl::Variable& _var ) const {
		assert( mCarlVariables.size() == mPplId );
#ifdef HYPRO_USE_PPL
		assert( mPplVariables.size() == mPplId );
#endif
		for ( std::size_t pos = 0; pos < mCarlVariables.size(); ++pos ) {
			if ( _var == mCarlVariables[pos] ) {
				return true;
			}
		}
		return false;
	}

	bool hasDimension( std::size_t i ) const {
		assert( mCarlVariables.size() == mPplId );
#ifdef HYPRO_USE_PPL
		assert( mPplVariables.size() == mPplId );
#endif
		return mCarlVariables.size() > i;
	}

#ifdef HYPRO_USE_PPL
	std::size_t inline id( const Parma_Polyhedra_Library::Variable& _var ) const {
		assert( mCarlVariables.size() == mPplId );
		assert( mPplVariables.size() == mPplId );
		for ( std::size_t pos = 0; pos < mPplVariables.size(); ++pos ) {
			if ( _var.id() == mPplVariables[pos].id() ) return pos;
		}
		assert( false );
		return 0;
	}
#endif

	std::size_t inline id( const carl::Variable& _var ) {
		assert( mCarlVariables.size() == mPplId );
#ifdef HYPRO_USE_PPL
		assert( mPplVariables.size() == mPplId );
#endif
		for ( std::size_t pos = 0; pos < mCarlVariables.size(); ++pos ) {
			if ( _var == mCarlVariables[pos] ) {
				return pos;
			}
		}
		// if the variable is not registered yet, add and return its associated dimension.
		return addCarlVariable( _var );
	}

	std::vector<carl::Variable> carlVariables() const {
		assert( mCarlVariables.size() == mPplId );
#ifdef HYPRO_USE_PPL
		assert( mPplVariables.size() == mPplId );
#endif
		return mCarlVariables;
	}

#ifdef HYPRO_USE_PPL
	std::vector<Parma_Polyhedra_Library::Variable> pplVariables() const {
		assert( mCarlVariables.size() == mPplId );
		assert( mPplVariables.size() == mPplId );
		return mPplVariables;
	}
#endif

	std::size_t size() const {
		assert( mCarlVariables.size() == mPplId );
#ifdef HYPRO_USE_PPL
		assert( mPplVariables.size() == mPplId );
#endif
		return mCarlVariables.size();
	}

	void clear() {
		assert( mCarlVariables.size() == mPplId );
		mCarlVariables.clear();
#ifdef HYPRO_USE_PPL
		assert( mPplVariables.size() == mPplId );
		mPplVariables.clear();
#endif
		mPool.clear();
		mPplId = 0;
	}

	void print() const {
		assert( mCarlVariables.size() == mPplId );
#ifdef HYPRO_USE_PPL
		assert( mPplVariables.size() == mPplId );
#endif
		for ( std::size_t pos = 0; pos < mCarlVariables.size(); ++pos ) {
			std::cout << mCarlVariables[pos] << " -> " << std::endl;  // mPplVariables[pos] << std::endl; //TODO: fix
		}
	}
};

}  // namespace hypro
