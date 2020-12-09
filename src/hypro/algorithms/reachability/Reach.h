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
#include "../../datastructures/reachability/ReachTreev2.h"
#include "analyzer/LTIAnalyzer.h"
#include "analyzer/ReturnTypes.h"
#include "analyzer/SingularAnalyzer.h"

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
template <typename Representation>
class Reach {
  public:
	using VerificationResult = AnalysisResult<VerificationSuccess, Failure<Representation>>;

  protected:
	LTIAnalyzer<Representation> mAnalyzer;

  public:
	/**
	 * @brief Constructor for a basic reachability analysis algorithm for linear hybrid automata.
	 *
	 * @param _automaton The analyzed automaton.
	 * @param _settings The reachability analysis settings.
	 */
	Reach( const HybridAutomaton<typename Representation::NumberType>& automaton, const FixedAnalysisParameters& fixedParameters, const AnalysisParameters& parameters, std::vector<ReachTreeNode<Representation>>& roots )
		: mAnalyzer( automaton, fixedParameters, parameters, roots ) {}

	/**
	 * @brief Computes the forward reachability of the given automaton.
	 * @details
	 * @return The flowpipe as a result of this computation.
	 */
	REACHABILITY_RESULT computeForwardReachability() {
		return mAnalyzer.run().result();
	}
};

template <typename Representation>
class ReachSingular {
  public:
	using VerificationResult = AnalysisResult<VerificationSuccess, Failure<Representation>>;

  protected:
	SingularAnalyzer<Representation> mAnalyzer;

  public:
	/**
	 * @brief Constructor for a basic reachability analysis algorithm for linear hybrid automata.
	 *
	 * @param _automaton The analyzed automaton.
	 * @param _settings The reachability analysis settings.
	 */
	ReachSingular( const HybridAutomaton<typename Representation::NumberType>& automaton, const FixedAnalysisParameters& fixedParameters, std::vector<ReachTreeNode<Representation>>& roots )
		: mAnalyzer( automaton, fixedParameters, roots ) {}

	/**
	 * @brief Computes the forward reachability of the given automaton.
	 * @details
	 * @return The flowpipe as a result of this computation.
	 */
	REACHABILITY_RESULT computeForwardReachability() {
		return mAnalyzer.run().result();
	}
};

template <class Representation, template<class T> class Method>
class ReachBase {
  public:
	using VerificationResult = AnalysisResult<VerificationSuccess, Failure<Representation>>;

  protected:
	Method<Representation> mAnalyzer; ///< Analyzer instance

  public:
	/**
	 * @brief Constructor for a basic reachability analysis method.
	 *
	 * @param _automaton The analyzed automaton.
	 * @param _settings The reachability analysis settings.
	 */
	ReachBase( const HybridAutomaton<typename Representation::NumberType>& automaton, const FixedAnalysisParameters& fixedParameters, std::vector<ReachTreeNode<Representation>>& roots )
		: mAnalyzer( automaton, fixedParameters, roots ) {}

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
