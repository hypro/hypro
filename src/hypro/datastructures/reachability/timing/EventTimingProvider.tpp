#include "EventTimingProvider.h"

namespace hypro {

	template<typename Number>
	EventTimingProvider<Number>::EventTimingProvider() : mRoot(new EventTimingNode<Number>()){
		TRACE("hypro.datastructures.timing","Root is " << mRoot);
		#ifndef NDEBUG
		writeTree();
		#endif
	}

	template<typename Number>
	void EventTimingProvider<Number>::initialize(const HybridAutomaton<Number>& ha, tNumber globalTimeHorizon) {
		for(const auto& state : ha.getInitialStates()) {
			EventTimingNode<Number>* child = new EventTimingNode<Number>(EventTimingContainer<Number>(globalTimeHorizon));
			child->addParent(mRoot);
			child->setLocation(state.first);
			child->setEntryTimestamp(carl::Interval<tNumber>(0));
			mRoot->addChild(child);
			TRACE("hypro.datastructures.timing","Add initial node " << child);
		}

		/*
		ReachabilitySettings& settings = SettingsProvider<State>::getInstance().getReachabilitySettings();
		EventTimingContainer empty = EventTimingContainer(settings.timeBound*settings.jumpDepth);
		empty.insertBadState(std::make_pair(CONTAINMENT::BOT, carl::Interval<tNumber>(Number(0),settings.timeBound*settings.jumpDepth)));
		for(auto locationPtr : ha.getLocations()) {
			mLocationTimings[locationPtr] = empty;
			for(auto transitionPtr : ha.getTransitions()) {
				if(transitionPtr->getSource() == locationPtr) {
					mLocationTimings[locationPtr].insertTransition(transitionPtr, std::make_pair(CONTAINMENT::BOT, carl::Interval<tNumber>(Number(0),settings.timeBound*settings.jumpDepth)));
				}
			}
		}
		*/

		#ifndef NDEBUG
		writeTree();
		#endif
	}

	template<typename Number>
	void EventTimingProvider<Number>::initialize(const Location<Number>* loc, tNumber globalTimeHorizon) {
		assert(mRoot->getChildren().empty());
		EventTimingNode<Number>* child = new EventTimingNode<Number>(EventTimingContainer<Number>(globalTimeHorizon));
		child->addParent(mRoot);
		child->setLocation(loc);
		child->setEntryTimestamp(carl::Interval<tNumber>(0));
		mRoot->addChild(child);
		TRACE("hypro.datastructures.timing","Add initial node " << child);

		#ifndef NDEBUG
		writeTree();
		#endif
	}

	template<typename Number>
	const EventTimingNode<Number>* EventTimingProvider<Number>::getTimingNode(const Path<Number,tNumber>& path) const {
		return findNode(path);
	}

	template<typename Number>
	EventTimingNode<Number>* EventTimingProvider<Number>::rGetNode(const Path<Number,tNumber>& path) const {
		return findNode(path);
	}

