#include "preprocessing.h"

namespace hydra {
namespace preprocessing {
hypro::PreprocessingInformation preprocess( const hypro::HybridAutomaton<hydra::Number>& automaton,
											const hypro::ReachabilitySettings& ) {
	auto dynamicsType = getDynamicType( automaton );

	return hypro::PreprocessingInformation{ dynamicsType };
}

}  // namespace preprocessing
}  // namespace hydra
