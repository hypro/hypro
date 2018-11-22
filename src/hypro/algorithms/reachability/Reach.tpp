#include "Reach.h"
#include <chrono>

namespace hypro {
namespace reachability {

	using clock = std::chrono::high_resolution_clock;
	using timeunit = std::chrono::microseconds;

	template<typename Number, typename ReacherSettings, typename State>
	Reach<Number,ReacherSettings,State>::Reach( const HybridAutomaton<Number>& _automaton, const ReachabilitySettings& _settings)
		: mAutomaton( _automaton ), mSettings(_settings), mCurrentLevel(0), mIntersectedBadStates(false) {
			//mAutomaton.addArtificialDimension();
		}

	template<typename Number, typename ReacherSettings, typename State>
	void Reach<Number,ReacherSettings,State>::initQueue() {
		for ( const auto& locationConstraintPair : mAutomaton.getInitialStates() ) {
			if(int(mCurrentLevel) <= mSettings.jumpDepth || mSettings.jumpDepth < 0){
				// Convert representation in state from matrix and vector to used representation type.
				State s;
				s.setLocation(locationConstraintPair.first);
				switch(mType){
					case representation_name::box: {
						s.setSetDirect(Converter<Number>::toBox(locationConstraintPair.second));
						break;
					}
					case representation_name::polytope_h: {
						s.setSetDirect(Converter<Number>::toHPolytope(locationConstraintPair.second));
						break;
					}
					case representation_name::polytope_v: {
						s.setSetDirect(Converter<Number>::toVPolytope(locationConstraintPair.second));
						break;
					}
					case representation_name::support_function: {
						s.setSetDirect(Converter<Number>::toSupportFunction(locationConstraintPair.second));
						break;
					}
					case representation_name::zonotope: {
						s.setSetDirect(Converter<Number>::toZonotope(locationConstraintPair.second));
						break;
					}
					case representation_name::constraint_set: {
						s.setSetDirect(locationConstraintPair.second);
						break;
					}
					#ifdef HYPRO_USE_PPL
					case representation_name::ppl_polytope: {
						s.setSetDirect(Converter<Number>::toPolytope(locationConstraintPair.second));
						break;
					}
					#endif

					default: {
						assert(false);
					}
				}
				TRACE("hypro.reacher.preprocessing","convert.");
				//s.setSetDirect(boost::apply_visitor(genericConversionVisitor<typename State::repVariant, Number>(mType), s.getSet()));
				s.setSetType(mType);
				TRACE("hypro.reacher.preprocessing","Type after conversion is " << s.getSetType(0));

				DEBUG("hypro.reacher","Adding initial set of type " << mType << ", current queue size (before) is " << mWorkingQueue.size());
				assert(mType == s.getSetType());

				s.setTimestamp(carl::Interval<tNumber>(0));
				mWorkingQueue.enqueue(std::make_unique<TaskType>(std::make_pair(mCurrentLevel, s)));
			}
		}
	}

	template<typename Number, typename ReacherSettings, typename State>
	std::vector<std::pair<unsigned, typename Reach<Number,ReacherSettings,State>::flowpipe_t>> Reach<Number,ReacherSettings,State>::computeForwardReachability() {
		// set up working queue -> add initial states
		// collect all computed reachable states
		std::vector<std::pair<unsigned, typename Reach<Number,ReacherSettings,State>::flowpipe_t>> collectedReachableStates;

		if(ReacherSettings::printStatus) {
			std::cout << std::endl << "Queue size: " << mWorkingQueue.size() << std::flush;
		}

		TRACE("hypro.reacher","working queue size: " << mWorkingQueue.size());

		if(ReacherSettings::printStatus) {
			std::cout << std::endl;
		}
		while ( !mWorkingQueue.isEmpty() ) {
			TaskTypePtr nextInitialSet = mWorkingQueue.dequeueFront();
			TRACE("hypro.reacher","working queue after pop: " << mWorkingQueue.size());
			if(ReacherSettings::printStatus) {
				std::cout << "\rQueue size: " << mWorkingQueue.size() << std::flush;
			}

			mCurrentLevel = nextInitialSet->first;
			INFO("hypro.reacher","Depth " << mCurrentLevel << ", Location: " << nextInitialSet->second.getLocation()->getName());
			assert(int(mCurrentLevel) <= mSettings.jumpDepth);
			TRACE("hypro.reacher","Obtained set of type " << nextInitialSet->second.getSetType() << ", requested type is " << mType);
			flowpipe_t newFlowpipe = computeForwardTimeClosure(nextInitialSet->second);

			collectedReachableStates.emplace_back(std::make_pair(nextInitialSet->second.getLocation()->hash(), newFlowpipe));
		}

		return collectedReachableStates;
	}


