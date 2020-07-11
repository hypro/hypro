#pragma once
#include "../../../datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../../../datastructures/reachability/ReachTreev2.h"
#include "../../../datastructures/reachability/Strategy.h"
#include "../../../types.h"
#include "./impl/RefinementAnalyzer.h"
#include "algorithms/reachability/analyzer/LTIAnalyzer.h"
#include "util/plotting/Plotter.h"
#include "util/type_handling/dispatch.h"

#include <functional>
#include <queue>
#include <variant>

namespace hypro {

template <class Number>
class CEGARAnalyzer {
	template <class... Representations>
	using TreeNodePtrVariant = std::variant<ReachTreeNode<Representations>*...>;

	using TreeNodePtr = apply<TreeNodePtrVariant, RepresentationsList<Number, Converter<Number>>>;

	template <class Representation>
	struct ConcreteRefinementLevel {
		RefinementAnalyzer<Representation> analyzer;
		ReachTreeNode<Representation> root{};
	};

	template <class... Representations>
	struct RefinementLevelVariant {
		std::variant<ConcreteRefinementLevel<Representations>...> variant;

		std::pair<REACHABILITY_RESULT, TreeNodePtr> run() {
			return std::visit( []( auto& level ) -> std::pair<REACHABILITY_RESULT, TreeNodePtr> {
				return level.analyzer.run();
			},
							   variant );
		}
	};

	template <class Representation>
	struct ConcreteBaseLevel {
		LTIAnalyzer<Representation> analyzer;
		std::vector<ReachTreeNode<Representation>> roots{};
	};

	template <class... Representations>
	struct BaseLevelVariant {
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

	using RefinementLevel = apply<RefinementLevelVariant, RepresentationsList<Number, Converter<Number>>>;
	using BaseLevel = apply<BaseLevelVariant, RepresentationsList<Number, Converter<Number>>>;

	BaseLevel createBaseLevel();
	RefinementLevel& createRefinementLevel( size_t index, Path<Number> path, Location<Number> const* loc );

  public:
	CEGARAnalyzer() = delete;

	/**
	 * @brief Construct a new CEGARAnalyzer object.
	 * @param ha The hybrid automaton to analyze
	 * @param setting The settings to use
	 */
	CEGARAnalyzer( const HybridAutomaton<Number>& ha, const Settings& settings )
		: mHybridAutomaton( ha )
		, mSettings( settings ) {
	}

	REACHABILITY_RESULT run();

	void plot() {
		// call to plotting.
		START_BENCHMARK_OPERATION( Plotting );

		std::size_t amount = 0;
		for ( auto& level : mLevels ) {
			std::visit( [&]( auto& concLevel ) {
				for ( const auto& node : preorder( concLevel.root ) ) {
					amount += node.getFlowpipe().size();
				}
			},
						level.variant );
		}

		auto& plt = Plotter<Number>::getInstance();
		for ( std::size_t pic = 0; pic < mSettings.plotDimensions.size(); ++pic ) {
			std::cout << "Prepare plot " << pic + 1 << "/" << mSettings.plotDimensions.size() << "." << std::endl;
			plt.setFilename( mSettings.plotFileNames[pic] );
			std::size_t segmentCount = 0;
			for ( auto& level : mLevels ) {
				std::visit( [&]( auto& concLevel ) {
					for ( const auto& node : preorder( concLevel.root ) ) {
						for ( const auto& segment : node.getFlowpipe() ) {
							std::cout << "\r" << segmentCount++ << "/" << amount << "..." << std::flush;
							plt.addObject( segment.project( mSettings.plotDimensions[pic] ).vertices() );
						}
					}
				},
							level.variant );
			}
			plt.plot2d( mSettings.plottingFileType );  // writes to .plt file for pdf creation
		}
		EVALUATE_BENCHMARK_RESULT( Plotting );
	}

  protected:
	HybridAutomaton<Number> mHybridAutomaton;
	std::vector<RefinementLevel> mLevels{};
	Settings mSettings{};
};

}  // namespace hypro

#include "CEGARAnalyzer.tpp"
