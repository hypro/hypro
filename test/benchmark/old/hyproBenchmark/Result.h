/*
 * Copyright (c) 2021.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

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

template <typename Data>
struct Result {
	std::string mName;							 // name as a reference
	std::chrono::duration<double> mRunningTime;	 // running time
	int mDimension = 1;							 // the dimension of the state space
	std::vector<Data> mContent;					 // some result data

  public:
	Result( std::string name, const std::chrono::duration<double>& runningTime )
		: mName( std::move( name ) ), mRunningTime( runningTime ) {}

	Result( std::string name, const std::chrono::duration<double>& runningTime, int dim )
		: mName( std::move( name ) ), mRunningTime( runningTime ), mDimension( dim ) {}

	Result( std::string name, const std::chrono::duration<double>& runningTime, int dim, const Data& data )
		: mName( std::move( name ) ), mRunningTime( runningTime ), mDimension( dim ), mContent() {
		mContent.push_back( data );
	}

	Result( std::string name, const std::chrono::duration<double>& runningTime, int dim, const std::vector<Data>& data )
		: mName( std::move( name ) ), mRunningTime( runningTime ), mDimension( dim ), mContent( data ) {}
};

}  // namespace benchmark