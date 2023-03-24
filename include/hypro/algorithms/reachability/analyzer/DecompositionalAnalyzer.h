/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once
#include <boost/iterator/function_output_iterator.hpp>
#include <hypro/algorithms/reachability/analyzer/DecompositionalUtil.h>
#include <hypro/algorithms/reachability/analyzer/ReturnTypes.h>
#include <hypro/algorithms/reachability/types.h>
#include <hypro/algorithms/reachability/workers/DiscreteWorker.h>
#include <hypro/algorithms/reachability/workers/LTIWorker.h>
#include <hypro/algorithms/reachability/workers/RectangularWorker.h>
#include <hypro/algorithms/reachability/workers/SingularWorker.h>
#include <hypro/datastructures/HybridAutomaton/HybridAutomaton.h>
#include <hypro/datastructures/reachability/Flowpipe.h>
#include <hypro/datastructures/reachability/ReachTreev2.h>
#include <hypro/types.h>
#include <queue>

namespace hypro {
namespace detail {

template <typename Representation, typename Location>
struct decompositionalQueueEntry {
	std::size_t clockIndex;
	std::vector<ReachTreeNode<Representation, Location>*> nodes;
	ReachTreeNode<Condition<typename Representation::NumberType>, Location>* dependencyNode;
};

}  // namespace detail

// indicates that the analysis succeeded, i.e. no intersection with bad states
struct DecompositionalSuccess {};

/**
 * @brief      Class implementing a reachability analysis algorithm for decomposed hybrid automata.
 * @tparam     Representation  The used state set representation type.
 */
template <typename LTIRep, typename SingularRep, typename DiscreteRep, typename RectangularRep, typename Automaton>
class DecompositionalAnalyzer {
	using Number = typename LTIRep::NumberType;
	using LocationT = typename Automaton::LocationType;
	using ComposedRep = apply<State, UniqueTypeList<Number, LTIRep, SingularRep, DiscreteRep, RectangularRep>>;
	using NodeVector = std::vector<ReachTreeNode<ComposedRep, LocationT>*>;
	using RepVector = std::vector<ComposedRep>;
	using SubspaceSets = std::map<std::size_t, ComposedRep>;

  public:
	using DecompositionalResult = AnalysisResult<DecompositionalSuccess, Failure<ComposedRep, LocationT>>;
	using WorkerVariant = std::variant<LTIWorker<LTIRep, Automaton>,
									   SingularWorker<SingularRep, Automaton>,
									   RectangularWorker<RectangularRep, Automaton>,
									   DiscreteWorker<DiscreteRep, Automaton>>;

