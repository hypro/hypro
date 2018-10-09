/**
 * @brief A struct for a collection of results.
 * 
 * @file Results.h
 * @author Stefan Schupp
 * @date 2018-09-28
 */
#pragma once

#include "Result.h"
#include <chrono>
#include <vector>

namespace benchmark
{
template<typename Data>
struct Results {
    std::vector<Result<Data>> mResults;
    std::chrono::duration<double> mCreationTime = std::chrono::duration<double>::zero();
    std::chrono::duration<double> mRunningTime = std::chrono::duration<double>::zero();

    auto begin() const {return mResults.begin();}
    auto begin() {return mResults.begin();}
    auto end() const {return mResults.end();}
    auto end() {return mResults.end();}

    auto push_back(const Result<Data>& in) {return mResults.push_back(in);}
    auto insert(auto pos, auto inStart, auto inEnd) {return mResults.insert(pos,inStart,inEnd);}
};   
} // benchmark
