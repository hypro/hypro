/**
 * @brief A struct for a collection of results.
 * 
 * @file Results.h
 * @author Stefan Schupp
 * @date 2018-09-28
 */
#pragma once

#include "Result.h"
#include <vector>

namespace benchmark
{
struct Results {
    std::vector<Result> mResults;
};   
} // benchmark
