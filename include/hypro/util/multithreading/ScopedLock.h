#pragma once

#include <mutex>

namespace hypro {

/**
 * @brief      Class for scoped lock, taken from http://stackoverflow.com/questions/14276508/how-does-scope-locking-work
 */
template <typename Lockable>
class ScopedLock {
  private:
	Lockable& _mtx;	 // keep ref to the mutex passed to the constructor
  public:
	explicit ScopedLock( Lockable& mtx )
		: _mtx( mtx ) {
		_mtx.lock();  // lock the mutex in the constructor
	}
	~ScopedLock() {
		_mtx.unlock();	// unlock the mutex in the constructor
	}
};

}  // namespace hypro
