#include "benchmarkBox.h"

namespace benchmark{
namespace box
{
    Results run(const Settings& settings) {
        Timer totalRunningTime;
        Results ress;

        // half-space intersection
        hypro::Box<::Number> box;
        box.addInterval(carl::Interval<::Number>(-1,1));
        for(std::size_t d = 1; d < settings.maxDimension; ++d) {
            // create instances
            for(std::size_t i = 0; i < settings.iterations; ++i) {
                
            }
            box.addInterval(carl::Interval<::Number>(-1,1));
        }

        

        std::cout << "Box benchmarking took " << totalRunningTime.elapsedMs() << " in total." << std::endl;

        return ress;
    }
} // box    
} // benchmark
