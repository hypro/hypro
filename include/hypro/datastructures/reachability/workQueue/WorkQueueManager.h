/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../../util/typetraits.h"
#include "WorkQueue.h"

namespace hypro {

    template<typename Workable>
    class WorkQueueManager {
        static_assert(std::is_pointer<Workable>::value || is_shared_ptr<Workable>::value,
                      "WorkQueue requires pointer type.");

    protected:
        std::vector<std::unique_ptr<WorkQueue<Workable>>> mQueues;

    public:
        WorkQueue<Workable> *addQueue();

        // WorkQueue<Workable>& addQueue(WorkQueue<Workable>&& queue);
        WorkQueue<Workable> *getQueue(std::size_t index);

        bool hasWorkable(bool lockedAcces) const;

        Workable getNextWorkable(bool lockedAccess, bool dequeueFront);
    };

}  // namespace hypro

#include "WorkQueueManager.tpp"
