#include "EventTimingContainer.h"

namespace hypro {

template <typename Number>
EventTimingContainer<Number>::EventTimingContainer( const EventTimingContainer<Number>& orig )
	: mInvariantEvents( orig.getInvariantTimings() )
	, mTransitionEvents( orig.getTransitionTimings() )
	, mBadStateEvents( orig.getBadStateTimings() ) {}

template <typename Number>
EventTimingContainer<Number>& EventTimingContainer<Number>::operator=( const EventTimingContainer<Number>& orig ) {
	mTransitionEvents = orig.mTransitionEvents;
	mInvariantEvents = orig.mInvariantEvents;
	mBadStateEvents = orig.mBadStateEvents;
	return *this;
}

template <typename Number>
EventTimingContainer<Number>& EventTimingContainer<Number>::operator=( EventTimingContainer<Number>&& orig ) {
	mTransitionEvents = std::move( orig.mTransitionEvents );
	mInvariantEvents = std::move( orig.mInvariantEvents );
	mBadStateEvents = std::move( orig.mBadStateEvents );
	return *this;
}

template <typename Number>
bool EventTimingContainer<Number>::isInitialized() const {
	return ( !mInvariantEvents.empty() && !mBadStateEvents.empty() );
}

template <typename Number>
void EventTimingContainer<Number>::initialize( tNumber timeHorizon ) {
	mInvariantEvents.initialize( CONTAINMENT::BOT, timeHorizon );
	mBadStateEvents.initialize( CONTAINMENT::BOT, timeHorizon );
}

template <typename Number>
void EventTimingContainer<Number>::merge( const EventTimingContainer<Number>& snapshot ) {
	// refine/replace transitions
	// Todo: This is not a nice implementation, but currently required since we don't use c++17 and HIV's are not default-constructible
	for ( const auto& transitionTimingPair : snapshot.getTransitionTimings() ) {
		auto transitionIt = mTransitionEvents.find( transitionTimingPair.first );
		if ( transitionIt == mTransitionEvents.end() ) {
			mTransitionEvents.insert( std::make_pair( transitionTimingPair.first, transitionTimingPair.second ) );
		} else {
			HierarchicalIntervalVector<CONTAINMENT, tNumber> tmp = transitionIt->second;
			tmp.merge( transitionTimingPair.second );
			mTransitionEvents.erase( transitionIt );
			mTransitionEvents.insert( std::make_pair( transitionTimingPair.first, tmp ) );
		}
	}
	mInvariantEvents.merge( snapshot.getInvariantTimings() );
	mBadStateEvents.merge( snapshot.getBadStateTimings() );
}

template <typename Number>
bool EventTimingContainer<Number>::hasTransitionEvent( Transition<Number, Location<Number>>* transition ) const {
	return ( mTransitionEvents.find( transition ) != mTransitionEvents.end() &&
			 ( mTransitionEvents.at( transition ).size() > 1 ||
			   ( mTransitionEvents.at( transition ).back().type != CONTAINMENT::BOT &&
				 mTransitionEvents.at( transition ).back().type != CONTAINMENT::NO ) ) );
}

template <typename Number>
bool EventTimingContainer<Number>::hasTransitionEvent( const carl::Interval<tNumber>& timeInterval, Transition<Number, Location<Number>>* transition ) const {
	if ( mTransitionEvents.find( transition ) == mTransitionEvents.end() ) {
		return false;
	}
	return ( mTransitionEvents.at( transition ).intersectsEntry( timeInterval, CONTAINMENT::YES ) ||
			 mTransitionEvents.at( transition ).intersectsEntry( timeInterval, CONTAINMENT::PARTIAL ) ||
			 mTransitionEvents.at( transition ).intersectsEntry( timeInterval, CONTAINMENT::FULL ) );
}

template <typename Number>
bool EventTimingContainer<Number>::hasTransitionInformation( const carl::Interval<tNumber>& timeInterval, Transition<Number, Location<Number>>* transition ) const {
	if ( mTransitionEvents.find( transition ) == mTransitionEvents.end() ) {
		return false;
	}
	return !( mTransitionEvents.at( transition ).intersectsEntry( timeInterval, CONTAINMENT::BOT ) );
}

template <typename Number>
bool EventTimingContainer<Number>::hasInvariantEvent( CONTAINMENT type ) const {
	return mInvariantEvents.hasEntry( type );
}

template <typename Number>
bool EventTimingContainer<Number>::satisfiedInvariant( const carl::Interval<tNumber>& timeInterval ) const {
	return ( mInvariantEvents.hasEntry( timeInterval, CONTAINMENT::PARTIAL ) ||
			 mInvariantEvents.hasEntry( timeInterval, CONTAINMENT::FULL ) ||
			 mInvariantEvents.hasEntry( timeInterval, CONTAINMENT::YES ) );
}

template <typename Number>
bool EventTimingContainer<Number>::hasInvariantEvent( const carl::Interval<tNumber>& timeInterval, CONTAINMENT type ) const {
	return mInvariantEvents.hasEntry( timeInterval, type );
}

template <typename Number>
bool EventTimingContainer<Number>::hasBadStateEvent() const {
	return ( mBadStateEvents.size() > 1 || mBadStateEvents.back().type != CONTAINMENT::BOT );
}

template <typename Number>
bool EventTimingContainer<Number>::hasBadStateEvent( const carl::Interval<tNumber>& timeInterval, CONTAINMENT type ) const {
	return mBadStateEvents.hasEntry( timeInterval, type );
}

template <typename Number>
bool EventTimingContainer<Number>::hasPositiveBadStateEvent( const carl::Interval<tNumber>& timeInterval ) const {
	for ( auto type : mBadStateEvents.getTypeOrder() ) {
		if ( static_cast<int>( type ) >= 0 ) {
			if ( mBadStateEvents.hasEntry( timeInterval, type ) ) {
				return true;
			}
		}
	}
	return false;
}

template <typename Number>
void EventTimingContainer<Number>::insertTransition( Transition<Number, Location<Number>>* transition, const carl::Interval<tNumber>& timeInterval, CONTAINMENT type ) {
	// #ifdef HYPRO_LOGGING
	//	auto tmp = carl::convert<tNumber, double>( timeInterval );
	//	TRACE( "hypro.datastructures.etc", "In " << this << ": Transition: " << transition->getSource()->hash() << " -> " << transition->getTarget()->hash//() << " in time " << tmp );
	// #endif
	if ( mTransitionEvents.find( transition ) == mTransitionEvents.end() ) {
		assert( !mInvariantEvents.empty() );
		// initialize with same time horizon as invariants and bad states.
		HierarchicalIntervalVector<CONTAINMENT, tNumber> tmp( std::vector<CONTAINMENT>( { CONTAINMENT::BOT, CONTAINMENT::PARTIAL, CONTAINMENT::FULL, CONTAINMENT::NO, CONTAINMENT::YES } ) );
		tmp.initialize( CONTAINMENT::BOT, mInvariantEvents.getTimeHorizon() );
		mTransitionEvents.insert( std::make_pair( transition, tmp ) );
	}
	return mTransitionEvents.at( transition ).insertInterval( type, timeInterval );
}

template <typename Number>
const std::map<Transition<Number, Location<Number>>*, HierarchicalIntervalVector<CONTAINMENT, tNumber>>& EventTimingContainer<Number>::getTransitionTimings() const {
	return mTransitionEvents;
}

template <typename Number>
std::map<Transition<Number, Location<Number>>*, HierarchicalIntervalVector<CONTAINMENT, tNumber>>& EventTimingContainer<Number>::rGetTransitionTimings() {
	return mTransitionEvents;
}

template <typename Number>
const HierarchicalIntervalVector<CONTAINMENT, tNumber>& EventTimingContainer<Number>::getTransitionTimings( Transition<Number, Location<Number>>* transition ) const {
	return mTransitionEvents.at( transition );
}

template <typename Number>
const HierarchicalIntervalVector<CONTAINMENT, tNumber>& EventTimingContainer<Number>::getInvariantTimings() const {
	return mInvariantEvents;
}

template <typename Number>
void EventTimingContainer<Number>::insertInvariant( const carl::Interval<tNumber>& timeInterval, CONTAINMENT type ) {
	assert( !mInvariantEvents.empty() );
	// #ifdef HYPRO_LOGGING
	//	auto tmp = carl::convert<tNumber, double>( timeInterval );
	//	TRACE( "hypro.datastructures.etc", "Invariant type " << type << " in time " << tmp );
	// #endif
	return mInvariantEvents.insertInterval( type, timeInterval );
}

template <typename Number>
void EventTimingContainer<Number>::insertBadState( const carl::Interval<tNumber>& timeInterval, CONTAINMENT type ) {
	assert( !mBadStateEvents.empty() );
	// #ifdef HYPRO_LOGGING
	//	auto tmp = carl::convert<tNumber, double>( timeInterval );
	//	TRACE( "hypro.datastructures.etc", "BadState type " << type << " in time " << tmp );
	// #endif
	mBadStateEvents.insertInterval( type, timeInterval );
}

template <typename Number>
const HierarchicalIntervalVector<CONTAINMENT, tNumber>& EventTimingContainer<Number>::getBadStateTimings() const {
	return mBadStateEvents;
}

template <typename Number>
std::size_t EventTimingContainer<Number>::getDotRepresentation( std::size_t startIndex, std::string& nodes, std::string& transitions, std::vector<unsigned>& levels ) const {
	std::stringstream s;
	s << "node" << startIndex << " [label=<<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\">";
	// add common info
	std::size_t colspan = 1;  //> mRefinements.size()? 1 : mRefinements.size();
	if ( this->getParent() == nullptr ) {
		s << "<TR><TD COLSPAN=\"" << colspan << "\">@" << this;
	} else {
		s << "<TR><TD COLSPAN=\"" << colspan << "\">@" << this << "<BR/>" << this->getLocation()->getName() << "(" << this->getLocation()->getId() << ")";
	}

	s << "</TD></TR>";
	s << "<TR><TD> Inv. " << mInvariantEvents << "</TD></TR>";
	s << "<TR><TD> Bad. " << mBadStateEvents << "</TD></TR>";
	for ( const auto& tEvent : mTransitionEvents ) {
		s << "<TR><TD> " << tEvent.first->getSource()->getId() << " - " << tEvent.first->getTarget()->getId() << ": " << tEvent.second << "</TD></TR>";
	}
	s << "</TABLE>>];" << std::endl;
	nodes += s.str();
	std::size_t offset = ++startIndex;
	/*
		if(!mChildren.empty()){
			for(const auto& child : mChildren) {
				std::stringstream t;

				t << "node" << (startIndex-1) << " -> node" << offset << " [label=\" ";
				t << carl::Interval<double>(child->getEntryTimestamp().lower(), child->getEntryTimestamp().upper()) << "\n";
				t <<"\"];" << std::endl;
				transitions += t.str();;
				offset = child->getDotRepresentation(offset,nodes,transitions,levels);
			}
		}
		*/
	assert( false && "Not implented yet." );
	return offset;
}

}  // namespace hypro
