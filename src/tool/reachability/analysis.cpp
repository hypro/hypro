#include "analysis.h"

namespace hydra {
namespace reachability {
void analyze() {
  // create appropriate Context
  LTIAnalyzer analyzer();
  analyzer.run();
}
} // namespace reachability
} // namespace hydra
