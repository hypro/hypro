#include "preprocessing.h"

namespace hydra {
namespace preprocessing {
hypro::PreprocessingInformation preprocess( const hypro::HybridAutomaton<hydra::Number>& automaton,
                                            bool decompose,
                                            std::size_t clockCount ) {
	auto dynamicsType = hypro::getDynamicType( automaton );
    hypro::PreprocessingInformation information{ dynamicsType };

    if ( decompose ) {
        auto [decomposedHa, decomposition] = hypro::decomposeAutomaton( automaton );
        for ( std::size_t subspace = 0; subspace < decomposition.subspaceTypes.size(); ++subspace ) {
            if ( isClockedSubspace( decomposition.subspaceTypes[ subspace ] ) ) {
                hypro::addInitialVarToAutomaton( decomposedHa, subspace );
                hypro::addClocksToAutomaton( decomposedHa, subspace, clockCount );
            }
        }
        information.decomposition = decomposition;
        information.decomposedHa = decomposedHa;
    }
	return information;
}

}  // namespace preprocessing
}  // namespace hydra
