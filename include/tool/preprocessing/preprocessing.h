/*
 * Copyright (c) 2021.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once
#include "typedefs.h"

#include <boost/program_options.hpp>
#include <hypro/algorithms/reachability/analyzer/DecompositionalUtil.h>
#include <hypro/datastructures/HybridAutomaton/HybridAutomaton.h>
#include <hypro/datastructures/HybridAutomaton/decomposition/DecompositionMethods.h>
#include <hypro/datastructures/reachability/PreprocessingInformation.h>
#include <hypro/datastructures/reachability/Settings.h>

namespace hydra {
namespace preprocessing {
/// calls the preprocessor on the passed hybrid automaton
template <typename Number>
hypro::PreprocessingInformation preprocess( const hypro::HybridAutomaton<Number>& automaton,
											bool decompose,
											std::size_t singularSubspaceSize,
											std::size_t clockCount ) {
	auto dynamicsType = hypro::getDynamicType( automaton );
	hypro::PreprocessingInformation information{ dynamicsType };

	if ( decompose ) {
		/**
		 * step 1: get subspace dynamics and maximal decomposition
		 * step 2: change dynamics if required (e.g. 0 clocks with mutliple singular subspaces)
		 * step 3: merge subspaces with same dynamics based on settings
		 * step 4: add initial variables and clocks to subspaces
		 */

		/**
		 * step 1
		 */
		auto [decomposedHa, decomposition] = hypro::decomposeAutomaton( automaton );
		/**
		 * step 2
		 * if clockCount > 0 nothing changes
		 * if clockCount == 0 and there are at least two non discrete subspaces, use lti analysis for singular subspaces
		 * here we need to consider that singular subspaces may be merged later, and thus result in fewer subspaces
		 */
		if ( clockCount == 0 ) {
			std::size_t singularSubspaceCount = std::accumulate( decomposition.subspaceTypes.begin(), decomposition.subspaceTypes.end(), 0,
																 []( std::size_t cur, auto const& dynamic ) { return dynamic == hypro::DynamicType::singular || dynamic == hypro::DynamicType::timed ? cur + 1 : cur; } );
			std::size_t ltiSubspaceCount = std::accumulate( decomposition.subspaceTypes.begin(), decomposition.subspaceTypes.end(), 0,
															[]( std::size_t cur, auto const& dynamic ) { return dynamic == hypro::DynamicType::linear || dynamic == hypro::DynamicType::affine ? cur + 1 : cur; } );
			if ( std::ceil( (float)singularSubspaceCount / singularSubspaceSize ) + ltiSubspaceCount > 1 ) {
				std::replace( decomposition.subspaceTypes.begin(), decomposition.subspaceTypes.end(), hypro::DynamicType::singular, hypro::DynamicType::linear );
				std::replace( decomposition.subspaceTypes.begin(), decomposition.subspaceTypes.end(), hypro::DynamicType::timed, hypro::DynamicType::linear );
			}
		}
		/**
		 * step 3
		 * always merge all discrete variables in one subspace
		 * merge singular subspaces to get subspaces of size at most `singularSubspaceSize`
		 */
		hypro::Decomposition mergedDecomposition;
		std::vector<std::size_t> discreteVars;
		std::vector<std::size_t> currentSingularVars;
		for ( std::size_t i = 0; i < decomposition.subspaces.size(); ++i ) {
			if ( decomposition.subspaceTypes[i] == hypro::DynamicType::discrete ) {
				for ( auto var : decomposition.subspaces[i] ) {
					discreteVars.push_back( var );
				}
			} else if ( decomposition.subspaceTypes[i] == hypro::DynamicType::singular || decomposition.subspaceTypes[i] == hypro::DynamicType::timed ) {
				assert( decomposition.subspaces[i].size() == 1 );
				currentSingularVars.push_back( decomposition.subspaces[i][0] );
			} else {
				mergedDecomposition.subspaceTypes.push_back( decomposition.subspaceTypes[i] );
				mergedDecomposition.subspaces.push_back( decomposition.subspaces[i] );
			}
			// subspace is full or last variable is reached
			if ( ( currentSingularVars.size() >= singularSubspaceSize || i == decomposition.subspaces.size() - 1 ) && currentSingularVars.size() > 0 ) {
				std::sort( currentSingularVars.begin(), currentSingularVars.end() );
				mergedDecomposition.subspaces.push_back( currentSingularVars );
				mergedDecomposition.subspaceTypes.push_back( hypro::DynamicType::singular );
				currentSingularVars.clear();
			}
		}
		if ( discreteVars.size() > 0 ) {
			// composition assumes for simplicity that subspace variables are ordered
			std::sort( discreteVars.begin(), discreteVars.end() );
			mergedDecomposition.subspaces.push_back( discreteVars );
			mergedDecomposition.subspaceTypes.push_back( hypro::DynamicType::discrete );
		}

		// decompse with merged subspaces
		auto automatonCopy = automaton;
		automatonCopy.decompose( mergedDecomposition.subspaces );
		decomposedHa = automatonCopy;
		decomposition = mergedDecomposition;

		/**
		 * step 4
		 */
		for ( std::size_t subspace = 0; subspace < decomposition.subspaceTypes.size(); ++subspace ) {
			if ( clockCount > 0 && decomposition.subspaceTypes[subspace] != hypro::DynamicType::discrete ) {
				hypro::addInitialVarToAutomaton( decomposedHa, subspace, decomposition.subspaces[subspace].size() );
				hypro::addClocksToAutomaton( decomposedHa, subspace, clockCount );
			}
		}
		information.decomposition = decomposition;
		information.decomposedHa = decomposedHa;
		information.clockCount = clockCount;
	}
	return information;
}
}  // namespace preprocessing
}  // namespace hydra
