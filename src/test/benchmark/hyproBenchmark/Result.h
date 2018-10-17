/**
 * @brief Struct representing a result.
 * 
 * @file Result.h
 * @author Stefan Schupp
 * @date 2018-09-28
 */
#pragma once

#include <chrono>
#include <string>

namespace benchmark {

template<typename Data>
struct Result {
    std::string mName;                              // name as a reference
    std::chrono::duration<double> mRunningTime;     // running time
    int mDimension = 1;                             // the dimension of the state space
    Data mContent;                                  // some result data

public:
    Result(const std::string& name, const std::chrono::duration<double>& runningTime) :
        mName(name)
        ,mRunningTime(runningTime)
    {}

    Result(const std::string& name, const std::chrono::duration<double>& runningTime, int dim) :
        mName(name)
        ,mRunningTime(runningTime)
        ,mDimension(dim)
    {}
};

} // namespace benchmark