/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once
#include "../../../types.h"
#include "HierarchicalIntervalVector.h"

namespace hypro {

template <typename L>
class Transition;

template <typename N>
class Location;

template <typename Number>
class EventTimingContainer {
  private:
	// Timing storage
	HierarchicalIntervalVector<CONTAINMENT, tNumber> mInvariantEvents;
	std::map<Transition<Location<Number>>*, HierarchicalIntervalVector<CONTAINMENT, tNumber>> mTransitionEvents;
	HierarchicalIntervalVector<CONTAINMENT, tNumber> mBadStateEvents;

	mutable std::mutex mutex;

  public:
	EventTimingContainer()
		: mInvariantEvents( std::vector<CONTAINMENT>( { CONTAINMENT::BOT, CONTAINMENT::PARTIAL, CONTAINMENT::FULL, CONTAINMENT::YES, CONTAINMENT::NO } ) )
		, mTransitionEvents()
		, mBadStateEvents( std::vector<CONTAINMENT>( { CONTAINMENT::BOT, CONTAINMENT::PARTIAL, CONTAINMENT::FULL, CONTAINMENT::YES, CONTAINMENT::NO } ) ) {
		DEBUG( "hydra.datastructures.etc", "Created new empty ETC: " << *this );
	}

	explicit EventTimingContainer( tNumber timeHorizon )
		: mInvariantEvents( std::vector<CONTAINMENT>( { CONTAINMENT::BOT, CONTAINMENT::PARTIAL, CONTAINMENT::FULL, CONTAINMENT::YES, CONTAINMENT::NO } ) )
		, mTransitionEvents()
		, mBadStateEvents( std::vector<CONTAINMENT>( { CONTAINMENT::BOT, CONTAINMENT::PARTIAL, CONTAINMENT::FULL, CONTAINMENT::YES, CONTAINMENT::NO } ) ) {
		mInvariantEvents.initialize( CONTAINMENT::BOT, timeHorizon );
		mBadStateEvents.initialize( CONTAINMENT::BOT, timeHorizon );
		DEBUG( "hydra.datastructures.etc", "Created new initialized ETC: " << *this );
	}

	EventTimingContainer( const EventTimingContainer& orig );
	EventTimingContainer( EventTimingContainer&& orig ) = default;
	~EventTimingContainer() = default;

	EventTimingContainer& operator=( const EventTimingContainer& orig );
	EventTimingContainer& operator=( EventTimingContainer&& orig );

	std::mutex& getMutex() const { return mutex; }
	bool isInitialized() const;
	void initialize( tNumber timeHorizon );

	void merge( const EventTimingContainer& snapshot );

	void setTransitionTimings( const std::map<Transition<Location<Number>>*, HierarchicalIntervalVector<CONTAINMENT, tNumber>>& timings ) { mTransitionEvents = timings; }
	void setTransitionTimings( Transition<Location<Number>>* t, const HierarchicalIntervalVector<CONTAINMENT, tNumber>& timings ) { mTransitionEvents.insert_or_assign( t, timings ); }
	void setInvariantTimings( const HierarchicalIntervalVector<CONTAINMENT, tNumber>& timings ) { mInvariantEvents = timings; }
	void setBadStateTimings( const HierarchicalIntervalVector<CONTAINMENT, tNumber>& timings ) { mBadStateEvents = timings; }

	const std::map<Transition<Location<Number>>*, HierarchicalIntervalVector<CONTAINMENT, tNumber>>& getTransitionTimings() const;
	std::map<Transition<Location<Number>>*, HierarchicalIntervalVector<CONTAINMENT, tNumber>>& rGetTransitionTimings();
	const HierarchicalIntervalVector<CONTAINMENT, tNumber>& getTransitionTimings( Transition<Location<Number>>* transition ) const;
	const HierarchicalIntervalVector<CONTAINMENT, tNumber>& getInvariantTimings() const;
	HierarchicalIntervalVector<CONTAINMENT, tNumber>& rGetInvariantTimings() { return mInvariantEvents; }
	// const std::vector<carl::Interval<Number>>& getInvariantTimings(CONTAINMENT type) const;
	const HierarchicalIntervalVector<CONTAINMENT, tNumber>& getBadStateTimings() const;

	bool hasTransitionEvent( Transition<Location<Number>>* transition ) const;
	bool hasTransitionEvent( const carl::Interval<tNumber>& timeInterval, Transition<Location<Number>>* transition ) const;
	bool hasTransitionInformation( const carl::Interval<tNumber>& timeInterval, Transition<Location<Number>>* transition ) const;
	bool hasTransition( Transition<Location<Number>>* t ) const { return mTransitionEvents.find( t ) != mTransitionEvents.end(); }

	bool hasInvariantEvent( CONTAINMENT type ) const;
	bool satisfiedInvariant( const carl::Interval<tNumber>& timeInterval ) const;
	bool hasInvariantEvent( const carl::Interval<tNumber>& timeInterval, CONTAINMENT type ) const;

	bool hasBadStateEvent() const;
	bool hasBadStateEvent( const carl::Interval<tNumber>& timeInterval, CONTAINMENT type ) const;
	bool hasPositiveBadStateEvent( const carl::Interval<tNumber>& timeInterval ) const;

	void insertTransition( Transition<Location<Number>>* transition, const carl::Interval<tNumber>& timeInterval, CONTAINMENT type );
	void insertInvariant( const carl::Interval<tNumber>& timeInterval, CONTAINMENT type );
	void insertBadState( const carl::Interval<tNumber>& timeInterval, CONTAINMENT type );

	friend std::ostream& operator<<( std::ostream& out, const EventTimingContainer& in ) {
		out << "Inv.: " << in.mInvariantEvents;
		out << "Tr.: ";
		for ( const auto& TTPair : in.mTransitionEvents ) {
			out << TTPair.first->getSource()->hash() << "->" << TTPair.first->getTarget()->hash() << ": " << TTPair.second;
		}
		out << "Bs.: " << in.mBadStateEvents;
		return out;
	}

	friend bool operator==( const EventTimingContainer& lhs, const EventTimingContainer& rhs ) {
		return ( lhs.mInvariantEvents == rhs.mInvariantEvents && lhs.mBadStateEvents == rhs.mBadStateEvents && lhs.mTransitionEvents == rhs.mTransitionEvents );
	}

	friend bool operator!=( const EventTimingContainer& lhs, const EventTimingContainer& rhs ) { return !( lhs == rhs ); }

	std::size_t getDotRepresentation( std::size_t startIndex, std::string& nodes, std::string& transitions, std::vector<unsigned>& levels ) const;
};

}  // namespace hypro

#include "ETC_util.h"
#include "EventTimingContainer.tpp"
