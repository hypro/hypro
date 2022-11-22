#pragma once

#include <chrono>
#include <iostream>

class Clock {
  private:
	std::chrono::high_resolution_clock::time_point startPoint;
	std::chrono::high_resolution_clock::duration duration;
	bool running = false;

  public:
	void start() {
		if ( !running ) {
			startPoint = std::chrono::high_resolution_clock::now();
			running = true;
		}
	}

	void stop() {
		if ( running ) {
			duration += std::chrono::high_resolution_clock::now() - startPoint;
			running = false;
		}
	}

	void reset() {
		duration = std::chrono::high_resolution_clock::duration::zero();
		running = false;
	}

	friend std::ostream& operator<<( std::ostream& out, const Clock& clk ) {
		out << double( std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1, 1>>>( clk.duration ).count() ) << " s";
		return out;
	}
};