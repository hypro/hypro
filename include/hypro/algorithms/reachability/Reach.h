/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

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
#include "../../datastructures/reachability/Settings.h"
#include "analyzer/LTIAnalyzer.h"
#include "analyzer/LTISetMinusAnalyzer.h"
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
template <typename Representation, typename SearchHeuristic = DepthFirst<Representation>, MULTITHREADING multithreading = MULTITHREADING::DISABLED>
class Reach {
  public:
	using VerificationResult = AnalysisResult<VerificationSuccess, Failure<Representation>>;

  protected:
	LTIAnalyzer<Representation, SearchHeuristic, multithreading> mAnalyzer;

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
class ReachUrgency {
  public:
	using VerificationResult = AnalysisResult<VerificationSuccess, Failure<Representation>>;

  protected:
	LTISetMinusAnalyzer<Representation> mAnalyzer;

  public:
	/**
	 * @brief Constructor for a basic reachability analysis algorithm for linear hybrid automata.
	 *
	 * @param _automaton The analyzed automaton.
	 * @param _settings The reachability analysis settings.
	 */
	ReachUrgency( const HybridAutomaton<typename Representation::NumberType>& automaton, const FixedAnalysisParameters& fixedParameters, const AnalysisParameters& parameters, std::vector<ReachTreeNode<Representation>>& roots )
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

template <class Representation, class Method>
class ReachBase {
  public:
	using VerificationResult = AnalysisResult<VerificationSuccess, Failure<Representation>>;  ///< return type

  protected:
	Method mAnalyzer;  ///< Analyzer instance

  public:
	/**
	 * @brief Constructor for a basic reachability analysis method.
	 *
	 * @param _automaton The analyzed automaton.
	 * @param _settings The reachability analysis settings.
	 */
	ReachBase( const HybridAutomaton<typename Representation::NumberType>& automaton, const Settings& parameters, std::vector<ReachTreeNode<Representation>>& roots )
		: mAnalyzer( automaton, parameters, roots ) {}

	/**
	 * @brief Computes the forward reachability of the given automaton.
	 * @details
	 * @return The flowpipe as a result of this computation.
	 */
	REACHABILITY_RESULT computeForwardReachability() {
		return mAnalyzer.run();
	}
};

}  // namespace reachability
}  // namespace hypro

// #include "Reach.tpp"
// #include "discreteHandling.tpp"
// #include "terminationHandling.tpp"
