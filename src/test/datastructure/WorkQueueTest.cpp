#include "../defines.h"
#include "gtest/gtest.h"
#include <hypro/datastructures/reachability/workQueue/WorkQueue.h>
#include <hypro/datastructures/reachability/workQueue/WorkQueueManager.h>
#include <memory>

using namespace hypro;

struct Data {
	int mContent = 0;
	Data( int i ) : mContent( i ) {}
};

TEST( WorkQueueTest, Construction ) {
	using Workable = std::shared_ptr<Data>;
	WorkQueueManager<Workable> qm;

	WorkQueue<Workable>* queue1 = qm.addQueue();

	EXPECT_TRUE( queue1->nonLockingIsEmpty() );
	EXPECT_TRUE( queue1->isEmpty() );
}

TEST( WorkQueueTest, AccessNonLocking ) {
	using Workable = std::shared_ptr<Data>;
	WorkQueueManager<Workable> qm;

	WorkQueue<Workable>* queue1 = qm.addQueue();

	queue1->nonLockingEnqueue( std::make_shared<Data>( Data{ 1 } ) );
	queue1->nonLockingEnqueue( std::make_shared<Data>( Data{ 2 } ) );
	queue1->nonLockingEnqueue( std::make_shared<Data>( Data{ 3 } ) );

	EXPECT_EQ( std::size_t( 3 ), queue1->nonLockingSize() );

	auto item = queue1->nonLockingDequeueFront();
	EXPECT_EQ( 1, item->mContent );
	EXPECT_EQ( std::size_t( 2 ), queue1->nonLockingSize() );

	item = queue1->nonLockingDequeueBack();
	EXPECT_EQ( 3, item->mContent );
	EXPECT_EQ( std::size_t( 1 ), queue1->nonLockingSize() );
}

TEST( WorkQueueTest, AccessLocking ) {
	using Workable = std::shared_ptr<Data>;
	WorkQueueManager<Workable> qm;

	WorkQueue<Workable>* queue1 = qm.addQueue();

	queue1->enqueue( std::make_shared<Data>( Data{ 1 } ) );
	queue1->enqueue( std::make_shared<Data>( Data{ 2 } ) );
	queue1->enqueue( std::make_shared<Data>( Data{ 3 } ) );

	EXPECT_EQ( std::size_t( 3 ), queue1->size() );

	auto item = queue1->dequeueFront();
	EXPECT_EQ( 1, item->mContent );
	EXPECT_EQ( std::size_t( 2 ), queue1->size() );

	item = queue1->dequeueBack();
	EXPECT_EQ( 3, item->mContent );
	EXPECT_EQ( std::size_t( 1 ), queue1->size() );
}
