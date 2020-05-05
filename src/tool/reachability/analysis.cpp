#include "analysis.h"

namespace hydra
{
namespace reachability
{

using namespace hypro;

template <typename State>
void concrete_analyze(HybridAutomaton<Number> &automaton, Setting setting) {
  LTIAnalyzer<State> analyzer{automaton, setting};
  auto result = analyzer.run();

  if (result == REACHABILITY_RESULT::UNKNOWN)
  {
    std::cout << "Could not verify safety." << std::endl;
    // Call bad state handling (e.g., return path)
  }
  else
  {
    std::cout << "The model is safe." << std::endl;
  }

  // call to plotting.
}

struct Dispatcher {
  template <typename Rep>
  void operator()(HybridAutomaton<Number> &automaton, Setting setting)
  {
    using concreteState = hypro::State<hydra::Number, Rep>;
    concrete_analyze<concreteState>(automaton, setting);
  }
};

void analyze(HybridAutomaton<Number> &automaton, Setting setting) {
  dispatch<hydra::Number, Converter<hydra::Number>>(setting.strategy.front().representation_type,
                                                    setting.strategy.front().representation_setting, Dispatcher{}, automaton, setting);
}

} // namespace reachability
} // namespace hydra