	/**
	 * @brief       Construct a new DecompositionalAnalyzer object.
	 * @details     The given automaton is expected to be decomposed into independent subspaces
	 *              given by the decomposition argument. The initial sets are assumed to have clocks which
	 *              are used for synchronization of the subspaces.
	 *              Decomposition can be achieved with the decomposeAutomaton function and clocks can be
	 *              added to the decomposed automaton with the addClockToAutomaton function.
	 * @param       ha                  The decomposed hybrid automaton to analyze.
	 * @param       decomposition       The decomposition information corresponding to the ha.
	 * @param       clockCount          The number of clocks used for synchronization
	 * @param       fixedParameters     The fixed analysis parameters.
	 * @param       parameters          The analyzer specific parameters (for using multiple analyzers).
	 * @param       roots               The roots for the analysis tree (one root for each subspace).
	 */
	DecompositionalAnalyzer( Automaton const& ha,
							 Decomposition const& decomposition,
							 std::size_t clockCount,
							 FixedAnalysisParameters const& fixedParameters,
							 AnalysisParameters const& parameters )
		: mHybridAutomaton( &ha )
		, mDecomposition( decomposition )
		, mClockCount( clockCount )
		, mFixedParameters( fixedParameters )
		, mParameters( parameters ) {
		mRoots = makeDecompositionalRoots( ha, decomposition );

		for ( auto& subspaceRoots : mRoots ) {
			NodeVector root;
			for ( std::size_t subspace = 0; subspace < decomposition.subspaces.size(); ++subspace ) {
				root.push_back( &subspaceRoots[subspace] );
			}
			ReachTreeNode<Condition<Number>, LocationT> dependencyNode{ subspaceRoots[0].getLocation(), Condition<Number>( ConstraintSetT<Number>() ), carl::Interval<SegmentInd>{ 0, 0 } };
			auto& dep = mDependencyRoots.emplace_back( std::move( dependencyNode ) );
			mWorkQueue.push_front( detail::decompositionalQueueEntry<ComposedRep, LocationT>{ 0, root, &dep } );
		}
		// construct decomposition without discrete subspaces. This is used for composition, since discrete subspace
		// aren't relevant there
		for ( std::size_t subspace = 0; subspace < decomposition.subspaceTypes.size(); ++subspace ) {
			if ( isSegmentedSubspace( decomposition.subspaceTypes[subspace] ) ) {
				mSegmentedSubspaces.push_back( subspace );
			} else if ( decomposition.subspaceTypes[subspace] == DynamicType::discrete ) {
				mDiscreteSubspaces.push_back( subspace );
			} else {
				mSingularSubspaces.push_back( subspace );
			}
			if ( decomposition.subspaceTypes[subspace] != DynamicType::discrete ) {
				mDecompositionWithoutDiscrete.subspaceTypes.push_back( decomposition.subspaceTypes[subspace] );
				mDecompositionWithoutDiscrete.subspaces.push_back( std::vector<std::size_t>() );
				for ( auto varIndex : decomposition.subspaces[subspace] ) {
					mDecompositionWithoutDiscrete.subspaces.back().push_back( getVarIndexWithoutDiscrete( varIndex, decomposition ) );
				}
			}
		}
#ifdef HYPRO_LOGGING
		INFO( "hypro.reachability", "Singular: " << mSingularSubspaces << ", discrete: " << mDiscreteSubspaces << ", lti: " << mSegmentedSubspaces << "\n" );
		for ( std::size_t i = 0; i < mDecomposition.subspaces.size(); ++i ) {
			INFO( "hypro.reachability", "subspace " << i << ": " << mDecomposition.subspaceTypes[i] << ", " << mDecomposition.subspaces[i] << "\n" );
		}
		INFO( "hypro.reachability", "Used representations: lti: " << LTIRep::type() << ", singular: " << SingularRep::type() << ", discrete: " << DiscreteRep::type() << "\n" );
#endif
	}

	/**
	 * @brief       Perform safety analysis.
	 * @return      A result object indicating either success (safety) or failure (bad states reachable).
	 */
	DecompositionalResult run();

	std::vector<std::vector<ReachTreeNode<ComposedRep, LocationT>>>& getRoots() { return mRoots; }
	std::vector<ReachTreeNode<Condition<Number>, LocationT>>& getDepRoots() { return mDependencyRoots; }

  private:
	/**
	 * @brief       Worker-visitor to reset workers for new task.
	 * @tparam      Representation      The used state set representation type.
	 */
	struct resetWorkerVisitor {
		void operator()( SingularWorker<SingularRep, Automaton>& worker ) {
			worker.reset();
		}
		void operator()( RectangularWorker<RectangularRep, Automaton>& ) {
			// worker.reset();
		}
		void operator()( LTIWorker<LTIRep, Automaton>& ) {
			return;
		}
		void operator()( DiscreteWorker<DiscreteRep, Automaton>& ) {
			return;
		}
	};