	template<typename Number>
	std::optional<EventTimingContainer<Number>> EventTimingProvider<Number>::getTimings(const Path<Number,tNumber>& path) const {

		// abort if we do not have a tree yet
		if(mRoot->getChildren().size() == 0) {
			TRACE("hypro.datastructures.timing","No child nodes, abort.");
			return std::nullopt;
		}

		// pointers to nodes on the path
		std::set<EventTimingNode<Number>*> workingSet;

		// fill working set with initial nodes
		assert(mRoot->getChildren().size() == 1);
		workingSet.emplace(*(mRoot->getChildren().begin()));

		// iterate over path
		auto pathIt = path.begin();
		while(pathIt != path.end()) {
			TRACE("hypro.datastructures.timing","Follow time step, have " << workingSet.size() << " nodes.");
			// remove all nodes from working set whose invariant timings do not contain the time interval in the path
			assert(!pathIt->isDiscreteStep());
			// stores candidates which match the timeStep
			std::set<EventTimingNode<Number>*> transitionCandidates;
			// verify against invariant timings.
			// Two-phase approach: Collect all which satisfy the invariant somehow,
			// then merge invariant intervals and check whether the invariant was satisfied the whole time.
			for(auto nodeIt = workingSet.begin(); nodeIt != workingSet.end();) {
				// check for full containment
				if((*nodeIt)->getTimings().satisfiedInvariant(pathIt->getTimestamp())) {
					transitionCandidates.insert(*nodeIt);
					++nodeIt;
				} else if ((*nodeIt)->getTimings().getInvariantTimings().intersectsEntry(pathIt->getTimestamp(), CONTAINMENT::FULL) ||
				   (*nodeIt)->getTimings().getInvariantTimings().intersectsEntry(pathIt->getTimestamp(), CONTAINMENT::PARTIAL) ||
				   (*nodeIt)->getTimings().getInvariantTimings().intersectsEntry(pathIt->getTimestamp(), CONTAINMENT::YES) ) {
					// check for partial containment
					transitionCandidates.insert(*nodeIt);
					++nodeIt;
					//TRACE("hypro.datastructures.timing","Not enough information, abort.");
					//return std::nullopt;
				} else {
					assert(!(*nodeIt)->getTimings().hasInvariantEvent(pathIt->getTimestamp(), CONTAINMENT::YES));
					assert(!(*nodeIt)->getTimings().hasInvariantEvent(pathIt->getTimestamp(), CONTAINMENT::PARTIAL));
					assert(!(*nodeIt)->getTimings().hasInvariantEvent(pathIt->getTimestamp(), CONTAINMENT::FULL));
					// the node does not satisfy the invariant, erase
					nodeIt = workingSet.erase(nodeIt);
				}
			}

			// merge invariant intervals to detect whether the invariant interval is fully covered
			// Todo: For the last step, is this neccessary?
			if(!transitionCandidates.empty()) {
				TRACE("hypro.datastructures.timing","Merge invariant intervals of " << transitionCandidates.size() << " candidates.");
				auto mergedHIV = (*transitionCandidates.begin())->getTimings().getInvariantTimings();
				for(auto it = ++transitionCandidates.begin(); it != transitionCandidates.end(); ++it) {
					mergedHIV = merge({mergedHIV, (*it)->getTimings().getInvariantTimings()});
				}

				TRACE("hypro.datastructures.timing","Invariant HIV after merge: " << mergedHIV);

				if(!fullCover(mergedHIV, pathIt->getTimestamp(), CONTAINMENT::FULL)) {
					TRACE("hypro.datastructures.timing","Information incomplete, abort, required timestamp: " << pathIt->getTimestamp());
					return std::nullopt;
				}
			}

			// follow the discrete jump, if applicable
			++pathIt;
			if(pathIt != path.end()) {
				// set up new working set
				workingSet.clear();

				TRACE("hypro.datastructures.timing","Follow discrete step, have " << transitionCandidates.size() << " nodes.");

				// try to follow the transition
				assert(pathIt->isDiscreteStep());
				for(const auto n : transitionCandidates) {
					for(const auto ch : n->getChildren()) {
						if(ch->getEntryTransition() == pathIt->transition && carl::set_have_intersection(ch->getEntryTimestamp(), pathIt->getTimestamp())) {
							workingSet.insert(ch);
						}
					}
				}
				// increase pathIt to the next time step or the end of the path
				++pathIt;
			}
		}

		if(workingSet.empty()) {
			TRACE("hypro.datastructures.timing","No nodes found, abort.");
			return std::nullopt;
		}

		TRACE("hypro.datastructures.timing","After loop, have " << workingSet.size() << " nodes.");

		// at this point workingSet should contain all nodes which can be reached following the path. Merge those.
		auto nodeIt = workingSet.begin();
		EventTimingContainer<Number> res = (*nodeIt)->getTimings();
		++nodeIt;
		for( ;nodeIt != workingSet.end(); ++nodeIt ) {
			merge({res,(*nodeIt)->getTimings()});
		}
		return res;
	}

	template<typename Number>
	void EventTimingProvider<Number>::updateTimings(const Path<Number,tNumber>& path, const EventTimingContainer<Number>& update) {
		auto toUpdate = this->rGetNode(path);
		std::lock_guard<std::mutex> lock(toUpdate->rGetTimings().getMutex());

		toUpdate->rGetTimings().merge(update);
		#ifndef NDEBUG
		writeTree();
		#endif
	}

