#pragma once

#include "flags.h"

#ifdef HYPRO_STATISTICS
#define INCL_FROM_CTR_REPO

#include "OperationCounter.h"
#include "util/multithreading/ScopedLock.h"
#include <mutex>

namespace hypro {

	struct CounterRepository {
		using CounterMapType = std::map<string, Counter*>;

		std::mutex mtx;
		CounterMapType counterMap;

		void add(std::string name, Counter& c) {
			ScopedLock(mtx);
			if(counterMap.find(name) != counterMap.end()) {
				throw n;
			}
			counterMap[name] = &c;
		}

		Counter& get(std::string name) const {
			ScopedLock(mtx);
			auto counterIt = counterMap.find(name);
			if( counterIt == counterMap.end() ) {
				throw n;
			}
			return *(counterIt->second);
		}

	};

	CounterRepository counterRepository;

	Counter::Counter(std::string name) {
		counterRepository.add(name, *this);
	}

} // namespace hypro

#endif
