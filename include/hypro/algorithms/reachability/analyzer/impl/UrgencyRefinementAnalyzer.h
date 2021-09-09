#pragma once
#include "../../../../datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../../../../datastructures/reachability/ReachTreev2.h"
#include "../../../../types.h"
#include "../../workers/UrgencyCEGARWorker.h"
#include "../ReturnTypes.h"

#include <deque>

namespace hypro {
namespace detail {

/**
 * @brief Get the initial refinement level for a transition. This is the minimal level unless the jump
 * enabling set is a halfspace, true or false and the refineHalfspaces flag is set.
 */
template <typename Number>
UrgencyRefinementLevel getInitialRefinementLevel( const Transition<Number>* transition, UrgencyCEGARSettings refinementSettings );

/**
 * @brief Get the next highest refinement level that is enabled in the settings.
 * @param level A Refinement level.
 * @param refinementSettings The settings which contain the enabled refinement levels.
 * @return The least refinement level that is larger than level and enabled in the settings.
 */
UrgencyRefinementLevel getNextRefinementLevel( const UrgencyRefinementLevel& level, const UrgencyCEGARSettings& refinementSettings );

/**
 * @brief Get the minimal refinement level that is enabled in the settings.
 * @param refinementSettings The settings which contain the enabled refinement levels.
 * @return The minimal enabled level.
 */
UrgencyRefinementLevel getMinRefinementLevel( const UrgencyCEGARSettings& refinementSettings );
/**
 * @brief Get the maximal refinement level that is enabled in the settings.
 * @param refinementSettings The settings which contain the enabled refinement levels.
 * @return The maximal enabled level.
 */
UrgencyRefinementLevel getMaxRefinementLevel( const UrgencyCEGARSettings& refinementSettings );

}  // namespace detail

/**
 * @brief Structure to indicate that refinement was successful and return the path successors.
 */
template <class Representation>
struct UrgencyRefinementSuccess {
	std::vector<ReachTreeNode<Representation>*> pathSuccessors{};
};
template <class Representation>
UrgencyRefinementSuccess( std::vector<ReachTreeNode<Representation>*> ) -> UrgencyRefinementSuccess<Representation>;

/**
 * @brief Internal analyzer for refinement of urgent transitions.
 * Given an initial unsafe node, the analyzer attempts to refine urgent transitions on the path
 * and verify safety on the refined path. If additional unsafe nodes are encountered, more transitions are refined
 * iteratively. If no more nodes can be refined and there are still non-refuted counterexample nodes, the
 * analyzer indicates that refinement was unsuccessful. If refinement was successful, the successors of the path
 * are returned, which can be pushed onto the queue of the analyzer that initiated refinement.
 * @tparam Representation The used state set representation.
 */
template <typename Representation>
class UrgencyRefinementAnalyzer {
  public:
	using Number = typename Representation::NumberType;
	using RefinementResult = AnalysisResult<UrgencyRefinementSuccess<Representation>, Failure<Representation>>;
	/**
	 * @brief Structure to hold a refinement candidate, consisting of a node on the unsafe path,
	 * an urgent transition for refinement and a level to refine the transition to.
	 */
	struct RefinePoint {
		ReachTreeNode<Representation>* node = nullptr;
		Transition<Number>* transition = nullptr;
		UrgencyRefinementLevel level = UrgencyRefinementLevel::SETDIFF;
	};

	UrgencyRefinementAnalyzer( HybridAutomaton<Number> const* ha,
							   FixedAnalysisParameters const& fixedParameters,
							   AnalysisParameters const& parameters,
							   UrgencyCEGARSettings const& refinementSettings,
							   std::list<ReachTreeNode<Representation>>& roots )
		: mHybridAutomaton( ha )
		, mFixedParameters( fixedParameters )
		, mParameters( parameters )
		, mRefinementSettings( refinementSettings )
		, mRoots( &roots ) {}

	/**
     * @brief Set the initial unsafe node and initialize the path.
     * @param failureNode The unsafe node that was encountered during analysis.
     */
	void setRefinement( ReachTreeNode<Representation>* failureNode ) {
		assert( mWorkQueue.empty() );
		mFailureNode = failureNode;
		mPath = failureNode->getPath();
	}

	/**
	 * @brief The main method to start refinement.
	 * @return Indicate either success and return the path successors or indicate failure
	 * and return the counterexample node that cannot be refuted.
	 */
	RefinementResult run();