	/**
	 * @brief       Worker-visitor to compute the time successors for the given task.
	 * @tparam      Representation      The used state set representation type.
	 * @param       task                The current task.
	 * @param       clockCount          Number of used clocks
	 * @return      The time intervals where the subspace satisfies the invariant.
	 */
	struct computeTimeSuccessorVisitor {
		ReachTreeNode<ComposedRep, LocationT>* task;
		std::size_t clockCount;	 // number of clocks
		long segmentCount = -1;	 // number of segments to compute in lti worker. if negative, use worker settings to get number of segments
		TimeInformation<Number> operator()( SingularWorker<SingularRep, Automaton>& worker ) {
			ReachTreeNode<SingularRep, LocationT> singularTask( task->getLocation(), std::visit( genericConvertAndGetVisitor<SingularRep>(), task->getInitialSet().getSet() ), task->getTimings() );
			worker.computeTimeSuccessors( singularTask, false );
			auto& flowpipe = task->getFlowpipe();
			std::transform( worker.getFlowpipe().begin(), worker.getFlowpipe().end(), std::back_inserter( flowpipe ), [=]( auto& segment ) {
				ComposedRep state{};
				state.setSet( segment );
				return state;
			} );
			// the first segment covers the entire time interval
			if ( flowpipe.size() == 0 ) {
				// invariant is initially violated
				return TimeInformation<Number>( clockCount );
			}
			assert( flowpipe.size() == 1 );
			// last variables are clocks
			return detail::getClockValues( flowpipe[0], clockCount );
		}
		TimeInformation<Number> operator()( LTIWorker<LTIRep, Automaton>& worker ) {
			auto& flowpipe = task->getFlowpipe();
			worker.computeTimeSuccessors(
				  std::visit( genericConvertAndGetVisitor<LTIRep>(), task->getInitialSet().getSet() ),
				  task->getLocation(),
				  boost::make_function_output_iterator( [&flowpipe]( LTIRep segment ) {
                    ComposedRep state;
                    state.setSet( segment );
                    flowpipe.push_back( state ); } ),
				  segmentCount,
				  false );
			// worker.computeTimeSuccessors( task->getInitialSet(), task->getLocation(), std::back_inserter( task->getFlowpipe() ), false );
			if ( task->getFlowpipe().size() == 0 ) {
				return TimeInformation<Number>( clockCount );
			}
			return detail::getClockValues( task->getFlowpipe()[0], clockCount ).unite( detail::getClockValues( task->getFlowpipe()[task->getFlowpipe().size() - 1], clockCount ) );
		}
		TimeInformation<Number> operator()( DiscreteWorker<DiscreteRep, Automaton>& worker ) {
			auto& flowpipe = task->getFlowpipe();
			worker.computeTimeSuccessors(
				  std::visit( genericConvertAndGetVisitor<DiscreteRep>(), task->getInitialSet().getSet() ),
				  task->getLocation(),
				  boost::make_function_output_iterator( [&flowpipe]( DiscreteRep segment ) {
                    ComposedRep state;
                    state.setSet( segment );
                    flowpipe.push_back( state ); } ),
				  false );
			// worker.computeTimeSuccessors( task->getInitialSet(), task->getLocation(), std::back_inserter( task->getFlowpipe() ), false );
			if ( task->getFlowpipe().size() == 0 ) {
				return TimeInformation<Number>( clockCount );
			}
			return TimeInformation<Number>( clockCount );
		}
		TimeInformation<Number> operator()( RectangularWorker<RectangularRep, Automaton>& ) {
			// Todo: rectangular worker. Should be very similar to singular case
			assert( false && "Rectangular dynamics not supported for decompositional analysis" );
			return TimeInformation<Number>{};
		}
	};

	/**
	 * @brief       Worker-visitor to compute the jump successors for the given task.
	 * @tparam      Representation      The used state set representation type.
	 * @param       task                The current task.
	 */
	struct computeSingularJumpSuccessorVisitor {
		ReachTreeNode<ComposedRep, LocationT>* task;
		void operator()( SingularWorker<SingularRep, Automaton>& worker ) {
			// todo: don't need the initial set here. Worker only uses location to compute jump successors.
			ReachTreeNode<SingularRep, LocationT> singularTask( task->getLocation(), std::visit( genericConvertAndGetVisitor<SingularRep>(), task->getInitialSet().getSet() ), task->getTimings() );
			worker.computeJumpSuccessors( singularTask );
		}
		void operator()( RectangularWorker<RectangularRep, Automaton>& ) {
			// todo
			return;
		}
		void operator()( LTIWorker<LTIRep, Automaton>& ) {
			assert( false && "Singular jump successor computation called for non-singular subspace." );
		}
		void operator()( DiscreteWorker<DiscreteRep, Automaton>& ) {
			assert( false && "Singular jump successor computation called for non-singular subspace." );
		}
	};

