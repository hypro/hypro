#pragma once

#include "flags.h"

#ifdef HYPRO_STATISTICS
#ifndef INCL_FROM_CTR_REPO
	static_assert(false, "This file may only be included indirectly by CounterRepository.h");
#endif


#include "util/multithreading/ScopedLock.h"
#include <mutex>

namespace hypro {

	/**
	 * @brief      An operation counter based on stackoverflow.com/questions/11365351/how-to-implement-efficient-c-runtime-statistics
	 */
	struct OperationCounter {
		std::mutex mtx;
		unsigned long val;
		unsigned long operator++() { return ++val; }
		operator unsigned long() const { return val; }
		void reset() { ScopedLock(mtx); val = 0; }
		OperationCounter(std::string name);
	};

	struct AtomicOperationCounter : public OperationCounter {
		unsigned long operator++() { ScopedLock(mtx); return ++val; }
		AtomicOperationCounter(std::string name) : OperationCounter(name) {}
	};

} // namespace hypro

#endif
