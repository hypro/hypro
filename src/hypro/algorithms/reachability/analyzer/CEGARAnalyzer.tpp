#include "CEGARAnalyzer.h"
#include "representations/GeometricObjectBase.h"
#include "util/combine.h"

namespace hypro {

template <class Number>
struct CEGARAnalyzer<Number>::CreateBaseLevel {
	template <class Representation>
	BaseLevel operator()( HybridAutomaton<Number> const& ha, Settings const& settings ) {
		auto roots = makeRoots<Representation>( ha );
		auto analyzer = LTIAnalyzer<Representation>{ ha, settings, roots };

		return BaseLevel{ ConcreteBaseLevel<Representation>{ std::move( analyzer ), std::move( roots ) } };
	}
};

template <class Number>
struct CEGARAnalyzer<Number>::CreateRefinementLevel {
	template <class Representation>
	RefinementLevel operator()( HybridAutomaton<Number> const& ha, Settings const& settings, Path<Number> path,
								Location<Number> const* loc ) {
		auto const& condition = ha.getInitialStates().at( loc );
		ReachTreeNode<Representation> root{ loc, Representation{ condition.getMatrix(), condition.getVector() }, carl::Interval{ 0, 0 } };
		auto analyzer = RefinementAnalyzer<Representation>{ ha, settings, root, path };

		return RefinementLevel{ ConcreteRefinementLevel<Representation>{ std::move( analyzer ), std::move( root ) } };
	}
};

template <class Number>
auto CEGARAnalyzer<Number>::createBaseLevel() -> BaseLevel {
	return dispatch<Number, Converter<Number>>( mSettings.strategy.front().representation_type,
												mSettings.strategy.front().representation_setting,
												CreateBaseLevel{},
												mHybridAutomaton, mSettings );
}

template <class Number>
auto CEGARAnalyzer<Number>::createRefinementLevel( size_t index, Path<Number> path,
												   Location<Number> const* loc ) -> RefinementLevel& {
	// if mLevels[index - 1] exists, return it
	if ( mLevels.size() >= index ) return mLevels.at( index - 1 );
	return mLevels.emplace_back(
		  dispatch<Number, Converter<Number>>( mSettings.strategy.at( index ).representation_type,
											   mSettings.strategy.at( index ).representation_setting,
											   CreateRefinementLevel{},
											   mHybridAutomaton, mSettings, path, loc ) );
}

template <class Number>
REACHABILITY_RESULT CEGARAnalyzer<Number>::run() {
	// the first level (levelInd 0), handeled specially
	BaseLevel firstLevel = createBaseLevel();

	REACHABILITY_RESULT result;
	std::vector<TreeNodePtr> nodes( mSettings.strategy.size() );
	size_t levelInd = 0;

	// procedure:
	// if on first level -> run level, on success: return , on failure: prepare next level
	// if on different level -> run level, on success: reset to previous level, on failure: prepare next level

	while ( true ) {
		// trying a level higher than we have available means we failed at all levels :'(
		if ( levelInd == mSettings.strategy.size() ) return REACHABILITY_RESULT::UNKNOWN;

		// special handling for first level
		if ( levelInd == 0 ) {
			// run level
			std::tie( result, nodes.at( levelInd ) ) = firstLevel.run();
			//on success: return
			if ( result == REACHABILITY_RESULT::SAFE ) return REACHABILITY_RESULT::SAFE;

			//on failure: prepare next level
			auto [path, location] = std::visit( []( auto* n ) {
				return std::pair{ n->getPath(), n->getLocation() };
			},
												nodes.at( levelInd ) );

			createRefinementLevel( levelInd + 1, path, location );
			levelInd += 1;
		} else {
			// run level
			std::tie( result, nodes.at( levelInd ) ) = mLevels.at( levelInd - 1 ).run();  // mLevels is offset by -1 because first level is handeled specially

			// on success: reset to previous level
			std::visit( [&]( auto& currLevel ) {
				std::visit( [&]( auto& prevLevel ) {
					using PrevRep = analyzer_rep<decltype( prevLevel.analyzer )>;

					auto* prevNode = std::get<ReachTreeNode<PrevRep>*>( nodes.at( levelInd - 1 ) );
					for ( auto* currNode : currLevel.analyzer.workQueue() ) {
						PrevRep initialSet{};
						convert( currNode->getInitialSet(), initialSet );  // bad syntax. Means: initialSet = convert( node->getInitialSet() )

						auto& child = prevNode->addChild( initialSet, currNode->getTimings(), currNode->getTransition() );
						//TODO add to work queue of prevLevel
					}
				},
							mLevels.at( levelInd - 2 ).variant );
			},
						mLevels.at( levelInd - 1 ).variant );

			// on failure: prepare next level
			auto [path, location] = std::visit( []( auto* n ) {
				return std::pair{ n->getPath(), n->getLocation() };
			},
												nodes.at( levelInd ) );

			createRefinementLevel( levelInd + 1, path, location );
			levelInd += 1;
		}
	}

	return REACHABILITY_RESULT::SAFE;
}

}  // namespace hypro
