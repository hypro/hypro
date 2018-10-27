#include "WorkQueueManager.h"

namespace hypro
{
    template<typename Workable>
    WorkQueue<Workable>& WorkQueueManager<Workable>::addQueue() {
        mQueues.emplace_back(std::move(WorkQueue<Workable>()));
        return mQueues.back();
    }

    template<typename Workable>
    WorkQueue<Workable>& WorkQueueManager<Workable>::addQueue(WorkQueue<Workable>&& queue) {
        mQueues.emplace_back(std::move(queue));
        return mQueues.back();
    }

    template<typename Workable>
    WorkQueue<Workable>& WorkQueueManager<Workable>::getQueue(std::size_t index) {
        assert(mQueues.size() > index);
        return mQueues[index];
    }

    template<typename Workable>
    bool WorkQueueManager<Workable>::hasWorkable(bool lockedAcces) const {
        for(const auto& queue : mQueues) {
            if(lockedAcces) {
                if(!queue.isEmpty()) {
                    return true;
                }
            } else {
                if(!queue.nonLockingIsEmpty()) {
                    return true;
                }
            }
        }
        return false;
    }

    template<typename Workable>
    Workable WorkQueueManager<Workable>::getNextWorkable(bool lockedAccess, bool dequeueFront) {
        Workable res = nullptr;
        // iterate over all managed queues -> order implied by order of creation.
        for(auto& queue : mQueues) {
            if(lockedAccess) {
                if(dequeueFront)
                    res = queue.dequeueFront();
                else
                    res = queue.dequeueBack();
            } else {
                if(dequeueFront)
                    res = queue.nonLockingDequeueFront();
                else
                    res = queue.nonLockingDequeueBack();
            }
            if(res != nullptr) {
                return res;
            }
        }
        // return nullptr if all queues were empty.
        return res;
    }

} // hypro
