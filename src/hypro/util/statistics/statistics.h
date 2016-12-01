#pragma once

#include "flags.h"
#include <carl/util/Singleton.h>

#define PRINT_STATS()
#define RESET_STATS()
#define COUNT(expr)

#ifdef HYPRO_STATISTICS
#define INCL_FROM_STATISTICS

#include "CounterRepository.h"

namespace hypro {
namespace statistics {

	class Statistician : public carl::Singleton<Statistician> {
		friend carl::Singleton<Statistician>;

	private:
		CounterRepository counters;

	public:
		~Statistician(){}

		void add(std::string name) {
			counters.add(name);
		}

		OperationCounter& get(std::string name) {
			return counters.get(name);
		}

		void reset() {
			counters.reset();
		}

		friend std::ostream& operator<<(std::ostream& ostr, const Statistician& stats) {
			ostr << "Statistics:" << std::endl;
			ostr << stats.counters;
			return ostr;
		}
	};

} // namespace statistics
} // namespace hypro

#undef PRINT_STATS
#undef RESET_STATS
#undef COUNT
#define PRINT_STATS() std::cout << hypro::statistics::Statistician::getInstance() << std::endl;
#define RESET_STATS() hypro::statistics::Statistician::getInstance().reset();
#define COUNT(expr) ++hypro::statistics::Statistician::getInstance().get(expr);

#endif
