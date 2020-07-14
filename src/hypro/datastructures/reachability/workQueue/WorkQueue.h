#pragma once

#include "../../../util/logging/Logger.h"
#include "../../../util/typetraits.h"
#include "WorkQueueSettings.h"

#include <assert.h>
#include <chrono>
#include <condition_variable>
#include <iosfwd>
#include <mutex>
#include <queue>
#include <string>

namespace hypro {

/**
 * Class encapsulating a thread safe queue in order to be accessed by
 * multiple workers.
 */
template <class Workable, class Setting>
class WorkQueueT {
	static_assert( std::is_pointer<Workable>::value || is_shared_ptr<Workable>::value || is_unique_ptr<Workable>::value, "WorkQueue requires pointer type." );

  protected:
	std::deque<Workable> mQueue;
	mutable std::mutex mSpinlock;

  public:
	using Workable_t = Workable;

	WorkQueueT() = default;
	WorkQueueT( WorkQueueT<Workable, Setting>&& in ) = delete;
	WorkQueueT( const WorkQueueT<Workable, Setting>& in ) = delete;

	/**
     * Destructor
     **/
	~WorkQueueT(){};

	/**
     * Pushed an Workable to the front of the queue.
     *
     * @param item item to be pushed at the front
     */
	void pushFront( const Workable& item );
	void nonLockingPushFront( const Workable& item );

	/**
     * enqueues an item
     * @param item item to be enqueued
     */
	void enqueue( Workable&& item );
	void nonLockingEnqueue( Workable&& item );

	/**
     *  dequeues an item by removing it from the queue and returning it
     *
     *  @return the Workable
     */
	Workable dequeueFront();
	Workable nonLockingDequeueFront();

	Workable dequeueBack();
	Workable nonLockingDequeueBack();

	/**
     * checks whether the queue is empty
     *
     * @return true iff no Workable is left.
     */
	bool isEmpty() const;
	bool nonLockingIsEmpty() const;

	std::size_t size() const;
	std::size_t nonLockingSize() const;

	bool exists( const Workable& item );
	bool nonLockingExists( const Workable& item );

	std::mutex& getMutex() { return mSpinlock; }

	friend std::ostream& operator<<( std::ostream& out, const WorkQueueT& queue ) {
		for ( auto elem : queue.getQueue() ) {
			out << elem << std::endl;
		}
		return out;
	}

  private:
	inline const std::deque<Workable>& getQueue() const { return mQueue; }

	// TODO move NodeOperator struct somewhere and only leave its declaration here. There is no need to instantiate it with every compile.
	/*
    struct DataOperator {
        bool operator()(Workable const& lhs, Workable const& rhs)
        {
        	// TODO: Workaround - normally shared_ptr in the queue should not be nullptr (deleted).
        	if(lhs == nullptr) {
        		return false;
        	}
        	if(rhs == nullptr) {
        		return true;
        	}
        	return lhs > rhs;
        }

    };
    */
};

template <typename Workable>
using WorkQueue = WorkQueueT<Workable, WorkQueueDefaultSetting>;

}  // namespace hypro

#include "WorkQueue.tpp"