	/**
	 * @brief       Worker-visitor to get the jump successors for the given transition in singular subspaces.
	 * @tparam      Representation      The used state set representation type.
	 * @param       transition          The transition for which to get successors.
	 * @return      The jump successor as Representation set.
	 */
	struct getJumpSuccessorVisitor {
		Transition<LocationT>* transition;
		std::vector<IndexedValuationSet<ComposedRep>> predecessors{};
		std::vector<TimedValuationSet<ComposedRep>> operator()( SingularWorker<SingularRep, Automaton>& worker ) {
			auto it = worker.getJumpSuccessorSets().find( transition );
			if ( it != worker.getJumpSuccessorSets().end() ) {
				auto successorList = it->second;
				assert( successorList.size() == 1 );
				ComposedRep succ;
				succ.setSet( successorList[0] );
				return { { succ, carl::Interval<SegmentInd>( 0 ) } };
			} else {
				return { { ComposedRep::Empty(), carl::Interval<SegmentInd>( 0 ) } };
			}
		}
		std::vector<TimedValuationSet<ComposedRep>> operator()( RectangularWorker<RectangularRep, Automaton>& ) {
			// todo
			return { { ComposedRep::Empty(), carl::Interval<SegmentInd>( 0 ) } };
		}
		std::vector<TimedValuationSet<ComposedRep>> operator()( LTIWorker<LTIRep, Automaton>& worker ) {
			std::vector<IndexedValuationSet<LTIRep>> ltiPredecessors;
			std::transform( predecessors.begin(), predecessors.end(), std::back_inserter( ltiPredecessors ), [=]( auto& indexedSegment ) {
				return IndexedValuationSet<LTIRep>{ std::visit(
														  genericConvertAndGetVisitor<LTIRep>(), indexedSegment.valuationSet.getSet() ),
													indexedSegment.index };
			} );
			auto workerRes = worker.computeJumpSuccessorsForGuardEnabled( ltiPredecessors, transition );
			std::vector<TimedValuationSet<ComposedRep>> res;
			std::transform( workerRes.begin(), workerRes.end(), std::back_inserter( res ), [=]( auto& timedSegment ) {
				ComposedRep succ;
				succ.setSet( timedSegment.valuationSet );
				return TimedValuationSet<ComposedRep>{ succ, timedSegment.time };
			} );
			return res;
		}
		std::vector<TimedValuationSet<ComposedRep>> operator()( DiscreteWorker<DiscreteRep, Automaton>& worker ) {
			auto [containment, successor] = worker.computeJumpSuccessorsForGuardEnabled(
				  std::visit( genericConvertAndGetVisitor<DiscreteRep>(), predecessors[0].valuationSet.getSet() ), transition );
			if ( containment == CONTAINMENT::NO ) return { { ComposedRep::Empty(), carl::Interval<SegmentInd>( 0 ) } };
			ComposedRep succ;
			succ.setSet( successor );
			return { { succ, carl::Interval<SegmentInd>( 0 ) } };
		}
	};

	struct LtiJumpSuccessorGen;
	struct LtiSegmentGen;

	std::vector<std::vector<ReachTreeNode<ComposedRep, LocationT>>> makeDecompositionalRoots( HybridAutomaton<Number> const& ha, Decomposition decomposition ) {
		std::vector<std::vector<ReachTreeNode<ComposedRep, LocationT>>> roots{};
		// for each initial set, create one vector (of size #subspaces) of nodes
		for ( auto const& [location, condition] : ha.getInitialStates() ) {
			std::vector<ReachTreeNode<ComposedRep, LocationT>> nodeVector;
			for ( std::size_t subspace = 0; subspace < decomposition.subspaces.size(); ++subspace ) {
				ComposedRep initialSet{};
				switch ( decomposition.subspaceTypes[subspace] ) {
					case DynamicType::discrete:
						initialSet.setSet( DiscreteRep{ condition.getMatrix( subspace ), condition.getVector( subspace ) } );
						break;
					case DynamicType::affine:
						[[fallthrough]];
					case DynamicType::linear:
						initialSet.setSet( LTIRep{ condition.getMatrix( subspace ), condition.getVector( subspace ) } );
						break;
					case DynamicType::timed:
						[[fallthrough]];
					case DynamicType::singular:
						initialSet.setSet( SingularRep{ condition.getMatrix( subspace ), condition.getVector( subspace ) } );
						break;
					case DynamicType::rectangular:
						initialSet.setSet( RectangularRep{ condition.getMatrix( subspace ), condition.getVector( subspace ) } );
						break;
					default:
						assert( false );
				}
				ReachTreeNode<ComposedRep, LocationT> node{ location, initialSet, carl::Interval<SegmentInd>{ 0, 0 } };
				nodeVector.push_back( std::move( node ) );
			}
			roots.push_back( std::move( nodeVector ) );
		}
		return roots;
	}

