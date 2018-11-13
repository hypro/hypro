#include "Reach.h"
#include <chrono>

namespace hypro {
namespace reachability {

	using clock = std::chrono::high_resolution_clock;
	using timeunit = std::chrono::microseconds;

	template<typename Number, typename ReacherSettings>
	Reach<Number,ReacherSettings>::Reach( const HybridAutomaton<Number, State_t<Number>>& _automaton, const ReachabilitySettings& _settings)
		: mAutomaton( _automaton ), mSettings(_settings), mCurrentLevel(0), mIntersectedBadStates(false) {
			//mAutomaton.addArtificialDimension();
		}


	template<typename Number, typename ReacherSettings>
	std::vector<std::pair<unsigned, flowpipe_t<Number>>> Reach<Number,ReacherSettings>::computeForwardReachability() {
		// set up working queue -> add initial states
		// collect all computed reachable states
		std::vector<std::pair<unsigned, flowpipe_t<Number>>> collectedReachableStates;

		for ( const auto& state : mAutomaton.getInitialStates() ) {
			if(int(mCurrentLevel) <= mSettings.jumpDepth || mSettings.jumpDepth < 0){
				// Convert representation in state from matrix and vector to used representation type.
				State_t<Number> s;
				s.setLocation(state.second.getLocation());

				if(state.second.getSetType(0) != mType) {
					TRACE("hypro.reacher.preprocessing","Type is: " << state.second.getSetType(0) << ", requested type is: " << mType);
					switch(mType){
						case representation_name::box: {
							s.setSetDirect(boost::apply_visitor(genericConversionVisitor<typename State_t<Number>::repVariant, Box<Number>>(), state.second.getSet()));
							break;
						}
						case representation_name::polytope_h: {
							s.setSetDirect(boost::apply_visitor(genericConversionVisitor<typename State_t<Number>::repVariant, HPolytope<Number>>(), state.second.getSet()));
							break;
						}
						case representation_name::polytope_v: {
							s.setSetDirect(boost::apply_visitor(genericConversionVisitor<typename State_t<Number>::repVariant, VPolytope<Number>>(), state.second.getSet()));
							break;
						}
						case representation_name::support_function: {
							s.setSetDirect(boost::apply_visitor(genericConversionVisitor<typename State_t<Number>::repVariant, SupportFunction<Number>>(), state.second.getSet()));
							break;
						}
						case representation_name::zonotope: {
							s.setSetDirect(boost::apply_visitor(genericConversionVisitor<typename State_t<Number>::repVariant, Zonotope<Number>>(), state.second.getSet()));
							break;
						}
						case representation_name::constraint_set: {
							s.setSetDirect(boost::apply_visitor(genericConversionVisitor<typename State_t<Number>::repVariant, ConstraintSet<Number>>(), state.second.getSet()));
							break;
						}
						#ifdef HYPRO_USE_PPL
						case representation_name::ppl_polytope: {
							s.setSetDirect(boost::apply_visitor(genericConversionVisitor<typename State_t<Number>::repVariant, Polytope<Number>>(), state.second.getSet()));
							break;
						}
						#endif

						default: {
							assert(false);
						}
					}
					TRACE("hypro.reacher.preprocessing","convert.");
					//s.setSetDirect(boost::apply_visitor(genericConversionVisitor<typename State_t<Number>::repVariant, Number>(mType), s.getSet()));
					s.setSetType(mType);
					TRACE("hypro.reacher.preprocessing","Type after conversion is " << s.getSetType(0));
				} else {
					TRACE("hypro.reacher.preprocessing","Types match, do nothing.");
					assert(boost::apply_visitor(genericTypeVisitor(), state.second.getSet()) == mType);
					s.setSetDirect(state.second.getSet());
					s.setSetType(boost::apply_visitor(genericTypeVisitor(), state.second.getSet()));
				}

				DEBUG("hypro.reacher","Adding initial set of type " << mType << ", current queue size (before) is " << mWorkingQueue.size());
				assert(mType == s.getSetType());

				s.setTimestamp(carl::Interval<tNumber>(0));
				mWorkingQueue.push_back(initialSet<Number>(mCurrentLevel, s));
			}
		}

		if(ReacherSettings::printStatus) {
			std::cout << std::endl << "Queue size: " << mWorkingQueue.size() << std::flush;
		}

		TRACE("hypro.reacher","working queue size: " << mWorkingQueue.size());

		if(ReacherSettings::printStatus) {
			std::cout << std::endl;
		}
		while ( !mWorkingQueue.empty() ) {
			initialSet<Number> nextInitialSet = mWorkingQueue.front();
			mWorkingQueue.pop_front();
			TRACE("hypro.reacher","working queue after pop: " << mWorkingQueue.size());
			if(ReacherSettings::printStatus) {
				std::cout << "\rQueue size: " << mWorkingQueue.size() << std::flush;
			}

			mCurrentLevel = boost::get<0>(nextInitialSet);
			INFO("hypro.reacher","Depth " << mCurrentLevel << ", Location: " << boost::get<1>(nextInitialSet).getLocation()->getName());
			assert(int(mCurrentLevel) <= mSettings.jumpDepth);
			TRACE("hypro.reacher","Obtained set of type " << boost::get<1>(nextInitialSet).getSetType() << ", requested type is " << mType);
			flowpipe_t<Number> newFlowpipe = computeForwardTimeClosure(boost::get<1>(nextInitialSet));

			collectedReachableStates.emplace_back(std::make_pair(boost::get<1>(nextInitialSet).getLocation()->hash(), newFlowpipe));
		}

		return collectedReachableStates;
	}


