#pragma once
#include "../../../datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../../../datastructures/reachability/ReachTreev2.h"
#include "../../../datastructures/reachability/Strategy.h"
#include "../../../types.h"
#include "../../../util/plotting/Plotter.h"
#include "../../../util/type_handling/dispatch.h"
#include "LTIAnalyzer.h"
#include "impl/RefinementAnalyzer.h"

#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/counting_range.hpp>
#include <functional>
#include <queue>
#include <variant>

namespace hypro {

template <class Number, class... Representations>
class CEGARAnalyzer {
	using TreeNodePtrVariant = std::variant<ReachTreeNode<Representations>*...>;

	template <class Representation>
	struct ConcreteRootsHolder {
		std::vector<ReachTreeNode<Representation>> roots{};

		ConcreteRootsHolder( ConcreteRootsHolder const& ) = delete;
		ConcreteRootsHolder& operator=( ConcreteRootsHolder const& ) = delete;

		ConcreteRootsHolder( ConcreteRootsHolder&& ) = default;
		ConcreteRootsHolder& operator=( ConcreteRootsHolder&& ) = default;
	};

	template <class Representation>
	struct ConcreteRefinementLevel : public ConcreteRootsHolder<Representation> {
		RefinementAnalyzer<Representation> analyzer;
		using ConcreteRootsHolder<Representation>::roots;

		ReachTreeNode<Representation>& addOrGetRoot( HybridAutomaton<Number> const& automaton, Location<Number> const* loc ) {
			auto rootIt = std::find_if( roots.begin(), roots.end(), [&]( auto& root ) { return root.getLocation() == loc; } );
			if ( rootIt == roots.end() ) {
				auto const& condition = automaton.getInitialStates().at( loc );
				return roots.emplace_back( loc, Representation{ condition.getMatrix(), condition.getVector() }, carl::Interval{ 0, 0 } );
			}
			return *rootIt;
		}
	};

	template <class Representation>
	struct ConcreteBaseLevel : public ConcreteRootsHolder<Representation> {
		LTIAnalyzer<Representation> analyzer;
	};

	struct RefinementLevel {
		std::variant<ConcreteRefinementLevel<Representations>...> variant;
	};

	struct BaseLevel {
		std::variant<ConcreteBaseLevel<Representations>...> variant;
	};

	struct CreateBaseLevel;
	struct CreateRefinementLevel;

	static BaseLevel createBaseLevel( HybridAutomaton<Number> const& automaton, Settings const& setting );
	RefinementLevel& createRefinementLevel( size_t index );
	template <class SourceRep, class TargetLevel>
	void transferNodes( std::vector<ReachTreeNode<SourceRep>*>& sourceNodes,
						std::variant<Failure<Representations>...> targetFailure,
						TargetLevel& targetLevel );

	template <class Representation>
	void handleFailure( ReachTreeNode<Representation>* conflictNode, size_t targetIndex );

	/**
	 * @brief Gets the level at index. Helps with the offset of mLevels.
	 */
	//	RefinementLevel& getRefinementLevel( size_t index ) {
	//		assert( index >= 1 );
	//		assert( index <= mLevels.size() );
	//
	//		return mLevels[index - 1];
	//	}

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
		, mBaseLevel( createBaseLevel( mHybridAutomaton, settings ) ) {}  // have to use mHybridAutomaton rather than ha, because mHybridAutomaton is a copy,
																		  // thus location and transition pointers are different between them.

	REACHABILITY_RESULT run();

	using TreePtrVariant = std::variant<ConcreteRootsHolder<Representations>*...>;

	TreePtrVariant getLevel( size_t levelIndex ) {
		if ( levelIndex == 0 ) {
			return std::visit( []( auto& baseLevel ) -> TreePtrVariant { return &baseLevel; }, mBaseLevel.variant );
		} else {
			return std::visit( []( auto& refinementLevel ) -> TreePtrVariant { return &refinementLevel; }, mLevels[levelIndex - 1].variant );
		}
	}

	auto getLevels() {
		return boost::adaptors::transform( boost::counting_range( 0ul, mLevels.size() + 1 ), [&]( size_t ind ) { return getLevel( ind ); } );
	}

  protected:
	HybridAutomaton<Number> mHybridAutomaton;
	Settings mSettings;
	BaseLevel mBaseLevel;
	std::vector<RefinementLevel> mLevels{};
};

template <class Number>
using CEGARAnalyzerDefault = apply<CEGARAnalyzer, concat<TypeList<Number>, RepresentationsList<Number, Converter<Number>>>>;

}  // namespace hypro

#include "CEGARAnalyzer.tpp"