	/**
	 * @brief       Initialize workers for the subspaces.
	 * @return      The initizalized workers as vector of variants.
	 */
	auto initializeWorkers( std::vector<TimeTransformationCache<LocationT>>& cache ) -> std::vector<WorkerVariant>;

	/**
	 * @brief       Preliminary check that nodes are consistent (e.g. no initial set is empty).
	 * @param       currentNodes    The current reachtree-nodes to analyze.
	 * @return      `true` if all checks pass, `false` otherwise.
	 */
	bool checkConsistency( NodeVector& currentNodes );

	/**
	 * @brief       Compute time successors in all subspaces.
	 * @detail 		The computed time successors are stored as flowpipes in the nodes.
	 * @param       currentNodes    The current reachtree-nodes to store the successor sets.
	 * @param       workers         The vector of worker variants to use for computation.
	 * @return      The clock intervals where all subspaces satisfy their respective invariants.
	 */
	auto computeTimeSuccessorsGetEnabledTime(
		  NodeVector& currentNodes,
		  std::vector<WorkerVariant>& workers,
		  std::size_t clockIndex )
		  -> TimeInformation<Number>;

	/**
	 * @brief       Reset unused clocks to zero.
	 * @param       segment         The segment for which to reset clocks.
	 * @param       clockIndex      The current clockIndex. All clocks with higher index are reset.
	 */
	void resetUnusedClocks( ComposedRep& segment, std::size_t clockIndex );

	/**
	 * @brief       Intersect computed segments with clock values and update flowpipes.
	 * @detail 		The segments are intersected in place.
	 * @param       currentNodes    The current reachtree-nodes where the flowpipes are stored.
	 * @param       clock           The time intervals to intersect with.
	 */
	void intersectSubspacesWithClock(
		  NodeVector& currentNodes,
		  TimeInformation<Number>& clock );

	/**
	 * @brief       Remove segments that are beyond a time horizon reachable in all subspaces for lightweight synchronization.
	 * @details     Get the minimum number of segments that every flowpipe has and in every
	 *              subspace delete segments with a higher index (e.g. if some subspace has
	 *              3 segments then segments 4,5... will be removed in all subspaces.)
	 * @param       currentNodes    Nodes that hold the flowpipe segments
	 */
	void removeRedundantSegments( NodeVector& currentNodes );

	/**
	 * @brief       Check if intersection with a bad state is empty.
	 * @param       currentNodes            The current reachtree-nodes where the flowpipes are stored.
	 * @param       dependencies            The dependencies on the initial variables.
	 * @param       badState                The bad state condition to check.
	 * @return      `true` if the bad state is not reachable and `false` otherwise.
	 */
	bool isSafe(
		  const NodeVector& currentNodes,
		  const Condition<Number>& dependencies,
		  const Condition<Number>& badState );

	/**
	 * @brief       Compute jump successors and reset unused clocks to zero.
	 * @param       nodes           Current nodes
	 * @param       workers         The vector of worker variants to use for computation.
	 * @param       transition      The transition to get successors for.
	 * @param       clockIndex      The currently used clock index. Clocks with higher index are reset after the jump.
	 * @return      Vector of jump successors as map { subspace (index) : reset jump successor (representation) }
	 */
	auto getJumpSuccessors(
		  const NodeVector& nodes,
		  std::vector<WorkerVariant> workers,
		  Transition<LocationT>* trans,
		  std::size_t clockIndex )
		  -> std::vector<SubspaceJumpSuccessors<ComposedRep>>;

