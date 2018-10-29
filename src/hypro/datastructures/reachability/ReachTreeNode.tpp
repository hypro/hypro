#include "ReachTreeNode.h"

namespace hypro
{

template<typename Number>
const typename State_t<Number>::repVariant& ReachTreeNode<Number>::getSetAtLevel(unsigned level) const {
	assert(mRefinements.size() > level);
	assert(!mRefinements.at(level).isDummy);
	return mRefinements.at(level).initialSet.getSet();
}

template<typename Number>
const State_t<Number>& ReachTreeNode<Number>::getStateAtLevel(unsigned level) const {
	assert(mRefinements.size() > level);
	assert(!mRefinements.at(level).isDummy);
	return mRefinements.at(level).initialSet;
	//return State(mLoc, mRefinements.at(level).initialSet, mDiscreteAssignment, mRefinements.at(level).clockAssignment, carl::Interval<Number>(-1));
}

template<typename Number>
const carl::Interval<tNumber>& ReachTreeNode<Number>::getTimestamp(unsigned level) const {
	assert(level < mRefinements.size());
	return mRefinements.at(level).entryTimestamp;
}

/*
template<typename Number>
std::vector<carl::Interval<tNumber>> ReachTreeNode<Number>::getTimeIntervals(hypro::Transition<Number>* t) const {
	TRACE("hydra.datastructures","Has " << mTransitionTimings.size() << " stored timings in total.");
	auto intvIt = mTransitionTimings.find(t);
	if( intvIt == mTransitionTimings.end() ){
		return std::vector<carl::Interval<tNumber>>();
	}
	return intvIt->second;
}
*/

template<typename Number>
unsigned ReachTreeNode<Number>::getLatestBTLevel() const {
	unsigned level = mRefinements.size()-1;
	while(level > 0 && mRefinements.at(level).isDummy == true) {
		--level;
	}
	//assert(!mRefinements.at(level).isDummy);
	return level;
}

template<typename Number>
unsigned ReachTreeNode<Number>::getLatestFullyComputedLevel() const {
	unsigned level = mRefinements.size()-1;
	while(level > 0 && mRefinements.at(level).fullyComputed == false) {
		--level;
	}
	assert(!mRefinements.at(level).isDummy);
	return level;
}

template<typename Number>
void ReachTreeNode<Number>::getLevelCnt(std::vector<std::size_t>& levels) const {
	for(std::size_t pos = 0; pos < mRefinements.size(); ++pos) {
		if(mRefinements[pos].fullyComputed) {
			while(levels.size() <= pos ) {
				levels.push_back(0);
			}
			levels[pos] += 1;
		}
	}
	for(const auto child : this->getChildren()) {
		child->getLevelCnt(levels);
	}
}

template<typename Number>
std::vector<ReachTreeNode<Number>*> ReachTreeNode<Number>::getChildrenForTransition(hypro::Transition<Number>* transition) const {
	// get all children
	ReachTreeNode<Number>::NodeList_t children = this->getChildren();
	std::vector<ReachTreeNode<Number>*> res;
	TRACE("hydra.datastructures", "Total number of children: " << children.size() << ", transition: " << transition);
	// delete all children not being a result of the transition
	for(auto childIt = children.begin(); childIt != children.end(); ++childIt) {
		// Note: The offset -1 for the depth results from the additional root node.
		ReachTreeNode<Number>* castChild = *childIt;
		if(castChild->getPath().getTransitionSequence(castChild->getPath().begin(), castChild->getPath().end()).back() == transition ) {
			TRACE("hydra.datastructures", "Transition: " << castChild->getPath().getTransitionSequence(castChild->getPath().begin(), castChild->getPath().end()).back() << " == " << transition);
			res.emplace_back(castChild);
		}
	}
	return res;
}

template<typename Number>
bool ReachTreeNode<Number>::isFullyComputedOnSomeLevel() const {
	for(const auto& ref : mRefinements) {
		if(ref.fullyComputed && !ref.hitBadStates) {
			return true;
		}
	}
	return false;
}

template<typename Number>
void ReachTreeNode<Number>::updateContent(ReachTreeNode<Number>* updatedNode) {
	TRACE("hydra.datastructure","Update refinements: ");
	for(const auto ref: mRefinements) {
		TRACE("hydra.datastructure", ref);
	}
	TRACE("hydra.datastructures","With new refinements: ");
	for(const auto ref: updatedNode->getRefinements()) {
		TRACE("hydra.datastructure", ref);
	}
	mPath = updatedNode->getPath();
	//mLoc = updatedNode->getLocation();
	// carefully update refinements - do not override old ones.
	for(unsigned refPos = 0; refPos < updatedNode->getRefinements().size(); ++refPos) {
		if(refPos < mRefinements.size() && !mRefinements.at(refPos).isDummy){
			continue;
		}
		if(!updatedNode->getRefinements().at(refPos).isDummy || (updatedNode->getRefinements().at(refPos).isDummy && mRefinements.size() <= refPos )){
			if(mRefinements.size() <= refPos){
				//assert(mRefinements.size() == refPos); // indirectly the difference cannot be more than one here.
				//Note: The difference can be more than one since the order the tasks are worked on is not predictable.
				TRACE("hydra.datastructures","Refinements are extended to level " << refPos << " by " << updatedNode->getRefinements().at(refPos));
				mRefinements.push_back(updatedNode->getRefinements().at(refPos));
			} else {
				TRACE("hydra.datastructures","Ref @" << refPos << ": " << mRefinements[refPos] << " is replaced by " << updatedNode->getRefinements().at(refPos));
				mRefinements[refPos] = updatedNode->getRefinements().at(refPos);
			}
		}
	}
	//mTransitionTimings = updatedNode->getTransitionTimings();
}

template<typename Number>
void ReachTreeNode<Number>::addRefinement(const RefinementSetting<Number>& ref) {
	mRefinements.push_back(ref);
}

template<typename Number>
void ReachTreeNode<Number>::setNewRefinement(unsigned level, const RefinementSetting<Number>& ref) {
	if(mRefinements.size() > level) {
		mRefinements[level] = ref;
	} else if(level == mRefinements.size()) {
		mRefinements.push_back(ref);
	}else{
		while(mRefinements.size() < level) {
			mRefinements.push_back(RefinementSetting<Number>(ref.initialSet.getLocation()));
		}
		mRefinements.push_back(ref);
	}
	DEBUG("hydra.datastructures","Set new refinement for level " << level << " for this " << this );
	assert(mRefinements.at(level) == ref);
}

template<typename Number>
void ReachTreeNode<Number>::convertRefinement(unsigned fromLevel, unsigned toLevel, const StrategyNode& toSettings) {
	assert(mRefinements.size() > fromLevel);
	// move refinement to level 0, convert type in case necessary
	RefinementSetting<Number> tmpRefinement = mRefinements.at(fromLevel);
	tmpRefinement.initialSet.setSetDirect(boost::apply_visitor(hypro::genericConversionVisitor<typename State_t<Number>::repVariant, Number>(toSettings.representation), mRefinements.at(fromLevel).initialSet.getSet()), 0);
	tmpRefinement.initialSet.setSetType(toSettings.representation, 0);
	//child->clearRefinements();
	this->setNewRefinement(toLevel,tmpRefinement);
	assert(mRefinements.at(toLevel).fullyComputed == false);
	//assert(mRefinements.size() == 1);
	assert(!mRefinements.at(toLevel).initialSet.getTimestamp().isEmpty());
}

/*
template<typename Number>
void ReachTreeNode<Number>::setInitSet(const State_t<Number>::repVariant& _initSet)
{
    mRefinements[0].initialSet.setSet(_initSet);
}
*/

template<typename Number>
void ReachTreeNode<Number>::setTimestamp( unsigned level, const carl::Interval<tNumber>& timeInterval)
{
	mRefinements[level].entryTimestamp = timeInterval;
	// Todo-check: The timestamp of the initial set should be a local one,
	// whereas the entry timestamp is also local, but in the scope of the parent node.
	//mRefinements[level].initialSet.setTimestamp(timeInterval);
}

/*
template<typename Number>
void ReachTreeNode<Number>::addTransitionInterval(hypro::Transition<Number>* _trans, const carl::Interval<tNumber>& _timeInterval)
{
	TRACE("hydra.datastructures","Add timing interval " <<  _timeInterval << " for transition " << _trans);

	// check, if there is already an entry for the respective transition
    auto timingIt = mTransitionTimings.find(_trans);
    if(timingIt == mTransitionTimings.end()) {
    	// if there is no entry, create a new one.
    	mTransitionTimings[_trans] = std::vector<carl::Interval<tNumber>>();
    	mTransitionTimings[_trans].push_back(_timeInterval);
    	TRACE("hydra.datastructures","Added timing interval to fresh node.");
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
				TRACE("hydra.datastructures","Extended timing map by union with existing interval to " << *tmp);
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
    		TRACE("hydra.datastructures","Extended timing map with new, disjunct interval.");
    	}
    }
}


template<typename Number>
void ReachTreeNode<Number>::refineIntervals()
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
                    TRACE("hydra.datastructures","Refinement deleted timings.");
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

template<typename Number>
bool ReachTreeNode<Number>::hasFixedPoint(const State_t<Number>& s, ReachTreeNode<Number>::Node_t skip) const {
	if(this == skip) {
		for(const auto& r : mRefinements) {
			if(r.fullyComputed && r.initialSet.contains(s)) {
				return true;
			}
		}
	} else if(this->getMutex().try_lock()) {
		for(const auto& r : mRefinements) {
			if(r.fullyComputed && r.initialSet.contains(s)) {
				this->getMutex().unlock();
				return true;
			}
		}
		this->getMutex().unlock();
	}

	for(const auto c : this->getChildren()) {
		if(c->hasFixedPoint(s,skip))
			return true;
	}
	return false;
}

template<typename Number>
void ReachTreeNode<Number>::setParent(ReachTreeNode<Number>* parent) {
	TreeNode<ReachTreeNode<Number>>::setParent(parent);
	mPath = parent->getPath();
}

template<typename Number>
std::size_t ReachTreeNode<Number>::getDotRepresentation(std::size_t startIndex, std::string& nodes, std::string& transitions, std::vector<unsigned>& levels) const {
	std::stringstream s;
	s << "node" << startIndex << " [label=<<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\">";
	std::size_t cnt = 0;
	// add common info
	std::size_t colspan = 1 > mRefinements.size()? 1 : mRefinements.size();
	//if(this->getParent() == nullptr){
		s << "<TR><TD COLSPAN=\""<< colspan << "\">@" << this;
	//} else {
	//	s << "<TR><TD COLSPAN=\""<< colspan << "\">@" << this << "<BR/>"<< this->getLocation()->getName() << "(" << this->getLocation()->getId() <<")";
	//}

	//if(mEventTimings.hasInvariantEvent(hypro::CONTAINMENT::FULL)){
	//	s << "<BR/><FONT POINT-SIZE=\"8.0\">inf(f): " << mEventTimings.getInvariantTimings(hypro::CONTAINMENT::FULL) << "</FONT>";
	//}
	// add refinement info
	s << "</TD></TR><TR>";
	if(mRefinements.empty()){
		s << "<TD> </TD>";
	}
	for(const auto& ref : mRefinements) {
		s << "<TD";
		if(ref.fullyComputed && !ref.hitBadStates){
			s << " BGCOLOR=\"green\">";
			if(levels.size() <= cnt) levels.push_back(0);
			levels[cnt] += 1;
		} else if(ref.hitBadStates) {
			s << " BGCOLOR=\"red\">";
			if(levels.size() <= cnt) levels.push_back(0);
			levels[cnt] += 1;
		} else if(!ref.isEmpty && !ref.isDummy) {
			s << " BGCOLOR=\"yellow\">";
		} else if(ref.isDummy){
			s << ">";
		} else {
			s << "> ";
		}
		s << "<FONT POINT-SIZE=\"8.0\">";
		if(!ref.isEmpty && !ref.isDummy) {
			//if(ref.eventTimings.hasInvariantEvent(hypro::CONTAINMENT::FULL)) {
			//	s <<  cnt << "<BR/>inv(f): " << ref.eventTimings.getInvariantTimings(hypro::CONTAINMENT::FULL);
			//} else {
				s << cnt << " (" << ref.initialSet.getLocation()->getId() << ")";
			//}
		}
		if(ref.hitBadStates){
			//assert(ref.eventTimings.hasBadStateEvent());
			//if(ref.eventTimings.hasBadStateEvent()) {
			//	s << "<BR/>bs: " << ref.eventTimings.getBadStateTimings()[0];
			//}
			s << "B";
		}
		if(ref.isDummy){
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
	if(!this->getChildren().empty()){
		for(const auto child : this->getChildren()) {
			std::stringstream t;

			//carl::Interval<tNumber> timestamp = child->getTimestamp(child->getRefinements().size()-1);
			t << "node" << (startIndex-1) << " -> node" << offset << " [label=\" ";
			for(auto& ref : child->getRefinements()){
				t << carl::Interval<double>(carl::convert<tNumber,double>(ref.entryTimestamp.lower()), carl::convert<tNumber,double>(ref.entryTimestamp.upper())) << "\n";
			}
			t <<"\"];" << std::endl;
			transitions += t.str();;
			offset = child->getDotRepresentation(offset,nodes,transitions,levels);
		}
	}
	return offset;
}

template<typename Number>
std::ostream& operator<< (std::ostream &out, const ReachTreeNode<Number>& reachTreeNode) {
    // TODO JNE refine operator
    out << "ReachTreeNode " << &reachTreeNode << ": path: " << reachTreeNode.mPath << std::endl << "Refinements: " << std::endl;
    for(const auto& ref : reachTreeNode.getRefinements())
    	out << ref << std::endl;
    return out;
}

} // hypro
