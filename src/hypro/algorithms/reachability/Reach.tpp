#include "Reach.h"
#include <chrono>

namespace hypro {
namespace reachability {

	using clock = std::chrono::high_resolution_clock;
	using timeunit = std::chrono::microseconds;

	template<typename Number, typename Representation>
	Reach<Number,Representation>::Reach( const HybridAutomaton<Number>& _automaton, const ReachabilitySettings<Number>& _settings)
		: mAutomaton( _automaton ), mSettings(_settings), mCurrentLevel(0), mIntersectedBadStates(false) {
			//mAutomaton.addArtificialDimension();
		}


	template<typename Number, typename Representation>
	std::vector<std::pair<unsigned, flowpipe_t<Representation>>> Reach<Number,Representation>::computeForwardReachability() {
		// set up working queue -> add initial states
		// collect all computed reachable states
		std::vector<std::pair<unsigned, flowpipe_t<Representation>>> collectedReachableStates;

		for ( const auto& state : mAutomaton.initialStates() ) {
			if(mCurrentLevel <= mSettings.jumpDepth){
				// Convert representation in state from matrix and vector to used representation type.
				State<Number> s;
				s.location = state.second.location;

				HPolytope<Number> tmpSet(state.second.set.first, state.second.set.second);
				representation_name type = Representation::type();
				switch(type){
					case representation_name::box: {
						s.set = Converter<Number>::toBox(tmpSet);
						DEBUG("Adding initial set " << boost::get<Box<Number>>(s.set));
						break;
					}
					case representation_name::polytope_h: {
						s.set = tmpSet;
						DEBUG("Adding initial set " << boost::get<HPolytope<Number>>(s.set));
						break;
					}
					case representation_name::polytope_v: {
						s.set = Converter<Number>::toVPolytope(tmpSet);
						DEBUG("Adding initial set " << boost::get<VPolytope<Number>>(s.set));
						break;
					}
					case representation_name::zonotope: {
						s.set = Converter<Number>::toZonotope(tmpSet);
						DEBUG("Adding initial set " << boost::get<Zonotope<Number>>(s.set));
						break;
					}
					case representation_name::support_function: {
						s.set = Converter<Number>::toSupportFunction(tmpSet);
						DEBUG("Adding initial set " << boost::get<SupportFunction<Number>>(s.set));
						break;
					}
					case representation_name::ppl_polytope: {
						s.set = Representation(state.second.set.first, state.second.set.second);
						DEBUG("Adding initial set " << boost::get<Polytope<Number>>(s.set));
						break;
					}
					default: {
						s.set = Representation(state.second.set.first, state.second.set.second);
					}
				}
				s.timestamp = carl::Interval<Number>(0);
				mWorkingQueue.emplace_back(initialSet<Number>(mCurrentLevel, s));
			}
		}

		while ( !mWorkingQueue.empty() ) {
			initialSet<Number> nextInitialSet = mWorkingQueue.front();
			mWorkingQueue.pop_front();

			mCurrentLevel = boost::get<0>(nextInitialSet);
			assert(mCurrentLevel <= mSettings.jumpDepth);
			INFO("Depth " << mCurrentLevel << ", Location: " << boost::get<1>(nextInitialSet).location->id());
			flowpipe_t<Representation> newFlowpipe = computeForwardTimeClosure(boost::get<1>(nextInitialSet));

			collectedReachableStates.emplace_back(std::make_pair(boost::get<1>(nextInitialSet).location->id(), newFlowpipe));
		}

		return collectedReachableStates;
	}


