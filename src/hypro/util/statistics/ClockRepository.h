#pragma once

#include "../../flags.h"

//#ifdef HYPRO_STATISTICS
#ifndef INCL_FROM_STATISTICS
static_assert( false, "This file may only be included indirectly by statistics.h" );
#endif

#define INCL_FROM_CTR_REPO

#include "../multithreading/ScopedLock.h"
#include "Clock.h"

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
class ClockRepository {
  private:
	using timerMapType = std::map<std::string, Clock*>;

	mutable std::mutex mtx;	 ///< lock to enable mutable exclusive access to counters
	timerMapType timerMap;	 ///< stored timers

  public:
	/// adds a counter
	void add( std::string name ) {
		ScopedLock<std::mutex>( this->mtx );
		if ( timerMap.find( name ) == timerMap.end() ) {
			timerMap[name] = new Clock();
		}
	}

	/// resets all counters
	void reset() {
		ScopedLock<std::mutex>( this->mtx );
		timerMap.clear();
	}

	/// getter for a specific counter
	Clock& get( std::string name ) {
		ScopedLock<std::mutex> lock( this->mtx );
		auto counterIt = timerMap.find( name );
		if ( counterIt == timerMap.end() ) {
			counterIt = timerMap.insert( std::make_pair( name, new Clock() ) ).first;
		}
		return *( counterIt->second );
	}

	/// returns number of stored counters
	std::size_t size() const {
		ScopedLock<std::mutex>( this->mtx );
		return timerMap.size();
	}

	/// outstream operator outputs all current counter values
	friend std::ostream& operator<<( std::ostream& ostr, const ClockRepository& repo ) {
		for ( const auto& counterPair : repo.timerMap ) {
			ostr << counterPair.first << ": " << *counterPair.second << std::endl;
		}
		return ostr;
	}
};

}  // namespace statistics
}  // namespace hypro

//#endif
