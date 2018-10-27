#include "WorkQueue.h"
#include <assert.h>
#include <mutex>
#include <sstream>

namespace hypro {
template <class Workable, class Setting>
void WorkQueueT<Workable,Setting>::pushFront(const Workable& item)
{
	assert(item != nullptr);
    std::lock_guard<std::mutex> lock(mSpinlock);
    this->nonLockingPushFront(item);
}

template <class Workable, class Setting>
void WorkQueueT<Workable,Setting>::nonLockingPushFront(const Workable& item)
{
	assert(item != nullptr);
    std::lock_guard<std::mutex> lock(mSpinlock);
    if(Setting::findDuplicates) {
        if(!nonLockingExists(item)) {
            mQueue.push_front(item);
        }
        return;
    }
    mQueue.push_front(item);
}

template <class Workable, class Setting>
void WorkQueueT<Workable,Setting>::enqueue(const Workable& item)
{
	assert(item != nullptr);
    std::lock_guard<std::mutex> lock(mSpinlock);
    this->nonLockingEnqueue(item);
}

template <class Workable, class Setting>
void WorkQueueT<Workable,Setting>::nonLockingEnqueue(const Workable& item)
{
	assert(item != nullptr);
    if(Setting::findDuplicates) {
        if(!nonLockingExists(item)) {
            mQueue.push_back(item);
        }
        return;
    }
    mQueue.push_back(item);
}

template <class Workable, class Setting>
bool WorkQueueT<Workable,Setting>::exists(const Workable& item)
{
	std::lock_guard<std::mutex> lock(mSpinlock);
	return nonLockingExists(item);
}

template <class Workable, class Setting>
bool WorkQueueT<Workable,Setting>::nonLockingExists(const Workable& item)
{
	assert(item != nullptr);
    for (const auto& elem : mQueue) {
        if (elem == item) {
            return true;
        }
    }
    return false;
}


template <class Workable, class Setting>
Workable WorkQueueT<Workable,Setting>::dequeueFront()
{
    std::lock_guard<std::mutex> lock(mSpinlock);
    return nonLockingDequeueFront();
}

template<class Workable, class Setting>
Workable WorkQueueT<Workable,Setting>::nonLockingDequeueFront()
{
    if (this->nonLockingIsEmpty()) {
        return nullptr;
    }
    Workable item = mQueue.front();
    mQueue.pop_front();
    assert(item != nullptr);
    return item;
}

template <class Workable, class Setting>
Workable WorkQueueT<Workable,Setting>::dequeueBack()
{
    std::unique_lock<std::mutex> lock(mSpinlock);
    return nonLockingDequeueBack();
}

template<class Workable, class Setting>
Workable WorkQueueT<Workable,Setting>::nonLockingDequeueBack()
{
    if (this->nonLockingIsEmpty()) {
        return nullptr;
    }
    Workable item = mQueue.back();
    mQueue.pop_back();
    assert(item != nullptr);
    return item;
}


template <class Workable, class Setting>
bool WorkQueueT<Workable,Setting>::isEmpty() const
{
	std::unique_lock<std::mutex> lock(mSpinlock);
    return nonLockingIsEmpty();
}

template <class Workable, class Setting>
bool WorkQueueT<Workable,Setting>::nonLockingIsEmpty() const
{
    return mQueue.empty();
}

template <class Workable, class Setting>
std::size_t WorkQueueT<Workable,Setting>::nonLockingSize() const
{
    return mQueue.size();
}

template <class Workable, class Setting>
std::size_t WorkQueueT<Workable,Setting>::size() const
{
	std::lock_guard<std::mutex> lock(mSpinlock);
    return nonLockingSize();
}
}  // hypro
