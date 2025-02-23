/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

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
    template<class Workable, class Setting>
    class WorkQueueT {
        static_assert(
                std::is_pointer<Workable>::value || is_shared_ptr<Workable>::value || is_unique_ptr<Workable>::value,
                "WorkQueue requires pointer type.");

    protected:
        std::deque<Workable> mQueue;
        mutable std::mutex mQueueLock;

    public:
        using Workable_t = Workable;

        WorkQueueT() = default;

        WorkQueueT(WorkQueueT<Workable, Setting> &&in) = delete;

        WorkQueueT(const WorkQueueT<Workable, Setting> &in) = delete;

        /**
         * Destructor
         **/
        ~WorkQueueT() {};

        /**
         * Pushed an Workable to the front of the queue.
         *
         * @param item item to be pushed at the front
         */
        void pushFront(const Workable &item);

        void nonLockingPushFront(const Workable &item);

        /**
         * enqueues an item
         * @param item item to be enqueued
         */
        void enqueue(Workable &&item);

        void nonLockingEnqueue(Workable &&item);

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

        bool exists(const Workable &item);

        bool nonLockingExists(const Workable &item);

        std::mutex &getMutex() { return mQueueLock; }

        friend std::ostream &operator<<(std::ostream &out, const WorkQueueT &queue) {
            for (auto elem: queue.getQueue()) {
                out << elem << std::endl;
            }
            return out;
        }

    private:
        inline const std::deque<Workable> &getQueue() const { return mQueue; }
    };

    template<typename Workable>
    using WorkQueue = WorkQueueT<Workable, WorkQueueDefaultSetting>;

}  // namespace hypro

#include "WorkQueue.tpp"
