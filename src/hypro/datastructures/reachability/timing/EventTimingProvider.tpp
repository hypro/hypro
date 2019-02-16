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
		std::vector<std::set<EventTimingNode<Number>*>> workingSets;
		// stores candidates which match the timeStep
		std::vector<std::set<EventTimingNode<Number>*>> transitionCandidates;

		// fill working set with initial nodes
		for(const auto nPtr : mRoot->getChildren()) {
			workingSets.emplace_back(std::set<EventTimingNode<Number>*>{});
			workingSets.back().emplace(nPtr);
			// prepare structure of 2nd set
			transitionCandidates.emplace_back(std::set<EventTimingNode<Number>*>{});
		}

		// iterate over path / follow the path
		auto pathIt = path.begin();
		while(pathIt != path.end()) {
			assert(workingSets.size() == transitionCandidates.size());
			TRACE("hypro.datastructures.timing","Follow time step, have " << workingSets.size() << " path-candidates.");
			// remove all nodes from working set whose invariant timings do not contain the time interval in the path
			assert(!pathIt->isDiscreteStep());
			// verify against invariant timings.
			// Two-phase approach: Collect all which satisfy the invariant somehow,
			// then merge invariant intervals and check whether the invariant was satisfied the whole time.

			// use flag to exit loop early
			bool allEmpty = true;

			for(std::size_t setIndex = 0; setIndex < workingSets.size(); ++setIndex){
				for(auto nodeIt = workingSets[setIndex].begin(); nodeIt != workingSets[setIndex].end();) {
					allEmpty = false;
					// check for full containment
					if((*nodeIt)->getTimings().satisfiedInvariant(pathIt->getTimestamp())) {
						transitionCandidates[setIndex].insert(*nodeIt);
						nodeIt = workingSets[setIndex].erase(nodeIt);
					} else if ((*nodeIt)->getTimings().getInvariantTimings().intersectsEntry(pathIt->getTimestamp(), CONTAINMENT::FULL) ||
					(*nodeIt)->getTimings().getInvariantTimings().intersectsEntry(pathIt->getTimestamp(), CONTAINMENT::PARTIAL) ||
					(*nodeIt)->getTimings().getInvariantTimings().intersectsEntry(pathIt->getTimestamp(), CONTAINMENT::YES) ) {
						// check for partial containment
						transitionCandidates[setIndex].insert(*nodeIt);
						nodeIt = workingSets[setIndex].erase(nodeIt);
						//TRACE("hypro.datastructures.timing","Not enough information, abort.");
						//return std::nullopt;
					} else {
						assert(!(*nodeIt)->getTimings().hasInvariantEvent(pathIt->getTimestamp(), CONTAINMENT::YES));
						assert(!(*nodeIt)->getTimings().hasInvariantEvent(pathIt->getTimestamp(), CONTAINMENT::PARTIAL));
						assert(!(*nodeIt)->getTimings().hasInvariantEvent(pathIt->getTimestamp(), CONTAINMENT::FULL));
						// the node does not satisfy the invariant, erase
						nodeIt = workingSets[setIndex].erase(nodeIt);
					}
				}
				assert(workingSets[setIndex].empty());
			}

			assert(workingSets.size() == transitionCandidates.size());

			if(allEmpty) {
				return std::nullopt;
			}

			TRACE("hypro.datastructures.timing","Working set.");
			printSet(workingSets);
			TRACE("hypro.datastructures.timing","Transition candidates.");
			printSet(transitionCandidates);

			// merge invariant intervals to detect whether the invariant interval is fully covered
			for(auto& subset : transitionCandidates) {
				if(!subset.empty()) {
					TRACE("hypro.datastructures.timing","Merge invariant intervals of " << subset.size() << " candidates.");
					HierarchicalIntervalVector<CONTAINMENT,tNumber> mergedHIV((*subset.begin())->getTimings().getInvariantTimings());
					// merge all invariant information
					for(auto it = ++subset.begin(); it != subset.end(); ++it) {
						mergedHIV = merge({mergedHIV, (*it)->getTimings().getInvariantTimings()});
					}

					TRACE("hypro.datastructures.timing","Invariant HIV after merge: " << mergedHIV);

					// if the invariant cannot be fully covered (information missing), remove subset (clear).
					if(!fullCover(mergedHIV, pathIt->getTimestamp(), CONTAINMENT::FULL)) {
						subset.clear();
						TRACE("hypro.datastructures.timing","Clear the subset, no full cover detected.");
						assert(subset.empty());
					}
				}
			}

			TRACE("hypro.datastructures.timing","Working set.");
			printSet(workingSets);
			TRACE("hypro.datastructures.timing","Transition candidates.");
			printSet(transitionCandidates);

			assert(workingSets.size() == transitionCandidates.size());

			// follow the discrete jump, if applicable
			++pathIt;
			if(pathIt != path.end()) {
				// set up new working set
				TRACE("hypro.datastructures.timing","Follow discrete step, have " << transitionCandidates.size() << " sets.");

				// try to follow the transition
				assert(pathIt->isDiscreteStep());
				for(std::size_t setIndex = 0; setIndex < transitionCandidates.size(); ++setIndex) {
					assert(workingSets[setIndex].empty());
					for(const auto nPtr : transitionCandidates[setIndex]) {
						TRACE("hypro.datastructures.timing","Consider " << transitionCandidates[setIndex].size() << " nodes.");
						for(const auto chPtr : nPtr->getChildren()) {
							if(chPtr->getEntryTransition() == pathIt->transition && carl::set_have_intersection(chPtr->getEntryTimestamp(), pathIt->getTimestamp())) {
								TRACE("hypro.datastructures.timing","Found matching node.");
								workingSets[setIndex].insert(chPtr);
							}
						}
					}
					// prepare for next iteration.
					transitionCandidates[setIndex].clear();
				}
				// increase pathIt to the next time step or the end of the path
				++pathIt;
			} else {
				// the last element in the path was a time step, move nodes to workingSet
				TRACE("hypro.datastructures.timing","Copy transitionCandidates to workingSet.");
				workingSets = transitionCandidates;
			}
		}
		assert(workingSets.size() == transitionCandidates.size());
		assert(workingSets.size() == mRoot->getChildren().size());

		TRACE("hypro.datastructures.timing","After loop, have " << workingSets.size() << " subsets.");

		// at this point workingSet should contain all nodes which can be reached following the path. Merge those and get the most precise.
		bool allEmpty = true;
		std::vector<EventTimingContainer<Number>> candidates;
		for(const auto& set : workingSets) {
			if(!set.empty()) {
				TRACE("hypro.datastructures.timing","Merge timings of " << set.size() << " containers.");
				allEmpty =  false;
				auto nodeIt = set.begin();
				EventTimingContainer<Number> res = (*nodeIt)->getTimings();
				++nodeIt;
				for( ;nodeIt != set.end(); ++nodeIt ) {
					res = merge({res,(*nodeIt)->getTimings()});
				}
				candidates.emplace_back(std::move(res));
			}
		}

		if(allEmpty) {
			return std::nullopt;
		}

		return intersect(candidates);
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
