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
#include <vector>

namespace benchmark {

template<typename Data>
struct Result {
    std::string mName;                              // name as a reference
    std::chrono::duration<double> mRunningTime;     // running time
    int mDimension = 1;                             // the dimension of the state space
    std::vector<Data> mContent;                     // some result data

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

    Result(const std::string& name, const std::chrono::duration<double>& runningTime, int dim, const Data& data) :
        mName(name)
        ,mRunningTime(runningTime)
        ,mDimension(dim)
        ,mContent()
    {
        mContent.push_back(data);
    }

    Result(const std::string& name, const std::chrono::duration<double>& runningTime, int dim, const std::vector<Data>& data) :
        mName(name)
        ,mRunningTime(runningTime)
        ,mDimension(dim)
        ,mContent(data)
    {}
};

} // namespace benchmark