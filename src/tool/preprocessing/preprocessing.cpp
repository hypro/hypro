#include "preprocessing.h"

namespace hydra {
namespace preprocessing {
hypro::PreprocessingInformation preprocess( const hypro::HybridAutomaton<hydra::Number> &,
											const hypro::ReachabilitySettings & ) {
	// do some preprocessing, write results to the settingsProvider.
	return hypro::PreprocessingInformation{};
}

}  // namespace preprocessing
}  // namespace hydra
