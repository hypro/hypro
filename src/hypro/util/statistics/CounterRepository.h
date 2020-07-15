#pragma once

#include "../../flags.h"

//#ifdef HYPRO_STATISTICS
#ifndef INCL_FROM_STATISTICS
static_assert( false, "This file may only be included indirectly by statistics.h" );
#endif

#define INCL_FROM_CTR_REPO

#include "../multithreading/ScopedLock.h"
#include "OperationCounter.h"

#include <map>
#include <mutex>
#include <string>

namespace hypro {
/**
 * \namespace statistics
 * \brief namespace encapsulating all statistics related code.
 */
namespace statistics {

/**
 * @brief Class which stores counters identified by strings
 */
class CounterRepository {
  private:
	using CounterMapType = std::map<std::string, OperationCounter*>;

	mutable std::mutex mtx;		///< lock to enable mutable exclusive access to counters
	CounterMapType counterMap;	///< stored counters

  public:
	/// adds a counter
	void add( std::string name ) {
		ScopedLock<std::mutex>( this->mtx );
		if ( counterMap.find( name ) == counterMap.end() ) {
			counterMap[name] = new OperationCounter();
		}
	}

	/// resets all counters
	void reset() {
		ScopedLock<std::mutex>( this->mtx );
		counterMap.clear();
	}

	/// getter for a specific counter
	OperationCounter& get( std::string name ) {
		ScopedLock<std::mutex>( this->mtx );
		auto counterIt = counterMap.find( name );
		if ( counterIt == counterMap.end() ) {
			counterIt = counterMap.insert( std::make_pair( name, new OperationCounter() ) ).first;
		}
		return *( counterIt->second );
	}

	/// returns number of stored counters
	std::size_t size() const {
		ScopedLock<std::mutex>( this->mtx );
		return counterMap.size();
	}

	/// outstream operator outputs all current counter values
	friend std::ostream& operator<<( std::ostream& ostr, const CounterRepository& repo ) {
		for ( const auto& counterPair : repo.counterMap ) {
			ostr << counterPair.first << ": " << *counterPair.second << std::endl;
		}
		return ostr;
	}
};

}  // namespace statistics
}  // namespace hypro

//#endif
