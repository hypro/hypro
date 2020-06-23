#pragma once
#include "../../../datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../../../datastructures/reachability/ReachTreev2.h"
#include "../../../datastructures/reachability/Strategy.h"
#include "../../../types.h"
#include "../workers/LTIWorker.h"
#include "./impl/RefinementAnalyzer.h"

#include <queue>
#include <variant>

namespace hypro {

template <class Number>
class CEGARAnalyzer {
  public:
	CEGARAnalyzer() = delete;

	/**
	 * @brief Construct a new LTIAnalyzer object with a single entry strategy
	 *
	 * @param ha
	 * @param setting The single entry of the strategy
	 */
	CEGARAnalyzer( const HybridAutomaton<Number>& ha, const Settings& setting )
		: mHybridAutomaton( ha )
		, mStrategy( Strategy{ { setting } } ) {
	}

	CEGARAnalyzer( const HybridAutomaton<Number>& ha, const Strategy& strategy )
		: mHybridAutomaton( ha )
		, mStrategy( strategy ) {
	}

	REACHABILITY_RESULT run();

  protected:
	template <class... Representations>
	using VariantT = std::variant<RefinementAnalyzer<Representations>...>;
	using Variant = apply<VariantT, RepresentationsList<Number, Converter<Number>>>;

	//std::queue<ReachTreeNode<State>*> mWorkQueue{};
	HybridAutomaton<Number> mHybridAutomaton;
	std::vector<Variant> mAnalyzers{};
	Strategy mStrategy{};
	TimeTransformationCache<Number> mTrafoCache{};
};

}  // namespace hypro

#include "CEGARAnalyzer.tpp"
