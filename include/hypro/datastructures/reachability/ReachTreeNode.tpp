#include "ReachTreeNode.h"

namespace hypro {

template <typename State>
const typename State::repVariant& ReachTreeNode<State>::getSetAtLevel( unsigned level ) const {
	assert( mRefinements.size() > level );
	assert( !mRefinements.at( level ).isDummy );
	return mRefinements.at( level ).initialSet.getSet();
}

template <typename State>
const State& ReachTreeNode<State>::getStateAtLevel( unsigned level ) const {
	TRACE( "hypro.datastructures", "Access level " << level << " on a node with " << mRefinements.size() << " refinements." );
	assert( mRefinements.size() > level );
	assert( !mRefinements.at( level ).isDummy );
	return mRefinements.at( level ).initialSet;
	// return State(mLoc, mRefinements.at(level).initialSet, mDiscreteAssignment, mRefinements.at(level).clockAssignment, carl::Interval<Number>(-1));
}

template <typename State>
const carl::Interval<tNumber>& ReachTreeNode<State>::getTimestamp( unsigned level ) const {
	assert( level < mRefinements.size() );
	return mRefinements.at( level ).entryTimestamp;
}

/*
template<typename State>
std::vector<carl::Interval<tNumber>> ReachTreeNode<State>::getTimeIntervals(hypro::Transition<Number>* t) const {
	TRACE("hypro.datastructures","Has " << mTransitionTimings.size() << " stored timings in total.");
	auto intvIt = mTransitionTimings.find(t);
	if( intvIt == mTransitionTimings.end() ){
		return std::vector<carl::Interval<tNumber>>();
	}
	return intvIt->second;
}
*/

template <typename State>
unsigned ReachTreeNode<State>::getLatestBTLevel() const {
	unsigned level = mRefinements.size() - 1;
	while ( level > 0 && mRefinements.at( level ).isDummy == true ) {
		--level;
	}
	// assert(!mRefinements.at(level).isDummy);
	return level;
}

template <typename State>
unsigned ReachTreeNode<State>::getLatestFullyComputedLevel() const {
	unsigned level = mRefinements.size() - 1;
	while ( level > 0 && mRefinements.at( level ).fullyComputed == false ) {
		--level;
	}
	assert( !mRefinements.at( level ).isDummy );
	return level;
}

template <typename State>
void ReachTreeNode<State>::getLevelCnt( std::vector<std::size_t>& levels ) const {
	for ( std::size_t pos = 0; pos < mRefinements.size(); ++pos ) {
		if ( mRefinements[pos].fullyComputed ) {
			while ( levels.size() <= pos ) {
				levels.push_back( 0 );
			}
			levels[pos] += 1;
		}
	}
	for ( const auto child : this->getChildren() ) {
		child->getLevelCnt( levels );
	}
}

template <typename State>
std::vector<ReachTreeNode<State>*> ReachTreeNode<State>::getChildrenForTransition( hypro::Transition<Number>* transition ) const {
	// get all children
	ReachTreeNode<State>::NodeList_t children = this->getChildren();
	std::vector<ReachTreeNode<State>*> res;
	TRACE( "hypro.datastructures", "Total number of children: " << children.size() << ", transition: " << transition );
	// delete all children not being a result of the transition
	for ( auto childIt = children.begin(); childIt != children.end(); ++childIt ) {
		// Note: The offset -1 for the depth results from the additional root node.
		ReachTreeNode<State>* castChild = *childIt;
		if ( castChild->getPath().getTransitionSequence( castChild->getPath().begin(), castChild->getPath().end() ).back() == transition ) {
			TRACE( "hypro.datastructures", "Transition: " << castChild->getPath().getTransitionSequence( castChild->getPath().begin(), castChild->getPath().end() ).back() << " == " << transition );
			res.emplace_back( castChild );
		}
	}
	return res;
}

template <typename State>
bool ReachTreeNode<State>::isFullyComputedOnSomeLevel() const {
	for ( const auto& ref : mRefinements ) {
		if ( ref.fullyComputed && !ref.hitBadStates ) {
			return true;
		}
	}
	return false;
}

template <typename State>
void ReachTreeNode<State>::updateContent( ReachTreeNode<State>* updatedNode ) {
#ifndef NDEBUG
#ifdef HYPRO_LOGGING
	TRACE( "hypro.datastructure", "Update refinements: " );
	for ( const auto& ref : mRefinements ) {
		TRACE( "hypro.datastructure", ref );
	}
	TRACE( "hypro.datastructures", "With new refinements: " );
	for ( const auto& ref : updatedNode->getRefinements() ) {
		TRACE( "hypro.datastructure", ref );
	}
#endif
#endif
	mPath = updatedNode->getPath();
	// mLoc = updatedNode->getLocation();
	//  carefully update refinements - do not override old ones.
	for ( unsigned refPos = 0; refPos < updatedNode->getRefinements().size(); ++refPos ) {
		if ( refPos < mRefinements.size() && !mRefinements.at( refPos ).isDummy ) {
			continue;
		}
		if ( !updatedNode->getRefinements().at( refPos ).isDummy || ( updatedNode->getRefinements().at( refPos ).isDummy && mRefinements.size() <= refPos ) ) {
			if ( mRefinements.size() <= refPos ) {
				// assert(mRefinements.size() == refPos); // indirectly the difference cannot be more than one here.
				// Note: The difference can be more than one since the order the tasks are worked on is not predictable.
				TRACE( "hypro.datastructures", "Refinements are extended to level " << refPos << " by " << updatedNode->getRefinements().at( refPos ) );
				mRefinements.push_back( updatedNode->getRefinements().at( refPos ) );
			} else {
				TRACE( "hypro.datastructures", "Ref @" << refPos << ": " << mRefinements[refPos] << " is replaced by " << updatedNode->getRefinements().at( refPos ) );
				mRefinements[refPos] = updatedNode->getRefinements().at( refPos );
			}
		}
	}
	// mTransitionTimings = updatedNode->getTransitionTimings();
}

template <typename State>
void ReachTreeNode<State>::addRefinement( const RefinementSetting<State>& ref ) {
	mRefinements.push_back( ref );
}

template <typename State>
void ReachTreeNode<State>::setNewRefinement( unsigned level, const RefinementSetting<State>& ref ) {
	if ( mRefinements.size() > level ) {
		mRefinements[level] = ref;
	} else if ( level == mRefinements.size() ) {
		mRefinements.push_back( ref );
	} else {
		while ( mRefinements.size() < level ) {
			mRefinements.push_back( RefinementSetting<State>( ref.initialSet.getLocation() ) );
		}
		mRefinements.push_back( ref );
	}
	DEBUG( "hypro.datastructures", "Set new refinement for level " << level << " for this " << this );
	assert( mRefinements.at( level ) == ref );
}

template <typename State>
void ReachTreeNode<State>::convertRefinement( unsigned fromLevel, unsigned toLevel ) {
	assert( mRefinements.size() > fromLevel );
	// move refinement to level 0, convert type in case necessary
	RefinementSetting tmpRefinement = mRefinements.at( fromLevel );
	SettingsProvider<State>::getInstance().getStrategy().advanceToLevel( tmpRefinement.initialSet, toLevel );
	this->setNewRefinement( toLevel, tmpRefinement );
	assert( mRefinements.at( toLevel ).fullyComputed == false );
	// assert(mRefinements.size() == 1);
	assert( !mRefinements.at( toLevel ).initialSet.getTimestamp().isEmpty() );
}

/*
template<typename State>
void ReachTreeNode<State>::setInitSet(const State::repVariant& _initSet)
{
	mRefinements[0].initialSet.setSet(_initSet);
}
*/

template <typename State>
void ReachTreeNode<State>::setTimestamp( unsigned level, const carl::Interval<tNumber>& timeInterval ) {
	mRefinements[level].entryTimestamp = timeInterval;
	// Todo-check: The timestamp of the initial set should be a local one,
	// whereas the entry timestamp is also local, but in the scope of the parent node.
	// mRefinements[level].initialSet.setTimestamp(timeInterval);
}

/*
template<typename State>
void ReachTreeNode<State>::addTransitionInterval(hypro::Transition<Number>* _trans, const carl::Interval<tNumber>& _timeInterval)
{
	TRACE("hypro.datastructures","Add timing interval " <<  _timeInterval << " for transition " << _trans);

	// check, if there is already an entry for the respective transition
	auto timingIt = mTransitionTimings.find(_trans);
	if(timingIt == mTransitionTimings.end()) {
		// if there is no entry, create a new one.
		mTransitionTimings[_trans] = std::vector<carl::Interval<tNumber>>();
		mTransitionTimings[_trans].push_back(_timeInterval);
		TRACE("hypro.datastructures","Added timing interval to fresh node.");
	} else {
		// if there is already an entry, check whether the current interval improves the existing intervals.
		// If yes, override, otherwise do nothing (keep old information, as it is better).
		bool completelyNewTimeInterval = true;
		auto insertionPosition = mTransitionTimings[_trans].end();
		for(auto intervalIt = mTransitionTimings[_trans].begin(); intervalIt != mTransitionTimings[_trans].end(); ++intervalIt) {
			if( intervalIt->intersectsWith(_timeInterval) ) {
				completelyNewTimeInterval = false;
				// in any case, if the intervals intersect, take the intersection to obtain a finer boundary.
				carl::Interval<tNumber> newInterval = intervalIt->convexHull(_timeInterval);
				// update the mapping (erase old, insert new at same pos).
				intervalIt = mTransitionTimings[_trans].erase(intervalIt);
				auto tmp = mTransitionTimings[_trans].insert(intervalIt, newInterval);
				TRACE("hypro.datastructures","Extended timing map by union with existing interval to " << *tmp);
				break;
			} else if( intervalIt->lower() > _timeInterval.upper() ) {
				// in case the intervals do not intersect, keep track of the boundaries to keep the interval vector ordered.
				insertionPosition = intervalIt;
				break;
			}
		}
		// if no intersection at all happened, use the possibly updated position of insertion to insert.
		if(completelyNewTimeInterval) {
			mTransitionTimings[_trans].insert(insertionPosition, _timeInterval);
			TRACE("hypro.datastructures","Extended timing map with new, disjunct interval.");
		}
	}
}


template<typename State>
void ReachTreeNode<State>::refineIntervals()
{
	auto iter_map = this->mTransitionTimings.begin();
	while (iter_map != this->mTransitionTimings.end()) {
		auto iter_inter = iter_map->second.begin();
		while (iter_inter != iter_map->second.end()) {
			auto iter_inter_next = iter_inter;
			++iter_inter_next;
			bool deletion = false;
			while (iter_inter_next != iter_map->second.end()) {
				if (iter_inter->contains(*iter_inter_next)) {
					iter_inter = iter_map->second.erase(iter_inter);
					deletion = true;
					TRACE("hypro.datastructures","Refinement deleted timings.");
					break;
				}
				++iter_inter_next;
			}
			if (!deletion && iter_inter != iter_map->second.end()) {
				++iter_inter;
			}
		}
		++iter_map;
	}
}
*/

template <typename State>
bool ReachTreeNode<State>::hasFixedPoint( const State& s, ReachTreeNode<State>::Node_t skip ) const {
	if ( this == skip ) {
		for ( const auto& r : mRefinements ) {
			if ( r.fullyComputed && r.initialSet.contains( s ) ) {
				return true;
			}
		}
	} else if ( this->getMutex().try_lock() ) {
		for ( const auto& r : mRefinements ) {
			if ( r.fullyComputed && r.initialSet.contains( s ) ) {
				this->getMutex().unlock();
				return true;
			}
		}
		this->getMutex().unlock();
	}

	for ( const auto c : this->getChildren() ) {
		if ( c->hasFixedPoint( s, skip ) )
			return true;
	}
	return false;
}

template <typename State>
void ReachTreeNode<State>::setParent( ReachTreeNode<State>* parent ) {
	TreeNode<ReachTreeNode<State>>::setParent( parent );
	mPath = parent->getPath();
}

template <typename State>
std::size_t ReachTreeNode<State>::getDotRepresentation( std::size_t startIndex, std::string& nodes, std::string& transitions, std::vector<unsigned>& levels ) const {
	std::stringstream s;
	s << "node" << startIndex << " [label=<<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\">";
	std::size_t cnt = 0;
	// add common info
	std::size_t colspan = 1 > mRefinements.size() ? 1 : mRefinements.size();
	// if(this->getParent() == nullptr){
	s << "<TR><TD COLSPAN=\"" << colspan << "\">@" << this;
	//} else {
	//	s << "<TR><TD COLSPAN=\""<< colspan << "\">@" << this << "<BR/>"<< this->getLocation()->getName() << "(" << this->getLocation()->getId() <<")";
	//}

	// if(mEventTimings.hasInvariantEvent(hypro::CONTAINMENT::FULL)){
	//	s << "<BR/><FONT POINT-SIZE=\"8.0\">inf(f): " << mEventTimings.getInvariantTimings(hypro::CONTAINMENT::FULL) << "</FONT>";
	// }
	//  add refinement info
	s << "</TD></TR><TR>";
	if ( mRefinements.empty() ) {
		s << "<TD> </TD>";
	}
	for ( const auto& ref : mRefinements ) {
		s << "<TD";
		if ( ref.fullyComputed && !ref.hitBadStates ) {
			s << " BGCOLOR=\"green\">";
			if ( levels.size() <= cnt ) levels.push_back( 0 );
			levels[cnt] += 1;
		} else if ( ref.hitBadStates ) {
			s << " BGCOLOR=\"red\">";
			if ( levels.size() <= cnt ) levels.push_back( 0 );
			levels[cnt] += 1;
		} else if ( !ref.isEmpty && !ref.isDummy ) {
			s << " BGCOLOR=\"yellow\">";
		} else if ( ref.isDummy ) {
			s << ">";
		} else {
			s << "> ";
		}
		s << "<FONT POINT-SIZE=\"8.0\">";
		if ( !ref.isEmpty && !ref.isDummy ) {
			// if(ref.eventTimings.hasInvariantEvent(hypro::CONTAINMENT::FULL)) {
			//	s <<  cnt << "<BR/>inv(f): " << ref.eventTimings.getInvariantTimings(hypro::CONTAINMENT::FULL);
			// } else {
			s << cnt << " (" << ref.initialSet.getLocation()->hash() << ")";
			//}
		}
		if ( ref.hitBadStates ) {
			// assert(ref.eventTimings.hasBadStateEvent());
			// if(ref.eventTimings.hasBadStateEvent()) {
			//	s << "<BR/>bs: " << ref.eventTimings.getBadStateTimings()[0];
			// }
			s << "B";
		}
		if ( ref.isDummy ) {
			s << "D";
		}
		s << "</FONT>";
		s << "</TD>";
		++cnt;
	}
	s << "</TR>";
	s << "</TABLE>>];" << std::endl;
	nodes += s.str();
	std::size_t offset = ++startIndex;
	if ( !this->getChildren().empty() ) {
		for ( const auto child : this->getChildren() ) {
			std::stringstream t;

			// carl::Interval<tNumber> timestamp = child->getTimestamp(child->getRefinements().size()-1);
			t << "node" << ( startIndex - 1 ) << " -> node" << offset << " [label=\" ";
			for ( auto& ref : child->getRefinements() ) {
				t << carl::Interval<double>( carl::convert<tNumber, double>( ref.entryTimestamp.lower() ), carl::convert<tNumber, double>( ref.entryTimestamp.upper() ) ) << "\n";
			}
			t << "\"];" << std::endl;
			transitions += t.str();
			;
			offset = child->getDotRepresentation( offset, nodes, transitions, levels );
		}
	}
	return offset;
}

template <typename State>
std::ostream& operator<<( std::ostream& out, const ReachTreeNode<State>& reachTreeNode ) {
	// TODO JNE refine operator
	out << "ReachTreeNode " << &reachTreeNode << ": path: " << reachTreeNode.mPath << std::endl
		<< "Refinements: " << std::endl;
	for ( const auto& ref : reachTreeNode.getRefinements() )
		out << ref << std::endl;
	return out;
}
template <typename S>
bool operator<( const ReachTreeNode<S>& lhs, const ReachTreeNode<S>& rhs ) {
	return ( lhs.getDepth() < rhs.getDepth() );
}

template <typename S>
bool operator==( const ReachTreeNode<S>& lhs, const ReachTreeNode<S>& rhs ) {
	// properties of tree node
	if ( lhs.mDepth != rhs.mDepth ||
		 lhs.mParent != rhs.mParent ||
		 lhs.mChildren.size() != rhs.mChildren.size() ) {
		return false;
	}

	if ( lhs.mPath != rhs.mPath ) {
		return false;
	}

	if ( lhs.mRefinements.size() != rhs.mRefinements.size() ) {
		return false;
	}

	for ( std::size_t i = 0; i < lhs.mRefinements.size(); ++i ) {
		if ( lhs.mRefinements[i] != rhs.mRefinements[i] ) {
			return false;
		}
	}
	return true;
}

}  // namespace hypro
