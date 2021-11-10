/*
 * Copyright (c) 2021.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

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
#include <fstream>
#include <hypro/util/convenienceOperators.h>
#include <iostream>
#include <string>
#include <vector>

namespace benchmark {
template <typename Data>
struct Results {
	std::vector<Result<Data>> mResults;
	std::chrono::duration<double> mCreationTime = std::chrono::duration<double>::zero();
	std::chrono::duration<double> mRunningTime = std::chrono::duration<double>::zero();

	auto begin() const { return mResults.begin(); }
	auto begin() { return mResults.begin(); }
	auto end() const { return mResults.end(); }
	auto end() { return mResults.end(); }

	auto push_back( const Result<Data>& in ) { return mResults.push_back( in ); }
	auto emplace_back( Result<Data>&& in ) { return mResults.emplace_back( std::move( in ) ); }
	auto insert( typename std::vector<Result<Data>>::iterator pos, typename std::vector<Result<Data>>::iterator inStart,
				 typename std::vector<Result<Data>>::iterator inEnd ) {
		return mResults.insert( pos, inStart, inEnd );
	}

	void createCSV( const std::string& filename, const std::string& delimiter = " ", const std::string& filter = "" ) {
		std::ofstream fstr;
		fstr.open( filename );
		fstr << "dimension" << delimiter << "rt\n";
		for ( const auto& r : mResults ) {
			// if results are filtered, apply filter.
			if ( filter != "" ) {
				if ( r.mName == filter ) {
					fstr << r.mDimension << delimiter;
					for ( const auto& i : r.mContent ) fstr << i << delimiter;
					fstr << r.mRunningTime.count() << "\n";
				}
			} else {
				fstr << r.mDimension << delimiter;
				for ( const auto& i : r.mContent ) fstr << i << delimiter;
				fstr << r.mRunningTime.count() << "\n";
			}
		}

		fstr.close();
	}
};
}  // namespace benchmark
