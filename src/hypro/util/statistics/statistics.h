#pragma once

#include "../../flags.h"

#include <carl/util/Singleton.h>

#define PRINT_STATS()
#define RESET_STATS()
#define COUNT( expr )
#define START_BENCHMARK_OPERATION( expr )
#define STOP_BENCHMARK_OPERATION( expr )
#define EVALUATE_BENCHMARK_RESULT( expr )

#ifdef HYPRO_STATISTICS
#define INCL_FROM_STATISTICS

#include "ClockRepository.h"
#include "CounterRepository.h"

namespace hypro {
namespace statistics {

/**
 * @brief Class which implements several counters on demand
 *
 */
class Statistician : public carl::Singleton<Statistician> {
	friend carl::Singleton<Statistician>;

  private:
	CounterRepository counters;	 ///< holds all counters
	ClockRepository timers;		 ///< holds all timers

  public:
	/// destructor
	~Statistician() {}

	/// adds a counter
	void add( std::string name ) {
		counters.add( name );
	}

	/// getter for counter
	OperationCounter& getCounter( std::string name ) {
		return counters.get( name );
	}

	/// getter for Timer
	Clock& getTimer( std::string name ) {
		return timers.get( name );
	}

	/// starts a timer
	void startTimer( std::string name ) {
		timers.get( name ).start();
	}

	/// stops a timer
	void stopTimer( std::string name ) {
		timers.get( name ).stop();
	}

	/// resets all counters
	void reset() {
		counters.reset();
		timers.reset();
	}

	/// outputs all current counter values
	friend std::ostream& operator<<( std::ostream& ostr, const Statistician& stats ) {
		ostr << "Counters:" << std::endl;
		ostr << stats.counters << std::endl;
		ostr << "Timers:" << std::endl;
		ostr << stats.timers << std::endl;
		return ostr;
	}
};

}  // namespace statistics
}  // namespace hypro

#undef PRINT_STATS
#undef RESET_STATS
#undef COUNT
#undef START_BENCHMARK_OPERATION
#undef STOP_BENCHMARK_OPERATION
#undef EVALUATE_BENCHMARK_RESULT
#define PRINT_STATS() std::cout << hypro::statistics::Statistician::getInstance() << std::endl;
#define RESET_STATS() hypro::statistics::Statistician::getInstance().reset();
#define COUNT( expr ) ++hypro::statistics::Statistician::getInstance().getCounter( expr );
#define START_BENCHMARK_OPERATION( name ) \
	hypro::statistics::Statistician::getInstance().startTimer( name );
#define STOP_BENCHMARK_OPERATION( name ) \
	hypro::statistics::Statistician::getInstance().stopTimer( name );
#define EVALUATE_BENCHMARK_RESULT( name )                             \
	hypro::statistics::Statistician::getInstance().stopTimer( name ); \
	std::cout << name << ": " << hypro::statistics::Statistician::getInstance().getTimer( name ) << std::endl;
#endif
