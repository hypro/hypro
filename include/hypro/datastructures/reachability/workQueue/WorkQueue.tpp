#include "WorkQueue.h"

#include <assert.h>
#include <mutex>
#include <sstream>

namespace hypro {
template <class Workable, class Setting>
void WorkQueueT<Workable, Setting>::pushFront( const Workable& item ) {
	assert( item != nullptr );
	TRACE( "hypro.datastructures", "Locked push front." );
	std::unique_lock<std::mutex> lock( mQueueLock );
	this->nonLockingPushFront( item );
}

template <class Workable, class Setting>
void WorkQueueT<Workable, Setting>::nonLockingPushFront( const Workable& item ) {
	TRACE( "hypro.datastructures", "Push front." );
	assert( item != nullptr );
	if ( Setting::findDuplicates ) {
		if ( !nonLockingExists( item ) ) {
			mQueue.push_front( item );
		}
		return;
	}
	mQueue.push_front( item );
}

template <class Workable, class Setting>
void WorkQueueT<Workable, Setting>::enqueue( Workable&& item ) {
	assert( item != nullptr );
	TRACE( "hypro.datastructures", "Locked enqueue." );
	std::unique_lock<std::mutex> lock( mQueueLock );
	this->nonLockingEnqueue( std::move( item ) );
}

template <class Workable, class Setting>
void WorkQueueT<Workable, Setting>::nonLockingEnqueue( Workable&& item ) {
	TRACE( "hypro.datastructures", "Enqueue." );
	assert( item != nullptr );
	if ( Setting::findDuplicates ) {
		if ( !nonLockingExists( item ) ) {
			mQueue.emplace_back( std::move( item ) );
		}
		return;
	}
	mQueue.emplace_back( std::move( item ) );
}

template <class Workable, class Setting>
bool WorkQueueT<Workable, Setting>::exists( const Workable& item ) {
	TRACE( "hypro.datastructures", "Locked exists." );
	std::unique_lock<std::mutex> lock( mQueueLock );
	return nonLockingExists( item );
}

template <class Workable, class Setting>
bool WorkQueueT<Workable, Setting>::nonLockingExists( const Workable& item ) {
	assert( item != nullptr );
	TRACE( "hypro.datastructures", "Exists." );
	for ( const auto& elem : mQueue ) {
		if ( elem == item ) {
			return true;
		}
	}
	return false;
}

template <class Workable, class Setting>
Workable WorkQueueT<Workable, Setting>::dequeueFront() {
	TRACE( "hypro.datastructures", "Locked dequeue front." );
	std::unique_lock<std::mutex> lock( mQueueLock );
	return nonLockingDequeueFront();
}

template <class Workable, class Setting>
Workable WorkQueueT<Workable, Setting>::nonLockingDequeueFront() {
	TRACE( "hypro.datastructures", "Dequeue front." );
	if ( this->nonLockingIsEmpty() ) {
		return nullptr;
	}
	Workable item{ std::move( mQueue.front() ) };
	mQueue.pop_front();
	assert( item != nullptr );
	return item;
}

template <class Workable, class Setting>
Workable WorkQueueT<Workable, Setting>::dequeueBack() {
	TRACE( "hypro.datastructures", "Locked dequeue back." );
	std::unique_lock<std::mutex> lock( mQueueLock );
	return nonLockingDequeueBack();
}

template <class Workable, class Setting>
Workable WorkQueueT<Workable, Setting>::nonLockingDequeueBack() {
	TRACE( "hypro.datastructures", "Dequeue back." );
	if ( this->nonLockingIsEmpty() ) {
		return nullptr;
	}
	Workable item = mQueue.back();
	mQueue.pop_back();
	assert( item != nullptr );
	return item;
}

template <class Workable, class Setting>
bool WorkQueueT<Workable, Setting>::isEmpty() const {
	TRACE( "hypro.datastructures", "Locked is empty." );
	std::unique_lock<std::mutex> lock( mQueueLock );
	return nonLockingIsEmpty();
}

template <class Workable, class Setting>
bool WorkQueueT<Workable, Setting>::nonLockingIsEmpty() const {
	TRACE( "hypro.datastructures", "Is empty." );
	return mQueue.empty();
}

template <class Workable, class Setting>
std::size_t WorkQueueT<Workable, Setting>::nonLockingSize() const {
	TRACE( "hypro.datastructures", "Size." );
	return mQueue.size();
}

template <class Workable, class Setting>
std::size_t WorkQueueT<Workable, Setting>::size() const {
	TRACE( "hypro.datastructures", "Locked size. (@" << this << ")" );
	std::unique_lock<std::mutex> lock( mQueueLock );
	return nonLockingSize();
}
}  // namespace hypro
