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
#include "../../config.h"
#include "../../datastructures/hybridAutomata/HybridAutomaton.h"
#include "../../util/Plotter.h"
#include "util.h"

// Debug Flag, TODO: Add more debug levels.
//#define REACH_DEBUG
//#define USE_REDUCTION

namespace hypro {
namespace reachability {

template <typename Representation>
using flowpipe_t = vector<Representation>;

template<typename Number>
struct ReachabilitySettings {
	Number timebound = fReach_TIMEBOUND;
	std::size_t iterationDepth = fReach_ITERATIONDEPTH;
	std::size_t discretization = fReach_TIMEDISCRETIZATION;
	unsigned long pplDenomimator = fReach_DENOMINATOR;
};

template <typename Number, typename Representation>
class Reach {
private:
	HybridAutomaton<Number, Representation> mAutomaton;
	ReachabilitySettings<Number> mSettings;

	std::map<std::size_t, flowpipe_t<Representation>> mFlowpipes;
	std::map<std::size_t, Location<Number>*> mFlowToLocation;
	std::map<Location<Number>*, std::vector<std::size_t>> mReach;
	std::size_t id = 0;

public:
	/**
	 * @brief Constructor for a basic reachability analysis algorithm for linear hybrid automata.
	 *
	 * @param _automaton The analyzed automaton.
	 * @param _settings The reachability analysis settings.
	 */
	Reach( const HybridAutomaton<Number, Representation>& _automaton, const ReachabilitySettings<Number> _settings = ReachabilitySettings<Number>());

	/**
	 * @brief Adds a flowpipe to be stored. Flowpipe segments are identified by ids.
	 *
	 * @param _flowpipe The flowpipe to be stored.
	 * @return The id with which the flowpipe is identified.
	 */
	std::size_t addFlowpipe( const flowpipe_t<Representation>& _flowpipe );

	/**
	 * @brief Returns a concrete flowpipe for a given id.
	 *
	 * @param _index The id.
	 * @return The flowpipe assigned to the id.
	 */
	const flowpipe_t<Representation>& getFlowpipe( std::size_t _index ) const;

	/**
	 * @brief Computes the forward reachability of the given automaton.
	 * @details The main computation method is the Method #1.
         *          To use the Method #2, there's a FLAG that needs to be enabled!
	 * @return The flowpipe as a result of this computation.
	 */
	std::set<std::size_t> computeForwardReachability();

        /**
	 * @brief Computes the forward reachability of the given automaton with the #1 Method.
	 * @details [long description]
	 * @return The flowpipe as a result of this computation.
	 */
	std::set<std::size_t> computeForwardReachabilityWithMethod1();

        /**
	 * @brief Computes the forward reachability of the given automaton with the #2 Method.
	 * @details [long description]
	 * @return The flowpipe as a result of this computation.
	 */
	std::set<std::size_t> computeForwardReachabilityWithMethod2();

	/**
	 * @brief Computes the forward time closure (FTC) of the given valuation in the respective location.
	 * @details [long description]
	 *
	 * @param _loc The location in which the FTC is to be computed.
	 * @param _val The valuation which is initial in the respective location.
	 *
	 * @return The id of the computed flowpipe.
	 */
	std::size_t computeForwardTimeClosure( hypro::Location<Number>* _loc, const Representation& _val );

	/**
	 * @brief Computes one time step and one discrete step, i.e. increases the depth of the search by one.
	 * @details [long description]
	 *
	 * @param _init The initial valuations.
	 * @return The resulting flowpipes.
	 */
	std::set<std::size_t> computeReach( const std::set<std::size_t>& _init );

	/**
	 * @brief Checks, whether the passed transition is enabled by the passed valuation. Sets the result to be the intersection of the guard and the valuation.
	 * @details [long description]
	 *
	 * @param _trans The transition, which is to be enabled.
	 * @param _val The valuation possibly enabling the passed transition.
	 * @param result At the end of the method this holds the result of the intersection of the guard and the valuation.
	 * @return True, if the transition is enabled, false otherwise.
	 */
	bool computePostCondition( const hypro::Transition<Number>& _trans, const Representation& _val, Representation& result );

	/**
	 * @brief Printing method for a flowpipe. Prints every segment.
	 *
	 * @param _flowpipe The flowpipe to be printed.
	 */
	void printFlowpipe( std::size_t _flowpipe ) const;

	/**
	 * @brief Printing method for a flowpipe. Prints only the first and the last segment.
	 *
	 * @param _flowpipe The flowpipe to be printed.
	 */
	void printFlowpipeReduced( std::size_t _flowpipe ) const;
};

}  // namespace reachability
}  // namespace hypro

#include "Reach.tpp"
