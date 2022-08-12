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
