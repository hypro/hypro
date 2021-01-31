#include "preprocessing.h"

namespace hydra {
namespace preprocessing {
hypro::PreprocessingInformation preprocess( const hypro::HybridAutomaton<hydra::Number>& automaton,
											const hypro::ReachabilitySettings& reachSettings,
                                            bool decompose ) {
	auto dynamicsType = hypro::getDynamicType( automaton );
    hypro::PreprocessingInformation information{ dynamicsType };

    if ( decompose ) {
        auto [decomposedHa, decomposition] = hypro::decomposeAutomaton( automaton );
        for ( std::size_t subspace = 0; subspace < decomposition.subspaceTypes.size(); ++subspace ) {
            if ( isClockedSubspace( decomposition.subspaceTypes[ subspace ] ) ) {
                hypro::addClockToAutomaton( decomposedHa, subspace, reachSettings.jumpDepth + 1 );
            }
        }
        information.decomposition = decomposition;
        information.decomposedHa = decomposedHa;
    }
	return information;
}

}  // namespace preprocessing
}  // namespace hydra
