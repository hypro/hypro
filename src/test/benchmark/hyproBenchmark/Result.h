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
    Data mContent;                                  // some result data

public:
    Result(const std::string& name, const std::chrono::duration<double>& runningTime) :
        mName(name)
        ,mRunningTime(runningTime)
    {}
};

} // namespace benchmark