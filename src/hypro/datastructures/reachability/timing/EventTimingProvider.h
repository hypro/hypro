#pragma once

#include "../../../util/logging/Filewriter.h"
#include "../../../util/logging/Logger.h"
#include "../../HybridAutomaton/HybridAutomaton.h"
#include "../../HybridAutomaton/Path.h"
#include "../Settings.h"
#include "../SettingsProvider.h"
#include "EventTimingContainer.h"
#include "EventTimingNode.h"

#include <carl/util/Singleton.h>
#include <optional>
#include <string>

namespace hypro {
template <typename Number>
class EventTimingProvider : public carl::Singleton<EventTimingProvider<Number>> {
	friend carl::Singleton<EventTimingProvider<Number>>;

  protected:
	EventTimingProvider();

  private:
	typename EventTimingNode<Number>::Node_t mRoot;
	std::string mName = "timingTree";

  public:
	void initialize( const HybridAutomaton<Number>& ha, tNumber globalTimeHorizon );
	void initialize( const Location<Number>* loc, tNumber globalTimeHorizon );

	void setName( const std::string& name ) { mName = name; }
	const std::string& getName() const { return mName; }

	EventTimingNode<Number>* getRoot() { return mRoot; }

	void clear() {
		delete mRoot;
		mRoot = new EventTimingNode<Number>();
	}

	~EventTimingProvider() {
		delete mRoot;
	}

	/**
	 * @brief	Find the best suitable node in the timing tree which matches the passed path.
	 */
	const EventTimingNode<Number>* getTimingNode( const Path<Number, tNumber>& path, std::size_t level = 0 ) const;

	/**
	 * @brief	Find the best suitable node in the timing tree which matches the passed path.
	 */
	EventTimingNode<Number>* rGetNode( const Path<Number, tNumber>& path, std::size_t level = 0 ) const;

	std::optional<EventTimingContainer<Number>> getTimings( const Path<Number, tNumber>& path ) const;

	void updateTimings( const Path<Number, tNumber>& path, const EventTimingContainer<Number>& update );

	typename EventTimingNode<Number>::Node_t addChildToNode( typename EventTimingNode<Number>::Node_t parent, tNumber timeHorizon );

	std::string getDotRepresentation() const;

  private:
	EventTimingNode<Number>* findNode( const Path<Number, tNumber>& path, std::size_t level ) const;
	void writeTree() const;

	// for dbg
	void printSet( const std::vector<std::set<EventTimingNode<Number>*>>& sets ) const {
		TRACE( "hypro.datastructures.timing", "Have " << sets.size() << " sets." );
		for ( const auto& set : sets ) {
			TRACE( "hypro.datastructures.timing", "Have " << set.size() << " containers." );
			for ( const auto sPtr : set ) {
				TRACE( "hypro.datastructures.timing", "Container " << *sPtr );
			}
		}
	}
};

}  // namespace hypro

#include "EventTimingProvider.tpp"