	template<typename Number>
	typename EventTimingNode<Number>::Node_t EventTimingProvider<Number>::addChildToNode(typename EventTimingNode<Number>::Node_t parent, tNumber timeHorizon) {
		typename EventTimingNode<Number>::Node_t newChild = new EventTimingNode<Number>(EventTimingContainer<Number>{timeHorizon});
		TRACE("hypro.datastructures.timing","Add child " << newChild << " to node " << parent);

		// set up tree
		newChild->addParent(parent);
		parent->addChild(newChild);
		#ifndef NDEBUG
		writeTree();
		#endif
		return newChild;
	}

	template<typename Number>
	std::string EventTimingProvider<Number>::getDotRepresentation() const {
		std::string nodes = "digraph structs \n { node [shape=record];\n";
		std::string transitions = "";
		std::string endDelimiter = "}\n";
		std::vector<unsigned> levels;

		mRoot->getDotRepresentation(0,nodes,transitions);

		return nodes + transitions + endDelimiter;
	}

	template<typename Number>
	EventTimingNode<Number>* EventTimingProvider<Number>::findNode(const Path<Number,tNumber>& path) const {
		TRACE("hypro.datastructures.timing","Get timings for path " << path);
		// to get the correct timing container we traverse from root to the end of the path.
		std::size_t pos = 0;

		// find the first initial node separately, since the root-node is not part of the path
		// Todo: We ignore several initial states for once.
		assert(!mRoot->getChildren().empty());
		auto curNode = (*mRoot->getChildren().begin());

		TRACE("hypro.datastructures.timing","Start at " << curNode );

		// traversal happens here:
		while(pos < path.size()) {
			TRACE("hypro.datastructures.timing","Position: " << pos);
			TRACE("hypro.datastructures.timing","Current node is " << curNode );
			if(path.at(pos).isDiscreteStep()) {
				TRACE("hypro.datastructures.timing","IsDiscreteStep, current node: " << curNode );
				//if(!curNode->getTimings().hasTransitionEvent(path.at(pos).timeInterval, path.at(pos).transition)) {
				if(!curNode->getTimings().hasTransitionEvent(path.at(pos).transition)) {
					TRACE("hypro.datastructures.timing", "There is no transition event, return nullptr.");
					return nullptr;
				}
				bool found = false;
				TRACE("hypro.datastructures.timing", "Consider " << curNode->getChildren().size() << " potential child nodes.");
				for(const auto& child : curNode->getChildren()) {
					if(child->getEntryTransition() == path.at(pos).transition && set_have_intersection(child->getEntryTimestamp(), (path.at(pos).timeInterval))) {
						TRACE("hypro.datastructures.timing", child << " is on the path (child timings: " << child->getTimings());
						curNode = child;
						found = true;
						// since we collect all children, there can be exactly ONE matching child.
						break;
					}
					#ifdef HYPRO_LOGGING
					else {
						TRACE("hypro.datastructures.timing", child << " is not on the path (child timings: " << child->getTimings());
						TRACE("hypro.datastructures.timing", "Reasons: Transitions match: " << (child->getEntryTransition() == path.at(pos).transition));
						TRACE("hypro.datastructures.timing", "Reasons: Timing intervals match: " << (set_have_intersection(child->getEntryTimestamp(), (path.at(pos).timeInterval))) << ", entry of child: " <<  carl::Interval<double>(child->getEntryTimestamp()) << " and this entry timestamp is " << carl::Interval<double>(path.at(pos).timeInterval) );
					}
					#endif
				}
				if(!found){
					return nullptr;
				}
				// find correct child node
			} else {
				// Todo: Add assertions to verify the time-transition here.
			}
			++pos;
		}

		TRACE("hypro.datastructures.timing","Return node " << curNode );
		return curNode;
	}

	template<typename Number>
	void EventTimingProvider<Number>::writeTree() const {
		auto file = LockedFileWriter{mName + ".gv"};
		file << getDotRepresentation();
	}

} // hypro
