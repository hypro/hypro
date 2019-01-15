#pragma once
#include "EventTimingContainer.h"
#include "../TreeNode.h"

namespace hypro {

template<typename Number>
class EventTimingNode : public TreeNode<EventTimingNode<Number>> {
protected:
    EventTimingContainer<Number> mTimings;
    const Location<Number>*       mLocation;
    carl::Interval<tNumber> mEntryTimeStamp;
public:
    using Node_t = typename TreeNode<EventTimingNode<Number>>::Node_t;
  	using const_Node_t = typename TreeNode<EventTimingNode<Number>>::const_Node_t;
  	using NodeList_t = typename TreeNode<EventTimingNode<Number>>::NodeList_t;

    EventTimingNode() = default;
    EventTimingNode(const EventTimingContainer<Number>& in)
        : mTimings(in)
    {}

    void setTimings(const EventTimingContainer<Number>& timings) {mTimings = timings;}
    const EventTimingContainer<Number>& getSettings() const {return mTimings;}

    void setLocation(const Location<Number>* loc) {mLocation = loc;}
    void setEntryTimestamp(const carl::Interval<tNumber>& t) {mEntryTimeStamp = t;}

    void getDotRepresentation(int id, std::string& nodes, std::string& transitions, std::vector<unsigned>& levels) const {}
};

} // hypro