/**
 * Reach holds a basic forward reachability analysis algorithm for linear hybrid automata.
 * @file Reach.h
 *
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @author Christopher Kugler
 *
 * @since	2014-04-30
 * @version	2015-10-15
 */

#pragma once
#include "util.h"
#include "Settings.h"
#include "../../config.h"
#include "../../datastructures/hybridAutomata/HybridAutomaton.h"
#include "../../util/Plotter.h"
#include "boost/tuple/tuple.hpp"

CLANG_WARNING_DISABLE("-Wdeprecated-register")
#include <eigen3/unsupported/Eigen/src/MatrixFunctions/MatrixExponential.h>
CLANG_WARNING_RESET

// Debug Flag, TODO: Add more debug levels.
#define REACH_DEBUG
//#define USE_REDUCTION

namespace hypro {
namespace reachability {

template <typename Representation>
using flowpipe_t = std::vector<Representation>;

template<typename Number, typename Representation>
using initialSet = boost::tuple<unsigned, Location<Number>*, Representation>;

template <typename Number, typename Representation>
class Reach {
private:
	HybridAutomaton<Number> mAutomaton;
	ReachabilitySettings<Number> mSettings;
	std::size_t mCurrentLevel;

	std::map<Location<Number>*, std::vector<flowpipe_t<Representation>>> mReachableStates;
	std::queue<initialSet<Number,Representation>> mWorkingQueue;

public:
	/**
	 * @brief Constructor for a basic reachability analysis algorithm for linear hybrid automata.
	 *
	 * @param _automaton The analyzed automaton.
	 * @param _settings The reachability analysis settings.
	 */
	Reach( const HybridAutomaton<Number>& _automaton, const ReachabilitySettings<Number>& _settings = ReachabilitySettings<Number>());

	/**
	 * @brief Computes the forward reachability of the given automaton.
	 * @details
	 * @return The flowpipe as a result of this computation.
	 */
	std::vector<flowpipe_t<Representation>> computeForwardReachability();

	/**
	 * @brief Computes the forward time closure (FTC) of the given valuation in the respective location.
	 * @details [long description]
	 *
	 * @param _loc The location in which the FTC is to be computed.
	 * @param _val The valuation which is initial in the respective location.
	 *
	 * @return The id of the computed flowpipe.
	 */
	flowpipe_t<Representation> computeForwardTimeClosure( hypro::Location<Number>* _loc, const Representation& _val );

	/**
	 * @brief Computes one time step and one discrete step, i.e. increases the depth of the search by one.
	 * @details [long description]
	 *
	 * @param _init The initial valuations.
	 * @return The resulting flowpipes.
	 */
	void processDiscreteBehaviour( const std::vector<boost::tuple<Transition<Number>*, Representation>>& _newInitialSets );

	/**
	 * @brief Checks, whether the passed transition is enabled by the passed valuation. Sets the result to be the intersection of the guard and the valuation.
	 * @details [long description]
	 *
	 * @param _trans The transition, which is to be enabled.
	 * @param _val The valuation possibly enabling the passed transition.
	 * @param result At the end of the method this holds the result of the intersection of the guard and the valuation.
	 * @return True, if the transition is enabled, false otherwise.
	 */
	bool intersectGuard( hypro::Transition<Number>* _trans, const Representation& _segment, Representation& result );

	/**
	 * @brief Printing method for a flowpipe. Prints every segment.
	 *
	 * @param _flowpipe The flowpipe to be printed.
	 */
	void printFlowpipe( const flowpipe_t<Representation>& _flowpipe ) const;

	/**
	 * @brief Printing method for a flowpipe. Prints only the first and the last segment.
	 *
	 * @param _flowpipe The flowpipe to be printed.
	 */
	void printFlowpipeReduced( const flowpipe_t<Representation>& _flowpipe ) const;
private:

	matrix_t<Number> computeTrafoMatrix( hypro::Location<Number>* _loc ) const;
	boost::tuple<bool, Representation, matrix_t<Number>, vector_t<Number>> computeFirstSegment( hypro::Location<Number>* _loc, const Representation& _val ) const;
	bool intersectBadStates( const Representation& _segment ) const;
};

}  // namespace reachability
}  // namespace hypro

#include "Reach.tpp"
