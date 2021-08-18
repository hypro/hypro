#pragma once
#include "../../../util/typetraits.h"
#include "WorkQueue.h"

namespace hypro {

template <typename Workable>
class WorkQueueManager {
	static_assert( std::is_pointer<Workable>::value || is_shared_ptr<Workable>::value, "WorkQueue requires pointer type." );

  protected:
	std::vector<std::unique_ptr<WorkQueue<Workable>>> mQueues;

  public:
	WorkQueue<Workable>* addQueue();
	// WorkQueue<Workable>& addQueue(WorkQueue<Workable>&& queue);
	WorkQueue<Workable>* getQueue( std::size_t index );

	bool hasWorkable( bool lockedAcces ) const;
	Workable getNextWorkable( bool lockedAccess, bool dequeueFront );
};

}  // namespace hypro

#include "WorkQueueManager.tpp"
