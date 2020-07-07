#pragma once

#include "../../flags.h"

#include <carl/util/Singleton.h>

#define PRINT_STATS()
#define RESET_STATS()
#define COUNT( expr )
#define START_BENCHMARK_OPERATION( expr )
#define EVALUATE_BENCHMARK_RESULT( expr )

#ifdef HYPRO_STATISTICS
#define INCL_FROM_STATISTICS

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
	CounterRepository counters;

  public:
	/// destructor
	~Statistician() {}

	/// adds a counter
	void add( std::string name ) {
		counters.add( name );
	}

	/// getter for counter
	OperationCounter& get( std::string name ) {
		return counters.get( name );
	}

	/// resets all counters
	void reset() {
		counters.reset();
	}

	/// outputs all current counter values
	friend std::ostream& operator<<( std::ostream& ostr, const Statistician& stats ) {
		ostr << "Statistics:" << std::endl;
		ostr << stats.counters;
		return ostr;
	}
};

}  // namespace statistics
}  // namespace hypro

#undef PRINT_STATS
#undef RESET_STATS
#undef COUNT
#undef START_BENCHMARK_OPERATION
#undef EVALUATE_BENCHMARK_RESULT
#define PRINT_STATS() std::cout << hypro::statistics::Statistician::getInstance() << std::endl;
#define RESET_STATS() hypro::statistics::Statistician::getInstance().reset();
#define COUNT( expr ) ++hypro::statistics::Statistician::getInstance().get( expr );
#define START_BENCHMARK_OPERATION( name ) std::chrono::high_resolution_clock::time_point name = std::chrono::high_resolution_clock::now()
#define EVALUATE_BENCHMARK_RESULT( name )                                                                              \
	do {                                                                                                               \
		std::chrono::high_resolution_clock::time_point name##_##end = std::chrono::high_resolution_clock::now();       \
		COUT( #name << " took " << std::chrono::duration<double>( name##_##end - name ).count() << "s" << std::endl ); \
	} while ( 0 )

#endif
