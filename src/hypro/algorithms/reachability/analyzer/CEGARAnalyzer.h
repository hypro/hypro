#pragma once
#include "../../../datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../../../datastructures/reachability/ReachTreev2.h"
#include "../../../datastructures/reachability/Strategy.h"
#include "../../../types.h"
#include "./impl/RefinementAnalyzer.h"
#include "algorithms/reachability/analyzer/LTIAnalyzer.h"
#include "util/plotting/Plotter.h"
#include "util/type_handling/dispatch.h"

#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/counting_range.hpp>
#include <functional>
#include <queue>
#include <variant>

namespace hypro {

template <class Number, class... Representations>
class CEGARAnalyzer {
	using TreeNodePtr = std::variant<ReachTreeNode<Representations>*...>;

	template <class Representation>
	struct ConcreteRefinementLevel {
		RefinementAnalyzer<Representation> analyzer;
		std::vector<ReachTreeNode<Representation>> roots{};

		ReachTreeNode<Representation>& addOrGetRoot( HybridAutomaton<Number> const& automaton, Location<Number> const* loc ) {
			auto rootIt = std::find_if( roots.begin(), roots.end(), [&]( auto& root ) { return root.getLocation() == loc; } );
			if ( rootIt == roots.end() ) {
				auto const& condition = automaton.getInitialStates().at( loc );
				return roots.emplace_back( loc, Representation{ condition.getMatrix(), condition.getVector() }, carl::Interval{ 0, 0 } );
			}
			return *rootIt;
		}

		ConcreteRefinementLevel( ConcreteRefinementLevel const& ) = delete;
		ConcreteRefinementLevel& operator=( ConcreteRefinementLevel const& ) = delete;

		ConcreteRefinementLevel( ConcreteRefinementLevel&& ) = default;
		ConcreteRefinementLevel& operator=( ConcreteRefinementLevel&& ) = default;
	};

	template <class Representation>
	struct ConcreteBaseLevel {
		LTIAnalyzer<Representation> analyzer;
		std::vector<ReachTreeNode<Representation>> roots{};

		ConcreteBaseLevel( ConcreteBaseLevel const& ) = delete;
		ConcreteBaseLevel& operator=( ConcreteBaseLevel const& ) = delete;

		ConcreteBaseLevel( ConcreteBaseLevel&& ) = default;
		ConcreteBaseLevel& operator=( ConcreteBaseLevel&& ) = default;
	};

	struct RefinementLevel {
		std::variant<ConcreteRefinementLevel<Representations>...> variant;

		std::pair<REACHABILITY_RESULT, TreeNodePtr> run() {
			return std::visit( []( auto& level ) -> std::pair<REACHABILITY_RESULT, TreeNodePtr> {
				return level.analyzer.run();
			},
							   variant );
		}
	};
	struct BaseLevel {
		std::variant<ConcreteBaseLevel<Representations>...> variant;

		std::pair<REACHABILITY_RESULT, TreeNodePtr> run() {
			return std::visit( []( auto& level ) -> std::pair<REACHABILITY_RESULT, TreeNodePtr> {
				return level.analyzer.run();
			},
							   variant );
		}
	};

	struct CreateBaseLevel;
	struct CreateRefinementLevel;

	static BaseLevel createBaseLevel( HybridAutomaton<Number> const& automaton, Settings const& setting );
	RefinementLevel& createRefinementLevel( size_t index );
	template <class LevelFrom, class LevelTo>
	void transferNodes( LevelFrom& from, TreeNodePtr& nodePtrFrom, LevelTo& to );

  public:
	CEGARAnalyzer() = delete;

	/**
	 * @brief Construct a new CEGARAnalyzer object.
	 * @param ha The hybrid automaton to analyze
	 * @param setting The settings to use
	 */
	CEGARAnalyzer( const HybridAutomaton<Number>& ha, const Settings& settings )
		: mHybridAutomaton( ha )
		, mSettings( settings )
		, mBaseLevel( createBaseLevel( ha, settings ) ) {
	}

	REACHABILITY_RESULT run();

	using TreePtrVariant = std::variant<std::vector<ReachTreeNode<Representations>>*...>;

	TreePtrVariant getTree( size_t levelIndex ) {
		if ( levelIndex == 0 ) {
			return std::visit( []( auto& baseLevel ) -> TreePtrVariant { return &baseLevel.roots; }, mBaseLevel.variant );
		} else {
			return std::visit( []( auto& refinementLevel ) -> TreePtrVariant { return &refinementLevel.roots; }, mLevels[levelIndex - 1].variant );
		}
	}

	auto getTrees() {
		return boost::adaptors::transform( boost::counting_range( 0ul, mLevels.size() + 1 ), [&]( size_t ind ) { return getTree( ind ); } );
	}

	void plot() {
		// call to plotting.
		START_BENCHMARK_OPERATION( Plotting );

		std::size_t amount = 0;
		for ( auto roots : getTrees() ) {
			std::visit( [&]( auto* r ) {
				for ( const auto& node : preorder( *r ) ) {
					amount += node.getFlowpipe().size();
				}
			},
						roots );
		}

		auto& plt = Plotter<Number>::getInstance();
		for ( std::size_t pic = 0; pic < mSettings.plotDimensions.size(); ++pic ) {
			std::cout << "Prepare plot " << pic + 1 << "/" << mSettings.plotDimensions.size() << "." << std::endl;
			plt.setFilename( mSettings.plotFileNames[pic] );
			std::size_t segmentCount = 0;
			for ( auto roots : getTrees() ) {
				std::visit( [&]( auto* r ) {
					for ( const auto& node : preorder( *r ) ) {
						for ( const auto& segment : node.getFlowpipe() ) {
							std::cout << "\r" << segmentCount++ << "/" << amount << "..." << std::flush;
							plt.addObject( segment.project( mSettings.plotDimensions[pic] ).vertices() );
						}
					}
				},
							roots );
			}
			plt.plot2d( mSettings.plottingFileType );  // writes to .plt file for pdf creation
		}
		EVALUATE_BENCHMARK_RESULT( Plotting );
	}

  protected:
	HybridAutomaton<Number> mHybridAutomaton;
	Settings mSettings{};
	BaseLevel mBaseLevel;
	std::vector<RefinementLevel> mLevels{};
};

template <class Number>
using CEGARAnalyzerDefault = apply<CEGARAnalyzer, concat<TypeList<Number>, RepresentationsList<Number, Converter<Number>>>>;

}  // namespace hypro

#include "CEGARAnalyzer.tpp"
