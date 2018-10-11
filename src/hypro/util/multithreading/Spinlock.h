#pragma once
#include <unistd.h>
#include <atomic>

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

} // hypro
