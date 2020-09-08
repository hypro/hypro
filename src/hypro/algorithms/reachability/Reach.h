/**
 * Reach holds a basic forward reachability analysis algorithm for linear hybrid automata.
 * @file Reach.h
 *
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @author Christopher Kugler
 * @author Phillip Florian
 *
 * @since	2014-04-30
 * @version	2016-06-20
 */

#pragma once
#include "analyzer/LTIAnalyzer.h"
#include "analyzer/ReturnTypes.h"
#include "datastructures/reachability/ReachTreev2.h"

namespace hypro {
/**
 * \namespace reachability
 * \brief Namespace for all reachabiltiy analysis algorithm related code.
 */

namespace reachability {

/**
 * @brief      Class implementing a basic reachbility analysis algorithm for linear hybrid automata.
 *
 * @tparam     Number          The used number type.
 * @tparam     Representation  The used state set representation type.
 */
template <typename Representation, class Analyzer = LTIAnalyzer<Representation>>
class Reach {
  public:
	using NodePtr = ReachTreeNode<Representation>*;
	using VerificationResult = AnalysisResult<VerificationSuccess, Failure<Representation>>;

  protected:
	bool mInitialStatesSet = false;
	Analyzer mAnalyzer;
	std::vector<ReachTreeNode<Representation>> mReachabilityTree;

  public:
	/**
	 * @brief Constructor for a basic reachability analysis algorithm for linear hybrid automata.
	 *
	 * @param _automaton The analyzed automaton.
	 * @param _settings The reachability analysis settings.
	 */
	Reach( const HybridAutomaton<typename Representation::NumberType>& automaton, const FixedAnalysisParameters& fixedParameters, const AnalysisParameters& parameters, std::vector<ReachTreeNode<Representation>>& roots )
		: mInitialStatesSet( !roots.empty() )
		, mAnalyzer( automaton, fixedParameters, parameters, roots )
		, mReachabilityTree() {}

	/**
	 * @brief Computes the forward reachability of the given automaton.
	 * @details
	 * @return The flowpipe as a result of this computation.
	 */
	REACHABILITY_RESULT computeForwardReachability() {
		return mAnalyzer.run().result();
	}
};

}  // namespace reachability
}  // namespace hypro

// #include "Reach.tpp"
// #include "discreteHandling.tpp"
// #include "terminationHandling.tpp"
