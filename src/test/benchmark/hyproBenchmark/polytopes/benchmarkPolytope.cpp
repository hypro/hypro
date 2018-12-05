#include "benchmarkPolytope.h"

namespace benchmark{
namespace polytope
{

    Results<int> run(const Settings& settings) {
        Timer totalRunningTime;
        Results<int> ress;

        // half-space intersection
        std::cout << "Benchmarking half space intersection." << std::endl;
        auto tmp = intersectHalfspace(settings);
        tmp.createCSV("polytopeIntersectHalfspace", "\t", "intersectHalfspace");
        tmp.createCSV("polytopeIntersectHalfspacePPL", "\t", "intersectHalfspacePPL");
        ress.insert(ress.end(), tmp.begin(), tmp.end());       

        // affine transformation
        std::cout << "Benchmarking affine transformation." << std::endl;
        tmp = affineTransformation(settings);
        tmp.createCSV("polytopeAffineTransformation", "\t");
        ress.insert(ress.end(), tmp.begin(), tmp.end());

        // union
        std::cout << "Benchmarking union." << std::endl;
        tmp = unite(settings);
        tmp.createCSV("polytopeUnion", "\t");
        ress.insert(ress.end(), tmp.begin(), tmp.end());

        // intersection
        std::cout << "Benchmarking intersection." << std::endl;
        tmp = intersect(settings);
        tmp.createCSV("polytopeIntersection", "\t","intersect");
        tmp.createCSV("polytopeIntersectionPPL", "\t", "intersectPPL");
        ress.insert(ress.end(), tmp.begin(), tmp.end());

        std::cout << "Polytope benchmarking took " << totalRunningTime.elapsedMs() << " sec in total." << std::endl;

        return ress;
    }
} // polytope    
} // benchmark
