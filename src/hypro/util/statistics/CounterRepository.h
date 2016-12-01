#pragma once

#include "flags.h"

//#ifdef HYPRO_STATISTICS
#ifndef INCL_FROM_STATISTICS
	static_assert(false, "This file may only be included indirectly by statistics.h");
#endif

#define INCL_FROM_CTR_REPO

#include "OperationCounter.h"
#include "util/multithreading/ScopedLock.h"
#include <mutex>
#include <string>
#include <map>

namespace hypro {
/**
 * \namespace statistics
 * \brief namespace encapsulating all statistics related code.
 */
namespace statistics {

		class CounterRepository {
	private:
		using CounterMapType = std::map<std::string, OperationCounter*>;

		mutable std::mutex mtx;
		CounterMapType counterMap;

	public:
		void add(std::string name) {
			ScopedLock<std::mutex>(this->mtx);
			if(counterMap.find(name) == counterMap.end()) {
				counterMap[name] = new OperationCounter();
			}
		}

		void reset() {
			ScopedLock<std::mutex>(this->mtx);
			counterMap.clear();
		}

		OperationCounter& get(std::string name) {
			ScopedLock<std::mutex>(this->mtx);
			auto counterIt = counterMap.find(name);
			if( counterIt == counterMap.end() ) {
				counterIt = counterMap.insert(std::make_pair(name, new OperationCounter())).first;
			}
			return *(counterIt->second);
		}

		std::size_t size() const {
			ScopedLock<std::mutex>(this->mtx);
			return counterMap.size();
		}

		friend std::ostream& operator<<(std::ostream& ostr, const CounterRepository& repo) {
			for(const auto& counterPair : repo.counterMap) {
				ostr << counterPair.first << ": " << *counterPair.second << std::endl;
			}
			return ostr;
		}
	};

} // namespace statistics
} // namespace hypro

//#endif
