#include "preprocessing.h"

namespace hydra {
namespace preprocessing {
hypro::PreprocessingInformation preprocess( const hypro::HybridAutomaton<hydra::Number>& automaton,
											bool decompose,
											bool useSingular,
											std::size_t clockCount ) {
	auto dynamicsType = hypro::getDynamicType( automaton );
	hypro::PreprocessingInformation information{ dynamicsType };

	if ( decompose ) {
		auto [decomposedHa, decomposition] = hypro::decomposeAutomaton( automaton );
		// mege discrete subspaces
		hypro::Decomposition newDecomposition;
		std::vector<std::size_t> discreteVars;
		for ( std::size_t i = 0; i < decomposition.subspaces.size(); ++i ) {
			if ( decomposition.subspaceTypes[i] == hypro::DynamicType::discrete ) {
				for ( auto var : decomposition.subspaces[i] ) {
					discreteVars.push_back( var );
				}
			} else {
				newDecomposition.subspaces.push_back( decomposition.subspaces[i] );
				if ( !useSingular && ( decomposition.subspaceTypes[i] == hypro::DynamicType::singular || decomposition.subspaceTypes[i] == hypro::DynamicType::timed ) ) {
					newDecomposition.subspaceTypes.push_back( hypro::DynamicType::linear );
				} else {
					newDecomposition.subspaceTypes.push_back( decomposition.subspaceTypes[i] );
				}
			}
		}
		if ( discreteVars.size() > 0 ) {
			// composition assumes for simplicity that subspace variables are ordered
			std::sort( discreteVars.begin(), discreteVars.end() );
			newDecomposition.subspaces.push_back( discreteVars );
			newDecomposition.subspaceTypes.push_back( hypro::DynamicType::discrete );
		}
		// decompse with merged discrete subspaces
		auto automatonCopy = automaton;
		automatonCopy.decompose( newDecomposition.subspaces );
		decomposedHa = automatonCopy;
		decomposition = newDecomposition;
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