  private:
	/**
   * @brief Given a transition and the discrete jump successors, generate the children nodes.
   */
	struct ChildNodeGen;
	/**
	 * @brief Check whether the jump time to a node matches the timing of the path to the initial unsafe node.
	 * @param node A node which may be on the unsafe path.
	 */
	bool matchesPathTiming( ReachTreeNode<Representation>* node );
	/**
	 * @brief Check whether the discrete transition to a node matches the timing of the path to the initial unsafe node.
	 * @param node A node which may be on the unsafe path.
	 */
	bool matchesPathTransition( ReachTreeNode<Representation>* node );

	/**
     * @brief Finds a node, transition and refinement level for the given unsafe node.
     * @param unsafeNode Node with reachable bad states.
     * @return A refine point containing a node on the path to the unsafe node, an outgoing urgent transition
     * and a refinement level.
     */
	auto findRefinementNode( ReachTreeNode<Representation>* unsafeNode )
		  -> RefinePoint;

	/**
     * @brief Checks if the refined node already exists as sibling of the unrefined node and creates it otherwise.
     * @detail If the unrefined node is a root (parent is nullptr), a new refined root is created and pushed to mRoots.
     * @param refine Pair of node and transition to refine.
     * @return The node with the new urgent transitions. The node is a sibling of the unrefined node and
     * the flowpipe may or may not already be computed.
     */
	auto refineNode( const RefinePoint& refine )
		  -> ReachTreeNode<Representation>*;

	/**
	 * @brief Check whether refinement of a candidate can be helpful for refuting an unsafe node.
	 * @detail Compute the intersection of the jump enabling set with the flowpipe of the candidate node
	 * and check safety on the path from the candidate to the unsafe node. If the result is unsafe, the candidate
	 * is suitable for refinement.
	 * @param candidate The refinement candidate with a node on the path to unsafe node.
	 * @param unsafeNode A node with reachable bad states.
	 * @return true if refinement can be helpful and false otherwise.
	 */
	bool suitableForRefinement( const RefinePoint& candidate, ReachTreeNode<Representation>* unsafeNode );

	/**
	 * @brief Compute a path from an initial node and check safety. This is to determine whether a candidate is suitable
	 * for refinement. Only nodes that lie on the path are generated during verification.
	 * @param initialNode The starting node containing the initial set.
	 * @param path The path to compute.
	 * @param initialTimeHorizon A time horizon that is used only to limit the first time elapse.
	 * @return true if the path is unsafe and false otherwise.
	 */
	bool pathUnsafe( ReachTreeNode<Representation>* initialNode, Path<Number> path, std::size_t initialTimeHorizon );

	/**
	 * @brief Evaluate the given heuristic for a transition and a node.
	 * @detail Heuristics are used to estimate how useful refinement of a candidate may be.
	 * @param t The transition that is a candidate for refinement.
	 * @param node The candidate node.
	 * @return A value dependent on the heuristic given in the settings. Can be used to compare transitions.
	 */
	std::size_t computeHeuristic( Transition<Number>* t, ReachTreeNode<Representation>* node );

	/**
	 * @brief Called after a transition has been chosen for refinement. Dependent on the heuristic,
	 * the function may clear the cache or increase a counter for the given transition.
	 * @param The transition that was chosen for refinement.
	 */
	void updateHeuristics( Transition<Number>* t );

  protected:
	std::deque<ReachTreeNode<Representation>*> mWorkQueue;	///< Queue for nodes in the tree which require processing
	HybridAutomaton<Number> const* mHybridAutomaton;		///< Hybrid automaton
	FixedAnalysisParameters mFixedParameters;				///< Analysis parameters
	AnalysisParameters mParameters;							///< Used analysis settings
	UrgencyCEGARSettings mRefinementSettings;				///< Settings that contain information about refinement levels
	Path<Number> mPath{};									///< Path to the initial unsafe node
	ReachTreeNode<Representation>* mFailureNode;			///< The initial failure node
	std::list<ReachTreeNode<Representation>>* mRoots;		///< The roots of the reach tree
	size_t const mMaxSegments = size_t( std::ceil( std::nextafter( carl::convert<tNumber, double>( mFixedParameters.localTimeHorizon / mParameters.timeStep ), std::numeric_limits<double>::max() ) ) );
	std::map<Transition<Number>*, std::size_t> mRefinementCache;  ///< Cache for heuristic values
	Transition<Number>* mLastRefine;
};

}  // namespace hypro

#include "UrgencyRefinementAnalyzer.tpp"
