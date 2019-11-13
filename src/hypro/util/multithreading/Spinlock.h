#pragma once
#include <atomic>
#include <unistd.h>

namespace hypro {

class Spinlock {
  public:
	Spinlock() {}
	/**
     * lock Spinlock
     */
	void lock();

	/**
     * unlock Spinlock
     **/
	void unlock();

  private:
	std::atomic_flag state_ = ATOMIC_FLAG_INIT;
};

}  // namespace hypro
