#pragma once

#include "EventTimingContainer.h"
#include "EventTimingNode.h"
#include "../SettingsProvider.h"
#include "../../HybridAutomaton/HybridAutomaton.h"
#include "../../HybridAutomaton/Path.h"
#include "../Settings.h"
#include <carl/util/Singleton.h>

namespace hypro
{
template<typename Number>
class EventTimingProvider : public carl::Singleton<EventTimingProvider<Number>>
{
    friend carl::Singleton<EventTimingProvider<Number>>;

protected:
	EventTimingProvider();

private:
	typename EventTimingNode<Number>::Node_t mRoot;

public:
	
	void initialize(const HybridAutomaton<Number>& ha);
	
	EventTimingContainer<Number>* getTimings(const Path<Number,tNumber>& path) const;
	
	void updateTimings(const Path<Number,tNumber>& path, const EventTimingContainer<Number>& update);

	typename EventTimingNode<Number>::Node_t addChildToNode(typename TreeNode<EventTimingNode<Number>>::Node_t parent, tNumber timeHorizon);

	std::string getDotRepresentation() const;
};

} // hypro

#include "EventTimingProvider.tpp"
