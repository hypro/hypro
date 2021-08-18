#pragma once
#include "../../../util/logging/Logger.h"
#include "../DAGNode.h"
#include "EventTimingContainer.h"
#include "TimingAggregate.h"

#include <ostream>

namespace hypro {

template <typename Number>
class EventTimingNode : public DAGNode<EventTimingNode<Number>> {
  protected:
	EventTimingContainer<Number> mTimings;
	const Location<Number>* mLocation = nullptr;
	const Transition<Number>* mEntryTransition = nullptr;
	carl::Interval<tNumber> mEntryTimestamp;
	TimingAggregate<Number> mTimingAggregate;
	std::size_t mLevel = 0;

  public:
	using Node_t = typename DAGNode<EventTimingNode<Number>>::Node_t;
	using const_Node_t = typename DAGNode<EventTimingNode<Number>>::const_Node_t;
	using NodeList_t = typename DAGNode<EventTimingNode<Number>>::NodeList_t;

	EventTimingNode() {}
	EventTimingNode( const EventTimingContainer<Number>& in )
		: mTimings( in ) {}

	const EventTimingContainer<Number>& getTimings() const;
	EventTimingContainer<Number>& rGetTimings();
	const Location<Number>* getLocation() const;
	const Transition<Number>* getEntryTransition() const;
	const carl::Interval<tNumber>& getEntryTimestamp() const;
	TimingAggregate<Number>& rGetTimingAggregate();

	void setLevel( std::size_t l );
	std::size_t getLevel() const;

	void setTimings( const EventTimingContainer<Number>& timings );
	void setLocation( const Location<Number>* loc );
	void setEntryTimestamp( const carl::Interval<tNumber>& t );
	void extendEntryTimestamp( const carl::Interval<tNumber>& t );
	void setEntryTransition( const Transition<Number>* trans );

	friend std::ostream& operator<<( std::ostream& out, const EventTimingNode<Number>& in ) {
		out << "lvl. " << in.getLevel() << ", content: ";
		out << in.getTimings();
		return out;
	}

	std::size_t getDotRepresentation( std::size_t id, std::string& nodes, std::string& transitions ) const;
};

}  // namespace hypro

#include "ETN_util.h"
#include "EventTimingNode.tpp"
