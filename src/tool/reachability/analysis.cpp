#include "analysis.h"
#include "../../hypro/util/type_handling/dispatch.h"

namespace hydra {
namespace reachability {

struct Dispatcher {
  template <typename Rep> void operator()() {
    concrete_analyze<hypro::State<hydra::Number, Rep>>();
  }
};

void analyze(DynamicStrategy strategy) {
  hypro::dispatch(strategy.front().representation_type,
                  strategy.front().representation_setting, Dispatcher);
}

template <typename State> void concrete_analyze() {
  LTIAnalyzer<State> hypro::analyzer();
  auto result == hypro::analyzer.run();

  if (result == REACHABILITY_RESULT::UNKNOWN) {
    std::cout << "Could not verify safety." << std::endl;
    // Call bad state handling (e.g., return path)
  } else {
    std::cout << "The model is safe." << std::endl;
  }

  // call to plotting.
}

} // namespace reachability
} // namespace hydra
