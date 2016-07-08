//
// Created by stefan on 06.07.16.
//

#pragma once

namespace hypro {
	namespace reachability {

		template<typename Number>
		using initialSet = boost::tuple<unsigned, State<Number>>;

		template <typename Number>
		class Reach<Number, SupportFunction<Number>> {
		private:
			HybridAutomaton<Number> mAutomaton;
			ReachabilitySettings<Number> mSettings;
			std::size_t mCurrentLevel;
			Number mBloatingFactor = 0.00001;
			std::map<unsigned, std::vector<flowpipe_t<SupportFunction<Number>>>> mReachableStates;
			std::queue<initialSet<Number>> mWorkingQueue;
			Plotter<Number>& plotter = Plotter<Number>::getInstance();

			mutable bool mIntersectedBadStates;

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
			std::vector<std::pair<unsigned, flowpipe_t<SupportFunction<Number>>>> computeForwardReachability();

			/**
			 * @brief Computes the forward time closure (FTC) of the given valuation in the respective location.
			 * @details [long description]
			 *
			 * @param _loc The location in which the FTC is to be computed.
			 * @param _val The valuation which is initial in the respective location.
			 *
			 * @return The id of the computed flowpipe.
			 */
			flowpipe_t<SupportFunction<Number>> computeForwardTimeClosure( const hypro::State<Number>& _state );


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
			void processDiscreteBehaviour( const std::vector<boost::tuple<Transition<Number>*, State<Number>>>& _newInitialSets );

			/**
			 * @brief Checks, whether the passed transition is enabled by the passed valuation. Sets the result to be the intersection of the guard and the valuation.
			 * @details [long description]
			 *
			 * @param _trans The transition, which is to be enabled.
			 * @param _val The valuation possibly enabling the passed transition.
			 * @param result At the end of the method this holds the result of the intersection of the guard and the valuation.
			 * @return True, if the transition is enabled, false otherwise.
			 */
			bool intersectGuard( hypro::Transition<Number>* _trans, const State<Number>& _segment, State<Number>& result );

			/**
			 * @brief Printing method for a flowpipe. Prints every segment.
			 *
			 * @param _flowpipe The flowpipe to be printed.
			 */
			void printFlowpipe( const flowpipe_t<SupportFunction<Number>>& _flowpipe ) const;

			/**
			 * @brief Printing method for a flowpipe. Prints only the first and the last segment.
			 *
			 * @param _flowpipe The flowpipe to be printed.
			 */
			void printFlowpipeReduced( const flowpipe_t<SupportFunction<Number>>& _flowpipe ) const;
		private:

			matrix_t<Number> computeTrafoMatrix( hypro::Location<Number>* _loc ) const;
			boost::tuple<bool, State<Number>, std::shared_ptr<const lintrafoParameters<Number>>> computeFirstSegment( const State<Number>& _state ) const;
			bool intersectBadStates( const State<Number>& _state, const SupportFunction<Number>& _segment ) const;
		};

	}  // namespace reachability
}  // namespace hypro

#include "Reach_SF.tpp"
