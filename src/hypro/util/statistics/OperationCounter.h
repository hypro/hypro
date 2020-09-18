#pragma once

#include "../../flags.h"

#ifdef HYPRO_STATISTICS
#ifndef INCL_FROM_CTR_REPO
static_assert( false, "This file may only be included indirectly by CounterRepository.h" );
#endif

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

#endif