	template<typename Number, typename Representation>
	flowpipe_t<Representation> Reach<Number,Representation>::computeForwardTimeClosure( const State<Number>& _state ) {
		assert(!_state.timestamp.isUnbounded());
#ifdef REACH_DEBUG
		std::cout << "Location: " << _state.location->id() << std::endl;
		std::cout << "Location printed : " << *_state.location << std::endl;
		std::cout << "Time step size: " << mSettings.timeStep << std::endl;
		std::cout << "Initial valuation: " << std::endl;
		boost::get<Representation>(_state.set).print();
#endif
		// new empty Flowpipe
		flowpipe_t<Representation> flowpipe;
		std::vector<boost::tuple<Transition<Number>*, State<Number>>> nextInitialSets;

		boost::tuple<bool, State<Number>, TrafoParameters<Number>> initialSetup = computeFirstSegment(_state);
#ifdef REACH_DEBUG
		std::cout << "Valuation fulfills Invariant?: ";
		std::cout << boost::get<0>(initialSetup) << std::endl;
#endif
		if ( boost::get<0>(initialSetup) ) {
			assert(!boost::get<1>(initialSetup).timestamp.isUnbounded());
			bool noFlow = false;

			// if the location does not have dynamic behaviour, check guards and exit loop.
			if(boost::get<2>(initialSetup).matrix() == matrix_t<Number>::Identity(boost::get<2>(initialSetup).matrix().rows(), boost::get<2>(initialSetup).matrix().cols()) &&
				boost::get<2>(initialSetup).vector() == vector_t<Number>::Zero(boost::get<2>(initialSetup).vector().rows())) {
				noFlow = true;
				// Collect potential new initial states from discrete behaviour.
				if(mCurrentLevel < mSettings.jumpDepth) {
					checkTransitions(_state, carl::Interval<Number>(Number(0),mSettings.timeBound), nextInitialSets);
				}
			}

			// insert first Segment into the empty flowpipe
			Representation currentSegment;
			if(noFlow) {
				currentSegment = boost::get<Representation>(_state.set);
			} else {
				currentSegment = boost::get<Representation>(boost::get<1>(initialSetup).set);
			}
			flowpipe.push_back( currentSegment );

			// Check for bad states intersection. The first segment is validated against the invariant, already.
			if(intersectBadStates(_state, currentSegment)){
				// clear queue to stop whole algorithm
				while(!mWorkingQueue.empty()){
					mWorkingQueue.pop_front();
				}
				return flowpipe;
			}

			// Set after linear transformation
			Representation nextSegment;
#ifdef USE_SYSTEM_SEPARATION
			Representation autonomPart = currentSegment;
#ifdef USE_ELLIPSOIDS
			// Easy to addapt to any Representation use ellipsoid for the idea of my masterthesis here
			Ellipsoid<Number> nonautonomPart(mBloatingFactor, currentSegment.dimension());
			Ellipsoid<Number> totalBloating = nonautonomPart;
#else
			Ellipsoid<Number> nonautonomPartAsEllispsoid(mBloatingFactor, currentSegment.dimension());
			Representation nonautonomPart = Representation(nonautonomPartAsEllispsoid);
			Representation totalBloating = nonautonomPart;
#endif
#endif
#ifdef REACH_DEBUG
			if(!noFlow){
				std::cout << "--- Loop entered ---" << std::endl;
			}
#endif

			// the first segment covers one time step already
			Number currentLocalTime = mSettings.timeStep;
			// intersection of bad states and violation of invariant is handled inside the loop
			while( !noFlow && currentLocalTime <= mSettings.timeBound ) {
				INFO("Time: " << std::setprecision(4) << std::setw(8) << fixed << carl::toDouble(currentLocalTime));
				// Verify transitions on the current set.
				if(mCurrentLevel <= mSettings.jumpDepth) {
					State<Number> guardSatisfyingState;
					State<Number> currentState = _state;
					currentState.set = currentSegment;
					currentState.timestamp += carl::Interval<Number>(currentLocalTime-mSettings.timeStep,currentLocalTime);
					currentState.timestamp = currentState.timestamp.intersect(carl::Interval<Number>(Number(0), mSettings.timeBound));
					checkTransitions(currentState, currentState.timestamp, nextInitialSets);
				}

				// perform linear transformation on the last segment of the flowpipe
#ifdef USE_SYSTEM_SEPARATION
				//autonomPart = autonomPart.linearTransformation( boost::get<2>(initialSetup), boost::get<3>(initialSetup) );
				autonomPart = applyLinearTransformation( autonomPart, boost::get<2>(initialSetup) );
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
				TrafoParameters<Number> tmpParameters(boost::get<2>(initialSetup));
				tmpParameters.setVector(vector_t<Number>::Zero(autonomPart.dimension()));
				nonautonomPart = applyLinearTransformation( nonautonomPart, tmpParameters);
				totalBloating = totalBloating.minkowskiSum(nonautonomPart);
#else
				nextSegment =  applyLinearTransformation(currentSegment, boost::get<2>(initialSetup) );
#endif
				// extend flowpipe (only if still within Invariant of location)
				std::pair<bool, Representation> newSegment = nextSegment.satisfiesHalfspaces( _state.location->invariant().mat, _state.location->invariant().vec );
#ifdef REACH_DEBUG
				std::cout << "Next Flowpipe Segment: " << newSegment.second << std::endl;
				std::cout << "still within Invariant?: ";
				std::cout << newSegment.first << std::endl;
#endif
				if ( newSegment.first ) {
					flowpipe.push_back( newSegment.second );
					if(intersectBadStates(_state, newSegment.second)){
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
				std::cout << "--- Loop left ---" << std::endl;
			}
			std::cout << "flowpipe: " << flowpipe.size() << " Segments computed." << std::endl;
			std::cout << "Process " << nextInitialSets.size() << " new initial sets." << std::endl;
#endif
			// The loop terminated correctly (i.e. no bad states were hit), process discrete behavior.
			if(mCurrentLevel < mSettings.jumpDepth){
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
