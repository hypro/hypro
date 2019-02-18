/**
 * @brief Main file which starts all benchmark runs.
 *
 * @file runBenchmarks.cpp
 * @author your name
 * @date 2018-09-28
 */

#include <flags.h>
#include "types.h"
#include "Clock.h"
#include "Settings.h"
#include "box/benchmarkBox.h"
#include "polytopes/benchmarkPolytope.h"
#include "supportFunction/benchmark_sf.h"
#include <representations/GeometricObject.h>
#include <iostream>
#include <future>

int main(int argc, char const *argv[])
{
    benchmark::Timer general;
    benchmark::Settings s;
    
    std::cout << "Benchmark boxes." << std::endl;
    benchmark::box::run(s);

    std::cout << "Benchmark polytopes." << std::endl;
    //benchmark::polytope::run(s);

    std::cout << "Benchmark support functions." << std::endl;
    std::async(std::launch::async,benchmark::sf::run,s);

    std::cout << "Benchmarking took " << general.elapsedMs() << " sec." << std::endl;
    return 0;
}
