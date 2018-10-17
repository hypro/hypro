#include "EventTimingProvider.h"

namespace hypro {

	template<typename Number>
	EventTimingProvider<Number>::EventTimingProvider() : mRoot(new EventTimingNode<Number>()){
		mRoot->setDepth(0);
		TRACE("hydra.datastructures.timing","Root is " << mRoot);
	}

	template<typename Number>
	void EventTimingProvider<Number>::initialize(const HybridAutomaton<Number>& ha) {
		tNumber timeHorizon = SettingsProvider<Number>::getInstance().getReachabilitySettings().timeBound*SettingsProvider<Number>::getInstance().getReachabilitySettings().jumpDepth;
		for(const auto& state : ha.getInitialStates()) {
			EventTimingNode<Number>* child = new EventTimingNode<Number>(EventTimingContainer<Number>(timeHorizon));
			child->setParent(mRoot);
			child->setLocation(state.first);
			child->setEntryTimestamp(carl::Interval<tNumber>(0));
			mRoot->addChild(child);
			TRACE("hydra.datastructures.timing","Add initial node " << child);
		}

		/*
		ReachabilitySettings<Number>& settings = SettingsProvider<Number>::getInstance().getReachabilitySettings();
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
	EventTimingContainer<Number>* EventTimingProvider<Number>::getTimings(const Path<Number,tNumber>& path) const{
		TRACE("hydra.datastructures.timing","Get timings for path " << path);
		// to get the correct timing container we traverse from root to the end of the path.
		typename EventTimingContainer<Number>::Node_t res = mRoot;
		std::size_t pos = 0;

		// find the first initial node separately, since the root-node is not part of the path
		// Todo: We ignore several initial states for once.
		assert(!mRoot->getChildren().empty());
		res = *mRoot->getChildren().begin();

		TRACE("hydra.datastructures.timing","Start at " << *res << " (@" << res << ")");

		// traversal happens here:
		while(pos < path.size()) {
			TRACE("hydra.datastructures.timing","Position: " << pos);
			TRACE("hydra.datastructures.timing","Current res. is " << *res << " (@" << res << ")");
			if(path.at(pos).isDiscreteStep()) {
				TRACE("hydra.datastructures.timing","IsDiscreteStep, res: " << res);
				assert(res->hasTransitionEvent(path.at(pos).timeInterval, path.at(pos).transition));
				if(!res->hasTransitionEvent(path.at(pos).timeInterval, path.at(pos).transition)) {
					return mRoot;
				}
				#ifndef NDEBUG
				bool found = false;
				#endif
				for(const auto& child : res->getChildren()) {
					if(child->getEntryTransition() == path.at(pos).transition && child->getEntryTimestamp().intersectsWith(path.at(pos).timeInterval)) {
						res = child;
						#ifndef NDEBUG
						found = true;
						#endif
						// since we collect all children, there can be exactly ONE matching child.
						break;
					}
				}
				assert(found);
				// find correct child node
			} else {
				// Todo: Add assertions to verify the time-transition here.
			}
			++pos;
		}

		TRACE("hydra.datastructures.timing","Return node " << res );
		return res;
	}

	template<typename Number>
	void EventTimingProvider<Number>::updateTimings(const Path<Number,tNumber>& path, const EventTimingContainer<Number>& update) {
		typename EventTimingContainer<Number>::Node_t toUpdate = const_cast<typename EventTimingContainer<Number>::Node_t>(this->getTimings(path));
		assert(toUpdate != mRoot);
		std::lock_guard<std::mutex> lock(toUpdate->getMutex());

		toUpdate->merge(update);
	}

	template<typename Number>
	TreeNode::Node_t EventTimingProvider<Number>::addChildToNode(TreeNode::Node_t parent, tNumber timeHorizon) {
		TRACE("hydra.datastructures.timing","Add child to node " << parent);
		typename EventTimingContainer<Number>::Node_t newChild = new EventTimingContainer<Number>(timeHorizon);
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
		mRoot->getDotRepresentation(0,nodes,transitions,levels);

		std::string levelCounts = "//";
		for(std::size_t i = 0; i < levels.size(); ++i){
			levelCounts += std::to_string(i);
			levelCounts += ": ";
			levelCounts += std::to_string(levels[i]);
			levelCounts += ", ";
		}

		levelCounts += "\n";

		return nodes + transitions + endDelimiter + levelCounts;

	}

} // hypro
