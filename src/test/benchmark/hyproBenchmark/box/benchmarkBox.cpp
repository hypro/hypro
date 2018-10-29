#include "benchmarkBox.h"

namespace benchmark{
namespace box
{

    Results<std::size_t> run(const Settings& settings) {
        Timer totalRunningTime;
        Results<std::size_t> ress;

        // half-space intersection
        std::cout << "Benchmarking half space intersection." << std::endl;
        auto tmp = intersectHalfspace(settings);
        tmp.createCSV("boxIntersectHalfspace", "\t", "intersectHalfspace");
        tmp.createCSV("boxIntersectHalfspacePPL", "\t", "intersectHalfspacePPL");
        ress.insert(ress.end(), tmp.begin(), tmp.end());       

        // affine transformation
        std::cout << "Benchmarking affine transformation." << std::endl;
        tmp = affineTransformation(settings);
        tmp.createCSV("boxAffineTransformation", "\t");
        ress.insert(ress.end(), tmp.begin(), tmp.end());

        // union
        std::cout << "Benchmarking union." << std::endl;
        tmp = unite(settings);
        tmp.createCSV("boxUnion", "\t");
        ress.insert(ress.end(), tmp.begin(), tmp.end());

        // intersection
        std::cout << "Benchmarking intersection." << std::endl;
        tmp = intersect(settings);
        tmp.createCSV("boxIntersection", "\t","intersect");
        tmp.createCSV("boxIntersectionPPL", "\t", "intersectPPL");
        ress.insert(ress.end(), tmp.begin(), tmp.end());

        std::cout << "Box benchmarking took " << totalRunningTime.elapsedMs() << " sec in total." << std::endl;

        return ress;
    }
} // box    
} // benchmark
