/**
 * @brief Example file which shows how to instanciate a concrete worker out of context handlers.
 */

#include <algorithms/reachability/workers/ContextBasedReachabilityWorker.h>

int main() {
    hypro::ReachabilitySettings<hypro::tNumber> settings;

    hypro::ContextBasedReachabilityWorker<double> worker = hypro::ContextBasedReachabilityWorker<double>(settings);
	return 0;
}
