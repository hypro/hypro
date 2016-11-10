#pragma once

#include "flags.h"
#include <carl/util/Singleton.h>

#define PRINT_STATS()
#define RESET_STATS()

#ifdef HYPRO_STATISTICS

#define INCL_FROM_STATISTICS

#include "CounterRepository.h"

namespace hypro {

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

} // namespace

#undef PRINT_STATS
#undef RESET_STATS
#define PRINT_STATS() std::cout << hypro::Statistician::getInstance() << std::endl;
#define RESET_STATS() hypro::Statistician::getInstance().reset();

#endif
