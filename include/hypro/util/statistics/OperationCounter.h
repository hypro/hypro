/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <hypro/flags.h>

#include "../multithreading/ScopedLock.h"

#include <mutex>

namespace hypro {
namespace statistics {

/**
 * @brief      An operation counter based on stackoverflow.com/questions/11365351/how-to-implement-efficient-c-runtime-statistics
 */
struct OperationCounter {
	std::mutex mMtx;
	unsigned long val = 0;
	unsigned long operator++() { return ++val; }
	unsigned long operator++( int ) { return val++; }
	operator unsigned long() const { return val; }
	void reset() {
		ScopedLock<std::mutex>( this->mMtx );
		val = 0;
	}

	friend std::ostream& operator<<( std::ostream& ostr, const OperationCounter& opCnt ) {
		ostr << opCnt.val;
		return ostr;
	}
};

struct AtomicOperationCounter : public OperationCounter {
	unsigned long operator++() {
		ScopedLock<std::mutex>( this->mMtx );
		return ++val;
	}

	unsigned long operator++( int ) {
		ScopedLock<std::mutex>( this->mMtx );
		return val++;
	}
};

struct AtomicCounter : public OperationCounter {
	unsigned long operator++() {
		ScopedLock<std::mutex>( this->mMtx );
		return ++val;
	}

	unsigned long operator++( int ) {
		ScopedLock<std::mutex>( this->mMtx );
		return ++val;
	}

	unsigned long operator--() {
		ScopedLock<std::mutex>( this->mMtx );
		return --val;
	}

	unsigned long operator--( int ) {
		ScopedLock<std::mutex>( this->mMtx );
		return val--;
	}
};

}  // namespace statistics
}  // namespace hypro

