#include <mutex>

namespace hypro {

template <typename Object>
class LockableObjectWrapper {
  private:
	Object instance;
	std::recursive_mutex mutex;
	int numLocks = 0;

  public:
	LockableObjectWrapper() = delete;

	~LockableObjectWrapper() {
		// ensure the lock is freed upon destruction.
		while ( numLocks > 0 )
			mutex.unlock();
	}

	LockableObjectWrapper( Object instance )
		: instance( instance ) {}

	Object& getLockedInstance() {
		mutex.lock();
		++numLocks;
		return instance;
	}

	void unlockInstance() {
		--numLocks;
		mutex.unlock();
	}

	int getNumLocks() const {
		return numLocks;
	}
};

}  // namespace hypro
