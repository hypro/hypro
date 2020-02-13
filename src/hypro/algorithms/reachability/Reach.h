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
#include "FirstSegment.h"
#include "config.h"
#include "datastructures/HybridAutomaton/HybridAutomaton.h"
#include "datastructures/HybridAutomaton/State.h"
#include "datastructures/reachability/ReachTree.h"
#include "datastructures/reachability/Settings.h"
#include "datastructures/reachability/workQueue/WorkQueue.h"
#include "representations/Ellipsoids/Ellipsoid.h"
#include "representations/GeometricObject.h"
#include "util/plotting/Plotter.h"

// Debug Flag, TODO: Add more debug levels.
#define REACH_DEBUG
#define USE_REDUCTION
//#define USE_SYSTEM_SEPARATION
// Needs system separation to affect the computation
//#define USE_ELLIPSOIDS

#define USE_SMART_AGGREGATION
#define ALWAYS_USE_AGGREGATION
//#define USE_FORCE_REDUCTION

namespace hypro {
/**
 * \namespace reachability
 * \brief Namespace for all reachabiltiy analysis algorithm related code.
 */
namespace reachability {

#include "util.h"

struct ReachSettings {
	static constexpr bool printStatus = true;
};

struct ReachQuiet : public ReachSettings {
	static constexpr bool printStatus = false;
};

/**
 * @brief      Class implementing a basic reachbility analysis algorithm for linear hybrid automata.
 *
 * @tparam     Number          The used number type.
 * @tparam     Representation  The used state set representation type.
 */
template <typename Number, typename ReacherSettings, typename State>
class Reach {
  public:
	using TaskType = std::pair<unsigned, State>;
	using TaskTypePtr = std::unique_ptr<TaskType>;
	using flowpipe_t = std::vector<State>;

  private:
	HybridAutomaton<Number> mAutomaton;
	ReachabilitySettings mSettings;
	std::size_t mCurrentLevel = 0;
	Number mBloatingFactor = 0;
	std::map<unsigned, std::vector<flowpipe_t>> mReachableStates;
	WorkQueue<TaskTypePtr> mWorkingQueue;
	Plotter<Number>& plotter = Plotter<Number>::getInstance();
	representation_name mType;
	bool mInitialStatesSet = false;
	ReachTree<State> mReachabilityTree;

	mutable bool mIntersectedBadStates;

  public:
	/**
	 * @brief Constructor for a basic reachability analysis algorithm for linear hybrid automata.
	 *
	 * @param _automaton The analyzed automaton.
	 * @param _settings The reachability analysis settings.
	 */
	Reach( const HybridAutomaton<Number>& _automaton, const ReachabilitySettings& _settings = ReachabilitySettings() );

	/**
	 * @brief Computes the forward reachability of the given automaton.
	 * @details
	 * @return The flowpipe as a result of this computation.
	 */
	std::vector<std::pair<unsigned, flowpipe_t>> computeForwardReachability();

	void setInitialStates( std::vector<State>&& initialStates );
	void addInitialState( State&& initialState );

	WorkQueue<TaskTypePtr>& rGetQueue() { return mWorkingQueue; }

	/**
	 * @brief Computes the forward time closure (FTC) of the given valuation in the respective location.
	 * @details [long description]
	 *
	 * @param _loc The location in which the FTC is to be computed.
	 * @param _val The valuation which is initial in the respective location.
	 *
	 * @return The id of the computed flowpipe.
	 */
	flowpipe_t computeForwardTimeClosure( const State& _state );

	/**
	 * @brief Returns whether the bad states were reachable so far.
	 * @details [long description]
	 * @return true, if the bad states were reachable.
	 */
	bool reachedBadStates() const { return mIntersectedBadStates; }

	/**
	 * @brief Computes one time step and one discrete step, i.e. increases the depth of the search by one.
	 * @details [long description]
	 *
	 * @param _init The initial valuations.
	 * @return The resulting flowpipes.
	 */
	void processDiscreteBehaviour( const std::vector<std::tuple<Transition<Number>*, State>>& _newInitialSets );

	/**
	 * @brief Checks, whether the passed transition is enabled by the passed valuation. Sets the result to be the intersection of the guard and the valuation.
	 * @details [long description]
	 *
	 * @param _trans The transition, which is to be enabled.
	 * @param _val The valuation possibly enabling the passed transition.
	 * @param result At the end of the method this holds the result of the intersection of the guard and the valuation.
	 * @return True, if the transition is enabled, false otherwise.
	 */
	bool intersectGuard( Transition<Number>* _trans, const State& _segment, State& result ) const;

	bool checkTransitions( const State& _state, const carl::Interval<tNumber>& currentTime, std::vector<std::tuple<Transition<Number>*, State>>& nextInitialSets ) const;

	const ReachabilitySettings& settings() const { return mSettings; }
	void setSettings( const ReachabilitySettings& settings ) { mSettings = settings; }

	representation_name getRepresentationType() const { return mType; }
	void setRepresentationType( const representation_name& type ) { mType = type; }

	const ReachTree<State>& getReachabilityTree() const;

  private:
	matrix_t<Number> computeTrafoMatrix( const Location<Number>* _loc ) const;
	//std::tuple<bool, State, matrix_t<Number>, vector_t<Number>> computeFirstSegment( const State& _state ) const;
	bool intersectBadStates( const State& _state ) const;
};

}  // namespace reachability
}  // namespace hypro

#include "Reach.tpp"
#include "discreteHandling.tpp"
#include "terminationHandling.tpp"
