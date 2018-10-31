#include "benchmarkBox.h"

namespace benchmark{
namespace box
{

    Results<std::size_t> run(const Settings& settings) {
        Timer totalRunningTime;
        Results<std::size_t> ress;
        std::vector<std::future<Results<std::size_t>>> workingTasks;

        workingTasks.emplace_back(std::async(std::launch::async,intersectHalfspace,settings));
        workingTasks.emplace_back(std::async(std::launch::async,affineTransformation,settings));
        workingTasks.emplace_back(std::async(std::launch::async,unite,settings));
        workingTasks.emplace_back(std::async(std::launch::async,intersect,settings));

        // half-space intersection
        auto tmp = workingTasks[0].get();
        tmp.createCSV("boxIntersectHalfspace", "\t", "intersectHalfspace");
        tmp.createCSV("boxIntersectHalfspacePPL", "\t", "intersectHalfspacePPL");

        // affine transformation
        tmp = workingTasks[1].get();
        tmp.createCSV("boxAffineTransformation", "\t");

        // union
        tmp = workingTasks[2].get();
        tmp.createCSV("boxUnion", "\t");

        // intersection
        tmp = workingTasks[3].get();
        tmp.createCSV("boxIntersection", "\t","intersect");
        tmp.createCSV("boxIntersectionPPL", "\t", "intersectPPL");

        return ress;
    }
} // box    
} // benchmark
