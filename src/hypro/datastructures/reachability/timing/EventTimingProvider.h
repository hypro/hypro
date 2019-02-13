#pragma once

#include "EventTimingContainer.h"
#include "EventTimingNode.h"
#include "../SettingsProvider.h"
#include "../../HybridAutomaton/HybridAutomaton.h"
#include "../../HybridAutomaton/Path.h"
#include "../../../util/logging/Filewriter.h"
#include "../../../util/logging/Logger.h"
#include "../Settings.h"
#include <carl/util/Singleton.h>
#include <string>
#include <optional>

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
	std::string mName = "timingTree";

public:

	void initialize(const HybridAutomaton<Number>& ha, tNumber globalTimeHorizon);
	void initialize(const Location<Number>* loc, tNumber globalTimeHorizon);

	void setName(const std::string& name) { mName = name; }
	const std::string& getName() const { return mName; }

	EventTimingNode<Number>* getRoot() { return mRoot; }

	void clear() { delete mRoot; mRoot = new EventTimingNode<Number>(); }

	/**
	 * @brief	Find the best suitable node in the timing tree which matches the passed path.
	 */
	const EventTimingNode<Number>* getTimingNode(const Path<Number,tNumber>& path) const;

	/**
	 * @brief	Find the best suitable node in the timing tree which matches the passed path.
	 */
	EventTimingNode<Number>* rGetNode(const Path<Number,tNumber>& path) const;

	std::optional<EventTimingContainer<Number>> getTimings(const Path<Number,tNumber>& path) const;

	void updateTimings(const Path<Number,tNumber>& path, const EventTimingContainer<Number>& update);

	typename EventTimingNode<Number>::Node_t addChildToNode(typename EventTimingNode<Number>::Node_t parent, tNumber timeHorizon);

	std::string getDotRepresentation() const;

private:
	EventTimingNode<Number>* findNode(const Path<Number,tNumber>& path) const;
	void writeTree() const;

};

} // hypro

#include "EventTimingProvider.tpp"
