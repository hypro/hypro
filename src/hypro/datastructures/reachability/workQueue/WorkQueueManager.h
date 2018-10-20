#pragma once
#include "WorkQueue.h"
#include "../../../util/typetraits.h"

namespace hypro
{

template<typename Workable>
class WorkQueueManager {
    static_assert(std::is_pointer<Workable>::value || is_shared_ptr<Workable>::value, "WorkQueue requires pointer type." );
protected:
    std::vector<std::unique_ptr<WorkQueue<Workable>>> mQueues;

public:

    WorkQueue<Workable>* addQueue();
    WorkQueue<Workable>* addQueue(std::unique_ptr<WorkQueue<Workable>>&& queue);

    Workable getNextWorkable(bool lockedAccess, bool dequeueFront);

};

} // hypro

#include "WorkQueueManager.tpp"
