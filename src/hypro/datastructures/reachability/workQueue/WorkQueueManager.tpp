#include "WorkQueueManager.h"

namespace hypro
{
    template<typename Workable>
    WorkQueue<Workable>* WorkQueueManager<Workable>::addQueue() {
        mQueues.emplace_back(std::unique_ptr<WorkQueue<Workable>>(new WorkQueue<Workable>()));
        return mQueues.back().get();
    }

    template<typename Workable>
    WorkQueue<Workable>* WorkQueueManager<Workable>::addQueue(std::unique_ptr<WorkQueue<Workable>>&& queue) {
        mQueues.emplace_back(queue);
        return mQueues.back().get();
    }

    template<typename Workable>
    Workable WorkQueueManager<Workable>::getNextWorkable(bool lockedAccess, bool dequeueFront) {
        Workable res = nullptr;
        // iterate over all managed queues -> order implied by order of creation.
        for(auto queue : mQueues) {
            if(lockedAccess) {
                if(dequeueFront)
                    res = queue->dequeueFront();
                else
                    res = queue->dequeueBack();
            } else {
                if(dequeueFront)
                    res = queue->nonLockingDequeueFront();
                else
                    res = queue->nonLockingDequeueBack();
            }
            if(res != nullptr) {
                return res;
            }
        }
        // return nullptr if all queues were empty.
        return res;
    }

} // hypro
