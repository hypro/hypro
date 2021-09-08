/**
 * @brief Class wrapping a std::chrono clock.
 *
 * @file Clock.h
 * @author Stefan Schupp
 * @date 2018-09-28
 */
#pragma once
#include <chrono>

namespace benchmark {
class Timer {
  protected:
	std::chrono::high_resolution_clock::time_point mStart;

  public:
	Timer() : mStart( std::chrono::high_resolution_clock::now() ) {}

	std::chrono::duration<double> elapsed() const;
	double elapsedMs() const;

	void reset() { mStart = std::chrono::high_resolution_clock::now(); }
};
}  // namespace benchmark
