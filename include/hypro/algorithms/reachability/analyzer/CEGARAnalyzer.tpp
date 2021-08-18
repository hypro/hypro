#ifndef CEGARANALYZER_TPP
#define CEGARANALYZER_TPP

#include "../../../representations/GeometricObjectBase.h"
#include "../../../util/combine.h"
#include "CEGARAnalyzer.h"

namespace hypro::detail {

template <class Number, class... Representations>
struct CEGARAnalyzer_apply<Number, Representations...>::CreateBaseLevel {
	template <class Representation>
	BaseLevel operator()( HybridAutomaton<Number> const& ha, FixedAnalysisParameters const& fixedParameters, AnalysisParameters const& parameters ) {
		auto roots = makeRoots<Representation>( ha );
		auto analyzer = LTIAnalyzer<Representation>{ ha, fixedParameters, parameters, roots };

		return BaseLevel{ ConcreteBaseLevel<Representation>{ { std::move( roots ) }, std::move( analyzer ) } };
	}
};

template <class Number, class... Representations>
struct CEGARAnalyzer_apply<Number, Representations...>::CreateRefinementLevel {
	template <class Representation>
	RefinementLevel operator()( HybridAutomaton<Number> const& ha, FixedAnalysisParameters const& fixedParameters, AnalysisParameters const& parameters ) {
		auto analyzer = RefinementAnalyzer<Representation>{ ha, fixedParameters, parameters };
		return RefinementLevel{ ConcreteRefinementLevel<Representation>{ {}, std::move( analyzer ) } };
	}
};

template <class Number, class... Representations>
auto CEGARAnalyzer_apply<Number, Representations...>::createBaseLevel( HybridAutomaton<Number> const& automaton, Settings const& settings ) -> BaseLevel {
	return dispatch<Number, Converter<Number>>( settings.strategy().front().representation_type,
												settings.strategy().front().representation_setting,
												CreateBaseLevel{},
												automaton, settings.fixedParameters(), settings.strategy().front() );
}

template <class Number, class... Representations>
auto CEGARAnalyzer_apply<Number, Representations...>::createRefinementLevel( size_t index ) -> RefinementLevel& {
	// if mLevels[index - 1] exists, return it
	if ( mLevels.size() >= index ) return mLevels.at( index - 1 );
	return mLevels.emplace_back(
		  dispatch<Number, Converter<Number>>( mSettings.strategy().at( index ).representation_type,
											   mSettings.strategy().at( index ).representation_setting,
											   CreateRefinementLevel{},
											   mHybridAutomaton, mSettings.fixedParameters(), mSettings.strategy().at( index ) ) );
}

template <class Number, class... Representations>
template <class SourceRep, class TargetLevel>
void CEGARAnalyzer_apply<Number, Representations...>::transferNodes( std::vector<ReachTreeNode<SourceRep>*>& sourceNodes,
																	 std::variant<Failure<Representations>...> targetFailure,
																	 TargetLevel& targetLevel ) {
	std::visit( [&]( auto& targetLevel_c ) {
		using TargetRep = analyzer_rep<decltype( targetLevel_c.analyzer )>;

		auto* targetNode_c = std::get<Failure<TargetRep>>( targetFailure ).conflictNode;
		for ( auto* sourceNode : sourceNodes ) {
			TargetRep initialSet{};
			convert( sourceNode->getInitialSet(), initialSet );	 // bad syntax. Means: initialSet = convert( node->getInitialSet() );

			auto& child = targetNode_c->addChild( initialSet, sourceNode->getTimings(), sourceNode->getTransition() );

			targetLevel_c.analyzer.addToQueue( &child );
		}
	},
				targetLevel.variant );
}

template <class Number, class... Representations>
template <class Representation>
void CEGARAnalyzer_apply<Number, Representations...>::handleFailure( ReachTreeNode<Representation>* conflictNode, size_t targetIndex ) {
	std::visit( [&]( auto& targetLevel ) {
		Path path = conflictNode->getPath();
		auto* targetRoot = &targetLevel.addOrGetRoot( mHybridAutomaton, path.rootLocation );
		targetLevel.analyzer.setRefinement( targetRoot, std::move( path ) );
	},
				createRefinementLevel( targetIndex ).variant );
}

template <class Number, class... Representations>
REACHABILITY_RESULT CEGARAnalyzer_apply<Number, Representations...>::run() {
	// data persistent through loop cycles
	std::vector<std::variant<Failure<Representations>...>> results( mSettings.strategy().size() );
	size_t levelInd = 0;
	bool save = true;

	// procedure:
	// run -> handle success or failure

	// continue while previous was safe or we can go to higher refinement
	while ( true ) {
		if ( levelInd == 0 ) {
			save = std::visit( [&]( auto& level ) {
				// run
				auto result = level.analyzer.run();
				// handle success
				if ( result.isSuccess() ) return true;
				// handle failure
				results.at( levelInd ) = result.failure();
				handleFailure( result.failure().conflictNode, levelInd + 1 );
				return false;
			},
							   mBaseLevel.variant );
			if ( save ) return REACHABILITY_RESULT::SAFE;
			levelInd += 1;
		} else {
			save = std::visit( [&]( auto& level ) {
				// run
				auto result = level.analyzer.run();
				if ( result.isSuccess() ) {
					// handle success
					if ( levelInd == 1 ) {
						transferNodes( result.success().pathSuccessors, results.at( 0 ), mBaseLevel );
					} else {
						auto& level = createRefinementLevel( levelInd - 1 );
						transferNodes( result.success().pathSuccessors, results.at( levelInd - 1 ), level );
					}
				} else if ( levelInd + 1 < mSettings.strategy().size() ) {
					// handle failure, if there's a next level to go to
					results.at( levelInd ) = result.failure();
					handleFailure( result.failure().conflictNode, levelInd + 1 );
				}
				return result.isSuccess();
			},
							   createRefinementLevel( levelInd ).variant );
			levelInd += save ? -1 : 1;
			if ( levelInd == mSettings.strategy().size() ) return REACHABILITY_RESULT::UNKNOWN;
		}
	}
}

}  // namespace hypro::detail

#endif