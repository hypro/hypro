#pragma once
#include "EventTimingContainer.h"
#include "TimingAggregate.h"
#include "../DAGNode.h"
#include "../../../util/logging/Logger.h"
#include <ostream>

namespace hypro {

template<typename Number>
class EventTimingNode : public DAGNode<EventTimingNode<Number>> {
protected:
    EventTimingContainer<Number>    mTimings;
    const Location<Number>*         mLocation = nullptr;
    carl::Interval<tNumber>         mEntryTimeStamp;
    TimingAggregate<Number>         mTimingAggregate;

public:
    using Node_t = typename DAGNode<EventTimingNode<Number>>::Node_t;
  	using const_Node_t = typename DAGNode<EventTimingNode<Number>>::const_Node_t;
  	using NodeList_t = typename DAGNode<EventTimingNode<Number>>::NodeList_t;

    EventTimingNode(){}
    EventTimingNode(const EventTimingContainer<Number>& in)
        : mTimings(in)
    {}

    void setTimings(const EventTimingContainer<Number>& timings) {mTimings = timings;}
    const EventTimingContainer<Number>& getTimings() const {return mTimings;}
    EventTimingContainer<Number>& rGetTimings() {return mTimings;}
    const Location<Number>* getLocation() const {return mLocation;}
    TimingAggregate<Number>& rGetTimingAggregate() {return mTimingAggregate;}

    void setLocation(const Location<Number>* loc) {mLocation = loc;mTimings.setLocation(loc);}
    void setEntryTimestamp(const carl::Interval<tNumber>& t) {
        TRACE("hypro.datastructures.timing", "Set entry timestamp of " << this << " to " << t);
        mEntryTimeStamp = t;
        mTimings.setEntryTimestamp(t);
    }

    void updateEntryTimestamp(const carl::Interval<tNumber>& t) {
        TRACE("hypro.datastructures.timing", "Update entry timestamp of " << this << " to " << t);
        mEntryTimeStamp = mEntryTimeStamp.convexHull(t);
        mTimings.setEntryTimestamp(mEntryTimeStamp);
    }

    friend std::ostream& operator<<(std::ostream& out, const EventTimingNode<Number>& in) {
        out << in.getTimings();
        return out;
    }

    std::size_t getDotRepresentation(int id, std::string& nodes, std::string& transitions) const {
        std::stringstream s;
        s << "node" << id << " [label=<<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\">";
        // add common info

        if(this->getLocation() == nullptr){
            s << "<TR><TD COLSPAN=\""<< 2 << "\">@" << this;
        } else {
        	s << "<TR><TD COLSPAN=\""<< 2 << "\">@" << this << "<BR/>"<< this->getLocation()->getName() << "(" << this->getLocation()->hash() <<")";
        }

        // add timing info
        s << "</TD></TR><TR><TD>";
        s << "inv: </TD><TD>" << mTimings.getInvariantTimings();
        s << "</TD></TR>";
        for(const auto& transTimingPair : mTimings.getTransitionTimings()) {
            s << "<TR><TD>";
            s << transTimingPair.first->getSource()->getName() << "-- " << transTimingPair.first->getTarget()->getName();
            s << "</TD><TD>";
            s << transTimingPair.second;
            s << "</TD></TR>";
        }
        s << "</TABLE>>];" << std::endl;
        nodes += s.str();
        std::size_t offset = ++id;
        if(!this->getChildren().empty()){
            for(const auto child : this->getChildren()) {
                std::stringstream t;
                t << "node" << (id-1) << " -> node" << offset << " [label=\" ";
                t << "[" << carl::convert<tNumber,double>(child->getTimings().getEntryTimestamp().lower()) << ";" << carl::convert<tNumber,double>(child->getTimings().getEntryTimestamp().upper()) << "]\n";
                t <<"\"];" << std::endl;
                transitions += t.str();;
                offset = child->getDotRepresentation(offset,nodes,transitions);
            }
        }
        return offset;
    }
};

} // hypro

#include "ETN_util.h"