	template<typename Number, typename ReacherSettings>
	flowpipe_t<Number> Reach<Number,ReacherSettings>::computeForwardTimeClosure( const State_t<Number>& _state ) {
		assert(!_state.getTimestamp().isUnbounded());
#ifdef REACH_DEBUG
		INFO("hypro.reacher", "Location: " << _state.getLocation()->hash());
		INFO("hypro.reacher", "Location printed : " << *(_state.getLocation()));
		INFO("hypro.reacher", "Time step size: " << mSettings.timeStep);
		INFO("hypro.reacher", "Initial valuation: " << _state);
		//std::cout << boost::get<State_t<Number>>(_state) << std::endl;
		//std::cout << _state << std::endl;
#endif
		// new empty Flowpipe
		flowpipe_t<Number> flowpipe;
		std::vector<boost::tuple<Transition<Number>*, State_t<Number>>> nextInitialSets;

		boost::tuple<hypro::CONTAINMENT, State_t<Number>, matrix_t<Number>, vector_t<Number>, Box<Number>> initialSetup = computeFirstSegment<Number,State_t<Number>>(_state, mSettings.timeStep);
#ifdef REACH_DEBUG
		INFO("hypro.reacher", "Valuation fulfills Invariant?: " << boost::get<0>(initialSetup));
#endif
		if ( boost::get<0>(initialSetup) != CONTAINMENT::NO ) { // see convenienceOperators for details
			assert(!boost::get<1>(initialSetup).getTimestamp().isUnbounded());
			bool noFlow = false;

			// if the location does not have dynamic behaviour, check guards and exit loop.
			if(boost::get<2>(initialSetup) == matrix_t<Number>::Identity(boost::get<2>(initialSetup).rows(), boost::get<2>(initialSetup).cols()) &&
				boost::get<3>(initialSetup) == vector_t<Number>::Zero(boost::get<3>(initialSetup).rows())) {
				noFlow = true;
				// Collect potential new initial states from discrete behaviour.
				if(int(mCurrentLevel) <= mSettings.jumpDepth || mSettings.jumpDepth < 0) {
					INFO("hypro.reacher", "-- Checking Transitions from initial!");
					checkTransitions(_state, carl::Interval<tNumber>(tNumber(0),mSettings.timeBound), nextInitialSets);
				}
			}

			// insert first Segment into the empty flowpipe
			State_t<Number> currentSegment;
			if(noFlow) {
				currentSegment = _state;
			} else {
				currentSegment = boost::get<1>(initialSetup);
			}
			flowpipe.push_back( currentSegment );

			// Check for bad states intersection. The first segment is validated against the invariant, already.
			if(intersectBadStates(currentSegment)){
				// clear queue to stop whole algorithm
				while(!mWorkingQueue.empty()){
					mWorkingQueue.pop_front();
				}
				return flowpipe;
			}

			// Set after linear transformation
			State_t<Number> nextSegment;
#ifdef USE_SYSTEM_SEPARATION
			State_t<Number> autonomPart = currentSegment;
#ifdef USE_ELLIPSOIDS
			// Easy to addapt to any State_t<Number> use ellipsoid for the idea of my masterthesis here
			Ellipsoid<Number> nonautonomPart(mBloatingFactor, currentSegment.dimension());
			Ellipsoid<Number> totalBloating = nonautonomPart;
#else
			Ellipsoid<Number> nonautonomPartAsEllispsoid(mBloatingFactor, currentSegment.dimension());
			State_t<Number> nonautonomPart = State_t<Number>(nonautonomPartAsEllispsoid);
			State_t<Number> totalBloating = nonautonomPart;
#endif
#endif
#ifdef REACH_DEBUG
			if(!noFlow){
				INFO("hypro.reacher", "--- Loop entered ---");
			}
#endif

			// the first segment covers one time step already
			tNumber currentLocalTime = mSettings.timeStep;
			// intersection of bad states and violation of invariant is handled inside the loop
			while( !noFlow && currentLocalTime <= mSettings.timeBound ) {
				INFO("hypro.reacher","Time: " << std::setprecision(4) << std::setw(8) << fixed << carl::toDouble(currentLocalTime));
				// Verify transitions on the current set.
				if(int(mCurrentLevel) < mSettings.jumpDepth || mSettings.jumpDepth < 0) {
					//State_t<Number> currentState = _state;
					State_t<Number> currentState = currentSegment;
					//std::cout << "-- Checking Transitions!" << std::endl;
					checkTransitions(currentState, currentState.getTimestamp(), nextInitialSets);
				}

				// perform linear transformation on the last segment of the flowpipe
#ifdef USE_SYSTEM_SEPARATION
				autonomPart = autonomPart.partiallyApplyTimeStep( ConstraintSet<Number>(boost::get<2>(initialSetup), boost::get<3>(initialSetup)), mSettings.timeStep, 0 );
#ifdef USE_ELLIPSOIDS
				if (mBloatingFactor != 0){
					Representation temp = Representation(totalBloating);
					nextSegment = autonomPart.minkowskiSum(temp);
				} else {
					nextSegment = autonomPart;
				}
#else
				if (mBloatingFactor != 0){
					nextSegment = autonomPart.minkowskiSum(totalBloating);
				} else {
					nextSegment = autonomPart;
				}
#endif
				// nonautonomPart = nonautonomPart.linearTransformation( boost::get<2>(initialSetup), vector_t<Number>::Zero(autonomPart.dimension()));
				nonautonomPart = nonautonomPart.linearTransformation(boost::get<2>(initialSetup));
				totalBloating = totalBloating.minkowskiSum(nonautonomPart);
#else
				nextSegment =  currentSegment.partiallyApplyTimeStep(ConstraintSet<Number>(boost::get<2>(initialSetup), boost::get<3>(initialSetup)), mSettings.timeStep, 0);
#endif
				// extend flowpipe (only if still within Invariant of location)
				std::pair<hypro::CONTAINMENT, State_t<Number>> newSegment = nextSegment.satisfies( _state.getLocation()->getInvariant());

#ifdef REACH_DEBUG
				INFO("hypro.reacher", "Next Flowpipe Segment: " << newSegment.second);
				INFO("hypro.reacher", "still within Invariant?: " << newSegment.first);
#endif
				if ( newSegment.first != CONTAINMENT::NO ) {
					flowpipe.push_back( newSegment.second );
					if(intersectBadStates(newSegment.second)){
						// clear queue to stop whole algorithm
						while(!mWorkingQueue.empty()){
							mWorkingQueue.pop_front();
						}
						return flowpipe;
					}
					// update currentSegment
					currentSegment = newSegment.second;
				} else {
					// the flowpipe does not longer satisfy the invariant -> quit loop
					break;
				}
				currentLocalTime += mSettings.timeStep;
			}
#ifdef REACH_DEBUG
			if(!noFlow){
				INFO("hypro.reacher", "--- Loop left ---");
			}
			INFO("hypro.reacher", "flowpipe: " << flowpipe.size() << " Segments computed.");
			INFO("hypro.reacher", "Process " << nextInitialSets.size() << " new initial sets.");
			INFO("hypro.reacher", "current level: " << mCurrentLevel);
#endif
			// The loop terminated correctly (i.e. no bad states were hit), process discrete behavior.
			assert(nextInitialSets.empty() || (int(mCurrentLevel) < mSettings.jumpDepth || mSettings.jumpDepth < 0));
			if(int(mCurrentLevel) < mSettings.jumpDepth || mSettings.jumpDepth < 0){
				processDiscreteBehaviour(nextInitialSets);
			}
			return flowpipe;
		} else {
			// return an empty flowpipe
			return flowpipe;
		}
	}

} // namespace reachability
} // namespace hypro
