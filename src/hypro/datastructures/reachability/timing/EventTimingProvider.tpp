#include "EventTimingProvider.h"

namespace hypro {

	template<typename Number>
	EventTimingProvider<Number>::EventTimingProvider() : mRoot(new EventTimingNode<Number>()){
		mRoot->setDepth(0);
		TRACE("hypro.datastructures.timing","Root is " << mRoot);
	}

	template<typename Number>
	void EventTimingProvider<Number>::initialize(const HybridAutomaton<Number>& ha, tNumber globalTimeHorizon) {
		for(const auto& state : ha.getInitialStates()) {
			EventTimingNode<Number>* child = new EventTimingNode<Number>(EventTimingContainer<Number>(globalTimeHorizon));
			child->setParent(mRoot);
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
	}

	template<typename Number>
	const EventTimingNode<Number>* EventTimingProvider<Number>::getTimingNode(const Path<Number,tNumber>& path) const{
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
				if(!curNode->getTimings().hasTransitionEvent(path.at(pos).timeInterval, path.at(pos).transition)) {
					TRACE("hypro.datastructures.timing", "There is no transition event, return nullptr.");
					return nullptr;
				}
				#ifndef NDEBUG
				bool found = false;
				#endif
				TRACE("hypro.datastructures.timing", "Consider " << curNode->getChildren().size() << " potential child nodes.");
				for(const auto& child : curNode->getChildren()) {
					if(child->getTimings().getEntryTransition() == path.at(pos).transition && set_have_intersection(child->getTimings().getEntryTimestamp(), (path.at(pos).timeInterval))) {
						TRACE("hypro.datastructures.timing", child << " is on the path (child timings: " << child->getTimings());
						curNode = child;
						#ifndef NDEBUG
						found = true;
						#endif
						// since we collect all children, there can be exactly ONE matching child.
						break;
					}
					#ifdef HYPRO_LOGGING
					else {
						TRACE("hypro.datastructures.timing", child << " is not on the path (child timings: " << child->getTimings());
						TRACE("hypro.datastructures.timing", "Reasons: Transitions match: " << (child->getTimings().getEntryTransition() == path.at(pos).transition));
						TRACE("hypro.datastructures.timing", "Reasons: Timing intervals match: " << (set_have_intersection(child->getTimings().getEntryTimestamp(), (path.at(pos).timeInterval))) << ", entry of child: " <<  child->getTimings().getEntryTimestamp() << " and this entry timestamp is " << path.at(pos).timeInterval );
					}
					#endif
				}
				assert(found);
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
	EventTimingNode<Number>* EventTimingProvider<Number>::rGetNode(const Path<Number,tNumber>& path) {
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
				#ifndef NDEBUG
				bool found = false;
				#endif
				TRACE("hypro.datastructures.timing", "Consider " << curNode->getChildren().size() << " potential child nodes.");
				for(const auto& child : curNode->getChildren()) {
					if(child->getTimings().getEntryTransition() == path.at(pos).transition && set_have_intersection(child->getTimings().getEntryTimestamp(), (path.at(pos).timeInterval))) {
						TRACE("hypro.datastructures.timing", child << " is on the path (child timings: " << child->getTimings());
						curNode = child;
						#ifndef NDEBUG
						found = true;
						#endif
						// since we collect all children, there can be exactly ONE matching child.
						break;
					}
					#ifdef HYPRO_LOGGING
					else {
						TRACE("hypro.datastructures.timing", child << " is not on the path (child timings: " << child->getTimings());
						TRACE("hypro.datastructures.timing", "Reasons: Transitions match: " << (child->getTimings().getEntryTransition() == path.at(pos).transition));
						TRACE("hypro.datastructures.timing", "Reasons: Timing intervals match: " << (set_have_intersection(child->getTimings().getEntryTimestamp(), (path.at(pos).timeInterval))) << ", entry of child: " <<  child->getTimings().getEntryTimestamp() << " and this entry timestamp is " << path.at(pos).timeInterval );
					}
					#endif
				}
				assert(found);
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
	void EventTimingProvider<Number>::updateTimings(const Path<Number,tNumber>& path, const EventTimingContainer<Number>& update) {
		auto toUpdate = this->rGetNode(path);
		std::lock_guard<std::mutex> lock(toUpdate->rGetTimings().getMutex());

		toUpdate->rGetTimings().merge(update);
	}

	template<typename Number>
	typename EventTimingNode<Number>::Node_t EventTimingProvider<Number>::addChildToNode(typename TreeNode<EventTimingNode<Number>>::Node_t parent, tNumber timeHorizon) {
		typename EventTimingNode<Number>::Node_t newChild = new EventTimingNode<Number>(EventTimingContainer<Number>{timeHorizon});
		TRACE("hypro.datastructures.timing","Add child " << newChild << " to node " << parent);
		newChild->setParent(parent);
		parent->addChild(newChild);
		return newChild;
	}

	template<typename Number>
	std::string EventTimingProvider<Number>::getDotRepresentation() const {
		std::string nodes = "digraph structs \n { node [shape=record];\n";
		std::string transitions = "";
		std::string endDelimiter = "}\n";
		std::vector<unsigned> levels;
		mRoot->getDotRepresentation(0,nodes,transitions);

		/*
		std::string levelCounts = "//";
		for(std::size_t i = 0; i < levels.size(); ++i){
			levelCounts += std::to_string(i);
			levelCounts += ": ";
			levelCounts += std::to_string(levels[i]);
			levelCounts += ", ";
		}

		levelCounts += "\n";

		return nodes + transitions + endDelimiter + levelCounts;
		*/
		return nodes + transitions + endDelimiter;
	}

} // hypro
