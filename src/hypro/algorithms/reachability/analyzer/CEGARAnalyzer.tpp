#include "CEGARAnalyzer.h"
#include "representations/GeometricObjectBase.h"
#include "util/combine.h"

namespace hypro {

template <class Number, class... Representations>
struct CEGARAnalyzer<Number, Representations...>::CreateBaseLevel {
	template <class Representation>
	BaseLevel operator()( HybridAutomaton<Number> const& ha, Settings const& settings ) {
		auto roots = makeRoots<Representation>( ha );
		auto analyzer = LTIAnalyzer<Representation>{ ha, settings, roots };

		return BaseLevel{ ConcreteBaseLevel<Representation>{ std::move( analyzer ), std::move( roots ) } };
	}
};

template <class Number, class... Representations>
struct CEGARAnalyzer<Number, Representations...>::CreateRefinementLevel {
	template <class Representation>
	RefinementLevel operator()( HybridAutomaton<Number> const& ha, Settings const& settings ) {
		auto analyzer = RefinementAnalyzer<Representation>{ ha, settings };
		return RefinementLevel{ ConcreteRefinementLevel<Representation>{ std::move( analyzer ), {} } };
	}
};

template <class Number, class... Representations>
auto CEGARAnalyzer<Number, Representations...>::createBaseLevel( HybridAutomaton<Number> const& automaton, Settings const& settings ) -> BaseLevel {
	return dispatch<Number, Converter<Number>>( settings.strategy.front().representation_type,
												settings.strategy.front().representation_setting,
												CreateBaseLevel{},
												automaton, settings );
}

template <class Number, class... Representations>
auto CEGARAnalyzer<Number, Representations...>::createRefinementLevel( size_t index ) -> RefinementLevel& {
	// if mLevels[index - 1] exists, return it
	if ( mLevels.size() >= index ) return mLevels.at( index - 1 );
	return mLevels.emplace_back(
		  dispatch<Number, Converter<Number>>( mSettings.strategy.at( index ).representation_type,
											   mSettings.strategy.at( index ).representation_setting,
											   CreateRefinementLevel{},
											   mHybridAutomaton, mSettings ) );
}

template <class Number, class... Representations>
template <class LevelFrom, class LevelTo>
void CEGARAnalyzer<Number, Representations...>::transferNodes( LevelFrom& from, TreeNodePtr& nodePtrTo, LevelTo& to ) {
	std::visit( [&]( auto& currLevel ) {
		std::visit( [&]( auto& prevLevel ) {
			using PrevRep = analyzer_rep<decltype( prevLevel.analyzer )>;

			auto* prevNode = std::get<ReachTreeNode<PrevRep>*>( nodePtrTo );
			for ( auto* currNode : currLevel.analyzer.workQueue() ) {
				PrevRep initialSet{};
				convert( currNode->getInitialSet(), initialSet );  // bad syntax. Means: initialSet = convert( node->getInitialSet() )

				auto& child = prevNode->addChild( initialSet, currNode->getTimings(), currNode->getTransition() );

				prevLevel.analyzer.addToQueue( &child );
			}
		},
					to.variant );
	},
				from.variant );
}

template <class Number, class... Representations>
REACHABILITY_RESULT CEGARAnalyzer<Number, Representations...>::run() {

	// procedure:
	// if on first level -> run level, on success: return , on failure: prepare next level
	// if on different level -> run level, on success: reset to previous level, on failure: prepare next level

	// invariant at start of loop: level at levelInd is created and ready to run

	/*while ( true ) {
		// trying a level higher than we have available means we failed at all levels :'(
		if ( levelInd == mSettings.strategy.size() ) return REACHABILITY_RESULT::UNKNOWN;

		// special handling for first level
		if ( levelInd == 0 ) {
			// run level
			REACHABILITY_RESULT result;
			std::tie( result, nodes.at( levelInd ) ) = mBaseLevel.run();
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
			REACHABILITY_RESULT result;
			std::tie( result, nodes.at( levelInd ) ) = mLevels.at( levelInd - 1 ).run();  // mLevels is offset by -1 because first level is handeled specially

			if ( result == REACHABILITY_RESULT::SAFE ) {  // on success: reset to previous level
				transferNodes( mLevels.at( levelInd - 1 ), nodes.at( levelInd ), mLevels.at( levelInd - 2 ) );
				levelInd -= 1;
			} else {
				// on failure: prepare next level
				auto [path, loc] = std::visit( []( auto* n ) {
					return std::pair{ n->getPath(), n->getLocation() };
				},
													nodes.at( levelInd ) );

				auto& level = createRefinementLevel( levelInd + 1 );
				std::visit( [loc=loc, &path = path]( auto& l ) {
					l.analyzer.setPath( path );
					auto rootIt = std::find_if( l.roots.begin(), l.roots.end(), [&]( auto& root ) { return root.getLocation() == loc; } );
					auto& root = ( rootIt == l.roots.end() ) ? l.roots.emplace_back( loc, { m }, carl::Interval{ 0, 0 } ): ;
				} )

					  levelInd += 1;
			}
		}
	}*/

	// procedure:
	// check results of prev. invocation -> prepare next run -> run

	std::vector<TreeNodePtr> nodes( mSettings.strategy.size() );
	size_t levelInd = 0;
	REACHABILITY_RESULT result;

	std::tie( result, nodes.at( levelInd ) ) = mBaseLevel.run();
	if ( result == REACHABILITY_RESULT::SAFE ) return REACHABILITY_RESULT::SAFE;

	while ( levelInd < mSettings.strategy.size() - 1 ) {
		// prev invocation ran into bad states -> climbing levels
		// get info from last invocation
		auto [path, loc] = std::visit( []( auto* n ) {
			return std::pair{ n->getPath(), n->getLocation() };
		},
											nodes.at( levelInd ) );
		// make sure next level exists and set path and initial state
		auto& level = createRefinementLevel( levelInd + 1 );
		std::visit( [&, &path=path, loc=loc]( auto& l ) {
			auto& root = l.addOrGetRoot( mHybridAutomaton, loc );
			l.analyzer.addToQueue( &root );
			l.analyzer.setPath( path );
		},
					level.variant );

		std::tie( result, nodes.at( levelInd + 1 ) ) = level.run();
		levelInd = levelInd + 1;

		while ( result == REACHABILITY_RESULT::SAFE ) {
			// prev invocation went through -> descend levels
			if ( levelInd == 0 ) return REACHABILITY_RESULT::SAFE;

			if ( levelInd == 1 ) {
				transferNodes( mLevels.at( levelInd - 1 ), nodes.at( levelInd ), mBaseLevel );	// mLevels is offset by one, so moving nodes from lvl 1 to 0
				std::tie( result, nodes.at( levelInd - 1 ) ) = mBaseLevel.run();
			} else {
				transferNodes( mLevels.at( levelInd - 1 ), nodes.at( levelInd ), mLevels.at( levelInd - 2 ) );	// moving nodes from levelInd to levelInd - 1
				std::tie( result, nodes.at( levelInd - 1 ) ) = mLevels[levelInd - 2].run();
			}

			levelInd -= 1;
		}
	}

	return REACHABILITY_RESULT::SAFE;
}

}  // namespace hypro
