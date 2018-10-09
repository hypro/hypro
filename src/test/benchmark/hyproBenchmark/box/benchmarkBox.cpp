#include "benchmarkBox.h"

namespace benchmark{
namespace box
{

    Results<int> run(const Settings& settings) {
        Timer totalRunningTime;
        Results<int> ress;

        // half-space intersection
        auto tmp = intersectHalfspaces(settings);
        ress.insert(ress.end(), tmp.begin(), tmp.end());       

        // satisfies half-spaces
        satisfiesHalfspaces(settings);

        std::cout << "Box benchmarking took " << totalRunningTime.elapsedMs() << " sec in total." << std::endl;

        return ress;
    }
} // box    
} // benchmark
