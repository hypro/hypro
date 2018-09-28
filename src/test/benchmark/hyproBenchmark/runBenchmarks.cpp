/**
 * @brief Main file which starts all benchmark runs.
 * 
 * @file runBenchmarks.cpp
 * @author your name
 * @date 2018-09-28
 */

#include "types.h"
#include "Clock.h"
#include "benchmarkBox.h"
#include <representations/GeometricObject.h>
#include <iostream>

int main(int argc, char const *argv[])
{
    benchmark::Timer general;

    benchmark::box::run();

    std::cout << "Benchmarking took " << general.elapsedMs() << "ms." << std::endl;
    return 0;
}