	template<typename Number, typename ReacherSettings, typename State>
	typename Reach<Number,ReacherSettings,State>::flowpipe_t Reach<Number,ReacherSettings,State>::computeForwardTimeClosure( const State& _state ) {
		assert(!_state.getTimestamp().isUnbounded());
#ifdef REACH_DEBUG
		INFO("hypro.reacher", "Location: " << _state.getLocation()->hash());
		INFO("hypro.reacher", "Location printed : " << *(_state.getLocation()));
		INFO("hypro.reacher", "Time step size: " << mSettings.timeStep);
		INFO("hypro.reacher", "Initial valuation: " << _state);
		//std::cout << boost::get<State>(_state) << std::endl;
		//std::cout << _state << std::endl;
#endif
		// new empty Flowpipe
		typename Reach<Number,ReacherSettings,State>::flowpipe_t flowpipe;
		std::vector<boost::tuple<Transition<Number>*, State>> nextInitialSets;

		boost::tuple<hypro::CONTAINMENT, State, matrix_t<Number>, vector_t<Number>, Box<Number>> initialSetup = computeFirstSegment<Number,State>(_state, mSettings.timeStep);
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
			State currentSegment;
			if(noFlow) {
				currentSegment = _state;
			} else {
				currentSegment = boost::get<1>(initialSetup);
			}
			flowpipe.push_back( currentSegment );

			// Check for bad states intersection. The first segment is validated against the invariant, already.
			if(intersectBadStates(currentSegment)){
				// clear queue to stop whole algorithm
				while(!mWorkingQueue.isEmpty()){
					mWorkingQueue.dequeueFront();
				}
				return flowpipe;
			}

			// Set after linear transformation
			State nextSegment;
#ifdef USE_SYSTEM_SEPARATION
			State autonomPart = currentSegment;
#ifdef USE_ELLIPSOIDS
			// Easy to addapt to any State use ellipsoid for the idea of my masterthesis here
			Ellipsoid<Number> nonautonomPart(mBloatingFactor, currentSegment.dimension());
			Ellipsoid<Number> totalBloating = nonautonomPart;
#else
			Ellipsoid<Number> nonautonomPartAsEllispsoid(mBloatingFactor, currentSegment.dimension());
			State nonautonomPart = State(nonautonomPartAsEllispsoid);
			State totalBloating = nonautonomPart;
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
					//State currentState = _state;
					State currentState = currentSegment;
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
				std::pair<hypro::CONTAINMENT, State> newSegment = nextSegment.satisfies( _state.getLocation()->getInvariant());

#ifdef REACH_DEBUG
				INFO("hypro.reacher", "Next Flowpipe Segment: " << newSegment.second);
				INFO("hypro.reacher", "still within Invariant?: " << newSegment.first);
#endif
				if ( newSegment.first != CONTAINMENT::NO ) {
					flowpipe.push_back( newSegment.second );
					if(intersectBadStates(newSegment.second)){
						// clear queue to stop whole algorithm
						while(!mWorkingQueue.isEmpty()){
							mWorkingQueue.dequeueFront();
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
