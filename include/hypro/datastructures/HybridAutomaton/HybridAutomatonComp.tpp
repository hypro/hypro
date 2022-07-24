/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "HybridAutomatonComp.h"

namespace hypro {

template <typename Number>
void ComposedLocation<Number>::validate() const {
	assert( mCompositionals.size() == mAutomaton.mAutomata.size() );
	// perform actual composition, if not already done
	if ( isValid ) return;
	// collect all locations taking part in the composition
	std::vector<Location<Number>*> locs;
	for ( std::size_t idx = 0; idx < mCompositionals.size(); ++idx ) {
		locs.push_back( mAutomaton.mAutomata[idx].getLocationByIndex( mCompositionals[idx] ) );
	}
}

template <typename Number>
std::vector<Location<Number>*> HybridAutomatonComp<Number>::getLocations() const {
	return mLocations;
}

template <typename Number>
Location<Number>* HybridAutomatonComp<Number>::getLocation( const std::size_t hash ) const {
	for ( const auto* l : mLocations ) {
		if ( l->hash() == hash ) {
			return l;
		}
	}
	return nullptr;
}

template <typename Number>
Location<Number>* HybridAutomatonComp<Number>::getLocation( const std::string& name ) const {
	for ( const auto* l : mLocations ) {
		if ( l->getName() == name ) {
			return l;
		}
	}
	return nullptr;
}

template <typename Number>
std::vector<Transition<Number>*> HybridAutomatonComp<Number>::getTransitions() const {}

template <typename Number>
const typename HybridAutomatonComp<Number>::locationConditionMap& HybridAutomatonComp<Number>::getInitialStates() const {
	return mInitialStates;
}

template <typename Number>
const typename HybridAutomatonComp<Number>::locationConditionMap& HybridAutomatonComp<Number>::getLocalBadStates() const {
	return mLocalBadStates;
}

template <typename Number>
const typename HybridAutomatonComp<Number>::conditionVector& HybridAutomatonComp<Number>::getGlobalBadStates() const {
	return mGlobalBadStates;
}

template <typename Number>
unsigned HybridAutomatonComp<Number>::dimension() const {}

template <typename Number>
const std::vector<std::string>& HybridAutomatonComp<Number>::getVariables() const {
	if ( mCachesValid ) return mVariables;

	/*
	for ( auto haIt = std::begin( mAutomata ); haIt != std::end( mAutomata ); ++haIt ) {
		mVariables.insert(std::begin(haIt->getVariables()); std::end(haIt->getVariables()));
		// find shared variables
		TRACE( "hypro.datastructures.hybridAutomaton", "Find shared variables" );
		for ( std::size_t i = 0; i != haVar.size(); ++i ) {
			bool left = false;
			bool right = false;
			std::size_t l = 0;
			std::size_t r = 0;
			while ( l != lhsVar.size() ) {
				if ( lhsVar[l] == haVar[i] ) {
					left = true;
					break;
				}
				++l;
			}
			while ( r != rhsVar.size() ) {
				if ( rhsVar[r] == haVar[i] ) {
					right = true;
					break;
				}
				++r;
			}
			if ( left && right ) {
				TRACE( "hypro.datastructures.hybridAutomaton", "Shared var at " << i << " corresponds to original indices (" << l << "," << r << ")" );
				sharedVars[i] = std::make_pair( l, r );
			}
		}
	}
	 */

	return mVariables;
}

template <typename Number>
const std::set<Label> HybridAutomatonComp<Number>::getLabels() const {}

}  // namespace hypro
