/**
 * Implementation of a timer used for benchmarks.
 * @file Timer.h
 *
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since 	2015-03-19
 * @version 	2015-03-19
 */

#pragma once

#include <chrono>

namespace hypro {

class Timer {
  private:
	std::chrono::high_resolution_clock::time_point mStart;

  public:
	Timer() : mStart( std::chrono::high_resolution_clock::now() ) {}

	double elapsed() {
		std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
		return std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1, 1000>>>( now - mStart ).count();
	}
};
}  // namespace hypro