	/**
	 * @brief       Get the singular jump successors for a transition and the clock values where all successors satisfy the invariant.
	 * @param       nodes           Current nodes
	 * @param       workers         The vector of worker variants to use for computation.
	 * @param       transition      The transition to get successors for.
	 * @param       clockIndex      The currently used clock index. Clocks with higher index are reset after the jump.
	 * @return      Pair of clock values where the jump is enabled and the jump successors in the singular subspaces.
	 */
	auto getSingularJumpSuccessors(
		  const NodeVector& nodes,
		  std::vector<WorkerVariant>& workers,
		  Transition<LocationT>* trans,
		  std::size_t clockIndex )
		  -> std::pair<TimeInformation<Number>, SubspaceSets>;

	/**
	 * @brief       Get the discrete jump successors for a transition.
	 * @param       nodes           Current nodes
	 * @param       workers         The vector of worker variants to use for computation.
	 * @param       transition      The transition to get successors for.
	 * @return      The jump successors in the discrete subspaces after applying the reset.
	 */
	auto getDiscreteJumpSuccessors(
		  const NodeVector& nodes,
		  std::vector<WorkerVariant>& workers,
		  Transition<LocationT>* trans )
		  -> SubspaceSets;

	/**
	 * @brief       Get the jump successors in the segmented subspaces for a transition.
	 * @param       nodes           Current nodes
	 * @param       workers         The vector of worker variants to use for computation.
	 * @param       transition      The transition to get successors for.
	 * @param       clockIndex      The currently used clock index. Clocks with higher index are reset after the jump.
	 * @return      Vector of jump successors as map { subspace (index) : reset jump successor (representation) }
	 */
	auto getSegmentedJumpSuccessors(
		  const NodeVector& nodes,
		  std::vector<WorkerVariant>& workers,
		  Transition<LocationT>* trans,
		  const TimeInformation<Number>& enabledTime,
		  std::size_t clockIndex )
		  -> std::vector<SubspaceJumpSuccessors<ComposedRep>>;

	/**
	 * @brief 		Reset all clocks to zero and synchronize subspaces by equalizing clocks and using the dependencies.
	 * @param 		sets 			Unsynchronized jump successor sets in the subspaces before clock reset.
	 * @param 		dependencies 	Initial dependencies between subspaces.
	 * @return 		Pair of new dependencies after synchronization and the jump successors with reset clocks.
	 */
	auto synchronizeAndResetClocks(
		  const RepVector& sets,
		  const Condition<Number>& dependencies )
		  -> std::pair<Condition<Number>, RepVector>;

  protected:
	std::deque<detail::decompositionalQueueEntry<ComposedRep, LocationT>> mWorkQueue;  // holds the tasks that still need to be computed
	Automaton const* mHybridAutomaton;												   // holds a pointer to the decomposed automaton
	Decomposition mDecomposition;													   // holds decomposition information corresponding to the automaton
	Decomposition mDecompositionWithoutDiscrete;									   // Decomposition with non-discrete subspaces. Used to get indices for synchroniziation without discrete subspaces
	std::size_t mClockCount;														   // holds the number of additional clocks in the (singular) subspaces
	FixedAnalysisParameters mFixedParameters;										   // holds common analysis parameters for all analyzers
	AnalysisParameters mParameters;													   // holds analyzer specific parameters
	std::vector<std::size_t> mSingularSubspaces;									   // holds the singular subspace indices
	std::vector<std::size_t> mSegmentedSubspaces;									   // holds the subspaces which have more than one segment as time successors (e.g. non-singular)
	std::vector<std::size_t> mDiscreteSubspaces;									   // holds subspaces with discrete dynamics
	std::vector<std::vector<ReachTreeNode<ComposedRep, LocationT>>> mRoots;
	std::vector<ReachTreeNode<Condition<Number>, LocationT>> mDependencyRoots;	// holds roots of reach tree that contains dependency information

	tNumber const mGlobalTimeHorizon = ( mFixedParameters.jumpDepth + 1 ) * mFixedParameters.localTimeHorizon;
	TimeInformation<Number> const mGlobalTimeInterval = TimeInformation<Number>( mClockCount, Number( 0 ), carl::convert<tNumber, Number>( mGlobalTimeHorizon ) );
};

}  // namespace hypro

#include "DecompositionalAnalyzer.tpp"
