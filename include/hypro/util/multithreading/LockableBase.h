#pragma once
#include <mutex>

namespace hypro {

class LockableBase {
  private:
	mutable std::mutex mutex;

  public:
	std::mutex& getMutex() const { return mutex; }
};

}  // namespace hypro
