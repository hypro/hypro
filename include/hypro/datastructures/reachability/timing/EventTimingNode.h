/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../../util/logging/Logger.h"
#include "../DAGNode.h"
#include "EventTimingContainer.h"
#include "TimingAggregate.h"

#include <ostream>

namespace hypro {

    template<typename Number>
    class EventTimingNode : public DAGNode<EventTimingNode<Number>> {
    protected:
        EventTimingContainer<Number> mTimings;
        const Location<Number> *mLocation = nullptr;
        const Transition<Location<Number>> *mEntryTransition = nullptr;
        carl::Interval<tNumber> mEntryTimestamp;
        TimingAggregate<Number> mTimingAggregate;
        std::size_t mLevel = 0;

    public:
        using Node_t = typename DAGNode<EventTimingNode<Number>>::Node_t;
        using NodeList_t = typename DAGNode<EventTimingNode<Number>>::NodeList_t;

        EventTimingNode() {}

        EventTimingNode(const EventTimingContainer<Number> &in)
                : mTimings(in) {}

        const EventTimingContainer<Number> &getTimings() const;

        EventTimingContainer<Number> &rGetTimings();

        const Location<Number> *getLocation() const;

        const Transition<Location<Number>> *getEntryTransition() const;

        const carl::Interval<tNumber> &getEntryTimestamp() const;

        TimingAggregate<Number> &rGetTimingAggregate();

        void setLevel(std::size_t l);

        std::size_t getLevel() const;

        void setTimings(const EventTimingContainer<Number> &timings);

        void setLocation(const Location<Number> *loc);

        void setEntryTimestamp(const carl::Interval<tNumber> &t);

        void extendEntryTimestamp(const carl::Interval<tNumber> &t);

        void setEntryTransition(const Transition<Location<Number>> *trans);

        friend std::ostream &operator<<(std::ostream &out, const EventTimingNode<Number> &in) {
            out << "lvl. " << in.getLevel() << ", content: ";
            out << in.getTimings();
            return out;
        }

        std::size_t getDotRepresentation(std::size_t id, std::string &nodes, std::string &transitions) const;
    };

}  // namespace hypro

#include "ETN_util.h"
#include "EventTimingNode.tpp"
