/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "WorkQueueManager.h"

namespace hypro {
    template<typename Workable>
    WorkQueue<Workable> *WorkQueueManager<Workable>::addQueue() {
        TRACE("hypro.datastructures", "Create new queue.");
        mQueues.emplace_back(std::make_unique<WorkQueue<Workable>>());
        TRACE("hypro.datastructures", "Return queue.");
        assert(mQueues.back());
        return mQueues.back().get();
    }

/*
	template<typename Workable>
	WorkQueue<Workable>& WorkQueueManager<Workable>::addQueue(WorkQueue<Workable>&& queue) {
		mQueues.emplace_back(std::move(queue));
		return mQueues.back();
	}
	*/

    template<typename Workable>
    WorkQueue<Workable> *WorkQueueManager<Workable>::getQueue(std::size_t index) {
        assert(mQueues.size() > index);
        assert(mQueues[index]);
        return mQueues[index].get();
    }

    template<typename Workable>
    bool WorkQueueManager<Workable>::hasWorkable(bool lockedAcces) const {
        for (const auto &queue: mQueues) {
            if (lockedAcces) {
                if (!queue->isEmpty()) {
                    return true;
                }
            } else {
                if (!queue->nonLockingIsEmpty()) {
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
        for (auto &queue: mQueues) {
            if (lockedAccess) {
                if (dequeueFront)
                    res = queue->dequeueFront();
                else
                    res = queue->dequeueBack();
            } else {
                if (dequeueFront)
                    res = queue->nonLockingDequeueFront();
                else
                    res = queue->nonLockingDequeueBack();
            }
            if (res != nullptr) {
                return res;
            }
        }
        // return nullptr if all queues were empty.
        return res;
    }

}  // namespace hypro
