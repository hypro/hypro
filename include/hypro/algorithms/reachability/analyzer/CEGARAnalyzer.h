#ifndef CEGARANALYZER_H
#define CEGARANALYZER_H

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

namespace detail {

/**
 * @brief impl that takes a TypeList, can be aliased to take conventional type pack
 * @tparam T the type list
 */
template <class T>
class CEGARAnalyzer_impl;

/**
 * specialization to unpack the TypeList
 */
template <class Number, class Automaton, class... Representations>
class CEGARAnalyzer_impl<TypeList<Number, Automaton, Representations...>> {
	using LocationType = typename Automaton::LocationType;
	using TreeNodePtrVariant = std::variant<ReachTreeNode<Representations, LocationType>*...>;

	template <class Representation, class Aut>
	struct ConcreteRootsHolder {
		std::vector<ReachTreeNode<Representation, typename Aut::LocationType>> roots{};

		ConcreteRootsHolder( ConcreteRootsHolder const& ) = delete;
		ConcreteRootsHolder& operator=( ConcreteRootsHolder const& ) = delete;

		ConcreteRootsHolder( ConcreteRootsHolder&& ) = default;
		ConcreteRootsHolder& operator=( ConcreteRootsHolder&& ) = default;
	};

	template <class Representation, class Aut>
	struct ConcreteRefinementLevel : public ConcreteRootsHolder<Representation, Aut> {
		RefinementAnalyzer<Representation, Aut> analyzer;
		using ConcreteRootsHolder<Representation, Aut>::roots;
		using LocationType = typename Aut::LocationType;

		ReachTreeNode<Representation, LocationType>& addOrGetRoot( Aut const& automaton, LocationType const* loc ) {
			auto rootIt = std::find_if( roots.begin(), roots.end(), [&]( auto& root ) { return root.getLocation() == loc; } );
			if ( rootIt == roots.end() ) {
				auto const& condition = automaton.getInitialStates().at( loc );
				return roots.emplace_back( loc, Representation{ condition.getMatrix(), condition.getVector() }, carl::Interval{ 0, 0 } );
			}
			return *rootIt;
		}
	};

	template <class Representation, class Aut>
	struct ConcreteBaseLevel : public ConcreteRootsHolder<Representation, Aut> {
		LTIAnalyzer<Representation, Aut> analyzer;
	};

	struct RefinementLevel {
		std::variant<ConcreteRefinementLevel<Representations, Automaton>...> variant;
	};

	struct BaseLevel {
		std::variant<ConcreteBaseLevel<Representations, Automaton>...> variant;
	};

	struct CreateBaseLevel;
	struct CreateRefinementLevel;

	static BaseLevel createBaseLevel( Automaton const& automaton, Settings const& setting );
	RefinementLevel& createRefinementLevel( size_t index );
	template <class SourceRep, class TargetLevel>
	void transferNodes( std::vector<ReachTreeNode<SourceRep, LocationType>*>& sourceNodes,
						std::variant<Failure<Representations, LocationType>...> targetFailure,
						TargetLevel& targetLevel );

	template <class Representation>
	void handleFailure( ReachTreeNode<Representation, LocationType>* conflictNode, size_t targetIndex );

  public:
	CEGARAnalyzer_impl() = delete;

	/**
	 * @brief Construct a new CEGARAnalyzer_impl object.
	 * @param ha The hybrid automaton to analyze
	 * @param setting The settings to use
	 */
	CEGARAnalyzer_impl( const Automaton& ha, const Settings& settings )
		: mHybridAutomaton( ha )
		, mSettings( settings )
		, mBaseLevel( createBaseLevel( mHybridAutomaton, settings ) ) {}  // have to use mHybridAutomaton rather than ha, because mHybridAutomaton is a copy,
																		  // thus location and transition pointers are different between them.

	REACHABILITY_RESULT run();

	using TreePtrVariant = std::variant<ConcreteRootsHolder<Representations, Automaton>*...>;

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
	Automaton mHybridAutomaton;
	Settings mSettings;
	BaseLevel mBaseLevel;
	std::vector<RefinementLevel> mLevels{};
};

template <class Number, class Automaton, class... Representations>
using CEGARAnalyzer_apply = CEGARAnalyzer_impl<TypeList<Number, Automaton, Representations...>>;
}  // namespace detail

// extern template class detail::CEGARAnalyzer_impl<concat<TypeList<double>, RepresentationsList<double, Converter<double>>>>;
// extern template class detail::CEGARAnalyzer_impl<concat<TypeList<mpq_class>, RepresentationsList<mpq_class, Converter<mpq_class>>>>;

template <class Number, class Automaton>
using CEGARAnalyzer = detail::CEGARAnalyzer_impl<concat<TypeList<Number>, TypeList<Automaton>, RepresentationsList<Number, Converter<Number>>>>;

}  // namespace hypro

#include "CEGARAnalyzer.tpp"

#endif
