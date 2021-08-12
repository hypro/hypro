/**
 * @brief Class wrapping a std::chrono clock.
 *
 * @file Clock.h
 * @author Stefan Schupp
 * @date 2018-09-28
 */

#include "Clock.h"
#include <chrono>

namespace benchmark {

std::chrono::duration<double> Timer::elapsed() const {
	return { std::chrono::high_resolution_clock::now() - mStart };
}

double Timer::elapsedMs() const {
	return std::chrono::duration<double>( std::chrono::high_resolution_clock::now() - mStart ).count();
}

}  // namespace benchmark
