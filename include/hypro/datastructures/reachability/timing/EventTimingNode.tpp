/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "EventTimingNode.h"

namespace hypro {
    template<typename Number>
    void EventTimingNode<Number>::setTimings(const EventTimingContainer<Number> &timings) {
        TRACE("hypro.datastructures.timing", "Set timings of node (" << this << "): " << *this << " TO " << timings);
        mTimings = timings;
    }

    template<typename Number>
    const EventTimingContainer<Number> &EventTimingNode<Number>::getTimings() const {
        return mTimings;
    }

    template<typename Number>
    EventTimingContainer<Number> &EventTimingNode<Number>::rGetTimings() {
        return mTimings;
    }

    template<typename Number>
    const Location<Number> *EventTimingNode<Number>::getLocation() const {
        return mLocation;
    }

    template<typename Number>
    const Transition<Location<Number>> *EventTimingNode<Number>::getEntryTransition() const {
        return mEntryTransition;
    }

    template<typename Number>
    const carl::Interval<tNumber> &EventTimingNode<Number>::getEntryTimestamp() const {
        return mEntryTimestamp;
    }

    template<typename Number>
    TimingAggregate<Number> &EventTimingNode<Number>::rGetTimingAggregate() {
        return mTimingAggregate;
    }

    template<typename Number>
    void EventTimingNode<Number>::setLevel(std::size_t l) {
        mLevel = l;
    }

    template<typename Number>
    std::size_t EventTimingNode<Number>::getLevel() const {
        return mLevel;
    }

    template<typename Number>
    void EventTimingNode<Number>::setLocation(const Location<Number> *loc) {
        mLocation = loc;
    }

    template<typename Number>
    void EventTimingNode<Number>::setEntryTimestamp(const carl::Interval<tNumber> &t) {
        TRACE("hypro.datastructures.timing", "Set entry timestamp of " << this << " to " << t);
        mEntryTimestamp = t;
    }

    template<typename Number>
    void EventTimingNode<Number>::extendEntryTimestamp(const carl::Interval<tNumber> &t) {
        TRACE("hypro.datastructures.timing", "Update entry timestamp of " << this << " to " << t);
#ifdef CARL_OLD_STRUCTURE
        mEntryTimestamp = mEntryTimestamp.convexHull( t );
#else
        mEntryTimestamp = mEntryTimestamp.convex_hull(t);
#endif
    }

    template<typename Number>
    void EventTimingNode<Number>::setEntryTransition(const Transition<Location<Number>> *trans) {
        mEntryTransition = trans;
    }

    template<typename Number>
    std::size_t
    EventTimingNode<Number>::getDotRepresentation(std::size_t id, std::string &nodes, std::string &transitions) const {
        std::stringstream s;
        s << "node" << id << " [label=<<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\">";

        // add common info
        s << "<TR><TD COLSPAN=\"" << 2 << "\">@" << this;

        // add timing info
        s << "</TD></TR><TR><TD>";
        s << "inv: </TD><TD>" << mTimings.getInvariantTimings();
        s << "</TD></TR>";
        for (const auto &transTimingPair: mTimings.getTransitionTimings()) {
            s << "<TR><TD>";
            s << transTimingPair.first->getSource()->getName() << "-- "
              << transTimingPair.first->getTarget()->getName();
            s << "</TD><TD>";
            s << transTimingPair.second;
            s << "</TD></TR>";
        }
        s << "</TABLE>>];" << std::endl;
        nodes += s.str();
        std::size_t offset = ++id;
        if (!this->getChildren().empty()) {
            for (const auto child: this->getChildren()) {
                std::stringstream t;
                t << "node" << (id - 1) << " -> node" << offset << " [label=\" ";
                t << "[" << carl::convert<tNumber, double>(child->getEntryTimestamp().lower()) << ";"
                  << carl::convert<tNumber, double>(child->getEntryTimestamp().upper()) << "]\n";
                t << "\"];" << std::endl;
                transitions += t.str();;
                offset = child->getDotRepresentation(offset, nodes, transitions);
            }
        }
        return offset;
    }

}  // namespace hypro
